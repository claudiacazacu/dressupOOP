#pragma once
#include <exception>
#include <string>

class BudgetException : public std::exception {

    std::string mesaj;

public:

    BudgetException(const std::string& mesaj);

    const char* what() const noexcept override;

};

class ArticleNotFoundException : public std::exception {

    std::string mesaj;

public:

    ArticleNotFoundException(const std::string& mesaj);

    const char* what() const noexcept override;

};