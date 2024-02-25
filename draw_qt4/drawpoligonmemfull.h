#ifndef DRAWPOLIGONMEMFULL_H

#define DRAWPOLIGONMEMFULL_H

#include <iostream>
#include <iomanip>
#ifndef DRAWBASEMEM_H
#include "drawmembase.h"
#endif
#ifndef QCOLOR_H
#include <qcolor.h>
#endif
//#ifndef QWMATRIX_H
//#include <qwmatrix.h>
//#endif

#include <list>

#ifndef __ListDouble__
#define __ListDouble__
struct ListDouble
{
    ListDouble()
    {
        nX=n=0;
        y=0;
    }
    ListDouble(double *Y, int nx=0, int N=0)
    {
        flag=true;
        setY(Y,nx,N);
    };
    ListDouble(double X1, double X2, double *Y, int nx=0, int N=0)
    {
        flag=true;
        setY(X1,X2,Y,nx,N);
    };
    ~ListDouble()
    {
        std::cout<<std::endl<<"0 ~ListDouble() countMem="<<countMem<<" n="<<n<<" y="<<(long)y<<std::flush;
        if (y>0)
        {
            countMem-=n*sizeof(double);
            delete[] y;
            y=0;
            std::cout<<std::endl<<"1 ~ListDouble() countMem="<<countMem<<" n="<<n<<" y="<<(long)y<<std::flush;
        }
        n=nX=0;
    };

    double *getY() {return y;};
    double getX1(){return x1;};
    double getX2(){return x2;};
    bool   getFlag(){return flag;};
    void   setFlag(bool b){flag=b;};
    bool   getFlagX(){return flagX;};

    void   setY(double *Y, int nx, int N)
    {
        flagX=false;
        x1=x2=.0;

        nX=nx;
        n=N;
        y=0;
        if (n>0)
        {
            countMem+=n*sizeof(double);
            //std::cout<<std::endl<<"setY countMem"<<countMem<<" n="<<n<<std::flush;
            y=new double[n];
            for(int i=0; i<n; i++)
                y[i]=Y[i];
        }
        else
            y=0;
    };

    void   setY(double X1, double X2, double *Y, int nx, int N)
    {
        flagX=true;
        x1=X1; x2=X2;
        nX=nx;
        n=N;
        y=0;
        if (n>0)
        {
            countMem+=n*sizeof(double);
            y=new double[n];
            for(int i=0; i<n; i++)
                y[i]=Y[i];
        }
        else
            y=0;
    };

    int getNX(){return nX;};
    int getN(){return n;};
    void setNX(int i){nX=i;};
    static long countMem;
private:
    int nX; // номер массива (списка)
    int n;
    bool flag;
    bool flagX; // true - заданы знвчения x1 и x2
    double *y;
    double x1,x2;
};
#endif

class DrawPoligonMemFull : public DrawMemBase
{
public:
    DrawPoligonMemFull( QWidget *parent,
                        //char *infX, char *infY,
                        const QString &infX, const QString &infY,
                        double xmin, double xmax, double ymin, double ymax,
                        long ir=1, long ipgr=1, long krx=8, long kry=8);
    ~DrawPoligonMemFull();
    void setY(double *Y,long n);
    void setY(double X1, double X2, double *Y, long N);
    void reset();
    void upDate();
    void setXBegDx(double x_beg, double dx){xBeg=x_beg; Dx=dx;};
    void setYBegDy(double y_beg, double dy){yBeg=y_beg; Dy=dy;};
    void setColor(bool c){keyColor=c;};
    void   setMinAmp(double a){minAmp=a;};
    double getMinAmp(){return minAmp;};
    double getNormAmp(){return normAmp;};
    void   setNormAmp(double a){normAmp=a;};
    void   reDraw();
    void   setDirect(bool b){keyVert=b;};
    void   setInvert(bool b){keyInvert=b;};
    void   setOrNotROP(bool b){keyOrNotROP=b;};
    bool   getKeyCircle(){return keyCircle;};
    int    getKolOut(){return kolOut;};
private:
    long    x0,y0,x1,y1;
    long    color;
    int     kolOut; // число полос, которые вышли за предел отображения (минус один)
    double  sizex,sizey;
    int  nX; // текущее дискретное значение
    std::list <ListDouble*> listDouble;
    double xBeg,Dx,yBeg,Dy;
    double minAmp, normAmp;
    bool keyColor; // true - цветное изображение
    bool keyPainter;
    bool keyVert;
    bool keyCircle;
    bool keyInvert; // true - бежит снизу вверх, false - сверху вниз
    bool keyOrNotROP;
    bool flagX; // true - заданы знвчения x1 и x2
    long draw(QPainter &p);
    long drawVert(QPainter &p);
protected:
    virtual void paintEvent(QPaintEvent *);
    bool keyFon;
};

#endif
