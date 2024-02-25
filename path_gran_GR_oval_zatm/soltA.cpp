#include "paths.h"

#define M 2 /* количество монотонных шагов */
#define EPS .17e-6
#define MAXIT 20

#define FORM1 "\na8,a7,s,hop,no %8.3f%9.3f%13.6f%3d%3d"
#define FORM2 "\na6,a7,s,koli,no %8.3lf%9.3lf%13.6lf%3d%3d"

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
  int flag=0;
  if (keympr<0 && keytr<0)
  {
      flag=1;
      keytr=0;
  }

  f2=f3=a2=a3=.0;
  a8=alfa0;

  /* вычисление дальности при начальном азимуте                 */
  /* no  -  0 - имеются отражения на всех скачках,              */
  /*        1 - просачивание или                                */
  /*            после отражения лучевая траектория не приходит  */
  /*            на поверхость Земли;                            */
  no=treks(d0,a8,ihop,6,delt,eps,ep,ep1,e,putdat);
  if (keysol>1)
    printf(FORM1,a8/RAD,AT(ihop-1),S(ihop-1),ihop,no);
  if (no)
      return no;

  a=AT(ihop-1)*RAD;
  //if (fabs(alfa0-a)<eps1)
  //    return no;
  kol++;
  if (DEV(ihop-1)<.0)
      dd= dd0;
  else
      dd=-dd0;
  do
  {
      a7=sin(a)-sin(alfa0)+cos(a)-cos(alfa0);
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
      //if (flag)
      //{
      //   keytr=-1;
      //    keysol=2;
      //}
      no=treks(d0,a8,ihop,6,delt,eps,ep,ep1,e,putdat);
      if (keysol>1)
      {
          printf(FORM1,a8/RAD,AT(ihop-1),S(ihop-1),ihop,no);
          //printf("\nf2*f3=%f kol=%d",f2*f3,kol);
      }
      a=AT(ihop-1)*RAD;
      kol++;
  } while (!no && f2*f3>=.0 && kol<MAXIT);

  if (no || kol>=MAXIT)
      return no;

  kol=0;
  do
  {
      if (flag)
      {
          keytr=-1;
          //keysol=2;
      }
      a8=a2-f2*(a3-a2)/(f3-f2);
      no=treks(d0,a8,ihop,6,delt,eps,ep,ep1,e,putdat);
      if (keysol>1)
        printf(FORM2,a8/RAD,AT(ihop-1),S(ihop-1),kol,no);
      if (flag)
      {
          keytr=0;
          //keysol=0;
      }
      a=AT(ihop-1)*RAD;
      a7=sin(a)-sin(alfa0)+cos(a)-cos(alfa0);
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

  return no;
} /* soltA */

