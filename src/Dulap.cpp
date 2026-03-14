#include "Dulap.h"
#include "Exceptions.h"

Dulap::Dulap(int capacitate, const std::string &proprietar)
    : capacitate_(capacitate), proprietar_(proprietar)
{
    if (capacitate_ <= 0)
    {
        throw InvalidInputException("Capacitatea dulapului trebuie sa fie pozitiva");
    }
}

Dulap::Dulap(const Dulap &other)
    : capacitate_(other.capacitate_), proprietar_(other.proprietar_)
{
    for (const auto &a : other.articole_)
    {
        articole_.push_back(a->clone());
    }
}

Dulap &Dulap::operator=(Dulap other)
{
    swap(other);
    return *this;
}

void Dulap::swap(Dulap &other) noexcept
{
    using std::swap;
    swap(articole_, other.articole_);
    swap(capacitate_, other.capacitate_);
    swap(proprietar_, other.proprietar_);
}

bool Dulap::EstePlin() const noexcept
{
    return static_cast<int>(articole_.size()) >= capacitate_;
}

bool Dulap::AdaugaArticol(std::unique_ptr<Articol> articol)
{
    if (!articol)
    {
        throw InvalidInputException("Nu se poate adauga un articol null in dulap");
    }
    if (EstePlin())
    {
        throw InventoryException("Dulapul este plin");
    }

    articole_.push_back(std::move(articol));
    return true;
}

int Dulap::CalculeazaValoareTotala() const noexcept
{
    int suma = 0;
    for (const auto &a : articole_)
    {
        suma += a->GetPret();
    }
    return suma;
}

void Dulap::Afiseaza(std::ostream &os) const
{
    os << "Dulapul lui " << proprietar_ << " (capacitate " << capacitate_ << ")\n";
    if (articole_.empty())
    {
        os << "  (gol)\n";
        return;
    }

    for (const auto &a : articole_)
    {
        os << "  ";
        a->Afiseaza(os);
        os << "\n";
    }
}

void Dulap::AfiseazaPotrivitePentruEveniment(const std::string &eveniment, std::ostream &os) const
{
    os << "Articole potrivite pentru evenimentul \"" << eveniment << "\":\n";
    bool gasit = false;
    for (const auto &a : articole_)
    {
        if (a->SePotrivesteLaEveniment(eveniment))
        {
            os << "  ";
            a->Afiseaza(os);
            os << "\n";
            gasit = true;
        }
    }
    if (!gasit)
    {
        os << "  Niciun articol potrivit.\n";
    }
}

size_t Dulap::NumarArticolePentruEveniment(const std::string &eveniment) const noexcept
{
    size_t total = 0;
    for (const auto &a : articole_)
    {
        if (a->SePotrivesteLaEveniment(eveniment))
        {
            ++total;
        }
    }
    return total;
}

std::ostream &operator<<(std::ostream &os, const Dulap &d)
{
    d.Afiseaza(os);
    return os;
}