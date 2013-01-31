

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>


char escritura[BUFSIZ];

char *reservadas[33] = {
    "and", "break", "do", "else", "elseif",
    "end", "false", "for", "function", "goto", "if",
    "in", "local", "nil", "not", "or", "repeat",
    "return", "then", "true", "until", "while",
    "..", "...", "==", ">=", "<=", "~=", "::", "<eof>",
    "<number>", "<name>", "<string>"
};

char *tipos_de_dato[8] = {"nil", "boolean", "number", "string", "function", "userdata", "thread", "table"};

int isComment,isString;

typedef struct automata {
	char buffer[BUFSIZ];
	int estado;
	int (*funcion)(struct automata *a,char c);
}automata;


automata ar[11];

void reset(automata arr[]){
    int i;
    for(i = 0; i < 11; i++){
        arr[i].estado = 0;
        memset(arr[i].buffer, '\0', BUFSIZ);
    }
	isComment = 0;
	isString = 0;
}

int getLastIndex(char buffer[]) {
	int i = 0;
	while(buffer[i] != '\0') {
		i++;
		if (i >= (BUFSIZ)) {
			break;
		}
	}
	return i;
}

int isKeyword(char str[]) {
	int size,i;
	size = sizeof(reservadas)/sizeof(reservadas[1]);
	for (i=0; i<size; i++) {
		if (strcmp(str, reservadas[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int istipos_de_dato(char str[]) {
	int size,i;
	size = sizeof(tipos_de_dato)/sizeof(tipos_de_dato[1]);
	for (i=0; i<size; i++) {
		if (strcmp(str, tipos_de_dato[i]) == 0) {
			return 1;
		}
	}
	return 0;
}




int reales(automata *a , char c) {
	if (isComment == 1 || isString == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (c == '+' || c == '-') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			if (isdigit(c)) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (c == '.') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 3;
				return 0;
			}
			return 0;
			break;
		case 1:
			if (isdigit(c)) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				return 0;
			}
			if (c == '.') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 3;
				return 0;
			}
			return 0;
			break;
		case 2:
			if (isdigit(c)) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			
			return 0;
			break;
		case 3:
			if (isdigit(c)) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 4;
				return 0;
			}
			return 0;
			break;
		case 4:
			if (isdigit(c)) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				return 0;
			} else {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Numero Real");
				return 1;
			}
			break;
		default:
			return 0;
			break;
	}
}


int numeros(automata *a , char c) {
	if (isComment == 1 || isString == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (c == '+' || c == '-') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (isdigit(c)) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			return 0;
			break;
		case 1:
			if (isdigit(c)) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			(*a).estado = -1;

			return 0;
			break;
		case 2:
			if (isdigit(c)) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				return 0;
			} else if (c != '.'){
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Numero Natural");
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


int ids(automata *a , char c) {

	if (isComment == 1 || isString == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (isalpha(c) || c == '_') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (c == ' ' || c == '\n') {
				return 0;
			}
			// Si comienza con algo mas 
			(*a).estado = -1;
			return 0;
			break;
		case 1:
			if (isdigit(c) || isalpha(c) || c == '_') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				return 0;
			} else {
				if (isKeyword((*a).buffer)) {
					fprintf(stdout, "%s\t%s\n",(*a).buffer,"Reservada");
				} else if (istipos_de_dato((*a).buffer)) {
					fprintf(stdout, "%s\t%s\n",(*a).buffer,"Tipo de Dato");
				} else {
					fprintf(stdout, "%s\t%s\n",(*a).buffer,"ID");
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

int comentarios(automata *a, char c){

	switch((*a).estado){
        case 0:
            if(c == '-'){
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
                (*a).estado = 1;
                return 0;
            }
        	return 0;
        	break;
    	case 1:
			if(c == '-'){
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
    		 	(*a).estado = 2;
				isComment = 1;
    		 	return 0;
    		}
            return 0;
            break; 
        case 2:
        	if(((int)c) != 10){
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 2;
				return 0;
        	} else {
      		    fprintf(stdout, "%s\t%s\n",(*a).buffer,"Comentario");
				return 1;
      		}
			return 0;
			break;
        default:
			return 0;
			break;
	}
}


int puntuacion(automata *a , char c){
	if (isComment == 1 || isString == 1) {(*a).estado = -1;}
    switch((*a).estado){
        case 0:
            if( c == '.' || c== ',' || c== ':'){
                sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
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
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Signo de puntuacion");
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


int asignacion(automata *a, char c){
	if (isComment == 1) {(*a).estado = -1;}
	//fprintf(stdout, "Asigestado:%d char:%c\n",(*a).estado,c);
    switch((*a).estado){
		case 0:
			if(c == '*' || c == '/' || c == '%'){
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 1;
				return 0;
			}
            if (c == '[' ){
                sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 6;
				return 0;
            }
            
            if (c == ']' ){
                sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 6;
				return 0;
            }
            
			if(c == '='){
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			if (c == '+') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 3;
				return 0;
			}
			if (c == '-') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
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
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador de asignacion");
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 2:
			fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador de asignacion");
			return 1;
			break;
		case 3:
			if(c == '+'){
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador de asignacion");
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 4:

            
            if ((isdigit(c) || c == ' ' || isalpha(c)) && isComment == 0) {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador Aritmetico");
                (*a).estado = -1;
				return 1;
			}
            
			return 0;
            
            break;
        case 5:
            if(c == '['){
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
                (*a).estado = 6;
				return 0;
			}
            
            return 0;
            break;
        case 6:
            
            if(c == '[' || c == ']'){
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Apertura // Cierre de Agrupador");
                (*a).estado = -1;
				return 1;
			}
            
            if(c == '='){
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
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


int conjuntos(automata *a , char c) {
	if (isComment == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if ((c == '(') || (c == ')') || (c == '{') || (c == '}')) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador de Agrupacion");
				return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}


int operadores_matematicos(automata *a , char c) {
	if (isComment == 1 || isString == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (((c == '+')  || (c == '/') || (c == '%')) && isComment == 0) {
				(*a).estado = 1;
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				return 0;
			}
			if (c == '*') {
				(*a).estado = 2;
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				return 0;
			}
			return 0;
		case 1:
			if ((isdigit(c) || c == ' ' || isalpha(c)) && isComment == 0) {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador Aritmetico");
				return 1;
			}
			return 0;
			break;
		case 2:
			if ((isdigit(c) || c == ' ' || isalpha(c)) && isComment == 0) {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador Aritmetico o Apuntador");
				return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}

int strings(automata *a , char c) {
	if (isComment == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if ((int)c == 34) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 1;
				isString = 1;
				return 0;
			}
			if ((int)c == 39) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 2;
				isString = 1;
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
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				return 0;
			} else {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"String");
				return 1;
			}
			return 0;
			break;
		case 2:
			if ((int)c != 39) {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				return 0;
			} else {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Char");
				return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}


int comparacion(automata *a , char c) {
	if (isComment == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (c == '=') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (c == '!') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (c == '>') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			if (c == '<') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
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
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador de comparacion");
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 2:
			if (c == '=') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador de comparacion");
				return 1;
			} else {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador de comparacion");
				return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}


int logicos(automata *a , char c) {
	if (isComment == 1) {(*a).estado = -1;}
	switch ((*a).estado) {
		case 0:
			if (c == '&') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 1;
				return 0;
			}
			if (c == '|') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				(*a).estado = 2;
				return 0;
			}
			if (c == '!') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador logico");
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
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador logico");
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 2:
			if (c == '|') {
				sprintf((*a).buffer+getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operador logico");
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
	reset(ar);
}


