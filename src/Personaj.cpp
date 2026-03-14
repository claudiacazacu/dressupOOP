#include "Personaj.h"
#include "ArticolDerivate.h"
#include "Exceptions.h"
#include <list>
#include <memory>
#include <utility>

int Personaj::totalPersonaje_ = 0;

Personaj::Personaj(const std::string &nume, const std::string &nationalitate, int nivel, int sold)
    : nume_(nume), nationalitate_(nationalitate), nivel_(nivel), dulap_(15, nume), sold_(sold)
{
    if (nume_.empty())
    {
        throw InvalidInputException("Personajul trebuie sa aiba un nume");
    }
    if (nationalitate_.empty())
    {
        throw InvalidInputException("Personajul trebuie sa aiba o nationalitate");
    }
    if (nivel_ <= 0)
    {
        throw InvalidInputException("Nivelul personajului trebuie sa fie pozitiv");
    }
    if (sold_ < 0)
    {
        throw InvalidInputException("Soldul initial nu poate fi negativ");
    }

    ++totalPersonaje_;
}

Personaj::Personaj(const Personaj &other)
    : nume_(other.nume_),
      nationalitate_(other.nationalitate_),
      nivel_(other.nivel_),
      dulap_(other.dulap_),
      sold_(other.sold_)
{
    ++totalPersonaje_;
}

Personaj &Personaj::operator=(Personaj other)
{
    using std::swap;
    swap(nume_, other.nume_);
    swap(nationalitate_, other.nationalitate_);
    swap(nivel_, other.nivel_);
    dulap_.swap(other.dulap_);
    swap(sold_, other.sold_);
    return *this;
}

void Personaj::Afiseaza(std::ostream &os) const
{
    os << "Nume: " << nume_
       << " | Nationalitate: " << nationalitate_
       << " | Nivel: " << nivel_
       << " | Sold: " << sold_ << "\n";

    dulap_.Afiseaza(os);
}

void Personaj::Cumpara(std::unique_ptr<Articol> articol)
{
    if (!articol)
    {
        throw InvalidInputException("Articol invalid pentru cumparare");
    }

    if (sold_ < articol->GetPret())
    {
        throw BudgetException("articolul \"" + articol->GetNume() +
                              "\" costa " + std::to_string(articol->GetPret()) +
                              ", iar soldul disponibil este " + std::to_string(sold_));
    }

    sold_ -= articol->GetPret();
    dulap_.AdaugaArticol(std::move(articol));
}

void Personaj::AfiseazaEchipamentDeSezon(const std::string &sezon, std::ostream &os) const
{
    os << "Echipament sezon \"" << sezon << "\" al lui " << nume_ << ":\n";

    bool gasit = false;
    std::list<std::unique_ptr<Articol>>::const_iterator it;

    for (it = dulap_.GetArticole().begin(); it != dulap_.GetArticole().end(); ++it)
    {
        const Imbracaminte *im = dynamic_cast<const Imbracaminte *>((*it).get());
        if (im != nullptr && im->GetSezon() == sezon)
        {
            gasit = true;
            os << "  ";
            (*it)->Afiseaza(os);
            os << "\n";
        }
    }

    if (!gasit)
    {
        os << "  Nu exista articole de sezonul " << sezon << " in dulap.\n";
    }
}

void Personaj::AfiseazaTinutePentruEveniment(const std::string &eveniment, std::ostream &os) const
{
    os << "Recomandari pentru evenimentul \"" << eveniment << "\" pentru " << nume_ << ":\n";
    dulap_.AfiseazaPotrivitePentruEveniment(eveniment, os);
}

void Personaj::AfiseazaAnalizaInventar(const std::string &eveniment, std::ostream &os) const
{
    os << "Analiza inventar pentru " << nume_ << ":\n";
    os << "  Sold curent: " << sold_ << "\n";
    os << "  Valoare dulap: " << dulap_.CalculeazaValoareTotala() << "\n";
    os << "  Articole potrivite pentru \"" << eveniment << "\": "
       << dulap_.NumarArticolePentruEveniment(eveniment) << "\n";
}

const Dulap &Personaj::GetDulap() const noexcept
{
    return dulap_;
}

int Personaj::TotalPersonaje() noexcept
{
    return totalPersonaje_;
}

std::ostream &operator<<(std::ostream &os, const Personaj &p)
{
    p.Afiseaza(os);
    return os;
}