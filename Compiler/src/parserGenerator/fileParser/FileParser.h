#ifndef COMPILER_FILE_PARSER_H
#define COMPILER_FILE_PARSER_H

#include <string>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "src/lexicalAnalysis/LexicalAnalyzer.h"
#include "src/parserGenerator/parseTable/ParseTable.h"

using namespace std;

class ParsingTable {
private:
    unordered_map<string, unordered_map<string, string>> table;
    string startingSymbol;
public:
    void setStartingSymbol(const string& symbol) {
        startingSymbol = symbol;
    }
    string getStartingSymbol() {
        return startingSymbol;
    }
    void addRule(const string& nonTerminal, const string& terminal, const string& rule) {
        table[nonTerminal][terminal] = rule;
    }
    string getRule(const string& nonTerminal, const string& terminal) {
        return table[nonTerminal][terminal];
    }
};

class FileParser {
private:
    static void pushRuleToStack(const string& basicString, std::stack<string>& stack1);
public:
    static list<string> parse(LexicalAnalyzer& lexicalAnalyzer, ParseTable& parsingTable);
    static list<string> parse2(queue<string> tokensQue, ParsingTable& parsingTable);
    static void writeOutput(const string& filePath, list<string>& output);
};


#endif //COMPILER_FILE_PARSER_H
