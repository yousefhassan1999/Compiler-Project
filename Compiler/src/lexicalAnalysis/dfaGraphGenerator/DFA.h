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
private:
    vector<PostfixContainer> *rules;

    static NFAstate *start;

    static void epsilonClosure(unordered_set<NFAstate *> *closure);

    static unordered_set<NFAstate *> move(unordered_set<NFAstate *> closure, char a);

public:
    static set<char> chars;

    static vector<DFAstate *> build_DFA();

    void create_inputs();

    DFA(vector<PostfixContainer> *rules,NFAstate *start){
        this->rules = rules;
        this->start = start;
    }


};


#endif //COMPILER_DFA_H
