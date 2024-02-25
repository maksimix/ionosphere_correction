#include <math.h>

void  trant (double f, double t, double eps, double sig,
             double la, double h, double fi,
             double *m, double *alfa, double *g)
/***********************************************************/
/*               Входные параметры                         */
/*                                                         */
/*   f    -  рабочая частота,(Мгц)                         */
/*   t    -  угол вылета,(рад)                             */
/*   eps  -  диэлектрическая проницаемость почвы           */
/*   sig  -  удельная проводимость почвы,(Сим/м)           */
/*   la   -  длина одного плеча диполя,(м)                 */
/*   h    -  высота подвеса диполя,(м)                     */
/*   fi   -  азимутальный угол,(рад)                       */
/*                                                         */
/*               Выходные параметры                        */
/*                                                         */
/*   m    -  отношение осей эллипса поляризации            */
/*                     излучаемой волны (со знаком)        */
/*   alfa -  угол наклона большой оси эллипса поляризации  */
/*                      к плоскости распространения,(рад)  */
/*   g    -  коэффициент усиления антенны,(раз)            */
/***********************************************************/
{
 long i;
 double mv,mg,mvsq,mgsq,ll,dmax,sgg,sga,cf,sf,cg,sg,al,al1,tp,root,gam;
 double pi=3.1415926535;
 double a[10]={0.,.1,.2,.3,.4,.47,.5,.54,.6,.64},
       b[10]={.9,.95,1.025,1.1,1.275,1.5,1.6,1.725,1.5,1.15};
 extern void dipole(double f,double t,double eps,double sig,
                    double la,double h,double cf,double sf,
                    double *mv,double *mg,double *gam);
  ll=la*f/300.;
  if (ll < a[0] || ll > a[9])
     {*alfa=0.;
      *m=0.;
      *g=0.;
      return;
     }
   else
     {for (i=0; i<9; i++)
       {if (ll >= a[i] && ll <= a[i+1])
           {dmax=b[i]+(ll-a[i])*(b[i+1]-b[i])/(a[i+1]-a[i]);
            break;
           }
       }
     }
  cf=cos(fi);
  sf=sin(fi);
  dipole(f,t,eps,sig,la,h,cf,sf,&mv,&mg,&gam);
  cg=cos(gam);
  sg=sin(gam);
  mgsq=mg*mg;
  mvsq=mv*mv;
  if (cg == 0.)
      sgg=0.;
    else
      sgg=(cg > 0.) ? 1. : -1.;
  if (mvsq == mgsq)
      al=pi*sgg/4.;
    else
      {al1=atan(2.*mv*mg*cg/(mgsq-mvsq))/2.;
       if (mgsq > mvsq)
           al=al1;
         else
           al=(fabs(cg) < 1e-6) ? pi/2. : al1+sgg*pi/2.;
      }
  if (mvsq == 0.)
      *m=0.;
    else
      {
       tp=1.+mgsq/mvsq;
       root=sqrt(fabs(tp*tp-(2.*sg*mg/mv)*(2.*sg*mg/mv)));
       *m=sqrt(fabs((tp-root)/(tp+root)));
      }
  if (al == 0.)
      sga=0.;
    else
      sga=(al > 0.) ? 1. : -1.;
  if (al == 0.)
      *alfa=pi/2.;
    else
      *alfa=pi/2.*sga-al;
  *g=dmax*(mvsq+mgsq);
  *m=(gam < 0.) ? -(*m) : *m;
  return;
 }
