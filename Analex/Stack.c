
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

int creaStack(Elemento **stack){
	*stack = 0;
	return TRUE;
}

int delStack(Elemento **stack){
	Elemento *next = 0;
	while(*stack){
		next = (*stack)->next;
		free(*stack);
		*stack = next;
	}
	return TRUE;
}

int push(Elemento **stack, int numero, char letra){
	Elemento *new = malloc(sizeof(Elemento));
	if(!new) return FALSE;
	new->numero = numero;
	new->letra = letra;
	new->next = *stack;
	*stack = new;
	return TRUE;
}

int pop(Elemento **stack, int * numero, char * letra){
	Elemento *elemento;
	if(!(elemento=*stack)) return FALSE;
	*numero = elemento->numero;
	*letra = elemento->letra;
	*stack = elemento->next;
	free(elemento);
	return TRUE;
}

int top(Elemento **stack, int * numero, char * letra){
	Elemento *elemento;
	if(!(elemento=*stack)) return FALSE;
	*numero = elemento->numero;
	*letra = elemento->letra;
	return TRUE;
}

void printRec(Elemento * elem){
	if(!elem) return;
	if(elem->next){
		printRec(elem->next);
	}
	printf("|l-%d n-%i|",elem->letra,elem->numero);
}

void printStack(Elemento ** stack){
	if(!stack) return;
	printRec(*stack);
	printf("\n");
}
