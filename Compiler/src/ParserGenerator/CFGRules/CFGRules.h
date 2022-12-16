#ifndef COMPILER_CFGRULES_H
#define COMPILER_CFGRULES_H

#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <list>

class CFGRules {

    std::map<std::string, std::list<std::string>> CFGRulesVec;
    int incremental = 0;

public:
    void readFileContent(const std::string &Path);

    std::map<std::string, std::list<std::string>> *GetCFGRulesVec();

    void RemoveLeftRec();

    void RemoveIndirectLeftRec();

private:
    static std::list<std::string> SplitOr(std::string RHSBasicString, std::string basicString);

    static std::string deleteLeadingAndTrailingSpace(std::string basicString);

};

#endif //COMPILER_CFGRULES_H
