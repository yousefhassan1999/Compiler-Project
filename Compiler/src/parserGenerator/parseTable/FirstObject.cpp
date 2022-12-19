//
// Created by ahmed on 12/19/2022.
//

#include "FirstObject.h"

FirstObject::FirstObject(string NewTerminal, string rule) {
    FirstObject::terminal = NewTerminal;
    FirstObject::rule = rule;
}

string FirstObject::GetTerminal() {
    return FirstObject::terminal;
}

string FirstObject::GetRule() {
    return FirstObject::rule;
}

void FirstObject::SetTerminal(string NewTerminal) {
    FirstObject::terminal = NewTerminal;
}

void FirstObject::SetRule(string rule) {
    FirstObject::rule = rule;
}
