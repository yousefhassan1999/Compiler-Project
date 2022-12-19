#include "FileParser.h"

void initParsingTable(ParsingTable& parsingTable) {
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

void initTokensQue(queue<string>& tokensQue) {
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

void testFileParse() {
    ParsingTable parsingTable;
    initParsingTable(parsingTable);

    queue<string> tokensQue;
    initTokensQue(tokensQue);

    list<string> output = FileParser::parse(tokensQue, parsingTable);
    for (auto& str : output) {
        cout << str << endl;
    }
}