#include <fstream>
#include <string>
#include <algorithm>
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
            list<string> RHS = Split(LHSString, deleteLeadingAndTrailingSpace(
                    myProduction.substr(pos + 1, myProduction.size() - 1)), " | ");
            CFGContainer container;
            container.SetNonTerminal(LHSString);
            container.SetRHS(RHS);
            CFGRulesVec.push_back(container);

            myProduction = myLine;
        }
    }
    int pos = myProduction.find('=');
    string LHSString = deleteLeadingAndTrailingSpace(myProduction.substr(1, pos - 2));
    list<string> RHS = Split(LHSString,
                             deleteLeadingAndTrailingSpace(myProduction.substr(pos + 1, myProduction.size() - 1)),
                             " | ");
    CFGContainer container;
    container.SetNonTerminal(LHSString);
    container.SetRHS(RHS);
    CFGRulesVec.push_back(container);
    MyReadFile.close();

}

list<string> CFGRules::Split(string RHSBasicString, string basicString, string splitPattern) {
    list<string> RHSVec;
    while (basicString.find(splitPattern) != string::npos) {
        int pos = basicString.find(splitPattern);
        string S1 = basicString.substr(0, pos);
        basicString =
                RHSBasicString != "" ? basicString.substr(pos + 3, basicString.size()) : basicString.substr(pos + 1,
                                                                                                            basicString.size());
        int firstPosCheck = RHSBasicString != "" ? S1.find(RHSBasicString) : 1;
        if (firstPosCheck == 0) {
            RHSVec.push_front(S1);
        } else {
            RHSVec.push_back(S1);
        }
    }
    int firstPosCheck = RHSBasicString != "" ? basicString.find(RHSBasicString) : 1;
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

        newProdVecString.push_back("Epsilon");
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

void CFGRules::ApplyLeftRefactor() {
    list<CFGContainer>::iterator itr1;
    for (itr1 = CFGRulesVec.begin(); itr1 != CFGRulesVec.end(); ++itr1) {
        int StateCounter = 0;
        string key = itr1->GetNonTerminal();
        itr1->GetRHS()->sort();
        list<list<string>> splitRHSVec;
        for (auto i = (*itr1).GetRHS()->begin(); i != (*itr1).GetRHS()->end(); ++i) {
            splitRHSVec.push_back(Split("", *i, " "));
        }
        list<list<string>> notFactoring;
        int check = splitRHSVec.size();
        while (splitRHSVec.size() > 0) {
            list<list<string>> Factoring;
            list<string> splitRHSVecFront = splitRHSVec.front();
            splitRHSVec.pop_front();
            check--;
            list<list<string>> splitRHSVecCopy(splitRHSVec.begin(), splitRHSVec.end());
            size_t max_num_seq = 0;
            int num_strings = 0;
            for (auto i = splitRHSVecFront.begin(); i != splitRHSVecFront.end(); ++i) {
                int num_seq = 0;
                auto j = splitRHSVecCopy.begin();
                for (j = splitRHSVecCopy.begin(); j != splitRHSVecCopy.end(); ++j) {
                    if ((*j).front() == (*i)) {
                        num_seq++;
                        (*j).pop_front();
                    } else {
                        break;
                    }
                }
                splitRHSVecCopy.erase(j,splitRHSVecCopy.end());
                if (max_num_seq == 0 && num_seq > 0) {
                    max_num_seq = num_seq;
                    num_strings++;
                } else if (max_num_seq == num_seq && num_seq !=0) {
                    num_strings++;
                } else {
                    break;
                }
            }
            if (max_num_seq == 0) {
                notFactoring.push_back(splitRHSVecFront);
            } else {
                auto end = std::next(splitRHSVec.begin(), std::min(max_num_seq, splitRHSVec.size()));
                Factoring.push_front(splitRHSVecFront);

                for (auto t = splitRHSVec.begin(); t != end; ++t){
                    Factoring.push_back((*t));
                }
                splitRHSVec.erase(splitRHSVec.begin(),end);
                list<string> commonFactor;
                string newCommonFactorKey = key + "_" + to_string(StateCounter++);
                for (auto t = Factoring.begin(); t != Factoring.end(); ++t) {
                    for (int i = 0; i < num_strings; i++) {
                        if (commonFactor.size() < num_strings) {
                            commonFactor.push_back(t->front());
                        }
                        t->pop_front();
                    }
                }
                commonFactor.push_back(newCommonFactorKey);
                notFactoring.push_back(commonFactor);

                CFGContainer container;
                container.SetNonTerminal(newCommonFactorKey);
                list<string> NewProductionRHS;
                for (auto t = Factoring.begin(); t != Factoring.end(); ++t) {
                    NewProductionRHS.push_back(ConvertListToString(*t));
                }
                container.SetRHS(NewProductionRHS);
                itr1++;
                CFGRulesVec.insert(itr1--, container);
            }
        }
        list<string> EditProductionRHS;
        for (auto t = notFactoring.begin(); t != notFactoring.end(); ++t) {
            EditProductionRHS.push_back(ConvertListToString(*t));
        }
        itr1->SetRHS(EditProductionRHS);
    }
}

string CFGRules::ConvertListToString(list<string> list) {
    if(list.size() == 0){
        return "Epsilon";
    }
    string concat = "";
    for(auto t = list.begin(); t != list.end(); ++t){
        concat += *t + " ";
    }
    return deleteLeadingAndTrailingSpace(concat);
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