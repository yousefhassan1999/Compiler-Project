#include <iostream>
#include <fstream>
#include "lexicalGenerator.h"

using namespace std;

int main() {
    LexicalGenerator ob;
    ob.GetLexicalRules().ReadFileContaint(
            "C:\\Users\\ahmed\\Desktop\\lexical rules.txt");
    // ob.GenerateNFA();
    return 0;
}
