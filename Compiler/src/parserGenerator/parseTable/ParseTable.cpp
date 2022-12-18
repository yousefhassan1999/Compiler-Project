//
// Created by ahmed on 12/17/2022.
//

#include <sstream>
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
