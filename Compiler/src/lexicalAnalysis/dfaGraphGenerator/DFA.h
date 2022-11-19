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

class DFA {
private:

    NFAstate *start;

    set<char> chars;

    static void epsilonClosure(unordered_set<NFAstate *> *closure);

    static unordered_set<NFAstate *> move(unordered_set<NFAstate *> closure, char a);

    void create_inputs(vector<PostfixContainer> *rules);

public:


    vector<DFAstate *> build_DFA();

    DFA(vector<PostfixContainer> *rules, NFAstate *start) {
        this->start = start;
        create_inputs(rules);
    }


};


#endif //COMPILER_DFA_H
