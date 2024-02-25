#ifndef DRAWMEM_H

#define DRAWMEM_H

#include "drawmembase.h"
#ifndef QCOLOR_H
#include <qcolor.h>
#endif
//#ifndef QWMATRIX_H
//#include <qwmatrix.h>
//#endif

#ifndef __KolMetka
const int KolMetka=5;
#define __KolMetka
#endif

class DrawMem : public DrawMemBase
{
  public:
    DrawMem( QWidget *parent,
         long k,
             //char *infX, char *infY,
         const QString &infX, const QString &infY,
         double xmin, double xmax, double ymin, double ymax,
         long ir=1, long ipgr=1, long krx=8, long kry=8);
    DrawMem(QWidget *parent,
         long k,
            //char *infX, char *infY,
         const QString &infX, const QString &infY,
         long ir=1, long ipgr=1, long krx=8, long kry=8);
    ~DrawMem();
    void setXY(double *x, double *y, long *n, long size);
    void setX(double *x, long n, long i);
    void setY(double *y, long n, long i);
    void   setColorLine(QColor colL, long nLine){colorLine[nLine]=colL;};
    QColor getColorLine(long nLine){return colorLine[nLine];};
    void   setColorPoint(QColor colP, long nLine){colorPoint[nLine]=colP;};
    QColor getColorPoint(long nLine){return colorPoint[nLine];};
    void   setColorLineMetka(QColor col, int n){if (n<KolMetka && n>=0) colorLineMetka[n]=col;};
    QColor getColorLineMetka(int n){if (n>=KolMetka || n<0) n=0; return colorLineMetka[n];};
    void upDate();
    void setXBegDx(double x_beg, double dx){xBeg=x_beg; Dx=dx;};
    void setYBegDy(double y_beg, double dy){yBeg=y_beg; Dy=dy;};
    void setSizePoint(int size){keyPoint=size;};
    int getSizePoint(){return keyPoint;};
    void clearData(){kolDataX=kolDataY=0; flagRangeX=flagRangeY=false;};
    int getPenWidth(long n){return penWidth[n];};
    void setPenWidth(long width, long n){penWidth[n]=width;};
    void resetData();
    void reDraw();
    void setSizeLineMetka(double x1, double x2, int nMetka)
    {
        if (nMetka<KolMetka)

        {
            x1Metka[nMetka]=x1;
            x2Metka[nMetka]=x2;
        }
    }
  private:
    long   kol;
    long   *n;
    double **x,**y;
    double xBeg,Dx,yBeg,Dy;
    int keyPoint;
    long kolDataX,kolDataY; // kolData=kol,  если все данные заполнены и можно рисовать
    QColor *colorLine, *colorPoint;
    QColor colorLineMetka[KolMetka]; // цвет линейной метки под графиком
    double x1Metka[KolMetka], x2Metka[KolMetka];
    long *penWidth;
    void initData(long k);
    long draw(QPainter &p);
  protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif
