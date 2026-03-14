#include "Dulap.h"
#include <iostream>

void Dulap::adauga(std::shared_ptr<Articol> a) {

    articole.push_back(a);

}

void Dulap::afiseaza() const {

    for(auto& a : articole)
        a->afiseaza();

}