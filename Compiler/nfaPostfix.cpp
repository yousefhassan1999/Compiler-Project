#include <string>
#include "nfaPostfix.h"

using namespace std;


void NFAPostfix::setTokenName(string newTokenName) {
    tokenName = newTokenName;
}

void NFAPostfix::setPostFix(string newPostFix) {
    postFix = newPostFix;
}

string &NFAPostfix::getTokenName() {
    return tokenName;
}

string &NFAPostfix::getPostFix() {
    return postFix;
}