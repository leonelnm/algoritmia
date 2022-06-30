cmake_minimum_required(VERSION 3.22)
project(ordenacion C)

set(CMAKE_C_STANDARD 99)

add_executable(ordenacion main.c fileUtils.c fileUtils.h burbuja.c burbuja.h types.c types.h quickSort.c quickSort.h)
