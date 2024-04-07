/*
***** START of the high-level language compiler file
*/

/*
***** Block of macro definition declarations
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXNISXTXT 50                             
#define NSINT     201                             
#define NCEL       20                             
#define NDST      500                             
#define NVXOD      53                             
#define NSTROKA   200                             
#define NNETRM     16                             
#define MAXLTXT    50                             
#define MAXFORMT   30                             

#define NSYM      100                            

/*
***** COMPILER database
*/

/*
***** Block of source text array declaration
*/

int  NISXTXT;                
char ISXTXT [MAXNISXTXT][80];

/*
***** Block of working variables declaration
*/

int I1,I2,I3,I4;                                  

char PREDSYM = ' ';                               


char STROKA [ NSTROKA ];                          

int I,J,K,L;                                      

union                                             
{                                                
char    BUFCARD [80];                           
struct
  {
  char METKA   [8];
  char PROB1;
  char OPERAC  [5];
  char PROB2;
  char OPERAND [12];
  char PROB3;
  char COMM    [52];
  } _BUFCARD;
} ASS_CARD ;

char ASSTXT [ MAXLTXT ][80];                      

int  IASSTXT;                        

char FORMT [MAXFORMT] [9];           

int  IFORMT;                                      

/*
***** Block of database tables declaration
*/

/*
***** Table used as a stack (magazine) of achievements
*/

struct
{
char DST1 [ 4 ];
int  DST2;
int  DST3;
int  DST4;
int  DST5;
} DST [ NDST ];

/*
***** Table used as a stack (magazine) of goals
*/

struct
 {
  char CEL1 [ 4 ];
  int  CEL2;
  int  CEL3;
 } CEL [ NCEL ];

/*
***** Table of syntax rules in recognition form,
***** grouped into "clusters" and represented as a bidirectional
***** list with alternative branching
*/

struct
 {
  int  POSL;
  int  PRED;
  char DER[4];
  int  ALT;
 } SINT [ NSINT ] =
/*   __________ _________ _______ _______ ______
    |  NN      :    посл : пред  :  дер  : альт |
    |__________:_________:_______:_______:______|                          */
{
 {/*.    0     .*/    -1 ,    -1 , "***" ,   -1 },
  /*                                               вход с символа - 0      */
 {/*.    1     .*/     2 ,     0 , "0  " ,    0 },
 {/*.    2     .*/     3 ,     1 , "CIF" ,    0 },
 {/*.    3     .*/     0 ,     2 , "*  " ,    0 },
  /*                                               вход с символа - 1      */
 {/*.    4     .*/     5 ,     0 , "1  " ,    0 },
 {/*.    5     .*/     6 ,     4 , "CIF" ,    7 },
 {/*.    6     .*/     0 ,     5 , "*  " ,    0 },

 {/*.    7     .*/     8 ,     4 , "MAN" ,    0 },
 {/*.    8     .*/     0 ,     7 , "*  " ,    0 },
  /*                                               вход с символа - 2      */
 {/*.    9     .*/    10 ,     0 , "2  " ,    0 },
 {/*.   10     .*/    11 ,     9 , "CIF" ,    0 },
 {/*.   11     .*/     0 ,    10 , "*  " ,    0 },
  /*                                               вход с символа - 3      */
 {/*.   12     .*/    13 ,     0 , "3  " ,    0 },
 {/*.   13     .*/    14 ,    12 , "CIF" ,    0 },
 {/*.   14     .*/     0 ,    13 , "*  " ,    0 },
  /*                                               вход с символа - 4      */
 {/*.   15     .*/    16 ,     0 , "4  " ,    0 },
 {/*.   16     .*/    17 ,    15 , "CIF" ,    0 },
 {/*.   17     .*/     0 ,    16 , "*  " ,    0 },
  /*                                               вход с символа - 5      */
 {/*.   18     .*/    19 ,     0 , "5  " ,    0 },
 {/*.   19     .*/    20 ,    18 , "CIF" ,    0 },
 {/*.   20     .*/     0 ,    19 , "*  " ,    0 },
  /*                                               вход с символа - 6      */
 {/*.   21     .*/    22 ,     0 , "6  " ,    0 },
 {/*.   22     .*/    23 ,    21 , "CIF" ,    0 },
 {/*.   23     .*/     0 ,    22 , "*  " ,    0 },
  /*                                               вход с символа - 7      */
 {/*.   24     .*/    25 ,     0 , "7  " ,    0 },
 {/*.   25     .*/    26 ,    24 , "CIF" ,    0 },
 {/*.   26     .*/     0 ,    25 , "*  " ,    0 },
  /*                                               вход с символа - 8      */
 {/*.   27     .*/    28 ,     0 , "8  " ,    0 },
 {/*.   28     .*/    29 ,    27 , "CIF" ,    0 },
 {/*.   29     .*/     0 ,    28 , "*  " ,    0 },
  /*                                               вход с символа - 9      */
 {/*.   30     .*/    31 ,     0 , "9  " ,    0 },
 {/*.   31     .*/    32 ,    30 , "CIF" ,    0 },
 {/*.   32     .*/     0 ,    31 , "*  " ,    0 },
  /*                                               вход с символа - A      */
 {/*.   33     .*/    34 ,     0 , "A  " ,    0 },
 {/*.   34     .*/    35 ,    33 , "BUK" ,    0 },
 {/*.   35     .*/     0 ,    34 , "*  " ,    0 },
  /*                                               вход с символа - B      */
 {/*.   36     .*/    37 ,     0 , "B  " ,    0 },
 {/*.   37     .*/    38 ,    36 , "BUK" ,    0 },
 {/*.   38     .*/     0 ,    37 , "*  " ,    0 },
  /*                                               вход с символа - C      */
 {/*.   39     .*/    40 ,     0 , "C  " ,    0 },
 {/*.   40     .*/    41 ,    39 , "BUK" ,    0 },
 {/*.   41     .*/     0 ,    40 , "*  " ,    0 },
  /*                                               вход с символа - D      */
 {/*.   42     .*/    43 ,     0 , "D  " ,    0 },
 {/*.   43     .*/    44 ,    42 , "BUK" ,   45 },
 {/*.   44     .*/     0 ,    43 , "*  " ,    0 },

 {/*.   45     .*/    46 ,    42 , "C  " ,    0 },
 {/*.   46     .*/    47 ,    45 , "L  " ,    0 },
 {/*.   47     .*/    48 ,    46 , "   " ,    0 },
 {/*.   48     .*/    49 ,    47 , "IDE" ,    0 },
 {/*.   49     .*/    50 ,    48 , "   " ,    0 },
 {/*.   50     .*/    51 ,    49 , "B  " ,  187 },
 {/*.   51     .*/    52 ,    50 , "I  " ,    0 },
 {/*.   52     .*/    53 ,    51 , "N  " ,    0 },
 {/*.   53     .*/    54 ,    52 , "   " ,    0 },
 {/*.   54     .*/    55 ,    53 , "F  " ,    0 },
 {/*.   55     .*/    56 ,    54 , "I  " ,    0 },
 {/*.   56     .*/    57 ,    55 , "X  " ,    0 },
 {/*.   57     .*/    58 ,    56 , "E  " ,    0 },
 {/*.   58     .*/    59 ,    57 , "D  " ,    0 },
 {/*.   59     .*/    60 ,    58 , "(  " ,    0 },
 {/*.   60     .*/    61 ,    59 , "RZR" ,    0 },
 {/*.   61     .*/    62 ,    60 , ")  " ,    0 },
 {/*.   62     .*/    63 ,    61 , ";  " ,   65 },
 {/*.   63     .*/    64 ,    62 , "ODC" ,    0 },
 {/*.   64     .*/    65 ,    63 , "*  " ,    0 },

 {/*.   65     .*/    66 ,    61 , "I  " ,    0 },
 {/*.   66     .*/    67 ,    65 , "N  " ,    0 },
 {/*.   67     .*/    68 ,    66 , "I  " ,    0 },
 {/*.   68     .*/    69 ,    67 , "T  " ,    0 },
 {/*.   69     .*/    70 ,    68 , "(  " ,    0 },
 {/*.   70     .*/    71 ,    69 , "LIT" ,    0 },
 {/*.   71     .*/    72 ,    70 , ")  " ,    0 },
 {/*.   72     .*/    73 ,    71 , ";  " ,    0 },
 {/*.   73     .*/   186 ,    72 , "ODC" ,    0 },
  /*                                               вход с символа - E      */
 {/*.   74     .*/    75 ,     0 , "E  " ,    0 },
 {/*.   75     .*/    76 ,    74 , "N  " ,   82 },
 {/*.   76     .*/    77 ,    75 , "D  " ,    0 },
 {/*.   77     .*/    78 ,    76 , "   " ,    0 },
 {/*.   78     .*/    79 ,    77 , "IPR" ,    0 },
 {/*.   79     .*/    80 ,    78 , ";  " ,    0 },
 {/*.   80     .*/    81 ,    79 , "OEN" ,    0 },
 {/*.   81     .*/     0 ,    80 , "*  " ,    0 },

 {/*.   82     .*/    83 ,    74 , "BUK" ,    0 },
 {/*.   83     .*/     0 ,    82 , "*  " ,    0 },
  /*                                               вход с символа - M      */
 {/*.   84     .*/    85 ,     0 , "M  " ,    0 },
 {/*.   85     .*/    86 ,    84 , "BUK" ,    0 },
 {/*.   86     .*/     0 ,    85 , "*  " ,    0 },
  /*                                               вход с символа - P      */
 {/*.   87     .*/    88 ,     0 , "P  " ,    0 },
 {/*.   88     .*/    89 ,    87 , "BUK" ,    0 },
 {/*.   89     .*/     0 ,    88 , "*  " ,    0 },
  /*                                               вход с символа - X      */
 {/*.   90     .*/    91 ,     0 , "X  " ,    0 },
 {/*.   91     .*/    92 ,    90 , "BUK" ,    0 },
 {/*.   92     .*/     0 ,    91 , "*  " ,    0 },
  /*                                               вход с символа - BUK    */
 {/*.   93     .*/    94 ,     0 , "BUK" ,    0 },
 {/*.   94     .*/    95 ,    93 , "IDE" ,    0 },
 {/*    95     .*/     0 ,    94 , "*  " ,    0 },
  /*                                               вход с символа - IDE    */
 {/*.   96     .*/    97 ,     0 , "IDE" ,    0 },
 {/*.   97     .*/    98 ,    96 , "BUK" ,  100 },
 {/*.   98     .*/    99 ,    97 , "IDE" ,    0 },
 {/*.   99     .*/     0 ,    98 , "*  " ,    0 },

 {/*.  100     .*/   101 ,    96 , "CIF" ,  103 },
 {/*.  101     .*/   102 ,   100 , "IDE" ,    0 },
 {/*.  102     .*/     0 ,   101 , "*  " ,    0 },

 {/*.  103     .*/   104 ,    96 , "IPE" ,  105 },
 {/*.  104     .*/     0 ,   103 , "*  " ,    0 },

 {/*.  105     .*/   106 ,    96 , "IPR" ,    0 },
 {/*.  106     .*/     0 ,   105 , "*  " ,    0 },
  /*                                               вход с символа - +      */
 {/*.  107     .*/   108 ,     0 , "+  " ,    0 },
 {/*.  108     .*/   109 ,   107 , "ZNK" ,    0 },
 {/*.  109     .*/     0 ,   108 , "*  " ,    0 },
  /*                                               вход с символа - -      */
 {/*.  110     .*/   111 ,     0 , "-  " ,    0 },
 {/*.  111     .*/   112 ,   110 , "ZNK" ,    0 },
 {/*.  112     .*/     0 ,   111 , "*  " ,    0 },
  /*                                               вход с символа - IPR    */
 {/*.  113     .*/   114 ,     0 , "IPR" ,    0 },
 {/*.  114     .*/   115 ,   113 , ":  " ,    0 },
 {/*.  115     .*/   116 ,   114 , "P  " ,    0 },
 {/*.  116     .*/   117 ,   115 , "R  " ,    0 },
 {/*.  117     .*/   118 ,   116 , "O  " ,    0 },
 {/*.  118     .*/   119 ,   117 , "C  " ,    0 },
 {/*.  119     .*/   120 ,   118 , "   " ,    0 },
 {/*.  120     .*/   121 ,   119 , "O  " ,    0 },
 {/*.  121     .*/   122 ,   120 , "P  " ,    0 },
 {/*.  122     .*/   123 ,   121 , "T  " ,    0 },
 {/*.  123     .*/   124 ,   122 , "I  " ,    0 },
 {/*.  124     .*/   125 ,   123 , "O  " ,    0 },
 {/*.  125     .*/   126 ,   124 , "N  " ,    0 },
 {/*.  126     .*/   127 ,   125 , "S  " ,    0 },
 {/*.  127     .*/   128 ,   126 , "(  " ,    0 },
 {/*.  128     .*/   129 ,   127 , "M  " ,    0 },
 {/*.  129     .*/   130 ,   128 , "A  " ,    0 },
 {/*.  130     .*/   131 ,   129 , "I  " ,    0 },
 {/*.  131     .*/   132 ,   130 , "N  " ,    0 },
 {/*.  132     .*/   133 ,   131 , ")  " ,    0 },
 {/*.  133     .*/   134 ,   132 , ";  " ,    0 },
 {/*.  134     .*/   135 ,   133 , "OPR" ,    0 },
 {/*.  135     .*/     0 ,   134 , "*  " ,    0 },
 /*                                                вход с символа - CIF    */
 {/*.  136     .*/   137 ,     0 , "CIF" ,    0 },
 {/*.  137     .*/   138 ,   136 , "RZR" ,    0 },
 {/*.  138     .*/     0 ,     0 , "*  " ,    0 },
  /*                                               вход с символа - RZR    */
 {/*.  139     .*/   140 ,     0 , "RZR" ,    0 },
 {/*.  140     .*/   141 ,   139 , "CIF" ,    0 },
 {/*.  141     .*/   142 ,   140 , "RZR" ,    0 },
 {/*.  142     .*/     0 ,   141 , "*  " ,    0 },
  /*                                               вход с символа - MAN    */
 {/*.  143     .*/   144 ,     0 , "MAN" ,    0 },
 {/*.  144     .*/   145 ,   143 , "B  " ,  147 },
 {/*.  145     .*/   146 ,   144 , "LIT" ,    0 },
 {/*.  146     .*/     0 ,   145 , "*  " ,    0 },

 {/*.  147     .*/   148 ,   143 , "0  " ,  150 },
 {/*.  148     .*/   149 ,   147 , "MAN" ,    0 },
 {/*.  149     .*/     0 ,   148 , "*  " ,    0 },

 {/*.  150     .*/   151 ,   143 , "1  " ,    0 },
 {/*.  151     .*/   152 ,   150 , "MAN" ,    0 },
 {/*.  152     .*/     0 ,   151 , "*  " ,    0 },
  /*                                               вход с символа - IPE    */
 {/*.  153     .*/   154 ,     0 , "IPE" ,    0 },
 {/*.  154     .*/   155 ,   153 , "=  " ,  159 },
 {/*.  155     .*/   156 ,   154 , "AVI" ,    0 },
 {/*.  156     .*/   157 ,   155 , ";  " ,    0 },
 {/*.  157     .*/   158 ,   156 , "OPA" ,    0 },
 {/*.  158     .*/     0 ,   157 , "*  " ,    0 },

 {/*.  159     .*/   160 ,   153 , "AVI" ,    0 },
 {/*.  160     .*/     0 ,   159 , "*  " ,    0 },
  /*                                               вход с символа - LIT    */
 {/*.  161     .*/   162 ,     0 , "LIT" ,    0 },
 {/*.  162     .*/   163 ,   161 , "AVI" ,    0 },
 {/*.  163     .*/     0 ,   162 , "*  " ,    0 },
  /*.                                              вход с символа - AVI    */
 {/*.  164     .*/   165 ,     0 , "AVI" ,    0 },
 {/*.  165     .*/   166 ,   164 , "ZNK" ,    0 },
 {/*.  166     .*/   167 ,   165 , "LIT" ,  168 },
 {/*.  167     .*/   197 ,   166 , "AVI" ,    0 },

 {/*.  168     .*/   169 ,   165 , "IPE" ,    0 },
 {/*.  169     .*/   170 ,   168 , "AVI" ,    0 },
 {/*.  170     .*/     0 ,   169 , "*  " ,    0 },
  /*                                               вход с символа - OPR    */
 {/*.  171     .*/   172 ,     0 , "OPR" ,    0 },
 {/*.  172     .*/   173 ,   171 , "TEL" ,    0 },
 {/*.  173     .*/   174 ,   172 , "OEN" ,    0 },
 {/*.  174     .*/   175 ,   173 , "PRO" ,    0 },
 {/*.  175     .*/     0 ,   174 , "*  " ,    0 },
  /*.                                              вход с символа - ODC    */
 {/*.  176     .*/   177 ,     0 , "ODC" ,    0 },
 {/*.  177     .*/   178 ,   176 , "TEL" ,    0 },
 {/*.  178     .*/     0 ,   177 , "*  " ,    0 },
  /*.                                              вход с символа - TEL    */
 {/*.  179     .*/   180 ,     0 , "TEL" ,    0 },
 {/*.  180     .*/   181 ,   179 , "ODC" ,  183 },
 {/*.  181     .*/   182 ,   180 , "TEL" ,    0 },
 {/*.  182     .*/     0 ,   181 , "*  " ,    0 },

 {/*.  183     .*/   184 ,   179 , "OPA" ,    0 },
 {/*.  184     .*/   185 ,   183 , "TEL" ,    0 },
 {/*.  185     .*/     0 ,   184 , "*  " ,    0 },

 {/*.  186     .*/     0 ,    73 , "*  " ,    0 },


 {/*.  187     .*/   188 ,    49 , "C  " ,    0 },
 {/*.  188     .*/   189 ,   187 , "H  " ,    0 },
 {/*.  189     .*/   190 ,   188 , "A  " ,    0 },
 {/*.  190     .*/   191 ,   189 , "R  " ,    0 },
 {/*.  191     .*/   192 ,   190 , "(  " ,    0 },
 {/*.  192     .*/   193 ,   191 , "RZR" ,    0 },
 {/*.  193     .*/   194 ,   192 , ")  " ,    0 },
 {/*.  194     .*/   195 ,   193 , ";  " ,    0 },
 {/*.  195     .*/   196 ,   194 , "ODC" ,    0 },
 {/*.  196     .*/     0 ,   195 , "*  " ,    0 },

 {/*.  197     .*/     0 ,   166 , "*  " ,    0 },

 {/*.  198     .*/   199 ,     0 , "*  " ,    0 },
 {/*.  199     .*/   200 ,   198 , "ZNK" ,    0 },
 {/*.  200     .*/     0 ,   199 , "*  " ,    0 }
};


/*
***** Table of inputs to the ?bushes? (roots) of grammar rules,
***** containing the type (terminality or nonterminality) of the root
***** characters
*/

struct
 {
  char SYM [4];
  int  VX;
  char TYP;
 } VXOD [ NVXOD ] =
/*   __________ ___________ _____ ________
    |  NN      |    Sysbol | input| Type |
    |__________|___________|_____|______| */

{
  {/*.   1     .*/   "AVI" , 164 , 'N' },
  {/*.   2     .*/   "BUK" ,  93 , 'N' },
  {/*.   3     .*/   "CIF" , 136 , 'N' },
  {/*.   4     .*/   "IDE" ,  96 , 'N' },
  {/*.   5     .*/   "IPE" , 153 , 'N' },
  {/*.   6     .*/   "IPR" , 113 , 'N' },
  {/*.   7     .*/   "LIT" , 161 , 'N' },
  {/*.   8     .*/   "MAN" , 143 , 'N' },
  {/*.   9     .*/   "ODC" , 176 , 'N' },
  {/*.  10     .*/   "OEN" ,   0 , 'N' },
  {/*.  11     .*/   "OPA" ,   0 , 'N' },
  {/*.  12     .*/   "OPR" , 171 , 'N' },
  {/*.  13     .*/   "PRO" ,   0 , 'N' },
  {/*.  14     .*/   "RZR" , 139 , 'N' },
  {/*.  15     .*/   "TEL" , 179 , 'N' },
  {/*.  16     .*/   "ZNK" ,   0 , 'N' },
  {/*.  17     .*/   "A  " ,  33 , 'T' },
  {/*.  18     .*/   "B  " ,  36 , 'T' },
  {/*.  19     .*/   "C  " ,  39 , 'T' },
  {/*.  20     .*/   "D  " ,  42 , 'T' },
  {/*.  21     .*/   "E  " ,  74 , 'T' },
  {/*.  22     .*/   "M  " ,  84 , 'T' },
  {/*.  23     .*/   "P  " ,  87 , 'T' },
  {/*.  24     .*/   "X  " ,  90 , 'T' },
  {/*.  25     .*/   "0  " ,   1 , 'T' },
  {/*.  26     .*/   "1  " ,   4 , 'T' },
  {/*.  27     .*/   "2  " ,   9 , 'T' },
  {/*.  28     .*/   "3  " ,  12 , 'T' },
  {/*.  29     .*/   "4  " ,  15 , 'T' },
  {/*.  30     .*/   "5  " ,  18 , 'T' },
  {/*.  31     .*/   "6  " ,  21 , 'T' },
  {/*.  32     .*/   "7  " ,  24 , 'T' },
  {/*.  33     .*/   "8  " ,  27 , 'T' },
  {/*.  34     .*/   "9  " ,  30 , 'T' },
  {/*.  35     .*/   "+  " , 107 , 'T' },
  {/*.  36     .*/   "-  " , 110 , 'T' },
  {/*.  37     .*/   ":  " ,   0 , 'T' },
  {/*.  38     .*/   "I  " ,   0 , 'T' },
  {/*.  39     .*/   "R  " ,   0 , 'T' },
  {/*.  40     .*/   "N  " ,   0 , 'T' },
  {/*.  41     .*/   "O  " ,   0 , 'T' },
  {/*.  42     .*/   "T  " ,   0 , 'T' },
  {/*.  43     .*/   "S  " ,   0 , 'T' },
  {/*.  44     .*/   "(  " ,   0 , 'T' },
  {/*.  45     .*/   ")  " ,   0 , 'T' },
  {/*.  46     .*/   "   " ,   0 , 'T' },
  {/*.  47     .*/   ";  " ,   0 , 'T' },
  {/*.  48     .*/   "L  " ,   0 , 'T' },
  {/*.  49     .*/   "F  " ,   0 , 'T' },
  {/*.  50     .*/   "=  " ,   0 , 'T' },
  {/*.  51     .*/   "H  " ,   0 , 'T' },
  {/*.  52     .*/   "*  " , 198 , 'T' }
};

/*
***** Table of the adjacency matrix - the basis for constructing the matrix
***** successors
*/

char TPR [ NVXOD ] [ NNETRM ] =
 {
/*
   __________ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
  |       AVI:BUK:CIF:IDE:IPE:IPR:LIT:MAN:ODC:OEN:OPA:OPR:PRO:RZR:TEL:ZNK|
  |__________:___:___:___:___:___:___:___:___:___:___:___:___:___:___:___| */
  {/*AVI*/ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*BUK*/ 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*CIF*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0  },
  {/*IDE*/ 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*IPE*/ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0  },
  {/*IPR*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0  },
  {/*LIT*/ 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*MAN*/ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*ODC*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0  },
  {/*OEN*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*OPA*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*OPR*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0  },
  {/*PRO*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*RZR*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0  },
  {/*TEL*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0  },
  {/*ZNK*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
/*
   __________ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
  |       AVI:BUK:CIF:IDE:IPE:IPR:LIT:MAN:ODC:OEN:OPA:OPR:PRO:RZR:TEL:ZNK|
  |__________:___:___:___:___:___:___:___:___:___:___:___:___:___:___:___| */
  {/*  A*/ 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  B*/ 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  C*/ 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  D*/ 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  E*/ 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  M*/ 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  P*/ 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  X*/ 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  0*/ 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  1*/ 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  2*/ 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  3*/ 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  4*/ 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  5*/ 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0  },
  {/*  6*/ 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0  },
  {/*  7*/ 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
/*
   __________ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
  |       AVI:BUK:CIF:IDE;IPE:IPR:LIT:MAN:ODC:OEN:OPA:OPR:PRO:RZR:TEL:ZNK|
  |__________:___:___:___:___:___:___:___:___:___:___:___:___:___:___:___| */
  {/*  8*/ 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  9*/ 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  +*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1  },
  {/*  -*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1  },
  {/*  :*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  I*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  R*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  N*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  O*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  T*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  S*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  (*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  )*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  ;*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*   */ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  L*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
/*
   __________ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
  |       AVI:BUK:CIF:IDE:IPE:IPR:LIT:MAN:ODC:OEN;OPA:OPR:PR0:RZR:TEL:ZNK|
  |__________:___:___:___:___:___:___:___:___:___:___:___:___:___:___:___| */
  {/*  F*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  =*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  H*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0  },
  {/*  **/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1  }
/*|_______________________________________________________________________| */
  };

/*
****** STARTING ON Source Text Processing
*/


void compress_ISXTXT()
 {
  I3 = 0;
  for ( I1 = 0 ; I1 < NISXTXT ; I1++ )
   {
    for ( I2 = 0 ; I2 < 80 ; I2++ )
     if ( ISXTXT [ I1 ][ I2 ] != '\x0' )
      {
       if ( ISXTXT [ I1 ][ I2 ] == ' ' &&
	   ( PREDSYM == ' ' || PREDSYM == ';' ||
	     PREDSYM == ')' || PREDSYM == ':' ||
	     PREDSYM == '('
	   )
	  )
	{
	 PREDSYM = ISXTXT [ I1 ][ I2 ];
	 goto L2;
	}

       if
	 (
	  ( ISXTXT [ I1 ][ I2 ] == '+' ||
	    ISXTXT [ I1 ][ I2 ] == '-' ||
	    ISXTXT [ I1 ][ I2 ] == '=' ||
	    ISXTXT [ I1 ][ I2 ] == '(' ||
	    ISXTXT [ I1 ][ I2 ] == ')' ||
	    ISXTXT [ I1 ][ I2 ] == '*'
	  )
	   &&
	  PREDSYM == ' '
	 )
	{
	 I3-- ;
	 goto L1;
	}


       if ( ISXTXT [ I1 ][ I2 ] == ' ' &&
	   ( PREDSYM == '+' || PREDSYM == '-' ||
	     PREDSYM == '=' || PREDSYM == '*'
	   )
	  )
	{
	 goto L2;
	}

L1:
       PREDSYM = ISXTXT [ I1 ][ I2 ];
       STROKA [ I3 ] = PREDSYM;
       I3++ ;

L2:    continue;
      }
     else
      break;
   }
  STROKA [I3] = '\x0';
 }



void build_TPR ()
  for ( I1 = 0; I1 < NNETRM; I1++ )
   {
    for ( I2 = 0; I2 < NVXOD; I2++ )
     {
      if ( TPR [ I2 ][ I1 ] & ( I1 != I2 ) )
       {
	for ( I3 = 0; I3 < NNETRM; I3++ )
	 TPR [ I2 ][ I3 ] |= TPR [ I1 ][ I3 ];
       }
     }
   }
 }



void mcel ( char* T1, int T2, int T3 )
 {
  strcpy ( CEL [ K ].CEL1, T1 );
  CEL [ K ].CEL2 = T2;
  CEL [ K ].CEL3 = T3;
  K++;
 }



void mdst ( char* T1, int T2, int T3, int T4, int T5 )
 {                              
  strcpy ( DST [ L ].DST1, T1 );
  DST [ L ].DST2 = T2;          
  DST [ L ].DST3 = T3;
  DST [ L ].DST4 = T4;
  DST [ L ].DST5 = T5;
  L++;
 }




int numb ( char* T1, int T2 )
 {
  int k;

  for ( I1 = 0; I1 < NVXOD; I1++ )
   {
    for ( k = 0; k < T2; k++ )
     {
      if ( (*(T1+k) != VXOD [ I1 ].SYM [k] ) )
       goto numb1;
     }
  if ( (VXOD [ I1 ].SYM [k] == '\x0') ||
       (VXOD [ I1 ].SYM [k] == ' '  )
     )
    return ( I1 );
numb1:
    continue;
   }
  return -1;
 }


int sint_ANAL ()                                 
 {                                               
  I4 = 0;

L1:

  K = 0;
  L = 0;
  I = 0;
  J = 1;
  mcel ( "PRO" , I , 999 );

  if (!TPR [numb ( &STROKA [I], 1 )][numb ( "PRO", 3 )])
   return 1;

L2:

  J = VXOD [ numb ( &STROKA [ I ], 1 ) ].VX ;

L3:

  J = SINT [ J ].POSL;

L31:

  I++;

  if ( I > I4 )


   I4 = I;

  if (VXOD [ numb ( SINT [ J ].DER, 3 ) ].TYP == 'T')
   {

    if ( STROKA [ I ] == SINT [ J ].DER [ 0 ] )
     goto L3;
    else
     goto L8;

   }

L4:

  if ( SINT [ SINT [ J ].POSL ].DER [ 0 ] == '*' )
   {
    I--;

    if ( !strcmp (SINT [J].DER, CEL [K-1].CEL1 ) )
     {
      mdst ( CEL[K-1].CEL1,CEL[K-1].CEL2,CEL[K-1].CEL3,I,J );

      if ( !strcmp( CEL[K-1].CEL1 , "PRO" ) )
       return 0;

L5:

      if (TPR [numb (CEL[K-1].CEL1, 3)] [numb (CEL[K-1].CEL1, 3)])
       {
	J = VXOD [ numb ( CEL[K-1].CEL1, 3 ) ].VX;
	goto L3;
       }

L6:

      J = CEL[K-1].CEL3;
      K--;
      goto L3;
     }

    if (!TPR [numb (SINT[J].DER, 3)] [numb (CEL[K-1].CEL1, 3)])
     goto L9;

    mdst ( SINT[J].DER, CEL[K-1].CEL2,0,I,J );
    J = VXOD [numb (SINT[J].DER, 3)].VX;
    goto L3;
   }

  if (!TPR [numb (&STROKA [I], 1)] [numb (SINT[J].DER, 3)])
   goto L8;

  mcel ( SINT[J].DER,I,J );
  goto L2;

L8:

  I--;

L9:

  if (SINT[J].ALT != 0)
   {
    J = SINT[J].ALT;
    goto L31;
   }

  J = SINT[J].PRED;

  if
   (
    ( VXOD [numb (SINT[J].DER, 3)].TYP == 'N' )
    &&
    ( SINT[J].PRED > 0 )
   )
   {
    mcel (DST[L-1].DST1, DST[L-1].DST2, DST[L-1].DST3);

L10:

    J = DST[L-1].DST5;
    L--;
    goto L9;
   }

  if
   (
    ( VXOD [numb (SINT[J].DER, 3)].TYP == 'N' )
    &&
    ( SINT[J].PRED == 0 )
   )
   {
    if (!strcmp ( CEL[K-1].CEL1, DST[L-1].DST1 ) )
     goto L6;
    else
     goto L10;
   }

  if ( SINT[J].PRED > 0 )
   goto L8;

  J = CEL[K-1].CEL3;
  K--;

  if ( J == 999 )
   return 2;
  else
   goto L8;

 }



struct           
 {               
  char NAME [8]; 
  char TYPE;     
  char RAZR [5]; 
  char INIT [50];
 } SYM [ NSYM ]; 

int ISYM = 0;
char NFIL [30]="\x0";



long int VALUE ( char* s )
 {                        
  long int S;             
  int i;                  

  i = 0;
  S = 0;
  while ( *(s + i) != 'B' )

   {

    S <<= 1;
    if ( *(s + i) == '1' )
     S++;
    i++;
   }

  return (S);
 }




void FORM ()                                      
 {                                                

  int i,j;

  for ( IFORMT = 0; IFORMT < MAXFORMT; IFORMT++ )
   memcpy ( FORMT [IFORMT], "\x0\x0\x0\x0\x0\x0\x0\x0\x0", 9 );

  IFORMT = 0;
  j = DST [I2].DST2;

FORM1:

  for ( i = j; i <= DST [I2].DST4+1; i++ )
   {
     if ( STROKA [i] == ':' || STROKA [i] == ' ' ||
	  STROKA [i] == '(' || STROKA [i] == ')' ||
	  STROKA [i] == ';' || STROKA [i] == '+' ||
	  STROKA [i] == '-' || STROKA [i] == '=' ||
	  STROKA [i] == '*'
	)
	{
	 FORMT [IFORMT] [i-j] = '\x0';
	 IFORMT ++;
	 j = i+1;
	 goto FORM1;
	}
     else
	 FORMT [IFORMT][i-j] = STROKA [i];

   }

  return;
 }


void ZKARD ()                                     
 {                                                

  char i;
  memcpy ( ASSTXT [ IASSTXT++ ],
			   ASS_CARD.BUFCARD, 80 );

  for ( i = 0; i < 79; i++ )
   ASS_CARD.BUFCARD [i] = ' ';
  return;
 }


int AVI1 ()
 {
  return 0;
 }



int BUK1 ()
 {
  return 0;
 }



int CIF1 ()
 {
  return 0;
 }


int IDE1 ()
 {
  return 0;
 }
int IPE1 ()
 {
  return 0;
 }
int IPR1 ()
 {
  return 0;
 }
int LIT1 ()
 {
  return 0;
 }
int MAN1 ()
 {
  return 0;
 }
int ODC1 ()
 {
  int i;
  FORM ();                                        
  
  for ( i = 0; i < ISYM; i++ )                    
   {                                              
    if (  !strcmp ( SYM [i].NAME, FORMT [1] ) &&  
	  strlen ( SYM [i].NAME ) ==              
			     strlen ( FORMT [1] )
       )
     return 6;                                    

   }

  strcpy ( SYM [ISYM].NAME, FORMT [1] );          
  strcpy ( SYM [ISYM].RAZR, FORMT [4] );          




  if ( !strcmp ( FORMT [2], "BIN" ) &&            
		  !strcmp ( FORMT [3], "FIXED" ) )
   {
    SYM [ISYM].TYPE = 'B';                        

    goto ODC11;                                   

   }
  else                                            
   {
    SYM [ISYM].TYPE = 'U';                        

    return 2;                                     

   }

ODC11:                                            

  if ( !strcmp ( FORMT [5], "INIT" )  )           
   strcpy ( SYM [ISYM++].INIT, FORMT [6] );       

  else                                            
   strcpy ( SYM [ISYM++].INIT, "0B" );            


   return 0;                                      

 }


int OEN1 ()
 {
  char i = 0;
  FORM ();                                        
  for ( i = 0; i < ISYM; i++ )                    
   {                                              
    if ( !strcmp ( SYM [i].NAME, FORMT [1] ) &&
		       (SYM [i].TYPE == 'P') &&
		       strlen (SYM [i].NAME) ==
			strlen ( FORMT [1] ) )
     return 0;                                    
   }
  return 1;                                       
 }

int OPA1 ()
 {
  return 0;
 }

int OPR1 ()
 {
  FORM ();                                        
  strcpy ( SYM [ISYM].NAME, FORMT [0] );          
  SYM [ISYM].TYPE   = 'P';                        
  SYM [ISYM++].RAZR [0] = '\x0';                  
  return 0;                                       
 }

int PRO1 ()
 {
  return 0;
 }

int RZR1 ()
 {
  return 0;
 }

int TEL1 ()
 {
  return 0;
 }

int ZNK1 ()
 {
  return 0;
 }

int AVI2 ()
 {
  char i;
  FORM ();

  if ( IFORMT == 1 )                              
     {                                            
    for ( i = 0; i < ISYM; i++ )                  
     {                                            
      if ( !strcmp ( SYM [i].NAME, FORMT [0] )  &&
	   strlen ( SYM [i].NAME ) ==
			      strlen ( FORMT [0] )
	 )
       {
	  if ( SYM [i].TYPE == 'B' )              
	   {

	    if ( strcmp ( SYM [i].RAZR, "15" )    
					     <= 0 )
	     memcpy ( ASS_CARD._BUFCARD.OPERAC,   
					"LH", 2 );
	    else
	     memcpy ( ASS_CARD._BUFCARD.OPERAC,   
					 "L", 1 );


	    strcpy ( ASS_CARD._BUFCARD.OPERAND,   
					"RRAB," );
	    strcat ( ASS_CARD._BUFCARD.OPERAND,   
				       FORMT [0]);

	    ASS_CARD._BUFCARD.OPERAND [ strlen    
	     ( ASS_CARD._BUFCARD.OPERAND ) ] = ' ';

	    memcpy ( ASS_CARD._BUFCARD.COMM,      
	     "Load var into register", 29 );

	    ZKARD ();                             

	    return 0;                             
	   }
	  else
	   return 3;                              


       }
     }
    return 4;                                     
   } else {
    for ( i = 0; i < ISYM; i++ )                  
     {                                            
      if ( !strcmp ( SYM [i].NAME, FORMT [IFORMT-1] )  && strlen ( SYM [i].NAME ) == strlen ( FORMT [IFORMT-1] ))
      {
        if ( SYM [i].TYPE == 'B' )              
        {                                      
          if ( STROKA [ DST [I2].DST4 - strlen( FORMT [IFORMT-1] ) ] == '+' )
          {
            if ( strcmp ( SYM [i].RAZR, "15" )  
                  <= 0 )
            memcpy ( ASS_CARD._BUFCARD.OPERAC,
              "AH", 2 );
            else                                
            memcpy ( ASS_CARD._BUFCARD.OPERAC,
              "A", 1 );
          }

          else
          {
            if ( STROKA [ DST [I2].DST4 - strlen ( FORMT [IFORMT-1] ) ] == '-' )
            {
              if ( strcmp ( SYM [i].RAZR, "15" ) <= 0 )
                memcpy( ASS_CARD._BUFCARD.OPERAC,"SH", 2 );
              else
                memcpy( ASS_CARD._BUFCARD.OPERAC, "S", 1 );
            }

            else
            return 5;                          
          }

          strcpy ( ASS_CARD._BUFCARD.OPERAND, "RRAB," );
          strcat ( ASS_CARD._BUFCARD.OPERAND, FORMT [IFORMT-1] );
          ASS_CARD._BUFCARD.OPERAND [ strlen( ASS_CARD._BUFCARD.OPERAND )] = ' ';
          memcpy ( ASS_CARD._BUFCARD.COMM, "Formation of intermediate value", 36 );
          ZKARD ();                             

          return 0;                             
	      }
        else
        return 3;                              
      }
     }
    return 4;                                     
   }
 }

int BUK2 ()
 {
  return 0;
 }

int CIF2 ()
 {
  return 0;
 }

int IDE2 ()
 {
  return 0;
 }

int IPE2 ()
 {
  return 0;
 }

int IPR2 ()
 {
  return 0;
 }


int LIT2 ()
 {
  return 0;
 }


int MAN2 ()
 {
  return 0;
 }

int ODC2 ()
 {
  return 0;
 }

int OEN2 ()
 {
  char RAB [20];
  char i = 0;
  FORM ();                                        

  memcpy ( ASS_CARD._BUFCARD.OPERAC, "BCR", 3 );  
  memcpy ( ASS_CARD._BUFCARD.OPERAND,"15,14", 5 );
  memcpy ( ASS_CARD._BUFCARD.COMM, "Exit the program", 18 );
  ZKARD ();                                       

  for ( i = 0; i < ISYM; i++ )
   {                                              
    if ( isalpha ( SYM [i].NAME [0] ) )           

     {                                            
      if ( SYM [i].TYPE == 'B' )                  

       {
	strcpy ( ASS_CARD._BUFCARD.METKA,         
				  SYM [i].NAME ); 

	ASS_CARD._BUFCARD.METKA [ strlen
	     ( ASS_CARD._BUFCARD.METKA ) ] = ' '; 

	memcpy ( ASS_CARD._BUFCARD.OPERAC,        
				       "DC", 2 ); 

	if ( strcmp ( SYM [i].RAZR, "15" ) <= 0 ) 

	 strcpy ( ASS_CARD._BUFCARD.OPERAND,      
					 "H\'" );
	else                                      

	 strcpy ( ASS_CARD._BUFCARD.OPERAND,      					 "F\'" );

//Dos command
//	strcat ( ASS_CARD._BUFCARD.OPERAND,       
//		 ltoa ( VALUE (SYM [i].INIT),     
//				 &RAB [0], 10) ); 
//let's do that in Unix!
	strcat(ASS_CARD._BUFCARD.OPERAND, gcvt(VALUE(SYM[i].INIT), 10, &RAB[0]));
	ASS_CARD._BUFCARD.OPERAND [ strlen        
	 ( ASS_CARD._BUFCARD.OPERAND ) ] = '\'';  

	memcpy ( ASS_CARD._BUFCARD.COMM,          
		 "Define var", 22 );  

	ZKARD ();                                 

       }
     }
   }

  memcpy ( ASS_CARD._BUFCARD.METKA, "RBASE", 5 ); 
  memcpy ( ASS_CARD._BUFCARD.OPERAC, "EQU",3 );   
  memcpy ( ASS_CARD._BUFCARD.OPERAND, "15", 2 );  


  ZKARD ();                                       

  memcpy ( ASS_CARD._BUFCARD.METKA, "RRAB", 4 );  
  memcpy ( ASS_CARD._BUFCARD.OPERAC, "EQU",3 );   
  memcpy ( ASS_CARD._BUFCARD.OPERAND, "5", 1 );   


  ZKARD ();                                       

  memcpy ( ASS_CARD._BUFCARD.OPERAC, "END", 3 );  


  i = 0;

  while ( FORMT [1][i] != '\x0' )                 
   ASS_CARD._BUFCARD.OPERAND [i] = FORMT [1][i++];

  memcpy ( ASS_CARD._BUFCARD.COMM,                
			  "End of Program", 15 );

  ZKARD ();                                       


  return 0;                                       
 }










int OPA2 ()
 {
  int i;

  FORM ();                                        


  for ( i = 0; i < ISYM; i++ )
   {                                              

    if ( !strcmp ( SYM [i].NAME, FORMT [0] )  &&  
	 strlen ( SYM [i].NAME ) ==               
			     strlen ( FORMT [0] )
       )
       {
	  if ( SYM [i].TYPE == 'B' )              
	   {                                      

	    if ( strcmp ( SYM [i].RAZR, "15" )    
					    <= 0 )
	     memcpy ( ASS_CARD._BUFCARD.OPERAC,   
				       "STH", 3 );

	    else                                  
	     memcpy ( ASS_CARD._BUFCARD.OPERAC,   
					"ST", 2 );

	    strcpy ( ASS_CARD._BUFCARD.OPERAND,   
					"RRAB," );

	    strcat ( ASS_CARD._BUFCARD.OPERAND,   
				      FORMT [0]) ;

	    ASS_CARD._BUFCARD.OPERAND [ strlen    
	    ( ASS_CARD._BUFCARD.OPERAND ) ] = ' ';

	    memcpy ( ASS_CARD._BUFCARD.COMM,"Generating the value of arithmetic expression", 37 );
	    ZKARD ();                             

	    return 0;                             
	   }

	  else                                    

	   return 3;                              

       }
   }
  return 4;                                       





 }


int OPR2 ()
 {
  char i = 0;
  FORM ();                                        


  while ( FORMT [0][i] != '\x0' )
   ASS_CARD._BUFCARD.METKA [i++] = FORMT [0][i];  


  memcpy ( ASS_CARD._BUFCARD.OPERAC, "START", 5 );
  memcpy ( ASS_CARD._BUFCARD.OPERAND, "0", 1 );   
  memcpy ( ASS_CARD._BUFCARD.COMM,"PROGRAM START", 16 );
  ZKARD ();                                       


  memcpy ( ASS_CARD._BUFCARD.OPERAC, "BALR", 4 ); 
  memcpy ( ASS_CARD._BUFCARD.OPERAND,"RBASE,0", 7 );
  memcpy ( ASS_CARD._BUFCARD.COMM, "Load base register", 22 );
  ZKARD ();                                       

  memcpy ( ASS_CARD._BUFCARD.OPERAC, "USING", 5 );
  memcpy ( ASS_CARD._BUFCARD.OPERAND,"*,RBASE", 7 );
  memcpy ( ASS_CARD._BUFCARD.COMM,"Set register as base", 23 );
  ZKARD ();                                       

  return 0;                                       
 }


int PRO2 ()                                       
 {                                                

  FILE *fp;                                       



  strcat ( NFIL , "ass" );                        


  if ( (fp = fopen ( NFIL , "wb" )) == NULL )     
   return (7);                                    

  else                                            
   fwrite (ASSTXT, 80 , IASSTXT , fp);            
  fclose ( fp );                                  
  return ( 0 );                                   
 }

int RZR2 ()
 {
  return 0;
 }


int TEL2 ()
 {
  return 0;
 }


int ZNK2 ()
 {
  return 0;
 }


int gen_COD ()                                    
{                                                
  int NOSH;                                       
  int (* FUN [NNETRM][2]) () =                    
  {
     {/*    1  */    AVI1, AVI2 },
     {/*    2  */    BUK1, BUK2 },
     {/*    3  */    CIF1, CIF2 }
     {/*    4  */    IDE1, IDE2 },
     {/*    5  */    IPE1, IPE2 },
     {/*    6  */    IPR1, IPR2 }
     {/*    7  */    LIT1, LIT2 },
     {/*    8  */    MAN1, MAN2 },
     {/*    9  */    ODC1, ODC2 },
     {/*   10  */    OEN1, OEN2 }
     {/*   11  */    OPA1, OPA2 },
     {/*   12  */    OPR1, OPR2 },
     {/*   13  */    PRO1, PRO2 },
     {/*   14  */    RZR1, RZR2 }
     {/*   15  */    TEL1, TEL2 }
     {/*   16  */    ZNK1, ZNK2 }
  };

  for ( I2 = 0; I2 < L; I2++ )                    
   if ( ( NOSH = FUN [                            
		      numb ( DST [I2].DST1, 3 )   
		     ][0] ()
	) != 0
      )
    return (NOSH);                                


  for ( I2 = 0; I2 < L; I2++ )                    
   if ( ( NOSH = FUN [                            
		      numb ( DST [I2].DST1, 3 )   
		     ][1] ()
	) != 0
      )
    return (NOSH);                                


  return 0;                                       

 }



int main (int argc, char **argv )
 {                                                
  FILE *fp;                                       
  char *ptr=argv[1];                              


  strcpy ( NFIL, ptr );                           





  if ( argc != 2 )

   {                                              
    printf ("%s\n", "Command line error. Number of arguments should be 2!"); 
    return;                                       
   }


  if
   (
    strcmp ( &NFIL [ strlen ( NFIL )-3 ], "pli" ) 
   )

   {
    printf ( "%s\n",                              
     "Invalid source file type" );
    return;                                       
   }


  else                                            
  {                                              
  if ( (fp = fopen ( NFIL , "rb" )) == NULL )   
  {
    printf ( "%s\n",
      "File not found!" );
    return;
  }
  else
    {
    for ( NISXTXT = 0; NISXTXT <= MAXNISXTXT; NISXTXT++ ){
      if ( !fread ( ISXTXT [NISXTXT], 80, 1, fp ) ) {
        if ( feof ( fp ) )                      
        goto main1;                            

        else
        {
          printf ( "%s\n",
          "Reading Error!" );
          return;                               
        }
      }
    }
    printf ( "%s\n", "Source text read buffer overflow" ); 
    return;                                     
    }
  }

main1:                                            
   fclose ( fp );                                 
   NFIL [ strlen ( NFIL )-3 ] = '\x0';            

  memset ( ASS_CARD.BUFCARD, ' ', 80 );           
  compress_ISXTXT ();                             

  build_TPR ();                                   


  if ( (sint_ANAL ()) )                           
   {                                              
     STROKA [I4 +20] = '\x0';
     printf                                       
      (                                           
       "%s%s%s%s\n",
       "Syntax error in source text: -> ",      
       "\"...",&STROKA [I4], "...\""
      );
     printf
      (
       "%s\n", "Translation interrupted!"
      );
     return;                                      
   }
  else                                            
   {
    switch ( gen_COD () )                         
     {
      case  0:                                    
       printf ( "%s\n",	"Translation completed successfully! ^^" );
       return;                                    

      case  1:                                    
       printf ( "%s\n",	"procedure name mismatch in prologue-epilogue" );
       break;                                     

      case  2:                                    
       STROKA [ DST [I2].DST2 +20 ] = '\x0';      
       printf ( "%s%s\n%s%s%s\n",	"invalid identifier type: ",	 &FORMT [1], " in source file -> \"...",	  &STROKA [ DST [I2].DST2 ], "...\"" );
       break;                                     


      case  3:                                    
       STROKA [ DST [I2].DST2 + 20 ] = '\x0';     
       printf ( "%s%s\n%s%s%s\n",	"invalid identifier type: ",	  &FORMT [IFORMT-1], " in source file -> \"...",	   &STROKA [ DST [I2].DST2 ], "...\"" );
       break;                                     


      case  4:                                    
       STROKA [ DST [I2].DST2 + 20 ] = '\x0';     
       printf ( "%s%s\n%s%s%s\n",	"undefined identifier: ",	 &FORMT [IFORMT-1], " here -> \"...",	  &STROKA [ DST [I2].DST2 ], "...\"" );
       break;                                     


      case  5:                                    
       STROKA [ DST [I2].DST2 + 20 ] = '\x0';     
       printf ( "%s%c\n%s%s%s\n",	"undefined operation: ",	 STROKA [ DST [I2].DST4 - strlen ( FORMT [IFORMT-1] ) ],	 " here -> \"...", &STROKA [ DST [I2].DST2 ], "...\"");
       break;                                     


      case  6:                                    
       STROKA [ DST [I2].DST2 + 20 ] = '\x0';     
       printf ( "%s%s\n%s%s%s\n",	"re-declaration of identifier: ",	 &FORMT [1], " here -> \"...", &STROKA [ DST [I2].DST2 ], "...\"" );
       break;                                     
     }

   }

  printf ( "%s\n", "[FAIL]Translation interrupted!" );       
	
  return 0;
}

