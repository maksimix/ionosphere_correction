using namespace std;
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
//#include <sys/time.h>
#include "paths.h"
//#include "..\draw\draw.h"

extern double Vx, Vy, Vz;

void sopr1(double  f1, double  h1, double  *y1,
           double df1, double dh1, double *dy1,
           double  f2, double  h2, double   y2,
           double df2, double dh2, double  dy2,
           double *h12, double *dh12,
           int key);

void sopr2(double  f1, double  h1, double  y1,
           double df1, double dh1, double dy1,
           double  f2, double  *h2, double  *y2,
           double df2, double *dh2, double *dy2,
           double  f3, double  h3, double  y3,
           double df3, double dh3, double dy3,
           double *h12, double *h23,
           double *dh12, double *dh23,
           int     key);

int  sopr3(double f1, double h1, double y1,
           double df1, double dh1, double dy1,
           double *f2, double *h2, double *y2,
           double *df2, double *dh2, double *dy2,
           double f3, double h3, double y3,
           double df3, double dh3, double dy3,
           double h12, double dh12,
           double *h23, double *dh23,
           int    key);

int ionos(double f, double t, double r,
          int    n);

double inions(FILE    *in,
              FILE    *out,
              int     iyear,
              double  ames,
              double  &w,
              double  &ig,
              double  rmax,
              long    keyvod,
              long    keyMod,
              long    keyes,
              double  tBeg,
              double  tEnd,
              double  tStep)
/***************************************************************/
/* Функция предназначена для организации прогноза и построения */
/* пространственного распределения ионизаци, при условии,      */
/* что высотный профиль удовлетворяет модели ИРИ               */
/*                                                             */
/*  ames   - месяц;                                            */
/*  w      - солнечная активность (пятна, поток или год);      */
/*  keyMod - 1 - прогноз профиля в соответствии с моделью CCIR,*/
/*           0 - прогноз URSI;                                 */
/*  keyvod - 0 - прогноз;                                      */
/*           1 - ввод параметров слоев вдоль трассы;           */
/*           2 - коррекция ионосферных параметров по данным ВЗ */
/*               в одной пространственной точке                */
/*  keyes  - 0 - прогноз параметров Es-слоя вдоль трассы,      */
/*           1 - ввод параметров Es-слоя вдоль трассы,         */
/*          -1 - Es-слой не учитывается;                       */
/*  keyl2  - 0 - прогноз на 2.2                                */
/*           1 - ввод параметров                               */
/*          -1 - прогноз ИРИ                                   */
/*                                                             */
/*VGG 09.02.2005                                               */
/***************************************************************/
/***************************************************************/
/*                                                             */
/*      ФУНКЦИМЯ ВВОДА ИОНОСФЕРНОЙ ИНФОРМАЦИИ.                 */
/*                                                             */
/*      ИМЕЕТСЯ ВОЗМОЖНОСТЬ ИПОЛЬЗОВАТЬ НЕСКОЛЬКО ИОНОСФЕРНЫХ  */
/*      МОДЕЛЕЙ:                                               */
/*        - ОДНОСЛОЙНАЯ ПАРАБОЛИЧЕСКАЯ;                        */
/*        - ПРОФИЛЬ ЗАДАЕТСЯ ПО ТОЧКАМ С РАЗЛИЧНЫМИ            */
/*          ГРАНИЧНЫМИ УСЛОВИЯМИ;                              */
/*                                                             */
/*      ПОДПРОГРАММА ДАЕТ ВОЗМОЖНОСТЬ ВВОДИТЬ ЛИНЕЙНЫЙ ПО      */
/*      КРИТИЧЕСКОЙ ЧАСТОТЕ РЕГУЛЯРНЫЙ ГРАДИЕНТ, А ТАКЖЕ       */
/*      МОДЕЛИРОВАТЬ ГАРМОНИЧЕСКИЕ ВОЛНОВЫЕ ВОЗМУЩЕНИЯ.        */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  double grana,granb,
         alam[3],t[3],a[3],b[3];
  long month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  int    i,npoint,key;
  GRAN   gran;

  long n[1];

  gx=gy=.0;
  fiIon0=fi0; tetaIon0=teta0;

  fscanf(in,"%d",&koltid);
  //printf("\nkoltid=%d",koltid);

  if (koltid<0  ||  koltid>3)
    {
      printf("\n*inionp Error input TID number");
      exit(EXIT_FAILURE);
    }

   if (koltid>0)
     {
       for(i=0; i<koltid; i++)
         fscanf(in,"%lg%lg%lg%lg%lg%lg",
                   &de[i],&alam[i],&t[i],&b[i],&a[i],&fit[i]);

       fprintf(out,"\nNumber TID:%2d",koltid);

       fprintf(out,"\nTid Parametres");
       fprintf(out,"\n  delt   lamb     t     b      a     fi");

       for(i=0; i<koltid; i++)
         fprintf(out,"\n%5.3f%8.1f%6.1f%6.1f%7.1f%8.3f",
                     de[i],alam[i],t[i],b[i],a[i],fit[i]);

       for(i=0; i<koltid; i++)
         {
           if (de[i]<.0       || de[i]>4.         ||
               alam[i]<1.     || alam[i]>5000000. ||
               t[i]<1.        || t[i]>10800.      ||
               fabs(b[i])>90. || fabs(a[i])>180.  ||
               fabs(fit[i])>180.)
             {
               printf("\n*inionp Error TID parametres");
               exit(EXIT_FAILURE);
             }

           om[i]=2.*PI/t[i];
           b[i]  *=RAD;
           a[i]  *=RAD;
           fit[i]*=RAD;
           pr[i]= 200.*PI*sin(b[i])/alam[i];
           pt[i]=-200.*PI*cos(b[i])*cos(a[i])/alam[i];
           pf[i]= 200.*PI*cos(b[i])*sin(a[i])/alam[i];
         }
     }

  fscanf(in,"%d%d",&keyFsp,&keyZat);

  printf("1 keyZat=%d\n",keyZat);

  if (keyZat)
  {
      FILE *inZ=fopen("zatm_29032006.dat","rt");;

      latCzat=new double[keyZat];
      lonCzat=new double[keyZat];
      timCzat=new double[keyZat];
      double *latCzat1=new double[keyZat];
      double *lonCzat1=new double[keyZat];
      double *latCzat2=new double[keyZat];
      double *lonCzat2=new double[keyZat];

      char str[256];
      int hh,mm;
      double gr,min;
      fgets(str,256,inZ);
      fgets(str,256,inZ);
      fgets(str,256,inZ);
      fgets(str,256,inZ);
      fgets(str,256,inZ);
      keyZat=0;
      for(int i=0; !feof(inZ); i++)
      {
          keyZat++;
          printf("2 keyZat=%d\n",keyZat);
          printf("%s\n",str);
          sscanf(str+1,"%d",&hh);
          sscanf(str+4,"%d",&mm);
          timCzat[i]=(double)hh*3600.+(double)mm*60.;
          sscanf(str+48,"%lg",&gr);
          sscanf(str+52,"%lg",&min);
          latCzat[i]=(gr+min/60.);
          sscanf(str+58,"%lg",&gr);
          sscanf(str+62,"%lg",&min);
          lonCzat[i]=(gr+min/60.);
          sscanf(str+9,"%lg",&gr);
          sscanf(str+12,"%lg",&min);
          latCzat1[i]=(gr+min/60.);
          sscanf(str+18,"%lg",&gr);
          sscanf(str+22,"%lg",&min);
          lonCzat1[i]=(gr+min/60.);
          sscanf(str+29,"%lg",&gr);
          sscanf(str+32,"%lg",&min);
          latCzat2[i]=(gr+min/60.);
          sscanf(str+38,"%lg",&gr);
          sscanf(str+42,"%lg",&min);
          lonCzat2[i]=(gr+min/60.);
          //printf("hh=%f  lat=%f  lon=%f",timCzat[i],latCzat[i],lonCzat[i]);
          fgets(str,256,inZ);
      }
      fclose(inZ);
      FILE *outZ;
      outZ=fopen("zatm_29032006_0.dat","wt");;
      fprintf(outZ,"%5d\n",keyZat);
      for(int i=0; i<keyZat; i++)
          fprintf(outZ,"%8.3f  %8.3f\n",latCzat[i],lonCzat[i]);
      fclose(outZ);
      outZ=fopen("zatm_29032006_1.dat","wt");;
      fprintf(outZ,"%5d\n",keyZat);
      for(int i=0; i<keyZat; i++)
          fprintf(outZ,"%8.3f  %8.3f\n",latCzat1[i],lonCzat1[i]);
      fclose(outZ);
      outZ=fopen("zatm_29032006_2.dat","wt");;
      fprintf(outZ,"%5d\n",keyZat);
      for(int i=0; i<keyZat; i++)
          fprintf(outZ,"%8.3f  %8.3f\n",latCzat2[i],lonCzat2[i]);
      fclose(outZ);
      delete[] latCzat1;
      delete[] latCzat2;
      delete[] lonCzat1;
      delete[] lonCzat2;
  }

  if (keyFsp>0)
  {
      double lat_0;
      double A[3][3],x[3],y[3],z[3];
      double alfa0,beta0,cAlfa0,sAlfa0,cBeta0,sBeta0;
      fscanf(in,"%lg%lg%lg%lg%lg%lg%lg%lg%lg",&delta0,&r_0,&fi_0,&lat_0,&beta0,&alfa0,&aX,&aY,&aZ);
      fprintf(out,"\ndelta=%5.3f  r0=%6.1f  lon=%8.3f lat=%8.3f",delta0,r_0,fi_0,lat_0);
      fprintf(out,"\nBeta=%6.1f  Alfa=%6.1f aX=%6.1f aY=%6.1f aZ=%6.1f\n",beta0,alfa0,aX,aY,aZ);
    
      r_0=R0+r_0*.01;
      teta_0=RAD*(90.-lat_0);
      fi_0*=RAD;
      aX*=.01;
      aY*=.01;
      aZ*=.01;
      beta0*=RAD;
      alfa0*=RAD;
      sAlfa0=sin(alfa0);
      cAlfa0=cos(alfa0);
      sBeta0=sin(beta0);
      cBeta0=cos(beta0);
      A[0][0]=-sin(teta_0); A[0][1]=-cos(teta_0)*cos(fi_0); A[0][2]=sin(teta_0)*cos(fi_0);
      A[1][0]= cos(teta_0); A[1][1]=-cos(teta_0)*sin(fi_0); A[1][2]=sin(teta_0)*sin(fi_0);
      A[2][0]= .0;          A[2][1]= sin(teta_0);           A[2][2]=cos(teta_0);
      x[0]=cAlfa0; x[1]=-sAlfa0; x[2]=.0;
      y[0]=cBeta0*sAlfa0;  y[1]=cBeta0*cAlfa0;  y[2]=sBeta0;
      z[0]=-sBeta0*sAlfa0; z[1]=-sBeta0*cAlfa0; z[2]=cBeta0;
      rx_0=r_0*sin(teta_0)*cos(fi_0);
      ry_0=r_0*sin(teta_0)*sin(fi_0);
      rz_0=r_0*cos(teta_0);

      for(int i=0; i<3; i++)
      {
          kx_0[i]=ky_0[i]=kz_0[i]=.0;
          for(int j=0; j<3; j++)
          {
              kx_0[i]+=A[i][j]*x[j];
              ky_0[i]+=A[i][j]*y[j];
              kz_0[i]+=A[i][j]*z[j];
          }
      }
  }
  else
  {
      rx_0=ry_0=rz_0=.0;
      aX=aY=aZ=1.;
      delta0=.0;
      for(int i=0; i<3; i++)
          kx_0[i]=ky_0[i]=kz_0[i]=.0;
  }

  fscanf(in,"%d",&keyOval);
  fi_m0=-110.8*RAD;
  teta_m0=(90.-81.3)*RAD;
  //fi_m0=.0*RAD;
  //teta_m0=(90.-90.)*RAD;
  steta_m0=sin(teta_m0);
  cteta_m0=cos(teta_m0);
  if (keyOval>0)
  {
      fi0_inv=90.;
      amp_proval=.0;
      lambd1=20.;
      lambd1=5.;
      fscanf(in,"%lg%lg%lg%lg%lg%lg%lg%lg",&fi0_inv,&amp_proval,&amp_proval1,&lambd1,&lambd2,&lambd3,&lambd4,&lambd5);
      ro_m=R0*(PI05-RAD*fi0_inv);
      lambd1*=.01;
      lambd2*=.01;
      lambd3*=.01;
      lambd4*=.01;
      lambd5*=.01;
  }

  fscanf(in,"%d",&mod);

  //printf("\nmod=%d",mod);
  if (mod<=0 || mod>10)
  {
      printf("\n*inionp Error type ionospher model");
      exit(EXIT_FAILURE);
  }
  if (mod<10)
  {
      switch (mod)
      {

          case 1: fprintf(out,"\nParabolic Ionospher Model with line gradient");
   
                  fscanf(in,"%lg%lg%lg",&f0,&hm,&ym);
   
                  if (hm<100. || hm>600. || ym<1. ||
                      ym>400. || f0<.0   || f0>20.)
                    {
                      printf("\n*inionp Error input ionospher model parametres");
                      exit(EXIT_FAILURE);
                    }
   
                  fprintf(out,"\nGeometric Layer Parametres");
                  fprintf(out,"\n hm=%6.1f  ym=%6.1f  f0=%5.2f",hm,ym,f0);
   
                  hm=hm*.01+R0;
                  HmF2=hm;
                  HmF1=HmE=HmD=HmEs=.0;
   
                  ym *=.01;
                  h0=hm-ym;
                  f02=f0*f0;
                  break;
   
          case 2: fprintf(out,"\nChapmen many-layers Ionospher model");
   
                  fscanf(in,"%d",&klay);
   
                  if (klay<1 || klay>5)
                    {
                      printf("\n*inionp Error input number layers");
                      exit(EXIT_FAILURE);
                    }
   
                  fscanf(in,"%lg",&h0);
   
                  if (h0<.0 || h0>900.)
                    {
                      printf("\n*inionp Error input Begin Higth");
                      exit(EXIT_FAILURE);
                    }
   
                  fprintf(out,"\nIonospher Begin Higth:%5.1f",h0);
   
                  for(i=0; i<klay; i++)
                    {
                      fscanf(in,"%lg%lg%lg%lg",&fl[i],&hl[i],&yl[i],&al[i]);
   
                      if (fl[i]<.0 || fl[i]>20.  ||
                          hl[i]<h0 || hl[i]>900. ||
                          yl[i]<1. || yl[i]>400. ||
                          al[i]<.0 || al[i]>100.)
                         {
                           printf("\n*inions Error input ionospher model parametres");
                           exit(EXIT_FAILURE);
                         }
                    }
   
                  f0=fl[klay-1];
                  fprintf(out,"\nNumber Layers:%2d",klay);
                  fprintf(out,"\nGeometric Layer Parametres");
                  fprintf(out,"\n  hm     ym     f0     al");
                  for(i=0; i<klay; i++)
                    {
                      fprintf(out,"\n%5.1f  %5.1f  %5.2f   %4.2f",
                                  hl[i],yl[i],fl[i],al[i]);
   
   
                      fl[i] *=fl[i];
   
                      hl[i]=hl[i]*.01+R0;
   
                      yl[i] *=.01;
                    }
   
                  hm=hl[klay-1];
   
                  h0=h0*.01+R0;
   
                  gx=.0;
                  gy=.0;
   
                  i=koltid;
                  koltid=0;
                  par=.0;
                  fr=1.;
                  fr2=1.;
                  ionos(.0,.0,h0,6);
                  par=v;
                  koltid=i;
                  break;
   
          case 3: fscanf(in,"%d",&klay);
   
                  if (klay<1 || klay>7)
                    {
                      printf("\n*inions Error input number layers");
                      exit(EXIT_FAILURE);
                    }
   
                  for(i=0; i<klay; i +=2)
                    {
                      fscanf(in,"%lg%lg%lg",&fl[i],&hl[i],&yl[i]);
   
                      if (fl[i]<.0 || fl[i]>20.  ||
                          hl[i]>900. ||
                          yl[i]<1. || yl[i]>400.)
                         {
                           printf("\n*inions Error input ionospher model parametres");
                           exit(EXIT_FAILURE);
                         }
                      hl[i]  =hl[i]*.01+R0;
                      yl[i] *=.01;
                    }
   
                  h0=hl[0]-yl[0];
                  f0=fl[klay-1];
                  hm=hl[klay-1];
                  al[klay-1]=hm;
   
                  fscanf(in,"%lg",&fl[3]);
   
                  if (fl[3]>fl[2] || fl[3]<.0)
                    {
                      printf("\n*inions Error input depth E-F layer");
                      exit(EXIT_FAILURE);
                    }
   
                  al[0]=hl[0];
                  fl[1]=fl[0];
                  hl[1]=hl[0];
   
                  sopr1(fl[1],hl[1],&yl[1],0,0,0,
                        fl[2],hl[2],yl[2],0,0,0,
                        &al[1],0,0);
   
                  if (klay==7)
                    {
                      al[4]=hl[4];
                      al[6]=hl[6];
                      if (sopr3(fl[4],hl[4],yl[4],0,0,0,
                                &fl[5],&hl[5],&yl[5],0,0,0,
                                fl[6],hl[6],yl[6],0,0,0,
                                al[4],0,&al[5],0,0))
                        {
                          klay=5;
                          fl[4]=fl[6];
                          hl[4]=hl[6];
                          yl[4]=hl[6];
                          al[4]=hl[6];
                        }
                    }
   
                  if (fl[3]<fl[2])
                    sopr2(fl[2],hl[2],yl[2],0,0,0,
                          fl[3],&hl[3],&yl[3],0,0,0,
                          fl[4],hl[4],yl[4],0,0,0,
                          &al[2],&al[3],0,0,0);
                  else
                    {
                      hl[3]=hl[2];
                      al[2]=hl[2];
                      sopr1(fl[3],hl[3],&yl[3],0,0,0,
                            fl[4],hl[4],yl[4],0,0,0,
                            &al[3],0,0);
                    }
   
                  fprintf(out,"\nNumber Layers:%2d",klay);
                  fprintf(out,"\nGeometric Layer Parametres");
                  fprintf(out,"\n  hm     ym     f0     hh");
                  for(i=0; i<klay; i++)
                    {
                      fprintf(out,"\n%5.1f  %5.1f  %5.2f  %5.1f",
                                  (hl[i]-R0)*100.,yl[i]*100.,fl[i],
                                  (al[i]-R0)*100.);
   
                      fl[i] *=fl[i];
                    }
   
                  break;
   
          case 4:
   
          case 5:
   
          case 6: fscanf(in,"%d",&npoint);
   
                  if (npoint<2 || npoint>100)
                     {
                        printf("\n*inionp Error input  N(h)-profil number points");
                        exit(EXIT_FAILURE);
                     }
   
                  for(i=0; i<npoint; i++)
                    {
                      fscanf(in,"%lg%lg",&hpl[i],&fpl[i]);
   
                      if (fpl[i]<.0 || fpl[i]>20. ||
                          hpl[i]<.0 || hpl[i]>1000.)
                        {
                          printf("\n*inionp Error input point-profil");
                          exit(EXIT_FAILURE);
                        }
                    }
   
                  fprintf(out,"\nPoints N(h)-profil");
   
                  for(i=0; i<npoint; i++)
                    {
                      if (i%10==0) fprintf(out,"\n");
                      fprintf(out,"%6.1f%6.2f",hpl[i],fpl[i]);
                    }
   
                  f0=fpl[npoint-1];
   
                  for(i=0; i<npoint; i++)
                    {
                      fpl[i] *=fpl[i];
   
                      hpl[i]=hpl[i]*.01+R0;
                    }
   
                  hm=hpl[npoint-1];
                  h0=hpl[0];
                  par=fpl[0];
   
                  fscanf(in,"%d%lg%lg",&key,&grana,&granb);
   
                  if (key<0 || key>4)
                    {
                      printf("\n*inionp Error input border conditions");
                      exit(EXIT_FAILURE);
                    }
   
                  fprintf(out,"\nBorder condition Type:%1d  grana=%12.5gl granb=%12.5gl",
                          key,grana,granb);
                  /* grana и granb - значения первых или вторых производных  */
                  /*                 квадрата плазменной частоты на границах */
                  /*                 заданного по точкам профиля.            */
   
                  switch (key)
                    {
   
                      case 1: grana *=100.;
                              granb *=100.;
                              gran=DxDx;
                              break;
   
                      case 2: grana *=10000.;
                              granb *=10000.;
                              gran=D2xD2x;
                              break;
   
                      case 3: grana *=100.;
                              granb *=10000.;
                              gran=DxD2x;
                              break;
   
                      case 4: grana *=10000.;
                              granb *=100.;
                              gran=D2xDx;
                    }
   
                  spN_H=new SPCUB(npoint,grana,granb,gran);
                  for(i=0; i<npoint; i++)
                  {
                      spN_H->setCarrierX(hpl[i],i);
                      spN_H->setCarrier(fpl[i],i);
                  }
                  
                  if (spN_H->form())
                    {
                      printf("\n*inionp Error N(h)-profil approximate");
                      exit(EXIT_FAILURE);
                    }
   
                  break;
      }

      fMin=f0;

      fscanf(in,"%lg%lg",&gx,&gy);

      if (fabs(gx)>1. || fabs(gy)>1.)
        {
          printf("\n*inionp Error input local gradient");
          exit(EXIT_FAILURE);
        }
   
   
      fprintf(out,"\nLocal Gradient  gx=%4.2f  gy=%4.2f",gx,gy);

      gx= gx*R0/f0;
      gy=-gy*R0/f0;
  }
  else
  {
      // реальный профиль, заданный моделью IRI с учетом его линейной динамики во времени
      int    imonth, iday;
      double time, time2;
      double zmin=H0,
             dz=DZ;
      double W,IG;
      long nx=NX, ny=NY, nz=NZ;
      double latIon,lonIon,f0E,hmE,f0F1,hmF1,f0F2,hmF2,f0Es,hmEs,tIon;
      long   it,hou,min,sek;
      double latIon0,lonIon0;


      fscanf(in,"%lg%lg",&lonIon0,&latIon0);
      fiIon0=lonIon0*RAD; tetaIon0=(90.-latIon0)*RAD;

      if (keyvod==2)
      {
          fscanf(in,"%lg%lg%ld%lg%lg%lg%lg%lg%lg%lg%lg",&lonIon,&latIon,&it,&f0Es,&hmEs,&f0E,&hmE,&f0F1,&hmF1,&f0F2,&hmF2);
          hou=it/10000l;
          min=(it-hou*10000l)/100l;
          sek=it-hou*10000l-min*100l;
          tIon=hou+(min+sek/60.)/60.+25.;
          cout<<endl<<"f0F2="<<f0F2<<"  hmF2="<<hmF2<<flush;
      }

      W=w;
      IG=ig;

      imonth=(long)ames;
      iday=(long)(month[imonth-1]*(ames-imonth)+.5);

      tim=tBeg;
      if (tBeg<.0)
        tBeg+=86400.;
      tBeg/=3600.; /* Гринвичское время в часах */
      while(tBeg>24.) tBeg-=24.;
      while(tBeg<.0)  tBeg+=24.;
      time=tBeg+25.; // всемирное время для программы iris13
      if (tEnd<.0)
        tEnd+=86400.;
      tEnd/=3600.; /* Гринвичское время в часах */
      while(tEnd>24.) tEnd-=24.;
      while(tEnd<.0)  tEnd+=24.;
      time2=tEnd+25.; // всемирное время для программы iris13

      //printf("\ntime=%f time2=%f iyear=%d imonth=%d iday=%d",time,time2,iyear,imonth,iday);

      iri_3dbase = new IRI_3D(lonIon0, latIon0, rmax, zmin, dz, nx, ny, nz); // основной профиль

      iri_3dbase->setYear(iyear);
      iri_3dbase->setDay(imonth*100+iday);
      iri_3dbase->setTime(time);
      iri_3dbase->setKeyEs((keyes!=-1));
      if (keyMod)
          iri_3dbase->setCCIR();
      else
          iri_3dbase->setURSI();
      if (fabs(W)>.0001)
      {
          //printf("\nW1=%f",W); 
          iri_3dbase->setSunActiv(W);
      }
      if (IG>.0)
      {
          //printf("\nIG1=%f",IG); 
          iri_3dbase->setSunIgActiv(IG);
      }

      if (keyvod==2)
      {
          iri_3dbase->setKeyCorIon( true );
          iri_3dbase->ioncorr( false, latIon,lonIon,tIon,f0E,hmE,f0F1,hmF1,f0F2,hmF2,f0Es,hmEs);
      }
      else
          iri_3dbase->setKeyCorIon( false );

      iri_3dbase->getAppzocsim3DProfil();
      ig=iri_3dbase->getSunIgActiv();
      w =iri_3dbase->getSunActiv();

      //printf("\nW=%f  IG=%f",w,ig);

      iri_3dbase2= new IRI_3D(lonIon0, latIon0, rmax, zmin, dz, nx, ny, nz); // дополнительные профиль

      iri_3dbase2->setYear(iyear);
      iri_3dbase2->setDay(imonth*100+iday);
      iri_3dbase2->setTime(time2);
      iri_3dbase2->setKeyEs((keyes!=-1));
      if (keyMod)
          iri_3dbase2->setCCIR();
      else
          iri_3dbase2->setURSI();
      if (fabs(W)>.0001)
          iri_3dbase2->setSunActiv(W);
      if (IG>.0)
          iri_3dbase2->setSunIgActiv(IG);

      if (keyvod==2)
      {
          iri_3dbase2->setKeyCorIon( true );
          iri_3dbase2->ioncorr( false, latIon,lonIon,tIon,f0E,hmE,f0F1,hmF1,f0F2,hmF2,f0Es,hmEs);
      }
      else
          iri_3dbase2->setKeyCorIon( false );

      iri_3dbase2->getAppzocsim3DProfil();

      fMin=__min(iri_3dbase->getFMinF2(),iri_3dbase2->getFMinF2());

      hm=.01*iri_3dbase->getMaxH()+R0;
      h0=R0+H0;
      /*
      fprintf(out,"\nf0D =%5.2f  hmD =%5.1f",iri_3dbase->getf0D(),iri_3dbase->gethmD());
      fprintf(out,"\nf0E =%5.2f  hmE =%5.1f",iri_3dbase->getf0E(),iri_3dbase->gethmE());
      fprintf(out,"\nf0F1=%5.2f  hmF1=%5.1f",iri_3dbase->getf0F1(),iri_3dbase->gethmF1());
      fprintf(out,"\nf0F2=%5.2f  hmF2=%5.1f",iri_3dbase->getf0F2(),iri_3dbase->gethmF2());
      */
      //struct timeval tv;
      //struct timezone tz;
      //gettimeofday(&tv,&tz);
      //cout<<"\ntz_minuteswest="<<tz.tz_minuteswest<<"  tz_dsttime="<<tz.tz_dsttime;
  }

  fr=1.;
  fr2=1.;

  fstream outN_H("N_H.dat",ios::out);
  char str[120];
  npoint=100;
  sprintf(str,"\n%2d",npoint);
  sprintf(str,"\nh0=%6.1f hm=%6.1f",100.*(h0-R0),100.*(hm-R0));
  outN_H<<str;
  
  for(i=0; i<npoint; i++)
  {
      hpl[i]=i*(hm-h0)/(double)(npoint-1)+h0;

      ionos(fi0,teta0,hpl[i],6);

      fpl[i]=sqrt(v);
      hpl[i]=(hpl[i]-R0)*100.;
      sprintf(str,"\n%6.2f  %7.3f %9.5f %9.5f %9.5f %8.3f %8.3f",hpl[i],fpl[i],Vx,Vy,Vz,fi0/RAD,teta0/RAD);
      outN_H<<str;
      //cout<<str;
  }
  n[0]=i;

  return w;
} /* inions */
