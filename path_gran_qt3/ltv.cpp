#include <math.h>
#include <float.h>
#include <stdio.h>

typedef int (*FUNC) (double x,
                     double *y, double *f,
                     int    n);
/*
void ltv(double *x,
         double y0[],
         double y1[],
         double f0[],
         double f1[],
         double *h,
         int    n,
         double e,
         double eps,
         FUNC func)
*/
void ltv(double *x,
         double *y0,
         double *y1,
         double *f0,
         double *f1,
         double *h,
         int    n,
         double e,
         double eps,
         FUNC func)
/*******************************************************************/
/*     ������� ������������ ���� ��� �������������� �������        */
/*     n ���. ��������� ������� ������� ������� ���������� ������� */
/*     ����� ����������������� ���������� �������� ����������.     */
/*                                                                 */
/* x    -����������� ����������;                                   */
/* y0,f0 -��������� �������� ������� � �����������;                */
/* y1,f1 -�������� ��������;                                       */
/* n    -����� ���������;                                          */
/* h    -��� ��������������, �� �� ����������� ���������� ��       */
/*       ���������� e � eps, ��� ��� ��������� ������ ����������   */
/*       ������ e � ������ eps;                                    */
/* func -��������� �� �������, ����������� �����������.            */
/*                                                                 */
/*VGG                                                              */
/*******************************************************************/
{
  double y2[22],f2[22],r,x0;
  int    i,let;


      let=1;
      r=DBL_MAX;

      while(r>eps && *h>.0)
      {
          //printf("\n1  y[2]=%f f[2]=%f",y0[2],f0[2]);
          for(i=0; i<n; i++)
            y2[i]=y0[i]+*h*f0[i]/3.;
          x0=*x+*h/3.;

          if ((*func)(x0,y2,f2,n))
          {
              //printf("\n2  y[2]=%f f[2]=%f",y2[2],f2[2]);
              *h *=.5;
              let=0;
              continue;
          }
          //printf("\n2  y[2]=%f f[2]=%f",y2[2],f2[2]);

          for(i=0; i<n; i++)
            y2[i]=y0[i]+*h*(f0[i]+f2[i])/6.;

          if ((*func)(x0,y2,f2,n))
          {
              //printf("\n3  y[2]=%f f[2]=%f",y2[2],f2[2]);
              *h *=.5;
              let=0;
              continue;
          }
          //printf("\n3  y[2]=%f f[2]=%f",y2[2],f2[2]);

          for(i=0; i<n; i++)
            y2[i]=y0[i]+*h*(f0[i]+3.*f2[i])/8.;
          x0=*x+*h*.5;

          if ((*func)(x0,y2,f1,n))
          {
              *h *=.5;
              let=0;
              continue;
          }

          for(i=0; i<n; i++)
            y2[i]=y0[i]+*h*(f0[i]-3.*f2[i]+4.*f1[i])*.5;
          x0=*x+*h;

          if ((*func)(x0,y2,f2,n))
          {
              *h *=.5;
              let=0;
              continue;
          }

          r=.0;
          for(i=0; i<n; i++)
          {
              y1[i]=y0[i]+*h*(f0[i]+4.*f1[i]+f2[i])/6.;
              r=(r>fabs(y1[i]-y2[i]))? r : fabs(y1[i]-y2[i]);
          }

          if (r>eps || (*func)(x0,y1,f1,n))
          {
              *h *=.5;
              let=0;
              continue;
          }
      }


  if (r<e && let) *h *=2.;
  *x=x0;

  return;

} /* ltv */