#include "vectorDFA.h"

#include <utility>

vectorDFA::vectorDFA(int nStates) {
    this->transitionTable = vector<unordered_map<char, toState>>(nStates);
    states = vector<StateInfo*>(nStates);
}

vectorDFA::vectorDFA(vector<DFAstate *> *dfaVec) {
    int nState = dfaVec->size();
    this->transitionTable = vector<unordered_map<char, toState>>(nState);

    for (int i = 0; i < nState; ++i) {
        DFAstate *state = dfaVec->at(i);
        if(state->acceptance) {
            addAcceptanceState(i, state->tokenName, state->tokenLexema);
        }
        for (auto &edge : state->transitions) {
            addTransition(i, edge.first, edge.second);
        }
    }
}

vector<unordered_map<char, toState>> &vectorDFA::getTransitionTable() {
    return transitionTable;
}

void vectorDFA::addTransition(int start, char input, int end) {
    transitionTable[start][input] = toState(end);
}

void vectorDFA::addAcceptanceState(int state, string tokenName, string tokenLexema) {
    states[state] = new StateInfo(tokenName, tokenLexema);
}

StateInfo* vectorDFA::getStateInfo(int state) {
    return states[state];
}

int vectorDFA::nextState(int currentState, char input) {
    return transitionTable[currentState][input].get();
}
