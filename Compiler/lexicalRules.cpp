#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <bits/stdc++.h>
#include "lexicalRules.h"

using namespace std;

void LexicalRules::ReadFileContaint (string Path) {
    string myText;
    ifstream MyReadFile(Path);
    while (getline (MyReadFile, myText)) {
        bool check = checkRegularDefinition(myText) || checkPunctuations(myText) || checkKeyWords(myText)? true : false;
        if(!check)
            RegularExpressions.push_back(myText);
    }
    MyReadFile.close();
}

bool LexicalRules::checkRegularDefinition(string LR){
    regex str_expr1 ("([a-zA-Z][a-zA-Z0-9]* = .*)");
    if (regex_match (LR,str_expr1)){
        RegularDefinitions.push_back(LR);
        return true;
    }
    return false;
}
bool LexicalRules::checkPunctuations(string LR){
    regex str_expr2 ("(\\[.*\\])");
    if (regex_match (LR,str_expr2)){
        //Punctuations
        LR = LR.substr(1, LR.size() - 2);
        stringstream ss(LR);
        string word;
        while (ss >> word) {
            if (word[0] == '\\')
                word = word.substr(1, word.size() - 1);
            Punctuations.push_back(word);
        }
        return true;
    }
    return false;
}
bool LexicalRules::checkKeyWords(string LR){
    regex str_expr3 ("(\\{.*\\})");
    if (regex_match (LR,str_expr3)){
        LR = LR.substr(1, LR.size() - 2);
        stringstream ss(LR);
        string word;
        while (ss >> word) {
            KeyWords.push_back(word);
        }
        return true;
    }
    return false;
}
vector<string>& LexicalRules::GetKeyWords(){
    return KeyWords;
}
vector<string>& LexicalRules::GetPunctuations(){
    return Punctuations;
}
vector<string>& LexicalRules::GetRegularDefinitions(){
    return RegularDefinitions;
}
vector<string>& LexicalRules::GetRegularExpressions(){
    return RegularExpressions;
}
