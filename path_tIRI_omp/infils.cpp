#include "paths.h"

void magfis(double fi, double teta, double r,
	    double h[3], double dh[3][3], double dh3[3][3][3]);

void infils(FILE *in, FILE *out)
/********************************************************************/
/*                                                                  */
/*         ФУНКЦИЯ ВВОДА ПАРАМЕТРОВ ГЕОМАГНИТНОГО ПОЛЯ              */
/*                                                                  */
/*VGG                                                               */
/********************************************************************/
  {
    double ai,d,amod;

    register int  i,j,k;

    sf=sf0=sin(fi0);
    cf=cf0=cos(fi0);
    st=st0=sin(teta0);
    ct=ct0=cos(teta0);

    fscanf(in,"%d",&ivar);

    if (!ivar)
    {
        fprintf(out,"\nGeomagnetic Field - const");

        fscanf(in,"%lg%lg%lg",&fh,&ai,&d);

        if (fh<.1e-10 || fh>5. || fabs(ai)>90. || fabs(d)>180)
        {
            printf("\n*infilp:Error inpur geomagnetoc Field Parametres");
            exit(EXIT_FAILURE);
        }

        fprintf(out,"\nfh=%5.2f  i=%6.1f  d=%6.1f",fh,ai,d);

        ai *=RAD;
        d  *=RAD;

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
    else
    {
        fprintf(out,"\nGlobal Geomagnetic Field Model");

        magfis(fi0,teta0,R0,h,dh,dh2);

        amod=h[0]*h[0]+h[1]*h[1];
        fh=2.79*sqrt(h[2]*h[2]+amod);
        ai=-atan2(h[2],sqrt(amod))/RAD;
        d=atan2(h[0],h[1])/RAD;

        fprintf(out,"\nfh=%5.2f  i=%6.1f  d=%6.1f",fh,ai,d);

    }

    return;

} /*  infils */
