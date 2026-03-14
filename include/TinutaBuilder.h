#pragma once
#include "Tinuta.h"
#include <memory>

class TinutaBuilder
{
private:
    std::string nume_;
    std::vector<std::shared_ptr<Articol>> articole_;

public:
    TinutaBuilder& SetNume(const std::string& nume);
    TinutaBuilder& AdaugaArticol(std::shared_ptr<Articol> articol);
    TinutaBuilder& AdaugaImbracaminte(std::shared_ptr<Articol> imbracaminte);
    TinutaBuilder& AdaugaIncaltaminte(std::shared_ptr<Articol> incaltaminte);
    TinutaBuilder& AdaugaAccesoriu(std::shared_ptr<Articol> accesoriu);

    Tinuta Build() const;
    void Reset();

    // Metode helper
    bool EsteValida() const;
    void AfiseazaStare(std::ostream& os) const;
};