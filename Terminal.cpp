#include "Terminal.h"
#include <sstream>

Terminal::Terminal(){}

Terminal::Terminal(Tree* tree)
{
    this->tree = tree;
    getcwd(this->cwd, sizeof(cwd));
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


void Terminal::formatDisk(int numberOfDisks)
{
    ofstream diskFile;
    for (int i = 0; i < numberOfDisks; i++)
    {
        string string_cwd = string(this->cwd);
        string_cwd += "/disk";
        string_cwd += std::to_string(i);
        string_cwd += ".dat";
        diskFile.open(string_cwd, ios::in | ios::binary | ios::trunc);
        diskFile.close();
    }
}

void Terminal::formatSectors(int numberOfDisks, int size)
{
    ofstream sectorsFile;
    for (int i = 0; i < numberOfDisks; i++)
    {
        string string_cwd = string(this->cwd);
        string_cwd += "/freeSectors";
        string_cwd += std::to_string(i);
        string_cwd += ".dat";
        sectorsFile.open(string_cwd, ios::in | ios::binary | ios::trunc);
        for (int j = 0; j < size; j++)
        {
            sectorsFile.write((char*)&j, sizeof(j));
        }
        sectorsFile.close();
    }
}

bool Terminal::checkHDD(int numberOfDisks)
{
    for(int i = 0; i < numberOfDisks; i++)
    {
        string string_cwd = string(this->cwd);
        string_cwd += "/disk";
        string_cwd += std::to_string(i);
        string_cwd += ".dat";
        if (FILE *file = fopen("disk0.dat".c_str(), "r"))
        {
            std::cout << "Loading Hard Drive " << i << std::endl;
        }
        else return false;
    }
    return true;
}

void Terminal::format(int numberOfDisks, int size)
{
    std::cout << "Formatting Hard Drives..." << std::endl;
    formatDisk(numberOfDisks);
    formatSectors(numberOfDisks, size);
}
