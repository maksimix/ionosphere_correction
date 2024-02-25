#ifndef DRAWCIRCUL_H

#define DRAWCIRCUL_H

#ifndef DRAWCIRCULBASE_H
#include "drawcirculbase.h"
#endif
#ifndef QCOLOR_H
#include <qcolor.h>
#endif
#ifndef QWMATRIX_H
#include <qwmatrix.h>
#endif

class DrawCircul : public DrawCirculBase
{
  public:
    DrawCircul( QWidget *parent,
                long k,
                FlagCirculBase Flag,
                long irx=1, long iry=0, long krx=8, long kry=8);
    ~DrawCircul();
    void setXY(double *x, double *y, long *n, long size);
    void setX(double *x, long n, long i);
    void setY(double *y, long n, long i);
    void   setColorLine(QColor colL, long nLine){colorLine[nLine]=colL;};
    QColor getColorLine(long nLine){return colorLine[nLine];};
    void   setColorPoint(QColor colP, long nLine){colorPoint[nLine]=colP;};
    QColor getColorPoint(long nLine){return colorPoint[nLine];};
    void upDate();
    void setXBegDx(double x_beg, double dx){xBeg=x_beg; Dx=dx;};
    void setYBegDy(double y_beg, double dy){yBeg=y_beg; Dy=dy;};
    void setClear(bool clear){keyClear=clear;};
    bool getClear(){return keyClear;};
    void setSizePoint(int size){keyPoint=size;};
    int getSizePoint(){return keyPoint;};
    void clearData(){kolDataX=kolDataY=0; flagRangeX=flagRangeY=false;};
    int getPenWidth(long n){return penWidth[n];};
    void setPenWidth(long width, long n){penWidth[n]=width;};
  private:
    long   kol;
    long   *n;
    double **x,**y;
    double xBeg,Dx,yBeg,Dy;
    bool keyClear;
    int keyPoint;
    long kolDataX,kolDataY; // kolData=kol,  если все данные заполнены и можно рисовать
    QColor *colorLine, *colorPoint;
    long *penWidth;
    void initData(long k);
    long draw(QPainter &p,
              bool keyClear,
              int keyPoint);
  protected:
      virtual void paintEvent(QPaintEvent *);
};

#endif