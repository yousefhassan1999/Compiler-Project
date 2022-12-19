//
// Created by ahmed on 12/19/2022.
//

#ifndef COMPILER_FIRSTOBJECT_H
#define COMPILER_FIRSTOBJECT_H

#include <bits/stdc++.h>
using namespace std;

class FirstObject {
private:
    string terminal;
    string rule;
public:
    FirstObject(string NewTerminal,string rule);

    string GetTerminal();

    string GetRule();

    void SetTerminal(string NewTerminal);

    void SetRule(string rule);

};


#endif //COMPILER_FIRSTOBJECT_H
