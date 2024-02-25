using namespace std;
#include <iostream>
#include <iomanip>
#include "paths.h"
#include "mysolt.h"

//#define M 2 /* количество монотонных шагов */
//#define EPS .17e-6
#define MAXIT 20

#define FORM1 "\na8,a7,s,hop,no,fun %8.3f%9.3f%13.6f%3d%3d%13.5e"
#define FORM2 "\na6,a7,s,koli,no %8.3lf%9.3lf%13.6lf%3d%3d"

MySoltA::MySoltA(double F, double T, double Fh, double h[3], double dh[3][3], double dh2[3][3][3], double D0, double Alfa0, int Hop,
        double Delt, double Eps, double Ep, double Ep1, int N,
        double Eps1, double Dd0, PUTDAT *Putdat) :
        f(F), t(T), fh(Fh), d0(D0), alfa0(Alfa0), ihop(Hop), delt(Delt), eps(Eps), ep(Ep), ep1(Ep1),
        n(N), eps1(Eps1), dd0(Dd0), putdat(Putdat)
{
    mytrek=0;
    mytrek=new MyTrek(f, fh, h, dh, dh2, delt, eps, ep, ep1);
    mytrek->setTime(t);
    //cout<<endl<<"MySoltA copy_iri_model()"<<flush;
    mytrek->copy_iri_model();
    //cout<<endl<<"1 new IRI_3D"<<flush;
    //mytrek->iri_3dbase =new IRI_3D(*::iri_3dbase);
    //cout<<endl<<"2 new IRI_3D"<<flush;
    //mytrek->iri_3dbase2=new IRI_3D(*::iri_3dbase2);
    //cout<<endl<<"3 new IRI_3D"<<flush;
}

MySoltA::~MySoltA()
{
	//cout<<endl<<"~MySoltA"<<flush;
    if (mytrek)
    {
		//cout<<endl<<"1 delete mytrek"<<flush;
        delete mytrek;
        //cout<<endl<<"2 delete mytrek"<<flush;
	}
    mytrek=0;
}

long MySoltA::soltA()
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

  //printf("\n2 keytr=%d",keytr);
  f2=f3=a2=a3=.0;
  a8=alfa0;

  /* вычисление дальности при начальном азимуте                 */
  /* no  -  0 - имеются отражения на всех скачках,              */
  /*        1 - просачивание или                                */
  /*            после отражения лучевая траектория не приходит  */
  /*            на поверхость Земли;                            */
  no=mytrek->treks(d0,a8,ihop,6,putdat);
  if (keysol>1)
    printf(FORM1,a8/RAD,AT(ihop-1),S(ihop-1),ihop,no,.0);
  if (no)
      return no;

  a=AT(ihop-1)*RAD;
  if (fabs(alfa0-a)<eps1)
      return no;
  kol++;
  if (DEV(ihop-1)<.0)
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
      no=mytrek->treks(d0,a8,ihop,6,putdat);
      if (keysol>1)
        printf(FORM1,a8/RAD,AT(ihop-1),S(ihop-1),ihop,no,a7);
      a=AT(ihop-1)*RAD;
      kol++;
  } while (!no && f2*f3>=.0 && kol<MAXIT);

  if (no || kol>=MAXIT)
      return no;

  kol=0;
  do
  {
      a8=a2-f2*(a3-a2)/(f3-f2);
      no=mytrek->treks(d0,a8,ihop,6,putdat);
      if (keysol>1)
        printf(FORM2,a8/RAD,AT(ihop-1),S(ihop-1),kol,no);
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

  return no;
} /* soltA */

