#include "Animal.h"
#include "Exceptions.h"

Animal::Animal(const std::string &nume, const std::string &culoare, int pret, std::string specie,
               const std::string &raritate, double rating, int popularitate)
    : Articol(nume, culoare, pret, raritate, rating, popularitate), specie_(std::move(specie))
{
    if (specie_.empty())
    {
        throw InvalidInputException("Animalul trebuie sa aiba o specie");
    }
}

void Animal::AfiseazaImpl(std::ostream &os) const
{
    os << "[Animal] " << nume_ << " | Pret: " << pret_ << " | Specie: " << specie_
       << " | Raritate: " << raritate_ << " | Rating: " << rating_;
}

std::unique_ptr<Articol> Animal::clone() const
{
    return std::make_unique<Animal>(*this);
}

bool Animal::SePotrivesteLaEveniment(const std::string &eveniment) const
{
    return eveniment == "Zoo" || eveniment == "Acasa" || eveniment == "Plimbare";
}

std::string Animal::Tip() const
{
    return "Animal";
}