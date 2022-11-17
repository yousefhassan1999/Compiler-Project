#ifndef LEXICALGENERATOR_H_INCLUDED
#define LEXICALGENERATOR_H_INCLUDED

#include <unordered_map>
#include <string>
#include "lexicalRules.h"
#include "nfaState.h"

class LexicalGenerator {

    LexicalRules lexicalRules;
    NFAstate startState;

public:
    LexicalRules &GetLexicalRules();

    void GenerateNFA();

private:
    void acceptNFA(NFA current, string tokenName);
    NFA generateBaseNFA(char key);
    NFA generateOrNFA(NFA first, NFA second);
    NFA generateAndNFA(NFA first, NFA second);
    void applyOneOrMore(NFA current);
    void applyZeroOrMore(NFA current);
};

#endif // LEXICALGENERATOR_H_INCLUDED
