#include "LexicalAnalyzer.h"
#include "src/lexicalAnalysis/dfa_minimization/DFAMinimizer.h"

LexicalRules *LexicalAnalyzer::readRules(const string &rulesPath) {
    auto start = chrono::steady_clock::now();

    auto *lRules = new LexicalRules();
    lRules->readFileContent(rulesPath);

    auto end = chrono::steady_clock::now();
    cout << "readRules: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    return lRules;
}

NFAGenerator *LexicalAnalyzer::generateNFA(LexicalRules *rules) {
    auto start = chrono::steady_clock::now();

    auto *nfaGenerator = new NFAGenerator(rules);

    auto end = chrono::steady_clock::now();
    cout << "generateNFA: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    return nfaGenerator;
}

vector<DFAstate *> LexicalAnalyzer::generateDFA(NFAGenerator *nfa) {
    auto start = chrono::steady_clock::now();

    DFA dfa(nfa->getNFARoot());
    vector<DFAstate *> dfaVec = dfa.build_DFA();

    auto end = chrono::steady_clock::now();
    cout << "generateDFA: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    return dfaVec;
}

vectorDFA *LexicalAnalyzer::minimizeDFA(vector<DFAstate *> &dfaVec) {
    auto start = chrono::steady_clock::now();

    vectorDFA vecDFA(dfaVec);
    vectorDFA *minimizedDFA = DFAMinimizer::minimize(&vecDFA);

    auto end = chrono::steady_clock::now();
    cout << "minimizeDFA: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    return minimizedDFA;
}

void LexicalAnalyzer::createMinimizedDFA(const string& rulesPath) {
    auto rules = readRules(rulesPath);
    auto nfa = generateNFA(rules);
    auto dfaVec = generateDFA(nfa);

    delete rules;
    delete nfa;

    auto minDFA = minimizeDFA(dfaVec);
    printf("Original: %zu,  Minimized: %zu\n", dfaVec.size(), minDFA->getTransitionTable().size());

    for (auto x: dfaVec) {
        delete x;
    }
    dfaVec.clear();
    dfa = minDFA;
}

void LexicalAnalyzer::initLexicalReader(const string &inputFilePath, const string &outputFilePath) {
    assert(dfa != nullptr);

    if(inputFile.is_open()) {
        inputFile.close();
        outputFile.close();
        while(!tokensQue.empty()) {
            tokensQue.pop();
        }
    }

    inputFile.open(inputFilePath);
    outputFile.open(outputFilePath);
}

string LexicalAnalyzer::nextToken() {
    if(!inputFile.is_open()) return "";

    string token;
    while(tokensQue.empty()) {
        if (inputFile >> token)
            parseToken(token);
        else
            return "";
    }

    token = tokensQue.front();
    tokensQue.pop();
    return token;
}

void LexicalAnalyzer::parseToken(const string &token) {
    int originalState = 0, start = -1, maxAcceptanceState = -1;
    bool reportError = false;
    string lexema, maxAcceptanceLexema;
    for (int i = 0; i < token.size(); i++) {
        lexema += token[i];
        originalState = dfa->nextState(originalState, token[i]);
        if (originalState == -1) {
            if (maxAcceptanceState != -1) { // apply maximal munch
                outputAcceptanceState(maxAcceptanceLexema, dfa->getStateInfo(maxAcceptanceState), reportError);
                i = start;
                maxAcceptanceState = -1;
            } else { // apply panic mode recovery
                reportError = true;
                start++;
                i = start;
            }
            originalState = 0;
            lexema = "";
        } else if (dfa->getStateInfo(originalState).acceptance) {
            maxAcceptanceState = originalState;
            maxAcceptanceLexema = lexema;
            start = i;
        }
    }
    if (maxAcceptanceState != -1) {
        outputAcceptanceState(maxAcceptanceLexema, dfa->getStateInfo(maxAcceptanceState), reportError);
    } else {
        outputFile << "Invalid input!" << endl;
    }
}

void LexicalAnalyzer::outputAcceptanceState(const string &lexema, const StateInfo &stateInfo, bool &reportError) {
    if (reportError) {
        outputFile << "Error reported and fixed to -> ";
        reportError = false;
    }

    if (stateInfo.tokenName == "Keyword" || stateInfo.tokenName == "Punctuations")
        tokensQue.push(lexema);
    else
        tokensQue.push(stateInfo.tokenName);

    outputFile << lexema << " -> (" << stateInfo.tokenName.c_str() << ")" << endl;
}




