#include "parserfunctions.h"
#include <QApplication>
#include <QProcess>
ParserFunctions::ParserFunctions()
{
    parser_error = 0;
}
void ParserFunctions::set_vector(VectorOfTokens vector)
{
    this->input_vector = vector;
}

void ParserFunctions::error()
{
    input_vector.advance();
    cout << "ERROR";
    this->set_parser_error();
}

void ParserFunctions::match(string expected_token) {
    if (input_vector.get_token().get_type() == expected_token) {
        input_vector.advance();
        //get character
    }
    else {
        error();
    }
}

TreeNode ParserFunctions::program() {
    TreeNode temp = stmt_sequence();
    return temp;
}


TreeNode ParserFunctions::stmt_sequence() {
    TreeNode temp, temp2;
    temp = statement();
    while (input_vector.get_token().get_type() == "SEMICOLON") {
        match("SEMICOLON");
        temp2 = statement();
        temp.add_brother(temp2);
        //statement();
    }
    return temp;
}

TreeNode ParserFunctions::statement() {
    if (input_vector.get_token().get_type() == "IF") {
        return if_stmt();
    }
    else if (input_vector.get_token().get_type() == "REPEAT") {
        return repeat_stmt();
    }
    else if (input_vector.get_token().get_type() == "IDENTIFIER") {
        return assign_stmt();
    }
    else if (input_vector.get_token().get_type() == "READ") {
        return read_stmt();
    }
    else if (input_vector.get_token().get_type() == "WRITE") {
        return write_stmt();
    }
    else {
        error();
    }
}

TreeNode ParserFunctions::if_stmt() {
    TreeNode temp, newTemp;
    temp.set_token("if", "IF");
    temp.set_shape("RECTANGLE");
    match("IF");
    temp.add_child(exp()); // condition
    match("THEN");
    temp.add_child(stmt_sequence());// body
    if (input_vector.get_token().get_type() == "END") {
        match("END");
    }
    else if (input_vector.get_token().get_type() == "ELSE") {
        newTemp.set_token("else", "ELSE");
        newTemp.set_shape("RECTANGLE");
        match("ELSE");
        newTemp.add_child(stmt_sequence());
        temp.add_child(newTemp); //else
        match("END");
    }
    else {
        error();
    }
    return temp;
}

TreeNode ParserFunctions::repeat_stmt() {
    TreeNode temp;
    temp.set_token("repeat", "REPEAT");
    temp.set_shape("RECTANGLE");
    match("REPEAT");
    temp.add_child(stmt_sequence());
    match("UNTIL");
    temp.add_child(exp());
    return temp;
}

TreeNode ParserFunctions::assign_stmt() {
    TreeNode temp;
    temp.set_token(input_vector.get_token().get_value(), "ASSIGN");
    temp.set_shape("RECTANGLE");
    match("IDENTIFIER");
    match("ASSIGN");
    temp.add_child(exp());
    return temp;
}

TreeNode ParserFunctions::read_stmt() {
    TreeNode temp;
    match("READ");
    temp.set_token(input_vector.get_token().get_value(), "READ");
    temp.set_shape("RECTANGLE");
    match("IDENTIFIER");
    return temp;
}

TreeNode ParserFunctions::write_stmt() {
    TreeNode temp;
    temp.set_token("write", "WRITE");
    temp.set_shape("RECTANGLE");
    match("WRITE");
    temp.add_child(exp());
    return temp;
}

TreeNode ParserFunctions::exp() {
    TreeNode temp, newTemp;
    temp = simple_exp();
    if (input_vector.get_token().get_type() == "LESSTHAN" || input_vector.get_token().get_type() == "EQUAL") {
        newTemp = comparison_op();
        newTemp.add_child(temp);
        newTemp.add_child(simple_exp());
        temp = newTemp;
    }
    return temp;
    /*else {
        error();
    }*/
}

TreeNode ParserFunctions::comparison_op() {
    TreeNode temp;
    temp.set_shape("ELLIPSE");
    if (input_vector.get_token().get_type() == "LESSTHAN") {
        temp.set_token("<", "OP");
        match("LESSTHAN");
    }
    else if (input_vector.get_token().get_type() == "EQUAL") {
        temp.set_token("=", "OP");
        match("EQUAL");
    }
    else {
        error();
    }
    return temp;
}

TreeNode ParserFunctions::simple_exp() {
    TreeNode temp, newTemp;
    temp = term();
    while (input_vector.get_token().get_type() == "PLUS" || input_vector.get_token().get_type() == "MINUS") {
        newTemp = add_op();
        newTemp.add_child(temp);
        newTemp.add_child(term());
        temp = newTemp;
    }
    return temp;
}

TreeNode ParserFunctions::add_op() {
    TreeNode temp;
    temp.set_shape("ELLIPSE");
    if (input_vector.get_token().get_type() == "PLUS") {
        match("PLUS");
        temp.set_token("+", "OP");
    }
    else if (input_vector.get_token().get_type() == "MINUS") {
        match("MINUS");
        temp.set_token("-", "OP");
    }
    else {
        error();
    }
    return temp;
}

TreeNode ParserFunctions::term() {
    TreeNode temp, newTemp;
    temp = factor();
    while (input_vector.get_token().get_type() == "MULT" || input_vector.get_token().get_type() == "DIV") {
        //newTemp = TreeNode();
        newTemp = mul_op();
        //factor();
        newTemp.add_child(temp);
        newTemp.add_child(factor());
        temp = newTemp;
    }
    return temp;
}

TreeNode ParserFunctions::mul_op() {
    TreeNode temp;
    temp.set_shape("ELLIPSE");
    if (input_vector.get_token().get_type() == "MULT") {
        temp.set_token("*", "OP");
        match("MULT");
    }
    else if (input_vector.get_token().get_type() == "DIV") {
        temp.set_token("/", "OP");
        match("DIV");
    }
    else {
        error();
    }
    return temp;
}

TreeNode ParserFunctions::factor()
{
    TreeNode temp;
    if (input_vector.get_token().get_type() == "OPENBRACKET")
    {
        match("OPENBRACKET");
        temp = exp();
        match("CLOSEDBRACKET");
    }
    else if (input_vector.get_token().get_type() == "NUMBER")
    {
        temp.set_token(input_vector.get_token().get_value(), "NUMBER"); //3yzeen n-set el token
        temp.set_shape("ELLIPSE");
        match("NUMBER");
    }
    else if (input_vector.get_token().get_type() == "IDENTIFIER")
    {
        temp.set_token(input_vector.get_token().get_value(), "IDENTIFIER"); //3yzeen n-set el token
        temp.set_shape("ELLIPSE");
        match("IDENTIFIER");
    }
    else
    {
        error();
    }
    return temp;
}

void ParserFunctions::set_parser_error()
{
    this->parser_error = 1;
}
void ParserFunctions::reset_parser_error()
{
    this->parser_error = 0;
}
bool ParserFunctions::get_parser_error()
{
    return this->parser_error;
}
