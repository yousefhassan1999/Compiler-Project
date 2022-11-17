#include <fstream>
#include <string>
#include "nfa.h"

void NFA::SetStartState(NFAstate s) {
    startState = s;
}

void NFA::SetEndState(NFAstate s) {
    endState = s;
}

NFAstate &NFA::GetStartState() {
    return startState;
}

NFAstate &NFA::GetEndState() {
    return endState;
}