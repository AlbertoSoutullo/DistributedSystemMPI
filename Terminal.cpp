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

vector<string> Terminal::Tokenize(string option)
{
    vector<string> tokens;
    stringstream ss(option);
    string token = "";

    while(getline(ss, token, ' '))
    {
        tokens.push_back(token);
    }
    return tokens;
}

