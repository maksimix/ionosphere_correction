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
#include "drawcirculbasecanvas.h"
#include <stdio.h>
#ifndef _MATH_H
#include <math.h>
#endif
#include <iostream.h>

void MyCanvasPolygon::drawShape( QPainter & p )
{
    //setWinding(true);
    QCanvasPolygon::drawShape(p);
    //p.drawPolyline(points());
    //p.drawPolygon(points());
}

DrawCirculBaseCanvas::DrawCirculBaseCanvas(QCanvas *viewing, QWidget *parent,
                                           FlagCirculBase Flag,
                                           long iRx, long iRy, long kRx, long kRy) :
                      QCanvasView(viewing, parent),
                      fildView(QRect(0,0,1,1)),
                      flag(Flag),
                      irx(iRx), iry(iRy), krx(kRx), kry(kRy)
{
  canvas=viewing;
  widget=parent;
    
  error=true;
  flagGist=false;
  gistX=gistY=0;

  beginAngl=endAngl=.0; // запрещенный сектор
  flagRangeX=flagRangeY=true; // диапазон изменений аргумента и функции определен
  colorAngle      =QColor(170,0,0);
  colorFon        =QColor(255,249,201);
  colorFonCircul  =QColor(0,0,0);
  colorText       =QColor(0,0,0);
  colorTextCircul =QColor(255,249,201);
  colorSetka      =QColor(200,200,200);
  colorRiski      =QColor(0,0,0);
  colorGist       =QColor(0, 0, 255);
  setBackgroundColor(colorFon);

  // расположение плоскостей круговой диаграммы
  zFild=1.;    // фон круговой диаграммы
  zText=2.;
  zGist=6.;
  zSetka=256.;  // сетка осей круговой диаграммы
  zAngl=5.;    // плоскость зарисовки запрета по азимуту
  zBase=10.;   // начало плоскостей прорисовки круговых диаграмм
  // отменить скроллинг канваса
  setHScrollBarMode (AlwaysOff);
  setVScrollBarMode (AlwaysOff);

  canvas->setBackgroundColor(colorFon);

  resizeMyCanvas();

  canvasSetka=new MyCanvasSetka(canvas, R, Flag, krx, kry, irx, iry);
  canvasSetka->setColorText(colorText);
  canvasSetka->setColorSetka(colorSetka);
  canvasSetka->setColorText(colorRiski);
  canvasSetka->setColorTextCircul(colorTextCircul);
  canvasSetka->setZ(zSetka);
  canvasSetka->show();

  fildDiagramm=new QCanvasEllipse(canvas);
  fildDiagramm->setZ(zFild);
  fildDiagramm->show();

  canvasSektor=new MyCanvasSektor(canvas, R);
  canvasSektor->setColorAngl(colorAngle);
  canvasSektor->setZ(zAngl);
  canvasSektor->setBeginAngl(beginAngl);
  canvasSektor->setEndAngl(endAngl);
  canvasSektor->show();

  canvasGistX=canvasGistY=0;

  if (grraz())
    error=false;   // ошибка
  else
    error=true;
}

DrawCirculBaseCanvas::~DrawCirculBaseCanvas()
{
    fildDiagramm->hide();
    delete fildDiagramm;
    canvasSetka->hide();
    delete canvasSetka;
    canvasSektor->hide();
    delete canvasSektor;
    if (canvasGistX)
    {
        for(int i=0; i<nxGist; i++)
            delete canvasGistX[i];
        delete[] canvasGistX;
    }
    if (canvasGistY)
    {
        for(int i=0; i<nyGist; i++)
            delete canvasGistY[i];
        delete[] canvasGistY;
    }
    if (flagGist)
    {
        gistX=gistY=0;
    }
}

long DrawCirculBaseCanvas::grraz()
/***************************************************************/
/*                                                             */
/*             Функция оформляет поле циклической диаграммы    */
/*                                                             */
/* ix          - абцисса в пикселях нижнего левого угла        */
/*               поля графика;                                 */
/* iy          - ордината в пикселях;                          */
/* nx          - ширина в пикселях поля графика по оси абцисс; */
/* ny          - ширина поля в пикселях по оси ординат;        */
/* irx, iry    - 0 - ставятся только риски по осям,            */
/*               1 - чертится координатная сетка;              */
/* krx         - количество точек разметки по оси x;           */
/* kry         - количество точек разметки по оси y;           */
/* left        - левая граница графика;                        */
/* top         - верхняя граница графика;                      */
/* right       - правая граница графика;                       */
/* bottom      - нижняя граница графика;                       */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  QBrush brush(colorFonCircul);
    
  canvasSetka->setX((double)xCentr);
  canvasSetka->setY((double)yCentr);
  canvasSetka->setSize(2*R, 2*R);

  R=canvasSetka->getR();
  int toR=R<<1;
  fildDiagramm->setSize(toR, toR);
  fildDiagramm->setBrush(brush);
  fildDiagramm->setX((double)xCentr);
  fildDiagramm->setY((double)yCentr);

  canvasSektor->setX((double)xCentr);
  canvasSektor->setY((double)yCentr);
  canvasSektor->setSize(2*R, 2*R);

  return 0      ;
} /* grraz */


void DrawCirculBaseCanvas::resizeEvent(QResizeEvent *event)
{
    QCanvasView::resizeEvent(event);

    resizeMyCanvas();
    
    grraz();

    if (flagGist && gistX && gistY)
    {
        drawGistX();
        drawGistY();
    }
}

inline void DrawCirculBaseCanvas::resizeMyCanvas() // подстроить канвас под размер виджета
{
       fildView=widget->geometry ();
       ny=fildView.height()-frameWidth();
       nx=fildView.width()-frameWidth();
       resize(nx, ny);
       canvas->resize(nx, ny);
   
       ix=0;
       iy=canvas->height();
       nx=canvas->width();
       ny=iy;
       xCentr=nx/2;
       yCentr=ny/2;
       R=((xCentr<yCentr)? xCentr : yCentr);
       left=0;
       right=nx;
       top=0;
       bottom=ny;
}

MyCanvasSetka::MyCanvasSetka(QCanvas *canvas, int r, FlagCirculBase Flag,
                             long kRx, long kRy, long iRx, long iRy) :
        QCanvasEllipse(r*2,r*2,canvas)
{
    flag=Flag;
    krx=kRx; kry=kRy; irx=iRx; iry=iRy;
    R=(long)r;
    xCentr=(long)x();
    yCentr=(long)y();
    font=new QFont( "Arial", 8 );
    fm=new QFontMetrics(*font);
    isw=fm->width('0');
    ihw=fm->height();
    maxSizeChar=(isw<ihw)? ihw : isw;
}

MyCanvasSetka::~MyCanvasSetka()
{
    delete font;
    delete fm;
}

void MyCanvasSetka::drawShape( QPainter & p )
{
  QPen pen;
  QBrush brush;
  QPoint p0, p1, p2, p3;
  //QFont  font("times",10);
  double cd,beta,ca,sa,ha,t1,t2,t3,t4,angle,da,db;
  const double RadToDeg=180./acos(-1.);
  char str[20];
  long i;

  p.setFont(*font);

  xCentr=(long)x();
  yCentr=(long)y();
  
  while(360%krx) // реальное число разбиений оси центральных углов
      krx++;
  if (krx>=360)
      krx=14;
  da=2.*acos(-1.)/krx;

  while(90%kry)  // реальное число разбиений радиальной оси по вертикальному углу
      kry++;
  if (kry>=90)
      kry=6;
  db=.5*acos(-1.)/kry;

  ca=1.;
  sa=.0;
  t1=cos(da);
  t2=-sin(da);
  ha=2.*t1;
  
  p0.rx()=xCentr;
  p0.ry()=yCentr;

  for(i=0; i<krx; i++)
  {
      if (irx)
      {
          p1=p0;
          p2.rx()=(long)((double)p0.x()+(double)R*sa);
          p2.ry()=(long)((double)p0.y()-(double)R*ca);
          
      }
      else
      {
        p2.rx()=p1.rx()=(long)((double)p0.x()+(double)R*sa);
        p2.ry()=p1.ry()=(long)((double)p0.y()-(double)R*ca);
      }
      p3.rx()=(long)((double)p0.x()+(double)(R+maxSizeChar/4)*sa);
      p3.ry()=(long)((double)p0.y()-(double)(R+maxSizeChar/4)*ca);
      angle=da*(double)i*RadToDeg;
      sprintf(str,"%3.0f",da*(double)i*RadToDeg);
      isw=fm->width(str)+maxSizeChar/4;
      pen.setColor(colorSetka);
      pen.setWidth(1);
      p.setPen(pen);

      if (irx)
        p.drawLine(p1,p2);
      pen.setColor(colorRiski);
      pen.setWidth(1);
      p.setPen(pen);
      p.drawLine(p2,p3);
      
      p3.rx()+=(long)(.5*(double)isw*sa);
      p3.ry()-=(long)(.5*(double)isw*ca);
      pen.setColor(colorText);
      pen.setWidth(1);
      p.setPen(pen);

      p.drawText(p3.x()-isw/2, p3.y()-ihw/2, isw, ihw, AlignCenter, str);
      
      t3=ha*ca-t1;
      t4=ha*sa-t2;
      t1=ca;
      t2=sa;
      ca=t3;
      sa=t4;
    }
  if (iry)
  {
    brush.setStyle(NoBrush);
    p.setBrush(brush);
    for(i=kry-1; i>0; i--)
    {
        QRect rab;
        beta=db*i;
        switch(flag)
        {
        case fcbCos:
            cd=cos(beta);
            beta*=RadToDeg;
            break;
        case fcbLin:
            beta*=RadToDeg;
            cd=1.-beta/90.;
            break;
        }
        sprintf(str,"%2.0f",beta);
        isw=fm->width(str);
        rab.setCoords(xCentr-R*cd, yCentr-R*cd, xCentr+R*cd, yCentr+R*cd);
        pen.setColor(colorSetka);
        pen.setWidth(1);
        p.setPen(pen);

        p.drawEllipse(rab);
            
        pen.setColor(colorTextCircul);
        pen.setWidth(1);
        p.setPen(pen);

        p.drawText(rab.right()-isw/2, yCentr, isw, ihw, AlignCenter, str);
    }
  }
}

void DrawCirculBaseCanvas::setDXYGist(double dx, double dy)
{
    dxGist=dx;
    dyGist=dy;
    nxGist=360./dxGist;
    nyGist=90./dyGist;

    if (nxGist<=0 || nyGist<=0)
    {
        flagGist=false;
        return;
    }

    flagGist=true; // будет отображаться гистограмма;
    canvasGistX=new MyCanvasPolygon*[nxGist];
    canvasGistY=new MyCanvasPolygon*[nyGist];
    QBrush brush( colorGist, SolidPattern );
    for(int i=0; i<nxGist; i++)
    {
        canvasGistX[i]= new MyCanvasPolygon(canvas);
        canvasGistX[i]->setBrush(brush);
        canvasGistX[i]->setZ(zGist);
        canvasGistX[i]->show();
    }
    for(int i=0; i<nyGist; i++)
    {
        canvasGistY[i]= new MyCanvasPolygon(canvas);
        canvasGistY[i]->setBrush(brush);
        canvasGistY[i]->setZ(zGist);
        canvasGistY[i]->show();
    }
}

void DrawCirculBaseCanvas::setGistX(long *x)
//
// Функция предназначена для отображения гистограммы пеленгов на круговой диаграмме
//
{
    gistX=x;
    if (gistX)
        drawGistX();
    else
    {
        for(int i=0; i<nxGist; i++)
        {
            QPointArray array;
            array.resize(0);
            canvasGistX[i]->setPoints(array);
        }
    }
}

void DrawCirculBaseCanvas::setGistY(long *y)
//
// Функция предназначена для отображения гистограммы углов места на круговой диаграмме
//
{
    gistY=y;
    if (gistY)
        drawGistY();
    else
    {
        for(int i=0; i<nyGist; i++)
        {
            QPointArray array;
            array.resize(0);
            canvasGistY[i]->setPoints(array);
        }
    }
}

void DrawCirculBaseCanvas::drawGistX()
{
  long norm,i;
  double rab,sa,ca,ha,t1,t2,t3,t4;
  const double pi4=.25*acos(-1.);
  const double RAD=acos(-1.)/180.;
  int X0,Y0,X1,Y1,X2,Y2,X3,Y3;

  norm=0;
  for(i=0; i<nxGist; i++)
    if (norm<gistX[i])
      norm=gistX[i];
  if (!norm)
    norm++;

  //cout<<endl<<"norm="<<norm;
  ca=1.;
  sa=.0;
  t1=cos(dxGist*RAD);
  t2=-sin(dxGist*RAD);
  ha=2.*t1;

  for(i=0; i<nxGist; i++)
  {
      QPointArray array(4);

      rab=cos(pi4*gistX[i]/norm);
      X0=xCentr+R*sa;
      Y0=yCentr-R*ca;
      X1=xCentr+R*rab*sa;
      Y1=yCentr-R*rab*ca;
      t3=ha*ca-t1;
      t4=ha*sa-t2;
      t1=ca;
      t2=sa;
      ca=t3;
      sa=t4;
      X2=xCentr+R*rab*sa;
      Y2=yCentr-R*rab*ca;
      X3=xCentr+R*sa;
      Y3=yCentr-R*ca;
      array.setPoint(0,X0,Y0);
      array.setPoint(1,X1,Y1);
      array.setPoint(2,X2,Y2);
      array.setPoint(3,X3,Y3);
      canvasGistX[i]->setPoints(array);
  }
}

void DrawCirculBaseCanvas::drawGistY()
{
  long norm,i;
  double rab,sb,cb,hb,t1,t2,t3,t4;
  const double pi4=.15*acos(-1.);     // было .18
  const double RAD=acos(-1.)/180.;

  norm=0;
  for(i=0; i<nyGist; i++)
    if (norm<gistY[i])
      norm=gistY[i];
  if (!norm)
    norm++;

  cb=1.0;
  sb=.0;
  t1=cos(dyGist*RAD);
  t2=-sin(dyGist*RAD);
  hb=2.*t1;
  for(i=0; i<nyGist; i++)
  {
      QPointArray array(4);

      rab=2.-cos(pi4*gistY[i]/norm);
      array.setPoint(0,xCentr+R*sb,yCentr-R*cb);
      array.setPoint(1,xCentr+R*rab*sb,yCentr-R*rab*cb);
      t3=hb*cb-t1;
      t4=hb*sb-t2;
      t1=cb;
      t2=sb;
      cb=t3;
      sb=t4;
      array.setPoint(2,xCentr+R*rab*sb,yCentr-R*rab*cb);
      array.setPoint(3,xCentr+R*sb,yCentr-R*cb);
      canvasGistY[i]->setPoints(array);
  }
}
