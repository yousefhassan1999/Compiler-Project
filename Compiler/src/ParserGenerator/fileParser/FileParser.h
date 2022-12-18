#ifndef COMPILER_FILE_PARSER_H
#define COMPILER_FILE_PARSER_H

#include <string>
#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

class ParsingTable {
public:
    const string startingSymbol = "METHOD_BODY";
    string getRule(const string& terminal, const string& nonTerminal) {
        return "'(' EXPRESSION ')'";
    }
    bool nonTerminal(const string& symbol) {
        return true;
    }
};

class FileParser {
private:
    static void pushRuleToStack(const string& basicString, std::stack<string>& stack1);
public:
    static const string END_SYMBOL;
    static list<string> parse(const string& filePath, queue<string>& tokensQue, ParsingTable& parsingTable);
    static void writeOutput(const string& filePath, list<string>& output);
};


#endif //COMPILER_FILE_PARSER_H
