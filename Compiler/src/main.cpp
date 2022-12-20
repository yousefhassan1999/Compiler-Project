#include "src/lexicalAnalysis/LexicalAnalysis.h"
#include "src/ParserGenerator/CFGRules/CFGRules.h"
#include "src/parserGenerator/parseTable/ParseTable.h"
#include "src/parserGenerator/fileParser/FileParserTest.cpp"
#include "src/lexicalAnalysis/LexicalAnalyzer.h"

using namespace std;

int main() {
    const string rulesPath = "../lexical rules.txt";
    const string inputFile = "../input file.txt";
    const string lexicalOutput = "../lexical output.txt";

    LexicalAnalyzer lexicalAnalyzer;
    lexicalAnalyzer.createMinimizedDFA(rulesPath);
    lexicalAnalyzer.initLexicalReader(inputFile, lexicalOutput);
    int count = 0;
    string token;
    while (!(token = lexicalAnalyzer.nextToken()).empty()) {
        ++count;
        cout << "[" <<token << "]\n";
    }
    cout << count;

    return 0;
}
