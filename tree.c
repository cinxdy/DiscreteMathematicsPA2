// tree.c

/* RED POINT
* 여러 파라미터일 때 elements 여러개
* checkCNF 구현한 뒤 CNF에 넣기
* checkSyntax 구현 // 괄호 문제가 아니라 아예 다른 인풋일 때에도 가능한 함수
* README.md 만들기
*/

#include "tree.h"

int check, open, close;

#if 1
int main(){
    struct Tree* root = NULL;

    // read input
    printf("input == ");
    root = parseToTree(root);
    if(root == NULL) printf("error!\n");

    // print read
    printf("read == ");
    printTree(root);
    printf("\n");

    // do NNF and print
    printf("NNF == ");
    root = NNF(root);
    printTree(root);
    printf("\n");

    // do CNF and print
    printf("CNF == ");
    root = CNF(root);
    printTree(root);

    printf("\n\n\n");

    // change form of the output
    printAnswer(root);

    DPrintf(printf("> main root=%p \n",root););
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
    //checkSyntax(ss);
    DPrintf(printf("- parseToTree temp=%c, ss=%s\n", temp, ss););

    if(ss[0] == '('){

        if(!strcmp(ss,"(and")) sign = _AND;
        else if(!strcmp(ss,"(or"))  sign = _OR;
        else if(!strcmp(ss,"(not")) sign = _NOT;

        t = newTree(sign, prop);
        t->left = parseToTree(t->left);
        if(sign != _NOT)
            t->right = parseToTree(t->right);
    }
    else{
        sign = _NUM;
        prop = ss[1] - '0';
        t = newTree(sign, prop);
    }

    DPrintf(printf("> parseToTree t=%p\n",t));
    return t;
}

void printTree(struct Tree* t){
    DPrintf(printf("< printTree tree=%p\n",t););
    if(t == NULL) return ;

    switch(t->sign){
        case _NUM: printf(" a%d", t->prop); break;
        case _AND: printf(" (and"); break;
        case _OR: printf(" (or");  break;
        case _NOT: printf(" (not"); break;
    }

    printTree(t->left);
    printTree(t->right);

    if(t->sign !=_NUM)
        printf(")");

    DPrintf(printf("> printTree tree=%p\n",t););
}

struct Tree* demorgan(struct Tree* t){
    DPrintf(printf("< demorgan tree=%p\n",t););

    if(t->sign == _NUM) t->prop *= -1;
    else if(t->sign == _AND || t->sign == _OR) {
        t->sign = 3- t->sign;
        t->left = demorgan(t->left);
        t->right = demorgan(t->right);
    }
    else if(t->sign == _NOT) t = t->left;
    
    DPrintf(printf("> demorgan tree=%p\n",t););
    return t;
}

struct Tree* NNF(struct Tree* t){
    DPrintf(printf("< NNF tree=%p\n",t););

    if(t == NULL){
        //printf("error! nullptr!\n");
        return t;
    }

    if(t->sign == _NOT){ // meet 'demorgan'
        t = demorgan(t->left);
    }
    else if(t->sign==_AND || t->sign==_OR){ // and || or
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

    if((t->left->sign == _NUM && t->right->sign == _NUM) || t == NULL){
        DPrintf(printf("> distribute tree t=%p\n",t););
        return t;
    }
    else if(t->left->sign == _NUM){
        p = t->right;
        t->right = NULL;

        pp = p->left;
        p->left = copyTree(t);
        p->left->right = pp;

        pp = p->right;
        p->right = copyTree(t);
        p->right->right = pp;

        deleteAll(t);
    }
    else {
        p = t->left;
        t->left = NULL;

        pp = p->left;
        p->left = copyTree(t);
        p->left->left = pp;

        pp = p->right;
        p->right = copyTree(t);
        p->right->left = pp;

        deleteAll(t); 
    }
    
    DPrintf(printf("> distribute tree p=%p\n",p););
    return p;
}

struct Tree* CNF(struct Tree* t){
    DPrintf(printf("< CNF tree=%p\n",t););

    if(t == NULL || t->sign == _NUM){
        //printf("error! nullptr!\n");
        return t;
    }

    if(t->sign == _OR){ // meet 'or'
        t = distribute(t);
        t->left = CNF(t->left);
        t->right = CNF(t->right);
    }
    else if(t->sign==_AND){ // if 'and'
        t->left = CNF(t->left);
        t->right = CNF(t->right);
    }

    DPrintf(printf("> CNF tree=%p\n",t););
    return t;
}

/*
int checkCNF(struct Tree* t){
    DPrintf(printf("< checkCNF tree=%p\n",t););
    int check;

    if(t == NULL || t->sign == 2) check = 0;
    else {
        check = 1;
    }
    
    DPrintf(printf("> checkCNF tree=%p\n",t););
}
*/

struct Tree* copyTree(struct Tree* t){
    DPrintf(printf("< copyTree tree=%p\n",t););

    if(t==NULL) return t;

    struct Tree* nt = newTree(t->sign,t->prop); // new tree
    nt->left = copyTree(t->left);
    nt->right = copyTree(t->right);

    DPrintf(printf("> copyTree tree=%p\n",nt););
    return nt;
}

void deleteAll(struct Tree* t){
    DPrintf(printf("< deleteTree tree=%p\n",t););

    if(t == NULL) return ;

    deleteAll(t->left);
    deleteAll(t->right);
    free(t);

    DPrintf(printf("> copyTree\n"););
}

/////ADDED/////

void printAnswer(struct Tree*t){
    DPrintf(printf("< printAnswer tree=%p",t););

    if(t == NULL) return ;
    
    switch(t->sign){
        case _NUM: printf("%d ", t->prop);
                printAnswer(t->left);
                printAnswer(t->right);
                break;
        case _AND: printAnswer(t->left);
                printf("\n");
                printAnswer(t->right);
                break;
        case _OR: printAnswer(t->left); 
                printf(" ");
                printAnswer(t->right);
                break;
        case _NOT: printf("-");
                printAnswer(t->left);
                printAnswer(t->right);
                break;
        default: break;
    }

    DPrintf(printf("> printAnswer tree=%p",t););
}

int checkSyntax(char ss[]){
    for(int i=0 ; i<strlen(ss) ; i++) {
        if(ss[i]=='(')  open++;
        if(ss[i]==')')  close++;
        if(!(ss[i]==' ' || ss[i]=='\0' || (48<=ss[i] && ss[i]<=57) || ss[i]==40 || ss[i]==41 || ss[i]==97 || ss[i]==100 || ss[i]==110 || ss[i]==111 || ss[i]==116 || ss[i]==114)){
            check=1;
            // printf("%c\n", ss[i]);
        }
    }
    return check;
}