#include "token.h"

Token::Token() {
    value = "NULL";
    type = "NULL";
}

void Token::set_token(string ivalue, string itype) {
    value = ivalue;
    type = itype;
}
void Token::set_token(char c) {
    value = c;
}
void Token::set_token(string s) {
    value = s;
}

void Token::print_token() {
    cout << value << ", " << type << endl;
}

string Token::get_type() {
    return type;
}

string Token::get_value() {
    return value;
}

void Token::set_type() {
    if (this->value == "if") {
        this->type = "IF";
    }
    else if (this->value == "then") {
        this->type = "THEN";
    }
    else if (this->value == "else") {
        this->type = "ELSE";
    }
    else if (this->value == "end") {
        this->type = "END";
    }
    else if (this->value == "repeat") {
        this->type = "REPEAT";
    }
    else if (this->value == "until") {
        this->type = "UNTIL";
    }
    else if (this->value == "read") {
        this->type = "READ";
    }
    else if (this->value == "write") {
        this->type = "WRITE";
    }
    else if (this->value == "+") {
        this->type = "PLUS";
    }
    else if (this->value == "-") {
        this->type = "MINUS";
    }
    else if (this->value == "*") {
        this->type = "MULTIPLY";
    }
    else if (this->value == "/") {
        this->type = "DIVIDE";
    }
    else if (this->value == "=") {
        this->type = "EQUAL";
    }
    else if (this->value == "<") {
        this->type = "LESSTHAN";
    }
    else if (this->value == ";") {
        this->type = "SEMICOLON";
    }
    else if (this->value == "(") {
        this->type = "OPENBRACKET";
    }
    else if (this->value == ")") {
        this->type = "CLOSEDBRACKET";
    }
    else if (this->value == ":=") {
        this->type = "ASSIGN";
    }
    else {
        this->type = "IDENTIFIER";
    }
}
