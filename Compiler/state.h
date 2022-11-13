#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include <vector>
#include <string>
#include <map>
#include "edge.h"

class Edge;        // forward declaration
class State {

    bool startState;
    bool acceptanceState;
    std::string tokenName;
    std::string tokenLexema;
    std::vector<Edge> stateEdges;
    //std::map<std::string, std::vector<State>> nextStates;
public:
    void SetStartState(bool b);
    void SetTokenName(std::string s);
    void SetTokenLexema(std::string s);
    void SetAcceptanceState(bool b);
    void SetAddToStateEdges(Edge e);
    //void SetAddToNextStates(string key ,State s);

    bool& GetStartState();
    bool& GetAcceptanceState();
    std::string& GetTokenName();
    std::string& GetTokenLexema();
    std::vector<Edge>& GetAStateEdges();
    //std::map<std::string, std::vector<State>>& GetNextStates();
private:

};

#endif // STATE_H_INCLUDED
