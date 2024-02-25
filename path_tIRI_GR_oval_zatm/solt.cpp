#include "ray.h"

#define M 2 /* количество монотонных шагов */
#define EPS .17e-6

//long kkk;

#define FORM1 "\nd8,d7,s,fr,hop %12.8f%7.2f%13.6f%7.3f%3d"
#define FORM2 "\nd6,d7,s,koli %12.8lf%7.2lf%13.6lf\
%3d"

long solti(double *d0,
          double *d1,
          double fr,
          double s0,
          long    ihop,
          double delt,
          double eps,
          double e,
          double eps1,
          double eps2,
          double dd0,
          double *di,
          double *dk,
          double *pgr,
          double *pgg,
          double *dff,
          double *sl,
          unsigned long   *m_laey)
/***************************************************************/
/*                                                             */
/* Функция находит все решения граничной задачи s(d)=s0  и     */
/* возвращает количество этих решений.                         */
/*                                                             */
/* d0   - левая граница отрезка, на котором ищатся решения,    */
/* d1   - правая граница этого отрезка,                        */
/* fr   - рабочая частота,                                     */
/* s0   - длина трассы,                                        */
/* ihop - число скачков,                                       */
/* eps1 - точность решения уравнения,                          */
/* eps2 - ограничение поиска корней по минимальной дальности,  */
/* dd   - начальный шаг по углу,                               */
/* di[] - массив углов вылета для решений,                     */
/* dk[] - угла прихода для всех решений,                       */
/* pgr[]- значения группового пути,                            */
/* pgg[]- значения фазового пути,                              */
/* sl[] - значения пространственного ослабления,               */
/* m_laey[] - описывает структуру отражений для всех решений.  */
/*                                                             */
/*VGG  версия 14.05.93                                         */
/***************************************************************/

{
  long    n,io,no,nl,io_key,ang_key;
  double f2,f3,d2,d3,d6,d7,d8,s,s1,s2,
         p,pg,df,ls,dd;
  unsigned long   m_l;

  io=n=0;
  io_key=-M; /* если io_key=0, то это означает, что при делении      */
             /* угла растояние монотонно возрастает в окрестности    */
             /* просачивания и превышает всегда s0                   */
  ang_key=0; /* 1, если для начального угла излучения нет отражений, */
             /*    а для первого угла, при котором есть отражения    */
             /*    расчитанная дальность меньше s0                   */
  s=s2=.0;
  f2=f3=d2=d3=.0;
  d8=*d0+dd0;
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

  do
    {
      d8 +=dd;
      no=treki(fr,d8,ihop,6,delt,eps,e,&s,&d7,&p,&pg,&df,&ls,&m_l);

      if (keysol>0)
        printf(FORM1,d8/RAD,d7/RAD,s,fr,ihop);

      s *=.01;
    }
  while(s<s0 && (d8>.0 || d7>PI5) && !no || key<0);
  //while(s<s0 && (d8>PI5 || d7>PI5) && !no || key<0);

  if (no && !key) return n;

  dd=-dd;

  while (no)
    {
      if (io) dd *=.5;
      d8 +=dd;
      no=treki(fr,d8,ihop,6,delt,eps,e,&s,&d7,&p,&pg,&df,&ls,&m_l);
      if (keysol>0)
        printf(FORM1,d8/RAD,d7/RAD,s,fr,ihop);
      s *=.01;
      if (no && !key || fabs(dd)<EPS) return n;
      if (key==-1)
        {
          d8 -=dd;
          io=1;
        }
      if (!no && s<=s0)
        {
          d2=d8;
          f2=s-s0;
          ang_key=1;
        }
    }

  if (ang_key)
    {
      d3=d8-dd;
      while (f3<=0)
        {
          d6=.5*(d2+d3);
          if (fabs(d6-d3)<EPS) break;
          no=treki(fr,d6,ihop,6,delt,eps,e,&s1,&d7,&p,&pg,&df,&ls,&m_l);
          if (keysol>0)
            printf(FORM1,d8/RAD,d7/RAD,s1,fr,ihop);
          s1 *=.01;
          if (no)
            {
              d3=d6;
              continue;
            }
          if (s1<=s0)
            {
              d2=d6;
              f2=s1-s0;
            }
          else
            {
              d3=d6;
              f3=s1-s0;
            }
        }
      *d0=d3;
      d8 =d2;
      s  =s0+f2;
    }
  else
    *d0=d8;

  while (fabs(dd)>EPS && (!io || io_key))
    {
      if (s<eps2 || d8>*d1) return n;

      if (ang_key)
        ang_key=0;
      else
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

          if ((d6=zero_t(d2,f2,d3,f3,fr,s0,ihop,delt,eps,e,eps1,&m_l))>=.0)
            {
              if (keysol<0) keytr=-1;
              no=treki(fr,d6,ihop,10,delt,eps,e,
                       &s1,&d7,&p,&pg,&df,&ls,&m_l);
              if (keysol<0) keytr=0;

              *(pgr+n)=p;
              *(pgg+n)=pg;
              *(di+n) =d6;
              *(dk+n) =d7;
              *(dff+n)=df;
              *(sl+n) =ls;
              *(m_laey+n)=m_l;
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
                  suchk[n][nl][0]=such[nl][0];
                  suchk[n][nl][1]=such[nl][1];
                }
              n++;
              if (n==10) return n;
            }
          f2=f3=d2=d3=.0;
        } /* yes */
      else
        { /* no */
          do
            {
              if (d8<.0 && d8>dd || no && (io || key<=0))
                        { io=1; d8 -=dd; dd *=0.5; }
              else
                if (io) dd *=0.5;

              d8 +=dd;

              no=treki(fr,d8,ihop,6,delt,eps,e,&s,&d7,&p,&pg,&df,&ls,&m_l);

              if (keysol>0)
                printf(FORM1,d8/RAD,d7/RAD,s,fr,ihop);
              s *=.01;

              if (no && !key && !io) io=1;

              if (no && key>0 && ihop>1 &io)
                io_key++;

              if (!no && io)
                if (s>s0 && s>s2)
                  { s2=s;  io_key++; }
                else
                  { s2=.0; io_key=-M; }
            }
          while (no && fabs(dd)>EPS && (!io || io_key));

        } /* no */
    }

  return n;
} /* solt */

#define MAXIT 20

double zero_t(double a,
              double fa,
              double b,
              double fb,
              double fr,
              double s0,
              long    ihop,
              double delt,
              double epst,
              double et,
              double tol,
              unsigned long *m_l)
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
  double e,eps,fx,tol1,xm,pp,q,s,r;
  double d7,s1,pgg,pg,df,ls,x,del;
  long   koli;

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
            return b;
          if (fabs(xm)<=tol1 || koli>MAXIT)
            return -b;

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
          while(treki(fr,b,ihop,6,delt,epst,et,&s1,&d7,&pg,&pgg,&df,&ls,m_l)
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
                printf(FORM2,b/RAD,d7/RAD,s1,koli);
            }

          koli++;

          if (keysol>0)
            printf(FORM2,b/RAD,d7/RAD,s1,koli);

          fb=s1*.01-s0;

        } /* do */
    } /* wh */
} /* zero_t */