#include <iostream>
#include <vector>
#include "nfaState.h"

using namespace std;

void NFAstate::SetTokenName(string s) {
    tokenName = s;
}

void NFAstate::SetTokenLexema(string s) {
    tokenLexema = s;
}

void NFAstate::SetAcceptence(bool b) {
    Acceptence = b;
}

void NFAstate::SetAddTransitions(char key, NFAstate s) {
    if (transitions.find(key) != transitions.end()) {
        transitions[key].push_back(&s);
    } else {
        vector<NFAstate *> vec;
        vec.push_back(&s);
        transitions[key] = vec;
    }
}

bool &NFAstate::GetAcceptence() {
    return Acceptence;
}

string &NFAstate::GetTokenName() {
    return tokenName;
}

string &NFAstate::GetTokenLexema() {
    return tokenLexema;
}

unordered_map<char, std::vector<NFAstate *>> &NFAstate::GetTransitions() {
    return transitions;
}

