cmake_minimum_required(VERSION 3.26)

set(MAIN_PROJECT_NAME "dressupOOP")
set(MAIN_EXECUTABLE_NAME "oop")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

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

if(COMMAND set_compiler_flags)
    set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
endif()

target_include_directories(${MAIN_EXECUTABLE_NAME} PRIVATE include)

set_target_properties(${MAIN_EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION bin)

if(APPLE)
    install(FILES launcher.command DESTINATION bin)
endif()

if(COMMAND copy_files)
    copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
else()
    configure_file(tastatura.txt ${CMAKE_BINARY_DIR}/bin/tastatura.txt COPYONLY)
endif()