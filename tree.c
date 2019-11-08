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
int parseToTree(struct Tree* t);
void printTree(struct Tree* t);

#if 1
int main(){
    struct Tree* root = (struct Tree*) malloc(sizeof(struct Tree));

    if(parseToTree(root)){
        printf("success!\n");
    }
    else{
        printf("error!\n");
    }

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

int parseToTree(struct Tree* t){ // close the bracket or not  true: close; false: still open;
    DPrintf(printf("< parseToTree t=%p\n",t));
    char temp;
    char ss[MAX_STR];
    int sign=0;
    int prop=0;
    int success;

    scanf("%c",&temp);
    DPrintf(printf("-parseToTree temp=%c", temp););
    if(temp == '('){
        scanf("%s",ss);

        if(!strcmp(ss,"and")) sign = 1;
        else if(!strcmp(ss,"or"))  sign = 2;
        else if(!strcmp(ss,"not")) sign = 3;

        t = newTree(sign, prop);
        success = parseToTree(t->left);
        success = parseToTree(t->right);
        DPrintf(printf("< parseToTree t=%p\n",t));
        return success;
    }
    else{
        scanf("%s",ss);
        sign = 0;
        prop = ss[1] - '\0';
        t = newTree(sign, prop);
    }
    
    DPrintf(printf("< parseToTree t=%p\n",t));
    if(ss[strlen(ss)-1]==')') return 1;
    else return 0;
}

void printTree(struct Tree* t){
    DPrintf(printf("< printTree tree=%p, tree->left=%p, tree->right=%p\n", t, t->left, t->right););

    if(t == NULL) return ;

    if(t->sign == 0)
        printf(" %d", t->prop);
    else{
        if(t->sign == 1)
            printf("(and");
        else if(t->sign == 2)
            printf("(or");
        else if(t->sign == 3)
            printf("(not");
    }


    printTree(t->left);
    printTree(t->right);

    if(t->sign !=0)
        printf(")");

    DPrintf(printf("> printTree tree=%p\n",t););
}