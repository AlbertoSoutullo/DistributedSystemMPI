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
    Node* testFolder2 = new Node(tree, tree->getRoot(), "testFolder2", "folder");

    //añado practica al arbol con el nodo root como padre
    Node* newChild = tree->addChild(testFolder, tree->getRoot());
    newChild = NULL;
    newChild = tree->addChild(testFile, tree->getRoot());
    newChild = NULL;
    newChild = tree->addChild(testFolder2, testFolder);
    newChild = NULL;

    newChild = tree->findNode(testFolder, 3);

//Doesn't work in QT
//    tree->updateChild(tree->getRoot());
//    std::cout << tree->getRoot()->getName() << std::endl;

    //tree->removeChild(testFolder2);

    newChild = tree->findNode(testFolder, 3);
    if (newChild == NULL) std::cout << "Not found" << std::endl;

    cd(tree, "testFolder");
    //pwd(tree);
    //ls(tree);
    mv(tree, "testFolder2", "aaabbbbc");
    mkdir(tree, "MKDIR");
    ls(tree);

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
