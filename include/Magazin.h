#pragma once
#include <list>
#include <memory>
#include <string>
#include <iostream>
#include "Articol.h"

class Magazin
{
    std::list<std::unique_ptr<Articol>> articole_;
    std::string nume_;
    static size_t totalArticoleMagazin;

public:
    friend std::ostream &operator<<(std::ostream &os, const Magazin &m);

    explicit Magazin(const std::string &nume);

    void Afiseaza(std::ostream &os) const;

    const Articol *CautaArticol(const std::string &nume) const;

    std::unique_ptr<Articol> ExtrageArticol(const std::string &nume);

    static size_t TotalArticole() noexcept { return totalArticoleMagazin; }
};