#include "lexicalGenerator.h"
#include "lexicalRules.h"

using namespace std;

LexicalRules *LexicalGenerator::getLexicalRules() {
    return &lexicalRules;
}

