//
// Created by ahmed on 12/17/2022.
//

#include <sstream>
#include <bits/stdc++.h>
#include "ParseTable.h"

void ParseTable::createParseTable() {
    createFirst();
    createFollows();
    unsigned long long nonTerminalSize = nonTerminalIndices.size();
    parseTable = new string *[nonTerminalSize];
    for (int i = 0; i < nonTerminalSize; i++) {
        parseTable[i] = new string[terminalIndices.size()];
    }
    for (const auto &firstElement: first) {
        string nonTerminal = firstElement.first;
        string followContent = SYNC;
        for (auto firstElementContent: firstElement.second) {
            if (firstElementContent.GetTerminal() == EPSILON) {
                followContent = EPSILON;
                continue;
            }
            parseTable[nonTerminalIndices[nonTerminal]][terminalIndices[firstElementContent.GetTerminal()]] = firstElementContent.GetRule();
        }
        for (const auto &followElement: follows[nonTerminal]) {
            int nonTerminalIndex = nonTerminalIndices[nonTerminal], terminalIndex = terminalIndices[followElement];
            if (parseTable[nonTerminalIndex][terminalIndex].empty()) {
                parseTable[nonTerminalIndex][terminalIndex] = followContent;
            } else if (followContent == EPSILON) {
                cout << "ambiguous grammar" << endl;
            }
        }
    }
    printResults();
}

void ParseTable::createFollows() {
    follows[startSymbol].insert(END_SYMBOL);
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
                            for (FirstObject firstElement: first[words[i + 1]]) {
                                if (firstElement.GetTerminal() == EPSILON) {
                                    addFollow = true;
                                    continue;
                                }
                                follows[words[i]].insert(firstElement.GetTerminal());
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
            FirstObject o(t, str);
            first[k].push_back(o);
        } else if (str == EPSILON) {
            FirstObject o(EPSILON, EPSILON);
            first[k].push_back(o);
        } else {
            vector<string> out = split(str);
            bool cnt = true;
            for (int i = 0; cnt && (i < out.size()); i++) {
                cnt = false;
                list<string> c = container[out[i]];
                calc_first(out[i], c);
                vector<FirstObject> v = first[out[i]];
                for (auto &elem: v) {
                    if (elem.GetTerminal() == EPSILON) cnt = true;
                    elem.SetRule(str);
                    first[k].push_back(elem);
                }
            }
        }
    }
}

void ParseTable::printResults() {
    cout << "first:" << endl;
    for (const auto &c: parserRules) {
        cout << c.GetNonTerminal() << "--> ";
        for (auto &elem: first[c.GetNonTerminal()]) {
            cout << elem.GetTerminal() << ",";
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

    cout << endl << "terminalIndices:" << endl;
    for (const auto &terminalIndex: terminalIndices) {
        cout << terminalIndex.first << " --> " << terminalIndex.second << endl;
    }

    cout << endl << "parse2 table:" << endl;
    for (int i = 0; i < nonTerminalIndices.size(); i++) {
        for (int j = 0; j < terminalIndices.size(); j++) {
            cout << "+" << parseTable[i][j] << "\t";
        }
        cout << endl;
    }
}

string ParseTable::getRule(const string &nonTerminal, const string &terminal) {
    return parseTable[nonTerminalIndices[nonTerminal]][terminalIndices[terminal]];
}

string ParseTable::getStartingSymbol() {
    return startSymbol;
}
