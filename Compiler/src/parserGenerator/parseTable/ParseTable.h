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

class ParseTable {
private:
    std::unordered_map<std::string, int> nonTerminalIndices;
    std::unordered_map<std::string, int> terminalIndices;
    std::string startSymbol;
    std::unordered_map<std::string, std::unordered_set<std::string>> first;
    std::unordered_map<std::string, std::unordered_set<std::string>> follows;
    std::list<CFGContainer> parserRules;

    static std::vector<std::string> split(const std::string& str);

    void createFirst();
    void createFollows();
    void createParseTable();

public:
    explicit ParseTable(const std::list<CFGContainer>& rules) {
        startSymbol = rules.front().GetNonTerminal();
        int i =0;
        for (const auto& rule:rules) {
            nonTerminalIndices.insert({rule.GetNonTerminal(),i});
        }
        parserRules = rules;
        createParseTable();
    }

//    ~ParseTable(){
//        delete first;
//        delete follows;
//    }

    std::string getRule(std::string nonTerminal, char terminal)


};


#endif //COMPILER_PARSE_TABLE_H
