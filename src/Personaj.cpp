#include "Personaj.h"
#include <iostream>

int Personaj::totalPersonaje = 0;

Personaj::Personaj(std::string nume, int bani)
    : nume(nume), bani(bani) {

    totalPersonaje++;

}

void Personaj::cumparaArticol(std::shared_ptr<Articol> a) {

    if(a->getPret() > bani)
        throw std::runtime_error("Nu ai bani");

    bani -= a->getPret();

    dulap.adauga(a);

}

Dulap& Personaj::getDulap() {

    return dulap;

}