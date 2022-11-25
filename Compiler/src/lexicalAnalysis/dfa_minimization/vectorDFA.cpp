#include "vectorDFA.h"

vectorDFA::vectorDFA(int nStates) {
    this->transitionTable = vector<unordered_map<char, toState>>(nStates);
    this->states = vector<StateInfo>(nStates);
}

vectorDFA::vectorDFA(vector<DFAstate *> &dfaVec) {
    size_t nStates = dfaVec.size();
    this->transitionTable = vector<unordered_map<char, toState>>(nStates);
    this->states = vector<StateInfo>(nStates);

    for (int i = 0; i < nStates; ++i) {
        DFAstate *state = dfaVec[i];
        if(state->acceptance)
            addAcceptanceState(i, state->tokenName);
        for (auto &edge : state->transitions) {
            this->addTransition(i, edge.first, edge.second.get());
        }
    }
}

vector<unordered_map<char, toState>> &vectorDFA::getTransitionTable() {
    return this->transitionTable;
}

void vectorDFA::addTransition(int start, char input, int end) {
    this->transitionTable[start][input] = toState(end);
}

void vectorDFA::addAcceptanceState(int state, string &tokenName) {
    states[state].acceptance = true;
    states[state].tokenName = tokenName;
}

StateInfo &vectorDFA::getStateInfo(int state) {
    return states[state];
}

int vectorDFA::nextState(int currentState, char input) {
    if(this->transitionTable[currentState].count(input) == 0)
        return -1;
    return this->transitionTable[currentState].at(input).get();
}
