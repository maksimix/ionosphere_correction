#include <math.h>

double si (double x)
/*  Интегральный  синус  */
{
 double d=2.0,t=3.0,e=1.0,eps=9.99e-6,pi2=1.570796;
 double y,z,z0,z1,z2,z3,z4,z5,z6,z7,z8,z9;
   if (x-14.0 > 0.) goto M1222;
   else             goto M1206;
M1206:  z1=x;
	z3=z1;
	z=z1;
	z0=d;
M1210:  z4=(d*z0-t)/(d*z0-d)/((d*z0-e)*(d*z0-e));
	z2=-z4*z1*x*x;
	z1=z2;
	z3+=z2;
	z=z2;
   if (fabs(z)-eps > 0.) goto  M3210;
   else                  goto  M1218;
M3210:  z0+=e;
	goto  M1210;
M1218:  y=z3;
	goto  M1248;
M1222:  z1=e;
	z3=e;
	z=e;
	z0=d;
M1226:  z4=(d*z0-d)*(d*z0-t);
	z2=-z4*z1/(x*x);
	z1=z2;
	z3+=z2;
	z=z2;
   if (fabs(z)-eps > 0.) goto  M3226;
   else                  goto  M1234;
M3226:  z0+=e;
	goto  M1226;
M1234:  z7=1./x;
	z5=z7;
	z6=z7;
	z0=d;
M1238:  z9=(d*z0-e)*(d*z0-d);
	z8=-z9*z7/(x*x);
	z7=z8;
	z5+=z8;
	z6=z8;
   if (fabs(z6)-eps > 0.)  goto  M9238;
   else                    goto  M1246;
M9238:  z0+=e;
	goto  M1238;
M1246:  y=pi2-cos(x)/x*z3-sin(x)/x*z5;
M1248:  return (y);
}
