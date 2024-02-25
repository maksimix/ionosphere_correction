/* igrf.f -- translated by f2c (version 20000121).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

union {
    struct {
	real umr, era, aquad, bquad;
    } _1;
    struct {
	real umr, erad, aquad, bquad;
    } _2;
} igrf1_;

#define igrf1_1 (igrf1_._1)
#define igrf1_2 (igrf1_._2)

union {
    struct {
	real x[3], h__[196];
    } _1;
    struct {
	real xi[3], h__[196];
    } _2;
} igrf2_;

#define igrf2_1 (igrf2_._1)
#define igrf2_2 (igrf2_._2)

struct {
    real sp[3];
} fidb0_;

#define fidb0_1 fidb0_

union {
    struct {
	integer nmax;
	real time, g[196];
	char name__[13];
    } _1;
    struct {
	integer nmax;
	real time, gh1[196];
	char fil1[13];
    } _2;
} model_;

#define model_1 (model_._1)
#define model_2 (model_._2)

struct {
    real ghi1, ghi2, ghi3;
} dipol_;

#define dipol_1 dipol_

struct {
    integer konsol;
} iounit_;

#define iounit_1 iounit_

struct {
    real umr;
} const_;

#define const_1 const_

struct {
    real xlong, year;
} findrlat_;

#define findrlat_1 findrlat_

struct {
    integer iyr;
} iyr_;

#define iyr_1 iyr_

struct {
    integer nm;
} nm_;

#define nm_1 nm_

union {
    struct {
	real clat;
	logical cr360, cr0;
	real rh;
    } _1;
    struct {
	real cclat;
	logical cr360, cr0;
	real rh;
    } _2;
} cgmgeo_;

#define cgmgeo_1 (cgmgeo_._1)
#define cgmgeo_2 (cgmgeo_._2)

struct {
    real ds3;
} a5_;

#define a5_1 a5_

union {
    struct {
	real st0, ct0, sl0, cl0, ctcl, stcl, ctsl, stsl, sfi, cfi, sps, cps, 
		shi, chi, hi, psi, xmut, a11, a21, a31, a12, a22, a32, a13, 
		a23, a33, ds3;
	integer k, iy;
	real ba[8];
    } _1;
    struct {
	real st0, ct0, sl0, cl0, ctcl, stcl, ctsl, stsl, ab[19];
	integer k, iy;
	real bb[8];
    } _2;
    struct {
	real a[8], sfi, cfi, b[7], ab[10];
	integer k, iy;
	real ba[8];
    } _3;
    struct {
	real a[10], sps, cps, b[15];
	integer k, iy;
	real ab[8];
    } _4;
} c1_;

#define c1_1 (c1_._1)
#define c1_2 (c1_._2)
#define c1_3 (c1_._3)
#define c1_4 (c1_._4)

/* Table of constant values */

static real c_b3 = (float)1.;
static integer c__1 = 1;
static integer c__3 = 3;
static integer c__4 = 4;
static integer c_n1 = -1;
static real c_b81 = (float)300.;
static real c_b91 = (float)90.;
static real c_b92 = (float)360.;
static real c_b93 = (float)-90.;
static integer c__0 = 0;
static integer c__25 = 25;

/* igrf.for, version number can be found at the end of this comment. */
/* ----------------------------------------------------------------------- */

/* Subroutines to compute IGRF parameters for IRI and all functions and */
/* subroutines required for this computation, including: */
/* 	IGRF_SUB, IGRF_DIP, FINDB0, SHELLG, STOER, FELDG, FELDCOF, GETSHC, */
/* 	INTERSHC, EXTRASHC, INITIZE, GEODIP, fmodip */

/* CGM coordinates : GEOCGM01, OVL_ANG, CGMGLA, CGMGLO, DFR1DR, */
/*   AZM_ANG, MLTUT, MFC, FTPRNT, GEOLOW, CORGEO, GEOCOR, SHAG, RIGHT, */
/*   IGRF, RECALC, SPHCAR, BSPCAR, GEOMAG, MAGSM, SMGSM */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Required i/o units: */
/*  KONSOL= 6 Program messages (used when jf(12)=.true. -> konsol) */
/*  KONSOL=11 Program messages (used when jf(12)=.false. -> MESSAGES.TXT) */

/*     COMMON/iounit/konsol is used to pass the value of KONSOL from */
/*     IRISUB to IRIFUN and IGRF. If KONSOL=1 than messages are turned off. */

/*  UNIT=14 IGRF/GETSHC: IGRF coeff. (DGRF%%%%.DAT or IGRF%%%%.DAT, %%%%=year) */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Corrections: */
/* 11/01/91 SHELLG: lowest starting point for B0 search is 2 */
/*  1/27/92 Adopted to IGRF-91 coeffcients model */
/*  2/05/92 Reduce variable names: INTER(P)SHC,EXTRA(P)SHC,INITI(ALI)ZE */
/*  8/08/95 Updated to IGRF-45-95; new coeff. DGRF90, IGRF95, IGRF95S */
/*  5/31/00 Updated to IGRF-45-00; new coeff.: IGRF00, IGRF00s */
/* -Version-mm/dd/yy-Description (Person reporting the correction) */
/* 2000.01 05/07/01 initial version */
/* 2000.02 07/11/01 replace feldi(xi,h) by feldi (P. Wilkinson) */
/* 2000.02 07/11/01 variables EGNR, AGNR,OGNR not used (P. Wilkinson) */
/* 2000.01 10/28/02 replace TAB/6 blanks, enforce 72/line (D. Simpson) */
/* 2000.02 11/08/02 change unit for coefficients to 14 */
/* 2000.03 06/05/03 correct DIPL computation (V. Truhlik) */
/* 2005.00 04/25/05 CALL FELDI and DO 1111 I=1,7 (Alexey Petrov) */
/* 2005.01 11/10/05 added igrf_dip and geodip (MLAT) */
/* 2005.02 11/10/05 FELDCOF: updated to IGRF-10 version */
/* 2005.03 12/21/06 GH2(120) -> GH2(144) */
/* 2007.00 05/18/07 Release of IRI-2007 */
/* 2007.08 07/30/09 SHELLG,STOER,FELDG,FELDCOF: NMAX=13; H/G-arrays(195) */
/* 2007.10 02/26/10 FELDCOF: updated to IGRF-11; DGRF05, IGRF10, IGRF10S */
/* 2007.11 04/27/10 RECALC: updated to IGRF-11 */
/* 2007.11 04/27/10 Make all arrays(195) to arrays(196) */
/* 2007.11 04/27/10 FELDCOF: corrected Filmod and also IGRF10.DAT */
/* 2007.11 04/29/10 New files dgrf%%%%.asc; new GETSHC; char*12 to 13 */

/* 2012.00 10/05/11 IRI-2012: bottomside B0 B1 model (SHAMDB0D, SHAB1D), */
/* 2012.00 10/05/11    bottomside Ni model (iriflip.for), auroral foE */
/* 2012.00 10/05/11    storm model (storme_ap), Te with PF10.7 (elteik), */
/* 2012.00 10/05/11    oval kp model (auroral_boundary), IGRF-11(igrf.for), */
/* 2012.00 10/05/11    NRLMSIS00 (cira.for), CGM coordinates, F10.7 daily */
/* 2012.00 10/05/11    81-day 365-day indices (apf107.dat), ap->kp (ckp), */
/* 2012.00 10/05/11    array size change jf(50) outf(20,1000), oarr(100). */
/* 2012.02 12/17/12 igrf_dip: Add magnetic declination as output parameter */
/* ----------------------------------------------------------------------- */

/* Subroutine */ int igrf_sub__(xlat, xlong, year, height, xl, icode, dipl, 
	babs)
real *xlat, *xlong, *year, *height, *xl;
integer *icode;
real *dipl, *babs;
{
    /* Builtin functions */
    double sqrt(), atan();

    /* Local variables */
    static real lati, dimo;
    extern /* Subroutine */ int feldg_();
    static real beast, longi, bdown;
    extern /* Subroutine */ int shellg_();
    static real bnorth;
    extern /* Subroutine */ int feldcof_();
    static real bab1;
    extern /* Subroutine */ int initize_();

/* ----------------------------------------------------------------------- */
/* INPUT: */
/*    xlat      geodatic latitude in degrees */
/*    xlong     geodatic longitude in degrees */
/*    year      decimal year (year+month/12.0-0.5 or */
/*                  year+day-of-year/365 or ../366 if leap year) */
/*    height    height in km */
/* OUTPUT: */
/*    xl        L value */
/*    icode      =1  L is correct; =2  L is not correct; */
/*               =3  an approximation is used */
/*    dipl      dip latitude in degrees */
/*    babs      magnetic field strength in Gauss */
/* ----------------------------------------------------------------------- */

    initize_();
    lati = *xlat;
    longi = *xlong;

/* ----------------CALCULATE PROFILES----------------------------------- */

    feldcof_(year, &dimo);
    feldg_(&lati, &longi, height, &bnorth, &beast, &bdown, babs);
    shellg_(&lati, &longi, height, &dimo, xl, icode, &bab1);
/*        DIP=ASIN(BDOWN/BABS)/UMR */
/*       DEC=ASIN(BEAST/SQRT(BEAST*BEAST+BNORTH*BNORTH))/UMR */
/*        DIPL=ATAN(0.5*TAN(DIP*UMR))/UMR */
    *dipl = atan(bdown / (float)2. / sqrt(bnorth * bnorth + beast * beast)) / 
	    igrf1_1.umr;
    return 0;
} /* igrf_sub__ */



/* Subroutine */ int igrf_dip__(xlat, xlong, year, height, dec, dip, dipl, 
	ymodip)
real *xlat, *xlong, *year, *height, *dec, *dip, *dipl, *ymodip;
{
    /* Builtin functions */
    double sqrt(), asin(), cos(), r_sign(), atan();

    /* Local variables */
    static real babs, dimo, h__;
    extern /* Subroutine */ int feldg_();
    static real beast, bdown, xlati, dipdiv, smodip, bnorth, xlongi;
    extern /* Subroutine */ int feldcof_(), initize_();

/* ----------------------------------------------------------------------- */
/* INPUT: */
/*    xlat      geodatic latitude in degrees */
/*    xlong     geodatic longitude in degrees */
/*    year      decimal year (year+month/12.0-0.5 or */
/*                  year+day-of-year/365 or ../366 if leap year) */
/*    height    height in km */
/* OUTPUT: */
/*    dec       magnetic declination in degrees */
/*    dip       magnetic inclination (dip) in degrees */
/*    dipl      dip latitude in degrees */
/*    ymodip    modified dip latitude = asin{dip/sqrt[dip^2+cos(LATI)]} */
/* ----------------------------------------------------------------------- */

    initize_();

/* ----------------CALCULATE PROFILES----------------------------------- */

    xlati = *xlat;
    xlongi = *xlong;
    h__ = *height;
    feldcof_(year, &dimo);
    feldg_(&xlati, &xlongi, &h__, &bnorth, &beast, &bdown, &babs);
    *dec = asin(beast / sqrt(beast * beast + bnorth * bnorth));
    *dip = asin(bdown / babs);
    dipdiv = *dip / sqrt(*dip * *dip + cos(xlati * igrf1_1.umr));
    if (dabs(dipdiv) > (float)1.) {
	dipdiv = r_sign(&c_b3, &dipdiv);
    }
    smodip = asin(dipdiv);
/*       DIPL1=ATAN(0.5*TAN(DIP))/UMR */
    *dipl = atan(bdown / (float)2. / sqrt(bnorth * bnorth + beast * beast)) / 
	    igrf1_1.umr;
    *ymodip = smodip / igrf1_1.umr;
    *dec /= igrf1_1.umr;
    *dip /= igrf1_1.umr;
    return 0;
} /* igrf_dip__ */



/* SHELLIG.FOR */

/* 11/01/91 SHELLG: lowest starting point for B0 search is 2 */
/*  1/27/92 Adopted to IGRF-91 coeffcients model */
/*  2/05/92 Reduce variable-names: INTER(P)SHC,EXTRA(P)SHC,INITI(ALI)ZE */
/*  8/08/95 Updated to IGRF-45-95; new coeff. DGRF90, IGRF95, IGRF95S */
/*  5/31/00 Updated to IGRF-45-00; new coeff.: IGRF00, IGRF00s */
/*  3/24/05 Updated to IGRF-45-10; new coeff.: IGRF05, IGRF05s */
/*  4/25/05 ENTRY FELDI(XI,H) and  DO 1111 I=1,7 [Alexey Petrov] */
/*  7/22/09 SHELLG: NMAX=13 for DGRF00 and IGRF05; H/G-arrays(195) */
/*  2/26/10 FELDCOF: Updated IGRF45-15; new coeff: DGRF05, IGRF10, IGRF10S */
/*  4/29/10 H/H-arrays(196); FELDCOF: corrected IGRF00 and ..00S */
/*  4/29/10 Change to new files dgrf%%%%.asc; new GETSHC; char*12 to 13 */

/* ********************************************************************* */
/*  SUBROUTINES SHELLG, STOER, FELDG, FELDCOF, GETSHC,        * */
/*       INTERSHC, EXTRASHC, INITIZE                                  * */
/* ********************************************************************* */
/* ********************************************************************* */



/* Subroutine */ int shellg_0_(n__, glat, glon, alt, dimo, fl, icode, b0, v)
int n__;
real *glat, *glon, *alt, *dimo, *fl;
integer *icode;
real *b0, *v;
{
    /* Initialized data */

    static real rmin = (float).05;
    static real rmax = (float)1.01;
    static real step = (float).2;
    static real steq = (float).03;
    static real u[9]	/* was [3][3] */ = { (float).3511737,(float)-.9148385,
	    (float)-.1993679,(float).9335804,(float).358368,(float)0.,(float)
	    .0714471,(float)-.186126,(float).9799247 };

    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double sin(), cos(), sqrt(), r_sign(), log(), exp();

    /* Local variables */
    static real bequ, rlat;
    static integer iequ;
    static real term, rlon, step2, d__;
    static integer i__, n;
    static real p[800]	/* was [8][100] */, r__, t, z__, radik, step12, c0, 
	    c1, c2, oterm, c3, d0, d1, d2, e0;
    extern /* Subroutine */ int stoer_();
    static real e1, e2, r1, r2, r3, dimob0, ff, gg, fi, ct, rq, st, oradik, 
	    zq, xx, zz, bq1, bq2, bq3, r3h, hli, stp, arg1, arg2;

/* ----------------------------------------------------------------------- */
/* CALCULATES L-VALUE FOR SPECIFIED GEODAETIC COORDINATES, ALTITUDE */
/* AND GEMAGNETIC FIELD MODEL. */
/* REF: G. KLUGE, EUROPEAN SPACE OPERATIONS CENTER, INTERNAL NOTE */
/*      NO. 67, 1970. */
/*      G. KLUGE, COMPUTER PHYSICS COMMUNICATIONS 3, 31-35, 1972 */
/* ----------------------------------------------------------------------- */
/* CHANGES (D. BILITZA, NOV 87): */
/*   - USING CORRECT DIPOL MOMENT I.E.,DIFFERENT COMMON/MODEL/ */
/*   - USING IGRF EARTH MAGNETIC FIELD MODELS FROM 1945 TO 1990 */
/* 09/07/22 NMAX=13 for DGRF00 and IGRF05; H/G-arrays(195) */
/* ----------------------------------------------------------------------- */
/*  INPUT:  ENTRY POINT SHELLG */
/*             GLAT  GEODETIC LATITUDE IN DEGREES (NORTH) */
/*             GLON  GEODETIC LONGITUDE IN DEGREES (EAST) */
/*             ALT   ALTITUDE IN KM ABOVE SEA LEVEL */

/*          ENTRY POINT SHELLC */
/*             V(3)  CARTESIAN COORDINATES IN EARTH RADII (6371.2 KM) */
/*                     X-AXIS POINTING TO EQUATOR AT 0 LONGITUDE */
/*                     Y-AXIS POINTING TO EQUATOR AT 90 LONG. */
/*                     Z-AXIS POINTING TO NORTH POLE */

/*          DIMO     DIPOL MOMENT IN GAUSS (NORMALIZED TO EARTH RADIUS) */

/*          COMMON */
/*             X(3)    NOT USED */
/*             H(144)  FIELD MODEL COEFFICIENTS ADJUSTED FOR SHELLG */
/* ----------------------------------------------------------------------- */
/*  OUTPUT: FL           L-VALUE */
/*          ICODE        =1 NORMAL COMPLETION */
/*                       =2 UNPHYSICAL CONJUGATE POINT (FL MEANINGLESS) */
/*                       =3 SHELL PARAMETER GREATER THAN LIMIT UP TO */
/*                          WHICH ACCURATE CALCULATION IS REQUIRED; */
/*                          APPROXIMATION IS USED. */
/*          B0           MAGNETIC FIELD STRENGTH IN GAUSS */
/* ----------------------------------------------------------------------- */

/* -- RMIN, RMAX ARE BOUNDARIES FOR IDENTIFICATION OF ICODE=2 AND 3 */
/* -- STEP IS STEP SIZE FOR FIELD LINE TRACING */
/* -- STEQ IS STEP SIZE FOR INTEGRATION */

    /* Parameter adjustments */
    if (v) {
	--v;
	}

    /* Function Body */
    switch(n__) {
	case 1: goto L_shellc;
	}

    bequ = (float)1e10;
/* *****ENTRY POINT  SHELLG  TO BE USED WITH GEODETIC CO-ORDINATES */
    rlat = *glat * igrf1_1.umr;
    ct = sin(rlat);
    st = cos(rlat);
    d__ = sqrt(igrf1_1.aquad - (igrf1_1.aquad - igrf1_1.bquad) * ct * ct);
    igrf2_1.x[0] = (*alt + igrf1_1.aquad / d__) * st / igrf1_1.era;
    igrf2_1.x[2] = (*alt + igrf1_1.bquad / d__) * ct / igrf1_1.era;
    rlon = *glon * igrf1_1.umr;
    igrf2_1.x[1] = igrf2_1.x[0] * sin(rlon);
    igrf2_1.x[0] *= cos(rlon);
    goto L9;

L_shellc:
/* *****ENTRY POINT  SHELLC  TO BE USED WITH CARTESIAN CO-ORDINATES */
    igrf2_1.x[0] = v[1];
    igrf2_1.x[1] = v[2];
    igrf2_1.x[2] = v[3];
/* *****CONVERT TO DIPOL-ORIENTED CO-ORDINATES */
L9:
    rq = (float)1. / (igrf2_1.x[0] * igrf2_1.x[0] + igrf2_1.x[1] * igrf2_1.x[
	    1] + igrf2_1.x[2] * igrf2_1.x[2]);
    r3h = sqrt(rq * sqrt(rq));
    p[8] = (igrf2_1.x[0] * u[0] + igrf2_1.x[1] * u[1] + igrf2_1.x[2] * u[2]) *
	     r3h;
    p[9] = (igrf2_1.x[0] * u[3] + igrf2_1.x[1] * u[4]) * r3h;
    p[10] = (igrf2_1.x[0] * u[6] + igrf2_1.x[1] * u[7] + igrf2_1.x[2] * u[8]) 
	    * rq;
/* *****FIRST THREE POINTS OF FIELD LINE */
    step = -r_sign(&step, &p[10]);
    stoer_(&p[8], &bq2, &r2);
    *b0 = sqrt(bq2);
    p[16] = p[8] + step * (float).5 * p[11];
    p[17] = p[9] + step * (float).5 * p[12];
    p[18] = p[10] + step * (float).5;
    stoer_(&p[16], &bq3, &r3);
    p[0] = p[8] - step * (p[11] * (float)2. - p[19]);
    p[1] = p[9] - step * (p[12] * (float)2. - p[20]);
    p[2] = p[10] - step;
    stoer_(p, &bq1, &r1);
    p[16] = p[8] + step * (p[19] * (float)20. - p[11] * (float)3. + p[3]) / (
	    float)18.;
    p[17] = p[9] + step * (p[20] * (float)20. - p[12] * (float)3. + p[4]) / (
	    float)18.;
    p[18] = p[10] + step;
    stoer_(&p[16], &bq3, &r3);
/* *****INVERT SENSE IF REQUIRED */
    if (bq3 <= bq1) {
	goto L2;
    }
    step = -step;
    r3 = r1;
    bq3 = bq1;
    for (i__ = 1; i__ <= 7; ++i__) {
	zz = p[i__ - 1];
	p[i__ - 1] = p[i__ + 15];
/* L1: */
	p[i__ + 15] = zz;
    }
/* *****SEARCH FOR LOWEST MAGNETIC FIELD STRENGTH */
L2:
    if (bq1 < bequ) {
	bequ = bq1;
	iequ = 1;
    }
    if (bq2 < bequ) {
	bequ = bq2;
	iequ = 2;
    }
    if (bq3 < bequ) {
	bequ = bq3;
	iequ = 3;
    }
/* *****INITIALIZATION OF INTEGRATION LOOPS */
    step12 = step / (float)12.;
    step2 = step + step;
    steq = r_sign(&steq, &step);
    fi = (float)0.;
    *icode = 1;
    oradik = (float)0.;
    oterm = (float)0.;
    stp = r2 * steq;
    z__ = p[10] + stp;
    stp /= (float).75;
    p[7] = step2 * (p[0] * p[3] + p[1] * p[4]);
    p[15] = step2 * (p[8] * p[11] + p[9] * p[12]);
/* *****MAIN LOOP (FIELD LINE TRACING) */
    for (n = 3; n <= 3333; ++n) {
/* *****CORRECTOR (FIELD LINE TRACING) */
	p[(n << 3) - 8] = p[(n - 1 << 3) - 8] + step12 * (p[(n << 3) - 5] * (
		float)5. + p[(n - 1 << 3) - 5] * (float)8. - p[(n - 2 << 3) - 
		5]);
	p[(n << 3) - 7] = p[(n - 1 << 3) - 7] + step12 * (p[(n << 3) - 4] * (
		float)5. + p[(n - 1 << 3) - 4] * (float)8. - p[(n - 2 << 3) - 
		4]);
/* *****PREPARE EXPANSION COEFFICIENTS FOR INTERPOLATION */
/* *****OF SLOWLY VARYING QUANTITIES */
	p[(n << 3) - 1] = step2 * (p[(n << 3) - 8] * p[(n << 3) - 5] + p[(n <<
		 3) - 7] * p[(n << 3) - 4]);
/* Computing 2nd power */
	r__1 = p[(n - 1 << 3) - 8];
/* Computing 2nd power */
	r__2 = p[(n - 1 << 3) - 7];
	c0 = r__1 * r__1 + r__2 * r__2;
	c1 = p[(n - 1 << 3) - 1];
	c2 = (p[(n << 3) - 1] - p[(n - 2 << 3) - 1]) * (float).25;
	c3 = (p[(n << 3) - 1] + p[(n - 2 << 3) - 1] - c1 - c1) / (float)6.;
	d0 = p[(n - 1 << 3) - 3];
	d1 = (p[(n << 3) - 3] - p[(n - 2 << 3) - 3]) * (float).5;
	d2 = (p[(n << 3) - 3] + p[(n - 2 << 3) - 3] - d0 - d0) * (float).5;
	e0 = p[(n - 1 << 3) - 2];
	e1 = (p[(n << 3) - 2] - p[(n - 2 << 3) - 2]) * (float).5;
	e2 = (p[(n << 3) - 2] + p[(n - 2 << 3) - 2] - e0 - e0) * (float).5;
/* *****INNER LOOP (FOR QUADRATURE) */
L4:
	t = (z__ - p[(n - 1 << 3) - 6]) / step;
	if (t > (float)1.) {
	    goto L5;
	}
	hli = (((c3 * t + c2) * t + c1) * t + c0) * (float).5;
	zq = z__ * z__;
	r__ = hli + sqrt(hli * hli + zq);
	if (r__ <= rmin) {
	    goto L30;
	}
	rq = r__ * r__;
	ff = sqrt(zq * (float)3. / rq + (float)1.);
	radik = *b0 - ((d2 * t + d1) * t + d0) * r__ * rq * ff;
	if (r__ - rmax <= (float)0.) {
	    goto L44;
	} else {
	    goto L45;
	}
L45:
	*icode = 2;
/* Computing 2nd power */
	r__1 = r__ - rmax;
	radik -= r__1 * r__1 * (float)12.;
L44:
	if (radik + radik <= oradik) {
	    goto L10;
	}
	term = sqrt(radik) * ff * ((e2 * t + e1) * t + e0) / (rq + zq);
	fi += stp * (oterm + term);
	oradik = radik;
	oterm = term;
	stp = r__ * steq;
	z__ += stp;
	goto L4;
/* *****PREDICTOR (FIELD LINE TRACING) */
L5:
	p[(n + 1 << 3) - 8] = p[(n << 3) - 8] + step12 * (p[(n << 3) - 5] * (
		float)23. - p[(n - 1 << 3) - 5] * (float)16. + p[(n - 2 << 3) 
		- 5] * (float)5.);
	p[(n + 1 << 3) - 7] = p[(n << 3) - 7] + step12 * (p[(n << 3) - 4] * (
		float)23. - p[(n - 1 << 3) - 4] * (float)16. + p[(n - 2 << 3) 
		- 4] * (float)5.);
	p[(n + 1 << 3) - 6] = p[(n << 3) - 6] + step;
	stoer_(&p[(n + 1 << 3) - 8], &bq3, &r3);
/* *****SEARCH FOR LOWEST MAGNETIC FIELD STRENGTH */
	if (bq3 < bequ) {
	    iequ = n + 1;
	    bequ = bq3;
	}
/* L3: */
    }
L10:
    if (iequ < 2) {
	iequ = 2;
    }
    fidb0_1.sp[0] = p[(iequ - 1 << 3) - 8];
    fidb0_1.sp[1] = p[(iequ - 1 << 3) - 7];
    fidb0_1.sp[2] = p[(iequ - 1 << 3) - 6];
    if (oradik < (float)1e-15) {
	goto L11;
    }
    fi += stp / (float).75 * oterm * oradik / (oradik - radik);

/* -- The minimal allowable value of FI was changed from 1E-15 to 1E-12, */
/* -- because 1E-38 is the minimal allowable arg. for ALOG in our envir. */
/* -- D. Bilitza, Nov 87. */

L11:
    fi = dabs(fi) * (float).5 / sqrt(*b0) + (float)1e-12;

/* *****COMPUTE L FROM B AND I.  SAME AS CARMEL IN INVAR. */

/* -- Correct dipole moment is used here. D. Bilitza, Nov 87. */

    dimob0 = *dimo / *b0;
    arg1 = log(fi);
    arg2 = log(dimob0);
/*      arg = FI*FI*FI/DIMOB0 */
/*      if(abs(arg).gt.88.0) arg=88.0 */
    xx = arg1 * 3 - arg2;
    if (xx > (float)23.) {
	goto L776;
    }
    if (xx > (float)11.7) {
	goto L775;
    }
    if (xx > (float)3.) {
	goto L774;
    }
    if (xx > (float)-3.) {
	goto L773;
    }
    if (xx > (float)-22.) {
	goto L772;
    }
/* L771: */
    gg = xx * (float).333338 + (float).30062102;
    goto L777;
L772:
    gg = ((((((((xx * (float)-8.1537735e-14 + (float)8.3232531e-13) * xx + (
	    float)1.0066362e-9) * xx + (float)8.1048663e-8) * xx + (float)
	    3.2916354e-6) * xx + (float)8.2711096e-5) * xx + (float)
	    .0013714667) * xx + (float).015017245) * xx + (float).43432642) * 
	    xx + (float).62337691;
    goto L777;
L773:
    gg = ((((((((xx * (float)2.6047023e-10 + (float)2.3028767e-9) * xx - (
	    float)2.1997983e-8) * xx - (float)5.3977642e-7) * xx - (float)
	    3.3408822e-6) * xx + (float)3.8379917e-5) * xx + (float)
	    .0011784234) * xx + (float).014492441) * xx + (float).43352788) * 
	    xx + (float).6228644;
    goto L777;
L774:
    gg = ((((((((xx * (float)6.3271665e-10 - (float)3.958306e-8) * xx + (
	    float)9.9766148e-7) * xx - (float)1.2531932e-5) * xx + (float)
	    7.9451313e-5) * xx - (float)3.2077032e-4) * xx + (float)
	    .0021680398) * xx + (float).012817956) * xx + (float).43510529) * 
	    xx + (float).6222355;
    goto L777;
L775:
    gg = (((((xx * (float)2.8212095e-8 - (float)3.8049276e-6) * xx + (float)
	    2.170224e-4) * xx - (float).0067310339) * xx + (float).12038224) *
	     xx - (float).18461796) * xx + (float)2.0007187;
    goto L777;
L776:
    gg = xx - (float)3.0460681;
L777:
    *fl = exp(log((exp(gg) + (float)1.) * dimob0) / (float)3.);
    return 0;
/* *****APPROXIMATION FOR HIGH VALUES OF L. */
L30:
    *icode = 3;
    t = -p[(n - 1 << 3) - 6] / step;
    *fl = (float)1. / ((r__1 = ((c3 * t + c2) * t + c1) * t + c0, dabs(r__1)) 
	    + (float)1e-15);
    return 0;
} /* shellg_ */

/* Subroutine */ int shellg_(glat, glon, alt, dimo, fl, icode, b0)
real *glat, *glon, *alt, *dimo, *fl;
integer *icode;
real *b0;
{
    return shellg_0_(0, glat, glon, alt, dimo, fl, icode, b0, (real *)0);
    }

/* Subroutine */ int shellc_(v, fl, b0)
real *v, *fl, *b0;
{
    return shellg_0_(1, (real *)0, (real *)0, (real *)0, (real *)0, fl, (
	    integer *)0, b0, v);
    }



/* Subroutine */ int stoer_(p, bq, r__)
real *p, *bq, *r__;
{
    /* Initialized data */

    static real u[9]	/* was [3][3] */ = { (float).3511737,(float)-.9148385,
	    (float)-.1993679,(float).9335804,(float).358368,(float)0.,(float)
	    .0714471,(float)-.186126,(float).9799247 };

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    double sqrt();

    /* Local variables */
    static real q;
    extern /* Subroutine */ int feldi_();
    static real dr, dx, dy, dz, rq, xm, ym, zm, wr, fli, dsq, dxm, dym, dzm;

/* ******************************************************************* */
/* * SUBROUTINE USED FOR FIELD LINE TRACING IN SHELLG                * */
/* * CALLS ENTRY POINT FELDI IN GEOMAGNETIC FIELD SUBROUTINE FELDG   * */

/* 09/07/22 NMAX=13 for DGRF00 and IGRF05; H/G-arrays(195) */
/* ******************************************************************* */
/* *****XM,YM,ZM  ARE GEOMAGNETIC CARTESIAN INVERSE CO-ORDINATES */
    /* Parameter adjustments */
    --p;

    /* Function Body */
    zm = p[3];
    fli = p[1] * p[1] + p[2] * p[2] + (float)1e-15;
/* Computing 2nd power */
    r__1 = zm + zm;
    *r__ = (fli + sqrt(fli * fli + r__1 * r__1)) * (float).5;
    rq = *r__ * *r__;
    wr = sqrt(*r__);
    xm = p[1] * wr;
    ym = p[2] * wr;
/* *****TRANSFORM TO GEOGRAPHIC CO-ORDINATE SYSTEM */
    igrf2_2.xi[0] = xm * u[0] + ym * u[3] + zm * u[6];
    igrf2_2.xi[1] = xm * u[1] + ym * u[4] + zm * u[7];
    igrf2_2.xi[2] = xm * u[2] + zm * u[8];
/* *****COMPUTE DERIVATIVES */
/*      CALL FELDI(XI,H) */
    feldi_();
    q = igrf2_2.h__[0] / rq;
    dx = igrf2_2.h__[2] + igrf2_2.h__[2] + q * igrf2_2.xi[0];
    dy = igrf2_2.h__[3] + igrf2_2.h__[3] + q * igrf2_2.xi[1];
    dz = igrf2_2.h__[1] + igrf2_2.h__[1] + q * igrf2_2.xi[2];
/* *****TRANSFORM BACK TO GEOMAGNETIC CO-ORDINATE SYSTEM */
    dxm = u[0] * dx + u[1] * dy + u[2] * dz;
    dym = u[3] * dx + u[4] * dy;
    dzm = u[6] * dx + u[7] * dy + u[8] * dz;
    dr = (xm * dxm + ym * dym + zm * dzm) / *r__;
/* *****FORM SLOWLY VARYING EXPRESSIONS */
    p[4] = (wr * dxm - p[1] * (float).5 * dr) / (*r__ * dzm);
    p[5] = (wr * dym - p[2] * (float).5 * dr) / (*r__ * dzm);
    dsq = rq * (dxm * dxm + dym * dym + dzm * dzm);
    *bq = dsq * rq * rq;
    p[6] = sqrt(dsq / (rq + zm * (float)3. * zm));
    p[7] = p[6] * (rq + zm * zm) / (rq * dzm);
    return 0;
} /* stoer_ */



/* Subroutine */ int feldg_0_(n__, glat, glon, alt, bnorth, beast, bdown, 
	babs, v, b)
int n__;
real *glat, *glon, *alt, *bnorth, *beast, *bdown, *babs, *v, *b;
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double sin(), cos(), sqrt();

    /* Local variables */
    static real brho;
    static integer imax;
    static real rlat;
    static integer last;
    static real rlon, bxxx, byyy, bzzz, d__, f;
    static integer i__, k, m;
    static real s, t, x, y, z__;
    static integer ihmax, ih;
    static real cp;
    static integer il;
    static real ct;
    static integer is;
    static real sp, rq, st, rho, xxx, yyy, zzz;

/* ----------------------------------------------------------------------- */
/* CALCULATES EARTH MAGNETIC FIELD FROM SPHERICAL HARMONICS MODEL */
/* REF: G. KLUGE, EUROPEAN SPACE OPERATIONS CENTRE, INTERNAL NOTE 61, */
/*      1970. */
/* ----------------------------------------------------------------------- */
/* CHANGES (D. BILITZA, NOV 87): */
/*   - FIELD COEFFICIENTS IN BINARY DATA FILES INSTEAD OF BLOCK DATA */
/*   - CALCULATES DIPOL MOMENT */
/* 09/07/22 NMAX=13 for DGRF00 and IGRF05; H/G-arrays(195) */
/* ----------------------------------------------------------------------- */
/*  INPUT:  ENTRY POINT FELDG */
/*               GLAT  GEODETIC LATITUDE IN DEGREES (NORTH) */
/*               GLON  GEODETIC LONGITUDE IN DEGREES (EAST) */
/*               ALT   ALTITUDE IN KM ABOVE SEA LEVEL */

/*          ENTRY POINT FELDC */
/*               V(3)  CARTESIAN COORDINATES IN EARTH RADII (6371.2 KM) */
/*                       X-AXIS POINTING TO EQUATOR AT 0 LONGITUDE */
/*                       Y-AXIS POINTING TO EQUATOR AT 90 LONG. */
/*                       Z-AXIS POINTING TO NORTH POLE */

/*          COMMON BLANK AND ENTRY POINT FELDI ARE NEEDED WHEN USED */
/*            IN CONNECTION WITH L-CALCULATION PROGRAM SHELLG. */

/*          COMMON /MODEL/ AND /IGRF1/ */
/*               UMR     = ATAN(1.0)*4./180.   <DEGREE>*UMR=<RADIANT> */
/*               ERA     EARTH RADIUS FOR NORMALIZATION OF CARTESIAN */
/*                       COORDINATES (6371.2 KM) */
/*               AQUAD, BQUAD   SQUARE OF MAJOR AND MINOR HALF AXIS OF */
/*                       EARTH ELLIPSOID AS RECOMMENDED BY INTERNAT. */
/*                       ASTRONOMICAL UNION (6378.160, 6356.775 KM). */
/*               NMAX    MAXIMUM ORDER OF SPHERICAL HARMONICS */
/*               TIME    YEAR (DECIMAL: 1973.5) FOR WHICH MAGNETIC */
/*                       FIELD IS TO BE CALCULATED */
/*               G(M)    NORMALIZED FIELD COEFFICIENTS (SEE FELDCOF) */
/*                       M=NMAX*(NMAX+2) */
/* ----------------------------------------------------------------------- */
/*  OUTPUT: BABS   MAGNETIC FIELD STRENGTH IN GAUSS */
/*          BNORTH, BEAST, BDOWN   COMPONENTS OF THE FIELD WITH RESPECT */
/*                 TO THE LOCAL GEODETIC COORDINATE SYSTEM, WITH AXIS */
/*                 POINTING IN THE TANGENTIAL PLANE TO THE NORTH, EAST */
/*                 AND DOWNWARD. */
/* ----------------------------------------------------------------------- */

/* -- IS RECORDS ENTRY POINT */

/* *****ENTRY POINT  FELDG  TO BE USED WITH GEODETIC CO-ORDINATES */
    /* Parameter adjustments */
    if (v) {
	--v;
	}
    if (b) {
	--b;
	}

    /* Function Body */
    switch(n__) {
	case 1: goto L_feldc;
	case 2: goto L_feldi;
	}

    is = 1;
    rlat = *glat * igrf1_1.umr;
    ct = sin(rlat);
    st = cos(rlat);
    d__ = sqrt(igrf1_1.aquad - (igrf1_1.aquad - igrf1_1.bquad) * ct * ct);
    rlon = *glon * igrf1_1.umr;
    cp = cos(rlon);
    sp = sin(rlon);
    zzz = (*alt + igrf1_1.bquad / d__) * ct / igrf1_1.era;
    rho = (*alt + igrf1_1.aquad / d__) * st / igrf1_1.era;
    xxx = rho * cp;
    yyy = rho * sp;
    goto L10;
/* *****ENTRY POINT  FELDC  TO BE USED WITH CARTESIAN CO-ORDINATES */

L_feldc:
    is = 2;
    xxx = v[1];
    yyy = v[2];
    zzz = v[3];
L10:
    rq = (float)1. / (xxx * xxx + yyy * yyy + zzz * zzz);
    igrf2_2.xi[0] = xxx * rq;
    igrf2_2.xi[1] = yyy * rq;
    igrf2_2.xi[2] = zzz * rq;
    goto L20;
/* *****ENTRY POINT  FELDI  USED FOR L COMPUTATION */

L_feldi:
    is = 3;
L20:
    ihmax = model_1.nmax * model_1.nmax + 1;
    last = ihmax + model_1.nmax + model_1.nmax;
    imax = model_1.nmax + model_1.nmax - 1;
    i__1 = last;
    for (i__ = ihmax; i__ <= i__1; ++i__) {
/* L8: */
	igrf2_2.h__[i__ - 1] = model_1.g[i__ - 1];
    }
    for (k = 1; k <= 3; k += 2) {
	i__ = imax;
	ih = ihmax;
L1:
	il = ih - i__;
	f = (float)2. / (real) (i__ - k + 2);
	x = igrf2_2.xi[0] * f;
	y = igrf2_2.xi[1] * f;
	z__ = igrf2_2.xi[2] * (f + f);
	i__ += -2;
	if ((i__1 = i__ - 1) < 0) {
	    goto L5;
	} else if (i__1 == 0) {
	    goto L4;
	} else {
	    goto L2;
	}
L2:
	i__1 = i__;
	for (m = 3; m <= i__1; m += 2) {
	    igrf2_2.h__[il + m] = model_1.g[il + m] + z__ * igrf2_2.h__[ih + 
		    m] + x * (igrf2_2.h__[ih + m + 2] - igrf2_2.h__[ih + m - 
		    2]) - y * (igrf2_2.h__[ih + m + 1] + igrf2_2.h__[ih + m - 
		    3]);
/* L3: */
	    igrf2_2.h__[il + m - 1] = model_1.g[il + m - 1] + z__ * 
		    igrf2_2.h__[ih + m - 1] + x * (igrf2_2.h__[ih + m + 1] - 
		    igrf2_2.h__[ih + m - 3]) + y * (igrf2_2.h__[ih + m + 2] + 
		    igrf2_2.h__[ih + m - 2]);
	}
L4:
	igrf2_2.h__[il + 1] = model_1.g[il + 1] + z__ * igrf2_2.h__[ih + 1] + 
		x * igrf2_2.h__[ih + 3] - y * (igrf2_2.h__[ih + 2] + 
		igrf2_2.h__[ih - 1]);
	igrf2_2.h__[il] = model_1.g[il] + z__ * igrf2_2.h__[ih] + y * 
		igrf2_2.h__[ih + 3] + x * (igrf2_2.h__[ih + 2] - igrf2_2.h__[
		ih - 1]);
L5:
	igrf2_2.h__[il - 1] = model_1.g[il - 1] + z__ * igrf2_2.h__[ih - 1] + 
		(x * igrf2_2.h__[ih] + y * igrf2_2.h__[ih + 1]) * (float)2.;
	ih = il;
	if (i__ >= k) {
	    goto L1;
	}
/* L6: */
    }
    if (is == 3) {
	return 0;
    }
    s = igrf2_2.h__[0] * (float).5 + (igrf2_2.h__[1] * igrf2_2.xi[2] + 
	    igrf2_2.h__[2] * igrf2_2.xi[0] + igrf2_2.h__[3] * igrf2_2.xi[1]) *
	     (float)2.;
    t = (rq + rq) * sqrt(rq);
    bxxx = t * (igrf2_2.h__[2] - s * xxx);
    byyy = t * (igrf2_2.h__[3] - s * yyy);
    bzzz = t * (igrf2_2.h__[1] - s * zzz);
    if (is == 2) {
	goto L7;
    }
    *babs = sqrt(bxxx * bxxx + byyy * byyy + bzzz * bzzz);
    *beast = byyy * cp - bxxx * sp;
    brho = byyy * sp + bxxx * cp;
    *bnorth = bzzz * st - brho * ct;
    *bdown = -bzzz * ct - brho * st;
    return 0;
L7:
    b[1] = bxxx;
    b[2] = byyy;
    b[3] = bzzz;
    return 0;
} /* feldg_ */

/* Subroutine */ int feldg_(glat, glon, alt, bnorth, beast, bdown, babs)
real *glat, *glon, *alt, *bnorth, *beast, *bdown, *babs;
{
    return feldg_0_(0, glat, glon, alt, bnorth, beast, bdown, babs, (real *)0,
	     (real *)0);
    }

/* Subroutine */ int feldc_(v, b)
real *v, *b;
{
    return feldg_0_(1, (real *)0, (real *)0, (real *)0, (real *)0, (real *)0, 
	    (real *)0, (real *)0, v, b);
    }

/* Subroutine */ int feldi_()
{
    return feldg_0_(2, (real *)0, (real *)0, (real *)0, (real *)0, (real *)0, 
	    (real *)0, (real *)0, (real *)0, (real *)0);
    }



/* Subroutine */ int feldcof_(year, dimo)
real *year, *dimo;
{
    /* Initialized data */

    static char filmod[13*15+1] = "dgrf1945.dat dgrf1950.dat dgrf1955.dat dg\
rf1960.dat dgrf1965.dat dgrf1970.dat dgrf1975.dat dgrf1980.dat dgrf1985.dat \
dgrf1990.dat dgrf1995.dat dgrf2000.dat dgrf2005.dat igrf2010.dat igrf2010s.d\
at";
    static real dtemod[15] = { (float)1945.,(float)1950.,(float)1955.,(float)
	    1960.,(float)1965.,(float)1970.,(float)1975.,(float)1980.,(float)
	    1985.,(float)1990.,(float)1995.,(float)2e3,(float)2005.,(float)
	    2010.,(float)2015. };

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    /* Subroutine */ int s_copy(), s_stop();
    double sqrt();

    /* Local variables */
    static integer iyea;
    extern /* Subroutine */ int intershc_(), extrashc_();
    static integer nmax1, nmax2;
    static doublereal f;
    static integer i__, j;
    static real sqrt2;
    static integer l, m, n;
    static doublereal x, f0;
    static integer numye, is, iu;
    extern /* Subroutine */ int getshc_();
    static real gh2[196], gha[196];
    static integer ier;
    static char fil2[13];
    static real dte1, dte2;

/* ----------------------------------------------------------------------- */
/*  DETERMINES COEFFICIENTS AND DIPOL MOMENT FROM IGRF MODELS */

/*       INPUT:  YEAR    DECIMAL YEAR FOR WHICH GEOMAGNETIC FIELD IS TO */
/*                       BE CALCULATED */
/*       OUTPUT: DIMO    GEOMAGNETIC DIPOL MOMENT IN GAUSS (NORMALIZED */
/*                       TO EARTH'S RADIUS) AT THE TIME (YEAR) */
/* 05/31/2000 updated to IGRF-2000 version (###) */
/* 03/24/2000 updated to IGRF-2005 version (###) */
/* 07/22/2009 NMAX=13 for DGRF00 and IGRF05; H/G-arrays(195) */
/* 02/26/2010 updated to IGRF-2010 version (###) */
/* 10/05/2011 added COMMON/DIPOL/ for MLT computation in DPMTRX (IRIFUN) */
/* ----------------------------------------------------------------------- */
/* ### FILMOD, DTEMOD array-size is number of IGRF maps */
/* ### updated coefficient file names and corresponding years */

/* ### numye is number of IGRF coefficient files minus 1 */

    numye = 14;

/*  IS=0 FOR SCHMIDT NORMALIZATION   IS=1 GAUSS NORMALIZATION */
/*  IU  IS INPUT UNIT NUMBER FOR IGRF COEFFICIENT SETS */

    iu = 14;
    is = 0;
/* -- DETERMINE IGRF-YEARS FOR INPUT-YEAR */
    model_2.time = *year;
    iyea = (integer) (*year / (float)5.) * 5;
    l = (iyea - 1945) / 5 + 1;
    if (l < 1) {
	l = 1;
    }
    if (l > numye) {
	l = numye;
    }
    dte1 = dtemod[l - 1];
    s_copy(model_2.fil1, filmod + (l - 1) * 13, (ftnlen)13, (ftnlen)13);
    dte2 = dtemod[l];
    s_copy(fil2, filmod + l * 13, (ftnlen)13, (ftnlen)13);
/* -- GET IGRF COEFFICIENTS FOR THE BOUNDARY YEARS */
    getshc_(&iu, model_2.fil1, &nmax1, &igrf1_2.erad, model_2.gh1, &ier, (
	    ftnlen)13);
    if (ier != 0) {
	s_stop("", (ftnlen)0);
    }
    getshc_(&iu, fil2, &nmax2, &igrf1_2.erad, gh2, &ier, (ftnlen)13);
    if (ier != 0) {
	s_stop("", (ftnlen)0);
    }
/* -- DETERMINE IGRF COEFFICIENTS FOR YEAR */
    if (l <= numye - 1) {
	intershc_(year, &dte1, &nmax1, model_2.gh1, &dte2, &nmax2, gh2, &
		model_2.nmax, gha);
    } else {
	extrashc_(year, &dte1, &nmax1, model_2.gh1, &nmax2, gh2, &
		model_2.nmax, gha);
    }
/* -- DETERMINE MAGNETIC DIPOL MOMENT AND COEFFIECIENTS G */
    f0 = 0.;
    for (j = 1; j <= 3; ++j) {
	f = gha[j - 1] * 1e-5;
	f0 += f * f;
/* L1234: */
    }
    *dimo = sqrt(f0);
    dipol_1.ghi1 = gha[0];
    dipol_1.ghi2 = gha[1];
    dipol_1.ghi3 = gha[2];
    model_2.gh1[0] = (float)0.;
    i__ = 2;
    f0 = 1e-5;
    if (is == 0) {
	f0 = -f0;
    }
    sqrt2 = sqrt((float)2.);
    i__1 = model_2.nmax;
    for (n = 1; n <= i__1; ++n) {
	x = (doublereal) n;
	f0 = f0 * x * x / (x * 4. - 2.);
	if (is == 0) {
	    f0 = f0 * (x * 2. - 1.) / x;
	}
	f = f0 * .5;
	if (is == 0) {
	    f *= sqrt2;
	}
	model_2.gh1[i__ - 1] = gha[i__ - 2] * f0;
	++i__;
	i__2 = n;
	for (m = 1; m <= i__2; ++m) {
	    f = f * (x + m) / (x - m + 1.);
	    if (is == 0) {
		f *= sqrt((x - m + 1.) / (x + m));
	    }
	    model_2.gh1[i__ - 1] = gha[i__ - 2] * f;
	    model_2.gh1[i__] = gha[i__ - 1] * f;
	    i__ += 2;
/* L9: */
	}
    }
    return 0;
} /* feldcof_ */



/* Subroutine */ int getshc_(iu, fspec, nmax, erad, gh, ier, fspec_len)
integer *iu;
char *fspec;
integer *nmax;
real *erad, *gh;
integer *ier;
ftnlen fspec_len;
{
    /* Format strings */
    static char fmt_667[] = "(a13)";
    static char fmt_100[] = "(\002Error while reading \002,a13)";

    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer s_wsfi(), do_fio(), e_wsfi(), f_open(), s_rsle(), e_rsle(), 
	    do_lio(), s_wsfe(), e_wsfe(), f_clos();

    /* Local variables */
    static char fout[80];
    static integer i__, j, nm;
    static real xmyear;

    /* Fortran I/O blocks */
    static icilist io___143 = { 0, fout, 0, fmt_667, 80, 1 };
    static cilist io___144 = { 1, 0, 1, 0, 0 };
    static cilist io___145 = { 1, 0, 1, 0, 0 };
    static cilist io___148 = { 1, 0, 1, 0, 0 };
    static cilist io___150 = { 0, 0, 0, fmt_100, 0 };


/* =============================================================== */
/*       Reads spherical harmonic coefficients from the specified */
/*       file into an array. */
/*       Input: */
/*           IU    - Logical unit number */
/*           FSPEC - File specification */
/*       Output: */
/*           NMAX  - Maximum degree and order of model */
/*           ERAD  - Earth's radius associated with the spherical */
/*                   harmonic coefficients, in the same units as */
/*                   elevation */
/*           GH    - Schmidt quasi-normal internal spherical */
/*                   harmonic coefficients */
/*           IER   - Error number: =  0, no error */
/*                                 = -2, records out of order */
/*                                 = FORTRAN run-time error number */
/* =============================================================== */
    /* Parameter adjustments */
    --gh;

    /* Function Body */
    for (j = 1; j <= 196; ++j) {
/* L1: */
	gh[j] = (float)0.;
    }
/* --------------------------------------------------------------- */
/*       Open coefficient file. Read past first header record. */
/*       Read degree and order of model and Earth's radius. */
/* --------------------------------------------------------------- */
    s_wsfi(&io___143);
    do_fio(&c__1, fspec, fspec_len);
    e_wsfi();
/* 667    FORMAT('/var/www/omniweb/cgi/vitmo/IRI/',A13) */
    o__1.oerr = 1;
    o__1.ounit = *iu;
    o__1.ofnmlen = 80;
    o__1.ofnm = fout;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    *ier = f_open(&o__1);
    if (*ier != 0) {
	goto L999;
    }
    io___144.ciunit = *iu;
    *ier = s_rsle(&io___144);
    if (*ier != 0) {
	goto L100001;
    }
    *ier = e_rsle();
L100001:
    if (*ier > 0) {
	goto L999;
    }
    io___145.ciunit = *iu;
    *ier = s_rsle(&io___145);
    if (*ier != 0) {
	goto L100002;
    }
    *ier = do_lio(&c__3, &c__1, (char *)&(*nmax), (ftnlen)sizeof(integer));
    if (*ier != 0) {
	goto L100002;
    }
    *ier = do_lio(&c__4, &c__1, (char *)&(*erad), (ftnlen)sizeof(real));
    if (*ier != 0) {
	goto L100002;
    }
    *ier = do_lio(&c__4, &c__1, (char *)&xmyear, (ftnlen)sizeof(real));
    if (*ier != 0) {
	goto L100002;
    }
    *ier = e_rsle();
L100002:
    if (*ier > 0) {
	goto L999;
    }
    nm = *nmax * (*nmax + 2);
    io___148.ciunit = *iu;
    *ier = s_rsle(&io___148);
    if (*ier != 0) {
	goto L100003;
    }
    i__1 = nm;
    for (i__ = 1; i__ <= i__1; ++i__) {
	*ier = do_lio(&c__4, &c__1, (char *)&gh[i__], (ftnlen)sizeof(real));
	if (*ier != 0) {
	    goto L100003;
	}
    }
    *ier = e_rsle();
L100003:
    if (*ier > 0) {
	goto L999;
    }
    goto L888;
L999:
    if (iounit_1.konsol > 1) {
	io___150.ciunit = iounit_1.konsol;
	s_wsfe(&io___150);
	do_fio(&c__1, fout, (ftnlen)80);
	e_wsfe();
    }
L888:
    cl__1.cerr = 0;
    cl__1.cunit = *iu;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* getshc_ */



/* Subroutine */ int intershc_(date, dte1, nmax1, gh1, dte2, nmax2, gh2, nmax,
	 gh)
real *date, *dte1;
integer *nmax1;
real *gh1, *dte2;
integer *nmax2;
real *gh2;
integer *nmax;
real *gh;
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l;
    static real factor;

/* =============================================================== */

/*       Version 1.01 */

/*       Interpolates linearly, in time, between two spherical */
/*       harmonic models. */

/*       Input: */
/*           DATE  - Date of resulting model (in decimal year) */
/*           DTE1  - Date of earlier model */
/*           NMAX1 - Maximum degree and order of earlier model */
/*           GH1   - Schmidt quasi-normal internal spherical */
/*                   harmonic coefficients of earlier model */
/*           DTE2  - Date of later model */
/*           NMAX2 - Maximum degree and order of later model */
/*           GH2   - Schmidt quasi-normal internal spherical */
/*                   harmonic coefficients of later model */

/*       Output: */
/*           GH    - Coefficients of resulting model */
/*           NMAX  - Maximum degree and order of resulting model */

/*       A. Zunde */
/*       USGS, MS 964, Box 25046 Federal Center, Denver, CO  80225 */

/* =============================================================== */
/* --------------------------------------------------------------- */
/*       The coefficients (GH) of the resulting model, at date */
/*       DATE, are computed by linearly interpolating between the */
/*       coefficients of the earlier model (GH1), at date DTE1, */
/*       and those of the later model (GH2), at date DTE2. If one */
/*       model is smaller than the other, the interpolation is */
/*       performed with the missing coefficients assumed to be 0. */
/* --------------------------------------------------------------- */
    /* Parameter adjustments */
    --gh;
    --gh2;
    --gh1;

    /* Function Body */
    factor = (*date - *dte1) / (*dte2 - *dte1);
    if (*nmax1 == *nmax2) {
	k = *nmax1 * (*nmax1 + 2);
	*nmax = *nmax1;
    } else if (*nmax1 > *nmax2) {
	k = *nmax2 * (*nmax2 + 2);
	l = *nmax1 * (*nmax1 + 2);
	i__1 = l;
	for (i__ = k + 1; i__ <= i__1; ++i__) {
/* L1122: */
	    gh[i__] = gh1[i__] + factor * (-gh1[i__]);
	}
	*nmax = *nmax1;
    } else {
	k = *nmax1 * (*nmax1 + 2);
	l = *nmax2 * (*nmax2 + 2);
	i__1 = l;
	for (i__ = k + 1; i__ <= i__1; ++i__) {
/* L1133: */
	    gh[i__] = factor * gh2[i__];
	}
	*nmax = *nmax2;
    }
    i__1 = k;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L1144: */
	gh[i__] = gh1[i__] + factor * (gh2[i__] - gh1[i__]);
    }
    return 0;
} /* intershc_ */



/* Subroutine */ int extrashc_(date, dte1, nmax1, gh1, nmax2, gh2, nmax, gh)
real *date, *dte1;
integer *nmax1;
real *gh1;
integer *nmax2;
real *gh2;
integer *nmax;
real *gh;
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k, l;
    static real factor;

/* =============================================================== */

/*       Version 1.01 */

/*       Extrapolates linearly a spherical harmonic model with a */
/*       rate-of-change model. */

/*       Input: */
/*           DATE  - Date of resulting model (in decimal year) */
/*           DTE1  - Date of base model */
/*           NMAX1 - Maximum degree and order of base model */
/*           GH1   - Schmidt quasi-normal internal spherical */
/*                   harmonic coefficients of base model */
/*           NMAX2 - Maximum degree and order of rate-of-change */
/*                   model */
/*           GH2   - Schmidt quasi-normal internal spherical */
/*                   harmonic coefficients of rate-of-change model */

/*       Output: */
/*           GH    - Coefficients of resulting model */
/*           NMAX  - Maximum degree and order of resulting model */

/*       A. Zunde */
/*       USGS, MS 964, Box 25046 Federal Center, Denver, CO  80225 */

/* =============================================================== */
/* --------------------------------------------------------------- */
/*       The coefficients (GH) of the resulting model, at date */
/*       DATE, are computed by linearly extrapolating the coef- */
/*       ficients of the base model (GH1), at date DTE1, using */
/*       those of the rate-of-change model (GH2), at date DTE2. If */
/*       one model is smaller than the other, the extrapolation is */
/*       performed with the missing coefficients assumed to be 0. */
/* --------------------------------------------------------------- */
    /* Parameter adjustments */
    --gh;
    --gh2;
    --gh1;

    /* Function Body */
    factor = *date - *dte1;
    if (*nmax1 == *nmax2) {
	k = *nmax1 * (*nmax1 + 2);
	*nmax = *nmax1;
    } else if (*nmax1 > *nmax2) {
	k = *nmax2 * (*nmax2 + 2);
	l = *nmax1 * (*nmax1 + 2);
	i__1 = l;
	for (i__ = k + 1; i__ <= i__1; ++i__) {
/* L1155: */
	    gh[i__] = gh1[i__];
	}
	*nmax = *nmax1;
    } else {
	k = *nmax1 * (*nmax1 + 2);
	l = *nmax2 * (*nmax2 + 2);
	i__1 = l;
	for (i__ = k + 1; i__ <= i__1; ++i__) {
/* L1166: */
	    gh[i__] = factor * gh2[i__];
	}
	*nmax = *nmax2;
    }
    i__1 = k;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L1177: */
	gh[i__] = gh1[i__] + factor * gh2[i__];
    }
    return 0;
} /* extrashc_ */



/* Subroutine */ int initize_()
{
    /* Builtin functions */
    double atan();

    /* Local variables */
    static real erequ, erpol;

/* ---------------------------------------------------------------- */
/* Initializes the parameters in COMMON/IGRF1/ */

/*       UMR     = ATAN(1.0)*4./180.   <DEGREE>*UMR=<RADIANT> */
/*       ERA     EARTH RADIUS FOR NORMALIZATION OF CARTESIAN */
/*                       COORDINATES (6371.2 KM) */
/*       EREQU   MAJOR HALF AXIS FOR EARTH ELLIPSOID (6378.160 KM) */
/*       ERPOL   MINOR HALF AXIS FOR EARTH ELLIPSOID (6356.775 KM) */
/*       AQUAD   SQUARE OF MAJOR HALF AXIS FOR EARTH ELLIPSOID */
/*       BQUAD   SQUARE OF MINOR HALF AXIS FOR EARTH ELLIPSOID */

/* ERA, EREQU and ERPOL as recommended by the INTERNATIONAL */
/* ASTRONOMICAL UNION . */
/* ----------------------------------------------------------------- */
    igrf1_1.era = (float)6371.2;
    erequ = (float)6378.16;
    erpol = (float)6356.775;
    igrf1_1.aquad = erequ * erequ;
    igrf1_1.bquad = erpol * erpol;
    igrf1_1.umr = atan((float)1.) * (float)4. / (float)180.;
    return 0;
} /* initize_ */



/* Subroutine */ int geodip_(iyr, sla, slo, dla, dlo, j)
integer *iyr;
real *sla, *slo, *dla, *dlo;
integer *j;
{
    static real r__, x, y, z__, pf, th;
    extern /* Subroutine */ int geomag_();
    static real rm, xm, ym, zm;
    extern /* Subroutine */ int sphcar_();
    static real dco, col, sco, rlo, szm;

/*  Calculates dipole geomagnetic coordinates from geocentric coordinates */
/*  or vice versa. */
/*                     J=0           J=1 */
/* 		INPUT:     J,SLA,SLO     J,DLA,DLO */
/* 		OUTPUT:     DLA,DLO       SLA,SLO */
/*  Last revision: November 2005 (Vladimir Papitashvili) */
/*  The code is modifed from GEOCOR written by V.Popov and V.Papitashvili */
/*  in mid-1980s. */
/*  Earth's radius (km) RE = 6371.2 */
/*  The radius of the sphere to compute the coordinates (in Re) */
/*        RH = (RE + HI)/RE */
    r__ = (float)1.;
    if (*j > 0) {
	goto L1234;
    }
    col = ((float)90. - *sla) * const_1.umr;
    rlo = *slo * const_1.umr;
    sphcar_(&r__, &col, &rlo, &x, &y, &z__, &c__1);
    geomag_(&x, &y, &z__, &xm, &ym, &zm, &c__1, iyr);
    sphcar_(&rm, &th, &pf, &xm, &ym, &zm, &c_n1);
    szm = zm;
    *dlo = pf / const_1.umr;
    dco = th / const_1.umr;
    *dla = (float)90. - dco;
    return 0;
L1234:
    col = ((float)90. - *dla) * const_1.umr;
    rlo = *dlo * const_1.umr;
    sphcar_(&r__, &col, &rlo, &xm, &ym, &zm, &c__1);
    geomag_(&x, &y, &z__, &xm, &ym, &zm, &c_n1, iyr);
    sphcar_(&rm, &th, &pf, &x, &y, &z__, &c_n1);
    szm = zm;
    *slo = pf / const_1.umr;
    sco = th / const_1.umr;
    *sla = (float)90. - sco;
    return 0;
} /* geodip_ */



doublereal fmodip_(xlat)
real *xlat;
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static real dipl;
    extern /* Subroutine */ int igrf_dip__();
    static real ymodip, dec, dip;

    igrf_dip__(xlat, &findrlat_1.xlong, &findrlat_1.year, &c_b81, &dec, &dip, 
	    &dipl, &ymodip);
    ret_val = ymodip;
    return ret_val;
} /* fmodip_ */



/* Subroutine */ int geocgm01_(icor, iyear, hi, dat, pla, plo)
integer *icor, *iyear;
real *hi, *dat, *pla, *plo;
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfi(), do_fio(), e_wsfi(), s_rsfi(), e_rsfi();

    /* Local variables */
    static real clac, claj, cloc, clar, slac, plaj, cloj, slaj, plan, slal, 
	    clor, sloc, slar, plas, ploj, sloj, plon, slol, plos, slor, plan1,
	     plas1, plon1, plos1, aclac;
    static integer i__, j;
    static real acloc, aclar, slacf, aclor, slocf, slarf, slorf;
    extern /* Subroutine */ int mltut_();
    static real re, rh, rj, ut;
    extern /* Subroutine */ int geocor_(), corgeo_(), geolow_();
    static integer icount;
    extern /* Subroutine */ int ftprnt_();
    static real daa, dla;
    extern /* Subroutine */ int mfc_();
    static real bfr, dlo, pmc, rbm, doo, brr, btr, azm, pmm;
    extern doublereal azm_ang__();
    static real pmp, pmr, ovl;
    extern doublereal ovl_ang__();
    static char str[12];

    /* Fortran I/O blocks */
    static icilist io___193 = { 0, str, 0, "(2F6.2)", 12, 1 };
    static icilist io___194 = { 0, str, 0, "(2F6.2)", 12, 1 };


/*  ********************************************************************* */
/*  Version 2011 for GEO-CGM.FOR    (good through 2015)      January 2011 */
/*  Version 2005 for GEO-CGM.FOR    (good through 2010)     November 2005 */
/*  Nov 11, 2005  IGRF and RECALC are is modified to the IGRF-10 model */
/*                and extended back to 1900 using the DGRF coeffcients */
/*  Apr 11, 2001  GEOLOW is modified to account for interpolation of */
/*                CGM meridians near equator across the 360/0 boundary */
/*  AUTHORS: */
/*  Natalia E. Papitashvili (WDC-B2, Moscow, Russia, now at NSSDC, */
/*    NASA/Goddard Space Flight Center, Greenbelt, Maryland) */
/*  Vladimir O. Papitashvili (IZMIRAN, Moscow, Russia, now at SPRL, */
/*    University of Michigan, Ann Arbor) */
/*  Conributions from Boris A. Belov and Vladimir A. Popov (both at */
/*    IZMIRAN), Therese Moretto (DMI, DSRI, now at NSF), Freddy */
/*    Christiansen (DMI, DSRI), and Scott Boardsen (NASA/GSFC). */
/*  The original version of this code is described in the brochure by */
/*  N.A. Tsyganenko, A.V. Usmanov, V.O. Papitashvili, N.E. Papitashvili, */
/*  and V.A. Popov, Software for computations of geomagnetic field and */
/*  related coordinate systems, Soviet Geophys. Committ., Moscow, 58 pp., */
/*  1987. A number of subroutines from the revised GEOPACK-96 software */
/*  package developed by Nikolai A. Tsyganenko and Mauricio Peredo are */
/*  utilized in this code with some modifications (see full versions of */
/*  GEOPACK packages on http://www-spof.gsfc.nasa.gov/Modeling/geopack.html). */
/*  This code consists of the main subroutine GEOCGM01, five functions */
/*  (OVL_ANG, CGMGLA, CGMGLO, DFRIDR, and AZM_ANG), eigth new and revised */
/*  subroutines from the above-mentioned brochure (MLTUT, MFC, FTPRNT, */
/*  GEOLOW, CORGEO, GEOCOR, SHAG, and RIGHT), and 9 subroutines from */
/*  GEOPACK-96 (IGRF, SPHCAR, BSPCAR, GEOMAG, MAGSM, SMGSM, RECALC, SUN) */
/*  ===================================================================== */
/*  Input parameters: */
/*     ICOR = +1    geo to cgm */
/*            -1    cgm to geo */
/*     IYEAR= year */
/*     HI   = altitude in km */
/*  Input/Output parameters: */
/*     DAT(1,i)=slar geocentric latitude (input/output if icor=+1/-1) */
/*     DAT(2,i)=slor geocentric longitude (input/output if icor=+1/-1) */
/*     DAT(3,i)=clar CGM latitude (input/output if icor=-1/+1) */
/*     DAT(4,i)=clor CGM longitude (input/output if icor=-1/+1) */
/*  Output parameters: */
/*     DAT(5,i)=rbm apex of the magnetic field line in Re (Re=6371.2 km) */
/*            (this parameter approximately equals the McIlwain L-value) */
/*     DAT(6,i)=btr IGRF Magnetic field H (nT) */
/*     DAT(7,i)=brr IGRF Magnetic field D (deg) */
/*     DAT(8,i)=ovl oval_angle as the azimuth to "magnetic north": */
/*                + east in Northern Hemisphere */
/*                + west in Southern Hemisphere */
/*     DAT(9,i)=azm meridian_angle as the azimuth to the CGM pole: */
/*                + east in Northern Hemisphere */
/*                + west in Southern Hemisphere */
/*     DAT(10,i)=utm magnetic local time (MLT) midnight in UT hours */
/*     		 i=1	for the start point */
/*     		 i=2	for the conjugate point of the start point (slac, sloc) */
/* 			 i=3    for the footprint at 1-Re of the start point (slaf,slof) */
/* 			 i=4    for the conjugate footprint at 1-Re of the start point */
/*     PLA(1)	geocentric latitude of the CGM pole in the Northern hemisphere */
/*     PLO(1)	geocentric longitude of the CGM pole in the Northern hemisphere */
/*     PLA(2)	geocentric latitude of the CGM pole in the Southern hemisphere */
/*     PLO(2)	geocentric longitude of the CGM pole in the Southern hemisphere */
/*     PLA(3)	geoce lati CGM North pole at the Earth's surface 1-Re or zero alt. */
/*     PLO(3)	geoce long CGM North pole at the Earth's surface 1-Re or zero alt. */
/*     PLA(4)	geoce lati CGM South pole at the Earth's surface 1-Re or zero alt. */
/*     PLO(4)	geoce long CGM South pole at the Earth's surface 1-Re or zero alt. */

/* In program: */
/*     dla  = dipole latitude */
/*     dlo  = dipole longitude */
/*  ===================================================================== */
/*      COMMON /C1/ AA(27),II(2),BB(8) */
/*      COMMON /RZ/ RH */
/*  Year (for example, as for Epoch 1995.0 - no fraction of the year) */
    /* Parameter adjustments */
    --plo;
    --pla;
    dat -= 12;

    /* Function Body */
    iyr_1.iyr = *iyear;
/*  Earth's radius (km) */
    re = (float)6371.2;
/*  NM is the number of harmonics */
    nm_1.nm = 10;
/*  The radius of the sphere to compute the coordinates (in Re) */
    rh = (re + *hi) / re;
/*  Correction of latitudes and longitudes if they are entered beyond of */
/*  the limits (this actually does not affect coordinate calculations */
/*  but the oval/meridian angles and MLT midnight cannot be computed) */
    if (dat[12] > (float)90.) {
	dat[12] = (float)180. - dat[12];
    }
    if (dat[12] < (float)-90.) {
	dat[12] = (float)-180. - dat[12];
    }
    if (dat[14] > (float)90.) {
	dat[14] = (float)180. - dat[14];
    }
    if (dat[14] < (float)-90.) {
	dat[14] = (float)-180. - dat[14];
    }
    if (dat[13] > (float)360.) {
	dat[13] += (float)-360.;
    }
    if (dat[13] < (float)-360.) {
	dat[13] += (float)360.;
    }
    if (dat[15] > (float)360.) {
	dat[15] += (float)-360.;
    }
    if (dat[15] < (float)-360.) {
	dat[15] += (float)360.;
    }
/*  Computation of CGM coordinates from geocentric ones at high- and */
/*  middle latitudes */
    if (*icor == 1) {
	slar = dat[12];
	slor = dat[13];
	if (dabs(slar) == (float)90.) {
	    slor = (float)360.;
	}
	geocor_(&slar, &slor, &rh, &dla, &dlo, &clar, &clor, &pmr);
	dat[14] = clar;
	dat[15] = clor;
    } else {
/*  Computation of geocentric coordinates from CGM ones at high- and */
/*  middle latitudes */
	clar = dat[14];
	clor = dat[15];
	if (dabs(clar) == (float)90.) {
	    clor = (float)360.;
	}
	corgeo_(&slar, &slor, &rh, &dla, &dlo, &clar, &clor, &pmr);
	dat[12] = slar;
	dat[13] = slor;
    }
/*  PMI is L-shell parameter for the magnetic field line; limit to 16 Re */
    if (pmr >= (float)16.) {
	pmr = (float)999.99;
    }
    dat[16] = pmr;
/*  Check if CGM_Lat has been calculated, then go for the conjugate point */
    if (clar > (float)999.) {
/*  CGM_Lat has NOT been calculated, call GEOLOW for computation of the */
/*  CGM coordinates at low latitudes using the CBM approach (see the */
/*  reference in GEOLOW) */
	geolow_(&slar, &slor, &rh, &clar, &clor, &rbm, &slac, &sloc);
	dat[14] = clar;
	dat[15] = clor;
	if (rbm >= (float)16.) {
	    rbm = (float)999.99;
	}
	dat[16] = rbm;
/*  Conjugate point coordinates at low latitudes */
	s_wsfi(&io___193);
	do_fio(&c__1, (char *)&slac, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&sloc, (ftnlen)sizeof(real));
	e_wsfi();
	s_rsfi(&io___194);
	do_fio(&c__1, (char *)&slac, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&sloc, (ftnlen)sizeof(real));
	e_rsfi();
	dat[23] = slac;
	dat[24] = sloc;
	geocor_(&slac, &sloc, &rh, &daa, &doo, &clac, &cloc, &rbm);
	if (clac > (float)999.) {
	    geolow_(&slac, &sloc, &rh, &clac, &cloc, &rbm, &slal, &slol);
	}
	dat[25] = clac;
	dat[26] = cloc;
	dat[27] = rbm;
    } else {
/*  Computation of the magnetically conjugated point at high- and */
/*  middle latitudes */
	clac = -clar;
	cloc = clor;
	dat[25] = clac;
	dat[26] = cloc;
	corgeo_(&slac, &sloc, &rh, &daa, &doo, &clac, &cloc, &pmc);
	dat[23] = slac;
	dat[24] = sloc;
	if (pmc >= (float)16.) {
	    pmc = (float)999.99;
	}
	dat[27] = pmc;
    }
/*  Same RBM for footprints as for the starting and conjugate points */
    dat[38] = dat[16];
    dat[49] = dat[27];
/*  Calculation of the magnetic field line footprint at the */
/*  Earth's surface for the starting point */
    if (rh > (float)1. && clar < (float)999. && clar < (float)999.) {
	ftprnt_(&rh, &slar, &slor, &clar, &clor, &aclar, &aclor, &slarf, &
		slorf, &c_b3);
	dat[34] = slarf;
	dat[35] = slorf;
	dat[36] = aclar;
	dat[37] = aclor;
/*  and for the conjugate point */
	ftprnt_(&rh, &slac, &sloc, &clac, &cloc, &aclac, &acloc, &slacf, &
		slocf, &c_b3);
	dat[45] = slacf;
	dat[46] = slocf;
	dat[47] = aclac;
	dat[48] = acloc;
    } else {
	for (i__ = 1; i__ <= 4; ++i__) {
	    for (j = 3; j <= 4; ++j) {
		dat[i__ + j * 11] = (float)999.99;
	    }
	}
    }
/*  Computation of geocentric coordinates of the North or South CGM */
/*  poles for a given year at the altitude RH and Earth's surface (1-Re) */
    corgeo_(&plan, &plon, &rh, &daa, &doo, &c_b91, &c_b92, &pmp);
    plan1 = plan;
    plon1 = plon;
    corgeo_(&plas, &plos, &rh, &daa, &doo, &c_b93, &c_b92, &pmp);
    plas1 = plas;
    plos1 = plos;
    if (rh > (float)1.) {
	corgeo_(&plan1, &plon1, &c_b3, &daa, &doo, &c_b91, &c_b92, &pmp);
	corgeo_(&plas1, &plos1, &c_b3, &daa, &doo, &c_b93, &c_b92, &pmm);
    }
    if (clar < (float)0.) {
	pla[1] = plas;
	plo[1] = plos;
    } else {
	pla[1] = plan;
	plo[1] = plon;
    }
    if (aclar < (float)0.) {
	pla[3] = plas1;
	plo[3] = plos1;
    } else {
	pla[3] = plan1;
	plo[3] = plon1;
    }
    if (clac < (float)0.) {
	pla[2] = plas;
	plo[2] = plos;
    } else {
	pla[2] = plan;
	plo[2] = plon;
    }
    if (aclac < (float)0.) {
	pla[4] = plas1;
	plo[4] = plos1;
    } else {
	pla[4] = plan1;
	plo[4] = plon1;
    }
    for (j = 1; j <= 4; ++j) {
	dat[j * 11 + 6] = (float)99999.;
	dat[j * 11 + 7] = (float)999.99;
	dat[j * 11 + 8] = (float)99999.;
	dat[j * 11 + 9] = (float)999.99;
	dat[j * 11 + 10] = (float)999.99;
	dat[j * 11 + 11] = (float)99.99;
    }
    icount = 2;
    if (rh > (float)1.) {
	icount = 4;
    }
    rj = rh;
    i__1 = icount;
    for (j = 1; j <= i__1; ++j) {
	if (j > 2) {
	    rj = (float)1.;
	}
	plaj = pla[j];
	ploj = plo[j];
	slaj = dat[j * 11 + 1];
	sloj = dat[j * 11 + 2];
	claj = dat[j * 11 + 3];
	cloj = dat[j * 11 + 4];
/*  Computation of the IGRF components */
	mfc_(&slaj, &sloj, &rj, &btr, &bfr, &brr);
	dat[j * 11 + 6] = btr;
	dat[j * 11 + 7] = bfr;
	dat[j * 11 + 8] = brr;
/*  Computation of the oval_angle (OVL) between the tangents to */
/*  geographic and CGM latitudes at a given point (the code is slightly */
/*  modified from the source provided by Therese Morreto in 1994). Note */
/*  that rotation of OVL on 90 deg anticlockwise provides the azimuth */
/*  to the local "magnetic" north (south) measured from the local */
/*  geographic meridian. The OVL_ANG can be calculated only at middle */
/*  and high latitudes where CGM --> GEO is permitted. */
	ovl = ovl_ang__(&slaj, &sloj, &claj, &cloj, &rj);
	dat[j * 11 + 9] = ovl;
/*  Computation of the meridian_angle (AZM) between the geographic */
/*  meridian and direction (azimuth along the great-circle arc) to */
/*  the North (South) CGM pole */
	azm = azm_ang__(&slaj, &sloj, &claj, &plaj, &ploj);
	dat[j * 11 + 10] = azm;
/*  Computation of the MLT midnight (in UT) */
	mltut_(&slaj, &sloj, &claj, &plaj, &ploj, &ut);
	dat[j * 11 + 11] = ut;
/*  End of loop j = 1,icount */
    }
    return 0;
} /* geocgm01_ */



doublereal ovl_ang__(sla, slo, cla, clo, rr)
real *sla, *slo, *cla, *clo, *rr;
{
    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double cos(), atan2();

    /* Local variables */
    static real step, denom;
    extern doublereal cgmgla_(), cgmglo_(), dfridr_();
    static real hom, err1, err2;

/*  ********************************************************************* */
/*  This function returns an estimate at the given location of the angle */
/*  (oval_angle) between the directions (tangents) along the constant */
/*  CGM and geographic latitudes by utilizing the function DFRIDR from */
/*  Numerical Recipes for FORTRAN. */
/*  This angle can be taken as the azimuth to the local "magnetic" north */
/*  (south) if the eastward (westward) tangent to the local CGM latitude */
/*  points south (north) from the local geographic latitude. */
/*  Written by Therese Moretto in August 1994 (revised by V. Papitashvili */
/*  in January 1999). */
/*  ********************************************************************* */
/*  Ignore points which nearly coincide with the geographic or CGM poles */
/*  within 0.01 degree in latitudes; this also takes care if SLA or CLA */
/*  are dummy values (e.g., 999.99) */
    if (dabs(*sla) >= (float)89.99 || dabs(*cla) >= (float)89.99 || dabs(*sla)
	     < (float)30.) {
	ret_val = (float)999.99;
	return ret_val;
    }
/*  Initialize values for the cgmglo and cgmgla functions */
    cgmgeo_1.rh = *rr;
    cgmgeo_1.clat = *cla;
    cgmgeo_1.cr360 = FALSE_;
    cgmgeo_1.cr0 = FALSE_;
/*  Judge if SLO may be crossing the 360-0 limit. If geocentric */
/*  longitude of the location is larger than 270 deg, then cr360 is */
/*  set "true"; if it is less than 90 deg, then cr0 is set "true". */
    if (*slo >= (float)270.) {
	cgmgeo_1.cr360 = TRUE_;
    }
    if (*slo <= (float)90.) {
	cgmgeo_1.cr0 = TRUE_;
    }
/*  An initial stepsize (in degrees) */
    step = (float)10.;
/*  Note that in the near-pole region the functions CGMGLA and CGMGLO */
/*  could be called from DFRIDR with the CGM latitudes exceeded 90 or */
/*  -90 degrees (e.g., 98 or -98) when STEP is added or subtracted to a */
/*  given CGM latitude (CLA). This does not produce discontinuities in */
/*  the functions because GEOCOR calculates GEOLAT smoothly for the */
/*  points lying behind the pole (e.g., as for 82 or - 82 deg. in the */
/*  above-mentioned example). However, it could be discontinuity in */
/*  GEOLON if |GEOLAT| = 90 deg. - see CGMGLO for details. */
    hom = dfridr_(cgmgla_, clo, &step, &err1);
    denom = dfridr_(cgmglo_, clo, &step, &err2);
    denom *= cos(*sla * (float).017453293);
    ret_val = -atan2(hom, denom);
    ret_val *= (float)57.2957751;
    return ret_val;
} /* ovl_ang__ */



doublereal cgmgla_(clon)
real *clon;
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static real rr, geolat;
    extern /* Subroutine */ int corgeo_();
    static real geolon, dla, dlo, pmi;

/*  ********************************************************************* */
/*  This function returns the geocentric latitude as a function of CGM */
/*  longitude with the CGM latitude held in common block CGMGEO. */
/*  Essentially this function just calls the subroutine CORGEO. */
/*  ********************************************************************* */
    rr = cgmgeo_2.rh;
    if (*clon > (float)360.) {
	*clon += (float)-360.;
    }
    if (*clon < (float)0.) {
	*clon += (float)360.;
    }
    corgeo_(&geolat, &geolon, &rr, &dla, &dlo, &cgmgeo_2.cclat, clon, &pmi);
    ret_val = geolat;
    return ret_val;
} /* cgmgla_ */



doublereal cgmglo_(clon)
real *clon;
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static real rr, geolat;
    extern /* Subroutine */ int corgeo_();
    static real geolon, dla, dlo, pmi;

/* ********************************************************************* */
/*  Same as the function CGMGLA but this returns the geocentric */
/*  longitude. If cr360 is true, geolon+360 deg is returned when geolon */
/*  is less than 90 deg. If cr0 is true, geolon-360 deg is returned */
/*  when geolon is larger than 270 degrees. */
/* ********************************************************************* */
    rr = cgmgeo_2.rh;
    if (*clon > (float)360.) {
	*clon += (float)-360.;
    }
    if (*clon < (float)0.) {
	*clon += (float)360.;
    }
L1:
    corgeo_(&geolat, &geolon, &rr, &dla, &dlo, &cgmgeo_2.cclat, clon, &pmi);
/*  Geographic longitude geolon could be any number (e.g., discontinued) */
/*  when geolat is the geographic pole */
    if (dabs(geolat) >= (float)89.99) {
	*clon += (float)-.01;
	goto L1;
    }
    if (cgmgeo_2.cr360 && geolon <= (float)90.) {
	ret_val = geolon + (float)360.;
    } else {
	if (cgmgeo_2.cr0 && geolon >= (float)270.) {
	    ret_val = geolon - (float)360.;
	} else {
	    ret_val = geolon;
	}
    }
    return ret_val;
} /* cgmglo_ */



doublereal dfridr_(func, x, h__, err)
doublereal (*func) ();
real *x, *h__, *err;
{
    /* Format strings */
    static char fmt_100[] = "(\002h must be nonzero in dfridr\002)";

    /* System generated locals */
    integer i__1;
    real ret_val, r__1, r__2, r__3, r__4;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe();

    /* Local variables */
    static real errt, a[100]	/* was [10][10] */;
    static integer i__, j;
    static real hh, fac;

    /* Fortran I/O blocks */
    static cilist io___253 = { 0, 0, 0, fmt_100, 0 };


/* ********************************************************************** */
/*  Numerical Recipes Fortran 77 Version 2.07 */
/*  Copyright (c) 1986-1995 by Numerical Recipes Software */
/* ********************************************************************** */
    if (*h__ == (float)0.) {
	if (iounit_1.konsol > 1) {
	    io___253.ciunit = iounit_1.konsol;
	    s_wsfe(&io___253);
	    e_wsfe();
	}
	return ret_val;
    }
    hh = *h__;
    r__1 = *x + hh;
    r__2 = *x - hh;
    a[0] = ((*func)(&r__1) - (*func)(&r__2)) / (hh * (float)2.);
    *err = (float)1e30;
    for (i__ = 2; i__ <= 10; ++i__) {
	hh /= (float)1.4;
	r__1 = *x + hh;
	r__2 = *x - hh;
	a[i__ * 10 - 10] = ((*func)(&r__1) - (*func)(&r__2)) / (hh * (float)
		2.);
	fac = (float)1.9599999999999997;
	i__1 = i__;
	for (j = 2; j <= i__1; ++j) {
	    a[j + i__ * 10 - 11] = (a[j - 1 + i__ * 10 - 11] * fac - a[j - 1 
		    + (i__ - 1) * 10 - 11]) / (fac - (float)1.);
	    fac *= (float)1.9599999999999997;
/* Computing MAX */
	    r__3 = (r__1 = a[j + i__ * 10 - 11] - a[j - 1 + i__ * 10 - 11], 
		    dabs(r__1)), r__4 = (r__2 = a[j + i__ * 10 - 11] - a[j - 
		    1 + (i__ - 1) * 10 - 11], dabs(r__2));
	    errt = dmax(r__3,r__4);
	    if (errt <= *err) {
		*err = errt;
		ret_val = a[j + i__ * 10 - 11];
	    }
/* L11: */
	}
	if ((r__1 = a[i__ + i__ * 10 - 11] - a[i__ - 1 + (i__ - 1) * 10 - 11],
		 dabs(r__1)) >= *err * (float)2.) {
	    return ret_val;
	}
/* L12: */
    }
    return ret_val;
} /* dfridr_ */



doublereal azm_ang__(sla, slo, cla, pla, plo)
real *sla, *slo, *cla, *pla, *plo;
{
    /* Format strings */
    static char fmt_2[] = "(/\002WARNING - The CGM pole PLA = \002,f6.2,\002\
 and station CLAT = \002,f6.2,\002 are not in the same hemisphere: AZM_ANG i\
s incorrect!\002)";

    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double r_sign();
    integer s_wsfe(), do_fio(), e_wsfe();
    double sin(), tan(), cos(), atan2();

    /* Local variables */
    static real alfa, am, cm, sb, sp, ss, st, rad, bet;

    /* Fortran I/O blocks */
    static cilist io___262 = { 0, 7, 0, fmt_2, 0 };


/*  ********************************************************************* */
/*  Computation of an angle between the north geographic meridian and */
/*  direction to the North (South) CGM pole: positive azimuth is */
/*  measured East (West) from geographic meridian, i.e., the angle is */
/*  measured between the great-circle arc directions to the geographic */
/*  and CGM poles. In this case the geomagnetic field components in */
/*  XYZ (NEV) system can be converted into the CGM system in both */
/*  hemispheres as: */
/*                           XM = X cos(alf) + Y sin(alf) */
/*                           YM =-X sin(alf) + Y cos(alf) */
/*  Written by V. O. Papitashvili in mid-1980s; revised in February 1999 */
/*  Ignore points which nearly coincide with the geographic or CGM poles */
/*  within 0.01 degree in latitudes; this also takes care if SLA or CLA */
/*  are dummy values (e.g., 999.99) */
/*  ********************************************************************* */
    if (dabs(*sla) >= (float)89.99 || dabs(*cla) >= (float)89.99) {
	ret_val = (float)999.99;
	return ret_val;
    }
    sp = (float)1.;
    ss = (float)1.;
    if (r_sign(&sp, pla) != r_sign(&ss, cla)) {
	s_wsfe(&io___262);
	do_fio(&c__1, (char *)&(*pla), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*cla), (ftnlen)sizeof(real));
	e_wsfe();
    }
    rad = (float).017453293;
    am = ((float)90. - dabs(*pla)) * rad;
    if (r_sign(&sp, pla) == r_sign(&ss, sla)) {
	cm = ((float)90. - dabs(*sla)) * rad;
    } else {
	cm = (dabs(*sla) + (float)90.) * rad;
    }
    if (*sla >= (float)0.) {
	bet = (*plo - *slo) * rad;
    } else {
	bet = (*slo - *plo) * rad;
    }
    sb = sin(bet);
    st = sin(cm) / tan(am) - cos(cm) * cos(bet);
    alfa = atan2(sb, st);
    ret_val = alfa / rad;
    return ret_val;
} /* azm_ang__ */



/* Subroutine */ int mltut_(sla, slo, cla, pla, plo, ut)
real *sla, *slo, *cla, *pla, *plo, *ut;
{
    /* Format strings */
    static char fmt_2[] = "(/\002WARNING - The CGM pole PLA = \002,f6.2,\002\
 and station CLAT = \002,f6.2,\002 are not in the same hemisphere: MLTMN is \
incorrect!\002)";

    /* Builtin functions */
    double r_sign();
    integer s_wsfe(), do_fio(), e_wsfe();
    double sin(), cos(), atan2();

    /* Local variables */
    static real a, x, y, bp, bt, qq, sp, qt, ss, cff, rad, cft, tpi, qqu, qtu;

    /* Fortran I/O blocks */
    static cilist io___274 = { 0, 7, 0, fmt_2, 0 };


/*  ********************************************************************* */
/*  Calculates the MLT midnight in UT hours */
/*  Definition of the MLT midnight (MLTMN) here is different from the */
/*  approach described elsewhere. This definition does not take into */
/*  account the geomagnetic meridian of the subsolar point which causes */
/*  seasonal variations of the MLTMN in UT time. The latter approach is */
/*  perfectly applicable to the dipole or eccentric dipole magnetic */
/*  coordinates but it fails with the CGM coordinates because there are */
/*  forbidden areas near the geomagnetic equator where CGM coordinates */
/*  cannot be calculated by definition [e.g., Gustafsson et al., JATP, */
/*  54, 1609, 1992]. */
/*  In this code the MLT midnight is defined as location of a given point */
/*  on (or above) the Earth's surface strictly behind the North (South) */
/*  CGM pole in such the Sun, the pole, and the point are lined up. */
/*  This approach was originally proposed and coded by Boris Belov */
/*  sometime in the beginning of 1980s; here it is slightly edited by */
/*  Vladimir Papitashvili in February 1999. */
/*  Ignore points which nearly coincide with the geographic or CGM poles */
/*  within 0.01 degree in latitudes; this also takes care if SLA or CLA */
/*  are dummy values (e.g., 999.99) */
/*  ********************************************************************* */
    if (dabs(*sla) >= (float)89.99 || dabs(*cla) >= (float)89.99) {
	*ut = (float)99.99;
	return 0;
    }
    tpi = (float)6.283185307;
    rad = (float).017453293;
    sp = (float)1.;
    ss = (float)1.;
    if (r_sign(&sp, pla) != r_sign(&ss, cla)) {
	s_wsfe(&io___274);
	do_fio(&c__1, (char *)&(*pla), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*cla), (ftnlen)sizeof(real));
	e_wsfe();
    }
/*  Solve the spherical triangle */
    qq = *plo * rad;
    cff = (float)90. - dabs(*pla);
    cff *= rad;
    if (cff < (float)1e-7) {
	cff = (float)1e-7;
    }
    if (r_sign(&sp, pla) == r_sign(&ss, sla)) {
	cft = (float)90. - dabs(*sla);
    } else {
	cft = dabs(*sla) + (float)90.;
    }
    cft *= rad;
    if (cft < (float)1e-7) {
	cft = (float)1e-7;
    }
    qt = *slo * rad;
    a = sin(cff) / sin(cft);
    y = a * sin(qq) - sin(qt);
    x = cos(qt) - a * cos(qq);
    *ut = atan2(y, x);
    if (*ut < (float)0.) {
	*ut += tpi;
    }
    qqu = qq + *ut;
    qtu = qt + *ut;
    bp = sin(cff) * cos(qqu);
    bt = sin(cft) * cos(qtu);
    *ut /= rad;
    *ut /= (float)15.;
    if (bp < bt) {
	goto L10;
    }
    if (*ut < (float)12.) {
	*ut += (float)12.;
    }
    if (*ut > (float)12.) {
	*ut += (float)-12.;
    }
L10:
    return 0;
} /* mltut_ */



/* Subroutine */ int mfc_(sla, slo, r__, h__, d__, z__)
real *sla, *slo, *r__, *h__, *d__, *z__;
{
    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double sqrt(), atan2();

    /* Local variables */
    extern /* Subroutine */ int igrf_();
    static real f;
    static integer i__;
    static real x, y, bf, br, bt, rla, rlo;

/*  ********************************************************************* */
/*  Computation of the IGRF magnetic field components */
/*  Extracted as a subroutine from the earlier version of GEO-CGM.FOR */
/*  V. Papitashvili, February 1999 */
/*  ********************************************************************* */
/*  This takes care if SLA or CLA are dummy values (e.g., 999.99) */
    if (*sla >= (float)999.) {
	x = (float)99999.;
	y = (float)99999.;
	*z__ = (float)99999.;
	*h__ = (float)99999.;
	*d__ = (float)999.99;
	i__ = (float)999.99;
	f = (float)99999.;
	return 0;
    }
/*  Computation of all geomagnetic field components */
    rla = ((float)90. - *sla) * (float).017453293;
    rlo = *slo * (float).017453293;
    igrf_(&iyr_1.iyr, &nm_1.nm, r__, &rla, &rlo, &br, &bt, &bf);
    x = -bt;
    y = bf;
    *z__ = -br;
/* Computing 2nd power */
    r__1 = x;
/* Computing 2nd power */
    r__2 = y;
    *h__ = sqrt(r__1 * r__1 + r__2 * r__2);
    *d__ = atan2(y, x) * (float)57.2957751;
    i__ = atan2(*z__, *h__) * (float)57.2957751;
/* Computing 2nd power */
    r__1 = *h__;
/* Computing 2nd power */
    r__2 = *z__;
    f = sqrt(r__1 * r__1 + r__2 * r__2);
    return 0;
} /* mfc_ */



/* Subroutine */ int ftprnt_(rh, sla, slo, cla, clo, acla, aclo, slaf, slof, 
	rf)
real *rh, *sla, *slo, *cla, *clo, *acla, *aclo, *slaf, *slof, *rf;
{
    /* System generated locals */
    real r__1, r__2, r__3;

    /* Builtin functions */
    double sin(), sqrt(), asin();

    /* Local variables */
    static real dlaf, frac, acol;
    extern /* Subroutine */ int shag_();
    static real dlof, pmif, rsla, rslo, r__, ds, rl, xf, yf, zf, rr;
    extern /* Subroutine */ int corgeo_(), sphcar_();
    static real dr0, dr1, rf1, xf1, yf1, zf1, sn2, dr10, col;

/*  ********************************************************************* */
/*  Calculation of the magnetic field line footprint at the Earth's */
/*  (or any higher) surface. */
/*  Extracted as a subroutine from the earlier version of GEO-CGM.FOR by */
/*  V. Papitashvili in February 1999 but then the subroutine was revised */
/*  to obtain the Altitude Adjusted CGM coordinates. The AACGM approach */
/*  is proposed by Kile Baker of the JHU/APL, see their World Wide Web */
/*  site http://sd-www.jhuapl.edu/RADAR/AACGM/ for details. */
/*  If RF = 1-Re (i.e., at the Earth's surface), then the footprint */
/*  location is defined as the Altitude Adjusted (AA) CGM coordinates */
/*  for a given point (ACLA, ACLO). */

/*  If RF = 1.xx Re (i.e., at any altitude above or below the starting */
/*  point), then the conjunction between these two points can be found */
/*  along the field line. */
/*  ********************************************************************* */
/*  This takes care if SLA or CLA are dummy values (e.g., 999.99) */
    if (*sla > (float)999. || *cla > (float)999. || *rf == *rh) {
	*acla = (float)999.99;
	*aclo = (float)999.99;
	*slaf = (float)999.99;
	*slof = (float)999.99;
	return 0;
    }
/*  Defining the Altitude Adjusted CGM coordinates for a given point */
    col = ((float)90. - *cla) * (float).017453293;
/* Computing 2nd power */
    r__1 = sin(col);
    sn2 = r__1 * r__1;
    acol = asin(sqrt(sn2 * *rf / *rh));
    *acla = (float)90. - acol * (float)57.29577951;
    if (*cla < (float)0.) {
	*acla = -(*acla);
    }
    *aclo = *clo;
    corgeo_(slaf, slof, rf, &dlaf, &dlof, acla, aclo, &pmif);
    if (*slaf < (float)999.) {
	return 0;
    }
/*  Tracing the magnetic field line down to the Earth's surface at low */
/*  latitudes if CORGEO failed to calculate geocentric coordinates SLAF */
/*  and SLOF */
    if (sn2 < (float)1e-7) {
	sn2 = (float)1e-7;
    }
    rl = *rh / sn2;
    frac = (float).03 / ((float)3. / (rl - (float).6) + (float)1.);
/*  Checking direction of the magnetic field-line, so the step along */
/*  the field-line will go down, to the Earth surface */
    if (*cla >= (float)0.) {
	frac = -frac;
    }
    ds = *rh * frac;
L250:
/*  Start from an initial point */
    r__ = *rh;
    rsla = ((float)90. - *sla) * (float).0174533;
    rslo = *slo * (float).0174533;
    sphcar_(&r__, &rsla, &rslo, &xf, &yf, &zf, &c__1);
    rf1 = r__;
    xf1 = xf;
    yf1 = yf;
    zf1 = zf;
L255:
    shag_(&xf, &yf, &zf, &ds);
/* Computing 2nd power */
    r__1 = xf;
/* Computing 2nd power */
    r__2 = yf;
/* Computing 2nd power */
    r__3 = zf;
    rr = sqrt(r__1 * r__1 + r__2 * r__2 + r__3 * r__3);
    if (rr > *rh) {
	ds = -ds;
	xf = xf1;
	yf = yf1;
	zf = zf1;
	goto L250;
    }
    if (rr > *rf) {
	rf1 = rr;
	xf1 = xf;
	yf1 = yf;
	zf1 = zf;
	goto L255;
    } else {
	dr1 = (r__1 = rf1 - *rf, dabs(r__1));
	dr0 = (r__1 = *rf - rr, dabs(r__1));
	dr10 = dr1 + dr0;
	if (dr10 != (float)0.) {
	    ds *= dr1 / dr10;
	    shag_(&xf1, &yf1, &zf1, &ds);
	}
	sphcar_(&rr, slaf, slof, &xf1, &yf1, &zf1, &c_n1);
	*slaf = (float)90. - *slaf * (float)57.29578;
	*slof *= (float)57.29578;
    }
    return 0;
} /* ftprnt_ */



/* Subroutine */ int geolow_(slar, slor, rh, clar, clor, rbm, slac, sloc)
real *slar, *slor, *rh, *clar, *clor, *rbm, *slac, *sloc;
{
    /* System generated locals */
    integer i__1;
    real r__1, r__2, r__3;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(), sin();

    /* Local variables */
    static real frac;
    static integer jdel, ihem;
    extern /* Subroutine */ int shag_();
    static real dsla, rdel;
    extern /* Subroutine */ int igrf_();
    static integer nobm, ndir;
    static real slan, rlan, slas, xgeo, ygeo, zgeo, rlas;
    static integer i__, j;
    static real delat, delon, arlat[181], arlon[181], rnlat;
    static doublereal b2, b3;
    static real rslat, rnlon, rslon;
    static integer l1, l2;
    static real r1, x1, y1, z1, bc[2], bf, dd;
    static integer jc;
    static doublereal bm;
    static integer ih;
    static real br, delcla, bt, ds, rl, rm, delclo, rr, sz;
    extern /* Subroutine */ int geocor_(), sphcar_();
    static real bb2, bb3, dr0, dr1;
    static integer n999;
    static real daa, cla, dhh, dr10;
    static integer jcn;
    static real dsd;
    static integer jdn;
    static real clo, col, sla, doo;
    static integer jcs;
    static real rla;
    static integer jds;
    static real xbm, ybm, zbm, pmm, sll, slm, slo, rlo, rbm1, xbm1, ybm1, 
	    zbm1;

/*  ********************************************************************* */
/*  Calculates CGM coordinates from geocentric ones at low latitudes */
/*  where the DGRF/IGRF magnetic field lines may never cross the dipole */
/*  equatorial plane and, therefore, the definition of CGM coordinates */
/*  becomes invalid. */

/*  The code is written by Natalia and Vladimir Papitashvili as a part */
/*  of the earlier versions of GEO-CGM.FOR; extracted as a subroutine by */
/*  V. Papitashvili in February 1999. */

/*  Apr 11, 2001  GEOLOW is modified to account for interpolation of */
/*                CGM meridians near equator across the 360/0 boundary */

/*  See the paper by  Gustafsson, G., N. E. Papitashvili, and V. O. */
/*  Papitashvili, A revised corrected geomagnetic coordinate system for */
/*  Epochs 1985 and 1990 [J. Atmos. Terr. Phys., 54, 1609-1631, 1992] */
/*  for detailed description of the B-min approach utilized here. */
/*  ********************************************************************* */
/*  This takes care if SLA is a dummy value (e.g., 999.99) */
    if (*slar > (float)999.) {
	*clar = (float)999.99;
	*clor = (float)999.99;
	*slac = (float)999.99;
	*sloc = (float)999.99;
	*rbm = (float)999.99;
	return 0;
    }
/*  HH is an error (nT) to determine B-min along the magnetic field line */
    dhh = (float).5;
/*  Filling the work arrays of CGM latitudes and longitudes with 999.99 */
/*  Note that at certain geocentric longitudes in the very near-equator */
/*  region no "geomagnetic equator" can be defined at all. */
    for (j = 61; j <= 121; ++j) {
	arlat[j - 1] = (float)999.99;
	arlon[j - 1] = (float)999.99;
    }
    slo = *slor;
    ndir = 0;
/*  Finding the geomagnetic equator as a projection of the B-min point */
/*  found for the field lines started from the last latitude in each */
/*  hemisphere where the CGM coordinates were obtained from geocentric */
/*  ones (GEO --> CGM). First the CGM coordinates are calculated in the */
/*  Northern (NDIR=0) and then in the Southern hemispheres (NDIR=1) */
L53:
    if (ndir == 0) {
/*  Program works from 30 deg. latitude down to the geographic equator */
/*  in the Northern Hemisphere */
	for (jc = 61; jc <= 91; ++jc) {
	    sla = (float)90. - (jc - 1);
	    geocor_(&sla, &slo, rh, &daa, &doo, &cla, &clo, &pmm);
	    if (cla > (float)999.) {
		ndir = 1;
		goto L53;
	    }
	    arlat[jc - 1] = cla;
	    arlon[jc - 1] = clo;
	}
	ndir = 1;
	goto L53;
    } else {
/*  Program works from -30 deg. latitude down to the geographic equator */
/*  in the Southern Hemisphere */
	for (jc = 121; jc >= 92; --jc) {
	    sla = (float)90. - (jc - 1);
	    geocor_(&sla, &slo, rh, &daa, &doo, &cla, &clo, &pmm);
	    if (cla > (float)999.) {
		ndir = 0;
		goto L57;
	    }
	    arlat[jc - 1] = cla;
	    arlon[jc - 1] = clo;
	}
	ndir = 0;
    }
L57:
/*  Finding last geographic latitudes along SLO where CGM coordinates */
/*  can be calculated */
    n999 = 0;
    ndir = 0;
    for (jc = 61; jc <= 121; ++jc) {
	if (arlat[jc - 1] > (float)999.) {
	    if (ndir == 0) {
		jcn = jc - 1;
		rnlat = arlat[jcn - 1];
		rnlon = arlon[jcn - 1];
		ndir = 1;
		n999 = 1;
	    }
	}
	if (arlat[jc - 1] < (float)999.) {
	    if (ndir == 1) {
		jcs = jc;
		rslat = arlat[jc - 1];
		rslon = arlon[jc - 1];
		ndir = 0;
		goto L59;
	    }
	}
    }
L59:
/*  If there is no points with 999.99 found along the SLO meridian, */
/*  then the IHEM loop will start from 3; otherwise it starts from 1 */
    if (n999 == 0) {
	ih = 3;
	goto L31;
    } else {
	ih = 1;
    }
/*  Interpolation of the appropriate CGM longitudes between last */
/*  geocentric latitudes along SLO where CGM coordinates were defined */
/* (modified by Freddy Christiansen of DMI to account for interpolation */
/*  across the 360/0 boundary - April 11, 2001) */
    rdel = (real) (jcs - jcn);
    if (rdel == (float)0.) {
	delon = (float)0.;
    } else {
	if (rslon > (float)270. && rnlon < (float)90.) {
	    delon = (rslon - (rnlon + (float)360.)) / rdel;
	} else {
	    if (rslon < (float)90. && rnlon > (float)270.) {
		delon = (rslon - (rnlon - (float)360.)) / rdel;
	    } else {
		delon = (rslon - rnlon) / rdel;
	    }
	}
    }
    i__1 = jcs - 1;
    for (jc = jcn + 1; jc <= i__1; ++jc) {
	arlon[jc - 1] = rnlon + delon * (jc - jcn);
	if (arlon[jc - 1] < (float)0.) {
	    arlon[jc - 1] += (float)360.;
	}
    }
L31:
/*  Finding the CGM equator at SLO on the sphere with radius RH */
    nobm = 0;
    for (ihem = ih; ihem <= 3; ++ihem) {
	rm = *rh;
/*  Defining the real equator point from the Northern Hemisphere */
	if (ihem == 1) {
	    cla = rnlat;
	    sla = (float)90. - (jcn - (float)1.);
	    slan = sla;
	}
/*  Defining the real equator point from the Southern Hemisphere */
	if (ihem == 2) {
	    cla = rslat;
	    sla = (float)90. - (jcs - 1);
	    slas = sla;
	}
/*  Defining the apex of the current magnetic field line */
	if (ihem == 3) {
	    cla = (float)0.;
	    sla = *slar;
	}
/*  Here CLA is used only to calculate FRAC */
	col = ((float)90. - cla) * (float).017453293;
	slm = ((float)90. - sla) * (float).017453293;
	sll = slo * (float).017453293;
	igrf_(&iyr_1.iyr, &nm_1.nm, &rm, &slm, &sll, &br, &bt, &bf);
	sz = -br;
	sphcar_(&rm, &slm, &sll, &xgeo, &ygeo, &zgeo, &c__1);
	bm = sqrt(br * br + bt * bt + bf * bf);
	xbm = xgeo;
	ybm = ygeo;
	zbm = zgeo;
/* Computing 2nd power */
	r__1 = sin(col);
	rl = (float)1. / (r__1 * r__1);
	frac = (float).03 / ((float)3. / (rl - (float).6) + (float)1.);
	if (sz <= (float)0.) {
	    frac = -frac;
	}
	dsd = rl * frac;
	ds = dsd;
L5:
/*  Keep two consequently computed points to define B-min */
	for (i__ = 1; i__ <= 2; ++i__) {
	    dd = ds;
	    shag_(&xgeo, &ygeo, &zgeo, &dd);
/* L11: */
	    if (i__ != 1) {
		goto L9;
	    }
	    xbm1 = xgeo;
	    ybm1 = ygeo;
	    zbm1 = zgeo;
/* Computing 2nd power */
	    r__1 = xbm1;
/* Computing 2nd power */
	    r__2 = ybm1;
/* Computing 2nd power */
	    r__3 = zbm1;
	    rbm1 = sqrt(r__1 * r__1 + r__2 * r__2 + r__3 * r__3);
L9:
	    sphcar_(&rm, &slm, &sll, &xgeo, &ygeo, &zgeo, &c_n1);
	    igrf_(&iyr_1.iyr, &nm_1.nm, &rm, &slm, &sll, &br, &bt, &bf);
/*  Go and compute the conjugate point if no B-min was found at this */
/*  magnetic field line (could happen at very near geomagnetic equator) */
	    if (rm < *rh) {
		nobm = 1;
		goto L77;
	    }
	    bc[i__ - 1] = sqrt(br * br + bt * bt + bf * bf);
/* L7: */
	}
	b2 = bc[0];
	b3 = bc[1];
	if (bm > b2 && b2 < b3) {
	    goto L15;
	}
	if (bm >= b2 && b2 < b3) {
	    goto L17;
	}
	if (bm > b2 && b2 <= b3) {
	    goto L17;
	}
	bm = bc[0];
	xgeo = xbm1;
	ygeo = ybm1;
	zgeo = zbm1;
	xbm = xbm1;
	ybm = ybm1;
	zbm = zbm1;
	goto L5;
L15:
	bb3 = (d__1 = b3 - b2, abs(d__1));
	bb2 = (d__1 = bm - b2, abs(d__1));
	if (bb2 < dhh && bb3 < dhh) {
	    goto L21;
	}
L17:
	bm = bm;
	xgeo = xbm;
	ygeo = ybm;
	zgeo = zbm;
	ds /= (float)2.;
	goto L5;
L21:
	sphcar_(&rbm1, &rla, &rlo, &xbm1, &ybm1, &zbm1, &c_n1);
	rla = (float)90. - rla * (float)57.2957751;
	rlo *= (float)57.2957751;
	if (ihem == 1) {
	    rlan = rla;
	}
	if (ihem == 2) {
	    rlas = rla;
	}
/*  Computation of the magnetically conjugate point at low latitudes */
/* L54: */
	if (ihem == 3) {
	    *rbm = rbm1;
	    rm = *rbm;
	    ds = dsd;
L55:
	    shag_(&xbm1, &ybm1, &zbm1, &ds);
/* Computing 2nd power */
	    r__1 = xbm1;
/* Computing 2nd power */
	    r__2 = ybm1;
/* Computing 2nd power */
	    r__3 = zbm1;
	    rr = sqrt(r__1 * r__1 + r__2 * r__2 + r__3 * r__3);
	    if (rr > *rh) {
		r1 = rr;
		x1 = xbm1;
		y1 = ybm1;
		z1 = zbm1;
		goto L55;
	    } else {
		dr1 = (r__1 = *rh - r1, dabs(r__1));
		dr0 = (r__1 = *rh - rr, dabs(r__1));
		dr10 = dr1 + dr0;
		if (dr10 != (float)0.) {
		    ds *= dr1 / dr10;
		    rm = r1;
		    shag_(&x1, &y1, &z1, &ds);
		}
		sphcar_(&rr, slac, sloc, &x1, &y1, &z1, &c_n1);
		*slac = (float)90. - *slac * (float)57.2957751;
		*sloc *= (float)57.2957751;
	    }
	}
/*  End of loop IHEM */
L77:
	;
    }
    if (n999 == 0) {
	goto L91;
    }
    if (nobm == 1) {
/*  Interpolation of CGM latitudes if there is no B-min at this */
/*  magnetic field line */
	rdel = (real) (jcs - jcn);
	if (rdel == (float)0.) {
	    delat = (float)0.;
	} else {
	    delat = (rslat - rnlat) / rdel;
	}
	jdel = 0;
	i__1 = jcs - 1;
	for (jc = jcn + 1; jc <= i__1; ++jc) {
	    ++jdel;
	    arlat[jc - 1] = rnlat + delat * jdel;
	}
	*rbm = (float)999.99;
	*slac = (float)999.99;
	*sloc = (float)999.99;
    } else {
/*  Geocentric latitude of the CGM equator */
	rla = (rlan + rlas) / (float)2.;
/*  Interpolation of the CGM latitudes in the Northern hemisphere */
	rdel = slan - rla;
	if (rdel == (float)0.) {
	    delat = (float)0.;
	} else {
	    delat = rnlat / rdel;
	}
	jdn = dabs(rdel);
	jdel = 0;
	i__1 = jcn + jdn;
	for (jc = jcn + 1; jc <= i__1; ++jc) {
	    ++jdel;
	    arlat[jc - 1] = rnlat - delat * jdel;
	}
/*  Interpolation of the CGM latitudes in the Southern hemisphere */
	rdel = slas - rla;
	if (rdel == (float)0.) {
	    delat = (float)0.;
	} else {
	    delat = rslat / rdel;
	}
	jds = dabs(rdel);
	jdel = 0;
	i__1 = jcs - jds;
	for (jc = jcs - 1; jc >= i__1; --jc) {
	    ++jdel;
	    arlat[jc - 1] = rslat + delat * jdel;
	}
    }
L91:
/*  Defining by interpolation the exact values of the CGM latitude */
/*  and longitude between two adjacent values */
    l1 = (float)90. - *slar + (float)1.;
    if (*slar < (float)0.) {
	l2 = l1 - 1;
    } else {
	l2 = l1 + 1;
    }
    dsla = (r__1 = *slar - (integer) (*slar), dabs(r__1));
    delcla = arlat[l2 - 1] - arlat[l1 - 1];
    delclo = arlon[l2 - 1] - arlon[l1 - 1];
    *clar = arlat[l1 - 1] + delcla * dsla;
    *clor = arlon[l1 - 1] + delclo * dsla;
    return 0;
} /* geolow_ */



/* Subroutine */ int corgeo_(sla, slo, rh, dla, dlo, cla, clo, pmi)
real *sla, *slo, *rh, *dla, *dlo, *cla, *clo, *pmi;
{
    /* Format strings */
    static char fmt_2[] = "(/\002WARNING - No calculations within +/-0.1 deg\
ree near CGM equator\002)";
    static char fmt_22[] = "(/\002WARNING - Selected CGM_Lat.=\002,f6.2,\002\
 is too close to geomagnetic\002/\002          equator where CGM coordinates\
 are not defined\002)";

    /* System generated locals */
    real r__1, r__2, r__3;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe();
    double sin(), sqrt(), atan();
    integer do_fio();

    /* Local variables */
    static real frac, scla;
    extern /* Subroutine */ int shag_();
    static real clas, slac, gxla, clos, sloc, gtet, r__, x, y, z__, r0, r1, 
	    x1, y1, z1;
    static integer jc, ng;
    static real pf, ds, th, rl;
    extern /* Subroutine */ int geomag_();
    static real rm, sn, xm, ym, zm;
    extern /* Subroutine */ int geocor_(), sphcar_(), geolow_();
    static real dr0, dr1, sn2, aa10, saa, dr10, col, rfi, gth, dls, saq, rbm, 
	    rlo, pms;

    /* Fortran I/O blocks */
    static cilist io___397 = { 0, 7, 0, fmt_2, 0 };
    static cilist io___439 = { 0, 7, 0, fmt_22, 0 };


/*  ********************************************************************* */
/*  Calculates geocentric coordinates from corrected geomagnetic ones. */
/*  The code is written by Vladimir Popov and Vladimir Papitashvili */
/*  in mid-1980s; revised by V. Papitashvili in February 1999 */
/*  ********************************************************************* */
/*  This takes care if CLA is a dummy value (e.g., 999.99) */
    jc = 0;
    if (dabs(*cla) < (float).1) {
	s_wsfe(&io___397);
	e_wsfe();
	jc = 1;
    }
    if (*cla > (float)999. || jc == 1) {
	*sla = (float)999.99;
	*slo = (float)999.99;
	*dla = (float)999.99;
	*dlo = (float)999.99;
	*pmi = (float)999.99;
	return 0;
    }
    ng = nm_1.nm;
    col = (float)90. - *cla;
    r__ = (float)10.;
    r1 = r__;
    r0 = r__;
    col *= (float).017453293;
    rlo = *clo * (float).017453293;
    sn = sin(col);
    sn2 = sn * sn;
/*  The CGM latitude should be at least 0.01 deg. away of the CGM pole */
    if (sn2 < (float)3e-9) {
	sn2 = (float)3e-9;
    }
/*      RFI = 1./SN2 */
    rfi = *rh / sn2;
    *pmi = rfi;
    if (*pmi > (float)99.999) {
	*pmi = (float)999.99;
    }
    aa10 = r__ / rfi;
/*  RFI = R if COL = 90 deg. */
    if (rfi <= r__) {
	goto L1;
    }
    saa = aa10 / ((float)1. - aa10);
    saq = sqrt(saa);
    scla = atan(saq);
    if (*cla < (float)0.) {
	scla = (float)3.14159265359 - scla;
    }
    goto L3;
L1:
    scla = (float)1.57079632679;
    r0 = rfi;
L3:
    sphcar_(&r0, &scla, &rlo, &xm, &ym, &zm, &c__1);
    geomag_(&x, &y, &z__, &xm, &ym, &zm, &c_n1, &iyr_1.iyr);
    rl = r0;
    frac = (float)-.03 / ((float)3. / (rl - (float).6) + (float)1.);
    if (*cla < (float)0.) {
	frac = -frac;
    }
    r__ = r0;
L5:
    ds = r__ * frac;
    nm_1.nm = (float)9. / r__ + (float)1. + (float).5;
    shag_(&x, &y, &z__, &ds);
/* Computing 2nd power */
    r__1 = x;
/* Computing 2nd power */
    r__2 = y;
/* Computing 2nd power */
    r__3 = z__;
    r__ = sqrt(r__1 * r__1 + r__2 * r__2 + r__3 * r__3);
    if (r__ <= *rh) {
	goto L7;
    }
    r1 = r__;
    x1 = x;
    y1 = y;
    z1 = z__;
    goto L5;
/*  Define intersection with the start surface */
L7:
    dr1 = (r__1 = *rh - r1, dabs(r__1));
    dr0 = (r__1 = *rh - r__, dabs(r__1));
    dr10 = dr1 + dr0;
    if (dr10 != (float)0.) {
	ds *= dr1 / dr10;
	shag_(&x1, &y1, &z1, &ds);
    }
    sphcar_(&r__, &gtet, &gxla, &x1, &y1, &z1, &c_n1);
    gth = gtet * (float)57.2957751;
    *slo = gxla * (float)57.2957751;
    *sla = (float)90. - gth;
    geomag_(&x1, &y1, &z1, &xm, &ym, &zm, &c__1, &iyr_1.iyr);
    sphcar_(&rm, &th, &pf, &xm, &ym, &zm, &c_n1);
    *dlo = pf * (float)57.2957751;
    *dla = (float)90. - th * (float)57.2957751;
    nm_1.nm = ng;
/*  Because CORGEO cannot check if the CGM --> GEO transformation is */
/*  performed correctly in the equatorial area (that is, where the IGRF */
/*  field line may never cross the dipole equatorial plane). Therefore, */
/*  the backward check is required for geocentric latitudes lower than */
/*  30 degrees (see the paper referenced in GEOLOW) */
    if (dabs(*sla) < (float)30. || dabs(*cla) < (float)30.) {
	geocor_(sla, slo, rh, &dls, &dls, &clas, &clos, &pms);
	if (clas > (float)999.) {
	    geolow_(sla, slo, rh, &clas, &clos, &rbm, &slac, &sloc);
	}
	if ((r__1 = dabs(*cla) - dabs(clas), dabs(r__1)) >= (float)1.) {
	    s_wsfe(&io___439);
	    do_fio(&c__1, (char *)&(*cla), (ftnlen)sizeof(real));
	    e_wsfe();
	    *sla = (float)999.99;
	    *slo = (float)999.99;
	    *pmi = (float)999.99;
	}
    }
    return 0;
} /* corgeo_ */



/* Subroutine */ int geocor_(sla, slo, rh, dla, dlo, cla, clo, pmi)
real *sla, *slo, *rh, *dla, *dlo, *cla, *clo, *pmi;
{
    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double sin(), sqrt(), atan();

    /* Local variables */
    static real frac;
    extern /* Subroutine */ int shag_();
    static real gxla, ssla, gtet, c__, r__, s, x, y, z__, r1, x1, y1, z1;
    static integer ng;
    static real pf, ds, th, rl;
    extern /* Subroutine */ int geomag_();
    static real rm, sn, xm, ym, zm, st;
    extern /* Subroutine */ int sphcar_();
    static real dcl, dco, hhh, col, rrh, rlo, rzm, szm;

/*  ********************************************************************* */
/*  Calculates corrected geomagnetic coordinates from geocentric ones */
/*  The code is written by Vladimir Popov and Vladimir Papitashvili */
/*  in mid-1980s; revised by V. Papitashvili in February 1999 */
/*  ********************************************************************* */
/*  This takes care if SLA is a dummy value (e.g., 999.99) */
    if (*sla > (float)999.) {
	*cla = (float)999.99;
	*clo = (float)999.99;
	*dla = (float)999.99;
	*dlo = (float)999.99;
	*pmi = (float)999.99;
	return 0;
    }
    ng = nm_1.nm;
    col = (float)90. - *sla;
    r__ = *rh;
    r1 = r__;
    col *= (float).017453293;
    rlo = *slo * (float).017453293;
    sphcar_(&r__, &col, &rlo, &x, &y, &z__, &c__1);
    geomag_(&x, &y, &z__, &xm, &ym, &zm, &c__1, &iyr_1.iyr);
    sphcar_(&rm, &th, &pf, &xm, &ym, &zm, &c_n1);
    szm = zm;
    *dlo = pf * (float)57.2957751;
    dco = th * (float)57.2957751;
    *dla = (float)90. - dco;
/* Computing 2nd power */
    r__1 = sin(th);
    rl = r__ / (r__1 * r__1);
    frac = (float).03 / ((float)3. / (rl - (float).6) + (float)1.);
    if (szm < (float)0.) {
	frac = -frac;
    }
/*  Error to determine the dipole equtorial plane: aprox. 0.5 arc min */
    hhh = (float)1.571e-4;
/*  Trace the IGRF magnetic field line to the dipole equatorial plane */
L1:
    ds = r__ * frac;
L3:
    nm_1.nm = (float)9. / r__ + (float)1. + (float).5;
    r1 = r__;
    x1 = x;
    y1 = y;
    z1 = z__;
    shag_(&x, &y, &z__, &ds);
    geomag_(&x, &y, &z__, &xm, &ym, &zm, &c__1, &iyr_1.iyr);
    sphcar_(&r__, &c__, &s, &xm, &ym, &zm, &c_n1);
/*  As tracing goes above (RH+10_Re), use the dipole field line */
    if (r__ > *rh + (float)10.) {
	goto L9;
    }
/*  If the field line returns to the start surface without crossing the */
/*  dipole equatorial plane, no CGM coordinates can be calculated */
    if (r__ <= *rh) {
	goto L11;
    }
    dcl = c__ - (float)1.5707963268;
    if (dabs(dcl) <= hhh) {
	goto L9;
    }
    rzm = zm;
    if (szm > (float)0. && rzm > (float)0.) {
	goto L1;
    }
    if (szm < (float)0. && rzm < (float)0.) {
	goto L1;
    }
    r__ = r1;
    x = x1;
    y = y1;
    z__ = z1;
    ds /= (float)2.;
    goto L3;
L9:
    geomag_(&x, &y, &z__, &xm, &ym, &zm, &c__1, &iyr_1.iyr);
    sphcar_(&r__, &gtet, &gxla, &xm, &ym, &zm, &c_n1);
    st = (r__1 = sin(gtet), dabs(r__1));
/* Computing 2nd power */
    r__2 = st;
    rrh = (r__1 = *rh / (r__ - *rh * (r__2 * r__2)), dabs(r__1));
    *cla = (float)1.5707963 - atan(st * sqrt(rrh));
    *cla *= (float)57.2957751;
    *clo = gxla * (float)57.2957751;
    if (szm < (float)0.) {
	*cla = -(*cla);
    }
    ssla = (float)90. - *cla;
    ssla *= (float).017453293;
    sn = sin(ssla);
/*       PMI = 1/(SN*SN) */
    *pmi = *rh / (sn * sn);
    goto L13;
L11:
    *cla = (float)999.99;
    *clo = (float)999.99;
    *pmi = (float)999.99;
L13:
    nm_1.nm = ng;
    return 0;
} /* geocor_ */



/* Subroutine */ int shag_(x, y, z__, ds)
real *x, *y, *z__, *ds;
{
    /* System generated locals */
    real r__1, r__2, r__3;

    /* Local variables */
    extern /* Subroutine */ int right_();
    static real r11, r12, r13, r21, r22, r23, r31, r32, r33, r41, r42, r43, 
	    r51, r52, r53;

/*  ********************************************************************* */
/*  Similar to SUBR STEP from GEOPACK-1996 but SHAG takes into account */
/*  only internal sources */
/*  The code is re-written from Tsyganenko's subroutine STEP by */
/*  Natalia and Vladimir Papitashvili in mid-1980s */
/*  ********************************************************************* */
    a5_1.ds3 = -(*ds) / (float)3.;
    right_(x, y, z__, &r11, &r12, &r13);
    r__1 = *x + r11;
    r__2 = *y + r12;
    r__3 = *z__ + r13;
    right_(&r__1, &r__2, &r__3, &r21, &r22, &r23);
    r__1 = *x + (r11 + r21) * (float).5;
    r__2 = *y + (r12 + r22) * (float).5;
    r__3 = *z__ + (r13 + r23) * (float).5;
    right_(&r__1, &r__2, &r__3, &r31, &r32, &r33);
    r__1 = *x + (r11 + r31 * (float)3.) * (float).375;
    r__2 = *y + (r12 + r32 * (float)3.) * (float).375;
    r__3 = *z__ + (r13 + r33 * (float)3.) * (float).375;
    right_(&r__1, &r__2, &r__3, &r41, &r42, &r43);
    r__1 = *x + (r11 - r31 * (float)3. + r41 * (float)4.) * (float)1.5;
    r__2 = *y + (r12 - r32 * (float)3. + r42 * (float)4.) * (float)1.5;
    r__3 = *z__ + (r13 - r33 * (float)3. + r43 * (float)4.) * (float)1.5;
    right_(&r__1, &r__2, &r__3, &r51, &r52, &r53);
    *x += (r11 + r41 * (float)4. + r51) * (float).5;
    *y += (r12 + r42 * (float)4. + r52) * (float).5;
    *z__ += (r13 + r43 * (float)4. + r53) * (float).5;
    return 0;
} /* shag_ */



/* Subroutine */ int right_(x, y, z__, r1, r2, r3)
real *x, *y, *z__, *r1, *r2, *r3;
{
    /* System generated locals */
    real r__1, r__2, r__3;

    /* Builtin functions */
    double sqrt();

    /* Local variables */
    extern /* Subroutine */ int igrf_();
    static real b, f, r__, t, bf, br, bt, bx, by, bz;
    extern /* Subroutine */ int bspcar_(), sphcar_();

/*  ********************************************************************* */
/*  Similar to SUBR RHAND from GEOPACK-1996 but RIGHT takes into account */
/*  only internal sources */
/*  The code is re-written from Tsyganenko's subroutine RHAND */
/*  by Natalia and Vladimir Papitashvili in mid-1980s */
/*  ********************************************************************* */
    sphcar_(&r__, &t, &f, x, y, z__, &c_n1);
    igrf_(&iyr_1.iyr, &nm_1.nm, &r__, &t, &f, &br, &bt, &bf);
    bspcar_(&t, &f, &br, &bt, &bf, &bx, &by, &bz);
/* Computing 2nd power */
    r__1 = bx;
/* Computing 2nd power */
    r__2 = by;
/* Computing 2nd power */
    r__3 = bz;
    b = a5_1.ds3 / sqrt(r__1 * r__1 + r__2 * r__2 + r__3 * r__3);
    *r1 = bx * b;
    *r2 = by * b;
    *r3 = bz * b;
    return 0;
} /* right_ */



/* Subroutine */ int igrf_(iy, nm, r__, t, f, br, bt, bf)
integer *iy, *nm;
real *r__, *t, *f, *br, *bt, *bf;
{
    /* Initialized data */

    static real g1900[66] = { (float)0.,(float)-31543.,(float)-2298.,(float)
	    -677.,(float)2905.,(float)924.,(float)1022.,(float)-1469.,(float)
	    1256.,(float)572.,(float)876.,(float)628.,(float)660.,(float)
	    -361.,(float)134.,(float)-184.,(float)328.,(float)264.,(float)5.,(
	    float)-86.,(float)-16.,(float)63.,(float)61.,(float)-11.,(float)
	    -217.,(float)-58.,(float)59.,(float)-90.,(float)70.,(float)-55.,(
	    float)0.,(float)34.,(float)-41.,(float)-21.,(float)18.,(float)6.,(
	    float)11.,(float)8.,(float)-4.,(float)-9.,(float)1.,(float)2.,(
	    float)-9.,(float)5.,(float)8.,(float)8.,(float)10.,(float)1.,(
	    float)-11.,(float)12.,(float)1.,(float)-2.,(float)2.,(float)-1.,(
	    float)-1.,(float)-3.,(float)-4.,(float)2.,(float)-5.,(float)-2.,(
	    float)6.,(float)4.,(float)0.,(float)2.,(float)2.,(float)0. };
    static real h1900[66] = { (float)0.,(float)0.,(float)5922.,(float)0.,(
	    float)-1061.,(float)1121.,(float)0.,(float)-330.,(float)3.,(float)
	    523.,(float)0.,(float)195.,(float)-69.,(float)-210.,(float)-75.,(
	    float)0.,(float)-210.,(float)53.,(float)-33.,(float)-124.,(float)
	    3.,(float)0.,(float)-9.,(float)83.,(float)2.,(float)-35.,(float)
	    36.,(float)-69.,(float)0.,(float)-45.,(float)-13.,(float)-10.,(
	    float)-1.,(float)28.,(float)-12.,(float)-22.,(float)0.,(float)8.,(
	    float)-14.,(float)7.,(float)-13.,(float)5.,(float)16.,(float)-5.,(
	    float)-18.,(float)0.,(float)-20.,(float)14.,(float)5.,(float)-3.,(
	    float)-2.,(float)8.,(float)10.,(float)-2.,(float)2.,(float)0.,(
	    float)2.,(float)1.,(float)2.,(float)6.,(float)-4.,(float)0.,(
	    float)-2.,(float)4.,(float)0.,(float)-6. };
    static real g1905[66] = { (float)0.,(float)-31464.,(float)-2298.,(float)
	    -728.,(float)2928.,(float)1041.,(float)1037.,(float)-1494.,(float)
	    1239.,(float)635.,(float)880.,(float)643.,(float)653.,(float)
	    -380.,(float)146.,(float)-192.,(float)328.,(float)259.,(float)-1.,
	    (float)-93.,(float)-26.,(float)62.,(float)60.,(float)-11.,(float)
	    -221.,(float)-57.,(float)57.,(float)-92.,(float)70.,(float)-54.,(
	    float)0.,(float)33.,(float)-41.,(float)-20.,(float)18.,(float)6.,(
	    float)11.,(float)8.,(float)-4.,(float)-9.,(float)1.,(float)2.,(
	    float)-8.,(float)5.,(float)8.,(float)8.,(float)10.,(float)1.,(
	    float)-11.,(float)12.,(float)1.,(float)-2.,(float)2.,(float)0.,(
	    float)-1.,(float)-3.,(float)-4.,(float)2.,(float)-5.,(float)-2.,(
	    float)6.,(float)4.,(float)0.,(float)2.,(float)2.,(float)0. };
    static real h1905[66] = { (float)0.,(float)0.,(float)5909.,(float)0.,(
	    float)-1086.,(float)1065.,(float)0.,(float)-357.,(float)34.,(
	    float)480.,(float)0.,(float)203.,(float)-77.,(float)-201.,(float)
	    -65.,(float)0.,(float)-193.,(float)56.,(float)-32.,(float)-125.,(
	    float)11.,(float)0.,(float)-7.,(float)86.,(float)4.,(float)-32.,(
	    float)32.,(float)-67.,(float)0.,(float)-46.,(float)-14.,(float)
	    -11.,(float)0.,(float)28.,(float)-12.,(float)-22.,(float)0.,(
	    float)8.,(float)-15.,(float)7.,(float)-13.,(float)5.,(float)16.,(
	    float)-5.,(float)-18.,(float)0.,(float)-20.,(float)14.,(float)5.,(
	    float)-3.,(float)-2.,(float)8.,(float)10.,(float)-2.,(float)2.,(
	    float)0.,(float)2.,(float)1.,(float)2.,(float)6.,(float)-4.,(
	    float)0.,(float)-2.,(float)4.,(float)0.,(float)-6. };
    static real g1910[66] = { (float)0.,(float)-31354.,(float)-2297.,(float)
	    -769.,(float)2948.,(float)1176.,(float)1058.,(float)-1524.,(float)
	    1223.,(float)705.,(float)884.,(float)660.,(float)644.,(float)
	    -400.,(float)160.,(float)-201.,(float)327.,(float)253.,(float)-9.,
	    (float)-102.,(float)-38.,(float)62.,(float)58.,(float)-11.,(float)
	    -224.,(float)-54.,(float)54.,(float)-95.,(float)71.,(float)-54.,(
	    float)1.,(float)32.,(float)-40.,(float)-19.,(float)18.,(float)6.,(
	    float)11.,(float)8.,(float)-4.,(float)-9.,(float)1.,(float)2.,(
	    float)-8.,(float)5.,(float)8.,(float)8.,(float)10.,(float)1.,(
	    float)-11.,(float)12.,(float)1.,(float)-2.,(float)2.,(float)0.,(
	    float)-1.,(float)-3.,(float)-4.,(float)2.,(float)-5.,(float)-2.,(
	    float)6.,(float)4.,(float)0.,(float)2.,(float)2.,(float)0. };
    static real h1910[66] = { (float)0.,(float)0.,(float)5898.,(float)0.,(
	    float)-1128.,(float)1e3,(float)0.,(float)-389.,(float)62.,(float)
	    425.,(float)0.,(float)211.,(float)-90.,(float)-189.,(float)-55.,(
	    float)0.,(float)-172.,(float)57.,(float)-33.,(float)-126.,(float)
	    21.,(float)0.,(float)-5.,(float)89.,(float)5.,(float)-29.,(float)
	    28.,(float)-65.,(float)0.,(float)-47.,(float)-14.,(float)-12.,(
	    float)1.,(float)28.,(float)-13.,(float)-22.,(float)0.,(float)8.,(
	    float)-15.,(float)6.,(float)-13.,(float)5.,(float)16.,(float)-5.,(
	    float)-18.,(float)0.,(float)-20.,(float)14.,(float)5.,(float)-3.,(
	    float)-2.,(float)8.,(float)10.,(float)-2.,(float)2.,(float)0.,(
	    float)2.,(float)1.,(float)2.,(float)6.,(float)-4.,(float)0.,(
	    float)-2.,(float)4.,(float)0.,(float)-6. };
    static real g1915[66] = { (float)0.,(float)-31212.,(float)-2306.,(float)
	    -802.,(float)2956.,(float)1309.,(float)1084.,(float)-1559.,(float)
	    1212.,(float)778.,(float)887.,(float)678.,(float)631.,(float)
	    -416.,(float)178.,(float)-211.,(float)327.,(float)245.,(float)
	    -16.,(float)-111.,(float)-51.,(float)61.,(float)57.,(float)-10.,(
	    float)-228.,(float)-51.,(float)49.,(float)-98.,(float)72.,(float)
	    -54.,(float)2.,(float)31.,(float)-38.,(float)-18.,(float)19.,(
	    float)6.,(float)11.,(float)8.,(float)-4.,(float)-9.,(float)2.,(
	    float)3.,(float)-8.,(float)6.,(float)8.,(float)8.,(float)10.,(
	    float)1.,(float)-11.,(float)12.,(float)1.,(float)-2.,(float)2.,(
	    float)0.,(float)-1.,(float)-3.,(float)-4.,(float)2.,(float)-5.,(
	    float)-2.,(float)6.,(float)4.,(float)0.,(float)1.,(float)2.,(
	    float)0. };
    static real h1915[66] = { (float)0.,(float)0.,(float)5875.,(float)0.,(
	    float)-1191.,(float)917.,(float)0.,(float)-421.,(float)84.,(float)
	    360.,(float)0.,(float)218.,(float)-109.,(float)-173.,(float)-51.,(
	    float)0.,(float)-148.,(float)58.,(float)-34.,(float)-126.,(float)
	    32.,(float)0.,(float)-2.,(float)93.,(float)8.,(float)-26.,(float)
	    23.,(float)-62.,(float)0.,(float)-48.,(float)-14.,(float)-12.,(
	    float)2.,(float)28.,(float)-15.,(float)-22.,(float)0.,(float)8.,(
	    float)-15.,(float)6.,(float)-13.,(float)5.,(float)16.,(float)-5.,(
	    float)-18.,(float)0.,(float)-20.,(float)14.,(float)5.,(float)-3.,(
	    float)-2.,(float)8.,(float)10.,(float)-2.,(float)2.,(float)0.,(
	    float)2.,(float)1.,(float)2.,(float)6.,(float)-4.,(float)0.,(
	    float)-2.,(float)4.,(float)0.,(float)-6. };
    static real g1920[66] = { (float)0.,(float)-31060.,(float)-2317.,(float)
	    -839.,(float)2959.,(float)1407.,(float)1111.,(float)-1600.,(float)
	    1205.,(float)839.,(float)889.,(float)695.,(float)616.,(float)
	    -424.,(float)199.,(float)-221.,(float)326.,(float)236.,(float)
	    -23.,(float)-119.,(float)-62.,(float)61.,(float)55.,(float)-10.,(
	    float)-233.,(float)-46.,(float)44.,(float)-101.,(float)73.,(float)
	    -54.,(float)2.,(float)29.,(float)-37.,(float)-16.,(float)19.,(
	    float)6.,(float)11.,(float)7.,(float)-3.,(float)-9.,(float)2.,(
	    float)4.,(float)-7.,(float)6.,(float)8.,(float)8.,(float)10.,(
	    float)1.,(float)-11.,(float)12.,(float)1.,(float)-2.,(float)2.,(
	    float)0.,(float)-1.,(float)-3.,(float)-4.,(float)2.,(float)-5.,(
	    float)-2.,(float)6.,(float)4.,(float)0.,(float)1.,(float)3.,(
	    float)0. };
    static real h1920[66] = { (float)0.,(float)0.,(float)5845.,(float)0.,(
	    float)-1259.,(float)823.,(float)0.,(float)-445.,(float)103.,(
	    float)293.,(float)0.,(float)220.,(float)-134.,(float)-153.,(float)
	    -57.,(float)0.,(float)-122.,(float)58.,(float)-38.,(float)-125.,(
	    float)43.,(float)0.,(float)0.,(float)96.,(float)11.,(float)-22.,(
	    float)18.,(float)-57.,(float)0.,(float)-49.,(float)-14.,(float)
	    -13.,(float)4.,(float)28.,(float)-16.,(float)-22.,(float)0.,(
	    float)8.,(float)-15.,(float)6.,(float)-14.,(float)5.,(float)17.,(
	    float)-5.,(float)-19.,(float)0.,(float)-20.,(float)14.,(float)5.,(
	    float)-3.,(float)-2.,(float)9.,(float)10.,(float)-2.,(float)2.,(
	    float)0.,(float)2.,(float)1.,(float)2.,(float)6.,(float)-4.,(
	    float)0.,(float)-2.,(float)4.,(float)0.,(float)-6. };
    static real g1925[66] = { (float)0.,(float)-30926.,(float)-2318.,(float)
	    -893.,(float)2969.,(float)1471.,(float)1140.,(float)-1645.,(float)
	    1202.,(float)881.,(float)891.,(float)711.,(float)601.,(float)
	    -426.,(float)217.,(float)-230.,(float)326.,(float)226.,(float)
	    -28.,(float)-125.,(float)-69.,(float)61.,(float)54.,(float)-9.,(
	    float)-238.,(float)-40.,(float)39.,(float)-103.,(float)73.,(float)
	    -54.,(float)3.,(float)27.,(float)-35.,(float)-14.,(float)19.,(
	    float)6.,(float)11.,(float)7.,(float)-3.,(float)-9.,(float)2.,(
	    float)4.,(float)-7.,(float)7.,(float)8.,(float)8.,(float)10.,(
	    float)1.,(float)-11.,(float)12.,(float)1.,(float)-2.,(float)2.,(
	    float)0.,(float)-1.,(float)-3.,(float)-4.,(float)2.,(float)-5.,(
	    float)-2.,(float)6.,(float)4.,(float)0.,(float)1.,(float)3.,(
	    float)0. };
    static real h1925[66] = { (float)0.,(float)0.,(float)5817.,(float)0.,(
	    float)-1334.,(float)728.,(float)0.,(float)-462.,(float)119.,(
	    float)229.,(float)0.,(float)216.,(float)-163.,(float)-130.,(float)
	    -70.,(float)0.,(float)-96.,(float)58.,(float)-44.,(float)-122.,(
	    float)51.,(float)0.,(float)3.,(float)99.,(float)14.,(float)-18.,(
	    float)13.,(float)-52.,(float)0.,(float)-50.,(float)-14.,(float)
	    -14.,(float)5.,(float)29.,(float)-17.,(float)-21.,(float)0.,(
	    float)8.,(float)-15.,(float)6.,(float)-14.,(float)5.,(float)17.,(
	    float)-5.,(float)-19.,(float)0.,(float)-20.,(float)14.,(float)5.,(
	    float)-3.,(float)-2.,(float)9.,(float)10.,(float)-2.,(float)2.,(
	    float)0.,(float)2.,(float)1.,(float)2.,(float)6.,(float)-4.,(
	    float)0.,(float)-2.,(float)4.,(float)0.,(float)-6. };
    static real g1930[66] = { (float)0.,(float)-30805.,(float)-2316.,(float)
	    -951.,(float)2980.,(float)1517.,(float)1172.,(float)-1692.,(float)
	    1205.,(float)907.,(float)896.,(float)727.,(float)584.,(float)
	    -422.,(float)234.,(float)-237.,(float)327.,(float)218.,(float)
	    -32.,(float)-131.,(float)-74.,(float)60.,(float)53.,(float)-9.,(
	    float)-242.,(float)-32.,(float)32.,(float)-104.,(float)74.,(float)
	    -54.,(float)4.,(float)25.,(float)-34.,(float)-12.,(float)18.,(
	    float)6.,(float)11.,(float)7.,(float)-3.,(float)-9.,(float)2.,(
	    float)5.,(float)-6.,(float)8.,(float)8.,(float)8.,(float)10.,(
	    float)1.,(float)-12.,(float)12.,(float)1.,(float)-2.,(float)3.,(
	    float)0.,(float)-2.,(float)-3.,(float)-4.,(float)2.,(float)-5.,(
	    float)-2.,(float)6.,(float)4.,(float)0.,(float)1.,(float)3.,(
	    float)0. };
    static real h1930[66] = { (float)0.,(float)0.,(float)5808.,(float)0.,(
	    float)-1424.,(float)644.,(float)0.,(float)-480.,(float)133.,(
	    float)166.,(float)0.,(float)205.,(float)-195.,(float)-109.,(float)
	    -90.,(float)0.,(float)-72.,(float)60.,(float)-53.,(float)-118.,(
	    float)58.,(float)0.,(float)4.,(float)102.,(float)19.,(float)-16.,(
	    float)8.,(float)-46.,(float)0.,(float)-51.,(float)-15.,(float)
	    -14.,(float)6.,(float)29.,(float)-18.,(float)-20.,(float)0.,(
	    float)8.,(float)-15.,(float)5.,(float)-14.,(float)5.,(float)18.,(
	    float)-5.,(float)-19.,(float)0.,(float)-20.,(float)14.,(float)5.,(
	    float)-3.,(float)-2.,(float)9.,(float)10.,(float)-2.,(float)2.,(
	    float)0.,(float)2.,(float)1.,(float)2.,(float)6.,(float)-4.,(
	    float)0.,(float)-2.,(float)4.,(float)0.,(float)-6. };
    static real g1935[66] = { (float)0.,(float)-30715.,(float)-2306.,(float)
	    -1018.,(float)2984.,(float)1550.,(float)1206.,(float)-1740.,(
	    float)1215.,(float)918.,(float)903.,(float)744.,(float)565.,(
	    float)-415.,(float)249.,(float)-241.,(float)329.,(float)211.,(
	    float)-33.,(float)-136.,(float)-76.,(float)59.,(float)53.,(float)
	    -8.,(float)-246.,(float)-25.,(float)25.,(float)-106.,(float)74.,(
	    float)-53.,(float)4.,(float)23.,(float)-33.,(float)-11.,(float)
	    18.,(float)6.,(float)11.,(float)7.,(float)-3.,(float)-9.,(float)
	    1.,(float)6.,(float)-6.,(float)8.,(float)7.,(float)8.,(float)10.,(
	    float)1.,(float)-12.,(float)11.,(float)1.,(float)-2.,(float)3.,(
	    float)0.,(float)-2.,(float)-3.,(float)-4.,(float)2.,(float)-5.,(
	    float)-2.,(float)6.,(float)4.,(float)0.,(float)2.,(float)3.,(
	    float)0. };
    static real h1935[66] = { (float)0.,(float)0.,(float)5812.,(float)0.,(
	    float)-1520.,(float)586.,(float)0.,(float)-494.,(float)146.,(
	    float)101.,(float)0.,(float)188.,(float)-226.,(float)-90.,(float)
	    -114.,(float)0.,(float)-51.,(float)64.,(float)-64.,(float)-115.,(
	    float)64.,(float)0.,(float)4.,(float)104.,(float)25.,(float)-15.,(
	    float)4.,(float)-40.,(float)0.,(float)-52.,(float)-17.,(float)
	    -14.,(float)7.,(float)29.,(float)-19.,(float)-19.,(float)0.,(
	    float)8.,(float)-15.,(float)5.,(float)-15.,(float)5.,(float)18.,(
	    float)-5.,(float)-19.,(float)0.,(float)-20.,(float)15.,(float)5.,(
	    float)-3.,(float)-3.,(float)9.,(float)11.,(float)-2.,(float)2.,(
	    float)0.,(float)2.,(float)1.,(float)2.,(float)6.,(float)-4.,(
	    float)0.,(float)-1.,(float)4.,(float)0.,(float)-6. };
    static real g1940[66] = { (float)0.,(float)-30654.,(float)-2292.,(float)
	    -1106.,(float)2981.,(float)1566.,(float)1240.,(float)-1790.,(
	    float)1232.,(float)916.,(float)914.,(float)762.,(float)550.,(
	    float)-405.,(float)265.,(float)-241.,(float)334.,(float)208.,(
	    float)-33.,(float)-141.,(float)-76.,(float)57.,(float)54.,(float)
	    -7.,(float)-249.,(float)-18.,(float)18.,(float)-107.,(float)74.,(
	    float)-53.,(float)4.,(float)20.,(float)-31.,(float)-9.,(float)17.,
	    (float)5.,(float)11.,(float)7.,(float)-3.,(float)-10.,(float)1.,(
	    float)6.,(float)-5.,(float)9.,(float)7.,(float)8.,(float)10.,(
	    float)1.,(float)-12.,(float)11.,(float)1.,(float)-2.,(float)3.,(
	    float)1.,(float)-2.,(float)-3.,(float)-4.,(float)2.,(float)-5.,(
	    float)-2.,(float)6.,(float)4.,(float)0.,(float)2.,(float)3.,(
	    float)0. };
    static real h1940[66] = { (float)0.,(float)0.,(float)5821.,(float)0.,(
	    float)-1614.,(float)528.,(float)0.,(float)-499.,(float)163.,(
	    float)43.,(float)0.,(float)169.,(float)-252.,(float)-72.,(float)
	    -141.,(float)0.,(float)-33.,(float)71.,(float)-75.,(float)-113.,(
	    float)69.,(float)0.,(float)4.,(float)105.,(float)33.,(float)-15.,(
	    float)0.,(float)-33.,(float)0.,(float)-52.,(float)-18.,(float)
	    -14.,(float)7.,(float)29.,(float)-20.,(float)-19.,(float)0.,(
	    float)8.,(float)-14.,(float)5.,(float)-15.,(float)5.,(float)19.,(
	    float)-5.,(float)-19.,(float)0.,(float)-21.,(float)15.,(float)5.,(
	    float)-3.,(float)-3.,(float)9.,(float)11.,(float)-2.,(float)2.,(
	    float)0.,(float)2.,(float)1.,(float)2.,(float)6.,(float)-4.,(
	    float)0.,(float)-1.,(float)4.,(float)0.,(float)-6. };
    static real g1945[66] = { (float)0.,(float)-30594.,(float)-2285.,(float)
	    -1244.,(float)2990.,(float)1578.,(float)1282.,(float)-1834.,(
	    float)1255.,(float)913.,(float)944.,(float)776.,(float)544.,(
	    float)-421.,(float)304.,(float)-253.,(float)346.,(float)194.,(
	    float)-20.,(float)-142.,(float)-82.,(float)59.,(float)57.,(float)
	    6.,(float)-246.,(float)-25.,(float)21.,(float)-104.,(float)70.,(
	    float)-40.,(float)0.,(float)0.,(float)-29.,(float)-10.,(float)15.,
	    (float)29.,(float)13.,(float)7.,(float)-8.,(float)-5.,(float)9.,(
	    float)7.,(float)-10.,(float)7.,(float)2.,(float)5.,(float)-21.,(
	    float)1.,(float)-11.,(float)3.,(float)16.,(float)-3.,(float)-4.,(
	    float)-3.,(float)-4.,(float)-3.,(float)11.,(float)1.,(float)2.,(
	    float)-5.,(float)-1.,(float)8.,(float)-1.,(float)-3.,(float)5.,(
	    float)-2. };
    static real h1945[66] = { (float)0.,(float)0.,(float)5810.,(float)0.,(
	    float)-1702.,(float)477.,(float)0.,(float)-499.,(float)186.,(
	    float)-11.,(float)0.,(float)144.,(float)-276.,(float)-55.,(float)
	    -178.,(float)0.,(float)-12.,(float)95.,(float)-67.,(float)-119.,(
	    float)82.,(float)0.,(float)6.,(float)100.,(float)16.,(float)-9.,(
	    float)-16.,(float)-39.,(float)0.,(float)-45.,(float)-18.,(float)
	    2.,(float)6.,(float)28.,(float)-17.,(float)-22.,(float)0.,(float)
	    12.,(float)-21.,(float)-12.,(float)-7.,(float)2.,(float)18.,(
	    float)3.,(float)-11.,(float)0.,(float)-27.,(float)17.,(float)29.,(
	    float)-9.,(float)4.,(float)9.,(float)6.,(float)1.,(float)8.,(
	    float)0.,(float)5.,(float)1.,(float)-20.,(float)-1.,(float)-6.,(
	    float)6.,(float)-4.,(float)-2.,(float)0.,(float)-2. };
    static real g1950[66] = { (float)0.,(float)-30554.,(float)-2250.,(float)
	    -1341.,(float)2998.,(float)1576.,(float)1297.,(float)-1889.,(
	    float)1274.,(float)896.,(float)954.,(float)792.,(float)528.,(
	    float)-408.,(float)303.,(float)-240.,(float)349.,(float)211.,(
	    float)-20.,(float)-147.,(float)-76.,(float)54.,(float)57.,(float)
	    4.,(float)-247.,(float)-16.,(float)12.,(float)-105.,(float)65.,(
	    float)-55.,(float)2.,(float)1.,(float)-40.,(float)-7.,(float)5.,(
	    float)19.,(float)22.,(float)15.,(float)-4.,(float)-1.,(float)11.,(
	    float)15.,(float)-13.,(float)5.,(float)-1.,(float)3.,(float)-7.,(
	    float)-1.,(float)-25.,(float)10.,(float)5.,(float)-5.,(float)-2.,(
	    float)3.,(float)8.,(float)-8.,(float)4.,(float)-1.,(float)13.,(
	    float)-4.,(float)4.,(float)12.,(float)3.,(float)2.,(float)10.,(
	    float)3. };
    static real h1950[66] = { (float)0.,(float)0.,(float)5815.,(float)0.,(
	    float)-1810.,(float)381.,(float)0.,(float)-476.,(float)206.,(
	    float)-46.,(float)0.,(float)136.,(float)-278.,(float)-37.,(float)
	    -210.,(float)0.,(float)3.,(float)103.,(float)-87.,(float)-122.,(
	    float)80.,(float)0.,(float)-1.,(float)99.,(float)33.,(float)-12.,(
	    float)-12.,(float)-30.,(float)0.,(float)-35.,(float)-17.,(float)
	    0.,(float)10.,(float)36.,(float)-18.,(float)-16.,(float)0.,(float)
	    5.,(float)-22.,(float)0.,(float)-21.,(float)-8.,(float)17.,(float)
	    -4.,(float)-17.,(float)0.,(float)-24.,(float)19.,(float)12.,(
	    float)2.,(float)2.,(float)8.,(float)8.,(float)-11.,(float)-7.,(
	    float)0.,(float)13.,(float)-2.,(float)-10.,(float)2.,(float)-3.,(
	    float)6.,(float)-3.,(float)6.,(float)11.,(float)8. };
    static real g1955[66] = { (float)0.,(float)-30500.,(float)-2215.,(float)
	    -1440.,(float)3003.,(float)1581.,(float)1302.,(float)-1944.,(
	    float)1288.,(float)882.,(float)958.,(float)796.,(float)510.,(
	    float)-397.,(float)290.,(float)-229.,(float)360.,(float)230.,(
	    float)-23.,(float)-152.,(float)-69.,(float)47.,(float)57.,(float)
	    3.,(float)-247.,(float)-8.,(float)7.,(float)-107.,(float)65.,(
	    float)-56.,(float)2.,(float)10.,(float)-32.,(float)-11.,(float)9.,
	    (float)18.,(float)11.,(float)9.,(float)-6.,(float)-14.,(float)6.,(
	    float)10.,(float)-7.,(float)6.,(float)9.,(float)4.,(float)9.,(
	    float)-4.,(float)-5.,(float)2.,(float)4.,(float)1.,(float)2.,(
	    float)2.,(float)5.,(float)-3.,(float)-5.,(float)-1.,(float)2.,(
	    float)-3.,(float)7.,(float)4.,(float)-2.,(float)6.,(float)-2.,(
	    float)0. };
    static real h1955[66] = { (float)0.,(float)0.,(float)5820.,(float)0.,(
	    float)-1898.,(float)291.,(float)0.,(float)-462.,(float)216.,(
	    float)-83.,(float)0.,(float)133.,(float)-274.,(float)-23.,(float)
	    -230.,(float)0.,(float)15.,(float)110.,(float)-98.,(float)-121.,(
	    float)78.,(float)0.,(float)-9.,(float)96.,(float)48.,(float)-16.,(
	    float)-12.,(float)-24.,(float)0.,(float)-50.,(float)-24.,(float)
	    -4.,(float)8.,(float)28.,(float)-20.,(float)-18.,(float)0.,(float)
	    10.,(float)-15.,(float)5.,(float)-23.,(float)3.,(float)23.,(float)
	    -4.,(float)-13.,(float)0.,(float)-11.,(float)12.,(float)7.,(float)
	    6.,(float)-2.,(float)10.,(float)7.,(float)-6.,(float)5.,(float)0.,
	    (float)-4.,(float)0.,(float)-8.,(float)-2.,(float)-4.,(float)1.,(
	    float)-3.,(float)7.,(float)-1.,(float)-3. };
    static real g1960[66] = { (float)0.,(float)-30421.,(float)-2169.,(float)
	    -1555.,(float)3002.,(float)1590.,(float)1302.,(float)-1992.,(
	    float)1289.,(float)878.,(float)957.,(float)800.,(float)504.,(
	    float)-394.,(float)269.,(float)-222.,(float)362.,(float)242.,(
	    float)-26.,(float)-156.,(float)-63.,(float)46.,(float)58.,(float)
	    1.,(float)-237.,(float)-1.,(float)-2.,(float)-113.,(float)67.,(
	    float)-56.,(float)5.,(float)15.,(float)-32.,(float)-7.,(float)17.,
	    (float)8.,(float)15.,(float)6.,(float)-4.,(float)-11.,(float)2.,(
	    float)10.,(float)-5.,(float)10.,(float)8.,(float)4.,(float)6.,(
	    float)0.,(float)-9.,(float)1.,(float)4.,(float)-1.,(float)-2.,(
	    float)3.,(float)-1.,(float)1.,(float)-3.,(float)4.,(float)0.,(
	    float)-1.,(float)4.,(float)6.,(float)1.,(float)-1.,(float)2.,(
	    float)0. };
    static real h1960[66] = { (float)0.,(float)0.,(float)5791.,(float)0.,(
	    float)-1967.,(float)206.,(float)0.,(float)-414.,(float)224.,(
	    float)-130.,(float)0.,(float)135.,(float)-278.,(float)3.,(float)
	    -255.,(float)0.,(float)16.,(float)125.,(float)-117.,(float)-114.,(
	    float)81.,(float)0.,(float)-10.,(float)99.,(float)60.,(float)-20.,
	    (float)-11.,(float)-17.,(float)0.,(float)-55.,(float)-28.,(float)
	    -6.,(float)7.,(float)23.,(float)-18.,(float)-17.,(float)0.,(float)
	    11.,(float)-14.,(float)7.,(float)-18.,(float)4.,(float)23.,(float)
	    1.,(float)-20.,(float)0.,(float)-18.,(float)12.,(float)2.,(float)
	    0.,(float)-3.,(float)9.,(float)8.,(float)0.,(float)5.,(float)0.,(
	    float)4.,(float)1.,(float)0.,(float)2.,(float)-5.,(float)1.,(
	    float)-1.,(float)6.,(float)0.,(float)-7. };
    static real g1965[66] = { (float)0.,(float)-30334.,(float)-2119.,(float)
	    -1662.,(float)2997.,(float)1594.,(float)1297.,(float)-2038.,(
	    float)1292.,(float)856.,(float)957.,(float)804.,(float)479.,(
	    float)-390.,(float)252.,(float)-219.,(float)358.,(float)254.,(
	    float)-31.,(float)-157.,(float)-62.,(float)45.,(float)61.,(float)
	    8.,(float)-228.,(float)4.,(float)1.,(float)-111.,(float)75.,(
	    float)-57.,(float)4.,(float)13.,(float)-26.,(float)-6.,(float)13.,
	    (float)1.,(float)13.,(float)5.,(float)-4.,(float)-14.,(float)0.,(
	    float)8.,(float)-1.,(float)11.,(float)4.,(float)8.,(float)10.,(
	    float)2.,(float)-13.,(float)10.,(float)-1.,(float)-1.,(float)5.,(
	    float)1.,(float)-2.,(float)-2.,(float)-3.,(float)2.,(float)-5.,(
	    float)-2.,(float)4.,(float)4.,(float)0.,(float)2.,(float)2.,(
	    float)0. };
    static real h1965[66] = { (float)0.,(float)0.,(float)5776.,(float)0.,(
	    float)-2016.,(float)114.,(float)0.,(float)-404.,(float)240.,(
	    float)-165.,(float)0.,(float)148.,(float)-269.,(float)13.,(float)
	    -269.,(float)0.,(float)19.,(float)128.,(float)-126.,(float)-97.,(
	    float)81.,(float)0.,(float)-11.,(float)100.,(float)68.,(float)
	    -32.,(float)-8.,(float)-7.,(float)0.,(float)-61.,(float)-27.,(
	    float)-2.,(float)6.,(float)26.,(float)-23.,(float)-12.,(float)0.,(
	    float)7.,(float)-12.,(float)9.,(float)-16.,(float)4.,(float)24.,(
	    float)-3.,(float)-17.,(float)0.,(float)-22.,(float)15.,(float)7.,(
	    float)-4.,(float)-5.,(float)10.,(float)10.,(float)-4.,(float)1.,(
	    float)0.,(float)2.,(float)1.,(float)2.,(float)6.,(float)-4.,(
	    float)0.,(float)-2.,(float)3.,(float)0.,(float)-6. };
    static real g1970[66] = { (float)0.,(float)-30220.,(float)-2068.,(float)
	    -1781.,(float)3e3,(float)1611.,(float)1287.,(float)-2091.,(float)
	    1278.,(float)838.,(float)952.,(float)800.,(float)461.,(float)
	    -395.,(float)234.,(float)-216.,(float)359.,(float)262.,(float)
	    -42.,(float)-160.,(float)-56.,(float)43.,(float)64.,(float)15.,(
	    float)-212.,(float)2.,(float)3.,(float)-112.,(float)72.,(float)
	    -57.,(float)1.,(float)14.,(float)-22.,(float)-2.,(float)13.,(
	    float)-2.,(float)14.,(float)6.,(float)-2.,(float)-13.,(float)-3.,(
	    float)5.,(float)0.,(float)11.,(float)3.,(float)8.,(float)10.,(
	    float)2.,(float)-12.,(float)10.,(float)-1.,(float)0.,(float)3.,(
	    float)1.,(float)-1.,(float)-3.,(float)-3.,(float)2.,(float)-5.,(
	    float)-1.,(float)6.,(float)4.,(float)1.,(float)0.,(float)3.,(
	    float)-1. };
    static real h1970[66] = { (float)0.,(float)0.,(float)5737.,(float)0.,(
	    float)-2047.,(float)25.,(float)0.,(float)-366.,(float)251.,(float)
	    -196.,(float)0.,(float)167.,(float)-266.,(float)26.,(float)-279.,(
	    float)0.,(float)26.,(float)139.,(float)-139.,(float)-91.,(float)
	    83.,(float)0.,(float)-12.,(float)100.,(float)72.,(float)-37.,(
	    float)-6.,(float)1.,(float)0.,(float)-70.,(float)-27.,(float)-4.,(
	    float)8.,(float)23.,(float)-23.,(float)-11.,(float)0.,(float)7.,(
	    float)-15.,(float)6.,(float)-17.,(float)6.,(float)21.,(float)-6.,(
	    float)-16.,(float)0.,(float)-21.,(float)16.,(float)6.,(float)-4.,(
	    float)-5.,(float)10.,(float)11.,(float)-2.,(float)1.,(float)0.,(
	    float)1.,(float)1.,(float)3.,(float)4.,(float)-4.,(float)0.,(
	    float)-1.,(float)3.,(float)1.,(float)-4. };
    static real g1975[66] = { (float)0.,(float)-30100.,(float)-2013.,(float)
	    -1902.,(float)3010.,(float)1632.,(float)1276.,(float)-2144.,(
	    float)1260.,(float)830.,(float)946.,(float)791.,(float)438.,(
	    float)-405.,(float)216.,(float)-218.,(float)356.,(float)264.,(
	    float)-59.,(float)-159.,(float)-49.,(float)45.,(float)66.,(float)
	    28.,(float)-198.,(float)1.,(float)6.,(float)-111.,(float)71.,(
	    float)-56.,(float)1.,(float)16.,(float)-14.,(float)0.,(float)12.,(
	    float)-5.,(float)14.,(float)6.,(float)-1.,(float)-12.,(float)-8.,(
	    float)4.,(float)0.,(float)10.,(float)1.,(float)7.,(float)10.,(
	    float)2.,(float)-12.,(float)10.,(float)-1.,(float)-1.,(float)4.,(
	    float)1.,(float)-2.,(float)-3.,(float)-3.,(float)2.,(float)-5.,(
	    float)-2.,(float)5.,(float)4.,(float)1.,(float)0.,(float)3.,(
	    float)-1. };
    static real h1975[66] = { (float)0.,(float)0.,(float)5675.,(float)0.,(
	    float)-2067.,(float)-68.,(float)0.,(float)-333.,(float)262.,(
	    float)-223.,(float)0.,(float)191.,(float)-265.,(float)39.,(float)
	    -288.,(float)0.,(float)31.,(float)148.,(float)-152.,(float)-83.,(
	    float)88.,(float)0.,(float)-13.,(float)99.,(float)75.,(float)-41.,
	    (float)-4.,(float)11.,(float)0.,(float)-77.,(float)-26.,(float)
	    -5.,(float)10.,(float)22.,(float)-23.,(float)-12.,(float)0.,(
	    float)6.,(float)-16.,(float)4.,(float)-19.,(float)6.,(float)18.,(
	    float)-10.,(float)-17.,(float)0.,(float)-21.,(float)16.,(float)7.,
	    (float)-4.,(float)-5.,(float)10.,(float)11.,(float)-3.,(float)1.,(
	    float)0.,(float)1.,(float)1.,(float)3.,(float)4.,(float)-4.,(
	    float)-1.,(float)-1.,(float)3.,(float)1.,(float)-5. };
    static real g1980[66] = { (float)0.,(float)-29992.,(float)-1956.,(float)
	    -1997.,(float)3027.,(float)1663.,(float)1281.,(float)-2180.,(
	    float)1251.,(float)833.,(float)938.,(float)782.,(float)398.,(
	    float)-419.,(float)199.,(float)-218.,(float)357.,(float)261.,(
	    float)-74.,(float)-162.,(float)-48.,(float)48.,(float)66.,(float)
	    42.,(float)-192.,(float)4.,(float)14.,(float)-108.,(float)72.,(
	    float)-59.,(float)2.,(float)21.,(float)-12.,(float)1.,(float)11.,(
	    float)-2.,(float)18.,(float)6.,(float)0.,(float)-11.,(float)-7.,(
	    float)4.,(float)3.,(float)6.,(float)-1.,(float)5.,(float)10.,(
	    float)1.,(float)-12.,(float)9.,(float)-3.,(float)-1.,(float)7.,(
	    float)2.,(float)-5.,(float)-4.,(float)-4.,(float)2.,(float)-5.,(
	    float)-2.,(float)5.,(float)3.,(float)1.,(float)2.,(float)3.,(
	    float)0. };
    static real h1980[66] = { (float)0.,(float)0.,(float)5604.,(float)0.,(
	    float)-2129.,(float)-200.,(float)0.,(float)-336.,(float)271.,(
	    float)-252.,(float)0.,(float)212.,(float)-257.,(float)53.,(float)
	    -297.,(float)0.,(float)46.,(float)150.,(float)-151.,(float)-78.,(
	    float)92.,(float)0.,(float)-15.,(float)93.,(float)71.,(float)-43.,
	    (float)-2.,(float)17.,(float)0.,(float)-82.,(float)-27.,(float)
	    -5.,(float)16.,(float)18.,(float)-23.,(float)-10.,(float)0.,(
	    float)7.,(float)-18.,(float)4.,(float)-22.,(float)9.,(float)16.,(
	    float)-13.,(float)-15.,(float)0.,(float)-21.,(float)16.,(float)9.,
	    (float)-5.,(float)-6.,(float)9.,(float)10.,(float)-6.,(float)2.,(
	    float)0.,(float)1.,(float)0.,(float)3.,(float)6.,(float)-4.,(
	    float)0.,(float)-1.,(float)4.,(float)0.,(float)-6. };
    static real g1985[66] = { (float)0.,(float)-29873.,(float)-1905.,(float)
	    -2072.,(float)3044.,(float)1687.,(float)1296.,(float)-2208.,(
	    float)1247.,(float)829.,(float)936.,(float)780.,(float)361.,(
	    float)-424.,(float)170.,(float)-214.,(float)355.,(float)253.,(
	    float)-93.,(float)-164.,(float)-46.,(float)53.,(float)65.,(float)
	    51.,(float)-185.,(float)4.,(float)16.,(float)-102.,(float)74.,(
	    float)-62.,(float)3.,(float)24.,(float)-6.,(float)4.,(float)10.,(
	    float)0.,(float)21.,(float)6.,(float)0.,(float)-11.,(float)-9.,(
	    float)4.,(float)4.,(float)4.,(float)-4.,(float)5.,(float)10.,(
	    float)1.,(float)-12.,(float)9.,(float)-3.,(float)-1.,(float)7.,(
	    float)1.,(float)-5.,(float)-4.,(float)-4.,(float)3.,(float)-5.,(
	    float)-2.,(float)5.,(float)3.,(float)1.,(float)2.,(float)3.,(
	    float)0. };
    static real h1985[66] = { (float)0.,(float)0.,(float)5500.,(float)0.,(
	    float)-2197.,(float)-306.,(float)0.,(float)-310.,(float)284.,(
	    float)-297.,(float)0.,(float)232.,(float)-249.,(float)69.,(float)
	    -297.,(float)0.,(float)47.,(float)150.,(float)-154.,(float)-75.,(
	    float)95.,(float)0.,(float)-16.,(float)88.,(float)69.,(float)-48.,
	    (float)-1.,(float)21.,(float)0.,(float)-83.,(float)-27.,(float)
	    -2.,(float)20.,(float)17.,(float)-23.,(float)-7.,(float)0.,(float)
	    8.,(float)-19.,(float)5.,(float)-23.,(float)11.,(float)14.,(float)
	    -15.,(float)-11.,(float)0.,(float)-21.,(float)15.,(float)9.,(
	    float)-6.,(float)-6.,(float)9.,(float)9.,(float)-7.,(float)2.,(
	    float)0.,(float)1.,(float)0.,(float)3.,(float)6.,(float)-4.,(
	    float)0.,(float)-1.,(float)4.,(float)0.,(float)-6. };
    static real g1990[66] = { (float)0.,(float)-29775.,(float)-1848.,(float)
	    -2131.,(float)3059.,(float)1686.,(float)1314.,(float)-2239.,(
	    float)1248.,(float)802.,(float)939.,(float)780.,(float)325.,(
	    float)-423.,(float)141.,(float)-214.,(float)353.,(float)245.,(
	    float)-109.,(float)-165.,(float)-36.,(float)61.,(float)65.,(float)
	    59.,(float)-178.,(float)3.,(float)18.,(float)-96.,(float)77.,(
	    float)-64.,(float)2.,(float)26.,(float)-1.,(float)5.,(float)9.,(
	    float)0.,(float)23.,(float)5.,(float)-1.,(float)-10.,(float)-12.,(
	    float)3.,(float)4.,(float)2.,(float)-6.,(float)4.,(float)9.,(
	    float)1.,(float)-12.,(float)9.,(float)-4.,(float)-2.,(float)7.,(
	    float)1.,(float)-6.,(float)-3.,(float)-4.,(float)2.,(float)-5.,(
	    float)-2.,(float)4.,(float)3.,(float)1.,(float)3.,(float)3.,(
	    float)0. };
    static real h1990[66] = { (float)0.,(float)0.,(float)5406.,(float)0.,(
	    float)-2279.,(float)-373.,(float)0.,(float)-284.,(float)293.,(
	    float)-352.,(float)0.,(float)247.,(float)-240.,(float)84.,(float)
	    -299.,(float)0.,(float)46.,(float)154.,(float)-153.,(float)-69.,(
	    float)97.,(float)0.,(float)-16.,(float)82.,(float)69.,(float)-52.,
	    (float)1.,(float)24.,(float)0.,(float)-80.,(float)-26.,(float)0.,(
	    float)21.,(float)17.,(float)-23.,(float)-4.,(float)0.,(float)10.,(
	    float)-19.,(float)6.,(float)-22.,(float)12.,(float)12.,(float)
	    -16.,(float)-10.,(float)0.,(float)-20.,(float)15.,(float)11.,(
	    float)-7.,(float)-7.,(float)9.,(float)8.,(float)-7.,(float)2.,(
	    float)0.,(float)2.,(float)1.,(float)3.,(float)6.,(float)-4.,(
	    float)0.,(float)-2.,(float)3.,(float)-1.,(float)-6. };
    static real g1995[66] = { (float)0.,(float)-29692.,(float)-1784.,(float)
	    -2200.,(float)3070.,(float)1681.,(float)1335.,(float)-2267.,(
	    float)1249.,(float)759.,(float)940.,(float)780.,(float)290.,(
	    float)-418.,(float)122.,(float)-214.,(float)352.,(float)235.,(
	    float)-118.,(float)-166.,(float)-17.,(float)68.,(float)67.,(float)
	    68.,(float)-170.,(float)-1.,(float)19.,(float)-93.,(float)77.,(
	    float)-72.,(float)1.,(float)28.,(float)5.,(float)4.,(float)8.,(
	    float)-2.,(float)25.,(float)6.,(float)-6.,(float)-9.,(float)-14.,(
	    float)9.,(float)6.,(float)-5.,(float)-7.,(float)4.,(float)9.,(
	    float)3.,(float)-10.,(float)8.,(float)-8.,(float)-1.,(float)10.,(
	    float)-2.,(float)-8.,(float)-3.,(float)-6.,(float)2.,(float)-4.,(
	    float)-1.,(float)4.,(float)2.,(float)2.,(float)5.,(float)1.,(
	    float)0. };
    static real h1995[66] = { (float)0.,(float)0.,(float)5306.,(float)0.,(
	    float)-2366.,(float)-413.,(float)0.,(float)-262.,(float)302.,(
	    float)-427.,(float)0.,(float)262.,(float)-236.,(float)97.,(float)
	    -306.,(float)0.,(float)46.,(float)165.,(float)-143.,(float)-55.,(
	    float)107.,(float)0.,(float)-17.,(float)72.,(float)67.,(float)
	    -58.,(float)1.,(float)36.,(float)0.,(float)-69.,(float)-25.,(
	    float)4.,(float)24.,(float)17.,(float)-24.,(float)-6.,(float)0.,(
	    float)11.,(float)-21.,(float)8.,(float)-23.,(float)15.,(float)11.,
	    (float)-16.,(float)-4.,(float)0.,(float)-20.,(float)15.,(float)
	    12.,(float)-6.,(float)-8.,(float)8.,(float)5.,(float)-8.,(float)
	    3.,(float)0.,(float)1.,(float)0.,(float)4.,(float)5.,(float)-5.,(
	    float)-1.,(float)-2.,(float)1.,(float)-2.,(float)-7. };
    static real g2000[66] = { (float)0.,(float)-29619.4,(float)-1728.2,(float)
	    -2267.7,(float)3068.4,(float)1670.9,(float)1339.6,(float)-2288.,(
	    float)1252.1,(float)714.5,(float)932.3,(float)786.8,(float)250.,(
	    float)-403.,(float)111.3,(float)-218.8,(float)351.4,(float)222.3,(
	    float)-130.4,(float)-168.6,(float)-12.9,(float)72.3,(float)68.2,(
	    float)74.2,(float)-160.9,(float)-5.9,(float)16.9,(float)-90.4,(
	    float)79.,(float)-74.,(float)0.,(float)33.3,(float)9.1,(float)6.9,
	    (float)7.3,(float)-1.2,(float)24.4,(float)6.6,(float)-9.2,(float)
	    -7.9,(float)-16.6,(float)9.1,(float)7.,(float)-7.9,(float)-7.,(
	    float)5.,(float)9.4,(float)3.,(float)-8.4,(float)6.3,(float)-8.9,(
	    float)-1.5,(float)9.3,(float)-4.3,(float)-8.2,(float)-2.6,(float)
	    -6.,(float)1.7,(float)-3.1,(float)-.5,(float)3.7,(float)1.,(float)
	    2.,(float)4.2,(float).3,(float)-1.1 };
    static real h2000[66] = { (float)0.,(float)0.,(float)5186.1,(float)0.,(
	    float)-2481.6,(float)-458.,(float)0.,(float)-227.6,(float)293.4,(
	    float)-491.1,(float)0.,(float)272.6,(float)-231.9,(float)119.8,(
	    float)-303.8,(float)0.,(float)43.8,(float)171.9,(float)-133.1,(
	    float)-39.3,(float)106.3,(float)0.,(float)-17.4,(float)63.7,(
	    float)65.1,(float)-61.2,(float).7,(float)43.8,(float)0.,(float)
	    -64.6,(float)-24.2,(float)6.2,(float)24.,(float)14.8,(float)-25.4,
	    (float)-5.8,(float)0.,(float)11.9,(float)-21.5,(float)8.5,(float)
	    -21.5,(float)15.5,(float)8.9,(float)-14.9,(float)-2.1,(float)0.,(
	    float)-19.7,(float)13.4,(float)12.5,(float)-6.2,(float)-8.4,(
	    float)8.4,(float)3.8,(float)-8.2,(float)4.8,(float)0.,(float)1.7,(
	    float)0.,(float)4.,(float)4.9,(float)-5.9,(float)-1.2,(float)-2.9,
	    (float)0.,(float)-2.2,(float)-7.4 };
    static real g2005[66] = { (float)0.,(float)-29554.63,(float)-1669.05,(
	    float)-2337.24,(float)3047.69,(float)1657.76,(float)1336.3,(float)
	    -2305.83,(float)1246.39,(float)672.51,(float)920.55,(float)797.96,
	    (float)210.65,(float)-379.86,(float)100.,(float)-227.,(float)
	    354.41,(float)208.95,(float)-136.54,(float)-168.05,(float)-13.55,(
	    float)73.6,(float)69.56,(float)76.74,(float)-151.34,(float)-14.58,
	    (float)14.58,(float)-86.36,(float)79.88,(float)-74.46,(float)
	    -1.65,(float)38.73,(float)12.3,(float)9.37,(float)5.42,(float)
	    1.94,(float)24.8,(float)7.62,(float)-11.73,(float)-6.88,(float)
	    -18.11,(float)10.17,(float)9.36,(float)-11.25,(float)-4.87,(float)
	    5.58,(float)9.76,(float)3.58,(float)-6.94,(float)5.01,(float)
	    -10.76,(float)-1.25,(float)8.76,(float)-6.66,(float)-9.22,(float)
	    -2.17,(float)-6.12,(float)1.42,(float)-2.35,(float)-.15,(float)
	    3.06,(float).29,(float)2.06,(float)3.77,(float)-.21,(float)-2.09 }
	    ;
    static real h2005[66] = { (float)0.,(float)0.,(float)5077.99,(float)0.,(
	    float)-2594.5,(float)-515.43,(float)0.,(float)-198.86,(float)
	    269.72,(float)-524.72,(float)0.,(float)282.07,(float)-225.23,(
	    float)145.15,(float)-305.36,(float)0.,(float)42.72,(float)180.25,(
	    float)-123.45,(float)-19.57,(float)103.85,(float)0.,(float)-20.33,
	    (float)54.75,(float)63.63,(float)-63.53,(float).24,(float)50.94,(
	    float)0.,(float)-61.14,(float)-22.57,(float)6.82,(float)25.35,(
	    float)10.93,(float)-26.32,(float)-4.64,(float)0.,(float)11.2,(
	    float)-20.88,(float)9.83,(float)-19.71,(float)16.22,(float)7.61,(
	    float)-12.76,(float)-.06,(float)0.,(float)-20.11,(float)12.69,(
	    float)12.67,(float)-6.72,(float)-8.16,(float)8.1,(float)2.92,(
	    float)-7.73,(float)6.01,(float)0.,(float)2.19,(float).1,(float)
	    4.46,(float)4.76,(float)-6.58,(float)-1.01,(float)-3.47,(float)
	    -.86,(float)-2.31,(float)-7.93 };
    static real g2010[66] = { (float)0.,(float)-29496.5,(float)-1585.9,(float)
	    -2396.6,(float)3026.,(float)1668.6,(float)1339.7,(float)-2326.3,(
	    float)1231.7,(float)634.2,(float)912.6,(float)809.,(float)166.6,(
	    float)-357.1,(float)89.7,(float)-231.1,(float)357.2,(float)200.3,(
	    float)-141.2,(float)-163.1,(float)-7.7,(float)72.8,(float)68.6,(
	    float)76.,(float)-141.4,(float)-22.9,(float)13.1,(float)-77.9,(
	    float)80.4,(float)-75.,(float)-4.7,(float)45.3,(float)14.,(float)
	    10.4,(float)1.6,(float)4.9,(float)24.3,(float)8.2,(float)-14.5,(
	    float)-5.7,(float)-19.3,(float)11.6,(float)10.9,(float)-14.1,(
	    float)-3.7,(float)5.4,(float)9.4,(float)3.4,(float)-5.3,(float)
	    3.1,(float)-12.4,(float)-.8,(float)8.4,(float)-8.4,(float)-10.1,(
	    float)-2.,(float)-6.3,(float).9,(float)-1.1,(float)-.2,(float)2.5,
	    (float)-.3,(float)2.2,(float)3.1,(float)-1.,(float)-2.8 };
    static real h2010[66] = { (float)0.,(float)0.,(float)4945.1,(float)0.,(
	    float)-2707.7,(float)-575.4,(float)0.,(float)-160.5,(float)251.7,(
	    float)-536.8,(float)0.,(float)286.4,(float)-211.2,(float)164.4,(
	    float)-309.2,(float)0.,(float)44.7,(float)188.9,(float)-118.1,(
	    float).1,(float)100.9,(float)0.,(float)-20.8,(float)44.2,(float)
	    61.5,(float)-66.3,(float)3.1,(float)54.9,(float)0.,(float)-57.8,(
	    float)-21.2,(float)6.6,(float)24.9,(float)7.,(float)-27.7,(float)
	    -3.4,(float)0.,(float)10.9,(float)-20.,(float)11.9,(float)-17.4,(
	    float)16.7,(float)7.1,(float)-10.8,(float)1.7,(float)0.,(float)
	    -20.5,(float)11.6,(float)12.8,(float)-7.2,(float)-7.4,(float)8.,(
	    float)2.2,(float)-6.1,(float)7.,(float)0.,(float)2.8,(float)-.1,(
	    float)4.7,(float)4.4,(float)-7.2,(float)-1.,(float)-4.,(float)-2.,
	    (float)-2.,(float)-8.3 };
    static real dg[45] = { (float)0.,(float)11.4,(float)16.7,(float)-11.3,(
	    float)-3.9,(float)2.7,(float)1.3,(float)-3.9,(float)-2.9,(float)
	    -8.1,(float)-1.4,(float)2.,(float)-8.9,(float)4.4,(float)-2.3,(
	    float)-.5,(float).5,(float)-1.5,(float)-.7,(float)1.3,(float)1.4,(
	    float)-.3,(float)-.3,(float)-.3,(float)1.9,(float)-1.6,(float)-.2,
	    (float)1.8,(float).2,(float)-.1,(float)-.6,(float)1.4,(float).3,(
	    float).1,(float)-.8,(float).4,(float)-.1,(float).1,(float)-.5,(
	    float).3,(float)-.3,(float).3,(float).2,(float)-.5,(float).2 };
    static real dh[45] = { (float)0.,(float)0.,(float)-28.8,(float)0.,(float)
	    -23.,(float)-12.9,(float)0.,(float)8.6,(float)-2.9,(float)-2.1,(
	    float)0.,(float).4,(float)3.2,(float)3.6,(float)-.8,(float)0.,(
	    float).5,(float)1.5,(float).9,(float)3.7,(float)-.6,(float)0.,(
	    float)-.1,(float)-2.1,(float)-.4,(float)-.5,(float).8,(float).5,(
	    float)0.,(float).6,(float).3,(float)-.2,(float)-.1,(float)-.8,(
	    float)-.3,(float).2,(float)0.,(float)0.,(float).2,(float).5,(
	    float).4,(float).1,(float)-.1,(float).4,(float).4 };
    static integer ma = 0;
    static integer iyr = 0;
    static integer ipr = 0;

    /* Format strings */
    static char fmt_999[] = "(/\002   IGRF: GIVEN YEAR\002,i5,\002 IS OUT OF\
 INTERVAL 1900-2015\002/,\002   *** CALCULATIONS WILL BE DONE FOR YEAR =\002\
,i5,\002 ***\002/)";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer s_wsfe(), do_fio(), e_wsfe();
    double sqrt(), cos(), sin();

    /* Local variables */
    static real a[11], b[11], c__, d__, e, g[66], h__[66];
    static integer k, m, n;
    static real p, q, s, u, w, x, y, z__, d2, f1, f2;
    static integer n2;
    static real p2, aa, cf, bi, an, hh, dp, dt, sf;
    static integer mm, mn;
    static real pm, pp, qq, xk, bbf, rec[66];
    static integer mnn;
    static real bbr, bbt;

    /* Fortran I/O blocks */
    static cilist io___554 = { 0, 6, 0, fmt_999, 0 };


/*  ********************************************************************* */
/*     CALCULATES COMPONENTS OF THE MAIN (INTERNAL) GEOMAGNETIC FIELD IN SPHERICAL */
/*     GEOGRAPHICAL COORDINATE SYSTEM, USING IAGA INTERNATIONAL GEOMAGNETIC REFERENCE */
/*     MODEL COEFFICIENTS (e.g., http://www.ngdc.noaa.gov/IAGA/wg8/igrf2000.html) */

/*     UPDATING THE COEFFICIENTS TO A GIVEN EPOCH IS MADE AUTOMATICALLY UPON THE FIRST */
/*     CALL AND AFTER EVERY CHANGE OF THE PARAMETER IY. */

/* -----INPUT PARAMETERS: */

/*     IY  -  YEAR NUMBER (FOUR-DIGIT; 1965 &LE IY &LE 2005) */
/*     NM  -  HIGHEST ORDER OF SPHERICAL HARMONICS IN THE SCALAR POTENTIAL (NM &LE 10) */
/*     R,T,F -  SPHERICAL COORDINATES (RADIUS R IN UNITS RE=6371.2 KM, GEOGRAPHIC */
/*                COLATITUDE  T  AND LONGITUDE  F  IN RADIANS) */

/* -----OUTPUT PARAMETERS: */

/*     BR,BT,BF - SPHERICAL COMPONENTS OF THE MAIN GEOMAGNETIC FIELD IN NANOTESLA */

/*     LAST MODIFICATION:  JANUARY 5, 2001, BY: N. A. TSYGANENKO */
/*     THE CODE WAS MODIFIED TO ACCEPT DATES THROUGH 2005. */
/*     IT HAS ALSO BEEN SLIGHTLY SIMPLIFIED BY TAKING OUT SOME REDUNDANT STATEMENTS, */
/*     AND A "SAVE" STATEMENT WAS ADDED, TO AVOID POTENTIAL PROBLEMS WITH SOME */
/*     FORTRAN COMPILERS. */

/*     MODIFIED TO DGRF TO ACCEPT YEARS FROM 1900 THROUGH 2005 */
/*     BY SCOTT BOARDSEN, NASA GSFC, OCTOBER 2004 */
/*     MODIFIED TO IGRF-10 WITH YEARS THROUGH 2010 */
/*     BY V. PAPITASHVILI, NOVEMBER 2005 */
/*     MODIFIED TO IGRF-11 WITH YEARS THROUGH 2015 */
/*     BY V. PAPITASHVILI, January 2011 */

/*  ********************************************************************* */


    if (ma != 1) {
	goto L10;
    }
    if (*iy != iyr) {
	goto L30;
    }
    goto L130;
L10:
    ma = 1;

    for (n = 1; n <= 11; ++n) {
	n2 = (n << 1) - 1;
	n2 *= n2 - 2;
	i__1 = n;
	for (m = 1; m <= i__1; ++m) {
	    mn = n * (n - 1) / 2 + m;
/* L20: */
	    rec[mn - 1] = (real) ((n - m) * (n + m - 2)) / (real) n2;
	}
    }

L30:
    iyr = *iy;
    if (iyr < 1900) {
	iyr = 1900;
    }
    if (iyr > 2015) {
	iyr = 2015;
    }
    if (*iy != iyr && ipr == 0) {
	s_wsfe(&io___554);
	do_fio(&c__1, (char *)&(*iy), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&iyr, (ftnlen)sizeof(integer));
	e_wsfe();
    }
    if (iyr != *iy) {
	ipr = 1;
    }
/* 	include 'igrf_goto.h' */
    if (iyr < 1905) {
	goto L1900;
    }
/* INTERPOLATE BETWEEN 1900 - 1905 */
    if (iyr < 1910) {
	goto L1905;
    }
/* INTERPOLATE BETWEEN 1905 - 1910 */
    if (iyr < 1915) {
	goto L1910;
    }
/* INTERPOLATE BETWEEN 1910 - 1915 */
    if (iyr < 1920) {
	goto L1915;
    }
/* INTERPOLATE BETWEEN 1915 - 1920 */
    if (iyr < 1925) {
	goto L1920;
    }
/* INTERPOLATE BETWEEN 1920 - 1925 */
    if (iyr < 1930) {
	goto L1925;
    }
/* INTERPOLATE BETWEEN 1925 - 1930 */
    if (iyr < 1935) {
	goto L1930;
    }
/* INTERPOLATE BETWEEN 1930 - 1935 */
    if (iyr < 1940) {
	goto L1935;
    }
/* INTERPOLATE BETWEEN 1935 - 1940 */
    if (iyr < 1945) {
	goto L1940;
    }
/* INTERPOLATE BETWEEN 1940 - 1945 */
    if (iyr < 1950) {
	goto L1945;
    }
/* INTERPOLATE BETWEEN 1945 - 1950 */
    if (iyr < 1955) {
	goto L1950;
    }
/* INTERPOLATE BETWEEN 1950 - 1955 */
    if (iyr < 1960) {
	goto L1955;
    }
/* INTERPOLATE BETWEEN 1955 - 1960 */
    if (iyr < 1965) {
	goto L1960;
    }
/* INTERPOLATE BETWEEN 1960 - 1965 */
    if (iyr < 1970) {
	goto L1965;
    }
/* INTERPOLATE BETWEEN 1965 - 1970 */
    if (iyr < 1975) {
	goto L1970;
    }
/* INTERPOLATE BETWEEN 1970 - 1975 */
    if (iyr < 1980) {
	goto L1975;
    }
/* INTERPOLATE BETWEEN 1975 - 1980 */
    if (iyr < 1985) {
	goto L1980;
    }
/* INTERPOLATE BETWEEN 1980 - 1985 */
    if (iyr < 1990) {
	goto L1985;
    }
/* INTERPOLATE BETWEEN 1985 - 1990 */
    if (iyr < 1995) {
	goto L1990;
    }
/* INTERPOLATE BETWEEN 1990 - 1995 */
    if (iyr < 2000) {
	goto L1995;
    }
/* INTERPOLATE BETWEEN 1995 - 2000 */
    if (iyr < 2005) {
	goto L2000;
    }
/* INTERPOLATE BETWEEN 2000 - 2005 */
    if (iyr < 2010) {
	goto L2005;
    }

/*       EXTRAPOLATE BEYOND 2010: */

/* INTERPOLATE BETWEEN 2005 - 2010 */
    dt = (real) iyr - (float)2010.;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g2010[n - 1];
	h__[n - 1] = h2010[n - 1];
	if (n > 45) {
	    goto L40;
	}
	g[n - 1] += dg[n - 1] * dt;
	h__[n - 1] += dh[n - 1] * dt;
L40:
	;
    }
    goto L300;
/*       INTERPOLATE BETWEEN YEARS */
/* INTERPOLATE BETWEEN 1900 - 1905: */
L1900:
    f2 = (iyr - 1900) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1900[n - 1] * f1 + g1905[n - 1] * f2;
	h__[n - 1] = h1900[n - 1] * f1 + h1905[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1905 - 1910: */
L1905:
    f2 = (iyr - 1905) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1905[n - 1] * f1 + g1910[n - 1] * f2;
	h__[n - 1] = h1905[n - 1] * f1 + h1910[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1910 - 1915: */
L1910:
    f2 = (iyr - 1910) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1910[n - 1] * f1 + g1915[n - 1] * f2;
	h__[n - 1] = h1910[n - 1] * f1 + h1915[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1915 - 1920: */
L1915:
    f2 = (iyr - 1915) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1915[n - 1] * f1 + g1920[n - 1] * f2;
	h__[n - 1] = h1915[n - 1] * f1 + h1920[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1920 - 1925: */
L1920:
    f2 = (iyr - 1920) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1920[n - 1] * f1 + g1925[n - 1] * f2;
	h__[n - 1] = h1920[n - 1] * f1 + h1925[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1925 - 1930: */
L1925:
    f2 = (iyr - 1925) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1925[n - 1] * f1 + g1930[n - 1] * f2;
	h__[n - 1] = h1925[n - 1] * f1 + h1930[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1930 - 1935: */
L1930:
    f2 = (iyr - 1930) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1930[n - 1] * f1 + g1935[n - 1] * f2;
	h__[n - 1] = h1930[n - 1] * f1 + h1935[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1935 - 1940: */
L1935:
    f2 = (iyr - 1935) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1935[n - 1] * f1 + g1940[n - 1] * f2;
	h__[n - 1] = h1935[n - 1] * f1 + h1940[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1940 - 1945: */
L1940:
    f2 = (iyr - 1940) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1940[n - 1] * f1 + g1945[n - 1] * f2;
	h__[n - 1] = h1940[n - 1] * f1 + h1945[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1945 - 1950: */
L1945:
    f2 = (iyr - 1945) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1945[n - 1] * f1 + g1950[n - 1] * f2;
	h__[n - 1] = h1945[n - 1] * f1 + h1950[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1950 - 1955: */
L1950:
    f2 = (iyr - 1950) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1950[n - 1] * f1 + g1955[n - 1] * f2;
	h__[n - 1] = h1950[n - 1] * f1 + h1955[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1955 - 1960: */
L1955:
    f2 = (iyr - 1955) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1955[n - 1] * f1 + g1960[n - 1] * f2;
	h__[n - 1] = h1955[n - 1] * f1 + h1960[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1960 - 1965: */
L1960:
    f2 = (iyr - 1960) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1960[n - 1] * f1 + g1965[n - 1] * f2;
	h__[n - 1] = h1960[n - 1] * f1 + h1965[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1965 - 1970: */
L1965:
    f2 = (iyr - 1965) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1965[n - 1] * f1 + g1970[n - 1] * f2;
	h__[n - 1] = h1965[n - 1] * f1 + h1970[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1970 - 1975: */
L1970:
    f2 = (iyr - 1970) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1970[n - 1] * f1 + g1975[n - 1] * f2;
	h__[n - 1] = h1970[n - 1] * f1 + h1975[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1975 - 1980: */
L1975:
    f2 = (iyr - 1975) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1975[n - 1] * f1 + g1980[n - 1] * f2;
	h__[n - 1] = h1975[n - 1] * f1 + h1980[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1980 - 1985: */
L1980:
    f2 = (iyr - 1980) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1980[n - 1] * f1 + g1985[n - 1] * f2;
	h__[n - 1] = h1980[n - 1] * f1 + h1985[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1985 - 1990: */
L1985:
    f2 = (iyr - 1985) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1985[n - 1] * f1 + g1990[n - 1] * f2;
	h__[n - 1] = h1985[n - 1] * f1 + h1990[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1990 - 1995: */
L1990:
    f2 = (iyr - 1990) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1990[n - 1] * f1 + g1995[n - 1] * f2;
	h__[n - 1] = h1990[n - 1] * f1 + h1995[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 1995 - 2000: */
L1995:
    f2 = (iyr - 1995) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g1995[n - 1] * f1 + g2000[n - 1] * f2;
	h__[n - 1] = h1995[n - 1] * f1 + h2000[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 2000 - 2005: */
L2000:
    f2 = (iyr - 2000) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g2000[n - 1] * f1 + g2005[n - 1] * f2;
	h__[n - 1] = h2000[n - 1] * f1 + h2005[n - 1] * f2;
    }
    goto L300;
/* INTERPOLATE BETWEEN 2005 - 2010: */
L2005:
    f2 = (iyr - 2005) / (float)5.;
    f1 = (float)1. - f2;
    for (n = 1; n <= 66; ++n) {
	g[n - 1] = g2005[n - 1] * f1 + g2010[n - 1] * f2;
	h__[n - 1] = h2005[n - 1] * f1 + h2010[n - 1] * f2;
    }
    goto L300;
/*   COEFFICIENTS FOR A GIVEN YEAR HAVE BEEN CALCULATED; NOW MULTIPLY */
/*   THEM BY SCHMIDT NORMALIZATION FACTORS: */
L300:
    s = (float)1.;
    for (n = 2; n <= 11; ++n) {
	mn = n * (n - 1) / 2 + 1;
	s = s * (real) ((n << 1) - 3) / (real) (n - 1);
	g[mn - 1] *= s;
	h__[mn - 1] *= s;
	p = s;
	i__1 = n;
	for (m = 2; m <= i__1; ++m) {
	    aa = (float)1.;
	    if (m == 2) {
		aa = (float)2.;
	    }
	    p *= sqrt(aa * (real) (n - m + 1) / (real) (n + m - 2));
	    mnn = mn + m - 1;
	    g[mnn - 1] *= p;
/* L120: */
	    h__[mnn - 1] *= p;
	}
    }
/*     NOW CALCULATE THE FIELD COMPONENTS */
/*     (IN CASE OF MULTIPLE INVOCATIONS WITH THE SAME VALUES OF IY AND NM, */
/*      CALCULATIONS START RIGHT HERE): */
L130:
    pp = (float)1. / *r__;
    p = pp;
    k = *nm + 1;
    i__1 = k;
    for (n = 1; n <= i__1; ++n) {
	p *= pp;
	a[n - 1] = p;
/* L150: */
	b[n - 1] = p * n;
    }
    p = (float)1.;
    d__ = (float)0.;
    bbr = (float)0.;
    bbt = (float)0.;
    bbf = (float)0.;
    u = *t;
    cf = cos(*f);
    sf = sin(*f);
    c__ = cos(u);
    s = sin(u);
    i__1 = k;
    for (m = 1; m <= i__1; ++m) {
	if (m == 1) {
	    goto L160;
	}
	mm = m - 1;
	w = x;
	x = w * cf + y * sf;
	y = y * cf - w * sf;
	goto L170;
L160:
	x = (float)0.;
	y = (float)1.;
L170:
	q = p;
	z__ = d__;
	bi = (float)0.;
	p2 = (float)0.;
	d2 = (float)0.;
	i__2 = k;
	for (n = m; n <= i__2; ++n) {
	    an = a[n - 1];
	    mn = n * (n - 1) / 2 + m;
	    e = g[mn - 1];
	    hh = h__[mn - 1];
	    w = e * y + hh * x;
	    bbr += b[n - 1] * w * q;
	    bbt -= an * w * z__;
	    if (m == 1) {
		goto L180;
	    }
	    qq = q;
	    if (s < (float)1e-5) {
		qq = z__;
	    }
	    bi += an * (e * x - hh * y) * qq;
L180:
	    xk = rec[mn - 1];
	    dp = c__ * z__ - s * q - xk * d2;
	    pm = c__ * q - xk * p2;
	    d2 = z__;
	    p2 = q;
	    z__ = dp;
/* L190: */
	    q = pm;
	}
	d__ = s * d__ + c__ * p;
	p = s * p;
	if (m == 1) {
	    goto L200;
	}
	bi *= mm;
	bbf += bi;
L200:
	;
    }

    *br = bbr;
    *bt = bbt;
    if (s < (float)1e-5) {
	goto L210;
    }
    *bf = bbf / s;
    return 0;
L210:
    if (c__ < (float)0.) {
	bbf = -bbf;
    }
    *bf = bbf;
    return 0;

} /* igrf_ */



/* Subroutine */ int recalc_(iyr, iday, ihour, min__, isec)
integer *iyr, *iday, *ihour, *min__, *isec;
{
    /* Initialized data */

    static integer iye = 0;
    static integer ide = 0;
    static integer ipr = 0;

    /* Format strings */
    static char fmt_10[] = "(/\002 RECALC: GIVEN YEAR\002,i5,\002 IS OUT OF \
INTERVAL 1900-2010\002/,\002   *** CALCULATIONS WILL BE DONE FOR YEAR =\002,\
i5,\002 ***\002/)";

    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    integer s_wsfe(), do_fio(), e_wsfe();
    double sqrt(), cos(), sin(), asin(), atan2();

    /* Local variables */
    static real sdec, cgst, sgst, t, y, obliq, slong, f1, f2, srasn, s1, s2, 
	    s3, y1, y2, y3, z1, z2, z3, g10, g11, h11, dj, dt, sq, exmagx, 
	    exmagy, exmagz, eymagx, eymagy, dy1, dz1, dz2, dz3, dy2, dy3, gst,
	     sqq, sqr;
    extern /* Subroutine */ int sun_();
    static real dip1, dip2, dip3;

    /* Fortran I/O blocks */
    static cilist io___595 = { 0, 6, 0, fmt_10, 0 };


/*  ********************************************************************* */
/*  If only IYR is given then CALL RECALC(IYR,0,25,0,0) */
/*  THIS IS A MODIFIED VERSION OF THE SUBROUTINE RECOMP WRITTEN BY */
/*  N. A. TSYGANENKO. SINCE I WANT TO USE IT IN PLACE OF SUBROUTINE */
/*  RECALC, I HAVE RENAMED THIS ROUTINE RECALC AND ELIMINATED THE */
/*  ORIGINAL RECALC FROM THIS VERSION OF THE <GEOPACK.FOR> PACKAGE. */
/*  THIS WAY ALL ORIGINAL CALLS TO RECALC WILL CONTINUE TO WORK WITHOUT */
/*  HAVING TO CHANGE THEM TO CALLS TO RECOMP. */

/*  AN ALTERNATIVE VERSION OF THE SUBROUTINE RECALC FROM THE GEOPACK */
/*  PACKAGE BASED ON A DIFFERENT APPROACH TO DERIVATION OF ROTATION */
/*  MATRIX ELEMENTS */

/*  THIS SUBROUTINE WORKS BY 20% FASTER THAN RECALC AND IS EASIER TO */
/*  UNDERSTAND */
/*  ##################################################### */
/*  #  WRITTEN BY  N.A. TSYGANENKO ON DECEMBER 1, 1991  # */
/*  ##################################################### */
/*  Modified by Mauricio Peredo, Hughes STX at NASA/GSFC Code 695, */
/*  September 1992 */

/*  Modified to accept years up to year 2000 and updated IGRF coeficients */
/*     from 1945 (updated by V. Papitashvili, February 1995) */

/*  Modified to accept years up to 2005 (V. Papitashvili, January 2001) */

/*  Modified to accept years from 1900 through 2010 using the DGRF & */
/*     IGRF-10 coeficients (updated by V. Papitashvili, November 2005) */

/*  Modified to accept years up to 2015 (V. Papitashvili, January 2011) */

/*   OTHER SUBROUTINES CALLED BY THIS ONE: SUN */

/*     IYR = YEAR NUMBER (FOUR DIGITS) */
/*     IDAY = DAY OF YEAR (DAY 1 = JAN 1) */
/*     IHOUR = HOUR OF DAY (00 TO 23) */
/*     MIN = MINUTE OF HOUR (00 TO 59) */
/*     ISEC = SECONDS OF DAY(00 TO 59) */
/*  ********************************************************************* */
    if (*iyr == iye && *iday == ide) {
	goto L5;
    }
/*  IYE AND IDE ARE THE CURRENT VALUES OF YEAR AND DAY NUMBER */
    c1_1.iy = *iyr;
    ide = *iday;
    if (c1_1.iy < 1900) {
	c1_1.iy = 1900;
    }
    if (c1_1.iy > 2015) {
	c1_1.iy = 2015;
    }
/*  WE ARE RESTRICTED BY THE INTERVAL 1900-2015, FOR WHICH THE DGRF & IGRF-11 */
/*  COEFFICIENTS ARE KNOWN; IF IYR IS OUTSIDE THIS INTERVAL, THE */
/*  SUBROUTINE GIVES A WARNING (BUT DOES NOT REPEAT IT AT THE NEXT CALLS) */
    if (c1_1.iy != *iyr && ipr == 0) {
	s_wsfe(&io___595);
	do_fio(&c__1, (char *)&(*iyr), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&c1_1.iy, (ftnlen)sizeof(integer));
	e_wsfe();
    }
    if (c1_1.iy != *iyr) {
	ipr = 1;
    }
    iye = c1_1.iy;
/*  LINEAR INTERPOLATION OF THE GEODIPOLE MOMENT COMPONENTS BETWEEN THE */
/*  VALUES FOR THE NEAREST EPOCHS: */
    if (c1_1.iy < 1905) {
/* 1900-1905 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1900.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)31543. + f2 * (float)31464.;
	g11 = f1 * (float)-2298. - f2 * (float)2298.;
	h11 = f1 * (float)5922. + f2 * (float)5909.;
    } else if (c1_1.iy < 1910) {
/* 1905-1910 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1905.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)31464. + f2 * (float)31354.;
	g11 = f1 * (float)-2298. - f2 * (float)2297.;
	h11 = f1 * (float)5909. + f2 * (float)5898.;
    } else if (c1_1.iy < 1915) {
/* 1910-1915 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1910.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)31354. + f2 * (float)31212.;
	g11 = f1 * (float)-2297. - f2 * (float)2306.;
	h11 = f1 * (float)5898. + f2 * (float)5875.;
    } else if (c1_1.iy < 1920) {
/* 1915-1920 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1915.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)31212. + f2 * (float)31060.;
	g11 = f1 * (float)-2306. - f2 * (float)2317.;
	h11 = f1 * (float)5875. + f2 * (float)5845.;
    } else if (c1_1.iy < 1925) {
/* 1920-1925 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1920.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)31060. + f2 * (float)30926.;
	g11 = f1 * (float)-2317. - f2 * (float)2318.;
	h11 = f1 * (float)5845. + f2 * (float)5817.;
    } else if (c1_1.iy < 1930) {
/* 1925-1930 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1925.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)30926. + f2 * (float)30805.;
	g11 = f1 * (float)-2318. - f2 * (float)2316.;
	h11 = f1 * (float)5817. + f2 * (float)5808.;
    } else if (c1_1.iy < 1935) {
/* 1930-1935 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1930.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)30805. + f2 * (float)30715.;
	g11 = f1 * (float)-2316. - f2 * (float)2306.;
	h11 = f1 * (float)5808. + f2 * (float)5812.;
    } else if (c1_1.iy < 1940) {
/* 1935-1940 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1935.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)30715. + f2 * (float)30654.;
	g11 = f1 * (float)-2306. - f2 * (float)2292.;
	h11 = f1 * (float)5812. + f2 * (float)5821.;
    } else if (c1_1.iy < 1945) {
/* 1940-1945 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1940.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)30654. + f2 * (float)30594.;
	g11 = f1 * (float)-2292. - f2 * (float)2285.;
	h11 = f1 * (float)5821. + f2 * (float)5810.;
    } else if (c1_1.iy < 1950) {
/* 1945-1950 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1945.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)30594. + f2 * (float)30554.;
	g11 = f1 * (float)-2285. - f2 * (float)2250.;
	h11 = f1 * (float)5810. + f2 * (float)5815.;
    } else if (c1_1.iy < 1955) {
/* 1950-1955 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1950.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)30554. + f2 * (float)30500.;
	g11 = f1 * (float)-2250. - f2 * (float)2215.;
	h11 = f1 * (float)5815. + f2 * (float)5820.;
    } else if (c1_1.iy < 1960) {
/* 1955-1960 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1955.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)30500. + f2 * (float)30421.;
	g11 = f1 * (float)-2215. - f2 * (float)2169.;
	h11 = f1 * (float)5820. + f2 * (float)5791.;
    } else if (c1_1.iy < 1965) {
/* 1960-1965 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1960.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)30421. + f2 * (float)30334.;
	g11 = f1 * (float)-2169. - f2 * (float)2119.;
	h11 = f1 * (float)5791. + f2 * (float)5776.;
    } else if (c1_1.iy < 1970) {
/* 1965-1970 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1965.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)30334. + f2 * (float)30220.;
	g11 = f1 * (float)-2119. - f2 * (float)2068.;
	h11 = f1 * (float)5776. + f2 * (float)5737.;
    } else if (c1_1.iy < 1975) {
/* 1970-1975 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1970.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)30220. + f2 * (float)30100.;
	g11 = f1 * (float)-2068. - f2 * (float)2013.;
	h11 = f1 * (float)5737. + f2 * (float)5675.;
    } else if (c1_1.iy < 1980) {
/* 1975-1980 */
	f2 = ((doublereal) c1_1.iy + (doublereal) (*iday) / (float)365. - (
		float)1975.) / (float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)30100. + f2 * (float)29992.;
	g11 = f1 * (float)-2013. - f2 * (float)1956.;
	h11 = f1 * (float)5675. + f2 * (float)5604.;
    } else if (c1_1.iy < 1985) {
/* 1980-1985 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1980.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)29992. + f2 * (float)29873.;
	g11 = f1 * (float)-1956. - f2 * (float)1905.;
	h11 = f1 * (float)5604. + f2 * (float)5500.;
    } else if (c1_1.iy < 1990) {
/* 1985-1990 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1985.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)29873. + f2 * (float)29775.;
	g11 = f1 * (float)-1905. - f2 * (float)1848.;
	h11 = f1 * (float)5500. + f2 * (float)5406.;
    } else if (c1_1.iy < 1995) {
/* 1990-1995 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1990.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)29775. + f2 * (float)29692.;
	g11 = f1 * (float)-1848. - f2 * (float)1784.;
	h11 = f1 * (float)5406. + f2 * (float)5306.;
    } else if (c1_1.iy < 2000) {
/* 1995-2000 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)1995.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)29692. + f2 * (float)29619.4;
	g11 = f1 * (float)-1784. - f2 * (float)1728.2;
	h11 = f1 * (float)5306. + f2 * (float)5186.1;
    } else if (c1_1.iy < 2005) {
/* 2000-2005 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)2e3) / (
		float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)29619.4 + f2 * (float)29554.63;
	g11 = f1 * (float)-1728.2 - f2 * (float)1669.05;
	h11 = f1 * (float)5186.1 + f2 * (float)5077.99;
    } else if (c1_1.iy < 2010) {
/* 2005-2010 */
	f2 = ((real) c1_1.iy + (real) (*iday) / (float)365. - (float)2005.) / 
		(float)5.;
	f1 = 1. - f2;
	g10 = f1 * (float)29554.63 + f2 * (float)29496.5;
	g11 = f1 * (float)-1669.05 - f2 * (float)1585.9;
	h11 = f1 * (float)5077.99 + f2 * (float)4945.1;
    } else {
/* 2010-2015 */
	dt = (real) c1_1.iy + (real) (*iday) / (float)365. - (float)2010.;
	g10 = (float)29496.5 - dt * (float)11.4;
	g11 = dt * (float)16.7 - (float)1585.9;
	h11 = (float)4945.1 - dt * (float)28.8;
    }
/*  NOW CALCULATE THE COMPONENTS OF THE UNIT VECTOR EzMAG IN GEO COORD */
/*  SYSTEM: */
/*  SIN(TETA0)*COS(LAMBDA0), SIN(TETA0)*SIN(LAMBDA0), AND COS(TETA0) */
/*         ST0 * CL0                ST0 * SL0                CT0 */
/* Computing 2nd power */
    r__1 = g11;
/* Computing 2nd power */
    r__2 = h11;
    sq = r__1 * r__1 + r__2 * r__2;
    sqq = sqrt(sq);
/* Computing 2nd power */
    r__1 = g10;
    sqr = sqrt(r__1 * r__1 + sq);
    c1_1.sl0 = -h11 / sqq;
    c1_1.cl0 = -g11 / sqq;
    c1_1.st0 = sqq / sqr;
    c1_1.ct0 = g10 / sqr;
    c1_1.stcl = c1_1.st0 * c1_1.cl0;
    c1_1.stsl = c1_1.st0 * c1_1.sl0;
    c1_1.ctsl = c1_1.ct0 * c1_1.sl0;
    c1_1.ctcl = c1_1.ct0 * c1_1.cl0;
/*  THE CALCULATIONS ARE TERMINATED IF ONLY GEO-MAG TRANSFORMATION */
/*  IS TO BE DONE  (IHOUR>24 IS THE AGREED CONDITION FOR THIS CASE): */
L5:
    if (*ihour > 24) {
	return 0;
    }
    sun_(&c1_1.iy, iday, ihour, min__, isec, &gst, &slong, &srasn, &sdec);
/*  S1,S2, AND S3 ARE THE COMPONENTS OF THE UNIT VECTOR EXGSM=EXGSE */
/*  IN THE SYSTEM GEI POINTING FROM THE EARTH'S CENTER TO THE SUN: */
    s1 = cos(srasn) * cos(sdec);
    s2 = sin(srasn) * cos(sdec);
    s3 = sin(sdec);
    cgst = cos(gst);
    sgst = sin(gst);
/*  DIP1, DIP2, AND DIP3 ARE THE COMPONENTS OF THE UNIT VECTOR */
/*  EZSM=EZMAG IN THE SYSTEM GEI: */
    dip1 = c1_1.stcl * cgst - c1_1.stsl * sgst;
    dip2 = c1_1.stcl * sgst + c1_1.stsl * cgst;
    dip3 = c1_1.ct0;
/*  NOW CALCULATE THE COMPONENTS OF THE UNIT VECTOR EYGSM IN THE SYSTEM */
/*  GEI BY TAKING THE VECTOR PRODUCT D x S AND NORMALIZING IT TO UNIT */
/*  LENGTH: */
    y1 = dip2 * s3 - dip3 * s2;
    y2 = dip3 * s1 - dip1 * s3;
    y3 = dip1 * s2 - dip2 * s1;
    y = sqrt(y1 * y1 + y2 * y2 + y3 * y3);
    y1 /= y;
    y2 /= y;
    y3 /= y;
/*  THEN IN THE GEI SYSTEM THE UNIT VECTOR Z=EZGSM=EXGSM x EYGSM=S x Y */
/*  HAS THE COMPONENTS: */
    z1 = s2 * y3 - s3 * y2;
    z2 = s3 * y1 - s1 * y3;
    z3 = s1 * y2 - s2 * y1;
/*  THE VECTOR EZGSE (HERE DZ) IN GEI HAS THE COMPONENTS (0,-SIN(DELTA), */
/*  COS(DELTA)) = (0.,-0.397823,0.917462); HERE DELTA = 23.44214 DEG FOR */
/*  THE EPOCH 1978 (SEE THE BOOK BY GUREVICH OR OTHER ASTRONOMICAL */
/*  HANDBOOKS). HERE THE MOST ACCURATE TIME-DEPENDENT FORMULA IS USED: */
    dj = (real) ((c1_1.iy - 1900) * 365 + (c1_1.iy - 1901) / 4 + *iday) - (
	    float).5 + (real) (*isec) / (float)86400.;
    t = dj / (float)36525.;
    obliq = ((float)23.45229 - t * (float).0130125) / (float)57.2957795;
    dz1 = (float)0.;
    dz2 = -sin(obliq);
    dz3 = cos(obliq);
/*  THEN THE UNIT VECTOR EYGSE IN GEI SYSTEM IS THE VECTOR PRODUCT DZ x S */
    dy1 = dz2 * s3 - dz3 * s2;
    dy2 = dz3 * s1 - dz1 * s3;
    dy3 = dz1 * s2 - dz2 * s1;
/*  THE ELEMENTS OF THE MATRIX GSE TO GSM ARE THE SCALAR PRODUCTS: */
/*  CHI=EM22=(EYGSM,EYGSE), SHI=EM23=(EYGSM,EZGSE), */
/*  EM32=(EZGSM,EYGSE)=-EM23, AND EM33=(EZGSM,EZGSE)=EM22 */
    c1_1.chi = y1 * dy1 + y2 * dy2 + y3 * dy3;
    c1_1.shi = y1 * dz1 + y2 * dz2 + y3 * dz3;
    c1_1.hi = asin(c1_1.shi);
/*  TILT ANGLE: PSI=ARCSIN(DIP,EXGSM) */
    c1_1.sps = dip1 * s1 + dip2 * s2 + dip3 * s3;
/* Computing 2nd power */
    r__1 = c1_1.sps;
    c1_1.cps = sqrt((float)1. - r__1 * r__1);
    c1_1.psi = asin(c1_1.sps);
/*  THE ELEMENTS OF THE MATRIX MAG TO SM ARE THE SCALAR PRODUCTS: */
/*  CFI=GM22=(EYSM,EYMAG), SFI=GM23=(EYSM,EXMAG); THEY CAN BE DERIVED */
/*  AS FOLLOWS: */
/*  IN GEO THE VECTORS EXMAG AND EYMAG HAVE THE COMPONENTS */
/*  (CT0*CL0,CT0*SL0,-ST0) AND (-SL0,CL0,0), RESPECTIVELY. HENCE, IN */
/*  GEI SYSTEM THE COMPONENTS ARE: */
/*  EXMAG:    CT0*CL0*COS(GST)-CT0*SL0*SIN(GST) */
/*            CT0*CL0*SIN(GST)+CT0*SL0*COS(GST) */
/*            -ST0 */
/*  EYMAG:    -SL0*COS(GST)-CL0*SIN(GST) */
/*            -SL0*SIN(GST)+CL0*COS(GST) */
/*             0 */
/*  THE COMPONENTS OF EYSM IN GEI WERE FOUND ABOVE AS Y1, Y2, AND Y3; */
/*  NOW WE ONLY HAVE TO COMBINE THE QUANTITIES INTO SCALAR PRODUCTS: */
    exmagx = c1_1.ct0 * (c1_1.cl0 * cgst - c1_1.sl0 * sgst);
    exmagy = c1_1.ct0 * (c1_1.cl0 * sgst + c1_1.sl0 * cgst);
    exmagz = -c1_1.st0;
    eymagx = -(c1_1.sl0 * cgst + c1_1.cl0 * sgst);
    eymagy = -(c1_1.sl0 * sgst - c1_1.cl0 * cgst);
    c1_1.cfi = y1 * eymagx + y2 * eymagy;
    c1_1.sfi = y1 * exmagx + y2 * exmagy + y3 * exmagz;
    c1_1.xmut = (atan2(c1_1.sfi, c1_1.cfi) + (float)3.1415926536) * (float)
	    3.8197186342;
/*  THE ELEMENTS OF THE MATRIX GEO TO GSM ARE THE SCALAR PRODUCTS: */
/*  A11=(EXGEO,EXGSM), A12=(EYGEO,EXGSM), A13=(EZGEO,EXGSM), */
/*  A21=(EXGEO,EYGSM), A22=(EYGEO,EYGSM), A23=(EZGEO,EYGSM), */
/*  A31=(EXGEO,EZGSM), A32=(EYGEO,EZGSM), A33=(EZGEO,EZGSM), */
/*  ALL THE UNIT VECTORS IN BRACKETS ARE ALREADY DEFINED IN GEI: */
/*  EXGEO=(CGST,SGST,0), EYGEO=(-SGST,CGST,0), EZGEO=(0,0,1) */
/*  EXGSM=(S1,S2,S3),  EYGSM=(Y1,Y2,Y3),   EZGSM=(Z1,Z2,Z3) */
/*  AND  THEREFORE: */
    c1_1.a11 = s1 * cgst + s2 * sgst;
    c1_1.a12 = -s1 * sgst + s2 * cgst;
    c1_1.a13 = s3;
    c1_1.a21 = y1 * cgst + y2 * sgst;
    c1_1.a22 = -y1 * sgst + y2 * cgst;
    c1_1.a23 = y3;
    c1_1.a31 = z1 * cgst + z2 * sgst;
    c1_1.a32 = -z1 * sgst + z2 * cgst;
    c1_1.a33 = z3;
    return 0;
} /* recalc_ */



/* Subroutine */ int sphcar_(r__, teta, phi, x, y, z__, j)
real *r__, *teta, *phi, *x, *y, *z__;
integer *j;
{
    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double sqrt(), atan2(), sin(), cos();

    /* Local variables */
    static real sq;

/*  ********************************************************************* */
/*   CONVERTS SPHERICAL COORDS INTO CARTESIAN ONES AND VICA VERSA */
/*    (TETA AND PHI IN RADIANS). */
/*                  J>0            J<0 */
/* -----INPUT:   J,R,TETA,PHI     J,X,Y,Z */
/* ----OUTPUT:      X,Y,Z        R,TETA,PHI */
/*  AUTHOR: NIKOLAI A. TSYGANENKO, INSTITUTE OF PHYSICS, ST.-PETERSBURG */
/*      STATE UNIVERSITY, STARY PETERGOF 198904, ST.-PETERSBURG, RUSSIA */
/*      (now the NASA Goddard Space Fligth Center, Greenbelt, Maryland) */
/*  ********************************************************************* */
    if (*j > 0) {
	goto L3;
    }
/* Computing 2nd power */
    r__1 = *x;
/* Computing 2nd power */
    r__2 = *y;
    sq = r__1 * r__1 + r__2 * r__2;
/* Computing 2nd power */
    r__1 = *z__;
    *r__ = sqrt(sq + r__1 * r__1);
    if (sq != (float)0.) {
	goto L2;
    }
    *phi = (float)0.;
    if (*z__ < (float)0.) {
	goto L1;
    }
    *teta = (float)0.;
    return 0;
L1:
    *teta = (float)3.141592654;
    return 0;
L2:
    sq = sqrt(sq);
    *phi = atan2(*y, *x);
    *teta = atan2(sq, *z__);
    if (*phi < (float)0.) {
	*phi += (float)6.28318531;
    }
    return 0;
L3:
    sq = *r__ * sin(*teta);
    *x = sq * cos(*phi);
    *y = sq * sin(*phi);
    *z__ = *r__ * cos(*teta);
    return 0;
} /* sphcar_ */



/* Subroutine */ int bspcar_(teta, phi, br, btet, bphi, bx, by, bz)
real *teta, *phi, *br, *btet, *bphi, *bx, *by, *bz;
{
    /* Builtin functions */
    double sin(), cos();

    /* Local variables */
    static real c__, s, be, cf, sf;

/*  ********************************************************************* */
/*   CALCULATES CARTESIAN FIELD COMPONENTS FROM SPHERICAL ONES */
/* -----INPUT:   TETA,PHI - SPHERICAL ANGLES OF THE POINT IN RADIANS */
/*              BR,BTET,BPHI -  SPHERICAL COMPONENTS OF THE FIELD */
/* -----OUTPUT:  BX,BY,BZ - CARTESIAN COMPONENTS OF THE FIELD */
/*  AUTHOR: NIKOLAI A. TSYGANENKO, INSTITUTE OF PHYSICS, ST.-PETERSBURG */
/*      STATE UNIVERSITY, STARY PETERGOF 198904, ST.-PETERSBURG, RUSSIA */
/*      (now the NASA Goddard Space Fligth Center, Greenbelt, Maryland) */
/*  ********************************************************************* */
    s = sin(*teta);
    c__ = cos(*teta);
    sf = sin(*phi);
    cf = cos(*phi);
    be = *br * s + *btet * c__;
    *bx = be * cf - *bphi * sf;
    *by = be * sf + *bphi * cf;
    *bz = *br * c__ - *btet * s;
    return 0;
} /* bspcar_ */



/* Subroutine */ int geomag_(xgeo, ygeo, zgeo, xmag, ymag, zmag, j, iyr)
real *xgeo, *ygeo, *zgeo, *xmag, *ymag, *zmag;
integer *j, *iyr;
{
    /* Initialized data */

    static integer ii = 1;

    extern /* Subroutine */ int recalc_();

/*  ********************************************************************* */
/* CONVERTS GEOCENTRIC (GEO) TO DIPOLE (MAG) COORDINATES OR VICA VERSA. */
/* IYR IS YEAR NUMBER (FOUR DIGITS). */
/*                           J>0                J<0 */
/* -----INPUT:  J,XGEO,YGEO,ZGEO,IYR   J,XMAG,YMAG,ZMAG,IYR */
/* -----OUTPUT:    XMAG,YMAG,ZMAG        XGEO,YGEO,ZGEO */
/*  AUTHOR: NIKOLAI A. TSYGANENKO, INSTITUTE OF PHYSICS, ST.-PETERSBURG */
/*      STATE UNIVERSITY, STARY PETERGOF 198904, ST.-PETERSBURG, RUSSIA */
/*      (now the NASA Goddard Space Fligth Center, Greenbelt, Maryland) */
/*  ********************************************************************* */
    if (*iyr == ii) {
	goto L1;
    }
    ii = *iyr;
    recalc_(&ii, &c__0, &c__25, &c__0, &c__0);
L1:
    if (*j < 0) {
	goto L2;
    }
    *xmag = *xgeo * c1_2.ctcl + *ygeo * c1_2.ctsl - *zgeo * c1_2.st0;
    *ymag = *ygeo * c1_2.cl0 - *xgeo * c1_2.sl0;
    *zmag = *xgeo * c1_2.stcl + *ygeo * c1_2.stsl + *zgeo * c1_2.ct0;
    return 0;
L2:
    *xgeo = *xmag * c1_2.ctcl - *ymag * c1_2.sl0 + *zmag * c1_2.stcl;
    *ygeo = *xmag * c1_2.ctsl + *ymag * c1_2.cl0 + *zmag * c1_2.stsl;
    *zgeo = *zmag * c1_2.ct0 - *xmag * c1_2.st0;
    return 0;
} /* geomag_ */



/* Subroutine */ int magsm_(xmag, ymag, zmag, xsm, ysm, zsm, j)
real *xmag, *ymag, *zmag, *xsm, *ysm, *zsm;
integer *j;
{
/*  ********************************************************************* */
/* CONVERTS DIPOLE (MAG) TO SOLAR MAGNETIC (SM) COORDINATES OR VICA VERSA */
/*                    J>0              J<0 */
/* -----INPUT: J,XMAG,YMAG,ZMAG     J,XSM,YSM,ZSM */
/* ----OUTPUT:    XSM,YSM,ZSM       XMAG,YMAG,ZMAG */
/*  ATTENTION: SUBROUTINE RECALC MUST BE CALLED BEFORE MAGSM IN TWO CASES */
/*     /A/  BEFORE THE FIRST USE OF MAGSM */
/*     /B/  IF THE CURRENT VALUES OF IYEAR,IDAY,IHOUR,MIN,ISEC ARE */
/*          DIFFERENT FROM THOSE IN THE PRECEDING CALL OF  MAGSM */
/*  AUTHOR: NIKOLAI A. TSYGANENKO, INSTITUTE OF PHYSICS, ST.-PETERSBURG */
/*      STATE UNIVERSITY, STARY PETERGOF 198904, ST.-PETERSBURG, RUSSIA */
/*      (now the NASA Goddard Space Fligth Center, Greenbelt, Maryland) */
/*  ********************************************************************* */
    if (*j < 0) {
	goto L1;
    }
    *xsm = *xmag * c1_3.cfi - *ymag * c1_3.sfi;
    *ysm = *xmag * c1_3.sfi + *ymag * c1_3.cfi;
    *zsm = *zmag;
    return 0;
L1:
    *xmag = *xsm * c1_3.cfi + *ysm * c1_3.sfi;
    *ymag = *ysm * c1_3.cfi - *xsm * c1_3.sfi;
    *zmag = *zsm;
    return 0;
} /* magsm_ */



/* Subroutine */ int smgsm_(xsm, ysm, zsm, xgsm, ygsm, zgsm, j)
real *xsm, *ysm, *zsm, *xgsm, *ygsm, *zgsm;
integer *j;
{
/*  ********************************************************************* */
/* CONVERTS SOLAR MAGNETIC (SM) TO SOLAR MAGNETOSPHERIC (GSM) COORDINATES */
/*   OR VICA VERSA. */
/*                  J>0                 J<0 */
/* -----INPUT: J,XSM,YSM,ZSM        J,XGSM,YGSM,ZGSM */
/* ----OUTPUT:  XGSM,YGSM,ZGSM       XSM,YSM,ZSM */
/*  ATTENTION: SUBROUTINE RECALC MUST BE CALLED BEFORE SMGSM IN TWO CASES */
/*     /A/  BEFORE THE FIRST USE OF SMGSM */
/*     /B/  IF THE CURRENT VALUES OF IYEAR,IDAY,IHOUR,MIN,ISEC ARE */
/*          DIFFERENT FROM THOSE IN THE PRECEDING CALL OF SMGSM */
/*  AUTHOR: NIKOLAI A. TSYGANENKO, INSTITUTE OF PHYSICS, ST.-PETERSBURG */
/*      STATE UNIVERSITY, STARY PETERGOF 198904, ST.-PETERSBURG, RUSSIA */
/*      (now the NASA Goddard Space Fligth Center, Greenbelt, Maryland) */
/*  ********************************************************************* */
    if (*j < 0) {
	goto L1;
    }
    *xgsm = *xsm * c1_4.cps + *zsm * c1_4.sps;
    *ygsm = *ysm;
    *zgsm = *zsm * c1_4.cps - *xsm * c1_4.sps;
    return 0;
L1:
    *xsm = *xgsm * c1_4.cps - *zgsm * c1_4.sps;
    *ysm = *ygsm;
    *zsm = *xgsm * c1_4.sps + *zgsm * c1_4.cps;
    return 0;
} /* smgsm_ */

