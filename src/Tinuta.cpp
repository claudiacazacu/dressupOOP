#include "Tinuta.h"
#include "ArticolDerivate.h"
#include <algorithm>
#include <iostream>

Tinuta::Tinuta(std::string nume) : nume_(std::move(nume)) {}

Tinuta::Tinuta(const Tinuta& other) : nume_(other.nume_), articole_(other.articole_) {}

Tinuta& Tinuta::operator=(const Tinuta& other) {
    if (this != &other) {
        nume_ = other.nume_;
        articole_ = other.articole_;
    }
    return *this;
}

bool Tinuta::AdaugaArticol(std::shared_ptr<Articol> articol) {
    if (!articol) return false;

    // Verificăm dacă articolul nu este deja în ținută
    auto it = std::find_if(articole_.begin(), articole_.end(),
        [&articol](const std::shared_ptr<Articol>& a) {
            return a->GetNume() == articol->GetNume();
        });

    if (it == articole_.end()) {
        articole_.push_back(articol);
        return true;
    }
    return false;
}

bool Tinuta::EliminaArticol(const std::string& numeArticol) {
    auto it = std::find_if(articole_.begin(), articole_.end(),
        [&numeArticol](const std::shared_ptr<Articol>& a) {
            return a->GetNume() == numeArticol;
        });

    if (it != articole_.end()) {
        articole_.erase(it);
        return true;
    }
    return false;
}

void Tinuta::Goleste() {
    articole_.clear();
}

int Tinuta::CalculeazaValoareTotala() const {
    int total = 0;
    for (const auto& articol : articole_) {
        total += articol->GetPret();
    }
    return total;
}

double Tinuta::CalculeazaElegantaMedie() const {
    if (articole_.empty()) return 0.0;

    double total = 0.0;
    int count = 0;

    for (const auto& articol : articole_) {
        // Pentru moment, folosim prețul ca indicator de eleganță
        // Mai târziu putem adăuga un sistem de rating
        total += articol->GetPret();
        count++;
    }

    return count > 0 ? total / count : 0.0;
}

bool Tinuta::EstePotrivitaPentruEveniment(const std::string& eveniment) const {
    if (articole_.empty()) return false;

    // Toate articolele trebuie să se potrivească pentru eveniment
    return std::all_of(articole_.begin(), articole_.end(),
        [&eveniment](const std::shared_ptr<Articol>& articol) {
            return articol->SePotrivesteLaEveniment(eveniment);
        });
}

bool Tinuta::ArticoleleSePotrivescSezon() const {
    if (articole_.empty()) return true;

    // Găsim primul articol de îmbrăcăminte pentru a determina sezonul de referință
    std::string sezonReferinta;
    for (const auto& articol : articole_) {
        const Imbracaminte* imbracaminte = dynamic_cast<const Imbracaminte*>(articol.get());
        if (imbracaminte) {
            sezonReferinta = imbracaminte->GetSezon();
            break;
        }
    }

    if (sezonReferinta.empty()) return true; // Dacă nu avem îmbrăcăminte, e ok

    // Verificăm că toate articolele de îmbrăcăminte au același sezon
    for (const auto& articol : articole_) {
        const Imbracaminte* imbracaminte = dynamic_cast<const Imbracaminte*>(articol.get());
        if (imbracaminte && imbracaminte->GetSezon() != sezonReferinta) {
            return false;
        }
    }

    return true;
}

bool Tinuta::EsteCompleta() const {
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

    // O ținută completă ar trebui să aibă cel puțin îmbrăcăminte și încălțăminte
    return areImbracaminte && areIncaltaminte;
}

void Tinuta::Afiseaza(std::ostream& os) const {
    os << "Tinuta: " << nume_ << "\n";
    os << "Numar articole: " << articole_.size() << "\n";
    os << "Valoare totala: " << CalculeazaValoareTotala() << " lei\n";
    os << "Potrivita pentru eveniment: " << (EstePotrivitaPentruEveniment("Gala") ? "Da" : "Nu") << "\n";
    os << "Articole se potrivesc sezon: " << (ArticoleleSePotrivescSezon() ? "Da" : "Nu") << "\n";
    os << "Completa: " << (EsteCompleta() ? "Da" : "Nu") << "\n";

    if (!articole_.empty()) {
        os << "Articole:\n";
        for (const auto& articol : articole_) {
            os << "  - " << articol->GetNume() << " (" << articol->Tip() << ", " << articol->GetPret() << " lei)\n";
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Tinuta& tinuta) {
    tinuta.Afiseaza(os);
    return os;
}