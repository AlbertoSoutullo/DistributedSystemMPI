#ifndef COMMANDS_H
#define COMMANDS_H
#include "Tree.h"

//Print nodes in current directory
void ls(Tree* tree);

//Print actual path
void pwd(Tree* tree);

//Change directory, accepts .. and /
void cd(Tree* tree, const char * name);

//Change name of a folder/file
void mv(Tree* tree, char* oldName, char* newName);

//Copy: origin-destination.
//file1 -> file1(Copy)
//file -> dict
//folder ->folder(copy) (it does copy content)
void cp(Tree* tree, const char * actual, const char * newOne);

//Create a new folder.
void mkdir(Tree* tree, char * name);

//Deletes an empty folder
void rmdir(Tree* tree, const char * name);

//Delete a file
void rm(Tree* tree, const char * name);

//Print real content of actual directory
void lls(Tree* tree);

//cd in real path. Accepts .. and /
void lcd(Tree* tree, const char * name);

//Show real path
void lpwd(Tree* tree);

//Upload a file or a folder. It uploads recursive content.
void upload(Tree* tree, const char* name);



#endif
