#include "Terminal.h"
#include <sstream>

Terminal::Terminal(){}

Terminal::Terminal(Tree* tree)
{
    this->tree = tree;
    getcwd(this->cwd, sizeof(cwd));
    this->commandManager = new Commands();
}

void Terminal::Initiate(Tree* tree)
{
    std::system("clear");
    std::cout << "Welcome to the Distribute File System" << std::endl;
    std::cout << "Actual remote directory is: " << std::endl;
    this->commandManager->pwd(tree);
    std::cout << std::endl;

    std::cout << "Actual local directory is: " << std::endl;
    this->commandManager->lpwd();
    std::cout << std::endl;

    std::cout << "If you want to leave, please write <exit>." << std::endl;
}

std::string Terminal::ReadInput(Tree* tree)
{
    std::string input = "";
    this->commandManager->pwd(tree);
    std::cout << ">";
    std::getline (std::cin, input);
    return input;
}

void Terminal::Tokenize(std::vector<std::string> &tokens, std::string option){
    std::stringstream ss(option);
    std::string token = "";

    if (option != "")
    {
        while(std::getline(ss, token, ' '))
        {
            tokens.push_back(token);
        }
    }

}

std::string Terminal::filterCommand(std::vector<std::string> tokens)
{
    std::string firstToken = "";
    firstToken = tokens.at(0);

    return firstToken;
}

std::string Terminal::filterFirstParam(std::vector<std::string> tokens)
{
    std::string firstParam = "";
    firstParam = tokens.at(1);

    return firstParam;
}

std::string Terminal::filterSecondParam(std::vector<std::string> tokens)
{
    std::string secondParam = "";
    secondParam = tokens.at(2);

    return secondParam;
}


void Terminal::executeCommand(Tree* tree, std::string command, std::string firstParam, std::string secondParam)
{
    bool executed = false;
    if (command == "ls")
    {
        this->commandManager->ls(tree);
        executed = true;
    }
    if (command == "pwd")
    {
        this->commandManager->pwd(tree);
        executed = true;
    }
    if (command == "cd")
    {
        this->commandManager->cd(tree, firstParam);
        executed = true;
    }
    if (command == "mv")
    {
        this->commandManager->mv(tree, firstParam, secondParam);
        executed = true;
    }
    if (command == "cp")
    {
        this->commandManager->cp(tree, firstParam, secondParam);
        executed = true;
    }
    if (command == "mkdir")
    {
        this->commandManager->mkdir(tree, firstParam);
        executed = true;
    }
    if (command == "rmdir")
    {
        this->commandManager->rmdir(tree, firstParam);
        executed = true;
    }
    if (command == "rm")
    {
        this->commandManager->rm(tree, firstParam);
        executed = true;
    }
    if (command == "lls")
    {
        this->commandManager->lls();
        executed = true;
    }
    if (command == "lcd")
    {
        this->commandManager->lcd(firstParam);
        executed = true;
    }
    if (command == "lpwd")
    {
        this->commandManager->lpwd();
        executed = true;
    }
    if (command == "upload")
    {
        this->commandManager->upload(tree, firstParam);
        executed = true;
    }
    if(!executed) std::cout << "Command "<< command << " not found." << std::endl;
    else std::cout << std::endl;
}
