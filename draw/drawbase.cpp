/***************************************************************************
                          drawbase.cpp  -  description
                             -------------------
    begin                : Tue Aug 22 2000
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
#include "drawbase.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <QCursor>
#include <QPoint>
#include <QMouseEvent>

DrawBase::DrawBase(QWidget *parent,
                   //char *infX, char *infY,
                   const QString &infX, const QString &infY,
                   double xMin, double xMax, double yMin, double yMax,
                   long iR,long iPgr, long kRx, long kRy) :
                   QWidget(parent),
                   fildView(QRect(0,0,1,1)), infx(infX), infy(infY),
                   ir(iR), ipgr(iPgr)
{
  error=true;
  latch=false;
  krx0=kRx;
  kry0=kRy;
  divot=NULL;
  xmin=xMin;
  xmax=xMax;
  ymin=yMin;
  ymax=yMax;
  flagRangeX=flagRangeY=true; // диапазон изменений аргумента и функции определен
  flagMinMax=true;
  otst=0;
  otstBegX=otstBegY=0;
  colorFon  =QColor(255,255,255);
  colorText =QColor(0,0,0);
  colorSetka=QColor(200,200,200);
  colorAxe  =QColor(0,0,0);
  //setBackgroundColor(colorFon);

  flagMouseDesable=true; // запретить выделение областей мышью
  flagMouseLeftPress=false;
  flagMouseRihtPress=false;
  flagMouseMidPress =false;
  flagMouseRelease  =false;
  flagMouseMove     =false;
  flagDraw          =true;

  pointBegMetka=pointEndMetka=QPoint(0,0);

  pix=0;
  //std::cout<<std::endl<<"1 DrawBase  pix="<<pix<<std::flush;
}

DrawBase::DrawBase(QWidget *parent,
                   //char *infX, char *infY,
                   const QString &infX, const QString &infY,
                   long iR,long iPgr, long kRx, long kRy) :
                   QWidget(parent),
                   fildView(QRect(0,0,1,1)), infx(infX), infy(infY),
                   ir(iR), ipgr(iPgr)
{
  error=true;
  latch=false;
  krx0=kRx;
  kry0=kRy;
  flagRangeX=flagRangeY=false; // диапазон изменений аргумента и функции не определен
  flagMinMax=false;
  divot=NULL;
  otst=0;
  otstBegX=otstBegY=0;
  xmin=xmax=ymin=ymax=.0;
  colorFon=QColor(0,0,0);

  flagMouseDesable=true; // запретить выделение областей мышью
  flagMouseLeftPress=false;
  flagMouseRihtPress=false;
  flagMouseMidPress =false;
  flagMouseRelease  =false;
  flagMouseMove     =false;
  flagDraw          =true;

  pointBegMetka=pointEndMetka=QPoint(0,0);

  pix=0;
  //std::cout<<std::endl<<"2 DrawBase  pix="<<pix<<std::flush;
}

DrawBase::~DrawBase()
{
  //dc.setViewport(fildView);
  //dc.setBackColor(dc.realColor(MGL_LIGHTGRAY));
  //dc.clearViewport();
  if (divot)
    delete[] divot;
  if (pix)
    delete pix;
}/* */
void DrawBase::paintEvent(QPaintEvent *e)
{
    //std::cout<<std::endl<<"DrawMemBase::paintEvent  flagDraw="<<flagDraw<<std::flush;
    if (!flagDraw)
        return;

    QRect r=contentsRect();
    if ( r!=fildView )
    {
        fildView=r;
        ix=0;
        iy=fildView.bottom()-fildView.top();
        nx=fildView.right()-fildView.left();
        ny=iy;

        std::cout<<std::endl<<"DrawMemBase::paintEvent"<<std::flush;
        std::cout<<std::endl<<"nx="<<nx<<"  ny="<<ny<<" fildView.top()="<<fildView.top()<<" fildView.left()="<<fildView.left()<<std::flush;
        if (pix)
            delete pix;
        pix=new QImage(nx, ny, QImage::Format_ARGB32_Premultiplied);
    }

    QPainter p;

    p.begin(pix);

    left=0;
    right=nx;
    top=0;
    bottom=ny;
    krx=krx0;
    kry=kry0;

    QBrush brush( colorFon, Qt::SolidPattern );
    p.fillRect(fildView,brush);

    if (grraz(p))
      error=false;   // ошибка
    else
      error=true;
    rClear.setLeft(left+ix+1);
    rClear.setRight(left+ix+nx);
    rClear.setTop(top+1);
    rClear.setBottom(top+iy-1);

    if (oblastDbl.size()>0)
    {
        oblast.clear();
        for(QVector<RectDbl>::iterator i=oblastDbl.begin(); i<oblastDbl.end(); i++)
        {
            pointBegMetka.rx()=ix+(int)(nx*(i->x0-xmin)/(xmax-xmin));
            pointBegMetka.ry()=iy-(int)(ny*(i->y0-ymin)/(ymax-ymin));
            pointEndMetka.rx()=ix+(int)(nx*(i->x1-xmin)/(xmax-xmin));
            pointEndMetka.ry()=iy-(int)(ny*(i->y1-ymin)/(ymax-ymin));
            oblast.push_back(QRect(pointBegMetka,pointEndMetka));
        }
        pointBegMetka=QPoint(0,0);
        pointEndMetka=QPoint(0,0);
    }

    p.end();
}

void DrawBase::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    //resizeMyCanvas();
    //std::cout<<std::endl<<"+++++++++++++++++++++++++++++++++++++++++++++++ resizeEvent";
}

void DrawBase::setInfXY( const QString &infX, const QString &infY )//char* infX, char* infY)
{
    bool flagX=false, flagY=false;
    //if (infX && strlen(infX)>0)
    if( !infX.isNull() && !infX.isEmpty() )
    {
        flagX=true;
        infx=infX;
    }
    //if (infY && strlen(infY)>0)
    if( !infY.isNull() && !infY.isEmpty() )
    {
        flagY=true;
        infy=infY;
    }
}

void DrawBase::oblastClear()
{
     oblast.clear();
     oblastDbl.clear();
     emit signalClear(-1);
}

void DrawBase::mouseDoubleClickEvent ( QMouseEvent * e )
{
    flagDraw=false;
    if (oblast.size()>0)
    {
        bool key=true;
        QPoint point=e->pos();
        for(int i=0; i<oblast.size(); i++)
        {
            if (oblast[i].contains(point))
            {
                pointBegMetka=oblast[i].topLeft();
                pointEndMetka=oblast[i].bottomRight();
                repaint();
                //update();
                oblast.erase(&oblast[i]);
                oblastDbl.erase(&oblastDbl[i]);
                key=false;
                emit signalClear(i);
                break;
            }
        }
        if (key)
        {
            for(QVector<QRect>::iterator i=oblast.end()-1; i>=oblast.begin(); i--)
            {
                pointBegMetka=i->topLeft();
                pointEndMetka=i->bottomRight();
                repaint();
                //update();
            }
            oblast.clear();
            oblastDbl.clear();
            emit signalClear(-1);
        }
    }
    flagDraw=true;
    pointBegMetka=QPoint(0,0);
    pointEndMetka=QPoint(0,0);
}

void DrawBase::mousePressEvent ( QMouseEvent * e )
{
    if (e->button()==Qt::MidButton)
    {
        flagMouseMidPress=true;
        flagMouseLeftPress=false;
        flagMouseRihtPress=false;
        flagMouseMove     =false;
        setCursor(QCursor(Qt::CrossCursor));
        pointMetka=e->pos();
        pointBegMetka=pointMetka;
        pointEndMetka=pointMetka;
        posX=xmin+(double)(pointMetka.x()-ix)*(xmax-xmin)/(double)nx;
        posY=ymin-(double)(pointMetka.y()-iy)*(ymax-ymin)/(double)ny;
        //std::cout<<std::endl<<"pointX="<<pointMetka.x()<<"  pointY="<<pointMetka.y()<<std::flush;
        //std::cout<<std::endl<<"posX="<<posX<<"  posY="<<posY<<std::flush;
        emit signalRealValue(posX, posY);
    }

    if (flagMouseDesable)
        return;

    //cout<<endl<<"mousePressEvent"<<flush;
        
    if (e->button()==Qt::LeftButton)
    {
        flagMouseLeftPress=true;
        flagMouseMidPress =false;
        flagMouseRihtPress=false;
        flagMouseMove     =false;
        pointBegin=e->pos();
        setCursor(QCursor(Qt::ArrowCursor));
    }

    if (e->button()==Qt::RightButton)
    {
        flagMouseLeftPress=false;
        flagMouseMidPress =false;
        flagMouseMove     =false;
        flagMouseRihtPress=true;
        pointBegin=e->pos();
        setCursor(QCursor(Qt::ArrowCursor));
    }
}

void DrawBase::mouseReleaseEvent ( QMouseEvent * e )
{
    setCursor(QCursor(Qt::ArrowCursor));

    if (flagMouseMidPress)
    {
        oblast.push_back(QRect(pointBegMetka,pointEndMetka));
        posX0=xmin+(double)(pointBegMetka.x()-ix)*(xmax-xmin)/(double)nx;
        posY0=ymin-(double)(pointBegMetka.y()-iy)*(ymax-ymin)/(double)ny;
        posX1=xmin+(double)(pointEndMetka.x()-ix)*(xmax-xmin)/(double)nx;
        posY1=ymin-(double)(pointEndMetka.y()-iy)*(ymax-ymin)/(double)ny;
        oblastDbl.push_back(RectDbl(posX0,posY0,posX1,posY1));
        emit signalRealValue(posX0, posY0,posX1,posY1);
        repaint();
        pointBegMetka=QPoint(0,0);
        pointEndMetka=QPoint(0,0);
        flagDraw=true;
    }

    if (flagMouseDesable)
    {
        flagMouseMidPress =false;
        flagMouseLeftPress=false;
        flagMouseMove     =false;
        flagMouseRihtPress=false;
        return;
    }

    //cout<<endl<<"contentsMouseReleaseEvent"<<flush;

    if (flagMouseLeftPress)
    {
    }
    if (flagMouseRihtPress)
    {
    }

    flagMouseMidPress =false;
    flagMouseLeftPress=false;
    flagMouseRihtPress=false;
    flagMouseMove     =false;
}

void DrawBase::mouseMoveEvent ( QMouseEvent * e )
{
    if (flagMouseMidPress) // движется мышка и нажата клавиша Ctrl
    {
        pointMetka=e->pos();
        flagDraw=false;
        repaint();
        //update();
        pointEndMetka=pointMetka;
        posX=xmin+(double)(pointMetka.x()-ix)*(xmax-xmin)/(double)nx;
        posY=ymin-(double)(pointMetka.y()-iy)*(ymax-ymin)/(double)ny;
        //std::cout<<std::endl<<"pointX="<<pointMetka.x()<<"  pointY="<<pointMetka.y()<<std::flush;
        //std::cout<<std::endl<<"posX="<<posX<<"  posY="<<posY<<std::flush;
        emit signalRealValue(posX, posY);
        repaint();
        //update();
    }

    if (flagMouseDesable)
        return;
    
    if (flagMouseLeftPress)
    {
        flagMouseMove=true;
        pointEnd=e->pos();
    }
    if (flagMouseRihtPress)
    {
        flagMouseMove=true;
        pointEnd=e->pos();
    }
}
