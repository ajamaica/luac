#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include "tablasim.h"

char buf[100];
FILE * fuente;


typedef struct worker {
	char buf[100];
	int estado;
	int (*funcion)(struct worker *a,char c);
}worker;
simbolo *ta;
worker ar[11];
char escritura[BUFSIZ];
int fdLexemas;
int commentariossi,stringsi;

char *reservadas[33] = {
    "and", "break", "do", "else", "elseif","end", "false", "for", "function", "goto", "if","in", "local", "nil", "not", "or", "repeat","return", "then", "true", "until", "while",
    "..", "...", "==", ">=", "<=", "~=", "::", "<eof>","<number>", "<name>", "<string>"
};

char *tipos_de_dato[8] = {"nil", "boolean", "number", "string", "function", "userdata", "thread", "table"};

void reinicia(worker arr[]){
    int i;
    for(i = 0; i < 11; i++){
        arr[i].estado = 0;
        memset(arr[i].buf, '\0', 100);
    }
	commentariossi = 0;
	stringsi = 0;
}

void lexema(char *l, char *t){
    sprintf(escritura,"%s\n%s\n", l, t);
    int tamano = strlen(escritura);
    write(fdLexemas, escritura, tamano);
}

int ultimo(char buf[]) {
	int i = 0;
	while(buf[i] != '\0') {
		i++;
		if (i >= (100)) {
			break;
		}
	}
	return i;
}

int verificaReservada(char str[]) {
	int size,i;
	size = sizeof(reservadas)/sizeof(reservadas[1]);
	for (i=0; i<size; i++) {
		if (strcmp(str, reservadas[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int verificaTipoDeDato(char str[]) {
	int size,i;
	size = sizeof(tipos_de_dato)/sizeof(tipos_de_dato[1]);
	for (i=0; i<size; i++) {
		if (strcmp(str, tipos_de_dato[i]) == 0) {
			return 1;
		}
	}
	return 0;
}


int reales(worker *a , char c) {
	if (commentariossi == 1 || stringsi == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (c == '+' || c == '-') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
                
				(*a).estado = 2;
				return 0;
			}
			if (isdigit(c)) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (c == '.') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 3;
				return 0;
			}
			return 0;
			break;
		case 1:
			if (isdigit(c)) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				return 0;
			}
			if (c == '.') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 3;
				return 0;
			}
			return 0;
			break;
		case 2:
			if (isdigit(c)) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			
			return 0;
			break;
		case 3:
			if (isdigit(c)) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 4;
				return 0;
			}
			return 0;
			break;
		case 4:
			if (isdigit(c)) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				return 0;
			} else {
                
                /*simbolo *sim = (simbolo *) malloc(sizeof(simbolo *));
                char * buff = (char *) malloc(sizeof(char*));
                sprintf(buff, "%s", (*a).buf);
                sim->nombre = (char *) malloc(sizeof(char*));
                strcpy(sim->nombre, buff);
                sim->tipo_de_dato = (char *) malloc(sizeof(char*));

                strcpy(sim->tipo_de_dato, "Numero Real");
                insertar(&ta,sim);*/
                
				fprintf(stdout, "%s\t%s\n",(*a).buf,"numer");
				lexema((*a).buf,"numer" );
				return 1;
			}
			break;
		default:
			return 0;
			break;
	}
}


int numeros(worker *a , char c) {
	if (commentariossi == 1 || stringsi == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (c == '+' || c == '-') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (isdigit(c)) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			return 0;
			break;
		case 1:
			if (isdigit(c)) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			(*a).estado = -1;
            
			return 0;
			break;
		case 2:
			if (isdigit(c)) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				return 0;
			} else if (c != '.'){
                
                /*simbolo *sim = (simbolo *) malloc(sizeof(simbolo *));
                char * buff = (char *) malloc(sizeof(char*));
                sprintf(buff, "%s", (*a).buf);
                sim->nombre = (char *) malloc(sizeof(char*));
                strcpy(sim->nombre, buff);
                sim->tipo_de_dato = (char *) malloc(sizeof(char*));
                strcpy(sim->tipo_de_dato, "numer");
                insertar(&ta,sim);*/
                
                
				fprintf(stdout, "%s\t%s\n",(*a).buf,"numer");
                lexema((*a).buf,"numer" );
				return 1;
			} else {
				(*a).estado = -1;
				return 0;
			}
            
			return 0;
			break;
		default:
			return 0;
			break;
	}
}

int puntuacion(worker *a , char c){
	if (commentariossi == 1 || stringsi == 1) {(*a).estado = -1;}
    switch((*a).estado){
        case 0:
            if( c == '.' || c== ',' || c== ':' || c == ';' ){
                sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado=1;
                return 0;
            }
			if (c == ' ' || c == '\n') {
				return 0;
			}
            return 0;
            break;
        case 1:
            if(((int)c)>=48 && ((int)c)<=57){
                return 0;
            }else{
				fprintf(stdout, "%s\t%s\n",(*a).buf,(*a).buf);
                lexema((*a).buf,(*a).buf );
				return 1;
            }
            return 0;
            break;
		default:
			return 0;
			break;
    }
	return 0;
}


int asignacion(worker *a, char c){
	if (commentariossi == 1) {(*a).estado = -1;}
    switch((*a).estado){
		case 0:
			if(c == '*' || c == '/' || c == '%'){
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 1;
				return 0;
			}
            if (c == '[' ){
                sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 6;
				return 0;
            }
            
            if (c == ']' ){
                sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 6;
				return 0;
            }
            
			if(c == '='){
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			if (c == '+') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 3;
				return 0;
			}
			if (c == '-') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 4;
				return 0;
			}
			if (c == ' ' || c == '\n') {
				return 0;
			}
			(*a).estado = -1;
			break;
		case 1:
			if(c == '='){
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"=");
				lexema((*a).buf,"=" );
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 2:
			fprintf(stdout, "%s\t%s\n",(*a).buf,"=");
			lexema((*a).buf,"=" );
			return 1;
			break;
		case 3:
			if(c == '+'){
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Asignacion");
				lexema((*a).buf,"Asignacion" );
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 4:
            
            
            if ((isdigit(c) || c == ' ' || isalpha(c)) && commentariossi == 0) {
				fprintf(stdout, "%s\t%s\n",(*a).buf,"binop");
				lexema((*a).buf,"binop" );
                (*a).estado = -1;
				return 1;
			}
            
			return 0;
            
            break;
        case 5:
            if(c == '['){
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
                (*a).estado = 6;
				return 0;
			}
            
            return 0;
            break;
        case 6:
            
            if(c == '[' || c == ']'){
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Apertura // Cierre de Agrupador");
				lexema((*a).buf,"Apertura // Cierre de Agrupador" );
                (*a).estado = -1;
				return 1;
			}
            
            if(c == '='){
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
                (*a).estado = 6;
				return 0;
			}
            
            
            return 0;
            break;
        default:
            return 0;
            break;
	}
	return 0;
}


int ids(worker *a , char c) {
    
	if (commentariossi == 1 || stringsi == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (isalpha(c) || c == '_') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (c == ' ' || c == '\n') {
				return 0;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 1:
			if (isdigit(c) || isalpha(c) || c == '_') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				return 0;
			} else {
				if (verificaReservada((*a).buf)) {
					fprintf(stdout, "%s\t%s\n",(*a).buf,(*a).buf);
					lexema((*a).buf,(*a).buf );
				} else if (verificaTipoDeDato((*a).buf)) {
					fprintf(stdout, "%s\t%s\n",(*a).buf,"Tipo de Dato");
					lexema((*a).buf,"Tipo de Dato" );
				} else {
                    
                    simbolo *sim = (simbolo *) malloc(sizeof(simbolo *));
                    char * buff = (char *) malloc(sizeof(char*));
                    sprintf(buff, "%s", (*a).buf);
                    
                    sim->nombre = (char *) malloc(sizeof(char*));
                    strcpy(sim->nombre, buff);
                    sim->tipo_de_dato = (char *) malloc(sizeof(char*));
                    strcpy(sim->tipo_de_dato, "id");
		    sim->valor = (int) -1;
                    insertar(&ta,sim);
                    
					fprintf(stdout, "%s\t%s\n",(*a).buf,"id");
					lexema((*a).buf,"id" );
				}
				return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}

int comentarios(worker *a, char c){
    
	switch((*a).estado){
        case 0:
            if(c == '-'){
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
                (*a).estado = 1;
                return 0;
            }
        	return 0;
        	break;
    	case 1:
			if(c == '-'){
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
    		 	(*a).estado = 2;
				commentariossi = 1;
    		 	return 0;
    		}
            return 0;
            break;
        case 2:
        	if(((int)c) != 10){
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 2;
				return 0;
        	} else {
      		    fprintf(stdout, "%s\t%s\n",(*a).buf,"Comentario");
				lexema((*a).buf,"Comentario" );
				return 1;
      		}
			return 0;
			break;
        default:
			return 0;
			break;
	}
}

int conjuntos(worker *a , char c) {
	if (commentariossi == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if ((c == '(') || (c == ')') || (c == '{') || (c == '}')) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,(*a).buf);
				lexema((*a).buf,(*a).buf );
				return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}


int operadores_matematicos(worker *a , char c) {
	if (commentariossi == 1 || stringsi == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (((c == '+')  || (c == '/') || (c == '*') || (c == '%')) && commentariossi == 0) {
				(*a).estado = 1;
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				return 0;
			}
			
			return 0;
		case 1:
			if ((isdigit(c) || c == ' ' || isalpha(c)) && commentariossi == 0) {
				fprintf(stdout, "%s\t%s\n",(*a).buf,"binop");
				lexema((*a).buf,"binop" );
				return 1;
			}
			return 0;
			break;
        default:
			return 0;
			break;
	}
}

int strings(worker *a , char c) {
	if (commentariossi == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if ((int)c == 34) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 1;
				stringsi = 1;
				return 0;
			}
			if ((int)c == 39) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 2;
				stringsi = 1;
				return 0;
			}
			if (c == ' ' || c == '\n') {
				return 0;
			}
			(*a).estado = -1;
            return 0;
			break;
		case 1:
			if ((int)c != 34) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				return 0;
			} else {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"String");
				lexema((*a).buf,"String" );
				return 1;
			}
			return 0;
			break;
		case 2:
			if ((int)c != 39) {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				return 0;
			} else {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Char");
				lexema((*a).buf,"char" );
				return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}


int comparacion(worker *a , char c) {
	if (commentariossi == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (c == '=') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (c == '!') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (c == '>') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			if (c == '<') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			if (c == ' ' || c == '\n') {
				return 0;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 1:
			if (c == '=') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"binop");
				lexema((*a).buf,"binop" );
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 2:
			if (c == '=') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"binop");
				lexema((*a).buf,"binop" );
				return 1;
			} else {
				fprintf(stdout, "%s\t%s\n",(*a).buf,"binop");
				lexema((*a).buf,"binop" );
				return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}


int logicos(worker *a , char c) {
	if (commentariossi == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (c == '&') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (c == '|') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			if (c == '!') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Operador logico");
				lexema((*a).buf,"Operador logico" );
				return 1;
			}
			if (c == ' ' || c == '\n') {
				return 0;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 1:
			if (c == '&') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Logico");
				lexema((*a).buf,"Logico" );
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 2:
			if (c == '|') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Logico");
				lexema((*a).buf,"Logico" );
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		default:
			return 0;
			break;
	}
}






void inicia(){
	ar[0].funcion = comentarios;
    ar[1].funcion = ids;
    ar[2].funcion = logicos;
    ar[3].funcion = comparacion;
    ar[4].funcion = asignacion;
    ar[5].funcion = numeros;
    ar[6].funcion = reales;
    ar[7].funcion = puntuacion;
    ar[8].funcion = strings;
    ar[9].funcion = conjuntos;
    ar[10].funcion = operadores_matematicos;
	reinicia(ar);
}


simbolo Analex(){
    
    ta = (simbolo *) malloc(sizeof(simbolo));
    printf("------- ANALEX -------");
	
    char *file = "codigo.txt";
    
    
    
	if((fuente=fopen(file,"r")) == NULL){
		fprintf(stderr, "Error: %s",file);
		return *ta;
	}
    
    if ((fdLexemas=open("lexemas.txt",O_WRONLY | O_CREAT | O_TRUNC,0666)) < 0) {
		fprintf(stderr, "Error al crear archivo lexemas.txt");
		return *ta;
	}
	
    inicia();
	
	char leido;
	
	while ((leido = getc(fuente)) != EOF) {
		
		if (ar[0].funcion(&ar[0],leido) == 1) {
			reinicia(ar);
			continue;
		}
		if (ar[1].funcion(&ar[1],leido) == 1) {
			reinicia(ar);
			continue;
		}
		if (ar[2].funcion(&ar[2],leido) == 1) {
			reinicia(ar);
			continue;
		}
		if (ar[3].funcion(&ar[3],leido) == 1) {
			reinicia(ar);
			continue;
		}
		if (ar[4].funcion(&ar[4],leido) == 1) {
			reinicia(ar);
			continue;
		}
		if (ar[5].funcion(&ar[5],leido) == 1) {
			reinicia(ar);
			continue;
		}
		if (ar[6].funcion(&ar[6],leido) == 1) {
			reinicia(ar);
			continue;
		}
		
		if (ar[7].funcion(&ar[7],leido) == 1) {
			reinicia(ar);
			continue;
		}
		
		if (ar[8].funcion(&ar[8],leido) == 1) {
			reinicia(ar);
			continue;
		}
		
		if (ar[9].funcion(&ar[9],leido) == 1) {
			reinicia(ar);
			continue;
		}
		
		if (ar[10].funcion(&ar[10],leido) == 1) {
			reinicia(ar);
			continue;
		}
		
	}
    
	fclose(fuente);
    
    imprimir(ta);
    return *ta;

}

