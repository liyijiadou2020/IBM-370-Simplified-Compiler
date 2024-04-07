current result:

EXAMP    START 0            Program starts

BALR  RBASE,0      Load base register

USING *,RBASE      Set base register

L     RRAB,A       Load var into register

A     RRAB,B       Formation of intermediate value

S     RRAB,C       Formation of intermediate value

ST    RRAB,D       Generate value of arithmetic express

BCR   15,14        Exit from program

A        DC    F'3.'        Defination of var

B        DC    F'4.'        Defination of var

C        DC    F'5.'        Defination of var

D        DC    F'0.'        Defination of var

RBASE    EQU   15                            

RRAB     EQU   5                             

END   EXAMP        End of program
