#include "Tree.h"
#include <time.h>
#include <iostream>
#include <fstream>


Tree::Tree()
{
    std::string root = "ROOT";
    std::string type = "dir";
    Node nodo(this, NULL, root , type);
	this->root =(Node*)malloc(sizeof(Node));

    //Probar si sin esto funciona igual
    *this->root = nodo;
	//current Dir root
    this->current_Dir = this->root;
	//size
	this->numberOfNodes++;
	//last node id root
    this->lastNodeAdded = 0;
}

//destructor
Tree :: ~Tree()
{}


////SETTERS////

//set new value in root
void Tree::setRoot(Node * root)
{
	this->root = root;
}

void Tree::setCurrentDir(Node* newDir)
{
	this->current_Dir = newDir;
}


////SPECIAL METHODS////

bool Tree::isFatherFolder(Node* father)
{
    if ((father->getType()).compare("fichero") == 0 || (father->getType()).compare("f") == 0 || (father->getType()).compare("file") == 0)
    {
        return 0;
    }
    return 1;
}

bool Tree::isAlreadyOnFather(Node* father, Node* son)
{
    if (father->getNumberOfOffsprings() == 0) return 0;

    vector<Node*>* offsprings = father->getOffsprings();

    for (Node* node: *offsprings)
    {
        //if ((strcmp(node->getName(), son->getName())) == 0) return 1;
        if (node->getName() == son->getName()) return 1;
    }

    return 0;
}

//Check if father is a folder: DONE
//Check if son's name is in father other sons: DONE
Node* Tree::addChild(Node* son, Node* father)
{
    if (!isFatherFolder(father))
    {
        std::cout << "The father is not a folder." << std::endl;
        return NULL;
    }

    //If father is a folder, we check if the son's name is already on it:

    if (isAlreadyOnFather(father, son))
    {
        std::cout << "There is already something with the same name." << std::endl;
        return NULL;
    }

    //If there are no repeated names, we add it:

    (*son).setTree(this);
    (*son).setFather(father);
    (*son).setLevel(father->getLevel() + 1);
    (*son).setDateLastModif(std::time(0));

    (*father).setNewOffSpring(son);
    (*father).setDateLastModif(std::time(0));
    (*father).setNumberOffsprings(1);
    this->numberOfNodes++;

    return son;
}

//
Node* Tree::findNode(Node* father, int id)
{
    if (father->getNumberOfOffsprings() == 0) return NULL;

    vector<Node*>* offsprings = father->getOffsprings();

    for (Node* node: *offsprings)
    {
        if (node->getId() == id) return node;
    }

    return 0;
}

//update node information
void Tree :: updateChild(Node* node)
{
    string option;
    off_t bytes;
    string name;
    bool changed = false;

    std::cout << "Do you want to modify the name? y/n" << std::endl;
    std::cin >> option;
    fflush(stdin);
    if (option == "y")
    {
        std::cout << "Set new name:" << std::endl;
        std::cin >> name;
        fflush(stdin);
        char charName[name.size() + 1];
        name.copy(charName, name.size() + 1);
        charName[name.size()] = '\0';
        node->setName(charName);
        changed = true;
    }

//    std::cout << "Do you want to modify the size? y/n" << std::endl;
//    std::cin >> option;
//    if (option == "y")
//    {
//        std::cout << "Set new size:" << std::endl;
//        std::cin >> bytes;
//        fflush(stdin);
//        node->setByteSize(bytes);
//        changed = true;
//    }

    if (changed) node->setDateLastModif(std::time(0));
}

//delete node from tree
void Tree::removeChild(Node* node)
{
    if(node->getId() == 0)
    {
        std::cout << "You cant delete root." << std::endl;
    }
    else
    {
        if(node->getNumberOfOffsprings() != 0)
        {
            std::cout << "You cant delete this, it's not empty." << std::endl;
        }
        else
        {
            Node* father = node->getNodeFather();
            for(int i = 0; i < father->getNumberOfOffsprings(); i++)
            {
                if (father->getOffsprings()->at(i)->getId() == node->getId())
                {
                    father->getOffsprings()->erase(father->getOffsprings()->begin() + i);
                }
            }
            node->setFather(NULL);
            father->setNumberOffsprings(-1);
            this->numberOfNodes--;
        }
    }
}

Node* Tree::findNodeByName(string name)
{
    if (this->getCurrentDir()->getNumberOfOffsprings() == 0) return NULL;

    vector<Node*>* offsprings = this->getCurrentDir()->getOffsprings();

    for (Node* node: *offsprings)
    {
        if (std::string(node->getName()) == name) return node;
    }
    return NULL;
}

/////SAVE TREE/////


void Tree::WriteBinaryFile()
{
    ofstream fs;
    fs.open("tree.dat", ios::out | ios::binary | ios::trunc);
    if (!fs.is_open()) std::cout << "Cannot open file." << std::endl;
    else saveTree(fs);
    fs.close();
}


void Tree::saveTreeRecursive(Node* nodeToSave, ofstream &of)
{
    int id = nodeToSave->getId();

    string name = nodeToSave->getName();
    char nameChar[20];
    strcpy(nameChar, name.c_str());

    string node_type = "";
    if (nodeToSave->getIsDirectory()) node_type = "File";
    else node_type = "Folder";

    off_t size = nodeToSave->getByteSize();
    time_t lastModification = nodeToSave->getDateLastModif();

    of.write((char*)&id, sizeof(id));
    of.write((char*)&nameChar, sizeof(nameChar));
    of.write((char*)&node_type, sizeof(node_type));
    of.write((char*)&size, sizeof(size));
    of.write((char*)&lastModification, sizeof(lastModification));

    vector<Node*>* elements = this->getRoot()->getOffsprings();
    for (int i = 0; i < this->getRoot()->getNumberOfOffsprings(); i++)
    {
        Node* nodeToSave = elements->at(i);
        saveTreeRecursive(nodeToSave, of);
    }
}


//id nodo y padre,
//block root, then childrens.
//do save after upload, cp, mv, mdkir, rmdir and rm
void Tree::saveTree(ofstream &of)
{
    int totalNodes = this->numberOfNodes;
    int lastNodeAdded = this->lastNodeAdded;
    of.write((char*)&totalNodes, sizeof(totalNodes));
    of.write((char*)&lastNodeAdded, sizeof(lastNodeAdded));

    vector<Node*>* elements = this->getRoot()->getOffsprings();
    for (int i = 0; i < this->getRoot()->getNumberOfOffsprings(); i++)
    {
        Node* nodeToSave = elements->at(i);
        saveTreeRecursive(nodeToSave, of);
    }

    of.close();
}


void Tree::loadTree()
{
    ifstream binaryFile;
    int size = 0;

    binaryFile.open("tree.dat", ios::in | ios::binary);
    binaryFile.seekg(0, ios::end);
    size = (int)binaryFile.tellg();
    binaryFile.seekg(0, ios::beg);

    int numberNodes = 0;
    int lastNode = -1;
    char name[20];
    while(binaryFile.tellg() < size)
    {
        binaryFile.read((char*)&numberNodes, sizeof(numberNodes));
        binaryFile.read((char*)&lastNode, sizeof(lastNode));
        binaryFile.read((char*)&name, sizeof(name));
    }
    std::cout << "The number of nodes are: " << numberNodes << std::endl;
    std::cout << "Last node added is: " << lastNode << std::endl;
    std::cout << "Name is: " << name << std::endl;

    binaryFile.close();
}





////GETTERS////

//returns root node * from tree
Node*  Tree :: getRoot()
{
	return this->root;
}

//return current dir
Node* Tree::getCurrentDir()
{
	return this->current_Dir;
}

//returns size of structure
int Tree::getNumberOfNodes()
{
	return this->numberOfNodes;
}

//returns last node id
int Tree::getLastNodeId() {
	return this->lastNodeAdded;
}
