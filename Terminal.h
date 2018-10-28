#pragma once
#include "Tree.h"
#include "Commands.h"

class Tree;
class Terminal
{
    Tree* tree;


public:
    Terminal();
    Terminal(Tree* tree);
    void Initiate(Tree* tree);
    string ReadInput(Tree* tree);
    vector<string> Tokenize(string option);
};

