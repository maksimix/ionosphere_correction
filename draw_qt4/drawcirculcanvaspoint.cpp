#include "./drawcirculcanvaspoint.h"
#include <stdlib.h>
#ifndef _MATH_H
#include <math.h>
#endif
#include <iostream.h>

void MyCanvasEllipse::drawShape( QPainter & p )
{
    QCanvasEllipse::drawShape(p);
    p.setPen(pen());
    p.drawLine(X1,Y1,X2,Y2);
};

DrawCirculCanvasPoint::DrawCirculCanvasPoint(QCanvas *canvas, QWidget *parent,
                                             long k,
                                             FlagCirculBase Flag,
                                             long iRx, long iRy, long kRx, long kRy) :

            DrawCirculBaseCanvas(canvas, parent, Flag, iRx, iRy, kRx, kRy)
    
{
  initData(k);
}

void DrawCirculCanvasPoint::initData(long k)
{
  long i;

  keyPoint=8;
  kol=k;
  kolDataX=kolDataY=0;
  x=new double [kol];
  y=new double [kol];
  xBeg=new double [kol];
  yBeg=new double [kol];
  xEnd=new double [kol];
  yEnd=new double [kol];
  n=new long [kol];
  colorLine =new QColor[kol];
  colorPoint=new QColor[kol];
  penWidth=new long[kol];

  diagramma=new MyCanvasEllipse*[kol];

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
      n[i]=0;
      colorLine[i].setRgb(255,0,0);
      colorPoint[i].setRgb(255,0,0);
      penWidth[i]=1;

      diagramma[i]=new MyCanvasEllipse(canvas);
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
}

DrawCirculCanvasPoint::~DrawCirculCanvasPoint()
{
  long i;

  delete[] x;
  delete[] y;
  delete[] xBeg;
  delete[] yBeg;
  delete[] xEnd;
  delete[] yEnd;
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
  delete info;

  delete font;
  delete fm;
}

void DrawCirculCanvasPoint::setTextInfo(const QString &s)
{
    info->setText(s);
}

void DrawCirculCanvasPoint::setTextInfA(const QString &s, int i)
{
    infA[i]->setText(s);
}

void DrawCirculCanvasPoint::setTextInfB(const QString &s, int i)
{
    infB[i]->setText(s);
}

void DrawCirculCanvasPoint::setTextInfSig(const QString &s, int i)
{
    infSig[i]->setText(s);
}

void DrawCirculCanvasPoint::setXY(double *X, double *Y)
{
  for(long i=0; i<kol; i++)
  {
      n[i]=1;
      x[i]=X[i];
      y[i]=Y[i];
      if (!flagRangeX || !flagRangeY)
      {
          flagRangeX=flagRangeY=true; // диапазон изменений аргумента и функции определен
      }
  }
  kolDataX=kolDataY=kol;
}

void DrawCirculCanvasPoint::setY(double Y, long i)
{
  if (i<kol)
    {
      y[i]=Y;
      n[i]=1;
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

void DrawCirculCanvasPoint::setX(double X, long i)
{
  if (i<kol)
    {
      x[i]=X;
      n[i]=1;
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

bool DrawCirculCanvasPoint::resetData()
{
    kolDataX=kolDataY=0;
    for(int i=0; i<kol; i++)
    {
        n[i]=0;
        x[i]=y[i]=.0;
    }
    return true;
}

long DrawCirculCanvasPoint::draw()
//
// Функция предназначена для отображения
// keyPoint - 1 - рисовать кружки, 0 -не рисовать
//
{
  double  r, sa, ca, cb;
  const double DegToRad=acos(-1.)/180.;
  long    i, j, k, nPoint;
  int     X, Y, X1, Y1;

  if (kolDataY<kol || kolDataX<kol)
  {
      return 1;
  }

  for(i=0; i<kol; i++)
  {
     QBrush brush( colorLine[i], SolidPattern );
     diagramma[i]->setBrush(brush);
     QPen pen( colorLine[i], SolidPattern );
     pen.setWidth(penWidth[i]);
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

     r=(double)R;
     sa=sin(x[i]*DegToRad);
     ca=cos(x[i]*DegToRad);
     X1=xCentr;
     Y1=yCentr;
     if (y[i]<.0)
     {
         diagramma[i]->setX(X1);
         diagramma[i]->setY(Y1);
         diagramma[i]->setSize(0,0);
         diagramma[i]->setLine(X1,Y1,X1,Y1);
         continue;
     }
     X=(long)((double)xCentr+r*sa);
     Y=(long)((double)yCentr-r*ca);
     diagramma[i]->setLine(X1,Y1,X,Y);
     cb=cos(y[i]*DegToRad);
     X=(long)((double)xCentr+r*sa*cb);
     Y=(long)((double)yCentr-r*ca*cb);
     diagramma[i]->setX(X);
     diagramma[i]->setY(Y);
     diagramma[i]->setSize(keyPoint, keyPoint);
  }

  canvas->setAllChanged(); // устанавливает все изменения в канвасе и требует их перерисовать
  //canvas->update();

  return 0;
}

void DrawCirculCanvasPoint::upDate()
{
  update();
}

void DrawCirculCanvasPoint::resizeEvent(QResizeEvent *event)
{
    DrawCirculBaseCanvas::resizeEvent(event);

    draw();
}
