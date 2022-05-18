/*
  Brett Bax
  CS4280
  Project 0
  2/14/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "tree.h"


node_t* buildTree(FILE *fp) {
  node_t *rootP = NULL;
  int tester;
  char buffer[200];
  
  rewind(fp);

  if ((tester = fscanf(fp, "%s", buffer)) <= 0) {
    printf("\nfscanf return value: %d\n", tester);
    perror("tree.c: buildTree");
    exit(1);
  }

  do {
    treeInsert(&rootP, buffer);
  } while (fscanf(fp, "%s", buffer) > 0);


  return rootP;
}

node_t* newNode(char *buffer) {

  node_t* node = (node_t*)malloc(sizeof(node_t));
  node->head = malloc(sizeof(nodeHead));
  nodeHead* var = createNodeHead(buffer);
  var->next = NULL;
  node->head = var;

  node->left = node->middle = node->right = NULL;
  node->stringEnd = 0;
  node->lastLetter = finalLetter(buffer);

  return node;
}


nodeHead* createNodeHead(char *word) {

  nodeHead* holder = malloc(sizeof(node_t));
  holder->word = malloc(strlen(word) + 1);
  strcpy(holder->word, word);
  holder->next = NULL;
  return holder;
}



/* Allocating memory for creating files. Adds extensions to filing
    using 'fileNumber' as an identifier to use the correct extension */
char* mallocFp(char* file, char arg[], char ext[], int fileNumber) {

  file = malloc(strlen(arg) + strlen(ext) + 1);

  if (fileNumber == 1) {
    strcpy(file, arg);
	  strcat(file, ".inorder");
  } else if (fileNumber == 2) {
    strcpy(file, arg);
	  strcat(file, ".preorder");
  } else if (fileNumber == 3) {
    strcpy(file, arg);
	  strcat(file, ".postorder");
  } else {
    strcpy(file, arg);
	  strcat(file, ".sp2022");
  }
    
  return file;
}

/* Get last letter of word or string */
char finalLetter(char *word) {
  return word[strlen(word) - 1];
}


bool searchList(nodeHead* head, char *str) {
  nodeHead* var = head;
  while(var != NULL) {
    if (strcmp(str, var->word) == 0) {
      return true;
    }
    var = var->next;
  }
  return false;
}


/* Opening stream for, calling, and closing stream for Inorder */
void sendToInorderFile(FILE* file, node_t* root, char* fileName, char* buffer) {
  int depth = 0;

  file = (fopen(fileName, "a"));
  printInorder(file, root, buffer, depth);
  fclose(file);
}

/* Opening stream for, calling, and closing stream for Preorder */
void sendToPreorderFile(FILE* file, node_t* root, char* fileName, char* buffer) {
  int depth = 0;

  file = (fopen(fileName, "a"));
  printPreorder(file, root, buffer, depth);
  fclose(file);
}

/* Opening stream for, calling, and closing stream for Postorder */
void sendToPostorderFile(FILE* file, node_t* root, char* fileName, char* buffer) {
  int depth = 0;

  file = (fopen(fileName, "a"));
  printPostorder(file, root, buffer, depth);
  fclose(file);
}

/* Printing all necessary tree information/variables */
void printingStuff(FILE* file, node_t* root, char* buffer, int depth) {
  fprintf(file, "%c", buffer[depth]);
  fputs(":", file);
  printLinkedList(root->head, file);
}


/* As mentioned in tree.h, the three functions below this comment were found and 
   derived from the function 'traverseTSTUtil' : https://www.geeksforgeeks.org/ternary-search-tree/
*/
void printInorder(FILE* file, node_t* root, char* buffer, int depth) {

    if (root != NULL) {
      printInorder(file, root->left, buffer, depth + 1);
      buffer[depth] = root->lastLetter;   

      if (root->stringEnd) {
        int i = 0;
        buffer[depth+1] = '\0';
        fputs("\n", file);
        
        for(i = 0; i < depth; i++) {
          fputs("\t", file);
        }
        printingStuff(file, root, buffer, depth);
      }
      printInorder(file, root->middle, buffer, depth + 1);
      printInorder(file, root->right, buffer, depth + 1);
    }
}

void printPreorder(FILE* file, node_t* rootP, char* buffer, int level) {
    
    if (rootP != NULL) {
      printPreorder(file, rootP->middle, buffer, level + 1);
      buffer[level] = rootP->lastLetter;
      if (rootP->stringEnd) {
        
        int i = 0;
        buffer[level+1] = '\0';
        fputs("\n", file);
        
        for(i = 0; i < level; i++) {
          fputs("\t", file);
        }

        printingStuff(file, rootP, buffer, level);
      }
      printPreorder(file, rootP->left, buffer, level + 1);
      printPreorder(file, rootP->right, buffer, level + 1);
    }
}


void printPostorder(FILE* file, node_t* root, char* buffer, int depth) {
    
    if (root != NULL){
      printPostorder(file, root->left, buffer, depth + 1);
      printPostorder(file, root->right, buffer, depth + 1);
      buffer[depth] = root->lastLetter;
      if(root->stringEnd) {
        int i = 0;
        buffer[depth+1] = '\0';
        fputs("\n", file);
        
        for(i = 0; i < depth; i++) {
          fputs("\t", file);
        }
        printingStuff(file, root, buffer, depth);
      }
      printPostorder(file, root->middle, buffer, depth + 1);
    } 
}


/* Insert node in tree, comparing last letters
  If a word/string is deemed a 'repeat', it is 
  inserted into the linked list using searchList
  and listInsert functions

  also derived from: https://www.geeksforgeeks.org/ternary-search-tree/ 
*/

void treeInsert(node_t** node, char *buffer) {
 
  if (!(*node)) {
    *node = newNode(buffer);
  }

  char tempLetter = finalLetter(buffer);
  char nodeLetter = (*node)->lastLetter;

  if (tempLetter > nodeLetter) {

    treeInsert(&((*node)->right), buffer);

  } else if (tempLetter < nodeLetter) {

    treeInsert(&((*node)->left), buffer);

  } else {

    if (!searchList((*node)->head, buffer)) {
      nodeHead* var = createNodeHead(buffer);
      var->next = (*node)->head;
      (*node)->head = var;
    } 
    else {
      (*node)->stringEnd = 1;
    }
  }
}

/* Printing list of middle children, using a flag to continue printing last letter
   and a colon after first print (due to the way my project is structured) */
void printLinkedList(nodeHead* head, FILE* file) {
  bool afterFirstPrint = false;
  nodeHead* tempHead = head;

  while(tempHead != NULL) {

    if (afterFirstPrint) {
      fprintf(file, "%c", finalLetter(tempHead -> word));
      fputs(":", file);
    }

    fprintf(file, "%s ", tempHead -> word);
    tempHead = tempHead -> next;
    afterFirstPrint = true;
  }
  afterFirstPrint = false;
}

