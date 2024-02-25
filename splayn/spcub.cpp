using namespace std;
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <float.h>
#include "spcub.h"

//VGG 11.1998

//int SPCUB3::count=0;

static void psi(double t,
                double dx,
                double* fi)
/***************************************************************/
/*                                                             */
/* Функция вычисляет значения базиснах функций кубического     */
/* сплайна.                                                    */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  double omt;

  omt    =1.-t;
  *fi    =omt*omt*(2.*t+1.);
  *(fi+1)=1.-*fi;
  *(fi+2)=t*omt*omt*dx;
  *(fi+3)=-t*t*omt*dx;

  return;
} /* psi */

static void psi(double t,
                double dx,
                double* fi,
                double* dfi,
                double* dfi2)
/***************************************************************/
/* Функция вычисляет значения базисных функций кубического     */
/* сплайна и их двух первых производных.                       */
/***************************************************************/
{
  double t2,omt,ttm,dt,omt2;

  t2=t*t;
  omt=1.-t;
  omt2=omt*omt;
  dt=2.*t;
  ttm=3.*t-1.;

  *fi     =omt2*(dt+1.);
  *(fi+1) =1.-*fi;
  *(fi+2) =t*omt2*dx;
  *(fi+3) =-t2*omt*dx;
  *dfi    =-6.*t*omt/dx;
  *(dfi+1)=-*dfi;
  *(dfi+2)=-omt*ttm;
  *(dfi+3)=t*(ttm-1.);
  *dfi2   =6.*(dt-1.)/(dx*dx);
  *(dfi2+1)=-*dfi2;
  *(dfi2+2)=2.*(ttm-1.)/dx;
  *(dfi2+3)=2.*ttm/dx;

  return;
}

static void psi(double t,
                double dx,
                double* fi,
                double* dfi)
/***************************************************************/
/* Функция вычисляет значения базисных функций кубического     */
/* сплайна и их двух первых производных.                       */
/***************************************************************/
{
  double t2,omt,ttm,dt,omt2;

  t2=t*t;
  omt=1.-t;
  omt2=omt*omt;
  dt=2.*t;
  ttm=3.*t-1.;

  *fi     =omt2*(dt+1.);
  *(fi+1) =1.-*fi;
  *(fi+2) =t*omt2*dx;
  *(fi+3) =-t2*omt*dx;
  *dfi    =-6.*t*omt/dx;
  *(dfi+1)=-*dfi;
  *(dfi+2)=-omt*ttm;
  *(dfi+3)=t*(ttm-1.);

  return;
}


SPCUB::SPCUB(long N, double ga, double gb, GRAN k)
  {
    i=0;
    n=N;
    nm=n-1;
    key=k;
    grana=ga;
    granb=gb;

    x =new double[n];
    f =new double[n];
    df=new double[n];
    if (!x || !f || !df)
      {
        cout<<"\nНЕТ ПАМЯТИ ДЛЯ РАЗМЕЩЕНИЯ ОДНОМЕРНОГО СПЛАЙНА"<<endl;
        exit(EXIT_FAILURE);
      }
  }

SPCUB::~SPCUB()
  {
    delete[] x;
    delete[] f;
    delete[] df;
  }

long SPCUB::form()
/***************************************************************/
/*                                                             */
/* Функция предназначена для определения коэффициентов одномер-*/
/* ного кубического сплайна.                                   */
/*                                                             */
/* Функция возвращает 1, если сплайн не может быть построен.   */
/* VGG                                                         */
/***************************************************************/
{
  double alamd,amy;
  double *a,*b,*c,*d;
  long i;
  long im,ip;

  a=new double[n];
  b=new double[n];
  c=new double[n];
  d=new double[n];

  if (!a || !b  || !c || !d)
    {
      cout<<"\nНЕТ ПАМЯТИ ДЛЯ РАЗМЕЩЕНИЯ ОДНОМЕРНОГО СПЛАЙНА"<<endl;
      exit(EXIT_FAILURE);
    }

  for(i=1; i<nm; i++)
    {
      im=i-1;
      ip=i+1;
      alamd=(*(x+ip)-*(x+i))/(*(x+ip)-*(x+im));
      amy  =1.-alamd;
      *(a+i)=alamd;
      *(b+i)=-2.;
      *(c+i)=amy;
      *(d+i)=3.*(alamd*(*(f+i)-*(f+im))/(*(x+i)-*(x+im))+
                 amy*(*(f+ip)-*(f+i))/(*(x+ip)-*(x+i)));
    }

  switch (key)
    {
      case DxDx:
        alamd  =.0;
        amy    =.0;
        *d     =2.*grana;
        *(d+nm)=2.*granb;
        break;
      case D2xD2x:
        alamd  =1.;
        amy    =1.;
        *d     =3.*(*(f+1)-*f)/(*(x+1)-*x)-
                .5*(*(x+1)-*x)*grana;
        *(d+nm)=3.*(*(f+nm)-*(f+nm-1))/(*(x+nm)-*(x+nm-1))+
                .5*(*(x+nm)-*(x+nm-1))*granb;
        break;
      case DxD2x:
        alamd  =.0;
        amy    =1.;
        *d     =2.*grana;
        *(d+nm)=3.*(*(f+nm)-*(f+nm-1))/(*(x+nm)-*(x+nm-1))+
                .5*(*(x+nm)-*(x+nm-1))*granb;
        break;
      case D2xDx:
        alamd  =1.;
        amy    =.0;
        *d     =3.*(*(f+1)-*f)/(*(x+1)-*x)-
                .5*(*(x+1)-*x)*grana;
        *(d+nm)=2.*granb;
    }
  *a     =.0;
  *b     =-2.;
  *c     =alamd;
  *(a+nm)=amy;
  *(b+nm)=-2.;
  *(c+nm)=.0;

  if (progon(df,a,b,c,d,n,.1e-15)) return 1;

  delete[] a;
  delete[] b;
  delete[] c;
  delete[] d;

  return 0;
} /* SPCUB::form */
/////////////////////////////////////////////////////////////////
long SPCUB::spcub(double  X,
                  double& F)
/***************************************************************/
/*                                                             */
/* Функция предназначена для вычисления одномерной кубической  */
/* сплайн-функции.                                             */
/*                                                             */
/* x - значение аргумента;                                     */
/* f -  вычисленное значение функции.                          */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  long   ip,key=0;

  if (X<=*x)
    {
      i=0;
      key=-1;
    }
  else
    if (X>*(x+nm-1))
      {
        i=nm-1;
        key=1;
      }
    else
      {
        while(X<*(x+i))  i--;
        while(X>*(x+i+1)) i++;
      }

  ip=i+1;
  dx=*(x+ip)-*(x+i);
  t=(X-*(x+i))/dx;
  psi(t,dx,fi);

  F=*(f+i)*fi[0]+*(f+ip)*fi[1]+*(df+i)*fi[2]+*(df+ip)*fi[3];

  return key;
} /* SPCUB::spcub */

long SPCUB::spcub(double X,
                  double& F,
                  double& dF)
/***************************************************************/
/*                                                             */
/* Функция предназначена для вычисления одномерной кубической  */
/* сплайн-функции.                                             */
/*                                                             */
/* x - значение аргумента;                                     */
/* f -  вычисленное значение функции.                          */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  long   ip,key=0;

  if (X<=*x)
    {
      i=0;
      key=-1;
    }
  else
    if (X>*(x+nm-1))
      {
        i=nm-1;
        key=1;
      }
    else
      {
        while(X<*(x+i))  i--;
        while(X>*(x+i+1)) i++;
      }

  ip=i+1;
  dx=*(x+ip)-*(x+i);
  t=(X-*(x+i))/dx;
  psi(t,dx,fi,dfi);

  F =*(f+i)*fi[0]+*(f+ip)*fi[1]+*(df+i)*fi[2]+*(df+ip)*fi[3];
  dF=*(f+i)*dfi[0]+*(f+ip)*dfi[1]+*(df+i)*dfi[2]+*(df+ip)*dfi[3];

  return key;
} /* SPCUB::spcub */

long SPCUB::spcub(double X,
                  double& F,
                  double& dF,
                  double& ddF)
/***************************************************************/
/*                                                             */
/* Функция предназначена для вычисления одномерной кубической  */
/* сплайн-функции.                                             */
/*                                                             */
/* x - значение аргумента;                                     */
/* f -  вычисленное значение функции.                          */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  long   ip,key=0;

  if (X<=*x)
    {
      i=0;
      key=-1;
    }
  else
    if (X>*(x+nm-1))
      {
        i=nm-1;
        key=1;
      }
    else
      {
        while(X<*(x+i))  i--;
        while(X>*(x+i+1)) i++;
      }

  ip=i+1;
  dx=*(x+ip)-*(x+i);
  t=(X-*(x+i))/dx;
  psi(t,dx,fi,dfi,ddfi);

  F  =*(f+i)*fi[0]+*(f+ip)*fi[1]+*(df+i)*fi[2]+*(df+ip)*fi[3];
  dF =*(f+i)*dfi[0]+*(f+ip)*dfi[1]+*(df+i)*dfi[2]+*(df+ip)*dfi[3];
  ddF=*(f+i)*ddfi[0]+*(f+ip)*ddfi[1]+*(df+i)*ddfi[2]+*(df+ip)*ddfi[3];

  return key;
} /* SPCUB::spcub */
////////////////////////////////////////////////////////////////

long SPCUB::spcub(double  X,
                  double& F, long &i)
/***************************************************************/
/*                                                             */
/* Функция предназначена для вычисления одномерной кубической  */
/* сплайн-функции.                                             */
/*                                                             */
/* x - значение аргумента;                                     */
/* f -  вычисленное значение функции.                          */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  long ip,key=0;

  if (X<=*x)
    {
      i=0;
      key=-1;
    }
  else
    if (X>*(x+nm-1))
      {
        i=nm-1;
        key=1;
      }
    else
      {
        for(i=0; i<nm; i++)
            if (X>=x[i] && X<x[i+1])
                break;
      }

  ip=i+1;
  dx=*(x+ip)-*(x+i);
  t=(X-*(x+i))/dx;
  psi(t,dx,fi);

  F=*(f+i)*fi[0]+*(f+ip)*fi[1]+*(df+i)*fi[2]+*(df+ip)*fi[3];

  return key;
} /* SPCUB::spcub */

long SPCUB::spcub(double X,
                  double& F,
                  double& dF, long &i)
/***************************************************************/
/*                                                             */
/* Функция предназначена для вычисления одномерной кубической  */
/* сплайн-функции.                                             */
/*                                                             */
/* x - значение аргумента;                                     */
/* f -  вычисленное значение функции.                          */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  long ip,key=0;
  double t,dx;    // рабочие переменные
  double fi[4],dfi[4],ddfi[4];

  if (X<=*x)
    {
      i=0;
      key=-1;
    }
  else
    if (X>*(x+nm-1))
      {
        i=nm-1;
        key=1;
      }
    else
      {
        for(i=0; i<nm; i++)
            if (X>=x[i] && X<x[i+1])
                break;
      }

  ip=i+1;
  dx=*(x+ip)-*(x+i);
  t=(X-*(x+i))/dx;
  psi(t,dx,fi,dfi);

  F =*(f+i)*fi[0]+*(f+ip)*fi[1]+*(df+i)*fi[2]+*(df+ip)*fi[3];
  dF=*(f+i)*dfi[0]+*(f+ip)*dfi[1]+*(df+i)*dfi[2]+*(df+ip)*dfi[3];

  return key;
} /* SPCUB::spcub */

long SPCUB::spcub(double X,
                  double& F,
                  double& dF,
                  double& ddF, long &i)
/***************************************************************/
/*                                                             */
/* Функция предназначена для вычисления одномерной кубической  */
/* сплайн-функции.                                             */
/*                                                             */
/* x - значение аргумента;                                     */
/* f -  вычисленное значение функции.                          */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  long ip,key=0;
  double t,dx;    // рабочие переменные
  double fi[4],dfi[4],ddfi[4];

  if (X<=*x)
    {
      i=0;
      key=-1;
    }
  else
    if (X>*(x+nm-1))
      {
        i=nm-1;
        key=1;
      }
    else
      {
        for(i=0; i<nm; i++)
            if (X>=x[i] && X<x[i+1])
                break;
      }

  ip=i+1;
  dx=*(x+ip)-*(x+i);
  t=(X-*(x+i))/dx;
  psi(t,dx,fi,dfi,ddfi);

  F  =*(f+i)*fi[0]+*(f+ip)*fi[1]+*(df+i)*fi[2]+*(df+ip)*fi[3];
  dF =*(f+i)*dfi[0]+*(f+ip)*dfi[1]+*(df+i)*dfi[2]+*(df+ip)*dfi[3];
  ddF=*(f+i)*ddfi[0]+*(f+ip)*ddfi[1]+*(df+i)*ddfi[2]+*(df+ip)*ddfi[3];

  return key;
} /* SPCUB::spcub */

SPCUB3::SPCUB3(long Nx, long Ny, long Nz,
               double gXa, double gXb, GRAN kX,
               double gYa, double gYb, GRAN kY,
               double gZa, double gZb, GRAN kZ,
               double gX, double gY, double gZ, double gXYZ)
  {
    long i,j;
    
    //count++;
    
    //cout<<endl<<"00 SPCUB3  count="<<count<<flush;

    ix=iy=iz=0;
    ixOld=iyOld=izOld=-1;
    xOld=yOld=zOld=DBL_MAX;
    nx=Nx; ny=Ny; nz=Nz;
    nmx=nx-1;
    nmy=ny-1;
    nmz=nz-1;
    maxXYZ=__max(nx,ny);
    maxXYZ=__max(maxXYZ,nz);
    nXY=nx*ny;
    nXZ=nx*nz;
    nYZ=ny*nz;
    nXYZ=nx*ny*nz;
    keyX=kX; keyY=kY; keyZ=kZ;
    granXa=new double[nYZ];
    granXb=new double[nYZ];
    granYa=new double[nXZ];
    granYb=new double[nXZ];
    granZa=new double[nXY];
    granZb=new double[nXY];
    for(i=0; i<4; i++)
      {
        granX[i]=new double[nx];
        granY[i]=new double[ny];
        granZ[i]=new double[nz];
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
    if (!dfxyz)
      {
        cout<<"\nНЕТ ПАМЯТИ ДЛЯ РАЗМЕЩЕНИЯ ОДНОМЕРНОГО СПЛАЙНА"<<endl;
        exit(EXIT_FAILURE);
      }
    for(i=0; i<4; i++)
      {
        for(j=0; j<nx; j++)
          *(granX[i]+j)=gX;
        for(j=0; j<ny; j++)
          *(granY[i]+j)=gY;
        for(j=0; j<nz; j++)
          *(granZ[i]+j)=gZ;
      }
    for(i=0; i<8; i++)
      granXYZ[i]=gXYZ;

    for(i=0; i<nXY; i++)
      {
        granZa[i]=gZa;
        granZb[i]=gZb;
      }
    for(i=0; i<nXZ; i++)
      {
        granYa[i]=gYa;
        granYb[i]=gYb;
      }
    for(i=0; i<nYZ; i++)
      {
        granXa[i]=gXa;
        granXb[i]=gXb;
      }
  }

SPCUB3::SPCUB3()
{
    long i,j;
    
    //count++;
    
    //cout<<endl<<"11 SPCUB3()  count="<<count<<flush;

    ix=iy=iz=0;
    ixOld=iyOld=izOld=-1;
    xOld=yOld=zOld=DBL_MAX;
    nx=ny=nz=0;
    nmx=nx-1;
    nmy=ny-1;
    nmz=nz-1;
    maxXYZ=__max(nx,ny);
    maxXYZ=__max(maxXYZ,nz);
    nXY=nx*ny;
    nXZ=nx*nz;
    nYZ=ny*nz;
    nXYZ=nx*ny*nz;
    keyX=keyY=keyZ=D2xD2x;
    granXa=0;
    granXb=0;
    granYa=0;
    granYb=0;
    granZa=0;
    granZb=0;
    for(i=0; i<4; i++)
    {
        granX[i]=0;
        granY[i]=0;
        granZ[i]=0;
    }
    x =0;
    y =0;
    z =0;
    f    =0;
    dfx  =0;
    dfy  =0;
    dfz  =0;
    dfxy =0;
    dfxz =0;
    dfyz =0;
    dfxyz=0;
    for(i=0; i<8; i++)
      granXYZ[i]=.0;
}

SPCUB3::SPCUB3(SPCUB3 &sp)
{
    long i,j;

    //count++;

    //cout<<endl<<"copy SPCUB3()  count="<<count<<flush;
   
    ix=iy=iz=0;
    ixOld=iyOld=izOld=-1;
    xOld=yOld=zOld=DBL_MAX;
    nx=sp.nx;
    ny=sp.ny;
    nz=sp.nz;
    nmx=nx-1;
    nmy=ny-1;
    nmz=nz-1;
    maxXYZ=__max(nx,ny);
    maxXYZ=__max(maxXYZ,nz);
    keyX=sp.keyX; keyY=sp.keyY; keyZ=sp.keyZ;

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
        x[i]=sp.x[i];
#pragma omp parallel for 	
    for(int i=0; i<ny; i++)
        y[i]=sp.y[i];
#pragma omp parallel for 	
    for(int i=0; i<nz; i++)
        z[i]=sp.z[i];
 
#pragma omp parallel for      
    for(int i=0; i<nXYZ; i++)
    {
        f[i]=sp.f[i];
        dfx[i]=sp.dfx[i];
        dfy[i]=sp.dfy[i];
        dfz[i]=sp.dfz[i];
        dfxy[i]=sp.dfxy[i];
        dfxz[i]=sp.dfxz[i];
        dfyz[i]=sp.dfyz[i];
        dfxyz[i]=sp.dfxyz[i];
    }
}

SPCUB3::~SPCUB3()
{
    //count--;
    
    //cout<<endl<<"1 ~SPCUB3()  count="<<count<<flush;
    if (x)
        delete[] x;
    if (y)
        delete[] y;
    if (z)
        delete[] z;
    //cout<<endl<<"2 ~SPCUB3()"<<flush;
    if (f)
	delete[] f;
    if (dfx)
	delete[] dfx;
    if (dfy)
	delete[] dfy;
    if (dfz)
	delete[] dfz;
    if (dfxy)
	delete[] dfxy;
    if (dfxz)
	delete[] dfxz;
    if (dfyz)
	delete[] dfyz;
    if (dfxyz)
	delete[] dfxyz;
    //cout<<endl<<"3 ~SPCUB3()"<<flush;
    if (granXa)
	delete[] granXa;
    if (granXb)
	delete[] granXb;
    if (granYa)
	delete[] granYa;
    if (granYb)
	delete[] granYb;
    if (granZa)
	delete[] granZa;
    if (granZb)
	delete[] granZb;
    for(long i=0; i<4; i++)
    {
	if (granX[i])
	    delete[] granX[i];
	if (granY[i])
            delete[] granY[i];
	if (granZ[i])
	    delete[] granZ[i];
    }
    //cout<<endl<<"4 ~SPCUB3()"<<flush;
}

long SPCUB3::form()
/***************************************************************/
/*                                                             */
/* Функция предназначена для определения коэффициентов трехмер-*/
/* ного кубического сплайна.                                   */
/*                                                             */
/* Функция возвращает 1, если сплайн не может быть построен.   */
/* VGG                                                         */
/***************************************************************/
{
  long jx,jy,jz;
  SPCUB *sp=new SPCUB(maxXYZ);

  //1. аппроксимация по x; находим dfx
  sp->setN(nx);
  sp->setTypeGran(keyX);
  for(jx=0; jx<nx; jx++)        //  заносим носитель
    sp->setCarrierX(x[jx],jx);
  for(jy=0; jy<ny; jy++)
    for(jz=0; jz<nz; jz++)
    {
      sp->setGran(*(granXa+nz*jy+jz),*(granXb+nz*jy+jz));
      for(jx=0; jx<nx; jx++)
        sp->setCarrier(*(f+(jx*ny+jy)*nz+jz),jx);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jx=0; jx<nx; jx++)
        setCarrierDX(sp->getCarrierDX(jx),jx,jy,jz);
    }

  //2. аппроксимация по y; находим dfy
  sp->setN(ny);
  sp->setTypeGran(keyY);
  for(jy=0; jy<ny; jy++)        //  заносим носитель
    sp->setCarrierX(y[jy],jy);
  for(jx=0; jx<nx; jx++)
    for(jz=0; jz<nz; jz++)
    {
      sp->setGran(*(granYa+nz*jx+jz),*(granYb+nz*jx+jz));
      for(jy=0; jy<ny; jy++)
        sp->setCarrier(*(f+(jx*ny+jy)*nz+jz),jy);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jy=0; jy<ny; jy++)
        setCarrierDY(sp->getCarrierDX(jy),jx,jy,jz);
    }

  //3. аппроксимация по z; находим dfz
  sp->setN(nz);
  sp->setTypeGran(keyZ);
  for(jz=0; jz<nz; jz++)        //  заносим носитель
    sp->setCarrierX(z[jz],jz);
  for(jx=0; jx<nx; jx++)
    for(jy=0; jy<ny; jy++)
    {
      sp->setGran(*(granZa+ny*jx+jy),*(granZb+ny*jx+jy));
      for(jz=0; jz<nz; jz++)
        sp->setCarrier(*(f+(jx*ny+jy)*nz+jz),jz);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jz=0; jz<nz; jz++)
        setCarrierDZ(sp->getCarrierDX(jz),jx,jy,jz);
    }

  //4. аппроксимация по x dfy с использованием d2fxy на ребрах lz0,...,lz3
  sp->setN(nx);
  sp->setTypeGran(DxDx);
  for(jx=0; jx<nx; jx++)        //  заносим носитель
    sp->setCarrierX(x[jx],jx);
  for(jz=0; jz<nz; jz++)
    {
      sp->setGran(*(granZ[0]+jz),*(granZ[1]+jz));
      for(jx=0; jx<nx; jx++)
        sp->setCarrier(getCarrierDY(jx,0,jz),jx);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jx=0; jx<nx; jx++)
        setCarrierDXY(sp->getCarrierDX(jx),jx,0,jz);
      sp->setGran(*(granZ[3]+jz),*(granZ[2]+jz));
      for(jx=0; jx<nx; jx++)
        sp->setCarrier(getCarrierDY(ix,nmy,iz),ix);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jx=0; jx<nx; jx++)
        setCarrierDXY(sp->getCarrierDX(jx),jx,nmy,jz);
    }

  //5. аппроксимация по y dfz с использованием d2fyz на ребрах lx0,...,lx3
  sp->setN(ny);
  sp->setTypeGran(DxDx);
  for(jy=0; jy<ny; jy++)        //  заносим носитель
    sp->setCarrierX(y[jy],jy);
  for(jx=0; jx<nx; jx++)
    {
      sp->setGran(*(granX[0]+jx),*(granX[1]+jx));
      for(jy=0; jy<ny; jy++)
        sp->setCarrier(getCarrierDZ(jx,jy,0),jy);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jy=0; jy<ny; jy++)
        setCarrierDYZ(sp->getCarrierDX(jy),jx,jy,0);
      sp->setGran(*(granX[3]+jx),*(granX[2]+jx));
      for(jy=0; jy<ny; jy++)
        sp->setCarrier(getCarrierDZ(jx,jy,nmz),jy);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jy=0; jy<ny; jy++)
        setCarrierDYZ(sp->getCarrierDX(jy),jx,jy,nmz);
    }

  //6. аппроксимация по z dfx с использованием d2fxz на ребрах ly0,...,ly3
  sp->setN(nz);
  sp->setTypeGran(DxDx);
  for(jz=0; jz<nz; jz++)        //  заносим носитель
    sp->setCarrierX(z[jz],jz);
  for(jy=0; jy<ny; jy++)
    {
      sp->setGran(*(granY[0]+jy),*(granY[1]+jy));
      for(jz=0; jz<nz; jz++)
        sp->setCarrier(getCarrierDX(0,jy,jz),jz);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jz=0; jz<nz; jz++)
        setCarrierDXZ(sp->getCarrierDX(jz),0,jy,jz);
      sp->setGran(*(granY[3]+jy),*(granY[2]+jy));
      for(jz=0; jz<nz; jz++)
        sp->setCarrier(getCarrierDX(nmx,jy,jz),jz);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jz=0; jz<nz; jz++)
        setCarrierDXZ(sp->getCarrierDX(jz),nmx,jy,jz);
    }

  //7. аппроксимация по y dfx; находим dfxy
  sp->setN(ny);
  sp->setTypeGran(DxDx);
  for(jy=0; jy<ny; jy++)        //  заносим носитель
    sp->setCarrierX(y[jy],jy);
  for(jx=0; jx<nx; jx++)
    for(jz=0; jz<nz; jz++)
    {
      sp->setGran(getCarrierDXY(jx,0,jz),getCarrierDXY(jx,nmy,jz));
      for(jy=0; jy<ny; jy++)
        sp->setCarrier(*(dfx+(jx*ny+jy)*nz+jz),jy);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jy=0; jy<ny; jy++)
        setCarrierDXY(sp->getCarrierDX(jy),jx,jy,jz);
    }

  //8. аппроксимация по z dfy; находим dfyz
  sp->setN(nz);
  sp->setTypeGran(DxDx);
  for(jz=0; jz<nz; jz++)        //  заносим носитель
    sp->setCarrierX(z[jz],jz);
  for(jx=0; jx<nx; jx++)
    for(jy=0; jy<ny; jy++)
    {
      sp->setGran(getCarrierDYZ(jx,jy,0),getCarrierDYZ(jx,jy,nmz));
      for(jz=0; jz<nz; jz++)
        sp->setCarrier(*(dfy+(jx*ny+jy)*nz+jz),jz);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jz=0; jz<nz; jz++)
        setCarrierDYZ(sp->getCarrierDX(jz),jx,jy,jz);
    }

  //9. аппроксимация по x dfz; находим dfxz
  sp->setN(nx);
  sp->setTypeGran(DxDx);
  for(jx=0; jx<nx; jx++)        //  заносим носитель
    sp->setCarrierX(x[jx],jx);
  for(jy=0; jy<ny; jy++)
    for(jz=0; jz<nz; jz++)
    {
      sp->setGran(getCarrierDXZ(0,jy,jz),getCarrierDXZ(nmx,jy,jz));
      for(jx=0; jx<nx; jx++)
        sp->setCarrier(*(dfz+(jx*ny+jy)*nz+jz),jx);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jx=0; jx<nx; jx++)
        setCarrierDXZ(sp->getCarrierDX(jx),jx,jy,jz);
    }

  //10. аппроксимируем по x dfyz вдоль ребер куба lx0,...lx3
  sp->setN(nx);
  sp->setTypeGran(DxDx);
  for(jx=0; jx<nx; jx++)        //  заносим носитель
    sp->setCarrierX(x[jx],jx);
  jy=jz=0; // lx0
  sp->setGran(granXYZ[0],granXYZ[1]);
  for(jx=0; jx<nx; jx++)
    sp->setCarrier(*(dfyz+(jx*ny+jy)*nz+jz),jx);
  if (sp->form())
    {
      delete sp;
      return 1;
    }
  for(jx=0; jx<nx; jx++)
    setCarrierDXYZ(sp->getCarrierDX(jx),jx,jy,jz);
  jy=nmy; jz=0; // lx1
  sp->setGran(granXYZ[2],granXYZ[3]);
  for(jx=0; jx<nx; jx++)
    sp->setCarrier(*(dfyz+(jx*ny+jy)*nz+jz),jx);
  if (sp->form())
    {
      delete sp;
      return 1;
    }
  for(jx=0; jx<nx; jx++)
    setCarrierDXYZ(sp->getCarrierDX(jx),jx,jy,jz);
  jy=nmy; jz=nmz; // lx2
  sp->setGran(granXYZ[4],granXYZ[5]);
  for(jx=0; jx<nx; jx++)
    sp->setCarrier(*(dfyz+(jx*ny+jy)*nz+jz),jx);
  if (sp->form())
    {
      delete sp;
      return 1;
    }
  for(jx=0; jx<nx; jx++)
    setCarrierDXYZ(sp->getCarrierDX(jx),jx,jy,jz);
  jy=0; jz=nmz; // lx3
  sp->setGran(granXYZ[6],granXYZ[7]);
  for(jx=0; jx<nx; jx++)
    sp->setCarrier(*(dfyz+(jx*ny+jy)*nz+jz),jx);
  if (sp->form())
    {
      delete sp;
      return 1;
    }
  for(jx=0; jx<nx; jx++)
    setCarrierDXYZ(sp->getCarrierDX(jx),jx,jy,jz);

  //11. аппроксимация по y dfxz с использованием d3fxyz на ребрах lx0,...,lx3
  sp->setN(ny);
  sp->setTypeGran(DxDx);
  for(jy=0; jy<ny; jy++)        //  заносим носитель
    sp->setCarrierX(y[jy],jy);
  for(jx=0; jx<nx; jx++)
    {
      sp->setGran(getCarrierDXYZ(jx,0,0),getCarrierDXYZ(jx,nmy,0));
      for(jy=0; jy<ny; jy++)
        sp->setCarrier(getCarrierDXZ(jx,jy,0),jy);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jy=0; jy<ny; jy++)
        setCarrierDXYZ(sp->getCarrierDX(jy),jx,jy,0);
      sp->setGran(getCarrierDXYZ(jx,0,nmz),getCarrierDXYZ(jx,nmy,nmz));
      for(jy=0; jy<ny; jy++)
        sp->setCarrier(getCarrierDXZ(jx,jy,nmz),jy);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jy=0; jy<ny; jy++)
        setCarrierDXYZ(sp->getCarrierDX(jy),jx,jy,nmz);
    }

  //12. аппроксимация по z dfxy с использованием df3xyz на гранях oxy1 и oxy2
  sp->setN(nz);
  sp->setTypeGran(DxDx);
  for(jz=0; jz<nz; jz++)        //  заносим носитель
    sp->setCarrierX(z[jz],jz);
  for(jx=0; jx<nx; jx++)
    for(jy=0; jy<ny; jy++)
    {
      sp->setGran(getCarrierDXYZ(jx,jy,0),getCarrierDXYZ(jx,jy,nmz));
      for(jz=0; jz<nz; jz++)
        sp->setCarrier(*(dfxy+(jx*ny+jy)*nz+jz),jz);
      if (sp->form())
        {
          delete sp;
          return 1;
        }
      for(jz=0; jz<nz; jz++)
        setCarrierDXYZ(sp->getCarrierDX(jz),jx,jy,jz);
    }
   delete sp;
   return 0;
} /* SPCUB3::form */

////////////////////////////////////////////////////////////
long SPCUB3::spcub(double X, double Y, double Z, double& F,
                   double& dFx, double& dFy, double& dFz,
                   double& dFxx, double& dFyy, double& dFzz,
                   double& dFxy, double& dFxz, double& dFyz,
                   long &KeyX, long &KeyY, long &KeyZ)
{
  long jx,jy,jz,ixp,iyp,izp;

  KeyX=KeyY=KeyZ=0;
  if (X<x[0])
    {
      KeyX=-1;
      ix=0;
    }
   else
     if (X>x[nmx])
       {
         KeyX=1;
         ix=nmx-1;
       }
      else
        {
          while(X<x[ix])   ix--;
          while(X>x[ix+1]) ix++;
        }
  if (Y<y[0])
    {
      KeyY=-1;
      iy=0;
    }
   else
     if (Y>y[nmy])
       {
         KeyY=1;
         iy=nmy-1;
       }
      else
        {
          while(Y<y[iy])   iy--;
          while(Y>y[iy+1]) iy++;
        }
  if (Z<z[0])
    {
      KeyZ=-1;
      iz=0;
    }
   else
     if (Z>z[nmz])
       {
         KeyZ=1;
         iz=nmz-1;
       }
      else
        {
          while(Z<z[iz])   iz--;
          while(Z>z[iz+1]) iz++;
        }

  if (ix!=ixOld || iy!=iyOld || iz!=izOld)
    {
      ixOld=ix;
      ixp=ix+1;
      dx=x[ixp]-x[ix];
      iyOld=iy;
      iyp=iy+1;
      dy=y[iyp]-y[iy];
      izOld=iz;
      izp=iz+1;
      dz=z[izp]-z[iz];

      C[0][0][0]=*(f+(ix*ny+iy)*nz+iz);
      C[0][0][1]=*(f+(ix*ny+iy)*nz+izp);
      C[0][0][2]=*(dfz+(ix*ny+iy)*nz+iz);
      C[0][0][3]=*(dfz+(ix*ny+iy)*nz+izp);
      C[0][1][0]=*(f+(ix*ny+iyp)*nz+iz);
      C[0][1][1]=*(f+(ix*ny+iyp)*nz+izp);
      C[0][1][2]=*(dfz+(ix*ny+iyp)*nz+iz);
      C[0][1][3]=*(dfz+(ix*ny+iyp)*nz+izp);
      C[0][2][0]=*(dfy+(ix*ny+iy)*nz+iz);
      C[0][2][1]=*(dfy+(ix*ny+iy)*nz+izp);
      C[0][2][2]=*(dfyz+(ix*ny+iy)*nz+iz);
      C[0][2][3]=*(dfyz+(ix*ny+iy)*nz+izp);
      C[0][3][0]=*(dfy+(ix*ny+iyp)*nz+iz);
      C[0][3][1]=*(dfy+(ix*ny+iyp)*nz+izp);
      C[0][3][2]=*(dfyz+(ix*ny+iyp)*nz+iz);
      C[0][3][3]=*(dfyz+(ix*ny+iyp)*nz+izp);
      C[1][0][0]=*(f+(ixp*ny+iy)*nz+iz);
      C[1][0][1]=*(f+(ixp*ny+iy)*nz+izp);
      C[1][0][2]=*(dfz+(ixp*ny+iy)*nz+iz);
      C[1][0][3]=*(dfz+(ixp*ny+iy)*nz+izp);
      C[1][1][0]=*(f+(ixp*ny+iyp)*nz+iz);
      C[1][1][1]=*(f+(ixp*ny+iyp)*nz+izp);
      C[1][1][2]=*(dfz+(ixp*ny+iyp)*nz+iz);
      C[1][1][3]=*(dfz+(ixp*ny+iyp)*nz+izp);
      C[1][2][0]=*(dfy+(ixp*ny+iy)*nz+iz);
      C[1][2][1]=*(dfy+(ixp*ny+iy)*nz+izp);
      C[1][2][2]=*(dfyz+(ixp*ny+iy)*nz+iz);
      C[1][2][3]=*(dfyz+(ixp*ny+iy)*nz+izp);
      C[1][3][0]=*(dfy+(ixp*ny+iyp)*nz+iz);
      C[1][3][1]=*(dfy+(ixp*ny+iyp)*nz+izp);
      C[1][3][2]=*(dfyz+(ixp*ny+iyp)*nz+iz);
      C[1][3][3]=*(dfyz+(ixp*ny+iyp)*nz+izp);
      C[2][0][0]=*(dfx+(ix*ny+iy)*nz+iz);
      C[2][0][1]=*(dfx+(ix*ny+iy)*nz+izp);
      C[2][0][2]=*(dfxz+(ix*ny+iy)*nz+iz);
      C[2][0][3]=*(dfxz+(ix*ny+iy)*nz+izp);
      C[2][1][0]=*(dfx+(ix*ny+iyp)*nz+iz);
      C[2][1][1]=*(dfx+(ix*ny+iyp)*nz+izp);
      C[2][1][2]=*(dfxz+(ix*ny+iyp)*nz+iz);
      C[2][1][3]=*(dfxz+(ix*ny+iyp)*nz+izp);
      C[2][2][0]=*(dfxy+(ix*ny+iy)*nz+iz);
      C[2][2][1]=*(dfxy+(ix*ny+iy)*nz+izp);
      C[2][2][2]=*(dfxyz+(ix*ny+iy)*nz+iz);
      C[2][2][3]=*(dfxyz+(ix*ny+iy)*nz+izp);
      C[2][3][0]=*(dfxy+(ix*ny+iyp)*nz+iz);
      C[2][3][1]=*(dfxy+(ix*ny+iyp)*nz+izp);
      C[2][3][2]=*(dfxyz+(ix*ny+iyp)*nz+iz);
      C[2][3][3]=*(dfxyz+(ix*ny+iyp)*nz+izp);
      C[3][0][0]=*(dfx+(ixp*ny+iy)*nz+iz);
      C[3][0][1]=*(dfx+(ixp*ny+iy)*nz+izp);
      C[3][0][2]=*(dfxz+(ixp*ny+iy)*nz+iz);
      C[3][0][3]=*(dfxz+(ixp*ny+iy)*nz+izp);
      C[3][1][0]=*(dfx+(ixp*ny+iyp)*nz+iz);
      C[3][1][1]=*(dfx+(ixp*ny+iyp)*nz+izp);
      C[3][1][2]=*(dfxz+(ixp*ny+iyp)*nz+iz);
      C[3][1][3]=*(dfxz+(ixp*ny+iyp)*nz+izp);
      C[3][2][0]=*(dfxy+(ixp*ny+iy)*nz+iz);
      C[3][2][1]=*(dfxy+(ixp*ny+iy)*nz+izp);
      C[3][2][2]=*(dfxyz+(ixp*ny+iy)*nz+iz);
      C[3][2][3]=*(dfxyz+(ixp*ny+iy)*nz+izp);
      C[3][3][0]=*(dfxy+(ixp*ny+iyp)*nz+iz);
      C[3][3][1]=*(dfxy+(ixp*ny+iyp)*nz+izp);
      C[3][3][2]=*(dfxyz+(ixp*ny+iyp)*nz+iz);
      C[3][3][3]=*(dfxyz+(ixp*ny+iyp)*nz+izp);
    }

  if (X!=xOld)
    {
      xOld=X;
      tx=(X-x[ix])/dx;
      psi(tx,dx,fbx,dfbx,ddfbx);
    }
  if (Y!=yOld)
    {
      yOld=Y;
      ty=(Y-y[iy])/dy;
      psi(ty,dy,fby,dfby,ddfby);
    }
  if (Z!=zOld)
    {
      zOld=Z;
      tz=(Z-z[iz])/dz;
      psi(tz,dz,fbz,dfbz,ddfbz);
    }

  F=dFx=dFy=dFz=.0;
  dFxx=dFyy=dFzz=.0;
  dFxy=dFyz=dFxz=.0;
  for(jx=0; jx<4; jx++)
    {
      s1=s4=s5=s7=s8=s9=.0;
      for(jy=0; jy<4; jy++)
        {
          s2=s3=s6=.0;
          for(jz=0; jz<4; jz++)
            {
              s2+=C[jx][jy][jz]*fbz[jz];
              s3+=C[jx][jy][jz]*dfbz[jz];
              s6+=C[jx][jy][jz]*ddfbz[jz];
            }
           s1+=s2*fby[jy];
           s4+=s2*dfby[jy];
           s5+=s3*fby[jy];
           s7+=s6*fby[jy];
           s8+=s2*ddfby[jy];
           s9+=s3*dfby[jy];
        }
      F+=s1*fbx[jx];
      dFx+=s1*dfbx[jx];
      dFy+=s4*fbx[jx];
      dFz+=s5*fbx[jx];
      dFxx+=s1*ddfbx[jx];
      dFyy+=s8*fbx[jx];
      dFzz+=s7*fbx[jx];
      dFxy+=s4*dfbx[jx];
      dFxz+=s5*dfbx[jx];
      dFyz+=s9*fbx[jx];
    }
  return KeyX*KeyY*KeyZ;
} /* SPCUB3::spcub */

long SPCUB3::spcub(double X, double Y, double Z, double& F,
                   double& dFx, double& dFy, double& dFz,
                   long &KeyX, long &KeyY, long &KeyZ)
{
  long jx,jy,jz,ixp,iyp,izp;

  KeyX=KeyY=KeyZ=0;
  if (X<x[0])
    {
      KeyX=-1;
      ix=0;
    }
   else
     if (X>x[nmx])
       {
         KeyX=1;
         ix=nmx-1;
       }
      else
        {
          while(X<x[ix])   ix--;
          while(X>x[ix+1]) ix++;
        }
  if (Y<y[0])
    {
      KeyY=-1;
      iy=0;
    }
   else
     if (Y>y[nmy])
       {
         KeyY=1;
         iy=nmy-1;
       }
      else
        {
          while(Y<y[iy])   iy--;
          while(Y>y[iy+1]) iy++;
        }
  if (Z<z[0])
    {
      KeyZ=-1;
      iz=0;
    }
   else
     if (Z>z[nmz])
       {
         KeyZ=1;
         iz=nmz-1;
       }
      else
        {
          while(Z<z[iz])   iz--;
          while(Z>z[iz+1]) iz++;
        }

  if (ix!=ixOld || iy!=iyOld || iz!=izOld)
    {
      ixOld=ix;
      ixp=ix+1;
      dx=x[ixp]-x[ix];
      iyOld=iy;
      iyp=iy+1;
      dy=y[iyp]-y[iy];
      izOld=iz;
      izp=iz+1;
      dz=z[izp]-z[iz];

      C[0][0][0]=*(f+(ix*ny+iy)*nz+iz);
      C[0][0][1]=*(f+(ix*ny+iy)*nz+izp);
      C[0][0][2]=*(dfz+(ix*ny+iy)*nz+iz);
      C[0][0][3]=*(dfz+(ix*ny+iy)*nz+izp);
      C[0][1][0]=*(f+(ix*ny+iyp)*nz+iz);
      C[0][1][1]=*(f+(ix*ny+iyp)*nz+izp);
      C[0][1][2]=*(dfz+(ix*ny+iyp)*nz+iz);
      C[0][1][3]=*(dfz+(ix*ny+iyp)*nz+izp);
      C[0][2][0]=*(dfy+(ix*ny+iy)*nz+iz);
      C[0][2][1]=*(dfy+(ix*ny+iy)*nz+izp);
      C[0][2][2]=*(dfyz+(ix*ny+iy)*nz+iz);
      C[0][2][3]=*(dfyz+(ix*ny+iy)*nz+izp);
      C[0][3][0]=*(dfy+(ix*ny+iyp)*nz+iz);
      C[0][3][1]=*(dfy+(ix*ny+iyp)*nz+izp);
      C[0][3][2]=*(dfyz+(ix*ny+iyp)*nz+iz);
      C[0][3][3]=*(dfyz+(ix*ny+iyp)*nz+izp);
      C[1][0][0]=*(f+(ixp*ny+iy)*nz+iz);
      C[1][0][1]=*(f+(ixp*ny+iy)*nz+izp);
      C[1][0][2]=*(dfz+(ixp*ny+iy)*nz+iz);
      C[1][0][3]=*(dfz+(ixp*ny+iy)*nz+izp);
      C[1][1][0]=*(f+(ixp*ny+iyp)*nz+iz);
      C[1][1][1]=*(f+(ixp*ny+iyp)*nz+izp);
      C[1][1][2]=*(dfz+(ixp*ny+iyp)*nz+iz);
      C[1][1][3]=*(dfz+(ixp*ny+iyp)*nz+izp);
      C[1][2][0]=*(dfy+(ixp*ny+iy)*nz+iz);
      C[1][2][1]=*(dfy+(ixp*ny+iy)*nz+izp);
      C[1][2][2]=*(dfyz+(ixp*ny+iy)*nz+iz);
      C[1][2][3]=*(dfyz+(ixp*ny+iy)*nz+izp);
      C[1][3][0]=*(dfy+(ixp*ny+iyp)*nz+iz);
      C[1][3][1]=*(dfy+(ixp*ny+iyp)*nz+izp);
      C[1][3][2]=*(dfyz+(ixp*ny+iyp)*nz+iz);
      C[1][3][3]=*(dfyz+(ixp*ny+iyp)*nz+izp);
      C[2][0][0]=*(dfx+(ix*ny+iy)*nz+iz);
      C[2][0][1]=*(dfx+(ix*ny+iy)*nz+izp);
      C[2][0][2]=*(dfxz+(ix*ny+iy)*nz+iz);
      C[2][0][3]=*(dfxz+(ix*ny+iy)*nz+izp);
      C[2][1][0]=*(dfx+(ix*ny+iyp)*nz+iz);
      C[2][1][1]=*(dfx+(ix*ny+iyp)*nz+izp);
      C[2][1][2]=*(dfxz+(ix*ny+iyp)*nz+iz);
      C[2][1][3]=*(dfxz+(ix*ny+iyp)*nz+izp);
      C[2][2][0]=*(dfxy+(ix*ny+iy)*nz+iz);
      C[2][2][1]=*(dfxy+(ix*ny+iy)*nz+izp);
      C[2][2][2]=*(dfxyz+(ix*ny+iy)*nz+iz);
      C[2][2][3]=*(dfxyz+(ix*ny+iy)*nz+izp);
      C[2][3][0]=*(dfxy+(ix*ny+iyp)*nz+iz);
      C[2][3][1]=*(dfxy+(ix*ny+iyp)*nz+izp);
      C[2][3][2]=*(dfxyz+(ix*ny+iyp)*nz+iz);
      C[2][3][3]=*(dfxyz+(ix*ny+iyp)*nz+izp);
      C[3][0][0]=*(dfx+(ixp*ny+iy)*nz+iz);
      C[3][0][1]=*(dfx+(ixp*ny+iy)*nz+izp);
      C[3][0][2]=*(dfxz+(ixp*ny+iy)*nz+iz);
      C[3][0][3]=*(dfxz+(ixp*ny+iy)*nz+izp);
      C[3][1][0]=*(dfx+(ixp*ny+iyp)*nz+iz);
      C[3][1][1]=*(dfx+(ixp*ny+iyp)*nz+izp);
      C[3][1][2]=*(dfxz+(ixp*ny+iyp)*nz+iz);
      C[3][1][3]=*(dfxz+(ixp*ny+iyp)*nz+izp);
      C[3][2][0]=*(dfxy+(ixp*ny+iy)*nz+iz);
      C[3][2][1]=*(dfxy+(ixp*ny+iy)*nz+izp);
      C[3][2][2]=*(dfxyz+(ixp*ny+iy)*nz+iz);
      C[3][2][3]=*(dfxyz+(ixp*ny+iy)*nz+izp);
      C[3][3][0]=*(dfxy+(ixp*ny+iyp)*nz+iz);
      C[3][3][1]=*(dfxy+(ixp*ny+iyp)*nz+izp);
      C[3][3][2]=*(dfxyz+(ixp*ny+iyp)*nz+iz);
      C[3][3][3]=*(dfxyz+(ixp*ny+iyp)*nz+izp);
    }

  if (X!=xOld)
    {
      xOld=X;
      tx=(X-x[ix])/dx;
      psi(tx,dx,fbx,dfbx,ddfbx);
    }
  if (Y!=yOld)
    {
      yOld=Y;
      ty=(Y-y[iy])/dy;
      psi(ty,dy,fby,dfby,ddfby);
    }
  if (Z!=zOld)
    {
      zOld=Z;
      tz=(Z-z[iz])/dz;
      psi(tz,dz,fbz,dfbz,ddfbz);
    }

  F=dFx=dFy=dFz=.0;
  for(jx=0; jx<4; jx++)
    {
      s1=s4=s5=.0;
      for(jy=0; jy<4; jy++)
        {
          s2=s3=.0;
          for(jz=0; jz<4; jz++)
            {
              s2+=C[jx][jy][jz]*fbz[jz];
              s3+=C[jx][jy][jz]*dfbz[jz];
            }
           s1+=s2*fby[jy];
           s4+=s2*dfby[jy];
           s5+=s3*fby[jy];
        }
      F+=s1*fbx[jx];
      dFx+=s1*dfbx[jx];
      dFy+=s4*fbx[jx];
      dFz+=s5*fbx[jx];
    }
  return KeyX*KeyY*KeyZ;
} /* SPCUB3::spcub */

long SPCUB3::spcub(double X, double Y, double Z, double& F,
                   long &KeyX, long &KeyY, long &KeyZ)
{
  long jx,jy,jz,ixp,iyp,izp;

  KeyX=KeyY=KeyZ=0;
  if (X<x[0])
    {
      KeyX=-1;
      ix=0;
    }
   else
     if (X>x[nmx])
       {
         KeyX=1;
         ix=nmx-1;
       }
      else
        {
          //while(X<x[ix])   ix--;
          //while(X>=x[ix+1]) ix++;
          for(ix=0; ix<nmx; ix++)
              if (X>=x[ix] && X<x[ix+1])
                  break;
        }
  if (Y<y[0])
    {
      KeyY=-1;
      iy=0;
    }
   else
     if (Y>y[nmy])
       {
         KeyY=1;
         iy=nmy-1;
       }
      else
        {
          //while(Y<y[iy])   iy--;
          //while(Y>=y[iy+1]) iy++;
          for(iy=0; iy<nmy; iy++)
              if (Y>=y[iy] && Y<y[iy+1])
                  break;
        }
  if (Z<z[0])
    {
      KeyZ=-1;
      iz=0;
    }
   else
     if (Z>z[nmz])
       {
         KeyZ=1;
         iz=nmz-1;
       }
      else
        {
          //while(Z<z[iz])   iz--;
          //while(Z>=z[iz+1]) iz++;
          for(iz=0; iz<nmz; iz++)
              if (Z>=z[iz] && Z<z[iz+1])
                  break;
        }
  if (ix!=ixOld || iy!=iyOld || iz!=izOld)
    {
      ixOld=ix;
      ixp=ix+1;
      dx=x[ixp]-x[ix];
      iyOld=iy;
      iyp=iy+1;
      dy=y[iyp]-y[iy];
      izOld=iz;
      izp=iz+1;
      dz=z[izp]-z[iz];

      C[0][0][0]=*(f+(ix*ny+iy)*nz+iz);
      C[0][0][1]=*(f+(ix*ny+iy)*nz+izp);
      C[0][0][2]=*(dfz+(ix*ny+iy)*nz+iz);
      C[0][0][3]=*(dfz+(ix*ny+iy)*nz+izp);
      C[0][1][0]=*(f+(ix*ny+iyp)*nz+iz);
      C[0][1][1]=*(f+(ix*ny+iyp)*nz+izp);
      C[0][1][2]=*(dfz+(ix*ny+iyp)*nz+iz);
      C[0][1][3]=*(dfz+(ix*ny+iyp)*nz+izp);
      C[0][2][0]=*(dfy+(ix*ny+iy)*nz+iz);
      C[0][2][1]=*(dfy+(ix*ny+iy)*nz+izp);
      C[0][2][2]=*(dfyz+(ix*ny+iy)*nz+iz);
      C[0][2][3]=*(dfyz+(ix*ny+iy)*nz+izp);
      C[0][3][0]=*(dfy+(ix*ny+iyp)*nz+iz);
      C[0][3][1]=*(dfy+(ix*ny+iyp)*nz+izp);
      C[0][3][2]=*(dfyz+(ix*ny+iyp)*nz+iz);
      C[0][3][3]=*(dfyz+(ix*ny+iyp)*nz+izp);
      C[1][0][0]=*(f+(ixp*ny+iy)*nz+iz);
      C[1][0][1]=*(f+(ixp*ny+iy)*nz+izp);
      C[1][0][2]=*(dfz+(ixp*ny+iy)*nz+iz);
      C[1][0][3]=*(dfz+(ixp*ny+iy)*nz+izp);
      C[1][1][0]=*(f+(ixp*ny+iyp)*nz+iz);
      C[1][1][1]=*(f+(ixp*ny+iyp)*nz+izp);
      C[1][1][2]=*(dfz+(ixp*ny+iyp)*nz+iz);
      C[1][1][3]=*(dfz+(ixp*ny+iyp)*nz+izp);
      C[1][2][0]=*(dfy+(ixp*ny+iy)*nz+iz);
      C[1][2][1]=*(dfy+(ixp*ny+iy)*nz+izp);
      C[1][2][2]=*(dfyz+(ixp*ny+iy)*nz+iz);
      C[1][2][3]=*(dfyz+(ixp*ny+iy)*nz+izp);
      C[1][3][0]=*(dfy+(ixp*ny+iyp)*nz+iz);
      C[1][3][1]=*(dfy+(ixp*ny+iyp)*nz+izp);
      C[1][3][2]=*(dfyz+(ixp*ny+iyp)*nz+iz);
      C[1][3][3]=*(dfyz+(ixp*ny+iyp)*nz+izp);
      C[2][0][0]=*(dfx+(ix*ny+iy)*nz+iz);
      C[2][0][1]=*(dfx+(ix*ny+iy)*nz+izp);
      C[2][0][2]=*(dfxz+(ix*ny+iy)*nz+iz);
      C[2][0][3]=*(dfxz+(ix*ny+iy)*nz+izp);
      C[2][1][0]=*(dfx+(ix*ny+iyp)*nz+iz);
      C[2][1][1]=*(dfx+(ix*ny+iyp)*nz+izp);
      C[2][1][2]=*(dfxz+(ix*ny+iyp)*nz+iz);
      C[2][1][3]=*(dfxz+(ix*ny+iyp)*nz+izp);
      C[2][2][0]=*(dfxy+(ix*ny+iy)*nz+iz);
      C[2][2][1]=*(dfxy+(ix*ny+iy)*nz+izp);
      C[2][2][2]=*(dfxyz+(ix*ny+iy)*nz+iz);
      C[2][2][3]=*(dfxyz+(ix*ny+iy)*nz+izp);
      C[2][3][0]=*(dfxy+(ix*ny+iyp)*nz+iz);
      C[2][3][1]=*(dfxy+(ix*ny+iyp)*nz+izp);
      C[2][3][2]=*(dfxyz+(ix*ny+iyp)*nz+iz);
      C[2][3][3]=*(dfxyz+(ix*ny+iyp)*nz+izp);
      C[3][0][0]=*(dfx+(ixp*ny+iy)*nz+iz);
      C[3][0][1]=*(dfx+(ixp*ny+iy)*nz+izp);
      C[3][0][2]=*(dfxz+(ixp*ny+iy)*nz+iz);
      C[3][0][3]=*(dfxz+(ixp*ny+iy)*nz+izp);
      C[3][1][0]=*(dfx+(ixp*ny+iyp)*nz+iz);
      C[3][1][1]=*(dfx+(ixp*ny+iyp)*nz+izp);
      C[3][1][2]=*(dfxz+(ixp*ny+iyp)*nz+iz);
      C[3][1][3]=*(dfxz+(ixp*ny+iyp)*nz+izp);
      C[3][2][0]=*(dfxy+(ixp*ny+iy)*nz+iz);
      C[3][2][1]=*(dfxy+(ixp*ny+iy)*nz+izp);
      C[3][2][2]=*(dfxyz+(ixp*ny+iy)*nz+iz);
      C[3][2][3]=*(dfxyz+(ixp*ny+iy)*nz+izp);
      C[3][3][0]=*(dfxy+(ixp*ny+iyp)*nz+iz);
      C[3][3][1]=*(dfxy+(ixp*ny+iyp)*nz+izp);
      C[3][3][2]=*(dfxyz+(ixp*ny+iyp)*nz+iz);
      C[3][3][3]=*(dfxyz+(ixp*ny+iyp)*nz+izp);
    }

  if (X!=xOld)
    {
      xOld=X;
      tx=(X-x[ix])/dx;
      psi(tx,dx,fbx,dfbx,ddfbx);
    }
  if (Y!=yOld)
    {
      yOld=Y;
      ty=(Y-y[iy])/dy;
      psi(ty,dy,fby,dfby,ddfby);
    }
  if (Z!=zOld)
    {
      zOld=Z;
      tz=(Z-z[iz])/dz;
      psi(tz,dz,fbz,dfbz,ddfbz);
    }

  F=.0;
  for(jx=0; jx<4; jx++)
    {
      s1=.0;
      for(jy=0; jy<4; jy++)
        {
          s2=.0;
          for(jz=0; jz<4; jz++)
            {
              s2+=C[jx][jy][jz]*fbz[jz];
            }
           s1+=s2*fby[jy];
        }
      F+=s1*fbx[jx];
    }

  return KeyX*KeyY*KeyZ;
} /* SPCUB3::spcub */

long SPCUB3::spcub(double X, double Y, double Z, double& F,
                   double& dFx, double& dFy, double& dFz,
                   double& dFxx, double& dFyy, double& dFzz,
                   double& dFxy, double& dFxz, double& dFyz, double &dFxyz,
                   long &KeyX, long &KeyY, long &KeyZ)
{
  long jx,jy,jz,ixp,iyp,izp;

  KeyX=KeyY=KeyZ=0;
  if (X<x[0])
    {
      KeyX=-1;
      ix=0;
    }
   else
     if (X>x[nmx])
       {
         KeyX=1;
         ix=nmx-1;
       }
      else
        {
          while(X<x[ix])   ix--;
          while(X>x[ix+1]) ix++;
        }
  if (Y<y[0])
    {
      KeyY=-1;
      iy=0;
    }
   else
     if (Y>y[nmy])
       {
         KeyY=1;
         iy=nmy-1;
       }
      else
        {
          while(Y<y[iy])   iy--;
          while(Y>y[iy+1]) iy++;
        }
  if (Z<z[0])
    {
      KeyZ=-1;
      iz=0;
    }
   else
     if (Z>z[nmz])
       {
         KeyZ=1;
         iz=nmz-1;
       }
      else
        {
          while(Z<z[iz])   iz--;
          while(Z>z[iz+1]) iz++;
        }
  if (ix!=ixOld || iy!=iyOld || iz!=izOld)
    {
      ixOld=ix;
      ixp=ix+1;
      dx=x[ixp]-x[ix];
      iyOld=iy;
      iyp=iy+1;
      dy=y[iyp]-y[iy];
      izOld=iz;
      izp=iz+1;
      dz=z[izp]-z[iz];

      C[0][0][0]=*(f+(ix*ny+iy)*nz+iz);
      C[0][0][1]=*(f+(ix*ny+iy)*nz+izp);
      C[0][0][2]=*(dfz+(ix*ny+iy)*nz+iz);
      C[0][0][3]=*(dfz+(ix*ny+iy)*nz+izp);
      C[0][1][0]=*(f+(ix*ny+iyp)*nz+iz);
      C[0][1][1]=*(f+(ix*ny+iyp)*nz+izp);
      C[0][1][2]=*(dfz+(ix*ny+iyp)*nz+iz);
      C[0][1][3]=*(dfz+(ix*ny+iyp)*nz+izp);
      C[0][2][0]=*(dfy+(ix*ny+iy)*nz+iz);
      C[0][2][1]=*(dfy+(ix*ny+iy)*nz+izp);
      C[0][2][2]=*(dfyz+(ix*ny+iy)*nz+iz);
      C[0][2][3]=*(dfyz+(ix*ny+iy)*nz+izp);
      C[0][3][0]=*(dfy+(ix*ny+iyp)*nz+iz);
      C[0][3][1]=*(dfy+(ix*ny+iyp)*nz+izp);
      C[0][3][2]=*(dfyz+(ix*ny+iyp)*nz+iz);
      C[0][3][3]=*(dfyz+(ix*ny+iyp)*nz+izp);
      C[1][0][0]=*(f+(ixp*ny+iy)*nz+iz);
      C[1][0][1]=*(f+(ixp*ny+iy)*nz+izp);
      C[1][0][2]=*(dfz+(ixp*ny+iy)*nz+iz);
      C[1][0][3]=*(dfz+(ixp*ny+iy)*nz+izp);
      C[1][1][0]=*(f+(ixp*ny+iyp)*nz+iz);
      C[1][1][1]=*(f+(ixp*ny+iyp)*nz+izp);
      C[1][1][2]=*(dfz+(ixp*ny+iyp)*nz+iz);
      C[1][1][3]=*(dfz+(ixp*ny+iyp)*nz+izp);
      C[1][2][0]=*(dfy+(ixp*ny+iy)*nz+iz);
      C[1][2][1]=*(dfy+(ixp*ny+iy)*nz+izp);
      C[1][2][2]=*(dfyz+(ixp*ny+iy)*nz+iz);
      C[1][2][3]=*(dfyz+(ixp*ny+iy)*nz+izp);
      C[1][3][0]=*(dfy+(ixp*ny+iyp)*nz+iz);
      C[1][3][1]=*(dfy+(ixp*ny+iyp)*nz+izp);
      C[1][3][2]=*(dfyz+(ixp*ny+iyp)*nz+iz);
      C[1][3][3]=*(dfyz+(ixp*ny+iyp)*nz+izp);
      C[2][0][0]=*(dfx+(ix*ny+iy)*nz+iz);
      C[2][0][1]=*(dfx+(ix*ny+iy)*nz+izp);
      C[2][0][2]=*(dfxz+(ix*ny+iy)*nz+iz);
      C[2][0][3]=*(dfxz+(ix*ny+iy)*nz+izp);
      C[2][1][0]=*(dfx+(ix*ny+iyp)*nz+iz);
      C[2][1][1]=*(dfx+(ix*ny+iyp)*nz+izp);
      C[2][1][2]=*(dfxz+(ix*ny+iyp)*nz+iz);
      C[2][1][3]=*(dfxz+(ix*ny+iyp)*nz+izp);
      C[2][2][0]=*(dfxy+(ix*ny+iy)*nz+iz);
      C[2][2][1]=*(dfxy+(ix*ny+iy)*nz+izp);
      C[2][2][2]=*(dfxyz+(ix*ny+iy)*nz+iz);
      C[2][2][3]=*(dfxyz+(ix*ny+iy)*nz+izp);
      C[2][3][0]=*(dfxy+(ix*ny+iyp)*nz+iz);
      C[2][3][1]=*(dfxy+(ix*ny+iyp)*nz+izp);
      C[2][3][2]=*(dfxyz+(ix*ny+iyp)*nz+iz);
      C[2][3][3]=*(dfxyz+(ix*ny+iyp)*nz+izp);
      C[3][0][0]=*(dfx+(ixp*ny+iy)*nz+iz);
      C[3][0][1]=*(dfx+(ixp*ny+iy)*nz+izp);
      C[3][0][2]=*(dfxz+(ixp*ny+iy)*nz+iz);
      C[3][0][3]=*(dfxz+(ixp*ny+iy)*nz+izp);
      C[3][1][0]=*(dfx+(ixp*ny+iyp)*nz+iz);
      C[3][1][1]=*(dfx+(ixp*ny+iyp)*nz+izp);
      C[3][1][2]=*(dfxz+(ixp*ny+iyp)*nz+iz);
      C[3][1][3]=*(dfxz+(ixp*ny+iyp)*nz+izp);
      C[3][2][0]=*(dfxy+(ixp*ny+iy)*nz+iz);
      C[3][2][1]=*(dfxy+(ixp*ny+iy)*nz+izp);
      C[3][2][2]=*(dfxyz+(ixp*ny+iy)*nz+iz);
      C[3][2][3]=*(dfxyz+(ixp*ny+iy)*nz+izp);
      C[3][3][0]=*(dfxy+(ixp*ny+iyp)*nz+iz);
      C[3][3][1]=*(dfxy+(ixp*ny+iyp)*nz+izp);
      C[3][3][2]=*(dfxyz+(ixp*ny+iyp)*nz+iz);
      C[3][3][3]=*(dfxyz+(ixp*ny+iyp)*nz+izp);
    }

  if (X!=xOld)
    {
      xOld=X;
      tx=(X-x[ix])/dx;
      psi(tx,dx,fbx,dfbx,ddfbx);
    }
  if (Y!=yOld)
    {
      yOld=Y;
      ty=(Y-y[iy])/dy;
      psi(ty,dy,fby,dfby,ddfby);
    }
  if (Z!=zOld)
    {
      zOld=Z;
      tz=(Z-z[iz])/dz;
      psi(tz,dz,fbz,dfbz,ddfbz);
    }

  F=dFx=dFy=dFz=.0;
  dFxx=dFyy=dFzz=.0;
  dFxy=dFyz=dFxz=.0;
  dFxyz=.0;
  for(jx=0; jx<4; jx++)
    {
      s1=s4=s5=s7=s8=s9=.0;
      for(jy=0; jy<4; jy++)
        {
          s2=s3=s6=.0;
          for(jz=0; jz<4; jz++)
            {
              s2+=C[jx][jy][jz]*fbz[jz];
              s3+=C[jx][jy][jz]*dfbz[jz];
              s6+=C[jx][jy][jz]*ddfbz[jz];
            }
           s1+=s2*fby[jy];
           s4+=s2*dfby[jy];
           s5+=s3*fby[jy];
           s7+=s6*fby[jy];
           s8+=s2*ddfby[jy];
           s9+=s3*dfby[jy];
        }
      F+=s1*fbx[jx];
      dFx+=s1*dfbx[jx];
      dFy+=s4*fbx[jx];
      dFz+=s5*fbx[jx];
      dFxx+=s1*ddfbx[jx];
      dFyy+=s8*fbx[jx];
      dFzz+=s7*fbx[jx];
      dFxy+=s4*dfbx[jx];
      dFxz+=s5*dfbx[jx];
      dFyz+=s9*fbx[jx];
      dFxyz+=s9*dfbx[jx];
    }
  return KeyX*KeyY*KeyZ;
} /* SPCUB3::spcub */
///////////////////////////////////////////////////////////

long SPCUB3::spcub(double X, double Y, double Z, double& F,
                   double& dFx, double& dFy, double& dFz,
                   double& dFxx, double& dFyy, double& dFzz,
                   double& dFxy, double& dFxz, double& dFyz,
                   long &KeyX, long &KeyY, long &KeyZ, long &ix, long &iy, long &iz)
{
  int jx,jy,jz,ixp,iyp,izp;
  double fbx[4],fby[4],fbz[4],dfbx[4],dfby[4],dfbz[4], // набор рабочих переменных
         ddfbx[4],ddfby[4],ddfbz[4],C[4][4][4],        // необходимых при вычислении значений
         s1,s2,s3,s4,s5,s6,s7,s8,s9,                   // сплайн-функции
         dx,dy,dz,
         tx,ty,tz;

  KeyX=KeyY=KeyZ=0;
  if (X<x[0])
    {
      KeyX=-1;
      ix=0;
    }
   else
     if (X>x[nmx])
       {
         KeyX=1;
         ix=nmx-1;
       }
      else
        {
         for(ix=0; ix<nmx; ix++)
             if (X>=x[ix] && X<x[ix+1])
                 break;
        }
  if (Y<y[0])
    {
      KeyY=-1;
      iy=0;
    }
   else
     if (Y>y[nmy])
       {
         KeyY=1;
         iy=nmy-1;
       }
      else
        {
         for(iy=0; iy<nmy; iy++)
             if (Y>=y[iy] && Y<y[iy+1])
                 break;
        }
  if (Z<z[0])
    {
      KeyZ=-1;
      iz=0;
    }
   else
     if (Z>z[nmz])
       {
         KeyZ=1;
         iz=nmz-1;
       }
      else
        {
         for(iz=0; iz<nmz; iz++)
             if (Z>=z[iz] && Z<z[iz+1])
                 break;
        }

      ixp=ix+1;
      dx=x[ixp]-x[ix];
      iyp=iy+1;
      dy=y[iyp]-y[iy];
      izp=iz+1;
      dz=z[izp]-z[iz];

      C[0][0][0]=*(f+(ix*ny+iy)*nz+iz);
      C[0][0][1]=*(f+(ix*ny+iy)*nz+izp);
      C[0][0][2]=*(dfz+(ix*ny+iy)*nz+iz);
      C[0][0][3]=*(dfz+(ix*ny+iy)*nz+izp);
      C[0][1][0]=*(f+(ix*ny+iyp)*nz+iz);
      C[0][1][1]=*(f+(ix*ny+iyp)*nz+izp);
      C[0][1][2]=*(dfz+(ix*ny+iyp)*nz+iz);
      C[0][1][3]=*(dfz+(ix*ny+iyp)*nz+izp);
      C[0][2][0]=*(dfy+(ix*ny+iy)*nz+iz);
      C[0][2][1]=*(dfy+(ix*ny+iy)*nz+izp);
      C[0][2][2]=*(dfyz+(ix*ny+iy)*nz+iz);
      C[0][2][3]=*(dfyz+(ix*ny+iy)*nz+izp);
      C[0][3][0]=*(dfy+(ix*ny+iyp)*nz+iz);
      C[0][3][1]=*(dfy+(ix*ny+iyp)*nz+izp);
      C[0][3][2]=*(dfyz+(ix*ny+iyp)*nz+iz);
      C[0][3][3]=*(dfyz+(ix*ny+iyp)*nz+izp);
      C[1][0][0]=*(f+(ixp*ny+iy)*nz+iz);
      C[1][0][1]=*(f+(ixp*ny+iy)*nz+izp);
      C[1][0][2]=*(dfz+(ixp*ny+iy)*nz+iz);
      C[1][0][3]=*(dfz+(ixp*ny+iy)*nz+izp);
      C[1][1][0]=*(f+(ixp*ny+iyp)*nz+iz);
      C[1][1][1]=*(f+(ixp*ny+iyp)*nz+izp);
      C[1][1][2]=*(dfz+(ixp*ny+iyp)*nz+iz);
      C[1][1][3]=*(dfz+(ixp*ny+iyp)*nz+izp);
      C[1][2][0]=*(dfy+(ixp*ny+iy)*nz+iz);
      C[1][2][1]=*(dfy+(ixp*ny+iy)*nz+izp);
      C[1][2][2]=*(dfyz+(ixp*ny+iy)*nz+iz);
      C[1][2][3]=*(dfyz+(ixp*ny+iy)*nz+izp);
      C[1][3][0]=*(dfy+(ixp*ny+iyp)*nz+iz);
      C[1][3][1]=*(dfy+(ixp*ny+iyp)*nz+izp);
      C[1][3][2]=*(dfyz+(ixp*ny+iyp)*nz+iz);
      C[1][3][3]=*(dfyz+(ixp*ny+iyp)*nz+izp);
      C[2][0][0]=*(dfx+(ix*ny+iy)*nz+iz);
      C[2][0][1]=*(dfx+(ix*ny+iy)*nz+izp);
      C[2][0][2]=*(dfxz+(ix*ny+iy)*nz+iz);
      C[2][0][3]=*(dfxz+(ix*ny+iy)*nz+izp);
      C[2][1][0]=*(dfx+(ix*ny+iyp)*nz+iz);
      C[2][1][1]=*(dfx+(ix*ny+iyp)*nz+izp);
      C[2][1][2]=*(dfxz+(ix*ny+iyp)*nz+iz);
      C[2][1][3]=*(dfxz+(ix*ny+iyp)*nz+izp);
      C[2][2][0]=*(dfxy+(ix*ny+iy)*nz+iz);
      C[2][2][1]=*(dfxy+(ix*ny+iy)*nz+izp);
      C[2][2][2]=*(dfxyz+(ix*ny+iy)*nz+iz);
      C[2][2][3]=*(dfxyz+(ix*ny+iy)*nz+izp);
      C[2][3][0]=*(dfxy+(ix*ny+iyp)*nz+iz);
      C[2][3][1]=*(dfxy+(ix*ny+iyp)*nz+izp);
      C[2][3][2]=*(dfxyz+(ix*ny+iyp)*nz+iz);
      C[2][3][3]=*(dfxyz+(ix*ny+iyp)*nz+izp);
      C[3][0][0]=*(dfx+(ixp*ny+iy)*nz+iz);
      C[3][0][1]=*(dfx+(ixp*ny+iy)*nz+izp);
      C[3][0][2]=*(dfxz+(ixp*ny+iy)*nz+iz);
      C[3][0][3]=*(dfxz+(ixp*ny+iy)*nz+izp);
      C[3][1][0]=*(dfx+(ixp*ny+iyp)*nz+iz);
      C[3][1][1]=*(dfx+(ixp*ny+iyp)*nz+izp);
      C[3][1][2]=*(dfxz+(ixp*ny+iyp)*nz+iz);
      C[3][1][3]=*(dfxz+(ixp*ny+iyp)*nz+izp);
      C[3][2][0]=*(dfxy+(ixp*ny+iy)*nz+iz);
      C[3][2][1]=*(dfxy+(ixp*ny+iy)*nz+izp);
      C[3][2][2]=*(dfxyz+(ixp*ny+iy)*nz+iz);
      C[3][2][3]=*(dfxyz+(ixp*ny+iy)*nz+izp);
      C[3][3][0]=*(dfxy+(ixp*ny+iyp)*nz+iz);
      C[3][3][1]=*(dfxy+(ixp*ny+iyp)*nz+izp);
      C[3][3][2]=*(dfxyz+(ixp*ny+iyp)*nz+iz);
      C[3][3][3]=*(dfxyz+(ixp*ny+iyp)*nz+izp);

      tx=(X-x[ix])/dx;
      psi(tx,dx,fbx,dfbx,ddfbx);
      ty=(Y-y[iy])/dy;
      psi(ty,dy,fby,dfby,ddfby);
      tz=(Z-z[iz])/dz;
      psi(tz,dz,fbz,dfbz,ddfbz);

  F=dFx=dFy=dFz=.0;
  dFxx=dFyy=dFzz=.0;
  dFxy=dFyz=dFxz=.0;
  for(jx=0; jx<4; jx++)
    {
      s1=s4=s5=s7=s8=s9=.0;
      for(jy=0; jy<4; jy++)
        {
          s2=s3=s6=.0;
          for(jz=0; jz<4; jz++)
            {
              s2+=C[jx][jy][jz]*fbz[jz];
              s3+=C[jx][jy][jz]*dfbz[jz];
              s6+=C[jx][jy][jz]*ddfbz[jz];
            }
           s1+=s2*fby[jy];
           s4+=s2*dfby[jy];
           s5+=s3*fby[jy];
           s7+=s6*fby[jy];
           s8+=s2*ddfby[jy];
           s9+=s3*dfby[jy];
        }
      F+=s1*fbx[jx];
      dFx+=s1*dfbx[jx];
      dFy+=s4*fbx[jx];
      dFz+=s5*fbx[jx];
      dFxx+=s1*ddfbx[jx];
      dFyy+=s8*fbx[jx];
      dFzz+=s7*fbx[jx];
      dFxy+=s4*dfbx[jx];
      dFxz+=s5*dfbx[jx];
      dFyz+=s9*fbx[jx];
    }
  return KeyX*KeyY*KeyZ;
} /* SPCUB3::spcub */

long SPCUB3::spcub(double X, double Y, double Z, double& F,
                   double& dFx, double& dFy, double& dFz,
                   long &KeyX, long &KeyY, long &KeyZ, long &ix, long &iy, long &iz)
{
  int jx,jy,jz,ixp,iyp,izp;
  double fbx[4],fby[4],fbz[4],dfbx[4],dfby[4],dfbz[4], // набор рабочих переменных
         ddfbx[4],ddfby[4],ddfbz[4],C[4][4][4],        // необходимых при вычислении значений
         s1,s2,s3,s4,s5,s6,s7,s8,s9,                   // сплайн-функции
         dx,dy,dz,
         tx,ty,tz;

  KeyX=KeyY=KeyZ=0;
  if (X<x[0])
    {
      KeyX=-1;
      ix=0;
    }
   else
     if (X>x[nmx])
       {
         KeyX=1;
         ix=nmx-1;
       }
      else
        {
         for(ix=0; ix<nmx; ix++)
             if (X>=x[ix] && X<x[ix+1])
                 break;
        }
  if (Y<y[0])
    {
      KeyY=-1;
      iy=0;
    }
   else
     if (Y>y[nmy])
       {
         KeyY=1;
         iy=nmy-1;
       }
      else
        {
         for(iy=0; iy<nmy; iy++)
             if (Y>=y[iy] && Y<y[iy+1])
                 break;
        }
  if (Z<z[0])
    {
      KeyZ=-1;
      iz=0;
    }
   else
     if (Z>z[nmz])
       {
         KeyZ=1;
         iz=nmz-1;
       }
      else
        {
          for(iz=0; iz<nmz; iz++)
              if (Z>=z[iz] && Z<z[iz+1])
                  break;
        }

      ixp=ix+1;
      dx=x[ixp]-x[ix];
      iyp=iy+1;
      dy=y[iyp]-y[iy];
      izp=iz+1;
      dz=z[izp]-z[iz];

      C[0][0][0]=*(f+(ix*ny+iy)*nz+iz);
      C[0][0][1]=*(f+(ix*ny+iy)*nz+izp);
      C[0][0][2]=*(dfz+(ix*ny+iy)*nz+iz);
      C[0][0][3]=*(dfz+(ix*ny+iy)*nz+izp);
      C[0][1][0]=*(f+(ix*ny+iyp)*nz+iz);
      C[0][1][1]=*(f+(ix*ny+iyp)*nz+izp);
      C[0][1][2]=*(dfz+(ix*ny+iyp)*nz+iz);
      C[0][1][3]=*(dfz+(ix*ny+iyp)*nz+izp);
      C[0][2][0]=*(dfy+(ix*ny+iy)*nz+iz);
      C[0][2][1]=*(dfy+(ix*ny+iy)*nz+izp);
      C[0][2][2]=*(dfyz+(ix*ny+iy)*nz+iz);
      C[0][2][3]=*(dfyz+(ix*ny+iy)*nz+izp);
      C[0][3][0]=*(dfy+(ix*ny+iyp)*nz+iz);
      C[0][3][1]=*(dfy+(ix*ny+iyp)*nz+izp);
      C[0][3][2]=*(dfyz+(ix*ny+iyp)*nz+iz);
      C[0][3][3]=*(dfyz+(ix*ny+iyp)*nz+izp);
      C[1][0][0]=*(f+(ixp*ny+iy)*nz+iz);
      C[1][0][1]=*(f+(ixp*ny+iy)*nz+izp);
      C[1][0][2]=*(dfz+(ixp*ny+iy)*nz+iz);
      C[1][0][3]=*(dfz+(ixp*ny+iy)*nz+izp);
      C[1][1][0]=*(f+(ixp*ny+iyp)*nz+iz);
      C[1][1][1]=*(f+(ixp*ny+iyp)*nz+izp);
      C[1][1][2]=*(dfz+(ixp*ny+iyp)*nz+iz);
      C[1][1][3]=*(dfz+(ixp*ny+iyp)*nz+izp);
      C[1][2][0]=*(dfy+(ixp*ny+iy)*nz+iz);
      C[1][2][1]=*(dfy+(ixp*ny+iy)*nz+izp);
      C[1][2][2]=*(dfyz+(ixp*ny+iy)*nz+iz);
      C[1][2][3]=*(dfyz+(ixp*ny+iy)*nz+izp);
      C[1][3][0]=*(dfy+(ixp*ny+iyp)*nz+iz);
      C[1][3][1]=*(dfy+(ixp*ny+iyp)*nz+izp);
      C[1][3][2]=*(dfyz+(ixp*ny+iyp)*nz+iz);
      C[1][3][3]=*(dfyz+(ixp*ny+iyp)*nz+izp);
      C[2][0][0]=*(dfx+(ix*ny+iy)*nz+iz);
      C[2][0][1]=*(dfx+(ix*ny+iy)*nz+izp);
      C[2][0][2]=*(dfxz+(ix*ny+iy)*nz+iz);
      C[2][0][3]=*(dfxz+(ix*ny+iy)*nz+izp);
      C[2][1][0]=*(dfx+(ix*ny+iyp)*nz+iz);
      C[2][1][1]=*(dfx+(ix*ny+iyp)*nz+izp);
      C[2][1][2]=*(dfxz+(ix*ny+iyp)*nz+iz);
      C[2][1][3]=*(dfxz+(ix*ny+iyp)*nz+izp);
      C[2][2][0]=*(dfxy+(ix*ny+iy)*nz+iz);
      C[2][2][1]=*(dfxy+(ix*ny+iy)*nz+izp);
      C[2][2][2]=*(dfxyz+(ix*ny+iy)*nz+iz);
      C[2][2][3]=*(dfxyz+(ix*ny+iy)*nz+izp);
      C[2][3][0]=*(dfxy+(ix*ny+iyp)*nz+iz);
      C[2][3][1]=*(dfxy+(ix*ny+iyp)*nz+izp);
      C[2][3][2]=*(dfxyz+(ix*ny+iyp)*nz+iz);
      C[2][3][3]=*(dfxyz+(ix*ny+iyp)*nz+izp);
      C[3][0][0]=*(dfx+(ixp*ny+iy)*nz+iz);
      C[3][0][1]=*(dfx+(ixp*ny+iy)*nz+izp);
      C[3][0][2]=*(dfxz+(ixp*ny+iy)*nz+iz);
      C[3][0][3]=*(dfxz+(ixp*ny+iy)*nz+izp);
      C[3][1][0]=*(dfx+(ixp*ny+iyp)*nz+iz);
      C[3][1][1]=*(dfx+(ixp*ny+iyp)*nz+izp);
      C[3][1][2]=*(dfxz+(ixp*ny+iyp)*nz+iz);
      C[3][1][3]=*(dfxz+(ixp*ny+iyp)*nz+izp);
      C[3][2][0]=*(dfxy+(ixp*ny+iy)*nz+iz);
      C[3][2][1]=*(dfxy+(ixp*ny+iy)*nz+izp);
      C[3][2][2]=*(dfxyz+(ixp*ny+iy)*nz+iz);
      C[3][2][3]=*(dfxyz+(ixp*ny+iy)*nz+izp);
      C[3][3][0]=*(dfxy+(ixp*ny+iyp)*nz+iz);
      C[3][3][1]=*(dfxy+(ixp*ny+iyp)*nz+izp);
      C[3][3][2]=*(dfxyz+(ixp*ny+iyp)*nz+iz);
      C[3][3][3]=*(dfxyz+(ixp*ny+iyp)*nz+izp);
      tx=(X-x[ix])/dx;
      psi(tx,dx,fbx,dfbx,ddfbx);
      ty=(Y-y[iy])/dy;
      psi(ty,dy,fby,dfby,ddfby);
      tz=(Z-z[iz])/dz;
      psi(tz,dz,fbz,dfbz,ddfbz);

  F=dFx=dFy=dFz=.0;
  for(jx=0; jx<4; jx++)
    {
      s1=s4=s5=.0;
      for(jy=0; jy<4; jy++)
        {
          s2=s3=.0;
          for(jz=0; jz<4; jz++)
            {
              s2+=C[jx][jy][jz]*fbz[jz];
              s3+=C[jx][jy][jz]*dfbz[jz];
            }
           s1+=s2*fby[jy];
           s4+=s2*dfby[jy];
           s5+=s3*fby[jy];
        }
      F+=s1*fbx[jx];
      dFx+=s1*dfbx[jx];
      dFy+=s4*fbx[jx];
      dFz+=s5*fbx[jx];
    }
  return KeyX*KeyY*KeyZ;
} /* SPCUB3::spcub */

long SPCUB3::spcub(double X, double Y, double Z, double& F,
                   long &KeyX, long &KeyY, long &KeyZ, long &ix, long &iy, long &iz)
{
  int jx,jy,jz,ixp,iyp,izp;
  double fbx[4],fby[4],fbz[4],dfbx[4],dfby[4],dfbz[4], // набор рабочих переменных
         ddfbx[4],ddfby[4],ddfbz[4],C[4][4][4],        // необходимых при вычислении значений
         s1,s2,s3,s4,s5,s6,s7,s8,s9,                   // сплайн-функции
         dx,dy,dz,
         tx,ty,tz;

  KeyX=KeyY=KeyZ=0;
  if (X<x[0])
    {
      KeyX=-1;
      ix=0;
    }
   else
     if (X>x[nmx])
       {
         KeyX=1;
         ix=nmx-1;
       }
      else
        {
          for(ix=0; ix<nmx; ix++)
              if (X>=x[ix] && X<x[ix+1])
                  break;
        }
  if (Y<y[0])
    {
      KeyY=-1;
      iy=0;
    }
   else
     if (Y>y[nmy])
       {
         KeyY=1;
         iy=nmy-1;
       }
      else
        {
          for(iy=0; iy<nmy; iy++)
              if (Y>=y[iy] && Y<y[iy+1])
                  break;
        }
  if (Z<z[0])
    {
      KeyZ=-1;
      iz=0;
    }
   else
     if (Z>z[nmz])
       {
         KeyZ=1;
         iz=nmz-1;
       }
      else
        {
          for(iz=0; iz<nmz; iz++)
              if (Z>=z[iz] && Z<z[iz+1])
                  break;
        }

      ixp=ix+1;
      dx=x[ixp]-x[ix];
      iyp=iy+1;
      dy=y[iyp]-y[iy];
      izp=iz+1;
      dz=z[izp]-z[iz];

      C[0][0][0]=*(f+(ix*ny+iy)*nz+iz);
      C[0][0][1]=*(f+(ix*ny+iy)*nz+izp);
      C[0][0][2]=*(dfz+(ix*ny+iy)*nz+iz);
      C[0][0][3]=*(dfz+(ix*ny+iy)*nz+izp);
      C[0][1][0]=*(f+(ix*ny+iyp)*nz+iz);
      C[0][1][1]=*(f+(ix*ny+iyp)*nz+izp);
      C[0][1][2]=*(dfz+(ix*ny+iyp)*nz+iz);
      C[0][1][3]=*(dfz+(ix*ny+iyp)*nz+izp);
      C[0][2][0]=*(dfy+(ix*ny+iy)*nz+iz);
      C[0][2][1]=*(dfy+(ix*ny+iy)*nz+izp);
      C[0][2][2]=*(dfyz+(ix*ny+iy)*nz+iz);
      C[0][2][3]=*(dfyz+(ix*ny+iy)*nz+izp);
      C[0][3][0]=*(dfy+(ix*ny+iyp)*nz+iz);
      C[0][3][1]=*(dfy+(ix*ny+iyp)*nz+izp);
      C[0][3][2]=*(dfyz+(ix*ny+iyp)*nz+iz);
      C[0][3][3]=*(dfyz+(ix*ny+iyp)*nz+izp);
      C[1][0][0]=*(f+(ixp*ny+iy)*nz+iz);
      C[1][0][1]=*(f+(ixp*ny+iy)*nz+izp);
      C[1][0][2]=*(dfz+(ixp*ny+iy)*nz+iz);
      C[1][0][3]=*(dfz+(ixp*ny+iy)*nz+izp);
      C[1][1][0]=*(f+(ixp*ny+iyp)*nz+iz);
      C[1][1][1]=*(f+(ixp*ny+iyp)*nz+izp);
      C[1][1][2]=*(dfz+(ixp*ny+iyp)*nz+iz);
      C[1][1][3]=*(dfz+(ixp*ny+iyp)*nz+izp);
      C[1][2][0]=*(dfy+(ixp*ny+iy)*nz+iz);
      C[1][2][1]=*(dfy+(ixp*ny+iy)*nz+izp);
      C[1][2][2]=*(dfyz+(ixp*ny+iy)*nz+iz);
      C[1][2][3]=*(dfyz+(ixp*ny+iy)*nz+izp);
      C[1][3][0]=*(dfy+(ixp*ny+iyp)*nz+iz);
      C[1][3][1]=*(dfy+(ixp*ny+iyp)*nz+izp);
      C[1][3][2]=*(dfyz+(ixp*ny+iyp)*nz+iz);
      C[1][3][3]=*(dfyz+(ixp*ny+iyp)*nz+izp);
      C[2][0][0]=*(dfx+(ix*ny+iy)*nz+iz);
      C[2][0][1]=*(dfx+(ix*ny+iy)*nz+izp);
      C[2][0][2]=*(dfxz+(ix*ny+iy)*nz+iz);
      C[2][0][3]=*(dfxz+(ix*ny+iy)*nz+izp);
      C[2][1][0]=*(dfx+(ix*ny+iyp)*nz+iz);
      C[2][1][1]=*(dfx+(ix*ny+iyp)*nz+izp);
      C[2][1][2]=*(dfxz+(ix*ny+iyp)*nz+iz);
      C[2][1][3]=*(dfxz+(ix*ny+iyp)*nz+izp);
      C[2][2][0]=*(dfxy+(ix*ny+iy)*nz+iz);
      C[2][2][1]=*(dfxy+(ix*ny+iy)*nz+izp);
      C[2][2][2]=*(dfxyz+(ix*ny+iy)*nz+iz);
      C[2][2][3]=*(dfxyz+(ix*ny+iy)*nz+izp);
      C[2][3][0]=*(dfxy+(ix*ny+iyp)*nz+iz);
      C[2][3][1]=*(dfxy+(ix*ny+iyp)*nz+izp);
      C[2][3][2]=*(dfxyz+(ix*ny+iyp)*nz+iz);
      C[2][3][3]=*(dfxyz+(ix*ny+iyp)*nz+izp);
      C[3][0][0]=*(dfx+(ixp*ny+iy)*nz+iz);
      C[3][0][1]=*(dfx+(ixp*ny+iy)*nz+izp);
      C[3][0][2]=*(dfxz+(ixp*ny+iy)*nz+iz);
      C[3][0][3]=*(dfxz+(ixp*ny+iy)*nz+izp);
      C[3][1][0]=*(dfx+(ixp*ny+iyp)*nz+iz);
      C[3][1][1]=*(dfx+(ixp*ny+iyp)*nz+izp);
      C[3][1][2]=*(dfxz+(ixp*ny+iyp)*nz+iz);
      C[3][1][3]=*(dfxz+(ixp*ny+iyp)*nz+izp);
      C[3][2][0]=*(dfxy+(ixp*ny+iy)*nz+iz);
      C[3][2][1]=*(dfxy+(ixp*ny+iy)*nz+izp);
      C[3][2][2]=*(dfxyz+(ixp*ny+iy)*nz+iz);
      C[3][2][3]=*(dfxyz+(ixp*ny+iy)*nz+izp);
      C[3][3][0]=*(dfxy+(ixp*ny+iyp)*nz+iz);
      C[3][3][1]=*(dfxy+(ixp*ny+iyp)*nz+izp);
      C[3][3][2]=*(dfxyz+(ixp*ny+iyp)*nz+iz);
      C[3][3][3]=*(dfxyz+(ixp*ny+iyp)*nz+izp);
      tx=(X-x[ix])/dx;
      psi(tx,dx,fbx,dfbx,ddfbx);
      ty=(Y-y[iy])/dy;
      psi(ty,dy,fby,dfby,ddfby);
      tz=(Z-z[iz])/dz;
      psi(tz,dz,fbz,dfbz,ddfbz);

  F=.0;
  for(jx=0; jx<4; jx++)
    {
      s1=.0;
      for(jy=0; jy<4; jy++)
        {
          s2=.0;
          for(jz=0; jz<4; jz++)
            {
              s2+=C[jx][jy][jz]*fbz[jz];
            }
           s1+=s2*fby[jy];
        }
      F+=s1*fbx[jx];
    }

  return KeyX*KeyY*KeyZ;
} /* SPCUB3::spcub */

long SPCUB3::spcub(double X, double Y, double Z, double& F,
                   double& dFx, double& dFy, double& dFz,
                   double& dFxx, double& dFyy, double& dFzz,
                   double& dFxy, double& dFxz, double& dFyz, double &dFxyz,
                   long &KeyX, long &KeyY, long &KeyZ, long &ix, long &iy, long &iz)
{
  int jx,jy,jz,ixp,iyp,izp;
  double fbx[4],fby[4],fbz[4],dfbx[4],dfby[4],dfbz[4], // набор рабочих переменных
         ddfbx[4],ddfby[4],ddfbz[4],C[4][4][4],        // необходимых при вычислении значений
         s1,s2,s3,s4,s5,s6,s7,s8,s9,                   // сплайн-функции
         dx,dy,dz,
         tx,ty,tz;

  KeyX=KeyY=KeyZ=0;
  if (X<x[0])
    {
      KeyX=-1;
      ix=0;
    }
   else
     if (X>x[nmx])
       {
         KeyX=1;
         ix=nmx-1;
       }
      else
        {
         for(ix=0; ix<nmx; ix++)
             if (X>=x[ix] && X<x[ix+1])
                 break;
        }
  if (Y<y[0])
    {
      KeyY=-1;
      iy=0;
    }
   else
     if (Y>y[nmy])
       {
         KeyY=1;
         iy=nmy-1;
       }
      else
        {
         for(iy=0; iy<nmy; iy++)
             if (Y>=y[iy] && Y<y[iy+1])
                 break;
        }
  if (Z<z[0])
    {
      KeyZ=-1;
      iz=0;
    }
   else
     if (Z>z[nmz])
       {
         KeyZ=1;
         iz=nmz-1;
       }
      else
        {
         for(iz=0; iz<nmz; iz++)
             if (Z>=z[iz] && Z<z[iz+1])
                 break;
        }


      ixp=ix+1;
      dx=x[ixp]-x[ix];
      iyp=iy+1;
      dy=y[iyp]-y[iy];
      izp=iz+1;
      dz=z[izp]-z[iz];

      C[0][0][0]=*(f+(ix*ny+iy)*nz+iz);
      C[0][0][1]=*(f+(ix*ny+iy)*nz+izp);
      C[0][0][2]=*(dfz+(ix*ny+iy)*nz+iz);
      C[0][0][3]=*(dfz+(ix*ny+iy)*nz+izp);
      C[0][1][0]=*(f+(ix*ny+iyp)*nz+iz);
      C[0][1][1]=*(f+(ix*ny+iyp)*nz+izp);
      C[0][1][2]=*(dfz+(ix*ny+iyp)*nz+iz);
      C[0][1][3]=*(dfz+(ix*ny+iyp)*nz+izp);
      C[0][2][0]=*(dfy+(ix*ny+iy)*nz+iz);
      C[0][2][1]=*(dfy+(ix*ny+iy)*nz+izp);
      C[0][2][2]=*(dfyz+(ix*ny+iy)*nz+iz);
      C[0][2][3]=*(dfyz+(ix*ny+iy)*nz+izp);
      C[0][3][0]=*(dfy+(ix*ny+iyp)*nz+iz);
      C[0][3][1]=*(dfy+(ix*ny+iyp)*nz+izp);
      C[0][3][2]=*(dfyz+(ix*ny+iyp)*nz+iz);
      C[0][3][3]=*(dfyz+(ix*ny+iyp)*nz+izp);
      C[1][0][0]=*(f+(ixp*ny+iy)*nz+iz);
      C[1][0][1]=*(f+(ixp*ny+iy)*nz+izp);
      C[1][0][2]=*(dfz+(ixp*ny+iy)*nz+iz);
      C[1][0][3]=*(dfz+(ixp*ny+iy)*nz+izp);
      C[1][1][0]=*(f+(ixp*ny+iyp)*nz+iz);
      C[1][1][1]=*(f+(ixp*ny+iyp)*nz+izp);
      C[1][1][2]=*(dfz+(ixp*ny+iyp)*nz+iz);
      C[1][1][3]=*(dfz+(ixp*ny+iyp)*nz+izp);
      C[1][2][0]=*(dfy+(ixp*ny+iy)*nz+iz);
      C[1][2][1]=*(dfy+(ixp*ny+iy)*nz+izp);
      C[1][2][2]=*(dfyz+(ixp*ny+iy)*nz+iz);
      C[1][2][3]=*(dfyz+(ixp*ny+iy)*nz+izp);
      C[1][3][0]=*(dfy+(ixp*ny+iyp)*nz+iz);
      C[1][3][1]=*(dfy+(ixp*ny+iyp)*nz+izp);
      C[1][3][2]=*(dfyz+(ixp*ny+iyp)*nz+iz);
      C[1][3][3]=*(dfyz+(ixp*ny+iyp)*nz+izp);
      C[2][0][0]=*(dfx+(ix*ny+iy)*nz+iz);
      C[2][0][1]=*(dfx+(ix*ny+iy)*nz+izp);
      C[2][0][2]=*(dfxz+(ix*ny+iy)*nz+iz);
      C[2][0][3]=*(dfxz+(ix*ny+iy)*nz+izp);
      C[2][1][0]=*(dfx+(ix*ny+iyp)*nz+iz);
      C[2][1][1]=*(dfx+(ix*ny+iyp)*nz+izp);
      C[2][1][2]=*(dfxz+(ix*ny+iyp)*nz+iz);
      C[2][1][3]=*(dfxz+(ix*ny+iyp)*nz+izp);
      C[2][2][0]=*(dfxy+(ix*ny+iy)*nz+iz);
      C[2][2][1]=*(dfxy+(ix*ny+iy)*nz+izp);
      C[2][2][2]=*(dfxyz+(ix*ny+iy)*nz+iz);
      C[2][2][3]=*(dfxyz+(ix*ny+iy)*nz+izp);
      C[2][3][0]=*(dfxy+(ix*ny+iyp)*nz+iz);
      C[2][3][1]=*(dfxy+(ix*ny+iyp)*nz+izp);
      C[2][3][2]=*(dfxyz+(ix*ny+iyp)*nz+iz);
      C[2][3][3]=*(dfxyz+(ix*ny+iyp)*nz+izp);
      C[3][0][0]=*(dfx+(ixp*ny+iy)*nz+iz);
      C[3][0][1]=*(dfx+(ixp*ny+iy)*nz+izp);
      C[3][0][2]=*(dfxz+(ixp*ny+iy)*nz+iz);
      C[3][0][3]=*(dfxz+(ixp*ny+iy)*nz+izp);
      C[3][1][0]=*(dfx+(ixp*ny+iyp)*nz+iz);
      C[3][1][1]=*(dfx+(ixp*ny+iyp)*nz+izp);
      C[3][1][2]=*(dfxz+(ixp*ny+iyp)*nz+iz);
      C[3][1][3]=*(dfxz+(ixp*ny+iyp)*nz+izp);
      C[3][2][0]=*(dfxy+(ixp*ny+iy)*nz+iz);
      C[3][2][1]=*(dfxy+(ixp*ny+iy)*nz+izp);
      C[3][2][2]=*(dfxyz+(ixp*ny+iy)*nz+iz);
      C[3][2][3]=*(dfxyz+(ixp*ny+iy)*nz+izp);
      C[3][3][0]=*(dfxy+(ixp*ny+iyp)*nz+iz);
      C[3][3][1]=*(dfxy+(ixp*ny+iyp)*nz+izp);
      C[3][3][2]=*(dfxyz+(ixp*ny+iyp)*nz+iz);
      C[3][3][3]=*(dfxyz+(ixp*ny+iyp)*nz+izp);
      tx=(X-x[ix])/dx;
      psi(tx,dx,fbx,dfbx,ddfbx);
      ty=(Y-y[iy])/dy;
      psi(ty,dy,fby,dfby,ddfby);
      tz=(Z-z[iz])/dz;
      psi(tz,dz,fbz,dfbz,ddfbz);

  F=dFx=dFy=dFz=.0;
  dFxx=dFyy=dFzz=.0;
  dFxy=dFyz=dFxz=.0;
  dFxyz=.0;
  for(jx=0; jx<4; jx++)
    {
      s1=s4=s5=s7=s8=s9=.0;
      for(jy=0; jy<4; jy++)
        {
          s2=s3=s6=.0;
          for(jz=0; jz<4; jz++)
            {
              s2+=C[jx][jy][jz]*fbz[jz];
              s3+=C[jx][jy][jz]*dfbz[jz];
              s6+=C[jx][jy][jz]*ddfbz[jz];
            }
           s1+=s2*fby[jy];
           s4+=s2*dfby[jy];
           s5+=s3*fby[jy];
           s7+=s6*fby[jy];
           s8+=s2*ddfby[jy];
           s9+=s3*dfby[jy];
        }
      F+=s1*fbx[jx];
      dFx+=s1*dfbx[jx];
      dFy+=s4*fbx[jx];
      dFz+=s5*fbx[jx];
      dFxx+=s1*ddfbx[jx];
      dFyy+=s8*fbx[jx];
      dFzz+=s7*fbx[jx];
      dFxy+=s4*dfbx[jx];
      dFxz+=s5*dfbx[jx];
      dFyz+=s9*fbx[jx];
      dFxyz+=s9*dfbx[jx];
    }
  return KeyX*KeyY*KeyZ;
} /* SPCUB3::spcub */
