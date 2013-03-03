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
#include "List.h"

FILE * fp;
Elemento ** stack;

int numero;
char letra;



int main (int argc, const char * argv[]) {
    
    stack = malloc(sizeof(Elemento*));
    
    Analex();
	
    printf("------- ANASIN -------\n");
    
    
    fp = fopen("lexemas.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    char * line = (char *) malloc(100);
    size_t len = 100;
    size_t read;
    
    struct test_struct *ptr = NULL;
    
    print_list();
    
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
    
    
    return 0;
}

int d(){
    
    
    pop_first();
    char *rgreso = pop_first();
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
    print_list();
    
    push(stack,0,index_of("$\n"));
    
    
    while(1){
        
        top(stack,&numero,&letra);
        char *loqueleodelafila = get_second();
        printStack(stack);
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