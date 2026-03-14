#pragma once
#include <vector>

template<typename T>
class ColectieTematica {

private:
    std::vector<T> elemente;

public:

    void adauga(const T& element) {

        elemente.push_back(element);

    }

    int numarElemente() const {

        return elemente.size();

    }

};

template<typename T>
int NumarareDupaCriteriu(const std::vector<T>& v) {

    int count = 0;

    for(const auto& el : v)
        count++;

    return count;

}