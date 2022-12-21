cmake_minimum_required(VERSION 3.23)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Compiler
        src/lexicalAnalysis/LexicalRules/lexicalRules.cpp
        src/lexicalAnalysis/LexicalRules/lexicalRules.h
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
        src/lexicalAnalysis/dfa_minimization/DFAMinimizer.h
        src/parserGenerator/CFGRules/CFGRules.h
        src/parserGenerator/CFGRules/CFGRules.cpp
        src/parserGenerator/CFGRules/CFGContainer.cpp
        src/parserGenerator/CFGRules/CFGContainer.h
        src/parserGenerator/parseTable/ParseTable.cpp
        src/parserGenerator/parseTable/ParseTable.h
        src/parserGenerator/parseTable/FirstObject.cpp
        src/parserGenerator/parseTable/FirstObject.h
        src/parserGenerator/fileParser/FileParser.cpp
        src/parserGenerator/fileParser/FileParser.h
        src/common/ErrorLogger.cpp
        src/common/ErrorLogger.h
        src/lexicalAnalysis/LexicalAnalyzer.cpp
        src/lexicalAnalysis/LexicalAnalyzer.h)
