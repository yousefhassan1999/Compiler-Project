//
// Created by Ahmed on 11/18/2022.
//

#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "DFAstate.h"
#include "nfaPostfix.h"
using namespace std;

class DFA {
    public:
    set<char> chars;
    void epsilonClosure(unordered_set<NFAstate *> *closure);
    unordered_set<NFAstate *> move(unordered_set<NFAstate *> closure, char a);
    vector<DFAstate *> build_DFA(NFAstate start,vector<char> inputs);

    void create_inputs(vector<NFAPostfix> rules);
};


#endif //COMPILER_DFA_H
