#include "FileParser.h"
#include "../../common/ErrorLogger.h"
#include <stack>

const int LIMIT = 1000;

static bool terminal(const string& symbol) {
    return symbol[0] == '\'';
}

list<string> FileParser::parse(LexicalAnalyzer &lexicalAnalyzer, ParseTable &parsingTable) {
    list<string> output;
    stack<string> parsingStack;

    parsingStack.push(END_SYMBOL);
    parsingStack.push(parsingTable.getStartingSymbol());
    output.push_back(parsingTable.getStartingSymbol());
    string token = "'" + lexicalAnalyzer.nextToken() + "'";

    int loopsCount = 0;
    bool noMoreTokens = false;
    while (!parsingStack.empty() && !(token.empty() && noMoreTokens) && loopsCount < LIMIT) {
        ++loopsCount;
        if(token == "''" && !noMoreTokens) {
            token = END_SYMBOL;
            noMoreTokens = true;
        }
        string stackTop = parsingStack.top();

        if(!terminal(stackTop)){
            string production = parsingTable.getRule(stackTop, token);
            if(production.empty()) { // Error
                ostringstream errorMsg;
                errorMsg << "[%] no production -> non-terminal: " << stackTop << ", terminal: " << token;
                output.push_back(errorMsg.str());
                token = "'" + lexicalAnalyzer.nextToken() + "'";
            }
            else if(production == SYNC){ // Error
                ostringstream errorMsg;
                errorMsg << "[%] sync -> non-terminal: " << stackTop << ", terminal: " << token;
                output.push_back(errorMsg.str());
                parsingStack.pop();
            }
            else {
                parsingStack.pop();
                pushRuleToStack(production, parsingStack);
                output.push_back(production);
            }
        }
        else {
            if(stackTop == token){
                token = "'" + lexicalAnalyzer.nextToken() + "'";
            }
            else {
                ostringstream errorMsg;
                errorMsg << "[%] token doesn't match -> expected: " << stackTop << ", found: " << token;
                output.push_back(errorMsg.str());
            }
            parsingStack.pop();
        }
    }

    if(!(parsingStack.empty() && token == "''")){
        if(loopsCount == LIMIT)
            output.emplace_back("[%] Max number of iterations exceeded, possible infinite loop");
        output.emplace_back("[%] Failed to complete parsing");
    }

    return output;
}

list<string> FileParser::parse2(queue<string> tokensQue, ParsingTable &parsingTable) {
    list<string> output;
    stack<string> parsingStack;

    string endSymbol = END_SYMBOL;
    tokensQue.push(endSymbol.substr(1, endSymbol.length() - 2));
    parsingStack.push(END_SYMBOL);
    parsingStack.push(parsingTable.getStartingSymbol());
    output.push_back(parsingTable.getStartingSymbol());

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
            if(stackTop == token){
                tokensQue.pop();
            }
            else {
                ostringstream errorMsg;
                errorMsg << "token doesn't match -> expected: " << stackTop << ", found: " << token;
                ErrorLogger::parsingError(errorMsg.str());
            }
            parsingStack.pop();
        }
    }

    if(!parsingStack.empty() || !tokensQue.empty()){
        ErrorLogger::parsingError("unable to complete parsing");
        output.emplace_back("Failed to continue parsing, check the errors log");
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
