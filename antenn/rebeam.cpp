#include <math.h>
#include <stdio.h>

void  rebeam (double f,double t, double m, double alfa,
              double eps, double sig, double la, double h,
              double psi, double fi, double *d)
/***************************************************************/
/*                     Входные параметры                       */
/*                                                             */
/*   f     -  рабочая частота,(Мгц)                            */
/*   t     -  угол прихода,(рад)                               */
/*   m     -  отношение осей эллипса поляризации падающей      */
/*                                                   волны     */
/*   alfa  -  угол наклона большой оси эллипса поляризации     */
/*                       к плоскости распространения,(рад)     */
/*   eps   -  относительная диэлектрическая  проницаемость     */
/*                              почвы                          */
/*   sig   -  удельная проводимость почвы,(Сим/м)              */
/*   la    -  длина луча антенны,(м)                           */
/*   h     -  высота подвеса точки питания антенны над         */
/*                               землёй,(м)                    */
/*   psi   -  угол наклона луча к горизонтальной               */
/*                                         плоскости,(рад)     */
/*   fi    -  азимутальный угол,(рад)                          */
/*                                                             */
/*                     Выходной параметр                       */
/*                                                             */
/*   d     -  КНД антенны с учетом поляризационного            */
/*                                   рассогласования,(раз)     */
/***************************************************************/
{
 double beta,sb,cb,sgnm,gam1,gam,gam2,e1,e2,s,l,lsq,e,esq,mv,mg,ra,rr,rab;
 double pi=3.1415926534;
 extern void beam(double f,double la,double h, double psi,double eps,
                  double sig,double fi, double t,double *mv,double *mg,double *gam);
 extern void resist(double f,double la,double h,double psi,double eps,double sig,
                    double *ra,double *rr);
   if (alfa == 0.)
      beta=pi/2.;
    else
      beta=(alfa < 0.) ? alfa+pi/2. : alfa-pi/2.;
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
        rab=fabs(m)/sqrt(m*m+(0.5*(1.-m*m)*sin(2.*beta))*(0.5*(1.-m*m)
            *sin(2.*beta)));
        if (rab>1.)
          rab=1.;
        else
          if (rab<-1.)
            rab=-1.;
        gam1=asin(rab);
        gam=(beta > 0.) ? -sgnm*gam1 : sgnm*(gam1-pi);
       }
   beam(f,la,h,psi,eps,sig,fi,t,&mv,&mg,&gam2);
   if (mg == 0. && mv == 0.)
       {*d=0.;
        return;
       }
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
   resist(f,la,h,psi,eps,sig,&ra,&rr);
   *d=4.*(mv*mv+mg*mg)*pi*pi*f*f*s/(3e3*rr);
   return;
 }
