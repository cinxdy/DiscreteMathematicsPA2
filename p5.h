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

// Tree with only two pointers (left and right)
struct Tree{
    int sign; // 0 prop; 1 and; 2 or; 3 not;
    int prop;
    struct Tree *left;
    struct Tree *right;
};

// for the elements of Tree, sign
enum SIGN { _NUM, _AND, _OR, _NOT };

// make the new node of the tree which has sign, and prop
// the sign has 0 or 1 (0 : node is a atomic proposition, 1 : node is a statement 'and',
// 2 : node is a statement 'or', 3: node is a statement 'not' )
// the prop has a number of propositions (e.g : a1 has prop 1, a2 has prop 2)
struct Tree* newTree(int sign, int prop);

// get the input text, and translate the text to tree nodes.
struct Tree* parseToTree(struct Tree* t);

// print tree started from t
void printTree(struct Tree* t);

// change the node. 
// if the node is a statement node, change 'and' to 'or', 'or' to 'and', 'not' to 'no not'
// else if the node is a atomic proposition, change 'a1' to 'a-1'
struct Tree* doNot(struct Tree* t);

// make the tree to be NNF.
struct Tree* NNF(struct Tree* t);

// if the nodes is not 'and', execute distribution.
struct Tree* distribute(struct Tree* t);

// make the tree to be CNF.
struct Tree* CNF(struct Tree* t);

// make a new tree which has the nodes same as tree t.
// and return the new tree.
struct Tree* copyTree(struct Tree* t);

// delete all nodes of the tree t (all nodes connected to the node t)
void deleteAll(struct Tree* t);

// print the tree with Answer form. (you'd know what I mean)
void printAnswer(struct Tree*t);
