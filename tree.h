/*
  Brett Bax
  CS4280
  Project 0
  2/14/2022

*/


#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdbool.h>
#include "node.h"

node_t* buildTree(FILE*);
node_t* newNode(char *);

nodeHead* createNodeHead(char *);

char* mallocFp(char*, char [], char [], int);
char finalLetter(char *);

bool searchList(nodeHead*, char *);

void sendToInorderFile(FILE*, node_t*, char*, char*);
void sendToPreorderFile(FILE*, node_t*, char*, char*);
void sendToPostorderFile(FILE*, node_t*, char*, char*);
void printingStuff(FILE*, node_t*, char*, int);

/* These three functions were derived/adjusted from a function found
    on GeeksForGeeks.org: https://www.geeksforgeeks.org/ternary-search-tree/
    "traverseTSTUtil" */
void printInorder(FILE* , node_t*, char*, int);
void printPreorder(FILE* ,node_t*, char*, int);
void printPostorder(FILE* , node_t*, char*, int);

void treeInsert(node_t**, char *);
void printLinkedList(nodeHead*, FILE*);


#endif