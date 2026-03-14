#include "Rochie.h"
#include "Exceptions.h"

Rochie::Rochie(const std::string &nume,
               const std::string &culoare,
               int pret,
               const std::string &sezon,
               const std::string &croiala,
               bool eleganta)
    : Imbracaminte(nume, culoare, pret, sezon), croiala_(croiala), eleganta_(eleganta)
{
    if (croiala_.empty())
    {
        throw InvalidInputException("Rochia trebuie sa aiba o croiala valida");
    }
}

void Rochie::AfiseazaImpl(std::ostream &os) const
{
    os << "[Rochie] " << nume_
       << " | Pret: " << pret_
       << " | Culoare: " << culoare_
       << " | Sezon: " << GetSezon()
       << " | Croiala: " << croiala_
       << " | " << (eleganta_ ? "Eleganta" : "Casual");
}

std::unique_ptr<Articol> Rochie::clone() const
{
    return std::make_unique<Rochie>(*this);
}

std::string Rochie::Tip() const
{
    return "Rochie";
}

bool Rochie::SePotrivesteLaEveniment(const std::string &eveniment) const
{
    if (eveniment == "Gala")
    {
        return eleganta_;
    }

    if (eveniment == "Plimbare")
    {
        return !eleganta_;
    }

    return true;
}

const std::string &Rochie::GetCroiala() const noexcept
{
    return croiala_;
}

bool Rochie::EsteEleganta() const noexcept
{
    return eleganta_;
}