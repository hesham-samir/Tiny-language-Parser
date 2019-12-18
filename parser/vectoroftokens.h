#ifndef VECTOROFTOKENS_H
#define VECTOROFTOKENS_H

#include "token.h"
#include "vector"

class VectorOfTokens {
private:
    vector<Token> tokens;
    unsigned int index = 0;

public:
    void add_token(Token t);
    void advance();
    Token get_token();
    void print_current_token();
    void print_vector();
    void clear();
};

#endif // VECTOROFTOKENS_H
