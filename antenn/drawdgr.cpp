#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "..\..\draw\mycolor.hpp"
#include "..\..\draw\draw.h"
#include "..\..\draw\init_gr.h"

extern color_t colorMax;

int drawdgr(double **x,        // массив аргументов
            double **y,        // массив функций
            long   *n,         // число точек, заданных при табуляции функций
            double xmin,       // минимум аргумента
            double xmax,       // максимум аргумента
            double ymin,       // минимум функций
            double ymax,       // максимум функций
            rect_t  &r,        // область расположения рисунка
            DRAW_CH &draw_ch,  // параметры области графика
            short   kol)       // количество графиков
//
// Функция предназначена для отображения графиков нескольких функций
// в декартовых координатах
//
{
  int      x0,y0,x1,y1;
  double   sizex,sizey;
  point_t  point;
  rect_t   r_clear=r;
  rect_t   rFill;
  long     i,j,color,dColor;

  if (!kol)
    return 1;

  MGL_setBackColor(COLFON);
  MGL_setViewport(r_clear);
  r_clear.left  =r.left+draw_ch.ix+1;
  r_clear.right =r.left+draw_ch.ix+draw_ch.nx;
  r_clear.top   =r.top+1;
  r_clear.bottom=r.top+draw_ch.iy-1;
  MGL_setViewport(r_clear);
  MGL_clearViewport();

  MGL_setViewport(r);
  MGL_setWriteMode(MGL_REPLACE_MODE);

  ymax +=3.*(ymax-ymin)/(double)draw_ch.ny;
  ymin -=3.*(ymax-ymin)/(double)draw_ch.ny;
  sizex=xmax-xmin;
  sizey=ymax-ymin;
  dColor=maxC/kol;
  if (!dColor)
    dColor=1;

  for(i=kol-1; i>=0; i--)  // первый график всегда на поверхности
    {
      x0= (*(*(x+i))-xmin)*draw_ch.nx/sizex+draw_ch.ix+1;
      y0=-(*(*(y+i))-ymin)*draw_ch.ny/sizey+draw_ch.iy;
      color=Blue+i;
      if (kol>5)
        {
          color=dColor*i;
          while(color>=maxC)
            color-=maxC;
          color=arrayColor[color];
        }
      //MGL_setColor(MGL_realColor(dc,color));
      MGL_setColor(color);
      for(j=1; j<n[i]; j++)
        {
          x1=(*(*(x+i)+j)-xmin)*draw_ch.nx/sizex+draw_ch.ix;
          if (x1==draw_ch.ix+draw_ch.nx)
            x1--;
          y1=-(*(*(y+i)+j)-ymin)*draw_ch.ny/sizey+draw_ch.iy;
          if (x1<=draw_ch.ix || x1>=draw_ch.ix+draw_ch.nx ||
              y1>=draw_ch.iy-1 || y1<=draw_ch.iy-draw_ch.ny ||
              x0<=draw_ch.ix || x0>=draw_ch.ix+draw_ch.nx ||
              y0>=draw_ch.iy-1 || y0<=draw_ch.iy-draw_ch.ny)
            {
            }
          else
            if (x0!=x1 || y0!=y1)
              MGL_lineCoord(x0,y0,x1,y1);
          x0=x1;
          y0=y1;
        }
    }

  return 0;
} /* drawdgr */

