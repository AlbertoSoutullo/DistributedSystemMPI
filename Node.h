#pragma once

#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <malloc.h>
#include "Tree.h"
#include <ctime>
#include <vector>
using namespace std;

class Tree;
class Node
{
	Tree* tree;
	Node* father;
    //Node ** offsprings = NULL;
    vector<Node*> offsprings;

    char name[25] ="";
    int Id; //It generates a new ID every time a node is created.
	int numberOfOffsprings;
    int level;
    bool isDirectory;

	off_t byteSize;
	time_t dateLastModif;

	
public:
    static int idcont; //varaible to count number of nodes created

	//constructor
    Node(Tree* tree, Node* nodeFather, char* name,  string node_type);
	Node();
	~Node(void);

	//getters
	string getType();
	Node* getNodeFather();
	int getId();
    vector<Node*> getOffsprings();
    char* getName();
	off_t getByteSize();
	time_t getDateLastModif();
	int getLevel();
	int getNumberOfOffsprings();
    bool getIsDirectory();

	//seters
	void setType(string type);
	void setFather(Node* father);
    void setNewOffSpring(/*bool first,*/ Node* son);
    void setName(char* name);
    void setByteSize(/*off_t t*/);
	void setDateLastModif(time_t m);
	void setLevel(int l);
	void setNumberOffsprings(int number);
    void setTree(Tree* tree);
    void setIsDirectory(bool isDirectory);

    //Utilities
    bool isFolder(string name);
};
