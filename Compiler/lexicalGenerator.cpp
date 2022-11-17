#include <iostream>
#include <utility>
#include "lexicalGenerator.h"
#include "lexicalRules.h"

#define EPSILON ' '

using namespace std;

void LexicalGenerator::GenerateNFA() {
    for (auto &it: lexicalRules.GetRules()) {
        cout << it.getTokenName() << ' ' << it.getPostFix() << "\n";
    }
    stack<NFA *> nfaStack;
    for (auto &rule: lexicalRules.GetRules()) {
        for (auto &ch: rule.getPostFix()) {
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
        if(nfaStack.size() == 2){
            applyOr(&nfaStack);
        }
    }

}

void LexicalGenerator::acceptNFA(NFA *current, string tokenName) {
    NFAstate *endState = current->getEndState();
    endState->SetAcceptence(true);
    endState->SetTokenName(std::move(tokenName));
}

NFA *LexicalGenerator::generateBaseNFA(char key) {
    NFA *generatedNFA = new NFA(new NFAstate(), new NFAstate());
    generatedNFA->getEndState()->SetTokenLexema(string(1, key));
    generatedNFA->getStartState()->SetAddTransitions(key, generatedNFA->getEndState());
    return generatedNFA;
}

NFA *LexicalGenerator::generateOrNFA(NFA *first, NFA *second) {
    NFA *generatedNFA = new NFA(new NFAstate(), new NFAstate());
    generatedNFA->getStartState()->SetAddTransitions(EPSILON, first->getStartState());
    generatedNFA->getStartState()->SetAddTransitions(EPSILON, second->getStartState());
    first->getEndState()->SetAddTransitions(EPSILON, generatedNFA->getEndState());
    second->getEndState()->SetAddTransitions(EPSILON, generatedNFA->getEndState());
    delete first;
    delete second;
    return generatedNFA;
}

NFA *LexicalGenerator::generateAndNFA(NFA *first, NFA *second) {
    NFA *generatedNFA = new NFA(new NFAstate(), new NFAstate());
    generatedNFA->getStartState()->SetAddTransitions(EPSILON, first->getStartState());
    first->getEndState()->SetAddTransitions(EPSILON, second->getStartState());
    second->getEndState()->SetAddTransitions(EPSILON, generatedNFA->getEndState());
    delete first;
    delete second;
    return generatedNFA;
}

void LexicalGenerator::applyAnd(stack<NFA *> *nfaStack) {
    NFA *second = nfaStack->top();
    nfaStack->pop();
    NFA *first = nfaStack->top();
    nfaStack->pop();
    nfaStack->push(generateAndNFA(first, second));
}

void LexicalGenerator::applyOr(stack<NFA *> *nfaStack) {
    NFA *first = nfaStack->top();
    nfaStack->pop();
    NFA *second = nfaStack->top();
    nfaStack->pop();
    nfaStack->push(generateOrNFA(first, second));
}

void LexicalGenerator::applyOneOrMore(NFA *current) {
    current->getEndState()->SetAddTransitions(EPSILON, current->getStartState());
}

void LexicalGenerator::applyZeroOrMore(NFA *current) {
    applyOneOrMore(current);
    current->getStartState()->SetAddTransitions(EPSILON, current->getEndState());
}

LexicalRules &LexicalGenerator::GetLexicalRules() {
    return lexicalRules;
}

