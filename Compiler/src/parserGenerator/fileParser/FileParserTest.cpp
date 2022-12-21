#include "FileParser.h"

void initParsingTable1(ParsingTable& parsingTable) {
    parsingTable.setStartingSymbol("S");
    parsingTable.addRule("S", "'s'", "R T");
    parsingTable.addRule("S", "'v'", "R T");
    parsingTable.addRule("S", "'t'", "R T");

    parsingTable.addRule("R", "'s'", "'s' U R 'b'");
    parsingTable.addRule("R", "'b'", EPSILON);

    parsingTable.addRule("U", "'s'", EPSILON);
    parsingTable.addRule("U", "'b'", EPSILON);
    parsingTable.addRule("U", "'u'", "'u' U");

    parsingTable.addRule("V", "'v'", "'v' V");
    parsingTable.addRule("V", "'t'", EPSILON);

    parsingTable.addRule("T", "'v'", "V 't' T");
    parsingTable.addRule("T", "'t'", "V 't' T");
    parsingTable.addRule("T", END_SYMBOL, EPSILON);
}

void initTokensQue1(queue<string>& tokensQue) {
    tokensQue.push("s");
    tokensQue.push("s");
    tokensQue.push("u");
    tokensQue.push("u");
    tokensQue.push("b");
    tokensQue.push("b");
    tokensQue.push("t");
    tokensQue.push("v");
    tokensQue.push("t");
}

void initParsingTable2(ParsingTable& parsingTable) {
    parsingTable.setStartingSymbol("S");
    parsingTable.addRule("S", "'a'", "A 'b' S");
    parsingTable.addRule("S", "'c'", "A 'b' S");
    parsingTable.addRule("S", "'e'", "'e'");
    parsingTable.addRule("S", END_SYMBOL, EPSILON);

    parsingTable.addRule("A", "'a'", "'a'");
    parsingTable.addRule("A", "'b'", SYNC);
    parsingTable.addRule("A", "'c'", "'c' A 'd'");
    parsingTable.addRule("A", "'d'", SYNC);
}

void initTokensQue21(queue<string>& tokensQue) {
    tokensQue.push("a");
    tokensQue.push("a");
    tokensQue.push("b");
}

void initTokensQue22(queue<string>& tokensQue) {
    tokensQue.push("c");
    tokensQue.push("e");
    tokensQue.push("a");
    tokensQue.push("d");
    tokensQue.push("b");
}

void testFileParse() {
    ParsingTable parsingTable;
    initParsingTable1(parsingTable);

    queue<string> tokensQue;
    initTokensQue1(tokensQue);

    list<string> output = FileParser::parse2(tokensQue, parsingTable);
    for (auto& str : output) {
        cout << str << endl;
    }
}