cmake_minimum_required(VERSION 3.22)
project(hashing C)

set(CMAKE_C_STANDARD 99)

add_executable(hashing main.c read_files.c read_files.h hash.c hash.h types.h types.c dynamic_list.c dynamic_list.h key_dependent.c key_dependent.h chaining.c chaining.h)
