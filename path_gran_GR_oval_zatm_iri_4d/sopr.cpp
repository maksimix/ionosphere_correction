#include <math.h>
#include <stdio.h>

void sopr1(double f1,
	   double h1,
	   double *y1,
	   double df1,
	   double dh1,
	   double *dy1,
	   double f2,
	   double h2,
	   double y2,
	   double df2,
	   double dh2,
	   double dy2,
	   double *h12,
	   double *dh12,
	   int    key)
/***************************************************************/
/*                                                             */
/* Функция сопрягает две квазипараболы, обеспечивая непрерыв-  */
/*           ность функции и ее первой производной             */
/*                                                             */
/* f1   - критическая частота первой квазипараболы;            */
/* h1   - высота максимума;                                    */
/* y1   - полутолщина (вычисляется);                           */
/* df1  - производная критической частоты по углу места;       */
/* dh1  - производная высоты максимума;                        */
/* dy1  - производная полутолщины (вычисляется);               */
/* f2                                                          */
/* h2                                                          */
/* y2                                                          */
/* df2                                                         */
/* dh2                                                         */
/* dy2                                                         */
/* h12  - высота точки сопряжения квазипарабол;                */
/* dh12 - производжная высоты сопряжения по углу места;        */
/* key  >0 , если рассчитывается пространственное ослабление.  */
/*                                                             */
/*VGG  версия 04.02.92                                         */
/***************************************************************/

{
  static double df,dh,sqf,rab,rab2,ra,ra2,zn,zn1,dhy,ch1,
		ddf,hy,hy2,f12,f22;

  hy=h2/y2-1.;
  hy2=hy*hy;
  f12=f1*f1;
  f22=f2*f2;
  df=f22-f12;
  sqf=sqrt(df);
  dh=h2-h1;
  zn1=h1*df+f22*dh*hy2;
  ch1=f22*h2*dh*hy2;
  *h12=ch1/zn1;
  ra2=f22*dh*dh*hy2-h1*h1*df;
  ra=sqrt(ra2);
  rab2=f12*ra2;
  rab=f1*ra;
  zn=1.+f2*h2*hy*sqf/rab;
  *y1=h1/zn;
  if (key>0)
    {
      ddf=f2*df2-f1*df1;
      dhy=(y2*dh2-h2*dy2)/(y2*y2);
      *dy1=(dh1-*y1*((sqf*hy*(df2*h2+f2*dh2)+
	   f2*h2*(dhy*sqf+hy*ddf/sqf))/rab-f2*h2*
	   hy*sqf*(df1*ra+f1/ra*(f2*hy2*dh*(dh*df2+
	   f2*(dh2-dh1))+f22*dh*dh*hy*dhy-
	   h1*(dh1*df+h1*ddf)))/rab2))/zn;
      *dh12=(f2*dh*hy2*(2.*df2*h2+f2*dh2)+f22*h2*hy*
	    (hy*(dh2-dh1)+2.*dhy*dh)-*h12*(dh1*df+
	    2.*h1*ddf+f2*hy*((2.*df2*dh+f2*(dh2-dh1))*hy+
	    2.*f2*dh*dhy)))/zn1;
    }
  return;
} /* sopr1 */

void sopr2(double f1,
	   double h1,
	   double y1,
	   double df1,
	   double dh1,
	   double dy1,
	   double f2,
	   double *h2,
	   double *y2,
	   double df2,
	   double *dh2,
	   double *dy2,
	   double f3,
	   double h3,
	   double y3,
	   double df3,
	   double dh3,
	   double dy3,
	   double *h12,
	   double *h23,
	   double *dh12,
	   double *dh23,
	   int    key)
/***************************************************************/
/*                                                             */
/* Функция сопрягает три квазипараболы, обеспечивая непрерыв-  */
/*           ность функции и ее первой производной             */
/*                                                             */
/* f1   - критическая частота первой квазипараболы;            */
/* h1   - высота максимума;                                    */
/* y1   - полутолщина;                                         */
/* df1  - производная критической частоты по углу места;       */
/* dh1  - производная высоты максимума;                        */
/* dy1  - производная полутолщины;                             */
/* f2                                                          */
/* h2   - вычисляется;                                         */
/* y2   - вычисляется;                                         */
/* df2                                                         */
/* dh2  - вычисляется;                                         */
/* dy2  - вычисляется;                                         */
/* f3                                                          */
/* h3                                                          */
/* y3                                                          */
/* df3                                                         */
/* dh3                                                         */
/* dy3                                                         */
/* h12  - высота точки сопряжения квазипарабол;                */
/* h23                                                         */
/* dh12 - производжная высоты сопряжения по углу места;        */
/* dh23                                                        */
/* key  >0 , если рассчитывается пространственное ослабление.  */
/*                                                             */
/*VGG  версия 04.02.92                                         */
/***************************************************************/

{
  static double h32,f12,f22,f32,df12,df32,hy1,hy3,a,b,c,d,h22,
		df11,ddf12,ddf32,dhy1,dhy3,da,db,dc,dhh1,dhh3,
		rab1,rab2,fhy3,fhy1;

  *h12=h1*h1;
  h32=h3*h3;
  f12=f1*f1;
  f32=f3*f3;
  f22=f2*f2;
  df12=f12-f22;
  df32=f32-f22;
  hy1=h1/y1-1.;
  hy3=h3/y3-1.;
  fhy3=f32*hy3*hy3;
  rab1=1.-df32/fhy3;
  fhy1=f12*hy1*hy1;
  rab2=1.-df12/fhy1;
  a=*h12*df12*rab1-h32*df32*rab2;
  b=2.*(h1*h32*df32-h3**h12*df12);
  c=*h12*h32*(f12-f32);
  d=sqrt(fabs(b*b-4.*a*c));
  *h2=-(b+d)/(2.*a);
  if (key>0)
    {
      ddf12=f1*df1-f2*df2;
      ddf32=f3*df3-f2*df2;
      dhy1=(y1*dh1-h1*dy1)/(y1*y1);
      dhy3=(y3*dh3-h3*dy3)/(y3*y3);
      dhh1=h1*dh1;
      dhh3=h3*dh3;
      da=2.*((dhh1*df12+*h12*ddf12)*rab1-*h12*df12*(ddf32-
	 df32*(df3*hy3+f3*dhy3)/sqrt(fhy3))/fhy3-
	 (dhh3*df32+h32*ddf32)*rab1+h32*df32*(ddf12-df12*
	 (df1*hy1+f1*dhy1)/sqrt(fhy1))/fhy1);
      db=2.*(dh1*h32*df32-dh3**h12*df12+2.*h1*h3*
	 (dh3*df32-dh1*df12+h3*ddf32-h1*ddf12));     
      dc=2.*((df12-df32)*(dhh1*h32+dhh3**h12)+*h12*h32*
	 (ddf12-ddf32));
      *dh2=-((*h2*da+db)**h2+dc)/(2.**h2*a+b);
    }
  h22=*h2**h2;
  b=h3-*h2;
  d=*h2-h1;
  c=sqrt(df32);
  rab1=b*hy3;
  rab1=f32*rab1*rab1-h22*df32;
  rab2=sqrt(rab1);
  da=f22*rab1;
  db=f2*rab2;
  dc=1.+f3*h3*hy3*c/db;
  *y2=*h2/dc;
  if(key>0)
    *dy2=(*dh2-*y2*((hy3*c*(df3*h3+f3*dh3)+f3*h3*
	 (c*dhy3+hy3*ddf32/c))/db-f3*h3*hy3*c*
	 (df2*rab2+f2/rab2*(f3*hy3*b*(df3*b*hy3+
	 f3*(dh3-*dh2)*hy3+f3*b*dhy3)-*h2**dh2*
	 df32-h22*ddf32))/da))/dc;
  if (d==.0)
    {
      *h12=h1;
      if (key>0) *dh12=dh1;
    }
  else
    {
      da=*h2*df12;
      db=d*f12*hy1*hy1;
      dc=1.-da/db;
      *h12=h1/dc;
      if (key>0)
	*dh12=(dh1+*h12/db*(*dh2*df12+*h2*ddf12-
	      da/(d*f1*hy1)*(f1*hy1*(*dh2-dh1)+
	      2.*d*(df1*hy1+f1*dhy1))))/dc;
    }
  da=*h2*df32;
  db=b*f32*hy3*hy3;
  dc=1.+da/db;
  *h23=h3/dc;
  if (key>0)
    *dh23=(dh3-*h23/db*(*dh2*df32+*h2*ddf32-
	  da/(b*f3*hy3)*(f3*hy3*(dh3-*dh2)+
	  2.*b*(df3*hy3+f3*dhy3))))/dc;
  return;
} /* sopr2 */

int  sopr3(double f1,
	   double h1,
	   double y1,
	   double df1,
	   double dh1,
	   double dy1,
	   double *f2,
	   double *h2,
	   double *y2,
	   double *df2,
	   double *dh2,
	   double *dy2,
	   double f3,
	   double h3,
	   double y3,
	   double df3,
	   double dh3,
	   double dy3,
	   double h12,
	   double dh12,
	   double *h23,
	   double *dh23,
	   int    key)
/***************************************************************/
/*                                                             */
/* Функция сопрягает три квазипараболы, обеспечивая непрерыв-  */
/* ность функции и ее первой производной, причем предполагает- */
/* ся, что высота сопряжения первой и второй квазипарабол      */
/* известна.                                                   */
/*                                                             */
/* f1   - критическая частота первой квазипараболы;            */
/* h1   - ее высота максимума;                                 */
/* y1   - ее полутолщина;                                      */
/* df1  - производная критической частоты по углу места;       */
/* dh1                                                         */
/* dy1                                                         */
/* f2   - вычисляемые параметры второй квазипараболы;          */
/* h2                                                          */
/* y2                                                          */
/* df1                                                         */
/* dh1                                                         */
/* dy1                                                         */
/* f3   - параметры третьей квазипараболы;                     */
/* h3                                                          */
/* y3                                                          */
/* df3                                                         */
/* dh3                                                         */
/* dy3                                                         */
/* h12  - высота сопряжения первой и второй квазипарабол;      */
/* h23  - вычисляемая высота сопряжения второй и третьей       */
/*        квазипарабол;                                        */
/* key  - >0, если вычhсляется простррнственное ослабление.    */
/*                                                             */
/* Функция возвращает 1, если сопряжение заданных квазипарабол */
/* обратной квазипараболой выполнено успешно, и 0 в противном  */
/* случае.                                                     */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  static double a1,a2,a3,b1,b2,b3,c1,c2,c3,
		da1,da2,da3,db1,db2,db3,dc1,dc2,dc3,a0,
		r,r1,f1_2,f2_2,f3_2,h1_2,h3_2,hy1,hy3,hy1_2,hy3_2,
		ohy1,ohy3,h12_2,dhy1,dhy3;

  hy1=h1/y1-1.;
  hy1_2=hy1*hy1;
  hy3=h3/y3-1.;
  hy3_2=hy3*hy3;
  f1_2=f1*f1;
  f3_2=f3*f3;
  h1_2=h1*h1;
  h3_2=h3*h3;
  ohy1=1.-hy1_2;
  ohy3=1.-hy3_2;
  h12_2=h12*h12;

  a1=f1_2*ohy1;
  b1=2.*f1_2*h1*hy1_2;
  c1=-f1_2*h1_2*hy1_2;

  a3=f3_2*ohy3;
  b3=2.*f3_2*h3*hy3_2;
  c3=-f3_2*h3_2*hy3_2;

  a0=2.*(a1-a3)*h12+b1-b3;
  *h23=(h12*(b3-b1)+2.*(c3-c1))/a0;

  b2=(b3**h23-b1*h12+2.*(c3-c1))/(*h23-h12);
  c2=c1+.5*(b1-b2)*h12;
  a2=a1+.5*(b1-b2)/h12;

  *h2=-2.*c2/b2;
  f2_2=a2+.5*b2/ *h2;

  if (c2<=.0 || b2>=.0 || f2_2<=.0)
    {
      *f2=.0;
      *h2=.0;
      *y2=.0;
      return 0;
    }

  *f2=sqrt(f2_2);
  r=sqrt(c2);
  r1=1.+r/(*f2**h2);
  *y2=*h2/r1;

  if (key)
    {
      df1=2.*f1*df1;
      df3=2.*f3*df3;
      dhy1=2.*hy1*(y1*dh1-h1*dy1)/(y1*y1);
      dhy3=2.*hy3*(y3*dh3-h3*dy3)/(y3*y3);

      da1=df1*ohy1-f1_2*dhy1;
      db1=2.*((df1*h1+f1_2*dh1)*hy1_2+f1_2*h1*dhy1);
      dc1=-h1*((df1*h1+2.*f1_2*dh1)*hy1_2+f1_2*dhy1*h1);

      da3=df3*ohy3-f3_2*dhy3;
      db3=2.*((df3*h3+f3_2*dh3)*hy3_2+f3_2*h3*dhy3);
      dc3=-h3*((df3*h3+2.*f3_2*dh3)*hy3_2+f3_2*dhy3*h3);


      *dh23=(2.*(dc3-dc1)+dh12*(b3-b1)+h12*(db3-db1)-
	    *h23*(2.*((da1-da3)*h12+dh12*(a1-a3))+db1-db3))/a0;

      db2=((db3**h23+b3**dh23-2.*(dc1-dc3)-db1*h12-b1*dh12)-
	   (*dh23-dh12)*b2)/(*h23-h12);
      dc2=dc1+.5*(h12*(db1-db2)+dh12*(b1-b2));
      da2=da1+.5*((db1-db2)*h12-dh12*(b1-b2))/h12_2;

      *dh2=2.*(c2*db2-b2*dc2)/(b2*b2);
      *df2=.5*(da2+.5*(*h2*db2-b2**dh2)/(*h2**h2))/ *f2;
      *dy2=(*dh2-*y2*(.5*dc2**f2**h2/r+r*(*df2**h2+*f2**dh2))/
	    (*f2**f2**h2**h2))/r1;
    }

  return 1;

} /* sopr3 */
