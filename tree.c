// tree.c

#include "tree.h"

#if 1
int main(){
    struct Tree* root = NULL;

    printf("input == ");
    
    root = parseToTree(root);
    if(root == NULL)
        printf("error!\n");

    printf("read == ");
    printTree(root);
    printf("\n");

    
    printf("NNF == ");
    root = NNF(root);
    printTree(root);
    printf("\n");

    
    printf("CNF == ");
    root = CNF(root);
    printTree(root);

    printf("\n\n\n");

    DPrintf(printf("root=%p \n",root););

    //DPrintf(printf("root=%p, root->left=%p, root->right=%p \n",root,root->left,root->right););
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

struct Tree* parseToTree(struct Tree* t){ // close the bracket or demorgan  true: close; false: still open;
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

    switch(t->sign){
        case 0: printf(" a%d", t->prop); break;
        case 1: printf(" (and"); break;
        case 2: printf(" (or");  break;
        case 3: printf(" (not"); break;
    }


    printTree(t->left);
    printTree(t->right);

    if(t->sign !=0)
        printf(")");

    DPrintf(printf("> printTree tree=%p\n",t););
}

struct Tree* demorgan(struct Tree* t){
    DPrintf(printf("< demorgan tree=%p\n",t););

    if(t->sign == 0) t->prop *= -1;
    else if(t->sign == 1 || t->sign == 2) {
        t->sign = 3- t->sign;
        t->left = demorgan(t->left);
        t->right = demorgan(t->right);
    }
    else if(t->sign == 3) t = t->left;
    
    return t;
    DPrintf(printf("> demorgan tree=%p\n",t););
}

struct Tree* NNF(struct Tree* t){
    DPrintf(printf("< NNF tree=%p\n",t););

    if(t == NULL){
        //printf("error! nullptr!\n");
        return t;
    }

    if(t->sign == 3){ // meet 'demorgan'
        t = demorgan(t->left);
    }
    else if(t->sign==1 || t->sign==2){ // and || or
        t->left = NNF(t->left);
        t->right = NNF(t->right);
    }

    DPrintf(printf("> NNF tree=%p\n",t););
    return t;
}

struct Tree* distribute(struct Tree* t){
    DPrintf(printf("< distribute tree=%p\n",t););
    struct Tree* p = NULL;
    struct Tree* pp = NULL;


    if(t->left->sign == 0 && t->right->sign == 0){
        return t;
    }
    else if(t->right->sign != 0){
        p = t->right;
        t->right = NULL;

        pp = p->left;
        p->left = copyTree(t);
        p->left->right = pp;

        pp = p->right;
        p->right = copyTree(t);
        p->right->right = pp;

        deleteAll(t);

        return p;
    }
    else if(t->left->sign != 0){
        p = t->left;
        t->left = NULL;

        pp = p->right;
        p->right = copyTree(t);
        p->right->left = pp;

        pp = p->left;
        p->left = copyTree(t);
        p->left->right = pp;

        deleteAll(t);

        return p;
    }
    
    return t;
    DPrintf(printf("> distribute tree=%p\n",t););
}

struct Tree* CNF(struct Tree* t){
    DPrintf(printf("< CNF tree=%p\n",t););

    if(t == NULL || t->sign == 0){
        //printf("error! nullptr!\n");
        return t;
    }

    if(t->sign == 2){ // meet 'or'
        t = distribute(t);
        //t = CNF(t);
    }
    else if(t->sign==1){ // if 'and'
        t->left = CNF(t->left);
        t->right = CNF(t->right);
    }

    return t;

    DPrintf(printf("> CNF tree=%p\n",t););
}

struct Tree* copyTree(struct Tree* t){
    if(t==NULL) return t;

    struct Tree* nt = newTree(t->sign,t->prop);
    nt->left = copyTree(t->left);
    nt->right = copyTree(t->right);
    return nt;
}

void deleteAll(struct Tree* t){
    if(t == NULL) return ;

    deleteAll(t->left);
    deleteAll(t->right);
    free(t);
}