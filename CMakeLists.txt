cmake_minimum_required(VERSION 3.10)

project(DSL_Compiler)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(
    Parser
    parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h
)

FLEX_TARGET(
    Scanner
    scanner.l
    ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

include_directories(
    src
    generator
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(
    dsl_to_cpp
    src/main.cpp
    generator/generator.cpp
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Scanner_OUTPUTS}
)