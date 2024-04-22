#include <math.h>
#include <stdio.h>
#include <stdlib.h>

bool  eschar(double ai,
             double fi,
             double t,
             long    m,
             double *f0,
             double *fb,
             double *hes,
             double *pps)
/*******************************************************************/
/*                                                                 */
/*        Прогноз параметров спорадическог слоя Es.                */
/* О.Овезгельдыев, Г.В.Михайлова Изв.АН Туркм.ССР сер. Физ.-техн., */
/* хим. и геол. наук. N6,1967; N3,6 1976; N6 1977.                 */
/*                                                                 */
/* ai - магитное наклонение;                                       */
/* fi - широта;                                                    */
/* t  - московское время;                                          */
/* m  - номер месяца (1-12);                                       */
/* f0 - f0Es - частота полупрозрачности;                           */
/* fb - fbEs - частота экранировки;                                */
/* hes- высота ES-слоя;                                            */
/* pes- вероятность появления Es-слоя.                             */
/*                                                                 */
/*VGG                                                              */
/*******************************************************************/
{
  float ax[2][5],a[2][5][3],b[2][5][3],r[5],p[2];
  float ah0[2],ah[2][6],bh[2][6],ph[2],coff[228];
  float d,dh,x,x1;
  const float pi  =3.141593,
              ln10=2.3025851;
  long nfi,nfh,i,j,k;
  FILE *es=0;

  es=fopen("esfil.dat","rb");
  if (!es)
  {
      printf("\nError: в рабочей директории отсутствует файл esfil.dat\n");
      fflush(stdout);
      return false;
  }
  
  d=pi/36.;
  x=atan2(tan(ai),sqrt(cos(fi)));

  if (fabs(x)>1.39) x=(x>=.0)? 1.39 : -1.39;
  if (m<.0) m=m+12;
  if (m>12) m=m-12;

  x=fabs(x);
//  nfi=fabs(x)/d;
  nfi=x/d;

  x1=(float)nfi*d;

  fseek(es,20*nfi+340*(m-1),SEEK_SET);

  fread(ax,sizeof(ax),1,es);

  fseek(es,120*nfi+4080,SEEK_SET);

  for(i=0; i<2; i++)
    for(j=0; j<5; j++)
      for(k=0; k<3; k++)
        {
          fread(&a[i][j][k],4,1,es);
          fread(&b[i][j][k],4,1,es);
        }

  for(i=0; i<5; i++)
    {
      for(j=0; j<2; j++)
        {
          p[j]=.0;

          for(k=0; k<3; k++)
            p[j] +=a[j][i][k]*cos(t*(float)(k+1))+
                   b[j][i][k]*sin(t*(float)(k+1));

          p[j] +=ax[j][i];
        }

      r[i]=p[0]+(p[1]-p[0])*(x-x1)/d;
    }

  *f0=exp(ln10*r[0]);
  *fb=exp(ln10*r[2]);
  *pps=r[4]*100.;

  if (*pps>100.) *pps=100.;
  if (*fb>=*f0)   *fb=*f0-.1;

//  x=fabs(x);

  if (x-2.*d<.0)
    {
      dh=d;
      nfh=x/dh;
      x1=dh*(float)nfh;
    }
  else
    if (x-6.*d<.0)
      {
        dh=2.*d;
        nfh=x/dh+1;
        x1=dh*(float)(nfh-1);
      }
    else
      if (x-8.*d<.0)
        {
          dh=d;
          nfh=x/dh-2;
          x1=dh*(float)(nfh+2);
        }
      else
        if (x-12.*d<.0)
          {
            dh=2.*d;
            nfh=x/dh+2;
            x1=dh*(float)(nfh-2);
          }
        else
          {
            dh=d;
            nfh=x/dh-4;
            x1=dh*(float)(nfh+4);
          }

  fseek(es,68*(m-1)+4*nfh+6120,SEEK_SET);

  fread(ah0,4,2,es);

  fseek(es,816*(m-1)+48*nfh+6936,SEEK_SET);

  for(i=0; i<2; i++)
    for(j=0; j<6; j++)
      {
        fread(&ah[i][j],4,1,es);
        fread(&bh[i][j],4,1,es);
      }

  fclose(es);

  for(i=0; i<2; i++)
    {
      ph[i]=.0;

      for(j=0; j<6; j++)
        ph[i]=ah[i][j]*sin(t*(float)(j+1)+bh[i][j]);

      ph[i] +=ah0[i];
    }

  *hes=ph[0]+(ph[1]-ph[0])*(x-x1)/dh;

  return true;
} /* eschar */
