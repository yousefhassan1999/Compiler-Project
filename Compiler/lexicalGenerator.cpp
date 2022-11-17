#include <iostream>
#include <string>
#include <stack>
#include "lexicalGenerator.h"
#include "lexicalRules.h"

using namespace std;

void LexicalGenerator::GenerateNFA() {
    for (auto &it: lexicalRules.GetRules()) {
        cout << it.getTokenName() << ' ' << it.getPostFix() << "\n";
    }
}

LexicalRules &LexicalGenerator::GetLexicalRules() {
    return lexicalRules;
}



