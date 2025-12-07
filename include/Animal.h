#pragma once
#include "Articol.h"
#include <string>
#include <iostream>

class Animal : public Articol
{
    std::string specie_;

public:
    Animal(const std::string &nume, const std::string &culoare, int pret, const std::string &specie);
    bool SePotrivesteLaEveniment(const std::string &eveniment) const override;
    void AfiseazaImpl(std::ostream &os) const override;

    std::unique_ptr<Articol> clone() const override;
    std::string Tip() const override;
    const std::string &GetSpecie() const { return specie_; }
};