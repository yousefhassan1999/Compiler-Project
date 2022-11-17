#include <fstream>
#include "nfa.h"

NFA::NFA(NFAstate *startState, NFAstate *endState) {
    this->startState = startState;
    this->endState = endState;
}

NFAstate *NFA::getStartState() {
    return startState;
}

NFAstate *NFA::getEndState() {
    return endState;
}
