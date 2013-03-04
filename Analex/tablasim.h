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

void insertar(p_t,s)
simbolo **p_t;
simbolo * s;
{
    s->sig = (*p_t);
    (*p_t) = s;
};


simbolo * buscar(t,nombre)
simbolo * t;
char nombre[20];
{
    while ( (t != NULL) && (strcmp(nombre, t->nombre)) )
        t = t->sig;
        return (t);
};


void imprimir(t)
simbolo * t;
{
    printf("Nombre | Tipo de Dato | Valor | Alcance\n");
    while (t != NULL)
    {
        printf("%c %s %i %i\n", t->nombre,t->tipo_de_dato,t->valor,t->alcance);
        t = t->sig;
    }
};



#endif
