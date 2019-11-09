// tree.c
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

#if 1
int main(){
    struct Tree* root = NULL;

    root = parseToTree(root);
    if(root == NULL)
        printf("error!\n");

    DPrintf(printf("root=%p \n",root););

    //DPrintf(printf("root=%p, root->left=%p, root->right=%p \n",root,root->left,root->right););

    printTree(root);
}
#endif

struct Tree* newTree(int sign, int prop){
    DPrintf(printf("< newTree sign=%d, prop=%d\n",sign,prop););
    struct Tree* t = (struct Tree*) malloc(sizeof(struct Tree));

    t->sign = sign;
    t->prop = prop;
    t->left = NULL;
    t->right = NULL;

    DPrintf(printf("> newTree=%p, sign=%d, prop=%d\n", t, sign,prop);
    printf("t=%p, t=%p, t=%p \n\n", t, t->left ,t->right););
    return t;
    
}

struct Tree* parseToTree(struct Tree* t){ // close the bracket or not  true: close; false: still open;
    DPrintf(printf("< parseToTree t=%p\n",t));
    char temp;
    char ss[MAX_STR];
    int sign=0;
    int prop=0;
    
    scanf("%s",ss);
    DPrintf(printf("-parseToTree temp=%c, ss=%s\n", temp, ss););

    if(ss[0] == '('){

        if(!strcmp(ss,"(and")) sign = 1;
        else if(!strcmp(ss,"(or"))  sign = 2;
        else if(!strcmp(ss,"(not")) sign = 3;

        t = newTree(sign, prop);
        t->left = parseToTree(t->left);
        if(sign != 3)
            t->right = parseToTree(t->right);
    }
    else{

        //if(ss[strlen(ss)-1]!=')') 
        //    return NULL;

        sign = 0;
        prop = ss[1] - '0';
        t = newTree(sign, prop);

    }

    DPrintf(printf("> parseToTree t=%p\n",t));
    
    return t;
}
/*
int checkSyntax(){
    DPrintf(printf("< checkSyntax\n"));

    int success;
    char temp;
    char ss[MAX_STR];

    scanf("%c",&temp);
    scanf("%s",ss);
    DPrintf(printf("- checkSyntax ss=%s\n",ss));

    if(temp == '('){
        
        success = checkSyntax();
        success = checkSyntax();
        
        return success;
    }

    if(ss[strlen(ss)-1]==')') success = 1;
    else success = 0;

    DPrintf(printf("> checkSyntax success=%d\n",success));
    return success;
}*/

void printTree(struct Tree* t){
    if(t == NULL) return ;
    DPrintf(printf("< printTree tree=%p, tree->left=%p, tree->right=%p\n", t, t->left, t->right););

    

    if(t->sign == 0)
        printf(" a%d", t->prop);
    else{
        if(t->sign == 1)
            printf(" (and");
        else if(t->sign == 2)
            printf(" (or");
        else if(t->sign == 3)
            printf(" (not");
    }

    printTree(t->left);
    printTree(t->right);

    if(t->sign !=0)
        printf(")");

    DPrintf(printf("> printTree tree=%p\n",t););
}