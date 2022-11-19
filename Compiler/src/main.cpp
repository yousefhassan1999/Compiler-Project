#include "src/lexicalAnalysis/lexicalGenerator.h"
#include "src/lexicalAnalysis/nfaGraphGenerator/NFAGenerator.h"
#include "src/lexicalAnalysis/dfaGraphGenerator/DFA.h"
#include "src/lexicalAnalysis/dfa_minimization/vectorDFA.h"
#include "src/lexicalAnalysis/dfa_minimization/DFAMinimizer.h"

using namespace std;

void test(vectorDFA *dfa) {
    string input;
    printf("Enter your input:\n");
    do {
        int state = 0;
        cin >> input;
        for (char i : input) {
            state = dfa->nextState(state, i);
            if (state == -1) {
                printf("Invalid input!\n");
                break;
            }
        }
        if(state != -1)
            printf("%d %s\n", dfa->getStateInfo(state)->acceptance, dfa->getStateInfo(state)->tokenName.c_str());
    }while(!input.empty());
}

int main() {
    LexicalGenerator ob;
    DFAMinimizer minimizer;

    ob.getLexicalRules()->readFileContent(".././lexical rules.txt");
    NFAGenerator nfaGenerator(ob.getLexicalRules());

    DFA dfa(ob.getLexicalRules()->getRules(), nfaGenerator.getNFARoot());
    vector<DFAstate *> dfaVec = dfa.build_DFA();

    vectorDFA vecDFA(dfaVec);
    vectorDFA *minimizedDFA = minimizer.minimize(&vecDFA);

    printf("Original: %zu,  Minimized: %zu\n", dfaVec.size(), minimizedDFA->getTransitionTable().size());
    test(minimizedDFA);
    return 0;
}
