//
// Created by ahmed on 12/17/2022.
//

#ifndef COMPILER_PARSE_TABLE_H
#define COMPILER_PARSE_TABLE_H


#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <vector>
#include "src/parserGenerator/CFGRules/CFGContainer.h"
#include "FirstObject.h"

using namespace std;

class ParseTable {
private:
    unordered_map<string, int> nonTerminalIndices;
    unordered_map<string, int> terminalIndices;
    string startSymbol;
    unordered_map<string, vector<FirstObject>> first;
    unordered_map<string, list<string>> container;
    unordered_map<string, unordered_set<string>> follows;
    string **parseTable;
    list<CFGContainer> parserRules;

    static vector<string> split(const string &str);

    void calc_first(const string &k, const list<string> &RHS);

    void createFirst();

    void createFollows();

    void createParseTable();

    void printResults();

public:
    explicit ParseTable(const list<CFGContainer> &rules) {
        startSymbol = rules.front().GetNonTerminal();
        int i = 0;
        for (const auto &rule: rules) {
            nonTerminalIndices.insert({rule.GetNonTerminal(), i});
        }
        parserRules = rules;
        createParseTable();
    }

    string getRule(const string &nonTerminal, const string &terminal);


};


#endif //COMPILER_PARSE_TABLE_H
