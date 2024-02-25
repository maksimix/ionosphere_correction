#include <math.h>

void rerth (double f, double t, double m, double alfa, double eps,
	    double sig,double *d, double *mo, double *psi)
/***************************************************************/
/*                Входные параметры                            */
/*                                                             */
/*   f    -  рабочая частота,(Мгц)                             */
/*   t    -  угол прихода(вылета) падающей волны               */
/*   m    -  отношение осей эллипса поляризации падающей       */
/*						   волны       */
/*   alfa -  угол наклона большой оси эллипса поляризации      */
/*           падающей волны к плоскости распространения,(рад)  */
/*   eps  -  диэлектрическая проницаемость почвы               */
/*   sig  -  удельная проводимость почвы,(Сим/м)               */
/*                                                             */
/*                Выходные параметры                           */
/*                                                             */
/*   d    -  потери при отражении от земли,(дб)                */
/*   mo   -  отношение осей эллипса поляризации отражённой     */
/*						     волны     */
/*   psi  -  угол наклона большой оси эллипса поляризации      */
/*           падающей волны к плоскости распространения,(рад)  */
/***************************************************************/
 {
  double mv,mg,mvsq,mgsq,ca,sa,rgr,rgi,rvr,rvi,rlg,img,
	bvr,bvi,bgr,bgi,gam,cg,sg,al,al1,tp,root,sgg;
  double pi=3.1415926534;
  extern void fm(double f,   double t,   double eps, double sig,
		 double *rgr,double *rgi,double *rvr,double *rvi);
   fm(f,t,eps,sig,&rgr,&rgi,&rvr,&rvi);
   ca=cos(alfa);
   sa=sin(alfa);
   bvr=rvr*ca-rvi*m*sa;
   bvi=rvi*ca+rvr*m*sa;
   bgr=rgr*sa+rgi*m*ca;
   bgi=rgi*sa-rgr*m*ca;
   mvsq=bvr*bvr+bvi*bvi;
   mgsq=bgr*bgr+bgi*bgi;
   mv=sqrt(mvsq);
   mg=sqrt(mgsq);
   if (mgsq+mvsq == 0.)
       {*d=1e12;
	*mo=0.;
	*psi=0.;
	return;
       }
   *d=-10.*log10((mvsq+mgsq)/(1.+m*m));
   rlg=bvr*bgr+bvi*bgi;
   img=bvi*bgr-bvr*bgi;
   if (img == 0. && rlg == 0.)
	    gam=0.;
     else
	    gam=atan2(img,rlg);
   cg=cos(gam);
   sg=sin(gam);
   if (cg == 0.)
	    sgg=0.;
     else
	    sgg=(cg > 0.) ? 1. : -1.;
   if (fabs(mgsq-mvsq)/(mgsq+mvsq) < 1e-6)
	al=(fabs(cg) > 1e-6) ? pi/4.*sgg : pi/2.;
     else
       {al1=0.5*atan(2.*mv*mg*cg/(mgsq-mvsq));
	if (mgsq > mvsq)
		al=al1;
	  else
		al=(fabs(cg) < 1e-6) ? pi/2. : al1+sgg*pi/2.;
       }
   tp=1.+mgsq/mvsq;
   root=sqrt(fabs(tp*tp-(2.*sg*mg/mv)*(2.*sg*mg/mv)));
   *mo=sqrt(fabs((tp-root)/(tp+root)));
   if (al == 0.)
	    *psi=pi/2.;
     else
	    *psi=(al < 0.) ? -al-pi/2. : -al+pi/2.;
   *mo=(gam<0.) ? -(*mo) : *mo;
   return;
 }
