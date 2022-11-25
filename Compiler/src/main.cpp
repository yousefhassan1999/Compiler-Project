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
            printf("state %d: %d %s\n", state, dfa->getStateInfo(state).acceptance, dfa->getStateInfo(state).tokenName.c_str());
    }while(!input.empty());
}

LexicalGenerator *readRules(const string &rulesPath) {
    auto start = chrono::steady_clock::now();

    auto *lGenerator = new LexicalGenerator();
    lGenerator->getLexicalRules()->readFileContent(rulesPath);

    auto end = chrono::steady_clock::now();
    cout << "readRules: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    return lGenerator;
}

NFAGenerator *generateNFA(LexicalGenerator *rules) {
    auto start = chrono::steady_clock::now();

    auto *nfaGenerator = new NFAGenerator(rules->getLexicalRules());

    auto end = chrono::steady_clock::now();
    cout << "generateNFA: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    return nfaGenerator;
}

vector<DFAstate *> generateDFA(LexicalGenerator *rules, NFAGenerator *nfa) {
    auto start = chrono::steady_clock::now();

    DFA dfa(rules->getLexicalRules()->getRules(), nfa->getNFARoot());
    vector<DFAstate *> dfaVec = dfa.build_DFA();

    auto end = chrono::steady_clock::now();
    cout << "generateDFA: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    return dfaVec;
}

vectorDFA *minimizeDFA(vector<DFAstate *> &dfaVec) {
    auto start = chrono::steady_clock::now();

    vectorDFA vecDFA(dfaVec);
    vectorDFA *minimizedDFA = DFAMinimizer::minimize(&vecDFA);

    auto end = chrono::steady_clock::now();
    cout << "minimizeDFA: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    return minimizedDFA;
}

int main() {
    auto rules = readRules(".././lexical rules.txt");
    auto nfa = generateNFA(rules);
    auto dfaVec = generateDFA(rules, nfa);

    delete rules;
    delete nfa;

    auto minDFA = minimizeDFA(dfaVec);
    printf("Original: %zu,  Minimized: %zu\n", dfaVec.size(), minDFA->getTransitionTable().size());

    for (auto x : dfaVec) {
        delete x;
    }
    dfaVec.clear();

    test(minDFA);
    return 0;
}
