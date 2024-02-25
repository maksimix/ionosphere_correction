using namespace std;

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "paths.h"

static void  fr_fact(double &fr, long &month, double  &time,
                     double  &Fam, double &Du, double &Dl, double &Vd,
                     double &SFam, double &Sdu, double &Sdl, double &Svd);

static void rnoise(long    &ns, long    &it,
                   double &f, double &lat, double &lon,
                   double &fam);

void   grss(double f,
            double lon,
            double lat,
            double t,
            long   mes,
            double &Fam,
            double &Du,
            double &Dl,
            double &Vd,
            double &SFam,
            double &Sdu,
            double &Sdl,
            double &Svd)
/***************************************************************/
/*                                                             */
/* Функция прогнозирует уровень шумов естественного происхож-  */
/* дения.                                                      */
/*                                                             */
/***************************************************************/
{
  long    i,j,it,it0,it1,mn,mn1;
  double yfr[2][4],p,spd;
//========================================================================

  if (lon>PI)
    lon=lon-PI2;

  it0=12.*t/PI+.5;
  it=(it0/4)%6+1;    // временной индекс
  mn=(mes/3)%4+1;    // номер сезона 1-зима, 2-весна, 3-лето, 4-осень
  rnoise(mn,it,f,lat,lon,Fam);
  if (Fam>.0)
    {
      fr_fact(f,mes,t,Fam,Du,Dl,Vd,SFam,Sdu,Sdl,Svd);
      spd=-(.2308*(f-2.)+15.);
    }
  else
    Fam=.0;

  if (spd>Fam)
    Fam=spd;
    return;
} /* grss */

static void fr_fact(double &fr,    // частота
                    long    &month, // месяц (1,2...12)
                    double &time,  // местное время в радианах
                    double &Fam,
                    double &Du,    // средняя мощность помех,превышаемая в течении
                                   // 10% часов (в дБ выше медианы временного интервала)
                    double &Dl,    // средняя мощность помех,превышаемая в течении
                                   // 90% часов (в дБ ниже медианы временного интервала)
                    double &Vdm,   // медианное значение отношения сред.квадр. значения
                                   // напряжения к среднему значению огиб. помехи
                    double &SFam,  // стандартное отклонение Fam
                    double &Sdu,   // стандартное отклонение Du
                    double &Sdl,   // стандартное отклонение Dl
                    double &Svd)   // стандартное отклонение Vd
{
  long    mes,tim,seek,ifr;
  double c[7],f,func[9],Fam_min,Fam_max;
  ifstream in;

  Vdm=Du=Dl=Sdu=Sdl=Svd=SFam=.0;
  mes=(month/3)%4;   // 0-зима,1-весна, 2-лето,3-осень
  while(time<.0)
    time +=PI2;
  while(time>PI2)
    time -=PI2;
  tim=12.*time/PI;
  tim=(tim/4)%6;    // временной индекс:0,1,2,3,4,5 (0-4,4-8,8-12,12-16,16-20,20,24)
//  tim=((int)time)/4; // для проверки
  //in.open("fam_sig.dat",std::ios::in|std::ios::binary);
  in.open("fam_sig.dat",ios::in|ios::binary);
  if (!((void*)in))
    {
      //in.clear(std::ios::goodbit);
      in.clear(ios::goodbit);
      cout<<"\nError: в рабочей директории отсутствует файл fam_sig.dat";
      exit(EXIT_FAILURE);
    }
  seek=sizeof(c)*9*(6*mes+tim);
  //in.seekg(seek,std::ios::beg);
  in.seekg(seek,ios::beg);

  if (fr<.01)
    f=.01;
  else
    if (fr>36.)
      f=36.;
    else
      f=fr;
  f=log10(f);

  for(long i=0; i<9; i++)
    {
      in.read((char*)c,sizeof(c));
      func[i]=.0;
      for(long j=6; j>=0; j--)
        func[i]=func[i]*f+c[j];

      if (i==0)
        Fam_max=c[0];
      if (i==1)
        Fam_min=c[0];
    }
  in.close();

  if (Fam>.0)
    Fam=func[1]+(Fam-Fam_min)*(func[0]-func[1])/(Fam_max-Fam_min);
  else
    Fam=.0;
  Du =func[2];
  Dl =func[3];
  Vdm=func[4];
  SFam=func[5];
  Sdu =func[6];
  Sdl =func[7];
  Svd =func[8];
  return;
}

static void rnoise(long    &ns,
                   long    &it,
                   double &f,
                   double &lat,
                   double &lon,
                   double &fam)
{
  float w[9][11];
  long k;
  ifstream inois;

  fam=.0;
  k=6*(ns-1)+it-1;

  //inois.open("noise.dat",std::ios::in|std::ios::binary);
  inois.open("noise.dat",ios::in|ios::binary);

  if (!((void*)inois))
    {
      //inois.clear(std::ios::goodbit);
      inois.clear(ios::goodbit);
      cout<<"\nError: в рабочей директории отсутствует файл noise.dat";
      exit(EXIT_FAILURE);
    }

  //inois.seekg(sizeof(w)*k,std::ios::beg);
  inois.seekg(sizeof(w)*k,ios::beg);
  inois.read((char*)&w[0][0],sizeof(w));
  inois.close();

  for(long i=10; i>=0; i--)
    fam=fam*sin(lat)+w[0][i]+w[1][i]*cos(lon)+w[2][i]*sin(lon)+w[3][i]*cos(2.*lon)+
        w[4][i]*sin(2.*lon)+w[5][i]+cos(3.*lon)+w[6][i]*sin(3.*lon)+
        w[7][i]*cos(4.*lon)+w[8][i]*sin(4.*lon);
  return;
}


