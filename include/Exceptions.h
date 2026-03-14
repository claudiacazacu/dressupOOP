#pragma once
#include <stdexcept>
#include <string>

class AppException : public std::runtime_error
{
public:
    explicit AppException(const std::string &msg) : std::runtime_error(msg) {}
};

class FileOpenException : public AppException
{
public:
    explicit FileOpenException(const std::string &file)
        : AppException("Nu s-a putut deschide fisierul: " + file) {}
};

class InventoryException : public AppException
{
public:
    explicit InventoryException(const std::string &msg) : AppException("Eroare inventar: " + msg) {}
};

class InvalidInputException : public AppException
{
public:
    explicit InvalidInputException(const std::string &msg) : AppException("Date invalide: " + msg) {}
};

class BudgetException : public AppException
{
public:
    explicit BudgetException(const std::string &msg) : AppException("Buget insuficient: " + msg) {}
};