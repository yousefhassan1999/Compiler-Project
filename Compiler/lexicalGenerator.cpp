#include <iostream>
#include <map>
#include <string>
#include <stack>
#include "lexicalGenerator.h"
#include "lexicalRules.h"

using namespace std;

void LexicalGenerator::GenerateNFA() {
    operatorPrecedence.insert(pair<char, int>('*', 3));
    operatorPrecedence.insert(pair<char, int>('+', 3));
    operatorPrecedence.insert(pair<char, int>(' ', 2));
    operatorPrecedence.insert(pair<char, int>('|', 1));

    vector<string> KeyWords = lexicalRules.GetKeyWords();
    vector<string> Punctuations = lexicalRules.GetPunctuations();
    map<string, string> RegularDefinitionsMap = lexicalRules.GetRegularDefinitionsMap();
    map<string, string> RegularExpressionsMap = lexicalRules.GetRegularExpressionsMap();
    RegularDefinitionsMap = postfixNotation(RegularDefinitionsMap);
    RegularExpressionsMap = postfixNotation(RegularExpressionsMap);

    /*map<string, string>::iterator itr;
    cout << "\tKEY\tELEMENT\n";
    for (itr = RegularDefinitionsMap.begin(); itr != RegularDefinitionsMap.end(); ++itr) {
        cout << '\t' << itr->first << '\t' << itr->second
             << '\n';
    }*/
    /*map<string, string>::iterator itr1;
    cout << "\tKEY\tELEMENT\n";
    for (itr1 = RegularExpressionsMap.begin(); itr1 != RegularExpressionsMap.end(); ++itr1) {
        cout << '\t' << itr1->first << '\t' << itr1->second << '\t'
             << '\n';
    }*/

    /*cout << "Punctuations\n";
    for (auto it = Punctuations.begin(); it != Punctuations.end(); ++it)
        cout << *it << "\n";
    cout << "KeyWords\n";
    for (auto it = KeyWords.begin(); it != KeyWords.end(); ++it)
        cout << *it << "\n";*/

    //Keywords branches generated.
//    for (auto it = KeyWords.begin(); it != KeyWords.end(); ++it)
//        GenerateKeyWordBranch(*it);
}

map<string, string> LexicalGenerator::postfixNotation(map<string, string> map1) {
    map<string, string> newMap;
    map<string, string>::iterator itr;
    for (itr = map1.begin(); itr != map1.end(); ++itr) {
        string Value = convertToPostfix(itr->second);
        newMap.insert(pair<string, string>(itr->first, Value));
    }
    return newMap;
}

string LexicalGenerator::convertToPostfix(string basicString) {
    stack<char> Stack;
    string newString;
    for (int i = 0; i < basicString.length(); i++) {
        char Ch = basicString.at(i);
        if (operatorPrecedence.find(Ch) != operatorPrecedence.end()) {
            auto operatorChar = operatorPrecedence.find(Ch);
            while (!Stack.empty() && Stack.top() != '(' &&
                   operatorPrecedence.find(Stack.top())->second >= operatorChar->second) {
                newString += Stack.top();
                Stack.pop();
            }
            Stack.push(Ch);
        } else if (Ch == '(') {
            Stack.push(Ch);
        } else if (Ch == ')') {
            while (!Stack.empty() && Stack.top() != '(') {
                newString += Stack.top();
                Stack.pop();
            }
            Stack.pop();
        } else {
            newString += Ch;
        }
    }
    while (!Stack.empty()) {
        newString += Stack.top();
        Stack.pop();
    }
    return newString;
}

void LexicalGenerator::GenerateKeyWordBranch(string keyWord) {
    NFAstate curruntState = startState;
    for (int i = 0; i < keyWord.length(); i++) {
        char ch = keyWord.at(i);
        string mapKey;
        mapKey += ch;
        NFAstate newState;
        /*State newState;
        Edge e;
        e.setNextState(&newState);
        e.setTrx(ch);
        curruntState.SetAddToStateEdges(e);*/
        curruntState = newState;
    }
}


LexicalRules &LexicalGenerator::GetLexicalRules() {
    return lexicalRules;
}



