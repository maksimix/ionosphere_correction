#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "paths.h"


/*==============================================================*/

int pk2_modul(double lat0,     //  широта, град
              double lon0,     //  долгота, град
              double Z0,       //  высота точки излучения, км
              double Z1,       //  высота точки приема, км
              int iYear,       //  год
              double aMes,        //  месяц в десятичном формате
              long it1,        //  начальное время в формате ччммсс
              long it2,        //  конечное время в формате ччммсс
              long it3,        //  шаг по времени в формате ччммсс для прогноза
              double iW,       //  число Вольфа
              double iIG,      //  индекс солнечной активности
              long   keymod,   //  1 - CCIR, 0 - URSI
              long   keyes,    //  1 - прогноз ES, 0 - нет ES
              long   keystorm, //  1 - учет магнитных возмущений, 0 - нет магнитных возмущений
              long   keyh,
              double f,        //  частота, МГц
              double d,        //  угол излучения, град
              double a,        //  азимут излучения, град
              long   t,        //  время излучения в формате ччммсс
              int iOX,         //  0 - щ-волна, 1 - ч-волна
              PUTDAT* putdat)  //  результаты расчета
{
  double alfa,d0,delt0,eps,ep,ep1;
  double w,W,ig,IG,ames,rmax;
  long   hou1,hou2,hou3,min1,min2,min3,
         sek1,sek2,sek3;
  double t1,t2,t3,time,dt,
         time1,time2,dtime;
  double e=.0625;
  int n,ihop,iyear;
  long keyvod, keyMod, keyEs, keypri;
  int i,j;
/*--------------------------------------------------------------*/
  delt0=.1;
  eps=1.e-5;
  ep=1.e-6;
  ep1=1.e-3;
  rmax=4000.;

  keyEs=keyes;
  keyMod=keymod;
  keyvod=keynu=keyl2=keypri=keytr=0;

  e=e*eps;
  z0=R0+Z0*.01;
  z1=R0+Z1*.01;
  rmax*=.01;

  ihop=1;
  n=22; // число уравнений
  
  fi0=lon0*RAD;
  teta0=(90.-lat0)*RAD;

  infils(keyh);

  hou1=it1/10000l;
  hou2=it2/10000l;
  hou3=it3/10000l;
  min1=(it1-hou1*10000l)/100l;
  min2=(it2-hou2*10000l)/100l;
  min3=(it3-hou3*10000l)/100l;
  sek1=it1-hou1*10000l-min1*100l;
  sek2=it2-hou2*10000l-min2*100l;
  sek3=it3-hou3*10000l-min3*100l;

  t1=hou1*3600.+min1*60.+sek1;
  t2=hou2*3600.+min2*60.+sek2;
  t3=hou3*3600.+min3*60.+sek3;
  dt=t3;
  
  hou3=t/10000l;
  min3=(t-hou3*10000l)/100l;
  sek3=t-hou3*10000l-min3*100l;
  t=hou3*3600.+min3*60.+sek3;

  if (t1>t2)
    t1-=86400.;
  fr=f;
  fr2=fr*fr;
  u1=fh/fr;
  u=u1*u1;

  i=ihop-1;

  FR(i)=fr;

  d0=d*RAD;
  alfa=a*RAD;
  tim=t;
  TIME(i)=tim;

  IOX(i)=iox=iOX;

  W=iW;
  IG=iIG;
  iyear=iYear;
  ames=aMes;
  inions(iyear,ames,W,IG,rmax,keyvod,keyMod,keyEs,keystorm,tim,t1,t2,dt);
  treks(d0,alfa,ihop,n,delt0,eps,ep,ep1,e,putdat);

  return 0;

} /* path0s */


void drawIon(double *fpl, double *hpl, int nf, int npoin, double hMin, double hMax, double fMax)
{
}

void drawTrek(double *sTr, double *hTr, long pointTr)
{
}

void drawInf(char *)
{
}
