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
        src/lexicalAnalysis/shared/NFAState.cpp
        src/lexicalAnalysis/shared/NFAState.h
        src/lexicalAnalysis/nfaGraphGenerator/NFAStackNode.h
        src/lexicalAnalysis/nfaGraphGenerator/NFAStackNode.cpp
        src/lexicalAnalysis/shared/PostfixContainer.h
        src/lexicalAnalysis/shared/PostfixContainer.cpp
        src/lexicalAnalysis/nfaGraphGenerator/NFAGenerator.cpp
        src/lexicalAnalysis/nfaGraphGenerator/NFAGenerator.h
        src/lexicalAnalysis/dfaGraphGenerator/DFA.h
        src/lexicalAnalysis/dfaGraphGenerator/DFA.cpp
        src/lexicalAnalysis/dfa_minimization/vectorDFA.cpp
        src/lexicalAnalysis/dfa_minimization/vectorDFA.h
        src/lexicalAnalysis/dfa_minimization/DFAMinimizer.cpp
        src/lexicalAnalysis/dfa_minimization/DFAMinimizer.h)
