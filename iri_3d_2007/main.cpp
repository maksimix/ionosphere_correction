using namespace std;

#include "iri_3d_new.h"

#include <iomanip>
#include <fstream>
#include <stdio.h>

extern double HmF2,HmF1,HmE,HmD,HmEs,F0F2,F0F1,F0E,F0D,F0Es,FbEs,PEs,fMin,Hi,
              fhTemp,DTemp,ITemp;

int main()
{
    double lon,lat,rmax,zmin,dz,zmax;
    long nx,ny,nz;
    double fi1,teta1,r1,n,v,vfi,vteta,vr;
    int i,iMax;
    char str[256];
    fstream out;

    out.open("out2.txt",ios::out);

    lon=39.0; lat=110.0; rmax=40.; zmin=H0; dz=DZ; nz=NZ; nx=NX; ny=NY;
    iri_3dbase = new IRI_3D(lon,lat,rmax,zmin,dz,nx,ny,nz);
    iri_3dbase->setYear(2007);
    iri_3dbase->setSunIgActiv(0);
    iri_3dbase->setSunActiv(0);
    iri_3dbase->setDay(1215);
    iri_3dbase->getAppzocsim3DProfil();
    zmax=iri_3dbase->getMaxH()/100.;
    
    iMax=(int)((zmax-zmin)/dz+.5);

    out<<"DZ="<<DZ<<" H0="<<H0<<" R0="<<R0<<endl;
    out<<"Lat="<<lat<<"  Lon="<<lon<<endl;
    out<<"zmax="<<zmax<<" zmin="<<zmin<<" dz="<<dz<<" iMax="<<iMax<<endl;
    out<<"W="<<iri_3dbase->getSunActiv()<<" IG="<<iri_3dbase->getSunIgActiv()<<endl;

    fi1=lon*RAD; teta1=(90.-lat)*RAD; r1=zmin+R0;

    for(i=0; i<iMax; i++)
    {
        ionosf(fi1, teta1, 100.*r1, v, vfi, vteta, vr);
        nuprof(fi1, teta1, 100.*r1, n);
        sprintf(str,"%7.3f  %6.3f  %12.5e  %12.5e  %12.5e  %9.5f",100.*(r1-R0),sqrt(fabs(v)),vfi,vteta,vr,n);
        out<<str<<endl;
        //out<<r1-100.*R0<<"   "<<n<<endl;
        r1+=dz;

    }
    out.close();
    return 0;

}
