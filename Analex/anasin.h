//
//  anasin.h
//  Analizador Lexico
//
//  Created by Brounie on 17/02/13.
//
//

#ifndef Analizador_Lexico_anasin_h
#define Analizador_Lexico_anasin_h

#define TERMINALESYNOTERMINALES 34
#define ESTADOS 53



char *uses[TERMINALESYNOTERMINALES] = {";\n", "binop\n", "TRUE\n", "FALSE\n", "numer\n", "string\n", "while\n", "do\n", "end\n", "if\n", "else\n", "elseif\n", "then\n", "return\n", "local\n", "ID\n", "=\n", "(\n", ")\n", "$\n", "CHUNK\n", "BLOCK\n", "SCOPE\n", "STATLIST\n", "LASTSTAT\n", "SEMI\n", "BINDING\n", "EXP\n", "EXP2\n", "PREFIXEXP\n", "STAT\n", "CONDS\n", "CONDLIST\n", "COND\n"};


int index_of(char *string);
int f0();
int d();
int e();
int ok();
int r();

char leerAnalex();
int Anasin();
int i();

int (*matriz[ESTADOS][TERMINALESYNOTERMINALES])()={
    {e,e,e,e,e,e,r,e,e,r,e,e,e,r,r,r,e,e,e,r,i,i,i,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,ok,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,r,e,r,r,r,r,e,r,r,r,e,e,e,r,e,e,e,i,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,d,e,r,d,r,r,e,d,d,d,e,e,e,r,e,e,e,e,i,e,i,e,e,e,i,e,e,e},
    {d,e,e,e,e,e,e,e,r,e,r,r,e,e,e,e,e,e,e,r,e,e,e,e,e,i,e,e,e,e,e,e,e,e},
    {d,e,e,e,e,e,r,e,r,r,r,r,e,r,r,r,e,e,e,r,e,e,e,e,e,i,e,e,e,e,e,e,e,e},
    {d,e,e,e,e,e,r,e,r,r,r,r,e,r,r,r,e,e,e,r,e,e,e,e,e,i,e,e,e,e,e,e,e,e},
    {e,e,d,d,d,d,e,e,e,e,e,e,e,e,e,d,e,d,e,e,e,e,e,e,e,e,e,i,e,i,e,e,e,e},
    {e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,d,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,d,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,d,d,d,d,e,e,e,e,e,e,e,e,e,d,e,d,e,e,e,e,e,e,e,e,e,i,e,i,e,e,e,e},
    {e,e,d,d,d,d,e,e,e,e,e,e,e,e,e,d,e,d,e,e,e,e,e,e,e,e,e,i,e,i,e,i,i,i},
    {e,e,e,e,e,e,e,e,r,e,r,r,e,e,e,e,e,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,r,e,r,r,r,r,e,r,r,r,e,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,r,e,r,r,r,r,e,r,r,r,e,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,r,e,r,r,r,r,e,r,r,r,e,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,d,e,e,e,e,e,e,r,e,r,r,e,e,e,e,e,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,d,d,d,d,e,e,e,e,e,e,e,e,e,d,e,d,e,e,e,e,e,e,e,e,e,i,e,i,e,e,e,e},
    {r,e,e,e,e,e,r,e,r,r,r,r,e,r,r,r,d,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,d,d,d,d,e,e,e,e,e,e,e,e,e,d,e,d,e,e,e,e,e,e,e,e,e,i,e,i,e,e,e,e},
    {e,d,e,e,e,e,e,d,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,e,e,d,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,e,e,r,e,d,d,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,e,e,r,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,d,e,e,e,e,e,e,e,e,e,e,d,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,d,d,d,d,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,i,e,e,e,e,e},
    {e,d,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,d,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,d,d,d,d,e,e,e,e,e,e,e,e,e,d,e,d,e,e,e,e,e,e,e,e,e,i,e,i,e,e,e,e},
    {r,d,e,e,e,e,r,e,r,r,r,r,e,r,r,r,e,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,r,e,r,r,e,e,e,r,r,r,e,e,e,e,e,i,i,e,e,e,e,e,e,e,e,e,e,e},
    {r,e,e,e,e,e,r,e,r,r,r,r,e,r,r,r,e,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,r,e,r,r,e,e,e,r,r,r,e,e,e,e,e,i,i,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,d,d,d,d,e,e,e,e,e,e,e,e,e,d,e,d,e,e,e,e,e,e,e,e,e,i,e,i,e,e,e,i},
    {e,e,e,e,e,e,r,e,r,r,r,r,e,r,r,r,e,e,e,e,e,i,i,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,r,e,e,e,e,r,r,r,r,r,r,r,r,r,r,e,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,d,e,e,e,e,r,e,r,r,r,r,e,r,r,r,e,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,e,e,d,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,e,e,r,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {e,e,e,e,e,e,e,e,r,e,r,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e,e},
    {r,e,e,e,e,e,r,e,r,r,r,r,e,r,r,r,e,e,e,r,e,e,e,e,e,e,e,e,e,e,e,e,e,e}
};


int matrizvalores[ESTADOS][TERMINALESYNOTERMINALES]={
                  /* (            a           )         $         A          */
    /*0*/{          3,              2,          0,       0,         1         },
    /*1*/{          0,              0,          0,       0,         0         },
    /*2*/{          0,              0,          2,       2,         0         },
    /*3*/{          3,              2,          0,       0,         4         },
    /*4*/{          0,              0,          5,       0,         0         },
    /*5*/{          0,              0,          1,       1,         0         }

};



int reduccciones[3][5] = {
    
    /*0*/{          -1,              -1,          -1,       -1,       -1          },
    /*0*/{           4,               0,           4,       2,         -1         },
    /*0*/{           4,               1,          -1,       -1,         -1        },
    
};



#endif
