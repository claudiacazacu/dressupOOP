#include "Observer.h"

void Subject::Attach(std::shared_ptr<Observer> observer)
{
    observers_.push_back(observer);
}

void Subject::Detach(std::shared_ptr<Observer> observer)
{
    auto it = std::find(observers_.begin(), observers_.end(), observer);
    if (it != observers_.end()) {
        observers_.erase(it);
    }
}

void Subject::Notify(const std::string& evenimentNou)
{
    for (const auto& observer : observers_) {
        observer->Update(evenimentNou);
    }
}

// Implementare PersonajObserver
PersonajObserver::PersonajObserver(const std::string& numePersonaj)
    : numePersonaj_(numePersonaj)
{}

void PersonajObserver::Update(const std::string& evenimentNou)
{
    std::cout << "[Observer] Personajul " << numePersonaj_
              << " a fost notificat: Evenimentul s-a schimbat la \"" << evenimentNou << "\"\n";
    std::cout << "[Observer] " << numePersonaj_
              << " își va actualiza recomandările de ținute pentru evenimentul nou.\n";
}

std::string PersonajObserver::GetNume() const
{
    return "PersonajObserver: " + numePersonaj_;
}

// Implementare MagazinObserver
MagazinObserver::MagazinObserver(const std::string& numeMagazin)
    : numeMagazin_(numeMagazin)
{}

void MagazinObserver::Update(const std::string& evenimentNou)
{
    std::cout << "[Observer] Magazinul " << numeMagazin_
              << " a fost notificat: Evenimentul s-a schimbat la \"" << evenimentNou << "\"\n";
    std::cout << "[Observer] " << numeMagazin_
              << " își va actualiza promoțiile pentru evenimentul nou.\n";
}

std::string MagazinObserver::GetNume() const
{
    return "MagazinObserver: " + numeMagazin_;
}