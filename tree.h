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
};

enum SIGN { _NUM, _AND, _OR, _NOT };

// make the new node of the tree which has sign, and prop
// the sign has 0 or 1 (0 : node is a atomic proposition, 1 : node is a statement 'and',
// 2 : node is a statement 'or', 3: node is a statement 'not' )
// the prop has a number of propositions (e.g : a1 has prop 1, a2 has prop 2)
struct Tree* newTree(int sign, int prop);

struct Tree* parseToTree(struct Tree* t);
void printTree(struct Tree* t);
struct Tree* doNot(struct Tree* t);
struct Tree* NNF(struct Tree* t);
struct Tree* distribute(struct Tree* t);
struct Tree* CNF(struct Tree* t);
struct Tree* copyTree(struct Tree* t);
void deleteAll(struct Tree* t);
void printAnswer(struct Tree*t);
int checkSyntax(char ss[]);