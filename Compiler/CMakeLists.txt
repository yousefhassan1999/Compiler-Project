cmake_minimum_required(VERSION 3.23)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Compiler
        src/lexicalAnalysis/lexicalGenerator.cpp
        src/lexicalAnalysis/lexicalGenerator.h
        src/lexicalAnalysis/lexicalRules.cpp
        src/lexicalAnalysis/lexicalRules.h
        src/main.cpp
        src/lexicalAnalysis/nfaState.cpp
        src/lexicalAnalysis/nfaState.h
        src/lexicalAnalysis/nfa.h
        src/lexicalAnalysis/nfa.cpp
        src/lexicalAnalysis/nfaPostfix.h
        src/lexicalAnalysis/nfaPostfix.cpp src/lexicalAnalysis/dfa_minimization/DFA.cpp src/lexicalAnalysis/dfa_minimization/DFA.h src/lexicalAnalysis/dfa_minimization/DFAMinimizer.cpp src/lexicalAnalysis/dfa_minimization/DFAMinimizer.h)
