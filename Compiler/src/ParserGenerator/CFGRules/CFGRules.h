#ifndef COMPILER_CFGRULES_H
#define COMPILER_CFGRULES_H

#include <vector>
#include <map>
#include <string>
#include <list>
#include "CFGContainer.h"

class CFGRules {

    std::list<CFGContainer> CFGRulesVec;
    int incremental = 0;

public:
    void readFileContent(const std::string &Path);

    std::list<CFGContainer> *GetCFGRulesVec();

    void RemoveLeftRec();

private:
    static std::list<std::string> SplitOr(std::string RHSBasicString, std::string basicString);

    static std::string deleteLeadingAndTrailingSpace(std::string basicString);

    bool LeftRecUpdate(std::string Key, std::list<std::string> *RHSVec, CFGContainer *newContainer);

};

#endif //COMPILER_CFGRULES_H
