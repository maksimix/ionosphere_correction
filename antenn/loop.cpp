#include <math.h>

void loop(double f, double t, double m, double alfa,
	  double eps, double sig, double h, double *d)
/**************************************************************/
/*                    Входные параметры                       */
/*                                                            */
/* f     - рабочая частота;                                   */
/* t     - угол прихода (рад);                                */
/* m     - отношение осей эллипса поляризации падающей        */
/*         волны со знаком;                                   */
/* alfa  - угол наклона большой оси эллипса поляризации       */
/*         к плоскости распространения пад. волны (рад);      */
/* eps   - диэлектирическая проницаемость почвы;              */
/* sig   - удельная проводимость почвы (Сим/м);               */
/* h     - высотиа подвеса рамки над Землей (м0.              */
/*                                                            */
/*                    Выходной параметр                       */
/*                                                            */
/* d     - интерференционный множитель для рамки.             */
/**************************************************************/
{
  double pi=3.1415926535;
  double faza,bvr,bvi,bvms,beta,cb,sb,rgr,rgi,rvr,rvi,e1,e2;
  extern void fm(double f, double t, double eps,double sig,
		 double *rgr, double *rgi, double *rvr, double *rvi);

  faza=-2.*sin(t)*pi*h*f/1.5e2;
  fm(f,t,eps,sig,&rgr,&rgi,&rvr,&rvi);
  bvr=1.+rvr*cos(faza)-rvi*sin(faza);
  bvi=rvr*sin(faza)+rvi*cos(faza);
  bvms=bvr*bvr+bvi*bvi;
  beta=(alfa>.0) ? alfa-pi/2. : alfa+pi/2.;
  cb=cos(beta);
  sb=sin(beta);
  e1=sb*sb+m*m*cb*cb;
  e2=cb*cb+m*m*sb*sb;
  *d=bvms*e1/(e1+e2);
  return;
}