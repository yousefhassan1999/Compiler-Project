#include <string>
#include <utility>
#include "PostfixContainer.h"

using namespace std;


void postfixContainer::setTokenName(string newTokenName) {
    tokenName = std::move(newTokenName);
}

void postfixContainer::setPostFix(string newPostFix) {
    postFix = std::move(newPostFix);
}

string &postfixContainer::getTokenName() {
    return tokenName;
}

string &postfixContainer::getPostFix() {
    return postFix;
}