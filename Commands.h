#include "Tree.h"
#include <unistd.h>
#include <dirent.h>

class Tree;
//DONE
//Print nodes in current directory
void ls(Tree* tree);

//DONE
//Print actual path
void pwd(Tree* tree);

//DONE
//Change directory, accepts .. and /
void cd(Tree* tree, string name);

//DONE
//Change name of a folder/file
void mv(Tree* tree, string oldName, string newName);

//Undone
//Copy: origin-destination.
//file1 -> file1(Copy)
//file -> dict
//folder ->folder(copy) (it does copy content)
void cp(Tree* tree, string actual, string newOne);

//DONE
//Create a new folder.
void mkdir(Tree* tree, string name);

//DONE
//Deletes an empty folder
void rmdir(Tree* tree, string name);

//DONE
//Delete a file
void rm(Tree* tree, string name);

//DONE
//Print real content of actual directory
void lls();

//DONE
//cd in real path. Accepts .. and /
void lcd(string name);

//DONE
//Show real path
void lpwd();

//DONE
//Upload a file or a folder. It uploads recursive content.
void upload(Tree* tree, string name);

//Utilities for upload
struct stat getFileInfo(string name);
bool uploadIsDirectory(struct stat fileInfo);
void uploadFile(Tree* tree, string name, struct stat fileInfo);
void uploadFolder(Tree* tree, Node* node, string name, struct stat fileInfo);

//utilities for copy
void cpCloneFile(Tree* tree, string original, string copy);
void cpCloneFileInFolder(Tree* tree, Node* father, string original, off_t byteSize);
void cpCloneFolder(Tree* tree, Node* nodeToCopy, Node* nodeDestination);
