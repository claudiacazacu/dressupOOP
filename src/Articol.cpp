#include "Articol.h"
#include <iostream>

Articol::Articol(int id, std::string nume, int pret)
    : id(id), nume(nume), pret(pret) {}

void Articol::afiseaza() const {

    std::cout << id << " " << nume << " " << pret << "\n";

}

int Articol::getPret() const {

    return pret;

}

int Articol::getId() const {

    return id;

}