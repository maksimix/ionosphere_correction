using namespace std;

#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <float.h>
#include "iri_3d_new.h"
//#include "../f2c/f2c.h"

IRI_3D *iri_3dbase=0;
IRI_3D *iri_3dbase2=0;

//int IRI_3D::countIri=0;

//#define R0  63.70
double HmF2,HmF1,HmE,HmD,HmEs,F0F2,F0F1,F0E,F0D,F0Es,FbEs,PEs,Hi;
double fhTemp,DTemp,ITemp;

double Vx, Vy, Vz;
extern "C"
{
int iri_sub_ne_(int *jf, int *jmag, float *alati, float *along, int *iyyyy,
                   int *mmdd, float *dhour,
                   float *heibeg, float *heiend, float *heistp,
                   float *outf, float *oarr);
int iri_sub_(int *jf, int *jmag, float *alati, float *along, int *iyyyy,
                int *mmdd, float *dhour,
                float *heibeg, float *heiend, float *heistp, float *outf, float *oarr);

int iri_sub_ne_(int *jf, int *jmag, float *alati, float *along, int *iyyyy,
                int *mmdd, float *dhour,
                float *heibeg, float *heiend, float *heistp, float *outf, float *oarr);
int fieldg_(float *dlat, float *dlong, float *alt, float *x, float *y,
              float *z__, float *f, float *dip, float *dec, float *smodip);
//int initize_();SPCUB3(
int my_initial_();

int gtd6_(int *iyd, float *sec, float *alt,
          float *glat, float *glong, float *stl,
          float *f107a, float *f107, float *ap, int *mass,
          float * d__, float *t);

void gtd7_(int *iyd, float *sec,float *alt,
           float *lat,float *lon, float *hour,
           float *f107a,float *f107,float *ap,int *mass,
           float *d__,float *t);
};

bool  eschar(double ai,
            double fi,
            double t,
            long    m,
            double *f0,
            double *fb,
            double *hes,
            double *pps);


IRI_3D::IRI_3D(double lon, double lat, double rmax, double zmin, double dz, long nx, long ny, long nz)
               :SPCUB3(nx,ny,nz)
{
  double x,y,z;
  long   i,j,k;
  
  //countIri++;
  //cout<<endl<<"00 IRI_3D  countIri="<<countIri<<flush;

  keyEs=true;
  keyCorIon = false;

  nu = new SPCUB3(nx,ny,nz);
  nu -> setTypeGran(D2xD2x,D2xD2x,D2xD2x);

  n=new double *[13];
  for(i=0; i<13; i++)
  {
      n[i]=new double [nz];
  }

  F0F2=new double[nx*ny];
  HmF2=new double[nx*ny];
  F0F1=new double[nx*ny];
  HmF1=new double[nx*ny];
  F0E=new double[nx*ny];
  HmE=new double[nx*ny];
  F0D=new double[nx*ny];
  HmD=new double[nx*ny];
  pEs=new double[nx*ny];
  HmEs=new double[nx*ny];
  FbEs=new double[nx*ny];
  F0Es=new double[nx*ny];
  fhMag=new double[nx*ny];
  IMag=new double[nx*ny];
  DMag=new double[nx*ny];;
  Hi=new double[nx*ny];;

  fi0=lon*RAD; teta0=(90.-lat)*RAD;
  r0=100.*R0;
  sFi0=sin(fi0);
  cFi0=cos(fi0);
  sTeta0=sin(teta0);
  cTeta0=cos(teta0);
  X0=r0*sTeta0*cFi0;
  Y0=r0*sTeta0*sFi0;
  Z0=r0*cTeta0;

  //cout<<endl<<"Z0="<<Z0<<" Y0="<<Y0<<" X0="<<X0<<" r0="<<r0<<" cTeta="<<cTeta0<<" cFi="<<cFi0;;

  out=new float[20*KOL];
  oarr=new float[100];
  jf=new int[50];
  for(i=0; i<50; i++)
    jf[i]=1;
  jf[1]=1;  // Te, Ti computed
  jf[2]=1;  // Ni computed
  jf[4]=1;  // 1 - CCIR, 0 - URSI
  jf[16]=1; // 0 - ++¬- L¬¬++¬+¬¬ +TLЦ++¬LLЦ
  //jf[21]=0; // ion densities in m-3
  //jf[23]=0; // Special: 3 D-region models
  jf[25]=0; // no storm updating
  //jf[11]=0;
  jf[20]=jf[25]=jf[27]=jf[28]=jf[29]=jf[32]=jf[33]=jf[34]=jf[35]=jf[36]=jf[37]=0;
  iyear=1999;
  jmag=0;
  imd=1215;
  hour=25.+10.;
  oarr[32]=10.; // L¬¬++¬++T +TLЦ++¬LL+
  
  setTypeGran(D2xD2x,D2xD2x,D2xD2x);

  xMin=yMin=-100.*rmax; xMax=yMax=100.*rmax;
  zMin=100.*zmin;
  dZ=100.*dz;
  zMax=zMin+dZ*nz;
  dX=(xMax-xMin)/(nx-1);
  dY=(yMax-yMin)/(ny-1);
  x=xMin;
  for(i=0; i<nx; i++)
    {
      setCarrierX(x,i);
      x+=dX;
    }
  x=xMin;
  for(i=0; i<nx; i++)
    {
      nu -> setCarrierX(x,i);
      x+=dX;
    }
  y=yMin;
  for(j=0; j<ny; j++)
    {
      setCarrierY(y,j);
      y+=dY;
    }
  y=yMin;
  for(j=0; j<ny; j++)
    {
      nu -> setCarrierY(y,j);
      y+=dY;
    }
  z=zMin;
  for(k=0; k<nz; k++)
    {
      setCarrierZ(z,k);
      z+=dZ;
    }
  z=zMin;
  for(k=0; k<nz; k++)
    {
      nu -> setCarrierZ(z,k);
      z+=dZ;
    }
  for(i=0; i<nx; i++)
    for(j=0; j<ny; j++)
      for(k=0; k<nz; k++)
          setCarrier(.0,i,j,k);
  for(i=0; i<nx; i++)
    for(j=0; j<ny; j++)
      for(k=0; k<nz; k++)
          nu -> setCarrier(.0,i,j,k);

  yearMax=2011;
  monthMax=1;
  FILE *in;
  in=fopen("ig_rz.dat","rt");
  if (in)
  {
      int m1,d1,year1,mMin,yearMin;
      fscanf(in,"%d,%d,%d,",&m1,&d1,&year1);
      fscanf(in,"%d,%d,%d,%d",&mMin,&yearMin,&monthMax,&yearMax);
      //in>>m1>>d1>>year1>>mMin>>yearMin>>monthMax>>yearMax;
      //cout<<"################### yearMax="<<yearMax<<" monthMax="<<monthMax<<" yearMin="<<yearMin<<flush;
  }
  //cout<<"################### yearMax="<<yearMax<<flush;
  fclose(in);

  hmEs=PEs=fbEs=f0Es=.0;

  // поправки
  D_foE = D_hmE = D_foF1 = D_hmF1 = D_foF2 = D_hmF2 = D_foEs = D_hmEs = 0.0;
  //initize_();
  my_initial_();
}

IRI_3D::IRI_3D(IRI_3D &iri)
        :SPCUB3((SPCUB3 &)iri)
{
    int i,j;

    //countIri++;
    //cout<<endl<<"copy IRI_3D  countIri="<<countIri<<flush;

    //*this=iri;
    
    sFi0=iri.sFi0;
    cFi0=iri.cFi0;
    sTeta0=iri.sTeta0;
    cTeta0=iri.cTeta0;
    r0=iri.r0;
    X0=iri.X0;
    Y0=iri.Y0;
    Z0=iri.Z0;    
    fi0=iri.fi0;
    teta0=iri.teta0;
    nx=iri.nx;
    ny=iri.ny;
    nz=iri.nz;
    hour=iri.hour;
    
    /*
    dX=iri.dX;
    dY=iri.dZ;
    xMin=iri.xMin;
    xMax=iri.xMax;
    yMin=iri.yMin;
    yMax=iri.yMax;
    zMin=iri.zMin;
    zMax=iri.zMax;
    hmax=iri.hmax;
    fmin=iri.fmin;
    fMinF2=iri.fMinF2;
    f0F2=iri.f0F2;
    hmF2=iri.hmF2;
    f0F1=iri.f0F1;
    hmF1=iri.hmF1;
    f0E=iri.f0E;
    hmE=iri.hmE;
    f0D=iri.f0D;
    hmD=iri.hmD;
    keyCorIon=iri.keyCorIon;
    */
    
    //out=new float[20*KOL];
    //oarr=new float[100];
    //jf=new int[50];
    //for(i=0; i<100; i++)
    //   oarr[i]=iri.oarr[i];
    //for(i=0; i<50; i++)
    //   jf[i]=iri.jf[i];
    //n=new double *[13];
    //for(i=0; i<13; i++)
    //{
    //    n[i]=new double [nz];
    //    for(j=0; j<nz; j++)
    //        *(n[i]+j)=*(iri.n[i]+j);
    //}
    
    
    out=0;
    oarr=0;
    jf=0;
    n=0;
    /*
    ix=iy=iz=0;
    ixOld=iyOld=izOld=-1;
    xOld=yOld=zOld=DBL_MAX;
    nmx=nx-1;
    nmy=ny-1;
    nmz=nz-1;
    maxXYZ=__max(nx,ny);
    maxXYZ=__max(maxXYZ,nz);
    keyX=iri.keyX; keyY=iri.keyY; keyZ=iri.keyZ;

    nXY=nx*ny;
    nXZ=nx*nz;
    nYZ=ny*nz;
    nXYZ=nx*ny*nz;
    
    granXa=0;//new double[nYZ];
    granXb=0;//new double[nYZ];
    granYa=0;//new double[nXZ];
    granYb=0;//new double[nXZ];
    granZa=0;//new double[nXY];
    granZb=0;//new double[nXY];
    for(i=0; i<4; i++)
    {
        granX[i]=0;//new double[nx];
        granY[i]=0;//new double[ny];
        granZ[i]=0;//new double[nz];
    }
    x =new double[nx];
    y =new double[ny];
    z =new double[nz];
    f    =new double[nXYZ];
    dfx  =new double[nXYZ];
    dfy  =new double[nXYZ];
    dfz  =new double[nXYZ];
    dfxy =new double[nXYZ];
    dfxz =new double[nXYZ];
    dfyz =new double[nXYZ];
    dfxyz=new double[nXYZ];

#pragma omp parallel for 
    for(int i=0; i<nx; i++)
        x[i]=iri.x[i];
#pragma omp parallel for 	
    for(int i=0; i<ny; i++)
        y[i]=iri.y[i];
#pragma omp parallel for 	
    for(int i=0; i<nz; i++)
        z[i]=iri.z[i];
    */
    /*
    for(i=0; i<4; i++)
    {
        for(j=0; j<nx; j++)
          *(granX[i]+j)=*(iri.granX[i]+j);
        for(j=0; j<ny; j++)
          *(granY[i]+j)=*(iri.granY[i]+j);
        for(j=0; j<nz; j++)
          *(granZ[i]+j)=*(iri.granZ[i]+j);
    }
    for(i=0; i<8; i++)
      granXYZ[i]=iri.granXYZ[i];

    for(i=0; i<nXY; i++)
    {
        granZa[i]=iri.granZa[i];
        granZb[i]=iri.granZb[i];
    }
    for(i=0; i<nXZ; i++)
    {
        granYa[i]=iri.granYa[i];
        granYb[i]=iri.granYb[i];
    }
    for(i=0; i<nYZ; i++)
    {
        granXa[i]=iri.granXa[i];
        granXb[i]=iri.granXb[i];
    }
    */
    /*
#pragma omp parallel for 
    for(int i=0; i<nXYZ; i++)
    {
        f[i]=iri.f[i];
        dfx[i]=iri.dfx[i];
        dfy[i]=iri.dfy[i];
        dfz[i]=iri.dfz[i];
        dfxy[i]=iri.dfxy[i];
        dfxz[i]=iri.dfxz[i];
        dfyz[i]=iri.dfyz[i];
        dfxyz[i]=iri.dfxyz[i];
    }    
    */

    int nxy=nx*ny;
    
    F0F2=new double[nx*ny];
    HmF2=new double[nx*ny];
    F0F1=new double[nx*ny];
    HmF1=new double[nx*ny];
    F0E=new double[nx*ny];
    HmE=new double[nx*ny];
    F0D=new double[nx*ny];
    HmD=new double[nx*ny];
    pEs=new double[nx*ny];
    HmEs=new double[nx*ny];
    FbEs=new double[nx*ny];
    F0Es=new double[nx*ny];
    fhMag=new double[nx*ny];
    IMag=new double[nx*ny];
    DMag=new double[nx*ny];;
    Hi=new double[nx*ny];;

#pragma omp parallel for 
    for(int i=0; i<nxy; i++)
    {
        F0F2[i]=iri.F0F2[i];
        HmF2[i]=iri.HmF2[i];
        F0F1[i]=iri.F0F1[i];
        HmF1[i]=iri.HmF1[i];
        F0E[i]=iri.F0E[i];
        HmE[i]=iri.HmE[i];
        F0D[i]=iri.F0D[i];
        HmD[i]=iri.HmD[i];
        pEs[i]=iri.pEs[i];
        HmEs[i]=iri.HmEs[i];
        FbEs[i]=iri.FbEs[i];
        F0Es[i]=iri.F0Es[i];
        fhMag[i]=iri.fhMag[i];
        IMag[i]=iri.IMag[i];
        DMag[i]=iri.DMag[i];
        Hi[i]=iri.Hi[i];
    }

    nu=new SPCUB3(*iri.nu);
}

IRI_3D::~IRI_3D()
{
  //countIri--;
  //cout<<endl<<"~IRI_3D  countIri="<<countIri<<flush;
    
  if (jf)
      delete[] jf;
  if (out)
      delete[] out;
  if (oarr)
      delete[] oarr;
  
  delete[] F0F2;
  delete[] HmF2;
  delete[] F0F1;
  delete[] HmF1;
  delete[] F0E;
  delete[] HmE;
  delete[] F0D;
  delete[] HmD;
  delete[] pEs;
  delete[] HmEs;
  delete[] FbEs;
  delete[] F0Es;
  delete[] fhMag;
  delete[] IMag;
  delete[] DMag;
  delete[] Hi;

  if (n)
  {
      for(long i=0; i<13; i++)
      {
	  if (n[i])
	      delete[] n[i];
      }
      delete[] n;
  }
  
  if (nu)
      delete nu;

  //iri_3dbase=0;
  //iri_3dbase2=0;
}

void IRI_3D::globalSfCoord(double x,
                           double y,
                           double &fi,
                           double &teta)
// Функция по локальным декартовым координатам, привязанным к
// опорной точке на поверхности Земли, вычисляет сферические координаты
//VGG
{
  double X,Y,Z;

  X=r0*sTeta0*cFi0-x*sFi0-y*cTeta0*cFi0;
  Y=r0*sTeta0*sFi0+x*cFi0-y*cTeta0*sFi0;
  Z=r0*cTeta0+y*sTeta0;
  teta=acos(Z/sqrt(X*X+Y*Y+Z*Z));
  fi=atan2(Y,X);
  if (fi<.0)
      fi+=PI2;
}

void IRI_3D::getAppzocsim3DProfil()
// Функция предназначена для вычисления высотного распределения ионизации
// в соответствии с моделью IRI-95 и ее пространственной апроксимации
//
//VGG
{
  double fi,teta;
  double x,y;
  double lat,lon;
  double f;
  int    i,j,k,l,m,nn13,kol;
  double pes=.0,fbes=.0,f0es=.0,hmes=.0;
  double Alt=100.,hx,hy,hz,Fh,Dip,Dec,Smodip;
  float f107a=150., f107=150.;
  float lat_f, lon_f, Alt_f=100., hx_f, hy_f, hz_f, Fh_f, Dip_f, Dec_f, Smodip_f;
  float z1,z2,dz_f,hou,alt;

  hou=hour;
  x=xMin;
  hmax=.0;
  fmin=30.;
  fMinF2=30.;
  dz_f=dZ;
  for(i=0; i<nx; i++)
  {
      y=yMin;
      for(j=0; j<ny; j++)
      {
          globalSfCoord(x,y,fi,teta);
          // вычисление высотного распределения ионизации
          // в точке с координатами fi и teta
          lon=fi/RAD;
          lat=(PI05-teta)/RAD;
          z2=zMin+dz_f*KOL;
          z1=zMin;
          nn13=0;
          //
          tm=.2617999*(hou-25.)+fi; // НЕУФОПЕ ЧТЕНС
          int mes=imd/100;
          lat_f=lat;
          lon_f=lon;
          fieldg_(&lat_f, &lon_f, &Alt_f, &hx_f, &hy_f, &hz_f, &Fh_f, &Dip_f, &Dec_f, &Smodip_f);
          hx=hx_f;
          hy=hy_f;
          hz=hz_f;
          Fh=Fh_f;
          Dip=Dip_f;
          Dec=Dec_f;
          Smodip=Smodip_f;
          if ( !eschar(Dip*RAD, lat*RAD, tm, mes, &f0es, &fbes, &hmes, &pes) )
          {
                if( fabs(D_foEs) > 0.000001 && keyCorIon)
                    keyEs = true;
          }
          //cout<<endl<<"Pes="<<pes<<" hmEs="<<hmes<<" f0Es="<<f0es<<" fbEs="<<fbes<<" I="<<Dip<<" hou="<<hou<<" keyEs="<<keyEs;
          //cout<<endl<<"keyEs = "<<keyEs<<"; fo = "<<f0es<<"; D_foEs = "<<D_foEs<<flush;


          if( keyCorIon )
          {
              if( keyEs )
              {
                  fbes += D_foEs;
                  hmes += D_hmEs;
              }
              double f1, h1, f2, h2, f3, h3, fes, hes;
              ioncorr( true, lat, lon, hou, f1, h1, f2, h2, f3, h3, fes, hes );
              //cout<<endl<<"@@@@@@@@@@ ioncorr     h1="<<h1<<" f1="<<f1<<" h3="<<h3<<" f3="<<f3;
          }

          //cout<<endl<<"keyEs = "<<keyEs<<"; fo = "<<f0es<<"; D_foEs = "<<D_foEs<<flush;

          while(z1<zMax)
          {
              if (z2>zMax)
                  z2=zMax;
              hou=hour;
              //cout<<endl<<"iri_sub"<<flush;
              iri_sub_(&jf[0], &jmag, &lat_f, &lon_f, &iyear, &imd, &hou, &z1, &z2, &dz_f, &out[0], &oarr[0]);
              //iri_sub_ne__((int*)&jf[0], (int *)&jmag, &lat, &lon, (int *)&iyear, (int *)&imd, &hou, &z1, &z2, &dZ, &out[0], &oarr[0]);
              //iri_sub__((int*)&jf[0], &jmag, &lat, &lon, &iyear, &imd, &hou, &z1, &z2, &dZ, &out[0], &oarr[0]);
              //cout<<"2#2#2#2#2#2#2  hE="<<oarr[5]<<" fE="<<sqrt(oarr[4]*NeTofn)<<" hF2="<<oarr[1]<<" fF2="<<sqrt(oarr[0]*NeTofn);
              //  заполнение массива по z
              hmax=__max(hmax,oarr[1]);
              kol=(long)((z2-z1)/dz_f);
              for(k=1; k<=kol; k++)
              {
                  //cout<<endl<<"z="<<z1+dZ*k<<" fpl="<<out[k * 11 - 11]*NeTofn;
                  if (out[k * 20 - 20]>.0)
                    {
                      //f=sqrt(out[k * 11 - 11]*NeTofn);
                      f=fabs(out[k * 20 - 20]*NeTofn);
                      *(n[8]+nn13)=1.e-6*out[k * 20 - 20];
                      fmin=__min(fmin,sqrt(f));
		      if (keyEs && hmes>=z1+dz_f*(k-1) && hmes<z1+dz_f*k && sqrt(f)<fbes)
		         f=fbes*fbes;
                      setCarrier(f,i,j,nn13);
                    }
                  else
                  {
                     *(n[8]+nn13)=.0;
                     setCarrier(.0,i,j,nn13);
                  }

                  if (out[k * 20 - 20+3]>.0)
                  {
                     *(n[10]+nn13)=out[k * 20 - 20+3]; // Te
                  }
                  else
                  {
                     *(n[10]+nn13)=.0; // Te
                  }

                  nn13++;
              }
              z1=z2;
              z2=z1+dz_f*KOL;
          }

    /*
    C     D(1) - HE NUMBER DENSITY(CM-3)
    C     D(2) - O NUMBER DENSITY(CM-3)
    C     D(3) - N2 NUMBER DENSITY(CM-3)
    C     D(4) - O2 NUMBER DENSITY(CM-3)
    C     D(5) - AR NUMBER DENSITY(CM-3)
    C     D(6) - TOTAL MASS DENSITY(GM/CM3)
    C     D(7) - H NUMBER DENSITY(CM-3)
    C     D(8) - N NUMBER DENSITY(CM-3)
    C     T(1) - EXOSPHERIC TEMPERATURE
    C     T(2) - TEMPERATURE AT ALT
    */
          f107 =oarr[40];
          f107a=f107;
          float sec=.0, hour_stl;
          int   mass=48; //для всего
          float ap[7]={4,4,4,4,4,4,4};
          float d__[8], t[2];

          if (hou>25)
             sec=hou-25.;
          else
             sec=hou; 
          hour_stl=sec+lon/15.;
          if (hour_stl>24.)
             hour_stl-=24.;

          sec*=3600.;

          for(alt=zMin,l=0; alt<zMax && l<nz; alt+=dz_f, l++)
          {
              int i1,i2;
              //float a1,a2,a3,a4,a5,a6,a7,a8,a9,a0;
              //gtd6_(&i1,&a1,&a2,&a3,&a4,&a5,&a6,&a7,&a8,&i2,&a9,&a0);
              
              gtd7_(&imd,&sec,&alt,&lat_f,&lon_f,&hour_stl,&f107a,&f107,&ap[0],&mass,&d__[0],&t[0]);
              //gtd6_((int *)&imd,(float*)&sec,(float*)&alt,(float*)&lat,(float*)&lon,(float*)&hour_stl,(float*)&f107a,
              //      (float*)&f107,(float*)&ap[0],(int *)&mass,(float*)&d__[0],(float*)&t[0]);
             for(k=0; k<8; k++)
             {
                if (d__[k]>.0)
                {
                    *(n[k]+l)=d__[k];
//                    if (k==5) cout<<" "<<*(n[k]+l);
                }
                else
                {
                    *(n[k]+l)=.0;
                }
             }
             for(m=11,k=0; m<13; m++,k++)
             {
                if (t[k]>.0)
                {
                    *(n[m]+l)=t[k];
//                    cout<<" "<<*(n[m]+l);
                }
                else
                {
                    *(n[m]+l)=.0;
                }
                    
             }
          }

          for(k=0; k<nz; k++)
          {
             double Te=(*(n[10]+k)>.0)? *(n[10]+k) : *(n[12]+k);
//             double nu_test;
             if (Te>.0)
             {
                double Nu=.0;
                double sqrtTe=sqrt(fabs(Te));
                double nuN2=2.50e-11**(n[2]+k)*Te/(1.+.0093*sqrtTe);
                double nuO2=1.82e-10**(n[3]+k)*(1.+.036*sqrtTe)*sqrtTe;
                double nuO =2.80e-10**(n[1]+k)*sqrtTe;
                double nuHe=4.70e-10**(n[0]+k)*sqrtTe;
                double nuH =4.60e-10**(n[6]+k)*sqrtTe;
                double nuEI;
                if (*(n[8]+k)>.0)
                   nuEI=12.65**(n[8]+k)*log10(220.*Te/exp(log(*(n[8]+k))/3.))/(Te*sqrtTe);
                else
                   nuEI=.0;
//                cout<<" "<<nuEI;

                if (zMin+k*dZ<120.)
                {
                   Nu=2.691e-11*(*(n[0]+k)+*(n[1]+k)+*(n[2]+k)+*(n[3]+k)+*(n[6]+k))**(n[12]+k);
                   *(n[9]+k)=1.e-6*(Nu);  //everything in MGc
//                   *(n[9]+k)=log10(Nu);
                }
                else *(n[9]+k)=1.e-6*(nuN2+nuO2+nuO+nuHe+nuH+nuEI);
//                else *(n[9]+k)=log10(nuN2+nuO2+nuO+nuHe+nuH+nuEI);

//                cout<<" "<<*(n[9]+k);
//                *(n[9]+k)= log10( 1.e6*(exp(12.7-.158*(zMin+k*dZ))+exp(-6.17-.0042*(zMin+k*dZ))) ); // model nu-profile
//                *(n[9]+k)= (exp(12.7-.158*(zMin+k*dZ))+exp(-6.17-.0042*(zMin+k*dZ))) ; // model nu-profile

                nu -> setCarrier(*(n[9]+k),i,j,k);
//                nu_test = nu -> getCarrier(i,j,k);
//                cout<<" "<<nu_test;
             }
          }

          //cout<<endl<<" sqrt(oarr[0]*NeTofn)="<<sqrt(oarr[0]*NeTofn)<<
          //    " t="<<hou-25.<<" iyear="<<iyear<<" imd="<<imd<<flush;

          F0F2[ny*i+j]=sqrt(oarr[0]*NeTofn);
          HmF2[ny*i+j]=oarr[1];
          if (oarr[2]>.0)
              F0F1[ny*i+j]=sqrt(oarr[2]*NeTofn);
          else
              F0F1[ny*i+j]=.0;
          if (oarr[3]>.0)
              HmF1[ny*i+j]=oarr[3];
          else
              HmF1[ny*i+j]=.0;
          F0E[ny*i+j]=sqrt(oarr[4]*NeTofn);
          HmE[ny*i+j]=oarr[5];
          F0D[ny*i+j]=sqrt(oarr[6]*NeTofn);
          HmD[ny*i+j]=oarr[7];
          pEs[ny*i+j]=pes;
          HmEs[ny*i+j]=hmes;
          FbEs[ny*i+j]=fbes;
          F0Es[ny*i+j]=f0es;
          fMinF2=__min(fMinF2,F0F2[ny*i+j]);
          Hi[ny*i+j]=oarr[22]; // hi
          fhMag[ny*i+j]=2.79*Fh;//sqrt(hx*hx+hy*hy+hz*hz);
          IMag[ny*i+j] =Dip;//atan2(hz,sqrt(hx*hx+hy*hy))/RAD;
          DMag[ny*i+j] =Dec;//atan2(hy,hx)/RAD;

          //cout<<endl<<"f0f2="<<F0F2[ny*i+j]<<"  hmF2="<<HmF2[ny*i+j]<<"  hmF1="<<HmF1[ny*i+j]<<" i="<<i<<" j="<<j<<flush;
          //cout<<"#############  hE="<<oarr[5]<<" fE="<<sqrt(oarr[4]*NeTofn)<<" hF2="<<oarr[1]<<" fF2="<<sqrt(oarr[0]*NeTofn);
          if (fabs(fi0-fi)<RAD && fabs(teta0-teta)<RAD) // критическа частота в опорной точке
          {
              f0F2=sqrt(oarr[0]*NeTofn);
              if (oarr[2]>.0)
                  f0F1=sqrt(oarr[2]*NeTofn);
              else
                  f0F1=.0;
              f0E =sqrt(oarr[4]*NeTofn);
              f0D =sqrt(oarr[6]*NeTofn);
              hmF2=oarr[1];
              if (oarr[3]>.0)
                  hmF1=oarr[3];
              else
                  hmF1=.0;
              hmE =oarr[5];
              hmD =oarr[7];
              //
              hmEs=hmes;
              PEs =pes;
              fbEs=fbes;
              f0Es=f0es;

              //cout<<endl<<"f0f2="<<f0F2<<"  hmF2="<<hmF2<<" f0f1="<<f0F1<<"  hmF1="<<hmF1<<" f0e="<<f0E<<"  hme="<<hmE<<" fbEs="<<fbEs<<" hmEs="<<hmEs<<" i="<<i<<" j="<<j<<" keyEs="<<keyEs<<" x="<<x<<" y="<<y<<flush;
          }
          y+=dY;
      }
      x+=dX;
  }
  // аппроксимация пространственного распределения ионизации
  form();
  nu->form();
  //for(i=0; i<nx; i++)
  //{
  //    for(j=0; j<ny; j++)
  //    {
  //        cout<<endl<<"x="<<getCarrierX(i)<<" y="<<getCarrierY(j)<<" f0F2="<<F0F2[ny*i+j]<<" i="<<i<<" j="<<j;
  //    }
  //}
}  

void IRI_3D::ioncorr( bool  key,
                      double lat, double lon, double time, // координаты точки и время, для которых выполняется коррекция
                      double &f1, double &h1, double &f2, double &h2, double &f3, double &h3, // ионосферные параметры после коррекции
                      double &fEs, double &hEs )              // параметры коррекции Es
//
// Функция вводит очередной набор ионосферных параметров, измеренных для заданной ионосферной станции;
// осуществляется прогнозирование этих же параметров и находится ошибка прогнозирования для этой же станции.
// Далее ионосферные параметры в заданной географической точке в соответствующий момент времени
// корректируются на ошибку прогнозирования.
// Выходные параметры: геометрические параметры ионосферных слоев в соответствующий момент времени.
// Если ионосферные параметры заданы нулями, то коррекция ионосферного прогноза не осуществляется;
// при этом будут выданы прогнозируемые ионосферные параметры.
{
  int i;
  float *out_local, *oarr_local;
  int   *jf_local;
  float z1=100., z2=200., zStep=20.;
  float tU;
  int   mes = imd/100;
  double Alt=100., hx, hy, hz, Fh, Dip, Dec, Smodip, f0es, fbes, hmes, pes;
  float lat_f, lon_f, Alt_f, hx_f, hy_f, hz_f, Fh_f, Dip_f, Dec_f, Smodip_f;

  //static double D_foE,D_hmE,D_foF1,D_hmF1,D_foF2,D_hmF2;
  //FILE    *in;

  lat_f=lat;
  lon_f=lon;
  Alt_f=Alt;

  out_local =new float[20*KOL];
  oarr_local = new float[100];
  jf_local=new int[50];

  for(i=0; i<50; i++)
      jf_local[i]=jf[i];
  jf_local[1]=0;
  jf_local[2]=0;
  jf_local[7]=1;
  jf_local[8]=1;
  jf_local[12]=1;
  jf_local[13]=1;
  jf_local[14]=1;
  jf_local[15]=1;
  jf_local[20]=jf_local[25]=jf_local[27]=jf_local[28]=jf_local[29]=
               jf_local[32]=jf_local[33]=jf_local[34]=jf_local[35]=jf_local[36]=jf_local[37]=0;
  for(i=0; i<20*KOL; i++)
    out_local[i]=.0;
  for(i=0; i<100; i++)
    oarr_local[i]=.0;

  if( jf[16] == 0 )
  {
      oarr_local[32] = oarr[32];
      jf_local[16] = jf[16];
  }

  if( jf[26] == 0 )
  {
          oarr_local[38] = oarr[38];
          jf_local[26] = jf[26];
  }

  tU = time;

  if (!key)
  {
      D_foE  = f1;
      D_hmE  = h1;
      D_foF1 = f2;
      D_hmF1 = h2;
      D_foF2 = f3;
      D_hmF2 = h3;
      D_foEs = fEs;
      D_hmEs = hEs;

      //cout<<endl<<"#####  D_foEs = "<<D_foEs<<endl<<flush;

      fieldg_(&lat_f, &lon_f, &Alt_f, &hx_f, &hy_f, &hz_f, &Fh_f, &Dip_f, &Dec_f, &Smodip_f);
      hx=hx_f;
      hy=hy_f;
      hz=hz_f;
      Fh=Fh_f;
      Dip=Dip_f;
      Dec=Dec_f;
      Smodip=Smodip_f;

      if( !eschar(Dip*RAD, lat*RAD, (.2617999*(time-25.)+(lon*RAD)), mes, &f0es, &fbes, &hmes, &pes) )
          keyEs=false;
      else
      {
          if( D_foEs>.0 )
          {
              D_foEs -= fbes;   // f0Es
              keyEs = true;
          }
          if( D_hmEs>.0 )
              D_hmEs -= hmes;   // f0Es
      }
      //cout<<endl<<"############################ Es ##############################"<<endl;
      //cout<<endl<<"keyEs = "<<keyEs<<"; fo = "<<f0es<<"; D_foEs = "<<D_foEs<<endl<<flush;

      iri_sub_( &jf_local[0], &jmag, &lat_f, &lon_f, &iyear, &imd, &tU, &z1, &z2, &zStep, &out_local[0], &oarr_local[0]);

      if( D_foE>.0 )
          D_foE -= sqrt( oarr_local[4]*NeTofn );   // f0E
      if( D_hmE>.0)
          D_hmE -= oarr_local[5];                // hE
      if( D_foF1>.0 )
          D_foF1 -= sqrt( oarr_local[2]*NeTofn );  // f0F1
      if( D_hmF1>.0 )
          D_hmF1 -= oarr_local[3];               // hF1
      if( D_foF2>.0 )
          D_foF2 -= sqrt( oarr_local[0]*NeTofn );  //fF2
      if( D_hmF2>.0 )
          D_hmF2 -= oarr_local[1];               // hF2

      //cout<<endl<<" 222222222 D_foF2 = "<<D_foF2<<" sqrt(oarr_local[0]*NeTofn)="<<sqrt(oarr_local[0]*NeTofn)<<
      //    " t="<<tU-25.<<" iyear="<<iyear<<" imd="<<imd<<" lat="<<lat_f<<"lon="<<lon_f<<flush;
      delete[] out_local;
      delete[] oarr_local;
      delete[] jf_local;

      return;
  }

  iri_sub_(&jf_local[0], &jmag, &lat_f, &lon_f, &iyear, &imd, &tU, &z1, &z2, &zStep, &out_local[0], &oarr_local[0]);
  //if (fabs(fi0/RAD-lon)<1. && fabs((PI05-teta0)/RAD-lat)<1.)
  //        cout<<endl<<" 333333  sqrt(oarr_local[0]*NeTofn)="<<sqrt(oarr_local[0]*NeTofn)<<
  //            " t="<<tU-25.<<" iyear="<<iyear<<" imd="<<imd<<" lat="<<lat<<"lon="<<lon<<flush;

  f1 = D_foE+sqrt(oarr_local[4]*NeTofn);  // f0E
  h1 = D_hmE+oarr_local[5];               // hE
  f2 = D_foF1+sqrt(oarr_local[2]*NeTofn); // f0F1
  h2 = D_hmF1+oarr_local[3];              // hF1
  f3 = D_foF2+sqrt(oarr_local[0]*NeTofn); //fF2
  h3 = D_hmF2+oarr_local[1];              // hF2

  if (f1>.5)
    {
      jf[14]=0;
      oarr[4]=f1;
    }
  else
  {
      f1=.0;
      jf[14]=1;
  }

  if (h1>.0)
    {
      jf[15]=0;
      oarr[5]=h1;
    }
  else
  {
      h1=.0;
      jf[15]=1;
  }

  if (f2>f1)
    {
      jf[12]=0;
      oarr[2]=f2;
    }
  else
  {
      f2=.0;
      jf[12]=1;
  }

  if (h2>.0)
    {
      jf[13]=0;
      oarr[3]=h2;
    }
  else
  {
      h2=.0;
      jf[13]=1;
  }

  if (f3>f1 && f3>f2)
    {
      jf[7]=0;
      oarr[0]=f3;
    }
  else
  {
      f3=0;
      jf[7]=1;
  }

  if (h3>.0)
    {
      jf[8]=0;
      oarr[1]=h3;
    }
  else
  {
      h3=.0;
      jf[8]=1;
  }

  //cout<<endl<<"f1="<<f1<<" h1="<<h1<<" f2="<<f2<<" h2="<<h2<<" f3="<<f3<<" h3="<<h3<<flush;

  delete[] out_local;
  delete[] oarr_local;
  delete[] jf_local;
}

void* appzocsim3DProfil(void *ptr)
{
    ((IRI_3D*)ptr)->getAppzocsim3DProfil();
    return (IRI_3D*)ptr;
}

int ionosf(double fi,     // сферические координаты расположения луча
            double teta,   //
            double r,      //
            double &v,     // нормированный квадрат плазменной частоты
            double &vfi,   // его производные по fi, tets, r
            double &vteta, //
            double &vr)    //
//  Вычисление профиля ионизации и его производных
//
//VGG
{
  double X,Y,Z,dX,dY,dZ,x,y;
  double sF,cF,sT,cT,vx,vy;
  double dxf,dyf,dxt,dyt,cdf,sdf;
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

  iri_3dbase->spcub(x,y,r-iri_3dbase->r0,v,vx,vy,vr,keyX,keyY,keyZ);
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
  vfi=vx*dxf+vy*dyf;
  vteta=vx*dxt+vy*dyt;
  Vx=vfi;
  Vy=vteta;
  Vz=vr;

  key=0;

  return key;
}

int ionosf(double fi,     // сферические координаты расположения луча
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
  Vx=vfi;
  Vy=vteta;
  Vz=vr;
  
  key=0;

  return key;
}

int ionosf(double fi,     // сферические координаты расположения луча
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
  Vx=vfi;
  Vy=vteta;
  Vz=vr;

  vff=vx*dxff+vxx*dxf*dxf+vyy*dyf*dyf+vy*dyff;
  vtt=vx*dxtt+vxx*dxt*dxt+vyy*dyt*dyt+vy*dytt;
  vft=vxx*dxf*dxt+vx*dxft+vyy*dyf*dyt+vy*dyft;
  vfr=vxz*dxf+vyz*dyf;
  vtr=vxz*dxt+vyz*dyt;

  key=0;

  return key;
}

int ionosf(double fi,     // сферические координаты расположения луча
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
  Vx=vfi;
  Vy=vteta;
  Vz=vr;

  vff=vx*dxff+vxx*dxf*dxf+vyy*dyf*dyf+vy*dyff;
  vtt=vx*dxtt+vxx*dxt*dxt+vyy*dyt*dyt+vy*dytt;
  vft=vxx*dxf*dxt+vx*dxft+vyy*dyf*dyt+vy*dyft;
  vfr=vxz*dxf+vyz*dyf;
  vtr=vxz*dxt+vyz*dyt;

  key=0;

  return key;
}

int nuprof(double fi,
            double teta,
            double r,
            double &n)
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

  iri_3dbase->nu->spcub(x,y,r-iri_3dbase->r0,n,keyX,keyY,keyZ,ix,iy,iz);
  key=fabs(keyX)+fabs(keyY);

//  nu_test = iri_3dbase->nu->getCarrier(10,10,140);
//  cout<<" "<<nu_test;

//  test = iri_3dbase->getCarrier(7,7,0);    cout<<" "<<test;
//  test = iri_3dbase->getCarrier(7,7,90);  cout<<" "<<test;

  key=0;

  return key;
}

int nuprof(double fi,
            double teta,
            double r,
            double time,
            double &n)
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

  key=fabs(keyX)+fabs(keyY);

  nt=(n2-n1)/(t2-t1);
  n=(time-t1)*nt+n1;

  key=0;

  return key;
}

void IRI_3D::resetProfil()
// Функция предназначена для сброса данных, оставшихся от предыдущего расчета профиля
//
//VGG
{
  double fi,teta;
  double x,y,z1,z2;
  double hou,lat,lon;
  double f;
  long i,j,k,nn13,kol;

  hou=hour+12.;
  if (hou>24.)
      hou-=24.;
  long iyea=iyear-1;

  long im=imd+600;
  while (im>1231)
      im-=1231;
  if (im<0100)
      im=0131;

  x=xMin;
  hmax=.0;
  y=yMin;
  globalSfCoord(x,y,fi,teta);
  // вычисление высотного распределения ионизации
  // в точке с координатами fi и teta
  lon=fi/RAD;
  lat=(PI05-teta)/RAD;
  z2=zMin+10.*dZ;
  z1=zMin;
  //iri_sub__((int*)&jf[0], (int *)&jmag, &lat, &lon, (int *)&iyea, (int *)&im, &hou, &z1, &z2, &dZ, &out[0], &oarr[0]);
}

void IRI_3D::setYear(int iy)
{
    while(iy>yearMax)
        iy-=11;

    iyear=iy;
}


int ionosf(double fi,     // сферические координаты расположения луча
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

iri_3dbase->spcub(x,y,r-iri_3dbase->r0,v,vx,vy,vr,keyX,keyY,keyZ,ix,iy,iz);
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

int ionosf(double fi,     // сферические координаты расположения луча
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

//cout<<endl<<"0 IRI ionosf"<<flush;
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

iri_3dbase ->spcub(x,y,r-iri_3dbase->r0,v1,vx1,vy1,vr1,keyX,keyY,keyZ,ix,iy,iz);
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
iri_3dbase2->spcub(x,y,r-iri_3dbase->r0,v2,vx2,vy2,vr2,keyX,keyY,keyZ,ix,iy,iz);
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

key=0;

return key;
}

int ionosf(double fi,     // сферические координаты расположения луча
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

int ionosf(double fi,     // сферические координаты расположения луча
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


