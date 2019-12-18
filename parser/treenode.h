#pragma once

#include<iostream>
#include<vector>
#include"token.h"

using namespace std;

class MainWindow;

class TreeNode
{
private:
    Token token_node;
    vector<TreeNode*> children;
    TreeNode* brother;
    string shape;
    int dim_x, dim_y;

public:
    //TreeNode(const TreeNode& copy);
    TreeNode();
    TreeNode(Token t_in);
    TreeNode(string type, string val);
    void add_child(TreeNode  child_in);
    void add_brother(TreeNode  brother_in);
    void print_node();
    void set_shape(string shape_in);
    Token get_token();
    void set_token(Token t_in);
    void set_token(string type, string val);
    TreeNode operator=(const TreeNode& copy);
    int get_far_x();
    int max_child_x();


    friend class MainWindow;
};
