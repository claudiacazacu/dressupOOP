#pragma once
#include <string>
#include "Dulap.h"
#include "Articol.h"

class Personaj
{
    std::string nume_;
    std::string nationalitate_;
    int nivel_ = 1;
    Dulap dulap_;
    int sold_ = 0;

public:
    Personaj(const std::string &nume, const std::string &nationalitate, int nivel = 1, int sold = 100);
    Personaj(const Personaj &other);
    Personaj &operator=(Personaj other);
    ~Personaj() = default;

    void Afiseaza(std::ostream &os) const;
    bool Cumpara(std::unique_ptr<Articol> articol);
    int GetSold() const noexcept { return sold_; }
    void AfiseazaEchipamentDeSezon(const std::string &sezon, std::ostream &os) const;
    const Dulap &GetDulap() const noexcept { return dulap_; }
};
