#include "TinutaBuilder.h"
#include "ArticolDerivate.h"
#include <iostream>

TinutaBuilder& TinutaBuilder::SetNume(const std::string& nume)
{
    nume_ = nume;
    return *this;
}

TinutaBuilder& TinutaBuilder::AdaugaArticol(const std::shared_ptr<Articol>& articol)
{
    if (articol) {
        articole_.push_back(articol);
    }
    return *this;
}

TinutaBuilder& TinutaBuilder::AdaugaImbracaminte(const std::shared_ptr<Articol>& imbracaminte)
{
    if (imbracaminte && dynamic_cast<Imbracaminte*>(imbracaminte.get())) {
        return AdaugaArticol(imbracaminte);
    }
    return *this;
}

TinutaBuilder& TinutaBuilder::AdaugaIncaltaminte(const std::shared_ptr<Articol>& incaltaminte)
{
    if (incaltaminte && dynamic_cast<Incaltaminte*>(incaltaminte.get())) {
        return AdaugaArticol(incaltaminte);
    }
    return *this;
}

TinutaBuilder& TinutaBuilder::AdaugaAccesoriu(const std::shared_ptr<Articol>& accesoriu)
{
    if (accesoriu && dynamic_cast<Accesoriu*>(accesoriu.get())) {
        return AdaugaArticol(accesoriu);
    }
    return *this;
}

Tinuta TinutaBuilder::Build() const
{
    Tinuta tinuta(nume_.empty() ? "Tinuta Custom" : nume_);

    for (const auto& articol : articole_) {
        tinuta.AdaugaArticol(articol);
    }

    return tinuta;
}

void TinutaBuilder::Reset()
{
    nume_.clear();
    articole_.clear();
}

bool TinutaBuilder::EsteValida() const
{
    if (articole_.empty()) return false;

    bool areImbracaminte = false;
    bool areIncaltaminte = false;

    for (const auto& articol : articole_) {
        if (dynamic_cast<const Imbracaminte*>(articol.get())) {
            areImbracaminte = true;
        } else if (dynamic_cast<const Incaltaminte*>(articol.get())) {
            areIncaltaminte = true;
        }
    }

    return areImbracaminte && areIncaltaminte;
}

void TinutaBuilder::AfiseazaStare(std::ostream& os) const
{
    os << "TinutaBuilder - Stare curenta:\n";
    os << "  Nume: " << (nume_.empty() ? "(nesetat)" : nume_) << "\n";
    os << "  Numar articole: " << articole_.size() << "\n";
    os << "  Valida: " << (EsteValida() ? "Da" : "Nu") << "\n";

    if (!articole_.empty()) {
        os << "  Articole:\n";
        for (const auto& articol : articole_) {
            os << "    - " << articol->GetNume() << " (" << articol->Tip() << ")\n";
        }
    }
}