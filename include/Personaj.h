#pragma once
#include <string>
#include "Dulap.h"

class Personaj {

    std::string nume;
    int bani;
    Dulap dulap;

    static int totalPersonaje;

public:

    Personaj(std::string nume, int bani);

    void cumparaArticol(std::shared_ptr<Articol> a);

    Dulap& getDulap();

};