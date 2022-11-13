#include <iostream>
#include <unordered_map>
#include <string>
#include "lexicalGenerator.h"
#include "lexicalRules.h"

using namespace std;

void LexicalGenerator::GenerateNFA(){
    vector<string> KeyWords = lexicalRules.GetKeyWords();
    vector<string> Punctuations = lexicalRules.GetPunctuations();
    vector<string> RegularDefinitions = lexicalRules.GetRegularDefinitions();
    vector<string> RegularExpressions = lexicalRules.GetRegularExpressions();
    //Keywords branches generated.
    for (auto it = KeyWords.begin(); it != KeyWords.end(); ++it)
        GenerateKeyWordBranch(*it);
}

void LexicalGenerator::GenerateKeyWordBranch(string keyWord){
    State s;
    State curruntState = s;
    Paths.push_back(s);
    for (int i = 0; i < keyWord.length(); i++) {
        char ch = keyWord.at(i);
        State newState;
        Edge e;
        e.setNextState(&newState);
        e.setTrx(ch);
        curruntState.SetAddToStateEdges(e);
        curruntState = s;
    }
}


LexicalRules& LexicalGenerator::GetLexicalRules(){
    return lexicalRules;
}


