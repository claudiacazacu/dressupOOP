#include "Articol.h"
#include "Exceptions.h"
#include <utility>

Articol::Articol(std::string nume, std::string culoare, int pret)
    : nume_(std::move(nume)), culoare_(std::move(culoare)), pret_(pret)
{
    if (nume_.empty())
    {
        throw InvalidInputException("Articolul trebuie sa aiba un nume");
    }
    if (culoare_.empty())
    {
        throw InvalidInputException("Articolul trebuie sa aiba o culoare");
    }
    if (pret_ < 0)
    {
        throw InvalidInputException("Pretul articolului nu poate fi negativ");
    }
}

void Articol::Afiseaza(std::ostream &os) const
{
    AfiseazaImpl(os);
}

std::ostream &operator<<(std::ostream &os, const Articol &a)
{
    a.Afiseaza(os);
    return os;
}