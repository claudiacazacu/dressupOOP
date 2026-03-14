#include "Animal.h"
#include <iostream>

Animal::Animal(const std::string& nume)
    : nume(nume) {}

void Animal::afiseaza() const {

    std::cout << "Animal: " << nume << std::endl;

}