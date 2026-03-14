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
    void Attach(const std::shared_ptr<Observer>& observer);
    void Detach(const std::shared_ptr<Observer>& observer);
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
    explicit PersonajObserver(std::string numePersonaj);

    void Update(const std::string& evenimentNou) override;
    std::string GetNume() const override;
};

// Observer concret pentru Magazin
class MagazinObserver : public Observer
{
private:
    std::string numeMagazin_;

public:
    explicit MagazinObserver(std::string numeMagazin);

    void Update(const std::string& evenimentNou) override;
    std::string GetNume() const override;
};