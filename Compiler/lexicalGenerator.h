#ifndef LEXICALGENERATOR_H_INCLUDED
#define LEXICALGENERATOR_H_INCLUDED
#include <unordered_map>
#include <string>
#include "lexicalRules.h"
#include "state.h"
#include "edge.h"

class LexicalGenerator {

    LexicalRules lexicalRules;
    std::unordered_map<std::string, State> regularDefinitionsMaps;
    std::unordered_map<char, int> operatorPrecedence;
    State startState;

public:
    LexicalRules& GetLexicalRules();
    void GenerateNFA();
private:
    void GenerateKeyWordBranch(std::string keyWord);
    std::map<std::string, std::string> postfixNotation(std::map<std::string, std::string> map1);
    std::string convertToPostfix(std::string basicString);

};

#endif // LEXICALGENERATOR_H_INCLUDED
