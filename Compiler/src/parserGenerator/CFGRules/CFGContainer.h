#ifndef COMPILER_CFGCONTAINER_H
#define COMPILER_CFGCONTAINER_H

#include <string>
#include <list>

class CFGContainer {
    std::string NonTerminal;
    std::list<std::string> RHS;

public:
    std::string GetNonTerminal();

    std::list<std::string> *GetRHS();

    void SetNonTerminal();

    void SetRHS();

    void SetNonTerminal(std::string NewNonTerminal);

    void SetRHS(std::list<std::string> newRHS);
};


#endif //COMPILER_CFGCONTAINER_H
