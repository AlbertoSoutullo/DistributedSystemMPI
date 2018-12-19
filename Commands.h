#include "Tree.h"
#include "HardDisk.h"
#include <unistd.h>
#include <dirent.h>
#include <stdexcept>

class Tree;
class HardDisk;

class Commands
{
    HardDisk* HDDs;

public:
    Commands();
    ~Commands();

    //Print nodes in current directory
    void ls(Tree* tree);

    //Print actual path
    void pwd(Tree* tree);

    //Change directory, accepts .. and /
    void cd(Tree* tree, std::string name);

    //Change name of a folder/file
    void mv(Tree* tree, std::string oldName, std::string newName);

    //Copy: origin-destination.
    //file1 -> file1(Copy)
    //file -> dict
    //folder ->folder(copy) (it does copy content)
    void cp(Tree* tree, std::string actual, std::string newOne);

    //Create a new folder.
    void mkdir(Tree* tree, std::string name);

    //Deletes an empty folder
    void rmdir(Tree* tree, std::string name);

    //Delete a file
    void rm(Tree* tree, std::string name);

    //Print real content of actual directory
    void lls();

    //cd in real path. Accepts .. and /
    void lcd(std::string name);

    //Show real path
    void lpwd();

    //Upload a file or a folder. It uploads recursive content.
    void upload(Tree* tree, std::string name);

    //Utilities for upload
    struct stat getFileInfo(std::string name);
    bool uploadIsDirectory(struct stat fileInfo);

    void uploadFile(Tree* tree,Node* node, std::string name, struct stat fileInfo);
    void uploadFolder(Tree* tree, Node* node, std::string name, struct stat fileInfo);

    //utilities for copy
    void cpCloneFile(Tree* tree, std::string original, std::string copy);
    void cpCloneFileInFolder(Tree* tree, Node* father, std::string original, off_t byteSize);
    void cpCloneFolder(Tree* tree, Node* nodeToCopy, Node* nodeDestination);

    ////New Aditions/////
    void download(Tree* tree, std::string fileName);
    bool format(std::string size);

};
