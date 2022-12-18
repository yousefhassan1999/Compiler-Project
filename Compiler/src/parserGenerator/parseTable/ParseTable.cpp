//
// Created by ahmed on 12/17/2022.
//

#include <sstream>
#include <bits/stdc++.h>
#include "ParseTable.h"

#define EPSILON "Epsilon"

using namespace std;

void ParseTable::createParseTable() {
    createFirst();
    createFollows();

}

string ParseTable::getRule(string nonTerminal, char terminal) {
    return {};
}


void ParseTable::createFollows() {
    follows[startSymbol].insert("'$'");
    int attempts = 10;
    while (attempts--) {
        for (auto rule: parserRules) {
            for (const auto &nextRule: *rule.GetRHS()) {
                auto words = split(nextRule);
                for (int i = 0; i < words.size(); i++) {
                    if (words[i][0] != '\'') { // check non-terminal
                        bool addFollow = true;
                        int j = i+1;
                        while (j != words.size() && addFollow) {
                            addFollow = false;
                            if (words[i + 1][0] == '\'') { // check terminal
                                follows[words[i]].insert(words[i + 1]);
                                continue;
                            }
                            //add first except epsilon
                            for (const string &firstElement: first[words[i + 1]]) {
                                if (firstElement == EPSILON) {
                                    addFollow = true;
                                    continue;
                                }
                                follows[words[i]].insert(firstElement);
                            }
                        }
                        if (addFollow && words[i] != rule.GetNonTerminal()){
                            // add follows
                            for (const string& followElement: follows[rule.GetNonTerminal()]) {
                                follows[words[i]].insert(followElement);
                            }
                        }
                    }
                }
            }
        }
    }
}

void ParseTable::createFirst() {
    for(auto it = parserRules.begin(); it != parserRules.end();++it){
        CFGContainer c = *it;
        container.insert({c.GetNonTerminal(),*c.GetRHS()});
    }
    for(auto it = parserRules.begin(); it != parserRules.end();++it){
        CFGContainer c = *it;
        calc_first(c.GetNonTerminal(),*c.GetRHS());
    }
   /* for(auto it = parserRules.begin(); it != parserRules.end();++it){
        CFGContainer c = *it;
        cout<<c.GetNonTerminal()<<"--> ";
        //calc_first(c.GetNonTerminal(),*c.GetRHS());
        for (const auto& elem: first[c.GetNonTerminal()]) {
            cout<<elem<<",";
        }
        cout<<endl;
    }*/
}

vector<string> ParseTable::split(const string &str) {
    vector<string> res;
    istringstream stream(str);
    string word;
    while (stream >> word) {
        res.push_back(word);
    }
    return res;
}


void ParseTable::calc_first(string k, list<string> RHS) {
    if(!first[k].empty()){return;}

    for(auto it = RHS.begin(); it != RHS.end();++it){
        string str = *it;
        if(str[0]=='\''){
            string t = "'";
            int z = 1;
            while(str[z]!='\''){
                t=t+str[z];
                z++;
            }
            t=t+str[z];
            first[k].insert(t);
        }else if(str == EPSILON){
            first[k].insert(EPSILON);
        }else{
            vector<string> out= split(str);
            //tokenize(str, ' ', out);
            bool cnt = true;
            for(int i = 0 ; cnt && (i < out.size() ) ; i++){
                cnt = false;
                list<string> c = container[out[i]];
                calc_first(out[i],c);
                unordered_set<string> s = first[out[i]];
                for (const auto& elem: s) {
                    if(elem == EPSILON) cnt = true;
                    first[k].insert(elem);
                }
            }

        }
    }
}
