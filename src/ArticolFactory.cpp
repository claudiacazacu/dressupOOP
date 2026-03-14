#include "ArticolFactory.h"
#include "Haina.h"
#include "Pantalon.h"
#include "Rochie.h"

std::shared_ptr<Articol> ArticolFactory::createArticol(
        const std::string& tip,
        int id,
        const std::string& nume,
        int pret) {

    if(tip == "Haina")
        return std::make_shared<Haina>(id, nume, pret, "iarna");

    if(tip == "Pantalon")
        return std::make_shared<Pantalon>(id, nume, pret, 42);

    if(tip == "Rochie")
        return std::make_shared<Rochie>(id, nume, pret, "eleganta");

    return nullptr;

}