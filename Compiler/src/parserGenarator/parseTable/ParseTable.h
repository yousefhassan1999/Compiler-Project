//
// Created by ahmed on 12/17/2022.
//

#ifndef COMPILER_PARSE_TABLE_H
#define COMPILER_PARSE_TABLE_H


#include <string>
#include <unordered_map>
#include <unordered_set>

class ParseTable {
private:
    std::unordered_map<std::string, int> nonTerminalIndices;
    std::unordered_set<char>* first = new std::unordered_set<char>[10];
    std::unordered_set<char>* follows = new std::unordered_set<char>[10];

public:

};


#endif //COMPILER_PARSE_TABLE_H
