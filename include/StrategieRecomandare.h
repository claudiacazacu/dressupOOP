#pragma once
#include <vector>
#include <memory>
#include "Tinuta.h"
#include "Personaj.h"

class StrategieRecomandare
{
public:
    virtual ~StrategieRecomandare() = default;
    virtual std::vector<Tinuta> Recomanda(const Personaj& personaj, const std::string& eveniment) const = 0;
    virtual std::string GetNume() const = 0;
};

class StrategiePretMinimizat : public StrategieRecomandare
{
public:
    std::vector<Tinuta> Recomanda(const Personaj& personaj, const std::string& eveniment) const override;
    std::string GetNume() const override { return "Pret Minimizat"; }
};

class StrategieElegantaMaximizata : public StrategieRecomandare
{
public:
    std::vector<Tinuta> Recomanda(const Personaj& personaj, const std::string& eveniment) const override;
    std::string GetNume() const override { return "Eleganta Maximizata"; }
};

class StrategieSezonPotrivit : public StrategieRecomandare
{
public:
    std::vector<Tinuta> Recomanda(const Personaj& personaj, const std::string& eveniment) const override;
    std::string GetNume() const override { return "Sezon Potrivit"; }
};

class RecomandatorTinute
{
private:
    std::shared_ptr<StrategieRecomandare> strategie_;

public:
    RecomandatorTinute(std::shared_ptr<StrategieRecomandare> strategie = nullptr);

    void SetStrategie(std::shared_ptr<StrategieRecomandare> strategie);
    std::vector<Tinuta> GenereazaRecomandari(const Personaj& personaj, const std::string& eveniment) const;
    std::string GetNumeStrategie() const;
};