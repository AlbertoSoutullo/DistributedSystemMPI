#include "Node.h"


//Constructors

Node::Node()
{}

bool Node::isFolder(string name)
{
    if (name.compare("fichero") == 0 || name.compare("f") == 0 || name.compare("file") == 0)
    {
        return 0;
    }
    return 1;
}

Node::Node(Tree* tree, Node* nodeFather, char* name,  string node_type)
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
        strncpy(this->name, name, strlen(name));
        this->numberOfOffsprings = 0;
        this->level = nodeFather->getLevel() + 1;
        if (isFolder(node_type)) this->isDirectory = 0;
        else this->isDirectory = 1;
        this->dateLastModif = std::time(0);
    }
}

//destructor
Node :: ~Node(void)
{
}


////GETTERS////

//returns type folder or archive
string  Node::getType()
{
	if (this->isDirectory == 0)
	{
		return "fichero";
	}
	else
	{
		return "directorio";
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
Node** Node::getOffspring()
{
	return this->offsprings;
}

//return name
char* Node::getName()
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

//get number of offsprings
int Node::getNumberOfOffsprings()
{
	return this->numberOfOffsprings;
}

////SETTERS/////

//set type
void Node::setType(string fichDire)
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

//creates new Node offSpring, flag first == true is the first one we save memory with malloc
//if flag first == false is not the first one we allocate with realloc
void Node::setNewOffSpring(bool first, Node* son)
{
	if (first == true)
	{
		//increment number of sons
		this->numberOfOffsprings++;
		//save memory
		this->offsprings = (Node**)malloc(sizeof(Node*));
		/////////HA DADO PUNTERAXOOOOOO/////// Esta solucionado as�, funciona ya bien :)
		//this->offsprings[0] = (Node*)malloc(sizeof(Node));
		//save value
		this->offsprings[0] = son;

	}
	else if (first == false)
	{
		//increment number of sons
		this->numberOfOffsprings++;
		this->offsprings = (Node**)realloc(this->offsprings, sizeof(Node*)*this->numberOfOffsprings);
		//for (int i = this->numberOfOffsprings-1; i < this->numberOfOffsprings; i++)
		//{
		this->offsprings[this->numberOfOffsprings - 1] = (Node*)malloc(sizeof(Node));

		//}

		this->offsprings[this->numberOfOffsprings - 1] = son;
	}




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
void Node::setName(char* name)
{
     strncpy(this->name, name, sizeof(name));
}

//TODO: check tam if file is not a directory
void Node::setByteSize(/*off_t tam*/)
{
    /*if (this->getType() == "directorio")
	{
		this->byteSize = 4096;
	}
	else
	{
		this->byteSize = tam;
    }*/
    this->byteSize = 4096;
}

//sets last time modification
void Node::setDateLastModif(time_t date)
{
	this->dateLastModif = date;
	/*struct stat buffer;
	int  status;
	status = stat(this->name, &buffer);
	this->dateLastModif = buffer.st_mtime;*/
}
//set level of file or directory in tree
void Node::setLevel(int level)
{
	this->level = level;
}
