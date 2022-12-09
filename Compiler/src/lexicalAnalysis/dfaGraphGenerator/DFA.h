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

    static void epsilonClosure(unordered_set<NFAstate *> *closure);

    static unordered_set<NFAstate *> move(unordered_set<NFAstate *> closure, char a);


public:


    vector<DFAstate *> build_DFA();

    DFA(NFAstate *start) {
        this->start = start;
    }


};


#endif //COMPILER_DFA_H
