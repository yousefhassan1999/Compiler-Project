#ifndef NFA_H_INCLUDED
#define NFA_H_INCLUDED

#include "nfaState.h"


class NFA {

    NFAstate startState;
    NFAstate endState;

public:
    void SetStartState(NFAstate s);

    void SetEndState(NFAstate s);

    NFAstate &GetStartState();

    NFAstate &GetEndState();

private:

};

#endif // NFA_H_INCLUDED
