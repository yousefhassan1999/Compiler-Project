#ifndef COMPILER_LEXICAL_ANALYZER_H
#define COMPILER_LEXICAL_ANALYZER_H

#include "src/lexicalAnalysis/LexicalRules/lexicalRules.h"
#include "src/lexicalAnalysis/nfaGraphGenerator/NFAGenerator.h"
#include "src/lexicalAnalysis/shared/DFAstate.h"
#include "src/lexicalAnalysis/dfa_minimization/vectorDFA.h"

using namespace std;

class LexicalAnalyzer {
private:
    ifstream inputFile;
    ofstream outputFile;
    queue<string> tokensQue;
    vectorDFA* dfa = nullptr;
    static LexicalRules* readRules(const string& rulesPath);
    static NFAGenerator* generateNFA(LexicalRules* rules);
    static vector<DFAstate*> generateDFA(NFAGenerator* nfa);
    static vectorDFA* minimizeDFA(vector<DFAstate*>& dfaVec);
    void parseToken(const string &token);
    void outputAcceptanceState(const string &lexema, const StateInfo &stateInfo, bool &reportError);
public:
    void createMinimizedDFA(const string& rulesPath);
    void initLexicalReader(const string& inputFilePath, const string& outputFilePath);
    string nextToken();
};


#endif //COMPILER_LEXICAL_ANALYZER_H
