using namespace std;
#include <iostream>
#include "draw2.h"
#include <stdlib.h>

Draw2::Draw2(QWidget *parent,
           long k,
           //char *infX, char *infY,
           const QString &infX, const QString &infY,
           double xMin, double xMax, double yMin, double yMax,
           long iR,long iPgr, long kRx, long kRy) :

           DrawPoligonMemFull(parent, infX, infY, xMin, xMax, yMin, yMax,
                   iR,iPgr, kRx, kRy)
{
    flagRangeX=flagRangeY=true;
    initData(k);
}

Draw2::Draw2(QWidget *parent,
           long k,
           //char *infX, char *infY,
           const QString &infX, const QString &infY,
           long iR,long iPgr, long kRx, long kRy) :

           DrawPoligonMemFull(parent, infX, infY, iR,iPgr, kRx, kRy)
{
    flagRangeX=flagRangeY=false;
    initData(k);
}

void Draw2::initData(long k)
{
    keyClear=false;
    keyPoint=0;
    kol=k;
    lineBeg=0;
    lineEnd=kol;
    kolDataX=kolDataY=0;
    x=new double* [kol];
    y=new double* [kol];
    n=new long[kol];
    colorLine =new QColor[kol];
    colorPoint=new QColor[kol];
    penWidth=new long[kol];
    for(long i=0; i<kol; i++)
    {
        n[i]=0;
        colorLine[i].setRgb(255,255,255);
        colorPoint[i].setRgb(255,0,0);
        penWidth[i]=1;
    }
    Dx=Dy=.0;
    xBeg=yBeg=.0;

    keyPainter=true;
}

Draw2::~Draw2()
{
  delete[] x;
  delete[] y;
  delete[] n;
  delete[] colorLine;
  delete[] colorPoint;
  delete[] penWidth;
}

void Draw2::setXY(double *X, double *Y, long *N, long Size)
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
  lineBeg=0;
  lineEnd=kol;
  kolDataX=kolDataY=kol;
  keyPainter=true;  // только одну линию перерисовать
}

void Draw2::setY(double *Y, long N, long i)
{
    keyPainter=true;
    if (i<kol)
    {
        y[i]=Y;
        n[i]=N;

        if (!flagRangeY)
        {
            kolDataY++;
            if (kolDataY==kol)
              for(i=0; i<kol; i++)
                if (n[i]==0 && kolDataY>0)
                  kolDataY--;
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

        lineBeg=i;
        lineEnd=i+1;
    }
  
    if (N)
        keyPainter=false;  // только одну линию перерисовать
}

void Draw2::setY(double *Y,long n)
{
    DrawPoligonMemFull::setY(Y,n);
}

void Draw2::setY(double X1, double X2, double *Y, long N)
{
    DrawPoligonMemFull::setY(X1,X2,Y,N);
}


void Draw2::setXBegDx(double x_beg, double dx)
{
    xBeg=x_beg;
    Dx=dx;
    DrawPoligonMemFull::setXBegDx(x_beg, dx);
}

void Draw2::setYBegDy(double y_beg, double dy)
{
    yBeg=y_beg;
    Dy=dy;
    DrawPoligonMemFull::setYBegDy(y_beg, dy);
}


void Draw2::setX(double *X, long N, long i)
{
    keyPainter=true;
    if (i<kol)
    {
        x[i]=X;
        n[i]=N;

        if (!flagRangeX)
        {
            kolDataX++;
            if (kolDataX==kol)
              for(i=0; i<kol; i++)
                if (n[i]==0 && kolDataX>0)
                  kolDataX--;
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

        lineBeg=i;
        lineEnd=i+1;
    }
  
    if (N)
        keyPainter=false;  // только одну линию перерисовать
}

void Draw2::resetData()
{
    keyPainter=true;

    if (!flagMinMax)
    {
        flagRangeX=flagRangeY=false;
        xmin=xmax=ymin=ymax=.0;
    }
    kolDataX=kolDataY=0;
    lineBeg=0;
    lineEnd=kol;

    for(int i=0; i<kol; i++)
        n[i]=0;

}

void Draw2::paintEvent(QPaintEvent *e)
{
    //cout<<endl<<"Draw2::paintEvent(QPaintEvent *e)"<<flush;
    if (keyPainter) // если изменилась только одна точка, перерисовывать все поле нет необходимости
        DrawPoligonMemFull::paintEvent(e);

    QPainter p;
    p.begin(this);
    p.setClipRect(e->rect());
    draw(p,keyClear,keyPoint);
    p.end();

    keyPainter=true;
}

long Draw2::draw(QPainter &p,
                bool keyClear,
                int keyPoint)
//
// Функция предназначена для отображения
// keyPoint - 1 - рисовать кружки, 0 -не рисовать
//
{
  long     x0,y0,x1,y1;
  double   sizex,sizey;
  QPoint   point;
  QRect    rFill;
  QPen     pen=p.pen();
  long     i,j;

  //printf("\nlineBeg=%d  lineEnd=%d",lineBeg,lineEnd);
  //if (!error || kolDataY<kol || kolDataX<kol)
  if (!error || lineBeg>=lineEnd || lineEnd>kol)
  {
      keyPainter=true;
      return 1;
  }

  if (keyClear && keyPainter)
  {
      QBrush brush( colorFon, SolidPattern );
      p.fillRect(rClear,brush);
  }

  sizex=xmax-xmin;
  sizey=ymax-ymin;
  //p.setRasterOp(Qt::XorROP);
  for(i=lineBeg; i<lineEnd; i++)
  {
      if (n[i]<=1)
          continue;
      if (x[i])
        x0=(*x[i]-xmin)*nx/sizex+ix;
      else
        x0=(xBeg-xmin)*nx/sizex+ix;
      if (y[i])
        y0=-(*y[i]-ymin)*ny/sizey+iy;
      else
        y0=-(yBeg-ymin)*ny/sizey+iy;

      for(j=1; j<n[i]; j++)
        {
          if (x[i])
            x1=(x[i][j]-xmin)*nx/sizex+ix;
          else
            x1= (xBeg+Dx*j-xmin)*nx/sizex+ix;
          if (y[i])
            y1=-(y[i][j]-ymin)*ny/sizey+iy;
          else
            y1=-(yBeg+Dy*j-ymin)*ny/sizey+iy;
          if (x1<=ix   || x1>=ix+nx ||
              y1>=iy+1 || y1<=iy-ny ||
              x0<=ix   || x0>=ix+nx ||
              y0>=iy+1 || y0<=iy-ny)
            {
              x0=x1;
              y0=y1;
            }
          else
            if (x0!=x1 || y0!=y1)
              {
                point.rx()=x0;
                point.ry()=y0;
                p.moveTo(point);
                point.rx()=x1;
                point.ry()=y1;
                pen.setWidth(penWidth[i]);
                pen.setColor(colorLine[i]);
                //pen.setColor(QColor(colorLine[i].red()^colorFon.red(),
                //                    colorLine[i].green()^colorFon.green(),
                //                    colorLine[i].blue()^colorFon.blue()));
                p.setPen(pen);
                p.lineTo(point);
                if (keyPoint>0)
                  {
                    rFill.setCoords(x0-keyPoint,y0-keyPoint,x0+keyPoint,y0+keyPoint);
                    p.setPen(colorPoint[i]);
                    p.setBrush(colorPoint[i]);
                    rFill.setCoords(x1-keyPoint,y1-keyPoint,x1+keyPoint,y1+keyPoint);
                    if (rFill.left()>ix && rFill.right()<ix+nx && rFill.bottom()<iy-1 && rFill.top()>iy-ny)
                      p.drawEllipse(rFill);
                   }
                x0=x1;
                y0=y1;
              }
        }
  }

  for(i=lineBeg; i<lineEnd; i++)
   if (n[i]>=1 && keyPoint>0)
      {
        if (x[i])
          x1=(*x[i]-xmin)*nx/sizex+ix;
        else
          x1= (xBeg-xmin)*nx/sizex+ix;
        if (y[i])
          y1=-(*y[i]-ymin)*ny/sizey+iy;
        else
          y1=-(yBeg-ymin)*ny/sizey+iy;
        rFill.setCoords(x1-keyPoint,y1-keyPoint,x1+keyPoint,y1+keyPoint);
        p.setPen(colorPoint[i]);
        p.setBrush(colorPoint[i]);
        //p.setPen(QColor(colorLine[i].red()^colorFon.red(),
        //                colorLine[i].green()^colorFon.green(),
        //                colorLine[i].blue()^colorFon.blue()));
        //p.setBrush(QColor(colorLine[i].red()^colorFon.red(),
        //                  colorLine[i].green()^colorFon.green(),
        //                  colorLine[i].blue()^colorFon.blue()));
        if (rFill.left()>ix && rFill.right()<ix+nx && rFill.bottom()<iy-1 && rFill.top()>iy-ny)
            p.drawEllipse(rFill);
      }
  //p.setRasterOp(Qt::CopyROP);

  keyPainter=true;
  lineBeg=0;
  lineEnd=kol;

  return 0;
}

void Draw2::upDate()
{
    //if (keyPainter)
    //    DrawPoligonMemFull::reDraw();
    repaint(false);
}
