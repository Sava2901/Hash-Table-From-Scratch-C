cmake_minimum_required(VERSION 3.26)
project(Hash_Table_From_Scratch_C C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(Hash_Table_From_Scratch_C
        src/hash_table.c
        src/hash_table.h
        src/main.c
)
