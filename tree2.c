#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
typedef struct Tree{
    Element e;
    int cmd; // 0:leaf nood 1:or, 2:and, 3:not
    struct Tree *left, *right;
}TREE
*/

int here=0;
int N;
char str[1001];

typedef struct Element{
   int sign;      //not 구분
   char name[11];
}Element;

typedef struct Tree{
   Element *element;
}Tree;

Element* makeElement() {
   Element *e = (Element *)malloc(sizeof(Element));
   int idx = 0;
   while (str[here+idx] != ' ' || str[here+idx] != '\n' || str[here] != ')') {   //뛰어 넘기
      e->name[idx] = str[here+idx];
      idx++;
   }
   e->sign = 1;
   here = here + idx;
   if (str[here+idx] == ')') here = here+1;

   return e;
}

Tree* orTree(Tree *a, Tree *b) {
   return 0;
}

Tree* andTree(Tree *a, Tree *b) {
   return 0;
}

Tree* notTree(Tree *a) {
   return 0;
}



Tree* makeTree() {
   if (str[here] == '\n' || str[here] == '\0') return NULL;
   if (str[here] == ' ') {
      here++;
      return makeTree();
   }

   Tree *c = (Tree*)malloc(sizeof(Tree));
   Tree *a, *b;
   if (str[here] == '(') {
      if (str[here+1] == 'o') { // or
         here=here+3;
         a = makeTree();
         b = makeTree();
         c = orTree(a,b);
      }
      else if (str[here+1] == 'a') { // and
         here=here+4;
         a = makeTree();
         b = makeTree();
         c = andTree(a,b);
      }
      else if (str[here+1] == 'n') { // not
         here=here+4;
         a = makeTree();
         c = notTree(a);
      }
   } else { // component
         Element *e = makeElement();
         c->element = e;
   }
   return c;
}

int main() {
   fgets(str, 1001, stdin);
   int slen = (int)strlen(str);
   Tree *root = makeTree();
   return 0;
}