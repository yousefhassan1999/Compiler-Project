#include <iostream>
#include <fstream>
#include "src/lexicalAnalysis/lexicalGenerator.h"

using namespace std;

int main() {
    LexicalGenerator ob;
    ob.getLexicalRules().readFileContent("D:\\lexical rules.txt");
    ob.generateNfa();
    return 0;
}
