#include "drawpoligonmem_v.h"
#include <stdlib.h>
#include <iostream>
#include <qpixmap.h>

long ListDouble::countMem=0;

DrawPoligonMemV::DrawPoligonMemV(QWidget *parent,
                                 //char *infX, char *infY,
                                 const QString &infX, const QString &infY,
                                 double xMin, double xMax, double yMin, double yMax,
                                 long iR,long iPgr, long kRx, long kRy) :

                DrawBase(parent, infX, infY, xMin, xMax, yMin, yMax,
                         iR,iPgr, kRx, kRy)
{
    keyClear=false;
    keyColor=true;
    keyCircle=false;
    Dx=Dy=.0;
    xBeg=yBeg=.0;
    keyPainter=true;
    nX=0;
    minAmp=.0;
    normAmp=1.;
    setColorFon(QColor(255,255,255));
    setColorAxe(QColor(0,0,0));
    setColorSetka(QColor(150,150,150));
    setColorText(QColor(0,0,0));

    listDouble.setAutoDelete(TRUE);
}

DrawPoligonMemV::~DrawPoligonMemV()
{
}

void DrawPoligonMemV::reset()
{
    nX=0;
    keyCircle=false;
    std::cout<<std::endl<<"1 countMem="<<ListDouble::countMem<<flush;
    listDouble.clear();
    std::cout<<std::endl<<"2 countMem="<<ListDouble::countMem<<flush;
    keyPainter=true;
    repaint(false);
}

void DrawPoligonMemV::setY(double *Y, long N)
{
    if (keyCircle)
        listDouble.removeFirst();
    listDouble.append(new ListDouble(Y,nX,N));
    if (keyCircle)
        keyPainter=true;
    else
    {
        nX++;
        if (nX)
            keyPainter=false;  // только одну точку перерисовывать
    }
    repaint(false);
}

void DrawPoligonMemV::paintEvent(QPaintEvent *e)
{
    if (keyPainter || keyCircle) // если изменилась только одна точка, перерисовывать все поле нет необходимости
    {
        DrawBase::paintEvent(e);
        printf("\nkeyCircle=%d",(int)keyCircle);
    }
    QPainter p;
    p.begin(this);
    //p.setClipRect(e->rect());
    draw(p,keyClear);
    p.end();
}


long DrawPoligonMemV::draw(QPainter &p,
                          bool keyClear)
//
// Функция предназначена для отображения
//
{
  QPoint  point;
  QRect   rFill;
  QPen    pen=p.pen();
  long    i,j,k;
  QColor  colorPoint;
  ListDouble *iList=listDouble.getFirst();
  double *iY;

  printf("\n############## draw");

  if (!error || !iList)
      return 1;

  if (keyClear)
  {
      QBrush brush( colorFon, SolidPattern );
      p.fillRect(rClear,brush);
  }

  sizex=xmax-xmin;
  sizey=ymax-ymin;

  if (keyPainter)
  {
      iList=listDouble.first();
      k=0;
  }
  else
  {
      iList=listDouble.last();
      k=nX-1;
  }

  for(; iList && k<nX; k++,iList=listDouble.next())
  {
      if (iList==listDouble.getFirst())
          y0=-(yBeg+Dy*k-ymin)*ny/sizey+iy;

      y1=-(yBeg+Dy*(iList->getNX()+1)-ymin)*ny/sizey+iy;
      printf("\ny0=%d  y1=%d  %d  %d",y0,y1,iy,iy-ny);
      if (y1<iy-ny || y0<iy-ny)
      {
          keyCircle=true;
          printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      }

      if (y1>iy && y0>iy || y1<iy-ny && y0<iy-ny)
      {
          y0=y1;
          continue;
      }
      else
      {
          if (y1>=iy) y1=iy;
          if (y0>=iy) y0=iy;
          if (y1<=iy-ny) y1=iy-ny+1;
          if (y0<=iy-ny) y0=iy-ny+1;
      }
      if (y0==y1)
      {
          continue;
      }
      x0=(xBeg-xmin)*nx/sizex+ix;
      p.setRasterOp(Qt::OrNotROP);

      QPixmap pix(nx-1,y0-y1);
      QPainter pp(&pix);

      double amp, ampTemp;
      amp=-1.;
      //printf("\niList->getN()=%d",iList->getN());
      for(j=0, iY=iList->getY(); j<iList->getN(); j++, iY++)
      {
          x1=(xBeg+Dx*j-xmin)*nx/sizex+ix;
          //printf("\nx0=%d  x1=%d",x0,x1);
          if (x1<ix && x0<ix || x1>ix+nx && x0>ix+nx)
              x0=x1;
          else
          {
              ampTemp=(*iY-minAmp)/normAmp;
              if (ampTemp<.0)
                  ampTemp=.0;
              else
                  if (ampTemp>1.)
                      ampTemp=1.;
              if (x1<ix) x1=ix;
              if (x0<ix) x0=ix;
              if (x1>=ix+nx) x1=ix+nx-1;
              if (x0>=ix+nx) x0=ix+nx-1;
    
              if (x0!=x1)
              {
                  if (amp<.0)
                      amp=ampTemp;
                  if (keyColor)
                  {
                    color=510*amp;
                    if (color<0)
                      color=0;
                    if (color>510)
                      color=510;
                    color&=0x1ff;
                    if (color>255)
                    {
                        colorPoint=QColor(color-255,510-color,0);
                    }
                    else
                    {
                        colorPoint=QColor(0,color,255-color);
                    }
                  }
                  else
                  {
                    color=255*amp;
                    if (color<0)
                      color=0;
                    if (color>255)
                      color=255;
                    color&=0x1ff;
                    colorPoint=QColor(255-color,255-color,255-color);
                  }

                  if (y0>y1)
                      rFill.setCoords(x0-ix,y0-y0,x1-ix,y0-y1);
                  else
                      rFill.setCoords(x0-ix,y0-y0,x1-ix,y1-y0);
                  pp.setBrush(colorPoint);
                  //pen.setCapStyle(Qt::SquareCap);
                  //pp.setPen(pen);
                  pp.setPen(colorPoint);
                  if (x0>=ix && x1<ix+nx && y1<=iy && y0>iy-ny)
                  {
                      pp.drawRect(rFill);
                      pp.fillRect(rFill,colorPoint);
                  }
                  x0=x1;
                  amp=-1.;
              }
              else
                  if (amp<ampTemp)
                      amp=ampTemp;
          }
      }
      p.drawPixmap((int)ix,(int)y1,pix);
      y0=y1;
  }
  
  p.setRasterOp(Qt::CopyROP);
  if (!keyColor)
      grraz(p);
  keyPainter=true;
  return 0;
}

void DrawPoligonMemV::upDate()
{
  //update(rClear);
  update();
}
