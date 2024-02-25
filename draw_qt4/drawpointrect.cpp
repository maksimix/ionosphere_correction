/***************************************************************************
                          drawpoint.cpp  -  description
                             -------------------
    begin                : Thu Aug 07 2003
    copyright            : (C) 2003 by Verotgradov G.G.
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

#include "drawpointrect.h"

#include <stdlib.h>
#include <stdio.h>
//#include <iostream>
//#include <iomanip>

DrawPointRect::DrawPointRect(QWidget *parent,
           long k,
           const QString &infX, const QString &infY,
           double xMin, double xMax, double yMin, double yMax,
           long iR,long iPgr, long kRx, long kRy) :

           DrawBase(parent, infX, infY, xMin, xMax, yMin, yMax,
                   iR,iPgr, kRx, kRy)
{
  initData(k);
}

void DrawPointRect::initData(long k)
{
  keyClear=false;
  kol=k;
  keyPainter=-1;
  formMetka=NoForm;
  pointDouble=new QPtrList<PointDouble> [kol];

  colorPoint=new QColor[kol];
  width     =new double[kol];
  hight     =new double[kol];
  for(long i=0; i<kol; i++)
  {
        colorPoint[i].setRgb(0,0,0);
        width[i]=.0;
        hight[i]=.0;
        (pointDouble+i)->setAutoDelete(TRUE);
  }
}

DrawPointRect::~DrawPointRect()
{
  delete[] pointDouble;
  delete[] colorPoint;
  delete[] hight;
  delete[] width;
}

void DrawPointRect::setXY(double X, double Y, QColor c, long N)
{
      if (latch || N>=kol)
          return;
      pointDouble[N].append(new PointDouble(X,Y,c,hight[N],width[N]));
      keyPainter=N;  // только одну точку перерисовывать
      repaint(false);
      //upDate();
      //keyPainter=-1;  // все точки перерисовать
}

void DrawPointRect::setXY(double X, double Y, long N)
{
      if (latch || N>=kol)
          return;
      pointDouble[N].append(new PointDouble(X,Y,colorPoint[N],hight[N],width[N]));
      keyPainter=N;  // только одну точку перерисовывать
      repaint(false);
      //upDate();
      //keyPainter=-1;  // все точки перерисовать
}

void DrawPointRect::setXY(PointDouble point, long N)
{
     if (latch || N>=kol)
       return;
     pointDouble[N].append(new PointDouble(point));
     keyPainter=N; // только одну точку перерисовывать
     repaint(false);
     //keyPainter=-1; // все точки перерисовать
}

void DrawPointRect::setXY(double X, double Y, QColor c, double h, double w, long N)
{
      if (latch || N>=kol)
          return;
      //std::cout<<std::endl<<"X="<<X<<" Y="<<Y<<" xmin="<<xmin<<" ymin="<<ymin<<" xmax="<<xmax<<" ymax="<<ymax<<std::flush;
      pointDouble[N].append(new PointDouble(X,Y,c,h,w));
      keyPainter=N;  // только одну точку перерисовывать
      repaint(false);
      //upDate();
      //keyPainter=-1;  // все точки перерисовать
}

void DrawPointRect::paintEvent(QPaintEvent *e)
{
   if (keyPainter<0) // если изменилась только одна точка, перерисовывать все поле нет необходимости
       DrawBase::paintEvent(e);
   QPainter p;
   p.begin(this);
   //p.setClipRect(e->rect());
   draw(p);
   p.end();
}

long DrawPointRect::draw(QPainter &p)
//
// Функция предназначена для отображения
//
{
  short    x0,y0,x1,y1;
  double   sizex,sizey;
  int      sizeW, sizeH;
  QPoint   point;
  QRect    rFill;
  long     i, iBeg, iEnd;
  PointDouble *iPoint;

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
       x0=-1;
       y0=-1;

       if (keyPainter>=0)
       {
           iPoint=pointDouble[keyPainter].last();
       }
       else
           iPoint=pointDouble[i].first();

       for(; iPoint; iPoint=pointDouble[i].next())
       {
            iPoint->setFlag(true);
            x1=(iPoint->getX()-xmin)*nx/sizex+ix;
            y1=-(iPoint->getY()-ymin)*ny/sizey+iy;
            //std::cout<<std::endl<<"X="<<iPoint->getX()<<" Y="<<iPoint->getY()<<" xmin="<<xmin<<" ymin="<<ymin<<" xmax="<<xmax<<" ymax="<<ymax<<std::flush;
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

                 if (iPoint->getWidth()>.0 && iPoint->getHight()>.0)
                 {
                     sizeW=(int)(.5*iPoint->getWidth()*nx/sizex);
                     sizeH=(int)(.5*iPoint->getHight()*ny/sizey);

                     int xleft,xright,ytop,ybottom;
                     xleft=x1-sizeW;
                     xright=x1+sizeW;
                     if (xleft==xright)
                         xright=xleft+1;
                     ytop=y1-sizeH;
                     ybottom=y1+sizeH;
                     if (ytop==ybottom)
                         ybottom=ytop+1;
                     rFill.setCoords(xleft,ytop,xright,ybottom);
                     p.setPen(iPoint->getColor());
                     p.setBrush(iPoint->getColor());
                     if (rFill.left()>ix && rFill.right()<ix+nx && rFill.bottom()<iy-1 && rFill.top()>iy-ny)
                         switch(formMetka)
                         {
                         case NoForm:
                         case Ellipse:
                             p.drawEllipse(rFill);
                             break;
                         case Rectangle:
                             p.drawRect(rFill);
                             break;
                         }
                 }
                 //else
                 //    std::cout<<std::endl<<"iPoint->getHight()="<<iPoint->getHight();
                 x0=x1;
                 y0=y1;
               }
       }
  }
  keyPainter=-1;
  return 0;
}

void DrawPointRect::upDate()
{
  //update(rClear);
  update();
}

void DrawPointRect::Clear()
{
    for(long i=0; i<kol; i++)
        pointDouble[i].clear();
}

void DrawPointRect::reset()
{
    Clear();
    keyPainter=-1;
    repaint(true);
    //printf("DrawPointRect::reset()\n");
}
