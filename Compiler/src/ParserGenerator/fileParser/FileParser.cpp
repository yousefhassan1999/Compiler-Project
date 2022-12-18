#include "FileParser.h"
#include <stack>
#include "../../common/ErrorLogger.h"

const string FileParser::END_SYMBOL = "$";

list<string> FileParser::parse(const string& filePath, queue<string>& tokensQue, ParsingTable &parsingTable) {
    list<string> output;

    stack<string> parsingStack;
    parsingStack.push(END_SYMBOL);
    parsingStack.push(parsingTable.startingSymbol);

    while (!parsingStack.empty()) {
        string token = tokensQue.empty() ? END_SYMBOL : tokensQue.front();
        string stackTop = parsingStack.top();

        if(parsingTable.nonTerminal(stackTop)){
            string rule = parsingTable.getRule(token, stackTop);
            if(rule.empty()) { // Error
                string errorMsg = "there is no rule for the following -> ";
                ErrorLogger::parsingError(errorMsg.append("terminal: ").append(token)
                    .append(", non-terminal: ").append(stackTop));
            }
            else {
                pushRuleToStack(rule, parsingStack);
            }
        }
        else if(stackTop != token){
            string errorMsg = "token doesn't match: expected ";
            ErrorLogger::parsingError(errorMsg.append(stackTop).append(", found").append(token));
        }
        parsingStack.pop();
        tokensQue.pop();
    }

    return output;
}

void FileParser::writeOutput(const string& filePath, list<string> &output) {
    ofstream outFile;
    outFile.open(filePath);
    for(auto& str : output) {
        outFile << str << endl;
    }
    outFile.close();
}

void FileParser::pushRuleToStack(const string& basicString, std::stack<string>& stack1) {

}
