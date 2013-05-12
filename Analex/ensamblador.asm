MOV i, #0 
<<<<<<< HEAD
LT B1, i 
BRT B1,  
JUMP E2,  
E1:    
JUMP E3,  
E2:    
=======
E1:    
LT B1, i 
BRT B1,  
JUMP E3,  
E2:    
MOV A, i 
ADD A, #1 
MOV T1, A 
MOV i, T1 
LT B2, #9 
BRT B2,  
JUMP E5,  
E4:    
MOV i, #0 
JUMP E6,  
E5:    
E6:    
CJNE #0, B3 
BRT B3,  
JUMP E8,  
E7:    
MOV P1, #176 
JUMP E9,  
E8:    
CJNE #1, B4 
BRT B4,  
JUMP E11,  
E10:    
MOV P1, #249 
JUMP E12,  
E11:    
CJNE #2, B5 
BRT B5,  
JUMP E14,  
E13:    
MOV P1, #192 
JUMP E15,  
E14:    
CJNE #3, B6 
BRT B6,  
JUMP E17,  
E16:    
MOV P1, #176 
JUMP E18,  
E17:    
CJNE #4, B7 
BRT B7,  
JUMP E20,  
E19:    
MOV P1, #153 
JUMP E21,  
E20:    
CJNE #5, B8 
BRT B8,  
JUMP E23,  
E22:    
MOV P1, #146 
JUMP E24,  
E23:    
CJNE #6, B9 
BRT B9,  
JUMP E26,  
E25:    
MOV P1, #130 
JUMP E27,  
E26:    
CJNE #7, B10 
BRT B10,  
JUMP E29,  
E28:    
MOV P1, #248 
JUMP E30,  
E29:    
CJNE #8, B11 
BRT B11,  
JUMP E32,  
E31:    
MOV P1, #128 
JUMP E33,  
E32:    
MOV P1, #144 
E33:    
E30:    
E27:    
E24:    
E21:    
E18:    
E15:    
E12:    
E9:    
JUMP E1,  
>>>>>>> 2b9b09d90dc4faee7d91bf08556a234a454dd00e
E3:    
END
