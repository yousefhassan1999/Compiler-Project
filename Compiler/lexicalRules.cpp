#include <iostream>
#include <fstream>
#include <string>
#include "lexicalRules.h"
#include <regex>

using namespace std;

void LexicalRules::ReadFileContaint (string Path) {
    string myText;
    ifstream MyReadFile(Path);
    while (getline (MyReadFile, myText)) {
        cout << myText<<"\n";
        checkRegularDefinition(myText);
        checkPunctuations(myText);
        checkKeyWords(myText);
    }
    MyReadFile.close();
}

bool LexicalRules::checkRegularDefinition(string LR){
    regex str_expr1 ("([a-zA-Z][a-zA-Z0-9]* = .*)");
    if (regex_match (LR,str_expr1)){
        cout << "string:object => RegularDefinition\n";
    }
    return false;
}
bool LexicalRules::checkPunctuations(std::string LR){
    regex str_expr2 ("(\\[.*\\])");
    if (regex_match (LR,str_expr2)){
        cout << "string:object => Punctuations\n";
    }
    return false;
}
bool LexicalRules::checkKeyWords(string LR){
    regex str_expr3 ("(\\{.*\\})");
    if (regex_match (LR,str_expr3)){
        cout << "string:object => KeyWords\n";
        return true;
    }
    return false;
}
