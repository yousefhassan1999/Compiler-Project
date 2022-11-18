#ifndef NFA_H_INCLUDED
#define NFA_H_INCLUDED

#include "src/lexicalAnalysis/shared/NFAState.h"


class NFAStackNode {
private:
    NFAstate *startState;
    NFAstate *endState;

public:
    NFAStackNode(NFAstate *startState, NFAstate *endState);

    NFAstate *getStartState();

    NFAstate *getEndState();
};

#endif // NFA_H_INCLUDED
