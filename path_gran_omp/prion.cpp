#include "paths.h"

#define STR1  "\n+================================================\
==============================+\n"
#define STR10 "|   Medium characteristics Sunspot number=%6.1f IG=%6.1f   \
GMT time:%02d:%02d    |\n"

#define STR11 "|------------------------------------------------\
------------------------------|\n"

#define STR2  "|-------+----+-----+------+----+-----+----+-----+\
-----+-----+-----+-----+------|\n"

#define STR3  "+================================================\
==============================+\n"

#define STR4 "|   S   | fh |  I  |   D  | fd |  hd | fe |  he |\
 ff1 | hf1 | ff2 | hf2 |   Hi |\n"

#define STR5 "|%7.1lf|%4.2lf|%5.1lf|%6.1lf|%4.2lf|%5.1lf|%4.2lf|%5.1lf|\
%5.2lf|%5.1lf|%5.2lf|%5.1lf|%6.1lf|\n"

#define STR20 "\n+==================================+\n"
#define STR21 "|       Es-layer parametres        |\n"
#define STR22 "|----------------------------------|\n"
#define STR23 "|   S   | hEs | fbEs | f0Es | P Es |\n"
#define STR24 "|-------+-----+------+------+------|\n"
#define STR25 "|%7.1f|%5.1f|%5.2f |%5.2f |%5.1f |\n"
#define STR26 "+==================================+\n"


void prion(FILE   *out,
           double  lat0,
           double  lon0,
           double  lat1,
           double  lon1,
           double  time,
           double  W,
           double  IG,
           long    keypri,
           long    keyes)
/***************************************************************/
/* Функция предназначена для организации отображения           */
/* ионосферной информации.                                     */
/*                                                             */
/* keypri - 0 - не отображать информацию;                      */
/*          1 - отображать во всех точках;                     */
/*         -1 - отображать по концам трассы;                   */
/*          2 - отображать графически во всех точках;          */
/*         -2 - отображать графически по концам трассы.        */
/*                                                             */
/*VGG 18.05.07                                                 */
/***************************************************************/
{
  long    step,hou,min;
  long    i,j;
  double  t=time;
  double  v,vfi,vteta,vr,vt;
  double  dlon,s0,alf,sao,cao,ss,cs,slf,clf,ds,s,cdlon;
  int     nf=5;
  double aokor[5],alkor[5];
  double fpl[500],hpl[500],hMin=.0,hMax=.0;
  double fMax=.0;
  double V=mytrek_ext->getV();
  IonPar p;
  int    npoint=100;

  if (!keypri || mod<8)
  {
      hMax=100.*(hm-R0)+50.;
      double h,h00=100.*h0;
      double dh=(hMax-hMin)/(double)(npoint-1);
      mytrek_ext->setTime(time);

      nf=1;
      //printf("\nhm=%f  hMax=%f",100.*(hm-R0),hMax);
      for(j=0; j<npoint; j++)
      {
          h=h00+dh*(double)j;
          mytrek_ext->ionos(fi0,teta0,.01*h,6);
          fpl[j]=sqrt(V);
          hpl[j]=h-100.*R0;
          if (fMax<fpl[j])
              fMax=fpl[j];
          //printf("\nh=%f  f=%f",h,sqrt(::v));
      }

      drawIon(fpl,hpl,nf,npoint,hMin,hMax,fMax);

      return;
  }
  printf("\n1111111111111111111111111111111\n");
  printf("\nlon0=%8.3f lat0=%8.3f  lon1=%8.3f lat1=%8.3f",lon0/RAD,lat0/RAD,lon1/RAD,lat1/RAD);
  dlon=lon1-lon0;
  s0=sin(lat0)*sin(lat1)+cos(lat0)*cos(lat1)*cos(dlon);
  s0=100.*R0*atan2(sqrt(1.-s0*s0),s0);
  alf =atan2(cos(lat1)*sin(dlon),sin(lat1)*cos(lat0)-
             sin(lat0)*cos(lat1)*cos(dlon));

  if (fabs(lat0-lat1)<.00001 && fabs(lon0-lon1)<.00001)
  {
      nf=1;
      ds=.0;
  }
  else
  {
      if (keypri>0)
      {
          nf=5;
      }
      else
      {
          nf=2;
      }
      ds=s0/(100.*R0*(nf-1));
  }
  

  sao=sin(lat0);
  cao=cos(lat0);

  slf=sin(alf);
  clf=cos(alf);

  for(i=0; i<nf; i++)
  {
      s=ds*(double)i;

      ss=sin(s);
      cs=cos(s);
      aokor[i]=atan2(slf*ss,(cs*cao-clf*ss*sao))+lon0; // долготы
      cdlon=cos(aokor[i]-lon0);
      alkor[i]=PI05-atan2((cs*cao-clf*ss*sao),          // широты
                         (cdlon*(cs*sao+clf*ss*cao)));
      if (cdlon<.0)
        alkor[i]-=PI;
  }

  if (t<.0)
    t+=86400.;

  hou=t/3600.;
  min=(t-(double)hou*3600.)/60.;

  fprintf(out,STR1);
  fprintf(out,STR10,W,IG,hou,min);
  fprintf(out,STR11);
  fprintf(out,STR4);
  fprintf(out,STR2);
  for(i=0; i<nf; i++)
  {
      ionosf(aokor[i],PI05-alkor[i],(H0+R0)*100.,time,v,vfi,vteta,vr,vt,p);
      fprintf(out,STR5,100.*R0*ds*i,p.fhTemp,p.ITemp,p.DTemp,p.F0D,(p.HmD-R0)*100.,p.F0E,(p.HmE-R0)*100.,
              p.F0F1,(p.HmF1-R0)*100.,p.F0F2,(p.HmF2-R0)*100.,p.Hi);
      if (hMax<(p.HmF2-R0)*100.)
          hMax=(p.HmF2-R0)*100.;
      if (p.F0F2>fMax)
          fMax=p.F0F2;
  }
  fprintf(out,STR3);
  fflush(out);
  //cout<<flush;

  if (keyes>=0)
  {
      fprintf(out,STR20);
      fprintf(out,STR21);
      fprintf(out,STR22);
      fprintf(out,STR23);
      fprintf(out,STR24);
      for(i=0; i<nf; i++)
      {
          ionosf(aokor[i],PI05-alkor[i],(H0+R0)*100.,time,v,vfi,vteta,vr,vt,p);
          fprintf(out,STR25,100.*R0*ds*i,(p.HmEs-R0)*100.,p.FbEs,p.F0Es,p.PEs);
      }
      fprintf(out,STR26);
      fflush(out);
      //cout<<flush;
  }

  hMax+=50.;
  double h,h0=100.*(H0+R0);
  double dh=(hMax-hMin)/(double)(npoint-1);

  mytrek_ext->setTime(time);
  for(i=0; i<nf; i++)
  {
      //printf("\ni=%d lon0=%f aokor[i]=%f alkor[i]=%f",i,lon0/RAD,aokor[i]/RAD,alkor[i]/RAD);
      sf=sin(aokor[i]);
      cf=cos(aokor[i]);
      st=sin(PI05-alkor[i]);
      ct=cos(PI05-alkor[i]);
      for(j=0; j<npoint; j++)
      {
          h=h0+dh*(double)j;
          mytrek_ext->ionos(aokor[i],PI05-alkor[i],.01*h,6);
          fpl[100*i+j]=sqrt(V);
          hpl[100*i+j]=h-100.*R0;
          //printf("\nh=%f  f=%f",h,sqrt(::v));
      }
  }

  double fi[MaxSion], teta[MaxSion];
  double smin;
  dsIon=(sMaxIon-sMinIon)/(100.*R0*(MaxSion-1));
  smin=sMinIon/(100.*R0);
  sao=sin(lat0);
  cao=cos(lat0);

  slf=sin(alfIon*RAD);
  clf=cos(alfIon*RAD);
  printf("\nMaxSion=%d\n",MaxSion);
  for(i=0; i<MaxSion; i++)
  {
      s=smin+dsIon*(double)i;

      ss=sin(s);
      cs=cos(s);
      fi[i]=atan2(slf*ss,(cs*cao-clf*ss*sao))+lon0; // долготы
      cdlon=cos(fi[i]-lon0);
      teta[i]=PI05-atan2((cs*cao-clf*ss*sao),          // 90-широты
                    (cdlon*(cs*sao+clf*ss*cao)));
      if (cdlon<.0)
          teta[i]-=PI;
      teta[i]=PI05-teta[i];
      //printf("\ns=%6.1f fi[%03d]=%8.3f  teta[%03d]=%8.3f lon0=%8.3f lat0=%8.3f",s*R0*100.,i,fi[i]/RAD,i,teta[i]/RAD,lon0/RAD,lat0/RAD);
  }
  dsIon=(sMaxIon-sMinIon)/(MaxSion-1);

  mytrek_ext->setTime(time);
  mytrek_ext->setFr(1.);
  printf("\nMaxHion=%d\n",MaxHion);
  hminIon=.0;//100.*H0;
  h0=100.*R0;
  dhIon=(hMax-hMin+100.*H0)/(double)(MaxHion-1);
  fmaxIon=.0;
  for(i=0; i<MaxSion; i++)
  {
      sf=sin(fi[i]);
      cf=cos(fi[i]);
      st=sin(teta[i]);
      ct=cos(teta[i]);
      for(j=0; j<MaxHion; j++)
      {
          h=h0+dhIon*(double)j;
          if (mytrek_ext->ionos(fi[i],teta[i],.01*h,6))
          {
              fplIon[i][j]=0.;
          }
          else
          {
              fplIon[i][j]=sqrt(V);
              if (fmaxIon<fplIon[i][j])
                  fmaxIon=fplIon[i][j];
          }
      }
  }

  printf("\ndrawIon dhIon=%f fpl=%f\n",dhIon,fplIon[MaxSion-1][MaxHion-10]);
  drawIon(fpl,hpl,nf,npoint,hMin,hMax,fMax);
}
