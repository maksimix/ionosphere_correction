#ifndef _IRI_H
#define _IRI_H

/*
#include "../../f2c/f2c.h"

extern "C"
{
  int iri_sub_ne__(logical *jf, integer *jmag, doublereal *alati, doublereal *along, integer *iyyyy,
                   integer *mmdd, doublereal *dhour,
                   doublereal *heibeg, doublereal *heiend, doublereal *heistp,
                   doublereal *outf, doublereal *oarr);
  int iri_sub__(logical *jf, integer *jmag, doublereal *alati, doublereal *along, integer *iyyyy,
                integer *mmdd, doublereal *dhour,
                doublereal *heibeg, doublereal *heiend, doublereal *heistp,
                doublereal *outf, doublereal *oarr);

  int fieldg_(doublereal *dlat, doublereal *dlong, doublereal *alt, doublereal *x, doublereal *y,
              doublereal *z__, doublereal *f, doublereal *dip, doublereal *dec, doublereal *smodip);
  int initialize_();
}
*/

extern "C"
{
#ifdef Fortran_G77
int iri_sub__(int *jf, int *jmag, float *alati, float *along, int *iyyyy, // g77
                int *mmdd, float *dhour,
                float *heibeg, float *heiend, float *heistp, float *outf, float *oarr);
#else
int iri_sub_(int *jf, int *jmag, float *alati, float *along, int *iyyyy,
                int *mmdd, float *dhour,
             float *heibeg, float *heiend, float *heistp, float *outf, float *oarr);
int iri_web_(int *jmag,int *jf, float *alati, float *along, int *iyyyy,
             int *mmdd, int *iut, float *dhour,
             float *height, float *h_tec_max, int *ivar, float *vbeg, float *vend, float *vstp,
             float *a, float *b);
#endif

void gtd7_(int *iyd, float *sec,float *alt,float *lat,float *lon,float *hour,float *f107a,float *f107,float *ap,int *mass,float *d__,float *t);

int fieldg_(float *dlat, float *dlong, float *alt, float *x, float *y,
              float *z__, float *f, float *dip, float *dec, float *smodip);
void my_initial_();
void read_ig_rz_();
void readapf107_();
void readJF(int *jf);
}

#endif
