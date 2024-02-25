#ifndef __ANTENN_H

#define __ANTENN_H

#ifndef _STDIO_H_INCLUDED
#include <stdio.h>
#endif

typedef struct     /* описание антенны на передаче                       */
  {                /*                                                    */
    long   type;   /* тип антенны                                        */
    double eps;    /* относительная диэлектрическая проницаемость почвы  */
    double sig;    /* удельная проводимость почвы                        */
    double l;      /* длина вибратора                                    */
    double h;      /* высота подвеса аннтенны или точки ее питания       */
    double psi;    /* угол наклона луча к горизонтальной плоскости       */
    double fi;     /* азимутальный угол                                  */
  } ANT_TRAN;

typedef struct     /* описание антенны на приеме                         */
  {                /*                                                    */
    long   type;   /* тип антенны                                        */
    long   n;      /* число вибраторов для БС                            */
    double eps;    /* относительная диэлектрическая проницаемость почвы  */
    double sig;    /* удельная проводимость почвы                        */
    double l;      /* длина вибратора                                    */
    double h;      /* высота подвеса аннтенны или точки ее питания       */
    double psi;    /* угол наклона луча к горизонтальной плоскости       */
    double fi;     /* азимутальный угол                                  */
    double rs;     /* сопротивление резистора, включенного в плече       */
    double ll;     /* расстояние между вибраторами по фидеру             */
  } ANT_REC;

#define TYPE1 a1->type
#define EPS1  a1->eps
#define SIG1  a1->sig
#define LA1   a1->l
#define H1    a1->h
#define FI1   a1->fi
#define PSI1  a1->psi

#define TYPE2 a2->type
#define EPS2  a2->eps
#define SIG2  a2->sig
#define LA2   a2->l
#define H2    a2->h
#define FI2   a2->fi
#define PSI2  a2->psi
#define RS    a2->rs
#define LL    a2->ll
#define NA    a2->n

void abspol(double    fr, double    alf1,  double alf2,
            long       ox, long       hop, long       n,
            ANT_TRAN  *a1,
            ANT_REC   *a2,
            double    *lp, double    *lr, double    *ku, double    *knd,
            double    *mm, double    *psi);

void get_ant(FILE *in,
             FILE *out,
             ANT_TRAN *a1,
             ANT_REC  *a2);

void  bs (long n, double l, double rs, double l1, double h,
          double eps, double sig, double f, double d, double fi,
          double *d1, double *d2, double *d3);

void ellips (double f, double delta, double eps, double sig,
             double la, double hk, double psi, double fi,
             double *m, double *alfa, double *g);

void  rebeam (double f,double t, double m, double alfa,
              double eps, double sig, double la, double h,
              double psi, double fi, double *d);

void  recant (double f, double t, double m, double alfa, double eps,
              double sig, double la, double h, double fi, double *d);

void  trant (double f, double t, double eps, double sig,
             double la, double h, double fi,
             double *m, double *alfa, double *g);

void loop(double f, double t, double m, double alfa,
          double eps, double sig, double h, double *d);

void rerth (double f, double t, double m, double alfa, double eps,
            double sig, double *d, double *mo, double *psi);

#endif