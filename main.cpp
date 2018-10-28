//#include "Tree.h"
#include <stdlib.h>
#include <string>

#include "Terminal.h"
#include <bits/stdc++.h>

int Node::idcont = 0;

int main(int argc, char *argv[]) 
{
    string options = "";
    vector<string> tokens;
    Tree* tree = new Tree();
    Terminal* terminal = new Terminal(tree);

    terminal->Initiate(tree);
    while(options != "exit")
    {
        options = terminal->ReadInput(tree);
        tokens = terminal->Tokenize(options);


    }




//    //
//    Tree* tree = new Tree();

//    //nuevo nodo a añadir
//    Node* testFolder = new Node(tree, tree->getRoot(), "testFolder", "folder");
//    Node* testFile = new Node(tree, tree->getRoot(), "testFile", "file");
//    Node* testFolder2 = new Node(tree, tree->getRoot(), "testFolder2", "folder");

//    //añado practica al arbol con el nodo root como padre
//    Node* newChild = tree->addChild(testFolder, tree->getRoot());
//    newChild = NULL;
//    newChild = tree->addChild(testFile, tree->getRoot());
//    newChild = NULL;
//    newChild = tree->addChild(testFolder2, testFolder);
//    newChild = NULL;

//    newChild = tree->findNode(testFolder, 3);

////Doesn't work in QT
////    tree->updateChild(tree->getRoot());
////    std::cout << tree->getRoot()->getName() << std::endl;

//    //tree->removeChild(testFolder2);

//    newChild = tree->findNode(testFolder, 3);
//    if (newChild == NULL) std::cout << "Not found" << std::endl;

//    cd(tree, "testFolder");
//    //pwd(tree);
//    //ls(tree);
//    //mv(tree, "testFolder2", "aaabbbbc");
//    mkdir(tree, "MKDIR");
//    //rmdir(tree, "MKDIR");
//    cd(tree, "/");
//    //rm(tree, "testFile");

//    //lcd("..");
//    //lls();
//    //lpwd();
//    upload(tree, ".");
//    cd(tree, ".");
//    ls(tree);
}
