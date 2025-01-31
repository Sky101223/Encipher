cmake_minimum_required(VERSION 3.10.0)

project(Encipher
    VERSION 1.0
    DESCRIPTION "用于加密"
    HOMEPAGE_URL "https://github.com/Sky101223/Encipher"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} src/Main.cpp)