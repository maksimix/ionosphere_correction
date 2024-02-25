#include <math.h>

double  ci (double x)
/*  Интегральный  косинус */
{
 double d=2.0,t=3.0,e=1.0,eps=9.99e-6;
 double y,z,z0,z1,z2,z3,z4,z5,z6,z7,z8,z9;
   if (x-14.0 > 0.)  goto  M1272;
   else              goto  M1256;
M1256:
   if (x==0.)  goto  M1295;
	z1=-0.25*x*x;
	z3=0.577216+log(x)+z1;
	z=z1;
	z0=d;
M1260:  z4=(d*z0-d)/(d*z0-e)/(d*d*z0*z0);
	z2=-z4*z1*x*x;
	z1=z2;
	z3+=z2;
	z=z2;
   if (fabs(z)-eps > 0.)  goto  M3260;
   else                   goto  M1268;
M3260:  z0+=1.;
	goto  M1260;
M1268:  y=z3;
	goto  M1298;
M1272:  z1=e;
	z3=e;
	z=e;
	z0=d;
M1276:  z4=(d*z0-d)*(d*z0-t);
	z2=-z4*z1/(x*x);
	z1=z2;
	z3+=z2;
	z=z2;
   if (fabs(z)-eps > 0.)  goto M3276;
   else                   goto M1282;
M3276:  z0+=e;
	goto  M1276;
M1282:  z7=1./x;
	z5=z7;
	z6=z7;
	z0=d;
M1286:  z9=(d*z0-e)*(d*z0-d);
	z8=-z9*z7/(x*x);
	z7=z8;
	z5+=z8;
	z6=z8;
   if (fabs(z6)-eps > 0.)  goto  M3286;
   else                    goto  M1294;
M3286:  z0+=e;
	goto  M1286;
M1294:  y=sin(x)*z3/x-cos(x)*z5/x;
	goto  M1298;
M1295:  y=-9.9e12;
M1298:  return (y);
}
