#include "Terminal.h"
#include <sstream>


Terminal::Terminal()
{
    this->tree = new Tree();
    getcwd(this->cwd, sizeof(cwd));
    this->commandManager = new Commands();
    this->tree->loadTree();
}

Terminal::~Terminal()
{
    delete this->tree;
    delete this->commandManager;
}

void Terminal::Initiate()
{
    std::system("clear");
    std::cout << "Welcome to the Distribute File System" << std::endl;
    std::cout << "Actual remote directory is: " << std::endl;
    this->commandManager->pwd(this->tree);
    std::cout << std::endl;

    std::cout << "Actual local directory is: " << std::endl;
    this->commandManager->lpwd();
    std::cout << std::endl;

    std::cout << "If you want to leave, please write <exit>." << std::endl;
}

std::string Terminal::ReadInput()
{
    std::string input = "";
    this->commandManager->pwd(this->tree);
    std::cout << ">";
    std::getline(std::cin, input);
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


void Terminal::executeCommand(std::string command, std::string firstParam, std::string secondParam)
{
    bool executed = false;
    if (command == "ls")
    {
        this->commandManager->ls(this->tree);
        executed = true;
    }
    if (command == "pwd")
    {
        this->commandManager->pwd(this->tree);
        executed = true;
    }
    if (command == "cd")
    {
        this->commandManager->cd(this->tree, firstParam);
        executed = true;
    }
    if (command == "mv")
    {
        this->commandManager->mv(this->tree, firstParam, secondParam);
        executed = true;
    }
    if (command == "cp")
    {
        this->commandManager->cp(this->tree, firstParam, secondParam);
        executed = true;
    }
    if (command == "mkdir")
    {
        this->commandManager->mkdir(this->tree, firstParam);
        executed = true;
    }
    if (command == "rmdir")
    {
        this->commandManager->rmdir(this->tree, firstParam);
        executed = true;
    }
    if (command == "rm")
    {
        this->commandManager->rm(this->tree, firstParam);
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
        this->commandManager->upload(this->tree, firstParam);
        executed = true;
    }
    if (command == "format")
    {
        if (this->commandManager->format(firstParam))
        {
            delete this->tree;
            this->tree = new Tree();
            this->tree->loadTree();
        }

        executed = true;
    }
    if (command == "download")
    {
        this->commandManager->download(this->tree, firstParam);
        executed = true;
    }
    if(!executed) std::cout << "Command "<< command << " not found." << std::endl;
    else std::cout << std::endl;
}

Tree* Terminal::getTree()
{
    return this->tree;
}
