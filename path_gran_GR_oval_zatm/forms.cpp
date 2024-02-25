#include <math.h>
#include "paths.h"

int progon(double *x, double *a, double *b, double *c, double *d,
	   int    n,
	   double eps);


int form(double *x,
	 double *f,
	 int    n,
	 double grana,
	 double granb,
	 int    key)
/********************************************************************/
/*                                                                  */
/*  ������������ ������������� ��� ������������ ������� ���������   */
/*  ������� ���������, ������� ������� ������������ �������������   */
/*  ������� ���������� �������� ��� ��������� ��������� ��������.   */
/*                                                                  */
/* x	-�������� ���������;                                        */
/* f	-�������� �������;                                          */
/* n	-���������� �����;                                          */
/* grana	-������� �� ����� �������;                          */
/* granb	-������� �� ������ �������;                         */
/* key	-��� ��������� �������:                                     */
/*	 1 - ������ ������ �����������;                             */
/*	 2 - ������ ������ �����������;                             */
/*	 3 - ����� ������, ������ ������ �����������;               */
/*	 4 - ����� ������, ������ ������ �����������;               */
/*   ������� ����������: 1, ���� ������������� ����������,          */
/*                       0 - ��� �������� �������������.            */
/*                                                                  */
/*VGG                                                               */
/********************************************************************/
{
  double alamd,amy,a[200],b[200],c[200],d[200];

  int i,im;

  nm=n-1;

  for(i=0; i<n; i++)
    {
      if (i<nm) dx[i]=x[i+1]-x[i];
      ff[i]=f[i];
      xx[i]=x[i];
    }

  for(i=1; i<nm; i++)
    {
      im=i-1;
      alamd=dx[i]/(dx[i]+dx[im]);
      amy=1.-alamd;
      a[i]=alamd;
      b[i]=-2.*(alamd+amy);
      c[i]=amy;
      d[i]=3.*(alamd*(f[i]-f[im])/dx[im]+amy*(f[i+1]-f[i])/dx[i]);
    }

  switch (key)
    {
      case 1: alamd=.0;
	      amy=.0;
	      d[0]=2.*grana;
	      d[nm]=2.*granb;
	      break;

      case 2: alamd=1.;
	      amy=1.;
	      d[0]=3.*(f[1]-f[0])/dx[0]-.5*dx[0]*grana;
	      d[nm]=3.*(f[nm]-f[nm-1])/dx[nm-1]-.5*dx[nm-1]*granb;
	      break;

      case 3: alamd=.0;
	      amy=1;
	      d[0]=2.*grana;
	      d[nm]=3.*(f[nm]-f[nm-1])/dx[nm-1]+.5*dx[nm-1]*granb;
	      break;

      case 4: alamd=1.;
	      amy=.0;
	      d[0]=3.*(f[1]-f[0])/dx[0]-.5*dx[0]*grana;
	      d[nm]=2.*granb;
    }

  a[0]=.0;
  b[0]=-2.;
  c[0]=alamd;
  a[nm]=amy;
  b[nm]=-2.;
  c[nm]=.0;

  if (progon(df,a,b,c,d,n,.1e-14)) return 1;

  return 0;

} /* form */
