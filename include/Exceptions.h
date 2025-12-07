#pragma once
#include <exception>
#include <string>
#include <stdexcept>

class AppException : public std::runtime_error
{
public:
    explicit AppException(const std::string &msg) : std::runtime_error(msg) {}
};

class FileOpenException : public AppException
{
public:
    explicit FileOpenException(const std::string &file)
        : AppException("Unable to open file: " + file) {}
};

class InventoryException : public AppException
{
public:
    explicit InventoryException(const std::string &msg) : AppException("Inventory error: " + msg) {}
};

class InvalidInputException : public AppException
{
public:
    explicit InvalidInputException(const std::string &msg) : AppException("Invalid input: " + msg) {}
};
