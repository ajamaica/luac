#ifndef ARBOL H
#define ARBOL H

typedef struct NodoArbol{
    struct NodoArbol *hijos[5];
    int tipo;
    char* valor;
    int numHijos;
}NodoArbol;

int creaArbol(NodoArbol **);
int delArbol(NodoArbol **);
int creaHoja(NodoArbol **, int , char* );
int agregaHijoExistente(NodoArbol **, NodoArbol **);
int agregaHijo(NodoArbol **, int , char* );
void printSubArbol(NodoArbol **, int );
void printArbol(NodoArbol **);
#endif
