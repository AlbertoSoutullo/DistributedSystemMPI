#pragma once

#include "Node.h"

class Node;
class Tree 
{
    Node*  root = NULL;
	Node*  current_Dir;
    int numberOfNodes = 0;
	int lastNodeAdded;

public:
	
	Tree();
	~Tree();

    //funciones especiales
    Node* addChild(Node* son, Node* father);
    Node* findNode(Node* father, int id);
    void updateChild(Node* node);
    void removeChild(Node* node);

	//void setNewNode(Node* father, string type);
	void setRoot(Node* newRoot);
	void setCurrentDir(Node* newDir);
    //Utilities
    bool isFatherFolder(Node* father);
    bool isAlreadyOnFather(Node* father, Node* son);

	//void printTreeStructure();
	Node* getCurrentDir();
    int getNumberOfNodes();
	int getLastNodeId();
	Node* getRoot();

    //Save Structure
    Node* searchByIdRecursive(Node* nodeToSearch, int id);
    Node* searchById(int id);
    void saveTreeRecursive(Node* nodeToSave, std::ofstream &of);
    void WriteBinaryFile();
    void saveTree(std::ofstream &of);
    void loadTree();


    //Utilities
    Node* findNodeByName(std::string name);
};

