#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lexicalRules.h"
#include "lexicalGenerator.h"

using namespace std;

int main () {
    LexicalGenerator ob;
    ob.GetLexicalRules().ReadFileContaint("D:\\fourth_year\\first term\\Compiler\\Assignments\\Compiler-Project\\Compiler\\lexical rules.txt");
    ob.GenerateNFA();
    /*LexicalRules ob;
    ob.ReadFileContaint("lexical rules.txt");
    vector<string> KeyWords = ob.GetLexicalRules().GetKeyWords();
    vector<string> Punctuations = ob.GetLexicalRules().GetPunctuations();
    vector<string> RegularDefinitions = ob.GetLexicalRules().GetRegularDefinitions();
    vector<string> RegularExpressions = ob.GetLexicalRules().GetRegularExpressions();

    cout << "RegularDefinitions\n";
    for (auto it = RegularDefinitions.begin(); it != RegularDefinitions.end(); ++it)
        cout << *it << "\n";
    cout << "Punctuations\n";
    for (auto it = Punctuations.begin(); it != Punctuations.end(); ++it)
        cout << *it << "\n";
    cout << "KeyWords\n";
    for (auto it = ob.GetLexicalRules().GetKeyWords().begin(); it != ob.GetLexicalRules().GetKeyWords().end(); ++it)
        cout << *it << "\n";
    cout << "RegularExpressions\n";
    for (auto it = RegularExpressions.begin(); it != RegularExpressions.end(); ++it)
        cout << *it << "\n";*/
    return 0;
}
