#include "FileParser.h"

void initParsingTable1(ParsingTable& parsingTable) {
    parsingTable.setStartingSymbol("S");
    parsingTable.addRule("S", "'s'", "R T");
    parsingTable.addRule("S", "'v'", "R T");
    parsingTable.addRule("S", "'t'", "R T");

    parsingTable.addRule("R", "'s'", "'s' U R 'b'");
    parsingTable.addRule("R", "'b'", FileParser::EPSILON);

    parsingTable.addRule("U", "'s'", FileParser::EPSILON);
    parsingTable.addRule("U", "'b'", FileParser::EPSILON);
    parsingTable.addRule("U", "'u'", "'u' U");

    parsingTable.addRule("V", "'v'", "'v' V");
    parsingTable.addRule("V", "'t'", FileParser::EPSILON);

    parsingTable.addRule("T", "'v'", "V 't' T");
    parsingTable.addRule("T", "'t'", "V 't' T");
    parsingTable.addRule("T", "'" + FileParser::END_SYMBOL + "'", FileParser::EPSILON);
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
    parsingTable.addRule("S", "'" + FileParser::END_SYMBOL + "'", FileParser::EPSILON);

    parsingTable.addRule("A", "'a'", "'a'");
    parsingTable.addRule("A", "'b'", FileParser::SYNC);
    parsingTable.addRule("A", "'c'", "'c' A 'd'");
    parsingTable.addRule("A", "'d'", FileParser::SYNC);
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
    initParsingTable2(parsingTable);

    queue<string> tokensQue;
    initTokensQue22(tokensQue);

    list<string> output = FileParser::parse(tokensQue, parsingTable);
    for (auto& str : output) {
        cout << str << endl;
    }
}