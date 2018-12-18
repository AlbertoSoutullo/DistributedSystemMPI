#pragma once
#include "Tree.h"
#include "Commands.h"

#define PATH_MAX        4096    /* chars in a path name including nul */

class Tree;
class Terminal
{
    char cwd[PATH_MAX];
    Tree* tree;
    Commands* commandManager;

public:

    Terminal();
    ~Terminal();
    void Initiate();
    std::string ReadInput();
    void Tokenize(std::vector<std::string>& tokens, std::string option);
    std::string filterCommand(std::vector<std::string> tokens);
    std::string filterFirstParam(std::vector<std::string> tokens);
    std::string filterSecondParam(std::vector<std::string> tokens);
    void executeCommand(std::string command, std::string firstParam, std::string secondParam);

    Tree* getTree();
};



/*
“Format 32000” creará un disco duro de 32000 bloques de 1kb (32MB).
En el archivo “sectoreslibres.dat” se almacenarán los números del 1 al 32000,
indicando que todos esos sectores están libres.
*/
