#ifndef NFA_H_INCLUDED
#define NFA_H_INCLUDED

#include "nfaState.h"


class NFA {
private:
    NFAstate *startState;
    NFAstate *endState;

public:
    NFA(NFAstate *startState, NFAstate *endState);

    NFAstate *getStartState();

    NFAstate *getEndState();
};

#endif // NFA_H_INCLUDED
