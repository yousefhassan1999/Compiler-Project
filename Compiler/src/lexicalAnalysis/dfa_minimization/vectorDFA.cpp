#include "vectorDFA.h"

#include <utility>

vectorDFA::vectorDFA(int nStates) {
    this->transitionTable = vector<unordered_map<char, toState>>(nStates);
    this->states = vector<StateInfo*>(nStates);
}

vectorDFA::vectorDFA(vector<DFAstate *> &dfaVec) {
    size_t nStates = dfaVec.size();
    this->transitionTable = vector<unordered_map<char, toState>>(nStates);
    this->states = vector<StateInfo*>(nStates);

    for (int i = 0; i < nStates; ++i) {
        DFAstate *state = dfaVec[i];
        this->addStateInfo(i, state->acceptance, state->tokenName, state->tokenLexema);
        for (auto &edge : state->transitions) {
            this->addTransition(i, edge.first, edge.second);
        }
    }
}

vector<unordered_map<char, toState>> &vectorDFA::getTransitionTable() {
    return this->transitionTable;
}

void vectorDFA::addTransition(int start, char input, int end) {
    this->transitionTable[start][input] = toState(end);
}

void vectorDFA::addStateInfo(int state, bool acceptance, string tokenName, string tokenLexema) {
    if(acceptance)
        this->states[state] = new StateInfo(std::move(tokenName), std::move(tokenLexema));
    else
        this->states[state] = new StateInfo();
}

StateInfo* vectorDFA::getStateInfo(int state) {
    return this->states[state];
}

int vectorDFA::nextState(int currentState, char input) {
    return this->transitionTable[currentState][input].get();
}
