#include "src/lexicalAnalysis/lexicalGenerator.h"
#include "src/lexicalAnalysis/nfaGraphGenerator/NFAGenerator.h"
#include "src/lexicalAnalysis/dfaGraphGenerator/DFA.h"

using namespace std;

//vectorDFA* makeDFA();

int main() {
    LexicalGenerator ob;
    ob.getLexicalRules()->readFileContent(".././lexical rules.txt");
    NFAGenerator nfaGenerator(ob.getLexicalRules());
    DFA dfa(ob.getLexicalRules()->getRules(), nfaGenerator.generateNFA());
    dfa.build_DFA();
    return 0;
}

//vectorDFA* makeDFA() {
//    vectorDFA* dfa = new vectorDFA(6);
//
//    dfa->addTransition(0, 'a', 1);
//    dfa->addTransition(0, 'b', 2);
//    dfa->addTransition(1, 'a', 0);
//    dfa->addTransition(1, 'b', 3);
//    dfa->addTransition(2, 'a', 4);
//    dfa->addTransition(2, 'b', 5);
//    dfa->addTransition(3, 'a', 4);
//    dfa->addTransition(3, 'b', 5);
//    dfa->addTransition(4, 'a', 4);
//    dfa->addTransition(4, 'b', 5);
//    dfa->addTransition(5, 'a', 5);
//    dfa->addTransition(5, 'b', 5);
//
//    dfa->addAcceptanceState(2, "", "");
//    dfa->addAcceptanceState(3, "", "");
//    dfa->addAcceptanceState(4, "", "");
//
//    return dfa;
//}
