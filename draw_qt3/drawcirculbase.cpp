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
#include "drawcirculbase.h"
#include <stdio.h>
#ifndef _MATH_H
#include <math.h>
#endif

DrawCirculBase::DrawCirculBase(QWidget *parent,
                               FlagCirculBase Flag,
                               long iRx, long iRy, long kRx, long kRy) :
                   QWidget(parent),
                   fildView(QRect(0,0,1,1)),
                   flag(Flag),
                   irx(iRx), iry(iRy), krx(kRx), kry(kRy)
{
  error=true;
  divot=NULL;
  beginAngl=endAngl=.0; // запрещенный сектор
  flagRangeX=flagRangeY=true; // диапазон изменений аргумента и функции определен
  colorAngle      =QColor(255,0,0);
  colorFon        =QColor(255,249,201);
  colorFonCircul  =QColor(250,250,250);
  colorText       =QColor(0,0,0);
  colorTextCircul =QColor(255,249,201);
  colorSetka      =QColor(200,200,200);
  colorRiski      =QColor(0,0,0);
  setBackgroundColor(colorFon);
}

DrawCirculBase::~DrawCirculBase()
{
  //dc.setViewport(fildView);
  //dc.setBackColor(dc.realColor(MGL_LIGHTGRAY));
  //dc.clearViewport();
  if (divot)
    delete[] divot;
}/* */
void DrawCirculBase::paintEvent(QPaintEvent *e)
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
    xCentr=nx/2;
    yCentr=ny/2;
    R=(xCentr<yCentr)? xCentr : yCentr;
    left=0;
    right=nx;
    top=0;
    bottom=ny;
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

long DrawCirculBase::grraz(QPainter &p)
/***************************************************************/
/*                                                             */
/*             Функция оформляет поле циклической диаграммы    */
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
  long   isw,ihw, maxSizeChar,
         i;
  QRect  fullView;
  QBrush brush( colorFonCircul, SolidPattern );
  QPen   pen=p.pen();
  QFont  font( "Arial", 8 );
  QPoint p0,p1,p2,p3;
  double cd,beta,ca,sa,ha,t1,t2,t3,t4,angle,da,db;
  const double RadToDeg=180./acos(-1.);
  char str[20];
//==============================================================
  p.setFont(font);
  QFontMetrics fm(font);

  isw=fm.width('0');
  ihw=fm.height();
  maxSizeChar=(isw<ihw)? ihw : isw;
  R-=maxSizeChar*1.5;
  
  rectCircul.setCoords(xCentr-R, yCentr-R, xCentr+R, yCentr+R);

  pen.setColor(colorText);
  pen.setWidth(1);
  p.setPen(pen);

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
  p.setBrush(brush);
  p.drawEllipse(rectCircul);

// запрещенный сектор всегда задается по часовой стрелки от begin до end
  long end  =(long)(endAngl*16.),
       begin=(long)(beginAngl*16.),
       kol  =begin-end;
  if (kol>0)
      kol-=5760; //360*16
  // kol по часовой стрелки -  отрицательно
  begin=1440-begin; // 90*16
  brush.setColor(colorAngle);
  p.setBrush(brush);
  p.drawPie(rectCircul,begin,kol);
//==============================================================

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
      isw=fm.width(str)+maxSizeChar/4;
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
        isw=fm.width(str);
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
  return 0      ;
} /* grraz */


