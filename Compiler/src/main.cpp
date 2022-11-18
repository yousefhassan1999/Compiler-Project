#include <iostream>
#include <fstream>
#include "src/lexicalAnalysis/lexicalGenerator.h"
#include "src/lexicalAnalysis/nfaGraphGenerator/NFAGenerator.h"

using namespace std;

int main() {
    LexicalGenerator ob;
    ob.getLexicalRules()->readFileContent(".././lexical rules.txt");
    NFAGenerator nfaGenerator(ob.getLexicalRules());
    nfaGenerator.generateNFA();
    nfaGenerator.getNFARoot();
    return 0;
}
