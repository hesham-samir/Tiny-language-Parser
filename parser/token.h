#pragma once
#include <string>
#include <iostream>
using namespace std;

class Token {
private:
    string value;
    string type;
public:
    Token();

    void set_token(string ivalue, string itype);
    void set_token(char c);
    void set_token(string s);

    void print_token();
    string get_type();
    string get_value();

    void set_type();
};
