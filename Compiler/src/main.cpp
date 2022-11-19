#include "src/lexicalAnalysis/lexicalGenerator.h"
#include "src/lexicalAnalysis/nfaGraphGenerator/NFAGenerator.h"
#include "src/lexicalAnalysis/dfaGraphGenerator/DFA.h"
#include "src/lexicalAnalysis/dfa_minimization/vectorDFA.h"
#include "src/lexicalAnalysis/dfa_minimization/DFAMinimizer.h"

using namespace std;

int main() {
    LexicalGenerator ob;
    DFAMinimizer minimizer;

    ob.getLexicalRules()->readFileContent(".././lexical rules.txt");
    NFAGenerator nfaGenerator(ob.getLexicalRules());

    DFA dfa(ob.getLexicalRules()->getRules(), nfaGenerator.generateNFA());
    vector<DFAstate *> dfaVec = dfa.build_DFA();

    vectorDFA vecDFA(dfaVec);
    vectorDFA *minimizedDFA = minimizer.minimize(&vecDFA);

    printf("%zu", minimizedDFA->getTransitionTable().size());
    return 0;
}
