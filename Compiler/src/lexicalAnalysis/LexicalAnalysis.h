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

    static void parseToken(const string &token, ofstream &outputFile, vectorDFA *dfa) {
        int originalState = 0, start = -1, maxAcceptanceState = -1;
        bool reportError = false;
        string lexema = "", maxAcceptanceLexema = "";
        for (int i = 0; i < token.size(); i++) {
            lexema += token[i];
            originalState = dfa->nextState(originalState, token[i]);
            if (originalState == -1) {
                if (maxAcceptanceState != -1) { // apply maximal munch
                    outputAcceptanceState(maxAcceptanceLexema, dfa->getStateInfo(maxAcceptanceState), reportError, outputFile);
                    i = start;
                    maxAcceptanceState = -1;
                } else { // apply panic mode recovery
                    reportError = true;
                    start++;
                    i = start;
                }
                originalState = 0;
                lexema = "";
            } else if (dfa->getStateInfo(originalState).acceptance) {
                maxAcceptanceState = originalState;
                maxAcceptanceLexema = lexema;
                start = i;
            }
        }
        if (maxAcceptanceState != -1) {
            outputAcceptanceState(maxAcceptanceLexema, dfa->getStateInfo(maxAcceptanceState), reportError, outputFile);
        } else {
            outputFile << "Invalid input!" << endl;
        }
    }

    static void outputAcceptanceState(const string &lexema, const StateInfo &stateInfo, bool &reportError, ofstream &outputFile) {
        if (reportError) {
            outputFile << "Error reported and fixed to -> ";
            reportError = false;
        }
        outputFile << lexema << " -> (" << stateInfo.tokenName.c_str() << ")" << endl;
    }

    static void parseInputFile(const string &inputFilePath, const string &outputFilePath, vectorDFA *dfa) {
        ifstream inputFile;
        inputFile.open(inputFilePath.c_str());
        ofstream outputFile;
        outputFile.open(outputFilePath.c_str());
        string token;
        while (inputFile >> token) {
            parseToken(token, outputFile, dfa);
        }
        inputFile.close();
        outputFile.close();
    }

public:

    //TODO make non static when create the tokens queue (Milestone 2)
    static void analyzeInput() {
        auto minDFA = getMinimizedDFA();
        minDFA->printTransitionTable("../transition_table.csv");
        char parseAgain = 'y';
        while (parseAgain == 'y'){
            parseInputFile(".././input file.txt", ".././lexical output.txt", minDFA);
            cout << "Successful Parsing, parse Again? (y)" << endl;
            cin >> parseAgain;
        }
        delete minDFA;
    }

};


#endif //COMPILER_LEXICAL_ANALYSIS_H
