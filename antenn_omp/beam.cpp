#include <math.h>

void  beam (double f, double la, double hk, double psi, double eps,
	    double sig, double fi, double delta, double *mt, double *mf,
	    double *gam)
/******************************************************************/
/*                   Входные параметры                            */
/*                                                                */
/*   f     -  рабочая частота,(Мгц)                               */
/*   la    -  длина луча антенны,(м)                              */
/*   hk    -  высота  подвеса  точки  питания  антенны над        */
/*                                               землёй,(м)       */
/*   psi   -  угол наклона луча к горизонтальной плоскости,(рад)  */
/*   eps   -  относительная  диэлектрическая  проницаемость       */
/*                                                    почвы       */
/*   sig   -  удельная проводимость почвы,(Сим/м)                 */
/*   fi    -  азимутальный угол,(рад)                             */
/*   delta -  угол места,(рад)                                    */
/*                                                                */
/*                   Выходные параметры                           */
/*                                                                */
/*   mt    -  вертикальная компонента действующей длины,(м)       */
/*   mf    -  горизонтальная компонента действующей длины,(м)     */
/*   gam   -  фазовый угол между компонентами,(рад)               */
/******************************************************************/
{
 double k,cp,sp,cfi,sfi,sd,cd,ca1,cb,cg,ca,akl,arg1,arg2,arg3,arg4,
       rvr,rvi,rgr,rgi,faza,skl2,ckl2,r1,r2,r3,r4,sfz,cfz,rver,rvei,
       rger,rgei,htr,hti,hfr,hfi,gmi,gmr;
 double pi=3.1415926534;
 extern void fm(double f,double t,double eps,double sig,
		double *rgr,double *rgi,double *rvr,double *rvi);
   cp=cos(psi);
   sp=sin(psi);
   cfi=cos(fi);
   sfi=sin(fi);
   sd=sin(delta);
   cd=cos(delta);
   ca1=cp*cd*cfi+sp*sd;
   cb=-cp*sd*cfi+sp*cd;
   cg=cp*sd*cfi+sp*cd;
   ca=cp*sfi;
   k=pi*f/1.5e2;
   akl=k*la;
   arg1=(1.+ca1)*akl/2.;
   arg2=(1.-ca1)*akl/2.;
   arg3=(1.+ca1-2.*sp*sd)*akl/2.;
   arg4=(1.-ca1+2.*sp*sd)*akl/2.;
   fm(f,delta,eps,sig,&rgr,&rgi,&rvr,&rvi);
   faza=2.*k*(hk+0.5*la*sp)*sd;
   skl2=sin(akl/2.);
   ckl2=cos(akl/2.);
   r1=(fabs(arg1) < 1e-4) ? la/2. : sin(arg1)*la/(2.*arg1);
   r2=(fabs(arg2) < 1e-4) ? la/2. : sin(arg2)*la/(2.*arg2);
   r3=(fabs(arg3) < 1e-4) ? la/2. : sin(arg3)*la/(2.*arg3);
   r4=(fabs(arg4) < 1e-4) ? la/2. : sin(arg4)*la/(2.*arg4);
   cfz=cos(faza);
   sfz=sin(faza);
   rver=rvr*cfz+rvi*sfz;
   rvei=rvi*cfz-rvr*sfz;
   rger=rgr*cfz+rgi*sfz;
   rgei=rgi*cfz-rgr*sfz;
   htr=skl2*cb*(r1+r2)+skl2*cg*rver*(r3+r4)+ckl2*cg*rvei*(r4-r3);
   hti=ckl2*cb*(r1-r2)+skl2*cg*rvei*(r3+r4)+ckl2*cg*rver*(r3-r4);
   hfr=skl2*ca*(r1+r2)+skl2*ca*rger*(r3+r4)+ckl2*ca*rgei*(r4-r3);
   hfi=ckl2*ca*(r1-r2)+skl2*ca*rgei*(r3+r4)+ckl2*ca*rger*(r3-r4);
   *mt=sqrt(htr*htr+hti*hti);
   *mf=sqrt(hfr*hfr+hfi*hfi);
   gmr=-htr*hfr-hti*hfi;
   gmi=htr*hfi-hti*hfr;
   if (gmi == 0. && gmr == 0.)
       *gam=0.;
    else
       *gam=atan2(gmi,gmr);
   return;
 }
