//
// Created by Ahmed on 11/18/2022.
//

#ifndef COMPILER_DFASTATE_H
#define COMPILER_DFASTATE_H
#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include "nfaState.h"
using namespace std;
class DFAstate
{
public:
    bool mark;
    bool Acceptence;
    string tokenName;
    string tokenLexema;
    unordered_set<NFAstate*> closure;
    unordered_map<char,DFAstate*> transitions;
    DFAstate(){
        mark = false;
        Acceptence=false;
        tokenLexema="";
        tokenName="";
    }
};
#endif //COMPILER_DFASTATE_H
