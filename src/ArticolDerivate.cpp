#include "ArticolDerivate.h"
#include <iostream>

Imbracaminte::Imbracaminte(const std::string &nume, const std::string &culoare, int pret, const std::string &sezon)
    : Articol(nume, culoare, pret), sezon_(sezon) {}

void Imbracaminte::AfiseazaImpl(std::ostream &os) const
{
    os << "[Imbracaminte] " << nume_ << " | Pret: " << pret_
       << " | Culoare: " << culoare_ << " | Sezon: " << sezon_;
}
bool Imbracaminte::SePotrivesteLaEveniment(const std::string &eveniment) const
{
    return true;
}

std::unique_ptr<Articol> Imbracaminte::clone() const
{
    return std::make_unique<Imbracaminte>(*this);
}

std::string Imbracaminte::Tip() const
{
    return sezon_;
}

Incaltaminte::Incaltaminte(const std::string &nume, const std::string &culoare, int pret, int marime)
    : Articol(nume, culoare, pret), marime_(marime) {}

void Incaltaminte::AfiseazaImpl(std::ostream &os) const
{
    os << "[Incaltaminte] " << nume_ << " | Pret: " << pret_
       << " | Culoare: " << culoare_ << " | Marime: " << marime_;
}

std::unique_ptr<Articol> Incaltaminte::clone() const
{
    return std::make_unique<Incaltaminte>(*this);
}

bool Incaltaminte::SePotrivesteLaEveniment(const std::string &eveniment) const
{
    return true;
}

std::string Incaltaminte::Tip() const
{
    return "Incaltaminte";
}

Accesoriu::Accesoriu(const std::string &nume, const std::string &culoare, int pret, const std::string &categorie)
    : Articol(nume, culoare, pret), categorie_(categorie) {}

void Accesoriu::AfiseazaImpl(std::ostream &os) const
{
    os << "[Accesoriu] " << nume_ << " | Pret: " << pret_
       << " | Culoare: " << culoare_ << " | Categorie: " << categorie_;
}

std::unique_ptr<Articol> Accesoriu::clone() const
{
    return std::make_unique<Accesoriu>(*this);
}
bool Accesoriu::SePotrivesteLaEveniment(const std::string &eveniment) const
{
    return true;
}
std::string Accesoriu::Tip() const
{
    return categorie_;
}