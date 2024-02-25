#include "drawpoligon.h"
#include <stdlib.h>

DrawPoligon::DrawPoligon(QWidget *parent,
                         //char *infX, char *infY,
                         const QString &infX, const QString &infY,
                         double xMin, double xMax, double yMin, double yMax,
                         long iR,long iPgr, long kRx, long kRy) :

    DrawBase(parent, infX, infY, xMin, xMax, yMin, yMax,
             iR,iPgr, kRx, kRy)
{
    keyClear=false;
    keyColor=true;
    Dx=Dy=.0;
    xBeg=yBeg=.0;
    keyPainter=true;
    n=0;
    minAmp=.0;
    normAmp=1.;
    setColorFon(QColor(255,255,255));
    setColorAxe(QColor(0,0,0));
    setColorSetka(QColor(150,150,150));
    setColorText(QColor(0,0,0));
}

DrawPoligon::~DrawPoligon()
{
}

void DrawPoligon::reset()
{
    nX=-1;
    keyPainter=true;
    //repaint(false);
    update();
}

void DrawPoligon::setY(double *Y)
{
    y=Y;
    nX++;
    keyPainter=false;
    //repaint(false);
    update();
}

void DrawPoligon::paintEvent(QPaintEvent *e)
{
    if (keyPainter)
        DrawBase::paintEvent(e);
    QPainter p;
    p.begin(this);
    //p.setClipRect(e->rect());
    draw(p,keyClear);
    p.end();
}


long DrawPoligon::draw(QPainter &p,
                       bool keyClear)
//
// Функция предназначена для отображения
//
{
  double  sizex,sizey;
  QPoint  point;
  QRect   rFill;
  QPen    pen=p.pen();
  long    i,j;
  QColor  colorPoint;

  if (!error || !n)
    return 1;

  
  if (keyClear)
  {
      QBrush brush( colorFon, Qt::SolidPattern );
      p.fillRect(rClear,brush);
  }

  sizex=xmax-xmin;
  sizey=ymax-ymin;

  if (!nX)
      x0=(xBeg+Dx*nX-xmin)*nx/sizex+ix;
  x1=(xBeg+Dx*(nX+1)-xmin)*nx/sizex+ix;
  if (x0==x1)
  {
      keyPainter=true;
      return 0;
  }
  y0=-(yBeg-ymin)*ny/sizey+iy;
  //p.setRasterOp(Qt::OrNotROP);
  ////p.setRasterOp(Qt::NotXorROP);
  for(j=1; j<n; j++)
  {
      y1=-(yBeg+Dy*j-ymin)*ny/sizey+iy;
      if (x1<ix && x0<ix || x1>ix+nx && x0>ix+nx ||
          y1>iy && y0>iy || y1<iy-ny && y0<iy-ny)
        {
          y0=y1;
        }
      else
      {
          if (x1<ix) x1=ix;
          if (x0<ix) x0=ix;
          if (y1>=iy) y1=iy;
          if (y0>=iy) y0=iy;
          if (x1>=ix+nx) x1=ix+nx-1;
          if (x0>=ix+nx) x0=ix+nx-1;
          if (y1<=iy-ny) y1=iy-ny+1;
          if (y0<=iy-ny) y0=iy-ny+1;

          if (y0!=y1)
          {
              double amp=(y[j]-minAmp)/normAmp;
              if (amp<.0)
                  amp=.0;
              else
                  if (amp>1.)
                      amp=1.;
              if (keyColor)
              {
                color=510*amp;
                if (color<0)
                  color=0;
                if (color>510)
                  color=510;
                color&=0x1ff;
                if (color>255)
                {
                    colorPoint=QColor(color-255,510-color,0);
                }
                else
                {
                    colorPoint=QColor(0,color,255-color);
                }
              }
              else
              {
                color=255*amp;
                if (color<0)
                  color=0;
                if (color>255)
                  color=255;
                color&=0x1ff;
                colorPoint=QColor(255-color,255-color,255-color);
              }
  
              rFill.setCoords(x0,y1,x1,y0);
              p.setBrush(colorPoint);
              //pen.setCapStyle(Qt::SquareCap);
              //p.setPen(pen);
              p.setPen(colorPoint);
              if (rFill.left()>=ix && rFill.right()<ix+nx && rFill.bottom()<=iy && rFill.top()>iy-ny)
                  p.drawRect(rFill);
              y0=y1;
          }
          else
              y0=y1;
      }
  }
  x0=x1;
  //p.setRasterOp(Qt::CopyROP);
  keyPainter=true;
  return 0;
}

void DrawPoligon::upDate()
{
  //update(rClear);
  update();
}
