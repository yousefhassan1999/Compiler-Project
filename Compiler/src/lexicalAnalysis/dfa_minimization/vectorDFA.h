#ifndef COMPILER_VECTOR_DFA_H
#define COMPILER_VECTOR_DFA_H

#include "src/lexicalAnalysis/dfaGraphGenerator/DFA.h"

#include <utility>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class StateInfo {
public:
    bool acceptance = false;
    string tokenName;
    string tokenLexema;

    StateInfo() = default;
    StateInfo(string tokenName, string tokenLexema) {
        this->tokenName = std::move(tokenName);
        this->tokenLexema = std::move(tokenLexema);
    }
};

class vectorDFA {
private:
    vector<unordered_map<char, toState>> transitionTable;
    vector<StateInfo> states;
public:
    explicit vectorDFA(int nStates);
    explicit vectorDFA(vector<DFAstate *> &dfaVec);

    vector<unordered_map<char, toState>> &getTransitionTable();
    StateInfo &getStateInfo(int state);
    void addTransition(int start, char input, int end);
    void addAcceptanceState(int state, string &tokenName, string &tokenLexema);
    int nextState(int currentState, char input);
};

#endif //COMPILER_VECTOR_DFA_H
