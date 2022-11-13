#include <fstream>
#include <string>
#include <regex>
#include <map>
#include "lexicalRules.h"

using namespace std;

void LexicalRules::ReadFileContaint (string Path) {
    string myText;
    ifstream MyReadFile(Path);
    while (getline (MyReadFile, myText)) {
        bool check = checkRegularDefinition(myText) || checkPunctuations(myText) || checkKeyWords(myText)? true : false;
        if(!check){
            myText.erase(std::remove_if(myText.begin(), myText.end(), ::isspace),myText.end());
            RegularExpressions.push_back(myText);
        }
    }
    MyReadFile.close();
    UpdateRegularExpressions();
    /*map<string, string>::iterator itr;
    cout << "\tKEY\tELEMENT\n";
    for (itr = RegularDefinitionsMap.begin(); itr != RegularDefinitionsMap.end(); ++itr) {
        cout << '\t' << itr->first << '\t' << itr->second
             << '\n';
    }
    map<string, string>::iterator itr1;
    cout << "\tKEY\tELEMENT\n";
    for (itr1 = RegularExpressionsMap.begin(); itr1 != RegularExpressionsMap.end(); ++itr1) {
        cout << '\t' << itr1->first << '\t' << itr1->second
             << '\n';
    }*/
}

void LexicalRules::UpdateRegularExpressions() {
    for (auto it = RegularExpressions.begin(); it != RegularExpressions.end(); ++it){
        string s = *it;
        int i=0;
        for(i=0;i<s.size();i++){
            if(s.at(i)==':')
                break;
        }
        string Key = s.substr(0, i);
        string Value = s.substr(i+1, s.size());
        Value = CheckMapSubstring(Value);
        RegularExpressionsMap.insert(pair<string, string>(Key, Value));
    }
}

bool LexicalRules::checkRegularDefinition(string LR){
    regex str_expr1 ("([a-zA-Z][a-zA-Z0-9]* = .*)");
    if (regex_match (LR,str_expr1)){
        LR.erase(std::remove_if(LR.begin(), LR.end(), ::isspace),LR.end());
        string newLR = updateMinus(LR);

        int pos = newLR.find("=");
        string Key = newLR.substr(0, pos);
        string Value = newLR.substr(pos+1, newLR.size() - 1);
        Value = CheckMapSubstring(Value);
        RegularDefinitionsMap.insert(pair<string, string>(Key, Value));
        //RegularDefinitions.push_back(newLR);
        return true;
    }
    return false;
}

string LexicalRules::updateMinus(string basicString) {
    while(basicString.find("-") < basicString.size() && basicString.find("-") > 0){
        int pos = basicString.find("-");
        string S1 = basicString.substr(0, pos-1);
        string S2 = basicString.substr(pos+2, basicString.size());
        char prevChar = basicString.at(pos-1);
        char afterChar = basicString.at(pos+1) ;
        string newS = "(";
        while(prevChar<=afterChar){
            newS = newS + prevChar + "|";
            prevChar++;
        }
        newS = newS.substr(0, newS.size()-1);
        newS += ")";
        basicString = S1 + newS + S2;
    }
    return basicString;
}

string LexicalRules::CheckMapSubstring(string basicString) {
    map<string, string>::iterator itr;
    string old;
    do{
        old = basicString;
        for (itr = RegularDefinitionsMap.begin(); itr != RegularDefinitionsMap.end(); ++itr) {
            int pos = isSubstring(itr->first, basicString);
            if(pos != -1){
                string S1 = basicString.substr(0, pos);
                string S2 = basicString.substr(pos+itr->first.size(), basicString.size());
                basicString = S1 + "(" + itr->second + ")"+ S2 ;
            }
        }
    }
    while(old != basicString);
    return basicString;
}

int LexicalRules::isSubstring(string basicString, string basicString1) {
    if (basicString1.find(basicString) != string::npos)
        return basicString1.find(basicString);
    return -1;
}

bool LexicalRules::checkPunctuations(string LR){
    regex str_expr2 ("(\\[.*\\])");
    if (regex_match (LR,str_expr2)){
        //Punctuations
        LR = LR.substr(1, LR.size() - 2);
        stringstream ss(LR);
        string word;
        while (ss >> word) {
            /*if (word[0] == '\\')
                word = word.substr(1, word.size() - 1);*/
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
map<string, string>& LexicalRules::GetRegularDefinitionsMap(){
    return RegularDefinitionsMap;
}
map<string, string>& LexicalRules::GetRegularExpressionsMap(){
    return RegularExpressionsMap;
}
vector<string>& LexicalRules::GetRegularExpressions(){
    return RegularExpressions;
}

