#ifndef LEXICALRULES_H_INCLUDED
#define LEXICALRULES_H_INCLUDED
#include <tr1/unordered_set>
#include <vector>

class LexicalRules {

    std::vector<std::string> KeyWords;
    std::vector<std::string> Punctuations ;
    std::vector<std::string> RegularDefinitions;
    std::vector<std::string> RegularExpressions;
public:
    void ReadFileContaint(std::string Path);
    std::vector<std::string>& GetKeyWords();
    std::vector<std::string>& GetPunctuations();
    std::vector<std::string>& GetRegularDefinitions();
    std::vector<std::string>& GetRegularExpressions();
private:
    bool checkRegularDefinition(std::string LR);
    bool checkPunctuations(std::string LR);
    bool checkKeyWords(std::string LR);
};

#endif // LEXICALRULES_H_INCLUDED
