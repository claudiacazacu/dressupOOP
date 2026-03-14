#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void Update(const std::string& evenimentNou) = 0;
    virtual std::string GetNume() const = 0;
};

class Subject
{
private:
    std::vector<std::shared_ptr<Observer>> observers_;

public:
    void Attach(std::shared_ptr<Observer> observer);
    void Detach(std::shared_ptr<Observer> observer);
    void Notify(const std::string& evenimentNou);

protected:
    virtual ~Subject() = default;
};

// Observer concret pentru Personaj
class PersonajObserver : public Observer
{
private:
    std::string numePersonaj_;

public:
    PersonajObserver(const std::string& numePersonaj);

    void Update(const std::string& evenimentNou) override;
    std::string GetNume() const override;
};

// Observer concret pentru Magazin
class MagazinObserver : public Observer
{
private:
    std::string numeMagazin_;

public:
    MagazinObserver(const std::string& numeMagazin);

    void Update(const std::string& evenimentNou) override;
    std::string GetNume() const override;
};