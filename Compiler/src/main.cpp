#include <iostream>
#include <fstream>
#include "src/lexicalAnalysis/lexicalGenerator.h"
#include "src/lexicalAnalysis/dfa_minimization/DFA.h"
#include "src/lexicalAnalysis/dfa_minimization/DFAMinimizer.h"

using namespace std;

DFA* makeDFA();

int main() {
//    LexicalGenerator ob;
//    ob.getLexicalRules().readFileContent("D:\\lexical rules.txt");
//    ob.generateNfa();
    DFAMinimizer minimizer;
    DFA *dfa = makeDFA();
    DFA *minDFA = minimizer.minimize(dfa);

    delete dfa;
    delete minDFA;
//    printf("Debug!\n");
    return 0;
}

DFA* makeDFA() {
    DFA* dfa = new DFA(6);

    dfa->addTransition(0, 'a', 1);
    dfa->addTransition(0, 'b', 2);
    dfa->addTransition(1, 'a', 0);
    dfa->addTransition(1, 'b', 3);
    dfa->addTransition(2, 'a', 4);
    dfa->addTransition(2, 'b', 5);
    dfa->addTransition(3, 'a', 4);
    dfa->addTransition(3, 'b', 5);
    dfa->addTransition(4, 'a', 4);
    dfa->addTransition(4, 'b', 5);
    dfa->addTransition(5, 'a', 5);
    dfa->addTransition(5, 'b', 5);

    dfa->addAcceptanceState(2, "", "");
    dfa->addAcceptanceState(3, "", "");
    dfa->addAcceptanceState(4, "", "");

    return dfa;
}
