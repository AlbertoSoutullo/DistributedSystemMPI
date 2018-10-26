#include "Tree.h"
#include <time.h>


Tree::Tree()
{
    Node nodo(this, NULL, "ROOT" , "dir");
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

void Tree:: setCurrentDir(Node* newDir)
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

    vector<Node*> offsprings = father->getOffsprings();

    for (Node* node: offsprings)
    {
        if ((strcmp(node->getName(), son->getName())) == 0) return 1;
    }

    return 0;
}

//EXPLICACIÓN: miramos en el 1º if si es un fichero o no en caso de fichero lo descartamos
//si es un directorio aumentamos en nivel de nuestro nuevo nodo hijo, y miramos si el padre tiene descendencia previa
//si no tiene se asigna el padre al hijo y el hijo al array de hijos del padre
//si si tiene descendencia se comprueba que el hijo no este ya añadido
// los flag sirven para modificar al final valores generales del arbol
//FIN EXPLICACION

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

    return son;
}

//
Node* Tree::findNode(Node* father, int id)
{
    if (father->getNumberOfOffsprings() == 0) return NULL;

    vector<Node*> offsprings = father->getOffsprings();

    for (Node* node: offsprings)
    {
        if (node->getId() == id) return node;
    }

    return 0;
}

//update node information
//in case you dont want to change a name yo introduce "not" and in case of size you introduce -1.
//void Tree :: modifyNodeProperties(Node* node)
//{
//	string option;
//	node->setByteSize(2);
//	time_t t;
//	
//	node->setDateLastModif(t);
//	
//	char name[25];
//	cout << "Do you want to modify name?" << endl;
//	cin >> option;
//	if (option == "y")
//	{
//		cout << "introduce value:" << endl;
//		cin >> name;
//		node->setName(name);
//
//	}
//	fflush(stdin);
//	off_t bytes;
//	cout << "Do you want to modify bytes?" << endl;
//	cin >> option;
//	if (option == "y")
//	{
//		int value;
//		cout << "introduce value:" << endl;
//		cin >> value;
//		
//
//	}
//	
//	cin >> bytes;
//
//
//
//	
//}

//delete node from tree
//void Tree :: deleteNode(Node* node)
//{

//	if (this->root == node)
//	{
//		printf("root not posible to delete");
//	}
//	else
//	{
//        if (node->getOffsprings() == NULL)
//		{
//			Node* father = (*node).getNodeFather();

//			for (int i = 0; i < father->getNumberOfOffsprings(); i++)
//			{
//                if (father->getOffsprings()[i]->getId() == node->getId())
//				{
//					father->setNumberOffsprings(-1);
//				}

//			}

//			node->setFather(NULL);
//			this->numberOfNodes--;
//		}
//		else
//		{
//			printf("Delete not posible , existence of childs for node");
//		}
//	}

	

//}



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
int Tree::getSizeStructure()
{
	return this->numberOfNodes;
}

//returns last node id
int Tree::getLastNodeId() {
	return this->lastNodeAdded;
}
