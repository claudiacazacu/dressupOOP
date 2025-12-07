cmake_minimum_required(VERSION 3.10)
project(DressUpGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Spunem unde sunt fisierele header (.h)
include_directories(include)

# 2. Definim sursele, cautandu-le in folderul 'src/'
set(SOURCES
    src/main.cpp
    src/Magazin.cpp
    src/Personaj.cpp
    src/Articol.cpp
    src/ArticolDerivate.cpp
    src/Haina.cpp
    src/Pantalon.cpp
    src/Animal.cpp
    src/Dulap.cpp
    src/Exceptions.cpp
)

# 3. Cream executabilul cu numele 'dressup' (ca sa fie consistent cu ce ai tu)
add_executable(dressup ${SOURCES})

# 4. Link catre headere
target_include_directories(dressup PRIVATE include)