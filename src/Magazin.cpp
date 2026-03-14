#include "Magazin.h"
#include "ArticolFactory.h"
#include "Exceptions.h"
#include <fstream>
#include <string>

size_t Magazin::totalArticoleMagazin_ = 0;

Magazin::Magazin(const std::string &nume, const std::string &fisierArticole) : nume_(nume)
{
    if (nume_.empty())
    {
        throw InvalidInputException("Magazinul trebuie sa aiba un nume");
    }
    IncarcaDinFisier(fisierArticole);
}

void Magazin::IncarcaDinFisier(const std::string &fisierArticole)
{
    std::ifstream fin(fisierArticole);
    if (!fin.is_open())
    {
        throw FileOpenException(fisierArticole);
    }

    articole_.clear();
    std::string linie;
    while (std::getline(fin, linie))
    {
        if (linie.empty())
        {
            continue;
        }
        articole_.push_back(ArticolFactory::CreeazaDinLinie(linie));
    }
    totalArticoleMagazin_ = articole_.size();
}

void Magazin::Afiseaza(std::ostream &os) const
{
    os << "Magazin: " << nume_ << "\n";
    if (articole_.empty())
    {
        os << "  (fara articole)\n";
        return;
    }

    for (const auto &a : articole_)
    {
        os << "  ";
        a->Afiseaza(os);
        os << "\n";
    }
}

std::unique_ptr<Articol> Magazin::ExtrageArticol(const std::string &nume)
{
    for (auto it = articole_.begin(); it != articole_.end(); ++it)
    {
        if ((*it)->GetNume() == nume)
        {
            auto rezultat = std::move(*it);
            articole_.erase(it);
            totalArticoleMagazin_ = articole_.size();
            return rezultat;
        }
    }
    throw InventoryException("Articolul \"" + nume + "\" nu exista in magazin");
}

std::ostream &operator<<(std::ostream &os, const Magazin &m)
{
    m.Afiseaza(os);
    return os;
}