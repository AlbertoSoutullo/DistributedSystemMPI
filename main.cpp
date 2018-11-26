//#include "Tree.h"
#include <stdlib.h>
#include <string>

#include "Terminal.h"
#include "harddisk.h"
#include <bits/stdc++.h>

int Node::idcont = 0;

int main(int argc, char *argv[]) 
{
    string options = "";
    string command = "";
    string firstParameter = "";
    string secondParameter = "";
    vector<string> tokens;
    Tree* tree = new Tree();
    Terminal* terminal = new Terminal(tree);

    tree->loadTree();

    terminal->Initiate(tree);
    HardDisk();
    while(options != "exit")
    {
        options = terminal->ReadInput(tree);
        if (options != "exit")
        {
            terminal->Tokenize(tokens, options);
            if (tokens.size() != 0)
            {
                command = terminal->filterCommand(tokens);
                if (tokens.size() > 1)
                {
                    firstParameter = terminal->filterFirstParam(tokens);
                }
                if (tokens.size() > 2)
                {
                    secondParameter = terminal->filterSecondParam(tokens);
                }
                terminal->executeCommand(tree, command, firstParameter, secondParameter);
                tokens.clear();
            }
        }
    }
    tree->WriteBinaryFile();

}
