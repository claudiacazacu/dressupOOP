#include "ArticolFactory.h"
#include "Animal.h"
#include "Articol.h"
#include "ArticolDerivate.h"
#include "Exceptions.h"
#include "Haina.h"
#include "Pantalon.h"
#include "Rochie.h"

#include <sstream>
#include <string>
#include <vector>

namespace
{
    bool ParseBool(const std::string &valoare)
    {
        if (valoare == "1" || valoare == "true" || valoare == "True" || valoare == "DA")
        {
            return true;
        }

        if (valoare == "0" || valoare == "false" || valoare == "False" || valoare == "NU")
        {
            return false;
        }

        throw InvalidInputException("Valoare booleana invalida: " + valoare);
    }
}

std::unique_ptr<Articol> ArticolFactory::CreeazaDinLinie(const std::string &linie)
{
    std::istringstream iss(linie);
    std::vector<std::string> campuri;
    std::string camp;

    while (iss >> camp)
    {
        campuri.push_back(camp);
    }

    return CreeazaDinCampuri(campuri);
}

std::unique_ptr<Articol> ArticolFactory::CreeazaDinCampuri(const std::vector<std::string> &campuri)
{
    if (campuri.empty())
    {
        throw InvalidInputException("Linie goala in fisierul cu articole");
    }

    const std::string &tip = campuri[0];

    if (tip == "HAINA")
    {
        if (campuri.size() < 7)
        {
            throw InvalidInputException("Format invalid pentru HAINA");
        }

        std::string raritate = campuri.size() > 7 ? campuri[7] : "Comun";
        double rating = campuri.size() > 8 ? std::stod(campuri[8]) : 3.0;
        int popularitate = campuri.size() > 9 ? std::stoi(campuri[9]) : 0;

        return std::make_unique<Haina>(
            campuri[1],
            campuri[2],
            std::stoi(campuri[3]),
            campuri[4],
            campuri[5],
            ParseBool(campuri[6]),
            raritate,
            rating,
            popularitate);
    }

    if (tip == "PANTALON")
    {
        if (campuri.size() < 6)
        {
            throw InvalidInputException("Format invalid pentru PANTALON");
        }

        std::string raritate = campuri.size() > 6 ? campuri[6] : "Comun";
        double rating = campuri.size() > 7 ? std::stod(campuri[7]) : 3.0;
        int popularitate = campuri.size() > 8 ? std::stoi(campuri[8]) : 0;

        return std::make_unique<Pantalon>(
            campuri[1],
            campuri[2],
            std::stoi(campuri[3]),
            campuri[4],
            std::stoi(campuri[5]),
            raritate,
            rating,
            popularitate);
    }

    if (tip == "ANIMAL")
    {
        if (campuri.size() < 5)
        {
            throw InvalidInputException("Format invalid pentru ANIMAL");
        }

        std::string raritate = campuri.size() > 5 ? campuri[5] : "Comun";
        double rating = campuri.size() > 6 ? std::stod(campuri[6]) : 3.0;
        int popularitate = campuri.size() > 7 ? std::stoi(campuri[7]) : 0;

        return std::make_unique<Animal>(
            campuri[1],
            campuri[2],
            std::stoi(campuri[3]),
            campuri[4],
            raritate,
            rating,
            popularitate);
    }

    if (tip == "INCALTAMINTE")
    {
        if (campuri.size() < 5)
        {
            throw InvalidInputException("Format invalid pentru INCALTAMINTE");
        }

        std::string raritate = campuri.size() > 5 ? campuri[5] : "Comun";
        double rating = campuri.size() > 6 ? std::stod(campuri[6]) : 3.0;
        int popularitate = campuri.size() > 7 ? std::stoi(campuri[7]) : 0;

        return std::make_unique<Incaltaminte>(
            campuri[1],
            campuri[2],
            std::stoi(campuri[3]),
            std::stoi(campuri[4]),
            raritate,
            rating,
            popularitate);
    }

    if (tip == "ACCESORIU")
    {
        if (campuri.size() < 5)
        {
            throw InvalidInputException("Format invalid pentru ACCESORIU");
        }

        std::string raritate = campuri.size() > 5 ? campuri[5] : "Comun";
        double rating = campuri.size() > 6 ? std::stod(campuri[6]) : 3.0;
        int popularitate = campuri.size() > 7 ? std::stoi(campuri[7]) : 0;

        return std::make_unique<Accesoriu>(
            campuri[1],
            campuri[2],
            std::stoi(campuri[3]),
            campuri[4],
            raritate,
            rating,
            popularitate);
    }

    if (tip == "ROCHIE")
    {
        if (campuri.size() < 7)
        {
            throw InvalidInputException("Format invalid pentru ROCHIE");
        }

        std::string raritate = campuri.size() > 7 ? campuri[7] : "Comun";
        double rating = campuri.size() > 8 ? std::stod(campuri[8]) : 3.0;
        int popularitate = campuri.size() > 9 ? std::stoi(campuri[9]) : 0;

        return std::make_unique<Rochie>(
            campuri[1],
            campuri[2],
            std::stoi(campuri[3]),
            campuri[4],
            campuri[5],
            ParseBool(campuri[6]),
            raritate,
            rating,
            popularitate);
    }

    throw InvalidInputException("Tip de articol necunoscut: " + tip);
}