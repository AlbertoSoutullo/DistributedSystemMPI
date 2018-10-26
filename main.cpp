//#include "Tree.h"
#include "Commands.h"
#include <stdlib.h>
#include <string>

int Node::idcont = 0;

int main(int argc, char *argv[]) 
{
    Tree* tree = new Tree();

    //nuevo nodo a añadir
    Node* testFolder = new Node(tree, tree->getRoot(), "testFolder", "folder");
    Node* testFile = new Node(tree, tree->getRoot(), "testFile", "file");

    std::cout << testFolder->getName() << std::endl;
    std::cout << testFile->getName() << std::endl;

    //añado practica al arbol con el nodo root como padre
    Node* newChild = tree->addChild(testFolder, tree->getRoot());

    std::cout << newChild->getName() << std::endl;
    std::cout << newChild->getLevel() << std::endl;
    std::cout << newChild->getId() << std::endl;
    std::cout << newChild->getDateLastModif() << std::endl;
    std::cout << newChild->getByteSize() << std::endl;
    std::cout << newChild->getNumberOfOffsprings() << std::endl;
    std::cout << newChild->getType() << std::endl;

//    std::cout << "Level:" << newChild->getLevel() << std::endl;
//    std::cout << "ID:" << newChild->getId() << std::endl;
//    std::cout << "Childs:" << newChild->getNumberOfOffsprings() << std::endl;
//    std::cout << "Byte Size:" << newChild->getByteSize() << std::endl;
//    std::cout << "Last time Mod:" << newChild->getDateLastModif() << std::endl;

    //repito con tmp y con texto
//	Node* tmp = new Node("dir", tree->getRoot(), tree);
//	tmp->setName("tmp");
//	//añado practica al arbol con el nodo root como padre
//	Node * nuevoDesc2 = tree->addNode(tmp, tree->getRoot());
//	Node* texto = new Node("fichero", tree->getRoot(), tree);
//	texto->setName("texto.txt");
//	//añado practica al arbol con el nodo root como padre
//	Node * nuevoDesc3 = tree->addNode(texto, tree->getRoot());
	
//	ls(tree);
//	pwd(tree);
//	//mkdir(tree, "creadoNuevo");
	
//	cp(tree,"practica","tmp");
//	/*string value;
//	std :: cout << "Program started" << endl;
//	while (value != "esc")
//	{
//		cin >> value;
//		fflush(stdin);
//	}*/

//	////////PRUEBAS PARA ADD NODE////
//	//////creo el arbol
//	//Tree * tree;
//	//tree = new Tree();

//	//printf("%s \n", tree->getRoot()->getName());
//	//std::cout <<"" << tree->getRoot()->getType()<<endl;
//	//
//	////nuevo nodo a añadir
//	//Node* practica = new Node("dir", tree->getRoot());
//	//practica->setName("practica");
//	////añado practica al arbol con el nodo root como padre
//	//Node * nuevoDesc = tree->addNode(practica, tree->getRoot());
//	////repito con tmp y con texto
//	//Node* tmp = new Node("dir", tree->getRoot());
//	//tmp->setName("tmp");
//	////añado practica al arbol con el nodo root como padre
//	//Node * nuevoDesc2 = tree->addNode(tmp, tree->getRoot());
//	//Node* texto = new Node("fichero", tree->getRoot());
//	//texto->setName("texto.txt");
//	////añado practica al arbol con el nodo root como padre
//	//Node * nuevoDesc3 = tree->addNode(texto, tree->getRoot());


//	////AHORA VAMOS A INTRODUCIR bin main.c y main
//	//Node* bin = new Node("dir", practica);
//	//bin->setName("bin");
//	////añado practica al arbol con el nodo root como padre
//	//Node * nuevoDesc4 = tree->addNode(bin, nuevoDesc);
//	////este caso debe dar error
//	//
//	////////FIN DE PRUEBAS PARA ADDnode//////

//	//////PRUEBAS PARA FIND NODE ////
//	//Node * found1 = tree->findNode(tree->getRoot(),2);
//	//Node * found2 = tree->findNode(nuevoDesc4->getNodeFather(), 4);
//	////error///
//	//Node * error1 = tree->findNode(tree->getRoot(), 5);
//	//Node * error2 = tree->findNode(tree->getRoot(), 0);
//	//////FIN PRUEBAS FIND NODE////

//	//////PRUEBAS MODIFY///

//	//////FIN PRUEBAS MODIFY////



//	//////PRUEBAS DELETE////
//	//tree->deleteNode(texto);
//	//tree->deleteNode(found2);
//	////error
//	//Tree* tree2 = new Tree();
//	//Node* nodoPrueb= new Node("fichero", NULL);
//	//tree2->addNode(nodoPrueb,tree2->getRoot());
//	//tree2->modifyNodeProperties(nodoPrueb);


//	//////FIN PRUEBAS DELETE////

}
