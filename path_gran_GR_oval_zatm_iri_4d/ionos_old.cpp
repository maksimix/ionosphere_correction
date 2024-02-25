#include <math.h>
#include "paths.h"

int ionos(double f,
	  double t,
	  double r,
	  int    n)
/***************************************************************/
/*                                                             */
/*	זץמכדיס קש‏יףלסופ תמב‏ומיו כקבהעבפב נלבתםוממןך         */
/*      ‏בףפןפש	י וחן נעןיתBןהמשט נן הוכבעפןקשם	כןןעהימבפבם    */
/*	הלס םןהולוך יןמןףזועש ןניףבממשט	י קקוהוממשט ק inions   */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
   double rd[3],rexp,r1,g,r2,r3,drtf[3],g2,dr,df,dt,
          tid0,rc[3],rff,rtt,rrr,rft,rfr,rtr,fo;
   double vt=.0;
   double nu=.0;

   int i;

/*--------------------------------------------------------------*/

   dr=r-R0;
   df=f-fi0;
   dt=t-teta0;

   if (r<h0)
     return 1;
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
               ionosf(f,t,100.*r,tim,v,vp[0],vp[1],vp[2],vt,vpp[0][0],vpp[1][1],vpp[2][2],
                      vpp[0][1],vpp[0][2],vpp[1][2]);
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
               ionosf(f,t,100.*r,tim,v,vp[0],vp[1],vp[2],vt);
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

   if (keyOval)
   {
       return 0;

       double cos_ro=st*steta_m0*cos(f-fi_m0)+ct*cteta_m0;
       double ro=R0*acos(cos_ro);
       double x=ro-ro_m;
       //printf("\nro=%f ro_m=%f x=%f lambd1=%f lambd2=%f",ro,ro_m,x,lambd1,lambd2);
       double k=1.-amp_proval*(tanh((x-lambd1)/lambd1)-tanh((x+lambd2)/lambd2));
       v*=k;
       double dkx,ch1,ch2,dkfi,dkteta;
       ch1=cosh((x-lambd1)/lambd1);
       ch2=cosh((x+lambd2)/lambd2);
       dkx=-amp_proval*(1./(lambd1*ch1*ch1)-1./(lambd2*ch2*ch2));
       dkfi  = dkx*R0*sf*steta_m0*sin(f-fi_m0)/sqrt(1.-cos_ro*cos_ro);
       dkteta=-dkx*R0*(ct*steta_m0*cos(f-fi_m0)-st*cteta_m0)/sqrt(1.-cos_ro*cos_ro);
       vp[1]*=dkfi;
       vp[2]*=dkteta;
   }

     return 0;

}  /* ionos */