#include <math.h>

void bs(long n, double l, double rs, double l1, double h,
        double eps, double sig, double f, double d, double fi,
        double *d1, double *d2, double *d3)
/*************************************************************/
/*                 Входные  параметры                        */
/*                                                           */
/*   n   - число вибраторов в полотне                        */
/*   l   - длина одного плеча вибратора,(м)                  */
/*   rs  - сопротивление резистора, включённого в плечо,(ом) */
/*   l1  - расстояние между вибраторами по фидеру,(м)        */
/*   h   - высота подвеса антенны,(м)                        */
/*   eps - диэлектрическая проницаемость почвы               */
/*   sig - удельная проводимость почвы,(Сим/м)               */
/*   f   - рабочая частота,(Мгц)                             */
/*   d   - угол места,(рад)                                  */
/*   fi  - азимутальный угол,(рад)                           */
/*                                                           */
/*                 Выходные  параметры                       */
/*                                                           */
/*   d1 - КНД  для антенны  БС,  (раз)                       */
/*   d2 - КНД  для антенны  БС-2,(раз)                       */
/*   d3 - КНД  для антенны  БС-3,(раз)                       */
/*************************************************************/
{
 double k1,ku,nu,nu1,nu2,al,riz,be,rv,xv,xiz,am,dij,
       x1,x2,a,b,rsr,xsr,bec1,w,a1,a2,cm,bm,zm,a3,a41,a42,
       a43,a4,rgr,rgi,rvr,rvi,ph,fih;
 double r[21][21],x[21][21],rx[21],xx[21];
 double pi=3.1415926535,wv=960.,w0=170.,e=0.5772;
 long   i,j;
 extern void fm(double f,   double t,   double eps, double sig,
                double *rgr,double *rgi,double *rvr,double *rvi);
 extern double ci(double x);
 extern double si(double x);
  if (n > 21 || n < 1)
     {*d1=.0;
      *d2=.0;
      *d3=.0;
      return;
     }
  al=pi*f/150.;
  riz=30.*(2.*(e+log(2.*al*l)-ci(2.*al*l))+sin(2.*al*l)*
      (si(4.*al*l)-2.*si(2.*al*l))+cos(2.*al*l)*(e+log(al*l)+
      ci(4.*al*l)-2.*ci(2.*al*l)));
  be=riz/(l*wv*(1.-sin(2.*al*l)/(2.*al*l)));
  rv=wv*(sinh(2.*be*l)-be/al*sin(2.*al*l))/(cosh(2.*be*l)-cos(2.*al*l));
  xv=-wv*(be/al*sinh(2.*be*l)+sin(2.*al*l))/(cosh(2.*be*l)-cos(2.*al*l));
  k1=1./(1.-w0*xv/(2.*al*l1*((rv+2.*rs)*(rv+2.*rs)+xv*xv)));
  xiz=60.*(2.*si(2.*al*l)+sin(2.*al*l)*(e+log(al*l)+ci(4.*al*l)-
      2.*ci(2.*al*l)-17.97)+cos(2.*al*l)*(2.*si(2.*al*l)-si(4.*al*l)));
  am=30.*(1.-cos(al*l));
  for (i=0; i<n; i++)
    {for (j=0; j<n; j++)
       {if (i==j)
           {r[i][j]=riz;
            x[i][j]=xiz;
           }
         else
           {dij=l1*fabs((double)(i-j));
            x1=al*sqrt(l*l/4.+dij*dij);
            x2=al*sqrt(9.*l*l/4.+dij*dij);
            a=2./x2*cos(x2)+2./x1*cos(x1)*(1.-2.*cos(al*l));
            b=2./x2*sin(x2)+2./x1*sin(x1)*(1.-2.*cos(al*l));
            r[i][j]=am*b;
            x[i][j]=am*a;
           }
        }
    }
 for (i=0; i<n; i++)
    {xx[i]=0.;
     rx[i]=0.;
    }
 rsr=0.;
 xsr=0.;
 for (i=0; i<n; i++)
   {for (j=0; j<n; j++)
      {xx[i]+=x[i][j];
       rx[i]+=r[i][j];
      }
   }
 for (i=0; i<n; i++)
   {xsr+=xx[i];
    rsr+=rx[i];
   }
 xsr/=(double) n;
 rsr/=(double) n;
 bec1=w0*(rsr+2.*rs)/(2.*l1*((rsr+2.*rs)*(rsr+2.*rs)+xsr*xsr));
 k1=1./(1.-w0*xsr/(2.*al*l1*((rsr+2.*rs)*(rsr+2.*rs)+xsr*xsr)));
 w=w0*k1;
 a1=73.1*w/((rsr+2.*rs+w/2.)*(rsr+2.*rs+w/2.)+xsr*xsr);
 fm(f,d,eps,sig,&rgr,&rgi,&rvr,&rvi);
 ph=sqrt(rgr*rgr+rgi*rgi);
 fih=atan2(rgi,rgr);
 a2=1.+ph*ph+2.*ph*cos(fih-2.*al*h*sin(d));
 cm=exp(-bec1*l1*(double) n);
 bm=exp(-bec1*l1);
 zm=al*l1*(cos(d)*cos(fi)-1./k1);
 a3=(cm*cm-2.*cm*cos(zm*n)+1.)/(bm*bm-2.*bm*cos(zm)+1.);
 a41=cos(al*l*cos(d)*sin(fi))-cos(al*l);
 a42=(sinh(4.*be*l)*cos(al*l))*(sinh(4.*be*l)*cos(al*l))+
     (cosh(4.*be*l)*sin(al*l))*(cosh(4.*be*l)*sin(al*l));
 a43=1.-cos(d)*cos(d)*sin(fi)*sin(fi);
 a4=a41/(sqrt(a42)*sqrt(a43));
 ku=a1*a2*a3*a4*a4;
 nu1=rsr/(rsr+2.*rs);
 nu2=1.-exp(-180.*be);
 nu=nu1*nu2;
 *d1=1.64*ku/nu;
 *d2=*d1*pow(10.,0.2);
 *d3=*d1*pow(10.,0.65);
 return;
}
