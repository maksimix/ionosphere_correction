#include "paths.h"

static double pares(double& f, double& teta, double& fh,
                     long&    k,
                     double& fo, double& fb);

static double res(double& f, double& teta, double& fh,
                   long&    k,
                   double& fo, double& fb);

static double des(double& f, double& teta, double& fh,
                   long&    k,
                   double& fo, double& fb);

static double ros(double& fo, double& fb);

void abs_es(double fr,
            long ox,
            long hop,
            long n,
            double *l_es)
/*****************************************************************/
/*                                                               */
/* Функция вычисляет потери при прохождении Es-слоя или          */
/* при отражении от него.                                        */
/*                                                               */
/* fr     - рабочая частота;                                     */
/* ox     - тип магнитоионной компоненты;                        */
/* hop    - количество скачков на траектории;                    */
/* n      - количество корней;                                   */
/* l_es[] - потери в Es.                                         */
/*                                                               */
/*VGG                                                            */
/*****************************************************************/
{
  double s,d0,sd0,cd0;
  static SR2 er(4,0,0);
  static SR1 mr(3);
  long    i,j,k,key=0;

  for(i=0; i<n; i++)
    {
      *(l_es+i)=.0;
      for(j=0; j<hop; j++)
        for(k=0; k<2; k++)
          {
            s=suchk[i][j][k];

            SP2::spcub2_n(s,t,key,*es,er);
            SP1::spcub_n(s,*mag,mr);

            cd0=cos(dhopk[i][j][k]);
            sd0=R0*cd0/refk[i][j];
            sd0=sqrt(1.-sd0*sd0);
            if (sd0>1.)
              sd0=1.;
            d0=asin(sd0);

            if (k==0 && s==suchk[i][j][1])
              {
                *(l_es+i) -=res(fr,d0,*mr.fun,ox,
                                *er.fun,*(er.fun+1));
                break;
              }
            else
              if (refk[i][j]>*(er.fun+2))
                *(l_es+i) -=des(fr,d0,*mr.fun,ox,
                                *er.fun,*(er.fun+1));
          }
    }

  return;
} /* abs_es */

static  double res(double& f,      /* частота                  */
                   double& teta,   /* угол вылета              */
                   double& fh,     /* гирочастота              */
                   long&    k,      /* магнитоионная компонента */
                   double& fo,     /* f0Es                     */
                   double& fb)     /* fbEs                     */
/**************************************************************/
/*    Функция вычисляет потери при отражении от Es-слоя.      */
/**************************************************************/
{
  return 20.*log10(1./(1.+pares(f,teta,fh,k,fo,fb)));
}

static  double des(double& f,      /* частота                  */
                   double& teta,   /* угол вылета              */
                   double& fh,     /* гирочастота              */
                   long&    k,      /* магнитоионная компонента */
                   double& fo,     /* f0Es                     */
                   double& fb)     /* fbEs                     */
/**************************************************************/
/*    Функция вычисляет потери при прохождениии Es-слоя.      */
/**************************************************************/
{
  double x;

  x=1./(1.+pares(f,teta,fh,k,fo,fb));
  return 10.*log10(1.-x*x);
}


static  double pares(double& f,      /* частота                  */
                     double& teta,   /* угол вылета              */
                     double& fh,     /* гирочастота              */
                     long&    k,      /* магнитоионная компонента */
                     double& fo,     /* f0Es                     */
                     double& fb)     /* fbEs                     */
/****************************************************************/
{
  double al,pok,prov;

  pok=ros(fo,fb);
  prov=fo/sin(teta)+.5*((k)? fh : -fh);

  if (prov<.1e-30) return .1e31;

  al=log10(f/prov);

  if (29./pok<al) return .1e31;
  if (-4./pok>al) return .1e-2;
  pok*=log(f/prov);
  if (pok<MIN_EXP)
    return .0;
  else
    return 10.*exp(pok);
}

static double ros(double& fo,
                  double& fb)
{
  double ra2;

  ra2=log10(fo/fb);

  if (ra2<0.041) return 50.6585365853;

  return 2.077/ra2;
}