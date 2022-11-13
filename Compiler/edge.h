#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED
#include "state.h"

class State;        // forward declaration
class Edge {

    std::string trx;
    State* nextState;
public:
    void setTrx(char s);
    void setNextState(State* st);

    std::string& GetTrx();
    State* GetNextState();
private:

};

#endif // EDGE_H_INCLUDED
