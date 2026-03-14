#include "Magazin.h"
#include "Haina.h"
#include "Pantalon.h"
#include "Rochie.h"
#include <fstream>
#include <iostream>

void Magazin::incarcaDinFisier(const std::string& file) {

    std::ifstream f(file);

    std::string tip;

    while(f >> tip) {

        int id, pret;
        std::string nume;

        f >> id >> nume >> pret;

        if(tip == "Haina") {

            articole.push_back(
                std::make_shared<Haina>(id,nume,pret,"iarna")
            );

        }

        if(tip == "Pantalon") {

            articole.push_back(
                std::make_shared<Pantalon>(id,nume,pret,42)
            );

        }

        if(tip == "Rochie") {

            articole.push_back(
                std::make_shared<Rochie>(id,nume,pret,"seara")
            );

        }

    }

}

void Magazin::afiseaza() const {

    for(auto& a : articole)
        a->afiseaza();

}

std::shared_ptr<Articol> Magazin::getArticol(int id) {

    for(auto& a : articole)
        if(a->getId() == id)
            return a;

    throw std::runtime_error("Articol inexistent");

}