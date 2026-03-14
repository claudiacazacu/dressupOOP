#pragma once
#include "ArticolDerivate.h"

class Rochie : public Imbracaminte
{
    std::string croiala_;
    bool eleganta_;

public:
    Rochie(const std::string &nume,
           const std::string &culoare,
           int pret,
           const std::string &sezon,
           const std::string &croiala,
           bool eleganta);

    void AfiseazaImpl(std::ostream &os) const override;
    std::unique_ptr<Articol> clone() const override;
    std::string Tip() const override { return "Rochie"; }
    bool SePotrivesteLaEveniment(const std::string &eveniment) const override;

    const std::string &GetCroiala() const noexcept { return croiala_; }
    bool EsteEleganta() const noexcept { return eleganta_; }
};