#pragma once
#include <string>

class Animal {

protected:
    std::string nume;

public:

    Animal(const std::string& nume);

    virtual void afiseaza() const;

};