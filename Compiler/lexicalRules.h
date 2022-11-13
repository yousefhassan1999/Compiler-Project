#ifndef LEXICALRULES_H_INCLUDED
#define LEXICALRULES_H_INCLUDED
#include <vector>
#include <map>

class LexicalRules {

    std::vector<std::string> KeyWords;
    std::vector<std::string> Punctuations ;
    std::map<std::string, std::string> RegularDefinitionsMap;
    std::map<std::string, std::string> RegularExpressionsMap;
    std::vector<std::string> RegularExpressions;
public:
    void ReadFileContaint(std::string Path);
    std::vector<std::string>& GetKeyWords();
    std::vector<std::string>& GetPunctuations();
    std::map<std::string, std::string>& GetRegularDefinitionsMap();
    std::map<std::string, std::string>& GetRegularExpressionsMap();
    std::vector<std::string>& GetRegularExpressions();
private:
    bool checkRegularDefinition(std::string LR);
    bool checkPunctuations(std::string LR);
    bool checkKeyWords(std::string LR);
    std::string updateMinus(std::string basicString);
    std::string CheckMapSubstring(std::string basicString);
    int isSubstring(std::string basicString, std::string basicString1);
    void UpdateRegularExpressions();

};

#endif // LEXICALRULES_H_INCLUDED
