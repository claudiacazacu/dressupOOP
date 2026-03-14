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
#include "Pantalon.h"
#include "Personaj.h"
#include "Rochie.h"
#include "TemplateUtils.h"

int main()
{
    try
    {
        // std::ifstream fin("tastatura.txt");
        // if (!fin.is_open())
        // {
        //     throw FileOpenException("tastatura.txt");
        // }

        GameSession &session = GameSession::Instance();
        session.SetEvenimentCurent("Gala");
        session.SetSezonPreferat("Vara");

        Magazin shop("Magazinul Jocului", "magazin.txt");
        Personaj player("Claudy", "Romanian", 1, 350);

        ColectieTematica<std::string> wishlist("Wishlist nume articole");
        wishlist.Adauga("Rochie1_mag");
        wishlist.Adauga("Ceas1_mag");

        ColectieTematica<int> istoricPreturi("Istoric preturi favorite");
        istoricPreturi.Adauga(120);
        istoricPreturi.Adauga(60);
        istoricPreturi.Adauga(25);

        std::string comanda;
        while (std::cin >> comanda)
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
                std::cin >> eveniment;
                session.SetEvenimentCurent(eveniment);
                std::cout << "Eveniment curent setat la: " << session.GetEvenimentCurent() << "\n";
            }
            else if (comanda == "SET_SEZON")
            {
                std::string sezon;
                std::cin >> sezon;
                session.SetSezonPreferat(sezon);
                std::cout << "Sezon preferat setat la: " << session.GetSezonPreferat() << "\n";
            }
            else if (comanda == "CUMPARA")
            {
                std::string numeArticol;
                std::cin >> numeArticol;
                std::cout << "Incerc sa cumpar: " << numeArticol << "\n";

                std::unique_ptr<Articol> articol = shop.ExtrageArticol(numeArticol);
                player.Cumpara(std::move(articol));

                std::cout << "Cumparare efectuata cu succes.\n";
            }
            else if (comanda == "AFISEAZA_SEZON")
            {
                std::string sezon;
                std::cin >> sezon;
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