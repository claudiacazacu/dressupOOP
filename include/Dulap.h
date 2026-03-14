#pragma once
#include <list>
#include <memory>
#include <string>
#include "Articol.h"

class Dulap
{
    std::list<std::unique_ptr<Articol>> articole_;
    int capacitate_;
    std::string proprietar_;

public:
    explicit Dulap(int capacitate = 20, const std::string &proprietar = "Anonim");
    Dulap(const Dulap &other);
    Dulap &operator=(Dulap other);
    ~Dulap() = default;

    void swap(Dulap &other) noexcept;

    bool EstePlin() const noexcept;
    bool AdaugaArticol(std::unique_ptr<Articol> articol);

    int CalculeazaValoareTotala() const noexcept;
    void Afiseaza(std::ostream &os) const;
    void AfiseazaPotrivitePentruEveniment(const std::string &eveniment, std::ostream &os) const;
    size_t NumarArticolePentruEveniment(const std::string &eveniment) const noexcept;

    // Funcții pentru filtrare și sortare după raritate/rating
    std::vector<std::shared_ptr<Articol>> FiltreazaDupaRaritate(const std::string &raritate) const;
    std::vector<std::shared_ptr<Articol>> SorteazaDupaRating(bool descrescator = true) const;
    std::vector<std::shared_ptr<Articol>> SorteazaDupaPret(bool descrescator = true) const;
    std::vector<std::shared_ptr<Articol>> RecomandaArticolePremium() const;

    const std::list<std::unique_ptr<Articol>> &GetArticole() const noexcept;
};