#include <math.h>

void  recant (double f, double t, double m, double alfa, double eps,
              double sig, double la, double h, double fi, double *d)
/****************************************************************/
/*                Входные параметры                             */
/*                                                              */
/*   f    -  рабочая частота,(Мгц)                              */
/*   t    -  угол прихода,(рад)                                 */
/*   m    -  отношение осей эллипса поляризации пришедшей       */
/*                                       волны (со знаком)      */
/*   alfa -  угол наклона большой оси эллипса поляризации       */
/*           пришедшей волны к плоскости распространения,(рад)  */
/*   eps  -  диэлектрическая проницаемость почвы                */
/*   sig  -  удельная проводимость почвы,(Сим/м)                */
/*   la   -  длина одного плеча диполя,(м)                      */
/*   h    -  высота повеса антенны над землёй,(м)               */
/*   fi   -  азимутальный угол,(рад)                            */
/*                                                              */
/*               Выходной параметр                              */
/*                                                              */
/*   d    -  КНД  антенны с учётом поляризационного             */
/*                                        рассогласования       */
/****************************************************************/
{
 long i;
 double ll,dmax,beta,cf,sf,sb,cb,sgnm,gam2,gam,gam1,e1,e2,s,lsq,
       esq,l,e,mv,mg,sga,rab;
 double pi=3.1415926535;
 double a[15]={0.,.1,.2,.3,.4,.5,.57,.6,.625,.66,.68,.7,.725,.75,.785},
       b[15]={1.5,1.55,1.625,1.775,2.075,2.55,3.,3.225,3.3,3.,2.5,2.1,
              1.5,1.,.5};
 extern void dipole(double f,double t,double eps,double sig,
                    double la,double h,double cf,double sf,
                    double *mv,double *mg,double *gam);
  cf=cos(fi);
  sf=sin(fi);
  ll=la*f/300.;
  if (ll < a[0] || ll > a[14])
     {*d=0.;
      return;
     }
   else
     for (i=0; i<14; i++)
       {if (ll >= a[i] && ll <= a[i+1])
           {dmax=b[i]+(ll-a[i])*(b[i+1]-b[i])/(a[i+1]-a[i]);
            break;
           }
       }
  if (alfa == 0.)
      sga=0.;
    else
      sga=(alfa > 0.) ? 1. : -1.;
  if (alfa == 0.)
      beta=pi/2.;
    else
      beta=alfa-sga*pi/2.;
  sb=sin(beta);
  cb=cos(beta);
  if (m == 0.)
      sgnm=0.;
    else
      sgnm=(m > 0.) ? 1. : -1.;
  if (m == 0.)
      gam=(beta > 0.) ? 0. : pi;
    else
      {
       rab=fabs(m)/sqrt(m*m+(.5*(1.-m*m)*sin(2.*beta))*
                                  (.5*(1.-m*m)*sin(2.*beta)));
        if (rab>1.)
          rab=1.;
        else
          if (rab<-1.)
            rab=-1.;
       gam1=asin(rab);
       gam=(beta > 0.) ? -sgnm*gam1 : sgnm*(gam1-pi);
      }
  dipole(f,t,eps,sig,la,h,cf,sf,&mv,&mg,&gam2);
  e1=sb*sb+m*m*cb*cb;
  e2=cb*cb+m*m*sb*sb;
  if (e2 != 0. && mg*mg != 0.)
      {l=mv/mg;
       lsq=l*l;
       esq=e1/e2;
       e=sqrt(esq);
       s=fabs((1.+esq*lsq+2.*l*e*cos(gam+gam2))/((1.+lsq)*(1.+esq)));
      }
  else
      {if (mg*mg == 0.)
           s=(e2 == 0.) ? 1. : e1/(e1+e2);
         else
           s=mv*mv/(mv*mv+mg*mg);
      }
  *d=dmax*s*(mv*mv+mg*mg);
  return;
}
