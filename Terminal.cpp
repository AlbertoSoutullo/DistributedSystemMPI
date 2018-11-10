#include "Terminal.h"
#include <sstream>

Terminal::Terminal(){}

Terminal::Terminal(Tree* tree)
{
    this->tree = tree;
}

void Terminal::Initiate(Tree* tree)
{
    std::system("clear");
    std::cout << "Welcome to the Distribute File System" << std::endl;
    std::cout << "Actual remote directory is: " << std::endl;
    pwd(tree);
    std::cout << std::endl;

    std::cout << "Actual local directory is: " << std::endl;
    lpwd();
    std::cout << std::endl;

    std::cout << "If you want to leave, please write <exit>." << std::endl;
}

string Terminal::ReadInput(Tree* tree)
{
    string input = "";
    pwd(tree);
    std::cout << ">";
    std::getline (std::cin, input);
    return input;
}

void Terminal::Tokenize(vector<string> &tokens, string option){
    stringstream ss(option);
    string token = "";

    if (option != "")
    {
        while(getline(ss, token, ' '))
        {
            tokens.push_back(token);
        }
    }

}

string Terminal::filterCommand(vector<string> tokens)
{
    string firstToken = "";
    firstToken = tokens.at(0);

    return firstToken;
}

string Terminal::filterFirstParam(vector<string> tokens)
{
    string firstParam = "";
    firstParam = tokens.at(1);

    return firstParam;
}

string Terminal::filterSecondParam(vector<string> tokens)
{
    string secondParam = "";
    secondParam = tokens.at(2);

    return secondParam;
}


void Terminal::executeCommand(Tree* tree, string command, string firstParam, string secondParam)
{
    bool executed = false;
    if (command == "ls")
    {
        ls(tree);
        executed = true;
    }
    if (command == "pwd")
    {
        pwd(tree);
        executed = true;
    }
    if (command == "cd")
    {
        cd(tree, firstParam);
        executed = true;
    }
    if (command == "mv")
    {
        mv(tree, firstParam, secondParam);
        executed = true;
    }
    if (command == "cp")
    {
        cp(tree, firstParam, secondParam);
        executed = true;
    }
    if (command == "mkdir")
    {
        mkdir(tree, firstParam);
        executed = true;
    }
    if (command == "rmdir")
    {
        rmdir(tree, firstParam);
        executed = true;
    }
    if (command == "rm")
    {
        rm(tree, firstParam);
        executed = true;
    }
    if (command == "lls")
    {
        lls();
        executed = true;
    }
    if (command == "lcd")
    {
        lcd(firstParam);
        executed = true;
    }
    if (command == "lpwd")
    {
        lpwd();
        executed = true;
    }
    if (command == "upload")
    {
        upload(tree, firstParam);
        executed = true;
    }
    if(!executed) std::cout << "Command "<< command << " not found." << std::endl;
    else std::cout << std::endl;
}
