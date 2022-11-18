#include <iostream>
#include <utility>
#include <vector>
#include "NFAState.h"

using namespace std;

void NFAstate::setTokenName(string s) {
    tokenName = std::move(s);
}

void NFAstate::setTokenLexema(string s) {
    tokenLexema = std::move(s);
}

void NFAstate::setAcceptance(bool b) {
    acceptance = b;
}

void NFAstate::SetAddTransitions(char key, NFAstate* s) {
    if (transitions.find(key) != transitions.end()) {
        transitions[key].push_back(s);
    } else {
        vector<NFAstate *> vec;
        vec.push_back(s);
        transitions[key] = vec;
    }
}

bool &NFAstate::getAcceptance() {
    return acceptance;
}

string &NFAstate::getTokenName() {
    return tokenName;
}

string &NFAstate::getTokenLexema() {
    return tokenLexema;
}

unordered_map<char, std::vector<NFAstate *>> &NFAstate::GetTransitions() {
    return transitions;
}

