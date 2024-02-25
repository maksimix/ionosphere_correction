/***************************************************************/
/*                                                             */
/* Головная функция, организующая постороение лучевой траекто- */
/* рии в сферически слоистой горизотнально-неоднородной        */
/* магнитоактивной ионосфере.                                  */
/*                                                             */
/*VGG                                                          */
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "paths.h"

#define STR1 "\ndelt0=%8.1lg  eps=%8.1lg  ep=%8.1lg  ep1=%8.1lg"

/*==============================================================*/

int main(int argc, char *argv[])
{
  double alfa,d0,delt0,eps,ep,ep1,
         f[200],d[200],a[200];
  long   t[200];
  double lat0,lon0,Z0,Z1,
         w,ig,ames;
  long   it1,it2,it3,hou1,hou2,hou3,min1,min2,min3,
         sek1,sek2,sek3;
  double t1,t2,t3,time,tmre,dt,
         time1,time2,dtime;

  double e=.0625;

  int n,io,ix,ihop,kolf,iyear;
  long keystorm, keymod, keyes,keyh;
  int i,j,id;

  PUTDAT putdat;

  FILE *in,*out;

/*--------------------------------------------------------------*/

  keyEs=0;

  if (argc>1 && strcmp(*(argv+1),"con")!=0)
    in=fopen(*(argv+1),"rt");
  else
    in=stdin;

  if (in==NULL)
    {
      printf("Input File:%s error open\n",*(argv+1));
      exit(EXIT_FAILURE);
    }

  if (argc>2 && strcmp(*(argv+2),"con")!=0)
    out=fopen(*(argv+2),"wt");
  else
    out=stdout;

  if (out==NULL)
    {
      printf("Output File:%s error open\n",*(argv+2));
      exit(EXIT_FAILURE);
    }

  fscanf(in,"%ld%ld%ld%ld",&keymod,&keyes,&keystorm,&keyh);
  
  fscanf(in,"%lg%lg%lg%lg",&delt0,&eps,&ep,&ep1);

  fscanf(in,"%lg%lg%lg%lg%ld%lg%lg%lg",
         &lon0,&lat0,&Z0,&Z1,&iyear,&ames,&w,&ig);

  fscanf(in,"%ld%ld%ld",&it1,&it2,&it3);

  ihop=1;

  fscanf(in,"%d",&kolf);

  for(id=0; id<kolf; id++)
    fscanf(in,"%lg%lg%lg%ld",&f[id],&d[id],&a[id],&t[id]);

  fscanf(in,"%d%d",&io,&ix);

  for(id=0; id<kolf; id++)
  {
      for(iox=io; iox<=ix; iox++)
      {
          pk2_modul(lat0,lon0,Z0,Z1,iyear,ames,it1,it2,it3,w,ig,keymod,keyes,keystorm,keyh,f[id],d[id],a[id],t[id],iox,&putdat);
          outtrs(out,&putdat,ihop);
      }
  }

  outtrs(out,&putdat,-1);

  return 0;

} /* path0s */

