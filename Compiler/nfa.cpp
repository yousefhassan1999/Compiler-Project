#include <fstream>
#include <string>
#include "nfa.h"

void NFA::setStartState(NFAstate s) {
    startState = s;
}

void NFA::setEndState(NFAstate s) {
    endState = s;
}

NFAstate &NFA::getStartState() {
    return startState;
}

NFAstate &NFA::getEndState() {
    return endState;
}