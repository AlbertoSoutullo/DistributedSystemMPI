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
    void Tokenize(vector<string>& tokens, string option);
    string filterCommand(vector<string> tokens);
    string filterFirstParam(vector<string> tokens);
    string filterSecondParam(vector<string> tokens);
    void executeCommand(Tree* tree, string command, string firstParam, string secondParam);
};

