cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "dressupOOP")
set(MAIN_EXECUTABLE_NAME "dressup")

project(${MAIN_PROJECT_NAME})

# Setam C++17 pentru compatibilitate maxima cu unique_ptr si GCC-ul de pe checker
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Acestea functioneaza daca ai folderul 'cmake' cu fisierele respective in proiect
# Daca nu le ai, comenteaza liniile, dar pastreaza structura ceruta
include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################

# Aici ar veni dependinte externe (FetchContent), momentan nu ai nevoie.

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
# Lista tuturor fisierelor sursa din proiectul tau
add_executable(${MAIN_EXECUTABLE_NAME}
    src/main.cpp
    src/Animal.cpp
    src/Articol.cpp
    src/ArticolDerivate.cpp
    src/Dulap.cpp
    src/Exceptions.cpp
    src/Haina.cpp
    src/Magazin.cpp
    src/Pantalon.cpp
    src/Personaj.cpp
)

# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
# Aceasta functie este definita in cmake/CompilerFlags.cmake
if(COMMAND set_compiler_flags)
    set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
endif()

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE include)

# Asiguram ca executabilul ajunge in folderul 'bin' pentru ca checker-ul sa il gaseasca
set_target_properties(${MAIN_EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION bin)

# Copiem fisierul de intrare langa executabil
if(COMMAND copy_files)
    copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
else()
    # Fallback in caz ca nu ai copy_files definit
    configure_file(tastatura.txt ${CMAKE_BINARY_DIR}/bin/tastatura.txt COPYONLY)
endif()