#pragma once
#include "Articol.h"
#include <iostream>
#include <memory>
#include <string>

class Imbracaminte : public Articol
{
protected:
    std::string sezon_;

public:
    Imbracaminte(const std::string &nume, const std::string &culoare, int pret, const std::string &sezon,
                 const std::string &raritate = "Comun", double rating = 3.0, int popularitate = 0);

    void AfiseazaImpl(std::ostream &os) const override;
    std::unique_ptr<Articol> clone() const override;
    std::string Tip() const override;
    const std::string &GetSezon() const noexcept { return sezon_; }
    bool SePotrivesteLaEveniment(const std::string &eveniment) const override;
};

class Incaltaminte : public Articol
{
    int marime_;

public:
    Incaltaminte(const std::string &nume, const std::string &culoare, int pret, int marime,
                 const std::string &raritate = "Comun", double rating = 3.0, int popularitate = 0);
    void AfiseazaImpl(std::ostream &os) const override;
    std::unique_ptr<Articol> clone() const override;
    std::string Tip() const override;
    int GetMarime() const noexcept { return marime_; }
    bool SePotrivesteLaEveniment(const std::string &eveniment) const override;
};

class Accesoriu : public Articol
{
    std::string categorie_;

public:
    Accesoriu(const std::string &nume, const std::string &culoare, int pret, const std::string &categorie,
              const std::string &raritate = "Comun", double rating = 3.0, int popularitate = 0);
    void AfiseazaImpl(std::ostream &os) const override;
    std::unique_ptr<Articol> clone() const override;
    std::string Tip() const override;
    const std::string &GetCategorie() const noexcept { return categorie_; }
    bool SePotrivesteLaEveniment(const std::string &eveniment) const override;
};