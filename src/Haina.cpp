#include "Haina.h"
#include <iostream>

Haina::Haina(int id, std::string nume, int pret, std::string sezon)
    : Articol(id,nume,pret), sezon(sezon) {}

void Haina::afiseaza() const {

    std::cout << "Haina ";
    Articol::afiseaza();

}