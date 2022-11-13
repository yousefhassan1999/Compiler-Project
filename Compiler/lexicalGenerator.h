#ifndef LEXICALGENERATOR_H_INCLUDED
#define LEXICALGENERATOR_H_INCLUDED
#include <unordered_map>
#include "lexicalRules.h"
#include "state.h"
#include "edge.h"

class LexicalGenerator {

    LexicalRules lexicalRules;
    std::unordered_map<std::string, State> RegularDifinationsMaps;
    std::vector<State> Paths;
    State startState;

public:
    LexicalRules& GetLexicalRules();
    void GenerateNFA();
private:
    void GenerateKeyWordBranch(std::string keyWord);
};

#endif // LEXICALGENERATOR_H_INCLUDED
