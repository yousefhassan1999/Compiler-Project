#ifndef LEXICAL_GENERATOR_H_INCLUDED
#define LEXICAL_GENERATOR_H_INCLUDED

#include <unordered_map>
#include <stack>
#include "lexicalRules.h"
#include "nfaState.h"
#include "nfa.h"

class LexicalGenerator {

    LexicalRules lexicalRules;
    NFAstate startState;

public:
    LexicalRules &getLexicalRules();

    void generateNfa();

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

#endif // LEXICAL_GENERATOR_H_INCLUDED
