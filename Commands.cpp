#include <iostream>
#include <string>
#include "Commands.h"

//permits view of files and folders of current_directory
void ls(Tree* tree)
{
	
	if (tree->getCurrentDir()->getOffspring() == NULL)
	{
		printf("ups there are no offsprings");
	}
	else
	{
		for (int i = 0; i < tree->getCurrentDir()->getNumberOfOffsprings(); i++)
		{
			
			std::cout << tree->getCurrentDir()->getOffspring()[i]->getType() << " " << tree->getCurrentDir()->getOffspring()[i]->getName() <<
				" " << tree->getCurrentDir()->getOffspring()[i]->getByteSize() << " " << tree->getCurrentDir()->getOffspring()[i]->getDateLastModif() << endl;

		}
	}

}

//lls command
void lls(Tree* tree)
{
	if (tree->getCurrentDir()->getOffspring() == NULL)
	{
		printf("ups there are no offsprings");
	}
	else
	{
		system("ls");
	}

}


void lpwd(Tree* tree)
{
	system("pwd");
}

//lcd
void lcd(Tree* tree, const char * name)
{
	if (strcmp(name, "/"))
	{
		string nameRoot = std::string(tree->getRoot()->getName());
		string total = "cd" + nameRoot;
		system(total.c_str());
	}
	else if (strcmp(name, ".."))
	{

		string nameRoot = std::string(tree->getRoot()->getNodeFather()->getName());
		string total = "cd" + nameRoot;
		system(total.c_str());
	}
	else
	{
		string name = std::string(name);
		string total = "cd" + name;
		system(name.c_str());
	}
}

void upload(Tree* tree,const char* name)
{
	string nameDF;
	cout << "fichero (f)  o directorio (d)" << endl;
	cin >> nameDF;
	Node* node;
	if (nameDF.compare(string("f")))
	{
		node = new Node("fichero", tree->getCurrentDir(), tree);
		Node * nodeAdded = tree->addNode(node, tree->getCurrentDir());
		string nameFD = nodeAdded->getName();
		string total = "cat " + nameFD+".txt";
		system(total.c_str());
	}
	else if(nameDF.compare(string("d")))
	{
		node = new Node("directorio", tree->getCurrentDir(), tree);
		Node * nodeAdded = tree->addNode(node, tree->getCurrentDir());
		string nameFD = nodeAdded->getName();
		//falta hacer de manera recursiva que se vaya subiendo todo
	}
	else
	{
		cout << "Error type" << endl;
	}

	
}


//cd 
void cd(Tree* tree, const char * name)
{
	if (strcmp(name, "/"))
	{
		tree->setCurrentDir(tree->getRoot());
	}
	else if (strcmp(name, ".."))
	{
		tree->setCurrentDir(tree->getCurrentDir()->getNodeFather());
	}
	else
	{
		/*for (int i = 0; i < tree->getCurrentDir()->getNumberOfOffsprings(); i++)
		{
			if (strcmp(tree->getCurrentDir()->getOffspring()[i]->getName(), name) == 0)
			{*/
				tree->setCurrentDir(findNodeByName(tree, name));
		/*	}
		}*/

	}
}

//permits view of files and folders of current_directory
void ls(Tree* tree)
{

	if (tree->getCurrentDir()->getOffspring() == NULL)
	{
		printf("ups there are no offsprings");
	}
	else
	{
		for (int i = 0; i < tree->getCurrentDir()->getNumberOfOffsprings(); i++)
		{

			std::cout << tree->getCurrentDir()->getOffspring()[i]->getName() << " ";

		}
	}

}

//prints path from current directory
void pwd(Tree* tree)
{
	
	string path[150];
	int steps=0;
	Node* node = tree->getCurrentDir();
	while (node->getId() != 0)
	{

		path[steps] = std:: string(node->getName());
		node = node->getNodeFather();
		steps++;


	}
	path[steps] = node->getName();

	for (int i = steps + 1; i > 0; i--)
	{
		cout << "/" << path[i - 1] << "/";
		
	}
	cout << endl;
}


Node * findNodeByName(Tree* tree, const char * name)
{
	for (int i = 0; i < tree->getCurrentDir()->getNumberOfOffsprings(); i++)
	{
		if (strcmp(tree->getCurrentDir()->getOffspring()[i]->getName(), name) == 0)
		{
			return tree->getCurrentDir()->getOffspring()[i];
		}
	}
	
	return NULL;
}


//Preguntar si esto es busqueda en profundidad o solo cambiar un nodo
void mv(Tree* tree, const char* oldName, const char* newName)
{
	findNodeByName(tree, newName)->setName(newName);
}

void cp(Tree* tree, const char * actual, const char * newOne)
{
	string fichero("fichero");
	string directorio("directorio");
	findNodeByName(tree, actual)->getType();
	findNodeByName(tree, newOne)->getType();
	if (findNodeByName(tree, actual)->getType().compare(fichero) == 0 && findNodeByName(tree, newOne)->getType().compare(fichero) == 0
		|| findNodeByName(tree, actual)->getType().compare(fichero) == 0 && findNodeByName(tree, newOne)->getType().compare(directorio) == 0
		|| findNodeByName(tree, actual)->getType().compare(directorio) == 0 && findNodeByName(tree, newOne)->getType().compare(directorio) == 0)
	{
		findNodeByName(tree, newOne)->setName(actual);
	}
	else
	{
		printf("Couldnt copy");
	}

}





//mkdir creation of new directory in current directory
void mkdir(Tree* tree, char * name)
{
	
	//tengo que hacer lo del id automatico para que este método funcione bien y quitar el parametro id de entrada
	Node* dir = new Node("dir", tree->getCurrentDir(),tree);
	dir->setName(name);

	tree->addNode(dir, tree->getCurrentDir());

}

//mkdir creation of new directory in current directory
void rmdir(Tree* tree, const char * name)
{
	//for (int i = 0; i < tree->getCurrentDir()->getNumberOfOffsprings(); i++)
	//{
	//	if (strcmp(tree->getCurrentDir()->getOffspring()[i]->getName(), name)==0)
	//	{
		Node * auxNode = findNodeByName(tree,name);
			if (auxNode->getOffspring() == NULL)
			{
				tree->deleteNode(findNodeByName(tree, name));
			}
	//	}
	//}
}

//rm deletes files // falta probarlo
void rm(Tree* tree, const char * name)
{
	/*for (int i = 0; i < tree->getCurrentDir()->getNumberOfOffsprings(); i++)
	{
		if (strcmp(tree->getCurrentDir()->getOffspring()[i]->getName(), name) == 0)
		{*/
	Node * nodeAux = findNodeByName(tree, name);
			if (nodeAux->getType() == "fichero")
			{
				tree->deleteNode(findNodeByName(tree, name));
			}

	/*	}
	}*/

}


//lcd : 
