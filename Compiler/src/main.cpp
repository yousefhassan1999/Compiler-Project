#include "src/lexicalAnalysis/LexicalAnalysis.h"
#include "src/ParserGenerator/CFGRules/CFGRules.h"
#include "src/parserGenerator/parseTable/ParseTable.h"

using namespace std;

int main() {
//    LexicalAnalysis::analyzeInput();
    CFGRules test ;
    test.readFileContent("../JavaCFG.txt");
    test.RemoveLeftRec();
    test.ApplyLeftRefactor();
    for (auto i = test.GetCFGRulesVec()->begin(); i != test.GetCFGRulesVec()->end(); ++i) {
        cout << '\t' << i->GetNonTerminal() << '\t';
        for (auto j = i->GetRHS()->begin(); j != i->GetRHS()->end(); ++j)
            cout  << *j << '\t'<< '\t';
        cout << '\n';
    }
    ParseTable p(*test.GetCFGRulesVec());
    return 0;
}
