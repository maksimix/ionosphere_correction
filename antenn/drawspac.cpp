#include <math.h>
#include "..\..\draw\mycolor.hpp"
#include "..\..\draw\init_gr.h"

extern color_t colorMax;
extern font_t  *fontApp;

void drawSpace(rect_t &r,    // область прорисовки диаграммы
               double Da,    // шаг по азимуту
               double Db,    // шаг по углу места
               double **amp, // ампдитуды диаграммы антенны
               long   L,     // число точек в диаграмме по углу места
               long   M)     // число точек в диаграмме по азимуту
//
// Функция предназначена для отображения пространственной диаграммы пеленгатора
//
{
  rect_t rab;
  int maxx,maxy;
  int x0,y0,a,b;
  int isw,ihw;
  point_t p1,p2;
  short i;
  double cd,beta,ca,sa;
  const long nLine=24;
  const double db=acos(-1.)/12.,
               da=acos(-1.)/(.5*nLine);
  const double RAD=360./(da*nLine);
  char str[20];
//==============================================================
  MGL_setViewport(r);
  MGL_setBackColor(MGL_realColor(dc,Yellow));
  MGL_clearViewport();

  MGL_useFont(fontApp);
  MGL_setTextDirection(MGL_RIGHT_DIR);
  MGL_setTextJustify(MGL_CENTER_TEXT,MGL_CENTER_TEXT);
  isw=MGL_maxCharWidth();
  ihw=MGL_textHeight();
  ihw=3*((ihw<isw)? isw : ihw);

  maxx=MGL_maxx();
  maxy=MGL_maxy();
  x0=maxx/2;       // координаты центра окружностей
  y0=maxy/2;
  a =x0-ihw;       // полуоси эллипса
  b =y0-ihw;

  x0=maxx/2;       // координаты центра окружностей
  y0=maxy/2;
  a =x0-ihw;       // полуоси эллипса
  b =y0-ihw;
  // рисуем пространственную диаграмму
  long l,m,color;
  point_t *p=new point_t[4];
  double cb,t1,t2,hb,ha,t3,t4,t5,t6,x[4],y[4];

  Da/=RAD;
  Db/=RAD;

  // по углу места, потом по азимуту
  cb=1.;
  //t1=cos(Db);
  //hb=2.*t1;
  for(l=1; l<L; l++)
    {
      //t2=hb*cb-t1;
      t1=cb;
      //cb=t2;
      ca=cos(-Da/2);
      sa=sin(-Da/2);
      t3=cos(-1.5*Da);
      t4=sin(-1.5*Da);
      ha=2.*cos(Da);
      cb=(double)(L-l)/(double)L; //*** Линейный масштаб
      for(m=0; m<M; m++)
        {
          t5=ha*ca-t3;
          t6=ha*sa-t4;
          t3=ca;
          t4=sa;
          ca=t5;
          sa=t6;
          color=(maxC-1)**(*(amp+l)+m);
          color&=0x1ff;
          MGL_setColor(arrayColor[color]);
          if (!m)
            {
              x[0]=x0+a*t1*t4;
              y[0]=y0-b*t1*t3;
              x[3]=x0+a*cb*t4;
              y[3]=y0-b*cb*t3;
            }
          else
            {
              x[0]=x[1];
              y[0]=y[1];
              x[3]=x[2];
              y[3]=y[2];
            }
          x[1]=x0+a*t1*sa+.5;
          y[1]=y0-b*t1*ca+.5;
          x[2]=x0+a*cb*sa+.5;
          y[2]=y0-b*cb*ca+.5;
          for(i=0; i<4; i++)
            {
              p[i].x=(x[i]<x0)? x[i]+.5 : x[i]-.5;
              p[i].y=(y[i]<y0)? y[i]+.5 : y[i]-.5;
            }
          MGL_fillPolygonCnvx(4,p,0,0);
        }
    }

  // рисуем полярную систему координат
  ca=1.0;
  sa=.0;
  t1=cos(da);
  t2=-sin(da);
  ha=2.*t1;
  for(i=0; i<nLine; i++)
    {
      p1.x=x0;
      p1.y=y0;
      p2.x=p1.x+a*sa;
      p2.y=p1.y-b*ca;
      sprintf(str,"%3.0f",da*i*RAD);
      isw=MGL_textWidth(str)/2;
      MGL_setColor(MGL_realColor(dc,colorDiagr));
      MGL_line(p1,p2);
      p2.x+=isw*sa;
      p2.y-=isw*ca;
      MGL_setColor(MGL_realColor(dc,DarkGray));
      MGL_drawStrXY(p2.x,p2.y,str);
      t3=ha*ca-t1;
      t4=ha*sa-t2;
      t1=ca;
      t2=sa;
      ca=t3;
      sa=t4;
    }

  for(i=0; i<6; i++)
    {
      beta=db*i;
      //cd=cos(beta);
      cd=(double)(6-i)/6.; //*** Линейный масштаб
      sprintf(str,"%2.0f",beta*RAD);
      rab.left  =x0-a*cd;
      rab.top   =y0-b*cd;
      rab.right =x0+a*cd;
      rab.bottom=y0+b*cd;
      MGL_setColor(MGL_realColor(dc,colorDiagr));
      MGL_ellipse(rab);
      if (i%2)
        {
          MGL_setColor(MGL_realColor(dc,DarkGray));
          MGL_drawStrXY(rab.right,y0,str);
          MGL_drawStrXY(rab.left,y0,str);
        }
    }
  delete[] p;
}
