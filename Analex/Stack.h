#ifndef STACK H
#define STACK H

#define TRUE 1
#define FALSE 0
	
typedef struct Elemento{
	struct Elemento *next;
	int numero;
	char letra;
	char* valor;
} Elemento;					

int creaStack(Elemento **);
int delStack(Elemento **);
int push(Elemento **,int,char, char *);
int pop(Elemento **,int *,char *, char *);
int top(Elemento **,int *,char *, char *);

#endif
