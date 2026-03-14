#pragma once
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include "Articol.h"

class Magazin
{
    std::list<std::unique_ptr<Articol>> articole_;
    std::string nume_;
    static size_t totalArticoleMagazin_;

public:
    friend std::ostream &operator<<(std::ostream &os, const Magazin &m);

    explicit Magazin(const std::string &nume, const std::string &fisierArticole = "magazin.txt");

    void IncarcaDinFisier(const std::string &fisierArticole);
    void Afiseaza(std::ostream &os) const;
    const Articol *CautaArticol(const std::string &nume) const;
    std::unique_ptr<Articol> ExtrageArticol(const std::string &nume);
    size_t NumarArticole() const noexcept { return articole_.size(); }

    static size_t TotalArticole() noexcept { return totalArticoleMagazin_; }
};