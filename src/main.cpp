#include <iostream>
#include "Magazin.h"
#include "Personaj.h"
#include "GameSession.h"

int main() {

    try {

        GameSession& session = GameSession::getInstance();

        Magazin magazin;
        magazin.incarcaDinFisier("data/magazin.txt");

        std::string nume;
        std::cout << "Introdu numele personajului: ";
        std::cin >> nume;

        Personaj p(nume, 200);

        bool running = true;

        while (running) {

            std::cout << "\n1. Vezi magazin\n";
            std::cout << "2. Cumpara articol\n";
            std::cout << "3. Vezi dulap\n";
            std::cout << "4. Iesi\n";

            int opt;
            std::cin >> opt;

            switch (opt) {

                case 1:
                    magazin.afiseaza();
                    break;

                case 2: {

                    int id;
                    std::cout << "ID articol: ";
                    std::cin >> id;

                    auto articol = magazin.getArticol(id);
                    p.cumparaArticol(articol);

                    break;
                }

                case 3:
                    p.getDulap().afiseaza();
                    break;

                case 4:
                    running = false;
                    break;
            }
        }

    } catch (std::exception& e) {

        std::cout << "Eroare: " << e.what() << "\n";

    }

    return 0;
}