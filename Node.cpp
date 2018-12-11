#include "Node.h"


//Constructors

Node::Node()
{}

bool Node::isFolder(std::string name)
{
    if (name.compare("fichero") == 0 || name.compare("f") == 0 || name.compare("file") == 0 || name.compare("File") == 0)
    {
        return 0;
    }
    return 1;
}

Node::Node(Tree* tree, Node* nodeFather, std::string name,  std::string node_type)
{
    //This note is ROOT
    if (nodeFather == NULL)
    {
        //Check if ROOT already exists
        if (tree->getRoot() == NULL)
        {
            this->tree = tree;
            this->father = NULL;
            this->setName("ROOT");
            this->Id = 0;
            this->idcont = 1;
            this->numberOfOffsprings = 0;
            this->level = 0;
            this->isDirectory = 1;
            this->byteSize = 4096;
            this->dateLastModif = std::time(0);
        }
        else
        {
            std::cout << "Error: ROOT already exists." << std::endl;
        }
    }
    //This note is not root
    else
    {
        this->tree = tree;
        this->father = nodeFather;
        //strncpy(this->name, name.c_str(), name.size());
        this->name = name;
        this->Id = this->idcont;
        this->idcont += 1;
        this->numberOfOffsprings = 0;
        this->level = nodeFather->getLevel() + 1;
        if (isFolder(node_type))
        {
            this->byteSize = 4096;
            this->isDirectory = 1;
        }
        else
        {
            this->byteSize = 0;
            this->isDirectory = 0;
        }
        this->dateLastModif = std::time(0);
    }
}

//destructor
Node :: ~Node(void)
{
}


////GETTERS////

//returns type folder or archive
std::string Node::getType()
{
	if (this->isDirectory == 0)
	{
        return "File";
	}
	else
	{
        return "Folder";
	}
}

//return pointer Node father
Node* Node::getNodeFather()
{
	return this->father;
}

//return id unic
int Node::getId()
{
	return this->Id;
}

//return offSpring
std::vector<Node*>* Node::getOffsprings()
{
    return &this->offsprings;
}

//return name
std::string Node::getName()
{
	return this->name;
}

//return size in bytes
off_t Node::getByteSize()
{
	//modificar por punter
	return this->byteSize;
}

//return last modification date
time_t Node::getDateLastModif()
{
	return this->dateLastModif;
}

int Node::getLevel()
{
	return this->level;
}

bool Node::getIsDirectory()
{
    return this->isDirectory;
}

//get number of offsprings
int Node::getNumberOfOffsprings()
{
	return this->numberOfOffsprings;
}

std::vector<location_t>* Node::getBlockLocations()
{
    return &this->blockOccupied;
}

int Node::getNumBlocksOccupied()
{
    return this->numBlocksOccupied;
}

////SETTERS/////

void Node::setTree(Tree* tree)
{
    this->tree = tree;
}

void Node::setIsDirectory(bool isDirectory)
{
    this->isDirectory = isDirectory;
}


//set type
void Node::setType(std::string fichDire)
{
	if (fichDire.compare("fichero") == 0 || fichDire.compare("f") == 0 || fichDire.compare("file") == 0)
	{
		this->isDirectory = 0;
	}
	else if (fichDire.compare("directorio") == 0 || fichDire.compare("dir") == 0 || fichDire.compare("folder") == 0)
	{
		this->isDirectory = 1;
	}
}

//set pointer node father
void Node::setFather(Node* father)
{
	this->father = father;
}

void Node::setNewOffSpring(Node* son)
{
    std::vector<Node*>* sons = this->getOffsprings();
    sons->push_back(son);
    //this->offsprings.push_back(son);
}

//set ++ offspring or -- offsprings number
void Node :: setNumberOffsprings(int number)
{
	if (number == -1)
	{
		this->numberOfOffsprings--;
	}
	else if (number == 1)
	{
		this->numberOfOffsprings++;
	}
}

//set the new id Name of the node, max 25 characters
void Node::setName(std::string name)
{
     //strncpy(this->name, name.c_str(), name.size());
     //this->name[sizeof(name)] = '\0';
    this->name = name;
}

//TODO: check tam if file is not a directory
void Node::setByteSize(off_t tam)
{
    if (this->getIsDirectory())
    {
        this->byteSize = 4096;
    }
    else
    {
        this->byteSize = tam;
    }
}

//sets last time modification
void Node::setDateLastModif(time_t date)
{
	this->dateLastModif = date;
}

//set level of file or directory in tree
void Node::setLevel(int level)
{
	this->level = level;
}

void Node::setID(int id)
{
    this->Id = id;
    this->idcont = id + 1;
}

void Node::setBlock(int block)
{
//    location_t location;
//    location.HDD = HDD;
//    location.block = block;
    this->blockOccupied.push_back(block);
}

void Node::setNumBlocksOccupied()
{
//    int blocks = 0;
//    for (int i = 0; i < this->blockOccupied.size(); i++)
//    {
//        int HDDSize = this->blockOccupied[i].size();
//        blocks += HDDSize;
//    }
    this->numBlocksOccupied = blockOccupied.size();
}

//void Node::setBlockList()
//{
//    this->blockOccupied.push_back(std::vector<int>());
//}

void Node::setBlockOccupied(std::vector<location_t> &blocks)
{
    this->blockOccupied = blocks;
}
