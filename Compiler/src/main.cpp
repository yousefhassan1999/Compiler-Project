#include "src/lexicalAnalysis/LexicalAnalysis.h"
#include "src/ParserGenerator/CFGRules/CFGRules.h"

using namespace std;

int main() {
//    LexicalAnalysis::analyzeInput();
    CFGRules test ;
    test.readFileContent("../JavaCFG.txt");
    test.RemoveLeftRec();
    map<string, list<string>>::iterator itr;
    for (itr = test.GetCFGRulesVec()->begin(); itr != test.GetCFGRulesVec()->end(); ++itr) {
        cout << '\t' << itr->first << '\t';
        for (auto i = itr->second.begin(); i != itr->second.end(); ++i)
            cout  << *i << '\n';
    }
    return 0;
}
