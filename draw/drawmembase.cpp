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
using namespace std;
#include "drawmembase.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <QCursor>
#include <QWidget>
//#include <Qt>
#include <QtGui>

MyMarker::MyMarker(double xMin, double xMax, double yMin, double yMax,
                   long iX, long iY, long nX, long nY)
{
    otst=0;

    setColorMarker(QColor(0,0,0));
    setColorFon(QColor(0,0,0));
    
    setMinMax(xMin,xMax,yMin,yMax);

    setGeometry(iX,iY,nX,nY);

    X=Y=0;
    setCenterMarker(X,Y);
}

void MyMarker::setCenterMarker(double x, double y)
{
    //std::cout<<endl<<"X="<<x<<" Y="<<y<<" xmin="<<xmin<<" xmax="<<xmax<<" ymin="<<ymin<<" ymax="<<ymax<<" otst="<<otst<<" sizex="<<sizex<<"  xmax-xmin="<<xmax-xmin;
    if (x>xmin && x<xmax)
    {
        X=x;
        xV2=xV1=(long)((X-xmin)*(nx-otst)/sizex)+ix;
    }
    else
    {
        xV2=xV1=0;
    }
    if (y>ymin && y<ymax)
    {
        Y=y;
        yH2=yH1=-(long)((Y-ymin)*(ny-otst)/sizey)+iy;
    }
    else
    {
        yH2=yH1=0;
    }
    //std::cout<<endl<<"xV1="<<xV1<<" yH1="<<yH1<<" xV2="<<xV2<<" yH2="<<yH2<<" ix="<<ix;
    if (x>xmin && x<xmax && y>ymin && y<ymax)
        setColorMarker(QColor(0,0,0));
    else
        setColorMarker(QColor(255,0,0));
}

void MyMarker::setMinMax(double xMin, double xMax, double yMin, double yMax)
{
    xmin=xMin;
    xmax=xMax;
    ymin=yMin;
    ymax=yMax;
    sizex=xmax-xmin;
    sizey=ymax-ymin;
}

void MyMarker::setGeometry(long iX, long iY, long nX, long nY)
{
    nx=nX;
    ny=nY;
    ix=iX;
    iy=iY;

    xH1=ix;
    xH2=ix+nx-otst;
    
    yV1=iy;
    yV2=iy-(ny-otst);
}

void MyMarker::setColorMarker(QColor c)
{
    colorMarker=c;
}

void MyMarker::draw( QPainter & painter )
{
    //cout<<endl<<"MyMarker::draw";
    //QColor color(colorMarker.red()^colorFon.red(),colorMarker.green()^colorFon.green(),
    //             colorMarker.blue()^colorFon.blue());
    QPen pen( colorMarker, Qt::DotLine);
    //QPen pen( color, Qt::DotLine);
    pen.setWidth(1);
    painter.setPen(pen);
    
    painter.drawLine(xH1,yH1,xH2,yH2);
    painter.drawLine(xV1,yV1,xV2,yV2);
}

DrawMemBase::DrawMemBase(QWidget *parent,
                         //char *infX, char *infY,
                         const QString &infX, const QString &infY,
                         double xMin, double xMax, double yMin, double yMax,
                         long iR,long iPgr, long kRx, long kRy) :
                         WIDGET(parent),
                         fildView(QRect(0,0,1,1)), infx(infX), infy(infY),
                         ir(iR), ipgr(iPgr)
{
  setFocusPolicy(Qt::StrongFocus);
  //setWindowFlags(Qt::WNoAutoErase);
  error=true;
  latch=false;
  krx0=kRx;
  kry0=kRy;
  xmin=xMin;
  xmax=xMax;
  ymin=yMin;
  ymax=yMax;
  flagRangeX=flagRangeY=true; // диапазон изменений аргумента и функции определен
  flagMinMax=true;
  realBegX=realBegY=.0;
  otst=otstBegX=otstBegY=0;
  otstup=2; // отступ для закрашиваемой области
  colorFon  =QColor(255,255,255);
  colorText =QColor(0,0,0);
  colorTextMetka =QColor(100,100,100);
  colorSetka=QColor(200,200,200);
  colorAxe  =QColor(0,0,0);
  colorSelectFild=QColor(255,255,255);
  colorMarkFild=QColor(0,255,0);
  colorLineFild=colorFon;
  //setBackgroundColor(colorFon);

  font=new QFont();
  fm=new QFontMetrics(*font);
  pointMetka=QPoint(0,0);
  metkaText=QString::null;

  flagMouseDesable=true; // запретить выделение областей мышью
  flagMouseLeftPress=false;
  flagMouseRihtPress=false;
  flagMouseMidPress =false;
  flagMouseRelease  =false;
  flagMouseMove     =false;
  //flagResize        =false;
  flagResize        =true;
  flagKeyCtrl       =false;
  flagIn            =false;
  flagMarker        =false;
  lineSelectFild=QRect(0,0,0,0); // выделяемая область
  lineCtrl=QRect(0,0,0,0);
  kolMarkFild=0;
  for(int i=0; i<MaxKolMarkFild; i++)
  {
      xMarkBegin[i]=.0;
      xMarkEnd[i]=.0;
      lineMarkFild[i]=QRect(0,0,0,0);
  }
  pix=0;
  pixSetka=0;
  marker=new MyMarker(xmin, xmax, ymin, ymax, ix, iy, nx, ny);
  setColorFon(colorFon);
  //setFocusPolicy ( QWidget::StrongFocus );
}

DrawMemBase::DrawMemBase(QWidget *parent,
                         //char *infX, char *infY,
                         const QString &infX, const QString &infY,
                         long iR,long iPgr, long kRx, long kRy) :
                         WIDGET(parent),
                         fildView(QRect(0,0,1,1)), infx(infX), infy(infY),
                         ir(iR), ipgr(iPgr)
{
  setFocusPolicy(Qt::StrongFocus);
  //setWindowFlags(Qt::WNoAutoErase);
  error=true;
  latch=false;
  krx0=kRx;
  kry0=kRy;
  flagRangeX=flagRangeY=false; // диапазон изменений аргумента и функции не определен
  flagMinMax=false;
  realBegX=realBegY=.0;
  otst=otstBegX=otstBegY=0;
  otstup=2; // отступ для закрашиваемой области
  xmin=xmax=ymin=ymax=.0;
  colorFon  =QColor(255,255,255);
  colorText =QColor(0,0,0);
  colorTextMetka =QColor(100,100,100);
  colorSetka=QColor(200,200,200);
  colorAxe  =QColor(0,0,0);
  colorSelectFild=QColor(255,255,255);
  colorMarkFild=QColor(0,255,0);
  colorLineFild=colorFon;
  //setBackgroundColor(colorFon);

  font=new QFont();
  fm=new QFontMetrics(*font);
  pointMetka=QPoint(0,0);
  metkaText=QString::null;

  flagMouseDesable=true; // запретить выделение областей мышью
  flagMouseLeftPress=false;
  flagMouseRihtPress=false;
  flagMouseMidPress =false;
  flagMouseRelease  =false;
  flagMouseMove     =false;
  //flagResize        =false;
  flagResize        =true;
  flagKeyCtrl       =false;
  flagIn            =false;
  flagMarker        =false;
  lineSelectFild=QRect(0,0,0,0); // выделяемая область
  lineCtrl=QRect(0,0,0,0);
  kolMarkFild=0;
  for(int i=0; i<MaxKolMarkFild; i++)
  {
      xMarkBegin[i]=.0;
      xMarkEnd[i]=.0;
      lineMarkFild[i]=QRect(0,0,0,0);
  }

  pix=0;
  pixSetka=0;
  marker=new MyMarker(xmin, xmax, ymin, ymax, ix, iy, nx, ny);

  setColorFon(colorFon);

  //setFocusPolicy ( QWidget::StrongFocus );
}

DrawMemBase::~DrawMemBase()
{
  delete font;
  delete fm;
  delete marker;
  if (pix)
    delete pix;
  if (pixSetka)
    delete pixSetka;
}/* */

void DrawMemBase::paintEvent(QPaintEvent *e)
{
    QColor color;
    QRect r=contentsRect();

    fildView=r;
    ix=0;
    iy=fildView.bottom()-fildView.top();
    nx=fildView.right()-fildView.left();
    ny=iy;

    //cout<<endl<<"DrawMemBase::paintEvent"<<flush;
    if (pix)
        delete pix;
    if (pixSetka)
        delete pixSetka;
    pix     =new QImage(nx, ny, QImage::Format_ARGB32_Premultiplied);
    pixSetka=new QImage(nx, ny, QImage::Format_ARGB32_Premultiplied);
    pixSetka->fill(Qt::transparent);

    left=0;
    right=nx;
    top=0;
    bottom=ny;
    krx=krx0;
    kry=kry0;

    QPainter p;

    p.begin(pix);
    QBrush brush( colorFon, Qt::SolidPattern );
    p.fillRect(fildView,brush);
    //QBrush brush( QColor(255,255,255), Qt::SolidPattern );
    //p.fillRect(fildView,brush);

    lineCtrl=QRect(ix,iy,ix+nx,iy+size.height()); // область для информации о нажатой Ctrl
    
    rClear.setLeft(left+ix+1);
    rClear.setRight(left+ix+nx);
    rClear.setTop(top+1);
    rClear.setBottom(top+iy-1);

    if (flagKeyCtrl)
    {
        color=colorLineFild;
    }
    else
        color=colorFon;
    p.setPen(color);
    p.setBrush(color);
    p.drawRect(lineCtrl);
    color=colorMarkFild;
    p.setPen(color);
    p.setBrush(color);

    p.setPen(colorMarkFild);
    p.setBrush(colorMarkFild);
    for(int i=0; i<maxKolMarkFild && lineMarkFild[i].width()>0 && lineMarkFild[i].height()>0; i++)
    {
        if (flagResize) /////////////////////////////
        {
            int x1=(xMarkBegin[i]<xmin)? size.width() : (int)((xMarkBegin[i]-xmin)/(xmax-xmin)*(nx-otst)+size.width());
            int x2=(xMarkEnd[i]>xmax)? nx+size.width() : (int)((xMarkEnd[i]-xmin)/(xmax-xmin)*(nx-otst)+size.width());
            lineMarkFild[i].setLeft(x1);
            lineMarkFild[i].setRight(x2);
        }
        lineMarkFild[i].setTop(otstup);
        lineMarkFild[i].setBottom(ny-otstup);
        p.drawRect(lineMarkFild[i]);
    }
    if (lineSelectFild.width()>0 && lineSelectFild.height()>0)
    {
        p.setPen(colorSelectFild);
        p.setBrush(colorSelectFild);
        p.drawRect(lineSelectFild);
    }

    //cout<<endl<<"flagMarker="<<flagMarker;
    if (flagMarker || flagMouseMidPress && flagMouseMove)
    {
        marker->setMinMax(xmin,xmax,ymin,ymax);
        marker->setGeometry(ix,iy,nx,ny);
        marker->draw(p);
    }

    p.end();

    p.begin(pixSetka);
    size=grraz(p);
    if (size==QSize(0,0))
      error=false;   // ошибка
    else
      error=true;
    p.end();

    flagResize=false;
}

void DrawMemBase::resizeEvent(QResizeEvent *event)
{
    flagResize=true;
    QWidget::resizeEvent(event);
}

void DrawMemBase::setInfXY( const QString &infX, const QString &infY )
{
    bool flagX=false, flagY=false;
    if (infX.length()>0)
    {
        flagX=true;
        infx=infX;
    }
    if (infY.length()>0)
    {
        flagY=true;
        infy=infY;
    }
}

void DrawMemBase::mouseDoubleClickEvent ( QMouseEvent * e )
{
    int i, k;
    //std::cout<<std::endl<<"contentsMouseDoubleClickEvent"<<std::flush;

    if (flagMouseDesable)
    {
        flagMouseMidPress =false;
        flagMouseLeftPress=false;
        flagMouseRihtPress=false;
        flagMouseMove     =false;
        return;
    }
    //std::cout<<std::endl<<"contentsMouseDoubleClickEvent"<<std::flush;

    if (e->button()==Qt::LeftButton)
    {
    }

    if (e->button()==Qt::RightButton)
    {
        flagMouseLeftPress=false;
        flagMouseRihtPress=false;
        flagMouseMidPress =false;
        flagMouseMove     =false;

        for(i=0; i<kolMarkFild; i++)
            lineMarkFild[i].setSize(QSize(0,0));
        kolMarkFild=0;

        emit signalResetSelectFild();

        //repaint(false);
        update();
    }
    //std::cout<<std::endl<<"mouseDoubleClickEvent  kolMarkFild="<<kolMarkFild<<" maxKolMarkFild="<<maxKolMarkFild<<std::flush;
}

void DrawMemBase::mousePressEvent ( QMouseEvent * e )
{
    int i, k;
    emit signalPressMouse(numberWindow, e->button());

    //std::cout<<std::endl<<"mousePressEvent  kolMarkFild="<<kolMarkFild<<" maxKolMarkFild="<<maxKolMarkFild<<std::flush;

    if (e->button()==Qt::MidButton)
    {
        flagMouseMidPress=true;
        flagMouseLeftPress=false;
        flagMouseRihtPress=false;
        flagMouseMove     =false;
        setCursor(QCursor(Qt::CrossCursor));
        pointMetka=e->pos();
        posX=xmin+(double)(pointMetka.x()-ix)*(xmax-xmin)/(double)(nx-otst)+realBegX;
        posY=ymin-(double)(pointMetka.y()-iy)*(ymax-ymin)/(double)(ny-otst)+realBegY;
        //std::cout<<std::endl<<"pointX="<<pointMetka.x()<<"  pointY="<<pointMetka.y()<<std::flush;
        //std::cout<<std::endl<<"posX="<<posX<<"  posY="<<posY<<std::flush;
        //metkaText.sprintf("%f %f",posX,posY);
        emit signalRealValue(posX, posY);
        update();
    }

    if (flagMouseDesable)
        return;

    //cout<<endl<<"contentsMousePressEvent"<<flush;

    pointBegin=e->pos();
    pointTemp=pointBegin;

    if (e->button()==Qt::LeftButton)
    {
        flagMouseLeftPress=true;
        flagMouseMidPress =false;
        flagMouseRihtPress=false;
        setCursor(QCursor(Qt::ArrowCursor));

        if (flagKeyCtrl)
        {
            QPoint point=e->pos();
      
            flagMouseLeftPress=false;
            flagMouseMidPress =false;
            flagMouseRihtPress=false;
            flagMouseMove     =false;
      
            for(i=0; i<kolMarkFild; i++)
            {
                if ( point.x() >= lineMarkFild[i].left() && point.x() <= lineMarkFild[i].right() )
                {
                    flagIn=true;
                    xMarkBegin[i]=.0;
                    xMarkEnd[i]=.0;
                    lineMarkFild[i].setSize(QSize(0,0));
                    update();
                    // перерисовать поле
                }
            }
            if (flagIn)
            {
                flagIn=false;
                emit signalResetMarkFild();
                k=0;
                for(i=0; i<kolMarkFild; i++)
                {
                    if ( lineMarkFild[i].width()==0)
                        continue;
                    if (k<i)
                    {
                        xMarkBegin[k]=xMarkBegin[i];
                        xMarkEnd[k]  =xMarkEnd[i];
                        lineMarkFild[k].setSize(QSize(lineMarkFild[i].width(),lineMarkFild[i].height()));
                        lineMarkFild[k].setX(lineMarkFild[i].x());
                        lineMarkFild[k].setY(lineMarkFild[i].y());
                        lineMarkFild[i].setSize(QSize(0,0));
                    }
                    k++;
                }
                kolMarkFild=k;
                double x1, x2;
                for(i=0; i<kolMarkFild; i++)
                {
                    x1=xmin+(xmax-xmin)*(lineMarkFild[i].x()-size.width())/(double)(nx-otst);
                    x2=xmin+(xmax-xmin)*((lineMarkFild[i].x()+lineMarkFild[i].width())-size.width())/(double)(nx-otst);
                    emit signalChangeMarkFild(i, x1, x2);
                }
            }
            else
            {
                for(i=0; i<kolMarkFild; i++)
                {
                    xMarkBegin[i]=.0;
                    xMarkEnd[i]=.0;
                    lineMarkFild[i].setSize(QSize(0,0));
                }

                kolMarkFild=0;
                update();
                emit signalResetMarkFild();
            }
        }
    }

    if (e->button()==Qt::RightButton)
    {
        flagMouseLeftPress=false;
        flagMouseMidPress =false;
        flagMouseMove     =false;
        flagMouseRihtPress=true;
        setCursor(QCursor(Qt::ArrowCursor));
    }

    pointEnd=pointBegin;
}

void DrawMemBase::mouseReleaseEvent ( QMouseEvent * e )
{
    //cout<<endl<<"contentsMouseReleaseEvent"<<flush;
    //setCursor(QCursor(ArrowCursor));

    if (flagMouseMidPress)
    {
        metkaText=QString::null;
        emit signalReleaseMouseMid();
        update();
    }

    if (flagMouseDesable)
    {
        flagMouseMidPress =false;
        flagMouseLeftPress=false;
        flagMouseRihtPress=false;
        flagMouseMove     =false;
        return;
    }

    //cout<<endl<<"1 contentsMouseReleaseEvent"<<flush;

    if (flagMouseLeftPress && maxKolMarkFild)
    {
        kolMarkFild--; /////////////
        if ( pointBegin.x() >= pointEnd.x() )
        {
            lineMarkFild[kolMarkFild].setSize(QSize(0,0));
            flagMouseLeftPress=false;
            flagMouseRihtPress=false;
            flagMouseMidPress =false;
            flagMouseMove =false;
            if (!kolMarkFild)
                emit signalResetSelectFild();
            return;
        }
        else
        {
            lineMarkFild[kolMarkFild].setLeft(pointBegin.x());
            lineMarkFild[kolMarkFild].setRight(pointEnd.x());
            lineMarkFild[kolMarkFild].setTop(otstup);
            lineMarkFild[kolMarkFild].setBottom(ny-otstup);
        }

        double x1, x2;
        x1=xmin+(xmax-xmin)*(pointBegin.x()-size.width())/(double)(nx-otst);
        x2=xmin+(xmax-xmin)*(pointEnd.x()-size.width())/(double)(nx-otst);

        for(int i=0; i<maxKolMarkFild; i++)
        {
            if ( i==kolMarkFild || lineMarkFild[i].width()==0  ||
                 ( lineMarkFild[i].width()>0 ) &&
                 ( pointBegin.x() > lineMarkFild[i].x()+lineMarkFild[i].width() &&
                   pointEnd.x()   > lineMarkFild[i].x()+lineMarkFild[i].width() ||
                   pointBegin.x() < lineMarkFild[i].x() && pointEnd.x() < lineMarkFild[i].x()
                 )
               )
                continue;
            else
            {
                lineMarkFild[kolMarkFild].setSize(QSize(0,0));
                flagMouseLeftPress=false;
                flagMouseMove =false;
                flagMouseRihtPress=false;
                flagMouseMidPress =false;
                return;
            }
        }


        xMarkBegin[kolMarkFild]=x1;
        xMarkEnd[kolMarkFild]=x2;
        emit signalChangeMarkFild(kolMarkFild, x1, x2);

        if (kolMarkFild<maxKolMarkFild)
            kolMarkFild++;
    }
    if (flagMouseRihtPress)
    {
        if ( pointBegin.x() >= pointEnd.x() )
        {
            lineSelectFild.setSize(QSize(0,0));
            flagMouseLeftPress=false;
            flagMouseRihtPress=false;
            flagMouseMidPress =false;
            flagMouseMove =false;
            return;
        }
        lineSelectFild.setLeft(pointBegin.x());
        lineSelectFild.setRight(pointEnd.x());
        lineSelectFild.setTop(otstup);
        lineSelectFild.setBottom(ny-otstup);
        double x1, x2;
        x1=xmin+(xmax-xmin)*(pointBegin.x()-size.width())/(double)(nx-otst);
        x2=xmin+(xmax-xmin)*(pointEnd.x()-size.width())/(double)(nx-otst);

        emit signalChangeSelectFild(x1, x2);

        update();
        lineSelectFild.setSize(QSize(0,0));
    }

    flagMouseMidPress =false;
    flagMouseLeftPress=false;
    flagMouseRihtPress=false;
    flagMouseMove     =false;
    //std::cout<<std::endl<<"mouseReleaseEvent  kolMarkFild="<<kolMarkFild<<" maxKolMarkFild="<<maxKolMarkFild<<std::flush;
}

void DrawMemBase::mouseMoveEvent ( QMouseEvent * e )
{
    pointMetka=e->pos();
    if (pointMetka.x()<=ix || pointMetka.x()>=ix+nx)
        return;
    //std::cout<<std::endl<<"ix="<<ix<<" pointMetka.x()="<<pointMetka.x()<<" pointBegin.x()=="<<pointBegin.x();
    if (pointBegin.x()<ix && pointMetka.x()>ix)
    {
        pointBegin.rx()=ix+1;
        pointTemp=pointBegin;
        //std::cout<<std::endl<<"    ix="<<ix<<" pointMetka.x()="<<pointMetka.x()<<" pointBegin.x()=="<<pointBegin.x();
    }
    if (pointMetka.x()>=ix+nx)
    {
        pointMetka.rx()=ix+nx-1;
    }


    if (flagMouseMidPress) // движется мышка
    {
        flagMouseMove=true;
        posX=xmin+(double)(pointMetka.x()-ix)*(xmax-xmin)/(double)(nx-otst)+realBegX;
        posY=ymin-(double)(pointMetka.y()-iy)*(ymax-ymin)/(double)(ny-otst)+realBegY;
        //std::cout<<std::endl<<"pointX="<<pointMetka.x()<<"  pointY="<<pointMetka.y()<<" ix="<<ix<<" xmax-xmin="<<xmax-xmin<<std::flush;
        //std::cout<<std::endl<<"posX="<<posX<<"  posY="<<posY<<"  realBegX="<<realBegX<<"  realBegY="<<realBegY<<std::flush;
        //metkaText.sprintf("%f %f",posX,posY);
        emit signalRealValue(posX, posY);

        marker->setMinMax(xmin,xmax,ymin,ymax);
        marker->setGeometry(ix,iy,nx,ny);

        marker->setCenterMarker(posX-realBegX,posY-realBegY);
        update();
        //repaint(false);
    }

    if (flagMouseDesable)
        return;
    //std::cout<<std::endl<<"1 kolMarkFild="<<kolMarkFild<<"  maxKolMarkFild="<<maxKolMarkFild<<std::flush;
    if (flagMouseLeftPress && !flagKeyCtrl && maxKolMarkFild)
    {
        flagMouseMove=true;
        pointEnd=pointMetka;
        pointEnd.ry()=0;

        QRect r;
        r.setTop(otstup);
        r.setBottom(ny-otstup);

        while(kolMarkFild>=maxKolMarkFild)
        {
            kolMarkFild--;
            lineMarkFild[kolMarkFild].setSize(QSize(0,0));
        }

        //std::cout<<std::endl<<"2 kolMarkFild="<<kolMarkFild<<std::flush;
        if ( pointBegin.x() <= pointEnd.x() )
        {
            if (pointEnd.x()>pointTemp.x())
            {
                r.setLeft(pointTemp.x());
                r.setRight(pointEnd.x());
            }
            else
                if (pointEnd.x()<pointTemp.x())
                {
                    r.setLeft(pointEnd.x());
                    r.setRight(pointTemp.x());
                }
            lineMarkFild[kolMarkFild].setLeft(pointBegin.x());
            lineMarkFild[kolMarkFild].setRight(pointEnd.x());
            lineMarkFild[kolMarkFild].setTop(otstup);
            lineMarkFild[kolMarkFild].setBottom(ny-otstup);
            pointTemp=pointEnd;
            kolMarkFild++;
            //std::cout<<std::endl<<"3 kolMarkFild="<<kolMarkFild<<std::flush;
        }
        else
        {
            if (pointTemp.x()>pointBegin.x())
            {
                r.setLeft(pointBegin.x());
                r.setRight(pointTemp.x());
                pointTemp=pointBegin;
            }
            lineMarkFild[kolMarkFild].setSize(QSize(0,0));
        }
        update();
    }

    if (flagMouseRihtPress)
    {
        flagMouseMove=true;
        pointEnd=pointMetka;
        pointEnd.ry()=0;

        if ( pointBegin.x() <= pointEnd.x() )
        {
            QRect r;
            if (pointEnd.x()>pointTemp.x())
            {
                r.setLeft(pointTemp.x());
                r.setRight(pointEnd.x());
            }
            else
                if (pointEnd.x()<pointTemp.x())
                {
                    r.setLeft(pointEnd.x());
                    r.setRight(pointTemp.x());
                }
            r.setTop(otstup);
            r.setBottom(ny-otstup);
            
            lineSelectFild.setLeft(pointBegin.x());
            lineSelectFild.setRight(pointEnd.x());
            lineSelectFild.setTop(otstup);
            lineSelectFild.setBottom(ny-otstup);
            pointTemp=pointEnd;
        }
        else
        {
            if (pointTemp.x()>=pointBegin.x())
            {
                QRect r;
                r.setLeft(pointBegin.x());
                r.setRight(pointTemp.x());
                r.setTop(otstup);
                r.setBottom(ny-otstup);
                lineSelectFild.setRight(pointBegin.x());
                pointTemp=pointBegin;
            }
        }
        update();
    }
}

void DrawMemBase::keyReleaseEvent(QKeyEvent *e)
{
    QColor color=colorFon;
    //std::cout<<std::endl<<"keyRelease="<<e->key();
    WIDGET::keyReleaseEvent(e);
    //std::cout<<std::endl<<"1 keyRelease="<<e->key();
    switch(e->key())
    {
    case Qt::Key_Control:
        {
            //std::cout<<std::endl<<"2 keyRelease="<<e->key();
            if (!maxKolMarkFild)
                break;
            flagKeyCtrl=false;
            update();
        }
        break;
    }
}

void DrawMemBase::keyPressEvent(QKeyEvent *e)
{
    QColor color=colorLineFild;
    //std::cout<<std::endl<<"keyPress="<<e->key();
    WIDGET::keyPressEvent(e);
    //std::cout<<std::endl<<"1 keyPress="<<e->key();
    switch(e->key())
    {
    case Qt::Key_Control:
        {
            //std::cout<<std::endl<<"2 keyPress="<<e->key();
            if (!maxKolMarkFild)
                break;
            flagKeyCtrl=true;
            update();
        }
        break;
    case Qt::Key_Escape:
        {
            //std::cout<<std::endl<<"3 keyPress="<<e->key();
            for(int i=0; i<kolMarkFild; i++)
            {
                xMarkBegin[i]=.0;
                xMarkEnd[i]=.0;
                lineMarkFild[i].setSize(QSize(0,0));
            }

            kolMarkFild=0;
            update();
            emit signalResetMarkFild();
        }
        break;
    }
}

void DrawMemBase::slotSetMarkerToPosition(double posX, double posY)
{
    //cout<<endl<<"slotSetMarkerToPosition"<<flush;
    posX-=realBegX;
    posY-=realBegY;

    marker->setMinMax(xmin,xmax,ymin,ymax);
    marker->setGeometry(ix,iy,nx,ny);
    
    marker->setCenterMarker(posX,posY);
    update();
}

void DrawMemBase::setMarkFild(double x1, double x2, int n)
{
    if (n>=maxKolMarkFild)
        return;

    xMarkBegin[n]=x1;
    xMarkEnd[n]=x2;

    QPoint p1, p2;
    p1.ry()=otstup;
    p2.ry()=ny-otstup;

    p1.rx()=(x1<xmin)? size.width() : (int)((x1-xmin)/(xmax-xmin)*(nx-otst)+size.width());
    p2.rx()=(x2>xmax)? nx+size.width() : (int)((x2-xmin)/(xmax-xmin)*(nx-otst)+size.width());
    
    lineMarkFild[n].setLeft(p1.x());
    lineMarkFild[n].setTop(p1.y());
    lineMarkFild[n].setRight(p2.x());
    lineMarkFild[n].setBottom(p2.y());
    update();
}

void DrawMemBase::setTextMetka(QString &str)
{
    metkaText=str;
}

void DrawMemBase::drawMetka(QPainter &p)
{
    if (metkaText.isEmpty())
        return;
    int size=fm->width(metkaText);
    int h   =fm->height();
    int X=pointMetka.x();
    int Y=pointMetka.y();
    if (X+size>ix+nx)
        X-=size;
    while(Y>iy)
        Y-=h;
    while(Y-h<iy-ny)
        Y+=h;
    p.setPen(colorTextMetka);
    p.drawText(X,Y,metkaText);
}

void DrawMemBase::setKolMarkFild(int n) // задает число помеченных участков
{
    kolMarkFild=n;
    for(int j=kolMarkFild; j<maxKolMarkFild; j++)
    {
        lineMarkFild[j].setSize(QSize(0,0));
        xMarkBegin[j]=xMarkEnd[j]=.0;
    }
    update();
}

void DrawMemBase::setXmin(double x)
{
    xmin=x;
    marker->setMinMax(xmin,xmax,ymin,ymax);
    update();
}

void DrawMemBase::setYmin(double y)
{
    ymin=y;
    marker->setMinMax(xmin,xmax,ymin,ymax);
    update();
}

void DrawMemBase::setXmax(double x)
{
    xmax=x;
    marker->setMinMax(xmin,xmax,ymin,ymax);
    update();
}

void DrawMemBase::setYmax(double y)
{
    ymax=y;
    marker->setMinMax(xmin,xmax,ymin,ymax);
    update();
}

void DrawMemBase::setXYminmax(double x1, double x2, double y1, double y2)
{
    xmin=x1;
    xmax=x2;
    ymin=y1;
    ymax=y2;
    marker->setMinMax(xmin,xmax,ymin,ymax);
    update();
}
