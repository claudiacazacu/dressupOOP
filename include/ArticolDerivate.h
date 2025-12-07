#pragma once
#include "Articol.h"
#include <string>
#include <memory>
#include <iostream>

class Imbracaminte : public Articol
{
protected:
    std::string sezon_;

public:
    Imbracaminte(const std::string &nume, const std::string &culoare, int pret, const std::string &sezon);

    bool SePotrivesteLaEveniment(const std::string &eveniment) const override;

    void AfiseazaImpl(std::ostream &os) const override;

    std::unique_ptr<Articol> clone() const override;
    std::string Tip() const override;
    const std::string &GetSezon() const { return sezon_; }
};

class Incaltaminte : public Articol
{
    int marime_;

public:
    Incaltaminte(const std::string &nume, const std::string &culoare, int pret, int marime);
    bool SePotrivesteLaEveniment(const std::string &eveniment) const override;
    void AfiseazaImpl(std::ostream &os) const override;
    std::unique_ptr<Articol> clone() const override;
    std::string Tip() const override;
    int GetMarime() const { return marime_; }
};

class Accesoriu : public Articol
{
    std::string categorie_;

public:
    Accesoriu(const std::string &nume, const std::string &culoare, int pret, const std::string &categorie);
    bool SePotrivesteLaEveniment(const std::string &eveniment) const override;
    void AfiseazaImpl(std::ostream &os) const override;
    std::unique_ptr<Articol> clone() const override;
    std::string Tip() const override;
    const std::string &GetCategorie() const { return categorie_; }
};