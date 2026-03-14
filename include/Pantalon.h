#pragma once
#include "Articol.h"

class Pantalon : public Articol {

    int marime;

public:

    Pantalon(int id, std::string nume, int pret, int marime);

    void afiseaza() const override;

};