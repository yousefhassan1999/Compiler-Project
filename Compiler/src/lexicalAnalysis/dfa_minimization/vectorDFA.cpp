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
    if(transitionTable[currentState].count(input) == 0)
        return -1;
    return transitionTable[currentState].at(input).get();
}

void vectorDFA::printTransitionTable(const string& filePath) {
    ofstream outputFile;
    outputFile.open(filePath.c_str());
    outputFile << "state,token name";

    unordered_set<char> inputSet;
    for (auto& state : transitionTable) {
        for (auto& edge : state) {
            if(inputSet.count(edge.first) <= 0){
                inputSet.insert(edge.first);
            }
        }
    }

    vector<char> inputs;
    for (auto input : inputSet) {
        inputs.push_back(input);
    }
    sort(inputs.begin(), inputs.end());
    for (auto input : inputs) {
        if(input == ',')
            outputFile << ",\"" << input << '\"';
        else
            outputFile << ',' << input;
    }
    outputFile << endl;

    for(int i = 0; i < transitionTable.size(); ++i) {
        string stateName = getStateInfo(i).acceptance ? getStateInfo(i).tokenName : "";
        outputFile << i << ',' << stateName;
        auto& edges = transitionTable[i];
        for (auto input : inputs) {
            string nextState = edges.count(input) > 0 ? to_string(edges.at(input).get()) : "";
            outputFile << "," << nextState;
        }
        outputFile << endl;
    }

    outputFile.close();
}
