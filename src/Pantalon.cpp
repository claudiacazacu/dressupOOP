#include "Pantalon.h"
#include <iostream>

Pantalon::Pantalon(const std::string &nume, const std::string &culoare, int pret, const std::string &sezon, int lungime)
    : Imbracaminte(nume, culoare, pret, sezon), lungime_(lungime) {}

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
        return lungime_ > 80;
    }
    return true;
}