/***************************************************************************
                          drawpoint.cpp  -  description
                             -------------------
    begin                : Thu Aug 31 2000
    copyright            : (C) 2000 by Verotgradov G.G.
    email                : vgg@phys.rsu.ru
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "drawpoint.h"

#include <stdlib.h>

DrawPoint::DrawPoint(QWidget *parent,
                     long k,
                     //char *infX, char *infY,
                     const QString &infX, const QString &infY,
                     double xMin, double xMax, double yMin, double yMax,
                     long iR,long iPgr, long kRx, long kRy) :

    DrawBase(parent, infX, infY, xMin, xMax, yMin, yMax,
             iR,iPgr, kRx, kRy)
{
  initData(k);
}

void DrawPoint::initData(long k)
{
  keyClear=false;
  kol=k;
  keyPainter=-1;
  pointDouble=new std::list <PointDouble> [kol];
  keyPoint=new int[kol];

  colorPoint=new QColor[kol];
  for(long i=0; i<kol; i++)
  {
        colorPoint[i].setRgb(0,0,0);
        keyPoint[i]=0;
  }
}

DrawPoint::~DrawPoint()
{
  delete[] pointDouble;
  delete[] colorPoint;
  delete[] keyPoint;
}

void DrawPoint::setXY(double X, double Y, QColor c, long N)
{
      if (latch || N>=kol)
          return;
      PointDouble point(X,Y, c);
      pointDouble[N].push_back(point);
      keyPainter=N;  // только одну точку перерисовывать
      repaint(false);
      //upDate();
      //keyPainter=-1;  // все точки перерисовать
}

void DrawPoint::setXY(double X, double Y, long N)
{
      if (latch || N>=kol)
          return;
      PointDouble point(X,Y, colorPoint[N]);
      pointDouble[N].push_back(point);
      keyPainter=N;  // только одну точку перерисовывать
      repaint(false);
      //upDate();
      //keyPainter=-1;  // все точки перерисовать
}

void DrawPoint::setXY(PointDouble point, long N)
  {
     if (latch || N>=kol)
       return;
     pointDouble[N].push_back(point);
     keyPainter=N; // только одну точку перерисовывать
     repaint(false);
     //keyPainter=-1; // все точки перерисовать
  }

void DrawPoint::paintEvent(QPaintEvent *e)
{
   if (keyPainter<0) // если изменилась только одна точка, перерисовывать все поле нет необходимости
       DrawBase::paintEvent(e);
   QPainter p;
   p.begin(this);
   //p.setClipRect(e->rect());
   draw(p);
   p.end();
}

long DrawPoint::draw(QPainter &p)
//
// Функция предназначена для отображения
// keyPoint - 1 - рисовать кружки, 0 -не рисовать
//
{
  short    x0,y0,x1,y1;
  double   sizex,sizey;
  QPoint   point;
  QRect    rFill;
  long     i, iBeg, iEnd;
  std::list <PointDouble>::iterator iPoint;

  if (keyClear)
  {
      //QBrush brush=p.brush();
      //brush.setColor(colorFon);
      QBrush brush( colorFon, SolidPattern );
      p.fillRect(rClear,brush);
  }

  sizex=xmax-xmin;
  sizey=ymax-ymin;

  if (keyPainter>=0)
  {
      iBeg=keyPainter;
      iEnd=keyPainter+1;
  }
  else
  {
      iBeg=0;
      iEnd=kol;
  }


  for(i=iBeg; i< iEnd; i++)
  {
       if (keyPainter>=0)
       {
           iPoint=pointDouble[keyPainter].end();
           iPoint--;
       }
       else
           iPoint=pointDouble[i].begin();
       x0=-1;
       y0=-1;
       for(; iPoint!=pointDouble[i].end(); iPoint++)
       {
            iPoint->setFlag(true);
            x1=(iPoint->getX()-xmin)*nx/sizex+ix;
            y1=-(iPoint->getY()-ymin)*ny/sizey+iy;
            if (x1<=ix   || x1>=ix+nx ||
               y1>=iy-1 || y1<=iy-ny)
              {
                x0=x1;
                y0=y1;
                iPoint->setFlag(false);
              }
           else
             if (x0!=x1 || y0!=y1)
               {
                 point.rx()=x1;
                 point.ry()=y1;
                 p.moveTo(point);
                 if (keyPoint[i]>0)
                     if (keyPoint[i]==1)
                     {
                         if (x1>ix && x1<ix+nx && y1<iy-1 && y1>iy-ny)
                         {
                             p.setPen(iPoint->getColor());
                             p.drawPoint(point);
                         }
                     }
                     else
                     {
                         int keyP=keyPoint[i]/2;
                         rFill.setCoords(x1-keyP,y1-keyP,x1+keyP,y1+keyP);
                         p.setPen(iPoint->getColor());
                         p.setBrush(iPoint->getColor());
                         if (rFill.left()>ix && rFill.right()<ix+nx && rFill.bottom()<iy-1 && rFill.top()>iy-ny)
                           p.drawEllipse(rFill);
                     }
                 x0=x1;
                 y0=y1;
               }
       }
  }
  keyPainter=-1;
  return 0;
}

void DrawPoint::upDate()
{
  //update(rClear);
  update();
}

void DrawPoint::Clear()
{
    for(long i=0; i<kol; i++)
        pointDouble[i].clear();
}
