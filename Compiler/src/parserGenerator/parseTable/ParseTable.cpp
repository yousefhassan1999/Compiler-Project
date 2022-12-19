//
// Created by ahmed on 12/17/2022.
//

#include <sstream>
#include <bits/stdc++.h>
#include "ParseTable.h"

#define EPSILON "Epsilon"

void ParseTable::createParseTable() {
    createFirst();
    createFollows();
    printResults();

    unsigned long long nonTerminalSize = nonTerminalIndices.size();
    unsigned long long terminalSize = nonTerminalIndices.size();// modify this to match terminal size
    parseTable = new string *[nonTerminalSize];
    for (int i = 0 ; i < nonTerminalSize; i++){
        parseTable[i] = new string [terminalSize];
    }


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
                        int j = i + 1;
                        while (j != words.size() && addFollow) {
                            addFollow = false;
                            if (words[i + 1][0] == '\'') { // check terminal
                                follows[words[i]].insert(words[i + 1]);
                                break;
                            }
                            //add first except epsilon
                            for (const string &firstElement: first[words[i + 1]]) {
                                if (firstElement == EPSILON) {
                                    addFollow = true;
                                    continue;
                                }
                                follows[words[i]].insert(firstElement);
                            }
                            j++;
                        }
                        if (addFollow && words[i] != rule.GetNonTerminal()) {
                            // add follows
                            for (const string &followElement: follows[rule.GetNonTerminal()]) {
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
    for (auto c: parserRules) {
        container.insert({c.GetNonTerminal(), *c.GetRHS()});
    }
    for (auto c: parserRules) {
        calc_first(c.GetNonTerminal(), *c.GetRHS());
    }
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


void ParseTable::calc_first(const string &k, const list<string> &RHS) {
    if (!first[k].empty()) { return; }
    for (auto str: RHS) {
        if (str[0] == '\'') {
            string t = "'";
            int z = 1;
            while (str[z] != '\'') {
                t += str[z];
                z++;
            }
            t += str[z];
            first[k].insert(t);
        } else if (str == EPSILON) {
            first[k].insert(EPSILON);
        } else {
            vector<string> out = split(str);
            bool cnt = true;
            for (int i = 0; cnt && (i < out.size()); i++) {
                cnt = false;
                list<string> c = container[out[i]];
                calc_first(out[i], c);
                unordered_set<string> s = first[out[i]];
                for (const auto &elem: s) {
                    if (elem == EPSILON) cnt = true;
                    first[k].insert(elem);
                }
            }
        }
    }
}

void ParseTable::printResults() {
    cout << "first:" << endl;
    for (const auto &c: parserRules) {
        cout << c.GetNonTerminal() << "--> ";
        for (const auto &elem: first[c.GetNonTerminal()]) {
            cout << elem << ",";
        }
        cout << endl;
    }
    cout << endl << "follows:" << endl;
    for (const auto &c: parserRules) {
        cout << c.GetNonTerminal() << "--> ";
        for (const auto &elem: follows[c.GetNonTerminal()]) {
            cout << elem << ",";
        }
        cout << endl;
    }
}

string ParseTable::getRule(const string &nonTerminal, const string &terminal) {
    return std::string();
}
