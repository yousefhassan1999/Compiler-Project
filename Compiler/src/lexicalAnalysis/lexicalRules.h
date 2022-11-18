#ifndef LEXICAL_RULES_H_INCLUDED
#define LEXICAL_RULES_H_INCLUDED

#include <vector>
#include <map>
#include <unordered_map>
#include "src/lexicalAnalysis/shared/PostfixContainer.h"

class LexicalRules {

    std::map<std::string, std::string> RegularDefinitionsMap;
    std::vector<std::string> RegularExpressions;
    std::unordered_map<char, int> operatorPrecedence;
    std::vector<PostfixContainer> rules;

public:
    void readFileContent(const std::string& Path);

    std::vector<PostfixContainer>* getRules();

private:
    bool checkRegularDefinition(std::string LR);

    bool checkPunctuations(std::string LR);

    bool checkKeyWords(std::string LR);

    static std::string updateMinus(std::string basicString);

    std::string checkMapSubstring(std::string basicString);

    static int isSubstring(const std::string& basicString, const std::string& basicString1);

    void updateRegularExpressions();

    static std::string addSeparator(std::string basicString);

    static std::string deleteLeadingAndTrailingSpace(std::string basicString);

    std::string convertToPostfix(std::string basicString);

    std::string specialConvertToPostfix(std::string basicString);
};

#endif // LEXICAL_RULES_H_INCLUDED
