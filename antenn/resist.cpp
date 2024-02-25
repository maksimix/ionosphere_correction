#include <math.h>

void  resist (double f, double la, double hk, double psi,
	      double eps,double sig,double *ra, double *rr)
/***********************************************************/
/*                  Входные параметры                      */
/*                                                         */
/*   f    -  рабочая частота,(Мгц)                         */
/*   la   -  длина антенны,(м)                             */
/*   hk   -  высота подвеса конца антенны,(м)              */
/*   psi  -  угол наклона  луча антенны к горизонтальной   */
/*                                       плоскости,(рад)   */
/*   eps  -  относительная диэлектрическая проницаемость   */
/*                                                 почвы   */
/*   sig  -  удельная проводимость почвы,(Сим/м)           */
/*                                                         */
/*                  Выходные параметры                     */
/*                                                         */
/*   ra   -  вспомогательная величина для расчёта КНД      */
/*   rr   -  вспомогательная величина для расчёта КУ       */
/***********************************************************/
 {
  double pi=3.1415926534;
  double k,sp,cp,t,x,sx,cx,z,aiv,aig,skl2,ckl2,ckl,r1,r2,r12,akl2,rr1,ra1;
   sp=sin(psi);
   cp=cos(psi);
   k=pi*f/1.5e2;
   t=1.8e4*sig/(f*eps);
   x=2.*k*(hk+la*sp/2.);
   sx=sin(x);
   cx=cos(x);
   z=1.5*(1.+2./(x*x))*cos(0.5*atan(t))/(sqrt(eps*sqrt(1.+t*t)));
   aiv=(sx/x-cx)*3./(x*x);
   aig=-1.5*((1./x-1./(x*x*x))*sx+cx/(x*x));
   akl2=k*la/2.;
   skl2=sin(akl2);
   ckl2=cos(akl2);
   ckl=cos(2.*akl2);
   r1=20.*(1.-ckl2)*(1.-ckl2);
   r2=20.*(ckl2-ckl)*(ckl2-ckl);
   r12=60.*(skl2/akl2-ckl2)*(1.-ckl2)*(ckl2-ckl)/(akl2*akl2);
   rr1=1.+aiv*sp*sp+aig*cp*cp;
   ra1=(r1+r2+2.*r12)*(rr1+z);
   *rr=ra1*rr1/(rr1+z);
   *ra=ra1;
   return;
  }
