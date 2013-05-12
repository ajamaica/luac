MOV i, #0 
MOV A, #0 
SUB A, i 
MOV A, #0 
RLC A 
MOV B1, A 
MOV A, B1 
CJNE A, #0 E1 
JUMP E2,  
E1:    
JUMP E3,  
E2:    
E3:    
END
