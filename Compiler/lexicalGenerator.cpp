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
    stack<NFA> nfaStack;
    for (auto &rule: lexicalRules.GetRules()){
        for (auto &ch : rule.getPostFix()){
            if(ch == '|'){
                applyOr(&nfaStack);
            } else if(ch == '*'){
                applyZeroOrMore(nfaStack.top());
            } else if (ch == '+'){
                applyOneOrMore(nfaStack.top());
            } else if (ch == ' '){
                NFA second = nfaStack.top();
                nfaStack.pop();
                NFA first = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(generateAndNFA(first,second));
            } else {
                nfaStack.push(generateBaseNFA(ch));
            }
        }
        acceptNFA(nfaStack.top(), rule.getTokenName());
        //TODO: merge the resulted NFA from Stack into one using or condition
    }
}

void LexicalGenerator::acceptNFA(NFA current, string tokenName) {
    NFAstate endState = current.getEndState();
    endState.SetAcceptence(true);
    endState.SetTokenName(std::move(tokenName));
}

NFA LexicalGenerator::generateBaseNFA(char key) {
    NFA generatedNFA;
    NFAstate generatedStartState;
    NFAstate generatedEndState;
    //TODO: check token lexema
    generatedEndState.SetTokenLexema(to_string(key));
    generatedStartState.SetAddTransitions(key,generatedEndState);
    generatedNFA.setStartState(generatedStartState);
    generatedNFA.setEndState(generatedEndState);
    return generatedNFA;
}

NFA LexicalGenerator::generateOrNFA(NFA first, NFA second) {
    NFA generatedNFA;
    NFAstate generatedStartState;
    NFAstate generatedEndState;
    generatedStartState.SetAddTransitions(EPSILON, first.getStartState());
    generatedStartState.SetAddTransitions(EPSILON, second.getStartState());
    first.getEndState().SetAddTransitions(EPSILON, generatedEndState);
    second.getEndState().SetAddTransitions(EPSILON, generatedEndState);
    generatedNFA.setStartState(generatedStartState);
    generatedNFA.setEndState(generatedEndState);
    return generatedNFA;
}

NFA LexicalGenerator::generateAndNFA(NFA first, NFA second) {
    NFA generatedNFA;
    NFAstate generatedStartState;
    NFAstate generatedEndState;
    generatedStartState.SetAddTransitions(EPSILON, first.getStartState());
    first.getEndState().SetAddTransitions(EPSILON, second.getStartState());
    second.getEndState().SetAddTransitions(EPSILON, generatedEndState);
    generatedNFA.setStartState(generatedStartState);
    generatedNFA.setEndState(generatedEndState);
    return generatedNFA;
}

void LexicalGenerator::applyOr(stack<NFA>* nfaStack){
    NFA first = nfaStack->top();
    nfaStack->pop();
    NFA second = nfaStack->top();
    nfaStack->pop();
    nfaStack->push(generateOrNFA(first,second));
}

void LexicalGenerator::applyOneOrMore(NFA current){
    current.getEndState().SetAddTransitions(EPSILON, current.getStartState());
}

void LexicalGenerator::applyZeroOrMore(NFA current){
    applyOneOrMore(current);
    current.getStartState().SetAddTransitions(EPSILON, current.getEndState());
}

LexicalRules &LexicalGenerator::GetLexicalRules() {
    return lexicalRules;
}



