#pragma once

#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <malloc.h>
#include "Tree.h"
using namespace std;

class Tree;
class Node
{
	Tree* tree;
	Node* father;
	Node ** offsprings = NULL;
	
    char name[25] ="";
	int Id;
	int numberOfOffsprings;
    int level;
    bool isDirectory;

	off_t byteSize;
	time_t dateLastModif;

	
public:
    static int idcont; //varaible to count number of nodes created

	//constructor
	Node(string nodeType, Node* father,Tree* tree);
	Node();
	~Node(void);

	//getters
	string getType();
	Node* getNodeFather();
	int getId();
	Node** getOffspring();
    char* getName();
	off_t getByteSize();
	time_t getDateLastModif();
	int getLevel();
	int getNumberOfOffsprings();

	//seters
	void setType(string type);
	void setFather(Node* father);
	void setNewOffSpring(bool first, Node* son);
	void setName(const char* name);
	void setByteSize(off_t t);
	void setDateLastModif(time_t m);
	void setLevel(int l);
	void setNumberOffsprings(int number);

};
