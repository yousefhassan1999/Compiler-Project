//
// Created by Ahmed on 11/18/2022.
//

#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "DFAstate.h"
using namespace std;

class DFA {
    public:
    void epsilonClosure(unordered_set<NFAstate *> *closure);
    unordered_set<NFAstate *> move(unordered_set<NFAstate *> closure, char a);
    vector<DFAstate *> build_DFA(NFAstate start,vector<char> inputs);
};


#endif //COMPILER_DFA_H
