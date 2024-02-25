//Added by qt3to4:
#include <QResizeEvent>
//#include <Q3PointArray>
#include <QMouseEvent>
#ifndef DRAWCANVAS_H

#define DRAWCANVAS_H

#ifndef DRAWBASECANVAS_H
#include "drawbasecanvas.h"
#endif
#ifndef QCOLOR_H
#include <qcolor.h>
#endif
#ifndef QWMATRIX_H
#include <qmatrix.h>
#endif
#ifndef QOBJECT_H
#include <qobject.h>
#endif

#ifndef __KolMetka
const int KolMetka=5;
#define __KolMetka
#endif

class MyCanvasPolyline : public Q3CanvasLine
{
public:
    MyCanvasPolyline(Q3Canvas *canvas) : Q3CanvasLine(canvas) {Q3CanvasLine::setPen(Qt::NoPen); keyPoint=0;};
    Q3PointArray &getPointArray(){return poly;};
    void setKol(long k){kol=k;};
    void setSizePoint(int n){keyPoint=n;};
    void setColorPoint(QColor c){colorPoint=c;};
    virtual void setPen(QPen pen){penLine=pen;};
private:
    virtual void drawShape( QPainter & painter );
    Q3PointArray poly;
    long kol, keyPoint;
    QPen penLine;
    QColor colorPoint;
};

class DrawCanvas : public DrawBaseCanvas
{
public:
    DrawCanvas( Q3Canvas *canvas, QWidget *parent,
         long k,
         char *infX, char *infY,
         double xmin, double xmax, double ymin, double ymax,
         long ir=1, long ipgr=1, long krx=8, long kry=8);
    DrawCanvas(Q3Canvas *canvas, QWidget *parent,
         long k,
         char *infX, char *infY,
         long ir=1, long ipgr=1, long krx=8, long kry=8);
    ~DrawCanvas();
    void setXY(double *x, double *y, long *n, long size);
    void setX(double *x, long n, long i);
    void setY(double *y, long n, long i);
    void   setColorLine(QColor colL, long nLine){colorLine[nLine]=colL;};
    QColor getColorLine(long nLine){return colorLine[nLine];};
    void   setColorPoint(QColor colP, long nLine)
    {
        colorPoint[nLine]=colP;
        diagramma[nLine]->setColorPoint(colP);
    };
    QColor getColorPoint(long nLine){return colorPoint[nLine];};
    void setColorLineMetka(QColor col, int n){if (n<KolMetka && n>=0) colorLineMetka[n]=col;};
    QColor getColorLineMetka(int n){if (n>=KolMetka || n<0) n=0; return colorLineMetka[n];};
    void upDate();
    void setXBegDx(double x_beg, double dx){xBeg=x_beg; Dx=dx;};
    void setYBegDy(double y_beg, double dy){yBeg=y_beg; Dy=dy;};
    void setClear(bool clear){keyClear=clear;};
    bool getClear(){return keyClear;};
    void setSizePoint(int size)
    {
        keyPoint=size;
        for(int i=0; i<kol; i++)
            diagramma[i]->setSizePoint(size);
            
    };
    int getSizePoint(){return keyPoint;};
    void clearData(){kolDataX=kolDataY=0; flagRangeX=flagRangeY=false;};
    int getPenWidth(long n){return penWidth[n];};
    void setPenWidth(long width, long n){penWidth[n]=width;};
    bool resetData(); // сброс установленных данных для графиков

public:
    void draw();
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
    bool keyClear;
    int keyPoint;
    long kolDataX,kolDataY; // kolData=kol,  если все данные заполнены и можно рисовать
    QColor *colorLine, *colorPoint;
    QColor colorLineMetka[KolMetka]; // цвет линейной метки под графиком
    long *penWidth;
    void initData(long k);
    double x1Metka[KolMetka], x2Metka[KolMetka];
    long *xBegin, *yBegin, *xEnd, *yEnd;

    void contentsMousePressEvent ( QMouseEvent * e );
    void contentsMouseReleaseEvent ( QMouseEvent * e );
    void contentsMouseMoveEvent ( QMouseEvent * e );

protected:

    MyCanvasPolyline **diagramma;
    
    Q3CanvasLine      *lineMetka[KolMetka];   // метки под графиком

    void resizeEvent(QResizeEvent *event);
};

#endif
