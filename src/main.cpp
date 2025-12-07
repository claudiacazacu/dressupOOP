#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Magazin.h"
#include "Personaj.h"
#include "Exceptions.h"
#include "Haina.h"
#include "Pantalon.h"
#include "Animal.h"
#include "ArticolDerivate.h"

int main()
{
    std::ifstream fin("tastatura.txt");

    try
    {
        if (!fin.is_open())
        {
            throw FileOpenException("tastatura.txt");
        }

        Magazin shop("Magazinul Jocului");
        Personaj player("Claudy", "Romanian", 1, 350);

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
            else if (comanda == "CUMPARA")
            {
                std::string numeArticol;
                fin >> numeArticol;
                std::cout << "Incerc sa cumpar: " << numeArticol << "... ";

                if (shop.CautaArticol(numeArticol))
                {
                    std::cout << "(Gasit in oferta)... ";
                }

                auto art = shop.ExtrageArticol(numeArticol);
                if (art)
                {
                    if (player.Cumpara(std::move(art)))
                    {
                        std::cout << "Succes!\n";
                    }
                    else
                    {
                        std::cout << "ESUAT (Fonduri/Spatiu).\n";
                    }
                }
                else
                {
                    std::cout << "Indisponibil.\n";
                }
            }
            else if (comanda == "AFISEAZA_SEZON")
            {
                std::string sezon;
                fin >> sezon;
                player.AfiseazaEchipamentDeSezon(sezon, std::cout);
            }
            else if (comanda == "EXIT")
            {
                break;
            }
        }

        fin.close();

        std::cout << "\n=statistici\n";

        std::cout << "Sold final jucator: " << player.GetSold() << "\n";
        std::cout << "Valoare totala inventar: " << player.GetDulap().CalculeazaValoareTotala() << "\n";

        std::cout << "Articole ramase in magazin (static): " << Magazin::TotalArticole() << "\n";

        const auto &articole = player.GetDulap().GetArticole();
        for (const auto &articol : articole)
        {
            std::cout << "Analiza articol: " << articol->GetNume() << "\n";

            if (articol->SePotrivesteLaEveniment("Gala"))
            {
                std::cout << "  - Se potriveste la Gala.\n";
            }
            else
            {
                std::cout << "  - NU se potriveste la Gala.\n";
            }

            if (const auto *haina = dynamic_cast<const Haina *>(articol.get()))
            {
                std::cout << "  [Haina] Material: " << haina->GetMaterial()
                          << ", Gluga: " << (haina->AreGluga() ? "Da" : "Nu")
                          << ", Tip: " << haina->Tip() << "\n";
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
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Eroare: " << e.what() << "\n";
        return 1;
    }

    return 0;
}