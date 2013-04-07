#ifndef TREESTACK_H
#define TREESTACK_H

#define TRUE 1
#define FALSE 0

#include "arbol.h"
	
struct StackRec 
{
    NodoArbol * arbol;
    struct StackRec *next;
};

typedef struct StackRec *StackArbol;
				

void initializeT(StackArbol *);
int emptyT(StackArbol);
void pushT(NodoArbol * , StackArbol *);
NodoArbol* popT(StackArbol *);
void printT(StackArbol *);

#endif
