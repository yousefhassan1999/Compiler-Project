#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <vector>
#include <unordered_map>
#include <string>
#include <map>

class NFAstate {

    bool acceptance = false;
    std::string tokenName;
    std::string tokenLexema;
    std::unordered_map<char, std::vector<NFAstate *>> transitions;

public:
    void setTokenName(std::string s);

    void setTokenLexema(std::string s);

    void setAcceptance(bool b);

    void SetAddTransitions(char key, NFAstate *s);

    bool &getAcceptance();

    std::string &getTokenName();

    std::string &getTokenLexema();

    std::unordered_map<char, std::vector<NFAstate *>> & getTransitions();

private:

};

#endif // STATE_H_INCLUDED
