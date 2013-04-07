#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"


#define TRUE 1
#define FALSE 0
#define HIJOS 5
//0 = hoja, 1 = nodo



int creaArbol(NodoArbol **arbol){
    *arbol = 0;
    return TRUE;
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
    NodoArbol *new = (NodoArbol *) malloc(sizeof(NodoArbol));
    if(!new) return FALSE;
    new->tipo = tipo;
    new->valor = (char*)malloc(sizeof(char*)*20);
    
    strcpy(new->valor, valor);
    new->numHijos = 0;

    for(int i = 0; i<5; i++){
        new->hijos[i] = NULL;
    }

    *arbol = new;
    return TRUE;
}

int agregaHijoExistente(NodoArbol **arbol, NodoArbol **hijo){
    (*arbol)->hijos[(*arbol)->numHijos] = (*hijo);
    ((*arbol)->numHijos)++;
}

int agregaHijo(NodoArbol **arbol, int tipo, char* valor){
    NodoArbol *new = malloc(sizeof(NodoArbol));
    if (!creaHoja(&new, tipo, valor)) return FALSE;
    (*arbol)->hijos[(*arbol)->numHijos] = new;
    ((*arbol)->numHijos)++;
    return TRUE;

}

void printSubArbol(NodoArbol **arbol, int nivel){
    for(int i = 0; i< nivel; i++){
        printf("-");
    }
    printf("%s (%d)\n", (*arbol)->valor, (*arbol)->tipo);
    nivel++;
    for(int i = 0; i<((*arbol)->numHijos); i++){
        printSubArbol(&(*arbol)->hijos[i], nivel);
    }
}
void printArbol(NodoArbol **arbol){
    printSubArbol(arbol, 0);
}

