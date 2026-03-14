#include "Quest.h"
#include "Personaj.h"
#include <iostream>
#include <algorithm>

Quest::Quest(std::string nume, std::string descriere, TipQuest tip, int obiectiv, int recompensaSold)
    : nume_(std::move(nume)), descriere_(std::move(descriere)), tip_(tip), obiectiv_(obiectiv), recompensaSold_(recompensaSold)
{}

void Quest::ActualizeazaProgres(const Personaj& personaj)
{
    if (complet_) return;

    switch (tip_) {
        case TipQuest::CUMPARA_ARTICOLE:
            progres_ = static_cast<int>(personaj.GetDulap().GetArticole().size());
            break;
        case TipQuest::ATINGE_VALOARE_DULAP:
            progres_ = personaj.GetDulap().CalculeazaValoareTotala();
            break;
        case TipQuest::ARTICOLE_POPULARE: {
            int articolePopulare = 0;
            for (const auto& articol : personaj.GetDulap().GetArticole()) {
                if (articol->GetPopularitate() > 10) { // prag arbitrar
                    articolePopulare++;
                }
            }
            progres_ = articolePopulare;
            break;
        }
        case TipQuest::DETINE_TINUTA_EVENIMENT:
            // Pentru simplitate, verificăm dacă avem suficiente articole pentru eveniment
            progres_ = static_cast<int>(personaj.GetDulap().NumarArticolePentruEveniment("Gala"));
            break;
    }

    if (progres_ >= obiectiv_ && !complet_) {
        MarcheazaComplet();
    }
}

void Quest::MarcheazaComplet()
{
    complet_ = true;
}

void Quest::Reseteaza()
{
    progres_ = 0;
    complet_ = false;
}

void Quest::Afiseaza(std::ostream& os) const
{
    os << "Quest: " << nume_ << "\n";
    os << "Descriere: " << descriere_ << "\n";
    os << "Progres: " << progres_ << "/" << obiectiv_ << "\n";
    os << "Status: " << (complet_ ? "Completat" : "Activ") << "\n";
    if (complet_) {
        os << "Recompensa: " << recompensaSold_ << " lei\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Quest& quest)
{
    quest.Afiseaza(os);
    return os;
}

// Implementare SistemQuest
SistemQuest::SistemQuest()
{
    // Adaugă câteva questuri implicite
    AdaugaQuest(std::make_shared<Quest>(
        "Colectionar Incepator",
        "Cumpara 3 articole",
        Quest::TipQuest::CUMPARA_ARTICOLE,
        3,
        50
    ));

    AdaugaQuest(std::make_shared<Quest>(
        "Tinuta de Gala",
        "Detine articole suficiente pentru o tinuta de gala",
        Quest::TipQuest::DETINE_TINUTA_EVENIMENT,
        5,
        100
    ));

    AdaugaQuest(std::make_shared<Quest>(
        "Colectionar Valoros",
        "Ajunge la valoarea totala de 500 lei in dulap",
        Quest::TipQuest::ATINGE_VALOARE_DULAP,
        500,
        150
    ));
}

void SistemQuest::AdaugaQuest(const std::shared_ptr<Quest>& quest)
{
    if (quest) {
        questuriActive_.push_back(quest);
    }
}

void SistemQuest::ActualizeazaToateQuesturile(const Personaj& personaj)
{
    for (auto it = questuriActive_.begin(); it != questuriActive_.end(); ) {
        (*it)->ActualizeazaProgres(personaj);
        if ((*it)->EsteComplet()) {
            // Mută în completate
            questuriCompletate_.push_back(*it);
            it = questuriActive_.erase(it);
        } else {
            ++it;
        }
    }
}

void SistemQuest::MarcheazaQuestComplet(const std::string& numeQuest)
{
    auto it = std::find_if(questuriActive_.begin(), questuriActive_.end(),
        [&numeQuest](const std::shared_ptr<Quest>& q) {
            return q->GetNume() == numeQuest;
        });

    if (it != questuriActive_.end()) {
        (*it)->MarcheazaComplet();
        questuriCompletate_.push_back(*it);
        questuriActive_.erase(it);
    }
}

void SistemQuest::AfiseazaQuesturiActive(std::ostream& os) const
{
    os << "Questuri active:\n";
    if (questuriActive_.empty()) {
        os << "  Niciun quest activ\n";
        return;
    }

    for (const auto& quest : questuriActive_) {
        os << "  ";
        quest->Afiseaza(os);
        os << "\n";
    }
}

void SistemQuest::AfiseazaQuesturiCompletate(std::ostream& os) const
{
    os << "Questuri completate:\n";
    if (questuriCompletate_.empty()) {
        os << "  Niciun quest completat\n";
        return;
    }

    for (const auto& quest : questuriCompletate_) {
        os << "  ";
        quest->Afiseaza(os);
        os << "\n";
    }
}