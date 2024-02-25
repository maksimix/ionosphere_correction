#include "paths.h"

                                // функция возвращает количество границ мертвой зоны или 0, если они не найдены
int pk4_modul(double lat0,     //  широта, град
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
              int iyear,       //  год
              double ames,     //  месяц в десятичном формате
              long it1,        //  начальное время в формате ччммсс
              long it2,        //  конечное время в формате ччммсс
              long it3,        //  шаг по времени в формате ччммсс для прогноза
              double w,       //  число Вольфа
              double ig,      //  индекс солнечной активности
              long   keymod,   //  1 - CCIR, 0 - URSI
              long   keyes,    //  1 - прогноз ES, 0 - нет ES
              long   keystorm, //  1 - учет магнитных возмущений, 0 - нет магнитных возмущений
              long   keymp,    //  1 - рассчитывать МПЧ, 0 - нет
              long   keyh,
              double f,         // частота
              PUTDAT **putdat,  // результаты в окрестности МПЧ х-волны
              int *n,           // число корней
              double *tVosZah,  // временные границы мертвых зон
              double *mpch)     //  МПЧ для заданного числа скачков и компоненты
{
  long t;
  long keyugl=0;
  int  hou, min, sek;
  int  nt;
  double epsDt=10., Dt=.0;
  double tTemp, tBeg=.0, tEnd=24.*3600., tStep=30.*60.;
  double tx1=-1., tx2=-1.;
  double mpchTemp;
  //FILE *out;

  //out=fopen("con","w");
  hou=it1/10000;
  min=(it1-hou*10000l)/100l;
  sek=it1-hou*10000l-min*100l;
  tBeg=hou*3600+min*60.+sek;
  hou=it2/10000;
  min=(it2-hou*10000l)/100l;
  sek=it2-hou*10000l-min*100l;
  tEnd=hou*3600.+min*60.+sek;
  hou=it3/10000;
  min=(it3-hou*10000l)/100l;
  sek=it3-hou*10000l-min*100l;
  tStep=hou*3600+min*60.+sek;

  int ih=1;
  int ik=1;
  int flag;
  int flagOt=1, flagOut=0;
  nt=0;
  for(flag=0; flag<MaxGran; flag++)
  {
          tx1=tx2=-1.;
          for(tTemp=tBeg; tTemp<tEnd && (tx1<.0 || tx2<.0); tTemp+=tStep)
          {
                hou=tTemp/3600.;
                min=(tTemp-hou*3600.)/60.;
                sek=tTemp-hou*3600.-min*60.;
                t=hou*10000l+min*100l+sek;
                //printf("\ntTemp=%f   t=%d",tTemp,t);
                if (!flag || tTemp>tBeg)
                {
                  n[flag]=pk3_modul(lat0,lon0,Z0,lat1,lon1,Z1,eps1,eps2,epsa,dd0,aa0,
                                    iyear,ames,it1,it2,it3,w,ig,keymod, keyes,keystorm,keymp,keyh,keyugl,f,t,ih,ik,putdat[flag],mpch[nt]);
                  //printf("\nt=%f  MUF=%f",tTemp,mpch[nt]);
                  nt++;
                }
                else
                  n[flag]=pk3_modul(lat0,lon0,Z0,lat1,lon1,Z1,eps1,eps2,epsa,dd0,aa0,
                                    iyear,ames,it1,it2,it3,w,ig,keymod, keyes,keystorm,0,keyh,keyugl,f,t,ih,ik,putdat[flag],mpchTemp);

                flagOt*=n[flag];
                flagOut+=n[flag];
                if (n[flag])
                  tx1=tTemp;
                else
                  tx2=tTemp;
                //printf("\ntTemp=%f n=%d tx1=%f tx2=%f",tTemp,n[flag],tx1,tx2);
                //if (n[flag])
                //    outtrs(out,putdat[flag],ih);
                tBeg=tTemp;
          }

          if (flagOt>0 || flagOut==0) // на заданной частоте временной интервал восход-заход не найден
            return flag;
          if (tTemp>=tEnd)
            return flag;

          Dt=fabs(tx2-tx1);
          while(Dt>epsDt || !n[flag])
          {
                    tTemp=.5*(tx1+tx2);
                    hou=tTemp/3600.;
                    min=(tTemp-hou*3600.)/60.;
                    sek=tTemp-hou*3600.-min*60.;
                    t=hou*10000l+min*100l+sek;
                    n[flag]=pk3_modul(lat0,lon0,Z0,lat1,lon1,Z1,eps1,eps2,epsa,dd0,aa0,
                                iyear,ames,it1,it2,it3,w,ig,keymod,keyes,keystorm,0,keyh,keyugl,f,t,ih,ik,putdat[flag],mpchTemp);
                    if (n[flag])
                      tx1=tTemp;
                    else
                      tx2=tTemp;
                    Dt=fabs(tx2-tx1);
                    //printf("\n2 tTemp=%f n=%d tx1=%f tx2=%f Dt=%f",tTemp,n[flag],tx1,tx2,Dt);
                    //if (n[flag])
                    //    outtrs(out,putdat[flag],ih);
          }
          tVosZah[flag]=tTemp;
  }

  return flag;
}
