/***************************************************************************
                          drawpoint.h  -  description
                             -------------------
    begin                : Thu Aug 07 2003
    copyright            : (C) 2003 by Verotgradov G.G.
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

#ifndef DRAWPOINTRECT_H
#define DRAWPOINTRECT_H

#include "drawbase.h"
#include <QColor>
#include <QMatrix>
#include <list>

/*
  author Verotgradov G.G.
*/

#ifndef POINTDOUBLE
#define POINTDOUBLE
struct PointDouble
  {
    PointDouble(double X, double Y, QColor c=QColor(0,0,0), double h=.0, double w=.0 )
      {x=X; y=Y; color=c; flag=true; hight=h; width=w;};
    double getX() const {return x;};
    double getY() const {return y;};
    double getWidth() const {return width;};
    double getHight() const {return hight;};
    bool   getFlag(){return flag;};
    QColor getColor() const {return color;};
    void   setFlag(bool b){flag=b;};
    private:
      double x;
      double y;
      double hight; // высота прямоугольника
      double width; // ширина прямоугольника
      bool   flag;
      QColor color;
  };
#endif

class DrawPointRect : public DrawBase
{
  public:
    DrawPointRect( QWidget *parent,
         long k,
                   //char *infX, char *infY,
         const QString &infX, const QString &infY,
         double xmin, double xmax, double ymin, double ymax,
         long ir=1, long ipgr=1, long krx=8, long kry=8);
    ~DrawPointRect();
    enum FormMetka {NoForm, Ellipse, Rectangle};
    void setXY(double x, double y, long n, bool flag=true);
    void setXY(double x, double y, QColor c, long n, bool flag=true);
    void setXY(double x, double y, QColor c, double h, double w, long n, bool flag=true);
    void setXY(PointDouble pointDouble, long n, bool flag=true);
    void setHight(double h, long n){hight[n]=h;};
    double getHight(long n){return hight[n];};
    void setWidth(double w, long n){width[n]=w;};
    double getWidth(long n){return width[n];};
    void   setColorPoint(QColor colP, long nLine){colorPoint[nLine]=colP;};
    QColor getColorPoint(long nLine){return colorPoint[nLine];};
    void upDate();
    void setClear(bool clear){keyClear=clear;};
    bool getClear(){return keyClear;};
    void setFormMetka(FormMetka m){formMetka=m;};
    FormMetka getFormMetka(){return formMetka;};
    void Clear();  // отчистка массивов точек
    void reset();
    std::list<PointDouble*>  *getListPointDouble(){return pointDouble;};
    long getKol(){return kol;};
  private:
    long   kol;
    int kolTemp;
    std::list<PointDouble*>  *pointDouble;
    bool keyClear;
    QColor *colorPoint; // цвета точек одной кривой
    double *hight;      // высоты точек одной кривой
    double *width;      // ширины точек одной кривой
    FormMetka formMetka;
    long keyPainter;
    void initData(long k);
    long draw(QPainter &p);
  protected:
    virtual void paintEvent(QPaintEvent *);
};
	
#endif // DrawPointRect
