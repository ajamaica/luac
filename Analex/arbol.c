
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HIJOS 5

typedef struct NodoArbol{
    struct NodoArbol *hijos[5];
    int tipo;
    char* valor;
    int numHijos;
} NodoArbol;

int creaArbol(NodoArbol **arbol){
    *arbol = 0;
    return true;
}

int delArbol(NodoArbol **arbol){
    int i = 0;
    while ((*arbol)->hijos[i]!=NULL){
        delArbol(&((*arbol)->hijos[i]));
        i++;
    }
    free((*arbol)->valor);
    free((*arbol));
}

int creaHoja(NodoArbol **arbol, int tipo, char* valor){
    NodoArbol *new = malloc(sizeof(NodoArbol));
    if(!new) return FALSE;
    printf("-Se creo la hoja\n");
    new->tipo = tipo;
    new->valor = (char*)malloc(sizeof(char*)*20);
    printf("--Se asigno el tipo\n");
    strcpy(new->valor, valor);
    printf("STRCPY!!!!\n");
    new->numHijos = 0;
    for(int i = 0; i<5; i++){
        new->hijos[i] = NULL;
    }
    printf("-Se inicializaron los hijos nulos\n");
    *arbol = new;
    printf("-Se asigno\n");
    return TRUE;
}

int agregaHijo(NodoArbol **arbol, int tipo, char* valor){
    NodoArbol *new = malloc(sizeof(NodoArbol));
    if (!creaHoja(&new, tipo, valor)) return FALSE;
    printf("Cree hoja\n");
    (*arbol)->hijos[(*arbol)->numHijos] = new;
    printf("Asigne el hijo en el arreglo\n");
    ((*arbol)->numHijos)++;
    printf("Aumente el numero de hijos\n");
}

void printArbol(NodoArbol **arbol){
    printSubArbol(arbol, 0);
}

void printSubArbol(NodoArbol **arbol, int nivel){
    for(int i = 0; i< nivel; i++){
        printf("-");
    }
    printf("%s (%d)\n", (*arbol)->valor, (*arbol)->tipo);
    nivel++;
    for(int i = 0; i<(*arbol)->numHijos; i++){
        printSubArbol(&(*arbol)->hijos[i], nivel);
    }
}
