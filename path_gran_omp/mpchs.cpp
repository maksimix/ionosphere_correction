#include "paths.h"
#include "mysolt.h"

#define M 2 /* количество монотонных шагов */
#define EPS .17e-4

double mpchs(MySolt *mySolt)
/***************************************************************/
/*                                                             */
/* Функция находит максимальную применимую частоту для заданной*/
/*                 протяженности трассы.                       */
/*                                                             */
/* s0   - длина трассы,                                        */
/* ihop - число скачков,                                       */
/* dd   - начальный шаг по углу,                               */
/* d1   - ограничение на максимальный угол вылета,             */
/* eps2 - ограничение на минимальную дальность при поиске      */
/*        отрезков, содержащих корни граничной задачи: s(d)=s0;*/
/*                                                             */
/*VGG  версия 24.06.06                                         */
/***************************************************************/

{
  long    l,ikor,io,no,io_key;
  double f2,f3,d2,d3,d7,d8,s,p,dd,df,f,
         d0,pg,eps1,dff,ls,s1,dOk;
  double db=mySolt->getDmin();
  double de=mySolt->getDmax();
  int    ihop=mySolt->getHop();
  PUTDAT* putdat=mySolt->getPutdat();

  if (fMin<1.5)
      fMin=1.5;
  df=(fMin>5.)? 5. : fMin;

  //printf("\ndf=%f  fMin=%f",df,fMin);

  p=mySolt->getS0()/(2.*ihop*R0);
  if (db<=.0)
  {
      db=atan2((h0*cos(p)-R0),h0*sin(p));//-dd0;
      if (db<.0) db=1.*RAD;
  }
  if (de<.0) de=PI;
  d0=db;

  mySolt->setDmin(db);
  mySolt->setDmax(de);

  f=fMin;
  do
  {
      f+=df;
      mySolt->setFr(f);
      no=mySolt->solt();
      if (keympr)
      {
          printf("\nf=%6.2f  d1=%5.2f  s=%8.2f   hop=%2d  no=%2d  iox=%2d  maxS=%8.2f",f,D1(0),S(ihop-1),ihop,no,iox,mySolt->getMaxS());
          fflush(stdout);
      }
  } while (mySolt->getMaxS()>.0 && .01*mySolt->getMaxS() < mySolt->getS0());

  do
  {
      f+=df;
      mySolt->setFr(f);
      no=mySolt->solt();
      if (keympr)
      {
          printf("\nf=%6.2f  d1=%5.2f  s=%8.2f   hop=%2d  no=%2d  iox=%2d  maxS=%8.2f",f,D1(0),S(ihop-1),ihop,no,iox,mySolt->getMaxS());
          fflush(stdout);
      }
  } while(no);

  while (df>.05)
  {
      df*=.5;
      if (no)
      {
          f+=df;
      }
      else
      {
          f-=df;
      }
      mySolt->setFr(f);
      no=mySolt->solt();
      if (keympr)
      {
          printf("\nf=%6.2f  d1=%5.2f  s=%8.2f   hop=%2d  no=%2d  iox=%2d",f,D1(0)/RAD,S(ihop-1),ihop,no,iox);
          fflush(stdout);
      }
  }

  return f;
} /* mpche */
