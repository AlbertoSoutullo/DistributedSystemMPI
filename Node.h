#pragma once

#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <malloc.h>
#include "Tree.h"
#include <ctime>
#include <vector>


/*
Entrega Parte 3:
-Si un fichero no es múltiplo, los bytes restantes se ponen a cero.
-Array de identificadores de boques en orden.
-Tamaño bloques usados.
*/

#define BLOCK_SIZE 1024

class Tree;
class Node
{
	Tree* tree;
	Node* father;
    std::vector<Node*> offsprings;

    std::string name = "";
    int Id; //It generates a new ID every time a node is created.
	int numberOfOffsprings;
    int level;
    bool isDirectory;

	off_t byteSize;
	time_t dateLastModif;

    ///Segunda Iteracion///
    //Vector de bloques que tenga identificadores de sectores del disco donde está guardado. Tan largo como el fichero, pero no más que el tamaó total del disco.
    //numBLoques: Cuantos bloques se han usado.
    std::vector<int> blockOccupied;
    int numBlocksOccupied = 0;
	
public:
    static int idcont; //varaible to count number of nodes created

	//constructor
    Node(Tree* tree, Node* nodeFather, std::string name, std::string node_type);
	Node();
    ~Node();

	//getters
    std::string getType();
	Node* getNodeFather();
	int getId();
    std::vector<Node*>* getOffsprings();
    std::string getName();
	off_t getByteSize();
	time_t getDateLastModif();
	int getLevel();
	int getNumberOfOffsprings();
    bool getIsDirectory();
    std::vector<int>* getBlockLocations();
    int getNumBlocksOccupied();

	//seters
    void setType(std::string type);
	void setFather(Node* father);
    void setNewOffSpring(Node* son);
    void setName(std::string name);
    void setByteSize(off_t t);
	void setDateLastModif(time_t m);
	void setLevel(int l);
	void setNumberOffsprings(int number);
    void setTree(Tree* tree);
    void setIsDirectory(bool isDirectory);
    void setID(int id);
    void setBlockOccupied(std::vector<int> &blocks);
    void setBlock(int block);
    void setNumBlocksOccupied();

    //Utilities
    bool isFolder(std::string name);
};

