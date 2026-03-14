#pragma once
#include "Articol.h"

class Haina : public Articol {

    std::string sezon;

public:

    Haina(int id, std::string nume, int pret, std::string sezon);

    void afiseaza() const override;

};