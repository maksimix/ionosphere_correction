/* cira.f -- translated by f2c (version 20000121).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    doublereal umr;
} const_;

#define const_1 const_

struct {
    doublereal hr, dr;
} const1_;

#define const1_1 const1_

/* cira.for, version number can be found at the end of this comment. */
/* ----------------------------------------------------------------------- */

/*   Calculates neutral temperature parameters for IRI using the */
/*   MSIS-86/CIRA 1986 Neutral Thermosphere Model. The subroutines */
/*   GTS5, GLOBE5 and GLOBL5 developed by A.E. Hedin (2/26/87) were */
/*   modified for use in IRI --------- D. Bilitza -------- March 1991 */

/* Corrections */
/* 11/09/99 always calculated Legendre; 'if glat' and 'if stl' taken out */
/* 11/09/99 use UMR, dumr and humr from COMMON */
/* Version-mm/dd/yy------------------------------------------------- */
/* 2001.01 05/07/01 start of versioning */
/* 2002.01 28/10/02 replace TAB/6 blanks, enforce 72/line (D. Simpson) */
/* 2007.00 05/18/07 Release of IRI-2007 */
/* ----------------------------------------------------------------------- */

/* Subroutine */ int cira86_(iday, sec, glat, glong, stl, f107a, tinf, tlb, 
	sigma)
integer *iday;
doublereal *sec, *glat, *glong, *stl, *f107a, *tinf, *tlb, *sigma;
{
    /* Initialized data */

    static doublereal xl = 1e3;
    static doublereal tll = 1e3;

    /* Builtin functions */
    double sin(), cos();

    /* Local variables */
    static doublereal c__, s, ctloc, stloc, c2, c4, f1, f2, f3, g0, s2, t1, 
	    t2, t3, t5, t4, t7, t8, z1, z2, c2tloc, c3tloc, s2tloc, s3tloc, 
	    t11, t12, t14, t71, t72, t81, t82, sr, zz, cd9, dr2, cd11, dfa, 
	    cd14, cd32, cd18, cd39, plg[36]	/* was [9][4] */, t7814;

/* ----------------------------------------------------------------------- */

/*     INPUT: */
/*        IDAY - DAY OF YEAR */
/*        SEC - UT(SEC) */
/*        GLAT - GEODETIC LATITUDE(DEG) */
/*        GLONG - GEODETIC LONGITUDE(DEG) */
/*        STL - LOCAL APPARENT SOLAR TIME(HRS) */
/*        F107A - 3 MONTH AVERAGE OF F10.7 FLUX */

/*     OUTPUT: */
/*        TINF - EXOSPHERIC TEMPERATURE (K) */
/*        TLB - TEMPERATURE AT LOWER BOUNDARY (K) */
/*        SIGMA - SHAPE PARAMETER FOR TEMPERATURE PROFILE */

/* ----------------------------------------------------------------------- */
/*      data umr/1.74E-2/,hr/0.2618/,dr/1.74e-2 */
/* DR,DR2/1.72142E-2,0.0344284/, */
/* SR/7.2722E-5/, */
/* ,HR/.2618/ */
/* ,DGTR/1.74533E-2/ */
/*       dr = hr * 24. / 365. */

    dr2 = const1_1.dr * 2.;
    sr = const1_1.hr / 3600.;

/* CALCULATE LEGENDRE POLYNOMIALS */

    if (xl == *glat) {
	goto L15;
    }
    c__ = sin(*glat * const_1.umr);
    s = cos(*glat * const_1.umr);
    c2 = c__ * c__;
    c4 = c2 * c2;
    s2 = s * s;
    plg[1] = c__;
    plg[2] = (c2 * 3. - 1.) * .5;
    plg[3] = (c__ * 5. * c2 - c__ * 3.) * .5;
    plg[4] = (c4 * 35. - c2 * 30. + 3.) / 8.;
    plg[5] = (c2 * 63. * c2 * c__ - c2 * 70. * c__ + c__ * 15.) / 8.;
    plg[10] = s;
    plg[11] = c__ * 3. * s;
    plg[12] = (c2 * 5. - 1.) * 1.5 * s;
    plg[13] = (c2 * 7. * c__ - c__ * 3.) * 2.5 * s;
    plg[14] = (c4 * 21. - c2 * 14. + 1.) * 1.875 * s;
    plg[15] = (c__ * 11. * plg[14] - plg[13] * 6.) / 5.;
    plg[20] = s2 * 3.;
    plg[21] = s2 * 15. * c__;
    plg[22] = (c2 * 7. - 1.) * 7.5 * s2;
    plg[23] = c__ * 3. * plg[22] - plg[21] * 2.;
    plg[30] = s2 * 15. * s;
    plg[31] = s2 * 105. * s * c__;
    plg[32] = (c__ * 9. * plg[31] - plg[30] * 7.) / 2.;
    plg[33] = (c__ * 11. * plg[32] - plg[31] * 8.) / 3.;
    xl = *glat;
L15:
    if (tll == *stl) {
	goto L16;
    }
    stloc = sin(const1_1.hr * *stl);
    ctloc = cos(const1_1.hr * *stl);
    s2tloc = sin(const1_1.hr * 2. * *stl);
    c2tloc = cos(const1_1.hr * 2. * *stl);
    s3tloc = sin(const1_1.hr * 3. * *stl);
    c3tloc = cos(const1_1.hr * 3. * *stl);
    tll = *stl;
L16:

    dfa = *f107a - 150.;

/* EXOSPHERIC TEMPERATURE */

/*         F10.7 EFFECT */
    t1 = (.00311701 - dfa * 6.4111e-6) * dfa;
    f1 = dfa * .00426385 + 1.;
    f2 = dfa * .00511819 + 1.;
    f3 = dfa * .00292246 + 1.;
/*        TIME INDEPENDENT */
    t2 = plg[2] * .0385528 + plg[4] * .00303445;
/*        SYMMETRICAL ANNUAL AND SEMIANNUAL */
    cd14 = cos(const1_1.dr * (*iday + 8.45398));
    cd18 = cos(dr2 * (*iday - 125.818));
    cd32 = cos(const1_1.dr * (*iday - 30.015));
    cd39 = cos(dr2 * (*iday - 2.75905));
    t3 = cd32 * .00805486 + cd18 * .014237;
/*        ASYMMETRICAL ANNUAL AND SEMIANNUAL */
    t5 = f1 * (plg[1] * -.127371 - plg[3] * .0302449) * cd14 - plg[1] * 
	    .0192645 * cd39;
/*        DIURNAL */
    t71 = plg[11] * .0123512 * cd14;
    t72 = plg[11] * -.00526277 * cd14;
    t7 = (plg[10] * -.105531 - plg[12] * .00607134 + t71) * ctloc + (plg[10] *
	     -.115622 + plg[12] * .0020224 + t72) * stloc;
/*        SEMIDIURNAL */
    t81 = plg[21] * .00386578 * cd14;
    t82 = plg[21] * .00389146 * cd14;
    t8 = (plg[20] * -5.16278e-4 - plg[22] * .00117388 + t81) * c2tloc + (plg[
	    20] * .00990156 - plg[22] * 3.54589e-4 + t82) * s2tloc;
/*        TERDIURNAL */
    z1 = plg[31] * cd14;
    z2 = plg[33] * cd14;
    t14 = (plg[30] * .00147284 - z1 * 1.73933e-4 + z2 * 3.65016e-5) * s3tloc 
	    + (plg[30] * 3.41345e-4 - z1 * 1.53218e-4 + z2 * 1.15102e-4) * 
	    c3tloc;
    t7814 = f2 * (t7 + t8 + t14);
/*        LONGITUDINAL */
    t11 = f3 * ((plg[11] * .00562606 + plg[13] * .00594053 + plg[15] * 
	    .00109358 - plg[10] * .00301801 - plg[12] * .00423564 - plg[14] * 
	    .00248289 + (plg[10] * .00189689 + plg[12] * .00415654) * cd14) * 
	    cos(const_1.umr * *glong) + (plg[11] * -.011654 - plg[13] * 
	    .00449173 - plg[15] * 3.53189e-4 + plg[10] * 9.19286e-4 + plg[12] 
	    * .00216372 + plg[14] * 8.63968e-4 + (plg[10] * .0118068 + plg[12]
	     * .0033119) * cd14) * sin(const_1.umr * *glong));
/*        UT AND MIXED UT,LONGITUDE */
    t12 = (1. - plg[1] * .565411) * cos(sr * (*sec - 31137.)) * (plg[1] * 
	    -.013341 - plg[3] * .0243409 - plg[5] * .0135688) + (plg[21] * 
	    8.45583e-4 + plg[23] * 5.38706e-4) * cos(sr * (*sec - 247.956) + 
	    const_1.umr * 2. * *glong);
/*  Exospheric temperature TINF/K  [Eq. A7] */
    *tinf = (t1 + 1. + t2 + t3 + t5 + t7814 + t11 + t12) * 1041.3 * .99604;

/* TEMPERATURE DERIVATIVE AT LOWER BOUNDARY */

/*         F10.7 EFFECT */
    t1 = dfa * .00252317;
/*        TIME INDEPENDENT */
    t2 = plg[2] * -.0467542 + plg[4] * .12026;
/*        ASYMMETRICAL ANNUAL */
    cd14 = cos(const1_1.dr * (*iday + 8.45398));
    t5 = plg[1] * -.13324 * cd14;
/*        SEMIDIURNAL */
    zz = plg[21] * cd14;
    t81 = zz * -.00973404;
    t82 = zz * -7.18482e-4;
    t8 = (plg[20] * .0191357 + plg[22] * .00787683 + t81) * c2tloc + (plg[20] 
	    * .00125429 - plg[22] * .00233698 + t82) * s2tloc;
/*  dTn/dh at lower boundary  [Eq. A6] */
    g0 = (t1 + 1. + t2 + t5 + t8) * 16.6728 * .951363;

/* NEUTRAL TEMPERATURE AT LOWER BOUNDARY 120KM */

    cd9 = cos(dr2 * (*iday - 89.382));
    cd11 = cos(const1_1.dr * (*iday + 8.45398));
    t1 = dfa * 5.68478e-4;
    t4 = cd9 * .0107674;
    t5 = plg[1] * -.0192414 * cd11;
    t7 = plg[10] * -.02002 * ctloc - plg[10] * .00195833 * stloc;
    t8 = (plg[20] * -.00938391 - plg[22] * .00260147 + plg[23] * 5.11651e-5 * 
	    cd11) * c2tloc + (plg[20] * .013148 - plg[22] * 8.08556e-4 + plg[
	    23] * .00255717 * cd11) * s2tloc;
/*  Tn at lower boundary 120km   [Eq. A8] */
    *tlb = (t1 + 1. + t4 + t5 + t7 + t8) * 386. * .976619;
/*  Sigma      [Eq. A5] */
    *sigma = g0 / (*tinf - *tlb);
    return 0;
} /* cira86_ */

