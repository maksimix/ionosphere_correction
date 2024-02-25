#include "drawpoligonmem.h"
#include <stdlib.h>
#include <iostream>
#include <qpixmap.h>

//long ListDouble::countMem=0;

DrawPoligonMem::DrawPoligonMem(QWidget *parent,
           char *infX, char *infY,
           double xMin, double xMax, double yMin, double yMax,
           long iR,long iPgr, long kRx, long kRy) :

           DrawBase(parent, infX, infY, xMin, xMax, yMin, yMax,
                   iR,iPgr, kRx, kRy)
{
    keyClear=false;
    keyColor=true;
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

DrawPoligonMem::~DrawPoligonMem()
{
}

void DrawPoligonMem::reset()
{
    nX=0;
    //std::cout<<std::endl<<"1 countMem="<<ListDouble::countMem<<flush;
    listDouble.clear();
    //std::cout<<std::endl<<"2 countMem="<<ListDouble::countMem<<flush;
    keyPainter=true;
    repaint(false);
}

void DrawPoligonMem::setY(double *Y, long N)
{
    listDouble.append(new ListDouble(Y,nX,N));
    nX++;
    if (nX)
        keyPainter=false;  // только одну точку перерисовывать
    repaint(false);
}

void DrawPoligonMem::paintEvent(QPaintEvent *e)
{
    if (keyPainter) // если изменилась только одна точка, перерисовывать все поле нет необходимости
        DrawBase::paintEvent(e);
    QPainter p;
    p.begin(this);
    //p.setClipRect(e->rect());
    draw(p,keyClear);
    p.end();
}


long DrawPoligonMem::draw(QPainter &p,
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
          x0=(xBeg+Dx*k-xmin)*nx/sizex+ix;

      x1=(xBeg+Dx*(iList->getNX()+1)-xmin)*nx/sizex+ix;

      if (x1<ix && x0<ix || x1>ix+nx && x0>ix+nx)
      {
          x0=x1;
          continue;
      }
      else
      {
          if (x1<ix) x1=ix;
          if (x0<ix) x0=ix;
          if (x1>=ix+nx) x1=ix+nx-1;
          if (x0>=ix+nx) x0=ix+nx-1;
      }
      if (x0==x1)
      {
          continue;
      }
      y0=-(yBeg-ymin)*ny/sizey+iy;
      p.setRasterOp(Qt::OrNotROP);

      QPixmap pix(x1-x0,ny);
      QPainter pp(&pix);

      double amp, ampTemp;
      amp=-1.;
      for(j=0, iY=iList->getY(); j<iList->getN(); j++, iY++)
      {
          y1=-(yBeg+Dy*j-ymin)*ny/sizey+iy;
          if (y1>iy && y0>iy || y1<iy-ny && y0<iy-ny)
              y0=y1;
          else
          {
              ampTemp=(*iY-minAmp)/normAmp;
              if (ampTemp<.0)
                  ampTemp=.0;
              else
                  if (ampTemp>1.)
                      ampTemp=1.;
              if (y1>=iy) y1=iy;
              if (y0>=iy) y0=iy;
              if (y1<=iy-ny) y1=iy-ny+1;
              if (y0<=iy-ny) y0=iy-ny+1;
    
              if (y0!=y1)
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
                      rFill.setCoords(x0-x0,y1-iy+ny,x1-x0,y0-iy+ny);
                  else
                      rFill.setCoords(x0-x0,y0-iy+ny,x1-x0,y1-iy+ny);
                  pp.setBrush(colorPoint);
                  //pen.setCapStyle(Qt::SquareCap);
                  //pp.setPen(pen);
                  pp.setPen(colorPoint);
                  if (x0>=ix && x1<ix+nx && y1<=iy && y0>iy-ny)
                  {
                      pp.drawRect(rFill);
                      pp.fillRect(rFill,colorPoint);
                  }
                  y0=y1;
                  amp=-1.;
              }
              else
                  if (amp<ampTemp)
                      amp=ampTemp;
          }
      }
      p.drawPixmap((int)x0,(int)(iy-ny),pix);
      x0=x1;
  }
  
  p.setRasterOp(Qt::CopyROP);
  if (!keyColor)
      grraz(p);
  keyPainter=true;
  return 0;
}

void DrawPoligonMem::upDate()
{
  //update(rClear);
  update();
}
