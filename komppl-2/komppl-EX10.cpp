#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "komppl.h"

/*..........................................................................*/
/*****************************************
 * Н А Ч А Л О  обработки исходного текста
 *****************************************/
/*..........................................................................*/



/* ///////////////////////////////////////////////////////////////// */

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала AVI на вто-*/
              /* ром проходе.   Здесь   */
              /* AVI -   "арифм.выраж." */


int AVI2()
{
  fprintf(fp_out, "%s\n", "AVI2");
  fflush(fp_out);
  char i;
  FORM();                                        /*форматируем правую часть*/
  /*арифметического ПЛ1-опе-*/
  /*ратора присваивания     */

  if (IFORMT == 1)                              /* если правая часть одно-*/
  {                                            /* термовая, то:          */
    for (i = 0; i < ISYM; i++)                  /* ищем этот терм в табли-*/
    {                                            /* це имен  и             */
      if (!strcmp(SYM[i].NAME, FORMT[0]) &&/* если находим, то:      */
        strlen(SYM[i].NAME) ==
        strlen(FORMT[0])
        )
      {
        if (SYM[i].TYPE == 'B')              /* в случае типа=bin fixed*/
        {

          if (strcmp(SYM[i].RAZR, "15")    /* и разрядности <= 15    */
            <= 0)
            memcpy(ASS_CARD._BUFCARD.OPERAC,   /* формируем код ассембле-*/
              "LH", 2);/* ровской операции LH,   */
          else
            memcpy(ASS_CARD._BUFCARD.OPERAC,   /* а при разрядности >15  */
              "L", 1);/* формируем код ассембле-*/
          /* ровской операции L     */

          strcpy(ASS_CARD._BUFCARD.OPERAND,   /*       формируем        */
            "RRAB,");/*       первый  и        */
          strcat(ASS_CARD._BUFCARD.OPERAND,   /* второй операнды ассемб-*/
            FORMT[0]);/* леровской операции     */

          ASS_CARD._BUFCARD.OPERAND[strlen    /* вставляем разделитель  */
          (ASS_CARD._BUFCARD.OPERAND)] = ' ';

          memcpy(ASS_CARD._BUFCARD.COMM,      /* и построчный коментарий*/
            "Load var into register", 29);

          ZKARD();                             /* запомнить операцию ас- */
          /* семблера  и            */
          return 0;                             /* завершить программу    */
        }
        else
          return 3;                              /* если тип терма не bin  */
        /* fixed,то выход по ошибке*/        
      }
    }
    return 4;                                     /* если терм-идентификатор*/
    /* неопределен, то выход  */
    /* по ошибке              */
  }
  else                                            /* если правая часть ариф-*/
              /* метического выражения  */
              /* двухтермовая, то:      */
  {
    for (i = 0; i < ISYM; i++)                  /* если правый терм ариф- */
    {                                            /* метического выражения  */
      if (!strcmp(SYM[i].NAME,                /*определен в табл.SYM,то:*/
        FORMT[IFORMT - 1]) &&
        strlen(SYM[i].NAME) ==
        strlen(FORMT[IFORMT - 1])
        )
      {
        if (SYM[i].TYPE == 'B')              /* если тип правого опе-  */
        {                                      /* ранда bin fixed, то:   */

          if (STROKA[DST[I2].DST4 -         /* если знак опер."+",то: */
            strlen(FORMT[IFORMT - 1])] == '+')
          {
            if (strcmp(SYM[i].RAZR, "15")  /* если разрядность прав. */
              <= 0)/* операнда <= 15, то:    */
              memcpy(ASS_CARD._BUFCARD.OPERAC,
                "AH", 2);/* формируем код ассембле-*/
            else                                /* ровской операции "AH",а*/
              memcpy(ASS_CARD._BUFCARD.OPERAC,
                "A", 1);/* иначе - "A"            */
          }

          else

          {
            if (STROKA[DST[I2].DST4 -       /* если же знак операции  */
              strlen(FORMT[IFORMT - 1])] == /* арифметического выра-  */
              '-')/* жения "-", то:         */

            {
              if (strcmp(SYM[i].RAZR, "15")/* при разрядности ариф-  */
                <= 0)/* метич.выраж.<= 15      */
                memcpy(ASS_CARD._BUFCARD.OPERAC,/* формируем код ассембле-*/
                  "SH", 2);/* ровской операции "SH",F*/
              else
                memcpy(ASS_CARD._BUFCARD.OPERAC,/* иначе - "S"            */
                  "S", 1);
            }

            else

              return 5;                          /* если знак операции не  */
            /* "+" и не "-", то завер-*/
            /* шение  программы  по   */
            /* ошибке                 */
          }
          /* формируем:             */
          strcpy(ASS_CARD._BUFCARD.OPERAND,   /* - первый операнд ассем-*/
            "RRAB,");/*блеровской операции;    */
          strcat(ASS_CARD._BUFCARD.OPERAND,   /* - второй операнд ассем-*/
            FORMT[IFORMT - 1]);/*блеровской операции;    */
          ASS_CARD._BUFCARD.OPERAND[strlen
          (ASS_CARD._BUFCARD.OPERAND)] =/* - разделяющий пробел;  */
            ' ';
          memcpy(ASS_CARD._BUFCARD.COMM,
            "Formation of intermediate value",/* - построчный коментарий*/
            36);
          ZKARD();                             /* запоминание ассембле-  */
          /* ровской операции       */

          return 0;                             /* успешное завершение    */
          /* пограммы               */
        }
        else
          return 3;                              /* если тип правого опе-  */
        /* ранда арифметического  */
        /* выражения не bin fixed,*/
        /* то завершение програм- */
        /* мы по ошибке           */
      }
    }
    return 4;                                     /* если правый операнд    */
    /* арифметического выраже-*/
    /*ния не определен в табл.*/
    /* SYM, то завершить про- */
    /* грамму по ошибке       */
  }

}

/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала BUK на вто-*/
              /* ром проходе.   Здесь   */
              /* BUK -   "буква"        */

int BUK2()
{
  fprintf(fp_out, "%s\n", "BUK2");
  fflush(fp_out);

  return 0;
}

/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала CIF на вто-*/
              /* ром проходе.   Здесь   */
              /* CIF -   "цифра"        */

int CIF2()
{
  fprintf(fp_out, "%s\n", "CIF2");
  fflush(fp_out);

  return 0;
}

/*..........................................................................*/


              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала IDE на вто-*/
              /* ром проходе.   Здесь   */
              /* IDE -   "идентификатор"*/

int IDE2()
{
  fprintf(fp_out, "%s\n", "IDE2");
  fflush(fp_out);

  return 0;
}


/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала IPE на вто-*/
              /* ром проходе.   Здесь   */
              /* IPE - "имя переменной" */

int IPE2()
{
  fprintf(fp_out, "%s\n", "IPE2");
  fflush(fp_out);

  return 0;
}

/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала IPR на вто-*/
              /* ром проходе.   Здесь   */
              /* IPR -   "имя программы" */

int IPR2()
{
  fprintf(fp_out, "%s\n", "IPR2");
  fflush(fp_out);

  return 0;
}

/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала LIT на вто-*/
              /* ром проходе.   Здесь   */
              /* LIT -   "литерал"      */

int LIT2()
{
  fprintf(fp_out, "%s\n", "LIT2");
  fflush(fp_out);

  return 0;
}

/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала MAN на вто-*/
              /* ром проходе.   Здесь   */
              /* MAN -   "мантисса"     */

int MAN2()
{
  fprintf(fp_out, "%s\n", "MAN2");
  fflush(fp_out);

  return 0;
}

/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала ODC на вто-*/
              /* ром проходе.   Здесь   */
              /* ODC - "операт.ПЛ1- DCL"*/

int ODC2()
{
  fprintf(fp_out, "%s\n", "ODC2");
  fflush(fp_out);

  return 0;
}

/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала OEN на вто-*/
              /* ром проходе.   Здесь   */
              /* OEN - "операт.ПЛ1-END" */

              /* программа    формирует */
              /* эпилог ассемблеровского*/
              /* эквивалента ПЛ1-прог-  */
              /* раммы                  */
int OEN2()
{
  fprintf(fp_out, "%s\n", "OEN2");
  fflush(fp_out);

  char RAB[20];
  char i = 0;
  FORM();                                        /* форматируем ПЛ1-опера- */
  /* тор END                */

  memcpy(ASS_CARD._BUFCARD.OPERAC, "BCR", 3);  /* формируем код безуслов-*/
  /*ного возврата управления*/
  /* в вызывающую программу */

  memcpy(ASS_CARD._BUFCARD.OPERAND, "15,14", 5);/* операнды команды и     */

  memcpy(ASS_CARD._BUFCARD.COMM,                /* поле построчного комен-*/
    "Exit from program", 18);/* тария                  */

  ZKARD();                                       /* запомнить опреацию Ассемблера */
  
  /* далее идет блок форми- */
  /* рования декларативных  */
  /* псевдоопераций DC для  */
  /* каждого идентификатора,*/
  /* попавшего в табл.SYM   */
  for (i = 0; i < ISYM; i++)
  {  
    if (isalpha(SYM[i].NAME[0])) /* если строка табл.SYM содержит идентификатор, */
      /* т.е.начинается с буквы,*/
    {                                            /* то:                    */
      if (SYM[i].TYPE == 'B')                  /* если тип оператора bin */
        /* fixed, то:             */
      {
        strcpy(ASS_CARD._BUFCARD.METKA,         /* пишем идентификатор в  */
          SYM[i].NAME); /* поле метки псевдоопера-*/
        /* ции DC                 */
        ASS_CARD._BUFCARD.METKA[strlen
        (ASS_CARD._BUFCARD.METKA)] = ' '; /* пишем разделитель полей*/

        memcpy(ASS_CARD._BUFCARD.OPERAC, "DC", 2);       /* пишем код псевдооперации DC */
           

        if (strcmp(SYM[i].RAZR, "15") <= 0) /* формируем операнды псевдооперации DC */          
          strcpy(ASS_CARD._BUFCARD.OPERAND, "H\'");     /* для случая полуслова   */
            
        else                                      /* или для случая слова */
          strcpy(ASS_CARD._BUFCARD.OPERAND, "F\'");

        //Dos command
        //	strcat ( ASS_CARD._BUFCARD.OPERAND,       /* формируем цифровую     */
        //		 ltoa ( VALUE (SYM [i].INIT),     /* часть операнда псевдо- */
        //				 &RAB [0], 10) ); /* операции,              */
        //let's do that in Unix!
        strcat(ASS_CARD._BUFCARD.OPERAND, gcvt(VALUE(SYM[i].INIT), 10, &RAB[0]));
        ASS_CARD._BUFCARD.OPERAND[strlen        /* замыкающий апостроф    */
        (ASS_CARD._BUFCARD.OPERAND)] = '\'';  /*          и             */

        memcpy(ASS_CARD._BUFCARD.COMM,          /* поле построчного комен-*/
          "Defination of var", 22);  /* тария                  */

        ZKARD();                                 /* запомнить операцию     */
        /*    Ассемблера          */
      }
    }
  }
  /* далее идет блок декла- */
  /* ративных ассемблеровс- */
  /* ких EQU-операторов, оп-*/
  /* ределяющих базовый и   */
  /* рабочий регистры общего*/
  /* назначения             */

  memcpy(ASS_CARD._BUFCARD.METKA, "RBASE", 5); /* формирование EQU-псев- */
  memcpy(ASS_CARD._BUFCARD.OPERAC, "EQU", 3);   /* дооперации определения */ /* 这里似乎被执行了两次？*/
  memcpy(ASS_CARD._BUFCARD.OPERAND, "15", 2);  /* номера базового регистра общего назначения*/  
  /*           и            */
  ZKARD();                                       /* запоминание ее         */

  memcpy(ASS_CARD._BUFCARD.METKA, "RRAB", 4);  /* формирование EQU-псев- */
  memcpy(ASS_CARD._BUFCARD.OPERAC, "EQU", 3);   /* дооперации определения */
  memcpy(ASS_CARD._BUFCARD.OPERAND, "5", 1);   /* номера базового регист-*/
  /* ра общего назначения   */
  /*            и           */
  ZKARD();                                       /* запоминание ее         */

  memcpy(ASS_CARD._BUFCARD.OPERAC, "END", 3);  /* формирование кода ас-  */
  /* семблеровской псевдо-  */
  /* операции END,          */
  i = 0;

  while (FORMT[1][i] != '\x0')                 /* ее операнда            */
    ASS_CARD._BUFCARD.OPERAND[i] = FORMT[1][i++];/*         и              */

  memcpy(ASS_CARD._BUFCARD.COMM,                /* построчного коментария */
    "End of program", 15);

  ZKARD();                                       /* запоминание псевдооперации*/  
  return 0;                                       /* завершение программы   */
}

/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала OPA на вто-*/
              /* ром проходе.   Здесь   */
              /* OPA - "операт.присваи- */
              /* вания арифметический   */

int OPA2()
{
  fprintf(fp_out, "%s\n", "OPA2");
  fflush(fp_out);

  int i;

  FORM();                                        /*форматируем ПЛ1-оператор*/
  /*присваивания арифметич. */

  for (i = 0; i < ISYM; i++)
  {                                              /* если идентификатор пра-*/
             /* вой части оператора оп-*/
    if (!strcmp(SYM[i].NAME, FORMT[0]) &&  /* ределен ранее через    */
      strlen(SYM[i].NAME) ==               /* оператор DCL, то:      */
      strlen(FORMT[0])
      )
    {
      if (SYM[i].TYPE == 'B')              /* если этот идентификатор*/
      {                                      /* имеет тип bin fixed,то:*/

        if (strcmp(SYM[i].RAZR, "15")    /* если bin fixed (15),то:*/
          <= 0)
          memcpy(ASS_CARD._BUFCARD.OPERAC,   /* сформировать команду   */
            "STH", 3);/* записи полуслова       */

        else                                  /* иначе:                 */
          memcpy(ASS_CARD._BUFCARD.OPERAC,   /* команду записи слова   */
            "ST", 2);

        strcpy(ASS_CARD._BUFCARD.OPERAND,   /*       доформировать    */
          "RRAB,");/*          операнды      */

        strcat(ASS_CARD._BUFCARD.OPERAND,   /*           команды      */
          FORMT[0]);

        ASS_CARD._BUFCARD.OPERAND[strlen    /*              и         */
        (ASS_CARD._BUFCARD.OPERAND)] = ' ';

        memcpy(ASS_CARD._BUFCARD.COMM,      /* построчный коментарий  */
          "Generate value of arithmetic express",
          37);
        ZKARD();                             /* запомнить операцию     */
        /* Ассемблера  и          */
        return 0;                             /* завершить программу    */
      }

      else                                    /* если идентификатор не  */
                /* имеет тип bin fixed,то:*/
        return 3;                              /* завершение с диагности-*/
      /* кой ошибки             */
    }
  }
  return 4;                                       /* если идентификатор ра- */
  /* нее не определен через */
  /* ПЛ1-оператор DCL,то за-*/
  /* вершение с диагностикой*/
  /* ошибки                 */

}

/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала OPR на вто-*/
              /* ром проходе.   Здесь   */
              /* OPR - "операт.ПЛ1-PROC"*/

              /* программа    формирует */
              /* пролог ассемблеровского*/
              /* эквивалента  исходной  */
              /* ПЛ1-программы          */
int OPR2()
{
  fprintf(fp_out, "%s\n", "OPR2");
  fflush(fp_out);

  char i = 0;
  FORM();                                        /* форматируем оператор   */
  /* ПЛ1 - "начало процедур-*/
  /* ного блока"            */
  while (FORMT[0][i] != '\x0')
    ASS_CARD._BUFCARD.METKA[i++] = FORMT[0][i];  /* нулевой терм используем*/
  /* как метку в START-псев-*/
  /* дооперации Ассемблера  */

  memcpy(ASS_CARD._BUFCARD.OPERAC, "START", 5);/* достраиваем код и опе- */
  memcpy(ASS_CARD._BUFCARD.OPERAND, "0", 1);   /* ранды  в  START-псевдо-*/
  memcpy(ASS_CARD._BUFCARD.COMM,                /* операции Ассемблера    */
    "Program starts", 16);
  ZKARD();                                       /* запоминаем карту Ассем-*/
  /* блера                  */

  memcpy(ASS_CARD._BUFCARD.OPERAC, "BALR", 4); /* формируем BALR-операцию*/
  memcpy(ASS_CARD._BUFCARD.OPERAND,             /* Ассемблера             */
    "RBASE,0", 7);
  memcpy(ASS_CARD._BUFCARD.COMM,
    "Load base register", 22);
  ZKARD();                                       /* и запоминаем ее        */

  memcpy(ASS_CARD._BUFCARD.OPERAC, "USING", 5);/* формируем USING-псевдо-*/
  memcpy(ASS_CARD._BUFCARD.OPERAND,             /* операцию Ассемблера    */
    "*,RBASE", 7);
  memcpy(ASS_CARD._BUFCARD.COMM,
    "Set base register", 23);
  ZKARD();                                       /* и запоминаем ее        */

  return 0;                                       /* завершить подпрограмму */
}

// TODO 打印错误
void print_ASSTXT_to_file() {  
  fprintf(fp_out, "\n%s \n", "SYNTAX ANALYZE FINISHED! NOW PRINTING IASSTXT... ");
  fprintf(fp_out, "%s = %d\n", "IASSTXT(lines)", IASSTXT);  
  fprintf(fp_out, "%s\n", "--------- ASS ---------> \n");
  for (int i = 0; i < IASSTXT; i++) {    
    fprintf(fp_out, "%d\t%s\n", i, ASSTXT[i]);
  }
  fprintf(fp_out, "\n%s\n", "<------------ASS ------\n");
  fflush(fp_out);
}

void print_DST() {
  fprintf(fp_out, "%s\n", "---> print DST stack:");
  for (int i = 0; i < L; i++) {

    int tmp = 0;
    tmp = idx_of_VXOD(DST[i].DST1, 3);
    fprintf(fp_out,
      ">>(%d/%d)\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\n",
      i, L,
      DST[i].DST1,
      DST[i].DST2,
      DST[i].DST3,
      DST[i].DST4,
      DST[i].DST5);
  }
  fprintf(fp_out, "%s\n\n", "<----");
  fflush(fp_out);
}



/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала PRO на вто-*/
              /* ром проходе.   Здесь   */
              /* PRO - "программа"      */

int PRO2()                                       /*прогр.формирует выходной*/
{                                                /*файл                    */
  fprintf(fp_out, "%s\n", "PRO2");
  fflush(fp_out);

  FILE* fp;                                       /*набор рабочих переменных*/

  strcat(NFIL, "ass");                        /*сформировать имя выходного файла*/  

  if ((fp = fopen(NFIL, "wb")) == NULL)     /*при неудачн.открыт.ф-ла */
    return (7);                                    /* сообщение об ошибке    */
  else                                            /*иначе:                  */
    fwrite(ASSTXT, 80, IASSTXT, fp);            /* формируем тело об.файла*/
  fclose(fp);                                  /*закрываем об'ектный файл*/
            
  print_ASSTXT_to_file();    
  return (0);                                   /*завершить полдпрограмму */
}



/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала RZR на вто-*/
              /* ром проходе.   Здесь   */
              /* RZR - "разрядность"    */

int RZR2()
{
  fprintf(fp_out, "%s\n", "RZR2");
  fflush(fp_out);

  return 0;
}

/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала TEL на вто-*/
              /* ром проходе.   Здесь   */
              /* TEL - "тело программы" */

int TEL2()
{
  fprintf(fp_out, "%s\n", "TEL2");
  fflush(fp_out);

  return 0;
}

/*..........................................................................*/

              /* п р о г р а м м а      */
              /* семантич. вычисления   */
              /* нетерминала ZNK на вто-*/
              /* ром проходе.   Здесь   */
              /* ZNK - "знак операции"  */

int ZNK2()
{
  fprintf(fp_out, "%s\n", "ZNK2");
  fflush(fp_out);

  return 0;
}



/*..........................................................................*/
/* 将分析后的源代码结构转换为机器代码或中间表示代码。分两趟进行，只在第二趟写出中间代码。 */
              /*  п р о г р а м м а     */
              /* управления абстрактной */
              /* ЭВМ  -  семантического */
              /* вычислителя, интерпре- */
              /* тирующего абстрактную  */
              /* программу, сформирован-*/
              /* ную синтаксическим ана-*/
              /* лизатором в стеке дос- */
              /* тигнутых целей.        */

              /* Суть алгоритма управле-*/
              /*ния  в  последовательной*/
int gen_COD() /*интерпретации строк сте-*/
{             /*ка достижений  в направ-*/
  int NOSH;    /*лении от дна к вершине. */
  fprintf(fp_out, "%s\n", "---> int gen_COD()");
  fflush(fp_out);

  int (*FUN[NNETRM][2]) () =                    /*При этом каждая строка  */
  {                                              /*воспринимается как кома-*/
    {/*    1  */    AVI1, AVI2 },                /*нда абстрактной ЭВМ со  */
    {/*    2  */    BUK1, BUK2 },                /*следующими полями:      */
    {/*    3  */    CIF1, CIF2 },
    {/*    4  */    IDE1, IDE2 },		  /* - DST.DST1 - код операции*/
    {/*    5  */    IPE1, IPE2 },     
    {/*    6  */    IPR1, IPR2 },
    {/*    7  */    LIT1, LIT2 },     /* - DST.DST2 - левая гра-*/
    {/*    8  */    MAN1, MAN2 },		  /*ница интерпретируемого  */
    {/*    9  */    ODC1, ODC2 },		  /*фрагмента исх.текста;   */
    {/*   10  */    OEN1, OEN2 },
    {/*   11  */    OPA1, OPA2 },		  /* - DST.DST4 -правая гра-*/
    {/*   12  */    OPR1, OPR2 },		  /*ница интерпретируемого  */
    {/*   13  */    PRO1, PRO2 },		  /*фрагмента исх.текста.   */
    {/*   14  */    RZR1, RZR2 },
    {/*   15  */    TEL1, TEL2 },
    {/*   16  */    ZNK1, ZNK2 },
    {/*   17  */    DCF1, DCF2 }
  };
  
  // was:
  //for (I2 = 0; I2 < L; I2++)                    /* организация первого прохода семантического вычисления */
  //  if ((NOSH = FUN[idx_of_VXOD(DST[I2].DST1, 3)][0]()) != 0)
  //    return (NOSH); /* выход из программы по ошибке*/      
  //  for (I2 = 0; I2 < L; I2++)                    /* организация второго прохода семантического вычисления */
  //    if ((NOSH = FUN[idx_of_VXOD(DST[I2].DST1, 3)][1]()) != 0)
  //      return (NOSH);       /* выход из программы по ошибке*/          

    // ---------- Li：--------------
    // 第一趟遍历成就栈
    fprintf(fp_out, ">>>>>>>>>>>>>>>>>>>>> %s <<<<<<<<<<<<<<<<<<<<<\n", "Pass1 of semantic calculation");    
    for (I2 = 0; I2 < L; I2++) {
      fprintf(fp_out, ">>>> %d/%d Operation code: %s\n", I2, L, DST[I2].DST1);
      print_DST(); // Li
      int tmp = 0;
      tmp = idx_of_VXOD(DST[I2].DST1, 3);
      //fprintf(fp_out, 
        //">> %s, operation code: %s, get from table: %d\n", "idx_of_VXOD", 
        //DST[I2].DST1, tmp);
      fflush(fp_out);

      NOSH = FUN[tmp][0]();
      if (NOSH != 0) {
        return NOSH;
      }

    }
    
    // 第二趟遍历成就栈
    fprintf(fp_out, ">>>>>>>>>>>>>>>>>>>>> %s <<<<<<<<<<<<<<<<<<<<<\n", "Pass2 of semantic calculation");
    fflush(fp_out);
    for (I2 = 0; I2 < L; I2++) {
      fprintf(fp_out, ">>>> %d/%d Operation code: %s\n", I2, L, DST[I2].DST1);

      int tmp = 0;
      tmp = idx_of_VXOD(DST[I2].DST1, 3);
      print_DST(); // Li
      //fprintf(fp_out, ">> %s, operation code: %s, get from table: %d\n", "idx_of_VXOD", DST[I2].DST1, tmp);
      fflush(fp_out);

      NOSH = FUN[tmp][1]();
      if (NOSH != 0) {
        return NOSH;
      }

    }
 // ---------- Li --------------
    
    return 0;    /* успешное завершение программы  */          
}



char* getDateTime()
{
  static char nowtime[20];
  time_t rawtime;
  struct tm* ltime;
  time(&rawtime);
  ltime = localtime(&rawtime);
  strftime(nowtime, 20, "%Y-%m-%d %H:%M:%S", ltime);
  return nowtime;
}

void print_error_message_of_COD(int result_gen_COD) {

  switch (result_gen_COD)                         /* семантическое вычислен.*/
  {
    // ===================== ERROR MESSAGES ====================================
  case  1:                                    /*если код завершения = 1,*/
    printf("%s\n",                           /* - диагностич.сообщение;*/
      "Name of product doesn't fix.");
    break;                                     /* - выйти на обобщающую  *//* - диагностич.сообщение; диагностику             */
  case  2:                                    /*если код завершения = 2,*/
    /* то:                    */
    STROKA[DST[I2].DST2 + 20] = '\x0';      /* - диагностич.сообщение;*/
    printf("%s%s\n%s%s%s\n",
      "Type of identifier not allow: ",
      &FORMT[1], " в исх.тексте -> \"...",
      &STROKA[DST[I2].DST2], "...\"");
    break;                                     /* - выйти на обобщающую диагностику             */
  case  3:                                    /*если код завершения = 3,*/
    /* то:                    */
    STROKA[DST[I2].DST2 + 20] = '\x0';     /* - диагностич.сообщение;*/
    printf("%s%s\n%s%s%s\n",
      "Type of identifier not allow_2",
      &FORMT[IFORMT - 1], " в исх.тексте -> \"...",
      &STROKA[DST[I2].DST2], "...\"");
    break;                                     /* -выйти на обобщающую  диагностику */
  case  4:                                    /*если код завершения = 4,*/
    /* то:                    */
    STROKA[DST[I2].DST2 + 20] = '\x0';     /* - диагностич.сообщение;*/
    printf("%s%s\n%s%s%s\n",
      "Undefined identifier: ",
      &FORMT[IFORMT - 1], " в исх.тексте -> \"...",
      &STROKA[DST[I2].DST2], "...\"");
    break;                                     /* - выйти на обобщающую диагностику */
  case  5:                                    /*если код завершения = 5,*/
    STROKA[DST[I2].DST2 + 20] = '\x0';     /* - диагностич.сообщение;*/
    printf("%s%c\n%s%s%s\n",
      "Undefined operation: ",
      STROKA[DST[I2].DST4 - strlen(FORMT[IFORMT - 1])],
      " ERROR HERE -> \"...", &STROKA[DST[I2].DST2], "...\"");
    break;                                     /* - выйти на обобщающую диагностику */
  case  6:                                    /*если код завершения = 6 */
    STROKA[DST[I2].DST2 + 20] = '\x0';     /* - диагностич.сообщение;*/
    printf("%s%s\n%s%s%s\n",
      "Identifier re-declared: ",
      &FORMT[1], " ERROR HERE -> \"...",
      &STROKA[DST[I2].DST2], "...\"");
    break;                                     /* - выйти на обобщающую диагностику */
  }
}

void print_title_log() {

  char* nowtime = getDateTime();
  fprintf(fp_out, "\n\n\n\n\n\n//////////////////////////////////////////////////////////////////////\n");
  fprintf(fp_out, "////////////////////////////////////////// %s ///////\n", nowtime);
  fprintf(fp_out, "//////////////////////////////////////////////////////////////////////\n\n");  
  fflush(fp_out);
}


/*..........................................................................*/

              /*  п р о г р а м м а,    */
              /* организующая последова-*/
              /* тельную обработку ис-  */
              /* ходного текста:        */
              /* - лексич.анализатором; */
              /* - синтаксич.анализат.; */
              /* - семантич.вычислителем*/
int main(int argc, char** argv)
{                                                /* рабочие переменные:    */
  FILE* fp;                                       /* - указатель на файл;   */
  fp_out = fopen("log.txt", "a+");                                  /* Li: 用于读取debug的结果 */
  if (NULL == fp_out) {
    printf("open log.txt failed! \n");
    return FILE_NOT_OPEN;
  }
  setbuf(fp_out, NULL);

  print_title_log();

  const char* ptr = "examppl.pli";
  strcpy(NFIL, ptr);

  /* проверка типа исх.файла*/
  if (strcmp(&NFIL[strlen(NFIL) - 3], "pli")) {
    printf("%s\n",                              /* выдать диагностику и   */
      "Invalid source file type");
    return -1;                                       /* завершить трансляцию   */
  }
  else {                                              /*пытаемся открыть файл и */
    if ((fp = fopen(NFIL, "rb")) == NULL) {
      printf("%s\n", "File not found");
      return -1;                                     /* завершение трансляции  */
    }
    else {
      for (NISXTXT = 0; NISXTXT <= MAXNISXTXT; NISXTXT++) {
        if (!fread(ISXTXT[NISXTXT], 80, 1, fp)) {
          if (feof(fp))                      /* в конце файла идем на  */
          {
            goto main1;                            /* метку  main1           */
          }
          else {
            printf("%s\n",
              "Error reading source file");
            return -1;
          }
        }
      }

      printf("%s\n", "Text read buffer overflow");
      return -1;
    }
  }

main1:                                            /* по завершении чтения   */
  /* исх.файла формируем    */
  fclose(fp);                                 /* префикс имени выходного*/
  NFIL[strlen(NFIL) - 3] = '\x0';            /* Ассемблеровского файла */
  memset(ASS_CARD.BUFCARD, ' ', 80);           /* чистка буфера строки   */
  /* выходного ассемблеровского файла */

  compress_ISXTXT();                             /* лексический анализ исходного текста*/
  build_TPR();                                   /* построение матрицы преемников */
  int return_code = sint_ANAL();
  if (return_code)                           /* синтаксический анализ  исходного текста */
  {
    STROKA[I4 + 20] = '\x0';
    printf("<ERROR CODE> %d\n", return_code);
    printf("%s%s%s%s\n", "<ERROR INFO> Syntax error here-> ", "\"...", &STROKA[I4], "...\"");
    printf("%s\n", "Translate interrupted.");
    return -1;                                      /* завершаем трансляцию   */
  }
  else                                            /* иначе делаем           */
  {
    int result_gen_COD = gen_COD();
    if (result_gen_COD == 0) {
      printf("%s\n", "Translation succeed!");
      return 0;                                    /* завершить трансляцию */
    }
    print_error_message_of_COD(result_gen_COD);
    fclose(fp_out);
  }

  printf("%s\n", "Translation interrupted.");       /* обобщающая диагностика */
  return -1;
}
/*..........................................................................*/
