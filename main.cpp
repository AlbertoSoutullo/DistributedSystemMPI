//#include "Tree.h"
#include <stdlib.h>
#include <string>

#include "Terminal.h"
#include <bits/stdc++.h>


int Node::idcont = 0;

int main(int argc, char *argv[]) 
{
    MPI_Init(&argc, &argv);
    std::string options = "";
    std::string command = "";
    std::string firstParameter = "";
    std::string secondParameter = "";
    std::vector<std::string> tokens;

    Terminal* terminal = new Terminal();

    terminal->Initiate();

    while(options != "exit")
    {
        options = terminal->ReadInput();

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
                terminal->executeCommand(command, firstParameter, secondParameter);
                command = "";
                firstParameter = "";
                secondParameter = "";
                tokens.clear();
            }
        }
    }
    terminal->getTree()->WriteBinaryFile();
    delete terminal;
}
