#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Dulap.h"
#include "Articol.h"
#include "Tinuta.h"
#include "Quest.h"

class Personaj
{
    std::string nume_;
    std::string nationalitate_;
    int nivel_;
    Dulap dulap_;
    int sold_;
    static int totalPersonaje_;
    SistemQuest sistemQuest_;

public:
    friend std::ostream &operator<<(std::ostream &os, const Personaj &p);

    Personaj(std::string nume, std::string nationalitate, int nivel = 1, int sold = 100);
    Personaj(const Personaj &other);
    Personaj &operator=(Personaj other);
    ~Personaj() = default;

    void Afiseaza(std::ostream &os) const;
    void Cumpara(std::unique_ptr<Articol> articol);
    void AfiseazaEchipamentDeSezon(const std::string &sezon, std::ostream &os) const;
    void AfiseazaTinutePentruEveniment(const std::string &eveniment, std::ostream &os) const;
    void AfiseazaAnalizaInventar(const std::string &eveniment, std::ostream &os) const;

    // Noi funcții pentru combinații recomandate
    std::vector<Tinuta> GenereazaTinutePentruEveniment(const std::string &eveniment) const;
    Tinuta CeaMaiBunaTinuta(const std::string &eveniment, const std::string &criteriu = "pret") const;
    std::vector<Tinuta> SorteazaTinute(std::vector<Tinuta> tinute, const std::string &criteriu) const;

    // Funcții pentru questuri
    void ActualizeazaQuesturi();
    void AfiseazaQuesturiActive(std::ostream &os) const;
    void AfiseazaQuesturiCompletate(std::ostream &os) const;
    void MarcheazaQuestComplet(const std::string &numeQuest);

    const Dulap &GetDulap() const noexcept;
    const SistemQuest &GetSistemQuest() const noexcept;
    static int TotalPersonaje() noexcept;
};