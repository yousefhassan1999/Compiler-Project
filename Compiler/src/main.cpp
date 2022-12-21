#include "src/ParserGenerator/CFGRules/CFGRules.h"
#include "src/parserGenerator/parseTable/ParseTable.h"
#include "src/parserGenerator/fileParser/FileParserTest.cpp"

using namespace std;

int main() {
    const string rules = "../lexical rules.txt";
    const string inputFile = "../input file.txt";
    const string lexicalOutput = "../lexical output.txt";
    const string parserOutput = "../parser output.txt";
    const string CFG = "../JavaCFG.txt";

    LexicalAnalyzer lexicalAnalyzer;
    lexicalAnalyzer.createMinimizedDFA(rules);
    lexicalAnalyzer.initLexicalReader(inputFile, lexicalOutput);

    CFGRules test ;
    test.readFileContent(CFG);
    test.RemoveLeftRec();
    test.ApplyLeftRefactor();
    for (auto & i : *test.GetCFGRulesVec()) {
        cout << '\t' << i.GetNonTerminal() << '\t';
        for (auto & j : *i.GetRHS())
            cout  << j << '\t'<< '\t';
        cout << '\n';
    }

    ParseTable parseTable(*test.GetCFGRulesVec());

    list<string> output = FileParser::parse(lexicalAnalyzer, parseTable);
    FileParser::writeOutput(parserOutput, output);

    return 0;
}
