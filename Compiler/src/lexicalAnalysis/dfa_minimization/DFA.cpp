#include "DFA.h"
#include <cassert>
#include <utility>

DFA::DFA(int nStates, int nInputs) {
    transitionTable = vector<vector<int>>(nStates, vector<int>(nInputs, -1));
    states = vector<StateInfo>(nStates);
    inputCount = 0;
}

vector<vector<int>> &DFA::getTransitionTable() {
    return transitionTable;
}

void DFA::addTransition(int start, char input, int end) {
    if(inputIdx.count(input) == 0) {
        assert(inputCount < transitionTable[0].size());
        inputIdx[input] = inputCount++;
    }
    transitionTable[start][inputIdx[input]] = end;
}

void DFA::addAcceptanceState(int state, string tokenName, string tokenLexema) {
    states[state] = *new StateInfo(std::move(tokenName), std::move(tokenLexema));
}

StateInfo &DFA::getStateInfo(int state) {
    return states[state];
}

int DFA::nextState(int currentState, char input) {
    if(inputIdx.count(input) == 0)
        return -1;
    return transitionTable[currentState][inputIdx[input]];
}

unsigned long long DFA::inputsSize() {
    return transitionTable[0].size();
}

DFA::DFA(int nStates, unordered_map<char, int> inputIdx) {
    transitionTable = vector<vector<int>>(nStates, vector<int>(inputIdx.size(), -1));
    this->inputIdx = inputIdx;
}

unordered_map<char, int> DFA::getInputIdx() {
    return inputIdx;
}
