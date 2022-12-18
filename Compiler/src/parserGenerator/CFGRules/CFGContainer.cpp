#include "CFGContainer.h"
#include <string>
#include <list>

using namespace std;

void CFGContainer::SetNonTerminal(string NewNonTerminal) {
    NonTerminal = NewNonTerminal;
}

void CFGContainer::SetRHS(list<string> newRHS) {
    RHS = newRHS;
}

string CFGContainer::GetNonTerminal() {
    return NonTerminal;
}

list<string> *CFGContainer::GetRHS() {
    return &RHS;
}

