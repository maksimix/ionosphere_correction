/***************************************************************************
                          drawpoint.h  -  description
                             -------------------
    begin                : Thu Aug 31 2000
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

#ifndef DRAWPOINT_H
#define DRAWPOINT_H

#ifndef DRAWBASE_H
#include "drawbase.h"
#endif
#ifndef QCOLOR_H
#include <qcolor.h>
#endif
#ifndef QWMATRIX_H
#include <qwmatrix.h>
#endif

#include <list>

/*
  author Verotgradov G.G.
*/

struct PointDouble
  {
    PointDouble(double X, double Y, QColor c=QColor(0,0,0)) {x=X; y=Y; color=c; flag=true;};
    double getX() const {return x;};
    double getY() const {return y;};
    bool   getFlag(){return flag;};
    QColor getColor() const {return color;};
    void   setFlag(bool b){flag=b;};
    private:
      double x;
      double y;
      bool   flag;
      QColor color;
  };

class DrawPoint : public DrawBase
{
  public:
    DrawPoint( QWidget *parent,
               long k,
               //char *infX, char *infY,
               const QString &infX, const QString &infY,
               double xmin, double xmax, double ymin, double ymax,
               long ir=1, long ipgr=1, long krx=8, long kry=8);
    ~DrawPoint();
    void setXY(double x, double y, long n);
    void setXY(double x, double y, QColor c, long n);
    void setXY(PointDouble pointDouble, long n);
    void   setColorPoint(QColor colP, long nLine){colorPoint[nLine]=colP;};
    QColor getColorPoint(long nLine){return colorPoint[nLine];};
    void upDate();
    void setClear(bool clear){keyClear=clear;};
    bool getClear(){return keyClear;};
    void setSizePoint(int size, long nLine){keyPoint[nLine]=size;};
    int  getSizePoint(long nLine){return keyPoint[nLine];};
    void Clear();  // отчистка массивов точек
	std::list <PointDouble>  *getListPointDouble(){return pointDouble;};
    long getKol(){return kol;};
  private:
    long   kol;
    std::list <PointDouble>  *pointDouble;
    bool keyClear;
    int *keyPoint;
    QColor *colorPoint;
    long keyPainter;
    void initData(long k);
    long draw(QPainter &p);
  protected:
    virtual void paintEvent(QPaintEvent *);
};
	
#endif
