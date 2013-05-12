//
//  tablasim.h
//  Analizador Lexico
//
//  Created by Arturo Jamaica Garcia on 03/03/13.
//
//

#ifndef Analizador_Lexico_tablasim_h
#define Analizador_Lexico_tablasim_h

typedef struct nulo
{
    struct nulo * sig;
    char *nombre;
    char *tipo_de_dato;
    int valor;
    int alcance;
} simbolo;

simbolo * crear()
{
    return NULL;
};

void insertar(simbolo **p_t,simbolo *s)
{
    s->sig = (*p_t);
    (*p_t) = s;
};



void imprimir(simbolo *t)
{
    printf("Nombre | Tipo de Dato | Valor | Alcance\n");
    while (t != NULL)
    {
        printf("%s %s %i %i\n", t->nombre,t->tipo_de_dato,t->valor,t->alcance);
        t = t->sig;

    }
};

int tamano(simbolo *t)
{
    int tamano = 0;
    while (t != NULL)
    {
        tamano++;
        t = t->sig;
        
    }
    return tamano;
};

simbolo* search(char * nombre, simbolo *t){
    simbolo * aux = (simbolo *) malloc(sizeof(simbolo));
    while (t->sig != NULL)
    {
       
        printf("%s", t->nombre);
        printf("%s",nombre);
  
        char buffer [50];
        
        sprintf (buffer, "%s\n", t->nombre);
        
        if(strcmp(buffer, nombre) == 0){
            printf("%s",nombre);
            return t;
        }
        
        t = t->sig;
    }
  
    return aux;
}



#endif
