#include <iostream>
#include <string>
#include "Commands.h"

//permits view of files and folders of current_directory
void ls(Tree* tree)
{
    if (tree->getRoot() == NULL) std::cout << "Root not initialized" << std::endl;

    Node* currentDirectory = tree->getCurrentDir();
    int numberOfElements = currentDirectory->getNumberOfOffsprings();
    vector<Node*>* elements = currentDirectory->getOffsprings();
    time_t time;
    struct tm* timeSt;
    //todo add total size in ls
    size_t totalSize = 0;

    for (int i = 0; i < numberOfElements; i++)
    {
        time = elements->at(i)->getDateLastModif();
        timeSt = localtime(&time);
        std::cout << elements->at(i)->getType() << " " << elements->at(i)->getName() << " ";
        std::cout << " with ID: " << elements->at(i)->getId() << ", ";
        std::cout << elements->at(i)->getByteSize() << " " << asctime(timeSt);
        totalSize += elements->at(i)->getByteSize();
    }
    std::cout << std::endl;
    std::cout << numberOfElements << " elements in remote directory " <<
                 currentDirectory->getName() << " with size of " << totalSize << std::endl;
}

//prints path from current directory
void pwd(Tree* tree)
{
    vector<string> path;
    Node* node = tree->getCurrentDir();

    while (node->getId() != 0)
    {
       path.push_back(node->getName());
       path.push_back("/");
       node = node->getNodeFather();
    }
    path.push_back("/root");

    for (int i = path.size()-1; i >= 0; --i)
    {
        std::cout << path.at(i);
    }
}

//cd
void cd(Tree* tree, string name)
{
    if (name == "/")
    {
        tree->setCurrentDir(tree->getRoot());
    }
    else if (name == "..")
    {
        if (tree->getCurrentDir()->getId() == 0)
        {
            std::cout << "You can't go back in Root." << std::endl;
        }
        else
        {
             tree->setCurrentDir(tree->getCurrentDir()->getNodeFather());
        }
    }
    else
    {
        Node* newDirectory = tree->findNodeByName(name);
        if (newDirectory == NULL) std::cout << "That directory does not exists." << std::endl;
        else
        {
            bool isFolder = newDirectory->getIsDirectory();
            if (isFolder)
            {
                tree->setCurrentDir(newDirectory);
            }
            else std::cout << "Destination is not a Folder." << std::endl;
        }
    }
}

void mv(Tree* tree, string oldName, string newNameString)
{
    //char newName[newNameString.size() + 1];
    //strcpy(newName, newNameString.c_str());
    Node* nodeToChange = NULL;
    Node* exists = NULL;

    if ((newNameString != "") && (newNameString != ".") && (newNameString != "..") && (newNameString != "/"))
    {
        nodeToChange = tree->findNodeByName(oldName);
        exists = tree->findNodeByName(newNameString);

        if (nodeToChange != NULL)
        {
            if (exists == NULL)
            {
                nodeToChange->setName(newNameString);
            }
            else
            {
                std::cout << "There exists something with that name already." << std::endl;
            }
        }
        else
        {
            std::cout << "That name is not in this directory." << std::endl;
        }
    }
    else std::cout << "Please, enter a valid name." << std::endl;
}

void cpCloneFile(Tree* tree, string original, string copy)
{
    if (copy == "")
    {
        copy = original + "_copy";
        Node* node = new Node(tree, tree->getCurrentDir(), copy, "File");
        tree->addChild(node, tree->getCurrentDir());
    }
    else
    {
        Node* node = new Node(tree, tree->getCurrentDir(), copy, "File");
        tree->addChild(node, tree->getCurrentDir());
    }
}

void cpCloneFileInFolder(Tree* tree, Node* father, string original, off_t byteSize)
{
    Node* node = new Node(tree, tree->getCurrentDir(), original, "File");
    node->setByteSize(byteSize);
    tree->addChild(node, father);
}


void cpCloneFolder(Tree* tree, Node* nodeToCopy, Node* nodeDestination)
{
    Node* node = new Node(tree, nodeDestination, nodeToCopy->getName(), "Folder");
    tree->addChild(node, nodeDestination);
    vector<Node*>* sons = nodeToCopy->getOffsprings();

    for (int i=0; i < sons->size(); i++ )
    {
        cpCloneFolder(tree, sons->at(i), node);
    }
}

//TODO - Recursive Copy
void cp(Tree* tree, string original, string copy)
{
    if ((copy != "") && (copy != ".") && (copy != "..") && (copy != "/"))
    {
        Node* nodeToCopy = tree->findNodeByName(original);
        Node* nodeDestination = tree->findNodeByName(copy);

        if (nodeToCopy != NULL)
        {
            if (nodeDestination != NULL) //If destination is not null, it must be a folder.
            {
                if(nodeDestination->getIsDirectory()) //We copy nodeToCopy to destination
                {
                    if (!nodeToCopy->getIsDirectory()) //file in directory
                    {
                        cpCloneFileInFolder(tree, nodeDestination, original, nodeToCopy->getByteSize());
                    }
                    else
                    {
                        cpCloneFolder(tree, nodeToCopy, nodeDestination);
                    }
                }
                else
                {
                    std::cout << "Destination exists, but is not a folder." << std::endl;
                }
            }
            else //If destination is null, you want to clone the node.
            {
                //Si directorio
                if (nodeToCopy->getType() == "File")
                {
                    cpCloneFile(tree, original, copy);
                }
                else //clone folder
                {
                    if (copy == "")
                    {
                        std::cout << "Insert a name please." << std::endl;
                    }
                    else
                    {
                        Node* asd = new Node(tree, tree->getCurrentDir(), copy, "Folder");
                        tree->addChild(asd, tree->getCurrentDir());
                        cpCloneFolder(tree, nodeToCopy, asd);
                    }
                }
            }
        }
        else
        {
            std::cout << "That name is not in this directory." << std::endl;
        }
    }
    else std::cout << "Please, enter a valid name." << std::endl;

}

//mkdir creation of new directory in current directory
void mkdir(Tree* tree, string name)
{
    if ((name != "") && (name != ".") && (name != "..") && (name != "/"))
    {
        Node* newDirectory = new Node(tree, tree->getCurrentDir(), name, "Folder");
        Node* result = NULL;
        result = tree->addChild(newDirectory, tree->getCurrentDir());
        if (result == NULL) std::cout << "A new Folder was not possible to create." << std::endl;
    }
    else
    {
        std::cout << "Please, enter a valid name for the new Folder." << std::endl;
    }
}

//mkdir creation of new directory in current directory
void rmdir(Tree* tree, string name)
{
    Node* nodeToDelete = tree->findNodeByName(name);

    if (nodeToDelete != NULL)
    {
        if (nodeToDelete->getIsDirectory())
        {
            int numberOfOffsprings = nodeToDelete->getNumberOfOffsprings();
            if (numberOfOffsprings == 0)
            {
                tree->removeChild(nodeToDelete);
            }
            else
            {
                std::cout << "The folder has content, it needs to be empty." << std::endl;
            }
        }
        else
        {
            std::cout << "The name does not correspond with a Folder." << std::endl;
        }
    }
    else
    {
        std::cout << "There is no folder with that name in the current directory." << std::endl;
    }
}

//rm deletes files
void rm(Tree* tree, string name)
{
    Node* nodeToDelete = tree->findNodeByName(name);

    if (nodeToDelete != NULL)
    {
        if (!nodeToDelete->getIsDirectory())
        {
            tree->removeChild(nodeToDelete);
        }
        else
        {
            std::cout << "The name does not correspond with a File." << std::endl;
        }
    }
    else
    {
        std::cout << "There is no file with that name in the current directory." << std::endl;
    }
}


//lls command
void lls()
{
    system("ls -l");
}

//lcd
void lcd(string name)
{
    if (name == "/")
    {
        chdir("/");
    }
    else if (name == "..")
    {
        chdir("..");
    }
    else
    {
        chdir(name.c_str());
    }
}


void lpwd()
{
    system("pwd");
}


struct stat getFileInfo(string name)
{
    struct stat fileInfo;
    //char fileName[name.size()];
    //strncpy(fileName, name.c_str(), name.size());
    stat(name.c_str(), &fileInfo);
    return fileInfo;
}

//https://stackoverflow.com/questions/146924/how-can-i-tell-if-a-given-path-is-a-directory-or-a-file-c-c
bool uploadIsDirectory(struct stat fileInfo)
{
    if(!S_ISREG(fileInfo.st_mode) /*& S_IFDIR*/)
    {
        return true;
    }
    else return false; //It could be more things but on our scope its not neccesary to check all.
}

void uploadFile(Tree* tree,Node* node, string name, struct stat fileInfo)
{
    Node* newFile = new Node(tree, node, name, "File");
    newFile->setByteSize(fileInfo.st_size);
    newFile->setDateLastModif(fileInfo.st_mtime);
    Node* result = tree->addChild(newFile, node);
    if (result == NULL) std::cout << "Error while uploading the file" << std::endl;
}

void uploadFolder(Tree* tree, Node* node, string name, struct stat fileInfo)
{
    DIR* dir;
    struct dirent* ent;

    if ((dir = opendir(name.c_str())) != NULL)
    {
        chdir(name.c_str());
        while ((ent = readdir(dir)) != NULL)
        {
            if ((strcmp(".", ent->d_name) != 0 ) & ((strcmp("..", ent->d_name) != 0 )))
            {
                stat(ent->d_name, &fileInfo);
                //if fichero
                if (S_IFDIR & (fileInfo.st_mode))
                {
                    Node* newFolder = new Node(tree, node, ent->d_name, "Folder");
                    Node* result = tree->addChild(newFolder, node);
                    if (result == NULL) std::cout << "Couldn't add Folder." << std::endl;
                    uploadFolder(tree, newFolder, ent->d_name, fileInfo);
                    chdir("..");
                }
                else //Upload a file
                {
                    std::cout << "Uploading " << ent->d_name << std::endl;
                    uploadFile(tree, node, ent->d_name, fileInfo);
                }
            }
        }
        closedir (dir);
    }
    else
    {
      std::cout << "File " << name << " can not be oppened." << std::endl;
    }
}

void upload(Tree* tree, string name)
{
    //fileInfo.st_size para el tama�o
    //fileInfo.st_mtime para la fecha de modificacion

    if ((name != "") && (name != ".") && (name != "..") && (name != "/"))
    {
        struct stat fileInfo = getFileInfo(name);
        if (uploadIsDirectory(fileInfo))  //Upload recursivo
        {
            Node* newFolder = new Node(tree, tree->getCurrentDir(), name, "Folder");
            Node* result = tree->addChild(newFolder, tree->getCurrentDir());
            if (result == NULL) std::cout << "Couldn't add Folder." << std::endl;
            uploadFolder(tree, newFolder, name, fileInfo);
        }
        else //Upload a file
        {
            std::cout << "Uploading " << name << std::endl;
            uploadFile(tree, tree->getCurrentDir(), name, fileInfo);
        }
    }
    else std::cout << "Please, enter a valid name to upload." << std::endl;

}
