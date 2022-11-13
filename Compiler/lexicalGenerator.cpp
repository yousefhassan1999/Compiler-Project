#include <iostream>
#include <map>
#include <string>
#include "lexicalGenerator.h"
#include "lexicalRules.h"

using namespace std;

void LexicalGenerator::GenerateNFA(){
    vector<string> KeyWords = lexicalRules.GetKeyWords();
    vector<string> Punctuations = lexicalRules.GetPunctuations();
    map<string, string> RegularExpressionsMap = lexicalRules.GetRegularExpressionsMap();

    //vector<string> RegularDefinitions = lexicalRules.GetRegularDefinitions();
    //vector<string> RegularExpressions = lexicalRules.GetRegularExpressions();
    /*cout << "RegularDefinitions\n";
    cout << "Punctuations\n";
    for (auto it = Punctuations.begin(); it != Punctuations.end(); ++it)
        cout << *it << "\n";
    cout << "KeyWords\n";
    for (auto it = KeyWords.begin(); it != KeyWords.end(); ++it)
        cout << *it << "\n";
    cout << "RegularExpressions\n";*/
    //Keywords branches generated.
//    for (auto it = KeyWords.begin(); it != KeyWords.end(); ++it)
//        GenerateKeyWordBranch(*it);
}

void LexicalGenerator::GenerateKeyWordBranch(string keyWord){
    State curruntState = startState;
    for (int i = 0; i < keyWord.length(); i++) {
        char ch = keyWord.at(i);
        string mapKey;
        mapKey +=ch;
        State newState;
        /*State newState;
        Edge e;
        e.setNextState(&newState);
        e.setTrx(ch);
        curruntState.SetAddToStateEdges(e);*/
        curruntState = newState;
    }
}


LexicalRules& LexicalGenerator::GetLexicalRules(){
    return lexicalRules;
}


