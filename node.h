/*
  Brett Bax
  CS4280
  Project 0
  2/14/2022

*/


#ifndef NODE_H
#define NODE_H

typedef struct head {
    struct head *next;
    char *word;
} nodeHead;

/* derived in part from: https://www.geeksforgeeks.org/ternary-search-tree/ */
typedef struct node{
    char lastLetter;
    struct node *left, *right, *middle;
    struct node *next;
    struct head* head;
    unsigned stringEnd: 1;

} node_t;

#endif