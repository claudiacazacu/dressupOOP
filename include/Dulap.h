#pragma once
#include <vector>
#include <memory>
#include "Articol.h"

class Dulap {

    std::vector<std::shared_ptr<Articol>> articole;

public:

    void adauga(std::shared_ptr<Articol> a);

    void afiseaza() const;

};