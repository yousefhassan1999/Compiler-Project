//
// Created by ahmed on 11/18/2022.
//

#include "NFAGenerator.h"

#define EPSILON ' '
using namespace std;

NFAstate *NFAGenerator::generateNFA(LexicalRules *lexicalRules) {
    stack<NFAStackNode *> nfaStack;
    for (auto rule: *lexicalRules->getRules()) {
        for (auto ch: rule.getPostFix()) {
            if (ch == '|') {
                applyOr(&nfaStack);
            } else if (ch == '*') {
                applyZeroOrMore(nfaStack.top());
            } else if (ch == '+') {
                applyOneOrMore(nfaStack.top());
            } else if (ch == ' ') {
                applyAnd(&nfaStack);
            } else {
                nfaStack.push(generateBaseNFA(ch));
            }
        }
        acceptNFA(nfaStack.top(), rule.getTokenName());
        if (nfaStack.size() == 2) {
            applyOr(&nfaStack);
        }
    }
    setNFARoot(nfaStack.top());
    return nfaRoot;
}


void NFAGenerator::setNFARoot(NFAStackNode *nfaStackNode) {
    nfaRoot = nfaStackNode->getStartState();
    delete nfaStackNode;
}

NFAStackNode *NFAGenerator::generateOrNFA(NFAStackNode *first, NFAStackNode *second) {
    auto generatedNFA = generateNewNFAStackNode();
    generatedNFA->getStartState()->SetAddTransitions(EPSILON, first->getStartState());
    generatedNFA->getStartState()->SetAddTransitions(EPSILON, second->getStartState());
    first->getEndState()->SetAddTransitions(EPSILON, generatedNFA->getEndState());
    second->getEndState()->SetAddTransitions(EPSILON, generatedNFA->getEndState());
    delete first;
    delete second;
    return generatedNFA;
}

void NFAGenerator::applyOr(std::stack<NFAStackNode *> *nfaStack) {
    NFAStackNode *first = nfaStack->top();
    nfaStack->pop();
    NFAStackNode *second = nfaStack->top();
    nfaStack->pop();
    nfaStack->push(generateOrNFA(first, second));
}

NFAStackNode *NFAGenerator::generateBaseNFA(char key) {
    auto generatedNFA = generateNewNFAStackNode();
    generatedNFA->getEndState()->setTokenLexema(string(1, key));
    generatedNFA->getStartState()->SetAddTransitions(key, generatedNFA->getEndState());
    return generatedNFA;
}

void NFAGenerator::applyOneOrMore(NFAStackNode *current) {
    current->getEndState()->SetAddTransitions(EPSILON, current->getStartState());
}

void NFAGenerator::applyZeroOrMore(NFAStackNode *current) {
    applyOneOrMore(current);
    current->getStartState()->SetAddTransitions(EPSILON, current->getEndState());
}

NFAStackNode *NFAGenerator::generateAndNFA(NFAStackNode *first, NFAStackNode *second) {
    auto generatedNFA = generateNewNFAStackNode();
    generatedNFA->getStartState()->SetAddTransitions(EPSILON, first->getStartState());
    first->getEndState()->SetAddTransitions(EPSILON, second->getStartState());
    second->getEndState()->SetAddTransitions(EPSILON, generatedNFA->getEndState());
    delete first;
    delete second;
    return generatedNFA;
}

void NFAGenerator::applyAnd(std::stack<NFAStackNode *> *nfaStack) {
    NFAStackNode *second = nfaStack->top();
    nfaStack->pop();
    NFAStackNode *first = nfaStack->top();
    nfaStack->pop();
    nfaStack->push(generateAndNFA(first, second));
}

void NFAGenerator::acceptNFA(NFAStackNode *current, std::string tokenName) {
    NFAstate *endState = current->getEndState();
    endState->setAcceptance(true);
    endState->setTokenName(std::move(tokenName));
}

NFAStackNode *NFAGenerator::generateNewNFAStackNode() {
    auto generatedNFA = new NFAStackNode(new NFAstate(), new NFAstate());
    internalNFAStates.insert(generatedNFA->getStartState());
    internalNFAStates.insert(generatedNFA->getEndState());
    return generatedNFA;
}
