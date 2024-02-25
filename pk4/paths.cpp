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
  double alfa,d0,delt0,eps,ep,ep1,Z0,Z1; /////////////////////////
  double e=.0625;
  int    n[2],io,ix,ih,ihm,kolf;
  int    i,j,id;
  long   nfr,ox1,ox2,mes,hop1,hop2,ifr,
         ikor,ik,ir;
  long   it1,it2,it3,hou1,hou2,hou3,min1,min2,min3,
         sek1,sek2,sek3;

  FILE *in,*out;

  PUTDAT **putdat;
  double eps1,epsa;
  double eps2;
  double rmax;
  double dd0,aa0;
  double d1;
  long   keymod,keystorm,keyes;
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

  fscanf(in,"%ld%ld%ld",&keymod,&keyes,&keystorm);
  fscanf(in,"%lg%lg%lg%lg%lg%lg%lg%lg%lg%lg",&delt0,&eps,&ep,&ep1,&eps1,&eps2,&epsa,&dd0,&aa0,&rmax);

  fscanf(in,"%lg%lg%lg%lg%lg%lg%d%lg%lg%lg",
            &lon0,&lat0,&Z0,&lon1,&lat1,&Z1,&iyear,&ames,&w,&ig);

  //fscanf(in,"%ld%ld%ld",&it1,&it2,&it3);
  it1=000000l;
  it2=240000l;
  it3=003000l;

  //fscanf(in,"%ld%ld%ld%ld%ld",&nfr,&hop1,&hop2,&ox1,&ox2);
  nfr=1;
  hop1=hop2=1;
  ox1=ox2=1;

  fscanf(in,"%lg",&f);
  putdat=(PUTDAT**)malloc(sizeof(PUTDAT*)*2);
  putdat[0]=(PUTDAT*)malloc(sizeof(PUTDAT)*hop2*maxKor);
  putdat[1]=(PUTDAT*)malloc(sizeof(PUTDAT)*hop2*maxKor);
  double tVoshod=.0, tZahod=.0;

  int flag=pk4_modul(lat0,lon0,Z0,lat1,lon1,Z1,eps1,eps2,epsa,dd0,aa0,
                     iyear,ames,it1,it2,it3,w,ig,keymod, keyes,keystorm,f,putdat,n,tVoshod,tZahod);
  if (flag)
  {

      hou=tVoshod/3600.;
      min=(tVoshod-hou*3600.)/60.;
      sek=tVoshod-hou*3600.-min*60.;
      t=hou*10000l+min*100l+sek+.5;
      printf("\ntVoshod=%d  %f",t,tVoshod);

      hou=tZahod/3600.;
      min=(tZahod-hou*3600.)/60.;
      sek=tZahod-hou*3600.-min*60.;
      t=hou*10000l+min*100l+sek+.5;
      printf("\ntZahod=%d  %f",t,tZahod);

      outtrs(out,putdat[0],1);
      outtrs(out,putdat[1],1);
      outtrs(out,putdat[0],-1);
  }

  return 0;
}

