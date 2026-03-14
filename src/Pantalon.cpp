#include "Pantalon.h"
#include "Exceptions.h"

Pantalon::Pantalon(const std::string &nume,
                   const std::string &culoare,
                   int pret,
                   const std::string &sezon,
                   int lungime)
    : Imbracaminte(nume, culoare, pret, sezon), lungime_(lungime)
{
    if (lungime_ <= 0)
    {
        throw InvalidInputException("Pantalonul trebuie sa aiba lungime pozitiva");
    }
}

void Pantalon::AfiseazaImpl(std::ostream &os) const
{
    os << "[Pantalon] " << nume_ << " | Pret: " << pret_
       << " | Culoare: " << culoare_ << " | Sezon: " << GetSezon()
       << " | Lungime: " << lungime_;
}

std::unique_ptr<Articol> Pantalon::clone() const
{
    return std::make_unique<Pantalon>(*this);
}

bool Pantalon::SePotrivesteLaEveniment(const std::string &eveniment) const
{
    if (eveniment == "Birou")
    {
        return lungime_ >= 90;
    }
    return true;
}