#include "Tree.h"

class Tree;
//Undone
//Print nodes in current directory
void ls(Tree* tree);

//Undone
//Print actual path
void pwd(Tree* tree);

//Undone
//Change directory, accepts .. and /
void cd(Tree* tree, const char * name);

//Undone
//Change name of a folder/file
void mv(Tree* tree, char* oldName, char* newName);

//Undone
//Copy: origin-destination.
//file1 -> file1(Copy)
//file -> dict
//folder ->folder(copy) (it does copy content)
void cp(Tree* tree, const char * actual, const char * newOne);

//Undone
//Create a new folder.
void mkdir(Tree* tree, char * name);

//Undone
//Deletes an empty folder
void rmdir(Tree* tree, const char * name);

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
