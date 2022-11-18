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
    vector<PostfixContainer> *rules;

    NFAstate *start;

    set<char> chars;

    static void epsilonClosure(unordered_set<NFAstate *> *closure);

    static unordered_set<NFAstate *> move(unordered_set<NFAstate *> closure, char a);

    void create_inputs();

public:


    vector<DFAstate *> build_DFA();

    DFA(vector<PostfixContainer> *rules, NFAstate *start) {
        this->rules = rules;
        this->start = start;
        create_inputs();
    }


};


#endif //COMPILER_DFA_H
