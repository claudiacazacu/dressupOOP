#include "StrategieRecomandare.h"
#include <algorithm>

RecomandatorTinute::RecomandatorTinute(std::shared_ptr<StrategieRecomandare> strategie)
    : strategie_(strategie)
{}

void RecomandatorTinute::SetStrategie(std::shared_ptr<StrategieRecomandare> strategie)
{
    strategie_ = strategie;
}

std::vector<Tinuta> RecomandatorTinute::GenereazaRecomandari(const Personaj& personaj, const std::string& eveniment) const
{
    if (strategie_) {
        return strategie_->Recomanda(personaj, eveniment);
    }
    return {};
}

std::string RecomandatorTinute::GetNumeStrategie() const
{
    return strategie_ ? strategie_->GetNume() : "Nicio strategie";
}

// Implementări concrete ale strategiilor

std::vector<Tinuta> StrategiePretMinimizat::Recomanda(const Personaj& personaj, const std::string& eveniment) const
{
    auto tinute = personaj.GenereazaTinutePentruEveniment(eveniment);

    // Sortează după preț crescător
    std::sort(tinute.begin(), tinute.end(),
        [](const Tinuta& a, const Tinuta& b) {
            return a.CalculeazaValoareTotala() < b.CalculeazaValoareTotala();
        });

    // Returnează primele 3 cele mai ieftine
    if (tinute.size() > 3) {
        tinute.resize(3);
    }

    return tinute;
}

std::vector<Tinuta> StrategieElegantaMaximizata::Recomanda(const Personaj& personaj, const std::string& eveniment) const
{
    auto tinute = personaj.GenereazaTinutePentruEveniment(eveniment);

    // Sortează după eleganță descrescătoare
    std::sort(tinute.begin(), tinute.end(),
        [](const Tinuta& a, const Tinuta& b) {
            return a.CalculeazaElegantaMedie() > b.CalculeazaElegantaMedie();
        });

    // Returnează primele 3 cele mai elegante
    if (tinute.size() > 3) {
        tinute.resize(3);
    }

    return tinute;
}

std::vector<Tinuta> StrategieSezonPotrivit::Recomanda(const Personaj& personaj, const std::string& eveniment) const
{
    auto tinute = personaj.GenereazaTinutePentruEveniment(eveniment);

    // Filtrează doar ținutele care se potrivesc sezonului
    std::vector<Tinuta> tinuteSezon;
    for (const auto& tinuta : tinute) {
        if (tinuta.ArticoleleSePotrivescSezon()) {
            tinuteSezon.push_back(tinuta);
        }
    }

    // Sortează după număr de articole descrescător
    std::sort(tinuteSezon.begin(), tinuteSezon.end(),
        [](const Tinuta& a, const Tinuta& b) {
            return a.GetNumarArticole() > b.GetNumarArticole();
        });

    // Returnează primele 3
    if (tinuteSezon.size() > 3) {
        tinuteSezon.resize(3);
    }

    return tinuteSezon;
}