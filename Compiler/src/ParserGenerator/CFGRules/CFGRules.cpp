#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <iostream>
#include "CFGRules.h"

using namespace std;

void CFGRules::readFileContent(const string &Path) {
    string myLine;
    string myProduction;

    ifstream MyReadFile(Path);
    getline(MyReadFile, myLine);
    myProduction = myLine;
    while (getline(MyReadFile, myLine)) {
        if (myLine.at(0) != '#') {
            myProduction += " " + myLine;
        } else {
            int pos = myProduction.find('=');
            string RHSString = deleteLeadingAndTrailingSpace(myProduction.substr(1, pos - 2));
            list<string> RHS = SplitOr(RHSString, deleteLeadingAndTrailingSpace(
                    myProduction.substr(pos + 1, myProduction.size() - 1)));
            CFGRulesVec.insert(pair<string, list<string>>(RHSString, RHS));

            myProduction = myLine;
        }
    }
    int pos = myProduction.find('=');
    string RHSString = deleteLeadingAndTrailingSpace(myProduction.substr(1, pos - 1));
    list<string> RHS = SplitOr(RHSString,
                               deleteLeadingAndTrailingSpace(myProduction.substr(pos + 1, myProduction.size() - 1)));
    CFGRulesVec.insert(pair<string, list<string>>(RHSString, RHS));
    MyReadFile.close();

}

list<string> CFGRules::SplitOr(string RHSBasicString, string basicString) {
    list<string> RHSVec;
    while (basicString.find(" | ") != string::npos) {
        int pos = basicString.find(" | ");
        string S1 = basicString.substr(0, pos);
        basicString = basicString.substr(pos + 3, basicString.size());
        int firstPosCheck = S1.find(RHSBasicString);
        if (firstPosCheck == 0) {
            RHSVec.push_front(S1);
        } else {
            RHSVec.push_back(S1);
        }

    }
    int firstPosCheck = basicString.find(RHSBasicString);
    if (firstPosCheck == 0) {
        RHSVec.push_front(basicString);
    } else {
        RHSVec.push_back(basicString);
    }
    return RHSVec;
}

void CFGRules::RemoveLeftRec() {
    map<string, list<string>>::iterator itr;
    for (itr = CFGRulesVec.begin(); itr != CFGRulesVec.end(); ++itr) {
        string Key = itr->first;
        list<string> newProdVecString;
        // get the part that case left rec
        for (auto i = itr->second.begin(); i != itr->second.end(); ++i) {
            if ((*i).find(Key) != 0) {
                break;
            }
            newProdVecString.push_back(CFGRulesVec.at(Key).front());
        }
        if (newProdVecString.size() > 0) {
            // remove the part that case left rec from map
            for (int i = 0; i < newProdVecString.size(); i++) {
                CFGRulesVec.at(Key).pop_front();
            }
            string newKey = Key + "_" + to_string(incremental++);

            for (auto i = itr->second.begin(); i != itr->second.end(); ++i) {
                *i += " " + newKey;
            }

            for (auto i = newProdVecString.begin(); i != newProdVecString.end(); ++i) {
                *i += " " + newKey;
                *i = (*i).substr(Key.size()+1, (*i).size());
            }
            newProdVecString.push_back(" ");
            CFGRulesVec.insert(pair<string, list<string>>(newKey, newProdVecString));
        }
    }
}

void CFGRules::RemoveIndirectLeftRec() {
    map<string, int> ProductionsOrder;
    map<string, list<string>>::iterator itr;
    int orderCount = 0;

    for (itr = CFGRulesVec.begin(); itr != CFGRulesVec.end(); ++itr) {
        ProductionsOrder.insert(pair<string, int>(itr->first, orderCount++));
    }

}

map<string, list<string>> *CFGRules::GetCFGRulesVec() {
    return &CFGRulesVec;
}

// Repeated functions
string CFGRules::deleteLeadingAndTrailingSpace(string basicString) {
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




