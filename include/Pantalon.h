#pragma once
#include "ArticolDerivate.h"

class Pantalon : public Imbracaminte
{
    int lungime_;

public:
    Pantalon(const std::string &nume,
             const std::string &culoare,
             int pret,
             const std::string &sezon,
             int lungime);

    void AfiseazaImpl(std::ostream &os) const override;
    std::unique_ptr<Articol> clone() const override;
    std::string Tip() const override { return "Pantalon"; }
    bool SePotrivesteLaEveniment(const std::string &eveniment) const override;

    int GetLungime() const { return lungime_; }
};