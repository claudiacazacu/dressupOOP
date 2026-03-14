#include "ArticolDerivate.h"
#include "Exceptions.h"

Imbracaminte::Imbracaminte(const std::string &nume, const std::string &culoare, int pret, const std::string &sezon)
    : Articol(nume, culoare, pret), sezon_(sezon)
{
    if (sezon_.empty())
    {
        throw InvalidInputException("Imbracamintea trebuie sa aiba un sezon");
    }
}

void Imbracaminte::AfiseazaImpl(std::ostream &os) const
{
    os << "[Imbracaminte] " << nume_ << " | Pret: " << pret_
       << " | Culoare: " << culoare_ << " | Sezon: " << sezon_;
}

std::unique_ptr<Articol> Imbracaminte::clone() const
{
    return std::make_unique<Imbracaminte>(*this);
}

std::string Imbracaminte::Tip() const
{
    return "Imbracaminte";
}

bool Imbracaminte::SePotrivesteLaEveniment(const std::string &eveniment) const
{
    (void)eveniment;
    return true;
}

Incaltaminte::Incaltaminte(const std::string &nume, const std::string &culoare, int pret, int marime)
    : Articol(nume, culoare, pret), marime_(marime)
{
    if (marime_ <= 0)
    {
        throw InvalidInputException("Marimea la incaltaminte trebuie sa fie pozitiva");
    }
}

void Incaltaminte::AfiseazaImpl(std::ostream &os) const
{
    os << "[Incaltaminte] " << nume_ << " | Pret: " << pret_
       << " | Culoare: " << culoare_ << " | Marime: " << marime_;
}

std::unique_ptr<Articol> Incaltaminte::clone() const
{
    return std::make_unique<Incaltaminte>(*this);
}

std::string Incaltaminte::Tip() const
{
    return "Incaltaminte";
}

bool Incaltaminte::SePotrivesteLaEveniment(const std::string &eveniment) const
{
    return eveniment != "Ski" || culoare_ != "Alb";
}

Accesoriu::Accesoriu(const std::string &nume, const std::string &culoare, int pret, const std::string &categorie)
    : Articol(nume, culoare, pret), categorie_(categorie)
{
    if (categorie_.empty())
    {
        throw InvalidInputException("Accesoriul trebuie sa aiba o categorie");
    }
}

void Accesoriu::AfiseazaImpl(std::ostream &os) const
{
    os << "[Accesoriu] " << nume_ << " | Pret: " << pret_
       << " | Culoare: " << culoare_ << " | Categorie: " << categorie_;
}

std::unique_ptr<Articol> Accesoriu::clone() const
{
    return std::make_unique<Accesoriu>(*this);
}

std::string Accesoriu::Tip() const
{
    return "Accesoriu";
}

bool Accesoriu::SePotrivesteLaEveniment(const std::string &eveniment) const
{
    return eveniment != "Ski" || categorie_ != "Elegant";
}