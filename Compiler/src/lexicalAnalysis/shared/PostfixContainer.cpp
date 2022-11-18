#include <string>
#include <utility>
#include "PostfixContainer.h"

using namespace std;


void PostfixContainer::setTokenName(string newTokenName) {
    tokenName = std::move(newTokenName);
}

void PostfixContainer::setPostFix(string newPostFix) {
    postFix = std::move(newPostFix);
}

string &PostfixContainer::getTokenName() {
    return tokenName;
}

string &PostfixContainer::getPostFix() {
    return postFix;
}