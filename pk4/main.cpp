#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "paths.h"

int main(int argc, char *argv[])
{
  double s0,alf,alf1,s1,lon0,lat0,lon1,lat1,dlon,
         w,ig,ames,ptr,b,
         time1,time2,dtime,
         Fam,Du,Dl,Vd,SFam,Sdu,Sdl,Svd,
         emp,epom,epom_i,sig_i;
  double f;
  long   t;
  double t1,t2,t3;
  double alfa,d0,delt0,eps,ep,ep1,Z0,Z1; /////////////////////////
  double e=.0625;
  int    io,ix,ih,ihm,kolf;
  int    i,j,id,hou,min,sek;
  int    *n;
  int    nt;
  long   nfr,ox1,ox2,mes,hop1,hop2,ifr,
         ikor,ik,ir,keyh;
  long   it1,it2,it3,hou1,hou2,hou3,min1,min2,min3,
         sek1,sek2,sek3;

  FILE *in,*out;

  PUTDAT **putdat;
  double eps1,epsa;
  double eps2;
  double rmax;
  double dd0,aa0;
  double d1;
  double *tVosZah;
  double *mpch;
  long   keymod,keystorm,keyes,keymp;
  int    iyear;
/*--------------------------------------------------------------*/

  if ((argc>1 || argc>2) && strcmp(*(argv+1),"con")!=0
                                && strcmp(*(argv+1),"CON")!=0)
    in=fopen(*(argv+1),"rt");
  else
    in=stdin;

  if (!in)
    {
      printf("\nInput File:%s error open\n",*(argv+1));
      exit(EXIT_FAILURE);
    }

  if ((argc>2 || argc>3) && strcmp(*(argv+2),"con")!=0
                         && strcmp(*(argv+2),"CON")!=0)
    {
      out=fopen(*(argv+2),"at");
    }
  else
        out=stdout;
  if (!out)
    {
      printf("\nOutput File:%s error open\n",*(argv+2));
      exit(EXIT_FAILURE);
    }

  fscanf(in,"%ld%ld%ld%ld%ld",&keymod,&keyes,&keystorm,&keymp,&keyh);
  //
  // keymp 0 - не рассчитывать, 1 -рассчитывать
  //
  fscanf(in,"%lg%lg%lg%lg%lg%lg%lg%lg%lg%lg",&delt0,&eps,&ep,&ep1,&eps1,&eps2,&epsa,&dd0,&aa0,&rmax);

  fscanf(in,"%lg%lg%lg%lg%lg%lg%d%lg%lg%lg",
            &lon0,&lat0,&Z0,&lon1,&lat1,&Z1,&iyear,&ames,&w,&ig);

  fscanf(in,"%ld%ld%ld",&it1,&it2,&it3);
  //it1=000000l;
  //it2=240000l;
  //it3=003000l;
  hou=it1/10000;
  min=(it1-hou*10000l)/100l;
  sek=it1-hou*10000l-min*100l;
  t1=hou+min/60.+sek/3600.;
  hou=it2/10000;
  min=(it2-hou*10000l)/100l;
  sek=it2-hou*10000l-min*100l;
  t2=hou+min/60.+sek/3600.;
  hou=it3/10000;
  min=(it3-hou*10000l)/100l;
  sek=it3-hou*10000l-min*100l;
  t3=hou+min/60.+sek/3600.;
  nt=(t2-t1)/t3+.5;

  //fscanf(in,"%ld%ld%ld%ld%ld",&nfr,&hop1,&hop2,&ox1,&ox2);
  nfr=1;
  hop1=hop2=1;
  ox1=ox2=1;

  fscanf(in,"%lg",&f);
  n=new int[MaxGran];
  tVosZah=new double[MaxGran];
  mpch=new double[nt];
  putdat=(PUTDAT**)malloc(sizeof(PUTDAT*)*MaxGran);
  for(i=0; i<MaxGran; i++)
  {
    putdat[i]=(PUTDAT*)malloc(sizeof(PUTDAT)*hop2*maxKor);
    tVosZah[i]=.0;
  }
  for(i=0; i<nt; i++)
  {
    mpch[i]=.0;
  }

  int flag=pk4_modul(lat0,lon0,Z0,lat1,lon1,Z1,eps1,eps2,epsa,dd0,aa0,
                     iyear,ames,it1,it2,it3,w,ig,keymod, keyes,keystorm,keymp,keyh,f,putdat,n,tVosZah,mpch);

  if (keymp)
  {
      for(i=0; i<nt; i++)
      {
        if (!(i%4))
          fprintf(out,"\n");
        fprintf(out,"  t=%5.2f MUF=%5.2f",t1+t3*i,mpch[i]);
      }
  }

  if (flag)
  {

      for(i=0; i<flag; i++)
      {
        hou=tVosZah[i]/3600.;
        min=(tVosZah[i]-hou*3600.)/60.;
        sek=tVosZah[i]-hou*3600.-min*60.;
        t=hou*10000l+min*100l+sek+.5;
        fprintf(out,"\nTime(hhmmss)=%06d  (s)=%f",t,tVosZah[i]);
      }

      for(i=0; i<flag; i++)
      {
        for(j=0; j<n[i]; j++)
          outtrs(out,putdat[i]+j,1);
      }
      outtrs(out,putdat[0],-1);

  }
  else
  {
      fprintf(out,"fr=%6.3f, no time",f);
  }

  for(i=0; i<MaxGran; i++)
  {
    delete[] putdat[i];
  }
  delete putdat;
  delete[] n;
  delete[] tVosZah;
  delete[] mpch;

  return 0;
}

