cmake_minimum_required(VERSION 3.16)
project(tienda_belleza LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encuentra Qt (Core y Sql necesarios)
find_package(Qt6 REQUIRED COMPONENTS Core Sql)

add_subdirectory(src)