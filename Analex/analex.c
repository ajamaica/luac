#include "analex.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

char buf[BUFSIZ];

int main (int argc, const char * argv[]) {
	
    argv[1] = "codigo.txt";
    
	if((fuente=fopen(argv[1],"r")) == NULL){
		fprintf(stderr, "Error: %s",argv[1]);
		return -1;
	}
	
    inicia();
	
	char leido;
	
	while ((leido = getc(fuente)) != EOF) {
		
		if (ar[0].funcion(&ar[0],leido) == 1) {
			reset(ar);
			continue;
		}
		if (ar[1].funcion(&ar[1],leido) == 1) {
			reset(ar);
			continue;
		}
		if (ar[2].funcion(&ar[2],leido) == 1) {
			reset(ar);
			continue;
		}
		if (ar[3].funcion(&ar[3],leido) == 1) {
			reset(ar);
			continue;
		}
		if (ar[4].funcion(&ar[4],leido) == 1) {
			reset(ar);
			continue;
		}
		if (ar[5].funcion(&ar[5],leido) == 1) {
			reset(ar);
			continue;
		}
		if (ar[6].funcion(&ar[6],leido) == 1) {
			reset(ar);
			continue;
		}
		
		if (ar[7].funcion(&ar[7],leido) == 1) {
			reset(ar);
			continue;
		}
		
		if (ar[8].funcion(&ar[8],leido) == 1) {
			reset(ar);
			continue;
		}
		
		if (ar[9].funcion(&ar[9],leido) == 1) {
			reset(ar);
			continue;
		}
		
		if (ar[10].funcion(&ar[10],leido) == 1) {
			reset(ar);
			continue;
		}
		
	}
    
	fclose(fuente);
	
    return 0;
}

