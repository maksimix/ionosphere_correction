#include <stdio.h>
#include <math.h>
#include "paths.h"

#define STR1 "\n+---+-----+-------+---+-----+-----+--------+\
--------+---------+------+------+------+------+-------+------+\
------+--------+--------+------+------+-------+-------+----------------+"

#define STR2 "\n+---+-----+-------+---+-----+-----+--------+\
--------+---------+------+------+------+------+-------+------+\
------+--------+--------+------+------+-------+-------+----------------+"

#define STR3 "\n+---+-----+-------+---+-----+-----+--------+\
--------+---------+------+------+------+------+-------+------+\
------+--------+--------+------+------+-------+-------+----------------+"

#define STR4 "\n|0-x| fr  |  time |hop| d0  | d1  |   fi   |\
  teta  |   dist  |  at  |  dev |  a1  |  a2  |   p   |  df  |\
  l   |   fot  |   tot  |  rot | lsp  |   pf  |    s  |                |"

#define STR5 "\n|%3d|%5.2f|%7.1f|%3d|%5.2f|%5.2f|%8.3f|%8.3f|\
%9.3f|%6.1f|%6.1f|%6.1f|%6.1f|%7.1f|%6.3f|%6.1f|%8.3f|%8.3f|%6.2f|%6.1f|%7.1f|%7.1f|%s|"

#define STR6 "\n|   |     |       |%3d|%5.2f|%5.2f|%8.3f|%8.3f|\
%9.3f|%6.1f|%6.1f|%6.1f|%6.1f|%7.1f|%6.3f|%6.1f|%8.3f|%8.3f|%6.2f|%6.1f|%7.1f|%7.1f|%s|"

void outtrs(FILE   *out,
	    PUTDAT *putdat,
	    int    ihop)
/***************************************************************/
/*	      ζυξλγιρ πεώατι ςασσώιταξξωθ δαξξωθ.              */
/*                                                             */
/* output -υλαϊατεμψ ξα στςυλτυςυ ςασσώιταξξωθ δαξξωθ;         */
/* ihop	  -ώισμο σλαώλοχ.                                      */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
   int i;
   static int kol=0;
   char strModa[17];

   if (ihop<0)
   {
      fprintf(out,STR2);
      return;
   }

   if (kol==0)
   {
      fprintf(out,STR1);
      fprintf(out,STR4);
      fprintf(out,STR3);
   }

   for(i=0; i<ihop; i++)
   {
       if (i==0 || ZOTR(i)>.0)
       {

	   kol++;

	   if (fabs(L(i)) >999.9) L(i) =999.9;
	   if (fabs(LS(i))>999.9) LS(i)=999.9;

	   if (i==0)
	     fprintf(out,STR5,IOX(i),FR(i),TIME(i),i+1,D1(i),D2(i),X(i),
			      Y(i),S(i),AT(i),DEV(i),A1(i),A2(i),P(i),DF(i),L(i),
			      XOTR(i),YOTR(i),ZOTR(i),LS(i),PG(i),PS(i),moda(Moda(i),strModa));
	   else
	     fprintf(out,STR6,i+1,D1(i),D2(i),X(i),
	        	      Y(i),S(i),AT(i),DEV(i),A1(i),A2(i),P(i),DF(i),L(i),
	        	      XOTR(i),YOTR(i),ZOTR(i),LS(i),PG(i),PS(i),moda(Moda(i),strModa));
//           fprintf(out,"p=%11.6f  df=%7.4f",PG(i),DF(i));
       }

       if (kol==20)
       {
	   kol=0;
	   fprintf(out,STR2);
       }
       if (ZOTR(i)<=.0)
           break;
   }

  return;

} /* outtrp */
