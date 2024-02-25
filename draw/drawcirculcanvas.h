#ifndef DRAWCIRCUL_CANVAS_H

#define DRAWCIRCUL_CANVAS_H

#ifndef DRAWCIRCULBASE_CANVAS_H
#include "drawcirculbasecanvas.h"
#endif
#ifndef QCOLOR_H
#include <qcolor.h>
#endif
#ifndef QWMATRIX_H
#include <qwmatrix.h>
#endif
#ifndef QCANVAS_H
#include <qcanvas.h>
#endif
#ifndef QPOINTARRAY_H
#include <qpointarray.h>
#endif

class DrawCirculCanvas : public DrawCirculBaseCanvas
{
public:
    
    DrawCirculCanvas( QCanvas *canvas, QWidget *parent,
                      long k,
                      FlagCirculBase Flag,
                      long irx=1, long iry=0, long krx=8, long kry=8);
    ~DrawCirculCanvas();
    void setXY(double *x, double *y, long *n, long size);
    void setX(double *x, long n, long i);
    void setY(double *y, long n, long i);
    void setTextInfo(const QString &s);
    void setTextInfA(const QString &s, int i);
    void setTextInfB(const QString &s, int i);
    void setTextInfSig(const QString &s, int i);
    void   setColorLine(QColor colL, long nLine){colorLine[nLine]=colL;};
    QColor getColorLine(long nLine){return colorLine[nLine];};
    void   setColorPoint(QColor colP, long nLine){colorPoint[nLine]=colP;};
    QColor getColorPoint(long nLine){return colorPoint[nLine];};
    void upDate();
    void setXBegDx(double x_beg, double dx){xBeg=x_beg; Dx=dx;};
    void setYBegDy(double y_beg, double dy){yBeg=y_beg; Dy=dy;};
    void setSizePoint(int size){keyPoint=size;};
    int getSizePoint(){return keyPoint;};
    void clearData(){kolDataX=kolDataY=0; flagRangeX=flagRangeY=false;};
    int getPenWidth(long n){return penWidth[n];};
    void setPenWidth(long width, long n){penWidth[n]=width;};
    bool resetData();
    long draw();

private:
    
    long   kol;
    long   *n;
    double **x,**y;
    double xBeg,Dx,yBeg,Dy;
    int    keyPoint;
    long   kolDataX,kolDataY; // kolData=kol,  если все данные заполнены и можно рисовать
    QColor *colorLine, *colorPoint;
    long   *penWidth;
    QCanvasText *info;
    QCanvasText **infA, **infB, **infSig;
    QFontMetrics *fm;
    QFont *font;
    int isw, ish, maxSizeChar;

    void initData(long k);

protected:

    MyCanvasPolygon **diagramma;

    void resizeEvent(QResizeEvent *event);
};

#endif
