#include "drawcirculcanvasspace.h"
#include <stdlib.h>
#ifndef _MATH_H
#include <math.h>
#endif
#include <iostream.h>

DrawCirculCanvasSpace::DrawCirculCanvasSpace(QCanvas *canvas, QWidget *parent,
                                             long l, long m,
                                             FlagCirculBase Flag,
                                             long iRx, long iRy, long kRx, long kRy) :

            DrawCirculBaseCanvas(canvas, parent, Flag, iRx, iRy, kRx, kRy)
    
{
    L=l;
    M=m;
    kol=(L+1)*M;
    setColorFonCircul(QColor(0,0,255));
    initData();
}

void DrawCirculCanvasSpace::initData()
{
  long i;

  resetData();

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

  for(i=0; i<kol; i++)
  {
      diagramma[i]=new MyCanvasPolygon(canvas);
      QBrush brush(QColor(0,0,0));
      diagramma[i]->setBrush(brush);

      diagramma[i]->setZ(zBase);
      diagramma[i]->show();
  }

  infA=new QCanvasText(canvas);
  infA->setText(str);
  infA->setZ(zText);
  infA->setFont(*font);
  infA->show();

  infB=new QCanvasText(canvas);
  infB->setText(str);
  infB->setZ(zText);
  infB->setFont(*font);
  infB->show();

  infSig=new QCanvasText(canvas);
  infSig->setText(str);
  infSig->setZ(zText);
  infSig->setFont(*font);
  infSig->show();
}

DrawCirculCanvasSpace::~DrawCirculCanvasSpace()
{
  long i;

  for(i=0; i<kol; i++)
  {
      diagramma[i]->hide();
      delete diagramma[i];
  }
  delete diagramma;

  infA->hide();
  delete infA;
  infB->hide();
  delete infB;
  infSig->hide();
  delete infSig;
  info->hide();
  delete info;

  delete font;
  delete fm;
}

void DrawCirculCanvasSpace::setTextInfo(const QString &s)
{
    info->setText(s);
}

void DrawCirculCanvasSpace::setTextInfA(const QString &s)
{
    infA->setText(s);
    infA->setX(maxSizeChar);
    infA->setY(ny-ish-maxSizeChar);
}

void DrawCirculCanvasSpace::setTextInfB(const QString &s)
{
    infB->setText(s);
    infB->setX(nx-fm->width(infB->text())-maxSizeChar);
    infB->setY(ny-ish-maxSizeChar);
}

void DrawCirculCanvasSpace::setTextInfSig(const QString &s)
{
    infSig->setText(s);
    infSig->setX(maxSizeChar);
    infSig->setY(maxSizeChar+ish*2);
}

bool DrawCirculCanvasSpace::resetData()
{
    Y=0;
    Z=0;
    Dx=xBeg=.0;
    return true;
}

long DrawCirculCanvasSpace::draw()
//
// Функция предназначена для отображения
//
{
  double ca,sa;
  long   l,m,k,color=0;
  double cb,t1,ha,t3,t4,t5,t6,xPoint[4],yPoint[4];
  QColor canvasColor;

  if (!Y && !Z)
      return 1;
  // по углу места, потом по азимуту
  t1=1.;
  for(l=0; l<L+1; l++,t1=cb)
  {
      if (l==L)
        cb=.0;
      else
        cb=cos(Y[l]);
      ca=cos(xBeg);
      sa=sin(xBeg);
      t3=cos(xBeg-Dx);
      t4=sin(xBeg-Dx);
      ha=2.*cos(Dx);
      for(m=0; m<M; m++)
      {
          k=M*l+m;
          QPointArray array(4);

          t5=ha*ca-t3;
          t6=ha*sa-t4;
          t3=ca;
          t4=sa;
          ca=t5;
          sa=t6;

          if (l==L)
              color=0;
          else
              color=(long)(510**(*(Z+l)+m));
          color&=0x1ff;
          
          if (color>255)
          {
              canvasColor=QColor(color-255,510-color,0);
          }
          else
          {
              canvasColor=QColor(0,color,255-color);
          }

          QBrush brush(canvasColor);
          diagramma[k]->setBrush(brush);
          if (!m)
          {
              xPoint[0]=xCentr+R*t1*t4;
              yPoint[0]=yCentr-R*t1*t3;
              xPoint[3]=xCentr+R*cb*t4;
              yPoint[3]=yCentr-R*cb*t3;
          }
          else
          {
              xPoint[0]=xPoint[1];
              yPoint[0]=yPoint[1];
              xPoint[3]=xPoint[2];
              yPoint[3]=yPoint[2];
          }
          xPoint[1]=xCentr+R*t1*sa+.5;
          yPoint[1]=yCentr-R*t1*ca+.5;
          xPoint[2]=xCentr+R*cb*sa+.5;
          yPoint[2]=yCentr-R*cb*ca+.5;
          for(int i=0; i<4; i++)
              array.setPoint(i, (int)((xPoint[i]<xCentr)? xPoint[i]+.5 : xPoint[i]-.5), (int)((yPoint[i]<yCentr)? yPoint[i]+.5 : yPoint[i]-.5));
          diagramma[k]->setPoints(array);
      }
  }

  canvas->setAllChanged(); // устанавливает все изменения в канвасе и требует их перерисовать
  //canvas->update();

  return 0;
}

void DrawCirculCanvasSpace::resizeEvent(QResizeEvent *event)
{
    DrawCirculBaseCanvas::resizeEvent(event);

    infA->setX(maxSizeChar);
    infA->setY(ny-ish-maxSizeChar);
    infB->setX(nx-fm->width(infB->text())-maxSizeChar);
    infB->setY(ny-ish-maxSizeChar);
    infSig->setX(maxSizeChar);
    infSig->setY(maxSizeChar+ish*2);

    draw();
}
