#pragma once

#include "Node.h"

class Node;
class Tree 
{
	Node*  root;
	Node*  current_Dir;
	int numberOfNodes;
	int lastNodeAdded;

public:
	
	Tree();
	~Tree();
	//void setNewNode(Node* father, string type);
	void setRoot(Node* newRoot);
	void setCurrentDir(Node* newDir);
    //Utilities
    bool isFatherFolder(Node* father);

	//funciones especiales
	Node* addChild(Node* son, Node* father);
	Node* findNode(Node* father, int id);
	void deleteNode(Node* node);
	void modifyNodeProperties(Node* node);
	
	//void printTreeStructure();
	Node* getCurrentDir();
	int getSizeStructure();
	int getLastNodeId();
	Node* getRoot();
};

