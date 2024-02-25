#include <stdio.h>
#include "..\..\draw\draw.h"
#include "..\..\draw\init_gr.h"
#include "..\..\draw\mycolor.hpp"

int fildInit(double  funmin,
             double  funmax,
             double  argmin,
             double  argmax,
             DRAW_CH &draw_win,
             char    infx[],
             char    infy[],
             rect_t  &fildView)
//
// Функция отображает на экране поле, в котором изображается
// координатная сетка графика
//
// VGG 1997
  {
    MGL_setViewport(fildView);
    MGL_setBackColor(MGL_realColor(dc,Yellow));
    MGL_clearViewport();
    draw_win.ix=0;
    draw_win.iy=fildView.bottom-fildView.top;
    draw_win.nx=fildView.right-fildView.left;
    draw_win.ny=draw_win.iy;
    draw_win.left  =fildView.left;
    draw_win.right =fildView.right;
    draw_win.top   =fildView.top;
    draw_win.bottom=fildView.bottom;

    if (grraz(&draw_win.ix,&draw_win.iy,argmin,argmax,funmin,funmax,
              &draw_win.nx,&draw_win.ny,draw_win.ir,draw_win.kxr,
              draw_win.kyr,draw_win.ipgr,
              &draw_win.left,&draw_win.top,&draw_win.right,&draw_win.bottom,
              infx,infy,1))
      return 1;
    else
      return 0;
}