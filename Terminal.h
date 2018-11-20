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

    //Part 3:
    //crea archivos de sectores y disco inicializados a vacio.
    //size is size of hdd in sectors.
    void format(int numberOfDisks, int size);
};



/*
“Format 32000” creará un disco duro de 32000 bloques de 1kb (32MB).
En el archivo “sectoreslibres.dat” se almacenarán los números del 1 al 32000,
indicando que todos esos sectores están libres.
*/
