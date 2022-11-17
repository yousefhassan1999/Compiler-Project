#ifndef LEXICALRULES_H_INCLUDED
#define LEXICALRULES_H_INCLUDED

#include <vector>
#include <map>
#include <unordered_map>
#include "nfaPostfix.h"

class LexicalRules {

    std::map<std::string, std::string> RegularDefinitionsMap;
    std::vector<std::string> RegularExpressions;
    std::unordered_map<char, int> operatorPrecedence;
    std::vector<NFAPostfix> rules;

public:
    void ReadFileContaint(std::string Path);

    std::vector<NFAPostfix> &GetRules();

private:
    bool checkRegularDefinition(std::string LR);

    bool checkPunctuations(std::string LR);

    bool checkKeyWords(std::string LR);

    std::string updateMinus(std::string basicString);

    std::string CheckMapSubstring(std::string basicString);

    int isSubstring(std::string basicString, std::string basicString1);

    void UpdateRegularExpressions();

    std::string AddSeperator(std::string basicString);

    std::string DeleteLeadingAndTralingSpace(std::string basicString);

    std::string convertToPostfix(std::string basicString);

};

#endif // LEXICALRULES_H_INCLUDED
