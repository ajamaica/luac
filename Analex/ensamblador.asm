MOV i, #0 
MOV A, i 
SUB A, #0 
MOV B1, A 
MOV A, B1 
CJNE A, #0 E1 
JUMP E2,  
E1:    
JUMP E3,  
E2:    
E3:    
END
