#pragma once
#include <string>

class Articol {

protected:

    int id;
    std::string nume;
    int pret;

public:

    Articol(int id, std::string nume, int pret);
    virtual ~Articol() = default;

    virtual void afiseaza() const;

    int getPret() const;
    int getId() const;

};