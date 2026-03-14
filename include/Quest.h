#pragma once
#include <string>
#include <vector>
#include <memory>

class Personaj;

class Quest
{
public:
    enum class TipQuest {
        CUMPARA_ARTICOLE,
        DETINE_TINUTA_EVENIMENT,
        ATINGE_VALOARE_DULAP,
        ARTICOLE_POPULARE
    };

private:
    std::string nume_;
    std::string descriere_;
    TipQuest tip_;
    int obiectiv_; // numărul țintă sau valoarea țintă
    int progres_ = 0;
    bool complet_ = false;
    int recompensaSold_ = 0;

public:
    Quest(const std::string& nume, const std::string& descriere, TipQuest tip, int obiectiv, int recompensaSold);

    // Getteri
    const std::string& GetNume() const { return nume_; }
    const std::string& GetDescriere() const { return descriere_; }
    TipQuest GetTip() const { return tip_; }
    int GetObiectiv() const { return obiectiv_; }
    int GetProgres() const { return progres_; }
    bool EsteComplet() const { return complet_; }
    int GetRecompensaSold() const { return recompensaSold_; }

    // Metode
    void ActualizeazaProgres(const Personaj& personaj);
    void MarcheazaComplet();
    void Reseteaza();

    // Afișare
    void Afiseaza(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Quest& quest);
};

class SistemQuest
{
private:
    std::vector<std::shared_ptr<Quest>> questuriActive_;
    std::vector<std::shared_ptr<Quest>> questuriCompletate_;

public:
    SistemQuest();

    // Gestionare questuri
    void AdaugaQuest(std::shared_ptr<Quest> quest);
    void ActualizeazaToateQuesturile(const Personaj& personaj);
    void MarcheazaQuestComplet(const std::string& numeQuest);

    // Getteri
    const std::vector<std::shared_ptr<Quest>>& GetQuesturiActive() const { return questuriActive_; }
    const std::vector<std::shared_ptr<Quest>>& GetQuesturiCompletate() const { return questuriCompletate_; }

    // Afișare
    void AfiseazaQuesturiActive(std::ostream& os) const;
    void AfiseazaQuesturiCompletate(std::ostream& os) const;
};