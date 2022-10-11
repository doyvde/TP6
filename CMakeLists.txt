cmake_minimum_required(VERSION 3.23)
project(TP6 C)

set(CMAKE_C_STANDARD 99)

add_executable(TP6 main.c mabiblio.c mabiblio.h)
file(COPY "graphe1.txt" DESTINATION ${CMAKE_BINARY_DIR})