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
//#include <iostream>
//#include <iomanip>
#include <stdio.h>
#include <qcursor.h>

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
  setBackgroundColor(colorFon);

  flagMouseDesable=true; // запретить выделение областей мышью
  flagMouseLeftPress=false;
  flagMouseRihtPress=false;
  flagMouseMidPress =false;
  flagMouseRelease  =false;
  flagMouseMove     =false;
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
}

DrawBase::~DrawBase()
{
  //dc.setViewport(fildView);
  //dc.setBackColor(dc.realColor(MGL_LIGHTGRAY));
  //dc.clearViewport();
  if (divot)
    delete[] divot;
}/* */
void DrawBase::paintEvent(QPaintEvent *e)
{
    QPainter p;

    p.begin(this);
    p.setClipRect(e->rect());

    fildView=geometry ();

    QBrush brush( colorFon, SolidPattern );
    p.fillRect(fildView,brush);
    ix=0;
    iy= fildView.bottom()-fildView.top();
    nx=fildView.right()-fildView.left();
    ny=iy;

    left=0;
    right=nx;
    top=0;
    bottom=ny;
    krx=krx0;
    kry=kry0;
    if (grraz(p))
      error=false;   // ошибка
    else
      error=true;
    rClear.setLeft(left+ix+1);
    rClear.setRight(left+ix+nx);
    rClear.setTop(top+1);
    rClear.setBottom(top+iy-1);
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

void DrawBase::mouseDoubleClickEvent ( QMouseEvent * e )
{
}

void DrawBase::mousePressEvent ( QMouseEvent * e )
{
    if (e->button()==MidButton)
    {
        flagMouseMidPress=true;
        flagMouseLeftPress=false;
        flagMouseRihtPress=false;
        flagMouseMove     =false;
        setCursor(QCursor(CrossCursor));
        pointMetka=e->pos();
        posX=xmin+(double)(pointMetka.x()-ix)*(xmax-xmin)/(double)nx;
        posY=ymin-(double)(pointMetka.y()-iy)*(ymax-ymin)/(double)ny;
        //std::cout<<std::endl<<"pointX="<<pointMetka.x()<<"  pointY="<<pointMetka.y()<<std::flush;
        //std::cout<<std::endl<<"posX="<<posX<<"  posY="<<posY<<std::flush;
        emit signalRealValue(posX, posY);
    }

    if (flagMouseDesable)
        return;

    //cout<<endl<<"mousePressEvent"<<flush;
        
    if (e->button()==LeftButton)
    {
        flagMouseLeftPress=true;
        flagMouseMidPress =false;
        flagMouseRihtPress=false;
        flagMouseMove     =false;
        pointBegin=e->pos();
        setCursor(QCursor(ArrowCursor));
    }

    if (e->button()==RightButton)
    {
        flagMouseLeftPress=false;
        flagMouseMidPress =false;
        flagMouseMove     =false;
        flagMouseRihtPress=true;
        pointBegin=e->pos();
        setCursor(QCursor(ArrowCursor));
    }
}

void DrawBase::mouseReleaseEvent ( QMouseEvent * e )
{
    setCursor(QCursor(ArrowCursor));

    if (flagMouseMidPress)
    {
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
        posX=xmin+(double)(pointMetka.x()-ix)*(xmax-xmin)/(double)nx;
        posY=ymin-(double)(pointMetka.y()-iy)*(ymax-ymin)/(double)ny;
        //std::cout<<std::endl<<"pointX="<<pointMetka.x()<<"  pointY="<<pointMetka.y()<<std::flush;
        //std::cout<<std::endl<<"posX="<<posX<<"  posY="<<posY<<std::flush;
        emit signalRealValue(posX, posY);
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
