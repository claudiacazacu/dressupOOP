cmake_minimum_required(VERSION 3.26)

set(MAIN_PROJECT_NAME "dressupOOP")
set(MAIN_EXECUTABLE_NAME "oop")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# SFML: găsește o instalare locală sau descarcă-o automat (folosită în CI)
find_package(SFML 2.6 COMPONENTS graphics window system QUIET)

if(NOT SFML_FOUND)
    include(FetchContent)
    set(FETCHCONTENT_QUIET OFF)
    set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.2
        GIT_SHALLOW    1
    )

    FetchContent_MakeAvailable(SFML)

    # FetchContent doesn't install SFMLConfig.cmake, but it provides SFML targets.
    set(SFML_FOUND TRUE)
endif()

if(NOT TARGET sfml-graphics)
    message(FATAL_ERROR "SFML targets not found; ensure SFML is installed or FetchContent succeeded.")
endif()

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

add_executable(${MAIN_EXECUTABLE_NAME}
    src/main.cpp
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

if(COMMAND set_compiler_flags)
    set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
endif()

target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE include)

target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

set_target_properties(${MAIN_EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION bin)

install(FILES
    tastatura.txt
    magazin.txt
    DESTINATION bin
)

if(APPLE)
    install(FILES launcher.command DESTINATION bin)
endif()

if(COMMAND copy_files)
    copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
    copy_files(FILES magazin.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
else()
    configure_file(tastatura.txt ${CMAKE_BINARY_DIR}/bin/tastatura.txt COPYONLY)
    configure_file(magazin.txt ${CMAKE_BINARY_DIR}/bin/magazin.txt COPYONLY)
endif()