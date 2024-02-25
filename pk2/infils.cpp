#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "paths.h"

void magfis(double fi, double teta, double r,
	    double h[3], double dh[3][3], double dh3[3][3][3]);

void infils(long keyh)
/********************************************************************/
/*                                                                  */
/*         ввод параметров геомагнитного поля                       */
/*         keyh: 1 - глобальная модель геомагнитного поля,          */
/*               0 - геомагнитное поле постоянно                    */
/*VGG                                                               */
/********************************************************************/
  {
    double ai,d,amod;
    int  i,j,k;

    sf=sf0=sin(fi0);
    cf=cf0=cos(fi0);
    st=st0=sin(teta0);
    ct=ct0=cos(teta0);

    ivar=keyh;
    magfis(fi0,teta0,R0,h,dh,dh2);

    amod=h[0]*h[0]+h[1]*h[1];
    fh=2.79*sqrt(h[2]*h[2]+amod);
    ai=-atan2(h[2],sqrt(amod));
    d=atan2(h[0],h[1]);

    if (!ivar)
    {
       h[0]=cos(ai)*sin(d);
       h[1]=-cos(ai)*cos(d);
       h[2]=-sin(ai);

       for(i=0; i<3; i++)
	 for(j=0; j<3; j++)
	   {
	     dh[i][j]=.0;
	     for(k=0; k<3; k++)
	       dh2[i][j][k]=.0;
	   }
    }

    ai/=RAD;
    d/=RAD;

    return;

} /*  infils */
