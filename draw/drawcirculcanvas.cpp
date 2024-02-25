#include "drawcirculcanvas.h"
#include <stdlib.h>
#ifndef _MATH_H
#include <math.h>
#endif
#include <iostream.h>

DrawCirculCanvas::DrawCirculCanvas(QCanvas *canvas, QWidget *parent,
                                   long k,
                                   FlagCirculBase Flag,
                                   long iRx, long iRy, long kRx, long kRy) :

            DrawCirculBaseCanvas(canvas, parent, Flag, iRx, iRy, kRx, kRy)
    
{
  initData(k);
}

void DrawCirculCanvas::initData(long k)
{
  long i;

  keyPoint=0;
  kol=k;
  kolDataX=kolDataY=0;
  x=new double* [kol];
  y=new double* [kol];
  n=new long[kol];
  colorLine =new QColor[kol];
  colorPoint=new QColor[kol];
  penWidth=new long[kol];

  diagramma=new MyCanvasPolygon*[kol];

  font=new QFont( "Arial", 8 );
  fm=new QFontMetrics(*font);
  isw=fm->width('0');
  ish=fm->height();
  maxSizeChar=((isw<ish)? ish : isw);
  QString str("");

  info=new QCanvasText(canvas);
  info->setX(maxSizeChar);
  info->setY(maxSizeChar);
  info->setZ(zText);
  info->setFont(*font);
  info->setText(str);
  info->show();
  infA  =new QCanvasText*[kol];
  infB  =new QCanvasText*[kol];
  infSig=new QCanvasText*[kol];

  for(i=0; i<kol; i++)
  {
      colorLine[i].setRgb(255,0,0);
      colorPoint[i].setRgb(255,0,0);
      penWidth[i]=1;

      diagramma[i]=new MyCanvasPolygon(canvas);
      diagramma[i]->setZ(zBase+(double)i);
      diagramma[i]->show();

      infA[i]=new QCanvasText(canvas);
      infA[i]->setText(str);
      infA[i]->setZ(zText);
      infA[i]->setFont(*font);
      infA[i]->show();

      infB[i]=new QCanvasText(canvas);
      infB[i]->setText(str);
      infB[i]->setZ(zText);
      infB[i]->setFont(*font);
      infB[i]->show();

      infSig[i]=new QCanvasText(canvas);
      infSig[i]->setText(str);
      infSig[i]->setZ(zText);
      infSig[i]->setFont(*font);
      infSig[i]->show();
}
  Dx=Dy=.0;
  xBeg=yBeg=.0;
}

DrawCirculCanvas::~DrawCirculCanvas()
{
  long i;

  delete[] x;
  delete[] y;
  delete[] n;
  delete[] colorLine;
  delete[] colorPoint;
  delete[] penWidth;

  for(i=0; i<kol; i++)
  {
      diagramma[i]->hide();
      delete diagramma[i];
      infA[i]->hide();
      delete infA[i];
      infB[i]->hide();
      delete infB[i];
      infSig[i]->hide();
      delete infSig[i];
  }
  delete diagramma;
  delete infA;
  delete infB;
  delete infSig;

  info->hide();
  delete info;

  delete font;
  delete fm;
}

void DrawCirculCanvas::setTextInfo(const QString &s)
{
    info->setText(s);
}

void DrawCirculCanvas::setTextInfA(const QString &s, int i)
{
    infA[i]->setText(s);
}

void DrawCirculCanvas::setTextInfB(const QString &s, int i)
{
    infB[i]->setText(s);
}

void DrawCirculCanvas::setTextInfSig(const QString &s, int i)
{
    infSig[i]->setText(s);
}

void DrawCirculCanvas::setXY(double *X, double *Y, long *N, long Size)
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

void DrawCirculCanvas::setY(double *Y, long N, long i)
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

void DrawCirculCanvas::setX(double *X, long N, long i)
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

bool DrawCirculCanvas::resetData()
{
    kolDataX=kolDataY=0;
    for(int i=0; i<kol; i++)
        n[i]=0;
    return true;
}

long DrawCirculCanvas::draw()
//
// Функция предназначена для отображения
// keyPoint - 1 - рисовать кружки, 0 -не рисовать
//
{
  double  r, sa, ca;
  const double DegToRad=acos(-1.)/180.;
  long    i, j, k, nPoint;
  int     X, Y, X1, Y1;

  if (/*!error || */kolDataY<kol || kolDataX<kol)
  {
      return 1;
  }

  for(i=0; i<kol; i++)
  {
     QBrush brush( colorLine[i], SolidPattern );
     diagramma[i]->setBrush(brush);
     QPen pen( colorLine[i], SolidPattern );
     diagramma[i]->setPen(pen);
     infA[i]  ->setColor(colorLine[i]);
     infB[i]  ->setColor(colorLine[i]);
     infSig[i]->setColor(colorLine[i]);
     infA[i]  ->setX(maxSizeChar);
     infA[i]  ->setY(ny-ish*(kol-i)-maxSizeChar);
     infB[i]  ->setX(nx-fm->width(infB[i]->text())-maxSizeChar);
     infB[i]  ->setY(ny-ish*(kol-i)-maxSizeChar);
     infSig[i]->setX(maxSizeChar);
     infSig[i]->setY(maxSizeChar+ish*(kol-i+1));

     nPoint=0;
     QPointArray array(n[i]+1);

     for(j=0; j<n[i]+1; j++)
     {
         k=(j==n[i])? 0 : j;
         r=*(y[i]+k) * (double)R;
         sa=sin(*(x[i]+k)*DegToRad);
         ca=cos(*(x[i]+k)*DegToRad);
         X=(long)((double)xCentr+r*sa);
         Y=(long)((double)yCentr-r*ca);
         if (nPoint && X==X1 && Y==Y1 && j<n[i])
             continue;
         X1=X; Y1=Y;
         array.setPoint(nPoint,X,Y);
         nPoint++;
     }
     array.resize(nPoint);
     diagramma[i]->setPoints(array);
  }

  canvas->setAllChanged(); // устанавливает все изменения в канвасе и требует их перерисовать
  //canvas->update();

  return 0;
}

void DrawCirculCanvas::upDate()
{
  update();
}

void DrawCirculCanvas::resizeEvent(QResizeEvent *event)
{
    DrawCirculBaseCanvas::resizeEvent(event);

    draw();
}
