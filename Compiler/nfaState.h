#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <vector>
#include <unordered_map>
#include <string>
#include <map>

class NFAstate {

    bool Acceptence;
    std::string tokenName;
    std::string tokenLexema;
    std::unordered_map<char, std::vector<NFAstate *>> transitions;

public:
    void SetTokenName(std::string s);

    void SetTokenLexema(std::string s);

    void SetAcceptence(bool b);

    void SetAddTransitions(char key, NFAstate* s);

    bool &GetAcceptence();

    std::string &GetTokenName();

    std::string &GetTokenLexema();

    std::unordered_map<char, std::vector<NFAstate *>> &GetTransitions();

private:

};

#endif // STATE_H_INCLUDED
