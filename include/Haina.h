#pragma once
#include "ArticolDerivate.h"

class Haina : public Imbracaminte
{
    std::string material_;
    bool areGluga_;

public:
    Haina(const std::string &nume,
          const std::string &culoare,
          int pret,
          const std::string &sezon,
          const std::string &material,
          bool areGluga);

    void AfiseazaImpl(std::ostream &os) const override;
    std::unique_ptr<Articol> clone() const override;
    std::string Tip() const override { return "Haina"; }
    bool SePotrivesteLaEveniment(const std::string &eveniment) const override;

    const std::string &GetMaterial() const { return material_; }
    bool AreGluga() const { return areGluga_; }
};