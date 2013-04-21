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

StackArbol ASTstack;

int numero;
char letra;
simbolo tabla_de_simbolos;


int main (int argc, const char * argv[]) {
    
    
    
    NodoArbol** arbol;
    
    
    stack = malloc(sizeof(Elemento*));
    initializeT(&nodosHuerfanos);
    initializeT(&ASTstack);
    
    
    tabla_de_simbolos = Analex();
    imprimir(&tabla_de_simbolos);
	
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
    
    
    Anasin();
}

int ok(){
    
    printf("LO LOGRAMOS!!!!! MERECEMOS UNA CERVEZA.");
    imprimir(&tabla_de_simbolos);
    exit(0);
}

int r(){
    printStack(stack);
    simbolo * amodificar;
    int numerodestack;
    char chardestack;
    char * valordestack = (char*)malloc(sizeof(char)*100);
    char * valorsignificativo;
    
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
        
        
        
        top(stack, &numerodestack, &chardestack, valordestack);
        
        int numeroquerelacionaelcharconlareduccion = reduccciones[tipo_de_reduccion][j];
        
        if(chardestack == numeroquerelacionaelcharconlareduccion ){
            pop(stack, &numerodestack, &chardestack, valordestack);
            if(chardestack == 1 || (chardestack >= 6 && chardestack <= 8))
            {
                valorsignificativo = (char*)malloc(sizeof(valordestack));
                strcpy(valorsignificativo, valordestack);
            }
        }else{
            printf("Error en Reduccion %d", tipo_de_reduccion);
            exit(0);
        }
    }
    top(stack, &numerodestack, &chardestack, valordestack);
    int loquevoyameter = matrizvalores[numerodestack][reduccciones[tipo_de_reduccion][j]];
    
    
    
    push(stack, loquevoyameter, reduccciones[tipo_de_reduccion][j], "");
    printStack(stack);
    //nuevoArbol es la raiz que se crea en cada reduccion
    NodoArbol ** nuevoArbol;
    NodoArbol ** hojaAux;
    NodoArbol ** ASTArbol;
    nuevoArbol = (NodoArbol**) malloc(sizeof(NodoArbol*));
    ASTArbol = (NodoArbol**) malloc(sizeof(NodoArbol*));
    
    //arbolDePila es el arbol que sale de la pila y se va a convertir en una hoja de nuevoArbol
    NodoArbol * arbolDePila;

    
    switch(tipo_de_reduccion){
        case 0: //CHUNK -> BLOCK
            creaHoja(nuevoArbol, 1, "CHUNK");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            break;
        case 1: //BLOCK -> SCOPE STATLIST
            printf("Accion semantica 5\n");
            creaHoja(nuevoArbol, 1, "BLOCK");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol,1,"BLOCK");
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,&arbolDePila);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,&arbolDePila);
            pushT(*ASTArbol,&ASTstack);
            
            break;
        case 2: //BLOCK -> SCOPE STATLIST LASTSTAT SEMI
            printf("Accion semantica 2\n");
            creaHoja(nuevoArbol, 1, "BLOCK");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            
            creaHoja(ASTArbol,1,"BLOCK");
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,arbolDePila);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,arbolDePila);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,arbolDePila);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,arbolDePila);
            pushT(*ASTArbol,&ASTstack);
            //Me lo salto por sanidad mental
            
            break;
        case 3: //SEMI -> ;
            printf("Accion semantica 3\n");
            creaHoja(nuevoArbol, 1, "SEMI");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, ";");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol,0,";");
            pushT(*ASTArbol,&ASTstack);
            break;
        case 4: //SEMI -> epsilon
            printf("Accion semantica 4\n");
            creaHoja(nuevoArbol, 1, "SEMI");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "epsilon");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol,0,"epsilon");
            pushT(*ASTArbol,&ASTstack);
            break;
        case 5: //SCOPE -> SCOPE STATLIST BINDING SEMI
            printf("Accion semantica 5\n");
            creaHoja(nuevoArbol, 1, "SCOPE");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol,1,"BLOCK");
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,&arbolDePila);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,&arbolDePila);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,&arbolDePila);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,&arbolDePila);
            pushT(*ASTArbol,&ASTstack);
            
            break;
        case 6: //SCOPE -> epsilon
            printf("Accion semantica 6\n");
            creaHoja(nuevoArbol, 1, "SCOPE");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "epsilon");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol,0,"epsilon");
            pushT(*ASTArbol,&ASTstack);
            
            break;
        case 7: //EXP -> EXP binop T ++++++
            printf("Accion semantica 7\n");
            creaHoja(nuevoArbol, 1, "EXP");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "binop");
            printf("Simbolo: %s\n",valorsignificativo);
            agregaHijoExistente(nuevoArbol, hojaAux);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            
            creaHoja(ASTArbol, 1, valorsignificativo);
            
            // Lado Izquierdo
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol, &arbolDePila);
            
             // Lado Derecho
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol, &arbolDePila);

            
            pushT(*ASTArbol, &ASTstack);
            

            
            break;
        case 8: //  EXP -> T
            printf("Accion semantica 8");
            creaHoja(nuevoArbol, 1, "EXP");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            break;
        case 9: //  T -> F
            printf("Accion semantica 9\n");
            creaHoja(nuevoArbol, 1, "T");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            break;
        case 10: // F -> ( EXP )
            printf("Accion semantica 10\n");
            creaHoja(nuevoArbol, 0, "F");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "(");
            agregaHijoExistente(nuevoArbol, hojaAux);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, ")");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            break;
        case 11: // F -> True +++++
            printf("Accion semantica 11\n");
            creaHoja(nuevoArbol, 0, "F");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "true");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol, 0, "true");
            pushT(*ASTArbol, &ASTstack);
            break;
        case 12: // F -> False +++++
            printf("Accion semantica 12\n");
            creaHoja(nuevoArbol, 0, "F");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "false");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol, 0, "false");
            pushT(*ASTArbol, &ASTstack);
            break;
        case 13: // F -> numer +++++
            printf("Accion semantica 13\n");
            creaHoja(nuevoArbol, 0, "F");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "numer");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol, 0, valorsignificativo);
            pushT(*ASTArbol, &ASTstack);
            
            break;
        case 14: // F -> string +++++
            printf("Accion semantica 14\n");
            creaHoja(nuevoArbol, 0, "F");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "string");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol, 0, valorsignificativo);
            pushT(*ASTArbol, &ASTstack);
            break;
        case 15: // F -> id +++++0000000
            printf("Accion semantica 15\n");
            creaHoja(nuevoArbol, 0, "F");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "id");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol, 0, valorsignificativo);
            pushT(*ASTArbol, &ASTstack);
            break;
        case 16: // STATLIST -> STATLIST STAT SEMI
            printf("Accion semantica 16\n");
            creaHoja(nuevoArbol, 1, "STATLIST");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol,1,"STATLIST");
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,&arbolDePila);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,&arbolDePila);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol,&arbolDePila);
            pushT(*ASTArbol,&ASTstack);
            
            break;
        case 17: // STATLIST -> epsilon
            printf("Accion semantica 6\n");
            creaHoja(nuevoArbol, 1, "STATLIST");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "epsilon");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol, 0, "epsilon");
            pushT(*ASTArbol, &ASTstack);
            
            break;
        case 18: // STAT -> while EXP do BLOCK end
            printf("Accion semantica 18\n");
            creaHoja(nuevoArbol, 1, "STAT");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "end");
            agregaHijoExistente(nuevoArbol, hojaAux);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "do");
            agregaHijoExistente(nuevoArbol, hojaAux);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "while");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol,1,"while");
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol, &arbolDePila);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol, &arbolDePila);
            pushT(*ASTArbol,&ASTstack);
            break;
        case 19: // STAT -> if CONDS end
            printf("Accion semantica 19\n");
            creaHoja(nuevoArbol, 1, "STAT");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "if");
            agregaHijoExistente(nuevoArbol, hojaAux);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            //CHECAR
            creaHoja(ASTArbol,1,"if");
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol, &arbolDePila);
            pushT(*ASTArbol, &ASTstack);
            
            
            NodoArbol * arbolDePilaAux;
            NodoArbol * aux2;
            arbolDePila = popT(&ASTstack);
            arbolDePilaAux = aux2 = popT(&ASTstack);
            while(!strcmp(aux2->valor,"if")&&aux2->numHijos==3)
            {
                aux2 = aux2->hijos[(aux2->numHijos)-1];
            }
            printf("Termino el ciclo\n");
            //aux2 = aux2->hijos[0];
            agregaHijoExistente(&aux2,&arbolDePila);
            printf("1\n");
            pushT(arbolDePilaAux,&ASTstack);
            printf("2\n");
            break;
        case 20: // CONDS -> CONDLIST
            printf("Accion semantica 20\n");
            creaHoja(nuevoArbol, 1, "CONDS");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            break;
        case 21: // CONDS -> CONDLIST else BLOCK
            printf("Accion semantica 21\n");
            creaHoja(nuevoArbol, 1, "CONDS");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "else");
            agregaHijoExistente(nuevoArbol, hojaAux);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            
           
           
            arbolDePila = popT(&ASTstack);
            *ASTArbol = popT(&ASTstack);
            pushT(*ASTArbol, &ASTstack);
            pushT(arbolDePila, &ASTstack);
            
            break;
        case 22: // CONDLIST -> COND
            printf("Accion semantica 22\n");
            creaHoja(nuevoArbol, 1, "CONDLIST");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            break;
        case 23: // CONDLIST -> CONDLIST elseif COND
            printf("Accion semantica 23\n");
            creaHoja(nuevoArbol, 1, "CONDLIST");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "elseif");
            agregaHijoExistente(nuevoArbol, hojaAux);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            //creaHoja(ASTArbol,1,"elseif");
            arbolDePila = popT(&ASTstack);
            *ASTArbol = popT(&ASTstack);
            agregaHijoExistente(ASTArbol, &arbolDePila);
            pushT(*ASTArbol, &ASTstack);
            
            break;
        case 24: // COND -> EXP then BLOCK
            printf("Accion semantica 24\n");
            creaHoja(nuevoArbol, 1, "COND");
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "then");
            agregaHijoExistente(nuevoArbol, hojaAux);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol,1,"if");
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol, &arbolDePila);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol, &arbolDePila);
            pushT(*ASTArbol, &ASTstack);
            
            break;
        case 25: // LASTSTAT -> return EXP
            printf("Accion semantica 25\n");
            creaHoja(nuevoArbol, 1, "LASTSTAT");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "return");
            agregaHijoExistente(nuevoArbol, hojaAux);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            break;
        case 26: // BINDING -> local id
            printf("Accion semantica 26\n");
            creaHoja(nuevoArbol, 1, "BINDING");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "local");
            agregaHijoExistente(nuevoArbol, hojaAux);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "id");
            agregaHijoExistente(nuevoArbol, hojaAux);
            pushT(*nuevoArbol, &nodosHuerfanos);
            amodificar = search(valorsignificativo, &tabla_de_simbolos);
            amodificar->alcance = 1;
            //imprimir(&tabla_de_simbolos);
            break;
        case 27: // BINDING -> local id = EXP
            printf("Accion semantica 27\n");
            creaHoja(nuevoArbol, 1, "BINDING");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "local");
            agregaHijoExistente(nuevoArbol, hojaAux);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "id");
            agregaHijoExistente(nuevoArbol, hojaAux);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "=");
            agregaHijoExistente(nuevoArbol, hojaAux);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol,1,"=");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, valorsignificativo);
            agregaHijoExistente(ASTArbol, hojaAux);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol, &arbolDePila);
            pushT(*ASTArbol, &ASTstack);
            
            
            amodificar = search(valorsignificativo, &tabla_de_simbolos);
            amodificar->alcance = 1;
            //imprimir(&tabla_de_simbolos);
            break;
        case 28: // BINDING -> id = EXP
            printf("Accion semantica 28\n");
            creaHoja(nuevoArbol, 1, "BINDING");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "id");
            agregaHijoExistente(nuevoArbol, hojaAux);
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, "=");
            agregaHijoExistente(nuevoArbol, hojaAux);
            arbolDePila = popT(&nodosHuerfanos);
            agregaHijoExistente(nuevoArbol, &arbolDePila);
            pushT(*nuevoArbol, &nodosHuerfanos);
            
            creaHoja(ASTArbol,1,"=");
            hojaAux = (NodoArbol**) malloc(sizeof(NodoArbol*));
            creaHoja(hojaAux, 0, valorsignificativo);
            agregaHijoExistente(ASTArbol, hojaAux);
            arbolDePila = popT(&ASTstack);
            agregaHijoExistente(ASTArbol, &arbolDePila);
            pushT(*ASTArbol, &ASTstack);
            break;
            
    }
     /*printf("============================================================================\n ARBOL SINTACTICO \n===========================================================================\n");
    printT(&nodosHuerfanos);
    */
    printf("============================================================================\n ARBOL AST \n===========================================================================\n");
    printT(&ASTstack);
    //printT2(&ASTstack);
    
    
    
    return 0;
}

int d(){
    
    
    char *valor = pop_first();
    char *rgreso = pop_first();
    printf("Desplazamiento %d\n",matrizvalores[numero][index_of(rgreso)]);
    if(rgreso != NULL){
        push(stack, matrizvalores[numero][index_of(rgreso)], index_of(rgreso), valor);
        return 0;
    }
    exit(0);
    return 1;
}

int i(){
    //pop_first();
    char * valordestack;
    char *rgreso = get_second();
    if(rgreso != NULL){
        printf("%s",rgreso);
        push(stack,matrizvalores[numero][letra],index_of(rgreso), valordestack);
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
    
    
    
    
    char * valordestack = (char*)malloc(sizeof(char)*100);
    fp = fopen("lexemas.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    creaStack(stack);
	
    
    push(stack,0,index_of("$\n"), valordestack);
    
    
    while(1){
        top(stack,&numero,&letra, valordestack);
        char *loqueleodelafila = get_second();
        printStack(stack);
        //printf("%s\n", loqueleodelafila);
        //printf("matriz[%s, %d]\n", loqueleodelafila, index_of(loqueleodelafila));
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
