//
// Created by Ahmed on 11/18/2022.
//

#ifndef COMPILER_DFA_H
#define COMPILER_DFA_H

#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "src/lexicalAnalysis/shared/DFAstate.h"
#include "src/lexicalAnalysis/shared/PostfixContainer.h"

using namespace std;

class DFA {
public:
    set<char> chars;

    static vector<DFAstate *> build_DFA(NFAstate start, vector<char> inputs);

    void create_inputs(vector<PostfixContainer> rules);

private:
    static void epsilonClosure(unordered_set<NFAstate *> *closure);

    static unordered_set<NFAstate *> move(unordered_set<NFAstate *> closure, char a);
};


#endif //COMPILER_DFA_H
