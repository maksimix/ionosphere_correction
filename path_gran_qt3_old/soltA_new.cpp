#include "paths.h"

#define M 2 /* количество монотонных шагов */
#define EPS .17e-9
#define MAXIT 100

#define FORM1 "\na8,a7,s,hop,no,fun %8.3f%9.3f%13.6f%3d%3d%13.5e%13.5e%5d%13.5e"
#define FORM2 "\na6,a7,s,koli,no %8.3lf%9.3lf%13.6lf%3d%3d%13.5e%13.5e"

long soltA(double d0,    // угол места
           double alfa0, // истиный азимут трассы
           long   ihop,
           double delt,
           double eps,
           double ep,
           double ep1,
           double e,
           double eps1,  // точность по азимуту
           double dd0,   // шаг по азимуту
           PUTDAT *putdat)
/***************************************************************/
/*                                                             */
/* Функция находит решение граничной задачи a(alf)=a0  и       */
/* возвращает 0 - решение найдено, иначе - 1                   */
/*                                                             */
/* ihop - число скачков,                                       */
/* eps1 - точность решения уравнения,                          */
/* dd   - начальный шаг по углу,                               */
/*                                                             */
/*VGG  версия 14.06.06                                         */
/***************************************************************/

{
  double a,f2,f3,a2,a3,a7,a8,s,dd;
  int kol=0;
  int no;
  /*
  dd=1.0*RAD;
  a8=alfa0-dd*10;
  for(int i=0; i<20; i++)
  {
      a8+=dd;
      no=treks(d0,a8,ihop,6,delt,eps,ep,ep1,e,putdat);
      a=AT(ihop-1)*RAD;
      a7=sin(a-alfa0);
      if (keysol>1)
          printf(FORM1,a8/RAD,AT(ihop-1),S(ihop-1),ihop,no,a7,dd,kol,AT(ihop-1)-alfa0/RAD);

  }
 */

  //printf("\n2 keytr=%d",keytr);
  f2=f3=a2=a3=.0;
  a8=alfa0;

  /* вычисление дальности при начальном азимуте                 */
  /* no  -  0 - имеются отражения на всех скачках,              */
  /*        1 - просачивание или                                */
  /*            после отражения лучевая траектория не приходит  */
  /*            на поверхость Земли;                            */

  no=treks(d0,a8,ihop,6,delt,eps,ep,ep1,e,putdat);
  if (keysol>1)
      printf(FORM1,a8/RAD,AT(ihop-1),S(ihop-1),ihop,no,DEV(ihop-1),dd0,kol,AT(ihop-1)-alfa0/RAD);
  if (no)
      return no;

  a=AT(ihop-1)*RAD;
  if (fabs(alfa0-a)<eps1)
      return no;
  kol++;
  /*
  //if (DEV(ihop-1)<.0)
  if (a-alfa0<.0)
      dd= dd0;
  else
      dd=-dd0;
  do
  {
      //a7=sin(a)-sin(alfa0)+cos(a)-cos(alfa0);
      a7=sin(a-alfa0);
      if (a7<.0)
      {
          a2=a8;
          f2=a7;
      }
      else
      {
          a3=a8;
          f3=a7;
      }
      a8+=dd;
      no=treks(d0,a8,ihop,6,delt,eps,ep,ep1,e,putdat);
      if (keysol>1)
          printf(FORM1,a8/RAD,AT(ihop-1),S(ihop-1),ihop,no,a7,dd,kol,AT(ihop-1)-alfa0/RAD);
      a=AT(ihop-1)*RAD;
      kol++;
      if (!no && fabs(sin(a-alfa0))<eps1)
          return no;
  } while (!no && f2*f3>=.0 && kol<MAXIT);

  if (no || kol>=MAXIT)
      return no;

  kol=0;
  do
  {
      a8=a2-f2*(a3-a2)/(f3-f2);
      no=treks(d0,a8,ihop,6,delt,eps,ep,ep1,e,putdat);
      if (keysol>1)
        printf(FORM2,a8/RAD,AT(ihop-1),S(ihop-1),kol,no,f2,f3);
      a=AT(ihop-1)*RAD;
      //a7=sin(a)-sin(alfa0)+cos(a)-cos(alfa0);
      a7=sin(a-alfa0);
      if (a7<.0)
      {
          a2=a8;
          f2=a7;
      }
      else
      {
          a3=a8;
          f3=a7;
      }
      kol++;
  } while(!no && kol<MAXIT && fabs(f2)>eps1 && fabs(f3)>eps1);
  */
  if (!no)
  {
      double aa;
      double a8_=a8;
      aa=a-alfa0;
      a7=sin(aa);
      if (a7<.0)
      {
          a2=a8;
          f2=a7;
      }
      else
      {
          a3=a8;
          f3=a7;
      }
      do
      {
          a8-=aa;
          no=treks(d0,a8,ihop,6,delt,eps,ep,ep1,e,putdat);
          if (keysol>1)
              printf(FORM1,a8/RAD,AT(ihop-1),S(ihop-1),ihop,no,a7,dd,kol,AT(ihop-1)-alfa0/RAD);
          if (!no)
          {
              a8_=a8;
          }
          else
          {
              a8=a8_;
              aa=.5*aa;
              no=0;
              kol++;
              continue;
          }

          a=AT(ihop-1)*RAD;
          aa=a-alfa0;
          a7=sin(aa);
          if (a7<.0)
          {
              a2=a8;
              f2=a7;
          }
          else
          {
              a3=a8;
              f3=a7;
          }
          kol++;
      } while (!no && f2*f3>=.0 && kol<MAXIT && fabs(a7)>eps1);

      if (!no && fabs(a7)>eps1 && f2*f3<.0)
      {
          kol=0;
          do
          {
              a8=a2-f2*(a3-a2)/(f3-f2);
              no=treks(d0,a8,ihop,6,delt,eps,ep,ep1,e,putdat);
              if (keysol>1)
                printf(FORM2,a8/RAD,AT(ihop-1),S(ihop-1),kol,no,f2,f3);
              a=AT(ihop-1)*RAD;
              //a7=sin(a)-sin(alfa0)+cos(a)-cos(alfa0);
              a7=sin(a-alfa0);
              if (a7<.0)
              {
                  a2=a8;
                  f2=a7;
              }
              else
              {
                  a3=a8;
                  f3=a7;
              }
              kol++;
          } while(!no && kol<MAXIT && fabs(f2)>eps1 && fabs(f3)>eps1);
      }
      //printf("\nno=%d a7=%13.5e f2=%13.5e f3=%13.5e eps1=%13.5e a-alfa0=%13.5e",no,a7,f2,f3,eps1,a-alfa0);
  }
  return no;
} /* soltA */

