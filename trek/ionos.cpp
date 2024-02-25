using namespace std;
#include <iostream>
#include <iomanip>
#include "paths.h"

extern double Vx, Vy, Vz;

int MyTrek::ionos(double f,
                  double t,
                  double r,
                  int    n)
/***************************************************************/
/*                                                             */
/*	ФУНКЦИЯ ВЫЧИСЛЯЕТ ЗНАЧЕНИЕ КВАДРАТА ПЛАЗМЕННОЙ         */
/*      ЧАСТОТЫ	И ЕГО ПРОИЗBОДНЫХ ПО ДЕКАРТОВЫМ	КООРДИНАТАМ    */
/*	ДЛЯ МОДЕЛЕЙ ИОНОСФЕРЫ ОПИСАННЫХ	И ВВЕДЕННЫХ В inions   */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
   double rd[3],rexp,r1,g,r2,r3,drtf[3],g2,dr,df,dt,
          tid0,rc[3],rff,rtt,rrr,rft,rfr,rtr,fo;
   double vt=.0;
   double nu=.0;
   IonPar p;
   int i;

/*--------------------------------------------------------------*/

   dr=r-R0;
   df=f-fi0;
   dt=t-teta0;

   if (r<h0)
   {
       v=.0;
       for(int i=0; i<3; i++)
       {
           vp[i]=.0;
           for(int j=0; j<3; j++)
               vpp[i][j]=.0;
       }
       return 1;
       //return 0;
   }
   else
       if (mod<10)
       {
           switch (mod)
           {
               case 1: r1=(r-h0)/ym;
                       v=f02*r1*(2.-r1)/fr2;
                       vp[2]=2.*f02*(1.-r1)/(ym*fr2);
                       vpp[2][2]=-2.*f02/(ym*ym*fr2);
                       //printf("\n%6.1f  %6.4f",100.*dr,sqrt(v));
                       break;
      
               case 2: v=.0;
                       vp[2]=.0;
                       vpp[2][2]=.0;
                       for(i=0; i<klay; i++)
                         {
                           r1=(r-hl[i])/yl[i];
                           rexp=exp(-r1);
                           r1=fl[i]*exp(al[i]*(1.-r1-rexp));
                           v +=r1;
                           r2=al[i]*(rexp-1.)/yl[i];
                           r3=r1*r2;
                           vp[2] +=r3;
                           vpp[2][2] +=r3*r2-r1*al[i]*rexp/(yl[i]*yl[i]);
                         }
                       v=(v-par)/fr2;
                       vp[2]     /=fr2;
                       vpp[2][2] /=fr2;
                       break;
      
               case 3: for(i=0; i<klay; i++)
                         {
                           if (r>al[i] && i!=klay-1) continue;
                           par=1.-2.*fmod(i,2.);
                           r1=(hl[i]-yl[i])/r;
                           r2=(hl[i]-r)/yl[i];
                           r3=r1*r2;
                           v=fl[i]*(1.-par*r3*r3)/fr2;
                           r1=hl[i]/yl[i]-1.;
                           r2=2.*fl[i]*par*r1*hl[i]/(r*r);
                           vp[2]=r2*r3/fr2;
                           vpp[2][2]=-r2*r1*(3.*hl[i]-2.*r)/(r*r*fr2);
                           if (r==h0) v=.0;
                           break;
                         }
                       break;
      
               case 4:
      
               case 5:
      
               case 6:
                       spN_H->spcub(r,v,vp[2],vpp[2][2]);
                       v         /=fr2;
                       vp[2]     /=fr2;
                       vpp[2][2] /=fr2;
                       break;
      
           }
      
           r1=gx*st;
           r2=2.*v;
           r3=gx*ct*df+gy;
      
           g=1.+r1*df+gy*dt;
           g2=g*g;
      
           if (n>8)
             {
               vpp[0][0]=r2*r1*r1;
               vpp[0][1]=r2*(r1*r3+g*gx*ct);
               vpp[0][2]=2.*vp[2]*g*r1;
               vpp[1][0]=vpp[0][1];
               vpp[1][1]=r2*(gy*gy-g*r1*df);
               vpp[1][2]=2.*vp[2]*g*r3;
               vpp[2][0]=vpp[0][2];
               vpp[2][1]=vpp[1][2];
               vpp[2][2]=vpp[2][2]*g2;
             }
      
           r2 *=g;
           v *=g2;
           vp[0]=r2*r1;
           vp[1]=r2*r3;
           vp[2]=vp[2]*g2;
       }
       else
       {
           if (n>8)
           {
               //cout<<endl<<"1 ionosf"<<flush;
               ionosf(f,t,100.*r,tim,v,vp[0],vp[1],vp[2],vt,vpp[0][0],vpp[1][1],vpp[2][2],
                      vpp[0][1],vpp[0][2],vpp[1][2],p);
               //cout<<endl<<"2 ionosf"<<flush;
               vpp[2][2]*=10000.;
               vpp[0][2]*=100.;
               vpp[1][2]*=100.;
               vpp[0][0]/=fr2;
               vpp[1][1]/=fr2;
               vpp[2][2]/=fr2;
               vpp[0][1]/=fr2;
               vpp[0][2]/=fr2;
               vpp[1][2]/=fr2;
           }
           else
           {
               vpp[0][0]=vpp[0][1]=vpp[0][2]=vpp[1][1]=vpp[1][2]=vpp[2][2]=.0;
               vt=.0;

               //cout<<endl<<"3 ionosf"<<flush;
               ionosf(f,t,100.*r,tim,v,vp[0],vp[1],vp[2],vt,p);
               //cout<<endl<<"4 ionosf"<<flush;
               //printf("\n v=%f r=%f",sqrt(v),100.*(r-R0));
           }
           vp[2]*=100.;
           v/=fr2;
           vp[0]/=fr2;
           vp[1]/=fr2;
           vp[2]/=fr2;
           vt   /=fr2;
       }

     if(keynu==0 && mod==10)
     {
         nuprof(f,t,100.*r,tim,nu);      //IRI model
         s=nu/(2.*fr*PI);
	 //printf("\nnu=%12.5e",nu);
     }
     else
     {
         s=(exp(12.7-15.8*(r-R0))+exp(-6.17-.42*(r-R0)))/(2.*fr*PI);
     }

     if(v<.0)
     {
	 v=.0;
	 vp[0]=.0;
	 vp[1]=.0;
         vp[2]=.0;
         vt=.0;
	 return 0;
     }

     if (koltid)
     {
	 r1=df*st;
	 r2=df*ct;

	 for(i=0; i<koltid; i++)
	   {
	     fo=-om[i]*tim+pr[i]*dr+(pt[i]*dt+pf[i]*r1)*r+fit[i];
	     rc[i]=-de[i]*cos(fo);
	     rd[i]=-de[i]*sin(fo);
	   }

	 tid0=.0;
	 drtf[0]=.0;
	 drtf[1]=.0;
	 drtf[2]=.0;
	 dvt=.0;

	 for(i=0; i<koltid; i++)
	   {
	     drtf[0] +=rd[i]*pf[i];
	     drtf[1] +=rd[i]*(pt[i]+pf[i]*r2);
	     drtf[2] +=rd[i]*(pr[i]+pt[i]*dt+pf[i]*r1);

	     dvt +=rd[i]*om[i];

	     tid0 +=rc[i];
	   }

	 tid0=1.-tid0;

	 drtf[0] *=r*st;
	 drtf[1] *=r;

         dvt=-v*dvt;
         dvt=vt*tid0-v*dvt;

	 if(n>8)
	   {
	     rff=.0;
	     rtt=.0;
	     rrr=.0;
	     rft=.0;
	     rfr=.0;
	     rtr=.0;

	     for(i=0; i<koltid; i++)
	       {
		 r1=r*pf[i]*st;
		 r2=r*(pt[i]+pf[i]*ct*df);
		 r3=pr[i]+pt[i]*dt+pf[i]*df*st;

		 rff +=rc[i]*r1*r1;
		 rtt +=rc[i]*r2*r2-rd[i]*r1*df;
		 rrr +=rc[i]*r3*r3;
		 rft +=rc[i]*r1*r2+rd[i]*r*pf[i]*ct;
		 rfr +=rc[i]*r1*r3+rd[i]*pf[i]*st;
		 rtr +=rc[i]*r2*r3+rd[i]*(pt[i]+pf[i]*ct*df);
	       }

	     vpp[0][0]=vpp[0][0]*tid0+2.*vp[0]*drtf[0]+v*rff;
	     vpp[1][1]=vpp[1][1]*tid0+2.*vp[1]*drtf[1]+v*rtt;
	     vpp[2][2]=vpp[2][2]*tid0+2.*vp[2]*drtf[2]+v*rrr;
	     vpp[0][1]=vpp[0][1]*tid0+vp[0]*drtf[1]+vp[1]*drtf[0]+v*rft;
	     vpp[0][2]=vpp[0][2]*tid0+vp[0]*drtf[2]+vp[2]*drtf[0]+v*rfr;
	     vpp[1][2]=vpp[1][2]*tid0+vp[1]*drtf[2]+vp[2]*drtf[1]+v*rtr;
	     vpp[1][0]=vpp[0][1];
	     vpp[2][0]=vpp[0][2];
	     vpp[2][1]=vpp[1][2];
	   }

	 vp[0]=v*drtf[0]+vp[0]*tid0;
	 vp[1]=v*drtf[1]+vp[1]*tid0;
	 vp[2]=v*drtf[2]+vp[2]*tid0;

	 v *=tid0;
     }

     if (keyFsp)
     {
         double rx,ry,rz,x1,y1,z1;
         double dx1r,dx1f,dx1t,dy1r,dy1f,dy1t,dz1r,dz1f,dz1t;
         double dlt,dDlt,sF_A,cF_A;
         double dlt_r,dlt_f,dlt_t;
         double dlt_rr,dlt_rf,dlt_rt,dlt_ft, dlt_ff, dlt_tt, dx1rr,dx1ff,dx1tt,dx1rf,dx1rt,dx1ft,dy1rr,dy1ff,dy1tt,dy1rf,dy1rt,dy1ft,
                dz1rr,dz1ff,dz1tt,dz1rf,dz1rt,dz1ft;
         double rabr,rabf,rabt;

         //printf("\nr*st*cf=%f  rx_0=%f",r*st*cf,rx_0);
         rx=r*st*cf-rx_0;
         ry=r*st*sf-ry_0;
         rz=r*ct-rz_0;
         x1=( rx*kx_0[0]+ry*kx_0[1]+rz*kx_0[2])/aX;
         y1=( rx*ky_0[0]+ry*ky_0[1]+rz*ky_0[2])/aY;
         z1=( rx*kz_0[0]+ry*kz_0[1]+rz*kz_0[2])/aZ;
         dDlt=delta0*exp(-x1*x1-y1*y1-z1*z1);
         dlt=1.+dDlt;

         dx1r=( st*cf*kx_0[0]+st*sf*kx_0[1]+ct*kx_0[2] )/aX;
         dx1f=r*( -st*sf*kx_0[0]+st*cf*kx_0[1] )/aX;
         dx1t=r*(  ct*cf*kx_0[0]+ct*sf*kx_0[1]-st*kx_0[2] )/aX;
         dy1r=( st*sf*ky_0[0]+st*sf*ky_0[1]+ct*ky_0[2] )/aY;
         dy1f=r*( -st*sf*ky_0[0]+st*cf*ky_0[1] )/aY;
         dy1t=r*(  ct*cf*ky_0[0]+ct*sf*ky_0[1]-st*ky_0[2] )/aY;
         dz1r=( st*cf*kz_0[0]+st*sf*kz_0[1]+ct*kz_0[2] )/aZ;
         dz1f=r*( -st*sf*kz_0[0]+st*cf*kz_0[1] )/aZ;
         dz1t=r*(  ct*cf*kz_0[0]+ct*sf*kz_0[1]-st*kz_0[2] )/aZ;
         dx1rr=.0;
         dx1ff=-r*( st*cf*kx_0[0]+st*sf*kx_0[1] )/aX;
         dx1tt=-r*( st*cf*kx_0[0]+st*sf*kx_0[1]+ct*kx_0[2] )/aX;
         dy1rr=.0;
         dy1ff=-r*( st*cf*ky_0[0]+st*sf*ky_0[1] )/aY;
         dy1tt=-r*( st*cf*ky_0[0]+st*sf*ky_0[1]+ct*ky_0[2] )/aY;
         dz1rr=.0;
         dz1ff=-r*( st*cf*kz_0[0]+st*sf*kz_0[1] )/aZ;
         dz1tt=-r*( st*cf*kz_0[0]+st*sf*kz_0[1]+ct*kz_0[2] )/aZ;
         dx1rf=( -st*sf*kx_0[0]+st*cf*kx_0[1] )/aX;
         dx1rt=( ct*cf*kx_0[0]+ct*sf*kx_0[1]-st*kx_0[2] )/aX;
         dx1ft=r*( -ct*sf*kx_0[0]+ct*cf*kx_0[1] )/aX;
         dy1rf=( st*cf*ky_0[0]+st*cf*ky_0[1] )/aY;
         dy1rt=( ct*sf*ky_0[0]+ct*sf*ky_0[1]-st*ky_0[2] )/aY;
         dy1ft=r*( -ct*sf*ky_0[0]+ct*cf*ky_0[1] )/aY;
         dz1rf=( -st*sf*kz_0[0]+st*cf*kz_0[1] )/aZ;
         dz1rt=( ct*cf*kz_0[0]+ct*sf*kz_0[1]-st*kz_0[2] )/aZ;
         dz1ft=r*( -ct*sf*kz_0[0]+ct*cf*kz_0[1] )/aZ;
         rabr=-2.*(x1*dx1r+y1*dy1r+z1*dz1r);
         rabf=-2.*(x1*dx1f+y1*dy1f+z1*dz1f);
         rabt=-2.*(x1*dx1t+y1*dy1t+z1*dz1t);

         dlt_r=dDlt*rabr;
         dlt_f=dDlt*rabf;
         dlt_t=dDlt*rabt;

         dlt_rr=dDlt*(rabr*rabr-2.*((x1*dx1rr+dx1r*dx1r)+(y1*dy1rr+dy1r*dy1r)+(z1*dz1rr+dz1r*dz1r)));
         dlt_ff=dDlt*(rabf*rabf-2.*((x1*dx1ff+dx1f*dx1f)+(y1*dy1ff+dy1f*dy1f)/aY+(z1*dz1ff+dz1f*dz1f)));
         dlt_tt=dDlt*(rabt*rabt-2.*((x1*dx1tt+dx1t*dx1t)+(y1*dy1tt+dy1t*dy1t)/aY+(z1*dz1tt+dz1t*dz1t)));
         dlt_rf=dDlt*(rabr*rabf-2.*((x1*dx1rf+dx1r*dx1f)+(y1*dy1rf+dy1r*dy1f)/aY+(z1*dz1rf+dz1r*dz1f)));
         dlt_rt=dDlt*(rabr*rabt-2.*((x1*dx1rt+dx1r*dx1t)+(y1*dy1rt+dy1r*dy1t)/aY+(z1*dz1rt+dz1r*dz1t)));
         dlt_ft=dDlt*(rabf*rabt-2.*((x1*dx1ft+dx1f*dx1t)+(y1*dy1ft+dy1f*dy1t)/aY+(z1*dz1ft+dz1f*dz1t)));

         vpp[0][0]=vpp[0][0]*dlt+2.*vp[0]*dlt_f+v*dlt_ff;
         vpp[1][1]=vpp[1][1]*dlt+2.*vp[1]*dlt_t+v*dlt_tt;
         vpp[2][2]=vpp[2][2]*dlt+2.*vp[2]*dlt_r+v*dlt_rr;
         vpp[0][1]=vpp[0][1]*dlt+vp[0]*dlt_t+vp[1]*dlt_f+v*dlt_ft;
         vpp[0][2]=vpp[0][2]*dlt+vp[0]*dlt_r+vp[2]*dlt_f+v*dlt_rf;
         vpp[1][2]=vpp[1][2]*dlt+vp[1]*dlt_r+vp[2]*dlt_t+v*dlt_rt;
         vpp[1][0]=vpp[0][1];
         vpp[2][0]=vpp[0][2];
         vpp[2][1]=vpp[1][2];

         //dlt_f=.0;
         //dlt_t=.0;
         //dlt_r=.0;
         vp[0]=v*dlt_f+vp[0]*dlt;
         vp[1]=v*dlt_t+vp[1]*dlt;
         vp[2]=v*dlt_r+vp[2]*dlt;

         v*=dlt;
         //if (r>160./100.+R0)
         //    printf("\nr=%f fi=%f teta=%f rx=%f  ry=%f  rz=%f v=%f dlt=%f",(r-R0)*100.,f/RAD,t/RAD,rx*100.,ry*100.,rz*100.,v,dlt);
     }

     return 0;

}  /* ionos */


int MyTrek::ionosf(double fi,     // сферические координаты расположения луча
          double teta,   //
          double r,      //
          double &v,     // нормированный квадрат плазменной частоты
          double &vfi,   // его производные по fi, tets, r
          double &vteta, //
          double &vr,
          IonPar &p)    //
//  Вычисление профиля ионизации и его производных
//
//VGG
{
double X,Y,Z,dX,dY,dZ,x,y;
double sF,cF,sT,cT,vx,vy;
double dxf,dyf,dxt,dyt,cdf,sdf;
long keyX,keyY,keyZ,key;
long ix,iy,iz;

//cout<<endl<<"0 ionosf_iri"<<flush;

sF=sin(fi);
cF=cos(fi);
sT=sin(teta);
cT=cos(teta);
X=r*sT*cF;
Y=r*sT*sF;
Z=r*cT;
dX=X-iri_3dbase->X0;
dY=Y-iri_3dbase->Y0;
dZ=Z-iri_3dbase->Z0;
x=dY*iri_3dbase->cFi0-dX*iri_3dbase->sFi0;
y=dZ*iri_3dbase->sTeta0-dX*iri_3dbase->cTeta0*iri_3dbase->cFi0-dY*iri_3dbase->cTeta0*iri_3dbase->sFi0;

//cout<<endl<<"1 ionosf_iri"<<flush;
iri_3dbase->spcub(x,y,r-iri_3dbase->r0,v,vx,vy,vr,keyX,keyY,keyZ,ix,iy,iz);
//cout<<endl<<"2 ionosf_iri"<<flush;
p.HmF2=(iri_3dbase->gethmF2(ix,iy))*.01+R0;
p.HmF1=(iri_3dbase->gethmF1(ix,iy))*.01+R0;
p.HmE =(iri_3dbase->gethmE(ix,iy))*.01+R0;
p.HmEs=(iri_3dbase->gethmEs(ix,iy))*.01+R0;
key=fabs(keyX)+fabs(keyY);

cdf=cF*iri_3dbase->cFi0+sF*iri_3dbase->sFi0;
//cdf=cF*iri_3dbase->cFi0-sF*iri_3dbase->sFi0; //old
sdf=sF*iri_3dbase->cFi0-cF*iri_3dbase->sFi0;
dxf=r*sT*cdf;
dyf=r*sT*iri_3dbase->cTeta0*sdf;
//dyf=r*sT*cT*sdf; //old
dxt=r*cT*sdf;
dyt=-r*(sT*iri_3dbase->sTeta0+cT*iri_3dbase->cTeta0*cdf);
vfi=vx*dxf+vy*dyf;
vteta=vx*dxt+vy*dyt;

key=0;

return key;
}

int MyTrek::ionosf(double fi,     // сферические координаты расположения луча
          double teta,   //
          double r,      //
          double time,
          double &v,     // нормированный квадрат плазменной частоты
          double &vfi,   // его производные по fi, tets, r
          double &vteta, //
          double &vr,    //
          double &vt,
          IonPar &p)    //
//  Вычисление профиля ионизации и его производных
//
//VGG
{
    //cout<<endl<<"00 ionosf_iri"<<flush;
    double X,Y,Z,dX,dY,dZ,x,y;
    double sF,cF,sT,cT,vx,vy;
    double dxf,dyf,dxt,dyt,cdf,sdf;
    long keyX,keyY,keyZ,key;
    long ix,iy,iz;
    double v1,vx1,vy1,vr1;
    double v2,vx2,vy2,vr2;
    double t1=iri_3dbase->getTime();
    double t2=iri_3dbase2->getTime();
    double hEs1,hEs2,hD1,hD2,hE1,hE2,hF11,hF12,hF21,hF22,f0F21,f0F11,f0E1,f0D1,f0Es1,fbEs1,
           f0F22,f0F12,f0E2,f0D2,f0Es2,fbEs2,pEs1,pEs2,hi1,hi2;
    
    //cout<<endl<<"r="<<r;
    //cout<<endl<<"000 ionosf_iri"<<flush;
    if (t1>24.)
        t1-=25.;
    if (t2>24.)
        t2-=25.;
    t1*=3600.;
    t2*=3600.;
    sF=sin(fi);
    cF=cos(fi);
    sT=sin(teta);
    cT=cos(teta);
    X=r*sT*cF;
    Y=r*sT*sF;
    Z=r*cT;
    dX=X-iri_3dbase->X0;
    dY=Y-iri_3dbase->Y0;
    dZ=Z-iri_3dbase->Z0;
    x=dY*iri_3dbase->cFi0-dX*iri_3dbase->sFi0;
    y=dZ*iri_3dbase->sTeta0-dX*iri_3dbase->cTeta0*iri_3dbase->cFi0-dY*iri_3dbase->cTeta0*iri_3dbase->sFi0;
    
    //cout<<endl<<"01 ionosf_iri"<<flush;
    iri_3dbase ->spcub(x,y,r-iri_3dbase->r0,v1,vx1,vy1,vr1,keyX,keyY,keyZ,ix,iy,iz);
    //cout<<endl<<"02 ionosf_iri"<<flush;
    //cout<<endl<<"1 x="<<x<<" y="<<y<<" r="<<r<<" "<<iri_3dbase->getIx()<<" "<<iri_3dbase->getIy()<<" "<<dZ<<" "<<dY<<" "<<dX<<" "<<iri_3dbase->Z0;
    hi1=iri_3dbase->getHi(ix,iy);
    hF21=iri_3dbase->gethmF2(ix,iy);
    f0F21=iri_3dbase->getf0F2(ix,iy);
    hF11=iri_3dbase->gethmF1(ix,iy);
    f0F11=iri_3dbase->getf0F1(ix,iy);
    hE1 =iri_3dbase->gethmE(ix,iy);
    f0E1=iri_3dbase->getf0E(ix,iy);
    hD1 =iri_3dbase->gethmD(ix,iy);
    f0D1=iri_3dbase->getf0D(ix,iy);
    hEs1=iri_3dbase->gethmEs(ix,iy);
    f0Es1=iri_3dbase->getf0Es(ix,iy);
    fbEs1=iri_3dbase->getfbEs(ix,iy);
    pEs1=iri_3dbase->getPEs(ix,iy);
    //cout<<endl<<"03 ionosf_iri"<<flush;
    iri_3dbase2->spcub(x,y,r-iri_3dbase->r0,v2,vx2,vy2,vr2,keyX,keyY,keyZ,ix,iy,iz);
    //cout<<endl<<"04 ionosf_iri"<<flush;
    //cout<<endl<<"2 x="<<x<<" y="<<y<<" r="<<r<<" "<<iri_3dbase->getIx()<<" "<<iri_3dbase->getIy()<<" "<<dZ<<" "<<dY<<" "<<dX;
    hi2=iri_3dbase2->getHi(ix,iy);
    hF22=iri_3dbase2->gethmF2(ix,iy);
    f0F22=iri_3dbase2->getf0F2(ix,iy);
    hF12=iri_3dbase2->gethmF1(ix,iy);
    f0F12=iri_3dbase2->getf0F1(ix,iy);
    hE2 =iri_3dbase2->gethmE(ix,iy);
    f0E2=iri_3dbase2->getf0E(ix,iy);
    hD2 =iri_3dbase->gethmD(ix,iy);
    f0D2=iri_3dbase->getf0D(ix,iy);
    hEs2=iri_3dbase2->gethmEs(ix,iy);
    f0Es2=iri_3dbase2->getf0Es(ix,iy);
    fbEs2=iri_3dbase2->getfbEs(ix,iy);
    pEs2=iri_3dbase2->getPEs(ix,iy);
    p.HmF2=(hF21+(time-t1)*(hF22-hF21)/(t2-t1))*.01+R0;
    p.F0F2=(f0F21+(time-t1)*(f0F22-f0F21)/(t2-t1));
    p.HmF1=(hF11+(time-t1)*(hF12-hF11)/(t2-t1))*.01+R0;
    p.F0F1=(f0F11+(time-t1)*(f0F12-f0F11)/(t2-t1));
    p.HmE =(hE1+(time-t1)*(hE2-hE1)/(t2-t1))*.01+R0;
    p.F0E=(f0E1+(time-t1)*(f0E2-f0E1)/(t2-t1));
    p.HmD =(hD1+(time-t1)*(hD2-hD1)/(t2-t1))*.01+R0;
    p.F0D =(f0D1+(time-t1)*(f0D2-f0D1)/(t2-t1));
    p.HmEs=(hEs1+(time-t1)*(hEs2-hEs1)/(t2-t1))*.01+R0;
    p.F0Es=(f0Es1+(time-t1)*(f0Es2-f0Es1)/(t2-t1));
    p.FbEs=(fbEs1+(time-t1)*(fbEs2-fbEs1)/(t2-t1));
    p.PEs=(pEs1+(time-t1)*(pEs2-pEs1)/(t2-t1));
    p.Hi=(hi1+(time-t1)*(hi2-hi1)/(t2-t1));
    p.fhTemp=(iri_3dbase->getFh(ix,iy));
    p.ITemp=(iri_3dbase->getI(ix,iy));
    p.DTemp=(iri_3dbase->getD(ix,iy));
    
    //cout<<endl<<"fi="<<fi/RAD<<" teta="<<(PI05-teta)/RAD<<"  t1="<<t1<<" t2="<<t2<<"  F0F2="<<F0F2<<" F0F21="<<f0F21<<" F0F22="<<f0F22<<flush;
    
    key=fabs(keyX)+fabs(keyY);
    
    vt=(v2-v1)/(t2-t1);
    v=(time-t1)*vt+v1;
    if (v<.0)
    {
        v=vx=vy=vr=.0;
    }
    else
    {
        vx=(time-t1)*(vx2-vx1)/(t2-t1)+vx1;
        vy=(time-t1)*(vy2-vy1)/(t2-t1)+vy1;
        vr=(time-t1)*(vr2-vr1)/(t2-t1)+vr1;
    }
    
    cdf=cF*iri_3dbase->cFi0+sF*iri_3dbase->sFi0;
    //cdf=cF*iri_3dbase->cFi0-sF*iri_3dbase->sFi0; //old
    sdf=sF*iri_3dbase->cFi0-cF*iri_3dbase->sFi0;
    dxf=r*sT*cdf;
    dyf=r*sT*iri_3dbase->cTeta0*sdf;
    //dyf=r*sT*cT*sdf; //old
    dxt=r*cT*sdf;
    dyt=-r*(sT*iri_3dbase->sTeta0+cT*iri_3dbase->cTeta0*cdf);
    vfi=vx*dxf+vy*dyf;
    vteta=vx*dxt+vy*dyt;
    
    Vx=vfi;
    Vy=vteta;
    Vz=vr;
    
    key=0;
    
    return key;
}

int MyTrek::ionosf(double fi,     // сферические координаты расположения луча
          double teta,   //
          double r,      //
          double &v,     // нормированный квадрат плазменной частоты
          double &vfi,   // его производные по fi, tets, r
          double &vteta, //
          double &vr,
          double &vff,
          double &vtt,
          double &vrr,
          double &vft,
          double &vfr,
          double &vtr,
          IonPar &p)    //
//  Вычисление профиля ионизации и его производных
//
//VGG
{
double X,Y,Z,dX,dY,dZ,x,y;
double sF,cF,sT,cT,vx,vy,vxx,vxy,vyy,vxz,vyz;
double dxf,dyf,dxt,dyt,cdf,sdf;
double dxff,dxtt,dxft,dyff,dytt,dyft;
long keyX,keyY,keyZ,key;
long ix,iy,iz;

sF=sin(fi);
cF=cos(fi);
sT=sin(teta);
cT=cos(teta);
X=r*sT*cF;
Y=r*sT*sF;
Z=r*cT;
dX=X-iri_3dbase->X0;
dY=Y-iri_3dbase->Y0;
dZ=Z-iri_3dbase->Z0;
x=dY*iri_3dbase->cFi0-dX*iri_3dbase->sFi0;
y=dZ*iri_3dbase->sTeta0-dX*iri_3dbase->cTeta0*iri_3dbase->cFi0-dY*iri_3dbase->cTeta0*iri_3dbase->sFi0;

iri_3dbase->spcub(x,y,r-iri_3dbase->r0,v,vx,vy,vr,vxx,vyy,vrr,vxy,vxz,vyz,keyX,keyY,keyZ,ix,iy,iz);
p.HmF2=(iri_3dbase->gethmF2(ix,iy))*.01+R0;
p.HmF1=(iri_3dbase->gethmF1(ix,iy))*.01+R0;
p.HmE =(iri_3dbase->gethmE(ix,iy))*.01+R0;
p.HmEs=(iri_3dbase->gethmEs(ix,iy))*.01+R0;

key=fabs(keyX)+fabs(keyY);

cdf=cF*iri_3dbase->cFi0+sF*iri_3dbase->sFi0;
//cdf=cF*iri_3dbase->cFi0-sF*iri_3dbase->sFi0; //old
sdf=sF*iri_3dbase->cFi0-cF*iri_3dbase->sFi0;
dxf=r*sT*cdf;
dyf=r*sT*iri_3dbase->cTeta0*sdf;
//dyf=r*sT*cT*sdf; //old
dxt=r*cT*sdf;
dyt=-r*(sT*iri_3dbase->sTeta0+cT*iri_3dbase->cTeta0*cdf);
dxff=-r*sT*sdf;
dxtt=dxff;
dyff=r*sT*(cF*iri_3dbase->cFi0-sF*iri_3dbase->sFi0)*iri_3dbase->cTeta0;
dytt=dyff-r*cT*iri_3dbase->sTeta0;
dxft=r*cT*cdf;
dyft=r*cT*sdf*iri_3dbase->cTeta0;

vfi=vx*dxf+vy*dyf;
vteta=vx*dxt+vy*dyt;

vff=vx*dxff+vxx*dxf*dxf+vyy*dyf*dyf+vy*dyff;
vtt=vx*dxtt+vxx*dxt*dxt+vyy*dyt*dyt+vy*dytt;
vft=vxx*dxf*dxt+vx*dxft+vyy*dyf*dyt+vy*dyft;
vfr=vxz*dxf+vyz*dyf;
vtr=vxz*dxt+vyz*dyt;

key=0;

return key;
}

int MyTrek::ionosf(double fi,     // сферические координаты расположения луча
          double teta,   //
          double r,      //
          double time,   // время с секундах, отсчитанное от момента основного профиля
          double &v,     // нормированный квадрат плазменной частоты
          double &vfi,   // его производные по fi, tets, r
          double &vteta, //
          double &vr,
          double &vt,    // производная v по времени
          double &vff,
          double &vtt,
          double &vrr,
          double &vft,
          double &vfr,
          double &vtr,
          IonPar &p)    //
//  Вычисление профиля ионизации и его производных
//
//VGG
{
double X,Y,Z,dX,dY,dZ,x,y;
double sF,cF,sT,cT,vx,vy,vxx,vxy,vyy,vxz,vyz;
double v1,vr1,vx1,vy1,vxx1,vrr1,vxy1,vyy1,vxz1,vyz1;
double v2,vr2,vx2,vy2,vxx2,vrr2,vxy2,vyy2,vxz2,vyz2;
double dxf,dyf,dxt,dyt,cdf,sdf;
double dxff,dxtt,dxft,dyff,dytt,dyft;
long keyX,keyY,keyZ,key;
long ix,iy,iz;
double t1=iri_3dbase->getTime();
double t2=iri_3dbase2->getTime();
double hEs1,hEs2,hE1,hE2,hF11,hF12,hF21,hF22;

if (t1>24.)
    t1-=25.;
if (t2>24.)
    t2-=25.;
t1*=3600.;
t2*=3600.;

sF=sin(fi);
cF=cos(fi);
sT=sin(teta);
cT=cos(teta);
X=r*sT*cF;
Y=r*sT*sF;
Z=r*cT;
dX=X-iri_3dbase->X0;
dY=Y-iri_3dbase->Y0;
dZ=Z-iri_3dbase->Z0;
x=dY*iri_3dbase->cFi0-dX*iri_3dbase->sFi0;
y=dZ*iri_3dbase->sTeta0-dX*iri_3dbase->cTeta0*iri_3dbase->cFi0-dY*iri_3dbase->cTeta0*iri_3dbase->sFi0;

iri_3dbase ->spcub(x,y,r-iri_3dbase->r0,v1,vx1,vy1,vr1,vxx1,vyy1,vrr1,vxy1,vxz1,vyz1,keyX,keyY,keyZ,ix,iy,iz);
hF21=iri_3dbase->gethmF2(ix,iy);
hF11=iri_3dbase->gethmF1(ix,iy);
hE1 =iri_3dbase->gethmE(ix,iy);
hEs1=iri_3dbase->gethmEs(ix,iy);
iri_3dbase2->spcub(x,y,r-iri_3dbase->r0,v2,vx2,vy2,vr2,vxx2,vyy2,vrr2,vxy2,vxz2,vyz2,keyX,keyY,keyZ,ix,iy,iz);
hF22=iri_3dbase2->gethmF2(ix,iy);
hF12=iri_3dbase2->gethmF1(ix,iy);
hE2 =iri_3dbase2->gethmE(ix,iy);
hEs2=iri_3dbase2->gethmEs(ix,iy);
p.HmF2=(hF21+(time-t1)*(hF22-hF21)/(t2-t1))*.01+R0;
p.HmF1=(hF11+(time-t1)*(hF12-hF11)/(t2-t1))*.01+R0;
p.HmE =(hE1+(time-t1)*(hE2-hE1)/(t2-t1))*.01+R0;
p.HmEs=(hEs1+(time-t1)*(hEs2-hEs1)/(t2-t1))*.01+R0;

//printf("\nHmF2=%f  HmF1=%f  HmE=%f ix=%d  iy=%d",HmF2-R0,HmF1-R0,HmE-R0,iri_3dbase->getIx(),iri_3dbase->getIy());

vt=(v2-v1)/(t2-t1);
v=(time-t1)*vt+v1;
if (v<.0)
{
    v=vx=vy=vr=vxx=vyy=vrr=vxy=vxz=vyz=.0;
}
else
{
    vx=(time-t1)*(vx2-vx1)/(t2-t1)+vx1;
    vy=(time-t1)*(vy2-vy1)/(t2-t1)+vy1;
    vr=(time-t1)*(vr2-vr1)/(t2-t1)+vr1;
    vxx=(time-t1)*(vxx2-vxx1)/(t2-t1)+vxx1;
    vyy=(time-t1)*(vyy2-vyy1)/(t2-t1)+vyy1;
    vrr=(time-t1)*(vrr2-vrr1)/(t2-t1)+vrr1;
    vxy=(time-t1)*(vxy2-vxy1)/(t2-t1)+vxy1;
    vxz=(time-t1)*(vxz2-vxz1)/(t2-t1)+vxz1;
    vyz=(time-t1)*(vyz2-vyz1)/(t2-t1)+vyz1;
}

//printf("\ntime=%f t1=%f t2=%f HmF2=%f fp=%f",time,t1,t2,HmF2-R0,sqrt(v));

key=fabs(keyX)+fabs(keyY);

cdf=cF*iri_3dbase->cFi0+sF*iri_3dbase->sFi0;
//cdf=cF*iri_3dbase->cFi0-sF*iri_3dbase->sFi0; //old
sdf=sF*iri_3dbase->cFi0-cF*iri_3dbase->sFi0;
dxf=r*sT*cdf;
dyf=r*sT*iri_3dbase->cTeta0*sdf;
//dyf=r*sT*cT*sdf; //old
dxt=r*cT*sdf;
dyt=-r*(sT*iri_3dbase->sTeta0+cT*iri_3dbase->cTeta0*cdf);
dxff=-r*sT*sdf;
dxtt=dxff;
dyff=r*sT*(cF*iri_3dbase->cFi0-sF*iri_3dbase->sFi0)*iri_3dbase->cTeta0;
dytt=dyff-r*cT*iri_3dbase->sTeta0;
dxft=r*cT*cdf;
dyft=r*cT*sdf*iri_3dbase->cTeta0;

vfi=vx*dxf+vy*dyf;
vteta=vx*dxt+vy*dyt;

vff=vx*dxff+vxx*dxf*dxf+vyy*dyf*dyf+vy*dyff;
vtt=vx*dxtt+vxx*dxt*dxt+vyy*dyt*dyt+vy*dytt;
vft=vxx*dxf*dxt+vx*dxft+vyy*dyf*dyt+vy*dyft;
vfr=vxz*dxf+vyz*dyf;
vtr=vxz*dxt+vyz*dyt;

key=0;

return key;
}

int MyTrek::nuprof(double fi,
            double teta,
            double r,
            double &nu)
//  nu-h profile in the point with spher.koord. (fi,theta,r)
//
{
  double X,Y,Z,dX,dY,dZ,x,y;
  double sF,cF,sT,cT;
  long keyX,keyY,keyZ,key;
//  double nu_test;
//  double test;
  long ix,iy,iz;

  sF=sin(fi);
  cF=cos(fi);
  sT=sin(teta);
  cT=cos(teta);
  X=r*sT*cF;
  Y=r*sT*sF;
  Z=r*cT;
  dX=X-iri_3dbase->X0;
  dY=Y-iri_3dbase->Y0;
  dZ=Z-iri_3dbase->Z0;
  x=dY*iri_3dbase->cFi0-dX*iri_3dbase->sFi0;
  y=dZ*iri_3dbase->sTeta0-dX*iri_3dbase->cTeta0*iri_3dbase->cFi0-dY*iri_3dbase->cTeta0*iri_3dbase->sFi0;

  iri_3dbase->nu->spcub(x,y,r-iri_3dbase->r0,nu,keyX,keyY,keyZ,ix,iy,iz);
  key=fabs(keyX)+fabs(keyY);

//  nu_test = iri_3dbase->nu->getCarrier(10,10,140);
//  cout<<" "<<nu_test;

//  test = iri_3dbase->getCarrier(7,7,0);    cout<<" "<<test;
//  test = iri_3dbase->getCarrier(7,7,90);  cout<<" "<<test;

  key=0;

  return key;
}

int MyTrek::nuprof(double fi,
            double teta,
            double r,
            double time,
            double &nu)
//  nu-h profile in the point with spher.koord. (fi,theta,r) and time point time
//
{
  double X,Y,Z,dX,dY,dZ,x,y;
  double sF,cF,sT,cT;
  long keyX,keyY,keyZ,key;
  double n1,n2,nt;
  double t1=iri_3dbase->getTime();
  double t2=iri_3dbase2->getTime();
  long ix,iy,iz;

  if (t1>24.)
      t1-=25.;
  if (t2>24.)
      t2-=25.;
  t1*=3600.;
  t2*=3600.;

  sF=sin(fi);
  cF=cos(fi);
  sT=sin(teta);
  cT=cos(teta);
  X=r*sT*cF;
  Y=r*sT*sF;
  Z=r*cT;
  dX=X-iri_3dbase->X0;
  dY=Y-iri_3dbase->Y0;
  dZ=Z-iri_3dbase->Z0;
  x=dY*iri_3dbase->cFi0-dX*iri_3dbase->sFi0;
  y=dZ*iri_3dbase->sTeta0-dX*iri_3dbase->cTeta0*iri_3dbase->cFi0-dY*iri_3dbase->cTeta0*iri_3dbase->sFi0;

  iri_3dbase->nu->spcub(x,y,r-iri_3dbase->r0,n1,keyX,keyY,keyZ,ix,iy,iz);
  iri_3dbase2->nu->spcub(x,y,r-iri_3dbase->r0,n2,keyX,keyY,keyZ,ix,iy,iz);
  
  //printf("\n n1=%12.5e  n2=%12.5e",n2,n2);

  key=fabs(keyX)+fabs(keyY);

  nt=(n2-n1)/(t2-t1);
  nu=(time-t1)*nt+n1;
  
  key=0;

  return key;
}



