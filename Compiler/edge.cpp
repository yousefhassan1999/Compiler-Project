#include <iostream>
#include "edge.h"

using namespace std;

void Edge::setTrx(char s){
    trx += s;
}
void Edge::setNextState(State* st){
    nextState = st;
}

string& Edge::GetTrx(){
    return trx;
}
State* Edge::GetNextState(){
    return nextState;
}
