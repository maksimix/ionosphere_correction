#ifndef _SOLT_H_
#define _SOLT_H_

using namespace std;
#include "paths.h"
#include <vector>
#include <set>
#include <QThread>

class TrekThread;

template <class T> class LessPutDat
{
public:
    bool operator() (const T* t1, const T* t2)
    {
		return *t1 < *t2;
    };
};

class MySoltA
{
public:
    MySoltA(double F, double T, double Fh, double h[3], double dh[3][3], double dh2[3][3][3], double D0, double Alfa0, int Hop,
            double Delt, double Eps, double Ep, double Ep1, int n,
            double Eps1, double Dd0, PUTDAT* Putdat);
    ~MySoltA();
    void setD0(double d){d0=d;};
    PUTDAT *getPutDat(){return putdat;};
    void setPutDat(PUTDAT* p){putdat=p;};
    long soltA();
    double getResult(){return result;};
    void setResult(double r){result=r;};
    MyTrek *getMyTrek(){return mytrek;};
    int getN(){return n;};
    int getHop(){return ihop;};
private:
    PUTDAT *putdat;
    MyTrek *mytrek;
    double f, t, fh, d0, alfa0, delt, eps, ep, ep1, e, eps1, dd0;
    int ihop, n;
    double result;
};

class MySolt
{
public:
    MySolt(double F, double T, double Fh, double h[3], double dh[3][3], double dh2[3][3][3], int Hop, double S0, double Alfa0, double Dmin, double Dmax,
           double Delt, double Eps, double Ep, double Ep1, int n,
           double Eps1, double Dd0, double Epsa, double Aa0, PUTDAT* putdat);
    MySolt(double S0, double Alfa0,
           double Delt, double Eps, double Ep, double Ep1, int n,
           double Eps1, double Dd0, double Epsa, double Aa0, PUTDAT* putdat);
    ~MySolt();
    long solt();
    bool getFlagMpch(){return flagMpch;};
    void setFlagMpch(bool b){flagMpch=b;};
    double getResult(){return result;};
    void setResult(double r){result=r;};
    double getS0(){return s0;};
    double getAlfa0(){return alfa0;};
    double getEpsS(){return eps1;};
    double getEpsA(){return epsa;};
    double getAa0(){return aa0;};
    double getDd0(){return dd0;};
    int getHop(){return ihop;};
    PUTDAT* getPutdat(){return putdat;};
    void setDelt(double d){delt=d;};
    void setEps(double Eps){eps=Eps; e=e*eps;};
    void setEp(double e){ep=e;};
    void setEp1(double e){ep1=e;};
    double getDelt(){return delt;};
    double getEps(){return eps;};
    double getEp(){return ep;};
    double getEp1(){return ep1;};
    double getE(){return e;};
    void setFr(double F){f=F;};
    double getFr(){return f;};
    void setDmin(double d){d0=d;};
    double getDmin(){return d0;};
    void setDmax(double d){d1=d;};
    double getDmax(){return d1;};
    void setTime(double T){t=T;};
    void setHop(int h){ihop=h;};
    double getMaxS(){return maxS;};
    void setFh(double f, double H[3], double Dh[3][3], double Dh2[3][3][3])
    {
        fh=f;
        for(int i=0; i<3; i++)
        {
            h[i]=H[i];
            for(int j=0; j<3; j++)
            {
                dh[i][j]=Dh[i][j];
                for(int k=0; k<3; k++)
                    dh2[i][j][k]=Dh2[i][j][k];
            }
        }
    };
private:
    std::vector <TrekThread*> vTrekThread;
    std::set < PUTDAT*, LessPutDat<PUTDAT> > sPutDat;
    PUTDAT *putdat;
    double f, t, fh, s0, alfa0, d0, d1, delt, eps, ep, ep1, e, eps1, dd0, epsa, aa0;
    double h[3], dh[3][3], dh2[3][3][3];
    double maxS; // аксимальное расстояние из всех рассчитанных
    int ihop, n;
    double result;
    bool flagMpch;
};

class TrekThread : public QThread
{
public:
    TrekThread(MySolt *ms, MySoltA *msa, double D2=.0, double F2=.0, double D3=.0, double F3=.0) {mySolt=ms; mySoltA=msa; d2=D2; f2=F2; d3=D3; f3=F3;};
    ~TrekThread() {};
    void run();
    MySoltA *getMySoltA(){return mySoltA;};
private:
    MySoltA *mySoltA;
    MySolt  *mySolt;
    double d2,f2,d3,f3;
    double zero_t(double a,
                  double fa,
                  double b,
                  double fb,
                  double s0,
                  double alfa,
                  long   ihop,
                  double tol,
                  double epsa,
                  double aa0,
                  PUTDAT *putdat);
};

double mpchs(MySolt* my);


#endif
