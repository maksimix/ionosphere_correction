#include "drawcanvas.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
//Added by qt3to4:
#include <Q3PointArray>
#include <QResizeEvent>
#include <QMouseEvent>

using namespace std;

DrawCanvas::DrawCanvas(Q3Canvas *canvas, QWidget *parent,
                       long k,
                       char *infX, char *infY,
                       double xMin, double xMax, double yMin, double yMax,
                       long iR,long iPgr, long kRx, long kRy) :
            
                       DrawBaseCanvas(canvas, parent, infX, infY, xMin, xMax, yMin, yMax,
                               iR, iPgr, kRx, kRy)
{
    initData(k);
}

DrawCanvas::DrawCanvas(Q3Canvas *canvas, QWidget *parent,
                       long k,
                       char *infX, char *infY,
                       long iR,long iPgr, long kRx, long kRy) :
            
                       DrawBaseCanvas(canvas, parent, infX, infY, iR, iPgr, kRx, kRy)
{
    initData(k);
}

void DrawCanvas::initData(long k)
{
  int i; 
  keyClear=false;
  keyPoint=0;
  kol=k;
  kolDataX=kolDataY=0;

  xBegin=new long[kol];
  yBegin=new long[kol];
  xEnd  =new long[kol];
  yEnd  =new long[kol];
  for(i=0; i<kol; i++)
      xBegin[i]=yBegin[i]=xEnd[i]=yEnd[i]=0;

  QPen pen;
  pen.setWidth(3);
  for(i=0; i<KolMetka; i++)
  {
      colorLineMetka[i]=colorFon;
      pen.setColor(colorLineMetka[i]);
      x1Metka[i]=x2Metka[i]=0;
      lineMetka[i]=new Q3CanvasLine(canvas);
      lineMetka[i]->setPen(pen);
      lineMetka[i]->setPoints(0,0,0,0);
      lineMetka[i]->setZ(zLineFild+1.);
      lineMetka[i]->show();
  }
  x=new double* [kol];
  y=new double* [kol];
  n=new long[kol];
  colorLine =new QColor[kol];
  colorPoint=new QColor[kol];
  penWidth=new long[kol];

  diagramma=new MyCanvasPolyline*[kol];

  for(i=0; i<kol; i++)
  {
      n[i]=0;
      colorLine[i].setRgb(255,0,0);
      colorPoint[i].setRgb(255,0,0);
      penWidth[i]=1;

      diagramma[i]=new MyCanvasPolyline(canvas);
      diagramma[i]->setZ(zBase+(double)i);
      diagramma[i]->show();
    }
  
  Dx=Dy=.0;
  xBeg=yBeg=.0;
}

DrawCanvas::~DrawCanvas()
{
  int i;
  delete[] x;
  delete[] y;
  delete[] n;
  delete[] colorLine;
  delete[] colorPoint;
  delete[] penWidth;
  delete[] xBegin;
  delete[] yBegin;
  delete[] xEnd;
  delete[] yEnd;

  for(i=0; i<kol; i++)
  {
      diagramma[i]->hide();
      delete diagramma[i];
  }
  delete diagramma;
  for(i=0; i<KolMetka; i++)
  {
      lineMetka[i]->hide();
      delete lineMetka[i];
  }
}

void DrawCanvas::setXY(double *X, double *Y, long *N, long Size)
{
  for(long i=0; i<kol; i++)
    {
      x[i]=X+Size*i;
      y[i]=Y+Size*i;
      n[i]=N[i];
      if (!flagRangeX || !flagRangeY)
        {
          xmax=xmin=X[0];
          ymax=ymin=Y[0];
          for(long j=1; j<N[i]; j++)
            {
              xmax=(xmax<X[j])? X[j] : xmax;
              ymax=(ymax<Y[j])? Y[j] : ymax;
              xmin=(xmin>X[j])? X[j] : xmin;
              ymin=(ymin>Y[j])? Y[j] : ymin;
            }
          flagRangeX=flagRangeY=true; // диапазон изменений аргумента и функции определен
        }
    }
  kolDataX=kolDataY=kol;
}

void DrawCanvas::setY(double *Y, long N, long i)
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
          if (ymin==ymax)
                if ( Y)
                    ymin=ymax=Y[0];
                else
                    ymin=ymax=yBeg;
          if (Y)
            for(i=0; i<N; i++)
              {
                 ymax=(ymax<Y[i])? Y[i] : ymax;
                 ymin=(ymin>Y[i])? Y[i] : ymin;
              }
          else
            {
              ymin=(ymin>yBeg)? yBeg : ymin;
              ymax=(ymax<yBeg+Dy*N)? yBeg+Dy*N : ymax;
            }
          if (kolDataY==kol)
            flagRangeY=true;
        }
    }
}

void DrawCanvas::setX(double *X, long N, long i)
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
            if (xmin==xmax)
                if (X)
                    xmin=xmax=X[0];
                else
                    xmin=xmax=xBeg;
          if (X)
            for(i=0; i<N; i++)
              {
                 xmax=(xmax<X[i])? X[i] : xmax;
                 xmin=(xmin>X[i])? X[i] : xmin;
              }
          else
            {
              xmin=(xmin>xBeg)? xBeg : xmin;
              xmax=(xmax<xBeg+Dx*N)? xBeg+Dx*N : xmax;
            }
          if (kolDataX==kol)
            flagRangeX=true;
        }
    }
}

bool DrawCanvas::resetData()
{
    if (!flagMinMax)
    {
        flagRangeX=flagRangeY=false;
        xmin=xmax=ymin=ymax=.0;
    }
    kolDataX=kolDataY=0;
    for(int i=0; i<kol; i++)
        n[i]=0;
    return true;
}

void DrawCanvas::draw()
//
// Функция предназначена для отображения
// keyPoint - 1 - рисовать кружки, 0 -не рисовать
//
{
  long     x1, y1, x0, y0;
  double   sizex, sizey;
  long     i, j, nPoint;
  bool     flag;

  if (/*error || */kolDataY<kol || kolDataX<kol)
      return;

  if (xmax==xmin)
      xmax=xmin+1.;
  if (ymax==ymin)
      ymax=ymin+1.;
  sizex=xmax-xmin;
  sizey=ymax-ymin;

  if (!flagMinMax)
  {
      double sx=xmax-xmin,
             sy=ymax-ymin;
  
      while(sx<1000.)
          sx*=10.;
      while(sy<1000.)
          sy*=10.;

      resizeMyCanvas();
      canvasSetka->setSize((int)sx, (int)sy); // это сделано только для автоматической перерисовки сетки
  }

  int step=size.height()/KolMetka;
  for(i=0; i<KolMetka; i++)
  {
      y1=y0=iy+step/2+step*i;
      x0=(long)((x1Metka[i]-xmin)*nx/sizex)+ix;
      x1=(long)((x2Metka[i]-xmin)*nx/sizex)+ix;
      QPen pen=lineMetka[i]->pen();
      pen.setColor(colorLineMetka[i]);
      lineMetka[i]->setPen(pen);
      lineMetka[i]->setPoints(x0, y0, x1, y1);
  }
  for(i=0; i<kol; i++)
  {
      if (n[i]<2)
      {
          xEnd[i]=yEnd[i]=xBegin[i]=yBegin[i]=0;
      }
      Q3PointArray &array=diagramma[i]->getPointArray();
      array.resize(n[i]);
      nPoint=0;
      x1=y1=0;
      flag=true;
      for(j=0; j<n[i]; j++)
      {
          if (x[i])
              x1=(long)((x[i][j]-xmin)*nx/sizex)+ix;
          else
              x1=(long)((xBeg+Dx*j-xmin)*nx/sizex)+ix;
          if (y[i])
              y1=-(long)((y[i][j]-ymin)*ny/sizey)+iy;
          else
              y1=-(long)((yBeg+Dy*j-ymin)*ny/sizey)+iy;
          if (x1>=ix && x1<=ix+nx && y1<=iy-1 && y1>=iy-ny)
          {
              if (!nPoint)
              {
                  xBegin[i]=x0=x1;
                  yBegin[i]=y0=y1;
              }
              else
                  if (x0==x1 && y0==y1)
                      continue;

              if (flag && nPoint && (xEnd[i]!=x1 || yEnd[i]!=y1 || xBegin[i]!=x0 || yBegin[i]!=y0))
              {
                  xBegin[i]=x0;
                  yBegin[i]=y0;
                  xEnd[i]=x1;
                  yEnd[i]=y1;
                  flag=false;
              }
              x0=x1;
              y0=y1;
              array.setPoint(nPoint,x1,y1);
              nPoint++;
          }
      }

      QPen pen( colorLine[i], Qt::SolidLine);
      pen.setWidth(penWidth[i]);
      diagramma[i]->setKol(nPoint);
      diagramma[i]->setPen(pen);
      diagramma[i]->setPoints(xBegin[i], yBegin[i], xEnd[i], yEnd[i]);
      //cout<<endl<<"nPoint="<<nPoint<<" xBegin[i]="<<xBegin[i]<<" yBegin[i]="<<yBegin[i]<<" xEnd[i]="<<xEnd[i]<<" yEnd[i]="<<yEnd[i]<<flush;
  }
  canvas->setAllChanged(); // устанавливает все изменения в канвасе и требует их перерисовать
  //canvas->update();
}

void DrawCanvas::upDate()
{
  update();
}

void DrawCanvas::resizeEvent(QResizeEvent *event)
{
    DrawBaseCanvas::resizeEvent(event);
    draw();
}

void MyCanvasPolyline::drawShape( QPainter & painter )
{
    painter.setPen(penLine);
    for(long i=0; i<kol-1; i++)
        painter.drawLine(*(poly+i), *(poly+i+1));
    if (keyPoint>0)
    {
        painter.setPen(colorPoint);
        QRect r;
        for(long i=0; i<kol; i++)
        {
            r.setCoords((poly+i)->x()-keyPoint, (poly+i)->y()-keyPoint,
                        (poly+i)->x()+keyPoint, (poly+i)->y()+keyPoint);
            painter.drawEllipse(r);
        }
    }
}

void DrawCanvas::contentsMousePressEvent ( QMouseEvent * e )
{
    DrawBaseCanvas::contentsMousePressEvent(e);
}

void DrawCanvas::contentsMouseReleaseEvent ( QMouseEvent * e )
{
    DrawBaseCanvas::contentsMouseReleaseEvent(e);
}

void DrawCanvas::contentsMouseMoveEvent ( QMouseEvent * e )
{
    DrawBaseCanvas::contentsMouseMoveEvent(e);
}
