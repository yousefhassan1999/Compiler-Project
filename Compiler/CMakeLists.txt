cmake_minimum_required(VERSION 3.23)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Compiler
        edge.cpp
        edge.h
        lexicalGenerator.cpp
        lexicalGenerator.h
        lexicalRules.cpp
        lexicalRules.h
        main.cpp
        nfaState.cpp
        nfaState.h
        nfa.h)
