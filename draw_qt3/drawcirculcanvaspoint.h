#ifndef DRAWCIRCUL_CANVAS_POINT_H

#define DRAWCIRCUL_CANVAS_POINT_H

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

class MyCanvasEllipse : public QCanvasEllipse
{
public:
    MyCanvasEllipse(QCanvas *canvas) : QCanvasEllipse(canvas){X1=Y1=X2=Y2=0; setSize(0,0);};
    void setLine(int x1, int y1, int x2, int y2){X1=x1; Y1=y1; X2=x2; Y2=y2;};
private:
    virtual void drawShape( QPainter & p );
    int X1,Y1,X2,Y2;
};

class DrawCirculCanvasPoint : public DrawCirculBaseCanvas
{
public:
    
    DrawCirculCanvasPoint( QCanvas *canvas, QWidget *parent,
                          long k,
                          FlagCirculBase Flag,
                          long irx=1, long iry=0, long krx=8, long kry=8);
    ~DrawCirculCanvasPoint();
    void setXY(double *x, double *y);
    void setX(double x, long i);
    void setY(double y, long i);
    void setTextInfo(const QString &s);
    void setTextInfA(const QString &s, int i);
    void setTextInfB(const QString &s, int i);
    void setTextInfSig(const QString &s, int i);
    void   setColorLine(QColor colL, long nLine){colorLine[nLine]=colL;};
    QColor getColorLine(long nLine){return colorLine[nLine];};
    void   setColorPoint(QColor colP, long nLine){colorPoint[nLine]=colP;};
    QColor getColorPoint(long nLine){return colorPoint[nLine];};
    void upDate();
    void setSizePoint(int size){keyPoint=size;};
    int getSizePoint(){return keyPoint;};
    void clearData(){kolDataX=kolDataY=0; flagRangeX=flagRangeY=false;};
    int getPenWidth(long n){return penWidth[n];};
    void setPenWidth(long width, long n){penWidth[n]=width;};
    bool resetData();
    long draw();

private:
    
    long   kol;
    double *x,*y;
    double *xBeg,*xEnd,*yBeg,*yEnd;
    long   *n;
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

    MyCanvasEllipse **diagramma;

    void resizeEvent(QResizeEvent *event);
};

#endif
