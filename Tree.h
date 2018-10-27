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
	int getSizeStructure();
	int getLastNodeId();
	Node* getRoot();

    //Utilities
    Node* findNodeByName(string name, bool isFolder);
};

