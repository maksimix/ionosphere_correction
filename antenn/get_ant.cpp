#include <stdio.h>
#include <math.h>
#include "antenn.h"

#define STR1 "\n��������������������������������������������������������\
��������������������"
#define STR2 "\n�Trans antenn type� EPS  � SIG  �    � La  �  H  � PSI �\
  Fi  �      �     �"
#define STR3 "\n�         %1d       �%6.3f�%6.3f�    �%5.1f�%5.1f�%5.1f�\
%6.1f�      �     �"
#define STR4 "\n��������������������������������������������������������\
��������������������"
#define STR5 "\n�Recev antenn type� EPS  � SIG  � N  � La  �  H  � PSI �\
  Fi  �  Rs  � Ll  �"
#define STR6 "\n�         %1d       �%6.3f�%6.3f� %2d �%5.1f�%5.1f�%5.1f�\
%6.1f�%6.1f�%5.1f�"
#define STR7 "\n��������������������������������������������������������\
��������������������"
#define RAD 1.745329251994329548e-2

void get_ant(FILE *in,
             FILE *out,
             ANT_TRAN *a1,
             ANT_REC  *a2)
/***************************************************************/
/*                                                             */
/* ������� ������������� ��� ����� ���������� ������ � ������� */
/* ������ � ��������.                                          */
/*                                                             */
/* in - ��������� �� ���� ����� ����������;                    */
/* out- ��������� �� ���� ������ ����������;                   */
/* a1 - ��������� �� �������� ���������� �������;              */
/* a2 - ��������� �� �������� �������� �������.                */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  EPS1=SIG1=LA1=H1=FI1=PSI1=.0;
  EPS2=SIG2=LA2=H2=FI2=PSI2=RS=LL=.0;
  NA=1;

  fscanf(in,"%ld",&TYPE1);
  /* TYPE1                                 */
  /*   0      ���������� ����������;       */
  /*   1      ��������� ��� �� ��������;   */
  /*   2      ���� �� ��������.            */
  switch (TYPE1)
    {
      case 1: fscanf(in,"%lg%lg%lg%lg%lg%lg",&EPS1,&SIG1,
                                             &LA1,&H1,&PSI1,&FI1);
      break;

      case 2: fscanf(in,"%lg%lg%lg%lg%lg",&EPS1,&SIG1,&LA1,&H1,&FI1);
    }

  fscanf(in,"%ld",&TYPE2);
  /* TYPE2                                 */
  /*   0      ���������� ��������;         */
  /*   1      ��������� ��� �� �������;    */
  /*   2      ��� �� ������;               */
  /*   3      �������� ������� �� ������;  */
  /*   4      ��,                          */
  /*   5      ��-2,                        */
  /*   6      ��-3.                        */

  switch (TYPE2)
    {
      case 1: fscanf(in,"%lg%lg%lg%lg%lg%lg",&EPS2,&SIG2,
                                             &LA2,&H2,&PSI2,&FI2);
      break;

      case 2: fscanf(in,"%lg%lg%lg%lg%lg",&EPS2,&SIG2,&LA2,&H2,&FI2);
      break;

      case 3: fscanf(in,"%lg%lg%lg",&EPS2,&SIG2,&H2);
      break;

      case 4:
      case 5:
      case 6: fscanf(in,"%lg%lg%ld%lg%lg%lg%lg%lg",
                     &EPS2,&SIG2,&NA,&LA2,&RS,&LL,&H2,&FI2);
    }

  if (TYPE1)
    {
      fprintf(out,STR1);
      fprintf(out,STR2);
      fprintf(out,STR3,TYPE1,EPS1,SIG1,LA1,H1,PSI1,FI1);
      FI1+=180.;
      if (FI1>180.)
        FI1-=360.;
      if (TYPE2)
        fprintf(out,STR4);
      else
        fprintf(out,STR7);
    }

  if (TYPE2)
    {
      if (!TYPE1)
        fprintf(out,STR1);

      fprintf(out,STR5);
      fprintf(out,STR6,TYPE2,EPS2,SIG2,NA,LA2,H2,PSI2,FI2,RS,LL);
      fprintf(out,STR7);
      FI2+=180.;
      if (FI2>180.)
        FI2-=360.;
    }

  PSI1 *=RAD;
  FI1  *=RAD;

  PSI2 *=RAD;
  FI2  *=RAD;

  return;
} /* get_ant */

