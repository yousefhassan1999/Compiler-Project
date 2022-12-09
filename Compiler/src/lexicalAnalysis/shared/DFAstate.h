//
// Created by Ahmed on 11/18/2022.
//

#ifndef COMPILER_DFA_STATE_H
#define COMPILER_DFA_STATE_H
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "nfaState.h"
using namespace std;

struct toState
{
    int next = -1;
    toState() = default;
    explicit toState (int next){
        this->next = next;
    }
    int get() const {
        return this->next;
    }
};

class DFAstate
{
public:
    bool mark;
    bool acceptance;
    string tokenName;
    string tokenLexema;
    unordered_set<NFAstate*> closure;
    unordered_map<char, toState> transitions;
    DFAstate(){
        mark = false;
        acceptance=false;
        tokenLexema="";
        tokenName="";
    }
};
#endif //COMPILER_DFA_STATE_H
