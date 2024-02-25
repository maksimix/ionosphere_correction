using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "paths.h"

SPCUB *spN_H=0;
extern double Vx, Vy, Vz;

int ionos(double f, double t, double r, int n);

double inions(int     iyear,
              double  ames,
              double  &w,
              double  &ig,
              double  rmax,
              long    keyvod,
              long    keyMod,
              long    keyes,
              long    keystorm,
              double  time,
              double  tbeg,
              double  tend,
              double  tStep)
/***************************************************************/
/* ������� ������������� ��� ����������� �������� � ���������� */
/* ����������������� ������������� ��������, ��� �������,      */
/* ��� �������� ������� ������������� ������ ���               */
/*                                                             */
/*  ames   - �����;                                            */
/*  w      - ��������� ���������� (�����, ����� ��� ���);      */
/*  keyMod - 1 - ������� ������� � ������������ � ������� CCIR,*/
/*           0 - ������� URSI;                                 */
/*  keyvod - 0 - �������;                                      */
/*           1 - ���� ���������� ����� ����� ������;           */
/*           2 - ��������� ����������� ���������� �� ������ �� */
/*               � ����� ���������������� �����                */
/*  keyes  - 0 - ������� ���������� Es-���� ����� ������,      */
/*           1 - ���� ���������� Es-���� ����� ������,         */
/*          -1 - Es-���� �� �����������;                       */
/*  keyl2  - 0 - ������� �� 2.2                                */
/*           1 - ���� ����������                               */
/*          -1 - ������� ���                                   */
/*                                                             */
/*VGG 09.02.2005                                               */
/***************************************************************/
/***************************************************************/
/*                                                             */
/*      �������� ����� ����������� ����������.                 */
/*                                                             */
/*      ������� ����������� ����������� ��������� �����������  */
/*      �������:                                               */
/*        - ����������� ��������������;                        */
/*        - ������� �������� �� ������ � ����������            */
/*          ���������� ���������;                              */
/*                                                             */
/*      ������������ ���� ����������� ������� �������� ��      */
/*      ����������� ������� ���������� ��������, � �����       */
/*      ������������ ������������� �������� ����������.        */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  double alam[3],t[3],a[3],b[3];
  long month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  int    i,npoint,key;
  static double tBeg=.0;
  static double tEnd=.0;
  static double Fi0=-999.;
  static double Teta0=-999.;
  long n[1];

  if (time>=tBeg && time<=tEnd && fabs(Fi0-fi0)<.000001 && fabs(Teta0-teta0)<.000001)
      return .0;

  //printf("\nt1=%f   t2=%f  t=%f",tBeg,tEnd,time);

  Fi0=fi0;
  Teta0=teta0;

  for(tEnd=tbeg+tStep; tEnd<=tend; tEnd+=tStep)
  {
      tBeg=tEnd-tStep;
      if (time>=tBeg && time<=tEnd)
      break;
  }
  if (tEnd>tend)
      return -1.;
  if (iri_3dbase)
      delete iri_3dbase;
  if (iri_3dbase2)
      delete iri_3dbase2;

  gx=gy=.0;
  mod=10;
  koltid=0;

  // �������� �������, �������� ������� IRI � ������ ��� �������� �������� �� �������
  int    imonth, iday;
  double time1, time2;
  double zmin=H0,
         dz=DZ;
  double W,IG;
  long nx=NX, ny=NY, nz=NZ;

  W=w;
  IG=ig;

  imonth=(long)ames;
  iday=(long)(month[imonth-1]*(ames-imonth)+.5);

  time1=tBeg/3600.;
  while(time1>24.) time1-=24.;
  while(time1<.0)  time1+=24.;
  time1+=25.; // ��������� ����� ��� ��������� iris13
  time2=tEnd/3600.;
  while(time2>24.) time2-=24.;
  while(time2<.0)  time2+=24.;
  time2+=25.; // ��������� ����� ��� ��������� iris13

  //printf("\ntime=%f time2=%f iyear=%d imonth=%d iday=%d",time,time2,iyear,imonth,iday);

  iri_3dbase = new IRI_3D(fi0/RAD, 90.-teta0/RAD, rmax, zmin, dz, nx, ny, nz); // �������� �������

  iri_3dbase->setYear(iyear);
  iri_3dbase->setDay(imonth*100+iday);
  iri_3dbase->setTime(time1);
  iri_3dbase->setKeyEs((keyes!=-1)));
  iri_3dbase->setJF(keystorm,25);
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
  iri_3dbase->getAppzocsim3DProfil();
  ig=iri_3dbase->getSunIgActiv();
  w =iri_3dbase->getSunActiv();

  //printf("\nW=%f  IG=%f",w,ig);

  iri_3dbase2= new IRI_3D(fi0/RAD, 90.-teta0/RAD, rmax, zmin, dz, nx, ny, nz); // �������������� �������

  iri_3dbase2->setYear(iyear);
  iri_3dbase2->setDay(imonth*100+iday);
  iri_3dbase2->setTime(time2);
  iri_3dbase2->setKeyEs((keyes!=-1)));
  iri_3dbase2->setJF(keystorm,25);
  if (keyMod)
      iri_3dbase2->setCCIR();
  else
      iri_3dbase2->setURSI();
  if (fabs(W)>.0001)
      iri_3dbase2->setSunActiv(W);
  if (IG>.0)
      iri_3dbase2->setSunIgActiv(IG);
  iri_3dbase2->getAppzocsim3DProfil();

  double f1=iri_3dbase->getFMinF2();
  double f2=iri_3dbase2->getFMinF2();
  fMin=__min(iri_3dbase->getFMinF2(),iri_3dbase2->getFMinF2());

  hm=.01*iri_3dbase->getMaxH()+R0;
  h0=R0+H0;
 
  return w;
} /* inions */
