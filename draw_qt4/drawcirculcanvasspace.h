#ifndef DRAWCIRCUL_CANVAS_SPACE_H

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

class DrawCirculCanvasSpace : public DrawCirculBaseCanvas
{
public:
    
    DrawCirculCanvasSpace( QCanvas *canvas, QWidget *parent,
                      long l, long m,
                      FlagCirculBase Flag,
                      long irx=1, long iry=0, long krx=8, long kry=8);
    ~DrawCirculCanvasSpace();
    void setY(double *y){Y=y;};
    void setZ(double **z){Z=z;};
    void setTextInfo(const QString &s);
    void setTextInfA(const QString &s);
    void setTextInfB(const QString &s);
    void setTextInfSig(const QString &s);
    void setXBegDx(double x_beg, double dx){xBeg=x_beg; Dx=dx;};
    bool resetData();
    long draw();

private:
    
    long   M, L, kol;
    double *Y, **Z;
    double xBeg, Dx;
    QCanvasText *infA, *infB, *infSig;
    QCanvasText *info;
    QFontMetrics *fm;
    QFont *font;
    int isw, ish, maxSizeChar;

    void initData();

protected:

    MyCanvasPolygon **diagramma;

    void resizeEvent(QResizeEvent *event);
};

#endif
