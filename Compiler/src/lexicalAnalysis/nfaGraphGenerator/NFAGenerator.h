//
// Created by ahmed on 11/18/2022.
//

#ifndef COMPILER_NFAGENERATOR_H
#define COMPILER_NFAGENERATOR_H


#include <utility>
#include <stack>

#include "src/lexicalAnalysis/lexicalRules.h"
#include "src/lexicalAnalysis/shared/NFAState.h"
#include "NFAStackNode.h"

class NFAGenerator {
private:
    LexicalRules *lexicalRules;
    NFAstate *nfaRoot{};
public:
    explicit NFAGenerator(LexicalRules *lexicalRules) {
        this->lexicalRules = lexicalRules;
    }

    NFAstate *generateNFA();

    NFAstate *getNFARoot() {
        return nfaRoot;
    }

private:
    void setNFARoot(NFAStackNode *nfaStackNode);

    static NFAStackNode *generateOrNFA(NFAStackNode *first, NFAStackNode *second);

    static void applyOr(std::stack<NFAStackNode *> *nfaStack);

    static NFAStackNode *generateBaseNFA(char key);

    static void applyOneOrMore(NFAStackNode *current);

    static void applyZeroOrMore(NFAStackNode *current);

    static NFAStackNode *generateAndNFA(NFAStackNode *first, NFAStackNode *second);

    static void applyAnd(std::stack<NFAStackNode *> *nfaStack);

    static void acceptNFA(NFAStackNode *current, std::string tokenName);

};


#endif //COMPILER_NFAGENERATOR_H
