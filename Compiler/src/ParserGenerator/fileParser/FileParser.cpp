#include "FileParser.h"
#include "../../common/ErrorLogger.h"
#include <stack>
#include <bits/stdc++.h>

const string FileParser::END_SYMBOL = "$";
const string FileParser::EPSILON = "epsilon";
const string FileParser::SYNC = "sync";

bool terminal(const string& symbol) {
    return symbol[0] == '\'';
}

list<string> FileParser::parse(queue<string> tokensQue, ParsingTable &parsingTable) {
    list<string> output;
    stack<string> parsingStack;

    tokensQue.push(END_SYMBOL);
    parsingStack.push("'" + END_SYMBOL + "'");
    parsingStack.push(parsingTable.getStartingSymbol());

    while (!parsingStack.empty() && !tokensQue.empty()) {
        string token = "'" + tokensQue.front() + "'";
        string stackTop = parsingStack.top();

        if(!terminal(stackTop)){
            string production = parsingTable.getRule(token, stackTop);
            if(production.empty()) { // Error
                ostringstream errorMsg;
                errorMsg << "no production -> non-terminal: " << stackTop << ", terminal: " << token;
                ErrorLogger::parsingError(errorMsg.str());
                tokensQue.pop();
            }
            else if(production == SYNC){ // Error
                ostringstream errorMsg;
                errorMsg << "sync -> non-terminal: " << stackTop << ", terminal: " << token;
                ErrorLogger::parsingError(errorMsg.str());
                parsingStack.pop();
            }
            else {
                parsingStack.pop();
                pushRuleToStack(production, parsingStack);
                output.push_back(production);
            }
        }
        else {
            if(stackTop != token){
                ostringstream errorMsg;
                errorMsg << "token doesn't match -> expected: " << stackTop << ", found: " << token;
                ErrorLogger::parsingError(errorMsg.str());
            }
            parsingStack.pop();
            tokensQue.pop();
        }
    }

    ErrorLogger::parsingError("unable to complete parsing");
    if(!parsingStack.empty() || !tokensQue.empty()){
        ErrorLogger::parsingError("unable to complete parsing");
    }

    return output;
}

void FileParser::pushRuleToStack(const string& rule, std::stack<string>& parsingStack) {
    istringstream ss(rule);
    stack<string> splits;
    string symbol;
    while (ss >> symbol) {
        if(symbol != EPSILON)
            splits.push(symbol);
    }
    while (!splits.empty()) {
        parsingStack.push(splits.top());
        splits.pop();
    }
}

void FileParser::writeOutput(const string& filePath, list<string> &output) {
    ofstream outFile;
    outFile.open(filePath);
    for(auto& str : output) {
        outFile << str << endl;
    }
    outFile.close();
}
