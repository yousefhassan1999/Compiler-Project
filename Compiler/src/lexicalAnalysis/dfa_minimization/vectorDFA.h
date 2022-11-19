#ifndef COMPILER_VECTOR_DFA_H
#define COMPILER_VECTOR_DFA_H

#include "src/lexicalAnalysis/dfaGraphGenerator/DFA.h"

#include <utility>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct toState
{
    int next = -1;
    toState() = default;
    explicit toState (int next){
        this->next = next;
    }
    int get() const {
        return this->next;
    }
};

class StateInfo {
public:
    bool acceptance = false;
    string tokenName;
    string tokenLexema;

    StateInfo() = default;
    StateInfo(string tokenName, string tokenLexema) {
        this->acceptance = true;
        this->tokenName = std::move(tokenName);
        this->tokenLexema = std::move(tokenLexema);
    }
};

class vectorDFA {
private:
    vector<unordered_map<char, toState>> transitionTable;
    vector<StateInfo *> states;
public:
    explicit vectorDFA(int nStates);
    explicit vectorDFA(vector<DFAstate *> &dfaVec);

    vector<unordered_map<char, toState>> &getTransitionTable();
    StateInfo* getStateInfo(int state);
    void addTransition(int start, char input, int end);
    void addStateInfo(int state, bool acceptance, string tokenName, string tokenLexema);
    int nextState(int currentState, char input);
};

#endif //COMPILER_VECTOR_DFA_H
