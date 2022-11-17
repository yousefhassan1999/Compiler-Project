#ifndef NFAPOSTFIX_H_INCLUDED
#define NFAPOSTFIX_H_INCLUDED

#include <string>

class NFAPostfix {

    std::string tokenName;
    std::string postFix;

public:
    void setTokenName(std::string newTokenName);

    void setPostFix(std::string newPostFix);

    std::string &getTokenName();

    std::string &getPostFix();

private:

};

#endif // NFAPOSTFIX_H_INCLUDED
