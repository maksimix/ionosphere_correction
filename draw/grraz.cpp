
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "drawbase.h"

static
void grstan(double xmin, double xmax,
            long nx, long kr,
            double *zxmin, double *hzx,
            long *kxr,
            double *hx,
            long *kporx,
            double *xmin1,
            long *kx);

static
void khz1(double r, double *hzx, double *zxm,
          long *kxr1,
          double xi1, double xi2, double xa1);

static
void khz2(double r, double *hzx, double *zxm,
          long *kxr1,
          double xi1, double xi2, double xa1);

static
void khz3(double r, double *hzx, double *zxm,
          long *kxr1,
          double xi1, double xi2, double xa1);

long DrawBase::grraz(QPainter &p)
/***************************************************************/
/*                                                             */
/*             Функция оформляет поле графика                  */
/*                                                             */
/* ix          - абцисса в пикселях нижнего левого угла        */
/*               поля графика;                                 */
/* iy          - ордината в пикселях;                          */
/* xmin        - минимальное значение абциссы;                 */
/* xmax        - максимальное значение абциссы;                */
/* ymin        - минимальное значение ординаты;                */
/* ymax        - миаксимальное значение ординаты;              */
/* nx          - ширина в пикселях поля графика по оси абцисс; */
/* ny          - ширина поля в пикселях по оси ординат;        */
/* ir          - 0 - ставятся только риски по осям,            */
/*               1 - чертится координатная сетка;              */
/* krx         - количество точек разметки по оси x;           */
/* kry         - количество точек разметки по оси y;           */
/* ipgr        - 0 - рисуются только координатные оси,         */
/*               1 - рисуется рамка вокруг графика;            */
/* isim        - максимальная ширина символов оцифровки;       */
/* left        - левая граница графика;                        */
/* top         - верхняя граница графика;                      */
/* right       - правая граница графика;                       */
/* bottom      - нижняя граница графика;                       */
/* infx        - наименование величины, откладываемой по оси x;*/
/* infy        - наименование величины, откладываемой по оси y;*/
/* otst        - отступ в пикселях от верхнего канта поля      */
/*               графика.                                      */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  double zxmin,hx,xmin1,hzx,z,z1,
         zymin,hy,ymin1,hzy;
  long    mdx,mdy,isw,ihw,iy1,ix1,nrx,nry,
         kporx,kpory,lx,ly,i,j,mz,k,
         size=1,
         keyx=0,  // признак изменения длины оцифровки (удаляется порядок)
         keyy=0,
         kx,ky,isim,err,
         maxx,maxy,
         mx,my,   // число знаков после запятой
         userpat=1;
  //char   *prx;
  //char   *pry;
  QString prx, pry;

  char   rzm[80];
  QRect fullView;
  QPoint point;
  QPen pen=p.pen();

  QFont font("Arial",8);
  //==============================================================
  p.setFont(font);
  QFontMetrics fm(font);

  pen.setColor(colorText);
  pen.setWidth(1);
  p.setPen(pen);
  fullView=fildView;
  right =fullView.right();
  left  =fullView.left();
  top   =fullView.top();
  bottom=fullView.bottom();
  maxx=right-left;
  maxy=bottom-top;
  if (xmax==xmin || ymax==ymin)
    return 1;
  nrx=nx/krx;
  if (!nrx)
    {
      nrx=1;
      return 1;
    }
  nry=ny/kry;
  if (!nry)
   {
      nry=1;
      return 1;
   }
  grstan(xmin,xmax,nx,nrx,&zxmin,&hzx,&krx,&hx,&kporx,&xmin1,&kx);

  grstan(ymin,ymax,ny,nry,&zymin,&hzy,&kry,&hy,&kpory,&ymin1,&ky);

  if (zxmin<.0)
    {
      kx++;
      mx=kx-3; // число цифр после запятой в оцифровке
    }
  else
    mx=kx-2;
  if (zymin<.0)
    {
      ky++;
      my=ky-3; // число цифр после запятой в оцифровке
    }
  else
    my=ky-2;

  if (kporx && abs(kporx)<4)
    { // число цифр после запятой в оцифровке изменяется
      keyx=1;
      if (kporx>0)
        if (mx<=kporx-1)
          {
            kx+=kporx-mx-1;
            mx=0;
          }
        else
          mx-=kporx;
      else
        {
          kx-=kporx;
          mx-=kporx;
        }
    }
  if (kpory && abs(kpory)<4)
    { // число цифр после запятой в оцифровке изменяется
      keyy=1;
      if (kpory>0)
        if (my<=kpory-1)
          {
            ky+=kpory-my-1;
            my=0;
          }
        else
          my-=kpory;
      else
        {
          ky-=kpory;
          my-=kpory;
        }
    }
  mdx=1;
  isw=fm.width('0');
  ihw=fm.height();

  isim=nx/((kx+1)*krx);
  while (isim<isw)
    {
      mdx++;
      isim=mdx*nx/((kx+1)*krx); /* ширина символов в пикселях */
    }

  mdy=1;
  isim=ny/kry;
  while (isim<ihw)
   {
      mdy++;
      isim=mdy*ny/kry;
    }

  iy1=ky*isw+ihw+2; /* отступ по x */
  //if (iy1<fm.width(infy))
  //    iy1=fm.width(infy);
  ix1=2*ihw;        /* отступ по y */

  if (iy1<otstBegX)
      iy1=otstBegX;
  if (ix1<otstBegY)
      ix1=otstBegY;

  if (maxy-iy<ix1) iy=maxy-ix1;
  if (maxy-iy+ny>maxy) ny=iy;
  if (ix<iy1) ix=iy1;
  if (ix+nx>maxx) nx=maxx-ix;
  left=ix-iy1;
  top=iy-ny;
  right=ix+nx;
  bottom=iy+ix1;

  if (kporx && !keyx)
  {
      lx=log10((double)labs(kporx))+1;
      //prx=new char[strlen(infx)+lx+5];
      prx.sprintf( "*10%+*d", lx, kporx );
      prx = infx + prx;
  }
  else
  {
      //prx=new char[strlen(infx)+1];
      //sprintf(prx,"%s",infx);
      prx = infx;
  }

  if (kpory && !keyy)
  {
      ly=log10((double)labs(kpory))+1;
      //pry=new char[strlen(infy)+ly+5];
      pry.sprintf( "*10%+*d", ly, kpory );
      pry = infy + pry;
  }
  else
  {
      //pry=new char[strlen(infy)+1];
      //sprintf(pry,"%s",infy);
      pry = infy;
  }
  ///////////////////////////
  pen.setColor(colorText);
  pen.setWidth(1);
  p.setPen(pen);  
  double angle=-90.;
  ly=fm.width(pry);
  ly=iy-ny+ly;
  lx=ix-iy1+fm.ascent();
  p.translate(lx,ly);
  p.rotate(angle);
  p.drawText(0,0,pry); ////////

  angle=90.;
  p.rotate(angle);
  p.translate(-lx,-ly);
  lx=fm.width(prx);
  lx=ix+nx-lx;
  ly=iy+ix1-fm.ascent()/2;
  p.drawText(lx,ly,prx);
  ////////////////////////
  /*
  pen.setColor(colorText);
  pen.setWidth(1);
  p.setPen(pen);
  ly=iy-ny+fm.ascent();
  lx=fm.ascent()/2;
  lx=0;
  p.drawText(lx,ly,pry); ////////

  lx=fm.width(prx);
  lx=ix+nx-lx;
  ly=iy+ix1-fm.ascent()/2;
  p.drawText(lx,ly,prx);
  */
  pen.setColor(colorAxe);
  pen.setWidth(1);
  p.setPen(pen);  

  p.drawLine(ix,iy,ix+nx,iy); /* ось абцисс  */
  p.drawLine(ix,iy,ix,iy-ny); /* ось ординат */

  if (ipgr==1)
    {
      p.drawLine(ix,iy-ny,ix+nx-1,iy-ny);  /* окантовка графика */
      p.drawLine(ix+nx-1,iy-ny,ix+nx-1,iy);
    }

  /* РАЗМЕТКА ОСИ X */

  for(i=0; i<krx; i++)
    if (mdx==1 || mdx>1 && i%mdx==0)
      {
        z=zxmin+hzx*i;
        mz=(nx-otst)*(zxmin+hzx*i-xmin1)/hx;
        if (keyx)
          {
            z1=z;
            j=0;
            while(j<abs(kporx))
              {
                if (kporx>0)
                  z1*=10.;
                else
                  z1/=10.;
                j++;
              }
            sprintf(rzm,"%*.*f",kx,mx,z1);
          }
        else
          sprintf(rzm,"%*.*f",kx,mx,z);

        ly=iy+ihw+4;
        lx=mz+ix;

        if (lx+(kx*isw+1)/2<maxx)
          {
            for(k=0; *(rzm+k)==' '; k++); // удаление незначащих нулей
            pen.setColor(colorText);
            pen.setWidth(1);
            p.setPen(pen);            
            p.drawText(lx-fm.width(rzm+k)/2,ly-fm.ascent()/2,(rzm+k));
          }
        if (ir==1)
          {
              pen.setColor(colorAxe);
              pen.setWidth(1);
              p.setPen(pen);              
              p.drawLine(lx,iy+2,lx,iy);
              if (lx!=ix)
              {
                  pen.setColor(colorSetka);
                  pen.setWidth(1);
                  p.setPen(pen);              
                  p.drawLine(lx,iy-1,lx,iy-ny+1);
              }
          }
        else
          {
              pen.setColor(colorAxe);
              pen.setWidth(1);
              p.setPen(pen);              
              p.drawLine(lx,iy+2,lx,iy);
          }
      }

  /* РАЗМЕТКА ОСИ Y */

  lx=ix-iy1+ihw;

  for(i=0; i<kry; i++)
    if (mdy==1 || mdy>1 && i%mdy==0)
      {
        z=zymin+hzy*i;
        mz=(ny-otst)*(zymin+hzy*i-ymin1)/hy;
        if (keyy)
          {
            z1=z;
            j=0;
            while(j<abs(kpory))
              {
                if (kpory>0)
                  z1*=10.;
                else
                  z1/=10.;
                j++;
              }
            sprintf(rzm,"%*.*f",ky,my,z1);
          }
        else
          sprintf(rzm,"%*.*f",ky,my,z);
        ly=iy-mz;

        if (ly-ihw>top)
          {
            for(k=0; *(rzm+k)==' '; k++); // удалуние незначащих нулей
            pen.setColor(colorText);
            pen.setWidth(1);
            p.setPen(pen);            
            //p.drawText(lx,ly+fm.ascent()/2,rzm);

            int rzm_X = ky*isw+ihw+2;
            if( rzm_X < otstBegX )
                rzm_X = otstBegX;
            p.drawText(/*lx*/rzm_X-fm.width(rzm)-4, ly+fm.ascent()/2,rzm);
          }
        if (ir==1)
          {
              pen.setColor(colorAxe);
              pen.setWidth(1);
              p.setPen(pen);              
              p.drawLine(ix-2,ly,ix,ly);
              if (ly!=iy)
              {
                  pen.setColor(colorSetka);
                  pen.setWidth(1);
                  p.setPen(pen);              
                  p.drawLine(ix+1,ly,ix+nx-2,ly);
              }
          }
        else
          {
              pen.setColor(colorAxe);
              pen.setWidth(1);
              p.setPen(pen);              
              p.drawLine(ix-2,ly,ix,ly);
          }
      }

  ny -=otst; /* отступили от верха на otst пикселей */
  nx -=otst; /* отступили справа на otst пикселей   */
//  MGL_unloadFont(font);
  //delete[] prx;
  //delete[] pry;
  return 0      ;
} /* grraz */

static
void grstan(double xmin, double xmax,
            long nx, long kr,
            double *zxmin, double *hzx,
            long *kxr,
            double *hx,
            long *kporx,
            double *xmin1,
            long *kx)
/***************************************************************/
/*                                                             */
/* xmin   - минимальное значение;                              */
/* xmax   - максимальное значение;                             */
/* nx     - длина в пикселях;                                  */
/* kr     - расстояние в пиксилях между линиями разметки;      */
/* zxmin  - минимальная точка разметки с удаленным порядком;   */
/* hzx    - шаг между линиями разметки с удаленным порядком;   */
/* kxr    - число линий разметки;                              */
/* hx     - полная вариация значений с удаленным порядком;     */
/* kporx  - порядок нормировки;                                */
/* xmin1  - минимальное значение с удаленным порядком;         */
/* kx     - число знаков в оцифровке оси.                      */
/*                                                             */
/* VGG                                                         */
/***************************************************************/
{
  double xmin2,xmax2,par,xmax1;
  const double l10=log(10.);
  long    kx1,kx2,kxr0,kxr1,kdop;

  kx1=(xmax==.0)? 0 : floor(log10(fabs(xmax)));
  kx2=(xmin==.0)? 0 : floor(log10(fabs(xmin)));
  *kporx=(kx2>kx1)? kx2 : kx1;

  par=exp(-l10**kporx);
  *xmin1=xmin*par;
  xmax1=xmax*par;
  *kx=0;
  par=exp(l10*(1-*kx));
  xmin2=xmax2=.0;
  while (xmax2-xmin2<1.5*par)
    {
      (*kx)++;
      par=exp(l10*(1-*kx));
      xmin2=ceil(*xmin1/par)*par;
      xmax2=ceil(xmax1/par)*par;
    }
  *hzx=par;
  *kxr=(xmax2-xmin2)/par-.5;
  kxr0=nx/kr;
  kxr1=*kxr;
  *zxmin=xmin2;
  kdop=1+(kxr0-2)/3;
  kxr0 +=kdop;
  if (*kxr>=kxr0)
    if (*xmin1*xmax1<.0)
      {
        khz2(2.,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
        if (kxr1>kxr0)
          khz2(2.,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
      }
    else
      {
        khz3(2.,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
        if (kxr1>kxr0)
          khz3(2.5,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
      }
  kxr0 -=2*kdop;
  if (*kxr<=kxr0)
    while (kxr1<kxr0)
      {
        khz1(.5,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
        if (kxr1<kxr0)
          khz1(.4,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
        if (kxr1<kxr0)
          khz3(2.5,hzx,zxmin,&kxr1,*xmin1,xmin2,xmax1);
      }
  *kxr=kxr1;
  if (fabs(*zxmin-*xmin1)<.1e-16) *zxmin +=*hzx;
  *kx=2.5-floor(log10(*hzx));
  while (*zxmin-*xmin1>*hzx)
    {
      *zxmin -=*hzx;
      (*kxr)++;
    }
  if (xmax1-*zxmin-(*kxr-1)**hzx<=.0) (*kxr)--;
  *hx=xmax1-*xmin1;
  return;
} /* grstan */

static
void khz1(double r, double *hzx, double *zxm,
          long *kxr1,
          double xi1, double xi2, double xa1)
{
  *hzx *=r;
  *zxm=xi2+*hzx*ceil((xi1-xi2)/ *hzx);
  *kxr1=ceil((xa1-*zxm)/ *hzx)+.5;
  return;
} /* khz1 */

static
void khz2(double r, double *hzx, double *zxm,
          long *kxr1,
          double xi1, double xi2, double xa1)
{
  *hzx *=r;
  *zxm=xi2+fmod(fabs(xi2+1.),*hzx);
  *kxr1=ceil((xa1-*zxm)/ *hzx);
  return;
} /* khz2 */

static
void khz3(double r, double *hzx, double *zxm,
          long *kxr1,
          double xi1, double xi2, double xa1)
{
  *hzx *=r;
  *zxm=*hzx+xi2;
  *kxr1=ceil((xa1-*zxm)/ *hzx);
  return;
} /* khz3 */



