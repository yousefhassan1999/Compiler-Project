#include "vectorDFA.h"

vectorDFA::vectorDFA(int nStates) {
    this->transitionTable = vector<unordered_map<char, toState>>(nStates);
    states = vector<StateInfo>(nStates);
}

vector<unordered_map<char, toState>> &vectorDFA::getTransitionTable() {
    return transitionTable;
}

void vectorDFA::addTransition(int start, char input, int end) {
    transitionTable[start][input] = toState(end);
}

void vectorDFA::addAcceptanceState(int state, string tokenName, string tokenLexema) {
    states[state] = *new StateInfo(std::move(tokenName), std::move(tokenLexema));
}

StateInfo &vectorDFA::getStateInfo(int state) {
    return states[state];
}

int vectorDFA::nextState(int currentState, char input) {
    return transitionTable[currentState][input].get();
}
