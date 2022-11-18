#ifndef LEXICAL_GENERATOR_H_INCLUDED
#define LEXICAL_GENERATOR_H_INCLUDED

#include <unordered_map>
#include <stack>
#include "lexicalRules.h"
#include "src/lexicalAnalysis/shared/NFAState.h"
#include "src/lexicalAnalysis/nfaGraphGenerator/NFAStackNode.h"

class LexicalGenerator {
private:
    LexicalRules lexicalRules;

public:
    LexicalRules *getLexicalRules();
};

#endif // LEXICAL_GENERATOR_H_INCLUDED
