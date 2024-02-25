#ifndef __PATHS_H
#define __PATHS_H

#ifndef __IRI_4D_H
#include "../iri_4d/iri_4d.h"
#endif

#ifndef __SPCUB_H
#include "../splayn/spcub.h"
#endif

#include <stdio.h>

#define PI  3.14159265358979312
#define PI2 6.28318530717958624
#define PI5 1.57079632679489656
#define RAD 1.745329251994329548e-2
#define DB  868.588
#define C   .2997925
#define R0  63.70
#define H0  .5
#define HM  5.
#define STEP .025
#define RAY 20
#define MaxHop 8
#define MaxGran 8

/* keyugl - 0 БЧФПНБФЙЮЕУЛПЕ ПРТЕДЕМЕОЙЕ ЗТБОЙГ РПЙУЛБ ЛПТОЕК; */
/*          1 ЧЧПД ЗТБОЙГ РПЙУЛБ ЛПТОЕК ДМС ЧУЕИ УЛБЮЛПЧ;      */
/*         -1 РТПУНПФТ ЧУЕИ ЧПЪНПЦОЩИ ХЗМПЧ, ОБЮЙОБС У НЙОЙ-   */
/*            НБМШОПЗП ДМС ДБООПК ФТБУУЩ Й УЛБЮЛБ ДП НБЛУЙНБМШ-*/
/*            ОПЗП У ЪБДБООЩН ЫБЗПН.                           */
/* keytr  - 0 ФТБЕЛФПТЙС ОЕ ЧЩЧПДЙФУС РП ХЪМБН,                */
/*          1 ФТБЕЛФПТЙС РЕЮБФБЕФУС Ч РТПГЕУУЕ РПУФПТЕОЙС Ч    */
/*            ЮЙУМПЧПН ЧЙДЕ;                                   */
/*         -1 ФТБЕЛФПТЙС ТЙУХЕФУС Ч ЗТБЖЙЮЕЛПН ЧЙДЕ.           */
/* keysol - 0 РТПГЕУУ РПЙУЛБ ЛПТОЕК ОЕ ПФПВТБЦБЕФУС;           */
/*          1 РТПГЕУУ ПФПВТБЦБЕФУС Ч ЮЙУМПЧПН ЧЙДЕ;            */
/*         -1 УФТПЙФУС ЗТБЖЙЛ ФТБЕЛФПТЙЙ, СЧМСАЭЕКУС ЛПТОЕН    */
/*            ЗТБОЙЮОПК ЪБДБЮЙ.                                */
/* keympr - 0 ОЕ ПФПВТБЦБЕФУС РПЙУЛ нрю;                       */
/*          1 ПФПВТБЦБЕФУС Ч ЮЙУМПЧПН ЧЙДЕ;                    */
/*         -1 ПФПВТБЦБЕФУС Ч ЗТБЖЙЮЕУЛПН ЧЙДЕ.                 */

const long MaxPointTr=50000;
const long MaxKolTr=100;
const long MaxSion=200;
const long MaxHion=300;

typedef struct
  {
    double lon0,lat0,lon1,lat1; // ЛППТДЙОБФЩ РЕТЕДБФЮЙЛБ Й РТЙЕНОЙЛБ
    double s0,alf0,alf1;        // ДМЙОБ ФТБУУЩ, БЪЙНХФ УП УФПТПОЩ РЕТЕДБФЮЙЛБ Й УП УФПТПОЩ РТЙЕНОЙЛБ
    double P,band;              // НПЭОПУФШ РЕТЕДБФЮЙЛБ, РПМПУБ РТЙЕНОЙЛБ
    double month,w;             // НЕУСГ Й УПМОЕЮОБС БЛФЙЧОПУФШ
    double tBeg,tEnd,tStep;     // УЕФЛБ ЪБДБОЙС ЙПОПУЖЕТОПК ЙОЖПТНБГЙЙ Ч УЕЛ
    long   typeAntT,typeAntR;   // ФЙР БОФЕОО ОБ РЕТЕДЕЕ Й ОБ РТЙЕНЕ
  } TRASSA;

typedef struct
  {
    long   kolTid; // ЮЙУМП ЧПЪНХЭЕОЙК
    double de[3],Lam[3],T[3],a[3],b[3],fi[3]; // РБТБНЕФТЩ рйч
  } TID;

typedef struct
  {
    double timeb;
    double timek;
    double *fr;
    double popo;
    double popx;
    long    kzap;
    long    kfr;
    TRASSA  trassa;
    TID     tid;
  } INFR;

typedef struct
  {
    double mpchx;     // нрю ФТБУУЩ РП И-ЛПНРПОЕОФЕ
    double fr;
    double epom;
    double time;
    double di[RAY];   // ХЗПМ НЕУФБ ОБ РЕТЕДБЮЕ
    double ai[RAY];   // БЪЙНХФ ОБ РЕТЕДБЮЕ
    double dk[RAY];   // ХЗПМ НЕУФБ ОБ РТЙЕНЕ
    double ak[RAY];   // БЪЙНХФ ОБ РТЙЕНЕ
    double e[RAY];
    double l_es[RAY];
    double p[RAY];
    double pg[RAY];   // ЖБЪПЧЩК РХФШ (ПФТЙГБФЕМЕО ДМС И-МХЮБ)
    double df[RAY];
    unsigned long moda[RAY];
    long    k;
  } COR;

int const maxKor=10;

extern
double fl[5],hl[5],yl[5],al[5],
       dx[99],df[100],ff[100],xx[100],
       u,u1,fh,
       amy,amy0,dmca0,
       sf,cf,st,ct,
       sf0,cf0,st0,ct0,
       fi0,teta0,
       z0,z1,rH0, // ЧЩУПФЩ РЕТЕДБФЮЙЛБ Й РТЙЕНОЙЛБ
       v,vp[3],vpp[3][3],dvt,s,par,
       dmrtf[3],dmv,ov,sa2,ak,anorm,
       h[3],dh[3][3],dh2[3][3][3],
       fr,fr2,
       tim,
       de[3],om[3],pf[3],pt[3],pr[3],fit[3],
       fot,tot,rot,
       fpl[100],hpl[100],
       f0,hm,ym,h0,f02,
       gx,gy,
       HmF2,HmF1,HmE,HmD,HmEs,F0F2,F0F1,F0E,F0D,F0Es,FbEs,PEs,fMin,Hi,
       fhTemp,DTemp,ITemp,
       FHhop[MaxHop][2],Ihop[MaxHop][2],Dhop[MaxHop][2],
       FHhopk[RAY][MaxHop][2],Ihopk[RAY][MaxHop][2],Dhopk[RAY][MaxHop][2],
       dhop[MaxHop][2],ref[MaxHop],dhopk[RAY][MaxHop][2],refk[RAY][MaxHop];
extern double HmF2,HmF1,HmE,HmD,HmEs,F0F2,F0F1,F0E,F0D,F0Es,FbEs,PEs,Hi;
extern double fhTemp,DTemp,ITemp;
extern double sTr[MaxPointTr],hTr[MaxPointTr],fiTr[MaxPointTr],tetaTr[MaxPointTr];
extern long pointTr;
extern double dfi_a,dfi_d,dteta_a,dteta_d;

extern double alfa0,beta0,aX,aY,aZ,delta0,delta1,r_0,teta_0,fi_0,rx_0,ry_0,rz_0,kx_0[3],ky_0[3],kz_0[3];
extern double fplIon[MaxSion][MaxHion],dsIon,dhIon,hminIon,fmaxIon;
extern double sMinIon,sMaxIon,alfIon;
extern double RMax;
extern double fi_m0,teta_m0,ro_m,lambd1,lambd2,amp_proval,fi0_inv,steta_m0,cteta_m0;
extern double fiIon0,tetaIon0; // point for zadaniya ionospher (RAD)

extern SPCUB *spN_H;

extern
    int    nm,ii,mod,iox,koltid,klay,ivar,keysol,keytr,keyEs,
           keympr,keyugl,keynu,keyl2,keyFsp,keyOval;

extern
    int keyZat;
extern
    double *timCzat,*latCzat,*lonCzat;

struct PUTDAT
	  {
	    int    iox;  /* тип нормальной волны 0 - "о", 1 - "х" */
	    double fr;   /* рабочая частота,МГц                   */
	    double time; /* мгновенное время в мин                */
	    double d1;   /* угол излучения с поверхности Земли    */
	    double d2;   /* угол прихода луча на Землю            */
	    double x;    /* х - координата прихода луча на Землю  */
	    double y;    /* у - координата прихода луча на Землю  */
	    double s;    /* протяженность трассы,км               */
	    double at;   /* географический азимут трассы          */
	    double dev;  /* девиация пеленга в точке излучения    */
            double a1;   /* azimuth izlucheniy                    */
            double a2;   /* azimuth priema                        */
	    double p;    /* групповой путь,км                     */
	    double df;   /* доплеровское смещение частоты,Гц      */
	    double l;    /* ионосферное поглощениме               */
	    double xotr; /* пространственные координаты точки     */
	    double yotr; /* отражения                             */
	    double zotr; /*                                       */
	    double ls;   /* пространственное ослабление,дБ        */
            double pg;   /* фазовый путь,км                       */
            double ps;   /* длина траектории,км                   */
            unsigned long moda;

            PUTDAT()
            {
                iox=0;
                fr=.0;
                time=.0;
                d1=d2=-1.; // признак нерассчитанных данных
                a1=a2=-1.;
                x=y=s=.0;
                at=dev=.0;
                p=pg=ps=.0;
                df=.0;
                l=ls=.0;
                xotr=yotr=zotr=.0;
                moda=0;
            };
	  };


typedef
    int (*FUNC) (double x,             /* фЙР ХЛБЪБФЕМЕК ОБ ЖХОЛГЙА,       */
		 double *y, double *f, /* ЧЩЮЙУМСАЭХА ЪОБЮЕОЙС РТПЙЪЧПДОЩИ */
		 int    n);            /* - РТБЧЩИ ЮБУФЕК ДЙЖ.-ХТБЧОЕОЙК   */

#define IOX(i)  ((putdat+(i))->iox)
#define FR(i)   ((putdat+(i))->fr)
#define TIME(i) ((putdat+(i))->time)
#define D1(i)   ((putdat+(i))->d1)
#define D2(i)   ((putdat+(i))->d2)
#define A1(i)   ((putdat+(i))->a1)
#define A2(i)   ((putdat+(i))->a2)
#define X(i)    ((putdat+(i))->x)
#define Y(i)    ((putdat+(i))->y)
#define S(i)    ((putdat+(i))->s)
#define AT(i)   ((putdat+(i))->at)
#define DEV(i)  ((putdat+(i))->dev)
#define DF(i)   ((putdat+(i))->df)
#define L(i)    ((putdat+(i))->l)
#define XOTR(i) ((putdat+(i))->xotr)
#define YOTR(i) ((putdat+(i))->yotr)
#define ZOTR(i) ((putdat+(i))->zotr)
#define LS(i)   ((putdat+(i))->ls)
#define PG(i)   ((putdat+(i))->pg)
#define PS(i)   ((putdat+(i))->ps)
#define P(i)    ((putdat+(i))->p)
#define Moda(i) ((putdat+(i))->moda)

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
              double  tStep);

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
              double  tStep);

void infils(FILE *in, FILE *out);

void infils(long keyh);

int  treks(double d0, double alfa,
           int ihop, int n,
           double delt0, double eps, double ep, double ep1, double e,
           PUTDAT *putdat);

void outtrs(FILE   *out,
            PUTDAT *putdat,
            int    ihop);

long solt(double d0,
          double d1,
          double alf0,
          double s0,
          long   ihop,
          double delt,
          double eps,
          double ep,
          double ep1,
          double e,
          double eps1, // ФПЮОПУФЙ РП ДБМШОПУФЙ
          double eps2,
          double epsa, // ФПЮОПУФШ РП БЪЙНХФХ
          double dd0,  // ЫБЗ РП ХЗМХ НЕУФБ
          double aa0,  // ЫБЗ РП БЪЙНХФХ
          PUTDAT *putdat);

double zero_t(double a,
              double fa,
              double b,
              double fb,
              double s0,
              double alfa,
              long    ihop,
              double delt,
              double epst,
              double ep,
              double ep1,
              double e,
              double tol,
              double epsa,
              double aa0,
              PUTDAT *putdat);

char* moda(unsigned long  m,
           char* str);

void outtrs(FILE   *out,
	    PUTDAT *putdat,
	    int    ihop);

long soltA(double d0,    // ХЗПМ НЕУФБ
           double alfa0, // ЙУФЙОЩК БЪЙНХФ ФТБУУЩ
           long   ihop,
           double delt,
           double eps,
           double ep,
           double ep1,
           double e,
           double eps1,  // ФПЮОПУФШ РП БЪЙНХФХ
           double dd0,   // ЫБЗ РП БЪЙНХФХ
           PUTDAT *putdat);

void   grss(double f, double lon, double lat, double t,
            long   mes, double &Fam, double &Du, double &Dl,
            double &Vd, double &SFam, double &Sdu,
            double &Sdl, double &Svd);

void abs_es(double fr, long ox, long hop, long n, double *l_es);

void ssno(double fr, double tim, long   mes, double alat,
          double& eno, double& sno);

void shell(double *a1, double *a2, double *a3,
           double *a4, double *a5, double *a6,
           double *a7, double *a8, double *a9, unsigned long *a10, long n);

void init_fil(char   *name,
              INFR   &infr,
              long    keyini);

void wr_fil(char *name,
            INFR &infr,
            long keyini,
            COR *cor);

void writeIndexDasf(char *name);

bool readIndexDasf(char *name);

void prion(FILE   *out,
           double  lat0,
           double  lon0,
           double  lat1,
           double  lon1,
           double  time,
           double  W,
           double  IG,
           long    keypri,
           long    keyes);

double mpchs(double s0,
             double alfa,
             long   ihop,
             double db,
             double de,
             double delt,
             double eps,
             double ep,
             double ep1,
             double e,
             double eps2,
             double epsa, // ФПЮОПУФШ РП БЪЙНХФХ
             double dd0,  // ЫБЗ РП ХЗМХ НЕУФБ
             double aa0,  // ЫБЗ РП БЪЙНХФХ
             PUTDAT *putdat);

void drawIon(double *fpl, double *hpl, int nf, int npoin, double hMin, double hMax, double fMax);

void drawTrek(double *sTr, double *hTr, long pointTr);

void drawClear();

double dist(double fi0, double teta0, double fi1, double teta1);

void drawInf(char *inf);


int pk2_modul(double lat0,     //  широта, град
              double lon0,     //  долгота, град
              double Z0,       //  высота точки излучения, км
              double Z1,       //  высота точки приема, км
              int iYear,       //  год
              double aMes,        //  месяц в десятичном формате
              long it1,        //  начальное время в формате ччммсс
              long it2,        //  конечное время в формате ччммсс
              long it3,        //  шаг по времени в формате ччммсс для прогноза
              double iW,       //  число Вольфа
              double iIG,      //  индекс солнечной активности
              long   keymod,   //  1 - CCIR, 0 - URSI
              long   keyes,    //  1 - прогноз ES, 0 - нет ES
              long   keystorm, //  1 - учет магнитных возмущений, 0 - нет магнитных возмущений
              long   keyh,     //  1 - глобаль модель геомагнитного поля, 0 - геомагнитное поле постоянно
              double f,        //  частота, МГц
              double d,        //  угол излучения, град
              double a,        //  азимут излучения, град
              long   t,        //  время излучения в формате ччммсс
              int iOX,         //  0 - o-волна, 1 - x-волна
              PUTDAT* putdat); //  результаты расчета

int pk3_modul(double lat0,     //  широта, град
              double lon0,     //  долгота, град
              double Z0,       //  высота точки излучения, км
              double lat1,     //  широта, град
              double lon1,     //  долгота, град
              double Z1,       //  высота точки приема, км
              double eps1,     //  точность по дальности
              double eps2,     //  порог по дальности
              double epsa,     //  точность по азимуту
              double dd0,      //  шаг по углу места
              double aa0,      //  шаг по азимуту
              int iYear,       //  год
              double aMes,     //  месяц в десятичном формате
              long it1,        //  начальное время в формате ччммсс
              long it2,        //  конечное время в формате ччммсс
              long it3,        //  шаг по времени в формате ччммсс для прогноза
              double iW,       //  число Вольфа
              double iIG,      //  индекс солнечной активности
              long   keymod,   //  1 - CCIR, 0 - URSI
              long   keyes,    //  1 - прогноз ES, 0 - нет ES
              long   keystorm, //  1 - учет магнитных возмущений, 0 - нет магнитных возмущений
              long   keymp,    //  1 - рассчитывать МПЧ, 0 - нет
              long   keyh,     //  1 - глобаль модель геомагнитного поля, 0 - геомагнитное поле постоянно
              long   keyugl,   //  <=0 - автоматическое определение диапазона поиска корней, >0 - по данным в putdat
              double f,        //  частота, МГц
              long   t,        //  время излучения в формате ччммсс
              int iHop,        //  число скачков
              int iOX,         //  0 - o-волна, 1 - x-волна
              PUTDAT* putdat,  //  результаты расчета
              double &mpch);   //  МПЧ для заданного числа скачков и компоненты

                                // функция возвращает количество границ мертвой зоны или 0, если они не найдены
int pk4_modul(double lat0,     //  широта, град
              double lon0,     //  долгота, град
              double Z0,       //  высота точки излучения, км
              double lat1,     //  широта, град
              double lon1,     //  долгота, град
              double Z1,       //  высота точки приема, км
              double eps1,     //  точность по дальности
              double eps2,     //  порог по дальности
              double epsa,     //  точность по азимуту
              double dd0,      //  шаг по углу места
              double aa0,      //  шаг по азимуту
              int iyear,       //  год
              double ames,     //  месяц в десятичном формате
              long it1,        //  начальное время в формате ччммсс
              long it2,        //  конечное время в формате ччммсс
              long it3,        //  шаг по времени в формате ччммсс для прогноза
              double w,       //  число Вольфа
              double ig,      //  индекс солнечной активности
              long   keymod,   //  1 - CCIR, 0 - URSI
              long   keyes,    //  1 - прогноз ES, 0 - нет ES
              long   keystorm, //  1 - учет магнитных возмущений, 0 - нет магнитных возмущений
              long   keymp,    //  1 - рассчитывать МПЧ, 0 - нет
              long   keyh,
              double f,         // частота
              PUTDAT **putdat,  // результаты в окрестности МПЧ х-волны
              int *n,           // число корней
              double *tVosZah,  // временные границы мертвых зон
              double *mpch);    //  МПЧ для заданного числа скачков и компоненты

#endif
