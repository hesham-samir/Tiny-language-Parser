#include "treenode.h"
#include <string>
#include <vector>
#include <iostream>
#include <QString>

int i = 0;
TreeNode::TreeNode()
{
    this->dim_x = 0;
    this->dim_y = 0;
    this->brother = nullptr;
}

TreeNode::TreeNode(Token t_in)
{
    this->token_node = t_in;
    this->dim_x = 0;
    this->dim_y = 0;
    this->brother = nullptr;
}

TreeNode::TreeNode(string value, string type)
{
    Token temp;
    temp.set_token(value, type);
    this->token_node = temp;
    this->dim_x = 0;
    this->dim_y = 0;
    this->brother = nullptr;
}


void TreeNode::add_child(TreeNode  child_in)
{
    this->children.push_back(new TreeNode(child_in.token_node));

    int vector_size = this->children.size();


    if(vector_size > 1)
    {
        if (this->children[vector_size - 2]->children.size() > 1)
        {
            this->children[vector_size - 1]->dim_x = this->children[vector_size - 2]->dim_x + (200*(this->children[vector_size - 2]->children.size())*(vector_size-1));
        }
        else
        {
            this->children[vector_size - 1]->dim_x = this->children[vector_size - 2]->dim_x + (200*(vector_size-1));
        }
        if (this->children[vector_size - 2]->brother != nullptr)
        {
            int far_x = this->children[vector_size - 2]->get_far_x();
            this->children[vector_size - 1]->dim_x = far_x + 200;
        }

    }
    else
    {
        this->children[vector_size - 1]->dim_x = this->dim_x - (200*(vector_size-1));
    }
    this->children[vector_size - 1]->dim_y = this->dim_y + 250;


    for (int i = 0; i < child_in.children.size(); i++)
    {
        this->children[vector_size - 1]->add_child(*child_in.children[i]);
    }

    if (child_in.brother != nullptr)
    {
        this->children[vector_size - 1]->add_brother(*child_in.brother);
    }
}

void TreeNode::add_brother(TreeNode  brother_in)
{
    if (this == nullptr)
    {
        return;
    }

    TreeNode * t_ptr = this;
    int vector_size = this->children.size();

    while (t_ptr->brother != nullptr)
    {
        t_ptr = t_ptr->brother;
    }

    t_ptr->brother = new TreeNode(brother_in.token_node);
    t_ptr->brother->dim_y = brother_in.dim_y;
    t_ptr->brother->dim_x = brother_in.dim_x;
    if(t_ptr->children.size() > 0){
        i++;
        cout << "*************" << endl << i << endl;
        cout <<t_ptr->children[vector_size -1]->get_token().get_value()<< " " <<t_ptr->children[vector_size -1]->get_token().get_type() << endl;
        cout << t_ptr->brother->get_token().get_type() << " " << t_ptr->brother->dim_x << endl;

        t_ptr->brother->dim_x = t_ptr->children[vector_size -1]->dim_x + 400;

        cout << t_ptr->brother->get_token().get_type() << " " << t_ptr->brother->get_token().get_value() << " " << t_ptr->brother->dim_x << endl;
        cout << "*************" << endl;

        if(t_ptr->children[vector_size -1]->children.size() < 2)
        {
            t_ptr->brother->dim_x = t_ptr->children[vector_size -1]->dim_x + 200;
        }
    }
    else
    {
        i++;
        cout << "*************" << endl << "Time :" << i << endl;
        cout << "Node that has brother: " << t_ptr->get_token().get_type() << " " << t_ptr->dim_x << endl;
        cout << "No. of children is " << t_ptr->children.size() << endl;
        cout << "brother before: " << t_ptr->brother->get_token().get_type() << " " << t_ptr->brother->dim_x << endl;
        if(t_ptr->brother->dim_x < t_ptr->dim_x)
        {
            t_ptr->brother->dim_x = t_ptr->dim_x + 400;
        }

        cout << "brother after: "<<t_ptr->brother->get_token().get_type() << " " << t_ptr->brother->dim_x << endl;
        cout << "*************" << endl;
    }

    //this->brother->dim_x = this->dim_x + 400;

    this->brother->dim_y = this->dim_y;

    for (int i = 0; i < brother_in.children.size(); i++)
    {
        t_ptr->brother->add_child(*brother_in.children[i]);
    }

    if (brother_in.brother != nullptr)
    {
        t_ptr->brother->add_brother(*brother_in.brother);
    }

    return;
}

void TreeNode::print_node()
{
    this->token_node.print_token();
    //cout << "X : " <<  this->dim_x << ", Y = " << this->dim_y << ", Shape : " << this->shape << endl;

    for (unsigned int i = 0; i < children.size(); i++)
    {
        cout << "Child no" << i << " of " << this->token_node.get_type() << " is : ";
        children[i]->print_node();
    }
    if (brother != nullptr)
    {
        cout << "Brother of " << this->token_node.get_type() << " is : ";
        brother->print_node();
    }

    return;
}

void TreeNode::set_shape(string shape_in)
{
    this->shape = shape_in;
}

Token TreeNode::get_token()
{
    return this->token_node;
}

void TreeNode::set_token(Token t_in)
{
    this->token_node = t_in;
}

void TreeNode::set_token(string value, string type)
{
    Token temp;
    temp.set_token(value, type);
    this->token_node = temp;
}

TreeNode TreeNode::operator=(const TreeNode& copy)
{
    this->token_node = copy.token_node;
    this->brother = nullptr;
    this->children.clear();
    if (copy.brother != nullptr)
    {
        this->add_brother(*copy.brother);
    }

    for (int i = 0; i < copy.children.size(); i++)
    {
        this->add_child(*copy.children[i]);
    }
    return *this;
}

int TreeNode::get_far_x()
{
    TreeNode * ptr;
    ptr = this;
    while(ptr->brother != nullptr)
    {
        ptr = ptr->brother;
    }
    return ptr->dim_x;
}
int TreeNode::max_child_x()
{
    int max = this->dim_x;
    for (int i = 0; i < this->children.size(); i++)
    {
        if (this->children[i]->dim_x > max)
        {
            max = this->children[i]->dim_x;
        }
    }
    return max;
}

