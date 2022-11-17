#ifndef LEXICALGENERATOR_H_INCLUDED
#define LEXICALGENERATOR_H_INCLUDED

#include <unordered_map>
#include <stack>
#include "lexicalRules.h"
#include "nfaState.h"
#include "nfa.h"

class LexicalGenerator {

    LexicalRules lexicalRules;
    NFAstate startState;

public:
    LexicalRules &GetLexicalRules();

    void GenerateNFA();

private:

    static NFA *generateOrNFA(NFA *first, NFA *second);

    static void applyOr(std::stack<NFA *> *nfaStack);

    static NFA *generateBaseNFA(char key);

    static void applyOneOrMore(NFA *current);

    static void applyZeroOrMore(NFA *current);

    static NFA *generateAndNFA(NFA *first, NFA *second);

    static void applyAnd(std::stack<NFA *> *nfaStack);

    static void acceptNFA(NFA *current, std::string tokenName);
};

#endif // LEXICALGENERATOR_H_INCLUDED
