#ifndef PARSERFUNCTIONS_H
#define PARSERFUNCTIONS_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "treenode.h"
#include "token.h"
#include "vectoroftokens.h"

using namespace std;

class TreeNode;

class ParserFunctions
{
private :
    VectorOfTokens input_vector;
    bool parser_error;
public:
    ParserFunctions();
    void set_vector(VectorOfTokens vector);
    void error();
    void match(string expected_token);
    TreeNode program();
    TreeNode stmt_sequence();
    TreeNode statement();
    TreeNode if_stmt();
    TreeNode exp();
    TreeNode repeat_stmt();
    TreeNode assign_stmt();
    TreeNode read_stmt();
    TreeNode write_stmt();
    TreeNode comparison_op();
    TreeNode simple_exp();
    TreeNode add_op();
    TreeNode term();
    TreeNode mul_op();
    TreeNode factor();
    void set_parser_error();
    bool get_parser_error();
    void reset_parser_error();
};

#endif // PARSERFUNCTIONS_H
