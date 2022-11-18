#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class StateInfo {
public:
    bool acceptance = false;
    string tokenName;
    string tokenLexema;

    StateInfo() {}
    StateInfo(string tokenName, string tokenLexema) {
        this->acceptance = true;
        this->tokenName = tokenName;
        this->tokenLexema = tokenLexema;
    }
};

class DFA {
private:
    unordered_map<char, int> inputIdx;
    vector<vector<int>> transitionTable;
    vector<StateInfo> states;
    int inputCount;
public:
    DFA(int nStates, int nInputs);

    vector<vector<int>> &getTransitionTable();
    StateInfo& getStateInfo(int state);
    unordered_map<char, int> getInputIdx();

    unsigned long long inputsSize();
    void addTransition(int start, char input, int end);
    void addAcceptanceState(int state, string tokenName, string tokenLexema);
    int nextState(int currentState, char input);
};

#endif //COMPILER_DFA_H
