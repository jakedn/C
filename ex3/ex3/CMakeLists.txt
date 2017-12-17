cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c MyIntFunctions.c MyStringFunctions.c GenericHashTable.c HashIntSearch.c HashStrSearch.c Key.h
        TableErrorHandle.c TableErrorHandle.h)
add_executable(untitled ${SOURCE_FILES})