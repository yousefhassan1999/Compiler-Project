#ifndef LEXICALRULES_H_INCLUDED
#define LEXICALRULES_H_INCLUDED
#include <tr1/unordered_set>
#include<list>

class LexicalRules {

    std::tr1::unordered_set <std::string> KeyWords ;
    std::list<std::string> l;
    std::list<std::string> l2;
public:
    void ReadFileContaint(std::string Path);
private:
    bool checkRegularDefinition(std::string LR);
    bool checkPunctuations(std::string LR);
    bool checkKeyWords(std::string LR);
};

#endif // LEXICALRULES_H_INCLUDED
