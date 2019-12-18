#include "vectoroftokens.h"

void VectorOfTokens::add_token(Token t) {
    tokens.push_back(t);
}
void VectorOfTokens::advance() {
    if (index < tokens.size() - 1) {
        index++;
    }
}
Token VectorOfTokens::get_token() {
    return tokens[index];
}
void VectorOfTokens::print_current_token() {
    tokens[index].print_token();
}
void VectorOfTokens::print_vector() {
    for (unsigned int i = 0; i < tokens.size(); i++) {
        tokens[i].print_token();
    }
}
void VectorOfTokens::clear()
{
    this->tokens.clear();
}
