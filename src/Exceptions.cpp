#include "Exceptions.h"

BudgetException::BudgetException(const std::string& mesaj)
    : mesaj(mesaj) {}

const char* BudgetException::what() const noexcept {

    return mesaj.c_str();

}

ArticleNotFoundException::ArticleNotFoundException(const std::string& mesaj)
    : mesaj(mesaj) {}

const char* ArticleNotFoundException::what() const noexcept {

    return mesaj.c_str();

}