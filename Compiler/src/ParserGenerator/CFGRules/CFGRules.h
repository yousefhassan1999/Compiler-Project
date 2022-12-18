#ifndef COMPILER_CFGRULES_H
#define COMPILER_CFGRULES_H

#include <vector>
#include <map>
#include <string>
#include <list>
#include "CFGContainer.h"

//done
class CFGRules {

    std::list<CFGContainer> CFGRulesVec;
public:
    void readFileContent(const std::string &Path);

    std::list<CFGContainer> *GetCFGRulesVec();

    void RemoveLeftRec();

    void ApplyLeftRefactor();

private:
    static std::list<std::string> Split(std::string RHSBasicString, std::string basicString, std::string splitPattern);

    static std::string deleteLeadingAndTrailingSpace(std::string basicString);

    bool LeftRecUpdate(std::string Key, std::list<std::string> *RHSVec, CFGContainer *newContainer);

    std::string ConvertListToString(std::list<std::string> list);
};

#endif //COMPILER_CFGRULES_H
