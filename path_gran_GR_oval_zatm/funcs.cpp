#include <math.h>
#include "paths.h"

int ionos(double f, double t, double r,
	  int    n);

void magfis(double f, double t, double r,
	    double h[3], double dh[3][3], double dh2[3][3][3]);

int funcs(double x,
	  double *y,
	  double *f,
	  int    n)
/*******************************************************************/
/*                                                                 */
/* ףזועי‏וףכיך קבעיבמפ נעןחעבםםש נןףפעןומיס לץ‏וקןך פעבוכפןעיי     */
/*                                                                 */
/* זץמכדיס קש‏יףלסופ תמב‏ומיס נעבקשט ‏בףפוך היזז. ץעבקמומיך לץ‏ב   */
/*                                                                 */
/* x  - ־ֵÚֱ׳ֹ׃ֱֹֽׁ ׀ֵֵֵֽׂ־־ֱׁ;                                    */
/* *y - ־ֱֲֿׂ ּױÞֵ׳Ùָ ֶױ־ֳֹֻÊ;                                     */
/* *f - Ú־ֱÞֵ־ֹׁ ׀ֱׂ׳Ùָ Þֱ׃װֵÊ ִֶֶֹ. ױֱׂ׳־ֵ־ֹÊ ּױÞֱ.               */
/*                                                                 */
/*VGG                                                              */
/*******************************************************************/
{
  double r,vovr,dmca,dmu,aim,vsq,usq,dhh,usa2,sq,
         s2,a,b,re,ab,ca,dov,ov2,ca2,t,dmvv,dmcc,dmvc,
         amy2,pa,pd,va,vd,ha,hd,dmuv,dmuc,
         dana,dand,hf,ht,hr,sq2,dmuu;

  double dca[3]    ={.0,.0,.0},
         du[3]     ={.0,.0,.0},
         du2[3][3] ={.0,.0,.0,.0,.0,.0,.0,.0,.0},
         dca2[3][3]={.0,.0,.0,.0,.0,.0,.0,.0,.0},
         dt[3]     ={.0,.0,.0},
         ua=.0,
         ud=.0,
         cosa=.0,
         cosd=.0;

  int  i;

  sf=sin(y[0]);
  cf=cos(y[0]);
  st=sin(y[1]);
  ct=cos(y[1]);

  if (ionos(y[0],y[1],y[2],n)) return 1;

  ov=1.-v;

  if (ov<=0) return 1;

  if (ivar)    /* םןהולר חלןגבלרמןחן חוןםבחמיפמןחן נןלס */
  {
      magfis(y[0],y[1],y[2],h,dh,dh2);

      t=sqrt(h[0]*h[0]+h[1]*h[1]+h[2]*h[2]);
      fh=2.79*t;

      h[0]=h[0]/t;
      h[1]=h[1]/t;
      h[2]=h[2]/t;
      r=15.5682/fr2;

      for(i=0; i<3; i++)
      {
	  dt[i]=h[0]*dh[0][i]+h[1]*dh[1][i]+h[2]*dh[2][i];
	  du[i]=5.58*fh*dt[i]/fr2;
      }

      dhh=dh[0][0]*dh[0][0]+dh[1][0]*dh[1][0]+dh[2][0]*dh[2][0];
      du2[0][0]=r*(dhh+t*(h[0]*dh2[0][0][0]+h[1]*dh2[1][0][0]+
		h[2]*dh2[2][0][0]));
      dh2[0][0][0]=(dh2[0][0][0]-(dh[0][0]*dt[0]*2.+h[0]*dhh-
		   3.*h[0]*dt[0]*dt[0])/t)/t;
      dh2[1][0][0]=(dh2[1][0][0]-(dh[1][0]*dt[0]*2.+h[1]*dhh-
		   3.*h[1]*dt[0]*dt[0])/t)/t;
      dh2[2][0][0]=(dh2[2][0][0]-(dh[2][0]*dt[0]*2.+h[2]*dhh-
		   3.*h[2]*dt[0]*dt[0])/t)/t;

      dhh=dh[0][0]*dh[0][1]+dh[1][0]*dh[1][1]+dh[2][0]*dh[2][1];
      du2[0][1]=r*(dhh+t*(h[0]*dh2[0][0][1]+h[1]*dh2[1][0][1]
		+h[2]*dh2[2][0][1]));
      dh2[0][0][1]=(dh2[0][0][1]-(dh[0][0]*dt[1]+dh[0][1]*dt[0]+
		   h[0]*dhh-3.*h[0]*dt[0]*dt[1])/t)/t;
      dh2[1][0][1]=(dh2[1][0][1]-(dh[1][0]*dt[1]+dh[1][1]*dt[0]+
		   h[1]*dhh-3.*h[1]*dt[0]*dt[1])/t)/t;
      dh2[2][0][1]=(dh2[2][0][1]-(dh[2][0]*dt[1]+dh[2][1]*dt[0]+
		   h[2]*dhh-3.*h[2]*dt[0]*dt[1])/t)/t;

      dhh=dh[0][0]*dh[0][2]+dh[1][0]*dh[1][2]+dh[2][0]*dh[2][2];
      du2[0][2]=r*(dhh+t*(h[0]*dh2[0][0][2]+h[1]*dh2[1][0][2]
		+h[2]*dh2[2][0][2]));
      dh2[0][0][2]=(dh2[0][0][2]-(dh[0][0]*dt[2]+dh[0][2]*dt[0]+
		   h[0]*dhh-3.*h[0]*dt[0]*dt[2])/t)/t;
      dh2[1][0][2]=(dh2[1][0][2]-(dh[1][0]*dt[2]+dh[1][2]*dt[0]+
		   h[1]*dhh-3.*h[1]*dt[0]*dt[2])/t)/t;
      dh2[2][0][2]=(dh2[2][0][2]-(dh[2][0]*dt[2]+dh[2][2]*dt[0]+
		   h[2]*dhh-3.*h[2]*dt[0]*dt[2])/t)/t;

      dhh=dh[0][1]*dh[0][1]+dh[1][1]*dh[1][1]+dh[2][1]*dh[2][1];
      du2[1][1]=r*(dhh+t*(h[0]*dh2[0][1][1]+h[1]*dh2[1][1][1]
		+h[2]*dh2[2][1][1]));
      dh2[0][1][1]=(dh2[0][1][1]-(dh[0][1]*dt[1]*2.+
		   h[0]*dhh-3.*h[0]*dt[1]*dt[1])/t)/t;
      dh2[1][1][1]=(dh2[1][1][1]-(dh[1][1]*dt[1]*2.+
		   h[1]*dhh-3.*h[1]*dt[1]*dt[1])/t)/t;
      dh2[2][1][1]=(dh2[2][1][1]-(dh[2][1]*dt[1]*2.+
		   h[2]*dhh-3.*h[2]*dt[1]*dt[1])/t)/t;

      dhh=dh[0][1]*dh[0][2]+dh[1][1]*dh[1][2]+dh[2][1]*dh[2][2];
      du2[1][2]=r*(dhh+t*(h[0]*dh2[0][1][2]+h[1]*dh2[1][1][2]
		+h[2]*dh2[2][1][2]));
      dh2[0][1][2]=(dh2[0][1][2]-(dh[0][1]*dt[2]+dh[0][2]*dt[1]+
		   h[0]*dhh-3.*h[0]*dt[1]*dt[2])/t)/t;
      dh2[1][1][2]=(dh2[1][1][2]-(dh[1][1]*dt[2]+dh[1][2]*dt[1]+
		   h[1]*dhh-3.*h[1]*dt[1]*dt[2])/t)/t;
      dh2[2][1][2]=(dh2[2][1][2]-(dh[2][1]*dt[2]+dh[2][2]*dt[1]+
		   h[2]*dhh-3.*h[2]*dt[1]*dt[2])/t)/t;

      dhh=dh[0][2]*dh[0][2]+dh[1][2]*dh[1][2]+dh[2][2]*dh[2][2];
      du2[2][2]=r*(dhh+t*(h[0]*dh2[0][2][2]+h[1]*dh2[1][2][2]
		+h[2]*dh2[2][2][2]));
      dh2[0][2][2]=(dh2[0][2][2]-(dh[0][2]*dt[2]*2.+
		   h[0]*dhh-3.*h[0]*dt[2]*dt[2])/t)/t;
      dh2[1][2][2]=(dh2[1][2][2]-(dh[1][2]*dt[2]*2.+
		   h[1]*dhh-3.*h[1]*dt[2]*dt[2])/t)/t;
      dh2[2][2][2]=(dh2[2][2][2]-(dh[2][2]*dt[2]*2.+
		   h[2]*dhh-3.*h[2]*dt[2]*dt[2])/t)/t;
      dh2[0][1][0]=dh2[0][0][1];
      dh2[1][1][0]=dh2[1][0][1];
      dh2[2][1][0]=dh2[2][0][1];
      dh2[0][2][0]=dh2[0][0][2];
      dh2[1][2][0]=dh2[1][0][2];
      dh2[2][2][0]=dh2[2][0][2];
      dh2[0][2][1]=dh2[0][1][2];
      dh2[1][2][1]=dh2[1][1][2];
      dh2[2][2][1]=dh2[2][1][2];

      dh[0][0]=(dh[0][0]-h[0]*dt[0])/t;
      dh[0][1]=(dh[0][1]-h[0]*dt[1])/t;
      dh[0][2]=(dh[0][2]-h[0]*dt[2])/t;
      dh[1][0]=(dh[1][0]-h[1]*dt[0])/t;
      dh[1][1]=(dh[1][1]-h[1]*dt[1])/t;
      dh[1][2]=(dh[1][2]-h[1]*dt[2])/t;
      dh[2][0]=(dh[2][0]-h[2]*dt[0])/t;
      dh[2][1]=(dh[2][1]-h[2]*dt[1])/t;
      dh[2][2]=(dh[2][2]-h[2]*dt[2])/t;
  }

  u1=fh/fr;
  u=u1*u1;

  ov2=ov*ov;
  dov=2.*ov;
  ak=sqrt(y[3]*y[3]+y[4]*y[4]+y[5]*y[5]);
  ca=(h[0]*y[3]+h[1]*y[4]+h[2]*y[5])/ak;
  ca2=ca*ca;
  sa2=1.-ca2;
  usa2=u*sa2;
  r=u*dov*dov*ca2;
  sq=sqrt(usa2*usa2+r);

  if (iox)
  {
      sq=-sq;
      r=dov-usa2+sq;
  }
  else
      r=dov+r/(sq+usa2);

  vovr=v*dov/r;
  amy2=1.-vovr;

  if (amy2<=.0) return 1;

  amy=sqrt(amy2);

  y[3] *=amy/ak;
  y[4] *=amy/ak;
  y[5] *=amy/ak;

  ak=amy;
  usq=1.+u*dov*ca2/sq;
  vsq=1.+(ov*dov-usa2)/sq;
  dmv=-(ov-v+vovr*usq)/r;
  dmca=ca*u*vovr*vsq/r;
  dmu=.5*vovr*((usa2*sa2+ov*dov*ca2)/sq-sa2)/r;
  anorm=amy2-2.*(v*dmv+u*dmu);
  dmca0=dmca;

  hf=(h[0]-y[3]*ca/ak)/ak;
  ht=(h[1]-y[4]*ca/ak)/ak;
  hr=(h[2]-y[5]*ca/ak)/ak;

  if (ivar)
  {
      dca[0]=(y[3]*dh[0][0]+y[4]*dh[1][0]+y[5]*dh[2][0])/ak;
      dca[1]=(y[3]*dh[0][1]+y[4]*dh[1][1]+y[5]*dh[2][1])/ak;
      dca[2]=(y[3]*dh[0][2]+y[4]*dh[1][2]+y[5]*dh[2][2])/ak;
      dmrtf[0]=dmv*vp[0]+dmu*du[0]+dmca*dca[0];
      dmrtf[1]=dmv*vp[1]+dmu*du[1]+dmca*dca[1];
      dmrtf[2]=dmv*vp[2]+dmu*du[2]+dmca*dca[2];
  }
  else
  {
      dmrtf[0]=dmv*vp[0];
      dmrtf[1]=dmv*vp[1];
      dmrtf[2]=dmv*vp[2];
  }

  f[0]=(y[3]-dmca*hf)/(y[2]*st);
  f[1]=(y[4]-dmca*ht)/y[2];
  f[2]=y[5]-dmca*hr;
  f[3]=(dmrtf[0]-y[3]*st*f[2]-y[2]*ct*y[3]*f[1])/(y[2]*st);
  f[4]=(dmrtf[1]-y[4]*f[2]+y[2]*ct*y[3]*f[0])/y[2];
  f[5]=dmrtf[2]+y[4]*f[1]+st*y[3]*f[0];

  if(n>6) f[6]=dmv*dvt/anorm;

  if(n>7)
  {
      s2=s*s;
      a=usa2*usa2+4.*u*(ov2-s2)*ca2;
      b=-8.*u*s*ov*ca2;
      a=sqrt(.5*fabs(a+sqrt(a*a+b*b)));
      b=.5*b/a;
      re=2.*(ov-s2)-usa2;
      aim=-2.*s*(2.-v);

      if (iox)
      {
	  re  -=a;
	  aim -=b;
      }
      else
      {
	  re  +=a;
	  aim +=b;
      }

      ab=re*re+aim*aim;
      a=1.-2.*v*(re*ov-s*aim)/ab;
      b=2.*v*(s*re+ov*aim)/ab;
      re=sqrt(.5*fabs(a+sqrt(a*a+b*b)));

      f[7]=amy*b/(re*anorm);
  }

  if (n>8)
  {
      /* ‏בףפר, ףןןפקופףפקץא‎בס ץעבקמומיסם הלס נעןיתקןהמשט  */
      /* זבתןקשט כןןעהימבפ נן לןכבלרמשם לץ‏וקשם כןןעהימבפבם */

      sq2=sq*sq;
      va=vp[0]*y[8]+vp[1]*y[9]+vp[2]*y[10];
      vd=vp[0]*y[14]+vp[1]*y[15]+vp[2]*y[16];
      pa=y[3]*y[11]+y[4]*y[12]+y[5]*y[13];
      pd=y[3]*y[17]+y[4]*y[18]+y[5]*y[19];
      ha=hf*y[11]+ht*y[12]+hr*y[13];
      hd=hf*y[17]+ht*y[18]+hr*y[19];

      if (ivar)
      {
	  ua=du[0]*y[8]+du[1]*y[9]+du[2]*y[10];
	  ud=du[0]*y[14]+du[1]*y[15]+du[2]*y[16];
	  cosa=dca[0]*y[8]+dca[1]*y[9]+dca[2]*y[10];
	  cosd=dca[0]*y[14]+dca[1]*y[15]+dca[2]*y[16];
	  dca2[0][0]=(y[3]*dh2[0][0][0]+y[4]*dh2[1][0][0]+
		      y[5]*dh2[2][0][0])/ak;
	  dca2[0][1]=(y[3]*dh2[0][0][1]+y[4]*dh2[1][0][1]+
		      y[5]*dh2[2][0][1])/ak;
	  dca2[0][2]=(y[3]*dh2[0][0][2]+y[4]*dh2[1][0][2]+
		      y[5]*dh2[2][0][2])/ak;
	  dca2[1][1]=(y[3]*dh2[0][1][1]+y[4]*dh2[1][1][1]+
		      y[5]*dh2[2][1][1])/ak;
	  dca2[1][2]=(y[3]*dh2[0][1][2]+y[4]*dh2[1][1][2]+
		      y[5]*dh2[2][1][2])/ak;
	  dca2[2][2]=(y[3]*dh2[0][2][2]+y[4]*dh2[1][2][2]+
		      y[5]*dh2[2][2][2])/ak;
	  dca2[1][0]=dca2[0][1];
	  dca2[2][0]=dca2[0][2];
	  dca2[2][1]=dca2[1][2];
      }

      sq2=sq*sq;
      a=(usa2*sa2+dov*ov*ca2)/sq;
      b=a-sa2;
      dmvv=2.*(1.+2.*usq*dmv+vovr*usa2*usa2*u*ca2/(sq*sq2))/r;
      dmcc=vovr*u*u*amy2*(usa2*(1.+ca2)/sq2-2.*ca2*(1.+
	   (dov*(ov-v)-usa2)/sq)/r)/sq;
      dmvc=2.*u*ca*((ov-v)*amy2+2.*vovr*(ov*u*ca2*(2.*ov2-
	   usa2)/sq2+amy2*usq-ov))/(r*sq);
      dmuv=((ov-v+2.*vovr*usq)*b-8.*v*u*ov2*ov2*ca2*ca2/(sq2*sq))/r*r;
      dmuc=vovr*ca*(amy2-u*amy2*(b/r+a/sq)+2.*u*dmu)/sq;
      dmuu=-2.*vovr*(b*b/r+2.*ov2*ov2*ca2*ca2/(sq2*sq))/r;

      a=ha-pa*ca/amy2;
      b=hd-pd*ca/amy2;

      if (ivar)
      {
            dana=2.*((ha+cosa)*(dmca-dmvc*v-dmuc*u)-va*(dmvv*v+dmuv*u)-
                 ua*(dmuu*u+dmuv*v));
            dand=2.*((hd+cosd)*(dmca-dmvc*v-dmuc*u)-vd*(dmvv*v+dmuv*u)-
                 ud*(dmuu*u+dmuv*v));
            f[8]=(y[11]-dmcc*hf*ha+dmca*(y[3]*a+hf*pa+ca*y[11])/amy2-
                 hf*(dmcc*cosa+dmvc*va+dmuc*ua)-dmca*(dh[0][0]*y[8]+dh[0][1]*y[9]+
                 dh[0][2]*y[10]-y[3]*cosa/ak)/ak-(y[10]*st+y[2]*ct*y[9])*f[0])
                 /(y[2]*st);
            f[14]=(y[17]-dmcc*hf*hd+dmca*(y[3]*b+hf*pd+ca*y[17])/amy2-
                  hf*(dmcc*cosd+dmvc*vd+dmuc*ud)-dmca*(dh[0][0]*y[14]+dh[0][1]*y[15]+
                  dh[0][2]*y[16]-y[3]*cosd/ak)/ak-(y[16]*st+y[2]*ct*y[15])*f[0])
                  /(y[2]*st);
            f[9]=(y[12]-dmcc*ht*ha+dmca*(y[4]*a+ht*pa+ca*y[12])/amy2-
                 ht*(dmcc*cosa+dmvc*va+dmuc*ua)-dmca*(dh[1][0]*y[8]+dh[1][1]*y[9]+
                 dh[1][2]*y[10]-y[4]*cosa/ak)/ak-y[10]*f[1])/y[2];
            f[15]=(y[18]-dmcc*ht*hd+dmca*(y[4]*b+ht*pd+ca*y[18])/amy2-
                  ht*(dmcc*cosd+dmvc*vd+dmuc*ud)-dmca*(dh[1][0]*y[14]+
                  dh[1][1]*y[15]+dh[1][2]*y[16]-y[4]*cosd/ak)/ak-y[16]*f[1])/y[2];
            f[10]=y[13]-dmcc*hr*ha+dmca*(y[5]*a+hr*pa+ca*y[13])/amy2-
                  hr*(dmcc*cosa+dmvc*va+dmuc*ua)-dmca*(dh[2][0]*y[8]+dh[2][1]*y[9]+
                  dh[2][2]*y[10]-y[5]*cosa/ak)/ak;
            f[16]=y[19]-dmcc*hr*hd+dmca*(y[5]*b+hr*pd+ca*y[19])/amy2-
                  hr*(dmcc*cosd+dmvc*vd+dmuc*ud)-dmca*(dh[2][0]*y[14]+
                  dh[2][1]*y[15]+dh[2][2]*y[16]-y[5]*cosd/ak)/ak;
            f[11]=(dmv*(vpp[0][0]*y[8]+vpp[0][1]*y[9]+vpp[0][2]*y[10])+
                  dmca*(dca2[0][0]*y[8]+dca2[0][1]*y[9]+dca2[0][2]*y[10])+
                  dmu*(du2[0][0]*y[8]+du2[0][1]*y[9]+du2[0][2]*y[10])+
                  dmvv*vp[0]*va+dmuu*du[0]*ua+dmcc*dca[0]*cosa+dmuv*(vp[0]*ua+
                  du[0]*va)+dmvc*(vp[0]*cosa+dca[0]*va)+dmuc*(du[0]*cosa+
                  dca[0]*ua)+ha*(dmcc*dca[0]+dmvc*vp[0]+dmuc*du[0])+
                  dmca*(dh[0][0]*y[11]+dh[1][0]*y[12]+dh[2][0]*y[13]-
                  dca[0]*pa/ak)/ak-st*y[11]*f[2]-y[3]*ct*y[9]*f[2]-
                  y[3]*st*f[10]-y[3]*ct*y[10]*f[1]+y[2]*y[3]*st*y[9]*f[1]-
                  y[2]*ct*y[11]*f[1]-y[2]*y[3]*ct*f[9]-(st*y[10]+
                  y[2]*ct*y[9])*f[3])/(y[2]*st);
            f[17]=(dmv*(vpp[0][0]*y[14]+vpp[0][1]*y[15]+vpp[0][2]*y[16])+
                  dmca*(dca2[0][0]*y[14]+dca2[0][1]*y[15]+dca2[0][2]*y[16])+
                  dmu*(du2[0][0]*y[14]+du2[0][1]*y[15]+du2[0][2]*y[16])+
                  dmvv*vp[0]*vd+dmuu*du[0]*ud+dmcc*dca[0]*cosd+dmuv*(vp[0]*ud+
                  du[0]*vd)+dmvc*(vp[0]*cosd+dca[0]*vd)+dmuc*(du[0]*cosd+
                  dca[0]*ud)+hd*(dmcc*dca[0]+dmvc*vp[0]+dmuc*du[0])+
                  dmca*(dh[0][0]*y[17]+dh[1][0]*y[18]+dh[2][0]*y[19]-
                  dca[0]*pd/ak)/ak-st*y[17]*f[2]-y[3]*ct*y[15]*f[2]-
                  y[3]*st*f[16]-y[3]*ct*y[16]*f[1]+y[2]*y[3]*st*y[15]*f[1]-
                  y[2]*ct*y[17]*f[1]-y[2]*y[3]*ct*f[15]-(st*y[16]+
                  y[2]*ct*y[15])*f[3])/(y[2]*st);
            f[12]=(dmv*(vpp[1][0]*y[8]+vpp[1][1]*y[9]+vpp[1][2]*y[10])+
                  dmca*(dca2[1][0]*y[8]+dca2[1][1]*y[9]+dca2[1][2]*y[10])+
                  dmu*(du2[1][0]*y[8]+du2[1][1]*y[9]+du2[1][2]*y[10])+
                  dmvv*vp[1]*va+dmuu*du[1]*ua+dmcc*dca[1]*cosa+dmuv*(vp[1]*ua+
                  du[1]*va)+dmvc*(vp[1]*cosa+dca[1]*va)+dmuc*(du[1]*cosa+
                  dca[1]*ua)+ha*(dmcc*dca[1]+dmvc*vp[1]+dmuc*du[1])+
                  dmca*(dh[0][1]*y[11]+dh[1][1]*y[12]+dh[2][1]*y[13]-
                  dca[1]*pa/ak)/ak-y[12]*f[2]-y[4]*f[10]+y[3]*ct*y[10]*f[0]+
                  y[2]*ct*y[11]*f[0]-y[2]*y[3]*st*y[9]*f[0]+
                  y[2]*y[3]*ct*f[8]-y[10]*f[4])/y[2];
            f[18]=(dmv*(vpp[1][0]*y[14]+vpp[1][1]*y[15]+vpp[1][2]*y[16])+
                  dmca*(dca2[1][0]*y[14]+dca2[1][1]*y[15]+dca2[1][2]*y[16])+
                  dmu*(du2[1][0]*y[14]+du2[1][1]*y[15]+du2[1][2]*y[16])+
                  dmvv*vp[1]*vd+dmuu*du[1]*ud+dmcc*dca[1]*cosd+dmuv*(vp[1]*ud+
                  du[1]*vd)+dmvc*(vp[1]*cosd+dca[1]*vd)+dmuc*(du[1]*cosd+
                  dca[1]*ud)+hd*(dmcc*dca[1]+dmvc*vp[1]+dmuc*du[1])+
                  dmca*(dh[0][1]*y[17]+dh[1][1]*y[18]+dh[2][1]*y[19]-
                  dca[1]*pd/ak)/ak-y[18]*f[2]-y[4]*f[16]+y[3]*ct*y[16]*f[0]+
                  y[2]*ct*y[17]*f[0]-y[2]*y[3]*st*y[15]*f[0]+
                  y[2]*y[3]*ct*f[14]-y[16]*f[4])/y[2];
            f[13]=dmv*(vpp[2][0]*y[8]+vpp[2][1]*y[9]+vpp[2][2]*y[10])+
                  dmca*(dca2[2][0]*y[8]+dca2[2][1]*y[9]+dca2[2][2]*y[10])+
                  dmu*(du2[2][0]*y[8]+du2[2][1]*y[9]+du2[2][2]*y[10])+
                  dmvv*vp[2]*va+dmuu*du[2]*ua+dmcc*dca[2]*cosa+dmuv*(vp[2]*ua+
                  du[2]*va)+dmvc*(vp[2]*cosa+dca[2]*va)+dmuc*(du[2]*cosa+
                  dca[2]*ua)+ha*(dmcc*dca[2]+dmvc*vp[2]+dmuc*du[2])+
                  dmca*(dh[0][2]*y[11]+dh[1][2]*y[12]+dh[2][2]*y[13]-
                  dca[2]*pa/ak)/ak+y[12]*f[1]+y[4]*f[9]+st*y[11]*f[0]+
                  y[3]*ct*y[9]*f[0]+y[3]*st*f[8];
            f[19]=dmv*(vpp[2][0]*y[14]+vpp[2][1]*y[15]+vpp[2][2]*y[16])+
                  dmca*(dca2[2][0]*y[14]+dca2[2][1]*y[15]+dca2[2][2]*y[16])+
                  dmu*(du2[2][0]*y[14]+du2[2][1]*y[15]+du2[2][2]*y[16])+
                  dmvv*vp[2]*vd+dmuu*du[2]*ud+dmcc*dca[2]*cosd+dmuv*(vp[2]*ud+
                  du[2]*vd)+dmvc*(vp[2]*cosd+dca[2]*vd)+dmuc*(du[2]*cosd+
                  dca[2]*ud)+hd*(dmcc*dca[2]+dmvc*vp[2]+dmuc*du[2])+
                  dmca*(dh[0][2]*y[17]+dh[1][2]*y[18]+dh[2][2]*y[19]-
                  dca[2]*pd/ak)/ak+y[18]*f[1]+y[4]*f[15]+st*y[17]*f[0]+
                  y[3]*ct*y[15]*f[0]+y[3]*f[14];
      }
      else
      {
            dana=2.*(ha*(dmca-dmvc*v-dmuc*u)-va*(dmvv*v+dmuv*u));
            dand=2.*(hd*(dmca-dmvc*v-dmuc*u)-vd*(dmvv*v+dmuv*u));

            f[8]=(y[11]-dmcc*hf*ha+dmca*(y[3]*a+hf*pa+ca*y[11])/amy2-
                 hf*dmvc*va-(y[10]*st+y[2]*ct*y[9])*f[0])
                 /(y[2]*st);
            f[14]=(y[17]-dmcc*hf*hd+dmca*(y[3]*b+hf*pd+ca*y[17])/amy2-
                  hf*dmvc*vd-(y[16]*st+y[2]*ct*y[15])*f[0])
                  /(y[2]*st);
            f[9]=(y[12]-dmcc*ht*ha+dmca*(y[4]*a+ht*pa+ca*y[12])/amy2-
                 ht*dmvc*va-y[10]*f[1])/y[2];
            f[15]=(y[18]-dmcc*ht*hd+dmca*(y[4]*b+ht*pd+ca*y[18])/amy2-
                  ht*dmvc*vd-y[16]*f[1])/y[2];
            f[10]=y[13]-dmcc*hr*ha+dmca*(y[5]*a+hr*pa+ca*y[13])/amy2-
                  hr*dmvc*va;
            f[16]=y[19]-dmcc*hr*hd+dmca*(y[5]*b+hr*pd+ca*y[19])/amy2-
                  hr*dmvc*vd;
            f[11]=(dmv*(vpp[0][0]*y[8]+vpp[0][1]*y[9]+vpp[0][2]*y[10])+
                  dmvv*vp[0]*va+ha*dmvc*vp[0]-
                  st*y[11]*f[2]-y[3]*ct*y[9]*f[2]-
                  y[3]*st*f[10]-y[3]*ct*y[10]*f[1]+y[2]*y[3]*st*y[9]*f[1]-
                  y[2]*ct*y[11]*f[1]-y[2]*y[3]*ct*f[9]-(st*y[10]+
                  y[2]*ct*y[9])*f[3])/(y[2]*st);
            f[17]=(dmv*(vpp[0][0]*y[14]+vpp[0][1]*y[15]+vpp[0][2]*y[16])+
                  dmvv*vp[0]*vd+hd*dmvc*vp[0]-
                  st*y[17]*f[2]-y[3]*ct*y[15]*f[2]-
                  y[3]*st*f[16]-y[3]*ct*y[16]*f[1]+y[2]*y[3]*st*y[15]*f[1]-
                  y[2]*ct*y[17]*f[1]-y[2]*y[3]*ct*f[15]-(st*y[16]+
                  y[2]*ct*y[15])*f[3])/(y[2]*st);
            f[12]=(dmv*(vpp[1][0]*y[8]+vpp[1][1]*y[9]+vpp[1][2]*y[10])+
                  dmvv*vp[1]*va+ha*dmvc*vp[1]-
                  y[12]*f[2]-y[4]*f[10]+y[3]*ct*y[10]*f[0]+
                  y[2]*ct*y[11]*f[0]-y[2]*y[3]*st*y[9]*f[0]+
                  y[2]*y[3]*ct*f[8]-y[10]*f[4])/y[2];
            f[18]=(dmv*(vpp[1][0]*y[14]+vpp[1][1]*y[15]+vpp[1][2]*y[16])+
                  dmvv*vp[1]*vd+hd*dmvc*vp[1]-
                  y[18]*f[2]-y[4]*f[16]+y[3]*ct*y[16]*f[0]+
                  y[2]*ct*y[17]*f[0]-y[2]*y[3]*st*y[15]*f[0]+
                  y[2]*y[3]*ct*f[14]-y[16]*f[4])/y[2];
            f[13]=dmv*(vpp[2][0]*y[8]+vpp[2][1]*y[9]+vpp[2][2]*y[10])+
                  dmvv*vp[2]*va+ha*dmvc*vp[2]+
                  y[12]*f[1]+y[4]*f[9]+st*y[11]*f[0]+
                  y[3]*ct*y[9]*f[0]+y[3]*st*f[8];
            f[19]=dmv*(vpp[2][0]*y[14]+vpp[2][1]*y[15]+vpp[2][2]*y[16])+
                  dmvv*vp[2]*vd+hd*dmvc*vp[2]+
                  y[18]*f[1]+y[4]*f[15]+st*y[17]*f[0]+
                  y[3]*ct*y[15]*f[0]+y[3]*f[14];
      }

      for(i=0; i<6; i++)
        f[i] /=anorm;

      for(i=8; i<14; i++)
        f[i]=(f[i]-f[i-8]*dana)/anorm;

      for(i=14; i<20; i++)
        f[i]=(f[i]-f[i-14]*dand)/anorm;
  }
  else
  {
      for(i=0; i<6; i++)
        f[i] /=anorm;
  }

  if (n>20)
      f[20]=amy2/anorm;
  if (n>21)
      f[21]=sqrt(amy2+dmca*dmca*sa2/amy2)/anorm;

  return 0;

} /*funcs*/
