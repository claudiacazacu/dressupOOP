#pragma once
#include "Articol.h"
#include <string>

class ArticolDerivate : public Articol {

protected:
    std::string material;

public:
    ArticolDerivate(int id, const std::string& nume, int pret, const std::string& material);

    void afiseaza() const override;

    std::string getMaterial() const;
};