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
  double *f;
  long   *t;
  double alfa,d0,delt0,eps,ep,ep1,Z0,Z1; /////////////////////////
  double e=.0625;
  int    n,io,ix,ih,ihm,kolf;
  int    i,j,id;
  long   nfr,ox1,ox2,mes,hop1,hop2,ifr,
         ikor,ik,ir;
  long   it1,it2,it3,hou1,hou2,hou3,min1,min2,min3,
         sek1,sek2,sek3;

  FILE *in,*out;

  PUTDAT *putdat;
  double eps1,epsa;
  double eps2;
  double rmax;
  double dd0,aa0;
  double d1;
  double mpch=.0;
  long   keymod,keystorm,keyes,keyh,keyugl,keymp;
  long   hou,min,sek,msek;
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
  fscanf(in,"%lg%lg%lg%lg%lg%lg%lg%lg%lg%lg",&delt0,&eps,&ep,&ep1,&eps1,&eps2,&epsa,&dd0,&aa0,&rmax);

  fscanf(in,"%lg%lg%lg%lg%lg%lg%d%lg%lg%lg",
            &lon0,&lat0,&Z0,&lon1,&lat1,&Z1,&iyear,&ames,&w,&ig);

  fscanf(in,"%ld%ld%ld",&it1,&it2,&it3);

  fscanf(in,"%ld%ld%ld%ld%ld",&nfr,&hop1,&hop2,&ox1,&ox2);

  if (nfr>0)
  {
      f=new double[nfr];
      t=new long[nfr];
      for(i=0; i<nfr; i++)
          fscanf(in,"%lg%ld",(f+i),(t+i));
  }

  putdat=new PUTDAT[hop2*maxKor];

  keyugl=0;

  for(ifr=0; ifr<nfr; ifr++)
  {
      for(ih=hop1; ih<=hop2; ih++)
      { /* ih */
          keyugl=0;
          for(ik=ox1; ik<=ox2; ik++)
          { /* ik */
              n=pk3_modul(lat0,lon0,Z0,lat1,lon1,Z1,eps1,eps2,epsa,dd0,aa0,
                          iyear,ames,it1,it2,it3,w,ig,keymod, keyes,keystorm,keymp,keyh,keyugl,
                          f[ifr],t[ifr],ih,ik,putdat,mpch);
              if (keymp>0)
                  fprintf(out,"\nmpch=%6.2f",mpch);
              for(i=0; i<n; i++)
                  outtrs(out,putdat+ih*i,ih);
              keyugl=n;
          } /* ik */
      } /* ih */
  }
  outtrs(out,putdat,-1);

  delete[] f;
  delete[] t;
  delete[] putdat;

  return 0;
}

