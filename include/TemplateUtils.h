#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class ColectieTematica
{
    std::vector<T> elemente_;
    std::string eticheta_;

public:
    explicit ColectieTematica(std::string eticheta) : eticheta_(std::move(eticheta)) {}

    void Adauga(const T &valoare)
    {
        elemente_.push_back(valoare);
    }

    bool Contine(const T &valoare) const
    {
        return std::find(elemente_.begin(), elemente_.end(), valoare) != elemente_.end();
    }

    const std::vector<T> &Elemente() const noexcept
    {
        return elemente_;
    }

    void Afiseaza(std::ostream &os) const
    {
        os << eticheta_ << ": ";
        if (elemente_.empty())
        {
            os << "(gol)";
            return;
        }

        bool primul = true;
        for (const auto &element : elemente_)
        {
            if (!primul)
            {
                os << ", ";
            }
            os << element;
            primul = false;
        }
    }
};

template <typename Container, typename Predicate>
size_t NumarareDupaCriteriu(const Container &container, Predicate predicat)
{
    return static_cast<size_t>(std::count_if(container.begin(), container.end(), predicat));
}