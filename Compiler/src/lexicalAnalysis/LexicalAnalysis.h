//
// Created by ahmed on 12/2/2022.
//

#ifndef COMPILER_LEXICAL_ANALYSIS_H
#define COMPILER_LEXICAL_ANALYSIS_H


#include <chrono>
#include <iostream>
#include "src/lexicalAnalysis/LexicalRules/lexicalRules.h"
#include "src/lexicalAnalysis/nfaGraphGenerator/NFAGenerator.h"
#include "src/lexicalAnalysis/shared/DFAstate.h"
#include "src/lexicalAnalysis/dfaGraphGenerator/DFA.h"
#include "src/lexicalAnalysis/dfa_minimization/vectorDFA.h"
#include "src/lexicalAnalysis/dfa_minimization/DFAMinimizer.h"

class LexicalAnalysis {
    //TODO Add the tokens queues for milestone 2
private:
    static LexicalRules *readRules(const string &rulesPath) {
        auto start = chrono::steady_clock::now();

        auto *lRules = new LexicalRules();
        lRules->readFileContent(rulesPath);

        auto end = chrono::steady_clock::now();
        cout << "readRules: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

        return lRules;
    }

    static NFAGenerator *generateNFA(LexicalRules *rules) {
        auto start = chrono::steady_clock::now();

        auto *nfaGenerator = new NFAGenerator(rules);

        auto end = chrono::steady_clock::now();
        cout << "generateNFA: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

        return nfaGenerator;
    }

    static vector<DFAstate *> generateDFA(LexicalRules *rules, NFAGenerator *nfa) {
        auto start = chrono::steady_clock::now();

        DFA dfa(rules->getRules(), nfa->getNFARoot());
        vector<DFAstate *> dfaVec = dfa.build_DFA();

        auto end = chrono::steady_clock::now();
        cout << "generateDFA: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

        return dfaVec;
    }

    static vectorDFA *minimizeDFA(vector<DFAstate *> &dfaVec) {
        auto start = chrono::steady_clock::now();

        vectorDFA vecDFA(dfaVec);
        vectorDFA *minimizedDFA = DFAMinimizer::minimize(&vecDFA);

        auto end = chrono::steady_clock::now();
        cout << "minimizeDFA: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

        return minimizedDFA;
    }

    static vectorDFA *getMinimizedDFA() {
        auto rules = readRules(".././lexical rules.txt");
        auto nfa = generateNFA(rules);
        auto dfaVec = generateDFA(rules, nfa);

        delete rules;
        delete nfa;

        auto minDFA = minimizeDFA(dfaVec);
        printf("Original: %zu,  Minimized: %zu\n", dfaVec.size(), minDFA->getTransitionTable().size());

        for (auto x: dfaVec) {
            delete x;
        }
        dfaVec.clear();
        return minDFA;
    }

    static void parseInputFile(const string &inputFilePath, const string &outputFilePath, vectorDFA *dfa) {
        ifstream inputFile;
        inputFile.open(inputFilePath.c_str());
        ofstream outputFile;
        outputFile.open(outputFilePath.c_str());
        string token;
        while (inputFile >> token) {
            int state = 0, start = 0;
            for (int i = start; i < token.size(); i++) {
                state = dfa->nextState(state, token[i]);
                if (state == -1 && start < token.size() - 1) {
                    i = start;
                    start++;
                    state = 0;
                }
            }
            if (state != -1 && dfa->getStateInfo(state).acceptance) {
                if (start != 0) {
                    outputFile << "Error reported and fixed to -> ";
                    printf("Error reported and fixed to -> ");
                }
                outputFile << dfa->getStateInfo(state).tokenName.c_str() << endl;
                printf("state %d: %s\n", state, dfa->getStateInfo(state).tokenName.c_str());
            } else {
                outputFile << "Invalid input!" << endl;
                printf("Invalid input!\n");
            }
        }
        inputFile.close();
        outputFile.close();
    }

public:

    //TODO make non static when create the tokens queue (Milestone 2)
    static void analyzeInput() {
        auto minDFA = getMinimizedDFA();
        //TODO Files path need to be taken from the console
        parseInputFile(".././input file.txt", ".././lexical output.txt", minDFA);
        delete minDFA;
    }

};


#endif //COMPILER_LEXICAL_ANALYSIS_H
