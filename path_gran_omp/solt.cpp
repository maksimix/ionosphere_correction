#include <sys/time.h>
#include <sys/timeb.h>
#include <omp.h>

#include "paths.h"
#include "mysolt.h"

//#define M 2 /* количество монотонных шагов */
//#define EPS .17e-6

//long kkk;

#define FORM1 "\nd8,d7,s,fr,hop,no %12.8f%7.2f%13.6f%8.2f%3d%3d"
#define FORM2 "\nd6,d7,s,koli,no %12.8lf%7.2lf%13.6lf%3d%3d"

MySolt::MySolt(double F, double T, double Fh, double H[3], double Dh[3][3], double Dh2[3][3][3], int Hop, double S0, double Alfa0, double Dmin, double Dmax,
               double Delt, double Eps, double Ep, double Ep1, int N,
               double Eps1, double Dd0, double Epsa, double Aa0, PUTDAT* Putdat) :
               f(F), t(T), fh(Fh), s0(S0), alfa0(Alfa0), d0(Dmin), d1(Dmax), n(N), ihop(Hop),
               delt(Delt), eps(Eps), ep(Ep), ep1(Ep1), eps1(Eps1), dd0(Dd0), epsa(Epsa), aa0(Aa0), putdat(Putdat)
{
    result=0;
    maxS=.0;
    flagMpch=false;
    for(int i=0; i<3; i++)
    {
        h[i]=H[i];
        for(int j=0; j<3; j++)
        {
            dh[i][j]=Dh[i][j];
            for(int k=0; k<3; k++)
                  dh2[i][j][k]=Dh2[i][j][k];
        }
    }
}

MySolt::MySolt(double S0, double Alfa0,
               double Delt, double Eps, double Ep, double Ep1, int N,
               double Eps1, double Dd0, double Epsa, double Aa0, PUTDAT* Putdat) :
               s0(S0), alfa0(Alfa0), n(N),
               delt(Delt), eps(Eps), ep(Ep), ep1(Ep1), eps1(Eps1), dd0(Dd0), epsa(Epsa), aa0(Aa0), putdat(Putdat)
{
    result=-1.;
    maxS=.0;
    flagMpch=false;
    for(int i=0; i<3; i++)
    {
        h[i]=.0;
        for(int j=0; j<3; j++)
        {
            dh[i][j]=.0;
            for(int k=0; k<3; k++)
                  dh2[i][j][k]=.0;
        }
    }
}


MySolt::~MySolt()
{
}

void TrekThread::run()
{
    mySolt->setResult(zero_t(d2,f2,d3,f3,mySolt->getS0(),mySolt->getAlfa0(),mySolt->getHop(),mySolt->getEpsS(),mySolt->getEpsA(),mySolt->getAa0(),mySoltA->getPutDat()));
    PUTDAT* putdat=mySoltA->getPutDat();
    if (mySolt->getResult()>=.0)
    {
        //printf("\nmySolt->getResult()=%6.2f  D1(0)=%6.2f",mySolt->getResult()/RAD,D1(0));
        int ihop=mySoltA->getHop();
        double d1=D1(0)*RAD;
        double a1=A1(0)*RAD;
        int n=mySoltA->getN();
        mySoltA->getMyTrek()->treks(d1,a1,ihop,n,putdat);
    }
    else
    {
        D1(0)=-99.; // признак того, что корень по каким-то причинам не найден (например, по количеству итераций)
    }
}

long MySolt::solt()
/***************************************************************/
/*                                                             */
/* Функция находит все решения граничной задачи s(d)=s0  и     */
/* возвращает количество этих решений.                         */
/*                                                             */
/* d0   - левая граница отрезка, на котором ищатся решения,    */
/* d1   - правая граница этого отрезка,                        */
/* s0   - длина трассы,                                        */
/* ihop - число скачков,                                       */
/* eps1 - точность решения уравнения,                          */
/* eps2 - ограничение поиска корней по минимальной дальности,  */
/* epsa -  точность по азимуту,                                */
/* dd0  -  шаг по углу места,                                  */
/* aa0  -  шаг по азимуту,                                     */
/* dd   - начальный шаг по углу,                               */
/*                                                             */
/*VGG  версия 14.06.06                                         */
/***************************************************************/

{
  long    no;
  timeval tv;
  double T1,T2,DT;
  int nK=0;

  maxS=.0;

  gettimeofday(&tv,NULL);
  T1=tv.tv_sec+tv.tv_usec/1000000.0;

  int kol=(int)((d1-d0)/dd0+.5);
  int nProc=omp_get_num_procs();
  omp_set_num_threads(nProc);
  PUTDAT **putdatA=new PUTDAT*[kol];
#pragma omp parallel for
  for(int k=0; k<kol; k++) // вычисляем характеристики распространения с заданным шагом по углу места
  {
      //printf("k=%2d  nThread=%2d\n",k,omp_get_thread_num());
      double d=d0+dd0*k;
      putdatA[k]=new PUTDAT[ihop];
      for(int i=0; i<ihop; i++)
      {
          PUTDAT* putdat=putdatA[k];
          IOX(i)=iox;
          FR(i)=f;
          TIME(i)=t;
          D1(i)=D2(i)=.0;
          S(i)=.0;
      }
      MySoltA *mySoltA=new MySoltA(f,t,fh,h,dh,dh2,d,alfa0,ihop,delt,eps,ep,ep1,n,epsa,aa0,putdatA[k]);
      int no=mySoltA->soltA();
      if (!no)
      {
      }
      else
      {
          PUTDAT* putdat=putdatA[k];
          D1(0)=-99.;
      }
      if (keysol)
      {
          PUTDAT* putdat=putdatA[k];
          printf("fr=%6.3f d=%5.2f  s=%9.3f\n",FR(ihop-1),D1(ihop-1),S(ihop-1));
          fflush(stdout);
      }
      delete mySoltA;
  }
  
  for(int k=0; k<kol; k++)
  {
      PUTDAT* putdat=putdatA[k];
      if (D1(0)>=.0)
      {
          sPutDat.insert(putdat); // помещаем найденные результаты
      }
      else
      {
          delete[] putdat;
      }
  }
  delete[] putdatA;

  //gettimeofday(&tv,NULL);
  //T2=tv.tv_sec+tv.tv_usec/1000000.0;
  //DT=T2-T1;

  //printf("\ntime,ms=%8.3f\n",DT*1000.);
  //fflush(stdout);

  std::set < PUTDAT*, LessPutDat<PUTDAT> >::const_iterator its, its1;

  if (!sPutDat.empty())
  {
      for(its=sPutDat.begin(); its!=sPutDat.end(); ++its)
      {
          PUTDAT *putdat =*its;
          if (((putdat +(ihop-1))->s)>maxS)
              maxS=((putdat +(ihop-1))->s);
      }
  }

  if (sPutDat.size()>1)
  {
          int size=sPutDat.size();
          for(its1=its=sPutDat.begin(),its1++; its!=sPutDat.end() && its1!=sPutDat.end(); its++, its1++)
          {
              PUTDAT *putdat =*its;
              PUTDAT *putdat1=*its1;
              double d,d2,d3,f2,f3;
              if (((putdat +(ihop-1))->s)<=.0)
                continue;
              if (((putdat1 +(ihop-1))->s)<=.0)
                continue;

              d2=((putdat +(0))->d1)*RAD;
              d3=((putdat1+(0))->d1)*RAD;
              f2=((putdat +(ihop-1))->s)*.01-s0;
              f3=((putdat1+(ihop-1))->s)*.01-s0;
              d=d2;

              //printf("1 fr=%6.3f d=%5.2f  s=%9.3f\n",FR(ihop-1),D1(ihop-1),S(ihop-1));
              if (f2*f3<.0)
              {
                  MySoltA *mySoltA=new MySoltA(f,t,fh,h,dh,dh2,d,alfa0,ihop,delt,eps,ep,ep1,n,epsa,aa0,this->putdat+ihop*nK);
                  PUTDAT* putdat=this->putdat+ihop*nK;
                  for(int i=0; i<ihop; i++)
                  {
                      IOX(i)=iox;
                      FR(i)=f;
                      TIME(i)=t;
                      D1(i)=D2(i)=.0;
                      S(i)=.0;
                  }
                  nK++;
                  TrekThread *trekThread=new TrekThread(this, mySoltA, d2, f2, d3, f3);
                  vTrekThread.push_back(trekThread);
                  trekThread->start();
                  if (flagMpch)
                      break;
              }
          }
  }
  if (!nK)
  {
      PUTDAT* putdat=this->putdat+ihop*nK;
      for(int i=0; i<ihop; i++)
      {
          IOX(i)=iox;
          FR(i)=f;
          TIME(i)=t;
          D1(i)=D2(i)=.0;
          S(i)=.0;
      }
  }

  // удаление всех созданных нитей
  if (!vTrekThread.empty())
  {
      vector <TrekThread *>::const_iterator itv;
      for(itv=vTrekThread.begin(); itv!=vTrekThread.end(); itv++)
      {
          TrekThread *p=*itv;
          p->wait();
          delete (p->getMySoltA());
          delete p;
      }
  }
  vTrekThread.clear();

  // удаление всех временных PUTDAT, помещенных в set
  if (!sPutDat.empty())
  {
      for(its=sPutDat.begin(); its!=sPutDat.end(); its++)
      {
            PUTDAT *item=*its;
            delete[] item;
      }
  }
  sPutDat.clear();

  for(int k=0; k<nK; k++)
  {
      PUTDAT* putdat=this->putdat+ihop*k;
      if (S(ihop-1)>maxS)
          maxS=S(ihop-1);
  }

  gettimeofday(&tv,NULL);
  T2=tv.tv_sec+tv.tv_usec/1000000.0;
  DT=T2-T1;

  //printf("\ntime,ms=%8.3f\n",DT*1000.);
  //fflush(stdout);
  // число найденных корней может быть меньше nK - число интервалов, которые могут содержать корни
  return nK;
} /* solt */

#define MAXIT 20

double TrekThread::zero_t(double a,
                          double fa,
                          double b,
                          double fb,
                          double s0,
                          double alfa,
                          long   ihop,
                          double tol,
                          double epsa,
                          double aa0,
                          PUTDAT *putdat)
/*******************************************************************/
/*                                                                 */
/*      Предназначена для отыскания действительного корня          */
/*   нелинейного уравнения с заданной точностью (Форсайт           */
/*   Дж.,Малькольм М.,Моулер К. Машинные методы  математических    */
/*   вычислений:Пер. с англ.-М.:Мир,1980.-290с.). Комбинируются    */
/*   разные алгоритмы  уменьшения исходного отрезка (метод         */
/*   бисекций  и метод секущих), что обеспечивает быструю          */
/*   сходимость итерационного процесса при минимальном             */
/*   количестве вычислений функции f(x).                           */
/*                                                                 */
/*   a   - левый конец исходного интервала;                        */
/*   fa  - значение функции в точке a;                             */
/*   b   - правый конец исходного интервала;                       */
/*   fb  - значение функции в точке b;                             */
/*   fr  - рабочая частота;                                        */
/*   s0  - длина трассы;                                           */
/*   ihop- число скачков;                                          */
/*   tol - выражение, указывающее максимальную длину интервала     */
/*         неопределенности отыскиваемого действительного корня.   */
/*                                                                 */
/*   Функция возвращает в качестве значения типа double            */
/*   найденный ею корень. Пользователь должен перед обращением     */
/*   к функции определить концы отрезка [a,b] так, чтобы функция,  */
/*   вычисленная при этих значениях аргумента, была разного знака. */
/*   Если корень не найден в пределах допустимой точности,         */
/*   то функция возвращает отрицательное значение.                 */
/*                                                                 */
/*VGG  версия 14.05.93                                             */
/*******************************************************************/

{
  double eps,e,fx,tol1,xm,pp,q,s,r;
  double d7,s1,pgg,pg,df,ls,x,del;
  int    koli,no;


  koli=0;

  /* определение машинной точности */
/*
  eps=1;
  while(1.+.5*eps>1.) eps *=.5;
*/
  eps=.1e-18;

  while(1)
    { /* wh */
      x=a;
      fx=fa;
      del=b-a;
      e=del;
      while (fb*fx<=.0)
      { /* do */
          if (fabs(fx)<fabs(fb))
            {
              a=b; fa=fb;
              b=x; fb=fx;
              x=a; fx=fa;
            }

          /* проверка сходимости */
          tol1=2.*eps*fabs(b)+1.e-14;
          xm=.5*(x-b);

          if (fabs(fb)<tol)
          {
              return b;
          }

          if (fabs(xm)<=tol1 || koli>MAXIT)
          {
              //printf("\nxm=%e  tol1=%e  koli=%d   b=%6.2f",xm,tol1,koli,-b/RAD);
              return -b;
          }

          /* необходиама ли бисекция */
          if (fabs(e)<tol1 || fabs(fa)<=fabs(fb))
            {
              del=xm;
              e=del;
            }
          else
            { /* возможна ли квадратичная интерполяция */
              if (a==x)
                { /* линейная интерполяция */
                  s=fb/fa;
                  pp=2.*xm*s;
                  q=1.-s;
                }
              else
                { /* обратная квадратичная интерполяция */
                  q=fa/fx;
                  r=fb/fx;
                  s=fb/fa;
                  pp=s*(2.*xm*q*(q-r)-(b-a)*(r-1.));
                }
              /* выбрать знаки */
              if (pp>.0) q=-q;
              pp=fabs(pp);
              /* приемлима ли интерполяция */
              if (2.*pp<3.*xm*q-fabs(tol1)*q && pp<fabs(e*q*.5))
                {
                  e=del;
                  del=pp/q;
                }
              else
                { /* бисекция */
                  del=xm;
                  e=del;
                }
            } /* возможна ли квадратичная интерполяция */
          /* завешить шаг */
          a=b;
          fa=fb;
          if (fabs(del)>tol1) b +=del;
          else
            if (xm<.0)      b -=fabs(tol1);
            else            b +=fabs(tol1);

          /* пропускаются значения углов места, где дальность  */
          /* не может быть вычислена                           */
          mySoltA->setD0(b);
          no=mySoltA->soltA();
          mySoltA->setResult(no);
          //PUTDAT *putdat=mySoltA->getPutDat();
          while(no && koli<=MAXIT)
          {
              koli++;
              if (fa>.0)
                {
                  a=b;
                  fa=400.;
                  b=.5*(b+x);
                }
              else
                {
                  x=b;
                  fx=400.;
                  b=.5*(a+b);
                }
              if (keysol>0)
              {
                  printf(FORM2,b/RAD,D2(ihop-1),S(ihop-1),koli,no);
              }
              mySoltA->setD0(b);
              no=mySoltA->soltA();
              mySoltA->setResult(no);
          }

          koli++;

          s1=S(ihop-1);

          if (keysol>0)
          {
              printf(FORM2,b/RAD,D2(ihop-1),s1,koli,no);
          }

          fb=s1*.01-s0;

        } /* do */
    } /* wh */
} /* zero_t */
