#include "Tree.h"

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
void cp(Tree* tree, const char * actual, const char * newOne);

//DONE
//Create a new folder.
void mkdir(Tree* tree, string name);

//Undone
//Deletes an empty folder
void rmdir(Tree* tree, string name);

//Undone
//Delete a file
void rm(Tree* tree, const char * name);

//Undone
//Print real content of actual directory
void lls(Tree* tree);

//Undone
//cd in real path. Accepts .. and /
void lcd(Tree* tree, const char * name);

//Undone
//Show real path
void lpwd(Tree* tree);

//Undone
//Upload a file or a folder. It uploads recursive content.
void upload(Tree* tree, const char* name);
