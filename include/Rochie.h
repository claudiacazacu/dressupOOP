#pragma once
#include "Articol.h"

class Rochie : public Articol {

    std::string tip;

public:

    Rochie(int id, std::string nume, int pret, std::string tip);

    void afiseaza() const override;

};