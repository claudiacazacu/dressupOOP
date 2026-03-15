#include "gui/Game.h"

#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "Animal.h"
#include "Articol.h"
#include "ArticolDerivate.h"
#include "Exceptions.h"
#include "GameSession.h"
#include "Haina.h"
#include "Magazin.h"
#include "Observer.h"
#include "Pantalon.h"
#include "Personaj.h"
#include "Quest.h"
#include "Rochie.h"
#include "StrategieRecomandare.h"
#include "TemplateUtils.h"
#include "Tinuta.h"
#include "TinutaBuilder.h"

static int RuleazaDemoConsola()
{
    try
    {
        std::ifstream fin("tastatura.txt");
        if (!fin.is_open())
        {
            throw FileOpenException("tastatura.txt");
        }

        GameSession &session = GameSession::Instance();
        session.SetEvenimentCurent("Gala");
        session.SetSezonPreferat("Vara");

        auto personajObserver = std::make_shared<PersonajObserver>("Claudy");
        auto magazinObserver = std::make_shared<MagazinObserver>("Magazinul Jocului");
        session.Attach(personajObserver);
        session.Attach(magazinObserver);

        Magazin shop("Magazinul Jocului", "magazin.txt");
        Personaj player("Claudy", "Romanian", 1, 350);

        auto strategiePret = std::make_shared<StrategiePretMinimizat>();
        auto strategieEleganta = std::make_shared<StrategieElegantaMaximizata>();
        auto strategieSezon = std::make_shared<StrategieSezonPotrivit>();
        RecomandatorTinute recomandator(strategiePret);

        Tinuta tinutaTest("Tinuta Test");
        TinutaBuilder builder;

        ColectieTematica<std::string> wishlist("Wishlist nume articole");
        wishlist.Adauga("Rochie1_mag");
        wishlist.Adauga("Ceas1_mag");

        ColectieTematica<int> istoricPreturi("Istoric preturi favorite");
        istoricPreturi.Adauga(120);
        istoricPreturi.Adauga(60);
        istoricPreturi.Adauga(25);

        std::string comanda;
        while (fin >> comanda)
        {
            std::cout << "\n>>> Procesare comanda: " << comanda << "\n";

            if (comanda == "AFISEAZA_MAGAZIN")
            {
                std::cout << shop;
            }
            else if (comanda == "AFISEAZA_PLAYER")
            {
                std::cout << player;
            }
            else if (comanda == "SET_EVENIMENT")
            {
                std::string eveniment;
                fin >> eveniment;
                session.SetEvenimentCurent(eveniment);
                std::cout << "Eveniment curent setat la: " << session.GetEvenimentCurent() << "\n";
            }
            else if (comanda == "SET_SEZON")
            {
                std::string sezon;
                fin >> sezon;
                session.SetSezonPreferat(sezon);
                std::cout << "Sezon preferat setat la: " << session.GetSezonPreferat() << "\n";
            }
            else if (comanda == "CUMPARA")
            {
                std::string numeArticol;
                fin >> numeArticol;
                std::cout << "Incerc sa cumpar: " << numeArticol << "\n";

                std::unique_ptr<Articol> articol = shop.ExtrageArticol(numeArticol);
                player.Cumpara(std::move(articol));

                std::cout << "Cumparare efectuata cu succes.\n";
            }
            else if (comanda == "AFISEAZA_SEZON")
            {
                std::string sezon;
                fin >> sezon;
                player.AfiseazaEchipamentDeSezon(sezon, std::cout);
            }
            else if (comanda == "RECOMANDA_PENTRU_EVENT")
            {
                player.AfiseazaTinutePentruEveniment(session.GetEvenimentCurent(), std::cout);
            }
            else if (comanda == "ANALIZA_INVENTAR")
            {
                player.AfiseazaAnalizaInventar(session.GetEvenimentCurent(), std::cout);
            }
            else if (comanda == "AFISEAZA_TEMPLATE")
            {
                wishlist.Afiseaza(std::cout);
                std::cout << "\n";
                istoricPreturi.Afiseaza(std::cout);
                std::cout << "\n";

                size_t numeFavorite = NumarareDupaCriteriu(
                    wishlist.Elemente(),
                    [](const std::string &nume)
                    {
                        return nume.find("mag") != std::string::npos;
                    });

                size_t preturiMari = NumarareDupaCriteriu(
                    istoricPreturi.Elemente(),
                    [](int pret)
                    {
                        return pret >= 60;
                    });

                std::cout << "Elemente wishlist care contin 'mag': " << numeFavorite << "\n";
                std::cout << "Preturi favorite >= 60: " << preturiMari << "\n";
            }
            else if (comanda == "TEST_STRATEGII")
            {
                std::cout << "Testare strategii de recomandare:\n";
                std::cout << "Strategie curenta: " << recomandator.GetNumeStrategie() << "\n";

                recomandator.SetStrategie(strategiePret);
                std::cout << "Schimbat la: " << recomandator.GetNumeStrategie() << "\n";
                auto tinutePret = recomandator.GenereazaRecomandari(player, session.GetEvenimentCurent());
                std::cout << "Recomandari cu strategie pret: " << tinutePret.size() << " tinute\n";

                recomandator.SetStrategie(strategieEleganta);
                std::cout << "Schimbat la: " << recomandator.GetNumeStrategie() << "\n";
                auto tinuteEleganta = recomandator.GenereazaRecomandari(player, session.GetEvenimentCurent());
                std::cout << "Recomandari cu strategie eleganta: " << tinuteEleganta.size() << " tinute\n";

                recomandator.SetStrategie(strategieSezon);
                std::cout << "Schimbat la: " << recomandator.GetNumeStrategie() << "\n";
                auto tinuteSezon = recomandator.GenereazaRecomandari(player, session.GetEvenimentCurent());
                std::cout << "Recomandari cu strategie sezon: " << tinuteSezon.size() << " tinute\n";
            }
            else if (comanda == "TEST_TINUTA")
            {
                std::cout << "Testare functionalitati Tinuta:\n";

                if (!player.GetDulap().GetArticole().empty())
                {
                    auto it = player.GetDulap().GetArticole().begin();
                    tinutaTest.AdaugaArticol(std::shared_ptr<Articol>((*it)->clone().release()));
                    std::cout << "Adaugat articol la tinuta\n";
                }

                std::cout << tinutaTest << "\n";

                if (!tinutaTest.GetArticole().empty())
                {
                    std::string numePrimul = tinutaTest.GetArticole()[0]->GetNume();
                    if (tinutaTest.EliminaArticol(numePrimul))
                    {
                        std::cout << "Eliminat articolul: " << numePrimul << "\n";
                    }
                }

                tinutaTest.Goleste();
                std::cout << "Tinuta golita. Numar articole ramas: " << tinutaTest.GetNumarArticole() << "\n";
            }
            else if (comanda == "TEST_BUILDER")
            {
                std::cout << "Testare TinutaBuilder:\n";

                builder.Reset();
                std::cout << "Builder resetat\n";

                builder.SetNume("Tinuta Custom");
                std::cout << "Setat nume: Tinuta Custom\n";

                if (!player.GetDulap().GetArticole().empty())
                {
                    for (const auto &articol : player.GetDulap().GetArticole())
                    {
                        if (dynamic_cast<const Imbracaminte *>(articol.get()))
                        {
                            builder.AdaugaImbracaminte(std::shared_ptr<Articol>(articol->clone().release()));
                            std::cout << "Adaugat imbracaminte\n";
                            break;
                        }
                    }
                }

                for (const auto &articol : shop.GetArticole())
                {
                    if (dynamic_cast<const Incaltaminte *>(articol.get()))
                    {
                        builder.AdaugaIncaltaminte(std::shared_ptr<Articol>(articol->clone().release()));
                        std::cout << "Adaugat incaltaminte\n";
                        break;
                    }
                }

                for (const auto &articol : shop.GetArticole())
                {
                    if (dynamic_cast<const Accesoriu *>(articol.get()))
                    {
                        builder.AdaugaAccesoriu(std::shared_ptr<Articol>(articol->clone().release()));
                        std::cout << "Adaugat accesoriu\n";
                        break;
                    }
                }

                builder.AfiseazaStare(std::cout);

                if (builder.EsteValida())
                {
                    Tinuta tinutaNoua = builder.Build();
                    std::cout << "Tinuta construita cu succes:\n"
                              << tinutaNoua << "\n";
                }
                else
                {
                    std::cout << "Tinuta nu este valida\n";
                }
            }
            else if (comanda == "TEST_QUESTURI")
            {
                std::cout << "Testare sistem quest-uri:\n";

                player.ActualizeazaQuesturi();
                player.AfiseazaQuesturiActive(std::cout);
                player.AfiseazaQuesturiCompletate(std::cout);

                std::cout << "Marcare quest completat (demonstratie)\n";
            }
            else if (comanda == "TEST_FILTRARE")
            {
                std::cout << "Testare filtrare articole:\n";

                auto articoleRare = player.GetDulap().FiltreazaDupaRaritate("Rar");
                std::cout << "Articole rare: " << articoleRare.size() << "\n";

                auto articoleSortateRating = player.GetDulap().SorteazaDupaRating();
                std::cout << "Articole sortate dupa rating: " << articoleSortateRating.size() << "\n";

                auto articoleSortatePret = player.GetDulap().SorteazaDupaPret();
                std::cout << "Articole sortate dupa pret: " << articoleSortatePret.size() << "\n";

                auto articolePremium = player.GetDulap().RecomandaArticolePremium();
                std::cout << "Articole premium recomandate: " << articolePremium.size() << "\n";
            }
            else if (comanda == "TEST_UNUSED_FUNCTIONS")
            {
                std::cout << "Testare toate functiile nefolosite anterior:\n";

                if (!player.GetDulap().GetArticole().empty())
                {
                    auto it = player.GetDulap().GetArticole().begin();
                    std::shared_ptr<Articol> articolTest = std::shared_ptr<Articol>((*it)->clone().release());

                    articolTest->SetRaritate("Epic");
                    articolTest->SetRating(4.5);
                    articolTest->IncrementeazaPopularitate();

                   /* std::cout << "Articol modificat - Raritate: " << articolTest->GetRaritate()
                              << ", Rating: " << articolTest.GetRating()
                              << ", Popularitate: " << articolTest.GetPopularitate() << "\n"; */
                }

                if (!player.GetSistemQuest().GetQuesturiActive().empty())
                {
                    auto quest = player.GetSistemQuest().GetQuesturiActive()[0];
                    std::cout << "Quest info - Descriere: " << quest->GetDescriere()
                              << ", Tip: " << static_cast<int>(quest->GetTip())
                              << ", Obiectiv: " << quest->GetObiectiv()
                              << ", Progres: " << quest->GetProgres()
                              << ", Recompensa: " << quest->GetRecompensaSold() << "\n";

                    quest->Reseteaza();
                    std::cout << "Quest resetat - Progres: " << quest->GetProgres() << "\n";
                }

                auto questuriCompletate = player.GetSistemQuest().GetQuesturiCompletate();
                std::cout << "Numar questuri completate: " << questuriCompletate.size() << "\n";

                session.Detach(personajObserver);
                std::cout << "Observer detasat\n";

                Tinuta ceaMaiBuna = player.CeaMaiBunaTinuta(session.GetEvenimentCurent(), "eleganta");
                std::cout << "Cea mai buna tinuta dupa eleganta:\n"
                          << ceaMaiBuna << "\n";

                session.Attach(personajObserver);
                std::cout << "Observer reatasat\n";
            }
            else if (comanda == "EXIT")
            {
                break;
            }
            else
            {
                throw InvalidInputException("Comanda necunoscuta: " + comanda);
            }
        }

        std::cout << "\n= statistici finale =\n";
        player.AfiseazaAnalizaInventar(session.GetEvenimentCurent(), std::cout);
        std::cout << "Articole ramase in magazin (static): " << Magazin::TotalArticole() << "\n";
        std::cout << "Personaje create (static): " << Personaj::TotalPersonaje() << "\n";

        const std::list<std::unique_ptr<Articol>> &articole = player.GetDulap().GetArticole();
        std::list<std::unique_ptr<Articol>>::const_iterator it;

        for (it = articole.begin(); it != articole.end(); ++it)
        {
            const Articol *articol = (*it).get();

            std::cout << "Analiza articol: " << articol->GetNume() << "\n";
            std::cout << "  - Tip din ierarhie: " << articol->Tip() << "\n";
            std::cout << "  - Potrivit pentru evenimentul curent? "
                      << (articol->SePotrivesteLaEveniment(session.GetEvenimentCurent()) ? "Da" : "Nu") << "\n";

            const Haina *haina = dynamic_cast<const Haina *>(articol);
            if (haina != nullptr)
            {
                std::cout << "  [Haina] Material: " << haina->GetMaterial()
                          << ", Gluga: " << (haina->AreGluga() ? "Da" : "Nu") << "\n";
            }
            else
            {
                const Pantalon *pantalon = dynamic_cast<const Pantalon *>(articol);
                if (pantalon != nullptr)
                {
                    std::cout << "  [Pantalon] Lungime: " << pantalon->GetLungime() << "\n";
                }
                else
                {
                    const Animal *animal = dynamic_cast<const Animal *>(articol);
                    if (animal != nullptr)
                    {
                        std::cout << "  [Animal] Specie: " << animal->GetSpecie() << "\n";
                    }
                    else
                    {
                        const Incaltaminte *incalt = dynamic_cast<const Incaltaminte *>(articol);
                        if (incalt != nullptr)
                        {
                            std::cout << "  [Incaltaminte] Marime: " << incalt->GetMarime() << "\n";
                        }
                        else
                        {
                            const Accesoriu *acc = dynamic_cast<const Accesoriu *>(articol);
                            if (acc != nullptr)
                            {
                                std::cout << "  [Accesoriu] Categorie: " << acc->GetCategorie() << "\n";
                            }
                            else
                            {
                                const Rochie *rochie = dynamic_cast<const Rochie *>(articol);
                                if (rochie != nullptr)
                                {
                                    std::cout << "  [Rochie] Croiala: " << rochie->GetCroiala()
                                              << ", Eleganta: " << (rochie->EsteEleganta() ? "Da" : "Nu") << "\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Eroare: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

static int RuleazaAplicatiaSFML()
{
    Game game;
    game.run();
    return 0;
}

int main()
{
#ifdef RUN_CONSOLE_DEMO
    return RuleazaDemoConsola();
#else
    return RuleazaAplicatiaSFML();
#endif
}