#include "Pantalon.h"
#include <iostream>

Pantalon::Pantalon(int id, std::string nume, int pret, int marime)
    : Articol(id,nume,pret), marime(marime) {}

void Pantalon::afiseaza() const {

    std::cout << "Pantalon ";
    Articol::afiseaza();

}