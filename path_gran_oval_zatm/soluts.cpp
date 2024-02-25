#include <stdio.h>
#include <math.h>
#include "paths.h"

const  int maxKolOtr=5;

int funcs(double x,
	  double *y, double *f,
	  int    n);

void ltv(double *x,
	 double *y0, double *y1, double *f0, double *f1,
	 double *h,
	 int    n,
	 double e, double eps,
	 FUNC   func);

#define SIGN(x,y) ((y>0)? fabs(x) : -fabs(x))


int soluts(double *x,
	   double *y0,
	   int    n,
	   double delt,
	   double e,
	   double eps,
	   double ep,
	   double ep1)
/*****************************************************************/
/*       æõîëãéñ ïóõýåóô÷ìñåô õðòá÷ìåîéå éîôåçòéòï÷áîéåí         */
/*       äéæ. õòá÷îåîéê	ìõþá.                                    */
/*	 ëáöäùê	ûáç éîôåçòéòï÷áîéñ ïóõûåóô÷ìñåôóñ ðïóòåäóô÷ïí    */
/*	 ðòïãåäõòù ltv.                                          */
/*	 ðïäðòïçòáííá õþéôù÷áåô	÷ïúíïöîùå ïóïâùå ôïþëé õòá÷îåîéê.*/
/*       æõîëãéñ ÷ïú÷òáýáåô: 0, åóìé ôòáåëôïòéñ ðïóôòïåîá é      */
/*                           1, åóìé îåô ïôòáöåîéñ.              */
/*                                                               */
/*VGG                                                            */
/*****************************************************************/
{
  double f0[22],y1[22],f1[22],
	 r=0;
  int kolOtr=0;
  int i,nost;

  nost=1;

  if (funcs(*x,y0,f0,n)) return 1;


  if (keytr>0)
    {
      printf("\n%12.5e",*x);
      for(i=0; i<n; i++)
	{
	  if (i%3==0) printf("\n");
	  printf("%12.5e %12.5e ",y0[i],f0[i]);
	}
    }

 while((y0[2]-rH0>eps || f0[2]>.0) && kolOtr<maxKolOtr)
 //while(f0[2]>.0 || fabs(y1[2]*100.-6370.-180.)>.1)
 {
      //if (.01*dist(fi0,teta0,y1[0],y1[1])>rmax)
      //    return -1;

      ltv(x,y0,y1,f0,f1,&delt,n,e,eps,funcs);

      if (dist(fi0,teta0,y1[0],y1[1])>RMax)
          return -1;

      if (keytr>0)
      {
	  if (n>8)
	    {
	      r=f1[3]*(y1[9]*y1[16]-y1[15]*y1[10])-
		f1[4]*(y1[8]*y1[16]-y1[14]*y1[10])+
		f1[5]*(y1[8]*y1[15]-y1[14]*y1[9]);

		r=r*y1[2]*y1[2]*sin(y1[1]);

		r=10.*log10(fabs(r)*10000.);
	    }

          printf("\nx=%12.5e",*x);
          /*
          for(i=0; i<n; i++)
	  {
	      if (i%3==0) printf("\n");
	      printf("%12.5e %12.5e ",y1[i],f1[i]);
          }
          */
          printf(" h=%12.5e %12.5e %d dist=%12.5e",y1[2]*100.-6370.,f1[2],kolOtr,dist(fi0,teta0,y1[0],y1[1]));
	  printf("\ndelt=%12.5e %12.5e %12.5e %12.5e %12.5e %12.5e",delt,v,sa2,r,e,eps);
      }
      if (keytr<0 && pointTr<MaxPointTr-1)
      {
          hTr[pointTr]=100.*(y1[2]-R0);
          sTr[pointTr]=dist(fi0,teta0,y1[0],y1[1]);
          pointTr++;
      }


      if (hm-y1[2]<eps || delt<.1e-13) return 1;

      if ((iox==0 && ov>ep) || (iox==1 && ov-u1>ep))
	nost=1;
      else
	if(nost)
	  {
	    nost=0;

	    if (iox==0 && sa2<ep1 && sa2>.1e-12)
	      {
		y1[3]=2.*ak*SIGN(h[0],y1[3])-y1[3];
		y1[4]=2.*ak*SIGN(h[1],y1[4])-y1[4];
		y1[5]=2.*ak*SIGN(h[2],y1[5])-y1[5];
	      }
	    else
	      {
		y1[3]=-y1[3];
		y1[4]=-y1[4];
		y1[5]=-y1[5];
	      }

	    if (n>8)
	      {
		if (funcs(*x,y1,f1,6)) return 1;

		y1[10]=(anorm*(y1[2]*(st*f1[0]*y1[11]+f1[1]*y1[12])+
			f1[2]*y1[13])-dmrtf[0]*y1[8]-dmrtf[1]*y1[9])
			/dmrtf[2];
		y1[16]=(anorm*(y1[2]*(st*f1[0]*y1[17]+f1[1]*y1[18])+
			f1[2]*y1[19])-dmrtf[0]*y1[14]-dmrtf[1]*y1[15])
			/dmrtf[2];

		funcs(*x,y1,f1,n);
	      }
	  }


      if (f0[2]*f1[2]<.0)
	{
	  fot=y1[0];
	  tot=y1[1];
          rot=y1[2];
          kolOtr++;
	}

      for(i=0; i<n; i++)
	{
	  y0[i]=y1[i];
	  f0[i]=f1[i];
	}

  }

  if (kolOtr>=maxKolOtr)
      return -1;

  return 0;

} /* solutp */

