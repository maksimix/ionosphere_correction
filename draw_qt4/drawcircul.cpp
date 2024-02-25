#include "drawcircul.h"
#include <stdlib.h>
#ifndef QPOINTARRAY_H
#include <qpointarray.h>
#endif
#ifndef _MATH_H
#include <math.h>
#endif

DrawCircul::DrawCircul(QWidget *parent,
                       long k,
                       FlagCirculBase Flag,
                       long iRx, long iRy, long kRx, long kRy) :

            DrawCirculBase(parent, Flag, iRx, iRy, kRx, kRy)
    
{
  initData(k);
}

void DrawCircul::initData(long k)
{
  keyClear=false;
  keyPoint=0;
  kol=k;
  kolDataX=kolDataY=0;
  x=new double* [kol];
  y=new double* [kol];
  n=new long[kol];
  colorLine =new QColor[kol];
  colorPoint=new QColor[kol];
  penWidth=new long[kol];
  for(long i=0; i<kol; i++)
    {
      colorLine[i].setRgb(255,0,0);
      colorPoint[i].setRgb(255,0,0);
      penWidth[i]=1;
    }
  Dx=Dy=.0;
  xBeg=yBeg=.0;
}

DrawCircul::~DrawCircul()
{
  delete[] x;
  delete[] y;
  delete[] n;
  delete[] colorLine;
  delete[] colorPoint;
  delete[] penWidth;
}

void DrawCircul::setXY(double *X, double *Y, long *N, long Size)
{
  for(long i=0; i<kol; i++)
    {
      x[i]=X+Size*i;
      y[i]=Y+Size*i;
      n[i]=N[i];
      if (!flagRangeX || !flagRangeY)
        {
          flagRangeX=flagRangeY=true; // диапазон изменений аргумента и функции определен
        }
    }
  kolDataX=kolDataY=kol;
}

void DrawCircul::setY(double *Y, long N, long i)
{
  if (i<kol)
    {
      y[i]=Y;
      n[i]=N;
      kolDataY++;
      if (kolDataY==kol)
        for(i=0; i<kol; i++)
          if (n[i]==0 && kolDataY>0)
            kolDataY--;
      if (!flagRangeY)
        {
          if (kolDataY==kol)
            flagRangeY=true;
        }
    }
}

void DrawCircul::setX(double *X, long N, long i)
{
  if (i<kol)
    {
      x[i]=X;
      n[i]=N;
      kolDataX++;
      if (kolDataX==kol)
        for(i=0; i<kol; i++)
          if (n[i]==0 && kolDataX>0)
            kolDataX--;
      if (!flagRangeX)
        {
          if (kolDataX==kol)
            flagRangeX=true;
        }
    }
}

void DrawCircul::paintEvent(QPaintEvent *e)
{
   DrawCirculBase::paintEvent(e);
   QPainter p;
   p.begin(this);
   p.setClipRect(e->rect());
   draw(p,keyClear,keyPoint);
   p.end();
}

long DrawCircul::draw(QPainter &p,
                      bool keyClear,
                      int keyPoint)
//
// Функция предназначена для отображения
// keyPoint - 1 - рисовать кружки, 0 -не рисовать
//
{
  double  r, sa, ca;
  const double DegToRad=acos(-1.)/180.;
  QRect   rFill;
  QPen    pen=p.pen();
  long    i, j, k;
  int     X, Y;
  QPointArray array;

  if (!error || kolDataY<kol || kolDataX<kol)
    return 1;

  if (keyClear) // пока не понятно, что с этим делать
    {
      QBrush brush( colorFon, SolidPattern );
      p.fillRect(rClear,brush);
    }

  for(i=0; i<kol; i++)
  {
     pen.setWidth(penWidth[i]);
     pen.setColor(colorLine[i]);
     p.setPen(pen);
     p.setBrush(colorLine[i]);

     array.resize(n[i]+1);

     for(j=0; j<n[i]+1; j++)
       {
         k=(j==n[i])? 0 : j;
         r=*(y[i]+k) * (double)R;
         sa=sin(*(x[i]+k)*DegToRad);
         ca=cos(*(x[i]+k)*DegToRad);
         X=(long)((double)xCentr+r*sa);
         Y=(long)((double)yCentr-r*ca);
         array.setPoint(j,X,Y);
       }
      if (i)
          p.drawPolyline(array);
      else
          p.drawPolygon(array);

      if (keyPoint>0)
          for(j=0; j<n[i]; j++)
          {
               array.point((uint)j,&X,&Y);
               rFill.setCoords(X-keyPoint,Y-keyPoint,X+keyPoint,Y+keyPoint);
               p.setPen(colorPoint[i]);
               p.setBrush(colorPoint[i]);
               p.drawEllipse(rFill);
          }
  }
  return 0;
}

void DrawCircul::upDate()
{
  //update(rClear);
  update();
}