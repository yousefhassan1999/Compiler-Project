//
// Created by ahmed on 12/17/2022.
//

#ifndef COMPILER_PARSE_TABLE_H
#define COMPILER_PARSE_TABLE_H

#define EPSILON "Epsilon"
#define SYNC "Sync"
#define END_SYMBOL "'$'"

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
        unordered_set<string> terminals;
        for (CFGContainer rule: rules) {
            nonTerminalIndices.insert({rule.GetNonTerminal(), i});
            for(const auto& rhs : *rule.GetRHS()){
                for(auto element : split(rhs)){
                    if (element[0]=='\''){
                        terminals.insert(element);
                    }
                }
            }
            i++;
        }
        i = 0;
        for (const auto& terminal:terminals){
            terminalIndices.insert({terminal,i});
            i++;
        }
        terminalIndices.insert({END_SYMBOL, i});
        parserRules = rules;
        createParseTable();
    }


    string getRule(const string &nonTerminal, const string &terminal);
    string getStartingSymbol();

};


#endif //COMPILER_PARSE_TABLE_H
