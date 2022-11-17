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

};

#endif // LEXICALGENERATOR_H_INCLUDED
