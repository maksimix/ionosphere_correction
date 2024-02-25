#include "paths.h"

#define M 2 /* количество монотонных шагов */
#define EPS .17e-9
#define MAXIT0 5000

//long kkk;

#define FORM1 "\nd8,d7,s,fr,hop,no %12.8f%7.2f%13.6f%8.2f%3d%3d"
#define FORM2 "\nd6,d7,s,koli,no %12.8lf%7.2lf%13.6lf%3d%3d"

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
          PUTDAT *putdat)
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
/* dd   - начальный шаг по углу,                               */
/*                                                             */
/*VGG  версия 14.06.06                                         */
/***************************************************************/

{
  long    n,io,no,nl;
  double f2,f3,d2,d3,d6,d7,d8,s,s1,s2,
      p,pg,df,ls,dd,alfa;
  int koli=0;
  int key=0;
  //keytr=0;
  io=n=0;
  s=s2=.0;
  f2=f3=d2=d3=.0;
  d8=d0+dd0;
  dd=-dd0;

  /* вычисление дальности при начальном угле вылета             */
  /* key - -1 - точка отражения левее,                          */
  /*        1 - правее области задания ионосферы,               */
  /*        0 - точка отражения внутри области;                 */
  /* no  -  0 - имеются отражения на всех скачках,              */
  /*        1 - просачивание или                                */
  /*            после отражения лучевая траектория не приходит  */
  /*            на поверхость Земли;                            */
// спускаемся по углу излученея до тех пор, пока
// дальность по Земле не станет больше длины трассы

  //printf("\n1 keytr=%d",keytr);
  alfa=alf0;
  do
  {
      d8+=dd;
      //printf("\n1 d8=%f",d8/RAD);
      if (d8<.0)
      {
          io=1;
          d8-=dd;
          break;
      }
      //no=treks(d8,alfa,ihop,6,delt,eps,ep,ep1,e,putdat+ihop*n);
      no=soltA(d8,alfa,ihop,delt,eps,ep,ep1,e,epsa,aa0,putdat+ihop*n);
      s=S(ihop*n+ihop-1);
      d7=D2(ihop*n+ihop-1)*RAD;

      if (keysol>0)
      {
          printf(FORM1,d8/RAD,d7/RAD,s,fr,ihop,no);
      }

      s *=.01;
  }
  while(s<s0 && !no);

  //printf("\n0  d0=%f alfa=%f dd=%f s=%f no=%d",d8/RAD,alfa/RAD,dd/RAD,s*100.,no);
  fflush(stdout);

  if (no==-1)
  {
      //return n;
      dd=-dd;
      io=0;
      while(no==-1 && d8<PI05 && d8>-PI05)
      {
          d8+=dd;
          no=soltA(d8,alfa,ihop,delt,eps,ep,ep1,e,epsa,aa0,putdat+ihop*n);
          s=S(ihop*n+ihop-1);
          d7=D2(ihop*n+ihop-1)*RAD;
    
          if (keysol>0)
          {
              printf(FORM1,d8/RAD,d7/RAD,s,fr,ihop,no);
              printf("\ndd=%f",dd/RAD);
          }
          s *=.01;
      }
  }
  else
      if (!io)
         dd=-dd;
  //printf("\n1  d0=%f alfa=%f dd=%f",d8/RAD,alfa/RAD,dd/RAD);
  fflush(stdout);
  while (fabs(dd)>EPS && koli<MAXIT0)
  {
      koli++;
      if (s<eps2 || d8>d1)
      {
          return n;
      }

      if (s<=s0)
        {
          d2=d8;
          f2=s-s0;
        }
      else
        {
          d3=d8;
          f3=s-s0;
        }
      //printf("\n2 d0=%f alfa=%f dd=%f f2=%f f3=%f",d8/RAD,alfa/RAD,dd/RAD,f2,f3);
      if (f2*f3<.0)
      { /* yes */
          /* если на границах отрезка [d2,d3], на котором, возможно, */
          /* имеется корень, структура лучевых траекторий, опреде-   */
          /* ляемая параметрами соответственно m2 и m3, различна,    */
          /* то предпринимается попытка делением этого отрезка на 2  */
          /* локализовать корень так, чтобы m2=m3.                   */
          /* Если это удается, то далее корень находится функцией    */
          /* zero_t.c. В противном случае продолжается поиск интер-  */
          /* валов подозрительных на наличие корней.                 */

          if ((d6=zero_t(d2,f2,d3,f3,s0,alfa,ihop,delt,eps,ep,ep1,e,eps1,epsa,aa0,putdat+ihop*n))>=.0)
            {
              if (keysol<0) keytr=-1;
              //keytr=1;
              //no=treks(d6,alfa,ihop,21,delt,eps,ep,ep1,e,putdat+ihop*n);
              //no=treks(d6,(AT(ihop*n+ihop-1)-DEV(ihop*n+ihop-1))*RAD,ihop,22,delt,eps,ep,ep1,e,putdat+ihop*n);
              //printf("\n2  d6=%6.3f  d7=%6.3f  s=%8.3f dd=%6.3f  io=%2d  no=%2d Alf=%8.3f",d6/RAD,D2(ihop*n+ihop-1),S(ihop*n-1),dd/RAD,io,no,(AT(ihop*n+ihop-1)-DEV(ihop*n+ihop-1)));
              //keytr=-1;
              no=treks(d6,A1(ihop*n)*RAD,ihop,22,delt,eps,ep,ep1,e,putdat+ihop*n);
              //keytr=0;
              if (keysol>0 || keysol<0)
              {
                   printf("\n2  d6=%6.3f d6=%6.3f d7=%6.3f  s=%8.3f dd=%6.3f  io=%2d  no=%2d Alf=%8.3f",
                          d6/RAD,D1(ihop*n),D2(ihop*n+ihop-1),S(ihop*n+ihop-1),dd/RAD,io,no,A1(ihop*n));
              }
              //keytr=0;
              if (keysol<0) keytr=0;

              //printf("\nd1=%f d2=%f S=%f P=%f Pg=%f",d6/RAD,D2(ihop*n+ihop-1),
              //       S(ihop*n+ihop-1),P(ihop*n+ihop-1),PG(ihop*n+ihop-1));
//            FILE *out;
//            out=fopen("proba.dat","at");
//            fprintf(out,"\nfr=%6.2f p=%10.4f pg=%10.4f df=%6.3f",fr,p,pg,df);
//            fclose(out);
/*
              double s2,dssl,dd=.00001;
              kkk=1;
              no=treki(fr,d6+dd,ihop,10,delt,eps,e,
                       &s2,&d7,&p,&pg,&df,&ls,&m_l);
              dssl=(s2-s1)/dd;
              dssl=10.*log10(fabs(100.*R0*sin(s1/(100.*R0))*sin(d7)/cos(d6)*dssl));
              printf("\nls=%6.2f  dssl=%6.2f",ls,dssl);
              printf("\ndssl=%6.2f",dssl*sin(d7));
              kkk=0;
*/
              for(nl=0; nl<ihop; nl++)
              {
                  dhopk[n][nl][0]=dhop[nl][0];
                  dhopk[n][nl][1]=dhop[nl][1];
                  refk[n][nl]    =ref[nl];
                  FHhopk[n][nl][0]=FHhop[nl][0];
                  Ihopk[n][nl][0] =Ihop[nl][0];
                  Dhopk[n][nl][0] =Dhop[nl][0];
                  FHhopk[n][nl][1]=FHhop[nl][1];
                  Ihopk[n][nl][1] =Ihop[nl][1];
                  Dhopk[n][nl][1] =Dhop[nl][1];
              }
              n++;
              if (n==21)
              {
                  return n;
              }
            }
          f2=f3=d2=d3=.0;
      } /* yes */
      else
      { /* no */
          do
          {
              koli++;
              if (io)
              {
                  dd*=.5;
                  if (no==1)
                      d8-=dd;
                  else
                  {
                      if (dd<.0)
                      {
                          d8+=dd;
                          while(d8<.0 && fabs(dd)>EPS)
                          {
                              dd*=.5;
                              d8-=dd;
                          }
                      }
                      else
                          d8+=dd;
                  }
              }
              else
                  d8+=dd;

              //printf("\nd0=%f alfa=%f dd=%f",d8/RAD,alfa/RAD,dd/RAD);
              //no=treks(d8,alfa,ihop,6,delt,eps,ep,ep1,e,putdat+ihop*n);
              no=soltA(d8,alfa,ihop,delt,eps,ep,ep1,e,epsa,aa0,putdat+ihop*n);
              s=S(ihop*n+ihop-1);
              d7=D2(ihop*n+ihop-1)*RAD;

              if (keysol>0)
                printf(FORM1,d8/RAD,d7/RAD,s,-fr,ihop,no);
              s *=.01;

              if (no==1 && !io) io=1;

          }
          while (no && fabs(dd)>EPS && koli<MAXIT0);

      } /* no */
  }

  return n;
} /* solt */

#define MAXIT 20

double zero_t(double a,
              double fa,
              double b,
              double fb,
              double s0,
              double alfa,
              long   ihop,
              double delt,
              double epst,
              double ep,
              double ep1,
              double et,
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
              //printf("\nxm=%e  tol1=%e  koli=%d",xm,tol1,koli);
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
          while((no=soltA(b,alfa,ihop,delt,epst,ep,ep1,et,epsa,aa0,putdat))
                //(no=treks(b,alfa,ihop,6,delt,epst,ep,ep1,et,putdat))
                && koli<=MAXIT)
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
                printf(FORM2,b/RAD,D2(ihop-1),S(ihop-1),koli,no);
          }

          koli++;

          s1=S(ihop-1);

          if (keysol>0)
            printf(FORM2,b/RAD,D2(ihop-1),s1,koli,no);

          fb=s1*.01-s0;

        } /* do */
    } /* wh */
} /* zero_t */
