#include <iostream>
#include <fstream>
#include "lexicalGenerator.h"

using namespace std;

int main() {
    LexicalGenerator ob;
    ob.GetLexicalRules().ReadFileContaint("D:\\fourth_year\\first term\\Compiler\\Assignments\\Compiler-Project\\Compiler\\lexical rules.txt");
    ob.GenerateNFA();
    return 0;
}
