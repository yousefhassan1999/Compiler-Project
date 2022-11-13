#include <iostream>
#include <vector>
#include "state.h"

using namespace std;

void State::SetStartState(bool b){
    startState = b;
}
void State::SetTokenName(string s){
    tokenName = s;
}
void State::SetTokenLexema(string s){
    tokenLexema = s;
}
void State::SetAcceptanceState(bool b){
    acceptanceState = b;
}
void State::SetAddToStateEdges(Edge e){
    stateEdges.push_back(e);
}

bool& State::GetStartState(){
    return startState;
}
bool& State::GetAcceptanceState(){
    return acceptanceState;
}

string& State::GetTokenName(){
    return tokenName;
}
string& State::GetTokenLexema(){
    return tokenLexema;
}
vector<Edge>& State::GetAStateEdges(){
    return stateEdges;
}
