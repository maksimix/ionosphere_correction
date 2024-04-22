#include <math.h>

long progon(double *x,
            double *a,
            double *b,
            double *c,
            double *d,
            long   n,
            double eps)
/************************************************************/
/*                                                          */
/*       ποδπςοηςαννα ςεϋεξιρ μεξτοώξοκ σιστενω υςαχξεξικ   */
/*                  νετοδον πςοηοξλι.                       */
/*        a(i)*x(i-1)-b(i)*x(i)+c(i)*x(i+1)-d(i)            */
/*                                                          */
/*           ηδε 0<= i <n,  c(n-1)=a(0)=0                   */
/*                                                          */
/* ζυξλγιρ χοϊχςαύαετ 1, εσμι σιστενα ξε ινεετ              */
/*                       εδιξστχεξξοηο ςεϋεξιρ, ιξαώε - 0   */
/*                                                          */
/*        ςεϋεξιε πονεύρετσρ χ νασσιχ x(n)                  */
/*VGG                                                       */
/************************************************************/
{
    double r;
    double *psi;
    double *teta;
    long   i;

    teta=new double[n+1];
    psi =new double[n+1];
    
    for(i=0; i<=n; i++)
      {
        psi[i]=.0;
        teta[i]=.0;
      }

    for(i=0; i<n; i++)
      {
        r=b[i]-a[i]*psi[i];

        if (fabs(r)<eps) return 1;

        psi[i+1]=c[i]/r;
        teta[i+1]=(a[i]*teta[i]-d[i])/r;
      }

    x[n-1]=teta[n];

    for(i=n-1; i>0; i--)
      x[i-1]=psi[i]*x[i]+teta[i];

    delete[] psi;
    delete[] teta;

    return 0;
} /* progon */
