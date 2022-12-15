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
    myProduction = myLine ;
    while (getline(MyReadFile, myLine)) {
        if(myLine.at(0) != '#'){
            myProduction += " " + myLine;
        }
        else{
            int pos = myProduction.find('=');
            vector<string> RHS;
            RHS.push_back(deleteLeadingAndTrailingSpace(myProduction.substr(pos + 1, myProduction.size() - 1)));
            CFGRulesVec.insert(pair<string, vector<string>>(deleteLeadingAndTrailingSpace(myProduction.substr(1, pos-1)), RHS));

            myProduction = myLine;
        }
    }
    int pos = myProduction.find('=');
    vector<string> RHS;
    RHS.push_back(deleteLeadingAndTrailingSpace(myProduction.substr(pos + 1, myProduction.size() - 1)));
    CFGRulesVec.insert(pair<string, vector<string>>(deleteLeadingAndTrailingSpace(myProduction.substr(1, pos-1)), RHS));
    MyReadFile.close();
}

map<string, vector<string>>* CFGRules::GetCFGRulesVec(){
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




