#pragma once
#include <memory>
#include <string>
#include "Articol.h"

class ArticolFactory {

public:

    static std::shared_ptr<Articol> createArticol(
        const std::string& tip,
        int id,
        const std::string& nume,
        int pret
    );

};