#include "Haina.h"
#include "Exceptions.h"

Haina::Haina(const std::string &nume, const std::string &culoare, int pret,
             const std::string &sezon, const std::string &material, bool areGluga)
    : Imbracaminte(nume, culoare, pret, sezon), material_(material), areGluga_(areGluga)
{
    if (material_.empty())
    {
        throw InvalidInputException("Haina trebuie sa aiba un material");
    }
}

void Haina::AfiseazaImpl(std::ostream &os) const
{
    os << "[Haina] " << nume_ << " | Pret: " << pret_
       << " | Culoare: " << culoare_ << " | Sezon: " << GetSezon()
       << " | Material: " << material_ << " | " << (areGluga_ ? "Cu gluga" : "Fara gluga");
}

std::unique_ptr<Articol> Haina::clone() const
{
    return std::make_unique<Haina>(*this);
}

bool Haina::SePotrivesteLaEveniment(const std::string &eveniment) const
{
    if (eveniment == "Gala")
    {
        return !areGluga_ && pret_ >= 50;
    }
    if (eveniment == "Ski")
    {
        return material_ == "Fleece" || material_ == "Fas";
    }
    return true;
}