//
// Created by ahmed on 11/18/2022.
//

#ifndef COMPILER_NFAGENERATOR_H
#define COMPILER_NFAGENERATOR_H


#include <utility>
#include <stack>
#include <iostream>
#include <unordered_set>

#include "src/lexicalAnalysis/lexicalRules.h"
#include "src/lexicalAnalysis/shared/NFAState.h"
#include "NFAStackNode.h"

class NFAGenerator {
private:
    NFAstate *nfaRoot;
    std::unordered_set<NFAstate *> internalNFAStates;
public:
    explicit NFAGenerator(LexicalRules *lexicalRules) {
        this->nfaRoot = nullptr;
        generateNFA(lexicalRules);
    }

    ~NFAGenerator() {
        std::cout << "start deleting NFA graph ...." << std::endl;
        for (auto state : internalNFAStates){
            delete state;
        }
        std::cout << "NFA graph deleted -_-!" << std::endl;
    }

    NFAstate *getNFARoot() {
        return nfaRoot;
    }

private:
    NFAstate *generateNFA(LexicalRules *lexicalRules);

    void setNFARoot(NFAStackNode *nfaStackNode);

    NFAStackNode *generateOrNFA(NFAStackNode *first, NFAStackNode *second);

    void applyOr(std::stack<NFAStackNode *> *nfaStack);

    NFAStackNode *generateBaseNFA(char key);

    NFAStackNode *generateNewNFAStackNode();

    static void applyOneOrMore(NFAStackNode *current);

    static void applyZeroOrMore(NFAStackNode *current);

    NFAStackNode *generateAndNFA(NFAStackNode *first, NFAStackNode *second);

    void applyAnd(std::stack<NFAStackNode *> *nfaStack);

    static void acceptNFA(NFAStackNode *current, std::string tokenName);

};


#endif //COMPILER_NFAGENERATOR_H
