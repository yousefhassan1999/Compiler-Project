#ifndef NFA_H_INCLUDED
#define NFA_H_INCLUDED

#include "nfaState.h"


class NFA {

    NFAstate startState;
    NFAstate endState;

public:
    void setStartState(NFAstate s);

    void setEndState(NFAstate s);

    NFAstate &getStartState();

    NFAstate &getEndState();

private:

};

#endif // NFA_H_INCLUDED
