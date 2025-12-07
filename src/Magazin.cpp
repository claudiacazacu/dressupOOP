#include "Magazin.h"
#include "ArticolDerivate.h"
#include "Haina.h"
#include "Pantalon.h"
#include "Animal.h"
#include <iostream>

size_t Magazin::totalArticoleMagazin = 0;

Magazin::Magazin(const std::string &nume) : nume_(nume)
{
    articole_.push_back(std::make_unique<Haina>("Tricou1_mag", "Negru", 10, "Vara", "Bumbac", false));
    articole_.push_back(std::make_unique<Haina>("Hanorac1_mag", "Negru", 25, "Iarna", "Fleece", true));

    articole_.push_back(std::make_unique<Pantalon>("Pantaloni1_mag", "Gri", 20, "Vara", 100));

    articole_.push_back(std::make_unique<Animal>("Pisica de plus", "Roz", 30, "Plus"));

    totalArticoleMagazin = articole_.size();
}

void Magazin::Afiseaza(std::ostream &os) const
{
    os << "Magazin: " << nume_ << "\n";
    for (const auto &a : articole_)
    {
        a->Afiseaza(os);
        os << "\n";
    }
}

const Articol *Magazin::CautaArticol(const std::string &nume) const
{
    for (const auto &a : articole_)
    {
        if (a->GetNume() == nume)
            return a.get();
    }
    return nullptr;
}

std::unique_ptr<Articol> Magazin::ExtrageArticol(const std::string &nume)
{
    for (auto it = articole_.begin(); it != articole_.end(); ++it)
    {
        if ((*it)->GetNume() == nume)
        {
            std::unique_ptr<Articol> rezultat = std::move(*it);
            articole_.erase(it);
            totalArticoleMagazin = articole_.size();
            return rezultat;
        }
    }
    return nullptr;
}
std::ostream& operator<<(std::ostream& os, const Magazin& m) {
    m.Afiseaza(os); 
    return os;
}