#include "Articol.h"
#include "Exceptions.h"
#include <utility>

Articol::Articol(std::string nume, std::string culoare, int pret,
                 std::string raritate, double rating, int popularitate)
    : nume_(std::move(nume)), culoare_(std::move(culoare)), pret_(pret),
      raritate_(std::move(raritate)), rating_(rating), popularitate_(popularitate)
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
    if (rating_ < 0.0 || rating_ > 5.0)
    {
        throw InvalidInputException("Rating-ul trebuie sa fie intre 0.0 si 5.0");
    }
    if (popularitate_ < 0)
    {
        throw InvalidInputException("Popularitatea nu poate fi negativa");
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