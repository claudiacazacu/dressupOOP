#pragma once
#include <string>
#include <memory>
#include <iostream>

class Articol
{
protected:
    std::string nume_;
    std::string culoare_;
    int pret_ = 0;

public:
    friend std::ostream &operator<<(std::ostream &os, const Articol &a);

    Articol(std::string nume, std::string culoare, int pret);
    virtual ~Articol() = default;

    void Afiseaza(std::ostream &os) const;

    virtual void AfiseazaImpl(std::ostream &os) const = 0;

    virtual std::unique_ptr<Articol> clone() const = 0;
    virtual std::string Tip() const = 0;
    virtual bool SePotrivesteLaEveniment(const std::string &eveniment) const = 0;

    int GetPret() const noexcept { return pret_; }
    const std::string &GetNume() const noexcept { return nume_; }
};