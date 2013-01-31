#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>

typedef struct worker {
	char buf[100];
	int estado;
	int (*funcion)(struct worker *a,char c);
}worker;
worker ar[11];

char escritura[100];
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
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Numero Real");
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
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Numero Natural");
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
            if( c == '.' || c== ',' || c== ':'){
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
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Puntuación");
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
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Asignacion");
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 2:
			fprintf(stdout, "%s\t%s\n",(*a).buf,"Asignacion");
			return 1;
			break;
		case 3:
			if(c == '+'){
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Asignacion");
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 4:
            
            
            if ((isdigit(c) || c == ' ' || isalpha(c)) && commentariossi == 0) {
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Aritmetico");
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
					fprintf(stdout, "%s\t%s\n",(*a).buf,"Reservada");
				} else if (verificaTipoDeDato((*a).buf)) {
					fprintf(stdout, "%s\t%s\n",(*a).buf,"Tipo de Dato");
				} else {
					fprintf(stdout, "%s\t%s\n",(*a).buf,"ID");
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
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Agrupador");
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
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Artirmetico");
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
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Comparacion");
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 2:
			if (c == '=') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Comparacion");
				return 1;
			} else {
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Comparacion");
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
				return 1;
			}
			(*a).estado = -1;
			return 0;
			break;
		case 2:
			if (c == '|') {
				sprintf((*a).buf+ultimo((*a).buf), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buf,"Logico");
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


