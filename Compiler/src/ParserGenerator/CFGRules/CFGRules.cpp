#include <fstream>
#include <string>
#include <regex>
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
            string LHSString = deleteLeadingAndTrailingSpace(myProduction.substr(1, pos - 2));
            list<string> RHS = SplitOr(LHSString, deleteLeadingAndTrailingSpace(
                    myProduction.substr(pos + 1, myProduction.size() - 1)));
            CFGContainer container;
            container.SetNonTerminal(LHSString);
            container.SetRHS(RHS);
            CFGRulesVec.push_back(container);

            myProduction = myLine;
        }
    }
    int pos = myProduction.find('=');
    string LHSString = deleteLeadingAndTrailingSpace(myProduction.substr(1, pos - 2));
    list<string> RHS = SplitOr(LHSString,
                               deleteLeadingAndTrailingSpace(myProduction.substr(pos + 1, myProduction.size() - 1)));
    CFGContainer container;
    container.SetNonTerminal(LHSString);
    container.SetRHS(RHS);
    CFGRulesVec.push_back(container);
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

bool CFGRules::LeftRecUpdate(string Key, list<string> *RHSVec, CFGContainer *newContainer) {
    int incremental = 0;
    list<string> newProdVecString;
    // get the part that case left rec
    for (auto i = RHSVec->begin(); i != RHSVec->end(); ++i) {
        if (i->find(Key) != 0) {
            break;
        }
        newProdVecString.push_back(*i);
    }
    if (newProdVecString.size() > 0) {
        // remove the part that case left rec from map
        for (int i = 0; i < newProdVecString.size(); i++) {
            RHSVec->pop_front();
        }
        string newKey = Key + "_" + to_string(incremental++);

        for (auto i = RHSVec->begin(); i != RHSVec->end(); ++i) {
            *i += " " + newKey;
        }

        for (auto i = newProdVecString.begin(); i != newProdVecString.end(); ++i) {
            *i += " " + newKey;
            *i = (*i).substr(Key.size() + 1, (*i).size());
        }

        newProdVecString.push_back(" ");
        newContainer->SetNonTerminal(newKey);
        newContainer->SetRHS(newProdVecString);
        return true;
    }
    return false;
}

void CFGRules::RemoveLeftRec() {
    list<CFGContainer>::iterator itr1;
    list<CFGContainer>::iterator itr2;
    for (itr1 = CFGRulesVec.begin(); itr1 != CFGRulesVec.end(); ++itr1) {
        string LHSNonTerminalRoot = itr1->GetNonTerminal();
        list<string> RHSVecRoot = *itr1->GetRHS();
        for (itr2 = CFGRulesVec.begin(); itr2 != itr1; ++itr2) {
            string LHSNonTerminal = itr2->GetNonTerminal();
            list<string> RHSVec = *itr2->GetRHS();
            for (auto i = RHSVecRoot.begin(); i != RHSVecRoot.end(); ++i) {
                if (i->find(LHSNonTerminal) == 0) {
                    string cut = deleteLeadingAndTrailingSpace(i->substr(LHSNonTerminal.size(), i->size()));
                    RHSVecRoot.erase(i);
                    for (auto j = RHSVec.begin(); j != RHSVec.end(); ++j) {
                        string toPushInList = deleteLeadingAndTrailingSpace(*j + " " + cut);
                        int firstPosCheck = toPushInList.find(LHSNonTerminalRoot);
                        if (firstPosCheck == 0) {
                            RHSVecRoot.push_front(toPushInList);
                        } else {
                            RHSVecRoot.push_back(toPushInList);
                        }
                    }
                }
            }
        }
        CFGContainer container;
        bool checkNewState = LeftRecUpdate(LHSNonTerminalRoot, &RHSVecRoot, &container);
        if (checkNewState) {
            itr1->SetRHS(RHSVecRoot);
            itr1++;
            CFGRulesVec.insert(itr1--, container);
        }
    }
}


std::list<CFGContainer> *CFGRules::GetCFGRulesVec() {
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




