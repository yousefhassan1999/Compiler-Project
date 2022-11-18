#include <fstream>
#include "src/lexicalAnalysis/lexicalGenerator.h"
#include "src/lexicalAnalysis/nfaGraphGenerator/NFAGenerator.h"
#include "src/lexicalAnalysis/dfaGraphGenerator/DFA.h"

using namespace std;

int main() {
    LexicalGenerator ob;
    ob.getLexicalRules()->readFileContent(".././lexical rules.txt");
    NFAGenerator nfaGenerator(ob.getLexicalRules());
    DFA dfa(ob.getLexicalRules()->getRules(),nfaGenerator.getNFARoot());
    dfa.build_DFA();
    return 0;
}
