#ifndef ARBOL_H
#define ARBOL_H

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

void printSubArbol2(NodoArbol **, int );
void printArbol2(NodoArbol **);

#endif
