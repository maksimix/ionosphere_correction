/***************************************************************************
 ***************************************************************************
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

#include "drawbasecanvas.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <qcursor.h>
//Added by qt3to4:
#include <QKeyEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <stdlib.h>

using namespace std;

DrawBaseCanvas::DrawBaseCanvas(Q3Canvas *viewing, QWidget *parent,
                               char *infX, char *infY,
                               double xMin, double xMax, double yMin, double yMax,
                               long iR, long iPgr, long kRx, long kRy) :
                               Q3CanvasView(viewing, parent),
                               fildView(QRect(0,0,1,1))
{
  canvas=viewing;
  widget=parent;
  numberWindow=0;

  flagMouseDesable=true; // запретить выделение областей мышью

  ir=iR;
  ipgr=iPgr;
  krx=kRx;
  kry=kRy;
  infx=infX;
  infy=infY;

  error=true;
  divot=NULL;
  xmin=xMin;
  xmax=xMax;
  ymin=yMin;
  ymax=yMax;
  realBegX=realBegY=.0;
  flagRangeX=flagRangeY=true; // диапазон изменений аргумента и функции определен
  flagMinMax=true;
  otst=0;
  colorText =QColor(0,0,0);
  colorSetka=QColor(200,200,200);
  colorAxe  =QColor(0,0,0);
  colorSelectFild=QColor(255,255,255);
  setColorFon(QColor(255,255,255));
  // расположение плоскостей графика
  zFild=1.;    // фон графика
  zMarkFild=2.;
  zLineFild=5.;
  zSetka=256.;  // сетка осей графика
  zBase=10.;   // начало плоскостей прорисовки графиков
  zTextMetka=300.;
  zSelectFild=3.;
  // отменить скроллинг канваса
  setHScrollBarMode (AlwaysOff);
  setVScrollBarMode (AlwaysOff);

  font=new QFont("times",10);
  fm=new QFontMetrics(*font);
  pointMetka=QPoint(0,0);
  canvasText=new Q3CanvasText(canvas);
  canvasText->setZ(zTextMetka);
  canvasText->setText(QString(""));
  canvasText->setX(.0);
  canvasText->setY(.0);
  canvasText->setFont(*font);
  canvasText->setColor(QColor(0,0,0));
  canvasText->show();

  ix=iy=nx=ny=0;

  canvasSetka=new MyRectCanvasSetka(canvas, fildView, &xmin, &xmax, &ymin, &ymax, &ix, &iy, &nx, &ny,
                                    &top, &left, &bottom, &right, krx, kry, ir);

  setFlagText(true);

  canvasSetka->setColorText(colorText);
  canvasSetka->setColorSetka(colorSetka);
  canvasSetka->setColorAxe(colorAxe);
  canvasSetka->setInf(infx, infy);
  canvasSetka->setIpgr(ipgr);
  canvasSetka->setZ(zSetka);
  canvasSetka->show();

  fildDiagramm=new Q3CanvasRectangle(canvas);
  fildDiagramm->setPen(Qt::NoPen);
  fildDiagramm->setZ(zFild);
  fildDiagramm->show();

  colorLineFild=colorFon;
  QBrush brush( colorLineFild, Qt::SolidPattern );
  QPen pen;
  pen.setColor(colorLineFild);
  pen.setCapStyle(Qt::FlatCap);
  pen.setWidth(1);
  
  lineFild=new Q3CanvasRectangle(canvas);
  lineFild->setPen(pen);
  lineFild->setBrush(brush);
  lineFild->setSize(0,0);
  lineFild->setZ(zLineFild);
  lineFild->show();

  flagMouseLeftPress=false;
  flagMouseRihtPress=false;
  flagMouseMidPress =false;
  flagMouseRelease  =false;
  flagMouseMove     =false;
  flagKeyCtrl       =false;
  kolMarkFild=0;

  colorMarkFild=QColor(0,255,0);
  pen.setColor(colorMarkFild);
  brush.setColor(colorMarkFild);

  maxKolMarkFild=MaxKolMarkFild;
  for(int i=0; i<MaxKolMarkFild; i++)
  {
      lineMarkFild[i]=new Q3CanvasRectangle(canvas);
      lineMarkFild[i]->setPen(pen);
      lineMarkFild[i]->setBrush(brush);
      lineMarkFild[i]->setSize(0,0);
      lineMarkFild[i]->setZ(zMarkFild);
      lineMarkFild[i]->show();
  }

  pen.setColor(colorSelectFild);
  brush.setColor(colorSelectFild);
  lineSelectFild=new Q3CanvasRectangle(canvas);
  lineSelectFild->setPen(pen);
  lineSelectFild->setBrush(brush);
  lineSelectFild->setSize(0,0);
  lineSelectFild->setZ(zSelectFild);
  lineSelectFild->show();

  canvasMarker=new MyCanvasMarker(canvas, xmin, xmax, ymin, ymax, ix, iy, nx, ny);
  canvasMarker->setZ(zTextMetka);
  canvasMarker->show();

  resizeMyCanvas();

}

DrawBaseCanvas::DrawBaseCanvas(Q3Canvas *viewing, QWidget *parent,
                               char *infX, char *infY,
                               long iR, long iPgr, long kRx, long kRy) :
                               Q3CanvasView(viewing, parent),
                               fildView(QRect(0,0,1,1))
{
  error=true;
  canvas=viewing;
  widget=parent;
  numberWindow=0;

  ir=iR;
  ipgr=iPgr;
  krx=kRx;
  kry=kRy;
  infx=infX;
  infy=infY;

  flagRangeX=flagRangeY=false; // диапазон изменений аргумента и функции не определен
  flagMinMax=false;
  divot=NULL;
  otst=0;
  xmin=xmax=ymin=ymax=.0;
  colorText =QColor(0,0,0);
  colorSetka=QColor(200,200,200);
  colorAxe  =QColor(0,0,0);
  colorSelectFild=QColor(255,255,255);
  setColorFon(QColor(255,255,255));
  // расположение плоскостей графика
  zFild=1.;    // фон графика
  zMarkFild=2.;
  zLineFild=5.;
  zSetka=256.;  // сетка осей графика
  zBase=10.;   // начало плоскостей прорисовки графиков
  zTextMetka=300.;
  zSelectFild=3.;
  // отменить скроллинг канваса
  setHScrollBarMode (AlwaysOff);
  setVScrollBarMode (AlwaysOff);

  canvasSetka=new MyRectCanvasSetka(canvas, fildView, &xmin, &xmax, &ymin, &ymax, &ix, &iy, &nx, &ny,
                                    &top, &left, &bottom, &right, krx, kry, ir);


  setFlagText(true);

  font=new QFont("times",8);
  fm=new QFontMetrics(*font);
  canvasText=new Q3CanvasText(canvas);
  canvasText->setZ(zTextMetka);
  canvasText->setText(QString(""));
  canvasText->setX(.0);
  canvasText->setY(.0);
  canvasText->setFont(*font);
  canvasText->setColor(QColor(0,0,0));
  canvasText->show();

  canvasSetka->setColorText(colorText);
  canvasSetka->setColorSetka(colorSetka);
  canvasSetka->setColorAxe(colorAxe);
  canvasSetka->setInf(infx, infy);
  canvasSetka->setIpgr(ipgr);
  canvasSetka->setZ(zSetka);
  canvasSetka->show();

  fildDiagramm=new Q3CanvasRectangle(canvas);
  fildDiagramm->setPen(Qt::NoPen);
  fildDiagramm->setZ(zFild);
  fildDiagramm->show();

  colorLineFild=colorFon;
  QBrush brush( colorLineFild, Qt::SolidPattern );
  QPen pen(colorLineFild);
  pen.setCapStyle(Qt::FlatCap);
  pen.setWidth(1);
  lineFild=new Q3CanvasRectangle(canvas);
  lineFild->setPen(pen);
  lineFild->setBrush(brush);
  lineFild->setSize(0,0);
  lineFild->setZ(zLineFild);
  lineFild->show();

  flagMouseLeftPress=false;
  flagMouseRihtPress=false;
  flagMouseRelease  =false;
  flagMouseMove     =false;

  colorMarkFild=QColor(0,255,0);
  pen.setColor(colorMarkFild);
  brush.setColor(colorMarkFild);


  kolMarkFild=0;
  for(int i=0; i<MaxKolMarkFild; i++)
  {
      lineMarkFild[i]=new Q3CanvasRectangle(canvas);
      lineMarkFild[i]->setPen(pen);
      lineMarkFild[i]->setBrush(brush);
      lineMarkFild[i]->setSize(0,0);
      lineMarkFild[i]->setZ(zMarkFild);
      lineMarkFild[i]->show();
  }

  pen.setColor(colorSelectFild);
  brush.setColor(colorSelectFild);
  lineSelectFild=new Q3CanvasRectangle(canvas);
  lineSelectFild->setPen(pen);
  lineSelectFild->setBrush(brush);
  lineSelectFild->setSize(0,0);
  lineSelectFild->setZ(zSelectFild);
  lineSelectFild->show();

  canvasMarker=new MyCanvasMarker(canvas, xmin, xmax, ymin, ymax, ix, iy, nx, ny);
  canvasMarker->setZ(zTextMetka);
  canvasMarker->show();
}

DrawBaseCanvas::~DrawBaseCanvas()
{
  if (divot)
      delete[] divot;

  for(int i=0; i<MaxKolMarkFild; i++)
  {
      lineMarkFild[i]->hide();
      delete lineMarkFild[i];
  }

  fildDiagramm->hide();
  delete fildDiagramm;
  canvasSetka->hide();
  delete canvasSetka;
  lineFild->hide();
  delete lineFild;
  canvasText->hide();
  delete canvasText;
  delete font;
  delete fm;
  delete canvasMarker;
}

void DrawBaseCanvas::resizeEvent(QResizeEvent *event)
{
    Q3CanvasView::resizeEvent(event);

    resizeMyCanvas();
}

void DrawBaseCanvas::resizeMyCanvas() // подстроить канвас под размер виджета
{
       fildView=widget->geometry ();

       ny=fildView.height()-frameWidth();
       nx=fildView.width()-frameWidth();
       canvas->resize(nx, ny);
       resize(nx, ny);
   
       ix=0;
       iy=ny;

       QBrush brush( colorFon, Qt::SolidPattern );

       fildDiagramm->setBrush(brush);
       fildDiagramm->setSize(nx, ny);
       fildDiagramm->setX(0);
       fildDiagramm->setY(0);
   
       canvasSetka->setFildView(fildView);
       canvasSetka->setPen(Qt::NoPen);
       size=canvasSetka->grraz();
       canvasSetka->setX(0);
       canvasSetka->setY(0);
       canvasSetka->setSize(nx, ny);
       error=canvasSetka->getError();
   
       rClear.setLeft(left+ix+1);
       rClear.setRight(left+ix+nx);
       rClear.setTop(top+1);
       rClear.setBottom(top+iy-1);

       QPen pen(colorLineFild);
       pen.setWidth(1);
       lineFild->setPen(pen);
       brush.setColor(colorLineFild);
       lineFild->setBrush(brush);
       lineFild->setSize(right-left-size.width(),size.height());
       lineFild->setX(left+size.width());
       lineFild->setY(iy);

       for(int i=0; i<kolMarkFild; i++)
       {
           setMarkFild(xMarkBegin[i],xMarkEnd[i],i);
       }

       canvasMarker->setGeometry(ix,iy,nx,ny);
}

void DrawBaseCanvas::contentsMouseDoubleClickEvent ( QMouseEvent * e )
{
	int i, k;
    if (flagMouseDesable)
    {
        flagMouseMidPress =false;
        flagMouseLeftPress=false;
        flagMouseRihtPress=false;
        flagMouseMove     =false;
        return;
    }
    //cout<<endl<<"contentsMouseDoubleClickEvent"<<flush;

    if (e->button()==Qt::LeftButton)
    {
        QPoint point=e->pos();
        bool flagIn=false;

        flagMouseLeftPress=false;
        flagMouseRihtPress=false;
        flagMouseMidPress =false;
        flagMouseMove     =false;

        for(i=0; i<kolMarkFild; i++)
        {
            if ( point.x() >= lineMarkFild[i]->x() && point.x() <= lineMarkFild[i]->x()+lineMarkFild[i]->width() )
            {
                lineMarkFild[i]->setSize(0,0);
                flagIn=true;
            }
        }
        if (flagIn)
        {
            emit signalResetMarkFild();
            k=0;
            for(i=0; i<kolMarkFild; i++)
            {
                if ( lineMarkFild[i]->width()==0)
                    continue;
                if (k<i)
                {
                    lineMarkFild[k]->setSize(lineMarkFild[i]->width(),lineMarkFild[i]->height());
                    lineMarkFild[k]->setX(lineMarkFild[i]->x());
                    lineMarkFild[k]->setY(lineMarkFild[i]->y());
                    lineMarkFild[i]->setSize(0,0);
                }
                k++;
            }
            kolMarkFild=k;
            double x1, x2;
            x1=xmin+(xmax-xmin)*(pointBegin.x()-size.width())/nx;
            x2=xmin+(xmax-xmin)*(pointEnd.x()-size.width())/nx;
            for(i=0; i<kolMarkFild; i++)
            {
                x1=xmin+(xmax-xmin)*(lineMarkFild[i]->x()-size.width())/nx;
                x2=xmin+(xmax-xmin)*((lineMarkFild[i]->x()+lineMarkFild[i]->width())-size.width())/nx;
                emit signalChangeMarkFild(i, x1, x2);
            }
        }
        else
        {
            for(i=0; i<kolMarkFild; i++)
                lineMarkFild[i]->setSize(0,0);
            kolMarkFild=0;
            emit signalResetMarkFild();
        }
        setCursor(QCursor(Qt::ArrowCursor));

        //emit signalResetMarkFild();
    }

    if (e->button()==Qt::RightButton)
    {
        flagMouseLeftPress=false;
        flagMouseRihtPress=false;
        flagMouseMidPress =false;
        flagMouseMove     =false;

        for(i=0; i<kolMarkFild; i++)
            lineMarkFild[i]->setSize(0,0);
        kolMarkFild=0;

        emit signalResetSelectFild();
    }
}

void DrawBaseCanvas::contentsMousePressEvent ( QMouseEvent * e )
{
    emit signalPressMouse(numberWindow, e->button());

    if (e->button()==Qt::MidButton)
    {
        flagMouseMidPress=true;
        setCursor(QCursor(Qt::CrossCursor));
    }

    if (flagMouseDesable)
        return;

    //cout<<endl<<"contentsMousePressEvent"<<flush;
        
    if (e->button()==Qt::LeftButton)
    {
        while(kolMarkFild>=maxKolMarkFild)
            kolMarkFild--;
        flagMouseLeftPress=true;
        flagMouseMidPress =false;
        flagMouseRihtPress=false;
        flagMouseMove     =false;
        pointBegin=e->pos();
        pointBegin.ry()=ny/2;
        QPen pen=lineMarkFild[kolMarkFild]->pen();
        pen.setWidth(1);
        pen.setColor(colorMarkFild);
        QBrush brush=lineMarkFild[kolMarkFild]->brush();
        brush.setColor(colorMarkFild);
        lineMarkFild[kolMarkFild]->setPen(pen);
        lineMarkFild[kolMarkFild]->setBrush(brush);
        setCursor(QCursor(Qt::ArrowCursor));
    }

    if (e->button()==Qt::RightButton)
    {
        flagMouseLeftPress=false;
        flagMouseMidPress =false;
        flagMouseMove     =false;
        flagMouseRihtPress=true;
        pointBegin=e->pos();
        pointBegin.ry()=ny/2;
        QPen pen=lineSelectFild->pen();
        pen.setWidth(1);
        pen.setColor(colorSelectFild);
        QBrush brush=lineSelectFild->brush();
        brush.setColor(colorSelectFild);
        lineSelectFild->setPen(pen);
        lineSelectFild->setBrush(brush);
        setCursor(QCursor(Qt::ArrowCursor));
    }

    pointEnd=pointBegin;
}

void DrawBaseCanvas::contentsMouseReleaseEvent ( QMouseEvent * e )
{
    setCursor(QCursor(Qt::ArrowCursor));

    if (flagMouseMidPress)
    {
        canvasText->setText(QString(""));
        canvasText->setX(.0);
        canvasText->setY(.0);
    }

    if (flagMouseDesable)
    {
        flagMouseMidPress =false;
        flagMouseLeftPress=false;
        flagMouseRihtPress=false;
        flagMouseMove     =false;
        return;
    }

    //cout<<endl<<"contentsMouseReleaseEvent"<<flush;

    if (flagMouseLeftPress)
    {
        if ( pointBegin.x() >= pointEnd.x() )
        {
            lineMarkFild[kolMarkFild]->setSize(0,0);
            flagMouseLeftPress=false;
            flagMouseRihtPress=false;
            flagMouseMove =false;
            if (!kolMarkFild)
                emit signalResetSelectFild();
            return;
        }
        double x1, x2;
        x1=xmin+(xmax-xmin)*(pointBegin.x()-size.width())/nx;
        x2=xmin+(xmax-xmin)*(pointEnd.x()-size.width())/nx;

        for(int i=0; i<maxKolMarkFild; i++)
        {
            if ( i==kolMarkFild || lineMarkFild[i]->width()==0  ||
                 ( lineMarkFild[i]->width()>0 ) &&
                 ( pointBegin.x() > lineMarkFild[i]->x()+lineMarkFild[i]->width() &&
                   pointEnd.x()   > lineMarkFild[i]->x()+lineMarkFild[i]->width() ||
                   pointBegin.x() < lineMarkFild[i]->x() && pointEnd.x() < lineMarkFild[i]->x()
                 )
               )
                continue;
            else
            {
                lineMarkFild[kolMarkFild]->setSize(0,0);
                flagMouseLeftPress=false;
                flagMouseRihtPress=false;
                flagMouseMove =false;                
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
            lineSelectFild->setSize(0,0);
            flagMouseRihtPress=false;
            flagMouseLeftPress=false;
            flagMouseMove =false;
            return;
        }
        double x1, x2;
        x1=xmin+(xmax-xmin)*(pointBegin.x()-size.width())/nx;
        x2=xmin+(xmax-xmin)*(pointEnd.x()-size.width())/nx;

        emit signalChangeSelectFild(x1, x2);

        cout<<endl<<"x1="<<x1<<"  x2="<<x2<<flush;

        lineSelectFild->setSize(0,0);
    }

    flagMouseMidPress =false;
    flagMouseLeftPress=false;
    flagMouseRihtPress=false;
    flagMouseMove     =false;

    canvas->setAllChanged();
}

void DrawBaseCanvas::setTextMetka(QString &str)
{
    canvasText->setText(str);
    int size=fm->width(str);
    int h   =fm->height();
    int X=pointMetka.x();
    int Y=pointMetka.y();
    if (X+size>ix+nx)
        X-=size;
    if (Y+h>iy)
        Y-=h;
    canvasText->setX((double)X);
    canvasText->setY((double)Y);

    //canvas->setAllChanged();
}

void DrawBaseCanvas::contentsMouseMoveEvent ( QMouseEvent * e )
{
    if (flagKeyCtrl || flagMouseMidPress) // движется мышка и нажата клавиша Ctrl
    {
        pointMetka=e->pos();
        
        posX=xmin+(double)(pointMetka.x()-ix)*(xmax-xmin)/(double)nx+realBegX;
        posY=ymin-(double)(pointMetka.y()-iy)*(ymax-ymin)/(double)ny+realBegY;
        //cout<<endl<<"pointX="<<pointMetka.x()<<"  pointY="<<pointMetka.y()<<flush;
        //cout<<endl<<"posX="<<posX<<"  posY="<<posY<<flush;

        emit signalRealValue(posX, posY);

        canvasMarker->setCenterMarker(posX-realBegX,posY-realBegY);
    }

    if (flagMouseDesable)
        return;

    flagMouseMove=true;
    pointEnd=e->pos();
    pointEnd.ry()=0;
    
    if (flagMouseLeftPress)
    {
        if ( pointBegin.x() < pointEnd.x() )
        {
            lineMarkFild[kolMarkFild]->setX(pointBegin.x());
            lineMarkFild[kolMarkFild]->setY(pointEnd.y());
            lineMarkFild[kolMarkFild]->setSize(pointEnd.x()-pointBegin.x(),ny);
            canvas->setAllChanged();
        }
    }

    if (flagMouseRihtPress)
    {
        if ( pointBegin.x() < pointEnd.x() )
        {
            lineSelectFild->setX(pointBegin.x());
            lineSelectFild->setY(pointEnd.y());
            lineSelectFild->setSize(pointEnd.x()-pointBegin.x(),ny);
            canvas->setAllChanged();
        }
    }
}

void DrawBaseCanvas::setMarkFild(double x1, double x2, int n)
{
    if (n>=maxKolMarkFild)
        return;

    xMarkBegin[n]=x1;
    xMarkEnd[n]=x2;

    QPoint p1, p2;
    p1.ry()=p2.ry()=0;

    p1.rx()=(x1<xmin)? size.width() : (int)((x1-xmin)/(xmax-xmin)*nx+size.width());
    p2.rx()=(x2>xmax)? nx+size.width() : (int)((x2-xmin)/(xmax-xmin)*nx+size.width());
    
    QPen pen=lineMarkFild[n]->pen();
    pen.setWidth(1);
    pen.setColor(colorMarkFild);
    QBrush brush=lineMarkFild[n]->brush();
    brush.setColor(colorMarkFild);
    lineMarkFild[n]->setPen(pen);
    lineMarkFild[n]->setBrush(brush);

    lineMarkFild[n]->setX(p1.x());
    lineMarkFild[n]->setY(p2.y());
    lineMarkFild[n]->setSize(p2.x()-p1.x(),ny);
}

void DrawBaseCanvas::setMinMax(double xMin, double xMax, double yMin, double yMax)
{
    if (xMin>=xMax || yMin>=yMax)
        return;

    xmin=xMin;
    xmax=xMax;
    ymin=yMin;
    ymax=yMax;

    double sizex=xmax-xmin,
           sizey=ymax-ymin;

    while(sizex<1000.)
        sizex*=10.;
    while(sizey<1000.)
        sizey*=10.;

    resizeMyCanvas();

    canvasSetka->setSize((int)sizex, (int)sizey); // это сделано только для автоматической перерисовки сетки

    canvasMarker->setMinMax(xmin,xmax,ymin,ymax);
}

void DrawBaseCanvas::slotKeyReleaseEvent(QKeyEvent *e)
{
    cout<<endl<<"keyRelease="<<e->key();
    switch(e->key())
    {
    case Qt::Key_Control:
        flagKeyCtrl=false;
        break;
    }
}

void DrawBaseCanvas::slotKeyPressEvent(QKeyEvent *e)
{
    cout<<endl<<"keyPress="<<e->key();
    switch(e->key())
    {
    case Qt::Key_Control:
        flagKeyCtrl=true;
        break;
    }
}

void DrawBaseCanvas::slotSetMarkerToPosition(double posX, double posY)
{
    posX-=realBegX;
    posY-=realBegY;
    
    canvasMarker->setCenterMarker(posX,posY);
}

void DrawBaseCanvas::setKolMarkFild(int n, bool allChanged) // задает число помеченных участков
{
    kolMarkFild=n;
    for(int j=kolMarkFild; j<maxKolMarkFild; j++)
    {
        lineMarkFild[j]->setSize(0,0);
        xMarkBegin[j]=xMarkEnd[j]=.0;
    }
    if (allChanged)
        canvas->setAllChanged();
}

MyRectCanvasSetka::MyRectCanvasSetka(Q3Canvas *canvas, QRect &r,
                                     double *Xmin, double *Xmax, double *Ymin, double *Ymax,
                                     long *iX, long *iY, long *nX, long *nY,
                                     long *Top, long *Left, long *Bottom, long *Right,
                                     long kRx, long kRy, long iR) :
        Q3CanvasRectangle((int)0, (int)0, (int)*nX, (int)*nY, canvas)
{
    error=false;
    otst=0;

    nx=nX; ny=nY; ix=iX; iy=iY; left=Qt::DockLeft; top=Qt::DockTop; right=Qt::DockRight; bottom=Qt::DockBottom;

    fullView=r;
    xmin=Xmin; xmax=Xmax; ymin=Ymin; ymax=Ymax;
    krx0=kRx; kry0=kRy; ir=iR;
    font=new QFont("times",8);
    fm=new QFontMetrics(*font);
    isw=fm->width('0');
    ihw=fm->height();
    maxSizeChar=(isw<ihw)? ihw : isw;
}

MyRectCanvasSetka::~MyRectCanvasSetka()
{
    delete font;
    delete fm;
}

void MyRectCanvasSetka::drawShape( QPainter & p )
/***************************************************************/
/*                                                             */
/*             Функция оформляет поле графика                  */
/*                                                             */
/* ix          - абцисса в пикселях нижнего левого угла        */
/*               поля графика;                                 */
/* iy          - ордината в пикселях;                          */
/* xmin        - минимальное значение абциссы;                 */
/* xmax        - максимальное значение абциссы;                */
/* ymin        - минимальное значение ординаты;                */
/* ymax        - миаксимальное значение ординаты;              */
/* nx          - ширина в пикселях поля графика по оси абцисс; */
/* ny          - ширина поля в пикселях по оси ординат;        */
/* ir          - 0 - ставятся только риски по осям,            */
/*               1 - чертится координатная сетка;              */
/* krx         - количество точек разметки по оси x;           */
/* kry         - количество точек разметки по оси y;           */
/* ipgr        - 0 - рисуются только координатные оси,         */
/*               1 - рисуется рамка вокруг графика;            */
/* isim        - максимальная ширина символов оцифровки;       */
/* left        - левая граница графика;                        */
/* top         - верхняя граница графика;                      */
/* right       - правая граница графика;                       */
/* bottom      - нижняя граница графика;                       */
/* infx        - наименование величины, откладываемой по оси x;*/
/* infy        - наименование величины, откладываемой по оси y;*/
/* otst        - отступ в пикселях от верхнего канта поля      */
/*               графика.                                      */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  char   *prx;
  char   *pry;
  char   rzm[12];
  QPoint point;
//==============================================================
  error=false;
  if (*xmax==*xmin || *ymax==*ymin)
  {
      error=true;
      return ;
  }

  p.setFont(*font);

  QPen pen;
  pen.setColor(colorText);
  pen.setWidth(1);
  p.setPen(pen);

  if (kporx && !keyx)
    {
      lx=(long)log10(fabs((double)kporx))+1;
      prx=new char[strlen(infx)+lx+5];
      sprintf(prx,"%s*10%+*d",infx,(int)lx,(int)kporx);
    }
  else
    {
      prx=new char[strlen(infx)+1];
      sprintf(prx,"%s",infx);
    }

  if (kpory && !keyy)
    {
      ly=(long)log10(fabs((double)kpory))+1;
      pry=new char[strlen(infy)+ly+5];
      sprintf(pry,"%s*10%+*d",infy,(int)ly,(int)kpory);
    }
  else
    {
      pry=new char[strlen(infy)+1];
      sprintf(pry,"%s",infy);
    }

  pen.setColor(colorText);
  pen.setWidth(1);
  p.setPen(pen);  
  double angle=-90.;
  ly=fm->width(pry);
  ly=*iy-*ny+ly+fm->ascent();
  lx=*ix-iy1+fm->ascent();
  p.translate(lx,ly);
  p.rotate(angle);
  if (flagText)
      p.drawText(0,0,pry);

  angle=90.;
  p.rotate(angle);
  p.translate(-lx,-ly);
  lx=fm->width(prx);
  lx=*ix+*nx-lx-isw-isw;
  ly=*iy+ix1-fm->ascent()/2;
  if (flagText)
      p.drawText(lx,ly,prx);

  pen.setColor(colorAxe);
  pen.setWidth(1);
  p.setPen(pen);  

  point.rx()=*ix;
  point.ry()=*iy;
  p.moveTo(point);
  point.rx()=*ix+*nx;
  p.lineTo(point); /* ось абцисс  */
  point.rx()=*ix;
  p.moveTo(point);
  point.ry()=*iy-*ny;
  p.lineTo(point); /* ось ординат */

  if (ipgr==1)
    {
      point.rx()=*ix;
      point.ry()=*iy-*ny;
      p.moveTo(point);
      point.rx()=*ix+*nx-1;
      p.lineTo(point);  /* окантовка графика */
      p.moveTo(point);
      point.rx()=*ix+*nx-1;
      point.ry()=*iy;
      p.lineTo(point);
    }

  /* РАЗМЕТКА ОСИ X */

  for(i=0; i<krx; i++)
    if (mdx==1 || mdx>1 && i%mdx==0)
      {
        z=zxmin+hzx*i;
        mz=(long)((*nx-otst)*(zxmin+hzx*i-xmin1)/hx);
        if (keyx)
          {
            z1=z;
            j=0;
            while(j<abs(kporx))
              {
                if (kporx>0)
                  z1*=10.;
                else
                  z1/=10.;
                j++;
              }
            sprintf(rzm,"%*.*f",(int)kx,(int)mx,z1);
          }
        else
          sprintf(rzm,"%*.*f",(int)kx,(int)mx,z);

        ly=*iy+ihw+4;
        lx=mz+*ix;

        if (lx+(kx*isw+1)/2<maxx)
          {
            for(k=0; *(rzm+k)==' '; k++); // удаление незначащих нулей
            pen.setColor(colorText);
            pen.setWidth(1);
            p.setPen(pen);
            if (flagText)
                p.drawText(lx-fm->width(rzm+k)/2,ly-fm->ascent()/2,(rzm+k));
          }
        if (ir==1)
          {
              pen.setColor(colorAxe);
              pen.setWidth(1);
              p.setPen(pen);              
              point.rx()=lx;
              point.ry()=*iy+2;
              p.moveTo(point);
              point.ry()=*iy;
              p.lineTo(point);
              pen.setColor(colorSetka);
              pen.setWidth(1);
              p.setPen(pen);              
              point.ry()-=1;
              p.moveTo(point);
              point.ry()=*iy-*ny+1;
              p.lineTo(point);
          }
        else
          {
              pen.setColor(colorAxe);
              pen.setWidth(1);
              p.setPen(pen);              
              point.rx()=lx;
              point.ry()=*iy+2;
              p.moveTo(point);
              point.ry()=*iy;
              p.lineTo(point);
          }
      }

  /* РАЗМЕТКА ОСИ Y */

  lx=*ix-iy1+ihw;

  for(i=0; i<kry; i++)
    if (mdy==1 || mdy>1 && i%mdy==0)
      {
        z=zymin+hzy*i;
        mz=(long)((*ny-otst)*(zymin+hzy*i-ymin1)/hy);
        if (keyy)
          {
            z1=z;
            j=0;
            while(j<abs(kpory))
              {
                if (kpory>0)
                  z1*=10.;
                else
                  z1/=10.;
                j++;
              }
            sprintf(rzm,"%*.*f",(int)ky,(int)my,z1);
          }
        else
          sprintf(rzm,"%*.*f",(int)ky,(int)my,z);
        ly=*iy-mz;

        if (ly-ihw>*top)
          {
            for(k=0; *(rzm+k)==' '; k++); // удалуние незначащих нулей
            pen.setColor(colorText);
            pen.setWidth(1);
            p.setPen(pen);
            if (flagText)
                p.drawText(lx,ly+fm->ascent()/2,rzm);
          }
        if (ir==1)
          {
              pen.setColor(colorAxe);
              pen.setWidth(1);
              p.setPen(pen);              
              point.rx()=*ix-2;
              point.ry()=ly;
              p.moveTo(point);
              point.rx()=*ix;
              p.lineTo(point);
              pen.setColor(colorSetka);
              pen.setWidth(1);
              p.setPen(pen);              
              point.rx()+=1;
              p.moveTo(point);
              point.rx()=*ix+*nx-2;
              p.lineTo(point);
          }
        else
          {
              pen.setColor(colorAxe);
              pen.setWidth(1);
              p.setPen(pen);              
              point.rx()=*ix-2;
              point.ry()=ly;
              p.moveTo(point);
              point.rx()=*ix;
              p.lineTo(point);
          }
      }

  *ny -=otst; /* отступили от верха на otst пикселей */
  *nx -=otst; /* отступили справа на otst пикселей   */

  delete[] prx;
  delete[] pry;
}

QSize MyRectCanvasSetka::grraz()
{
    QSize size(0,0);
    keyx=keyy=0;
    krx=krx0; kry=kry0;
    error=false;
      
    *right =fullView.right();
    *left  =fullView.left();
    *top   =fullView.top();
    *bottom=fullView.bottom();
    maxx=*right-*left;
    maxy=*bottom-*top;
    if (*xmax==*xmin || *ymax==*ymin)
    {
        error=true;
        return size;
    }
    nrx=*nx/krx;
    if (!nrx)
      {
          nrx=1;
          error=true;
          return size;
      }
    nry=*ny/kry;
    if (!nry)
     {
         nry=1;
         error=true;
         return size;
     }
    grstan(*xmin,*xmax,*nx,nrx,&zxmin,&hzx,&krx,&hx,&kporx,&xmin1,&kx);
  
    grstan(*ymin,*ymax,*ny,nry,&zymin,&hzy,&kry,&hy,&kpory,&ymin1,&ky);
  
    if (zxmin<.0)
      {
        kx++;
        mx=kx-3; // число цифр после запятой в оцифровке
      }
    else
      mx=kx-2;
    if (zymin<.0)
      {
        ky++;
        my=ky-3; // число цифр после запятой в оцифровке
      }
    else
      my=ky-2;

    if (kporx && abs(kporx)<4)
      { // число цифр после запятой в оцифровке изменяется
        keyx=1;
        if (kporx>0)
          if (mx<=kporx-1)
            {
              kx+=kporx-mx-1;
              mx=0;
            }
          else
            mx-=kporx;
        else
          {
            kx-=kporx;
            mx-=kporx;
          }
      }
    if (kpory && abs(kpory)<4)
      { // число цифр после запятой в оцифровке изменяется
        keyy=1;
        if (kpory>0)
          if (my<=kpory-1)
            {
              ky+=kpory-my-1;
              my=0;
            }
          else
            my-=kpory;
        else
          {
            ky-=kpory;
            my-=kpory;
          }
      }
    mdx=1;
  
    isim=*nx/((kx+1)*krx);
    while (isim<isw)
      {
        mdx++;
        isim=mdx**nx/((kx+1)*krx); /* ширина символов в пикселях */
      }
  
    mdy=1;
    isim=*ny/kry;
    while (isim<ihw)
     {
        mdy++;
        isim=mdy**ny/kry;
      }

    if (flagText)
    {
        iy1=ky*isw+ihw+2; /* отступ по x */
        ix1=2*ihw;      /* отступ по y */
    }
    else
    {
        iy1=2;
        ix1=8;
    }
  
    if (maxy-*iy<ix1) *iy=maxy-ix1;
    if (maxy-*iy+*ny>maxy) *ny=*iy;
    if (*ix<iy1) *ix=iy1;
    if (*ix+*nx>maxx) *nx=maxx-*ix;
  
    *left  =*ix-iy1;
    *top   =*iy-*ny;
    *right =*ix+*nx;
    *bottom=*iy+ix1;

    size.setWidth(iy1);
    size.setHeight(ix1);
    return size;
}

void MyRectCanvasSetka::grstan(double xmin, double xmax,
                               long nx, long kr,
                               double *zxmin, double *hzx,
                               long *kxr,
                               double *hx,
                               long *kporx,
                               double *xmin1,
                               long *kx)
/***************************************************************/
/*                                                             */
/* xmin   - минимальное значение;                              */
/* xmax   - максимальное значение;                             */
/* nx     - длина в пикселях;                                  */
/* kr     - расстояние в пиксилях между линиями разметки;      */
/* zxmin  - минимальная точка разметки с удаленным порядком;   */
/* hzx    - шаг между линиями разметки с удаленным порядком;   */
/* kxr    - число линий разметки;                              */
/* hx     - полная вариация значений с удаленным порядком;     */
/* kporx  - порядок нормировки;                                */
/* xmin1  - минимальное значение с удаленным порядком;         */
/* kx     - число знаков в оцифровке оси.                      */
/*                                                             */
/* VGG                                                         */
/***************************************************************/
{
  double xmin2,xmax2,par,xmax1;
  const double l10=log(10.);
  long    kx1,kx2,kxr0,kxr1,kdop;

  kx1=(xmax==.0)? 0 : (long)floor(log10(fabs(xmax)));
  kx2=(xmin==.0)? 0 : (long)floor(log10(fabs(xmin)));
  *kporx=(kx2>kx1)? kx2 : kx1;

  par=exp(-l10**kporx);
  *xmin1=xmin*par;
  xmax1=xmax*par;
  *kx=0;
  par=exp(l10*(1-*kx));
  xmin2=xmax2=.0;
  while (xmax2-xmin2<1.5*par)
    {
      (*kx)++;
      par=exp(l10*(1-*kx));
      xmin2=ceil(*xmin1/par)*par;
      xmax2=ceil(xmax1/par)*par;
    }
  *hzx=par;
  *kxr=(long)((xmax2-xmin2)/par-.5);
  kxr0=nx/kr;
  kxr1=*kxr;
  *zxmin=xmin2;
  kdop=1+(kxr0-2)/3;
  kxr0 +=kdop;
  if (*kxr>=kxr0)
    if (*xmin1*xmax1<.0)
      {
        khz2(2.,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
        if (kxr1>kxr0)
          khz2(2.,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
      }
    else
      {
        khz3(2.,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
        if (kxr1>kxr0)
          khz3(2.5,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
      }
  kxr0 -=2*kdop;
  if (*kxr<=kxr0)
    while (kxr1<kxr0)
      {
        khz1(.5,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
        if (kxr1<kxr0)
          khz1(.4,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
        if (kxr1<kxr0)
          khz3(2.5,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
      }
  *kxr=kxr1;
  if (fabs(*zxmin-*xmin1)<.1e-16) *zxmin +=*hzx;
  *kx=(long)(2.5-floor(log10(*hzx)));
  while (*zxmin-*xmin1>*hzx)
    {
      *zxmin -=*hzx;
      (*kxr)++;
    }
  if (xmax1-*zxmin-(*kxr-1)**hzx<=.0) (*kxr)--;
  *hx=xmax1-*xmin1;
  return;
} /* grstan */

void MyRectCanvasSetka::khz1(double r, double *hzx, double *zxm,
                             long *kxr1,
                             double xi1, double xi2, double xa1)
{
  *hzx *=r;
  *zxm=xi2+*hzx*ceil((xi1-xi2)/ *hzx);
  *kxr1=(long)(ceil((xa1-*zxm)/ *hzx)+.5);
  return;
} /* khz1 */

void MyRectCanvasSetka::khz2(double r, double *hzx, double *zxm,
                             long *kxr1,
                             double xi1, double xi2, double xa1)
{
  *hzx *=r;
  *zxm=xi2+fmod(fabs(xi2+1.),*hzx);
  *kxr1=(long)(ceil((xa1-*zxm)/ *hzx));
  return;
} /* khz2 */

void MyRectCanvasSetka::khz3(double r, double *hzx, double *zxm,
                             long *kxr1,
                             double xi1, double xi2, double xa1)
{
  *hzx *=r;
  *zxm=*hzx+xi2;
  *kxr1=(long)(ceil((xa1-*zxm)/ *hzx));
  return;
} /* khz3 */

MyCanvasMarker::MyCanvasMarker(Q3Canvas *canv, double xMin, double xMax, double yMin, double yMax,
                               long iX, long iY, long nX, long nY)
                : Q3CanvasLine(canv)
{
    canvas=canv;
    
    setColorMarker(QColor(0,0,0));
    
    setMinMax(xMin,xMax,yMin,yMax);

    setGeometry(iX,iY,nX,nY);

    X=Y=0;
}

void MyCanvasMarker::setCenterMarker(double x, double y)
{
    //cout<<endl<<"X="<<x<<" Y="<<y<<" xmin="<<xmin<<" xmax="<<xmax<<" ymin="<<ymin<<" ymax="<<ymax;
    if (x>xmin && x<xmax)
    {
        X=x;
        xV2=xV1=(long)((X-xmin)*nx/sizex)+ix;
    }
    else
        xV2=xV1=0;
    if (y>ymin && y<ymax)
    {
        Y=y;
        yH2=yH1=-(long)((Y-ymin)*ny/sizey)+iy;
    }
    else
        yH2=yH1=0;
    if (x>xmin && x<xmax && y>ymin && y<ymax)
    {
        setColorMarker(QColor(0,0,0));
        setPoints(0,0,xV2,yH2);
    }
    else
    {
        setColorMarker(QColor(255,0,0));
        setPoints(xH1,yV1,xH2,yV2);
    }

    canvas->setAllChanged();
}

void MyCanvasMarker::setMinMax(double xMin, double xMax, double yMin, double yMax)
{
    xmin=xMin;
    xmax=xMax;
    ymin=yMin;
    ymax=yMax;
    sizex=xmax-xmin;
    sizey=ymax-ymin;
}

void MyCanvasMarker::setGeometry(long iX, long iY, long nX, long nY)
{
    nx=nX;
    ny=nY;
    ix=iX;
    iy=iY;

    xH1=ix;
    xH2=ix+nx;
    
    yV1=iy;
    yV2=iy-ny;
}

void MyCanvasMarker::setColorMarker(QColor c)
{
    colorMarker=c;
}

void MyCanvasMarker::drawShape( QPainter & painter )
{

    QPen pen( colorMarker, Qt::DotLine);
    pen.setWidth(1);
    painter.setPen(pen);
    
    painter.drawLine(xH1,yH1,xH2,yH2);
    painter.drawLine(xV1,yV1,xV2,yV2);
}
