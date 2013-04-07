





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TreeStack.h"




void initializeT(StackArbol *stack)
{
    *stack = NULL;
}

int emptyT(StackArbol stack)
{
    return stack == NULL;
}

void pushT(NodoArbol ** arbol, StackArbol *stack)
{
    StackArbol tmp = (StackArbol) malloc(sizeof(struct StackRec));
    
    if(tmp == NULL)
    {
        printf("Overflow de memoria en el stack\n");
    }
    else
    {
        tmp -> arbol = arbol;
        tmp -> next = *stack;
        *stack = tmp;
    }

}

NodoArbol** popT(StackArbol *stack)
{
    if(*stack == NULL)
    {
        printf("Underflow de memoria en el stack\n");
    }
    else
    {
        StackArbol tmp = *stack;
        NodoArbol ** arbol = (*stack)->arbol;
        *stack = (*stack)->next;
        free(tmp);
        return arbol;
    }
}

void printT(StackArbol *stack)
{
    if(*stack == NULL)
    {
        printf("Underflow de memoria en el stack\n");
    }
    else
    {
        StackArbol tmp = *stack;
        while(!emptyT(tmp))
        {
            NodoArbol ** arbol = tmp->arbol;
            printArbol(arbol);     
            tmp = tmp->next;
        }
    }
}
/*
int creaStackT(ElementoT **stack){
	*stack = 0;
	return TRUE;
}

int delStackT(ElementoT **stack){
	ElementoT *next = 0;
	while(*stack){
		next = (*stack)->next;
		free(*stack);
		*stack = next;
	}
	return TRUE;
}

int pushT(ElementoT **stack, NodoArbol * arbol){
	ElementoT *new = malloc(sizeof(ElementoT));
	if(!new) return FALSE;
	new->arbol = arbol;
	new->next = *stack;
	*stack = new;
	return TRUE;
}



int topT(ElementoT **stack, NodoArbol ** arbol){
	ElementoT *elementoT;
	if(!(elementoT=*stack)) return FALSE;
	*arbol = elementoT->arbol;
	return TRUE;
}

void printRecT(ElementoT * elem){
	if(!elem) return;
	if(elem->next){
		printRecT(elem->next);
	}
	printArbol(&(elem->arbol));
}

void printStackT(ElementoT ** stack){
	if(!stack) return;
	printRecT(*stack);
	printf("\n");
}

int popT(ElementoT **stack, NodoArbol ** arbol){
printf("pop\n");
	ElementoT *elementoT;
	if(!(elementoT=*stack)) return FALSE;
	*stack = elementoT->next;
	*arbol = (elementoT->arbol);
    printf("sacando \n");
    printArbol(arbol);
    printf("de \n");
	printStackT(&elementoT);
	//free(ElementoT);
	return TRUE;
}
*/
