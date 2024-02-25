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
#include <sys/time.h>
#include <sys/timeb.h>

#include "paths.h"


void inions(FILE *in, FILE *out);

void infils(FILE *in, FILE *out);


#define STR1 "\ndelt0=%8.1lg  eps=%8.1lg  ep=%8.1lg  ep1=%8.1lg"

/*==============================================================*/

int main(int argc, char *argv[])
{
  double alfa,d0,delt0,eps,ep,ep1,
         f[200],d[200],a[200],t[200];
  double lat0,lon0,
         w,W,ig,IG,ames,ptr,b,rmax;
  long   it1,it2,it3,hou1,hou2,hou3,min1,min2,min3,
         sek1,sek2,sek3;
  double t1,t2,t3,time,tmre,dt,
         time1,time2,dtime;

  int n,io,ix,ihop,kolf,iyear;
  long keyvod, keyMod, keyEs, keypri;
  int i,j,id;
  double T1,T2,DT;

  PUTDAT *putdat;

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


  fscanf(in,"%lg%lg%lg%lg%lg",&delt0,&eps,&ep,&ep1,&rmax);
  fprintf(out,STR1,delt0,eps,ep,ep1);
  fscanf(in,"%ld%ld%ld%ld%ld%ld%ld",&keyvod,&keynu,&keyMod,&keyl2,&keyEs,&keypri,&keytr);

  RMax=rmax;
  z0=z1=R0;
  rmax*=.01;

  fscanf(in,"%lg%lg%lg%lg%ld%lg%lg%lg%lg%lg",
         &lon0,&lat0,&z0,&z1,&iyear,&ames,&w,&ig,&ptr,&b);

  fscanf(in,"%lg%lg%lg",&sMinIon,&sMaxIon,&alfIon);

  z0=.01*z0+R0;
  z1=.01*z1+R0;
  fi0=lon0*RAD;
  teta0=(90.-lat0)*RAD;
  lon0*=RAD;
  lat0*=RAD;

  fscanf(in,"%ld%ld%ld",&it1,&it2,&it3);
  printf("\nit1=%ld  it2=%ld  t3=%ld",it1,it2,it3);

  hou1=it1/10000l;
  hou2=it2/10000l;
  hou3=it3/10000l;
  min1=(it1-hou1*10000l)/100l;
  min2=(it2-hou2*10000l)/100l;
  min3=(it3-hou3*10000l)/100l;
  sek1=it1-hou1*10000l-min1*100l;
  sek2=it2-hou2*10000l-min2*100l;
  sek3=it3-hou3*10000l-min3*100l;
  printf("\nh=%ld m=%ld s=%ld h2=%ld m2=%ld s2=%ld",hou1,min1,sek1,hou2,min2,sek2);
  t1=hou1*3600.+min1*60.+sek1;
  t2=hou2*3600.+min2*60.+sek2;
  t3=hou3*3600.+min3*60.+sek3;
  dt=t3;
  printf("\nt1=%f  t2=%f  t3=%f",t1,t2,t3);
  if (t1>t2)
    t1-=86400.; // теперь полночь содержится внутри интервала моделирования

  mytrek_ext=new MyTrek(delt0,eps,ep,ep1);

  infils(in,out);

  W=w;
  IG=ig;
  inions(in,out,iyear,ames,W,IG,rmax,keyvod,keyMod,keyEs,t1,t2,dt);

  printf("\ninion\n");

  prion(out,lat0,lon0,lat0,lon0,t1,W,IG,keypri,keyEs);

  printf("\nprion\n");

  fscanf(in,"%d",&ihop);

  fscanf(in,"%d",&kolf);

  for(id=0; id<kolf; id++)
    fscanf(in,"%lg%lg%lg%lg",&f[id],&d[id],&a[id],&t[id]);

  printf("\nkolf=%d\n",kolf);

  fscanf(in,"%d%d",&io,&ix);

  fscanf(in,"%d",&n);
  printf("\n\nNumber diff. equation:%2d\n",n);
  fprintf(out,"\n\nNumber diff. equation:%2d\n",n);

  //putdat=(PUTDAT*)malloc(sizeof(PUTDAT)*ihop);
  putdat=0;

  //MyTrek myTrek(delt0,eps,ep,ep1);
  //myTrek.setFh(fh,h,dh,dh2);

  timeval tv;
  gettimeofday(&tv,NULL);
  T1=tv.tv_sec+tv.tv_usec/1000000.0;
  
  for(iox=io; iox<=ix; iox++)
  {
      //for(int i=0; i<ihop; i++)
      //  IOX(i)=iox;

      #pragma omp parallel for
      for(int id=0; id<kolf; id++)
      {
          MyTrek myTrek(delt0,eps,ep,ep1);
          myTrek.setFh(fh,h,dh,dh2);
          myTrek.copy_iri_model();
          PUTDAT* putdat=(PUTDAT*)malloc(sizeof(PUTDAT)*ihop);

          double fr=f[id];
          double d0=d[id]*RAD;
          double alfa=a[id]*RAD;
          double tim=t[id];

          for(int i=0; i<ihop; i++)
          {
              IOX(i)=iox;
              FR(i)=fr;
              TIME(i)=tim;
          }

          tim=tim+t1;
          //printf("\ntim=%f t1=%f\n",tim,t1);

          myTrek.treks(fr,tim,d0,alfa,ihop,n,putdat);
          
          outtrs(out,putdat,ihop);
          free(putdat);
          putdat=0;
      }
  }

  gettimeofday(&tv,NULL);
  T2=tv.tv_sec+tv.tv_usec/1000000.0;
  DT=T2-T1;
  printf("\ntime,ms=%8.3f\n",DT*1000.);

  outtrs(out,putdat,-1);

  if (putdat)
      free(putdat);

  if (spN_H)
      delete spN_H;
  if (mytrek_ext)
      delete mytrek_ext;

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

