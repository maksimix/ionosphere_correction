#ifndef __PATHS_H
#define __PATHS_H

#include "../iri_3d/iri_3d_new.h"
#include "../trek/mytrek.h"

#ifndef __PI5
#define __PI5
const double PI5=1.57079632679489656;
#endif

int const RAY=20;
int const MaxHop=8;
int const MaxGran=8;

/* keyugl - 0 автоматическое определение границ поиска корней; */
/*          1 ввод границ поиска корней для всех скачков;      */
/*         -1 просмотр всех возможных углов, начиная с мини-   */
/*            мального для данной трассы и скачка до максималь-*/
/*            ного с заданным шагом.                           */
/* keytr  - 0 траектория не выводится по узлам,                */
/*          1 траектория печатается в процессе посторения в    */
/*            числовом виде;                                   */
/*         -1 траектория рисуется в графичеком виде.           */
/* keysol - 0 процесс поиска корней не отображается;           */
/*          1 процесс отображается в числовом виде;            */
/*         -1 строится график траектории, являющейся корнем    */
/*            граничной задачи.                                */
/* keympr - 0 не отображается поиск МПЧ;                       */
/*          1 отображается в числовом виде;                    */
/*         -1 отображается в графическом виде.                 */

const int MaxKolTr=100;
const int MaxSion=200;
const int MaxHion=300;

typedef struct
  {
    double lon0,lat0,lon1,lat1; // координаты передатчика и приемника
    double s0,alf0,alf1;        // длина трассы, азимут со стороны передатчика и со стороны приемника
    double P,band;              // мощность передатчика, полоса приемника
    double month,w;             // месяц и солнечная активность
    double tBeg,tEnd,tStep;     // сетка задания ионосферной информации в сек
    long   typeAntT,typeAntR;   // тип антенн на передее и на приеме
  } TRASSA;

typedef struct
  {
    long   kolTid; // число возмущений
    double de[3],Lam[3],T[3],a[3],b[3],fi[3]; // параметры ПИВ
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
    double mpchx;     // МПЧ трассы по х-компоненте
    double fr;
    double epom;
    double time;
    double di[RAY];   // угол места на передаче
    double ai[RAY];   // азимут на передаче
    double dk[RAY];   // угол места на приеме
    double ak[RAY];   // азимут на приеме
    double e[RAY];
    double l_es[RAY];
    double p[RAY];
    double pg[RAY];   // фазовый путь (отрицателен для х-луча)
    double df[RAY];
    unsigned long moda[RAY];
    long    k;
  } COR;

int const maxKor=10;


extern
double fl[5],hl[5],yl[5],al[5],
       dx[99],df[100],ff[100],xx[100],
       sf0,cf0,st0,ct0,
       sf,cf,st,ct,
       fh,h[3],dh[3][3],dh2[3][3][3],
       fi0,teta0,
       z0,z1,rH0, // высоты передатчика и приемника
       de[3],om[3],pf[3],pt[3],pr[3],fit[3],
       f0,hm,ym,h0,f02,
       gx,gy,
       HmF2,HmF1,HmE,HmD,HmEs,F0F2,F0F1,F0E,F0D,F0Es,FbEs,PEs,fMin,Hi,
       fhTemp,DTemp,ITemp;
extern double HmF2,HmF1,HmE,HmD,HmEs,F0F2,F0F1,F0E,F0D,F0Es,FbEs,PEs,Hi;
extern double fhTemp,DTemp,ITemp;
extern double dfi_a,dfi_d,dteta_a,dteta_d;

extern double aX,aY,aZ,delta0,r_0,teta_0,fi_0,rx_0,ry_0,rz_0,kx_0[3],ky_0[3],kz_0[3];
extern double fplIon[MaxSion][MaxHion],dsIon,dhIon,hminIon,fmaxIon;
extern double sMinIon,sMaxIon,alfIon;
extern double RMax;

//

extern
    int    nm,ii,mod,iox,koltid,klay,ivar,keysol,keytr,keyEs,
           keympr,keyugl,keynu,keyl2,keyFsp;

#ifndef _PUTDAT_
#define _PUTDAT_

struct PUTDAT
	  {
	    int    iox;  /* РХО МНПЛЮКЭМНИ БНКМШ 0 - "Н", 1 - "У" */
	    double fr;   /* ПЮАНВЮЪ ВЮЯРНРЮ,лцЖ                   */
	    double time; /* ЛЦМНБЕММНЕ БПЕЛЪ Б ЛХМ                */
	    double d1;   /* СЦНК ХГКСВЕМХЪ Я ОНБЕПУМНЯРХ гЕЛКХ    */
	    double d2;   /* СЦНК ОПХУНДЮ КСВЮ МЮ гЕЛКЧ            */
	    double x;    /* У - ЙННПДХМЮРЮ ОПХУНДЮ КСВЮ МЮ гЕЛКЧ  */
	    double y;    /* С - ЙННПДХМЮРЮ ОПХУНДЮ КСВЮ МЮ гЕЛКЧ  */
	    double s;    /* ОПНРЪФЕММНЯРЭ РПЮЯЯШ,ЙЛ               */
	    double at;   /* ЦЕНЦПЮТХВЕЯЙХИ ЮГХЛСР РПЮЯЯШ          */
	    double dev;  /* ДЕБХЮЖХЪ ОЕКЕМЦЮ Б РНВЙЕ ХГКСВЕМХЪ    */
        double a1;   /* azimuth izlucheniy                    */
        double a2;   /* azimuth priema                        */
	    double p;    /* ЦПСООНБНИ ОСРЭ,ЙЛ                     */
	    double df;   /* ДНОКЕПНБЯЙНЕ ЯЛЕЫЕМХЕ ВЮЯРНРШ,цЖ      */
	    double l;    /* ХНМНЯТЕПМНЕ ОНЦКНЫЕМХЛЕ               */
	    double xotr; /* ОПНЯРПЮМЯРБЕММШЕ ЙННПДХМЮРШ РНВЙХ     */
	    double yotr; /* НРПЮФЕМХЪ                             */
	    double zotr; /*                                       */
	    double ls;   /* ОПНЯРПЮМЯРБЕММНЕ НЯКЮАКЕМХЕ,Да        */
        double pg;   /* ТЮГНБШИ ОСРЭ,ЙЛ                       */
        double ps;   /* ДКХМЮ РПЮЕЙРНПХХ,ЙЛ                   */
        double FHhop1;
        double FHhop2;
        double Ihop1;
        double Ihop2;
        double Dhop1;
        double Dhop2;
        double dhop1;
        double dhop2;   
        double ref;     
        unsigned long moda;

            PUTDAT()
            {
                iox=0;
                fr=.0;
                time=.0;
                d1=d2=-1.; // ОПХГМЮЙ МЕПЮЯЯВХРЮММШУ ДЮММШУ
                a1=a2=-1.;
                x=y=s=.0;
                at=dev=.0;
                p=pg=ps=.0;
                df=.0;
                l=ls=.0;
                xotr=yotr=zotr=.0;
                ref=dhop1=dhop2=.0;
                FHhop1=FHhop2=Ihop1=Ihop2=Dhop1=Dhop2=.0;                
                moda=0;
            };

            bool operator < (PUTDAT const &other) const
            {
                return d1 < other.d1;
            };
	  };


#define FR(i)       ((putdat+(i))->fr)
#define TIME(i)     ((putdat+(i))->time)
#define D1(i)       ((putdat+(i))->d1)
#define D2(i)       ((putdat+(i))->d2)
#define A1(i)       ((putdat+(i))->a1)
#define A2(i)       ((putdat+(i))->a2)
#define X(i)        ((putdat+(i))->x)
#define Y(i)        ((putdat+(i))->y)
#define S(i)        ((putdat+(i))->s)
#define AT(i)       ((putdat+(i))->at)
#define DEV(i)      ((putdat+(i))->dev)
#define DF(i)       ((putdat+(i))->df)
#define L(i)        ((putdat+(i))->l)
#define XOTR(i)     ((putdat+(i))->xotr)
#define YOTR(i)     ((putdat+(i))->yotr)
#define ZOTR(i)     ((putdat+(i))->zotr)
#define LS(i)       ((putdat+(i))->ls)
#define PG(i)       ((putdat+(i))->pg)
#define PS(i)       ((putdat+(i))->ps)
#define P(i)        ((putdat+(i))->p)
#define Moda(i)     ((putdat+(i))->moda)
#define d_hop1(i)   ((putdat+(i))->dhop1)
#define d_hop2(i)   ((putdat+(i))->dhop2)
#define D_hop1(i)   ((putdat+(i))->Dhop1)
#define D_hop2(i)   ((putdat+(i))->Dhop2)
#define I_hop1(i)   ((putdat+(i))->Ihop1)
#define I_hop2(i)   ((putdat+(i))->Ihop2)
#define FH_hop1(i)  ((putdat+(i))->FHhop1)
#define FH_hop2(i)  ((putdat+(i))->FHhop2)
#define Ref(i)      ((putdat+(i))->ref)

#endif

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
              double  tStep,
              INFR    &infr);

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

void magfis(double fi, double teta, double r,
        double h[3], double dh[3][3], double dh3[3][3][3]);

void infils(long keyh);

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
          double eps1, // точности по дальности
          double eps2,
          double epsa, // точность по азимуту
          double dd0,  // шаг по углу места
          double aa0,  // шаг по азимуту
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

long soltA(double d0,    // угол места
           double alfa0, // истиный азимут трассы
           long   ihop,
           double delt,
           double eps,
           double ep,
           double ep1,
           double e,
           double eps1,  // точность по азимуту
           double dd0,   // шаг по азимуту
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
             double epsa, // точность по азимуту
             double dd0,  // шаг по углу места
             double aa0,  // шаг по азимуту
             PUTDAT *putdat);

void drawIon(double *fpl, double *hpl, int nf, int npoin, double hMin, double hMax, double fMax);

void drawTrek(double *sTr, double *hTr, long pointTr);

void drawClear();

void drawInf(char *inf);


int pk2_modul(double lat0,     //  ЬХПНРЮ, ЦПЮД
              double lon0,     //  ДНКЦНРЮ, ЦПЮД
              double Z0,       //  БШЯНРЮ РНВЙХ ХГКСВЕМХЪ, ЙЛ
              double Z1,       //  БШЯНРЮ РНВЙХ ОПХЕЛЮ, ЙЛ
              int iYear,       //  ЦНД
              double aMes,        //  ЛЕЯЪЖ Б ДЕЯЪРХВМНЛ ТНПЛЮРЕ
              long it1,        //  МЮВЮКЭМНЕ БПЕЛЪ Б ТНПЛЮРЕ ВВЛЛЯЯ
              long it2,        //  ЙНМЕВМНЕ БПЕЛЪ Б ТНПЛЮРЕ ВВЛЛЯЯ
              long it3,        //  ЬЮЦ ОН БПЕЛЕМХ Б ТНПЛЮРЕ ВВЛЛЯЯ ДКЪ ОПНЦМНГЮ
              double iW,       //  ВХЯКН бНКЭТЮ
              double iIG,      //  ХМДЕЙЯ ЯНКМЕВМНИ ЮЙРХБМНЯРХ
              long   keymod,   //  1 - CCIR, 0 - URSI
              long   keyes,    //  1 - ОПНЦМНГ ES, 0 - МЕР ES
              long   keystorm, //  1 - СВЕР ЛЮЦМХРМШУ БНГЛСЫЕМХИ, 0 - МЕР ЛЮЦМХРМШУ БНГЛСЫЕМХИ
              long   keyh,     //  1 - ЦКНАЮКЭ ЛНДЕКЭ ЦЕНЛЮЦМХРМНЦН ОНКЪ, 0 - ЦЕНЛЮЦМХРМНЕ ОНКЕ ОНЯРНЪММН
              double f,        //  ВЮЯРНРЮ, лцЖ
              double d,        //  СЦНК ХГКСВЕМХЪ, ЦПЮД
              double a,        //  ЮГХЛСР ХГКСВЕМХЪ, ЦПЮД
              long   t,        //  БПЕЛЪ ХГКСВЕМХЪ Б ТНПЛЮРЕ ВВЛЛЯЯ
              int iOX,         //  0 - o-БНКМЮ, 1 - x-БНКМЮ
              PUTDAT* putdat); //  ПЕГСКЭРЮРШ ПЮЯВЕРЮ

int pk3_modul(double lat0,     //  ЬХПНРЮ, ЦПЮД
              double lon0,     //  ДНКЦНРЮ, ЦПЮД
              double Z0,       //  БШЯНРЮ РНВЙХ ХГКСВЕМХЪ, ЙЛ
              double lat1,     //  ЬХПНРЮ, ЦПЮД
              double lon1,     //  ДНКЦНРЮ, ЦПЮД
              double Z1,       //  БШЯНРЮ РНВЙХ ОПХЕЛЮ, ЙЛ
              double eps1,     //  РНВМНЯРЭ ОН ДЮКЭМНЯРХ
              double eps2,     //  ОНПНЦ ОН ДЮКЭМНЯРХ
              double epsa,     //  РНВМНЯРЭ ОН ЮГХЛСРС
              double dd0,      //  ЬЮЦ ОН СЦКС ЛЕЯРЮ
              double aa0,      //  ЬЮЦ ОН ЮГХЛСРС
              int iYear,       //  ЦНД
              double aMes,     //  ЛЕЯЪЖ Б ДЕЯЪРХВМНЛ ТНПЛЮРЕ
              long it1,        //  МЮВЮКЭМНЕ БПЕЛЪ Б ТНПЛЮРЕ ВВЛЛЯЯ
              long it2,        //  ЙНМЕВМНЕ БПЕЛЪ Б ТНПЛЮРЕ ВВЛЛЯЯ
              long it3,        //  ЬЮЦ ОН БПЕЛЕМХ Б ТНПЛЮРЕ ВВЛЛЯЯ ДКЪ ОПНЦМНГЮ
              double iW,       //  ВХЯКН бНКЭТЮ
              double iIG,      //  ХМДЕЙЯ ЯНКМЕВМНИ ЮЙРХБМНЯРХ
              long   keymod,   //  1 - CCIR, 0 - URSI
              long   keyes,    //  1 - ОПНЦМНГ ES, 0 - МЕР ES
              long   keystorm, //  1 - СВЕР ЛЮЦМХРМШУ БНГЛСЫЕМХИ, 0 - МЕР ЛЮЦМХРМШУ БНГЛСЫЕМХИ
              long   keymp,    //  1 - ПЮЯЯВХРШБЮРЭ лов, 0 - МЕР
              long   keyh,     //  1 - ЦКНАЮКЭ ЛНДЕКЭ ЦЕНЛЮЦМХРМНЦН ОНКЪ, 0 - ЦЕНЛЮЦМХРМНЕ ОНКЕ ОНЯРНЪММН
              long   keyugl,   //  <=0 - ЮБРНЛЮРХВЕЯЙНЕ НОПЕДЕКЕМХЕ ДХЮОЮГНМЮ ОНХЯЙЮ ЙНПМЕИ, >0 - ОН ДЮММШЛ Б putdat
              double f,        //  ВЮЯРНРЮ, лцЖ
              long   t,        //  БПЕЛЪ ХГКСВЕМХЪ Б ТНПЛЮРЕ ВВЛЛЯЯ
              int iHop,        //  ВХЯКН ЯЙЮВЙНБ
              int iOX,         //  0 - o-БНКМЮ, 1 - x-БНКМЮ
              PUTDAT* putdat,  //  ПЕГСКЭРЮРШ ПЮЯВЕРЮ
              double &mpch);   //  лов ДКЪ ГЮДЮММНЦН ВХЯКЮ ЯЙЮВЙНБ Х ЙНЛОНМЕМРШ

                                // ТСМЙЖХЪ БНГБПЮЫЮЕР ЙНКХВЕЯРБН ЦПЮМХЖ ЛЕПРБНИ ГНМШ ХКХ 0, ЕЯКХ НМХ МЕ МЮИДЕМШ
int pk4_modul(double lat0,     //  ЬХПНРЮ, ЦПЮД
              double lon0,     //  ДНКЦНРЮ, ЦПЮД
              double Z0,       //  БШЯНРЮ РНВЙХ ХГКСВЕМХЪ, ЙЛ
              double lat1,     //  ЬХПНРЮ, ЦПЮД
              double lon1,     //  ДНКЦНРЮ, ЦПЮД
              double Z1,       //  БШЯНРЮ РНВЙХ ОПХЕЛЮ, ЙЛ
              double eps1,     //  РНВМНЯРЭ ОН ДЮКЭМНЯРХ
              double eps2,     //  ОНПНЦ ОН ДЮКЭМНЯРХ
              double epsa,     //  РНВМНЯРЭ ОН ЮГХЛСРС
              double dd0,      //  ЬЮЦ ОН СЦКС ЛЕЯРЮ
              double aa0,      //  ЬЮЦ ОН ЮГХЛСРС
              int iyear,       //  ЦНД
              double ames,     //  ЛЕЯЪЖ Б ДЕЯЪРХВМНЛ ТНПЛЮРЕ
              long it1,        //  МЮВЮКЭМНЕ БПЕЛЪ Б ТНПЛЮРЕ ВВЛЛЯЯ
              long it2,        //  ЙНМЕВМНЕ БПЕЛЪ Б ТНПЛЮРЕ ВВЛЛЯЯ
              long it3,        //  ЬЮЦ ОН БПЕЛЕМХ Б ТНПЛЮРЕ ВВЛЛЯЯ ДКЪ ОПНЦМНГЮ
              double w,       //  ВХЯКН бНКЭТЮ
              double ig,      //  ХМДЕЙЯ ЯНКМЕВМНИ ЮЙРХБМНЯРХ
              long   keymod,   //  1 - CCIR, 0 - URSI
              long   keyes,    //  1 - ОПНЦМНГ ES, 0 - МЕР ES
              long   keystorm, //  1 - СВЕР ЛЮЦМХРМШУ БНГЛСЫЕМХИ, 0 - МЕР ЛЮЦМХРМШУ БНГЛСЫЕМХИ
              long   keymp,    //  1 - ПЮЯЯВХРШБЮРЭ лов, 0 - МЕР
              long   keyh,
              double f,         // ВЮЯРНРЮ
              PUTDAT **putdat,  // ПЕГСКЭРЮРШ Б НЙПЕЯРМНЯРХ лов У-БНКМШ
              int *n,           // ВХЯКН ЙНПМЕИ
              double *tVosZah,  // БПЕЛЕММШЕ ЦПЮМХЖШ ЛЕПРБШУ ГНМ
              double *mpch);    //  лов ДКЪ ГЮДЮММНЦН ВХЯКЮ ЯЙЮВЙНБ Х ЙНЛОНМЕМРШ

#endif
