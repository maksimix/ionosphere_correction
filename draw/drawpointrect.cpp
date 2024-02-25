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

using namespace std;

#include "drawpointrect.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <QPainterPath>
#include <QPaintEvent>

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
  //setUpdatesEnabled(false);
  keyClear=false;
  kol=k;
  keyPainter=-1;
  formMetka=NoForm;
  //cout<<endl<<"initData kol="<<kol<<flush;
  pointDouble=new list<PointDouble*> [kol];

  colorPoint=new QColor[kol];
  width     =new double[kol];
  hight     =new double[kol];
  for(long i=0; i<kol; i++)
  {
        colorPoint[i].setRgb(0,0,0);
        width[i]=.0;
        hight[i]=.0;
  }
}

DrawPointRect::~DrawPointRect()
{
  delete[] pointDouble;
  delete[] colorPoint;
  delete[] hight;
  delete[] width;
}

void DrawPointRect::setXY(double X, double Y, QColor c, long N, bool flag)
{
      if (latch || N>=kol)
          return;
      pointDouble[N].push_back(new PointDouble(X,Y,c,hight[N],width[N]));
      keyPainter=N;  // только одну точку перерисовывать
      //QRect r(0,0,0,0);
      //repaint();
      if (flag)
          upDate();
      keyPainter=-1;  // все точки перерисовать
}

void DrawPointRect::setXY(double X, double Y, long N, bool flag)
{
      if (latch || N>=kol)
          return;
      pointDouble[N].push_back(new PointDouble(X,Y,colorPoint[N],hight[N],width[N]));
      keyPainter=N;  // только одну точку перерисовывать
      if (flag)
          repaint();
      else
          keyPainter=-1;
      //upDate();
      //keyPainter=-1;  // все точки перерисовать
}

void DrawPointRect::setXY(PointDouble point, long N, bool flag)
{
     if (latch || N>=kol)
       return;
     pointDouble[N].push_back(new PointDouble(point));
     keyPainter=N; // только одну точку перерисовывать
     if (flag)
         repaint();
      else
          keyPainter=-1;
     //keyPainter=-1; // все точки перерисовать
}

void DrawPointRect::setXY(double X, double Y, QColor c, double h, double w, long N, bool flag)
{
      if (latch || N>=kol)
          return;
      //std::cout<<std::endl<<"1 X="<<X<<" Y="<<Y<<" xmin="<<xmin<<" ymin="<<ymin<<" xmax="<<xmax<<" ymax="<<ymax<<std::flush;
      pointDouble[N].push_back(new PointDouble(X,Y,c,h,w));
      //std::cout<<std::endl<<"2 X="<<X<<" Y="<<Y<<" xmin="<<xmin<<" ymin="<<ymin<<" xmax="<<xmax<<" ymax="<<ymax<<std::flush;
      keyPainter=N;  // только одну точку перерисовывать
      if (flag)
          repaint();
      else
          keyPainter=-1;
      //std::cout<<std::endl<<"3 X="<<X<<" Y="<<Y<<" xmin="<<xmin<<" ymin="<<ymin<<" xmax="<<xmax<<" ymax="<<ymax<<std::flush;
      //upDate();
      //keyPainter=-1;  // все точки перерисовать
}


void DrawPointRect::paintEvent(QPaintEvent *e)
{
   //cout<<endl<<"1 paintEvent keyPainter="<<keyPainter<<flush;

   if (keyPainter<0) // если изменилась только одна точка, перерисовывать все поле нет необходимости
       DrawBase::paintEvent(e);
   //cout<<endl<<"2 paintEvent"<<flush;
   //return;
   if (pix==0)
       return;
   QPainter p;
   p.begin(pix);
   //cout<<endl<<"21 paintEvent"<<flush;
   //p.setClipRect(e->rect());
   if (flagDraw)
   {
       draw(p);
   }

   p.end();

   //cout<<endl<<"7 paintEvent"<<flush;
   QPainter pp;
   pp.begin(this);
   pp.drawImage(0, 0, *pix);
   if (flagDraw)
   {
       pp.setBrush(Qt::NoBrush);
       pp.setPen(Qt::black);
       if (oblast.size()>0)
       {
           pp.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
           for(QVector<QRect>::iterator i=oblast.end()-1; i>=oblast.begin(); i--)
           {
               pp.drawRect(*i);
           }
           pp.setCompositionMode(QPainter::CompositionMode_SourceOver);
       }
   }
   else
   {
       pp.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
       QRect rect(pointBegMetka,pointEndMetka);
       pp.drawRect(rect);
       pp.setCompositionMode(QPainter::CompositionMode_SourceOver);
   }
   pp.end();
   //cout<<endl<<"8 paintEvent"<<flush;
   keyPainter=-1;
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
  list<PointDouble*>::iterator iPoint;
  //cout<<endl<<"DrawPointRect"<<flush;
  if (!kol)
      return 0;

  if (keyClear)
    {
      //QBrush brush=p.brush();
      //brush.setColor(colorFon);
      ////QBrush brush( colorFon, SolidPattern );
      ////p.fillRect(rClear,brush);
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
           iPoint=pointDouble[keyPainter].end();
           iPoint--;
       }
       else
           iPoint=pointDouble[i].begin();

       for(; iPoint!=pointDouble[i].end(); iPoint++)
       {
            (*iPoint)->setFlag(true);
            x1=((*iPoint)->getX()-xmin)*nx/sizex+ix;
            y1=-((*iPoint)->getY()-ymin)*ny/sizey+iy;
            //std::cout<<std::endl<<"X="<<iPoint->getX()<<" Y="<<iPoint->getY()<<" xmin="<<xmin<<" ymin="<<ymin<<" xmax="<<xmax<<" ymax="<<ymax<<std::flush;
            if (x1<=ix   || x1>=ix+nx ||
               y1>=iy-1 || y1<=iy-ny)
              {
                x0=x1;
                y0=y1;
                (*iPoint)->setFlag(false);
              }
           else
             if (x0!=x1 || y0!=y1)
             {
                 //QPainterPath path;
                 //point.rx()=x1;
                 //point.ry()=y1;
                 //path.moveTo(point);

                 if ((*iPoint)->getWidth()>.0 && (*iPoint)->getHight()>.0)
                 {
                     sizeW=(int)(.5*(*iPoint)->getWidth()*nx/sizex);
                     sizeH=(int)(.5*(*iPoint)->getHight()*ny/sizey);

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
                     p.setPen((*iPoint)->getColor());
                     p.setBrush((*iPoint)->getColor());
                     if (rFill.left()>ix && rFill.right()<ix+nx && rFill.bottom()<iy-1 && rFill.top()>iy-ny)
                         switch(formMetka)
                         {
                         case NoForm:
                         case Ellipse:
                             //path.addEllipse(rFill);
                             p.drawEllipse(rFill);
                             break;
                         case Rectangle:
                             //path.addRect(rFill);
                             p.drawRect(rFill);
                             break;
                         }
                     //p.drawPath(path);
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
    //cout<<endl<<"kol="<<kol<<flush;
    for(long i=0; i<kol; i++)
    {
        //cout<<endl<<"i="<<i<<" pointDouble[i].size()="<<pointDouble[i].size()<<flush;
        if (!pointDouble[i].empty())
        {
            for(list<PointDouble*>::iterator it=pointDouble[i].begin(); it!=pointDouble[i].end(); it++)
                delete *it;
            pointDouble[i].clear();
        }
        //cout<<" 1pointDouble[i].size()="<<pointDouble[i].size()<<flush;
    }
}

void DrawPointRect::reset()
{
    Clear();
    keyPainter=-1;
    repaint();
    //printf("DrawPointRect::reset()\n");
}
