#include "..\..\draw\mycolor.hpp"
#include "..\..\draw\draw.h"
#include "..\..\draw\init_gr.h"
#include <math.h>
#include <stdlib.h>

extern color_t colorMax;
extern font_t  *fontApp;

void drawEll(rect_t &r,    // область прорисовки диаграммы
             double **alf, // азимуты
             double **amp, // ампдитуды круговой диаграммы
             long   *n,    // число точек в диаграмме
             long   kol)   // число диаграмм
//
// Функция предназначена для отображения круговой диаграммы
//
{
  int i,j,k,x,y,N;
  long maxx,maxy,x0,y0,a,b,ihw,isw;
  rect_t rab;
  double R,mod;
  double cd,beta,ca,sa,ha,t1,t2,t3,t4;
  point_t p1,p2;
  const long nLine=24;
  const double RAD=acos(-1.)/180.,
               Da =acos(-1.)/(.5*nLine),
               PI5=.5*acos(-1.);
  const double db=acos(-1.)/12.;
  point_t *p;
  char str[20];
  int  penX=5, // размер пера
       penY=5,
       penOldX,penOldY;
//=========================================================
  for(N=i=0; i<kol; i++)
    N=__max(N,n[i]+1);
  p=new point_t[N];
  MGL_useFont(fontApp);
  MGL_setTextDirection(MGL_RIGHT_DIR);
  MGL_setTextJustify(MGL_CENTER_TEXT,MGL_CENTER_TEXT);
  MGL_setWriteMode(MGL_REPLACE_MODE);
  isw=MGL_maxCharWidth();
  ihw=MGL_textHeight();
  ihw=3*((ihw<isw)? isw : ihw);  // было 3 только для круговой диаграммы

  MGL_setViewport(r);
  MGL_setBackColor(MGL_realColor(dc,Yellow));
  MGL_clearViewport();
  MGL_setColor(COLFON);
  MGL_getPenSize(&penOldX,&penOldY);

  maxx=MGL_maxx();
  maxy=MGL_maxy();
  x0=maxx/2;       // координаты центра окружностей
  y0=maxy/2;
  a =x0-ihw;       // полуоси эллипса
  b =y0-ihw;

  rab.left  =x0-a+1;
  rab.top   =y0-b+1;
  rab.right =x0+a-1;
  rab.bottom=y0+b-1;
  MGL_fillEllipse(rab);

  mod=(a>b)? a-5 : b-5;

  ca=1.0;
  sa=.0;
  t1=cos(Da);
  t2=-sin(Da);
  ha=2.*t1;
  for(i=0; i<nLine; i++)
    {
      p1.x=x0;
      p1.y=y0;
      p2.x=p1.x+a*sa;
      p2.y=p1.y-b*ca;
      sprintf(str,"%3.0f",Da*i/RAD);
      isw=MGL_textWidth(str)/2;
      x=x0+a*sa;
      y=y0-b*ca;
      MGL_setColor(COLSETKA);
      MGL_lineCoord(x0,y0,x,y);
      p2.x+=isw*sa;
      p2.y-=isw*ca;
      //MGL_setColor(COLFRAME);
      MGL_setColor(MGL_realColor(dc,DarkGray));
      MGL_drawStrXY(p2.x,p2.y,str);
      t3=ha*ca-t1;
      t4=ha*sa-t2;
      t1=ca;
      t2=sa;
      ca=t3;
      sa=t4;
    }

  for(i=0; i<5; i++)
    {
      cd=1.-i/5.;
      sprintf(str,"%3.1f",cd);
      rab.left  =x0-a*cd;
      rab.top   =y0-b*cd;
      rab.right =x0+a*cd;
      rab.bottom=y0+b*cd;
      MGL_setColor(COLSETKA);
      MGL_ellipse(rab);
      if (i)
        {
          //MGL_setColor(COLFRAME);
          MGL_setColor(MGL_realColor(dc,DarkGray));
          MGL_drawStrXY(rab.right,y0,str);
          MGL_drawStrXY(rab.left,y0,str);
        }
    }

  for(j=0; j<kol; j++)
    {
      switch(j)
        {
          case 0:
                 MGL_setColor(MGL_realColor(dc,Red));
                 break;
          case 1:
                 MGL_setColor(MGL_realColor(dc,LightGreen));
                 break;
          case 2:
                 MGL_setColor(MGL_realColor(dc,LightBlue));
                 break;
        }

      MGL_setPenSize(penX,penY);
      for(i=0; i<n[j]+1; i++)
        {
          if (i==n[j])
            {
              R=*(amp[j]+0)*mod;
              sa=sin(*(alf[j]+0)*RAD);
              ca=cos(*(alf[j]+0)*RAD);
            }
          else
            {
              R=*(amp[j]+i)*mod;
              sa=sin(*(alf[j]+i)*RAD);
              ca=cos(*(alf[j]+i)*RAD);
            }
          p[i].x=x0+R*sa-penX/2;
          p[i].y=y0-R*ca-penY/2;
        }
//      if (j)
        MGL_polyLine(n[j]+1,p);
//      else
//        MGL_fillPolygon(n[j]+1,p,0,0);
    }
  MGL_setPenSize(penOldX,penOldY);
  delete[] p;
}

