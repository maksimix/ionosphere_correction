#include <math.h>

void dipole (double f, double t, double eps, double sig, double la, double h,
	     double cf, double sf, double *mv ,double *mg, double *gam)
/**************************************************************/
/*              Входные параметры                             */
/*   f    -  рабочая частота,(Мгц)                            */
/*   t    -  угол вылета,(рад)                                */
/*   eps  -  диэлектрическая проницаемость почвы              */
/*   sig  -  удельная проводимость почвы,(Сим/м)              */
/*   la   -  длина одного плеча диполя,(м)                    */
/*   h    -  высота подвеса диполя над землёй,(м)             */
/*   cf   -  косинус азимутального угла                       */
/*   sf   -  синус   азимутального угла                       */
/*                                                            */
/*              Выходные параметры                            */
/*                                                            */
/*   mv   -  вертикальная  компонента  интерференционного     */
/*                                              множителя     */
/*   mg   -  горизонтальная компонента интерференционного     */
/*                                              множителя     */
/*   gam  -  фазовый угол между компонентами                  */
/*	               интерференционного  множителя,(рад)    */
/**************************************************************/
 {
  double ct,st,df,akl,faza,tp,cp,sp,ci,si,td,sd,cd,
	bvr,bvi,bgr,bgi,rgr,rgi,rvr,rvi,cfz,sfz;
  double pi=3.1415926534;
  extern void fm(double f,   double t,   double eps, double sig,
		 double *rgr,double *rgi,double *rvr,double *rvi);
   ct=cos(t);
   st=sin(t);
   fm(f,t,eps,sig,&rgr,&rgi,&rvr,&rvi);
   akl=pi*la*f/1.5e2;
   faza=pi*h*f/1.5e2;
   if (fabs(ct) < 1e-6 || fabs(cf) < 1e-6)
      {cp=0.;
       sp=1.;
      }
    else
      {tp=st/(ct*cf);
       cp=1./sqrt(1.+tp*tp);
       sp=tp*cp;
      }
   ci=sf*sp;
   si=sqrt(fabs((1.+ci)*(1.-ci)));
   if (fabs(cf) < 1e-6)
       td = (fabs(st) < 1e-6) ? 1e12 : ct/st;
    else
       td = sf*cp/cf;
   cd=1./sqrt(1.+td*td);
   sd=td*cd;
   if (cos(akl) == 1.)
       df=1.;
     else
       df=(cos(akl*sd)-cos(akl))/(cd*(1.-cos(akl)));
   cfz=cos(2.*st*faza);
   sfz=sin(2.*st*faza);
   bvr=df*ci*(-1.+rvr*cfz+rvi*sfz);
   bvi=df*ci*(rvi*cfz-rvr*sfz);
   bgr=df*si*(1.+rgr*cfz+rgi*sfz);
   bgi=df*si*(rgi*cfz-rgr*sfz);
   *mv=sqrt(bvr*bvr+bvi*bvi);
   *mg=sqrt(bgr*bgr+bgi*bgi);
   cfz=bvi*bgr-bvr*bgi;
   sfz=bvr*bgr+bvi*bgi;
   if (sfz == 0. && cfz == 0.)
       *gam=0.;
     else
       *gam=atan2(cfz,sfz);
   return;
 }
