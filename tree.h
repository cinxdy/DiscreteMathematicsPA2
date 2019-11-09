// tree.h

#ifndef TREE_H
    #define TREE_H
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR 128
#ifdef DEBUG
    #define DPrintf(f) f;
#else
    #define DPrintf(f) ;
#endif

struct Tree{
    int sign; // 0 prop; 1 and; 2 or; 3 not;
    int prop;
    struct Tree *left;
    struct Tree *right;
} ;

struct Tree* newTree(int sign, int prop);
struct Tree* parseToTree(struct Tree* t);
//int checkSyntax();
void printTree(struct Tree* t);
struct Tree* not(struct Tree* t);
struct Tree* NNF(struct Tree* t);
