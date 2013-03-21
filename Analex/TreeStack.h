#ifndef TREESTACK H
#define TREESTACK H

#define TRUE 1
#define FALSE 0

#include "arbol.h"
	
typedef struct ElementoT{
	struct ElementoT *next;
	NodoArbol * arbol;
} ElementoT;					

int creaStackT(ElementoT **);
int delStackT(ElementoT **);
int pushT(ElementoT **,NodoArbol *);
int popT(ElementoT **,NodoArbol**);
int topT(ElementoT **,NodoArbol**);

#endif
