cmake_minimum_required(VERSION 3.24)

set(MAIN_PROJECT_NAME "dressupOOP")
set(MAIN_EXECUTABLE_NAME "oop")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option(BUILD_SHARED_LIBS "Build SFML as shared libraries" FALSE)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "install_dir" CACHE PATH "Install path" FORCE)
endif()

include(FetchContent)

# Build only the SFML modules actually needed by this project
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SFML)

add_executable(${MAIN_EXECUTABLE_NAME}
    src/main.cpp
    src/gui/Game.cpp
    src/Animal.cpp
    src/Articol.cpp
    src/ArticolDerivate.cpp
    src/ArticolFactory.cpp
    src/Dulap.cpp
    src/Exceptions.cpp
    src/GameSessions.cpp
    src/Haina.cpp
    src/Magazin.cpp
    src/Pantalon.cpp
    src/Personaj.cpp
    src/Rochie.cpp
    src/Tinuta.cpp
    src/Quest.cpp
    src/StrategieRecomandare.cpp
    src/Observer.cpp
    src/TinutaBuilder.cpp
)

target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE include)

target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

if(WARNINGS_AS_ERRORS)
    set_property(TARGET ${MAIN_EXECUTABLE_NAME} PROPERTY COMPILE_WARNING_AS_ERROR ON)
endif()

if(MSVC)
    target_compile_options(${MAIN_EXECUTABLE_NAME} PRIVATE /W4)
else()
    target_compile_options(${MAIN_EXECUTABLE_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

set_target_properties(${MAIN_EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION bin)
install(FILES tastatura.txt magazin.txt DESTINATION bin)

if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
    install(DIRECTORY assets DESTINATION bin)
endif()

if(APPLE)
    install(FILES launcher.command DESTINATION bin)
    configure_file(launcher.command ${CMAKE_BINARY_DIR}/bin/launcher.command COPYONLY)
endif()