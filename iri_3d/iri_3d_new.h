#ifndef __IRI_3D_H
#define __IRI_3D_H
#include <math.h>
#include <fstream>
#include "../splayn/spcub.h"

//VGG 14.09.2000
          
#ifndef __PI 
#define __PI
const double PI=3.14159265358979312;
#endif

#ifndef __PI2 
#define __PI2
const double PI2=6.28318530717958624;
#endif
#ifndef __PI05
#define __PI05 
const double PI05=1.57079632679489656;
#endif
#ifndef __RAD
#define __RAD
const double RAD=1.745329251994329548e-2;
#endif
#ifndef __R0
#define __R0
const double R0=63.70;
#endif
#ifndef __H0
#define __H0
const double H0=.5;
#endif
const long   KOL=1000l;
const double NeTofn=8.0645e-11;
const double DZ=.025;
const long   NX=15;
const long   NY=15;
const long   NZ=180;

struct IonPar
{
    double HmF2,HmF1,HmE,HmD,HmEs,F0F2,F0F1,F0E,F0D,F0Es,FbEs,PEs,Hi;
    double fhTemp,DTemp,ITemp;
    IonPar()
    {
        HmF2=HmF1=HmE=HmD=HmEs=F0F2=F0F1=F0E=F0D=F0Es=FbEs=PEs=Hi=.0;
        fhTemp=DTemp=ITemp=.0;
    };
};

int ionosf(double fi,     // сферические координаты расположения луча
            double teta,   //
            double r,      //
            double &v,     // нормированный квадрат плазменной частоты
            double &vfi,   // его производные по fi, tets, r
            double &vteta, //
            double &vr);   //
int ionosf(double fi,     // сферические координаты расположения луча
            double teta,   //
            double r,      //
            double time,
            double &v,     // нормированный квадрат плазменной частоты
            double &vfi,   // его производные по fi, tets, r
            double &vteta, //
            double &vr,    //
            double &vt);   //
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
            double &vtr);    //
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
            double &vtr);   //

int nuprof(double fi,
            double teta,
            double r,
            double &n);
int nuprof(double fi,
            double teta,
            double r,
            double time,
            double &n);

int ionosf(double fi,     // сферические координаты расположения луча
            double teta,   //
            double r,      //
            double &v,     // нормированный квадрат плазменной частоты
            double &vfi,   // его производные по fi, tets, r
            double &vteta, //
            double &vr,
            IonPar &);   //
int ionosf(double fi,     // сферические координаты расположения луча
            double teta,   //
            double r,      //
            double time,
            double &v,     // нормированный квадрат плазменной частоты
            double &vfi,   // его производные по fi, tets, r
            double &vteta, //
            double &vr,    //
            double &vt,
            IonPar &);   //
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
            IonPar &);    //
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
            IonPar &);   //

void* appzocsim3DProfil(void *ptr);

class IRI_3D: public SPCUB3
{
  public:
    IRI_3D(double lon, double lat, double rmax, double zmin, double dz, long nx, long ny, long nz);
    IRI_3D(IRI_3D &iri);
    ~IRI_3D();
    
    //int static countIri;
    
    void globalSfCoord(double x,
                       double y,
                       double &fi,
                       double &teta);
    void ioncorr( bool   key,
                  double lat, double lon, double time, // координаты точки и время, для которых выполняется коррекция
                  double &f1, double &h1, double &f2, double &h2, double &f3, double &h3, // ионосферные параметры после коррекции
                  double &fEs, double &hEs );          // параметры Es
    void getAppzocsim3DProfil();
    void resetProfil();

    void setCoordOporPoint(double fi, double teta){fi0=fi; teta0=teta;};
    void getCoordOporPoint(double &fi, double &teta){fi=fi0; teta=teta0;};
    void setRange(double rMax, double dx, double dy){xMin=yMin=-rMax; xMax=yMax=rMax; dX=dx; dY=dy;};
    void getRange(double &rMax, double &dx, double &dy){rMax=xMax,dx=dX; dy=dY;};
    void setYear(int iy);
    int getYear(){return iyear;};
    void setDay(int day){imd=day;};
    int getDay(){return imd;};
    void   setTime(float hou){hour=hou;};
    float getTime(){return ((hour>24.)? hour-25. : hour);};
    void setKeyCorIon( bool key) { keyCorIon = key; };
    void setOARR(float val, int num){oarr[num]=val;}
    void setCCIR(){jf[4]=1;};
    void setURSI(){jf[4]=0;};
    int  getCCIR_URSI(){return jf[4];};
    void setSunActiv(float w)
    {
        if (w>.0)
        {
            setJF(0,16); oarr[32]=w;
        }
        else
        {
            setJF(1,16);
            setJF(0,24);
            oarr[40]=-w;
        }
    }; // установка солнечной активности
    //
    float getSunActiv(){return oarr[32];}; // чтение солнечной активности
    void   setSunIgActiv(float ig)
    {
        if (ig>.0)
        {
            setJF(0,26);
            oarr[38]=ig;
        }
        else
            setJF(1,26);
    }; // установка солнечной активности

    float getSunIgActiv(){return oarr[38];}; // чтение солнечной активности
    void   setJF(int val, int num){jf[num]=val;};
    bool   getJF(int num){return (bool)jf[num];};
    double getMaxH(){return hmax;};
    double getMinF(){return fmin;};
    double getFMinF2(){return fMinF2;};
    double getf0F2(){return f0F2;};
    double getf0F1(){return f0F1;};
    double getf0E() {return f0E;};
    double getf0D() {return f0D;};
    double gethmF2(){return hmF2;};
    double gethmF1(){return hmF1;};
    double gethmE() {return hmE;};
    double gethmD() {return hmD;};
    bool   getKeyEs(){return keyEs;};
    void   setKeyEs(bool b){keyEs=b;};
    double gethmEs(){return hmEs;};
    double getf0Es(){return f0Es;};
    double getfbEs(){return fbEs;};
    double getPEs(){return PEs;};
    //
    double getf0F2(long i, long j){return F0F2[ny*i+j];};
    double getf0F1(long i, long j){return F0F1[ny*i+j];};
    double getf0E(long i, long j) {return F0E[ny*i+j];};
    double getf0D(long i, long j) {return F0D[ny*i+j];};
    double gethmF2(long i, long j){return HmF2[ny*i+j];};
    double gethmF1(long i, long j){return HmF1[ny*i+j];};
    double gethmE(long i, long j) {return HmE[ny*i+j];};
    double gethmD(long i, long j) {return HmD[ny*i+j];};
    double gethmEs(long i, long j){return HmEs[ny*i+j];};
    double getf0Es(long i, long j){return F0Es[ny*i+j];};
    double getfbEs(long i, long j){return FbEs[ny*i+j];};
    double getPEs(long i, long j) {return pEs[ny*i+j];};
    double getFh(long i, long j) {return fhMag[ny*i+j];};
    double getD(long i, long j) {return DMag[ny*i+j];};
    double getI(long i, long j) {return IMag[ny*i+j];};
    double getHi(long i, long j) {return Hi[ny*i+j];};

  public:
      double sFi0,cFi0,sTeta0;
      double cTeta0,r0,X0,Y0,Z0; // глобальные координаты опорной точки


  private:
    double fi0,teta0; // координаты опорной точки, в окрестности которой оппроксимируется профиль
    double dX,dY,dZ,xMin,xMax,yMin,yMax,zMin,zMax; // область аппроксимации профиля в декартовой системе координат и шаг сетки
    //double sFi0,cFi0,sTeta0;
    double hmax,fmin,fMinF2;
    //double cTeta0,r0,X0,Y0,Z0; // глобальные координаты опорной точки
    double f0F2,hmF2,f0F1,hmF1,f0E,hmE,f0D,hmD; // параметры в опорной точке
    double D_foE, D_hmE, D_foF1, D_hmF1, D_foF2, D_hmF2, D_foEs, D_hmEs;
    double PEs,hmEs,fbEs,f0Es;
    double *F0F2,*HmF2,*F0F1,*HmF1,*F0E,*HmE,*F0D,*HmD,*pEs,*HmEs,*FbEs,*F0Es,*Hi;
    double *fhMag,*IMag,*DMag;

    bool keyCorIon;

    int    *jf;
    int    iyear,  // год
           jmag,   // 0 - географические координаты, 1 - магнитные
           imd;    // день в формате ммдд
    int    monthMax, yearMax;
    float  hour;   // всемирное время в десятичных часах (>24 - всемирное, если задано <24 - местное, то должно быть переведено во свемирное)
    float  tm;     // московское время в рад
    float  *out,*oarr;
    bool   keyEs;
    double **n;

    public:
       SPCUB3 *nu;


  friend int ionosf(double fi,     // сферические координаты расположения луча
                     double teta,   //
                     double r,      //
                     double &v,     // нормированный квадрат плазменной частоты
                     double &vfi,   // его производные по fi, tets, r
                     double &vteta, //
                     double &vr);   //
  friend int ionosf(double fi,     // сферические координаты расположения луча
                     double teta,   //
                     double r,      //
                     double time,
                     double &v,     // нормированный квадрат плазменной частоты
                     double &vfi,   // его производные по fi, tets, r
                     double &vteta, //
                     double &vr,    //
                     double &vt);   //
  friend int ionosf(double fi,     // сферические координаты расположения луча
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
                     double &vtr);    //
  friend int ionosf(double fi,     // сферические координаты расположения луча
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
                     double &vtr);   //
  friend int nuprof(double fi,
                     double teta,
                     double r,
                     double &n);
  friend int nuprof(double fi,
                     double teta,
                     double r,
                     double time,
                     double &n);

  friend int ionosf(double fi,     // сферические координаты расположения луча
                     double teta,   //
                     double r,      //
                     double &v,     // нормированный квадрат плазменной частоты
                     double &vfi,   // его производные по fi, tets, r
                     double &vteta, //
                     double &vr, IonPar &p);   //
  friend int ionosf(double fi,     // сферические координаты расположения луча
                     double teta,   //
                     double r,      //
                     double time,
                     double &v,     // нормированный квадрат плазменной частоты
                     double &vfi,   // его производные по fi, tets, r
                     double &vteta, //
                     double &vr,    //
                     double &vt, IonPar &p);   //
  friend int ionosf(double fi,     // сферические координаты расположения луча
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
                     double &vtr, IonPar &p);    //
  friend int ionosf(double fi,     // сферические координаты расположения луча
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
                     double &vtr, IonPar &p);   //

  friend void* appzocsim3DProfil(void *ptr);
};

extern IRI_3D *iri_3dbase;
extern IRI_3D *iri_3dbase2;
#endif  //iri_3d.hpp
