#include "Dulap.h"
#include "Exceptions.h"
#include <utility>

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
    std::list<std::unique_ptr<Articol>>::const_iterator it;
    for (it = other.articole_.begin(); it != other.articole_.end(); ++it)
    {
        articole_.push_back((*it)->clone());
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
    std::list<std::unique_ptr<Articol>>::const_iterator it;
    for (it = articole_.begin(); it != articole_.end(); ++it)
    {
        suma += (*it)->GetPret();
    }
    return suma;
}

void Dulap::Afiseaza(std::ostream &os) const
{
    os << "Dulapul lui " << proprietar_ << "\n";

    if (articole_.empty())
    {
        os << "  (gol)\n";
        return;
    }

    std::list<std::unique_ptr<Articol>>::const_iterator it;
    for (it = articole_.begin(); it != articole_.end(); ++it)
    {
        os << "  ";
        (*it)->Afiseaza(os);
        os << "\n";
    }
}

void Dulap::AfiseazaPotrivitePentruEveniment(const std::string &eveniment, std::ostream &os) const
{
    os << "Articole potrivite pentru evenimentul \"" << eveniment << "\":\n";

    bool gasit = false;
    std::list<std::unique_ptr<Articol>>::const_iterator it;
    for (it = articole_.begin(); it != articole_.end(); ++it)
    {
        if ((*it)->SePotrivesteLaEveniment(eveniment))
        {
            os << "  ";
            (*it)->Afiseaza(os);
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
    std::list<std::unique_ptr<Articol>>::const_iterator it;
    for (it = articole_.begin(); it != articole_.end(); ++it)
    {
        if ((*it)->SePotrivesteLaEveniment(eveniment))
        {
            ++total;
        }
    }
    return total;
}

const std::list<std::unique_ptr<Articol>> &Dulap::GetArticole() const noexcept
{
    return articole_;
}