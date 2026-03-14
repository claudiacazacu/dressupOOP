#include "ArticolDerivate.h"
#include <iostream>

ArticolDerivate::ArticolDerivate(int id, const std::string& nume, int pret, const std::string& material)
    : Articol(id, nume, pret), material(material) {}

void ArticolDerivate::afiseaza() const {

    Articol::afiseaza();
    std::cout << "Material: " << material << std::endl;

}

std::string ArticolDerivate::getMaterial() const {

    return material;

}