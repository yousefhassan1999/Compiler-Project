#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <iostream>
#include "lexicalRules.h"

using namespace std;

void LexicalRules::readFileContent(const string &Path) {
    operatorPrecedence.insert(pair<char, int>('*', 3));
    operatorPrecedence.insert(pair<char, int>('+', 3));
    operatorPrecedence.insert(pair<char, int>(' ', 2));
    operatorPrecedence.insert(pair<char, int>('|', 1));

    string myText;
    ifstream MyReadFile(Path);
    while (getline(MyReadFile, myText)) {
        bool check = checkRegularDefinition(myText) || checkPunctuations(myText) || checkKeyWords(myText);
        if (!check) {
            RegularExpressions.push_back(myText);
        }
    }
    MyReadFile.close();
    updateRegularExpressions();
}

bool LexicalRules::checkPunctuations(string LR) {
    regex str_expr2("(\\[.*\\])");
    if (regex_match(LR, str_expr2)) {
        LR = LR.substr(1, LR.size() - 2);
        stringstream ss(LR);
        string word;
        while (ss >> word) {
            string value(word);
            value = specialConvertToPostfix(value);
            NFAPostfix newNFAPostfix;
            newNFAPostfix.setTokenName("Punctuations");
            newNFAPostfix.setPostFix(value);
            rules.push_back(newNFAPostfix);
        }
        return true;
    }
    return false;
}

bool LexicalRules::checkKeyWords(string LR) {
    regex str_expr3("(\\{.*\\})");
    if (regex_match(LR, str_expr3)) {
        LR = LR.substr(1, LR.size() - 2);
        stringstream ss(LR);
        string word;
        while (ss >> word) {
            string value(word);
            value = specialConvertToPostfix(value);
            NFAPostfix newNFAPostfix;
            newNFAPostfix.setTokenName("Keyword");
            newNFAPostfix.setPostFix(value);
            rules.push_back(newNFAPostfix);
        }
        return true;
    }
    return false;
}

bool LexicalRules::checkRegularDefinition(string LR) {
    regex str_expr1("([a-zA-Z][a-zA-Z0-9]* = .*)");    //.*[^(\:( )*)|(\\( )*)]( )*=.*
    if (regex_match(LR, str_expr1)) {
        LR.erase(std::remove_if(LR.begin(), LR.end(), ::isspace), LR.end());
        string newLR = updateMinus(LR);

        int pos = newLR.find('=');
        string Key = newLR.substr(0, pos);
        string Value = newLR.substr(pos + 1, newLR.size() - 1);
        Value = checkMapSubstring(Value);
        RegularDefinitionsMap.insert(pair<string, string>(Key, Value));

        string ValuePostfix = convertToPostfix(Value);
        return true;
    }
    return false;
}

void LexicalRules::updateRegularExpressions() {
    for (auto s: RegularExpressions) {
        int i;
        for (i = 0; i < s.length(); i++) {
            if (s.at(i) == ':')
                break;
        }
        string Key = s.substr(0, i);
        string Value = s.substr(i + 1, s.size());
        Value = checkMapSubstring(Value);
        Value = deleteLeadingAndTrailingSpace(Value);
        Value = addSeparator(Value);
        Value = convertToPostfix(Value);

        NFAPostfix newNFAPostfix;
        newNFAPostfix.setTokenName(Key);
        newNFAPostfix.setPostFix(Value);
        rules.push_back(newNFAPostfix);
    }
}

string LexicalRules::updateMinus(string basicString) {
    while (basicString.find('-') != string::npos) {
        int pos = basicString.find('-');
        string S1 = basicString.substr(0, pos - 1);
        string S2 = basicString.substr(pos + 2, basicString.size());
        char prevChar = basicString.at(pos - 1);
        char afterChar = basicString.at(pos + 1);
        string newS = "(";
        while (prevChar <= afterChar) {
            newS = newS + prevChar + "|";
            prevChar++;
        }
        newS = newS.substr(0, newS.size() - 1);
        newS += ")";
        basicString = S1 + newS + S2;
    }
    return basicString;
}

string LexicalRules::checkMapSubstring(string basicString) {
    map<string, string>::iterator itr;
    string old;
    do {
        old = basicString;
        for (itr = RegularDefinitionsMap.begin(); itr != RegularDefinitionsMap.end(); ++itr) {
            int pos = isSubstring(itr->first, basicString);
            if (pos != -1) {
                string S1 = basicString.substr(0, pos);
                string S2 = basicString.substr(pos + itr->first.size(), basicString.size());
                basicString = S1 + "(" + itr->second + ")" + S2;
            }
        }
    } while (old != basicString);
    return basicString;
}

int LexicalRules::isSubstring(const string &basicString, const string &basicString1) {
    if (basicString1.find(basicString) != string::npos)
        return basicString1.find(basicString);
    return -1;
}

string LexicalRules::addSeparator(string basicString) {
    string newBasicString;
    for (int i = 0; i < basicString.length(); i++) {
        if (basicString.at(i) == ' ' && (basicString.at(i - 1) == '|' || basicString.at(i + 1) == '|')) {
            continue;
        } else if (basicString.at(i) == ' ' && (basicString.at(i - 1) == '(' && basicString.at(i + 1) != ')')) {
            continue;
        } else if ((basicString.at(i) != '(' && basicString.at(i) != ')' && basicString.at(i) != '|' &&
                    basicString.at(i) != ' ') &&
                   (i + 1 < basicString.length()) &&
                   (basicString.at(i + 1) != '|' && basicString.at(i + 1) != ')' && basicString.at(i + 1) != ' ')) {
            newBasicString = newBasicString + basicString.at(i) + " ";
        } else {
            newBasicString += basicString.at(i);
        }
    }
    return newBasicString;
}

string LexicalRules::deleteLeadingAndTrailingSpace(string basicString) {
    int i;
    int j;
    for (i = 0; i < basicString.length(); i++) {
        if (basicString.at(i) != ' ') {
            break;
        }
    }
    for (j = basicString.length() - 1; j > -1; j--) {
        if (basicString.at(j) != ' ') {
            break;
        }
    }
    return basicString.substr(i, j + 1);
}

string LexicalRules::convertToPostfix(string basicString) {
    stack<char> Stack;
    string newString;
    for (char Ch: basicString) {
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

string LexicalRules::specialConvertToPostfix(string basicString) {
    string newValue;
    if (basicString.length() < 2)
        return basicString;
    newValue = newValue + basicString.at(0) + basicString.at(1) + " ";
    int i=2;
    while(i < basicString.length()){
        newValue = newValue + basicString.at(i) + " ";
        i++;
    }
    return newValue;
}

vector<NFAPostfix> &LexicalRules::getRules() {
    return rules;
}




