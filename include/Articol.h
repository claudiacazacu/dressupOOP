#pragma once
#include <iostream>
#include <memory>
#include <string>

class Articol
{
protected:
    std::string nume_;
    std::string culoare_;
    int pret_ = 0;
    std::string raritate_; // "Comun", "Rar", "Epic", "Legendary"
    double rating_ = 0.0; // 0.0 - 5.0
    int popularitate_ = 0; // număr de utilizări/achiziții

public:
    friend std::ostream &operator<<(std::ostream &os, const Articol &a);

    Articol(std::string nume, std::string culoare, int pret,
            std::string raritate = "Comun", double rating = 3.0, int popularitate = 0);
    virtual ~Articol() = default;

    void Afiseaza(std::ostream &os) const;

    virtual void AfiseazaImpl(std::ostream &os) const = 0;
    virtual std::unique_ptr<Articol> clone() const = 0;
    virtual std::string Tip() const = 0;
    virtual bool SePotrivesteLaEveniment(const std::string &eveniment) const = 0;

    int GetPret() const noexcept { return pret_; }
    const std::string &GetNume() const noexcept { return nume_; }
    const std::string &GetRaritate() const noexcept { return raritate_; }
    double GetRating() const noexcept { return rating_; }
    int GetPopularitate() const noexcept { return popularitate_; }

    void SetRaritate(const std::string &raritate) { raritate_ = raritate; }
    void SetRating(double rating) { rating_ = std::max(0.0, std::min(5.0, rating)); }
    void IncrementeazaPopularitate() { ++popularitate_; }
};