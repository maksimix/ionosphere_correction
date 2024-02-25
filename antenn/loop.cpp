#include <math.h>

void loop(double f, double t, double m, double alfa,
	  double eps, double sig, double h, double *d)
/**************************************************************/
/*                    ������� ���������                       */
/*                                                            */
/* f     - ������� �������;                                   */
/* t     - ���� ������� (���);                                */
/* m     - ��������� ���� ������� ����������� ��������        */
/*         ����� �� ������;                                   */
/* alfa  - ���� ������� ������� ��� ������� �����������       */
/*         � ��������� ��������������� ���. ����� (���);      */
/* eps   - ���������������� ������������� �����;              */
/* sig   - �������� ������������ ����� (���/�);               */
/* h     - ������� ������� ����� ��� ������ (�0.              */
/*                                                            */
/*                    �������� ��������                       */
/*                                                            */
/* d     - ����������������� ��������� ��� �����.             */
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