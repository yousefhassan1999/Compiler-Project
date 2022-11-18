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
class DFAstate
{
public:
    bool mark;
    bool acceptance;
    string tokenName;
    string tokenLexema;
    unordered_set<NFAstate*> closure;
    unordered_map<char,int> transitions;
    DFAstate(){
        mark = false;
        acceptance=false;
        tokenLexema="";
        tokenName="";
    }
};
#endif //COMPILER_DFA_STATE_H
