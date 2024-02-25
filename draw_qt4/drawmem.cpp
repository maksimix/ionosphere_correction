#include "drawmem.h"
#include <stdlib.h>

DrawMem::DrawMem(QWidget *parent,
           long k,
                 //char *infX, char *infY,
           const QString &infX, const QString &infY,
           double xMin, double xMax, double yMin, double yMax,
           long iR,long iPgr, long kRx, long kRy) :

           DrawMemBase(parent, infX, infY, xMin, xMax, yMin, yMax,
                   iR,iPgr, kRx, kRy)
{
  initData(k);
}

DrawMem::DrawMem(QWidget *parent,
           long k,
                 //char *infX, char *infY,
           const QString &infX, const QString &infY,
           long iR,long iPgr, long kRx, long kRy) :

           DrawMemBase(parent, infX, infY, iR,iPgr, kRx, kRy)
{
  initData(k);
}

void DrawMem::initData(long k)
{
    int i;

    keyPoint=0;
    kol=k;
    kolDataX=kolDataY=0;
    x=new double* [kol];
    y=new double* [kol];
    n=new long[kol];
    colorLine =new QColor[kol];
    colorPoint=new QColor[kol];
    penWidth=new long[kol];
    for( i=0; i<kol; i++)
    {
        n[i]=0;
        colorLine[i].setRgb(255,255,255);
        colorPoint[i].setRgb(255,0,0);
        penWidth[i]=1;
    }
    Dx=Dy=.0;
    xBeg=yBeg=.0;
    for(i=0; i<KolMetka; i++)
    {
        colorLineMetka[i]=colorFon;
        x1Metka[i]=x2Metka[i]=0;
    }
}

DrawMem::~DrawMem()
{
  delete[] x;
  delete[] y;
  delete[] n;
  delete[] colorLine;
  delete[] colorPoint;
  delete[] penWidth;
}

void DrawMem::setXY(double *X, double *Y, long *N, long Size)
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

void DrawMem::setY(double *Y, long N, long i)
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

void DrawMem::setX(double *X, long N, long i)
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

void DrawMem::resetData()
{
    if (!flagMinMax)
    {
        flagRangeX=flagRangeY=false;
        xmin=xmax=ymin=ymax=.0;
    }
    kolDataX=kolDataY=0;
    for(int i=0; i<kol; i++)
        n[i]=0;
}

void DrawMem::paintEvent(QPaintEvent *e)
{
    DrawMemBase::paintEvent(e);

    QPainter p;
    p.begin(pix);
    draw(p);
    drawMetka(p);
    p.end();

    p.begin(this);
    p.drawImage(0, 0, *pix);
    p.setOpacity(0.7);
    p.drawImage(0, 0, *pixSetka);
    p.end();
}

long DrawMem::draw(QPainter &p)
//
// Функция предназначена для отображения
// keyPoint - 1 - рисовать кружки, 0 -не рисовать
//
{
    long     x0,y0,x1,y1;
    long     i,j;
    double   sizex,sizey;
    QRect    rFill;
    
    QPen pen=p.pen();

    //if (!error || kolDataY<kol || kolDataX<kol)
    if ( !error )
      return 1;
  
    sizex=xmax-xmin;
    sizey=ymax-ymin;
    // цветные метки под графиком
    int step=size.height()/KolMetka;
    for(i=0; i<KolMetka; i++)
    {
        y1=y0=iy+step/2+step*i;
        x0=(long)((x1Metka[i]-xmin)*nx/sizex)+ix;
        x1=(long)((x2Metka[i]-xmin)*nx/sizex)+ix;
        pen.setColor(colorLineMetka[i]);
        pen.setWidth(3);
        p.setPen(pen);
        p.drawLine(x0, y0, x1, y1);
    }
  
    for(i=0; i<kol; i++)
    {
        if (!n[i])
            continue;
        if (x[i])
          x0=(long)((*x[i]-xmin)*nx/sizex+ix);
        else
          x0=(long)((xBeg-xmin)*nx/sizex+ix);
        if (y[i])
          y0=-(long)((*y[i]-ymin)*ny/sizey)+iy;
        else
          y0=-(long)((yBeg-ymin)*ny/sizey)+iy;
  
        for(j=1; j<n[i]; j++)
          {
            if (x[i])
              x1=(long)((x[i][j]-xmin)*nx/sizex+ix);
            else
              x1=(long)((xBeg+Dx*j-xmin)*nx/sizex+ix);
            if (y[i])
              y1=-(long)((y[i][j]-ymin)*ny/sizey)+iy;
            else
              y1=-(long)((yBeg+Dy*j-ymin)*ny/sizey)+iy;
            if (x1<=ix   || x1>=ix+nx ||
                y1>=iy-1 || y1<=iy-ny ||
                x0<=ix   || x0>=ix+nx ||
                y0>=iy-1 || y0<=iy-ny)
              {
                x0=x1;
                y0=y1;
              }
            else
              if (x0!=x1 || y0!=y1)
                {
                  pen.setWidth(penWidth[i]);
                  pen.setColor(colorLine[i]);
                  p.setPen(pen);
                  p.drawLine(x0,y0,x1,y1);
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
  
    for(i=0; i<kol; i++)
     if (n[i]>=1 && keyPoint>0)
        {
          if (x[i])
            x1=(long)((*x[i]-xmin)*nx/sizex+ix);
          else
            x1=(long)((xBeg-xmin)*nx/sizex+ix);
          if (y[i])
            y1=-(long)((*y[i]-ymin)*ny/sizey+iy);
          else
            y1=-(long)((yBeg-ymin)*ny/sizey+iy);

          rFill.setCoords(x1-keyPoint,y1-keyPoint,x1+keyPoint,y1+keyPoint);
          p.setPen(colorPoint[i]);
          p.setBrush(colorPoint[i]);
          if (rFill.left()>ix && rFill.right()<ix+nx && rFill.bottom()<iy-1 && rFill.top()>iy-ny)
            p.drawEllipse(rFill);
        }
  
    return 0;
}

void DrawMem::upDate()
{
  update();
}

void DrawMem::reDraw()
{
    //repaint(false);
    update();
}
