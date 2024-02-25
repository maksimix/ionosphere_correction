#include <math.h>
#include "paths.h"
#include "./antenn.h"

static void pol(double f, double delta, double fh, double i,
                double fi, double *m,   double *psi);

static void polar(double f, double delta1, double delta2, double ma,
                  double psia, double fh1, double fh2, double fi1,
                  double fi2, double i1, double i2, double fox[2],
                  double mc[2], double psic[2]);

void abspol(double    fr,
            double    alf1,
            double    alf2,
            long       ox,
            long       hop,
            long       n,
            ANT_TRAN  *a1,
            ANT_REC   *a2,
            double    *lp,
            double    *lr,
            double    *ku,
            double    *knd,
            double    *mm,
            double    *psi)
/***************************************************************/
/*                                                             */
/* fr   - рабочая частота;                                     */
/* alf1 - азимут трассы на приемник;                           */
/* alf2 - азимут трассы на передатчик;                         */
/* ox   - 0 - обыкновенная волна,                              */
/*        1 - необыкновенная волна;                            */
/* hop  - количество скачков;                                  */
/* n    - количество корней на заданной частоте;               */
/* a1   - указатель на структуру описания передающей антенны;  */
/* a2   - указатель на структуру описания приемной антенны;    */
/* lp   - указатель на массив поляризационных потерь;          */
/* lr   - указатель на массив потерь при отражении от Земли;   */
/* ku   - указатель на массив усилений антенн;                 */
/* knd  - указатель на массив КНД антенн;                      */
/* mm   - указатель на массив отношений осей эллипса поляри-   */
/*        зации на выходе из ионосферы;                        */
/* psi  - угол наклона эллипса поляризации.                    */
/*                                                             */
/*VGG  06.02.92                                                */
/***************************************************************/

{
  double polr,pols,ma,psia,di,dk,epse,sige,
         fh1,fh2,i1,i2,b1,b2,ref,d1,d2,d3,
         alfa,
         mc[2],psic[2],fox[2];
  long    i,j;

  epse=.5*(EPS1+EPS2);
  sige=.5*(SIG1+SIG2);

  for(i=0; i<n; i++)
    {
      pols=polr=.0;
      di=dhopk[i][0][0];
      dk=-dhopk[i][hop-1][1];

      switch (TYPE1)
        {
          case 0:
                  ma=.0;
                  psia=.0;
                  *(ku+i)=.0;
                  break;

          case 1: ellips(fr,di,EPS1,SIG1,LA1,H1,PSI1,alf1-FI1,&ma,&psia,(ku+i));
                  break;

          case 2: trant(fr,di,EPS1,SIG1,LA1,H1,alf1-FI1,&ma,&psia,(ku+i));
        }

      if (TYPE1)
        if (*(ku+i)<1.e-90)
          *(ku+i)=-900.;
        else
          *(ku+i)=10.*log10(*(ku+i));

      if (TYPE1)
        for(j=0; j<hop; j++)
          {
            fh1=FHhopk[i][j][0];
            i1 =Ihopk[i][j][0];
            b1 =alf1-Dhopk[i][j][0];
            fh2=FHhopk[i][j][1];
            i2 =Ihopk[i][j][1];
            b2 =alf1-Dhopk[i][j][1];

            polar(fr,dhopk[i][j][0],dhopk[i][j][1],ma,psia,
                  fh1,fh2,b1,b2,i1,i2,fox,mc,psic);

            if (j+1<hop)
              {
                rerth(fr,dhopk[i][j][1],mc[ox],psic[ox],epse,sige,
                      &ref,&ma,&psia);
                polr -=ref;
              }

            pols -=fox[ox];
          }
        else
          {
            fh1=FHhopk[i][hop-1][0];
            i1 =Ihopk[i][hop-1][0];
            b1 =alf1-Dhopk[i][hop-1][0];
            fh2=FHhopk[i][hop-1][1];
            i2 =Ihopk[i][hop-1][1];
            b2 =alf1-Dhopk[i][hop-1][1];

            polar(fr,dhopk[i][hop-1][0],dhopk[i][hop-1][1],ma,psia,
                  fh1,fh2,b1,b2,i1,i2,fox,mc,psic);
            *(mm+i) =mc[ox];
            *(psi+i)=psic[ox];
          }

      *(lp+i)=pols;
      *(lr+i)=polr;

      switch (TYPE2)
        {
          case 0:
                  *(knd+i)=.0;
                  break;

          case 1: rebeam(fr,dk,mc[ox],psic[ox],EPS2,SIG2,LA2,H2,PSI2,alf2-FI2,
                         (knd+i));
                  break;

          case 2: recant(fr,dk,mc[ox],psic[ox],EPS2,SIG2,LA2,H2,alf2-FI2,
                         (knd+i));
                  break;

          case 3: loop(fr,dk,mc[ox],psic[ox],EPS2,SIG2,H2,(knd+i));
                  break;

          case 4:
          case 5:
          case 6: bs(NA,LA2,RS,LL,H2,EPS2,SIG2,fr,dk,alf2-FI2,&d1,&d2,&d3);
                  if (TYPE2==4)
                    *(knd+i)=d1;
                  else
                    if (TYPE2==5)
                      *(knd+i)=d2;
                    else
                      *(knd+i)=d3;
        }

      if (TYPE2)
        if (*(knd+i)<1.e-90)
          *(knd+i)=-900.;
        else
          *(knd+i)=10.*log10(*(knd+i));
    }
} /* abspol */


static void polar(double f,
                  double delta1,
                  double delta2,
                  double ma,
                  double psia,
                  double fh1,
                  double fh2,
                  double fi1,
                  double fi2,
                  double i1,
                  double i2,
                  double fox[2],
                  double mc[2],
                  double psic[2])
/***************************************************************/
/*                                                             */
/*      Функция предназначена для расчета поляризационного     */
/*      рассогласования и параметров эллипса поляризации на    */
/*                 выходе из ионосферы.                        */
/*                                                             */
/* f      - рабочая частота;                                   */
/* delta1 - угол входа в ионосферу;                            */
/* delta2 - угол выхода луча из ионосферы;                     */
/* ma     - отношение осей эллипса поляризаци волны на входе;  */
/* psia   - наклон большой оси эллипса поляризации к плоскости */
/*          распространения на входе в ионосферу;              */
/* fh1    - гирочастота на входе;                              */
/* fh2    - гирочастоита на выходе луча из ионосферы;          */
/* fi1    - магнитный азимут направления луча на входе;        */
/* fi2    - магнитный азимут направления луча на выходе        */
/*          из ионосферы;                                      */
/* i1     - магнитное наклонение на входе;                     */
/* i2     - магнитное наклонение на выходе из ионосферы;       */
/* fox[2] - поляризационные потери на входе в ионосферу;       */
/* mc[2]  - отношения осей эллипсов поляризации соответственно */
/*          для "о" и "х" волн на выходе из ионосферы;         */
/* psic[2]- наклон больших осей эллипсов к плоскости распрост- */
/*          ранения на выходе из ионосферы.                    */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  double psi,m,r1,fon,fxn;


      pol(f,delta1,fh1,i1,fi1,&psi,&m);

      psi=-psi;
      m=-m;
      r1=cos(psia-psi);
      r1 *=r1;
      fon=((1.+ma*m)*(1.+ma*m)*r1+(ma+m)*(ma+m)*(1.-r1))/
          ((1.+ma*ma)*(1.+m*m));
      fxn=1.-fon;

      pol(f,-delta2,fh2,i2,fi2+PI,&m,&psi);

      mc[0]=m;
      mc[1]=-m;
      psic[0]=psi;

      if (psi<.0) psic[1]=psi+PI5;
      if (psi>.0) psic[1]=psi-PI5;

      if (fon<=.0)
        fox[0]=-999.;
      else
        fox[0]=10.*log10(fon);

      if (fxn<=.0)
        fox[1]=-999.;
      else
        fox[1]=10.*log10(fxn);

      return;
} /* polar */

static void pol(double f,
                double delta,
                double fh,
                double i,
                double fi,
                double *m,
                double *psi)
/***************************************************************/
/*                                                             */
/* Функция вычисляет параметры эллипса поляризации в рамках    */
/*             теории передельой поляризации.                  */
/***************************************************************/
{
  double cfi,sfi,ct,st,sd0,cd0,si,ci;

      sd0=sin(delta);
      cd0=cos(delta);
      si=sin(i);
      ci=cos(i);
      cfi=cos(fi);
      sfi=sin(fi);
      ct=-sd0*si+cd0*ci*cfi;
      st=sqrt(1.-ct*ct);

      *psi=atan2(ci*sfi,si*cd0+ci*cfi*sd0);

      *m=tan(.5*atan2(ct,.5*fh/f*st*st));

      return;
} /* pol */