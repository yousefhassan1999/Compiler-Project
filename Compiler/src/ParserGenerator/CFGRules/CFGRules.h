#ifndef COMPILER_CFGRULES_H
#define COMPILER_CFGRULES_H

#include <vector>
#include <map>
#include <unordered_map>
#include <string>

class CFGRules {

    std::map<std::string, std::vector<std::string>> CFGRulesVec;
public:
    void readFileContent(const std::string& Path);

    std::map<std::string, std::vector<std::string>>* GetCFGRulesVec();

private:
//    bool checkRegularDefinition(std::string LR);
//
//    bool checkPunctuations(std::string LR);
//
//    bool checkKeyWords(std::string LR);
//
//    static std::string updateMinus(std::string basicString);
//
//    std::string checkMapSubstring(std::string basicString);
//
//    static int isSubstring(const std::string& basicString, const std::string& basicString1);
//
//    void updateRegularExpressions();
//
//    static std::string addSeparator(std::string basicString);
//
    static std::string deleteLeadingAndTrailingSpace(std::string basicString);
//
//    std::string convertToPostfix(std::string basicString);
//
//    std::string specialConvertToPostfix(std::string basicString);
};

#endif //COMPILER_CFGRULES_H
