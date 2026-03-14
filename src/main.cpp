#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Animal.h"
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
        std::ifstream fin("tastatura.txt");
        if (!fin.is_open())
        {
            throw FileOpenException("tastatura.txt");
        }

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
                auto articol = shop.ExtrageArticol(numeArticol);
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

                const auto numeFavorite = NumarareDupaCriteriu(
                    wishlist.Elemente(), [](const std::string &nume) { return nume.find("mag") != std::string::npos; });
                const auto preturiMari = NumarareDupaCriteriu(
                    istoricPreturi.Elemente(), [](int pret) { return pret >= 60; });

                std::cout << "Elemente wishlist care contin 'mag': " << numeFavorite << "\n";
                std::cout << "Preturi favorite >= 60: " << preturiMari << "\n";
            }
            else if (comanda == "EXIT")
            {
                break;
            }
            else
            {
                throw InvalidInputException("Comanda necunoscuta in tastatura.txt: " + comanda);
            }
        }

        std::cout << "\n= statistici finale =\n";
        player.AfiseazaAnalizaInventar(session.GetEvenimentCurent(), std::cout);
        std::cout << "Articole ramase in magazin (static): " << Magazin::TotalArticole() << "\n";
        std::cout << "Personaje create (static): " << Personaj::TotalPersonaje() << "\n";

        const auto &articole = player.GetDulap().GetArticole();
        for (const auto &articol : articole)
        {
            std::cout << "Analiza articol: " << articol->GetNume() << "\n";
            std::cout << "  - Tip din ierarhie: " << articol->Tip() << "\n";
            std::cout << "  - Potrivit pentru evenimentul curent? "
                      << (articol->SePotrivesteLaEveniment(session.GetEvenimentCurent()) ? "Da" : "Nu") << "\n";

            if (const auto *haina = dynamic_cast<const Haina *>(articol.get()))
            {
                std::cout << "  [Haina] Material: " << haina->GetMaterial()
                          << ", Gluga: " << (haina->AreGluga() ? "Da" : "Nu") << "\n";
            }
            else if (const auto *pantalon = dynamic_cast<const Pantalon *>(articol.get()))
            {
                std::cout << "  [Pantalon] Lungime: " << pantalon->GetLungime() << "\n";
            }
            else if (const auto *animal = dynamic_cast<const Animal *>(articol.get()))
            {
                std::cout << "  [Animal] Specie: " << animal->GetSpecie() << "\n";
            }
            else if (const auto *incalt = dynamic_cast<const Incaltaminte *>(articol.get()))
            {
                std::cout << "  [Incaltaminte] Marime: " << incalt->GetMarime() << "\n";
            }
            else if (const auto *acc = dynamic_cast<const Accesoriu *>(articol.get()))
            {
                std::cout << "  [Accesoriu] Categorie: " << acc->GetCategorie() << "\n";
            }
            else if (const auto *rochie = dynamic_cast<const Rochie *>(articol.get()))
            {
                std::cout << "  [Rochie] Croiala: " << rochie->GetCroiala()
                          << ", Eleganta: " << (rochie->EsteEleganta() ? "Da" : "Nu") << "\n";
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