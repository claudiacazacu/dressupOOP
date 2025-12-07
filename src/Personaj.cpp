#include "Personaj.h"
#include "Exceptions.h"
#include "ArticolDerivate.h" // pentru Imbracaminte
#include <iostream>
#include <type_traits>

Personaj::Personaj(const std::string &nume, const std::string &nationalitate, int nivel, int sold)
    : nume_(nume), nationalitate_(nationalitate), nivel_(nivel), dulap_(15, nume), sold_(sold) {}

Personaj::Personaj(const Personaj &other)
    : nume_(other.nume_), nationalitate_(other.nationalitate_), nivel_(other.nivel_),
      dulap_(other.dulap_), sold_(other.sold_) {}

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
    os << "Nume: " << nume_ << " | Nationalitate: " << nationalitate_ << " | Nivel: " << nivel_ << " | Sold: " << sold_ << "\n";
    dulap_.Afiseaza(os);
}

bool Personaj::Cumpara(std::unique_ptr<Articol> articol)
{
    if (!articol)
        return false;
    if (sold_ < articol->GetPret())
    {
        return false;
    }
    if (dulap_.EstePlin())
    {
        return false;
    }
    sold_ -= articol->GetPret();
    dulap_.AdaugaArticol(std::move(articol));
    return true;
}

void Personaj::AfiseazaEchipamentDeSezon(const std::string &sezon, std::ostream &os) const
{
    os << "Echipament sezon \"" << sezon << "\" al lui " << nume_ << ":\n";
    bool gasit = false;
    for (const auto &a_ptr : dulap_.GetArticole())
    {
        const Imbracaminte *im = dynamic_cast<const Imbracaminte *>(a_ptr.get());
        if (im && im->GetSezon() == sezon)
        {
            gasit = true;
            a_ptr->Afiseaza(os);
            os << "\n";
        }
    }
    if (!gasit)
        os << "  Nu exista articole de sezonul " << sezon << " in dulap.\n";
}
// ... la sfârșitul fișierului ...

std::ostream& operator<<(std::ostream& os, const Personaj& p) {
    p.Afiseaza(os);
    return os;
}