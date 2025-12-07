#include "Dulap.h"
#include "Exceptions.h"
#include <algorithm>
#include <iostream>

Dulap::Dulap(int capacitate, const std::string& proprietar)
    : capacitate_(capacitate), proprietar_(proprietar) { }

Dulap::Dulap(const Dulap& other)
    : capacitate_(other.capacitate_), proprietar_(other.proprietar_) {
    articole_.clear();
    for (const auto& a : other.articole_) {
        articole_.push_back(a->clone());
    }
}

Dulap& Dulap::operator=(Dulap other) {
    swap(other);
    return *this;
}

void Dulap::swap(Dulap& other) noexcept {
    using std::swap;
    swap(articole_, other.articole_);
    swap(capacitate_, other.capacitate_);
    swap(proprietar_, other.proprietar_);
}

bool Dulap::EstePlin() const noexcept {
    return static_cast<int>(articole_.size()) >= capacitate_;
}

bool Dulap::AdaugaArticol(std::unique_ptr<Articol> articol) {
    if (!articol) return false;
    if (EstePlin()) {
        throw InventoryException("Dulapul este plin");
    }
    articole_.push_back(std::move(articol));
    return true;
}

int Dulap::CalculeazaValoareTotala() const noexcept {
    int s = 0;
    for (const auto& a : articole_) s += a->GetPret();
    return s;
}

void Dulap::Afiseaza(std::ostream& os) const {
    os << "Dulapul lui " << proprietar_ << " (capacitate " << capacitate_ << ")\n";
    if (articole_.empty()) {
        os << "  (gol)\n";
        return;
    }
    for (const auto& a : articole_) {
        os << "  ";
        a->Afiseaza(os);
        os << "\n";
    }
}
    std::ostream& operator<<(std::ostream& os, const Dulap& d) {
    d.Afiseaza(os);
    return os;
}

