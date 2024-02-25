#include "antenn.h"
#include "..\..\draw\draw.h"
#include "..\..\draw\init_gr.h"
#include "..\..\draw\mycolor.hpp"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <graph.h>

font_t  *fontApp;

void get_ant(FILE *in,
             FILE *out,
             ANT_TRAN *a1,
             ANT_REC  *a2);
int fildInit(double  funmin,
             double  funmax,
             double  argmin,
             double  argmax,
             DRAW_CH &draw_win,
             char    infx[],
             char    infy[],
             rect_t  &fildView);
int drawdgr(double **x,        // массив аргументов
            double **y,        // массив функций
            long   *n,         // число точек, заданных при табуляции функций
            double xmin,       // минимум аргумента
            double xmax,       // максимум аргумента
            double ymin,       // минимум функций
            double ymax,       // максимум функций
            rect_t  &r,        // область расположения рисунка
            DRAW_CH &draw_ch,  // параметры области графика
            short   kol);      // количество графиков
void drawEll(rect_t &r,    // область прорисовки диаграммы
             double **alf, // азимуты
             double **amp, // ампдитуды круговой диаграммы
             long   *n,    // число точек в диаграмме
             long   kol);  // число диаграмм
void drawSpace(rect_t &r,    // область прорисовки диаграммы
               double Da,    // шаг по азимуту
               double Db,    // шаг по углу места
               double **amp, // ампдитуды диаграммы антенны
               long   L,     // число точек в диаграмме по углу места
               long   M);    // число точек в диаграмме по азимуту

void main(int argc, char *argv[])
{
  ANT_REC  rec;
  ANT_TRAN tran;
  FILE *in,*out;
  double fr,ma=.937,psia=.0;
  double Ma=.0,Psia=.0;
  double ku,knd,Max,d1,d2,d3;
  const double PI=acos(-1.);
  const double PI5=.5*acos(-1.);
  const double PI2=2.*PI;
  const double RAD=PI/180.;
  double **diagA,**diagB;
  double **xA,**xB;
  double dA=5.*RAD,dB=2.5*RAD;
  double a,b;
  long   *nA,*nB;
  long   i,j,n,m,k,l,kol,kolA;
  rect_t fillA,fillB,fillR,fillT;
  rect_t extent;
  int mode = grDETECT;
  char fontFileApp[]={"fix8x10b.fnt"};
  long maxx,maxy;
  DRAW_CH draw_winA,draw_winB;
  long keyAnt=0; // 0 - пеpедающие антенны
  long key=0,keyDiagr=0;
  const unsigned long kbEsc = 0x011B,
                      kbF2  = 0x3C00,
                      kbF1  = 0x3B00,
                      kbF10 = 0x4400;
  const char *at1[3]={"Isotropic",
                      "V-type for transmitter",
                      "Sausage for transmitter"};
  const char *at2[7]={"Isotropic",
                      "V-type for receiver",
                      "Sausage for receiver",
                      "Magnetic loop for receiver",
                      "BS for receiver",
                      "BS-2 for receiver",
                      "BS-3 for receiver"};
  const char otho[]=
  {"\nantenn.exe 1.2   Copyright(c) Vertogradov G.G. 1998\
  \n            tel (8632)359516, vgg@phys.rnd.runnet.ru\
  \n                      Rostov-on-Don, Russia\
  \n                     Rostov State University\
  \n                     RadioPhysics Departament\
  \n                        SIGNAL laboratory\
  \n                         tel (8632)223402\n"};
//===================================================================
  _clearscreen(_GCLEARSCREEN);
  printf("%s",otho);
  if (argc>1 && strcmp(*(argv+1),"con")!=0
             && strcmp(*(argv+1),"CON")!=0)
    in=fopen(*(argv+1),"rt");
  else
    in=stdin;

  if (!in)
    {
      printf("\nВОДНОЙ ФАЙЛ:%s НЕ ОТКРЫЛСЯ\n",*(argv+1));
      exit(EXIT_FAILURE);
    }

  if (argc>2 && strcmp(*(argv+2),"con")!=0
             && strcmp(*(argv+2),"CON")!=0)
    out=fopen(*(argv+2),"wt");
  else
    out=stdout;

  if (!out)
    {
      printf("\nВЫВОДНОЙ ФАЙЛ:%s НЕ ОТКРЫЛСЯ\n",*(argv+2));
      exit(EXIT_FAILURE);
    }

  get_ant(in,out,&tran,&rec);
  fscanf(in,"%ld",&keyAnt);
  fscanf(in,"%lg%lg",&dA,&dB);
  if (dA<2. || dB<1.)
    exit(EXIT_FAILURE);
  fscanf(in,"%lg%lg%lg",&fr,&ma,&psia);
  Ma=ma;
  Psia=psia;
  psia*=RAD;
  dA*=RAD;
  dB*=RAD;
  kol=PI5/dB;
  kolA=PI2/dA+1;
  nA=new long[kol];
  diagA=new double*[kol];
  xA=new double*[kol];
  for(i=0; i<kol; i++)
    {
      diagA[i]=new double[kolA];
      xA[i]=new double[kolA];
    }
  nB=new long[kolA];
  diagB=new double*[kolA];
  xB=new double*[kolA];
  for(i=0; i<kolA; i++)
    {
      diagB[i]=new double[kol];
      xB[i]=new double[kol];
      if (!xB[i])
        exit(EXIT_FAILURE);
    }

  while(fr>.0 && key!=kbEsc)
    {
      dc=initGraphics(mode);
      myColor(maxcol);
      //MGL_setBackColor(COLFON);
      MGL_setBackColor(BlueColor);
      MGL_clearDevice();
      maxx=MGL_maxx();
      maxy=MGL_maxy();
      MGL_getViewport(&extent);
      extent.left  +=10;
      extent.right -=10;
      extent.top   +=10;
      extent.bottom-=10;

      fillA=fillB=fillR=fillT=extent;
      fillA.right=extent.right-maxx/3;
      fillB.left=fillA.right+2;
      fillA.bottom=fillA.top+maxy/3;
      fillB.bottom=fillA.bottom;
      fillR.top=fillA.bottom+2;
      fillT.top=fillR.top;
      fillR.right=fillR.left+fillR.bottom-fillR.top;
      fillT.left=fillR.right+2;

      fontApp = MGL_loadFont(fontFileApp);
      if ( MGL_result() != grOK)
        {
          MGL_exit();
        }

      m=0;
      Max=.0;
      for(b=dB; b<PI5-dB,m<kol; b+=dB)
        {
          n=0;
          for(a=.0; a<PI2; a+=dA)
            {
              if (keyAnt)
                switch(rec.type)
                  {
                    case 0:
                      ku=1.;
                      break;
                    case 1:
                      rebeam(fr,b,ma,psia,rec.eps,rec.sig,rec.l,rec.h,rec.psi,-rec.fi+a,&knd);
                      ku=knd;
                      break;
                    case 2:
                      recant(fr,b,ma,psia,rec.eps,rec.sig,rec.l,rec.h,-rec.fi+a,&knd);
                      ku=knd;
                      break;
                    case 3:
                      loop(fr,b,ma,psia,rec.eps,rec.sig,rec.h,&knd);
                      ku=knd;
                      break;
                    case 4:
                    case 5:
                    case 6:
                      bs(rec.n,rec.l,rec.rs,rec.ll,rec.h,rec.eps,rec.sig,fr,b,-rec.fi+a,&d1,&d2,&d3);
                      if (rec.type==4)
                        knd=d1;
                      else
                        if (rec.type==5)
                          knd=d2;
                        else
                          knd=d3;
                      ku=knd;
                      break;
                  }
              else
                switch(tran.type)
                  {
                    case 0:
                      ku=1.;
                      break;
                    case 1:
                      ellips(fr,b,tran.eps,tran.sig,tran.l,tran.h,tran.psi,-tran.fi+a,&ma,&psia,&ku);
                      break;
                    case 2:
                      trant(fr,b,tran.eps,tran.sig,tran.l,tran.h,-tran.fi+a,&ma,&psia,&ku);
                      //recant(fr,b,ma,psia,rec.eps,rec.sig,rec.l,rec.h,rec.fi+a,&knd);
                      //ku=knd;
                      break;
                  }
              *(diagA[m]+n)=ku;
              if (Max<ku)
                {
                  k=m;
                  l=n;
                  Max=ku;
                  Ma=ma;
                  Psia=psia/RAD;
                }
              *(xA[m]+n)=a/RAD;
              n++;
            }
          nA[m]=n;
          m++;
        }

      for(i=0; i<m; i++)
        {
          for(j=0; j<n; j++)
            {
              *(diagA[i]+j)/=Max;
              *(diagB[j]+i)=*(diagA[i]+j);
              *(xB[j]+i)=dB*(i+1)/RAD;
              nB[j]=m;
            }
        }
      draw_winA.ir=1;
      draw_winA.kxr=10;
      draw_winA.kyr=10;
      draw_winA.ipgr=1;
      draw_winB.ir=1;
      draw_winB.kxr=10;
      draw_winB.kyr=10;
      draw_winB.ipgr=1;
      fildInit(.0,1.,.0,360.,draw_winA,"alfa,deg","A",fillA);
      fildInit(.0,1.,.0,90.,draw_winB,"beta,deg","A",fillB);
      //drawdgr(&xA[k],&diagA[k],&nA[k],.0,360.,.0,1.,fillA,draw_winA,1);
      drawdgr(xA,diagA,nA,.0,360.,.0,1.,fillA,draw_winA,kol);
      //drawdgr(&xB[l],&diagB[l],&nB[l],.0,90.,.0,1.,fillB,draw_winB,1);
      drawdgr(xB,diagB,nB,.0,90.,.0,1.,fillB,draw_winB,kolA);
      if (keyDiagr)
        drawSpace(fillR,dA/RAD,dB/RAD,diagA,m,n);
      else
        drawEll(fillR,&xA[k],&diagA[k],&nA[k],1);

      MGL_setViewport(fillT);
      MGL_setTextJustify(MGL_CENTER_TEXT,MGL_CENTER_TEXT);
      MGL_setWriteMode(MGL_REPLACE_MODE);
      MGL_setColor(COLFON);
      MGL_clearViewport();
      MGL_setColor(COLFRAME);
      long x,y;
      long ihw=MGL_textHeight();
      char str[256];
      x=MGL_maxx()/2;
      y=MGL_maxy()/2-10*ihw;

      if (keyAnt)
        sprintf(str,"%s",at2[rec.type]);
      else
        sprintf(str,"%s",at1[tran.type]);
      MGL_drawStrXY(x,y,str);
      y+=2*ihw;
      sprintf(str,"Fr=%5.2fMHz  a/b=%5.2f Psi=%6.1f",fr,Ma,Psia);
      MGL_drawStrXY(x,y,str);
      y+=2*ihw;
      sprintf(str,"Maximum Parametrs");
      MGL_drawStrXY(x,y,str);
      y+=2*ihw;
      sprintf(str,"Beta=%5.2f  Alfa=%6.2f  K=%5.1fdB",*(xB[0]+k),*(xA[k]+l),10.*log10(Max));
      MGL_drawStrXY(x,y,str);

      y+=8*ihw;
      sprintf(str,"F1 - Next frequency; F2 - switch of diagramm");
      MGL_drawStrXY(x,y,str);
      y+=2*ihw;
      sprintf(str,"F10 - save of diagramm; Esc - Exit");
      MGL_drawStrXY(x,y,str);

      while(!checkEvent() || (key=waitEvent())!=kbEsc)
        {
          if (key&0x00FF)
            key&=0x00FF;
          switch(key)
            {
              case kbF1:
                MGL_exit();
                fscanf(in,"%lg%lg%lg",&fr,&ma,&psia);
                Ma=ma;
                Psia=psia;
                psia*=RAD;
                break;
              case kbF2:
                keyDiagr^=0x1;
                if (keyDiagr)
                  drawSpace(fillR,dA/RAD,dB/RAD,diagA,m,n);
                else
                  drawEll(fillR,&xA[k],&diagA[k],&nA[k],1);
                key=0;
                break;
              case kbF10:
                saveBMP(0,0,maxx-1,maxy-1);
                key=0;
                break;
            }
          if (key==kbF1)
            {
              key=0;
              break;
            }
        }
    }

  for(i=0; i<kol; i++)
    {
      delete[] xA[i];
      delete[] diagA[i];
    }
  for(i=0; i<kolA; i++)
    {
      delete[] xB[i];
      delete[] diagB[i];
    }
  delete[] xA;
  delete[] diagA;
  delete[] xB;
  delete[] diagB;
  delete[] nA;
  delete[] nB;
}