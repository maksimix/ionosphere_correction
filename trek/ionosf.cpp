using namespace std;

#include "mytrek.h"
#include "../iri_3d/iri_3d_new.h"


int MyTrek::ionosf(double fi,     // сферические координаты расположения луча
            double teta,   //
            double r,      //
            double time,
            double &v,     // нормированный квадрат плазменной частоты
            double &vfi,   // его производные по fi, tets, r
            double &vteta, //
            double &vr,    //
            double &vt)    //
//  Вычисление профиля ионизации и его производных
//
//VGG
{
  double X,Y,Z,dX,dY,dZ,x,y;
  double sF,cF,sT,cT,vx,vy;
  double dxf,dyf,dxt,dyt,cdf,sdf;
  long keyX,keyY,keyZ,key;
  double v1,vx1,vy1,vr1;
  double v2,vx2,vy2,vr2;
  double t1=iri_3dbase->getTime();
  double t2=iri_3dbase2->getTime();
  double hEs1,hEs2,hD1,hD2,hE1,hE2,hF11,hF12,hF21,hF22,f0F21,f0F11,f0E1,f0D1,f0Es1,fbEs1,
         f0F22,f0F12,f0E2,f0D2,f0Es2,fbEs2,pEs1,pEs2,hi1,hi2;

  //cout<<endl<<"r="<<r;
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

  iri_3dbase ->spcub(x,y,r-iri_3dbase->r0,v1,vx1,vy1,vr1,keyX,keyY,keyZ);
  //cout<<endl<<"1 x="<<x<<" y="<<y<<" r="<<r<<" "<<iri_3dbase->getIx()<<" "<<iri_3dbase->getIy()<<" "<<dZ<<" "<<dY<<" "<<dX<<" "<<iri_3dbase->Z0;
  hi1=iri_3dbase->getHi(iri_3dbase->getIx(),iri_3dbase->getIy());
  hF21=iri_3dbase->gethmF2(iri_3dbase->getIx(),iri_3dbase->getIy());
  f0F21=iri_3dbase->getf0F2(iri_3dbase->getIx(),iri_3dbase->getIy());
  hF11=iri_3dbase->gethmF1(iri_3dbase->getIx(),iri_3dbase->getIy());
  f0F11=iri_3dbase->getf0F1(iri_3dbase->getIx(),iri_3dbase->getIy());
  hE1 =iri_3dbase->gethmE(iri_3dbase->getIx(),iri_3dbase->getIy());
  f0E1=iri_3dbase->getf0E(iri_3dbase->getIx(),iri_3dbase->getIy());
  hD1 =iri_3dbase->gethmD(iri_3dbase->getIx(),iri_3dbase->getIy());
  f0D1=iri_3dbase->getf0D(iri_3dbase->getIx(),iri_3dbase->getIy());
  hEs1=iri_3dbase->gethmEs(iri_3dbase->getIx(),iri_3dbase->getIy());
  f0Es1=iri_3dbase->getf0Es(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  fbEs1=iri_3dbase->getfbEs(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  pEs1=iri_3dbase->getPEs(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  iri_3dbase2->spcub(x,y,r-iri_3dbase->r0,v2,vx2,vy2,vr2,keyX,keyY,keyZ);
  //cout<<endl<<"2 x="<<x<<" y="<<y<<" r="<<r<<" "<<iri_3dbase->getIx()<<" "<<iri_3dbase->getIy()<<" "<<dZ<<" "<<dY<<" "<<dX;
  hi2=iri_3dbase2->getHi(iri_3dbase->getIx(),iri_3dbase->getIy());
  hF22=iri_3dbase2->gethmF2(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  f0F22=iri_3dbase2->getf0F2(iri_3dbase->getIx(),iri_3dbase->getIy());
  hF12=iri_3dbase2->gethmF1(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  f0F12=iri_3dbase2->getf0F1(iri_3dbase->getIx(),iri_3dbase->getIy());
  hE2 =iri_3dbase2->gethmE(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  f0E2=iri_3dbase2->getf0E(iri_3dbase->getIx(),iri_3dbase->getIy());
  hD2 =iri_3dbase->gethmD(iri_3dbase->getIx(),iri_3dbase->getIy());
  f0D2=iri_3dbase->getf0D(iri_3dbase->getIx(),iri_3dbase->getIy());
  hEs2=iri_3dbase2->gethmEs(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  f0Es2=iri_3dbase2->getf0Es(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  fbEs2=iri_3dbase2->getfbEs(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  pEs2=iri_3dbase2->getPEs(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  HmF2=(hF21+(time-t1)*(hF22-hF21)/(t2-t1))*.01+R0;
  F0F2=(f0F21+(time-t1)*(f0F22-f0F21)/(t2-t1));
  HmF1=(hF11+(time-t1)*(hF12-hF11)/(t2-t1))*.01+R0;
  F0F1=(f0F11+(time-t1)*(f0F12-f0F11)/(t2-t1));
  HmE =(hE1+(time-t1)*(hE2-hE1)/(t2-t1))*.01+R0;
  F0E=(f0E1+(time-t1)*(f0E2-f0E1)/(t2-t1));
  HmD =(hD1+(time-t1)*(hD2-hD1)/(t2-t1))*.01+R0;
  F0D =(f0D1+(time-t1)*(f0D2-f0D1)/(t2-t1));
  HmEs=(hEs1+(time-t1)*(hEs2-hEs1)/(t2-t1))*.01+R0;
  F0Es=(f0Es1+(time-t1)*(f0Es2-f0Es1)/(t2-t1));
  FbEs=(fbEs1+(time-t1)*(fbEs2-fbEs1)/(t2-t1));
  PEs=(pEs1+(time-t1)*(pEs2-pEs1)/(t2-t1));
  Hi=(hi1+(time-t1)*(hi2-hi1)/(t2-t1));
  fhTemp=(iri_3dbase->getFh(iri_3dbase->getIx(),iri_3dbase->getIy()));
  ITemp=(iri_3dbase->getI(iri_3dbase->getIx(),iri_3dbase->getIy()));
  DTemp=(iri_3dbase->getD(iri_3dbase->getIx(),iri_3dbase->getIy()));

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
            double &vtr)    //
//  Вычисление профиля ионизации и его производных
//
//VGG
{
  double X,Y,Z,dX,dY,dZ,x,y;
  double sF,cF,sT,cT,vx,vy,vxx,vxy,vyy,vxz,vyz;
  double dxf,dyf,dxt,dyt,cdf,sdf;
  double dxff,dxtt,dxft,dyff,dytt,dyft;
  long keyX,keyY,keyZ,key;

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

  iri_3dbase->spcub(x,y,r-iri_3dbase->r0,v,vx,vy,vr,vxx,vyy,vrr,vxy,vxz,vyz,keyX,keyY,keyZ);
  HmF2=(iri_3dbase->gethmF2(iri_3dbase->getIx(),iri_3dbase->getIy()))*.01+R0;
  HmF1=(iri_3dbase->gethmF1(iri_3dbase->getIx(),iri_3dbase->getIy()))*.01+R0;
  HmE =(iri_3dbase->gethmE(iri_3dbase->getIx(),iri_3dbase->getIy()))*.01+R0;
  HmEs=(iri_3dbase->gethmEs(iri_3dbase->getIx(),iri_3dbase->getIy()))*.01+R0;

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
            double &vtr)    //
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

  iri_3dbase ->spcub(x,y,r-iri_3dbase->r0,v1,vx1,vy1,vr1,vxx1,vyy1,vrr1,vxy1,vxz1,vyz1,keyX,keyY,keyZ);
  hF21=iri_3dbase->gethmF2(iri_3dbase->getIx(),iri_3dbase->getIy());
  hF11=iri_3dbase->gethmF1(iri_3dbase->getIx(),iri_3dbase->getIy());
  hE1 =iri_3dbase->gethmE(iri_3dbase->getIx(),iri_3dbase->getIy());
  hEs1=iri_3dbase->gethmEs(iri_3dbase->getIx(),iri_3dbase->getIy());
  iri_3dbase2->spcub(x,y,r-iri_3dbase->r0,v2,vx2,vy2,vr2,vxx2,vyy2,vrr2,vxy2,vxz2,vyz2,keyX,keyY,keyZ);
  hF22=iri_3dbase2->gethmF2(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  hF12=iri_3dbase2->gethmF1(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  hE2 =iri_3dbase2->gethmE(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  hEs2=iri_3dbase2->gethmEs(iri_3dbase2->getIx(),iri_3dbase2->getIy());
  HmF2=(hF21+(time-t1)*(hF22-hF21)/(t2-t1))*.01+R0;
  HmF1=(hF11+(time-t1)*(hF12-hF11)/(t2-t1))*.01+R0;
  HmE =(hE1+(time-t1)*(hE2-hE1)/(t2-t1))*.01+R0;
  HmEs=(hEs1+(time-t1)*(hEs2-hEs1)/(t2-t1))*.01+R0;
  
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
            int &n)
//  nu-h profile in the point with spher.koord. (fi,theta,r)
//
{
  double X,Y,Z,dX,dY,dZ,x,y;
  double sF,cF,sT,cT;
  long keyX,keyY,keyZ,key;
//  double nu_test;
//  double test;

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

  iri_3dbase->nu->spcub(x,y,r-iri_3dbase->r0,n,keyX,keyY,keyZ);
  key=fabs(keyX)+fabs(keyY);

//  nu_test = iri_3dbase->nu->getCarrier(10,10,140);
//  cout<<" "<<nu_test;

//  test = iri_3dbase->getCarrier(7,7,0);    cout<<" "<<test;
//  test = iri_3dbase->getCarrier(7,7,90);  cout<<" "<<test;

  //printf("\nn=%12.5e",n);
  key=0;

  return key;
}

int MyTrek::nuprof(double fi,
            double teta,
            double r,
            double time,
            int &n)
//  nu-h profile in the point with spher.koord. (fi,theta,r) and time point time
//
{
  double X,Y,Z,dX,dY,dZ,x,y;
  double sF,cF,sT,cT;
  long keyX,keyY,keyZ,key;
  double n1,n2,nt;
  double t1=iri_3dbase->getTime();
  double t2=iri_3dbase2->getTime();

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

  iri_3dbase->nu->spcub(x,y,r-iri_3dbase->r0,n1,keyX,keyY,keyZ);
  iri_3dbase2->nu->spcub(x,y,r-iri_3dbase->r0,n2,keyX,keyY,keyZ);

  key=fabs(keyX)+fabs(keyY);

  nt=(n2-n1)/(t2-t1);
  n=(time-t1)*nt+n1;
  
  key=0;

  return key;
}

