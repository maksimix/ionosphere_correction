#include "paths.h"

int MyTrek::soluts(double *x,
                    double *y0,
                    int    n,
                    double delt,
                    double e,
                    double eps,
                    double ep,
                    double ep1)
/*****************************************************************/
/*       ФУНКЦИЯ ОСУЩЕСТВЛЯЕТ УПРАВЛЕНИЕ ИНТЕГРИРОВАНИЕМ         */
/*       ДИФ. УРАВНЕНИЙ	ЛУЧА.                                    */
/*	 КАЖДЫЙ	ШАГ ИНТЕГРИРОВАНИЯ ОСУШЕСТВЛЯЕТСЯ ПОСРЕДСТВОМ        */
/*	 ПРОЦЕДУРЫ ltv.                                              */
/*	 ПОДПРОГРАММА УЧИТЫВАЕТ	ВОЗМОЖНЫЕ ОСОБЫЕ ТОЧКИ УРАВНЕНИЙ.    */
/*       ФУНКЦИЯ ВОЗВРАЩАЕТ: 0, ЕСЛИ ТРАЕКТОРИЯ ПОСТРОЕНА И      */
/*                           1, ЕСЛИ НЕТ ОТРАЖЕНИЯ.              */
/*                                                               */
/*VGG                                                            */
/*****************************************************************/
{
  double f0[22],y1[22],f1[22],r=0;
  int kolOtr=0;
  int i,nost;
  double x1,x2,h1,h2;
  int    n1=0,n2=5;
  int    ini,key_h;

  nost=1;

  ini=key_h=0;
  key_h=1;

  do
    {
      if (key_h)
        ltv(x,y0,f0,y1,f1,&delt,n,e,eps,n1,n2,&r);
      else
        ltv_i(x,y0,f0,y1,f1,&delt,n,e,eps,n1,n2,&ini,&r);

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

        printf("\n%12.5e",*x);
        /*
        for(i=0; i<n; i++)
        {
          if (i%3==0) printf("\n");
          printf("%12.5e %12.5e ",y1[i],f1[i]);
        }
        */
        printf(" %12.5e %12.5e %d %12.5e",y1[2]*100.-6370.,f1[2],kolOtr,dist(fi0,teta0,y1[0],y1[1]));
        printf("\n%12.5e %12.5e %12.5e %12.5e %12.5e %12.5e",delt,v,sa2,r,e,eps);
      }
      if (keytr<0 && pointTr<MaxPointTr-1)
      {
          hTr[pointTr]=100.*(y1[2]-R0);
          sTr[pointTr]=dist(fi0,teta0,y1[0],y1[1]);
          pointTr++;
      }
      /*
      if (*(y1+2)<rH0)
        {
          x2=*x;
          *x=x1;
          h2=*(y1+2);
          key_h=1;
        }
      else
        {
          x1=*x;
          h1=*(y1+2);
        }
      if (key_h)
        {
          delt=(x2-x1)*(rH0-h1)/(h2-h1);
          if (*(y1+2)<rH0)
            {
              *(y1+2)=h1;
              continue;
            }
        }
      */
      if (hm-y1[2]<eps || y1[1]-rH0>eps && delt<.1e-13)
          return 1;

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
                if (func(*x,y1,f1,6)) return 1;

                y1[10]=(anorm*(y1[2]*(st*f1[0]*y1[11]+f1[1]*y1[12])+
                    f1[2]*y1[13])-dmrtf[0]*y1[8]-dmrtf[1]*y1[9])
                    /dmrtf[2];
                y1[16]=(anorm*(y1[2]*(st*f1[0]*y1[17]+f1[1]*y1[18])+
                    f1[2]*y1[19])-dmrtf[0]*y1[14]-dmrtf[1]*y1[15])
                    /dmrtf[2];

                func(*x,y1,f1,n);
              }
              ini=0;
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

  }   while((y0[2]-rH0>eps || f0[2]>.0) && kolOtr<maxKolOtr);

  if (kolOtr>=maxKolOtr)
      return -1;

  return 0;

} /* soluts */

