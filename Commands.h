#ifndef COMMANDS_H
#define COMMANDS_H
#include "Tree.h"

void ls(Tree* tree);
void lls(Tree* tree);
void lpwd(Tree* tree);
void lcd(Tree* tree, const char * name);
void upload(Tree* tree, const char* name);
void pwd(Tree* tree);
void mkdir(Tree* tree, const char * name);
void rmdir(Tree* tree, const char * name);
void cd(Tree* tree, const char * name);
void cp(Tree* tree, const char * actual, const char * newOne);
Node * findNodeByName(Tree* tree, const char * name);
void mv(Tree* tree, const char* oldName, const char* newName);
void cp(Tree* tree, const char * actual, const char * newOne);
void rm(Tree* tree, const char * name);

#endif