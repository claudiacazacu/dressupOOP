#pragma once
#include <iostream>
#include <string>
#include "Dulap.h"

class Personaj
{
    std::string nume_;
    std::string nationalitate_;
    int nivel_ = 1;
    Dulap dulap_;
    int sold_ = 0;
    static int totalPersonaje_;

public:
    friend std::ostream &operator<<(std::ostream &os, const Personaj &p);

    Personaj(const std::string &nume, const std::string &nationalitate, int nivel = 1, int sold = 100);
    Personaj(const Personaj &other);
    Personaj &operator=(Personaj other);
    ~Personaj() = default;

    void Afiseaza(std::ostream &os) const;
    void Cumpara(std::unique_ptr<Articol> articol);
    void AfiseazaEchipamentDeSezon(const std::string &sezon, std::ostream &os) const;
    void AfiseazaTinutePentruEveniment(const std::string &eveniment, std::ostream &os) const;
    void AfiseazaAnalizaInventar(const std::string &eveniment, std::ostream &os) const;

    int GetSold() const noexcept { return sold_; }
    const Dulap &GetDulap() const noexcept { return dulap_; }
    static int TotalPersonaje() noexcept { return totalPersonaje_; }
};