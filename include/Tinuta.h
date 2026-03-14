#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Articol.h"

class Tinuta
{
private:
    std::string nume_;
    std::vector<std::shared_ptr<Articol>> articole_;

public:
    Tinuta(const std::string& nume = "Tinuta Anonima");
    Tinuta(const Tinuta& other);
    Tinuta& operator=(const Tinuta& other);
    ~Tinuta() = default;

    // Metode principale
    bool AdaugaArticol(std::shared_ptr<Articol> articol);
    bool EliminaArticol(const std::string& numeArticol);
    void Goleste();

    // Calculări
    int CalculeazaValoareTotala() const;
    double CalculeazaElegantaMedie() const; // Dacă adăugăm rating mai târziu

    // Verificări
    bool EstePotrivitaPentruEveniment(const std::string& eveniment) const;
    bool ArticoleleSePotrivescSezon() const;
    bool EsteCompleta() const; // Verifică dacă are toate tipurile necesare

    // Afișare
    void Afiseaza(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Tinuta& tinuta);

    // Getteri
    const std::string& GetNume() const { return nume_; }
    const std::vector<std::shared_ptr<Articol>>& GetArticole() const { return articole_; }
    size_t GetNumarArticole() const { return articole_.size(); }

    // Setteri
    void SetNume(const std::string& nume) { nume_ = nume; }
};