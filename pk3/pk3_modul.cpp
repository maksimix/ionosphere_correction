#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "paths.h"
#include "../antenn/antenn.h"

/*==============================================================*/

int pk3_modul(double lat0,     //  широта, град
              double lon0,     //  долгота, град
              double Z0,       //  высота точки излучения, км
              double lat1,     //  широта, град
              double lon1,     //  долгота, град
              double Z1,       //  высота точки приема, км
              double eps1,     //  точность по дальности
              double eps2,     //  порог по дальности
              double epsa,     //  точность по азимуту
              double dd0,      //  шаг по углу места
              double aa0,      //  шаг по азимуту
              int iYear,       //  год
              double aMes,     //  месяц в десятичном формате
              long it1,        //  начальное время в формате ччммсс
              long it2,        //  конечное время в формате ччммсс
              long it3,        //  шаг по времени в формате ччммсс для прогноза
              double iW,       //  число Вольфа
              double iIG,      //  индекс солнечной активности
              long   keymod,   //  1 - CCIR, 0 - URSI
              long   keyes,    //  1 - прогноз ES, 0 - нет ES
              long   keystorm, //  1 - учет магнитных возмущений, 0 - нет магнитных возмущений
              long   keymp,    //  1 - рассчитывать МПЧ, 0 - нет
              long   keyh,     //  1 - глобаль модель геомагнитного поля, 0 - геомагнитное поле постоянно
              long   keyugl,   //  <=0 - автоматическое определение диапазона поиска корней, >0 - по данным в putdat
              double f,        //  частота, МГц
              long   t,        //  время излучения в формате ччммсс
              int iHop,        //  число скачков
              int iOX,         //  0 - o-волна, 1 - x-волна
              PUTDAT* putdat,  //  результаты расчета
              double &mpch)    //  МПЧ для заданного числа скачков и компоненты
{
  double s0,alf,alf1,s1,dlon,
         w,W,ig,IG,ames,ptr,b,
         t1,t2,t3,dt;
  double alfa,d0,delt0,eps,ep,ep1; /////////////////////////
  double e=.0625;
  int    n,ih;
  double dbeg,dend;
  long   hou1,hou2,hou3,min1,min2,min3,
         sek1,sek2,sek3;
  char   mod[17];
  double rmax;
  double d1;
  long   keyMod,keyvod,keypri,keypr,keynois,
         keypol,keyel,keyFr,keyOut;
  long   hou,min,sek,msek;
  int    iyear;
/*--------------------------------------------------------------*/

  keyvod=0;
  keynu=0;
  keyMod=keymod;
  keyl2=0;
  keyEs=keyes;
  keynois=0;
  keypri=0;
  keypr=0;
  keyh=0;
  keytr=0;
  keysol=0;
  keympr=0;

  delt0=.1;
  eps=1.e-6;
  ep=1.e-6;
  ep1=1.e-3;
  rmax=4000.;

  e=e*eps;
  eps1*=.01;
  eps2*=.01;
  rmax*=.01;
  dd0*=RAD;
  epsa*=RAD;
  aa0*=RAD;

  ames=aMes;

  teta0=90.-lat0;
  fi0=lon0;

  lon0 *=RAD;  lat0 *=RAD;
  lon1 *=RAD;  lat1 *=RAD;
  dlon=lon1-lon0;
  z0=Z0*.01+R0;
  z1=Z1*.01+R0;

  s0=sin(lat0)*sin(lat1)+cos(lat0)*cos(lat1)*cos(dlon);
  s0=R0*atan2(sqrt(1.-s0*s0),s0);
  alf =atan2(cos(lat1)*sin(dlon),sin(lat1)*cos(lat0)-
             sin(lat0)*cos(lat1)*cos(dlon));
  alf1=atan2(-cos(lat0)*sin(dlon),sin(lat0)*cos(lat1)-
             sin(lat1)*cos(lat0)*cos(dlon));

  fi0   *=RAD;
  teta0 *=RAD;

  if (eps2<.0 && s0>2.5 || eps2<-2.5 && s0<2.5)
    if (s0>5.)   eps2=.2*s0;
    else
      if (s0<2.5) eps2=-2.5;
      else        eps2=.0;
  if (keyugl<=0 || keymp>0)
  {
    if (s0>25.)  dend=.25*PI;
    else
      if (s0>2.5)  dend=.50*PI;
      else         dend=.75*PI;
  }
  else
  {
      dbeg=D1(iHop*0)*RAD-dd0;
      dend=D1(iHop*(keyugl-1))*RAD+dd0;
      if (dbeg<.0)
          dbeg=.0;
  }

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
  if (t1>t2)
    t1-=86400.; // теперь полночь содержится внутри интервала моделирования

  h0=H0+R0;
  s1=s0/(2.*(iHop+1)*R0);
  dbeg=atan((h0*cos(s1)-R0)/(h0*sin(s1)))-dd0;

  hou3=t/10000l;
  min3=(t-hou3*10000l)/100l;
  sek3=t-hou3*10000l-min3*100l;
  t=hou3*3600.+min3*60.+sek3;

  infils(keyh);

  W=iW;
  IG=iIG;
  iyear=iYear;
  ames=aMes;
  tim=t; // время для ПИВ отсчитывается от 0 (от полночи текущего дня)

  inions(iyear,ames,W,IG,rmax,keyvod,keyMod,keyEs,keystorm,tim,t1,t2,dt);

  ih=iHop;
  iox=iOX;
  *mod='\0';
  if (keymp)
    mpch=mpchs(s0,alf,ih,dbeg,dend,delt0,eps,ep,ep1,e,eps2,epsa,dd0,aa0,putdat);
  else
    mpch=.0;

  fr=f;
  fr2=fr*fr;
  u1=fh/fr;
  u=u1*u1;
  ih=iHop;
  n=0;
  iox=iOX;
  *mod='\0';
  n=solt(dbeg,dend,alf,s0,ih,delt0,eps,ep,ep1,e,eps1,eps2,epsa,dd0,aa0,putdat);
  for(int i=0; i<n; i++)
  {
      for(int j=0; j<ih; j++)
      {
          IOX( ih*i+j)=iox;
          FR(  ih*i+j)=fr;
          TIME(ih*i+j)=tim;
      }
  }

  return n;
}


void drawIon(double *fpl, double *hpl, int nf, int npoin, double hMin, double hMax, double fMax)
{
}

void drawTrek(double *sTr, double *hTr, long pointTr)
{
}

void drawInf(char *inf)
{
}
