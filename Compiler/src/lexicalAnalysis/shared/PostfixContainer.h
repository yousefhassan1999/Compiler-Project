#ifndef NFA_POSTFIX_H_INCLUDED
#define NFA_POSTFIX_H_INCLUDED

#include <string>

class PostfixContainer {

    std::string tokenName;
    std::string postFix;

public:
    void setTokenName(std::string newTokenName);

    void setPostFix(std::string newPostFix);

    std::string &getTokenName();

    std::string &getPostFix();

private:

};

#endif // NFA_POSTFIX_H_INCLUDED
