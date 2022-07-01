cmake_minimum_required(VERSION 3.22)
project(busqueda C)

set(CMAKE_C_STANDARD 99)

add_executable(busqueda main.c read_files.c read_files.h rabin_karp.c rabin_karp.h)
