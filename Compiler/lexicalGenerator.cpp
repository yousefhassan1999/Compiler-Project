#include <iostream>
#include <string>
#include <stack>
#include "lexicalGenerator.h"
#include "lexicalRules.h"
#include "nfa.h"


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
                NFA first = nfaStack.top();
                nfaStack.pop();
                NFA second = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(generateOrNFA(first,second));
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
        acceptNFA(nfaStack.top(),rule.getTokenName());
        //TODO: merge the resulted NFA from Stack into one using or condition
    }
}

void LexicalGenerator::acceptNFA(NFA current, string tokenName) {
    NFAstate endState = current.GetEndState();
    endState.SetAcceptence(true);
    endState.SetTokenName(tokenName);
}

NFA LexicalGenerator::generateBaseNFA(char key) {
    NFA generatedNFA;
    NFAstate generatedStartState;
    NFAstate generatedEndState;
    generatedStartState.SetAddTransitions(key,generatedEndState);
    generatedNFA.SetStartState(generatedStartState);
    generatedNFA.SetEndState(generatedEndState);
    return generatedNFA;
}

NFA LexicalGenerator::generateOrNFA(NFA first, NFA second) {
    NFA generatedNFA;
    NFAstate generatedStartState;
    NFAstate generatedEndState;
    generatedStartState.SetAddTransitions(EPSILON,first.GetStartState());
    generatedStartState.SetAddTransitions(EPSILON,second.GetStartState());
    first.GetEndState().SetAddTransitions(EPSILON,generatedEndState);
    second.GetEndState().SetAddTransitions(EPSILON,generatedEndState);
    generatedNFA.SetStartState(generatedStartState);
    generatedNFA.SetEndState(generatedEndState);
    return generatedNFA;
}

NFA LexicalGenerator::generateAndNFA(NFA first, NFA second) {
    NFA generatedNFA;
    NFAstate generatedStartState;
    NFAstate generatedEndState;
    generatedStartState.SetAddTransitions(EPSILON,first.GetStartState());
    first.GetEndState().SetAddTransitions(EPSILON,second.GetStartState());
    second.GetEndState().SetAddTransitions(EPSILON,generatedEndState);
    generatedNFA.SetStartState(generatedStartState);
    generatedNFA.SetEndState(generatedEndState);
    return generatedNFA;
}

void LexicalGenerator::applyOneOrMore(NFA current){
    current.GetEndState().SetAddTransitions(EPSILON,current.GetStartState());
}

void LexicalGenerator::applyZeroOrMore(NFA current){
    applyOneOrMore(current);
    current.GetStartState().SetAddTransitions(EPSILON,current.GetEndState());
}

LexicalRules &LexicalGenerator::GetLexicalRules() {
    return lexicalRules;
}



