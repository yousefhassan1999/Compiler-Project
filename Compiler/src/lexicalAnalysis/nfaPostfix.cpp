#include <string>
#include <utility>
#include "nfaPostfix.h"

using namespace std;


void NFAPostfix::setTokenName(string newTokenName) {
    tokenName = std::move(newTokenName);
}

void NFAPostfix::setPostFix(string newPostFix) {
    postFix = std::move(newPostFix);
}

string &NFAPostfix::getTokenName() {
    return tokenName;
}

string &NFAPostfix::getPostFix() {
    return postFix;
}