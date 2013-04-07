//
//  anasin.c
//  Analizador Lexico
//
//  Created by Brounie on 17/02/13.
//
//

#include <stdio.h>
#include "anasin.h"
#include "analex.h"
#include "Stack.h"
#include "TreeStack.h"
#include "List.h"
#include "tablasim.h"
#include "arbol.h"


FILE * fp;
Elemento ** stack;
StackArbol nodosHuerfanos;


int numero;
char letra;
simbolo * tabla_de_simbolos;


int main (int argc, const char * argv[]) {
    
    
    
    NodoArbol** arbol;
    /*
    creaHoja(arbol, 1, "Hola");
    printArbol(arbol);
    agregaHijo(arbol, 1, "Hoja1");
    printArbol(arbol);
    agregaHijo(arbol, 1, "Hoja2");
    printArbol(arbol);
    agregaHijo(arbol, 1, "Hoja3");
    printArbol(arbol);
    agregaHijo(arbol, 1, "Hoja4");
    printArbol(arbol);
    agregaHijo(arbol, 1, "Hoja5");
    printArbol(arbol);
    agregaHijo(&(*arbol)->hijos[1], 1, "Hoja1");
    printArbol(arbol);
    agregaHijo(&(*arbol)->hijos[1], 1, "Hoja2");
    printArbol(arbol);*/

    
    stack = malloc(sizeof(Elemento*));
    initializeT(&nodosHuerfanos);
    tabla_de_simbolos = (simbolo *) malloc(sizeof(simbolo));

    
    tabla_de_simbolos = Analex(tabla_de_simbolos);
    
	
    printf("------- ANASIN -------\n");
    
    
    fp = fopen("lexemas.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    char * line = (char *) malloc(100);
    size_t len = 100;
    size_t read;
    
    
    
    
    
    while ((read = getline(&line, &len, fp)) != -1) {
        
        add_to_list(line,true);
     
    }
    
    
    
    
    
    /*
    add_to_list("(\n",true);
    add_to_list("(\n",true);
    
    add_to_list("(\n",true);
    add_to_list("(\n",true);
    
    add_to_list("a\n",true);
    add_to_list("a\n",true);
    
    add_to_list(")\n",true);
    add_to_list(")\n",true);
    
    add_to_list(")\n",true);
    add_to_list(")\n",true);
    
    add_to_list("$\n",true);
    add_to_list("$\n",true);
    */
    
    Anasin();
    
}

int ok(){
    
    printf("LO LOGRAMOS!!!!! MERECEMOS UNA CERVEZA.");
    exit(0);
}

int r(){
    printStack(stack);
    int numerodestack;
    char chardestack;
    
    char *loqueleodelafila = get_second();
    int tipo_de_reduccion = matrizvalores[numero][index_of(loqueleodelafila)];
    printf("Reduccion %d\n\n", tipo_de_reduccion);
    int i = 0;
    
    while (reduccciones[tipo_de_reduccion][i] != -1) {
        i++;
    }
    
    i--;
    int j;
    for (j = i; j> 0; j--) {
        
        
        
        top(stack, &numerodestack, &chardestack);
            
        int numeroquerelacionaelcharconlareduccion = reduccciones[tipo_de_reduccion][j];
       
        if(chardestack == numeroquerelacionaelcharconlareduccion ){
            pop(stack, &numerodestack, &chardestack);
        }else{
            printf("Error en Reduccion %d", tipo_de_reduccion);
            exit(0);
        }
    }
    
    top(stack, &numerodestack, &chardestack);
    
    int loquevoyameter = matrizvalores[numerodestack][reduccciones[tipo_de_reduccion][j]];

    
    
    push(stack, loquevoyameter, reduccciones[tipo_de_reduccion][j]);
    printStack(stack);
    //nuevoArbol es la raiz que se crea en cada reduccion
    NodoArbol ** nuevoArbol;
    nuevoArbol = (NodoArbol**) malloc(sizeof(NodoArbol*));
    //arbolDePila es el arbol que sale de la pila y se va a convertir en una hoja de nuevoArbol
    NodoArbol * arbolDePila;
    
    switch(tipo_de_reduccion){
            /*case 0: //CHUNK -> BLOCK
             creaHoja(nuevoArbol, 1, "CHUNK");
             pop(nodosHuerfanos,&direccion,&basura);
             agregaHojaExistente(nuevoArbol, direccion);
             break;*/
         case 9: //  T -> F
             printf("Accion semantica 9\n");
             printf("+++++++\n");
             printT(&nodosHuerfanos);
             creaHoja(nuevoArbol, 1, "T");
             printf("+++++++\n");
             printT(&nodosHuerfanos);
             printf("Creamos arbol con T\n");
             printArbol(nuevoArbol);
             printf("Pila:\n");
             printT(&nodosHuerfanos);
             arbolDePila = popT(&nodosHuerfanos);
             printf("Sacamos un arbol de la pila\n");
             printArbol(&arbolDePila);
             agregaHijoExistente(nuevoArbol, &arbolDePila);
             pushT(*nuevoArbol, &nodosHuerfanos);
             printT(&nodosHuerfanos);
             
             break;
             
        case 11:
            printf("Accion semantica 11\n");
            creaHoja(nuevoArbol, 0, "F");
            printf("Creamos arbol con F\n");
            printArbol(nuevoArbol);
            pushT(*nuevoArbol, &nodosHuerfanos);
            printf("Agregamos arbol al stack\n");
            printf("Pila:\n");
            printT(&nodosHuerfanos);
            break;
             
    }
    
    
     
    return 0;
}

int d(){
    
    
    pop_first();
    char *rgreso = pop_first();
    printf("Desplazamiento %d\n",matrizvalores[numero][index_of(rgreso)]);
    if(rgreso != NULL){
        push(stack, matrizvalores[numero][index_of(rgreso)], index_of(rgreso));
        return 0;
    }
    exit(0);
    return 1;
}

int i(){
    //pop_first();
    char *rgreso = get_second();
    if(rgreso != NULL){
        printf("%s",rgreso);
        push(stack,matrizvalores[numero][letra],index_of(rgreso));
        printf("%i , %i \n",numero, letra);
        return 0;
    }
    return 1;
}

int f0(){
    // DUMMY FUNCTION
    return 1;
}

int e(){
    printf("Error! Panico!\n");
    exit(0);
    return 1;
}



int Anasin(){
    
    
    
    
    
    fp = fopen("lexemas.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    /*
    while ((read = getline(&line, &len, fp)) != -1) {
        
        printf("%s", line);
        
    }
     */
    
    /* Creamos METEMOS $ y 1)*/
    
    
    creaStack(stack);
	
    
   
    
    
    //char* leido = get_first();
    //print_list();
    
    push(stack,0,index_of("$\n"));
    
    
    while(1){
        top(stack,&numero,&letra);
        char *loqueleodelafila = get_second();
        printStack(stack);
        printf("%s\n", loqueleodelafila);
        printf("%s, %d\n", loqueleodelafila, index_of(loqueleodelafila));
        matriz[numero][index_of(loqueleodelafila)]();
        //matriz[0][0]();
        
        
    }
        
    
    fclose(fp);
    return 0;
}




char leerAnalex(){
    
    char * lexema = (char *) malloc(100);
    char * tipo = (char *) malloc(100);
    size_t len = 100;
    
    getline(&lexema, &len, fp);
    
    //QUE HACER CON LO QUE LEA

    getline(&tipo, &len, fp);
    
    
    int dondeesta = index_of(tipo);
  
    return (char *) dondeesta;
}


int index_of(char *string){
    for (int i = 0; i< TERMINALESYNOTERMINALES; i++) {
        if(strcmp(uses[i], string) == 0){
            return i;
        }
    }
    return -1;
}
