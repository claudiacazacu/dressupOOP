#include "Rochie.h"
#include <iostream>

Rochie::Rochie(int id, std::string nume, int pret, std::string tip)
    : Articol(id,nume,pret), tip(tip) {}

void Rochie::afiseaza() const {

    std::cout << "Rochie ";
    Articol::afiseaza();

}