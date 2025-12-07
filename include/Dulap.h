#pragma once
#include <list>
#include <memory>
#include <string>
#include "Articol.h"

class Dulap
{
    std::list<std::unique_ptr<Articol>> articole_;
    int capacitate_ = 0;
    std::string proprietar_;

public:
    friend std::ostream &operator<<(std::ostream &os, const Dulap &d);
    Dulap(int capacitate = 20, const std::string &proprietar = "Anonim");
    Dulap(const Dulap &other);
    Dulap &operator=(Dulap other);
    ~Dulap() = default;

    void swap(Dulap &other) noexcept;

    bool EstePlin() const noexcept;
    bool AdaugaArticol(std::unique_ptr<Articol> articol);

    int CalculeazaValoareTotala() const noexcept;
    void Afiseaza(std::ostream &os) const;

    const std::list<std::unique_ptr<Articol>> &GetArticole() const noexcept { return articole_; }
};
