#include "Personaj.h"
#include "ArticolDerivate.h"
#include "Exceptions.h"
#include <algorithm>
#include <list>
#include <memory>
#include <utility>

int Personaj::totalPersonaje_ = 0;

Personaj::Personaj(const std::string &nume, const std::string &nationalitate, int nivel, int sold)
    : nume_(nume), nationalitate_(nationalitate), nivel_(nivel), dulap_(15, nume), sold_(sold)
{
    if (nume_.empty())
    {
        throw InvalidInputException("Personajul trebuie sa aiba un nume");
    }
    if (nationalitate_.empty())
    {
        throw InvalidInputException("Personajul trebuie sa aiba o nationalitate");
    }
    if (nivel_ <= 0)
    {
        throw InvalidInputException("Nivelul personajului trebuie sa fie pozitiv");
    }
    if (sold_ < 0)
    {
        throw InvalidInputException("Soldul initial nu poate fi negativ");
    }

    ++totalPersonaje_;
}

Personaj::Personaj(const Personaj &other)
    : nume_(other.nume_),
      nationalitate_(other.nationalitate_),
      nivel_(other.nivel_),
      dulap_(other.dulap_),
      sold_(other.sold_)
{
    ++totalPersonaje_;
}

Personaj &Personaj::operator=(Personaj other)
{
    using std::swap;
    swap(nume_, other.nume_);
    swap(nationalitate_, other.nationalitate_);
    swap(nivel_, other.nivel_);
    dulap_.swap(other.dulap_);
    swap(sold_, other.sold_);
    return *this;
}

void Personaj::Afiseaza(std::ostream &os) const
{
    os << "Nume: " << nume_
       << " | Nationalitate: " << nationalitate_
       << " | Nivel: " << nivel_
       << " | Sold: " << sold_ << "\n";

    dulap_.Afiseaza(os);
}

void Personaj::Cumpara(std::unique_ptr<Articol> articol)
{
    if (!articol)
    {
        throw InvalidInputException("Articol invalid pentru cumparare");
    }

    if (sold_ < articol->GetPret())
    {
        throw BudgetException("articolul \"" + articol->GetNume() +
                              "\" costa " + std::to_string(articol->GetPret()) +
                              ", iar soldul disponibil este " + std::to_string(sold_));
    }

    sold_ -= articol->GetPret();
    dulap_.AdaugaArticol(std::move(articol));

    // Actualizează questurile după cumpărare
    ActualizeazaQuesturi();
}

void Personaj::AfiseazaEchipamentDeSezon(const std::string &sezon, std::ostream &os) const
{
    os << "Echipament sezon \"" << sezon << "\" al lui " << nume_ << ":\n";

    bool gasit = false;
    std::list<std::unique_ptr<Articol>>::const_iterator it;

    for (it = dulap_.GetArticole().begin(); it != dulap_.GetArticole().end(); ++it)
    {
        const Imbracaminte *im = dynamic_cast<const Imbracaminte *>((*it).get());
        if (im != nullptr && im->GetSezon() == sezon)
        {
            gasit = true;
            os << "  ";
            (*it)->Afiseaza(os);
            os << "\n";
        }
    }

    if (!gasit)
    {
        os << "  Nu exista articole de sezonul " << sezon << " in dulap.\n";
    }
}

void Personaj::AfiseazaTinutePentruEveniment(const std::string &eveniment, std::ostream &os) const
{
    os << "Recomandari pentru evenimentul \"" << eveniment << "\" pentru " << nume_ << ":\n";
    dulap_.AfiseazaPotrivitePentruEveniment(eveniment, os);
}

void Personaj::AfiseazaAnalizaInventar(const std::string &eveniment, std::ostream &os) const
{
    os << "Analiza inventar pentru " << nume_ << ":\n";
    os << "  Sold curent: " << sold_ << "\n";
    os << "  Valoare dulap: " << dulap_.CalculeazaValoareTotala() << "\n";
    os << "  Articole potrivite pentru \"" << eveniment << "\": "
       << dulap_.NumarArticolePentruEveniment(eveniment) << "\n";
}

const Dulap &Personaj::GetDulap() const noexcept
{
    return dulap_;
}

const SistemQuest &Personaj::GetSistemQuest() const noexcept
{
    return sistemQuest_;
}

int Personaj::TotalPersonaje() noexcept
{
    return totalPersonaje_;
}

// Implementări pentru combinații recomandate
std::vector<Tinuta> Personaj::GenereazaTinutePentruEveniment(const std::string &eveniment) const
{
    std::vector<Tinuta> tinute;
    const auto& articole = dulap_.GetArticole();

    // Colectăm articolele potrivite pentru eveniment
    std::vector<std::shared_ptr<Articol>> articolePotrivite;
    for (const auto& articol : articole) {
        if (articol->SePotrivesteLaEveniment(eveniment)) {
            articolePotrivite.push_back(std::shared_ptr<Articol>(articol->clone().release()));
        }
    }

    if (articolePotrivite.size() < 2) {
        return tinute; // Nu putem forma ținute cu mai puțin de 2 articole
    }

    // Generăm combinații simple (2-4 articole)
    for (size_t i = 0; i < articolePotrivite.size(); ++i) {
        for (size_t j = i + 1; j < articolePotrivite.size(); ++j) {
            Tinuta tinuta("Tinuta " + std::to_string(tinute.size() + 1));
            tinuta.AdaugaArticol(articolePotrivite[i]);
            tinuta.AdaugaArticol(articolePotrivite[j]);

            // Adăugăm un al treilea articol dacă e posibil
            if (j + 1 < articolePotrivite.size()) {
                tinuta.AdaugaArticol(articolePotrivite[j + 1]);
            }

            // Verificăm dacă ținuta respectă regulile
            if (tinuta.ArticoleleSePotrivescSezon() && tinuta.EstePotrivitaPentruEveniment(eveniment)) {
                tinute.push_back(tinuta);
            }

            if (tinute.size() >= 10) break; // Limităm la 10 ținute pentru performanță
        }
        if (tinute.size() >= 10) break;
    }

    return tinute;
}

Tinuta Personaj::CeaMaiBunaTinuta(const std::string &eveniment, const std::string &criteriu) const
{
    auto tinute = GenereazaTinutePentruEveniment(eveniment);
    if (tinute.empty()) {
        return Tinuta("Nicio tinuta disponibila");
    }

    tinute = SorteazaTinute(std::move(tinute), criteriu);
    return tinute.front();
}

std::vector<Tinuta> Personaj::SorteazaTinute(std::vector<Tinuta> tinute, const std::string &criteriu) const
{
    if (criteriu == "pret") {
        std::sort(tinute.begin(), tinute.end(),
            [](const Tinuta& a, const Tinuta& b) {
                return a.CalculeazaValoareTotala() < b.CalculeazaValoareTotala();
            });
    } else if (criteriu == "eleganta") {
        std::sort(tinute.begin(), tinute.end(),
            [](const Tinuta& a, const Tinuta& b) {
                return a.CalculeazaElegantaMedie() > b.CalculeazaElegantaMedie();
            });
    } else if (criteriu == "numar_articole") {
        std::sort(tinute.begin(), tinute.end(),
            [](const Tinuta& a, const Tinuta& b) {
                return a.GetNumarArticole() > b.GetNumarArticole();
            });
    }

    return tinute;
}

std::ostream &operator<<(std::ostream &os, const Personaj &p)
{
    p.Afiseaza(os);
    return os;
}

// Implementări pentru questuri
void Personaj::ActualizeazaQuesturi()
{
    sistemQuest_.ActualizeazaToateQuesturile(*this);
}

void Personaj::AfiseazaQuesturiActive(std::ostream &os) const
{
    sistemQuest_.AfiseazaQuesturiActive(os);
}

void Personaj::AfiseazaQuesturiCompletate(std::ostream &os) const
{
    sistemQuest_.AfiseazaQuesturiCompletate(os);
}

void Personaj::MarcheazaQuestComplet(const std::string &numeQuest)
{
    sistemQuest_.MarcheazaQuestComplet(numeQuest);
}