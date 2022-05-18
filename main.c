/*  
    Author: Brett Bax
    Class: CS4280
    Date Due: 2/14/2022
    Assignment: Project 0
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "node.h"
#include "tree.h"


int main(int argc, char* argv[]) {

    FILE* fp = NULL;
    node_t* rootP = NULL;
    
    /* input buffer and file extensions */
    char buffer[200];
    char spExt[7] = ".sp2022";
    char inExt[8] = ".inorder";
    char preExt[9] = ".preorder";
    char postExt[10] = ".postorder";

    /* pointers for infile and outputfiles */
    char *preorder = NULL;
    char *postorder = NULL;
    char *inorder = NULL;
    char *infile = NULL;

    if(argc == 0 || argc >= 4){

        printf("main.c: Invalid Input. Killing program.");
        exit(1);

    }else if(argc == 1) {
       /*           if "./P0"           */
        printf("Input Text:\n");
        fgets(buffer, 200, stdin);

        fp = fopen("output", "a");
        fputs(buffer, fp);
        fclose(fp);

        fp = fopen("output", "r");

        inorder = mallocFp(inorder, "output", inExt, 1);
        preorder = mallocFp(preorder, "output", preExt, 2);
        postorder = mallocFp(postorder, "output", postExt, 3);

        rootP = buildTree(fp);
        fclose(fp);

    } else if(argc == 2){
        /*       "./P0 test"          */
        infile = mallocFp(infile, argv[1], spExt, 4);
        fp = fopen(infile, "r");

        /* Below if statement courtesy of: https://stackoverflow.com/questions/13566082/how-to-check-if-a-file-has-content-or-not-using-c */
        if ( fp != NULL ) {
            fseek(fp, 0, SEEK_END);
            int size = ftell(fp);
            if (size == 0) {
                printf( "Error: Source file empty\n");
                exit(1);
            } 
        }

        inorder = mallocFp(inorder, argv[1], inExt, 1);
        preorder = mallocFp(preorder, argv[1], preExt, 2);
        postorder = mallocFp(postorder, argv[1], postExt, 3);

        rootP = buildTree(fp);
        fclose(fp);

    } else {
        /*        "./P0 w text.sp2022"          */
        printf("Input text: \n");
        fgets(buffer, 200, stdin);
        fp = fopen(argv[2], "a");
        fputs(buffer, fp);
        fclose(fp);
        fp = fopen(argv[2], "r");

        inorder = mallocFp(inorder, "output", inExt, 1);
        preorder = mallocFp(preorder, "output", preExt, 2);
        postorder = mallocFp(postorder, "output", postExt, 3);

        rootP = buildTree(fp);
        fclose(fp);
    }
    
    /* traversals and printing trees */
    sendToInorderFile(fp, rootP, inorder, buffer);
    sendToPreorderFile(fp, rootP, preorder, buffer);
    sendToPostorderFile(fp, rootP, postorder, buffer);

    /* freeing allocated memory */
    free(infile);
    free(inorder);
    free(preorder);
    free(postorder);

    return 0;
}
