#include <iostream>
#include <fstream>
#include <string>
#include "lexicalRules.h"

using namespace std;

int main () {
    LexicalRules ob;
    ob.ReadFileContaint("lexical rules.txt");
    return 0;
}
