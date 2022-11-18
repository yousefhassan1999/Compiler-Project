#include "DFA.h"

DFA::DFA(int nStates) {
    this->transitionTable = vector<unordered_map<char, toState>>(nStates);
    states = vector<StateInfo>(nStates);
}

vector<unordered_map<char, toState>> &DFA::getTransitionTable() {
    return transitionTable;
}

void DFA::addTransition(int start, char input, int end) {
    transitionTable[start][input] = toState(end);
}

void DFA::addAcceptanceState(int state, string tokenName, string tokenLexema) {
    states[state] = *new StateInfo(std::move(tokenName), std::move(tokenLexema));
}

StateInfo &DFA::getStateInfo(int state) {
    return states[state];
}

int DFA::nextState(int currentState, char input) {
    return transitionTable[currentState][input].get();
}
