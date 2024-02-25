#include <math.h>
#include <stdio.h>

void ellips (double f, double delta, double eps, double sig,
	     double la, double hk, double psi, double fi,
	     double *m, double *alfa, double *g)
/***************************************************************/
/*                   ������� ���������                         */
/*                                                             */
/*   f     -  ������� �������,(���)                            */
/*   delta -  ���� ������,(���)                                */
/*   eps   -  ������������� ��������������� �������������      */
/*                                                  �����      */
/*   sig   -  �������� ������������ �����,(���/�)              */
/*   la    -  ����� ���� �������,(�)                           */
/*   hk    -  ������ ������� ����� ������� ������� ���         */
/*                                             ���̣�,(�)      */
/*   psi   -  ���� ������� ���� � ��������������               */
/*                                        ���������,(���)      */
/*   fi    -  ������������ ����,(���)                          */
/*                                                             */
/*                   �������� ���������                        */
/*                                                             */
/*   m     -  ��������� ���� ������� �����������               */
/*                                        ���������� �����     */
/*   alfa  -  ���� ������� ������� ��� ������� �����������     */
/*                       � ��������� ���������������,(���)     */
/*   g     -  ����������� �������� �������,(���)               */
/***************************************************************/
 {
  double mv,mg,mvsq,mgsq,m1,cgm,sgm,al,al1,tp,root,gam,r,rr;
  double pi=3.1415926534;
  extern void beam(double f,double la, double hk,double psi,double eps,double sig,
		   double fi,double delta,double *mt,double *mf,double *gam);
  extern void resist(double f,double la,double hk,double psi,double eps,double sig,
		     double *ra,double *rr);
    beam(f,la,hk,psi,eps,sig,fi,delta,&mv,&mg,&gam);
    if (mv == 0. && mg == 0.)
	{*g=0.;
	 *m=0.;
	 *alfa=0.;
	 return;
	}
    cgm=cos(gam);
    sgm=sin(gam);
    mgsq=mg*mg;
    mvsq=mv*mv;
    if (mvsq == mgsq)
       al=(cgm < 0.) ? -pi/4. : pi/4.;
     else
       {al1=atan(2.*mv*mg*cgm/(mgsq-mvsq))/2.;
	if (mgsq > mvsq)
	   al=al1;
	 else
	   al=(cgm < 0.) ? al1-pi/2. : al1+pi/2.;
       }
    if (mvsq == 0.)
	m1=0.;
     else
	{tp=1.+mgsq/mvsq;
	 root=sqrt(fabs(tp*tp-(2.*sgm*mg/mv)*(2.*sgm*mg/mv)));
	 m1=sqrt(fabs((tp-root)/(tp+root)));
	}
    if (fabs(al) < 1e-6)
       *alfa=pi/2.;
     else
       *alfa=(al < 0.) ? -al-pi/2. : -al+pi/2.;
    resist(f,la,hk,psi,eps,sig,&r,&rr);
    *g=4.*(mgsq+mvsq)*pi*pi*f*f/(3e3*r);
    *m=(gam < 0.) ? -m1 : m1;
    return;
 }
