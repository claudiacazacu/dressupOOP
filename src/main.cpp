#include <iostream>
#include <fstream> 
#include <string>
#include "Magazin.h"
#include "Personaj.h"
#include "Exceptions.h"

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
        Personaj player("Claudy", "Romanian", 1, 250); 

        std::string comanda;

        while (fin >> comanda)
        {
            std::cout << "\n>>> Procesare comanda: " << comanda << "\n";

            if (comanda == "AFISEAZA_MAGAZIN")
            {
                shop.Afiseaza(std::cout);
            }
            else if (comanda == "AFISEAZA_PLAYER")
            {
                player.Afiseaza(std::cout);
            }
            else if (comanda == "CUMPARA")
            {
                std::string numeArticol;
                fin >> numeArticol; 

                std::cout << "Incerc sa cumpar: " << numeArticol << "... ";

                auto art = shop.ExtrageArticol(numeArticol);

                if (art)
                {
                    if (player.Cumpara(std::move(art)))
                    {
                        std::cout << "Succes!\n";
                    }
                    else
                    {
                        std::cout << "ESUAT (Fonduri insuficiente sau dulap plin).\n";
                    }
                }
                else
                {
                    std::cout << "Articolul nu exista in magazin.\n";
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
            else
            {
                std::cout << "Comanda necunoscuta: " << comanda << "\n";
            }
        }

        fin.close();
    }
    catch (const AppException &e)
    {
        std::cerr << "\nEroare aplicatie: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nEroare standard: " << e.what() << "\n";
        return 2;
    }

    return 0;
}