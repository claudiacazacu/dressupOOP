#pragma once
#include <vector>
#include <memory>
#include "Articol.h"

class Magazin {

    std::vector<std::shared_ptr<Articol>> articole;

public:

    void incarcaDinFisier(const std::string& file);

    void afiseaza() const;

    std::shared_ptr<Articol> getArticol(int id);

};