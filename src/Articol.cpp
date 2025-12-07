#include "Articol.h"
#include <utility>
#include <iostream>

Articol::Articol(std::string nume, std::string culoare, int pret)
    : nume_(std::move(nume)), culoare_(std::move(culoare)), pret_(pret) {}

void Articol::Afiseaza(std::ostream &os) const
{
    AfiseazaImpl(os);
}

std::ostream &operator<<(std::ostream &os, const Articol &a)
{
    a.Afiseaza(os);
    return os;
}