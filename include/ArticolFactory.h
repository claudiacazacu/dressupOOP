#pragma once
#include <memory>
#include <string>
#include <vector>

class Articol;

class ArticolFactory
{
public:
    static std::unique_ptr<Articol> CreeazaDinLinie(const std::string &linie);
    static std::unique_ptr<Articol> CreeazaDinCampuri(const std::vector<std::string> &campuri);
};