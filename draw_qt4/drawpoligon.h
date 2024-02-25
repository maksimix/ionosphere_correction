#ifndef DRAWPOLIGON_H

#define DRAWPOLIGON_H

#ifndef DRAWBASE_H
#include "drawbase.h"
#endif
#ifndef QCOLOR_H
#include <qcolor.h>
#endif
#ifndef QWMATRIX_H
#include <qwmatrix.h>
#endif

class DrawPoligon : public DrawBase
{
public:
    DrawPoligon( QWidget *parent,
                 //char *infX, char *infY,
                 const QString &infX, const QString &infY,
                 double xmin, double xmax, double ymin, double ymax,
                 long ir=1, long ipgr=1, long krx=8, long kry=8);
    ~DrawPoligon();
    void setY(double *Y);
    void reset();
    void setN(long N){n=N;};
    void upDate();
    void setXBegDx(double x_beg, double dx){xBeg=x_beg; Dx=dx;};
    void setYBegDy(double y_beg, double dy){yBeg=y_beg; Dy=dy;};
    void setClear(bool clear){keyClear=clear;};
    void setColor(bool c){keyColor=c;};
    bool getClear(){return keyClear;};
    void   setMinAmp(double a){minAmp=a;};
    double getMinAmp(){return minAmp;};
    double getNormAmp(){return normAmp;};
    void   setNormAmp(double a){normAmp=a;};
private:
    long   n;
    long   nX; // текущее дискретное значение x
    long    x0,y0,x1,y1;
    long    color;
    double *y;
    double xBeg,Dx,yBeg,Dy;
    double minAmp, normAmp;
    bool keyClear;
    bool keyColor; // true - цветное изображение
    bool keyPainter;
    long draw(QPainter &p, bool keyClear);
protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif
