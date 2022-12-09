#include <fstream>
#include "NFAStackNode.h"

NFAStackNode::NFAStackNode(NFAstate *startState, NFAstate *endState) {
    this->startState = startState;
    this->endState = endState;
}

NFAstate *NFAStackNode::getStartState() {
    return startState;
}

NFAstate *NFAStackNode::getEndState() {
    return endState;
}
