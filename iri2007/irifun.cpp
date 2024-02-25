/* irifun.f -- translated by f2c (version 20061008).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#ifdef __cplusplus
extern "C" {
#endif
#include "f2c.h"

/* Common Block Declarations */

extern union {
    struct {
	doublereal umr;
    } _1;
    struct {
	doublereal faktor;
    } _2;
    struct {
	doublereal dtr;
    } _3;
} const_;

#define const_1 (const_._1)
#define const_2 (const_._2)
#define const_3 (const_._3)

struct {
    doublereal argmax;
} argexp_;

#define argexp_1 argexp_

extern struct {
    doublereal humr, dumr;
} const1_;

#define const1_1 const1_

union {
    struct {
	doublereal hmf2, xnmf2, hmf1;
	logical f1reg;
    } _1;
    struct {
	doublereal hmf2, xnmf2, xhmf1;
	logical f1reg;
    } _2;
} block1_;

#define block1_1 (block1_._1)
#define block1_2 (block1_._2)

union {
    struct {
	doublereal beta, eta, delta, zeta;
    } _1;
    struct {
	doublereal beta, eta, del, zeta;
    } _2;
} blo10_;

#define blo10_1 (blo10_._1)
#define blo10_2 (blo10_._2)

struct {
    doublereal b2top, tc3, alg10, hcor1;
    integer itopn;
} blo11_;

#define blo11_1 blo11_

union {
    struct {
	doublereal b0, b1, c1;
    } _1;
    struct {
	doublereal b0, b1, d1f1;
    } _2;
} block2_;

#define block2_1 (block2_._1)
#define block2_2 (block2_._2)

struct {
    doublereal hz, t, hst;
} block3_;

#define block3_1 block3_

struct {
    doublereal hme, xnme, hef;
} block4_;

#define block4_1 block4_

struct {
    doublereal e[4];
    logical night;
} block5_;

#define block5_1 block5_

struct {
    doublereal hmd, xnmd, hdx;
} block6_;

#define block6_1 block6_

struct {
    doublereal d1, xkk, fp30, fp3u, fp1, fp2;
} block7_;

#define block7_1 block7_

struct {
    doublereal ah[7], ate1, st[6], d__[5];
} blote_;

#define blote_1 blote_

struct {
    doublereal hs, tnhs, xsm[4], mm[5], g[4];
    integer m;
} block8_;

#define block8_1 block8_

struct {
    doublereal xsm1, tex, tlbd, sig;
} blotn_;

#define blotn_1 blotn_

struct {
    integer konsol, monito;
} iounit_;

#define iounit_1 iounit_

struct {
    integer kf, n;
} mflux_;

#define mflux_1 mflux_

/* Table of constant values */

static doublereal c_b3 = 394.5;
static doublereal c_b5 = 100.;
static doublereal c_b6 = 300.;
static doublereal c_b18 = 1.;
static doublereal c_b30 = 10.;
static integer c__6 = 6;
static doublereal c_b55 = .33333333333333331;
static integer c__8 = 8;
static integer c__4 = 4;
static integer c__1 = 1;
static integer c__0 = 0;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__9 = 9;
static integer c__76 = 76;
static integer c__13 = 13;
static integer c__988 = 988;
static integer c__7 = 7;
static integer c__49 = 49;
static integer c__441 = 441;
static doublereal c_b207 = 2.36;
static doublereal c_b209 = .25;
static doublereal c_b212 = 2.7;
static doublereal c_b306 = 2.;
static doublereal c_b310 = .1;
static doublereal c_b311 = .15;
static integer c__5 = 5;

/* irifun.for, version number can be found at the end of this comment. */
/* ----------------------------------------------------------------------- */

/* Functions and subroutines for the International Reference */
/* Ionosphere model. These functions and subroutines are called by */
/* IRI_SUB subroutine (IRISUB.FOR). */

/* ----------------------------------------------------------------------- */

/* i/o units:  6   messages (during execution) to monitor */
/*            10   CCIR and URSI coefficients */
/*            11   alternate unit for message file (if jf(12)=.false.) */
/*            12   solar/ionospheric indices: ig_rz.dat */
/*            13   magnetic indices: ap.dat */
/*            14   igrf coefficients */

/* ----------------------------------------------------------------------- */
/* changes from IRIFU9 to IRIF10: */
/*       SOCO for solar zenith angle */
/*       ACOS and ASIN argument forced to be within -1 / +1 */
/*       EPSTEIN functions corrected for large arguments */
/* ----------------------------------------------------------------------- */
/* changes from IRIF10 to IRIF11: */
/*       LAY subroutines introduced */
/*       TEBA corrected for 1400 km */
/* ----------------------------------------------------------------------- */
/* changes from IRIF11 to IRIF12: */
/*       Neutral temperature subroutines now in CIRA86.FOR */
/*       TEDER changed */
/*       All names with 6 or more characters replaced */
/*       10/29/91 XEN: 10^ in loop, instead of at the end */
/*       1/21/93 B0_TAB instead of B0POL */
/*       9/22/94 Alleviate underflow condition in IONCOM exp() */
/* ----------------------------------------------------------------------- */
/* changes from IRIF12 to IRIF13: */
/*        9/18/95 MODA: add leap year and number of days in month */
/*        9/29/95 replace F2out with FOUT and XMOUT. */
/*       10/ 5/95 add TN and DTNDH; earlier in CIRA86.FOR */
/*       10/ 6/95 add TCON for reading indices */
/*       10/20/95 MODA: IN=1 MONTH=IMO */
/*       10/20/95 TCON: now includes RZ interpolation */
/*       11/05/95 IONCOM->IONCO1, added IONCOM_new, IONCO2 */
/*       11/05/95 LSTID added for strom-time updating */
/*       11/06/95 ROGUL: transition 20. instead of 15. */
/*       12/01/95 add UT_LT for (date-)correct UT<->LT conversion */
/*       01/16/96 TCON: add IMST to SAVE statement */
/*       02/02/96 ROGUL: 15. reinstated */
/*       02/07/96 UT_LT: ddd, dddend integer, no leap year 2000 */
/*       03/15/96 ZERO: finding delta for topside */
/*       03/18/96 UT_LT: mode=1, change of year */
/*       12/09/96 since 2000 is leap, delete y/100*100 condition */
/*       04/25/97 XMDED: minimal value also daytime */
/*       05/18/98 TCON: changes to IG_RZ (update date); -R = Cov */
/*       05/19/98 Replaced IONCO2&APROK; HEI,XHI in IONCOM_NEW */
/*       10/01/98 added INITIALIZE */
/*       04/30/99 MODA: reset bb(2)=28 */
/*       11/08/99 avoid negative x value in function XE2. Set x=0. */
/*       11/09/99 added COMMON/const1/humr,dumr also for CIRA86 */
/*       11/30/99 EXIT in APROK replaced with GOTO (N. Smirnova) */
/* ----------------------------------------------------------------------- */
/* changes from IRIF13 to IRIFUN: */
/* -Version-mm/dd/yy-description [person reporting correction] */
/* 2000.01 05/09/00 Include B0_98 subroutine to replace B0_NEW and B0POL */
/* 2000.02 05/18/00 Include Elteik and spharm_ik for Te */
/* 2000.03 06/09/00 Include xe3_1, xe4_1, xe_1 */
/* 2000.04 06/11/00 Include f1_c1, f1_prob, modified fof1ed */
/* 2000.05 10/30/00 Include vdrift */
/* 2000.06 04/15/01 Include IGRF_SUB subroutine for IK Te model */
/* 2000.07 05/07/01 Include storm subroutine STORM and Ap access s/w */
/* 2000.08 09/07/01 APF: if(j1.eq.j2) -> if(IY.eq.j2) [P. Wilkinson] */
/* 2000.09 09/07/01 CONVER: LO2 = MOD(LO1,20)+1 [P. Webb,D. Pesnell] */
/* 2000.10 02/20/02 CONVER/DATA: 105.78 -> 015.78 [A. Shovkoplyas] */
/* 2000.11 10/28/02 replace TAB/6 blanks, enforce 72/line [D. Simpson] */
/* 2000.12 11/08/02 removing unused variables (corr); apf0 removed */
/* 2000.13 11/26/02 apf() using keyed access to ap.dat file; apf->apf1 */
/* 2000.14 11/27/02 changed F1_PROB; always 6 preceeding spaces */
/* 2005.01 03/09/05 CALION,INVDPC,CALNE for new Ne, Ni models */
/* 2005.01 11/14/05 APF_ONLY for F107D; */
/* 2005.01 11/14/05 spreadf_brazil; added constraint 0<=P<=1 */
/* 2005.02 05/11/06 NeQuick: XE1,TOPQ, M3000HM; stormvd, */
/* 2005.02 03/27/07 STORM: hourly interpolation of Ap  [A. Oinats] */
/* 2007.00 05/18/07 Release of IRI-2007 */
/* 2007.01 09/19/07 vdrift et al.: without *8 (no change in results) */

/* ************************************************************** */
/* ********** INTERNATIONAL REFERENCE IONOSPHERE **************** */
/* ************************************************************** */
/* ****************  FUNCTIONS,SUBROUTINES  ********************* */
/* ************************************************************** */
/* ** initialize:	INITIALIZE */
/* ** NE:         XE1,TOPQ,ZERO,DXE1N,XE2,XE3_1,XE4_1,XE5,XE6, */
/* **             XE_1,CALNE */
/* ** TE/TI:      ELTEIK,SPHARM_IK,TEBA,SPHARM,ELTE,TEDE,TI,TEDER, */
/* **		          TN,DTNDH */
/* ** NI:         RPID,RDHHE,RDNO,KOEFP1,KOEFP2,KOEFP3,SUFE */
/* **               IONCO2,APROK,IONCOMP,IONCO1,CALION,INVDPC */
/* ** PEAKS:      FOUT,XMOUT,HMF2ED,FOF1ED,f1_c1,f1_prob,FOEEDI,XMDED, */
/* **		          GAMMA1 */
/* ** PROFILE PAR:B0_98,TAL,VALGUL */
/* ** MAG. FIELD: GGM,FIELDG,CONVER(Geom. Corrected Latitude) */
/* ** FUNCTIONS:  REGFA1 */
/* ** TIME:       SOCO,HPOL,MODA,UT_LT */
/* ** EPSTEIN:    RLAY,D1LAY,D2LAY,EPTR,EPST,EPSTEP,EPLA */
/* ** LAY:        XE2TO5,XEN,VALGUL,ROGUL,LNGLSN,LSKNM,INILAY */
/* ** INDICES:    TCON,APF,APF_ONLY */
/* ** Storm:   	LSTID,storm */
/* ** ion drift:  vdrift,bspl4_time,bspl4_long,g,stormvd, */
/* **             bspl4_ptime */
/* ** spread-F:	spreadf_brazil,bspl2f,bspl2l,bspl2s,bspl4t */
/* ************************************************************** */

/* ************************************************************** */
/* ***  -------------------ADDRESSES------------------------  *** */
/* ***  I  PROF. K. RAWER             DR. D. BILITZA       I  *** */
/* ***  I  HERRENSTR. 43              GSFC CODE 632        I  *** */
/* ***  I  7801 MARCH 1               GREENBELT MD 20771   I  *** */
/* ***  I  F.R.G.                     USA                  I  *** */
/* ***  ----------------------------------------------------  *** */
/* ************************************************************** */
/* ************************************************************** */


/* Subroutine */ int initialize_()
{
    /* Builtin functions */
    double atan(doublereal);

    /* Local variables */
    static doublereal pi;

    argexp_1.argmax = 88.;
    pi = atan(1.) * 4.;
    const_1.umr = pi / 180.;
    const1_1.humr = pi / 12.;
    const1_1.dumr = pi / 182.5;
    return 0;
} /* initialize_ */


/* ************************************************************* */
/* *************** ELECTRON DENSITY **************************** */
/* ************************************************************* */

doublereal xe1_(doublereal *h__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double d_sign(doublereal *, doublereal *), exp(doublereal);

    /* Local variables */
    static doublereal x, y, x0, rco, xmx0, dxdh, xred, tcor;
    extern doublereal eptr_(doublereal *, doublereal *, doublereal *), topq_(
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal eptr1, eptr2;

/* ---------------------------------------------------------------- */
/* REPRESENTING ELECTRON DENSITY(M-3) IN THE TOPSIDE IONOSPHERE */
/* (H=HMF2....1000 KM) BY HARMONIZED BENT-MODEL ADMITTING */
/* VARIABILITY OFGLOBAL PARAMETER ETA,ZETA,BETA,DELTA WITH */
/* GEOM. LATITUDE, SMOOTHED SOLAR FLUX AND CRITICAL FREQUENCY */
/* (SEE MAIN PROGRAM). */
/* [REF.:K.RAWER,S.RAMAKRISHNAN,1978] */
/* ---------------------------------------------------------------- */
    if (blo11_1.itopn == 2) {
	ret_val = topq_(h__, &block1_1.xnmf2, &block1_1.hmf2, &blo11_1.b2top);
	return ret_val;
    }
    dxdh = (1e3 - block1_1.hmf2) / 700.;
    x0 = 300. - blo10_1.delta;
    xmx0 = (*h__ - block1_1.hmf2) / dxdh;
    x = xmx0 + x0;
    eptr1 = eptr_(&x, &blo10_1.beta, &c_b3) - eptr_(&x0, &blo10_1.beta, &c_b3)
	    ;
    eptr2 = eptr_(&x, &c_b5, &c_b6) - eptr_(&x0, &c_b5, &c_b6);
    y = blo10_1.beta * blo10_1.eta * eptr1 + blo10_1.zeta * (eptr2 * 100. - 
	    xmx0);
    y *= dxdh;
    if (abs(y) > argexp_1.argmax) {
	y = d_sign(&argexp_1.argmax, &y);
    }
    tcor = 0.;
    if (blo11_1.itopn == 1 && *h__ > blo11_1.hcor1) {
	xred = *h__ - blo11_1.hcor1;
	rco = blo11_1.tc3 * xred;
	tcor = rco * blo11_1.alg10;
    }
    ret_val = block1_1.xnmf2 * exp(-y + tcor);
    return ret_val;
} /* xe1_ */



doublereal topq_(doublereal *h__, doublereal *no, doublereal *hmax, 
	doublereal *ho)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal z__, g1, ee, dh, ep;

/* ---------------------------------------------------------------- */
/*  NeQuick formula */
/* ---------------------------------------------------------------- */
    dh = *h__ - *hmax;
    g1 = dh * .125;
    z__ = dh / (*ho * (g1 * 100. / (*ho * 100. + g1) + 1.));
    if (z__ > 40.) {
	ret_val = 0.;
	return ret_val;
    }
    ee = exp(z__);
    if (ee > 1e7) {
	ep = 4. / ee;
    } else {
/* Computing 2nd power */
	d__1 = ee + 1.;
	ep = ee * 4. / (d__1 * d__1);
    }
    ret_val = *no * ep;
    return ret_val;
} /* topq_ */



doublereal zero_(doublereal *delta)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal z1, z2, arg1;

/* FOR A PEAK AT X0 THE FUNCTION ZERO HAS TO BE EQUAL TO 0. */
    arg1 = *delta / 100.;
    if (abs(arg1) < argexp_1.argmax) {
	z1 = 1. / (exp(arg1) + 1.);
    } else if (arg1 < 0.) {
	z1 = 1.;
    } else {
	z1 = 0.;
    }
    arg1 = (*delta + 94.5) / blo10_2.beta;
    if (abs(arg1) < argexp_1.argmax) {
	z2 = 1. / (exp(arg1) + 1.);
    } else if (arg1 < 0.) {
	z2 = 1.;
    } else {
	z2 = 0.;
    }
    ret_val = blo10_2.zeta * (1. - z1) - blo10_2.eta * z2;
    return ret_val;
} /* zero_ */



doublereal dxe1n_(doublereal *h__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal x, x0;
    extern doublereal epst_(doublereal *, doublereal *, doublereal *);
    static doublereal epst1, epst2;

/* LOGARITHMIC DERIVATIVE OF FUNCTION XE1 (KM-1). */
    x0 = 300. - blo10_1.delta;
    x = (*h__ - block1_1.hmf2) / (1e3 - block1_1.hmf2) * 700. + x0;
    epst2 = epst_(&x, &c_b5, &c_b6);
    epst1 = epst_(&x, &blo10_1.beta, &c_b3);
    ret_val = -blo10_1.eta * epst1 + blo10_1.zeta * (1. - epst2);
    return ret_val;
} /* dxe1n_ */



doublereal xe2_(doublereal *h__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), exp(doublereal), cosh(
	    doublereal);

    /* Local variables */
    static doublereal x, z__;

/* ELECTRON DENSITY FOR THE BOTTOMSIDE F-REGION (HMF1...HMF2). */
    x = (block1_1.hmf2 - *h__) / block2_1.b0;
    if (x <= 0.) {
	x = 0.;
    }
    z__ = pow_dd(&x, &block2_1.b1);
    if (z__ > argexp_1.argmax) {
	z__ = argexp_1.argmax;
    }
    ret_val = block1_1.xnmf2 * exp(-z__) / cosh(x);
    return ret_val;
} /* xe2_ */



doublereal xe3_1__(doublereal *h__)
{
    /* System generated locals */
    doublereal ret_val, d__1, d__2;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    extern doublereal xe2_(doublereal *);
    static doublereal h1bar;

/* ELECTRON DENSITY FOR THE F1-LAYER (HZ.....HMF1) */
/* USING THE NEW DEFINED F1-LAYER FUNCTION (Reinisch and Huang, Advances */
/* in Space Research, Volume 25, Number 1, 81-88, 2000) */

    h1bar = *h__;
    if (block1_1.f1reg) {
	d__1 = (block1_1.hmf1 - *h__) / block1_1.hmf1;
	d__2 = block2_2.d1f1 + 1.;
	h1bar = block1_1.hmf1 * (1. - pow_dd(&d__1, &d__2));
    }
    ret_val = xe2_(&h1bar);
    return ret_val;
} /* xe3_1__ */



doublereal xe4_1__(doublereal *h__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double d_sign(doublereal *, doublereal *), sqrt(doublereal);

    /* Local variables */
    extern doublereal xe3_1__(doublereal *);
    static doublereal h1bar;

/* ELECTRON DENSITY FOR THE INTERMEDIATE REGION (HEF...HZ) */
/* USING THE NEW DEFINED FUNCTION */

    if (block3_1.hst < 0.) {
	ret_val = block4_1.xnme + block3_1.t * (*h__ - block4_1.hef);
	return ret_val;
    }
    if (block3_1.hst == block4_1.hef) {
	h1bar = *h__;
    } else {
	h1bar = block3_1.hz + block3_1.t * .5 - d_sign(&c_b18, &block3_1.t) * 
		sqrt(block3_1.t * (block3_1.t * .25 + block3_1.hz - *h__));
    }
    ret_val = xe3_1__(&h1bar);
    return ret_val;
} /* xe4_1__ */



doublereal xe5_(doublereal *h__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal t1, t3;

/* ELECTRON DENSITY FOR THE E AND VALLEY REGION (HME..HEF). */
    t3 = *h__ - block4_1.hme;
    t1 = t3 * t3 * (block5_1.e[0] + t3 * (block5_1.e[1] + t3 * (block5_1.e[2] 
	    + t3 * block5_1.e[3])));
    if (block5_1.night) {
	goto L100;
    }
    ret_val = block4_1.xnme * (t1 + 1);
    return ret_val;
L100:
    ret_val = block4_1.xnme * exp(t1);
    return ret_val;
} /* xe5_ */



doublereal xe6_(doublereal *h__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal z__, fp3;

/* ELECTRON DENSITY FOR THE D REGION (HA...HME). */
    if (*h__ > block6_1.hdx) {
	goto L100;
    }
    z__ = *h__ - block6_1.hmd;
    fp3 = block7_1.fp3u;
    if (z__ > 0.) {
	fp3 = block7_1.fp30;
    }
    ret_val = block6_1.xnmd * exp(z__ * (block7_1.fp1 + z__ * (block7_1.fp2 + 
	    z__ * fp3)));
    return ret_val;
L100:
    z__ = block4_1.hme - *h__;
    ret_val = block4_1.xnme * exp(-block7_1.d1 * pow_dd(&z__, &block7_1.xkk));
    return ret_val;
} /* xe6_ */



doublereal xe_1__(doublereal *h__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal xe1_(doublereal *), xe2_(doublereal *), xe5_(doublereal 
	    *), xe6_(doublereal *);
    static doublereal hmf1;
    extern doublereal xe3_1__(doublereal *), xe4_1__(doublereal *);

/* ELECTRON DENSITY BEETWEEN HA(KM) AND 1000 KM */
/* SUMMARIZING PROCEDURES  NE1....6; */
    if (block1_2.f1reg) {
	hmf1 = block1_2.xhmf1;
    } else {
	hmf1 = block1_2.hmf2;
    }
    if (*h__ < block1_2.hmf2) {
	goto L100;
    }
    ret_val = xe1_(h__);
    return ret_val;
L100:
    if (*h__ < hmf1) {
	goto L300;
    }
    ret_val = xe2_(h__);
    return ret_val;
L300:
    if (*h__ < block3_1.hz) {
	goto L400;
    }
    ret_val = xe3_1__(h__);
    return ret_val;
L400:
    if (*h__ < block4_1.hef) {
	goto L500;
    }
    ret_val = xe4_1__(h__);
    return ret_val;
L500:
    if (*h__ < block4_1.hme) {
	goto L600;
    }
    ret_val = xe5_(h__);
    return ret_val;
L600:
    ret_val = xe6_(h__);
    return ret_val;
} /* xe_1__ */



/* Subroutine */ int calne_(integer *crd, doublereal *invdip, doublereal *fl, 
	doublereal *dimo, doublereal *b0, doublereal *dipl, doublereal *mlt, 
	doublereal *alt, integer *ddd, doublereal *f107, doublereal *nne)
{
    /* Initialized data */

    static struct {
	doublereal e_1[8];
	doublereal fill_2[4];
	doublereal e_3[8];
	doublereal fill_4[4];
	doublereal e_5[8];
	doublereal fill_6[4];
	doublereal e_7[8];
	doublereal fill_8[4];
	doublereal e_9[8];
	doublereal fill_10[4];
	doublereal e_11[8];
	doublereal fill_12[4];
	doublereal e_13[8];
	doublereal fill_14[4];
	doublereal e_15[8];
	doublereal fill_16[4];
	doublereal e_17[8];
	doublereal fill_18[4];
	doublereal e_19[8];
	doublereal fill_20[4];
	doublereal e_21[8];
	doublereal fill_22[4];
	doublereal e_23[8];
	doublereal fill_24[4];
	doublereal e_25[8];
	doublereal fill_26[4];
	doublereal e_27[8];
	doublereal fill_28[4];
	doublereal e_29[8];
	doublereal fill_30[4];
	doublereal e_31[8];
	doublereal fill_32[4];
	doublereal e_33[8];
	doublereal fill_34[4];
	doublereal e_35[8];
	doublereal fill_36[4];
	doublereal e_37[8];
	doublereal fill_38[4];
	doublereal e_39[8];
	doublereal fill_40[4];
	doublereal e_41[8];
	doublereal fill_42[4];
	doublereal e_43[8];
	doublereal fill_44[4];
	doublereal e_45[8];
	doublereal fill_46[4];
	doublereal e_47[8];
	doublereal fill_48[4];
	doublereal e_49[8];
	doublereal fill_50[4];
	doublereal e_51[8];
	doublereal fill_52[4];
	doublereal e_53[8];
	doublereal fill_54[4];
	doublereal e_55[8];
	doublereal fill_56[4];
	doublereal e_57[8];
	doublereal fill_58[4];
	doublereal e_59[8];
	doublereal fill_60[4];
	doublereal e_61[8];
	doublereal fill_62[4];
	doublereal e_63[8];
	doublereal fill_64[4];
	doublereal e_65[8];
	doublereal fill_66[4];
	doublereal e_67[8];
	doublereal fill_68[4];
	doublereal e_69[8];
	doublereal fill_70[4];
	doublereal e_71[8];
	doublereal fill_72[4];
	doublereal e_73[8];
	doublereal fill_74[4];
	doublereal e_75[8];
	doublereal fill_76[4];
	doublereal e_77[8];
	doublereal fill_78[4];
	doublereal e_79[8];
	doublereal fill_80[4];
	doublereal e_81[8];
	doublereal fill_82[4];
	doublereal e_83[8];
	doublereal fill_84[4];
	doublereal e_85[8];
	doublereal fill_86[4];
	doublereal e_87[8];
	doublereal fill_88[4];
	doublereal e_89[8];
	doublereal fill_90[4];
	doublereal e_91[8];
	doublereal fill_92[4];
	doublereal e_93[8];
	doublereal fill_94[4];
	doublereal e_95[8];
	doublereal fill_96[4];
	doublereal e_97[8];
	doublereal fill_98[4];
	} equiv_37 = { 11.654, 10.964, 10.369, 10.044, 11.447, 10.747, 10.23, 
		9.8437, {0}, -2.2826e-8, -1.5354e-9, 1.9844e-8, -4.8215e-10, 
		.33033, .2354, .18549, .28312, {0}, -.29373, -.17357, -.20005,
		 -.3576, -.38532, -.16245, -.17478, -.47686, {0}, -3.4268e-10,
		 2.4852e-8, 4.6147e-8, 2.1775e-8, -.22359, -.015474, .023684, 
		.14238, {0}, .064972, .1255, .13227, .082508, .21158, .084395,
		 .049509, -.0096995, {0}, -4.1631e-8, -5.3015e-9, 1.8945e-8, 
		4.7923e-9, -.013881, .036128, -.079218, -.048066, {0}, 
		.002504, -8.5408e-4, .11316, .094327, -.029286, 6.6939e-4, 
		.12211, .1203, {0}, -.23607, -.27902, -.18108, -.054271, 
		-.23339, -.23379, -.19639, -.078194, {0}, 3.3224e-9, 
		4.7844e-9, 2.7934e-9, 5.2633e-10, .0077235, .034316, -.03928, 
		.013805, {0}, -6.5151e-4, .007144, -.014698, .011187, .05723, 
		.0060415, .031281, .008247, {0}, 4.38e-9, 1.8258e-9, 
		4.1471e-9, -5.1303e-9, -.034982, .0050101, .014507, .0046119, 
		{0}, 5.517e-4, -.0023096, .0035627, -.021555, .011379, 
		-.0034666, -.010088, -.036194, {0}, 3.3359e-9, 2.5878e-9, 
		2.7073e-9, 5.7277e-10, .0025918, -.0077481, .0057436, 
		.0028395, {0}, -.38492, -.27308, -.072201, -.0072596, -.33942,
		 -.30157, -.12489, -.026545, {0}, 7.7351e-9, 4.6071e-9, 
		1.7208e-9, -6.4714e-10, .049621, -.0057407, .012205, .0011682,
		 {0}, .048326, .048916, .039133, -.010944, .06018, .063775, 
		.0089282, .011891, {0}, -2.4344e-9, -9.9364e-9, -3.6288e-9, 
		1.2469e-9, -.0079666, .010736, -.011558, -.0024794, {0}, 
		-.0092751, -.038824, -.003979, .0012361, .002157, -.0040436, 
		.0061501, .014748, {0}, 4.8353e-9, 4.5371e-9, 5.9338e-10, 
		3.2732e-11, -.0080235, .007492, -.0052639, -.0099502, {0}, 
		.10247, .0039659, -.044768, -.060089, .0807, -.019215, 
		-.023903, .018415, {0}, -7.7373e-10, -1.9952e-9, -1.135e-9, 
		5.949e-10, .03504, .010255, -.0090686, -.033637, {0}, 
		-.0043734, -5.8555e-4, -.0019636, -.0024869, -.0044115, 
		.0051722, -2.4549e-5, .01099, {0}, -1.4332e-10, 1.4458e-9, 
		1.6649e-9, -1.2181e-10, .006931, -.0050936, 6.6842e-6, 
		-.010111, {0}, -.0014617, .0069817, .0063878, -8.3456e-4, 
		.0055866, -8.485e-4, -2.8069e-4, .0029349, {0}, -.038595, 
		.041239, .013926, .02139, .037179, -.056382, -.042259, 
		-.025495, {0}, 2.2162e-9, -5.4244e-10, -2.8892e-10, 
		3.7568e-10, .018795, .016156, -.0087094, -.043211, {0}, 
		.020572, .010611, .0050022, .0099164, .015728, .014547, 
		.0080624, .011705, {0}, -2.2251e-9, -1.3677e-9, -8.1142e-11, 
		-1.1158e-9, .0079808, -.0035661, -.0024729, -.010655, {0}, 
		.0037842, .0028933, .0013966, 8.9177e-4, -.0037419, .0051087, 
		-5.7736e-4, .0051037, {0}, -.075166, .028197, .035646, 
		.013681, .017878, -.023719, .0061173, .015616, {0}, 
		6.2465e-10, -1.3422e-9, -8.2139e-10, 3.0065e-10, -.0094949, 
		8.3592e-4, .0014685, .0031856, {0}, .0016258, -.0085109, 
		-.0016012, .0026197, .008762, .0031225, -.0019136, -.0036023, 
		{0}, 2.5023e-10, 9.2018e-10, -1.0333e-10, -2.8667e-10, 
		-.0022723, .0019821, -6.6155e-4, -9.4473e-4, {0}, .019937, 
		-.020264, .021714, .012303, .02158, .026843, -.016568, 
		.0085888, {0}, -1.5199e-9, -8.7024e-10, -1.7686e-9, 
		-2.7819e-10, .030423, .0026876, -.0066461, .0024022, {0}, 
		-.0043, -.0022666, -.0027486, .0010276, -.001615, -.0062698, 
		-.0029717, .0055707, {0}, 5.8564e-10, -3.236e-10, -1.6622e-10,
		 -4.8067e-10, -.0020801, -2.7731e-4, -5.9281e-4, -1.65e-5, {0}
		, .026435, .0048919, .01423, .018107, -.026775, -.018704, 
		.0059044, -.0057463, {0}, 1.3539e-9, -7.2078e-10, 6.645e-11, 
		-6.3629e-11, .0047439, .0022622, -.0015221, .0052602, {0}, 
		.0052811, -.0030536, 6.071e-4, .001416, -6.2996e-4, .0011103, 
		-.0010024, -.0010524, {0}, .024115, -.0077757, .010634, 
		.013259, -.038774, .0074859, .004364, -.0045751, {0}, 
		7.1913e-10, -7.6475e-10, -7.634e-10, -4.2105e-10, -.0010191, 
		-.0015696, -1.2153e-5, .0030727, {0}, .0028906, -.0038334, 
		-.0028168, 3.9284e-4, -5.9711e-4, -.0014674, -4.6287e-4, 
		-.0016474, {0}, -.010944, .0044619, 4.7432e-4, -.0011911, 
		-.00618, -.012356, -.0014742, -.0031363, {0}, 4.8498e-11, 
		-3.4009e-10, -1.1803e-11, 1.2981e-11, .0043409, -6.2705e-5, 
		3.7337e-4, 4.2265e-4, {0}, 5.0294e-4, .0034805, -4.2779e-4, 
		-7.4254e-4, -.010281, -.009027, 1.2299e-4, -5.1937e-4, {0}, 
		-2.3208e-11, -3.3311e-10, -3.4642e-10, 2.7134e-11, .0023239, 
		-2.1341e-4, -1.8383e-4, .0012478, {0}, .0096733, -.0050825, 
		-.0011471, .0032463, -.0094754, -.014714, 3.4953e-4, 
		-.0021649, {0}, -.006112, -.0026849, .0050097, -.0030059, 
		-.012886, -.0026567, -.0013791, -5.2399e-4 };

#define dneh ((doublereal *)&equiv_37)

    static doublereal dnel[441]	/* was [3][3][49] */ = { 11.062,10.41,10.158,
	    10.967,10.407,10.166,0.0,0.0,0.0,-3.0911e-8,-5.5863e-8,-1.9548e-8,
	    .40368,.3515,.23694,0.0,0.0,0.0,-.38235,-.28735,-.36749,-.30547,
	    -.26152,-.27429,0.0,0.0,0.0,1.1313e-8,-6.7549e-8,-8.0357e-9,
	    -.13178,.03821,.1152,0.0,0.0,0.0,.14829,-.039147,.025141,.1221,
	    .025637,.030762,0.0,0.0,0.0,-6.3573e-8,-7.4702e-8,-3.2793e-8,
	    .047599,-.031519,-.082451,0.0,0.0,0.0,-.031902,-.07756,.064338,
	    .045964,.093065,.13504,0.0,0.0,0.0,-.24123,-.2677,-.20881,-.2694,
	    -.20338,-.14885,0.0,0.0,0.0,2.3955e-9,2.6217e-9,2.2857e-9,.050649,
	    .024015,.0063431,0.0,0.0,0.0,-.034781,-.02678,-.018004,.020835,
	    .048189,.072066,0.0,0.0,0.0,1.3383e-9,-1.8328e-9,4.1065e-9,
	    .013125,-.01231,-.014211,0.0,0.0,0.0,-.024546,-.03837,-.009227,
	    -.026758,-.012074,-.012608,0.0,0.0,0.0,1.8658e-9,1.132e-9,
	    2.3974e-9,.0083855,.0063295,.012061,0.0,0.0,0.0,-.26632,-.18013,
	    -.14469,-.30743,-.16583,-.10051,0.0,0.0,0.0,4.8835e-9,3.8029e-9,
	    5.8152e-10,-.035169,-.021338,7.1648e-4,0.0,0.0,0.0,.0029025,
	    -.031418,-.071135,.068584,.039239,.029195,0.0,0.0,0.0,-4.6079e-9,
	    -6.7073e-9,2.8358e-9,.022068,.0053636,.0053905,0.0,0.0,0.0,
	    -.032911,-.057161,-.025824,-.022965,-.012633,-.017088,0.0,0.0,0.0,
	    2.0026e-9,2.4874e-10,1.2833e-9,-.012112,.00144,.014637,0.0,0.0,
	    0.0,.076453,.059222,.044022,.056553,.068102,.021114,0.0,0.0,0.0,
	    8.8255e-10,-1.2232e-9,1.9468e-9,-.0057016,-.0063957,-.0079212,0.0,
	    0.0,0.0,.0010963,-.0014529,.017507,.008737,.0090268,.0084367,0.0,
	    0.0,0.0,-2.9776e-10,9.9371e-12,-1.7886e-9,-.0030176,-.0089534,
	    -.016341,0.0,0.0,0.0,-.001217,.0036985,.0016676,9.2492e-4,
	    7.3362e-4,.0049292,0.0,0.0,0.0,-.038531,-.0039165,.0056214,
	    -.04243,-.038612,-.022852,0.0,0.0,0.0,-1.7732e-10,3.3004e-9,
	    1.7403e-9,-.014924,-.018755,1.2029e-4,0.0,0.0,0.0,-.0012508,
	    .003805,.0068439,.007493,.0053402,2.7544e-4,0.0,0.0,0.0,
	    6.1993e-10,-7.624e-10,-9.6757e-10,-.005169,.0047158,.011996,0.0,
	    0.0,0.0,-1.9205e-4,-.0040473,5.7429e-5,9.9006e-4,7.3675e-4,
	    -1.6057e-5,0.0,0.0,0.0,-.0091547,.013918,.0041441,.01521,.02728,
	    .03187,0.0,0.0,0.0,6.1475e-10,-9.8974e-11,4.7678e-10,-7.8933e-4,
	    .001765,.0036162,0.0,0.0,0.0,.0031384,.0010506,.002627,-.0021342,
	    -.0035763,-.0032132,0.0,0.0,0.0,-3.7043e-10,-8.294e-10,5.0045e-11,
	    -4.1959e-4,.0017527,.0014402,0.0,0.0,0.0,.036801,.019068,.026003,
	    .0091102,-.017144,.013314,0.0,0.0,0.0,1.1714e-9,3.1352e-9,
	    1.9442e-9,.0014167,-.0013996,-.0018461,0.0,0.0,0.0,.0037754,
	    .0073603,.0061356,-.0030343,.0027811,.0058733,0.0,0.0,0.0,
	    -2.6027e-10,6.3141e-12,-1.8709e-10,5.129e-4,-.0014789,-.0028286,
	    0.0,0.0,0.0,-.0020821,1.8285e-5,-.0042284,-.01713,-.0021127,
	    -.0061876,0.0,0.0,0.0,3.3725e-10,2.3434e-10,-5.4793e-10,.0036913,
	    .0040656,.0052857,0.0,0.0,0.0,.0014911,3.944e-4,-8.4581e-4,
	    -3.4739e-4,2.7334e-4,-.0014054,0.0,0.0,0.0,.0087638,.0088034,
	    .011288,8.7815e-4,-.0021757,-.0041018,0.0,0.0,0.0,4.5218e-10,
	    1.188e-9,-5.9374e-10,.0055685,.002767,-3.0424e-4,0.0,0.0,0.0,
	    3.2066e-4,.0021945,-7.3269e-4,-.0012357,-4.2398e-5,3.4306e-4,0.0,
	    0.0,0.0,-.0036726,-.004336,-.0016501,-.021451,-.012504,-.0064164,
	    0.0,0.0,0.0,1.0395e-10,1.1249e-10,1.2251e-10,.0025966,5.5083e-4,
	    3.4624e-4,0.0,0.0,0.0,.0029062,6.2337e-4,8.1305e-4,-.0082735,
	    -.0063574,-.0035857,0.0,0.0,0.0,2.783e-10,-9.1034e-11,-3.6491e-10,
	    .0026567,.0019005,.0015636,0.0,0.0,0.0,-.0037388,-.0024846,
	    -.001568,-.017557,-.014233,-.0060995,0.0,0.0,0.0,.0033715,
	    .0033931,-4.4728e-5,-.0037272,-.0028291,-.0055164 };

    /* Builtin functions */
    double d_lg10(doublereal *), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal nneh, nnel;
    extern /* Subroutine */ int nelow_(integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *), nehigh_(
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, integer *, doublereal *
	    , doublereal *);

/* Version 1.0 (released 30.6.2004) */
/* CALNE calculates electron density in the outer */
/* ionosphere with account of solar activity (F107 index). */
/* CALNE uses subroutines NELOW and NEHIGH. */
/* Linearly interpolates for solar activity. */
/* Inputs: CRD - 0 .. INVDIP */
/*               1 .. FL, DIMO, B0, DIPL (used for calculation INVDIP inside) */
/*         INVDIP - "mix" coordinate of the dip latitude and of */
/*                    the invariant latitude; */
/*                    positive northward, in deg, range <-90.0;90.0> */
/*         FL, DIMO, BO - McIlwain L parameter, dipole moment in */
/*                        Gauss, magnetic field strength in Gauss - */
/*                        parameters needed for invariant latitude */
/*                        calculation */
/*         DIPL - dip latitude */
/*                positive northward, in deg, range <-90.0;90.0> */
/*         MLT - magnetic local time (central dipole) */
/*               in hours, range <0;24) */
/*         ALT - altitude above the Earth's surface; */
/*               in km, range <350;2000> */
/*         DDD - day of year; range <0;365> */
/*         F107 - F107 index */
/* Output: NNE - electron density [m-3] */
/* Versions:  1.0 FORTRAN */
/* Author of the code: */
/*         Vladimir Truhlik */
/*         Institute of Atm. Phys. */
/*         Bocni II. */
/*         141 31 Praha 4, Sporilov */
/*         Czech Republic */
/*         e-mail: vtr@ufa.cas.cz */
/*         tel/fax: +420 267103058 */
/* /////////////////////coefficients high solar activity//////////////////////// */
/* //////////////////////////////////NE///////////////////////////////////////// */
/*     550km equinox */
/*     550km June solstice */
/*     900km equinox */
/*     900km June solstice */
/*     1500km equinox */
/*     1500km June solstice */
/*     2400km equinox */
/*     2400km June solstice */
/* //////////////////////////////////////////////////////////////////////////////////// */
/* /////////////////////coefficients low solar activity//////////////////////////////// */
/* //////////////////////////////////Ne//////////////////////////////////////////////// */
/*     400km equinox */
/*     400km June solstice */
/*     650km equinox */
/*     650km June solstice */
/*     1000km equinox */
/*     1000km June solstice */
/* //////////////////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////solar minimum//////////////////////////////////////// */
    nelow_(crd, invdip, fl, dimo, b0, dipl, mlt, alt, ddd, dnel, &nnel);
/* ///////////////////////////////solar maximum//////////////////////////////////////// */
    nehigh_(crd, invdip, fl, dimo, b0, dipl, mlt, alt, ddd, dneh, &nneh);
/*     interpolation (in logarithm) */
    *nne = (d_lg10(&nneh) - d_lg10(&nnel)) / 115. * (*f107 - 85.) + d_lg10(&
	    nnel);
    *nne = pow_dd(&c_b30, nne);
    return 0;
} /* calne_ */

#undef dneh


/* Subroutine */ int nelow_(integer *crd, doublereal *invdip, doublereal *fl, 
	doublereal *dimo, doublereal *b0, doublereal *dipl, doublereal *mlt, 
	doublereal *alt, integer *ddd, doublereal *d__, doublereal *nne)
{
    /* Initialized data */

    static integer mirreq[49] = { 1,-1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,
	    -1,1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1,1,-1,
	    1,-1,1,1 };

    /* Builtin functions */
    double log(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c__[49];
    static integer i__;
    extern /* Subroutine */ int spharm_ik__(doublereal *, integer *, integer *
	    , doublereal *, doublereal *);
    static doublereal aa, bb, ah[3], st[2], n400, n650, st1, st2, n1000, ano[
	    3], dno[1], sum, n100a, n100b, n400a, n400b, n650a, n650b;
    static integer ddda, dddb, dddd;
    static doublereal n0a100, n0b100, n0a400, n0b400, n0a650, n0b650;
    static integer seza, sezb;
    static doublereal dtor;
    extern doublereal eptr_(doublereal *, doublereal *, doublereal *);
    static doublereal rmlt;
    static integer sezai, sezbi;
    static doublereal invdp;
    extern doublereal invdpc_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal rcolat;

/* NELOW calculates electron density in the outer */
/* ionosphere for a low solar activity (F107 < 100). */
/* Based on spherical harmonics approximation of electron ion density */
/* (by AE-C, AE-D, and AE-E) at altitudes centred on 400km, 650km, and 1000km. */
/* For intermediate altitudes an interpolation is used. */
/* Recommended altitude range: 350-2000 km!!! */
/* For days between seasons centred at (21.3. = 79; 21.6. = 171; */
/* 23.9. 265; 21.12. = 354) relative ion density is linearly interpolated. */
/* Inputs: CRD - 0 .. INVDIP */
/*               1 .. FL, DIMO, B0, DIPL (used for calculation INVDIP inside) */
/*         INVDIP - "mix" coordinate of the dip latitude and of */
/*                    the invariant latitude; */
/*                    positive northward, in deg, range <-90.0;90.0> */
/*         FL, DIMO, BO - McIlwain L parameter, dipole moment in */
/*                        Gauss, magnetic field strength in Gauss - */
/*                        parameters needed for invariant latitude */
/*                        calculation */
/*         DIPL - dip latitude */
/*                positive northward, in deg, range <-90.0;90.0> */
/*         MLT - magnetic local time (central dipole) */
/*               in hours, range <0;24) */
/*         ALT - altitude above the Earth's surface; */
/*               in km, range <350;2000> */
/*         DDD - day of year; range <0;365> */
/*         D - coefficints of spherical harmonics for a given ion */
/* Output: NNE - Ne density */
    /* Parameter adjustments */
    d__ -= 13;

    /* Function Body */
/* //////////////////////////////////////////////////////////////////////////////////// */
    dtor = .01745329252;
/*     coefficients for mirroring */
    for (i__ = 1; i__ <= 49; ++i__) {
	d__[(i__ * 3 + 3) * 3 + 1] = d__[(i__ * 3 + 2) * 3 + 1] * mirreq[i__ 
		- 1];
	d__[(i__ * 3 + 3) * 3 + 2] = d__[(i__ * 3 + 2) * 3 + 2] * mirreq[i__ 
		- 1];
/* L10: */
	d__[(i__ * 3 + 3) * 3 + 3] = d__[(i__ * 3 + 2) * 3 + 3] * mirreq[i__ 
		- 1];
    }
    if (*crd == 1) {
	invdp = invdpc_(fl, dimo, b0, dipl, &dtor);
    } else if (*crd == 0) {
	invdp = *invdip;
    } else {
	return 0;
    }
    rmlt = *mlt * dtor * 15.;
    rcolat = (90. - invdp) * dtor;
    spharm_ik__(c__, &c__6, &c__6, &rcolat, &rmlt);
/*     21.3. - 20.6. */
    if (*ddd >= 79 && *ddd < 171) {
	seza = 1;
	sezb = 2;
	ddda = 79;
	dddb = 171;
	dddd = *ddd;
    }
/*     21.6. - 22.9. */
    if (*ddd >= 171 && *ddd < 265) {
	seza = 2;
	sezb = 4;
	ddda = 171;
	dddb = 265;
	dddd = *ddd;
    }
/*     23.9. - 20.12. */
    if (*ddd >= 265 && *ddd < 354) {
	seza = 4;
	sezb = 3;
	ddda = 265;
	dddb = 354;
	dddd = *ddd;
    }
/*     21.12. - 20.3. */
    if (*ddd >= 354 || *ddd < 79) {
	seza = 3;
	sezb = 1;
	ddda = 354;
	dddb = 444;
	dddd = *ddd;
	if (*ddd >= 354) {
	    dddd = *ddd;
	} else {
	    dddd = *ddd + 365;
	}
    }
    sezai = (seza - 1) % 3 + 1;
    sezbi = (sezb - 1) % 3 + 1;
/*     400km level */
    n0a400 = 0.;
    n0b400 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a400 += c__[i__ - 1] * d__[(sezai + i__ * 3) * 3 + 1];
/* L30: */
	n0b400 += c__[i__ - 1] * d__[(sezbi + i__ * 3) * 3 + 1];
    }
    n400a = n0a400;
    n400b = n0b400;
    n400 = (n400b - n400a) / (dddb - ddda) * (dddd - ddda) + n400a;
/*     650km level */
    n0a650 = 0.;
    n0b650 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a650 += c__[i__ - 1] * d__[(sezai + i__ * 3) * 3 + 2];
/* L70: */
	n0b650 += c__[i__ - 1] * d__[(sezbi + i__ * 3) * 3 + 2];
    }
    n650a = n0a650;
    n650b = n0b650;
    n650 = (n650b - n650a) / (dddb - ddda) * (dddd - ddda) + n650a;
/*     1000km level */
    n0a100 = 0.;
    n0b100 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a100 += c__[i__ - 1] * d__[(sezai + i__ * 3) * 3 + 3];
/* L110: */
	n0b100 += c__[i__ - 1] * d__[(sezbi + i__ * 3) * 3 + 3];
    }
    n100a = n0a100;
    n100b = n0b100;
    n1000 = (n100b - n100a) / (dddb - ddda) * (dddd - ddda) + n100a;
/*      IF (ALT .LT. 650) NO=(N650-N400)/250.0*(ALT-400)+N400 */
/*      IF (ALT .GE. 650) NO=(N1000-N650)/350.0*(ALT-650)+N650 */
/*      NION=10**NO */
    ano[0] = n400;
    ano[1] = n650;
    ano[2] = n1000;
    ah[0] = 400.;
    ah[1] = 650.;
    ah[2] = 1e3;
    dno[0] = 20.;
    st1 = (ano[1] - ano[0]) / (ah[1] - ah[0]);
    i__ = 2;
    st2 = (ano[i__] - ano[i__ - 1]) / (ah[i__] - ah[i__ - 1]);
    ano[i__ - 1] -= (st2 - st1) * dno[i__ - 2] * log(2.);
    for (i__ = 1; i__ <= 2; ++i__) {
/* L220: */
	st[i__ - 1] = (ano[i__] - ano[i__ - 1]) / (ah[i__] - ah[i__ - 1]);
    }
    argexp_1.argmax = 88.;
    sum = ano[0] + st[0] * (*alt - ah[0]);
    i__ = 1;
    aa = eptr_(alt, &dno[i__ - 1], &ah[i__]);
    bb = eptr_(ah, &dno[i__ - 1], &ah[i__]);
    sum += (st[i__] - st[i__ - 1]) * (aa - bb) * dno[i__ - 1];
    *nne = pow_dd(&c_b30, &sum);
    return 0;
} /* nelow_ */

/* Subroutine */ int nehigh_(integer *crd, doublereal *invdip, doublereal *fl,
	 doublereal *dimo, doublereal *b0, doublereal *dipl, doublereal *mlt, 
	doublereal *alt, integer *ddd, doublereal *d__, doublereal *nne)
{
    /* Initialized data */

    static integer mirreq[49] = { 1,-1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,
	    -1,1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1,1,-1,
	    1,-1,1,1 };

    /* Builtin functions */
    double log(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c__[49];
    static integer i__;
    extern /* Subroutine */ int spharm_ik__(doublereal *, integer *, integer *
	    , doublereal *, doublereal *);
    static doublereal aa, bb, ah[4], st[3], n900, n550, st1, st2, n1500, 
	    n2500, ano[4], dno[2], sum, n150a, n150b, n250a, n900a, n550a, 
	    n550b, n900b, n250b;
    static integer ddda, dddb, dddd;
    static doublereal n0a150, n0b150, n0a250, n0a900, n0a550, n0b550, n0b900, 
	    n0b250;
    static integer seza, sezb;
    static doublereal dtor;
    extern doublereal eptr_(doublereal *, doublereal *, doublereal *);
    static doublereal rmlt;
    static integer sezai, sezbi;
    static doublereal invdp;
    extern doublereal invdpc_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal rcolat;

/* NEHIGH calculates electron density in the outer */
/* ionosphere for high solar activity (F107 >= 150). */
/* Based on spherical harmonics approximation of electron density */
/* (by IK24 and IK25) at altitudes centred on 550km, 900km, 1500km, and 2400km. */
/* For intermediate altitudes a interpolation is used. */
/* Recommended altitude range: 500-3000 km!!! */
/* For days between seasons centred at (21.3. = 79; 21.6. = 171; */
/* 23.9. 265; 21.12. = 354) relative ion density is linearly interpolated. */
/* Inputs: CRD - 0 .. INVDIP */
/*               1 .. FL, DIMO, B0, DIPL (used for calculation INVDIP inside) */
/*         INVDIP - "mix" coordinate of the dip latitude and of */
/*                    the invariant latitude; */
/*                    positive northward, in deg, range <-90.0;90.0> */
/*         FL, DIMO, BO - McIlwain L parameter, dipole moment in */
/*                        Gauss, magnetic field strength in Gauss - */
/*                        parameters needed for invariant latitude */
/*                        calculation */
/*         DIPL - dip latitude */
/*                positive northward, in deg, range <-90.0;90.0> */
/*         MLT - magnetic local time (central dipole) */
/*               in hours, range <0;24) */
/*         ALT - altitude above the Earth's surface; */
/*               in km, range <500;3000> */
/*         DDD - day of year; range <0;365> */
/*         D - coefficints of spherical harmonics for a given ion */
/* Output: NNE - electron density [m-3] */
    /* Parameter adjustments */
    d__ -= 17;

    /* Function Body */
/* //////////////////////////////////////////////////////////////////////////////////// */
    dtor = .01745329252;
/*     coefficients for mirroring */
    for (i__ = 1; i__ <= 49; ++i__) {
	d__[(i__ * 3 + 3 << 2) + 1] = d__[(i__ * 3 + 2 << 2) + 1] * mirreq[
		i__ - 1];
	d__[(i__ * 3 + 3 << 2) + 2] = d__[(i__ * 3 + 2 << 2) + 2] * mirreq[
		i__ - 1];
	d__[(i__ * 3 + 3 << 2) + 3] = d__[(i__ * 3 + 2 << 2) + 3] * mirreq[
		i__ - 1];
/* L10: */
	d__[(i__ * 3 + 3 << 2) + 4] = d__[(i__ * 3 + 2 << 2) + 4] * mirreq[
		i__ - 1];
    }
    if (*crd == 1) {
	invdp = invdpc_(fl, dimo, b0, dipl, &dtor);
    } else if (*crd == 0) {
	invdp = *invdip;
    } else {
	return 0;
    }
    rmlt = *mlt * dtor * 15.;
    rcolat = (90. - invdp) * dtor;
    spharm_ik__(c__, &c__6, &c__6, &rcolat, &rmlt);
/*     21.3. - 20.6. */
    if (*ddd >= 79 && *ddd < 171) {
	seza = 1;
	sezb = 2;
	ddda = 79;
	dddb = 171;
	dddd = *ddd;
    }
/*     21.6. - 22.9. */
    if (*ddd >= 171 && *ddd < 265) {
	seza = 2;
	sezb = 4;
	ddda = 171;
	dddb = 265;
	dddd = *ddd;
    }
/*     23.9. - 20.12. */
    if (*ddd >= 265 && *ddd < 354) {
	seza = 4;
	sezb = 3;
	ddda = 265;
	dddb = 354;
	dddd = *ddd;
    }
/*     21.12. - 20.3. */
    if (*ddd >= 354 || *ddd < 79) {
	seza = 3;
	sezb = 1;
	ddda = 354;
	dddb = 444;
	dddd = *ddd;
	if (*ddd >= 354) {
	    dddd = *ddd;
	} else {
	    dddd = *ddd + 365;
	}
    }
    sezai = (seza - 1) % 3 + 1;
    sezbi = (sezb - 1) % 3 + 1;
/*     550km level */
    n0a550 = 0.;
    n0b550 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a550 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) + 1];
/* L30: */
	n0b550 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) + 1];
    }
    n550a = n0a550;
    n550b = n0b550;
    n550 = (n550b - n550a) / (dddb - ddda) * (dddd - ddda) + n550a;
/*     900km level */
    n0a900 = 0.;
    n0b900 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a900 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) + 2];
/* L70: */
	n0b900 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) + 2];
    }
    n900a = n0a900;
    n900b = n0b900;
    n900 = (n900b - n900a) / (dddb - ddda) * (dddd - ddda) + n900a;
/*     1500km level */
    n0a150 = 0.;
    n0b150 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a150 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) + 3];
/* L110: */
	n0b150 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) + 3];
    }
    n150a = n0a150;
    n150b = n0b150;
    n1500 = (n150b - n150a) / (dddb - ddda) * (dddd - ddda) + n150a;
/*     2500km level */
    n0a250 = 0.;
    n0b250 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a250 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) + 4];
/* L150: */
	n0b250 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) + 4];
    }
    n250a = n0a250;
    n250b = n0b250;
    n2500 = (n250b - n250a) / (dddb - ddda) * (dddd - ddda) + n250a;
/*      IF (ALT .LT. 900) NO=(N900-N550)/350.0*(ALT-550)+N550 */
/*      IF ((ALT .GE. 900) .AND. (ALT .LT. 1500)) */
/*     &  NO=(N1500-N900)/600.0*(ALT-900)+N900 */
/*      IF (ALT .GE. 1500) NO=(N2500-N1500)/1000.0*(ALT-1500)+N1500 */
    ano[0] = n550;
    ano[1] = n900;
    ano[2] = n1500;
    ano[3] = n2500;
    ah[0] = 550.;
    ah[1] = 900.;
    ah[2] = 1500.;
    ah[3] = 2250.;
    dno[0] = 20.;
    dno[1] = 20.;
    st1 = (ano[1] - ano[0]) / (ah[1] - ah[0]);
    for (i__ = 2; i__ <= 3; ++i__) {
	st2 = (ano[i__] - ano[i__ - 1]) / (ah[i__] - ah[i__ - 1]);
	ano[i__ - 1] -= (st2 - st1) * dno[i__ - 2] * log(2.);
/* L200: */
	st1 = st2;
    }
    for (i__ = 1; i__ <= 3; ++i__) {
/* L220: */
	st[i__ - 1] = (ano[i__] - ano[i__ - 1]) / (ah[i__] - ah[i__ - 1]);
    }
    argexp_1.argmax = 88.;
    sum = ano[0] + st[0] * (*alt - ah[0]);
    for (i__ = 1; i__ <= 2; ++i__) {
	aa = eptr_(alt, &dno[i__ - 1], &ah[i__]);
	bb = eptr_(ah, &dno[i__ - 1], &ah[i__]);
/* L230: */
	sum += (st[i__] - st[i__ - 1]) * (aa - bb) * dno[i__ - 1];
    }
    *nne = pow_dd(&c_b30, &sum);
    return 0;
} /* nehigh_ */



/* ********************************************************** */
/* ***************** ELECTRON TEMPERATURE ******************** */
/* ********************************************************** */

/* Subroutine */ int elteik_(integer *crd, integer *f107y, integer *seasy, 
	doublereal *invdip, doublereal *fl, doublereal *dimo, doublereal *b0, 
	doublereal *dipl, doublereal *mlt, doublereal *alt, integer *ddd, 
	doublereal *f107, doublereal *te, doublereal *sigte)
{
    /* Initialized data */

    static doublereal b[8] = { 1.259921,-.1984259,-.04686632,-.01314096,
	    -.00308824,8.2777e-4,-.00105877,.00183142 };
    static integer mirreq[81] = { 1,-1,1,-1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,
	    -1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,1,-1,1,-1,1,
	    -1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,
	    -1,1,1,-1,1,1,-1,1,-1,1,1 };
    static struct {
	doublereal e_1[8];
	doublereal fill_2[4];
	doublereal e_3[8];
	doublereal fill_4[4];
	doublereal e_5[8];
	doublereal fill_6[4];
	doublereal e_7[8];
	doublereal fill_8[4];
	doublereal e_9[8];
	doublereal fill_10[4];
	doublereal e_11[8];
	doublereal fill_12[4];
	doublereal e_13[8];
	doublereal fill_14[4];
	doublereal e_15[8];
	doublereal fill_16[4];
	doublereal e_17[8];
	doublereal fill_18[4];
	doublereal e_19[8];
	doublereal fill_20[4];
	doublereal e_21[8];
	doublereal fill_22[4];
	doublereal e_23[8];
	doublereal fill_24[4];
	doublereal e_25[8];
	doublereal fill_26[4];
	doublereal e_27[8];
	doublereal fill_28[4];
	doublereal e_29[8];
	doublereal fill_30[4];
	doublereal e_31[8];
	doublereal fill_32[4];
	doublereal e_33[8];
	doublereal fill_34[4];
	doublereal e_35[8];
	doublereal fill_36[4];
	doublereal e_37[8];
	doublereal fill_38[4];
	doublereal e_39[8];
	doublereal fill_40[4];
	doublereal e_41[8];
	doublereal fill_42[4];
	doublereal e_43[8];
	doublereal fill_44[4];
	doublereal e_45[8];
	doublereal fill_46[4];
	doublereal e_47[8];
	doublereal fill_48[4];
	doublereal e_49[8];
	doublereal fill_50[4];
	doublereal e_51[8];
	doublereal fill_52[4];
	doublereal e_53[8];
	doublereal fill_54[4];
	doublereal e_55[8];
	doublereal fill_56[4];
	doublereal e_57[8];
	doublereal fill_58[4];
	doublereal e_59[8];
	doublereal fill_60[4];
	doublereal e_61[8];
	doublereal fill_62[4];
	doublereal e_63[8];
	doublereal fill_64[4];
	doublereal e_65[8];
	doublereal fill_66[4];
	doublereal e_67[8];
	doublereal fill_68[4];
	doublereal e_69[8];
	doublereal fill_70[4];
	doublereal e_71[8];
	doublereal fill_72[4];
	doublereal e_73[8];
	doublereal fill_74[4];
	doublereal e_75[8];
	doublereal fill_76[4];
	doublereal e_77[8];
	doublereal fill_78[4];
	doublereal e_79[8];
	doublereal fill_80[4];
	doublereal e_81[8];
	doublereal fill_82[4];
	doublereal e_83[8];
	doublereal fill_84[4];
	doublereal e_85[8];
	doublereal fill_86[4];
	doublereal e_87[8];
	doublereal fill_88[4];
	doublereal e_89[8];
	doublereal fill_90[4];
	doublereal e_91[8];
	doublereal fill_92[4];
	doublereal e_93[8];
	doublereal fill_94[4];
	doublereal e_95[8];
	doublereal fill_96[4];
	doublereal e_97[8];
	doublereal fill_98[4];
	doublereal e_99[8];
	doublereal fill_100[4];
	doublereal e_101[8];
	doublereal fill_102[4];
	doublereal e_103[8];
	doublereal fill_104[4];
	doublereal e_105[8];
	doublereal fill_106[4];
	doublereal e_107[8];
	doublereal fill_108[4];
	doublereal e_109[8];
	doublereal fill_110[4];
	doublereal e_111[8];
	doublereal fill_112[4];
	doublereal e_113[8];
	doublereal fill_114[4];
	doublereal e_115[8];
	doublereal fill_116[4];
	doublereal e_117[8];
	doublereal fill_118[4];
	doublereal e_119[8];
	doublereal fill_120[4];
	doublereal e_121[8];
	doublereal fill_122[4];
	doublereal e_123[8];
	doublereal fill_124[4];
	doublereal e_125[8];
	doublereal fill_126[4];
	doublereal e_127[8];
	doublereal fill_128[4];
	doublereal e_129[8];
	doublereal fill_130[4];
	doublereal e_131[8];
	doublereal fill_132[4];
	doublereal e_133[8];
	doublereal fill_134[4];
	doublereal e_135[8];
	doublereal fill_136[4];
	doublereal e_137[8];
	doublereal fill_138[4];
	doublereal e_139[8];
	doublereal fill_140[4];
	doublereal e_141[8];
	doublereal fill_142[4];
	doublereal e_143[8];
	doublereal fill_144[4];
	doublereal e_145[8];
	doublereal fill_146[4];
	doublereal e_147[8];
	doublereal fill_148[4];
	doublereal e_149[8];
	doublereal fill_150[4];
	doublereal e_151[8];
	doublereal fill_152[4];
	doublereal e_153[8];
	doublereal fill_154[4];
	doublereal e_155[8];
	doublereal fill_156[4];
	doublereal e_157[8];
	doublereal fill_158[4];
	doublereal e_159[8];
	doublereal fill_160[4];
	doublereal e_161[8];
	doublereal fill_162[4];
	} equiv_192 = { 2118.5, 2625.3, 2922.8, 3373.8, 2073.2, 2596.4, 
		2962.1, 3289., {0}, -.9096, -1.4102, -1.0193, -.14579, 118.58,
		 273.69, 396.88, 234.06, {0}, 874.79, 1057.8, 500.52, 290.57, 
		703.41, 718.93, 296.52, 232.42, {0}, .53665, .60533, 1.9156, 
		-.89423, 406.06, 447.51, 277.82, 168.45, {0}, 72.315, -201.22,
		 -88.798, -178.18, -154.1, -389.08, -135., -379.64, {0}, 
		-1.4522, -2.5531, 4.4598, 1.3821, 59.091, 6.4097, -28.285, 
		-23.183, {0}, -68.231, -98.647, 22.407, -89.134, -73.198, 
		-50.443, 18.036, -67.725, {0}, -.17205, 1.5826, 2.305, 
		-.31758, -100.67, 79.006, -82.958, 98.597, {0}, -95.868, 
		-140.76, -3.8484, -67.731, -70.712, -95.54, -39.738, 28.565, {
		0}, -537.4, -917.64, -1295.9, -1437.2, -633.23, -981.62, 
		-1205.8, -1370.5, {0}, -.55762, .52004, -.8733, .062781, 
		47.818, 9.4112, 68.198, 75.544, {0}, -137., -101.94, 27.027, 
		46.214, -76.003, -39.071, 22.164, 132.35, {0}, -.6688, 
		-.53743, -.60724, -.040312, -49.778, -12.918, -15.473, .19927,
		 {0}, -.64616, 46.185, 28.496, -7.0553, 67.586, 60.87, 19.76, 
		-1.3429, {0}, -.014436, .30271, -.52927, -.057943, -7.3829, 
		23.039, 13.793, -.98459, {0}, -13.574, -16.661, 5.7042, 
		-15.921, -7.0501, -31.332, -22.13, -1.7632, {0}, -.0051068, 
		-.43778, -.25504, .07697, 13.663, 8.3557, 2.2585, -4.2301, {0}
		, 191.76, 276.36, -39.328, -53.597, 126.61, 131., -95.227, 
		-211.62, {0}, -.35708, .099112, 1.8577, -3.2922, -49.014, 
		-32.576, -79.347, .55279, {0}, -16.8, -27.807, 25.325, 
		-57.514, -44.884, -96.546, -18.617, -95.367, {0}, .53899, 
		-.36236, 1.057, -2.2513, -27.004, 5.8694, -14.626, -12.788, {
		0}, 27.73, 92.38, 39.141, 27.316, -5.4925, 71.925, 28.497, 
		40.782, {0}, .21264, .55131, .012857, -.49774, -14.39, 10.059,
		 9.7753, 4.8734, {0}, -1.1162, -5.7407, 4.4854, 10.223, 
		14.573, -9.7102, 5.1487, -5.0869, {0}, -.2102, .12985, 
		-1.0437, .15541, 14.89, -.18709, -3.0464, -4.8522, {0}, 
		-470.27, -514.8, -491.04, -510.8, -222.43, -398.06, -503.02, 
		-525.66, {0}, -.22692, -.32325, -.062939, .15422, 46.961, 
		-30.957, 32.524, 60.198, {0}, -8.4973, -42.135, -41.205, 
		-26.147, 21.169, -7.8514, -6.2727, -20.405, {0}, -.12278, 
		.04636, .3222, .4506, .63799, 2.9864, -2.7864, 30.107, {0}, 
		4.92, -.47321, -10.599, .77452, -1.4838, 4.7169, 4.3374, 
		1.9692, {0}, -.014939, -.20887, -.18242, -.03268, 6.6321, 
		-6.3766, -1.0944, 4.2044, {0}, 2.6356, -2.3466, .9116, 
		-.74846, .41318, 4.5467, 1.0615, -1.6327, {0}, -93.732, 
		-341.32, -354.25, -213.99, -156.42, -217.13, -149.55, -111.21,
		 {0}, .17524, -.81632, -.16068, -1.0117, 113., 27.924, 4.5911,
		 -35.375, {0}, -8.027, 20.252, -1.3725, 15.173, -8.9014, 
		6.9898, 13.417, 5.2049, {0}, .048917, .31349, .096252, 
		-.72407, -4.9933, 6.4391, -3.8776, 15.725, {0}, 4.1404, 
		-3.2548, 6.6323, 3.2157, 7.3107, -2.9495, -.08603, 10.054, {0}
		, .21455, -.02972, .10111, -.09554, 9.4305, 1.3537, 4.9763, 
		3.7913, {0}, .65988, -2.512, 1.5864, 2.0921, -1.5203, 3.0092, 
		1.7831, -.16254, {0}, 239.73, 312.81, 266.98, 338.03, 193.25, 
		246.62, 285.93, 149.83, {0}, .0067066, -.044738, -.13164, 
		.32007, -22.07, -4.3575, -41.944, -40.229, {0}, 32.942, 4.413,
		 25.957, -25.597, -6.2284, -8.7582, 2.543, 1.9216, {0}, 
		.10491, -.031125, .18661, -.018768, -.10572, -5.6902, 4.1294, 
		-2.5669, {0}, -1.1019, 1.3784, .95289, -4.3258, -3.6677, 
		-1.844, 5.5434, -1.3679, {0}, -.0089674, .041569, .12827, 
		-.094149, -6.1689, 2.0276, 2.1086, 1.9556, {0}, -258.71, 
		-109.8, -20.802, -112.74, -68.242, -154.56, -79.921, -52.991, 
		{0}, -.40511, .70001, -.50001, -.55848, -29.507, -4.1566, 
		8.916, 12.377, {0}, 18.509, 4.0861, 1.7802, -19.836, 13.496, 
		1.594, -14.931, -18.352, {0}, -.06559, -.1667, -.22686, 
		-.19519, 7.9801, -2.261, 6.7306, -.27843, {0}, 3.3369, -4.852,
		 -.99243, -2.95, -1.7483, -1.879, -7.4849, -2.6711, {0}, 
		-.014607, .036492, -.088453, -.065675, .42264, -.20589, 
		2.0152, 1.027, {0}, 193.45, 180.57, 169.38, 275.06, 132.32, 
		166.12, 244.35, -17.185, {0}, .45946, .20765, .15072, 
		-.094098, 9.753, -2.8783, -27.216, -1.0283, {0}, -17.988, 
		8.8382, -1.2249, 18.588, -3.3159, -.097839, -6.5424, -13.286, 
		{0}, .065776, -.028354, .0059212, -.1546, -3.8368, .71863, 
		-.22848, 1.4314, {0}, -1.7171, -1.634, 2.1008, .81344, .73997,
		 .224, .6678, -.53584, {0}, 32.232, 174.92, 149.81, 184.79, 
		127.38, 89.569, -5.021, -67.809, {0}, -.13975, -.70915, 
		-.030983, -.39938, .43677, -8.7802, -1.6876, -9.6756, {0}, 
		-7.9626, 9.6069, -2.3113, 13.448, -.43172, -2.9563, -3.8484, 
		-4.6022, {0}, -.089984, .12205, -.016773, .088669, 3.2624, 
		-1.5339, .48596, 1.8112, {0}, -.52076, .37218, .50314, 3.904, 
		.24603, -.69508, 1.2499, -.0061062, {0}, -67.466, -57.398, 
		-28.87, -53.105, -152.97, -89.068, -128.23, 26.33, {0}, 
		-.024359, -.29121, -.12562, .20753, .3813, 2.4977, -4.7155, 
		16.726, {0}, 1.2132, -4.3088, 5.5983, -3.5771, -5.6753, 
		.56978, -8.9457, 3.9444, {0}, -9.7418e-4, .056543, .036513, 
		-.014386, -.17841, 1.0112, -.26414, 2.7303, {0}, 166.62, 
		60.417, -32.056, 133.06, 14.078, 107.25, -10.88, 47.634, {0}, 
		.30197, .25141, -.35823, .22388, 8.1371, -8.8621, 17.04, 
		-32.729, {0}, .3487, 2.2588, -.71938, -.43013, -1.0298, 
		-4.8559, -1.3495, 1.2863, {0}, .0020862, -.065538, -.030424, 
		.058347, -.87611, -.85244, .046478, -.87681, {0}, -100.91, 
		-160.84, -59.756, -72.119, 18.043, -62.185, -55.357, 5.8417, {
		0}, -.11583, .32163, -.31999, .0015187, -20.388, 7.2504, 
		29.895, -11.842, {0}, -.64353, -3.5354, .38169, 2.1445, 
		3.5874, 1.8318, -2.6035, 1.7747, {0}, -45.914, -39.077, 
		57.626, 1.5871, -68.187, -79.203, -3.7697, 49.485, {0}, 
		-.29075, -.044285, .34086, .34653, 12.396, 2.8472, -5.3693, 
		-9.5141, {0}, -1.3476, -3.4426, 5.0895, 1.8858, 1.4384, 
		-.13483, .53346, -1.7739, {0}, -25.206, 26.798, 1.2152, 
		11.009, -18.542, 21.818, 14.172, 28.452, {0}, .055027, 
		.067368, .14523, -.10913, 9.8107, -4.2387, 5.3848, -8.8851, {
		0}, -106.63, -67.479, -60.723, .13126, -1.7652, -57.925, 
		-23.065, -4.4171, {0}, .13394, .098125, -.015587, .16358, 
		-10.545, 2.5552, -5.2616, 4.1421, {0}, 27.825, 70.079, 52.597,
		 33.089, 12.793, 46.6, 22.592, -26.145, {0}, 33.973, 21.724, 
		-6.7261, 49.158, 24.878, 34.333, -15.174, -44.075 };

#define d__ ((doublereal *)&equiv_192)

    static integer mf107[49] = { 1,-1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,
	    -1,1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1,1,-1,
	    1,-1,1,1 };
    static struct {
	doublereal e_1[8];
	doublereal fill_2[4];
	doublereal e_3[8];
	doublereal fill_4[4];
	doublereal e_5[8];
	doublereal fill_6[4];
	doublereal e_7[8];
	doublereal fill_8[4];
	doublereal e_9[8];
	doublereal fill_10[4];
	doublereal e_11[8];
	doublereal fill_12[4];
	doublereal e_13[8];
	doublereal fill_14[4];
	doublereal e_15[8];
	doublereal fill_16[4];
	doublereal e_17[8];
	doublereal fill_18[4];
	doublereal e_19[8];
	doublereal fill_20[4];
	doublereal e_21[8];
	doublereal fill_22[4];
	doublereal e_23[8];
	doublereal fill_24[4];
	doublereal e_25[8];
	doublereal fill_26[4];
	doublereal e_27[8];
	doublereal fill_28[4];
	doublereal e_29[8];
	doublereal fill_30[4];
	doublereal e_31[8];
	doublereal fill_32[4];
	doublereal e_33[8];
	doublereal fill_34[4];
	doublereal e_35[8];
	doublereal fill_36[4];
	doublereal e_37[8];
	doublereal fill_38[4];
	doublereal e_39[8];
	doublereal fill_40[4];
	doublereal e_41[8];
	doublereal fill_42[4];
	doublereal e_43[8];
	doublereal fill_44[4];
	doublereal e_45[8];
	doublereal fill_46[4];
	doublereal e_47[8];
	doublereal fill_48[4];
	doublereal e_49[8];
	doublereal fill_50[4];
	doublereal e_51[8];
	doublereal fill_52[4];
	doublereal e_53[8];
	doublereal fill_54[4];
	doublereal e_55[8];
	doublereal fill_56[4];
	doublereal e_57[8];
	doublereal fill_58[4];
	doublereal e_59[8];
	doublereal fill_60[4];
	doublereal e_61[8];
	doublereal fill_62[4];
	doublereal e_63[8];
	doublereal fill_64[4];
	doublereal e_65[8];
	doublereal fill_66[4];
	doublereal e_67[8];
	doublereal fill_68[4];
	doublereal e_69[8];
	doublereal fill_70[4];
	doublereal e_71[8];
	doublereal fill_72[4];
	doublereal e_73[8];
	doublereal fill_74[4];
	doublereal e_75[8];
	doublereal fill_76[4];
	doublereal e_77[8];
	doublereal fill_78[4];
	doublereal e_79[8];
	doublereal fill_80[4];
	doublereal e_81[8];
	doublereal fill_82[4];
	doublereal e_83[8];
	doublereal fill_84[4];
	doublereal e_85[8];
	doublereal fill_86[4];
	doublereal e_87[8];
	doublereal fill_88[4];
	doublereal e_89[8];
	doublereal fill_90[4];
	doublereal e_91[8];
	doublereal fill_92[4];
	doublereal e_93[8];
	doublereal fill_94[4];
	doublereal e_95[8];
	doublereal fill_96[4];
	doublereal e_97[8];
	doublereal fill_98[4];
	} equiv_193 = { 2.1792, 3.3758, 1.478, 1.4513, 3.2236, 1.7678, 1.3888,
		 .86854, {0}, -2.1275e-7, -4.8705e-7, -5.4689e-9, -2.7903e-8, 
		.7858, -.12523, 1.1103, -.099343, {0}, -.30369, -1.4844, 
		-.35681, -2.1232, .040518, -.031971, 1.6445, .017241, {0}, 
		-3.1861e-7, -7.914e-7, 3.569e-7, 1.2079e-7, -.078758, -1.1885,
		 .73508, .41379, {0}, -.40109, -1.201, 1.4442, .28524, 
		-.74039, -.20748, .099423, 1.0034, {0}, -2.3529e-7, 
		-4.3759e-7, -1.8771e-7, -4.0135e-8, -.55023, -.62911, -.12668,
		 -.71819, {0}, -.518, -.61125, -.58029, .68231, .22661, 
		-.69839, 1.1793, -1.0619, {0}, -.021268, -2.4395, .63736, 
		.435, -.17191, .14225, .32611, -.44765, {0}, 6.5788e-11, 
		8.4646e-9, 8.5859e-8, 1.2651e-8, -.45161, .029845, -.13932, 
		-1.0826, {0}, .32767, .50103, 1.7747, .56992, .077189, 
		-.074911, .34714, -6.5641e-4, {0}, -3.9204e-8, 1.5398e-9, 
		-1.896e-7, -4.285e-8, .024208, .1808, -.040398, -.23379, {0}, 
		.0060337, .1914, -.0096585, .15039, .075019, -.0013199, 
		.28188, -.41201, {0}, 1.8103e-9, 4.5214e-8, -7.3912e-9, 
		-1.3229e-8, .0054542, -.11076, -.2184, .082089, {0}, -.031331,
		 2.2253, -.67418, .09429, 1.8923, -.0055801, .30676, 2.2647, {
		0}, 1.3981e-8, -7.6345e-8, -2.0098e-8, -2.4997e-8, -.86309, 
		-.63437, .16201, -.10331, {0}, .48055, -.95472, -.23251, 
		-.77275, -.073536, .19093, -.14507, .13969, {0}, -3.5571e-8, 
		6.7707e-8, 4.3772e-8, 5.429e-8, -.1541, .12925, .33787, 
		.34386, {0}, .09851, .0053013, .086224, -.12859, -.12294, 
		.08625, -.04693, -.14873, {0}, 3.0118e-9, -5.0649e-8, 
		1.5699e-8, 9.4636e-9, -.11886, .17273, .054924, .048438, {0}, 
		-.077406, -.58881, .30123, .52854, -2.0559, -.1501, .39874, 
		-.22364, {0}, 1.4673e-8, 1.1959e-8, -2.8897e-8, -2.1479e-9, 
		-.04364, -.12204, .06987, .0033408, {0}, -.11584, .031184, 
		-.10286, .092855, -.22578, .047007, .023651, -.057226, {0}, 
		2.6239e-8, -2.4972e-9, 7.3823e-9, -2.7594e-8, .0063167, 
		.058541, -.10188, -.087379, {0}, -.037815, -.0044759, .035984,
		 .0074358, .058175, .0069108, .031284, .10073, {0}, -.75343, 
		-1.9022, .99977, -.45033, -.55051, .33109, 1.0411, .16683, {0}
		, -4.5728e-9, 3.8763e-9, -2.5975e-8, -7.4883e-10, -.30664, 
		.1405, -.41114, -.13735, {0}, -.22223, -.10882, .022399, 
		-.039305, -.049306, .08014, -.10548, .019385, {0}, -1.0071e-9,
		 3.0299e-8, -1.5372e-8, 2.2454e-8, .052511, -.034096, 
		-.023342, -.027082, {0}, -.068871, -.034453, .029522, 
		-.044181, .014045, -.0083293, .0091528, .031018, {0}, 
		-.088247, .13296, .11931, .053266, .22313, -.10468, .092067, 
		.067087, {0}, 6.3637e-9, 3.1168e-8, -4.4525e-9, 8.3007e-9, 
		.19961, .1078, -.10666, -.0079098, {0}, .037528, .014878, 
		.041555, -.018869, -.0089555, -.023355, .026649, .047972, {0},
		 -1.4578e-9, -8.3137e-9, 5.0431e-9, 2.7783e-10, -.04083, 
		.021534, -.037639, -.043783, {0}, .086601, -.47944, .066187, 
		-.052278, -.74402, .05951, -.18572, .31339, {0}, 4.082e-8, 
		-2.8746e-8, 1.3181e-8, 2.5128e-8, -.03452, .0043653, -.066661,
		 .041214, {0}, .13803, .035825, .061906, .056681, -.11823, 
		-.022744, .094229, .0081151, {0}, 6.0607e-9, -1.2058e-8, 
		-8.3984e-10, 3.031e-9, -.04151, .042113, .03184, -.027117, {0}
		, -.028557, .30506, .058869, -.11503, .12895, -.078295, 
		.0058198, .031667, {0}, -4.8644e-9, -9.5413e-9, -9.2211e-9, 
		3.5058e-8, .038704, -.042225, .0048141, -.013346, {0}, 
		.0015314, .0071259, -.0078035, .020314, .0053682, -.0019368, 
		.0094962, .0082864, {0}, -.080197, .0070469, -.074955, 
		.044499, .079895, -.093049, -.11103, .20433, {0}, -1.5931e-8, 
		-2.3296e-9, 3.8595e-8, 1.0183e-9, .12443, -.0097186, -.02174, 
		.0090147, {0}, -.016002, -.0088034, .02126, .016406, .0025079,
		 -.015204, -7.2465e-4, .014602, {0}, -.029124, -.028111, 
		.035597, 6.9291e-4, -.038743, -.0051251, -.033437, .056125, {
		0}, 4.8067e-9, -2.4131e-9, 5.3006e-9, 6.8229e-9, -.021658, 
		-.015143, -.016689, -.0052173, {0}, .0090446, .0056115, 
		.040952, -.027379, .068794, -.01367, -.076956, .028963, {0}, 
		1.2273e-8, -4.8153e-9, 2.2709e-8, 5.845e-9, .036839, -.016588,
		 -.010285, -.012959, {0}, -.030496, -6.945e-5, .018248, 
		-.014324, -.041913, -.011932, -.057708, .031247, {0}, 
		.0078786, .011739, -.017679, -.014532, -.0035795, -.027587, 
		-.1031, -.035943 };

#define fa ((doublereal *)&equiv_193)

    static struct {
	doublereal e_1[8];
	doublereal fill_2[4];
	doublereal e_3[8];
	doublereal fill_4[4];
	doublereal e_5[8];
	doublereal fill_6[4];
	doublereal e_7[8];
	doublereal fill_8[4];
	doublereal e_9[8];
	doublereal fill_10[4];
	doublereal e_11[8];
	doublereal fill_12[4];
	doublereal e_13[8];
	doublereal fill_14[4];
	doublereal e_15[8];
	doublereal fill_16[4];
	doublereal e_17[8];
	doublereal fill_18[4];
	doublereal e_19[8];
	doublereal fill_20[4];
	doublereal e_21[8];
	doublereal fill_22[4];
	doublereal e_23[8];
	doublereal fill_24[4];
	doublereal e_25[8];
	doublereal fill_26[4];
	doublereal e_27[8];
	doublereal fill_28[4];
	doublereal e_29[8];
	doublereal fill_30[4];
	doublereal e_31[8];
	doublereal fill_32[4];
	doublereal e_33[8];
	doublereal fill_34[4];
	doublereal e_35[8];
	doublereal fill_36[4];
	doublereal e_37[8];
	doublereal fill_38[4];
	doublereal e_39[8];
	doublereal fill_40[4];
	doublereal e_41[8];
	doublereal fill_42[4];
	doublereal e_43[8];
	doublereal fill_44[4];
	doublereal e_45[8];
	doublereal fill_46[4];
	doublereal e_47[8];
	doublereal fill_48[4];
	doublereal e_49[8];
	doublereal fill_50[4];
	doublereal e_51[8];
	doublereal fill_52[4];
	doublereal e_53[8];
	doublereal fill_54[4];
	doublereal e_55[8];
	doublereal fill_56[4];
	doublereal e_57[8];
	doublereal fill_58[4];
	doublereal e_59[8];
	doublereal fill_60[4];
	doublereal e_61[8];
	doublereal fill_62[4];
	doublereal e_63[8];
	doublereal fill_64[4];
	doublereal e_65[8];
	doublereal fill_66[4];
	doublereal e_67[8];
	doublereal fill_68[4];
	doublereal e_69[8];
	doublereal fill_70[4];
	doublereal e_71[8];
	doublereal fill_72[4];
	doublereal e_73[8];
	doublereal fill_74[4];
	doublereal e_75[8];
	doublereal fill_76[4];
	doublereal e_77[8];
	doublereal fill_78[4];
	doublereal e_79[8];
	doublereal fill_80[4];
	doublereal e_81[8];
	doublereal fill_82[4];
	doublereal e_83[8];
	doublereal fill_84[4];
	doublereal e_85[8];
	doublereal fill_86[4];
	doublereal e_87[8];
	doublereal fill_88[4];
	doublereal e_89[8];
	doublereal fill_90[4];
	doublereal e_91[8];
	doublereal fill_92[4];
	doublereal e_93[8];
	doublereal fill_94[4];
	doublereal e_95[8];
	doublereal fill_96[4];
	doublereal e_97[8];
	doublereal fill_98[4];
	} equiv_194 = { -419.34, -672.22, -252.47, -421.57, -626.95, -399.11, 
		-280.05, -198.99, {0}, 7.5753e-5, 1.1078e-4, -1.0611e-5, 
		-1.2843e-5, -17.178, 59.796, -98.261, 83.014, {0}, 300.92, 
		290.62, 35.396, 116.77, 114.05, 41.54, -399.83, -123.64, {0}, 
		1.1961e-4, 1.8966e-4, -8.7667e-5, -1.9182e-5, 171.27, 234.66, 
		-26.619, -49.417, {0}, 168.97, 290.21, -296.34, 6.6617, 
		137.52, 40.871, 8.2338, -179.56, {0}, 8.2549e-5, 9.973e-5, 
		1.6567e-5, -2.7718e-5, 136.41, 145.29, 17.867, 184.31, {0}, 
		84.754, 148.05, 77.489, -105.27, -70.975, 121.04, -177.85, 
		306.99, {0}, -.074083, 490.25, -117.99, -17.184, 14.633, 
		-46.233, -101.22, 27.139, {0}, -1.8769e-6, -1.4587e-5, 
		-1.362e-5, -3.4177e-7, 52.949, 11.266, 91.687, 212.87, {0}, 
		-87.576, -62.774, -312.33, -72.191, -28.16, 27.21, -87.297, 
		23.659, {0}, 1.3779e-5, -5.6489e-6, 3.1358e-5, -1.1358e-7, 
		-30.614, -36.695, -2.8501, 42.878, {0}, 7.9487, -23.959, 
		-10.114, -18.024, -27.29, -6.5125, -39.83, 80.452, {0}, 
		-2.355e-6, 3.4145e-6, -4.9641e-6, -1.2578e-7, 1.8518, 19.678, 
		45.134, -28.811, {0}, -71.043, -492.72, 103.63, -66.518, 
		-354.65, -63.622, -106.69, -418.89, {0}, -3.4455e-6, 1.593e-5,
		 4.2123e-6, 6.2438e-6, 178.95, 160.88, -25.633, 11.639, {0}, 
		-75.485, 183.63, 27.824, 230.27, 20.545, -41.296, 7.1774, 
		-4.1313, {0}, 1.3096e-5, -9.9393e-6, -9.7994e-6, -1.7359e-5, 
		56.681, -7.7296, -74.302, -75.002, {0}, -4.7573, -7.0072, 
		-19.069, 40.8, 34.224, -20.603, 15.876, 34.022, {0}, 
		1.9409e-6, 4.4609e-6, -2.8885e-6, 2.1467e-6, 26.772, -37.075, 
		-1.7359, -22.607, {0}, 75.447, 86.865, -74.787, -137.15, 
		371.67, 24.707, -91.679, 18.021, {0}, -2.3927e-6, -2.9546e-6, 
		7.6758e-6, -8.5554e-7, 9.1041, 32.399, -19.696, 8.1737, {0}, 
		19.243, -3.1763, 10.608, -17.205, 21.472, -6.7277, 3.0117, 
		14.083, {0}, 2.423e-6, -1.2566e-7, -6.8638e-7, 5.0757e-6, 
		-.43844, -6.0272, 20.649, 19.836, {0}, 3.6926, -.58817, 
		-11.534, .22927, -12.918, -3.463, -9.3364, -18.668, {0}, 
		159.66, 396.87, -183.12, 80.476, 81.502, -55.263, -226.7, 
		-62.033, {0}, 6.5501e-6, -6.5285e-6, 1.1865e-6, -2.7589e-6, 
		38.268, -25.945, 97.904, 10.904, {0}, 43.22, 10.005, -9.6891, 
		3.3827, 1.0318, -14.906, 15.046, -1.3, {0}, -2.1216e-6, 
		-2.5441e-6, 3.8221e-6, -4.066e-6, -7.3473, 4.1722, -3.3399, 
		3.8715, {0}, 14.776, 4.6315, -7.1519, 13.065, -5.108, 3.4384, 
		-.87702, -7.8479, {0}, 25.894, -27.349, -27.741, -2.0229, 
		-46.51, 22.157, -12.437, 21.208, {0}, -8.0222e-9, 5.5261e-6, 
		-5.9749e-6, 2.192e-6, -30.223, -20.458, 22.864, -5.9507, {0}, 
		-6.4715, -1.1131, -9.3219, 10.875, 5.3605, 2.8784, -3.6244, 
		-13.782, {0}, -3.7197e-7, 1.9219e-6, 1.9756e-6, -6.1136e-7, 
		9.3017, -4.4228, 6.7245, 7.2326, {0}, 11.891, 85.274, -16.897,
		 7.201, 127.1, 19.416, 16.524, -53.504, {0}, -9.2441e-6, 
		-3.1671e-6, -3.0522e-7, -5.4154e-6, 4.5835, -15.663, 23.854, 
		-5.7353, {0}, -28.838, -9.8191, -8.7396, -8.7107, 25.091, 
		6.5339, -23.351, -1.3774, {0}, 2.6401e-6, 7.434e-7, 1.0363e-7,
		 -4.2033e-7, 6.7618, -7.9988, -7.1407, 6.5094, {0}, -.83915, 
		-67.348, -21.515, 24.655, -24.027, 14.137, -1.8966, -7.5963, {
		0}, -6.8336e-7, -1.2024e-6, 1.1544e-6, -7.7856e-6, -8.2618, 
		1.6251, 3.3737, 3.8696, {0}, .41298, -.53796, 1.3571, -4.6298,
		 .081357, .6489, -3.0866, -.2007, {0}, 21.763, -14.772, 
		15.544, -16.797, -18.817, 4.8511, 9.1835, -38.873, {0}, 
		-1.2271e-6, 8.2916e-6, -3.6035e-6, 1.357e-6, -20.141, 2.1505, 
		1.9951, -2.7285, {0}, 2.7614, 1.9457, -2.9642, -3.2055, 
		-.31208, 2.9129, -.40653, -2.3107, {0}, 8.317, 8.3258, 
		-8.9441, -.54947, 1.8021, -.67762, .19179, -9.2363, {0}, 
		-1.7405e-6, 3.5652e-7, -1.5169e-6, 1.2722e-6, 2.7531, .57748, 
		5.1555, 1.1762, {0}, .9756, -3.424, -8.5483, 8.1156, -14.198, 
		3.7354, 8.6789, -4.0574, {0}, -1.4005e-6, 5.481e-7, 
		-1.6971e-6, 5.5588e-6, -8.6175, 1.0259, 2.9229, 3.3439, {0}, 
		3.5829, .29803, -8.4912, 2.0961, 8.0561, 1.5804, 8.9559, 
		-7.0163, {0}, .75525, -4.8309, 3.1723, 6.3166, -2.6929, 
		1.5189, 21.825, 10.312 };

#define fb ((doublereal *)&equiv_194)

    static doublereal sz[400]	/* was [4][4][25] */ = { -22.484,11.725,
	    48.197,162.89,81.616,66.929,66.565,54.078,33.939,84.35,.33717,
	    116.24,-32.521,80.799,-16.095,200.01,15.678,-45.645,15.085,197.16,
	    -78.931,-63.062,-78.329,102.57,41.603,10.359,115.54,262.77,77.815,
	    -109.34,99.417,95.915,-197.82,4.5733,-25.638,271.76,-148.77,
	    -31.518,26.828,32.942,63.171,35.955,45.506,128.54,-99.172,54.753,
	    -14.653,162.46,181.37,18.517,11.104,120.47,-21.824,39.008,-30.595,
	    -27.484,28.139,-53.957,-.75635,-44.443,117.71,23.566,-46.748,
	    29.653,-118.41,-23.715,-19.587,-33.004,-22.731,2.2092,18.69,
	    -42.371,-12.545,-55.573,-18.256,-104.11,-49.189,-64.691,-3.1115,
	    -6.3464,-46.499,-15.863,48.883,-152.13,-44.445,-11.085,9.4627,
	    38.394,26.427,62.484,-6.5165,-69.986,42.987,1.1268,-50.367,
	    -28.476,-80.932,25.084,12.754,-63.033,-1.3629,-28.826,-29.049,
	    -21.161,-59.703,-15.365,35.243,-89.133,6.1923,6.9659,-5.526,
	    -90.499,28.705,-8.8654,-7.4101,-23.628,-5.1986,11.331,29.074,
	    4.3066,-5.234,5.6723,-41.46,-20.989,19.022,-11.639,3.1643,-6.396,
	    -15.15,-4.2437,-17.884,1.525,9.5949,-3.195,2.4002,-27.098,-14.02,
	    -6.6484,4.8214,-7.994,-1.4961,-9.282,.18895,-1.9869,40.453,22.447,
	    -9.7165,-28.945,113.26,29.916,-8.8067,105.62,-.63531,78.126,
	    31.778,-47.922,56.301,111.94,-42.743,33.675,-130.51,20.916,38.258,
	    -84.696,-29.675,-4.7622,31.262,-46.081,36.48,49.952,52.812,11.982,
	    33.056,-87.659,15.466,82.809,24.204,-25.716,3.6539,-16.515,-41.54,
	    -14.363,-.36726,18.271,3.6464,-2.9937,-13.524,13.529,-3.4998,
	    46.876,22.751,-17.643,-8.7547,-6.0094,-4.929,-1.2776,-8.2913,
	    -4.0448,9.7701,-15.616,5.6044,7.2634,-7.4173,7.9148,25.603,
	    -20.595,23.019,.93427,16.474,21.711,107.93,4.2591,-75.447,-14.279,
	    32.131,6.8675,19.248,-10.773,-39.91,22.318,-41.21,-41.123,-12.153,
	    15.153,.92847,-12.222,9.0909,8.2797,-2.8678,-9.1323,-.86902,
	    -.11678,-1.171,2.0048,8.4328,37.615,-.59928,24.208,-9.4305,7.0991,
	    5.0067,.14226,3.3659,-8.3759,22.539,1.6311,-1.3888,2.9773,4.0883,
	    -.2907,-.86133,7.5449,-6.517,-15.497,7.7048,9.2573,-16.276,5.0453,
	    -8.4915,55.75,-43.198,1.0317,38.983,6.5244,30.011,-17.277,-14.775,
	    -13.719,-30.348,-45.482,-10.472,-29.729,-17.811,-5.2144,46.583,
	    18.242,-6.1286,-14.682,-15.296,9.0964,-4.8281,-4.1386,4.1764,
	    -12.865,-.29433,13.202,-10.872,-21.289,3.3205,12.274,6.6691,
	    -2.7894,10.387,3.6067,-6.0608,4.4221,-3.2089,-1.66,-.77575,
	    -7.4193,-2.9917,-14.486,4.7621,-4.9093,1.5727,-2.9295,26.471,
	    27.438,23.967,-.96292,16.429,1.4783,9.7707,22.237,6.3293,-15.604,
	    14.373,-2.7499,-1.5255,-1.4336,4.4872,.053619,1.6831,-2.13,4.4365,
	    3.7949,-5.603,.45843,-1.4347,-3.153,1.2135,-11.663,-1.0131,
	    -5.8915,-1.0996,-5.041,11.533,5.8705,-11.973,-4.2789,-10.083,
	    3.1022,20.101,-12.944,-3.2377,-14.685,-7.7471,-2.1478,-1.8499,
	    -.090391,-2.404,-6.0288,-2.8452,1.2787,7.0796,-2.6639,-6.7061,
	    -.46328,-7.1151,2.9291,-3.2303,1.1209,3.7529,4.4852,-2.0904,
	    -.28128,1.1287,-10.345,8.4677,3.4613,5.3906,4.3236,1.4691,9.0868,
	    5.1599,-3.6895,8.3354,4.0532,-8.6309,-12.419,1.1991,1.9866,
	    -6.4519,6.9714,10.316,2.0811,.26667,-2.3532,3.1579,4.5608,4.3186,
	    -5.6245,2.8745,1.5677,-7.8509,-7.583,.12403,1.386,-.24907,-2.693 }
	    ;

    /* System generated locals */
    doublereal d__1, d__2, d__3, d__4, d__5, d__6, d__7, d__8;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), sqrt(doublereal), acos(
	    doublereal), sin(doublereal), cos(doublereal), d_sign(doublereal *
	    , doublereal *);

    /* Local variables */
    static doublereal a, c__[82];
    static integer i__;
    extern /* Subroutine */ int spharm_ik__(doublereal *, integer *, integer *
	    , doublereal *, doublereal *);
    static doublereal t900, t550, asa, t1500, t2500, csz[25], cf107[49], 
	    t150a, t150b, t900a, t550a, t550b, t900b, t250a, t250b;
    static integer ddda, dddb, dddd;
    static doublereal alfa, t0a150, beta, t0b150, t0a900, t0a550, t0b550, 
	    t1a550, t1b550, t2a550, t2b550, t3a550, t3b550, t0b900, t1a900, 
	    t1b900, t2a900, t2b900, t3a900, t3b900, t1a150, t1b150, t2a150;
    static integer seza, sezb;
    static doublereal t2b150, t3a150, t3b150, t0a250, dtor, invl, t0b250, 
	    t1a250, t1b250, t2a250, rmlt, t2b250, t3a250, t3b250, rdipl;
    static integer sezai, sezbi;
    static doublereal invdp, rinvl, rcolat;

/* Version 2000 (released 30.12.1999) */
/* Empirical model of electron temperature (Te) in the outer ionosphere */
/* for high solar activity conditions (F107 >= 100). */
/* Based on spherical harmonics approximation of measured */
/* Te (by IK19, IK24, and IK25 satellites) at altitudes centred on 550km, */
/* 900km, 1500km, and 2500km. For intermediate altitudes a linear */
/* interpolation is used. Recommended altitude range: 500-3000 km!!! */
/* Linear extrapolation is used for altitude ranges <500;550)km */
/* and (2500;3000> km. For days between seasons centred at */
/* (21.3. = 79; 21.6. = 171; 23.9. 265; 21.12. = 354) Te is */
/* linearly interpolated. */
/* Inputs: CRD - 0 .. INVDIP */
/*               1 .. FL, DIMO, B0, DIPL (used for calculation INVDIP */
/* 						inside) */
/*         F107Y - 0 .. F107 correction NOT included */
/*                 1 .. F107 correction included */
/*         SEASY - 0 .. seasonal correction NOT included */
/*                 1 .. seasonal correction included */
/*         INVDIP - "mix" coordinate of the dip latitude and of */
/*                    the invariant latitude; */
/*                    positive northward, in deg, range <-90.0;90.0> */
/*         FL, DIMO, BO - McIlwain L parameter, dipole moment in */
/*                        Gauss, magnetic field strength in Gauss - */
/*                        parameters needed for invariant latitude */
/*                        calculation */
/*         DIPL - dip latitude */
/*                positive northward, in deg, range <-90.0;90.0> */
/*         MLT - magnetic local time (central dipole) */
/*               in hours, range <0;24) */
/*         ALT - altitude above the Earth's surface; */
/*               in km, range <500;3000> */
/*         DDD - day of year; range <0;365> */
/*         F107 - daily solar radio flux; */
/*                high solar activity; range <100;250> */
/* Output: TE - electron temperature in K */
/*         SIGTE - standard deviation of TE in K */
/*                 (not yet included) */
/* Versions: 1.00 (IDL) the first version Te=Te(invl,mlt,alt,season) */
/*           1.50 (IDL) corrected IK19 Te at 900km for possible */
/*                      Ne > 2E11 m-3 */
/*           2.00 (IDL) F107 included as a linear perturbation on global */
/* 			Te pattern */
/*                      Te=Te(invlat,mlt,alt,season,F107) */
/*           3.00 (IDL) invdipl introduced */
/*           2000 (IDL,FORTRAN) correction for seasons included */
/* Authors of the model (Te measurements (1), data processing (2), model */
/*                       formulation and building (3)): */
/*                V. Truhlik (2,3), L. Triskova (2,3), J. Smilauer (1,2), */
/*                          (Institute of Atm. Phys., Prague) */
/*                                 and V.V. Afonin (1) */
/*                                      (IKI, Moscow) */
/* Author of the code: */
/*         Vladimir Truhlik */
/*         Institute of Atm. Phys. */
/*         Bocni II. */
/*         141 31 Praha 4, Sporilov */
/*         Czech Republic */
/*         e-mail: vtr@ufa.cas.cz */
/*         tel/fax: +420 67103058, +420 602 273111 / +420 72 762528 */
/* //////////////////////coefficients - main model part/////////////// */
/*     550km equinox */
/*     550km June solstice */
/*     900km equinox */
/*     900km June solstice */
/*     1500km equinox */
/*     1500km June solstice */
/*     2500km equinox */
/*     2500km June solstice */
/* ////////////coefficients - F107 correction////////////////////// */
/*     550km equinox */
/*     550km June solstice */
/*     900km equinox */
/*     900km June solstice */
/*     1500km equinox */
/*     1500km June solstice */
/*     2500km equinox */
/*     2500km June solstice */
/* ///////////coefficients - seasonal correction//////////////// */
/*     550km March equinox */
/*     550km June solstice */
/*     550km December solstice */
/*     550km September equinox */
/*     900km March equinox */
/*     900km June solstice */
/*     900km December solstice */
/*     900km September equinox */
/*     1500km March equinox */
/*     1500km June solstice */
/*     1500km December solstice */
/*     1500km September equinox */
/*     2500km March equinox */
/*     2500km June solstice */
/*     2500km December solstice */
/*     2500km September equinox */
/* ////////////////////////////////////////////////////////////// */
    dtor = .01745329252;
/*     coefficients for mirroring */
    for (i__ = 1; i__ <= 81; ++i__) {
	d__[(i__ * 3 + 3 << 2) - 16] = d__[(i__ * 3 + 2 << 2) - 16] * mirreq[
		i__ - 1];
	d__[(i__ * 3 + 3 << 2) - 15] = d__[(i__ * 3 + 2 << 2) - 15] * mirreq[
		i__ - 1];
	d__[(i__ * 3 + 3 << 2) - 14] = d__[(i__ * 3 + 2 << 2) - 14] * mirreq[
		i__ - 1];
/* L10: */
	d__[(i__ * 3 + 3 << 2) - 13] = d__[(i__ * 3 + 2 << 2) - 13] * mirreq[
		i__ - 1];
    }
    for (i__ = 1; i__ <= 49; ++i__) {
	fa[(i__ * 3 + 3 << 2) - 16] = fa[(i__ * 3 + 2 << 2) - 16] * mf107[i__ 
		- 1];
	fb[(i__ * 3 + 3 << 2) - 16] = fb[(i__ * 3 + 2 << 2) - 16] * mf107[i__ 
		- 1];
	fa[(i__ * 3 + 3 << 2) - 15] = fa[(i__ * 3 + 2 << 2) - 15] * mf107[i__ 
		- 1];
	fb[(i__ * 3 + 3 << 2) - 15] = fb[(i__ * 3 + 2 << 2) - 15] * mf107[i__ 
		- 1];
	fa[(i__ * 3 + 3 << 2) - 14] = fa[(i__ * 3 + 2 << 2) - 14] * mf107[i__ 
		- 1];
	fb[(i__ * 3 + 3 << 2) - 14] = fb[(i__ * 3 + 2 << 2) - 14] * mf107[i__ 
		- 1];
	fa[(i__ * 3 + 3 << 2) - 13] = fa[(i__ * 3 + 2 << 2) - 13] * mf107[i__ 
		- 1];
/* L20: */
	fb[(i__ * 3 + 3 << 2) - 13] = fb[(i__ * 3 + 2 << 2) - 13] * mf107[i__ 
		- 1];
    }
    if (*crd == 1) {

/* calculation of INVDIP from FL, DIMO, BO, and DIPL invariant */
/* latitude calculated by highly accurate polynomial expansion */

	d__1 = *dimo / *b0;
	a = pow_dd(&d__1, &c_b55) / *fl;
/* Computing 2nd power */
	d__1 = a;
/* Computing 3rd power */
	d__2 = a;
/* Computing 4th power */
	d__3 = a, d__3 *= d__3;
/* Computing 5th power */
	d__4 = a, d__5 = d__4, d__4 *= d__4;
/* Computing 6th power */
	d__6 = a, d__6 *= d__6;
/* Computing 7th power */
	d__7 = a, d__8 = d__7, d__7 *= d__7, d__8 *= d__7;
	asa = a * (b[0] + b[1] * a + b[2] * (d__1 * d__1) + b[3] * (d__2 * (
		d__2 * d__2)) + b[4] * (d__3 * d__3) + b[5] * (d__5 * (d__4 * 
		d__4)) + b[6] * (d__6 * (d__6 * d__6)) + b[7] * (d__8 * (d__7 
		* d__7)));
	if (asa > 1.) {
	    asa = 1.;
	}
/*      invariant latitude (absolute value) */
	rinvl = acos(sqrt(asa));
	invl = rinvl / dtor;
	rdipl = *dipl * dtor;
/* Computing 3rd power */
	d__1 = sin((abs(rdipl)));
	alfa = d__1 * (d__1 * d__1);
/* Computing 3rd power */
	d__1 = cos(rinvl);
	beta = d__1 * (d__1 * d__1);
	invdp = (alfa * d_sign(&c_b18, dipl) * invl + beta * *dipl) / (alfa + 
		beta);
    } else if (*crd == 0) {
	invdp = *invdip;
    } else {
	return 0;
    }
    rmlt = *mlt * dtor * 15.;
    rcolat = (90. - invdp) * dtor;
    spharm_ik__(c__, &c__8, &c__8, &rcolat, &rmlt);
    spharm_ik__(cf107, &c__6, &c__6, &rcolat, &rmlt);
    spharm_ik__(csz, &c__4, &c__4, &rcolat, &rmlt);
/*     21.3. - 20.6. */
    if (*ddd >= 79 && *ddd < 171) {
	seza = 1;
	sezb = 2;
	ddda = 79;
	dddb = 171;
	dddd = *ddd;
    }
/*     21.6. - 22.9. */
    if (*ddd >= 171 && *ddd < 265) {
	seza = 2;
	sezb = 4;
	ddda = 171;
	dddb = 265;
	dddd = *ddd;
    }
/*     23.9. - 20.12. */
    if (*ddd >= 265 && *ddd < 354) {
	seza = 4;
	sezb = 3;
	ddda = 265;
	dddb = 354;
	dddd = *ddd;
    }
/*     21.12. - 20.3. */
    if (*ddd >= 354 || *ddd < 79) {
	seza = 3;
	sezb = 1;
	ddda = 354;
	dddb = 444;
	dddd = *ddd;
	if (*ddd >= 354) {
	    dddd = *ddd;
	} else {
	    dddd = *ddd + 365;
	}
    }
    sezai = (seza - 1) % 3 + 1;
    sezbi = (sezb - 1) % 3 + 1;
    if (*alt < 900.) {
/*     550km level */
	t0a550 = 0.;
	t0b550 = 0.;
	t1a550 = 0.;
	t1b550 = 0.;
	t2a550 = 0.;
	t2b550 = 0.;
	t3a550 = 0.;
	t3b550 = 0.;
	for (i__ = 1; i__ <= 81; ++i__) {
	    t0a550 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) - 16];
/* L30: */
	    t0b550 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) - 16];
	}
	for (i__ = 1; i__ <= 49; ++i__) {
	    t1a550 += cf107[i__ - 1] * fa[(sezai + i__ * 3 << 2) - 16];
/* L40: */
	    t1b550 += cf107[i__ - 1] * fa[(sezbi + i__ * 3 << 2) - 16];
	}
	for (i__ = 1; i__ <= 49; ++i__) {
	    t2a550 += cf107[i__ - 1] * fb[(sezai + i__ * 3 << 2) - 16];
/* L50: */
	    t2b550 += cf107[i__ - 1] * fb[(sezbi + i__ * 3 << 2) - 16];
	}
	for (i__ = 1; i__ <= 25; ++i__) {
	    t3a550 += csz[i__ - 1] * sz[(seza + (i__ << 2) << 2) - 20];
/* L60: */
	    t3b550 += csz[i__ - 1] * sz[(sezb + (i__ << 2) << 2) - 20];
	}
	t550a = t0a550 + *f107y * (t1a550 * *f107 + t2a550) + *seasy * t3a550;
	t550b = t0b550 + *f107y * (t1b550 * *f107 + t2b550) + *seasy * t3b550;
	t550 = (t550b - t550a) / (dddb - ddda) * (dddd - ddda) + t550a;
    }
    if (*alt < 1500.) {
/*     900km level */
	t0a900 = 0.;
	t0b900 = 0.;
	t1a900 = 0.;
	t1b900 = 0.;
	t2a900 = 0.;
	t2b900 = 0.;
	t3a900 = 0.;
	t3b900 = 0.;
	for (i__ = 1; i__ <= 81; ++i__) {
	    t0a900 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) - 15];
/* L70: */
	    t0b900 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) - 15];
	}
	for (i__ = 1; i__ <= 49; ++i__) {
	    t1a900 += cf107[i__ - 1] * fa[(sezai + i__ * 3 << 2) - 15];
/* L80: */
	    t1b900 += cf107[i__ - 1] * fa[(sezbi + i__ * 3 << 2) - 15];
	}
	for (i__ = 1; i__ <= 49; ++i__) {
	    t2a900 += cf107[i__ - 1] * fb[(sezai + i__ * 3 << 2) - 15];
/* L90: */
	    t2b900 += cf107[i__ - 1] * fb[(sezbi + i__ * 3 << 2) - 15];
	}
	for (i__ = 1; i__ <= 25; ++i__) {
	    t3a900 += csz[i__ - 1] * sz[(seza + (i__ << 2) << 2) - 19];
/* L100: */
	    t3b900 += csz[i__ - 1] * sz[(sezb + (i__ << 2) << 2) - 19];
	}
	t900a = t0a900 + *f107y * (t1a900 * *f107 + t2a900) + *seasy * t3a900;
	t900b = t0b900 + *f107y * (t1b900 * *f107 + t2b900) + *seasy * t3b900;
	t900 = (t900b - t900a) / (dddb - ddda) * (dddd - ddda) + t900a;
    }
    if (*alt > 900.) {
/*     1500km level */
	t0a150 = 0.;
	t0b150 = 0.;
	t1a150 = 0.;
	t1b150 = 0.;
	t2a150 = 0.;
	t2b150 = 0.;
	t3a150 = 0.;
	t3b150 = 0.;
	for (i__ = 1; i__ <= 81; ++i__) {
	    t0a150 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) - 14];
/* L110: */
	    t0b150 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) - 14];
	}
	for (i__ = 1; i__ <= 49; ++i__) {
	    t1a150 += cf107[i__ - 1] * fa[(sezai + i__ * 3 << 2) - 14];
/* L120: */
	    t1b150 += cf107[i__ - 1] * fa[(sezbi + i__ * 3 << 2) - 14];
	}
	for (i__ = 1; i__ <= 49; ++i__) {
	    t2a150 += cf107[i__ - 1] * fb[(sezai + i__ * 3 << 2) - 14];
/* L130: */
	    t2b150 += cf107[i__ - 1] * fb[(sezbi + i__ * 3 << 2) - 14];
	}
	for (i__ = 1; i__ <= 25; ++i__) {
	    t3a150 += csz[i__ - 1] * sz[(seza + (i__ << 2) << 2) - 18];
/* L140: */
	    t3b150 += csz[i__ - 1] * sz[(sezb + (i__ << 2) << 2) - 18];
	}
	t150a = t0a150 + *f107y * (t1a150 * *f107 + t2a150) + *seasy * t3a150;
	t150b = t0b150 + *f107y * (t1b150 * *f107 + t2b150) + *seasy * t3b150;
	t1500 = (t150b - t150a) / (dddb - ddda) * (dddd - ddda) + t150a;
    }
    if (*alt >= 1500.) {
/*     2500km level */
	t0a250 = 0.;
	t0b250 = 0.;
	t1a250 = 0.;
	t1b250 = 0.;
	t2a250 = 0.;
	t2b250 = 0.;
	t3a250 = 0.;
	t3b250 = 0.;
	for (i__ = 1; i__ <= 81; ++i__) {
	    t0a250 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) - 13];
/* L150: */
	    t0b250 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) - 13];
	}
	for (i__ = 1; i__ <= 49; ++i__) {
	    t1a250 += cf107[i__ - 1] * fa[(sezai + i__ * 3 << 2) - 13];
/* L160: */
	    t1b250 += cf107[i__ - 1] * fa[(sezbi + i__ * 3 << 2) - 13];
	}
	for (i__ = 1; i__ <= 49; ++i__) {
	    t2a250 += cf107[i__ - 1] * fb[(sezai + i__ * 3 << 2) - 13];
/* L170: */
	    t2b250 += cf107[i__ - 1] * fb[(sezbi + i__ * 3 << 2) - 13];
	}
	for (i__ = 1; i__ <= 25; ++i__) {
	    t3a250 += csz[i__ - 1] * sz[(seza + (i__ << 2) << 2) - 17];
/* L180: */
	    t3b250 += csz[i__ - 1] * sz[(sezb + (i__ << 2) << 2) - 17];
	}
	t250a = t0a250 + *f107y * (t1a250 * *f107 + t2a250) + *seasy * t3a250;
	t250b = t0b250 + *f107y * (t1b250 * *f107 + t2b250) + *seasy * t3b250;
	t2500 = (t250b - t250a) / (dddb - ddda) * (dddd - ddda) + t250a;
    }
    if (*alt < 900.) {
	*te = (t900 - t550) / 350. * (*alt - 550) + t550;
    }
    if (*alt >= 900. && *alt < 1500.) {
	*te = (t1500 - t900) / 600. * (*alt - 900) + t900;
    }
    if (*alt >= 1500.) {
	*te = (t2500 - t1500) / 1e3 * (*alt - 1500) + t1500;
    }
    return 0;
} /* elteik_ */

#undef fb
#undef fa
#undef d__




/* Subroutine */ int spharm_ik__(doublereal *c__, integer *l, integer *m, 
	doublereal *colat, doublereal *az)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal), pow_di(doublereal *, integer *);

    /* Local variables */
    static integer i__, k, n;
    static doublereal x, y;
    static integer mt;
    static doublereal caz, saz;

/* CALCULATES THE COEFFICIENTS OF THE SPHERICAL HARMONIC */
/* FROM IRI 95 MODEL */
/* NOTE: COEFFICIENTS CORRESPONDING TO COS, SIN SWAPPED!!! */
    /* Parameter adjustments */
    --c__;

    /* Function Body */
    c__[1] = 1.;
    k = 2;
    x = cos(*colat);
    c__[k] = x;
    ++k;
    i__1 = *l;
    for (i__ = 2; i__ <= i__1; ++i__) {
	c__[k] = (((i__ << 1) - 1) * x * c__[k - 1] - (i__ - 1) * c__[k - 2]) 
		/ i__;
/* L10: */
	++k;
    }
    y = sin(*colat);
    i__1 = *m;
    for (mt = 1; mt <= i__1; ++mt) {
	caz = cos(mt * *az);
	saz = sin(mt * *az);
	c__[k] = pow_di(&y, &mt);
	++k;
	if (mt == *l) {
	    goto L16;
	}
	c__[k] = c__[k - 1] * x * ((mt << 1) + 1);
	++k;
	if (mt + 1 == *l) {
	    goto L16;
	}
	i__2 = *l;
	for (i__ = mt + 2; i__ <= i__2; ++i__) {
	    c__[k] = (((i__ << 1) - 1) * x * c__[k - 1] - (i__ + mt - 1) * 
		    c__[k - 2]) / (i__ - mt);
/* L15: */
	    ++k;
	}
L16:
	n = *l - mt + 1;
	i__2 = n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    c__[k] = c__[k - n] * saz;
	    c__[k - n] *= caz;
/* L18: */
	    ++k;
	}
/* L20: */
    }
    return 0;
} /* spharm_ik__ */



/* Subroutine */ int teba_(doublereal *dipl, doublereal *slt, integer *ns, 
	doublereal *te)
{
    /* Initialized data */

    static doublereal c__[648]	/* was [4][2][81] */ = { 3.1,3.136,3.372,
	    3.574,3.13654,3.144,3.367,3.574,-.003215,.006498,.01006,0.,
	    .006796,.008571,.01038,-.005639,.244,.2289,.1436,.07537,.181413,
	    .2539,.1407,.07094,-4.613e-4,.01859,.002023,0.,.08564,.06937,
	    .03622,-.03347,-.01711,-.03328,-.05166,-.08459,-.032856,-.01667,
	    -.03144,-.0861,.02605,-.004889,.009606,0.,-.003508,.02249,.0112,
	    -.02877,-.09546,-.03054,-.05596,-.0294,-.01438,-.04162,-.05674,
	    -.03154,.01794,-.01773,4.914e-4,0.,-.02454,.01201,.03219,-.002847,
	    .0127,-.01728,-.003124,.04547,.002745,.02435,.001288,.01235,
	    .02791,.06555,-.04713,-.05321,.05284,.05232,-.05799,-.05966,
	    .01536,.01775,-.007371,0.,.01136,.02521,-.004609,-.003236,
	    -.006629,-.02488,-.004823,.004328,-.01956,-.0199,.003252,3.795e-4,
	    -.003616,-.009498,-.002213,0.,-.005805,-.007671,-2.859e-4,
	    -8.634e-4,.01229,.01493,.006569,.006022,.002801,.01264,.01226,
	    .003377,4.147e-4,.00281,-1.962e-4,0.,-.001211,-.001551,-.004539,
	    -1.071e-4,.001447,.002406,3.309e-4,-9.168e-4,.004127,-.001928,
	    .00131,-.002151,-4.453e-4,.005436,-3.908e-4,0.,.002909,.003652,
	    -5.603e-4,-4.057e-4,-.1853,-.2115,-.2836,-.1768,-.25751,-.2019,
	    -.311,-.1783,-.01245,.007007,.007829,0.,-.0037915,.005697,
	    -.001268,.0126,-.03675,-.05129,.01175,.0294,-.0136,-.03159,.01539,
	    .02835,.004965,-.007327,9.919e-4,0.,-.013225,-.01451,.003146,
	    -.00242,.00546,.02402,.006589,5.902e-4,.01202,.02868,.007787,
	    .003002,.008117,.004772,.002045,0.,.01256,.01377,-.00143,-.004684,
	    -.01002,-.007374,-.007346,-.009047,-.012165,-.004383,-.00482,
	    -.006756,5.466e-4,-3.835e-4,-8.9e-4,0.,.01326,.01172,.002924,
	    -7.493e-4,-.03087,-.05013,-.0347,-.06555,-.07123,-.05683,-.09981,
	    -.06147,-.003435,.002866,-.004977,0.,5.793e-4,.003593,-.007838,
	    -.005636,-1.107e-4,.002216,.00147,-.001033,.001537,.003571,
	    -1.663e-4,-.001234,.002199,2.412e-4,-2.823e-6,0.,.006914,.003282,
	    4.769e-4,-.001613,4.115e-4,.002094,6.465e-4,.001674,-.004173,
	    .001732,.004148,-6.353e-5,6.061e-4,.00122,-1.448e-4,0.,1.052e-4,
	    -4.921e-4,-.001008,-2.503e-4,2.916e-4,-1.703e-4,.001401,2.802e-4,
	    -5.765e-4,-.001165,-9.79e-4,-1.729e-4,-.06584,-.1082,-.08988,
	    -.06786,-.04041,-.1066,-.09049,-.07148,.004729,-.004992,-3.293e-5,
	    0.,-.001752,-.01892,-.002994,.005326,-.001523,-.004065,-.001848,
	    .004193,-.00542,.00357,-.006748,.004006,6.689e-4,.003615,4.439e-4,
	    0.,-.00684,-8.631e-4,-9.889e-4,6.484e-4,.001031,-.002738,-.001263,
	    -6.448e-4,8.921e-4,-.001876,.001488,-1.046e-4,5.398e-4,-7.177e-4,
	    3.17e-4,0.,-.002228,-8.414e-5,-.001154,-6.034e-4,-.001924,
	    2.173e-4,-6.227e-4,9.277e-4,.001428,.002356,-8.412e-5,-9.435e-4,
	    -.04565,-.04373,.01721,-.01634,.006635,-.04259,-.01302,-.002385,
	    .007244,-.00375,-.00199,0.,-.0048045,-.00322,-.004859,.006853,
	    -8.543e-5,.005507,-4.627e-4,-.002531,-.001659,.004641,-7.172e-4,
	    .00151,.001052,-.001567,2.897e-6,0.,-9.341e-4,6.223e-4,-9.401e-4,
	    .001319,-6.696e-4,-.001458,-5.454e-4,1.93e-5,2.23e-4,-.00168,
	    9.101e-4,9.049e-5,-7.492e-4,-7.397e-4,3.385e-4,0.,-9.995e-4,
	    -1.243e-4,-1.735e-4,-1.999e-4,.04405,.07903,.08432,.0528,.04285,
	    .07393,.07055,.03976,.003047,.004131,-.001951,0.,-5.211e-4,
	    -.003143,.006398,.002802,.002858,.003714,.001487,.002438,-.003293,
	    -.002362,-.003103,-.00103,-1.465e-4,.001073,.001042,0.,.00179,
	    .001235,-9.38e-4,5.599e-4,.001195,-8.991e-4,-4.788e-4,-5.292e-4,
	    6.435e-4,-.001551,-4e-4,-4.791e-4,-1.024e-4,2.976e-4,-1.276e-4,0.,
	    -1.891e-4,2.099e-4,-.001165,-8.46e-5,.04582,.02623,.02373,.01555,
	    .03844,.02299,.02713,.02683,8.749e-4,.002344,.002409,0.,.00359,
	    .005301,-.001654,.00427,3.011e-4,5.608e-4,5.263e-4,-.003259,
	    -8.139e-4,-.004306,.002781,5.911e-4,4.473e-4,4.124e-4,.001301,0.,
	    -.001996,-.001303,-5.215e-6,2.987e-4,-2.782e-4,1.509e-4,-4.177e-4,
	    -5.998e-4,2.398e-4,7.687e-6,2.258e-4,-2.08e-4,.04911,.05103,
	    .03974,.03168,.02938,.05305,.05022,.01396,-.01016,.00345,1.418e-4,
	    0.,.00761,.006642,.0095,-.001922,.0027,.001283,-.001048,.002382,
	    .00347655,-.001686,4.147e-4,-.001063,-9.304e-4,7.238e-4,-2.982e-4,
	    0.,.001707,.001048,3.499e-4,3.803e-4,-.001202,-3.464e-5,-3.396e-5,
	    -4.078e-4,2.769e-4,5.958e-4,-6.097e-4,1.343e-4,.0221,.01663,.0131,
	    .02312,-.0157,.04341,.04118,.01771,.002566,-.001644,.001413,0.,
	    9.83e-4,-8.819e-5,.006556,-.001038,-1.22e-4,-7.1e-4,-1.373e-4,
	    1.481e-4,-6.532e-4,-3.33e-4,.003793,-4.645e-4,3.987e-4,5.281e-4,
	    2.638e-4,0.,9.29e-5,-2.158e-4,-1.226e-4,-2.481e-4,-.05744,-.02729,
	    -.04171,-.01885,-.02506,-.04106,-.02517,-.02251,.004408,.003556,
	    -5.932e-4,0.,.004681,.004191,1.491e-4,-.0029,-.003497,-.003391,
	    -7.523e-4,.001144,.001461,.002045,.001075,-3.977e-4,8.3e-4,
	    -1.787e-4,-6.883e-4,0.,-3.757e-6,-1.437e-4,4.531e-4,-5.16e-4,
	    -.03536,.002154,-.02355,-.009952,-.009728,-.01803,-.009012,
	    -.008079,-.008813,.006476,5.695e-4,0.,.002315,-8.072e-4,.003343,
	    -.001528,.002423,-8.282e-4,-2.219e-5,-5.51e-4,6.377e-4,-4.24e-4,
	    .003431,3.06e-4,-.02994,-.02361,-.02301,-.0202,-.01705,-.026,
	    -.02519,-.01582,-.001929,9.557e-4,-9.962e-5,0.,.002767,-.002329,
	    3.793e-5,-8.536e-4,-5.268e-4,3.205e-4,-6.761e-4,-7.283e-5,
	    -6.992e-4,5.949e-4,5.973e-4,1.565e-4,-.02228,-.02301,.00204,
	    -.01272,-.0115,-.01371,-.01423,-.01252,.003385,-8.54e-4,-5.479e-4,
	    0.,-.001644,-.002188,-.00132,2.319e-4,.0413,-.01126,.02591,
	    .002224,.003355,.01788,-.006048,.004311,.004876,-.002323,-.002425,
	    0.,-.004326,6.405e-4,-.005005,.001024,.02692,-.008582,.01583,
	    -.00251,.02035,.005977,-.0115,1.296e-6,.001684,.02683,.009577,
	    .02434,.02985,.01333,.02574,.0179 };

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal a[82];
    static integer i__, j, k;
    static doublereal az;
    static integer is;
    static doublereal ste;
    static integer kend;
    static doublereal colat;
    extern /* Subroutine */ int spharm_(doublereal *, integer *, integer *, 
	    doublereal *, doublereal *);

/* CALCULATES ELECTRON TEMPERATURES TE(1) TO TE(4) AT ALTITUDES */
/* 300, 400, 1400 AND 3000 KM FOR DIP-LATITUDE DIPL/DEG AND */
/* LOCAL SOLAR TIME SLT/H USING THE BRACE-THEIS-MODELS (J. ATMOS. */
/* TERR. PHYS. 43, 1317, 1981); NS IS SEASON IN NORTHERN */
/* HEMISOHERE: IS=1 SPRING, IS=2 SUMMER .... */
/* ALSO CALCULATED ARE THE TEMPERATURES AT 400 KM ALTITUDE FOR */
/* MIDNIGHT (TE(5)) AND NOON (TE(6)). */
    /* Parameter adjustments */
    --te;

    /* Function Body */
    if (*ns < 3) {
	is = *ns;
    } else if (*ns > 3) {
	is = 2;
	*dipl = -(*dipl);
    } else {
	is = 1;
    }
    colat = const_1.umr * (90. - *dipl);
    az = const1_1.humr * *slt;
    spharm_(a, &c__8, &c__8, &colat, &az);
    if (is == 2) {
	kend = 3;
    } else {
	kend = 4;
    }
    i__1 = kend;
    for (k = 1; k <= i__1; ++k) {
	ste = 0.;
	for (i__ = 1; i__ <= 81; ++i__) {
/* L1: */
	    ste += a[i__ - 1] * c__[k + (is + (i__ << 1) << 2) - 13];
	}
/* L2: */
	te[k] = pow_dd(&c_b30, &ste);
    }
    if (is == 2) {
	*dipl = -(*dipl);
	colat = const_1.umr * (90. - *dipl);
	spharm_(a, &c__8, &c__8, &colat, &az);
	ste = 0.;
	for (i__ = 1; i__ <= 81; ++i__) {
/* L11: */
	    ste += a[i__ - 1] * c__[((i__ << 1) + 2 << 2) - 9];
	}
	te[4] = pow_dd(&c_b30, &ste);
    }
/* ---------- TEMPERATURE AT 400KM AT MIDNIGHT AND NOON */
    for (j = 1; j <= 2; ++j) {
	ste = 0.;
	az = const1_1.humr * (j - 1) * 12.;
	spharm_(a, &c__8, &c__8, &colat, &az);
	for (i__ = 1; i__ <= 81; ++i__) {
/* L3: */
	    ste += a[i__ - 1] * c__[(is + (i__ << 1) << 2) - 11];
	}
/* L4: */
	te[j + 4] = pow_dd(&c_b30, &ste);
    }
    return 0;
} /* teba_ */


/* Subroutine */ int spharm_(doublereal *c__, integer *l, integer *m, 
	doublereal *colat, doublereal *az)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal), pow_di(doublereal *, integer *);

    /* Local variables */
    static integer i__, k, n;
    static doublereal x, y;
    static integer mt;
    static doublereal caz, saz;

/* CALCULATES THE COEFFICIENTS OF THE SPHERICAL HARMONIC */
/* EXPANSION THAT WAS USED FOR THE BRACE-THEIS-MODELS. */
    /* Parameter adjustments */
    --c__;

    /* Function Body */
    c__[1] = 1.;
    k = 2;
    x = cos(*colat);
    c__[k] = x;
    ++k;
    i__1 = *l;
    for (i__ = 2; i__ <= i__1; ++i__) {
	c__[k] = (((i__ << 1) - 1) * x * c__[k - 1] - (i__ - 1) * c__[k - 2]) 
		/ i__;
/* L10: */
	++k;
    }
    y = sin(*colat);
    i__1 = *m;
    for (mt = 1; mt <= i__1; ++mt) {
	caz = cos(mt * *az);
	saz = sin(mt * *az);
	c__[k] = pow_di(&y, &mt);
	++k;
	if (mt == *l) {
	    goto L16;
	}
	c__[k] = c__[k - 1] * x * ((mt << 1) + 1);
	++k;
	if (mt + 1 == *l) {
	    goto L16;
	}
	i__2 = *l;
	for (i__ = mt + 2; i__ <= i__2; ++i__) {
	    c__[k] = (((i__ << 1) - 1) * x * c__[k - 1] - (i__ + mt - 1) * 
		    c__[k - 2]) / (i__ - mt);
/* L15: */
	    ++k;
	}
L16:
	n = *l - mt + 1;
	i__2 = n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    c__[k] = c__[k - n] * caz;
	    c__[k - n] *= saz;
/* L18: */
	    ++k;
	}
/* L20: */
    }
    return 0;
} /* spharm_ */



doublereal elte_(doublereal *h__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static integer i__;
    static doublereal aa, bb, sum;
    extern doublereal eptr_(doublereal *, doublereal *, doublereal *);

/* ---------------------------------------------------------------- */
/* ELECTRON TEMPERATURE PROFILE BASED ON THE TEMPERATURES AT 120 */
/* HMAX,300,400,600,1400,3000 KM ALTITUDE. INBETWEEN CONSTANT */
/* GRADIENT IS ASSUMED. ARGMAX IS MAXIMUM ARGUMENT ALLOWED FOR */
/* EXP-FUNCTION. */
/* ---------------------------------------------------------------- */

    sum = blote_1.ate1 + blote_1.st[0] * (*h__ - blote_1.ah[0]);
    for (i__ = 1; i__ <= 5; ++i__) {
	aa = eptr_(h__, &blote_1.d__[i__ - 1], &blote_1.ah[i__]);
	bb = eptr_(blote_1.ah, &blote_1.d__[i__ - 1], &blote_1.ah[i__]);
/* L1: */
	sum += (blote_1.st[i__] - blote_1.st[i__ - 1]) * (aa - bb) * 
		blote_1.d__[i__ - 1];
    }
    ret_val = sum;
    return ret_val;
} /* elte_ */



doublereal tede_(doublereal *h__, doublereal *den, doublereal *cov)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal y, yc, acov;

/* ELECTRON TEMEPERATURE MODEL AFTER BRACE,THEIS . */
/* FOR NEG. COV THE MEAN COV-INDEX (3 SOLAR ROT.) IS EXPECTED. */
/* DEN IS THE ELECTRON DENSITY IN M-3. */
    y = (*h__ * 17.01 - 2746.) * exp(*h__ * -5.122e-4 + (6.094e-12 - *h__ * 
	    3.353e-14) * *den) + 1051.;
    acov = abs(*cov);
    yc = (acov * .00202 + .117) / (exp(-(acov - 102.5) / 5.) + 1.) + 1.;
    if (*cov < 0.) {
	yc = (acov * .00169 + .123) / (exp(-(acov - 115.) / 10.) + 1.) + 1.;
    }
    ret_val = y * yc;
    return ret_val;
} /* tede_ */



/* ************************************************************* */
/* **************** ION TEMPERATURE **************************** */
/* ************************************************************* */


doublereal ti_(doublereal *h__)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Local variables */
    static integer i__;
    static doublereal aa, bb, sum;
    extern doublereal eptr_(doublereal *, doublereal *, doublereal *);

/* ---------------------------------------------------------------- */
/* ION TEMPERATURE FOR HEIGHTS NOT GREATER 1000 KM AND NOT LESS HS */
/* EXPLANATION SEE FUNCTION RPID. */
/* ---------------------------------------------------------------- */
    sum = block8_1.mm[0] * (*h__ - block8_1.hs) + block8_1.tnhs;
    i__1 = block8_1.m - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	aa = eptr_(h__, &block8_1.g[i__ - 1], &block8_1.xsm[i__ - 1]);
	bb = eptr_(&block8_1.hs, &block8_1.g[i__ - 1], &block8_1.xsm[i__ - 1])
		;
/* L100: */
	sum += (block8_1.mm[i__] - block8_1.mm[i__ - 1]) * (aa - bb) * 
		block8_1.g[i__ - 1];
    }
    ret_val = sum;
    return ret_val;
} /* ti_ */



doublereal teder_(doublereal *h__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal tn_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal tnh, dtdx;
    extern doublereal dtndh_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/* THIS FUNCTION ALONG WITH PROCEDURE REGFA1 ALLOWS TO FIND */
/* THE  HEIGHT ABOVE WHICH TN BEGINS TO BE DIFFERENT FROM TI */
    tnh = tn_(h__, &blotn_1.tex, &blotn_1.tlbd, &blotn_1.sig);
    dtdx = dtndh_(h__, &blotn_1.tex, &blotn_1.tlbd, &blotn_1.sig);
    ret_val = dtdx * (blotn_1.xsm1 - *h__) + tnh;
    return ret_val;
} /* teder_ */



doublereal tn_(doublereal *h__, doublereal *tinf, doublereal *tlbd, 
	doublereal *s)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal zg2;

/* -------------------------------------------------------------------- */
/*       Calculate Temperature for MSIS/CIRA-86 model */
/* -------------------------------------------------------------------- */
    zg2 = (*h__ - 120.) * 6476.77 / (*h__ + 6356.77);
    ret_val = *tinf - *tlbd * exp(-(*s) * zg2);
    return ret_val;
} /* tn_ */



doublereal dtndh_(doublereal *h__, doublereal *tinf, doublereal *tlbd, 
	doublereal *s)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal zg1, zg2, zg3;

/* --------------------------------------------------------------------- */
    zg1 = *h__ + 6356.77;
    zg2 = 6476.77 / zg1;
    zg3 = (*h__ - 120.) * zg2;
    ret_val = -(*tlbd) * exp(-(*s) * zg3) * (*s / zg1 * (zg3 - zg2));
    return ret_val;
} /* dtndh_ */



/* ************************************************************* */
/* ************* ION RELATIVE PRECENTAGE DENSITY ***************** */
/* ************************************************************* */


doublereal rpid_(doublereal *h__, doublereal *h0, doublereal *n0, integer *m, 
	doublereal *st, integer *id, doublereal *xs)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal aa, bb, sm, xi, sum;
    extern doublereal eptr_(doublereal *, doublereal *, doublereal *);

/* ------------------------------------------------------------------ */
/* D.BILITZA,1977,THIS ANALYTIC FUNCTION IS USED TO REPRESENT THE */
/* RELATIVE PRECENTAGE DENSITY OF ATOMAR AND MOLECULAR OXYGEN IONS. */
/* THE M+1 HEIGHT GRADIENTS ST(M+1) ARE CONNECTED WITH EPSTEIN- */
/* STEP-FUNCTIONS AT THE STEP HEIGHTS XS(M) WITH TRANSITION */
/* THICKNESSES ID(M). RPID(H0,H0,N0,....)=N0. */
/* ARGMAX is the highest allowed argument for EXP in your system. */
/* ------------------------------------------------------------------ */
    /* Parameter adjustments */
    --xs;
    --id;
    --st;

    /* Function Body */
    sum = (*h__ - *h0) * st[1];
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	xi = (doublereal) id[i__];
	aa = eptr_(h__, &xi, &xs[i__]);
	bb = eptr_(h0, &xi, &xs[i__]);
/* L100: */
	sum += (st[i__ + 1] - st[i__]) * (aa - bb) * xi;
    }
    if (abs(sum) < argexp_1.argmax) {
	sm = exp(sum);
    } else if (sum > 0.) {
	sm = exp(argexp_1.argmax);
    } else {
	sm = 0.;
    }
    ret_val = *n0 * sm;
    return ret_val;
} /* rpid_ */



/* Subroutine */ int rdhhe_(doublereal *h__, doublereal *hb, doublereal *rdoh,
	 doublereal *rdo2h, doublereal *rno, doublereal *pehe, doublereal *
	rdh, doublereal *rdhe)
{
    static doublereal rest;

/* BILITZA,FEB.82,H+ AND HE+ RELATIVE PERECENTAGE DENSITY BELOW */
/* 1000 KM. THE O+ AND O2+ REL. PER. DENSITIES SHOULD BE GIVEN */
/* (RDOH,RDO2H). HB IS THE ALTITUDE OF MAXIMAL O+ DENSITY. PEHE */
/* IS THE PRECENTAGE OF HE+ IONS COMPARED TO ALL LIGHT IONS. */
/* RNO IS THE RATIO OF NO+ TO O2+DENSITY AT H=HB. */
    *rdhe = 0.;
    *rdh = 0.;
    if (*h__ <= *hb) {
	goto L100;
    }
    rest = 100. - *rdoh - *rdo2h - *rno * *rdo2h;
    *rdh = rest * (1. - *pehe / 100.);
    *rdhe = rest * *pehe / 100.;
L100:
    return 0;
} /* rdhhe_ */



doublereal rdno_(doublereal *h__, doublereal *hb, doublereal *rdo2h, 
	doublereal *rdoh, doublereal *rno)
{
    /* System generated locals */
    doublereal ret_val;

/* D.BILITZA, 1978. NO+ RELATIVE PERCENTAGE DENSITY ABOVE 100KM. */
/* FOR MORE INFORMATION SEE SUBROUTINE RDHHE. */
    if (*h__ > *hb) {
	goto L200;
    }
    ret_val = 100. - *rdo2h - *rdoh;
    return ret_val;
L200:
    ret_val = *rno * *rdo2h;
    return ret_val;
} /* rdno_ */



/* Subroutine */ int koefp1_(doublereal *pg1o)
{
    /* Initialized data */

    static doublereal feld[80] = { -11.,-11.,4.,-11.,.08018,.13027,.04216,.25,
	    -.00686,.00999,5.113,.1,170.,180.,.1175,.15,-11.,1.,2.,-11.,.069,
	    .161,.254,.18,.0161,.0216,.03014,.1,152.,167.,.04916,.17,-11.,2.,
	    2.,-11.,.072,.092,.014,.21,.01389,.03863,.05762,.12,165.,168.,
	    .008,.258,-11.,1.,3.,-11.,.091,.088,.008,.34,.0067,.0195,.04,.1,
	    158.,172.,.01,.24,-11.,2.,3.,-11.,.083,.102,.045,.03,.00127,.01,
	    .05,.09,167.,185.,.015,.18 };

    static integer i__, k;

/* THIEMANN,1979,COEFFICIENTS PG1O FOR CALCULATING  O+ PROFILES */
/* BELOW THE F2-MAXIMUM. CHOSEN TO APPROACH DANILOV- */
/* SEMENOV'S COMPILATION. */
    /* Parameter adjustments */
    --pg1o;

    /* Function Body */
    k = 0;
    for (i__ = 1; i__ <= 80; ++i__) {
	++k;
/* L10: */
	pg1o[k] = feld[i__ - 1];
    }
    return 0;
} /* koefp1_ */



/* Subroutine */ int koefp2_(doublereal *pg2o)
{
    /* Initialized data */

    static doublereal feld[32] = { 1.,-11.,-11.,1.,695.,-7.81e-4,-.00264,
	    2177.,1.,-11.,-11.,2.,570.,-.002,-.0052,1040.,2.,-11.,-11.,1.,
	    695.,-7.86e-4,-.00165,3367.,2.,-11.,-11.,2.,575.,-.00126,-.00524,
	    1380. };

    static integer i__, k;

/* THIEMANN,1979,COEFFICIENTS FOR CALCULATION OF O+ PROFILES */
/* ABOVE THE F2-MAXIMUM (DUMBS,SPENNER:AEROS-COMPILATION) */
    /* Parameter adjustments */
    --pg2o;

    /* Function Body */
    k = 0;
    for (i__ = 1; i__ <= 32; ++i__) {
	++k;
/* L10: */
	pg2o[k] = feld[i__ - 1];
    }
    return 0;
} /* koefp2_ */



/* Subroutine */ int koefp3_(doublereal *pg3o)
{
    /* Initialized data */

    static doublereal feld[80] = { -11.,1.,2.,-11.,160.,31.,130.,-10.,198.,0.,
	    .05922,-.07983,-.00397,8.5e-4,-.00313,0.,-11.,2.,2.,-11.,140.,30.,
	    130.,-10.,190.,0.,.05107,-.07964,9.7e-4,-.01118,-.02614,-.09537,
	    -11.,1.,3.,-11.,140.,37.,125.,0.,182.,0.,.0307,-.04968,-.00248,
	    -.02451,-.00313,0.,-11.,2.,3.,-11.,140.,37.,125.,0.,170.,0.,
	    .02806,-.04716,6.6e-4,-.02763,-.02247,-.01919,-11.,-11.,4.,-11.,
	    140.,45.,136.,-9.,181.,-26.,.02994,-.04879,-.01396,8.9e-4,-.09929,
	    .05589 };

    static integer i__, k;

/* THIEMANN,1979,COEFFICIENTS FOR CALCULATING O2+ PROFILES. */
/* CHOSEN AS TO APPROACH DANILOV-SEMENOV'S COMPILATION. */
    /* Parameter adjustments */
    --pg3o;

    /* Function Body */
    k = 0;
    for (i__ = 1; i__ <= 80; ++i__) {
	++k;
/* L10: */
	pg3o[k] = feld[i__ - 1];
    }
    return 0;
} /* koefp3_ */



/* Subroutine */ int sufe_(doublereal *field, doublereal *rfe, integer *m, 
	doublereal *fe)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k;
    static doublereal efe[4];

/* SELECTS THE REQUIRED ION DENSITY PARAMETER SET. */
/* THE INPUT FIELD INCLUDES DIFFERENT SETS OF DIMENSION M EACH */
/* CARACTERISED BY 4 HEADER NUMBERS. RFE(4) SHOULD CONTAIN THE */
/* CHOSEN HEADER NUMBERS.FE(M) IS THE CORRESPONDING SET. */
    /* Parameter adjustments */
    --fe;
    --rfe;
    --field;

    /* Function Body */
    k = 0;
L100:
    for (i__ = 1; i__ <= 4; ++i__) {
	++k;
/* L101: */
	efe[i__ - 1] = field[k];
    }
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++k;
/* L111: */
	fe[i__] = field[k];
    }
    for (i__ = 1; i__ <= 4; ++i__) {
	if (efe[i__ - 1] > -10. && rfe[i__] != efe[i__ - 1]) {
	    goto L100;
	}
/* L120: */
    }
    return 0;
} /* sufe_ */

/* Subroutine */ int ionco2_(doublereal *hei, doublereal *xhi, integer *it, 
	doublereal *f, doublereal *r1, doublereal *r2, doublereal *r3, 
	doublereal *r4)
{
    /* Initialized data */

    static integer j1ms70[7] = { 11,11,10,10,11,9,11 };
    static integer j2ms70[7] = { 13,11,10,11,11,9,11 };
    static doublereal h1s70[91]	/* was [13][7] */ = { 75.,85.,90.,95.,100.,
	    120.,130.,200.,220.,250.,270.,0.,0.,75.,85.,90.,95.,100.,120.,
	    130.,200.,220.,250.,270.,0.,0.,75.,85.,90.,95.,100.,115.,200.,
	    220.,250.,270.,0.,0.,0.,75.,80.,95.,100.,120.,140.,200.,220.,250.,
	    270.,0.,0.,0.,75.,80.,95.,100.,120.,150.,170.,200.,220.,250.,270.,
	    0.,0.,75.,80.,95.,100.,140.,200.,220.,250.,270.,0.,0.,0.,0.,75.,
	    80.,85.,95.,100.,110.,145.,200.,220.,250.,270.,0.,0. };
    static doublereal h2s70[91]	/* was [13][7] */ = { 75.,80.,90.,95.,100.,
	    120.,130.,140.,150.,200.,220.,250.,270.,75.,80.,90.,95.,100.,120.,
	    130.,200.,220.,250.,270.,0.,0.,75.,80.,90.,95.,100.,115.,200.,
	    220.,250.,270.,0.,0.,0.,75.,80.,95.,100.,120.,140.,150.,200.,220.,
	    250.,270.,0.,0.,75.,80.,95.,100.,120.,150.,170.,200.,220.,250.,
	    270.,0.,0.,75.,80.,95.,100.,140.,200.,220.,250.,270.,0.,0.,0.,0.,
	    75.,80.,90.,95.,100.,110.,145.,200.,220.,250.,270.,0.,0. };
    static doublereal r1ms70[91]	/* was [13][7] */ = { 6.,30.,60.,63.,
	    59.,59.,66.,52.,20.,4.,2.,0.,0.,6.,30.,60.,63.,69.,62.,66.,52.,
	    20.,4.,2.,0.,0.,6.,30.,60.,63.,80.,68.,53.,20.,4.,2.,0.,0.,0.,4.,
	    10.,60.,85.,65.,65.,52.,25.,12.,4.,0.,0.,0.,4.,10.,60.,89.,72.,
	    60.,60.,52.,30.,20.,10.,0.,0.,4.,10.,60.,92.,68.,54.,40.,25.,13.,
	    0.,0.,0.,0.,1.,8.,20.,60.,95.,93.,69.,65.,45.,30.,20.,0.,0. };
    static doublereal r2ms70[91]	/* was [13][7] */ = { 4.,10.,30.,32.,
	    41.,41.,32.,29.,34.,28.,15.,3.,1.,4.,10.,30.,32.,31.,38.,32.,28.,
	    15.,3.,1.,0.,0.,4.,10.,30.,32.,20.,32.,28.,15.,3.,1.,0.,0.,0.,2.,
	    6.,30.,15.,35.,30.,34.,26.,19.,8.,3.,0.,0.,2.,6.,30.,11.,28.,38.,
	    29.,29.,25.,12.,5.,0.,0.,2.,6.,30.,8.,32.,30.,20.,14.,8.,0.,0.,0.,
	    0.,1.,2.,10.,20.,5.,7.,31.,23.,18.,15.,10.,0.,0. };
    static doublereal rk1ms70[91]	/* was [13][7] */ = { 2.4,6.,.6,-.8,
	    0.,.7,-.2,-1.6,-.533,-.1,-.067,0.,0.,2.4,6.,.6,1.2,-.35,.4,-.2,
	    -1.6,-.533,-.1,-.067,0.,0.,2.4,6.,.6,3.4,-.8,-.176,-1.65,-.533,
	    -.1,-.067,0.,0.,0.,1.2,3.333,5.,-1.,0.,-.216,-1.35,-.433,-.4,-.1,
	    0.,0.,0.,1.2,3.333,5.8,-.85,-.4,0.,-.267,-1.1,-.333,-.4,-.2,0.,0.,
	    1.2,3.333,6.4,-.6,-.233,-.7,-.5,-.6,-.267,0.,0.,0.,0.,1.4,2.4,4.,
	    7.,-.2,-.686,-.072,-1.,-.5,-.5,-.5,0.,0. };
    static doublereal rk2ms70[91]	/* was [13][7] */ = { 1.2,2.,.4,1.8,
	    0.,-.9,-.3,.5,-.12,-.65,-.4,-.1,-.033,1.2,2.,.4,-.2,.35,-.6,-.057,
	    -.65,-.4,-.1,-.033,0.,0.,1.2,2.,.4,-2.4,.8,-.047,-.65,-.4,-.1,
	    -.033,0.,0.,0.,.8,1.6,-3.,1.,-.25,.4,-.16,-.35,-.367,-.25,-.1,0.,
	    0.,.8,1.6,-3.8,.85,.333,-.45,0.,-.2,-.433,-.35,-.1,0.,0.,.8,1.6,
	    -4.4,.6,-.033,-.5,-.2,-.3,-.2,0.,0.,0.,0.,.2,.8,2.,-3.,.2,.686,
	    -.145,-.25,-.1,-.25,-.2,0.,0. };
    static integer j1ms140[7] = { 11,11,10,10,9,9,12 };
    static integer j2ms140[7] = { 11,11,10,9,10,10,12 };
    static doublereal h1s140[91]	/* was [13][7] */ = { 75.,85.,90.,95.,
	    100.,120.,130.,140.,200.,220.,250.,0.,0.,75.,85.,90.,95.,100.,
	    120.,130.,140.,200.,220.,250.,0.,0.,75.,85.,90.,95.,100.,120.,
	    140.,200.,220.,250.,0.,0.,0.,75.,80.,95.,100.,120.,140.,200.,220.,
	    250.,270.,0.,0.,0.,75.,80.,95.,100.,120.,200.,220.,250.,270.,0.,
	    0.,0.,0.,75.,80.,95.,100.,130.,200.,220.,250.,270.,0.,0.,0.,0.,
	    75.,80.,85.,95.,100.,110.,140.,180.,200.,220.,250.,270.,0. };
    static doublereal h2s140[91]	/* was [13][7] */ = { 75.,80.,90.,95.,
	    100.,120.,130.,155.,200.,220.,250.,0.,0.,75.,80.,90.,95.,100.,
	    120.,130.,160.,200.,220.,250.,0.,0.,75.,80.,90.,95.,100.,120.,
	    165.,200.,220.,250.,0.,0.,0.,75.,80.,95.,100.,120.,180.,200.,250.,
	    270.,0.,0.,0.,0.,75.,80.,95.,100.,120.,160.,200.,220.,250.,270.,
	    0.,0.,0.,75.,80.,95.,100.,130.,160.,200.,220.,250.,270.,0.,0.,0.,
	    75.,80.,90.,95.,100.,110.,140.,180.,200.,220.,250.,270.,0. };
    static doublereal r1ms140[91]	/* was [13][7] */ = { 6.,30.,60.,63.,
	    59.,59.,66.,66.,38.,14.,1.,0.,0.,6.,30.,60.,63.,69.,62.,66.,66.,
	    38.,14.,1.,0.,0.,6.,30.,60.,63.,80.,65.,65.,38.,14.,1.,0.,0.,0.,
	    4.,10.,60.,85.,66.,66.,38.,22.,9.,1.,0.,0.,0.,4.,10.,60.,89.,71.,
	    42.,26.,17.,10.,0.,0.,0.,0.,4.,10.,60.,93.,71.,48.,35.,22.,10.,0.,
	    0.,0.,0.,1.,8.,20.,60.,95.,93.,72.,60.,58.,40.,26.,13.,0. };
    static doublereal r2ms140[91]	/* was [13][7] */ = { 4.,10.,30.,32.,
	    41.,41.,30.,30.,10.,6.,1.,0.,0.,4.,10.,30.,32.,31.,38.,31.,29.,9.,
	    6.,1.,0.,0.,4.,10.,30.,32.,20.,35.,26.,9.,6.,1.,0.,0.,0.,2.,6.,
	    30.,15.,34.,24.,10.,5.,1.,0.,0.,0.,0.,2.,6.,30.,11.,28.,37.,21.,
	    14.,8.,5.,0.,0.,0.,2.,6.,30.,7.,29.,36.,29.,20.,13.,5.,0.,0.,0.,
	    1.,2.,10.,20.,5.,7.,28.,32.,28.,20.,14.,7.,0. };
    static doublereal rk1ms140[91]	/* was [13][7] */ = { 2.4,6.,.6,-.8,
	    0.,.7,0.,-.467,-1.2,-.433,0.,0.,0.,2.4,6.,.6,1.2,-.35,.4,0.,-.467,
	    -1.2,-.433,0.,0.,0.,2.4,6.,.6,3.4,-.75,0.,-.45,-1.2,-.433,0.,0.,
	    0.,0.,1.2,3.333,5.,-.95,0.,-.467,-.8,-.433,-.4,0.,0.,0.,0.,1.2,
	    3.333,5.8,-.9,-.363,-.8,-.3,-.35,-.3,0.,0.,0.,0.,1.2,3.333,6.6,
	    -.733,-.329,-.65,-.433,-.6,-.267,0.,0.,0.,0.,1.4,2.4,4.,7.,-.2,
	    -.7,-.3,-.1,-.9,-.467,-.65,-.333,0. };
    static doublereal rk2ms140[91]	/* was [13][7] */ = { 1.2,2.,.4,1.8,
	    0.,-1.1,0.,-.444,-.2,-.166,0.,0.,0.,1.2,2.,.4,-.2,.35,-.7,-.067,
	    -.5,-.15,-.166,0.,0.,0.,1.2,2.,.4,-2.4,.75,-.2,-.486,-.15,-.166,
	    0.,0.,0.,0.,.8,1.6,-3.,.95,-.167,-.7,-.1,-.2,0.,0.,0.,0.,0.,.8,
	    1.6,-3.8,.85,.225,-.4,-.35,-.2,-.15,-.133,0.,0.,0.,.8,1.6,-4.6,
	    .733,.233,-.175,-.45,-.233,-.4,-.1,0.,0.,0.,.2,.8,2.,-3.,.2,.7,.1,
	    -.2,-.4,-.2,-.35,-.167,0. };
    static integer j1mr70[7] = { 12,12,12,9,10,11,13 };
    static integer j2mr70[7] = { 9,9,10,13,12,11,11 };
    static doublereal h1r70[91]	/* was [13][7] */ = { 75.,80.,90.,95.,100.,
	    120.,140.,180.,200.,220.,250.,270.,0.,75.,80.,90.,95.,100.,120.,
	    145.,180.,200.,220.,250.,270.,0.,75.,80.,90.,95.,100.,120.,145.,
	    180.,200.,220.,250.,270.,0.,75.,95.,100.,110.,140.,180.,200.,250.,
	    270.,0.,0.,0.,0.,75.,95.,125.,150.,185.,195.,200.,220.,250.,270.,
	    0.,0.,0.,75.,95.,100.,150.,160.,170.,190.,200.,220.,250.,270.,0.,
	    0.,75.,80.,85.,95.,100.,140.,160.,170.,190.,200.,220.,250.,270. };
    static doublereal h2r70[91]	/* was [13][7] */ = { 75.,95.,100.,120.,180.,
	    200.,220.,250.,270.,0.,0.,0.,0.,75.,95.,100.,120.,180.,200.,220.,
	    250.,270.,0.,0.,0.,0.,75.,95.,100.,120.,130.,190.,200.,220.,250.,
	    270.,0.,0.,0.,75.,80.,85.,95.,100.,110.,130.,180.,190.,200.,220.,
	    250.,270.,75.,80.,85.,95.,100.,125.,150.,190.,200.,220.,250.,270.,
	    0.,75.,80.,85.,95.,100.,150.,190.,200.,220.,250.,270.,0.,0.,75.,
	    85.,95.,100.,140.,180.,190.,200.,220.,250.,270.,0.,0. };
    static doublereal r1mr70[91]	/* was [13][7] */ = { 13.,17.,57.,57.,
	    30.,53.,58.,38.,33.,14.,6.,2.,0.,13.,17.,57.,57.,37.,56.,56.,38.,
	    33.,14.,6.,2.,0.,13.,17.,57.,57.,47.,58.,55.,37.,33.,14.,6.,2.,0.,
	    5.,65.,54.,58.,58.,38.,33.,9.,1.,0.,0.,0.,0.,5.,65.,65.,54.,40.,
	    40.,45.,26.,17.,10.,0.,0.,0.,5.,65.,76.,56.,57.,48.,44.,51.,35.,
	    22.,10.,0.,0.,3.,11.,35.,75.,90.,65.,63.,54.,54.,50.,40.,26.,13. }
	    ;
    static doublereal r2mr70[91]	/* was [13][7] */ = { 7.,43.,70.,47.,
	    15.,17.,10.,4.,0.,0.,0.,0.,0.,7.,43.,63.,44.,17.,17.,10.,4.,0.,0.,
	    0.,0.,0.,7.,43.,53.,42.,42.,13.,17.,10.,4.,0.,0.,0.,0.,3.,5.,26.,
	    34.,46.,42.,41.,23.,16.,16.,10.,1.,0.,3.,5.,26.,34.,35.,35.,42.,
	    25.,22.,14.,8.,5.,0.,3.,5.,26.,34.,24.,41.,31.,26.,20.,13.,5.,0.,
	    0.,3.,15.,15.,10.,35.,35.,30.,34.,20.,14.,7.,0.,0. };
    static doublereal rk1mr70[91]	/* was [13][7] */ = { .8,4.,0.,-5.4,
	    1.15,.25,-.5,-.25,-.95,-.267,-.2,-.067,0.,.8,4.,0.,-4.,.95,0.,
	    -.514,-.25,-.95,-.267,-.2,-.067,0.,.8,4.,0.,-2.,.55,-.12,-.514,
	    -.2,-.95,-.267,-.2,-.067,0.,3.,-2.2,.4,0.,-.5,-.25,-.48,-.4,-.033,
	    0.,0.,0.,0.,3.,0.,-.44,-.466,0.,1.,-.95,-.3,-.35,-.3,0.,0.,0.,3.,
	    2.2,-.4,.1,-.9,-.2,.7,-.8,-.433,-.6,-.267,0.,0.,1.6,4.8,4.,3.,
	    -.625,-.1,-.9,0.,-.4,-.5,-.467,-.65,-.3 };
    static doublereal rk2mr70[91]	/* was [13][7] */ = { 1.8,5.4,-1.15,
	    -.533,.1,-.35,-.2,-.2,0.,0.,0.,0.,0.,1.8,4.,-.95,-.45,0.,-.35,-.2,
	    -.2,0.,0.,0.,0.,0.,1.8,2.,-.55,0.,-.483,.4,-.35,-.2,-.2,0.,0.,0.,
	    0.,.4,4.2,.8,2.4,-.4,-.05,-.36,-.7,0.,-.3,-.3,-.05,0.,.4,4.2,.8,
	    .2,0.,.28,-.425,-.3,-.4,-.2,-.15,-.133,0.,.4,4.2,.8,-2.,.34,-.25,
	    -.5,-.3,-.233,-.4,-.1,0.,0.,1.2,0.,-1.,.625,0.,-.5,.4,-.7,-.2,
	    -.35,-.167,0.,0. };
    static integer j1mr140[7] = { 12,12,11,12,9,9,13 };
    static integer j2mr140[7] = { 10,9,10,12,13,13,12 };
    static doublereal h1r140[91]	/* was [13][7] */ = { 75.,80.,90.,95.,
	    100.,115.,130.,145.,200.,220.,250.,270.,0.,75.,80.,90.,95.,100.,
	    110.,120.,145.,200.,220.,250.,270.,0.,75.,80.,90.,95.,100.,115.,
	    150.,200.,220.,250.,270.,0.,0.,75.,95.,100.,120.,130.,140.,150.,
	    190.,200.,220.,250.,270.,0.,75.,95.,120.,150.,190.,200.,220.,250.,
	    270.,0.,0.,0.,0.,75.,95.,100.,145.,190.,200.,220.,250.,270.,0.,0.,
	    0.,0.,75.,80.,85.,95.,100.,120.,160.,170.,190.,200.,220.,250.,
	    270. };
    static doublereal h2r140[91]	/* was [13][7] */ = { 75.,95.,100.,
	    115.,130.,175.,200.,220.,250.,270.,0.,0.,0.,75.,95.,100.,110.,
	    175.,200.,220.,250.,270.,0.,0.,0.,0.,75.,95.,100.,115.,130.,180.,
	    200.,220.,250.,270.,0.,0.,0.,75.,80.,85.,95.,100.,120.,130.,190.,
	    200.,220.,250.,270.,0.,75.,80.,85.,95.,100.,120.,140.,160.,190.,
	    200.,220.,250.,270.,75.,80.,85.,95.,100.,145.,165.,180.,190.,200.,
	    220.,250.,270.,75.,85.,95.,100.,120.,145.,170.,190.,200.,220.,
	    250.,270.,0. };
    static doublereal r1mr140[91]	/* was [13][7] */ = { 13.,17.,57.,57.,
	    28.,51.,56.,56.,12.,8.,1.,0.,0.,13.,17.,57.,57.,36.,46.,55.,56.,
	    10.,8.,1.,0.,0.,13.,17.,57.,57.,46.,56.,55.,12.,8.,1.,0.,0.,0.,5.,
	    65.,54.,59.,56.,56.,53.,23.,16.,13.,3.,1.,0.,5.,65.,65.,54.,29.,
	    16.,16.,10.,2.,0.,0.,0.,0.,5.,65.,76.,58.,36.,25.,20.,12.,7.,0.,
	    0.,0.,0.,3.,11.,35.,75.,91.,76.,58.,49.,45.,32.,28.,20.,12. };
    static doublereal r2mr140[91]	/* was [13][7] */ = { 7.,43.,72.,49.,
	    44.,14.,7.,4.,1.,0.,0.,0.,0.,7.,43.,64.,51.,14.,7.,4.,1.,0.,0.,0.,
	    0.,0.,7.,43.,54.,44.,44.,13.,7.,4.,1.,0.,0.,0.,0.,3.,5.,26.,34.,
	    46.,41.,44.,9.,11.,7.,2.,1.,0.,3.,5.,26.,34.,35.,35.,40.,40.,16.,
	    14.,9.,5.,2.,3.,5.,26.,34.,24.,40.,40.,32.,19.,20.,10.,7.,3.,3.,
	    15.,15.,9.,24.,35.,40.,28.,28.,20.,10.,8.,0. };
    static doublereal rk1mr140[91]	/* was [13][7] */ = { .8,4.,0.,-5.8,
	    1.533,.333,0.,-.8,-.2,-.233,-.05,0.,0.,.8,4.,0.,-4.2,1.3,.6,.04,
	    -.836,-.1,-.233,-.05,0.,0.,.8,4.,0.,-2.2,.667,-.029,-.86,-.2,
	    -.233,-.05,0.,0.,0.,3.,-2.2,.25,-.3,0.,-.3,-.75,-.7,-.15,-.333,
	    -.1,-.033,0.,3.,0.,-.367,-.625,-1.3,0.,-.2,-.4,-.067,0.,0.,0.,0.,
	    3.,2.2,-.4,-.489,-1.1,-.25,-.267,-.25,-.2,0.,0.,0.,0.,1.6,4.8,4.,
	    3.2,-.75,-.45,-.9,-.2,-1.3,-.2,-.267,-.4,-.3 };
    static doublereal rk2mr140[91]	/* was [13][7] */ = { 1.8,5.8,-1.533,
	    -.333,-.667,-.28,-.15,-.1,-.05,0.,0.,0.,0.,1.8,4.2,-1.3,-.569,
	    -.28,-.15,-.1,-.05,0.,0.,0.,0.,0.,1.8,2.2,-.667,0.,-.62,-.3,-.15,
	    -.1,-.05,0.,0.,0.,0.,.4,4.2,.8,2.4,-.25,.3,-.583,.2,-.2,-.167,
	    -.05,-.033,0.,.4,4.2,.8,.02,0.,.25,0.,-.6,-.2,-.25,-.133,-.15,
	    -.067,.4,4.2,.8,-2.,.356,0.,-.533,-1.3,.1,-.5,-.1,-.2,-.1,1.2,0.,
	    -1.2,.75,.44,.2,-.6,0.,-.4,-.333,-.1,-.2,0. };
    static integer j1mw70[7] = { 13,13,13,13,9,8,9 };
    static integer j2mw70[7] = { 10,10,11,11,9,8,11 };
    static doublereal h1w70[91]	/* was [13][7] */ = { 75.,80.,85.,95.,100.,
	    110.,125.,145.,180.,200.,220.,250.,270.,75.,80.,85.,95.,100.,110.,
	    120.,150.,180.,200.,220.,250.,270.,75.,80.,85.,95.,100.,110.,120.,
	    155.,180.,200.,220.,250.,270.,75.,80.,90.,100.,110.,120.,140.,
	    160.,190.,200.,220.,250.,270.,75.,80.,90.,110.,150.,200.,220.,
	    250.,270.,0.,0.,0.,0.,75.,80.,90.,100.,150.,200.,250.,270.,0.,0.,
	    0.,0.,0.,75.,80.,90.,100.,120.,130.,140.,200.,270.,0.,0.,0.,0. };
    static doublereal h2w70[91]	/* was [13][7] */ = { 75.,90.,95.,100.,110.,
	    125.,190.,200.,250.,270.,0.,0.,0.,75.,90.,95.,100.,110.,125.,190.,
	    200.,250.,270.,0.,0.,0.,75.,90.,95.,100.,110.,120.,145.,190.,200.,
	    250.,270.,0.,0.,75.,80.,95.,100.,110.,120.,150.,200.,220.,250.,
	    270.,0.,0.,75.,80.,90.,95.,110.,145.,200.,250.,270.,0.,0.,0.,0.,
	    75.,80.,90.,100.,140.,150.,200.,250.,0.,0.,0.,0.,0.,75.,80.,85.,
	    90.,100.,120.,130.,140.,160.,200.,270.,0.,0. };
    static doublereal r1mw70[91]	/* was [13][7] */ = { 28.,35.,65.,65.,
	    28.,44.,46.,50.,25.,25.,10.,5.,0.,28.,35.,65.,65.,36.,49.,47.,47.,
	    25.,25.,10.,5.,0.,28.,35.,65.,65.,48.,54.,51.,43.,25.,25.,10.,5.,
	    0.,16.,24.,66.,54.,58.,50.,50.,38.,25.,25.,10.,5.,0.,16.,24.,66.,
	    66.,46.,30.,20.,6.,3.,0.,0.,0.,0.,16.,24.,66.,76.,49.,32.,12.,7.,
	    0.,0.,0.,0.,0.,6.,19.,67.,91.,64.,68.,60.,40.,12.,0.,0.,0.,0. };
    static doublereal r2mw70[91]	/* was [13][7] */ = { 5.,35.,35.,72.,
	    56.,54.,12.,12.,2.,0.,0.,0.,0.,5.,35.,35.,64.,51.,53.,12.,12.,2.,
	    0.,0.,0.,0.,5.,35.,35.,52.,46.,49.,41.,12.,12.,2.,0.,0.,0.,4.,10.,
	    40.,46.,42.,50.,41.,12.,7.,2.,0.,0.,0.,4.,10.,30.,34.,34.,51.,14.,
	    4.,2.,0.,0.,0.,0.,4.,10.,30.,24.,45.,48.,20.,5.,0.,0.,0.,0.,0.,2.,
	    6.,17.,23.,9.,36.,32.,40.,40.,20.,6.,0.,0. };
    static doublereal rk1mw70[91]	/* was [13][7] */ = { 1.4,6.,0.,-7.4,
	    1.6,.133,.2,-.714,0.,-.75,-.167,-.25,0.,1.4,6.,0.,-5.8,1.3,-.2,0.,
	    -.733,0.,-.75,-.167,-.25,0.,1.4,6.,0.,-3.4,.6,-.3,-.229,-.72,0.,
	    -.75,-.167,-.25,0.,1.6,4.2,-1.2,.4,-.8,0.,-.6,-.433,0.,-.75,-.167,
	    -.25,0.,1.6,4.2,0.,-.5,-.32,-.5,-.467,-.15,-.1,0.,0.,0.,0.,1.6,
	    4.2,1.,-.54,-.34,-.4,-.25,-.2,0.,0.,0.,0.,0.,2.6,4.8,2.4,-1.35,.4,
	    -.8,-.333,-.4,-.3,0.,0.,0.,0. };
    static doublereal rk2mw70[91]	/* was [13][7] */ = { 2.,0.,7.4,-1.6,
	    -.133,-.646,0.,-.2,-.1,0.,0.,0.,0.,2.,0.,5.8,-1.3,.133,-.631,0.,
	    -.2,-.1,0.,0.,0.,0.,2.,0.,3.4,-.6,.3,-.32,-.644,0.,-.2,-.1,0.,0.,
	    0.,1.2,2.,1.2,-.4,.8,-.3,-.58,-.25,-.167,-.1,0.,0.,0.,1.2,2.,.8,
	    0.,.486,-.673,-.2,-.1,-.066,0.,0.,0.,0.,1.2,2.,-.6,.525,.3,-.56,
	    -.3,-.1,0.,0.,0.,0.,0.,.8,2.2,1.2,-1.4,1.35,-.4,.8,0.,-.5,-.2,
	    -.167,0.,0. };
    static integer j1mw140[7] = { 12,11,11,11,11,10,12 };
    static integer j2mw140[7] = { 10,11,11,11,11,10,12 };
    static doublereal h1w140[91]	/* was [13][7] */ = { 75.,80.,85.,95.,
	    100.,110.,125.,145.,190.,200.,220.,250.,0.,75.,80.,85.,95.,100.,
	    110.,120.,150.,190.,220.,250.,0.,0.,75.,80.,85.,95.,100.,110.,
	    120.,155.,190.,220.,250.,0.,0.,75.,80.,90.,100.,110.,120.,140.,
	    160.,190.,220.,250.,0.,0.,75.,80.,90.,110.,150.,160.,190.,200.,
	    220.,250.,270.,0.,0.,75.,80.,90.,100.,150.,160.,190.,200.,250.,
	    270.,0.,0.,0.,75.,80.,90.,100.,120.,130.,140.,160.,190.,200.,250.,
	    270.,0. };
    static doublereal h2w140[91]	/* was [13][7] */ = { 75.,90.,95.,
	    100.,110.,125.,190.,200.,220.,250.,0.,0.,0.,75.,90.,95.,100.,110.,
	    120.,125.,190.,200.,220.,250.,0.,0.,75.,90.,95.,100.,110.,120.,
	    145.,190.,200.,220.,250.,0.,0.,75.,80.,95.,100.,110.,120.,150.,
	    190.,200.,220.,250.,0.,0.,75.,80.,90.,95.,110.,145.,190.,200.,
	    220.,250.,270.,0.,0.,75.,80.,90.,100.,140.,150.,200.,220.,250.,
	    270.,0.,0.,0.,75.,80.,85.,90.,100.,120.,130.,140.,160.,180.,200.,
	    220.,0. };
    static doublereal r1mw140[91]	/* was [13][7] */ = { 28.,35.,65.,65.,
	    28.,44.,46.,50.,9.,6.,2.,0.,0.,28.,35.,65.,65.,36.,49.,47.,47.,8.,
	    2.,0.,0.,0.,28.,35.,65.,65.,48.,54.,51.,43.,8.,2.,0.,0.,0.,16.,
	    24.,66.,54.,58.,50.,50.,42.,8.,2.,0.,0.,0.,16.,24.,66.,66.,46.,
	    49.,9.,10.,7.,2.,0.,0.,0.,16.,24.,66.,76.,49.,54.,10.,14.,4.,1.,
	    0.,0.,0.,6.,19.,67.,91.,64.,68.,60.,58.,11.,20.,5.,2.,0. };
    static doublereal r2mw140[91]	/* was [13][7] */ = { 5.,35.,35.,72.,
	    56.,54.,5.,5.,1.,0.,0.,0.,0.,5.,35.,35.,64.,51.,53.,53.,5.,5.,1.,
	    0.,0.,0.,5.,35.,35.,52.,46.,49.,41.,5.,5.,1.,0.,0.,0.,4.,10.,40.,
	    46.,42.,50.,41.,5.,5.,1.,0.,0.,0.,4.,10.,30.,34.,34.,51.,10.,5.,
	    3.,1.,0.,0.,0.,4.,10.,30.,24.,45.,48.,4.,2.,1.,0.,0.,0.,0.,2.,6.,
	    17.,23.,9.,36.,32.,40.,39.,29.,1.,0.,0. };
    static doublereal rk1mw140[91]	/* was [13][7] */ = { 1.4,6.,0.,-7.4,
	    1.6,.133,.2,-.911,-.3,-.2,-.066,0.,0.,1.4,6.,0.,-5.8,1.3,-.2,0.,
	    -.975,-.2,-.066,0.,0.,0.,1.4,6.,0.,-3.4,.6,-.3,-.229,-1.,-.2,
	    -.066,0.,0.,0.,1.6,4.2,-1.2,.4,-.8,0.,-.4,-1.133,-.2,-.066,0.,0.,
	    0.,1.6,4.2,0.,-.5,.3,-1.133,.1,-.15,-.166,-.1,0.,0.,0.,1.6,4.2,1.,
	    -.54,.5,-1.466,.4,-.2,-.15,-.0333,0.,0.,0.,2.6,4.8,2.4,-1.35,.4,
	    -.8,-.1,-1.566,.9,-.3,-.15,-.05,0. };
    static doublereal rk2mw140[91]	/* was [13][7] */ = { 2.,0.,7.4,-1.6,
	    -.133,-.754,0.,-.2,-.033,0.,0.,0.,0.,2.,0.,5.8,-1.3,.2,0.,-.738,
	    0.,-.2,-.033,0.,0.,0.,2.,0.,3.4,-.6,.3,-.32,-.8,0.,-.2,-.033,0.,
	    0.,0.,1.2,2.,1.2,-.4,.8,-.3,-.9,0.,-.2,-.033,0.,0.,0.,1.2,2.,.8,
	    0.,.486,-.911,-.5,-.1,-.066,-.05,0.,0.,0.,1.2,2.,-.6,.525,.3,-.88,
	    -.1,-.033,-.05,0.,0.,0.,0.,.8,2.2,1.2,-1.4,1.35,-.4,.8,-.05,-.5,
	    -1.4,-.05,0.,0. };

    /* Builtin functions */
    double d_nint(doublereal *);

    /* Local variables */
    static doublereal h__, z__, r170, r270, r1140, r2140;
    extern /* Subroutine */ int aprok_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/* ---------------------------------------------------------------- */
/*     INPUT DATA : */
/*      hei  -  altitude in km */
/*      xhi  -  solar zenith angle in degree */
/*      it   -  season (month) */
/*      F    -  10.7cm solar radio flux */
/*     OUTPUT DATA : */
/*     R1 -  NO+ concentration (in percent) */
/*     R2 -  O2+ concentration (in percent) */
/*     R3 -  Cb+ concentration (in percent) */
/*     R4 -  O+  concentration (in percent) */

/*  A.D. Danilov and N.V. Smirnova, Improving the 75 to 300 km ion */
/*  composition model of the IRI, Adv. Space Res. 15, #2, 171-177, 1995. */

/* ----------------------------------------------------------------- */
    h__ = *hei;
    z__ = *xhi;
    if (z__ < 20.) {
	z__ = 20.;
    }
    if (z__ > 90.) {
	z__ = 90.;
    }
    if (*it == 1 || *it == 2 || *it == 11 || *it == 12) {
	if (*f < 140.) {
	    aprok_(j1mw70, j2mw70, h1w70, h2w70, r1mw70, r2mw70, rk1mw70, 
		    rk2mw70, &h__, &z__, r1, r2);
	    r170 = *r1;
	    r270 = *r2;
	}
	if (*f > 70.) {
	    aprok_(j1mw140, j2mw140, h1w140, h2w140, r1mw140, r2mw140, 
		    rk1mw140, rk2mw140, &h__, &z__, r1, r2);
	    r1140 = *r1;
	    r2140 = *r2;
	}
	if (*f > 70. && *f < 140.) {
	    *r1 = r170 + (r1140 - r170) * (*f - 70) / 70;
	    *r2 = r270 + (r2140 - r270) * (*f - 70) / 70;
	}
    }
    if (*it == 5 || *it == 6 || *it == 7 || *it == 8) {
	if (*f < 140.) {
	    aprok_(j1ms70, j2ms70, h1s70, h2s70, r1ms70, r2ms70, rk1ms70, 
		    rk2ms70, &h__, &z__, r1, r2);
	    r170 = *r1;
	    r270 = *r2;
	}
	if (*f > 70.) {
	    aprok_(j1ms140, j2ms140, h1s140, h2s140, r1ms140, r2ms140, 
		    rk1ms140, rk2ms140, &h__, &z__, r1, r2);
	    r1140 = *r1;
	    r2140 = *r2;
	}
	if (*f > 70. && *f < 140.) {
	    *r1 = r170 + (r1140 - r170) * (*f - 70) / 70;
	    *r2 = r270 + (r2140 - r270) * (*f - 70) / 70;
	}
    }
    if (*it == 3 || *it == 4 || *it == 9 || *it == 10) {
	if (*f < 140.) {
	    aprok_(j1mr70, j2mr70, h1r70, h2r70, r1mr70, r2mr70, rk1mr70, 
		    rk2mr70, &h__, &z__, r1, r2);
	    r170 = *r1;
	    r270 = *r2;
	}
	if (*f > 70.) {
	    aprok_(j1mr140, j2mr140, h1r140, h2r140, r1mr140, r2mr140, 
		    rk1mr140, rk2mr140, &h__, &z__, r1, r2);
	    r1140 = *r1;
	    r2140 = *r2;
	}
	if (*f > 70. && *f < 140.) {
	    *r1 = r170 + (r1140 - r170) * (*f - 70) / 70;
	    *r2 = r270 + (r2140 - r270) * (*f - 70) / 70;
	}
    }
    *r3 = 0.;
    *r4 = 0.;
    if (h__ < 100.) {
	*r3 = 100 - (*r1 + *r2);
    }
    if (h__ >= 100.) {
	*r4 = 100 - (*r1 + *r2);
    }
    if (*r3 < 0.) {
	*r3 = 0.;
    }
    if (*r4 < 0.) {
	*r4 = 0.;
    }
    *r1 = d_nint(r1);
    *r2 = d_nint(r2);
    *r3 = d_nint(r3);
    *r4 = d_nint(r4);
/* L300: */
    return 0;
} /* ionco2_ */



/* Subroutine */ int aprok_(integer *j1m, integer *j2m, doublereal *h1, 
	doublereal *h2, doublereal *r1m, doublereal *r2m, doublereal *rk1m, 
	doublereal *rk2m, doublereal *hei, doublereal *xhi, doublereal *r1, 
	doublereal *r2)
{
    /* Initialized data */

    static doublereal zm[7] = { 20.,40.,60.,70.,80.,85.,90. };

    /* System generated locals */
    integer i__1;

    /* Local variables */
    static doublereal h__;
    static integer i__;
    static doublereal z__;
    static integer j1, j2, i1, i2, i3;
    static doublereal h01, h02, r01, r02, r11, r12, rk, rk1, rk2;

/* ----------------------------------------------------------------- */
    /* Parameter adjustments */
    rk2m -= 14;
    rk1m -= 14;
    r2m -= 14;
    r1m -= 14;
    h2 -= 14;
    h1 -= 14;
    --j2m;
    --j1m;

    /* Function Body */
    h__ = *hei;
    z__ = *xhi;
    j1 = 1;
    j2 = 1;
    i1 = 1;
    for (i__ = 1; i__ <= 7; ++i__) {
	i1 = i__;
	if (z__ == zm[i__ - 1]) {
	    j1 = 0;
	}
	if (z__ <= zm[i__ - 1]) {
	    goto L11;
	}
/* L1: */
    }
L11:
    i2 = 1;
    i__1 = j1m[i1];
    for (i__ = 2; i__ <= i__1; ++i__) {
	i2 = i__ - 1;
	if (h__ < h1[i__ + i1 * 13]) {
	    goto L22;
	}
	i2 = j1m[i1];
/* L2: */
    }
L22:
    i3 = 1;
    i__1 = j2m[i1];
    for (i__ = 2; i__ <= i__1; ++i__) {
	i3 = i__ - 1;
	if (h__ < h2[i__ + i1 * 13]) {
	    goto L33;
	}
	i3 = j2m[i1];
/* L3: */
    }
L33:
    r01 = r1m[i2 + i1 * 13];
    r02 = r2m[i3 + i1 * 13];
    rk1 = rk1m[i2 + i1 * 13];
    rk2 = rk2m[i3 + i1 * 13];
    h01 = h1[i2 + i1 * 13];
    h02 = h2[i3 + i1 * 13];
    *r1 = r01 + rk1 * (h__ - h01);
    *r2 = r02 + rk2 * (h__ - h02);
    if (j1 == 1) {
	j1 = 0;
	j2 = 0;
	--i1;
	r11 = *r1;
	r12 = *r2;
	goto L11;
    }
    if (j2 == 0) {
	rk = (z__ - zm[i1 - 1]) / (zm[i1] - zm[i1 - 1]);
	*r1 += (r11 - *r1) * rk;
	*r2 += (r12 - *r2) * rk;
    }
    return 0;
} /* aprok_ */



/* Subroutine */ int ioncomp_(doublereal *xy, integer *id, integer *ismo, 
	doublereal *xm, doublereal *hx, doublereal *zd, doublereal *fd, 
	doublereal *fp, doublereal *fs, doublereal *dion)
{
    extern /* Subroutine */ int igrf_sub__(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *);
    static doublereal h__;
    static integer i__, month_sea__;
    static doublereal ro, xl, xioncomp_h__, ro2, xioncomp_n__, xioncomp_o__, 
	    rcl, cov, xhi, rno, xioncomp_he__;
    static integer iddd;
    static doublereal babs, dipl, dimo, xmlt;
    static integer icode;
    static doublereal diont[7], xlati, ryear;
    extern /* Subroutine */ int ionco2_(doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), calion_(integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *);
    static doublereal xlongi, xinvdip;

/* ------------------------------------------------------- */
/*       xy      decimal year */
/*       id       day of year */
/*       ismo    seasonal month (Northern Hemisphere January */
/*                   is ismo=1 and so is Southern H. July) */
/*       xm      MLT in hours */
/*       hx      altitude in km */
/*       zd      solar zenith angle in degrees */
/*       fd      latitude in degrees */
/*       fp      longitude in degrees */
/*       fs      10.7cm solar radio flux */
/*       dion(1)   O+  relative density in percent */
/*       dion(2)   H+  relative density in percent */
/*       dion(3)   N+  relative density in percent */
/*       dion(4)   He+ relative density in percent */
/*       dion(5)   NO+ relative density in percent */
/*       dion(6)   O2+ relative density in percent */
/*       dion(7)   Cluster+ relative density in percent */
/* ------------------------------------------------------- */
    /* Parameter adjustments */
    --dion;

    /* Function Body */
    for (i__ = 1; i__ <= 7; ++i__) {
/* L1122: */
	diont[i__ - 1] = 0.;
    }
    xmlt = *xm;
    iddd = *id;
    ryear = *xy;
    month_sea__ = *ismo;
    h__ = *hx;
    xhi = *zd;
    xlati = *fd;
    xlongi = *fp;
    cov = *fs;
    if (h__ > 300.) {
	igrf_sub__(&xlati, &xlongi, &ryear, &h__, &xl, &icode, &dipl, &babs);
	if (xl > 10.) {
	    xl = 10.;
	}
/*        	icd=1    ! compute INVDIP */
	dimo = .311653;
	calion_(&c__1, &xinvdip, &xl, &dimo, &babs, &dipl, &xmlt, &h__, &iddd,
		 &cov, &xioncomp_o__, &xioncomp_h__, &xioncomp_he__, &
		xioncomp_n__);
	diont[0] = xioncomp_o__ * 100.;
	diont[1] = xioncomp_h__ * 100.;
	diont[2] = xioncomp_n__ * 100.;
	diont[3] = xioncomp_he__ * 100.;
    } else {
	ionco2_(&h__, &xhi, &month_sea__, &cov, &rno, &ro2, &rcl, &ro);
	diont[4] = rno;
	diont[5] = ro2;
	diont[6] = rcl;
	diont[0] = ro;
    }
    for (i__ = 1; i__ <= 7; ++i__) {
	dion[i__] = diont[i__ - 1];
/* L1: */
    }
    return 0;
} /* ioncomp_ */



/* Subroutine */ int ionco1_(doublereal *h__, doublereal *zd, doublereal *fd, 
	doublereal *fs, doublereal *t, doublereal *cn)
{
    /* Initialized data */

    static doublereal po[30]	/* was [5][6] */ = { 0.,0.,0.,0.,98.5,0.,0.,
	    0.,0.,320.,0.,0.,0.,0.,-2.59e-4,2.79e-4,-.00333,-.00352,-.00516,
	    -.0247,0.,0.,0.,0.,-2.5e-6,.00104,-1.79e-4,-4.29e-5,1.01e-5,
	    -.00127 };
    static doublereal ph[30]	/* was [5][6] */ = { -4.97e-7,-.121,-.131,0.,
	    98.1,355.,-191.,-127.,0.,2040.,0.,0.,0.,0.,-4.79e-6,-2e-4,5.67e-4,
	    2.6e-4,0.,-.00508,0.,0.,0.,0.,0.,0.,0.,0.,0.,0. };
    static doublereal pn[30]	/* was [5][6] */ = { .76,-5.62,-4.99,0.,5.79,
	    83.,-369.,-324.,0.,593.,0.,0.,0.,0.,-6.3e-5,-.00674,-.00793,
	    -.00465,0.,-.00326,0.,0.,0.,0.,-1.17e-5,.00488,-.00131,-7.03e-4,
	    0.,-.00238 };
    static doublereal phe[30]	/* was [5][6] */ = { -.895,6.1,5.39,0.,8.01,
	    0.,0.,0.,0.,1200.,0.,0.,0.,0.,-1.04e-5,.0019,9.53e-4,.00106,0.,
	    -.00344,0.,0.,0.,0.,0.,0.,0.,0.,0.,0. };

    /* Builtin functions */
    double cos(doublereal), exp(doublereal);

    /* Local variables */
    static doublereal f;
    static integer i__, j;
    static doublereal p[120]	/* was [5][6][4] */, s, z__, cm[4], hm[4], hx,
	     alh[4], all[4], arg, var[6], beth[4], betl[4];

/* --------------------------------------------------------------- */
/* ion composition model */
/*   A.D. Danilov and A.P. Yaichnikov, A New Model of the Ion */
/*   Composition at 75 to 1000 km for IRI, Adv. Space Res. 5, #7, */
/*   75-79, 107-108, 1985 */

/*       h       altitude in km */
/*       zd      solar zenith angle in degrees */
/*       fd      latitude in degrees */
/*       fs      10.7cm solar radio flux */
/*       t       season (decimal month) */
/*       cn(1)   O+  relative density in percent */
/*       cn(2)   H+  relative density in percent */
/*       cn(3)   N+  relative density in percent */
/*       cn(4)   He+ relative density in percent */
/* Please note: molecular ions are now computed in IONCO2 */
/*       [cn(5)   NO+ relative density in percent */
/*       [cn(6)   O2+ relative density in percent */
/*       [cn(7)   cluster ions  relative density in percent */
/* --------------------------------------------------------------- */

/*        dimension       cn(7),cm(7),hm(7),alh(7),all(7),beth(7), */
/*     &                  betl(7),p(5,6,7),var(6),po(5,6),ph(5,6), */
/*     &                  pn(5,6),phe(5,6),pno(5,6),po2(5,6),pcl(5,6) */
    /* Parameter adjustments */
    --cn;

    /* Function Body */
/*       data pno/-22.4,17.7,-13.4,-4.88,62.3,32.7,0.,19.8,2.07,115., */
/*    &          5*0.,3.94E-3,0.,2.48E-3,2.15E-4,6.67E-3,5*0., */
/*    &          -8.4E-3,0.,-3.64E-3,2.E-3,-2.59E-2/ */
/*       data po2/8.,-12.2,9.9,5.8,53.4,-25.2,0.,-28.5,-6.72,120., */
/*    &          5*0.,-1.4E-2,0.,-9.3E-3,3.3E-3,2.8E-2,5*0.,4.25E-3, */
/*    &          0.,-6.04E-3,3.85E-3,-3.64E-2/ */
/*       data pcl/4*0.,100.,4*0.,75.,10*0.,4*0.,-9.04E-3,-7.28E-3, */
/*    &          2*0.,3.46E-3,-2.11E-2/ */
    z__ = *zd * const_1.umr;
    f = *fd * const_1.umr;
    for (i__ = 1; i__ <= 5; ++i__) {
	for (j = 1; j <= 6; ++j) {
	    p[i__ + (j + 6) * 5 - 36] = po[i__ + j * 5 - 6];
	    p[i__ + (j + 12) * 5 - 36] = ph[i__ + j * 5 - 6];
	    p[i__ + (j + 18) * 5 - 36] = pn[i__ + j * 5 - 6];
	    p[i__ + (j + 24) * 5 - 36] = phe[i__ + j * 5 - 6];
/*               p(i,j,5)=pno(i,j) */
/*               p(i,j,6)=po2(i,j) */
/*               p(i,j,7)=pcl(i,j) */
/* L8: */
	}
    }
    s = 0.;
/*       do 5 i=1,7 */
    for (i__ = 1; i__ <= 4; ++i__) {
	for (j = 1; j <= 6; ++j) {
	    var[j - 1] = p[(j + i__ * 6) * 5 - 35] * cos(z__) + p[(j + i__ * 
		    6) * 5 - 34] * cos(f) + p[(j + i__ * 6) * 5 - 33] * cos((
		    300. - *fs) * .013) + p[(j + i__ * 6) * 5 - 32] * cos((*t 
		    - 6.) * .52) + p[(j + i__ * 6) * 5 - 31];
/* L7: */
	}
	cm[i__ - 1] = var[0];
	hm[i__ - 1] = var[1];
	all[i__ - 1] = var[2];
	betl[i__ - 1] = var[3];
	alh[i__ - 1] = var[4];
	beth[i__ - 1] = var[5];
	hx = *h__ - hm[i__ - 1];
	if (hx < 0.) {
	    goto L1;
	} else if (hx == 0) {
	    goto L2;
	} else {
	    goto L3;
	}
L1:
	arg = hx * (hx * all[i__ - 1] + betl[i__ - 1]);
	cn[i__] = 0.;
	if (arg > -argexp_1.argmax) {
	    cn[i__] = cm[i__ - 1] * exp(arg);
	}
	goto L4;
L2:
	cn[i__] = cm[i__ - 1];
	goto L4;
L3:
	arg = hx * (hx * alh[i__ - 1] + beth[i__ - 1]);
	cn[i__] = 0.;
	if (arg > -argexp_1.argmax) {
	    cn[i__] = cm[i__ - 1] * exp(arg);
	}
L4:
	if (cn[i__] < cm[i__ - 1] * .005) {
	    cn[i__] = 0.;
	}
	if (cn[i__] > cm[i__ - 1]) {
	    cn[i__] = cm[i__ - 1];
	}
	s += cn[i__];
/* L5: */
    }
/*       do 6 i=1,7 */
    for (i__ = 1; i__ <= 4; ++i__) {
/* L6: */
	cn[i__] = cn[i__] / s * 100.;
    }
    return 0;
} /* ionco1_ */



/* Subroutine */ int calion_(integer *crd, doublereal *invdip, doublereal *fl,
	 doublereal *dimo, doublereal *b0, doublereal *dipl, doublereal *mlt, 
	doublereal *alt, integer *ddd, doublereal *f107, doublereal *no, 
	doublereal *nh, doublereal *nhe, doublereal *nn)
{
    /* Initialized data */

    static struct {
	doublereal e_1[8];
	doublereal fill_2[4];
	doublereal e_3[8];
	doublereal fill_4[4];
	doublereal e_5[8];
	doublereal fill_6[4];
	doublereal e_7[8];
	doublereal fill_8[4];
	doublereal e_9[8];
	doublereal fill_10[4];
	doublereal e_11[8];
	doublereal fill_12[4];
	doublereal e_13[8];
	doublereal fill_14[4];
	doublereal e_15[8];
	doublereal fill_16[4];
	doublereal e_17[8];
	doublereal fill_18[4];
	doublereal e_19[8];
	doublereal fill_20[4];
	doublereal e_21[8];
	doublereal fill_22[4];
	doublereal e_23[8];
	doublereal fill_24[4];
	doublereal e_25[8];
	doublereal fill_26[4];
	doublereal e_27[8];
	doublereal fill_28[4];
	doublereal e_29[8];
	doublereal fill_30[4];
	doublereal e_31[8];
	doublereal fill_32[4];
	doublereal e_33[8];
	doublereal fill_34[4];
	doublereal e_35[8];
	doublereal fill_36[4];
	doublereal e_37[8];
	doublereal fill_38[4];
	doublereal e_39[8];
	doublereal fill_40[4];
	doublereal e_41[8];
	doublereal fill_42[4];
	doublereal e_43[8];
	doublereal fill_44[4];
	doublereal e_45[8];
	doublereal fill_46[4];
	doublereal e_47[8];
	doublereal fill_48[4];
	doublereal e_49[8];
	doublereal fill_50[4];
	doublereal e_51[8];
	doublereal fill_52[4];
	doublereal e_53[8];
	doublereal fill_54[4];
	doublereal e_55[8];
	doublereal fill_56[4];
	doublereal e_57[8];
	doublereal fill_58[4];
	doublereal e_59[8];
	doublereal fill_60[4];
	doublereal e_61[8];
	doublereal fill_62[4];
	doublereal e_63[8];
	doublereal fill_64[4];
	doublereal e_65[8];
	doublereal fill_66[4];
	doublereal e_67[8];
	doublereal fill_68[4];
	doublereal e_69[8];
	doublereal fill_70[4];
	doublereal e_71[8];
	doublereal fill_72[4];
	doublereal e_73[8];
	doublereal fill_74[4];
	doublereal e_75[8];
	doublereal fill_76[4];
	doublereal e_77[8];
	doublereal fill_78[4];
	doublereal e_79[8];
	doublereal fill_80[4];
	doublereal e_81[8];
	doublereal fill_82[4];
	doublereal e_83[8];
	doublereal fill_84[4];
	doublereal e_85[8];
	doublereal fill_86[4];
	doublereal e_87[8];
	doublereal fill_88[4];
	doublereal e_89[8];
	doublereal fill_90[4];
	doublereal e_91[8];
	doublereal fill_92[4];
	doublereal e_93[8];
	doublereal fill_94[4];
	doublereal e_95[8];
	doublereal fill_96[4];
	doublereal e_97[8];
	doublereal fill_98[4];
	} equiv_390 = { -.012838, -.11873, -.50096, -.75121, -.013612, -.114, 
		-.38369, -.8219, {0}, 3.3892e-9, -7.9543e-8, 3.9699e-7, 
		4.7106e-6, -.005555, .072284, .28162, .36727, {0}, -.0049527, 
		.088754, .54222, .98731, -.0088001, .059514, .3341, .86943, {
		0}, 9.6584e-9, 1.2749e-7, -4.2933e-7, -1.1517e-5, -.0067878, 
		-.092827, -.44591, -.51681, {0}, -2.8249e-4, .037834, .042261,
		 -.21953, -.0025424, .02467, .12217, .043418, {0}, 9.2209e-9, 
		-3.7071e-8, -1.2006e-7, 7.7259e-6, -6.6143e-4, .018185, 
		.14901, .14628, {0}, -.0015708, -.033659, -.13304, -.073014, 
		-.0030189, -.0053528, -.12365, -.1619, {0}, -.0015997, 
		-.13753, -.57614, -.34116, -5.1701e-4, -.10798, -.33668, 
		-.48689, {0}, -1.7077e-10, -6.7705e-8, 1.995e-7, -1.3414e-6, 
		-3.4954e-4, .049821, .14641, .079939, {0}, 6.0805e-4, 
		-.007837, .042972, .038833, -2.9469e-5, -.0054609, .015156, 
		.029131, {0}, -3.2035e-9, 5.0045e-8, -3.6102e-8, -6.9663e-7, 
		4.0382e-5, -.0073866, -.042536, .0094168, {0}, 4.6574e-4, 
		.017354, .036207, .010871, 3.1389e-6, .0055822, .026524, 
		.016115, {0}, -3.0838e-9, -1.2451e-8, -8.1212e-9, 5.1607e-7, 
		5.8065e-5, -.0022066, -.0055077, -.011809, {0}, -.0017719, 
		-.055262, -.30608, -.52445, .0016808, -.0094552, -.11957, 
		-.48438, {0}, 1.7746e-9, -1.6397e-8, 7.6853e-8, 1.5335e-6, 
		-2.0046e-4, -.0070287, .060421, .10166, {0}, .0020281, 
		.0090203, .06809, .11675, .0011039, .015038, -.0039161, .128, 
		{0}, 5.955e-10, -3.1764e-9, -5.5044e-8, -9.3384e-7, .0010451, 
		-.0049536, -.010382, -.061316, {0}, -8.4087e-4, 3.22e-4, 
		-.0046984, -.0089381, -1.0243e-4, -.002197, .011853, -.016983,
		 {0}, 7.3645e-10, 4.4309e-9, 2.6068e-8, 1.5077e-7, -1.633e-4, 
		.0018018, -.0079129, .014167, {0}, .0016083, -.047726, 
		-.15518, -.0049602, .0013405, -.051372, .054055, .0035405, {0}
		, -1.902e-10, -1.6271e-8, -2.0579e-8, -6.4438e-7, -4.031e-4, 
		.015935, -.039953, -.0078288, {0}, -5.6389e-4, -.016568, 
		-.021672, -.010283, 2.964e-4, -7.7984e-4, .0071875, -.0032292,
		 {0}, 2.1437e-10, 8.7942e-9, 9.6017e-9, -3.9542e-8, 3.3187e-4,
		 -9.883e-4, .0060955, .0087041, {0}, -9.153e-5, .0039707, 
		.0076241, .0017114, 1.5748e-4, -6.1488e-4, -.0030049, 
		-.0036171, {0}, -8.1471e-4, -.013873, -.15461, -.11767, 
		-.0010201, -.0054875, -.0045588, -.15451, {0}, -1.4259e-9, 
		-1.3387e-8, 3.9902e-8, 2.1163e-7, -3.4733e-4, -.0068829, 
		-.0070102, -.011808, {0}, -5.3451e-4, -.005541, .0039501, 
		-.0014566, -1.8801e-4, .009091, 8.8947e-5, .028659, {0}, 
		-6.4989e-10, 3.276e-9, -9.3205e-9, -2.4207e-7, 1.337e-4, 
		-.003618, .0046705, -2.7932e-4, {0}, 9.7174e-5, .0015026, 
		.0036564, .001979, -3.8261e-5, 4.6157e-4, -.0015544, 
		-.0027786, {0}, -9.1365e-4, 5.413e-4, -.018591, -.0088082, 
		2.5237e-4, -.0037871, .052816, .15649, {0}, 3.6711e-10, 
		-4.3665e-9, -1.5121e-8, -4.2416e-8, 9.9983e-5, -9.0714e-5, 
		-.032857, -.0048513, {0}, -2.8037e-5, -.0085634, -.010493, 
		.0010644, 5.3315e-5, 6.0385e-4, .0075772, -.0024998, {0}, 
		7.6651e-11, 2.2732e-9, 5.6094e-9, -2.3959e-9, 6.1462e-5, 
		1.6097e-4, 3.3781e-4, -9.9171e-4, {0}, .0015422, -.0073394, 
		.02303, .094817, -2.2161e-4, -.0072617, .053629, -.080071, {0}
		, 1.4647e-10, -9.4292e-9, -4.0654e-8, -7.9695e-7, 3.8285e-4, 
		-.0019084, -.02243, -.0024185, {0}, -1.7107e-5, -.0041713, 
		-6.5416e-4, -.0041841, 3.689e-5, .0035375, .0024118, .0064073,
		 {0}, 2.1872e-10, 2.0113e-9, 1.286e-10, -5.9703e-8, 
		-2.8965e-6, -8.3529e-4, 3.1271e-4, -2.6383e-4, {0}, 1.4265e-4,
		 .0025152, -.035348, .042488, -2.6102e-5, -.007738, -.014393, 
		-.0047954, {0}, 6.1624e-10, -1.4286e-10, 1.1426e-8, 4.4664e-8,
		 2.1884e-5, 1.0796e-4, -.0066816, -.008672, {0}, 1.2512e-4, 
		-.0027636, -.0040794, .0016134, 5.6101e-5, 5.0314e-4, 
		.0017099, .0015965, {0}, 4.8548e-4, .0014591, .024538, 
		.045698, 3.2898e-4, -.013759, .0042075, -.0071514, {0}, 
		-1.6132e-10, -3.7848e-9, -2.8703e-8, -2.0829e-7, 4.8422e-5, 
		5.3603e-4, -.0020012, .0070614, {0}, -1.4022e-5, -.0021361, 
		.0011241, -.0012046, 8.9837e-7, 6.4259e-4, -6.8627e-4, 
		-.0018408, {0}, -1.1307e-4, -.00173, .0030503, -1.0719e-4, 
		2.0305e-5, -.0064764, -.016996, -.011994, {0}, 1.6024e-10, 
		-6.3066e-12, 7.4212e-10, 1.853e-7, 1.3643e-5, -1.6915e-4, 
		.0019841, -.0047379, {0}, 2.7979e-4, -.001819, -.0091099, 
		.0085126, 1.1488e-4, -.0073788, -.010077, -.020841, {0}, 
		6.1773e-11, -1.1929e-9, -6.342e-9, 4.9934e-8, 4.8798e-5, 
		3.5767e-4, -4.0022e-4, -.0029637, {0}, -2.7536e-5, -.0024384, 
		-.0024364, .0077988, -1.7122e-6, -.0038287, -.0035827, 
		-.0049867, {0}, 3.7412e-5, .0045096, .0078412, .0014431, 
		1.3591e-4, -.0032403, .0010792, -.014069 };

#define doh ((doublereal *)&equiv_390)

    static struct {
	doublereal e_1[8];
	doublereal fill_2[4];
	doublereal e_3[8];
	doublereal fill_4[4];
	doublereal e_5[8];
	doublereal fill_6[4];
	doublereal e_7[8];
	doublereal fill_8[4];
	doublereal e_9[8];
	doublereal fill_10[4];
	doublereal e_11[8];
	doublereal fill_12[4];
	doublereal e_13[8];
	doublereal fill_14[4];
	doublereal e_15[8];
	doublereal fill_16[4];
	doublereal e_17[8];
	doublereal fill_18[4];
	doublereal e_19[8];
	doublereal fill_20[4];
	doublereal e_21[8];
	doublereal fill_22[4];
	doublereal e_23[8];
	doublereal fill_24[4];
	doublereal e_25[8];
	doublereal fill_26[4];
	doublereal e_27[8];
	doublereal fill_28[4];
	doublereal e_29[8];
	doublereal fill_30[4];
	doublereal e_31[8];
	doublereal fill_32[4];
	doublereal e_33[8];
	doublereal fill_34[4];
	doublereal e_35[8];
	doublereal fill_36[4];
	doublereal e_37[8];
	doublereal fill_38[4];
	doublereal e_39[8];
	doublereal fill_40[4];
	doublereal e_41[8];
	doublereal fill_42[4];
	doublereal e_43[8];
	doublereal fill_44[4];
	doublereal e_45[8];
	doublereal fill_46[4];
	doublereal e_47[8];
	doublereal fill_48[4];
	doublereal e_49[8];
	doublereal fill_50[4];
	doublereal e_51[8];
	doublereal fill_52[4];
	doublereal e_53[8];
	doublereal fill_54[4];
	doublereal e_55[8];
	doublereal fill_56[4];
	doublereal e_57[8];
	doublereal fill_58[4];
	doublereal e_59[8];
	doublereal fill_60[4];
	doublereal e_61[8];
	doublereal fill_62[4];
	doublereal e_63[8];
	doublereal fill_64[4];
	doublereal e_65[8];
	doublereal fill_66[4];
	doublereal e_67[8];
	doublereal fill_68[4];
	doublereal e_69[8];
	doublereal fill_70[4];
	doublereal e_71[8];
	doublereal fill_72[4];
	doublereal e_73[8];
	doublereal fill_74[4];
	doublereal e_75[8];
	doublereal fill_76[4];
	doublereal e_77[8];
	doublereal fill_78[4];
	doublereal e_79[8];
	doublereal fill_80[4];
	doublereal e_81[8];
	doublereal fill_82[4];
	doublereal e_83[8];
	doublereal fill_84[4];
	doublereal e_85[8];
	doublereal fill_86[4];
	doublereal e_87[8];
	doublereal fill_88[4];
	doublereal e_89[8];
	doublereal fill_90[4];
	doublereal e_91[8];
	doublereal fill_92[4];
	doublereal e_93[8];
	doublereal fill_94[4];
	doublereal e_95[8];
	doublereal fill_96[4];
	doublereal e_97[8];
	doublereal fill_98[4];
	} equiv_391 = { -3.1678, -1.5293, -.81841, -.66978, -2.8141, -1.3652, 
		-.815, -.56899, {0}, 3.6289e-7, 1.9563e-7, 1.3246e-7, 
		4.5698e-7, -.44836, -.37141, -.31034, -.25609, {0}, -.055819, 
		-.71593, -.99407, -1.2361, .008276, -.69554, -1.0382, -1.0606,
		 {0}, -1.0303e-6, 5.0551e-8, -3.5826e-7, -1.5676e-7, .19407, 
		.21456, .22304, -.016164, {0}, -.11119, -.10967, -.11572, 
		-.12804, .028119, .091424, -.13799, -.19427, {0}, -1.7286e-7, 
		1.4302e-7, -3.8968e-7, -6.0241e-7, -.026308, .040012, .062362,
		 .10428, {0}, .029466, .23166, .18954, .27591, -.015432, 
		.093601, .26902, .19448, {0}, .69927, .70241, .26643, .040136,
		 .48983, .48116, .26612, .11527, {0}, -1.0867e-7, 6.7276e-8, 
		-1.2399e-8, -1.157e-7, .086385, .032264, -.047466, .016518, {
		0}, -.038446, -.0039113, .022029, .021493, -.0752, .068285, 
		.019184, .036148, {0}, -3.1427e-8, -2.3431e-8, 3.5262e-8, 
		-4.5863e-8, .018661, .0098315, -.070576, -.0070688, {0}, 
		.014009, -.029279, -.025895, .0026574, .004978, -.003408, 
		-.017642, .010841, {0}, 4.5348e-8, -2.168e-8, 2.5542e-8, 
		1.7588e-8, -.016762, -.0011225, .014685, .0036512, {0}, 
		.26142, .30214, .17279, .15964, .18896, .1262, .077755, 
		.10339, {0}, 9.8583e-8, 8.5569e-8, -1.0393e-8, 1.247e-7, 
		-.086811, .033225, -.031315, -.0021704, {0}, -.01537, 
		-.059577, -.030719, .018918, 5.1824e-4, -.04842, .019684, 
		-.0070271, {0}, -8.8257e-8, -7.4572e-8, -6.3703e-9, 9.3632e-8,
		 -.0064436, -.028323, -.013324, .019422, {0}, .011618, 
		.013847, .0075848, -.0024488, .0035544, -.0022914, .0034012, 
		.0041677, {0}, 9.8907e-8, 1.9007e-8, -1.4497e-8, 2.0725e-8, 
		.0094714, .007972, .037043, -.0066189, {0}, -.054724, .091829,
		 .09787, .066975, .020099, .12455, -.018646, .043364, {0}, 
		2.2519e-7, -8.0079e-8, -1.3003e-7, 1.1782e-8, .019941, 
		-.042949, .026457, -.025002, {0}, .015621, .026453, -.0020224,
		 .019413, .025581, -.0053643, .0098637, .014219, {0}, 
		-1.0045e-8, 2.1214e-8, -3.9366e-8, 6.2877e-9, -.0052659, 
		.0067441, .0026819, -.0022654, {0}, .0036467, -.0032018, 
		-.0032416, .0053689, -.0034378, .014582, .0017598, .005644, {
		0}, -.12359, -.21978, .015904, -.015363, -.12902, -.040379, 
		-.021755, -.037866, {0}, 4.9284e-8, 1.733e-9, -1.5451e-8, 
		-2.0022e-9, .014578, .038848, .0042552, 1.0338e-4, {0}, 
		-.011143, -.0011862, -.0035652, -.021002, -.0025016, 
		-.0032937, -.016633, -.0039639, {0}, 2.3898e-9, 2.2427e-8, 
		-1.3658e-9, -6.7078e-9, -.02076, .0091013, -.0067044, 
		-.0033311, {0}, -.0058604, .0013491, -.0077126, -.0029894, 
		.0034195, -.0075494, .0034964, -3.3289e-4, {0}, -.001002, 
		.028588, -.015924, .0061202, -.082338, -.06258, -.0048719, 
		-.052423, {0}, -1.1869e-7, -5.3489e-8, 1.6773e-8, 1.2119e-8, 
		.0050698, .011877, .005979, .002543, {0}, -8.7861e-4, .011135,
		 -.0037276, -.0022888, -3.4081e-4, -.00489, 2.3021e-5, 
		-.0071279, {0}, -1.0543e-8, -1.3678e-9, 1.7795e-8, 4.3298e-9, 
		-.0027512, -.005377, .0054778, .0032787, {0}, .098818, 
		.079619, .0074727, -.046405, -.040443, .015066, -.012598, 
		.0059375, {0}, 7.4183e-8, 1.5714e-8, 3.0856e-8, -5.8474e-8, 
		.0022658, -9.2034e-4, .0099962, .0072932, {0}, .013692, 
		.007193, 7.4715e-4, -.0036078, -.0080779, -.007237, -.0010507,
		 -.0019167, {0}, -1.6456e-8, 2.9905e-9, 7.3372e-9, -1.6963e-8,
		 -.003129, -3.5355e-4, .0057994, -.0018983, {0}, -.038041, 
		-.038042, .013716, -.018254, -.001535, .0086705, .020765, 
		.0045326, {0}, 3.5978e-8, 1.1725e-8, 4.6691e-8, -1.0377e-9, 
		.0025313, .010198, .011593, .0068099, {0}, -.0039582, 
		.0034274, .0040197, -.0013715, -.003474, .0020618, -3.2365e-4,
		 -7.4999e-5, {0}, .028077, -.0049647, -.011936, -.0022111, 
		.0082225, .05721, -.0015353, -.0078634, {0}, -2.2537e-8, 
		2.1675e-9, 5.822e-9, 3.4185e-9, -.0026921, .0068151, .0014942,
		 -.0055813, {0}, .0015597, .0079079, .0038995, 9.5343e-4, 
		.0013247, -.0018874, .0019642, -5.3892e-4, {0}, -.003761, 
		-.0079338, .0072715, -.0022094, .0057483, .017634, .0088836, 
		8.528e-4, {0}, -2.4712e-8, 3.6623e-8, -2.0243e-8, 2.7066e-9, 
		.0040066, .0098946, .0042172, .0014028, {0}, .004046, 
		8.5068e-4, .0041793, -.0024215, .013048, .018101, -1.8502e-4, 
		.0035032, {0}, 7.7021e-9, 1.7537e-9, -3.2785e-9, -3.1546e-9, 
		1.6612e-4, .0053287, .0023092, -3.7237e-4, {0}, -.0014101, 
		.023308, .013978, -.0010581, .0065345, .030321, .001837, 
		-2.5767e-5, {0}, .016789, -.021869, -.0061225, -.0010098, 
		.0061813, .0068488, -3.7978e-4, -8.071e-4 };

#define dhh ((doublereal *)&equiv_391)

    static struct {
	doublereal e_1[8];
	doublereal fill_2[4];
	doublereal e_3[8];
	doublereal fill_4[4];
	doublereal e_5[8];
	doublereal fill_6[4];
	doublereal e_7[8];
	doublereal fill_8[4];
	doublereal e_9[8];
	doublereal fill_10[4];
	doublereal e_11[8];
	doublereal fill_12[4];
	doublereal e_13[8];
	doublereal fill_14[4];
	doublereal e_15[8];
	doublereal fill_16[4];
	doublereal e_17[8];
	doublereal fill_18[4];
	doublereal e_19[8];
	doublereal fill_20[4];
	doublereal e_21[8];
	doublereal fill_22[4];
	doublereal e_23[8];
	doublereal fill_24[4];
	doublereal e_25[8];
	doublereal fill_26[4];
	doublereal e_27[8];
	doublereal fill_28[4];
	doublereal e_29[8];
	doublereal fill_30[4];
	doublereal e_31[8];
	doublereal fill_32[4];
	doublereal e_33[8];
	doublereal fill_34[4];
	doublereal e_35[8];
	doublereal fill_36[4];
	doublereal e_37[8];
	doublereal fill_38[4];
	doublereal e_39[8];
	doublereal fill_40[4];
	doublereal e_41[8];
	doublereal fill_42[4];
	doublereal e_43[8];
	doublereal fill_44[4];
	doublereal e_45[8];
	doublereal fill_46[4];
	doublereal e_47[8];
	doublereal fill_48[4];
	doublereal e_49[8];
	doublereal fill_50[4];
	doublereal e_51[8];
	doublereal fill_52[4];
	doublereal e_53[8];
	doublereal fill_54[4];
	doublereal e_55[8];
	doublereal fill_56[4];
	doublereal e_57[8];
	doublereal fill_58[4];
	doublereal e_59[8];
	doublereal fill_60[4];
	doublereal e_61[8];
	doublereal fill_62[4];
	doublereal e_63[8];
	doublereal fill_64[4];
	doublereal e_65[8];
	doublereal fill_66[4];
	doublereal e_67[8];
	doublereal fill_68[4];
	doublereal e_69[8];
	doublereal fill_70[4];
	doublereal e_71[8];
	doublereal fill_72[4];
	doublereal e_73[8];
	doublereal fill_74[4];
	doublereal e_75[8];
	doublereal fill_76[4];
	doublereal e_77[8];
	doublereal fill_78[4];
	doublereal e_79[8];
	doublereal fill_80[4];
	doublereal e_81[8];
	doublereal fill_82[4];
	doublereal e_83[8];
	doublereal fill_84[4];
	doublereal e_85[8];
	doublereal fill_86[4];
	doublereal e_87[8];
	doublereal fill_88[4];
	doublereal e_89[8];
	doublereal fill_90[4];
	doublereal e_91[8];
	doublereal fill_92[4];
	doublereal e_93[8];
	doublereal fill_94[4];
	doublereal e_95[8];
	doublereal fill_96[4];
	doublereal e_97[8];
	doublereal fill_98[4];
	} equiv_392 = { -3.0827, -1.71, -1.2078, -1.123, -2.976, -2.0393, 
		-1.5728, -1.3029, {0}, 4.4643e-7, 5.254e-7, -8.3889e-8, 
		-2.9419e-7, -.86799, -.81007, -.68726, -.43965, {0}, -.34361, 
		-.8228, -.86323, -.95822, .048259, -.43286, -.46811, -.4354, {
		0}, -4.7996e-7, -8.2344e-7, -1.5199e-7, -3.4817e-7, .48124, 
		.30351, .024677, -.12774, {0}, -.29473, -.40545, -.44768, 
		-.35165, -.0092323, -.17024, -.45196, -.54683, {0}, 1.5576e-7,
		 -5.5031e-7, 2.509e-7, 2.2927e-7, -.17802, .046307, .15523, 
		.089815, {0}, .20815, .33911, .35311, .33646, .12279, 
		-.002422, .30631, .24691, {0}, .40991, .25554, .1321, .089248,
		 .16776, -.063442, .14197, .15207, {0}, -2.9466e-8, 8.4842e-8,
		 -4.213e-9, -1.1195e-7, .21054, -.001637, -.078123, .045816, {
		0}, -.059793, .083244, -.002548, .038351, -.051912, .06746, 
		-.017428, .042447, {0}, 3.8185e-8, 9.6193e-8, 3.0688e-8, 
		-7.4946e-8, -.010298, -.010338, -.017897, -.027108, {0}, 
		.025958, -.060073, -.043178, 2.5411e-5, .015834, -.044583, 
		-.018015, .0027242, {0}, -5.2957e-8, -2.0823e-7, 1.8903e-9, 
		2.165e-8, -.0083905, .0096863, .02721, -.0073419, {0}, .66694,
		 .3006, .089046, -.0088392, .15721, .0053744, .060701, 
		-.047334, {0}, 1.1803e-7, 7.9876e-8, -1.0776e-8, -1.7418e-8, 
		-.02726, .0026359, -.13212, .050151, {0}, -.029476, -.1175, 
		.029388, .012222, -.067125, -.058995, -.022745, -.021149, {0},
		 1.4225e-8, -2.9524e-8, 2.2664e-8, 4.5854e-9, -.039449, 
		-.01631, -.017608, -.023378, {0}, -.013761, -.035514, 
		-.011335, -.021108, .0047324, .0073342, -.012909, .0043055, {
		0}, -7.2518e-8, -2.9102e-8, -1.4036e-8, 3.078e-8, .010327, 
		9.4701e-4, .020402, -.016985, {0}, -.28967, -.045851, -.04987,
		 .031391, -.18399, .069508, -.0040894, .015813, {0}, 
		-2.0293e-8, -4.7236e-9, -2.0597e-8, -9.2939e-9, .02086, 
		-.043418, .0039555, -.016609, {0}, .018383, .024348, .0051163,
		 .011868, .043145, -.0051968, -.0036464, .011566, {0}, 
		1.0666e-8, 4.2832e-9, 1.5444e-8, -2.3493e-9, -.0049043, 
		-.003068, .014643, .0062104, {0}, -.0098637, -.0074072, 
		.0070597, .0040791, -.0056411, .011837, -.0055944, .0050605, {
		0}, -.21268, -.11252, -.11044, -.0092411, -.24448, -.12321, 
		-.08809, -.035118, {0}, 4.3123e-8, 9.5787e-8, 3.2974e-8, 
		-3.1598e-9, .071468, .042603, -.01093, -.020272, {0}, 
		-.013389, .026864, .033729, -.0025908, -.012413, -.035437, 
		-.0073501, -.0085016, {0}, 2.678e-9, 1.7685e-8, 9.666e-9, 
		-9.0595e-9, -.013358, .016518, -.0056046, -.009016, {0}, 
		9.9442e-4, -.0059893, -.020066, -.0010797, -.0022098, 
		-.012969, .0026169, -.0068417, {0}, -.0078858, -.16605, 
		-.047281, .0402, -.03976, .032534, -.016782, -.025045, {0}, 
		5.6098e-9, -1.3665e-7, 1.0175e-8, -2.938e-9, -.0079188, 
		.002845, .014274, -.010184, {0}, -.0049395, .012534, .0045853,
		 -.0015619, 6.9939e-4, .0035741, -2.7868e-4, -.0063754, {0}, 
		-4.389e-10, 1.1691e-8, 3.9224e-9, -2.7627e-10, -.0053921, 
		-.0020381, .0021147, .0060554, {0}, -.083089, .047303, 
		-.05684, .022044, -.055414, -.050507, -.018199, -.020355, {0},
		 5.472e-8, 6.8012e-10, 3.2182e-8, -1.6962e-8, .0085107, 
		.0082961, .0088925, -.0028685, {0}, .014305, .010472, .012884,
		 -.0085223, -.009889, 3.8507e-4, -.0015835, -.0026734, {0}, 
		-9.3089e-9, 1.9695e-9, 6.6859e-9, -3.6076e-9, 5.1361e-4, 
		.0010441, .0018784, -.0015766, {0}, -.0068383, -.0082855, 
		.042958, .023448, .066272, .041571, .011248, .0064888, {0}, 
		-7.1157e-9, -8.1465e-9, 7.5059e-9, -4.9645e-9, -.002551, 
		-.0029669, .0072779, -.0016234, {0}, -.0039638, .0057602, 
		.0050972, -5.8718e-4, -.0073423, -7.791e-4, 4.4115e-4, 
		-.0025859, {0}, .0099653, .0078478, -.03422, -.015134, 
		.0020118, .022211, .0018361, .0066457, {0}, 1.0788e-8, 
		-2.5233e-8, 4.4177e-9, -8.6918e-9, -.0064885, -.003513, 
		-.0011211, -.0014526, {0}, -.0011729, .0030308, .0066776, 
		-.0023766, .0027256, .0023044, .001106, -.0011457, {0}, 
		-.0029558, -.0085876, -.0047692, 7.2023e-4, .0086778, .029926,
		 .011001, .0022648, {0}, 1.6849e-8, 2.5667e-9, 1.1823e-8, 
		9.0865e-10, -8.981e-4, .0026085, .0012477, -8.7925e-4, {0}, 
		.0012213, .0065844, -.0088228, .0030388, .01035, .025759, 
		.0090196, .0041493, {0}, -8.7021e-9, -1.7771e-8, -2.5359e-9, 
		-2.6828e-9, -.0031749, 3.9804e-4, -5.8886e-4, -2.3712e-4, {0},
		 -.014505, -.0061409, -.011986, 4.6501e-4, .016338, .031126, 
		.00973, 7.9344e-4, {0}, -5.6113e-4, -.010949, -.0051509, 
		-7.739e-4, -.0021051, .01086, .0049376, .001845 };

#define dheh ((doublereal *)&equiv_392)

    static struct {
	doublereal e_1[8];
	doublereal fill_2[4];
	doublereal e_3[8];
	doublereal fill_4[4];
	doublereal e_5[8];
	doublereal fill_6[4];
	doublereal e_7[8];
	doublereal fill_8[4];
	doublereal e_9[8];
	doublereal fill_10[4];
	doublereal e_11[8];
	doublereal fill_12[4];
	doublereal e_13[8];
	doublereal fill_14[4];
	doublereal e_15[8];
	doublereal fill_16[4];
	doublereal e_17[8];
	doublereal fill_18[4];
	doublereal e_19[8];
	doublereal fill_20[4];
	doublereal e_21[8];
	doublereal fill_22[4];
	doublereal e_23[8];
	doublereal fill_24[4];
	doublereal e_25[8];
	doublereal fill_26[4];
	doublereal e_27[8];
	doublereal fill_28[4];
	doublereal e_29[8];
	doublereal fill_30[4];
	doublereal e_31[8];
	doublereal fill_32[4];
	doublereal e_33[8];
	doublereal fill_34[4];
	doublereal e_35[8];
	doublereal fill_36[4];
	doublereal e_37[8];
	doublereal fill_38[4];
	doublereal e_39[8];
	doublereal fill_40[4];
	doublereal e_41[8];
	doublereal fill_42[4];
	doublereal e_43[8];
	doublereal fill_44[4];
	doublereal e_45[8];
	doublereal fill_46[4];
	doublereal e_47[8];
	doublereal fill_48[4];
	doublereal e_49[8];
	doublereal fill_50[4];
	doublereal e_51[8];
	doublereal fill_52[4];
	doublereal e_53[8];
	doublereal fill_54[4];
	doublereal e_55[8];
	doublereal fill_56[4];
	doublereal e_57[8];
	doublereal fill_58[4];
	doublereal e_59[8];
	doublereal fill_60[4];
	doublereal e_61[8];
	doublereal fill_62[4];
	doublereal e_63[8];
	doublereal fill_64[4];
	doublereal e_65[8];
	doublereal fill_66[4];
	doublereal e_67[8];
	doublereal fill_68[4];
	doublereal e_69[8];
	doublereal fill_70[4];
	doublereal e_71[8];
	doublereal fill_72[4];
	doublereal e_73[8];
	doublereal fill_74[4];
	doublereal e_75[8];
	doublereal fill_76[4];
	doublereal e_77[8];
	doublereal fill_78[4];
	doublereal e_79[8];
	doublereal fill_80[4];
	doublereal e_81[8];
	doublereal fill_82[4];
	doublereal e_83[8];
	doublereal fill_84[4];
	doublereal e_85[8];
	doublereal fill_86[4];
	doublereal e_87[8];
	doublereal fill_88[4];
	doublereal e_89[8];
	doublereal fill_90[4];
	doublereal e_91[8];
	doublereal fill_92[4];
	doublereal e_93[8];
	doublereal fill_94[4];
	doublereal e_95[8];
	doublereal fill_96[4];
	doublereal e_97[8];
	doublereal fill_98[4];
	} equiv_393 = { -1.6313, -1.4724, -1.6315, -1.7525, -1.595, -1.4816, 
		-1.5647, -1.752, {0}, 3.3826e-9, 6.2234e-7, 1.1175e-7, 
		-1.0714e-6, .12602, .25836, .42744, .38232, {0}, .23816, 
		.19984, .47753, .86183, .24136, .25713, .47853, .81527, {0}, 
		2.8373e-7, -6.2436e-7, -1.0014e-7, 1.1184e-6, .16546, 
		-.011671, -.2716, -.2887, {0}, -.020961, -.059609, -.10097, 
		-.27829, .017991, -.11685, -.037019, -.1073, {0}, -5.3533e-7, 
		5.3063e-8, -1.0216e-7, 2.7162e-7, -.013398, -.080473, .021446,
		 .07022, {0}, .08716, .040544, -.053935, -.10538, .093804, 
		-.025842, -.13457, -.16764, {0}, .098248, -.029918, -.3357, 
		-.13943, -.0077106, .017538, -.11104, -.21758, {0}, 4.4888e-8,
		 4.1071e-7, 2.0709e-7, -1.1095e-7, .014206, .03148, .087769, 
		-.020171, {0}, -.032244, 5.6303e-4, .044824, .045835, 
		-.0023237, -.0052361, .0040593, .034368, {0}, -2.0063e-8, 
		-4.7255e-8, 1.8159e-8, -1.8177e-7, -.0012863, -.020114, 
		-.027075, -.0022874, {0}, -.020732, .0080654, .022117, 
		.0083712, 2.3217e-4, .010788, .0084188, .027205, {0}, 
		1.4134e-9, -3.4962e-8, -8.4695e-8, 1.0937e-7, -.0022888, 
		.0060475, -.012262, -.0064735, {0}, .06867, .016174, -.16189, 
		-.42987, -.033507, -.082585, -.064727, -.33147, {0}, 
		3.8855e-8, 1.0136e-7, 9.9261e-8, -3.9255e-7, .021777, .015506,
		 .071687, .092558, {0}, -.079258, .011632, .057796, .066012, 
		-.02319, -.0093973, -.038468, .049336, {0}, 3.6878e-8, 
		-2.4108e-8, 4.8814e-8, 5.4483e-8, -.02655, .0069887, 
		-.0079663, -.041876, {0}, .030244, .010895, -.0075845, 
		.0090376, .0054864, .0016035, .012872, .0050738, {0}, 
		-3.3364e-8, -1.4658e-8, -5.1309e-8, 7.3468e-8, .0063951, 
		-.0046125, .0028088, .012235, {0}, -.066861, -.043236, 
		-.12423, .0050653, -.048363, .0012645, -.012956, -.012631, {0}
		, 3.2622e-8, 1.5584e-7, 1.3321e-7, -6.8615e-9, .021732, 
		.028444, -.039502, -.026016, {0}, .020265, -.0076984, 
		-.016181, -.013051, -.002925, .0082369, -7.9875e-5, .010295, {
		0}, -1.4791e-8, 1.8395e-8, -7.7736e-9, -4.6976e-9, -.0079064, 
		-.0026763, .0061428, -.0060847, {0}, .0066954, 6.3333e-4, 
		.0046002, .0039132, -.005498, -7.5445e-4, -.0012074, .0022948,
		 {0}, .02134, -.0052038, -.12281, -.038456, .040796, .026349, 
		.0038344, -.1806, {0}, -3.2037e-8, 1.5845e-7, 2.4201e-7, 
		1.6913e-8, .013459, -.016736, .0033477, -.017793, {0}, 
		.0090073, -.0068821, .014288, -8.327e-4, .0074514, .0013463, 
		-.0033677, .0054176, {0}, 2.0858e-8, -1.8127e-8, 1.1896e-8, 
		-3.9315e-8, -.0057685, 1.7333e-5, -.0030964, 2.2462e-4, {0}, 
		-.0052152, .0012382, -.0053069, .002999, 2.1205e-4, 
		-9.0561e-4, 9.6501e-4, .0018786, {0}, .039714, -.066883, 
		-.018104, -.0059986, -.019001, -.008105, .0082409, .11605, {0}
		, -1.9344e-9, 6.051e-8, -1.9814e-8, 6.4241e-9, -.0014431, 
		-.0056762, -.028989, .0017233, {0}, -8.96e-5, -.0073364, 
		-.0084131, -3.6095e-4, 6.2449e-4, .0031943, .0043657, 
		-.0015451, {0}, -3.7487e-9, 1.1055e-8, 2.2753e-9, -4.3472e-9, 
		-.0012225, -3.0766e-4, 9.4355e-5, .0013382, {0}, -.040648, 
		-.02013, .0051336, .093971, .0049048, -.026193, .01313, 
		-.073353, {0}, 1.722e-8, 1.0636e-7, 1.4694e-7, 6.1373e-8, 
		-.014864, -.012177, -.018814, -3.7852e-4, {0}, .005633, 
		-.0043419, .0049619, -.007076, -.0016067, -.0012289, .0027093,
		 .0013236, {0}, 4.4101e-9, -5.693e-9, 4.1959e-9, -2.7203e-9, 
		-.001502, 4.1217e-4, -.0012167, -9.6993e-4, {0}, .0041397, 
		-.019632, -.022226, .045148, -.0037769, -.024327, -.0057969, 
		.018479, {0}, -4.3699e-10, 2.3733e-8, -5.4731e-8, -1.1452e-8, 
		-.0013646, -.0061348, -.0064927, -.0056199, {0}, -.0035601, 
		-.0017396, -.0052711, -1.6323e-4, -.0014496, -.0012113, 
		4.195e-4, 8.0329e-4, {0}, -.016551, .0047721, .01304, .022101,
		 -.012677, -.017103, -.0091788, -.017815, {0}, -2.6274e-9, 
		5.6015e-8, 4.8906e-8, 5.663e-9, -.0028348, -.0022901, 
		-.0072444, .0035429, {0}, 8.3802e-4, -.0016795, .0022301, 
		-9.0528e-4, -3.0407e-5, 6.3735e-4, -.001473, -.0015325, {0}, 
		.0012105, -4.7359e-4, -2.7938e-4, .006739, -.0030275, 
		-.012284, -.010845, -.0046303, {0}, -1.0517e-8, -1.4109e-8, 
		-2.2648e-8, 1.1191e-9, -.0014841, -.0038308, -.0025005, 
		-.0039437, {0}, -.0085131, 1.4272e-4, -.015969, .0057927, 
		-.0067625, -.010159, -.0082969, -.017196, {0}, 4.5467e-9, 
		2.0978e-8, -6.5911e-9, 2.2189e-9, -.0022857, -.0017879, 
		-.001966, -.0020703, {0}, -.0022753, -.0029585, .0036104, 
		.0089446, -.001918, -.01251, -.0063399, -3.6631e-4, {0}, 
		-.0033013, .010551, .0029534, -6.3752e-4, -.0051806, -.010009,
		 -.0058925, -.016702 };

#define dnh ((doublereal *)&equiv_393)

    static doublereal dol[441]	/* was [3][3][49] */ = { -.0034295,-.26245,
	    -.89352,-.0075061,-.31262,-.69317,0.0,0.0,0.0,4.8322e-10,
	    8.4041e-7,2.4097e-5,.0042214,.2164,.33146,0.0,0.0,0.0,7.9335e-4,
	    .22991,.37286,.0032811,.29808,.59247,0.0,0.0,0.0,1.8237e-9,
	    -2.106e-6,-1.0359e-5,-.0043773,-.29615,-.38841,0.0,0.0,0.0,
	    .001032,-.0597,.010068,4.1127e-5,.064926,.15031,0.0,0.0,0.0,
	    -7.3733e-10,5.5301e-6,-1.7035e-5,.0027276,.0038438,.034648,0.0,
	    0.0,0.0,-5.8045e-4,.026165,-.020139,-4.5069e-4,-.090777,-.20436,
	    0.0,0.0,0.0,-.0021541,-.34817,-1.0039,-.0069573,-.38422,-.76788,
	    0.0,0.0,0.0,-6.5013e-10,2.5875e-7,8.8331e-6,.0032289,.13193,
	    .11303,0.0,0.0,0.0,-3.1081e-4,.017171,-.13731,4.5324e-4,.031168,
	    -.030861,0.0,0.0,0.0,-9.8478e-12,-7.7857e-7,4.7035e-6,-5.4022e-4,
	    -.036264,.03173,0.0,0.0,0.0,8.0628e-5,-.0064432,-.036637,
	    -2.8733e-4,.023774,.058057,0.0,0.0,0.0,2.1821e-10,6.9845e-7,
	    -2.6654e-6,1.7425e-4,-.0093167,-.032321,0.0,0.0,0.0,-.0019044,
	    -.13705,-.20386,-.0044235,-.15581,-.23509,0.0,0.0,0.0,-8.3791e-10,
	    1.07e-6,1.5439e-5,-1.1619e-5,.015604,.12907,0.0,0.0,0.0,
	    -1.5618e-4,.0075614,-.036661,.0013238,.023125,-.025901,0.0,0.0,
	    0.0,-4.6595e-11,-5.6468e-7,1.026e-5,-5.1465e-4,.01324,.0097355,
	    0.0,0.0,0.0,1.5868e-4,8.2754e-4,-.045066,-3.3052e-4,-.0012961,
	    .030717,0.0,0.0,0.0,-1.6618e-10,1.9031e-7,-2.8682e-6,3.8804e-4,
	    -.011848,-.02717,0.0,0.0,0.0,7.2724e-5,-.025396,-.17254,6.8531e-4,
	    -.032185,-.10447,0.0,0.0,0.0,-3.1159e-10,-7.2603e-7,-4.9526e-6,
	    -1.9665e-4,-.0051446,-.070094,0.0,0.0,0.0,1.5783e-4,-.017557,
	    -.067622,1.9622e-4,.010193,-.026774,0.0,0.0,0.0,-6.1281e-10,
	    2.1324e-7,-1.0877e-6,2.8863e-4,-.0079351,.020725,0.0,0.0,0.0,
	    -3.2544e-5,-.0010498,-.012351,-6.5642e-5,.0032452,2.486e-4,0.0,
	    0.0,0.0,-5.8917e-4,-.064057,-.10953,-.0028855,-.13403,-.29119,0.0,
	    0.0,0.0,-6.1467e-10,4.6894e-7,7.0854e-6,5.0512e-4,-.0010768,
	    .09344,0.0,0.0,0.0,-1.0295e-4,-.009139,-.014296,7.0149e-4,.012773,
	    -.0080132,0.0,0.0,0.0,5.7992e-11,9.6493e-9,6.7187e-6,-1.5869e-4,
	    .0029588,-.0019018,0.0,0.0,0.0,5.7641e-5,1.7969e-4,-.020577,
	    -1.5202e-4,-9.6663e-4,.0044841,0.0,0.0,0.0,6.7711e-5,.070926,
	    .064692,.0015939,.056863,.059359,0.0,0.0,0.0,6.1432e-10,
	    -3.6416e-7,-3.0932e-6,-5.6796e-4,-.021862,-.019317,0.0,0.0,0.0,
	    8.637e-5,-.0069695,-.011908,-1.067e-4,.010585,-.018184,0.0,0.0,
	    0.0,-2.367e-10,8.9469e-8,-1.666e-6,1.2569e-7,-.0031121,.0050489,
	    0.0,0.0,0.0,2.2941e-5,.02431,.066329,-8.3699e-4,-.033781,-.10292,
	    0.0,0.0,0.0,-4.7808e-11,-1.7204e-7,-7.0914e-7,-8.4185e-5,-.012186,
	    .012137,0.0,0.0,0.0,4.7716e-5,-.00545,-.015392,2.4768e-5,.0047556,
	    8.1073e-4,0.0,0.0,0.0,2.1198e-11,9.1857e-8,2.1883e-6,4.6445e-5,
	    -5.703e-4,7.1284e-4,0.0,0.0,0.0,2.8298e-6,.021846,.0045838,
	    1.9761e-4,.012328,.0083372,0.0,0.0,0.0,3.6265e-10,8.1249e-8,
	    -8.4412e-7,6.0184e-5,-.0064108,.01334,0.0,0.0,0.0,-4.4578e-6,
	    -7.2438e-4,5.4739e-4,-1.0454e-5,.0017929,-.0067512,0.0,0.0,0.0,
	    1.7541e-4,.021225,.028565,3.2389e-4,-.0021691,.017102,0.0,0.0,0.0,
	    2.1511e-10,-1.1084e-8,-9.7635e-7,-3.7438e-5,-.0082313,-.0024549,
	    0.0,0.0,0.0,2.5195e-5,-4.9135e-4,.0050974,-3.4186e-5,.0019333,
	    -.0017239,0.0,0.0,0.0,-2.7325e-5,-.0015282,-5.1648e-4,-3.5859e-4,
	    -.011646,.019465,0.0,0.0,0.0,-2.3875e-11,5.4962e-8,-2.9444e-8,
	    -6.1472e-5,-.0016945,-.0054019,0.0,0.0,0.0,-3.1418e-6,-.0020812,
	    -.0010738,-4.7218e-4,-.027066,.048407,0.0,0.0,0.0,4.6152e-11,
	    3.7817e-8,-2.7121e-7,7.6277e-6,1.357e-4,-.0044151,0.0,0.0,0.0,
	    -2.9151e-5,-4.2919e-4,.0034379,1.4752e-4,-.0085273,-.019067,0.0,
	    0.0,0.0,3.7913e-5,1.7766e-4,-.0021828,-4.509e-4,-.015711,.015001 }
	    ;
    static doublereal dhl[441]	/* was [3][3][49] */ = { -2.3735,-.75599,
	    -.31869,-2.2303,-.76906,-.46737,0.0,0.0,0.0,-4.1106e-7,-2.3535e-7,
	    1.509e-7,-.2793,-.42549,-.12403,0.0,0.0,0.0,-.15043,-.41761,
	    -.4056,-.16289,-.62598,-.64613,0.0,0.0,0.0,7.105e-8,-2.8901e-8,
	    2.8552e-7,.084439,.22279,.18831,0.0,0.0,0.0,-.044023,.048799,
	    -.0042289,.043059,.14493,.12419,0.0,0.0,0.0,5.19e-8,-1.4005e-7,
	    3.6878e-8,-.0109,.10653,-.059911,0.0,0.0,0.0,.075167,-.075257,
	    .19957,.005906,.27012,.19218,0.0,0.0,0.0,.26079,.5085,.27526,
	    .38539,.3871,.29484,0.0,0.0,0.0,-5.4677e-8,-5.5769e-8,4.0798e-7,
	    -.097745,-.06164,.040311,0.0,0.0,0.0,.040421,.074268,.11343,
	    .018579,.046697,.098207,0.0,0.0,0.0,8.4393e-9,-4.0953e-8,
	    -1.0028e-7,.014256,-.057444,-.029219,0.0,0.0,0.0,.0042554,.02088,
	    .051526,6.8489e-4,.020933,-.011908,0.0,0.0,0.0,1.7166e-8,
	    -3.9792e-8,-6.0643e-8,-.0011027,.0088119,.038705,0.0,0.0,0.0,
	    .19018,.19637,.092397,.23516,.14986,-.0018943,0.0,0.0,0.0,
	    -6.0764e-8,3.5212e-8,-2.1866e-7,.038591,.021907,-.042874,0.0,0.0,
	    0.0,.038687,.035924,.086528,-.029264,-.018032,-.04606,0.0,0.0,0.0,
	    6.3717e-8,-3.2961e-8,2.346e-8,-.0019275,-.046878,-.034199,0.0,0.0,
	    0.0,.0064895,-.011911,.036848,.024632,-.016714,-.022322,0.0,0.0,
	    0.0,-4.0891e-8,5.4324e-9,6.2456e-8,-3.0091e-4,.042935,.025785,0.0,
	    0.0,0.0,.038167,.029918,.015483,-.024136,-.024183,.025357,0.0,0.0,
	    0.0,1.8652e-8,1.083e-8,-1.7108e-7,.021471,.02029,.027261,0.0,0.0,
	    0.0,-.010038,.034518,.036333,-.014274,-.010109,.0098865,0.0,0.0,
	    0.0,1.9645e-8,-5.4744e-9,-1.0845e-8,-.0029073,.0052285,.0016691,
	    0.0,0.0,0.0,.0021804,.010144,.010259,.004065,-.0069878,.0062808,
	    0.0,0.0,0.0,-.014444,-.015615,.004332,.026483,.042781,-.0091296,
	    0.0,0.0,0.0,6.5822e-9,9.3932e-9,-2.6987e-7,.0039806,.005669,
	    -.013707,0.0,0.0,0.0,.0070666,.0079662,-.010254,-.01356,-.011873,
	    -.0087014,0.0,0.0,0.0,-8.4659e-9,-4.4936e-9,-8.8644e-8,3.6952e-4,
	    -.0045405,-.0034345,0.0,0.0,0.0,-.0055334,-.0014126,-.002117,
	    5.3108e-4,-.0036632,-.0046994,0.0,0.0,0.0,.015556,-.031648,
	    -.021956,-.039132,-.022072,-.025409,0.0,0.0,0.0,1.2414e-8,
	    2.2804e-8,-1.3044e-7,.023689,.0012209,-.0067929,0.0,0.0,0.0,
	    -.0043661,.0062742,-.0068424,-6.6253e-4,-.0058301,.0012701,0.0,
	    0.0,0.0,4.4984e-9,-9.5574e-9,-3.8852e-8,.0013556,3.1915e-6,
	    .0036829,0.0,0.0,0.0,.0093627,-.011306,-.016083,.023462,.010209,
	    -.0029346,0.0,0.0,0.0,-2.4554e-9,1.6269e-9,-2.8545e-8,-.0032744,
	    .0019771,-.0021371,0.0,0.0,0.0,-.0036096,2.2078e-4,.00478,
	    .0014565,.0013042,-.0074109,0.0,0.0,0.0,7.8989e-9,2.8647e-9,
	    4.3092e-8,2.4812e-4,.0014817,.0014351,0.0,0.0,0.0,-.012352,
	    -.017932,-9.4451e-4,-3.2051e-4,.0020904,-.0074944,0.0,0.0,0.0,
	    1.0504e-8,-5.0077e-9,-4.6383e-8,.0026108,-7.5031e-4,-.002353,0.0,
	    0.0,0.0,-4.5357e-6,-.0023559,.0017086,7.5391e-4,.0022646,-.002396,
	    0.0,0.0,0.0,7.8762e-4,-.0092953,.0079651,-.019602,.011547,
	    -.0082307,0.0,0.0,0.0,-5.2915e-9,-5.1441e-9,2.1903e-7,.0050088,
	    .0067321,-4.0801e-4,0.0,0.0,0.0,-.0019697,-.0022185,3.388e-4,
	    8.0312e-4,9.517e-4,.001943,0.0,0.0,0.0,4.2966e-4,2.9117e-5,
	    4.5247e-4,.013604,.017845,.001899,0.0,0.0,0.0,5.977e-9,-4.8547e-9,
	    1.0538e-7,.0032853,.0061338,6.7012e-4,0.0,0.0,0.0,.0037248,
	    .0044236,.0037229,.0081745,.012967,-.0022565,0.0,0.0,0.0,
	    6.9259e-9,-2.8102e-9,-8.6806e-8,.0019033,.0023311,-4.5399e-4,0.0,
	    0.0,0.0,.0030955,9.3261e-4,-5.2132e-4,.016966,.029597,-.0017694,
	    0.0,0.0,0.0,.0027742,.0019538,-5.7966e-4,.012348,-.0022654,
	    -6.3397e-4 };
    static doublereal dhel[441]	/* was [3][3][49] */ = { -2.8533,-1.6103,
	    -1.3192,-3.0612,-2.2374,-1.9424,0.0,0.0,0.0,-2.1986e-7,-1.3811e-7,
	    1.8143e-6,-1.0562,-.74507,-.58403,0.0,0.0,0.0,.072644,.11838,
	    -.021284,.088532,-.14689,.34084,0.0,0.0,0.0,2.2489e-7,2.4209e-7,
	    -5.786e-6,.085373,-.025946,-.19084,0.0,0.0,0.0,-.18677,-.12965,
	    -.13203,.081474,.047283,-.054692,0.0,0.0,0.0,-3.9095e-7,
	    -6.5882e-8,1.0367e-6,.028747,.14143,.20943,0.0,0.0,0.0,.01085,
	    .13191,.087882,.13534,.32299,.0067653,0.0,0.0,0.0,.22428,.46161,
	    .25246,.4358,.19366,.17048,0.0,0.0,0.0,-1.5216e-8,-2.56e-7,
	    3.054e-7,.044317,.087688,.1956,0.0,0.0,0.0,-.10736,.12864,.12671,
	    -.018054,.012526,.072251,0.0,0.0,0.0,-7.9766e-8,7.8717e-8,
	    7.0752e-7,-.013027,-.02281,-.0013912,0.0,0.0,0.0,-.041078,.029376,
	    .051175,.041295,-.0022711,.049874,0.0,0.0,0.0,4.7277e-8,
	    -2.0378e-9,-1.0432e-6,-.0044592,-.011824,-.0051299,0.0,0.0,0.0,
	    .6334,.37085,.15597,.10223,-.048523,-.22192,0.0,0.0,0.0,
	    -1.5529e-8,2.5941e-7,-1.9061e-7,.13085,-8.2298e-4,-.13285,0.0,0.0,
	    0.0,.0081139,.023336,.097418,-.077696,-.22395,-.17111,0.0,0.0,0.0,
	    1.4044e-8,-2.5896e-7,2.2626e-6,-.073836,-.034992,-.028852,0.0,0.0,
	    0.0,.0058076,.070754,.063152,.01978,.018125,.017141,0.0,0.0,0.0,
	    -4.6109e-8,1.5037e-7,-2.4478e-6,.015735,.01423,-.041047,0.0,0.0,
	    0.0,-.088933,-.16104,-.16992,-.059522,-.027661,.13092,0.0,0.0,0.0,
	    -6.0933e-9,2.5861e-8,-6.0624e-7,.048434,.023424,.029271,0.0,0.0,
	    0.0,.0089345,.021873,-.016865,.01597,.0047094,.021492,0.0,0.0,0.0,
	    7.8024e-9,-3.9311e-10,2.6681e-7,.0035974,-.010739,.031053,0.0,0.0,
	    0.0,.010524,.017883,.0024771,-.003801,-.0034746,.017248,0.0,0.0,
	    0.0,-.0708,-.059487,-.039535,-.10031,-.22153,-.17665,0.0,0.0,0.0,
	    3.0069e-8,7.5016e-8,5.9015e-7,.017651,-.018756,-.0019095,0.0,0.0,
	    0.0,-.038559,-.0038658,-.054337,.012491,-.0071623,-.01009,0.0,0.0,
	    0.0,1.981e-9,-1.5184e-8,-1.4229e-7,.0090502,.0046047,-.028027,0.0,
	    0.0,0.0,-.02764,-.022297,-.025864,-.0087768,-.0045071,-.015999,
	    0.0,0.0,0.0,-.038927,-.032125,.045711,-.0096294,.022894,.069373,
	    0.0,0.0,0.0,2.5396e-8,1.3503e-8,1.4937e-7,.018994,-.024285,
	    -.040136,0.0,0.0,0.0,-.0059943,-.0010069,-.01996,.0046892,
	    -.0055847,.013345,0.0,0.0,0.0,1.4326e-8,2.3685e-8,-1.0504e-7,
	    2.5748e-4,-9.8852e-4,.0095536,0.0,0.0,0.0,-.020216,-.023076,
	    .012233,-.0096002,.067171,-.010609,0.0,0.0,0.0,-1.0963e-8,
	    1.6395e-8,-6.6122e-8,-.006245,-5.0134e-4,-.022548,0.0,0.0,0.0,
	    -.010778,-.0047465,8.5225e-4,.0090447,-.0029361,-.015098,0.0,0.0,
	    0.0,-3.1408e-9,2.1465e-9,8.6051e-9,-.0018477,-.0042558,-.011711,
	    0.0,0.0,0.0,-.0090961,-.021087,.027375,.018898,.015103,.026458,
	    0.0,0.0,0.0,-1.6521e-8,-1.0412e-8,6.545e-8,-.0069182,-.009786,
	    -.015922,0.0,0.0,0.0,.0053029,-.004445,-.0061311,.0020626,
	    -.0018098,.0034746,0.0,0.0,0.0,-.033221,.0069945,.012666,.0047967,
	    .018795,-.018009,0.0,0.0,0.0,2.9052e-11,1.608e-8,1.9864e-7,
	    -.0057386,.0045063,4.8529e-4,0.0,0.0,0.0,-.0019158,.0031289,
	    .0028454,-6.0267e-4,.0024747,-.0038353,0.0,0.0,0.0,.0063675,
	    .009476,.01902,.025325,.011677,.0019446,0.0,0.0,0.0,-8.1957e-9,
	    -8.4313e-9,-5.1153e-8,.0011937,-.0042526,-.0074106,0.0,0.0,0.0,
	    .007436,-.0021643,.0044576,.021619,.014606,-.0039309,0.0,0.0,0.0,
	    -7.6241e-9,-8.3007e-9,-2.0117e-8,-.0013459,.0022638,-.0013632,0.0,
	    0.0,0.0,.0065228,.0023316,.0086293,.037915,.021285,-.0047108,0.0,
	    0.0,0.0,.0032586,-.0088253,-.0055447,.017314,.013963,.0072728 };
    static doublereal dnl[441]	/* was [3][3][49] */ = { -1.7368,-1.5547,
	    -1.7382,-1.7418,-1.5723,-1.4667,0.0,0.0,0.0,-3.0027e-8,6.7091e-7,
	    -6.0635e-7,.070525,.40251,.163,0.0,0.0,0.0,.22184,.40622,.4474,
	    .29785,.40235,.64765,0.0,0.0,0.0,-6.7089e-7,-5.583e-8,4.7518e-7,
	    .011675,-.16855,-.16832,0.0,0.0,0.0,-.10635,-.13901,.091015,
	    -.092159,-.14445,-.19603,0.0,0.0,0.0,6.8139e-7,-6.7244e-7,
	    8.6631e-7,-.1295,-.02999,.13735,0.0,0.0,0.0,.058091,.1488,
	    -.0041582,-.058461,-.20387,-.28157,0.0,0.0,0.0,-.062121,-.082658,
	    -.31542,-.13966,-.17979,-.091417,0.0,0.0,0.0,3.1864e-7,2.6659e-7,
	    -8.6896e-7,.015042,.19726,-.024826,0.0,0.0,0.0,.048208,.010021,
	    -.088282,.046388,-.068767,-.027273,0.0,0.0,0.0,-2.744e-7,
	    1.3823e-7,1.7889e-7,-.0097774,-.027798,.031754,0.0,0.0,0.0,-.0024,
	    -.0074716,-.038424,.0035422,.0045989,.02012,0.0,0.0,0.0,6.6031e-8,
	    -8.922e-8,5.6129e-8,-.0086287,.013561,-.0068389,0.0,0.0,0.0,
	    -.10868,-.13959,-.10561,-.08771,-.12212,-.096535,0.0,0.0,0.0,
	    7.2869e-8,2.0864e-7,1.0863e-7,.038852,.024244,.019137,0.0,0.0,0.0,
	    -.010042,-.010484,-.037752,-.0090949,-.04267,-.032374,0.0,0.0,0.0,
	    -4.6008e-8,4.4276e-8,-1.1781e-7,-.018152,.062073,.071156,0.0,0.0,
	    0.0,.0016205,.019706,-.041151,3.6013e-4,-.0052021,.013993,0.0,0.0,
	    0.0,4.6331e-9,-1.1884e-7,-1.4323e-8,.0072089,-.02386,-.038484,0.0,
	    0.0,0.0,-.036398,-.012037,-.038984,.025707,-.064837,.031979,0.0,
	    0.0,0.0,1.7139e-7,-6.249e-8,-4.7271e-7,.0084327,.031524,-.04256,
	    0.0,0.0,0.0,6.2127e-4,-.029276,-.037386,-.0065605,-.018784,
	    -.003819,0.0,0.0,0.0,-4.0138e-8,4.0271e-8,8.5416e-8,4.8306e-4,
	    .012402,.011174,0.0,0.0,0.0,.0012439,-.01231,-.012316,5.0042e-4,
	    1.1119e-5,-.0023599,0.0,0.0,0.0,-.018217,-.0026679,.10742,
	    -.031783,-.019303,.0034835,0.0,0.0,0.0,4.6073e-8,3.5891e-8,
	    1.5944e-7,.0057723,-.022166,-.006433,0.0,0.0,0.0,.0037524,
	    -.0065922,-.0028192,.008823,.011413,-.0014724,0.0,0.0,0.0,
	    -2.0566e-8,-1.6467e-8,-1.2504e-8,-.002626,-.0022769,-.0027194,0.0,
	    0.0,0.0,-.0030241,-3.9885e-4,-.016905,-.0011217,.0010334,.0018374,
	    0.0,0.0,0.0,.027188,.020962,.02827,.057169,-.0036042,.0079017,0.0,
	    0.0,0.0,6.3375e-8,-5.5785e-8,-1.9685e-7,-.0052793,-.0034116,
	    -.013993,0.0,0.0,0.0,-.0037723,-.0074266,.0089762,-.0031765,
	    -.0042969,1.4415e-4,0.0,0.0,0.0,-3.9013e-9,2.5071e-8,2.8706e-8,
	    5.1564e-4,.0037668,.0018409,0.0,0.0,0.0,.0069304,.0224,.067218,
	    .013519,-.016617,.0015734,0.0,0.0,0.0,5.703e-8,-2.8034e-8,
	    5.7165e-8,-.0039896,-.020903,-.01315,0.0,0.0,0.0,-1.2236e-4,
	    -.0012509,-.0082717,.0017336,.011176,-.0043392,0.0,0.0,0.0,
	    -6.4988e-9,-1.9655e-8,3.0388e-8,-2.8791e-4,-.0034928,-8.7189e-4,
	    0.0,0.0,0.0,.012409,.010287,.019133,.013395,-.019803,-.0069494,
	    0.0,0.0,0.0,6.2839e-9,2.6129e-8,1.4687e-8,-.0053013,-.0037789,
	    -.0070281,0.0,0.0,0.0,-.0014527,-.0013332,5.5305e-4,-5.6986e-4,
	    2.9788e-4,-.0015472,0.0,0.0,0.0,.001437,.010731,.0079431,.003063,
	    -.03188,7.6997e-4,0.0,0.0,0.0,1.8605e-8,2.4252e-9,4.8793e-8,
	    -.0038017,-.010222,-.0097752,0.0,0.0,0.0,1.8677e-4,.0015417,
	    .0086786,9.3966e-4,.0037033,-.0010346,0.0,0.0,0.0,.0039142,
	    .0031698,.004901,-5.1651e-4,-.030094,-.0042392,0.0,0.0,0.0,
	    -4.8721e-9,1.8012e-8,3.24e-8,-.0030807,-2.2242e-4,-.0073591,0.0,
	    0.0,0.0,-.0041931,-.0031057,-.0038863,-.0044359,-.028816,.01061,
	    0.0,0.0,0.0,7.9621e-9,1.534e-8,-2.5953e-8,-.0020503,-.0044691,
	    -.0058767,0.0,0.0,0.0,1.9265e-4,.0030302,-.0023986,8.0675e-4,
	    -.022928,2.4544e-4,0.0,0.0,0.0,-.0013332,-.0029436,-.0069512,
	    1.1912e-4,-.016669,.0060162 };

    /* Builtin functions */
    double d_lg10(doublereal *), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal nhh, nhl, nnh, noh, nnl, nol, nheh, nhel, ntot;
    extern /* Subroutine */ int ionlow_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *), 
	    ionhigh_(integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, integer *, doublereal *);

/* Version 1.0 (released 20.12.2002) */
/* CALION calculates relative density of O+, H+, He+ and N+  in the outer */
/* ionosphere with regard to solar activity (F107 index). */
/* CALION uses subroutines IONLOW and IONHIGH. */
/* Linearly interpolates for solar activity. */
/* Inputs: CRD - 0 .. INVDIP */
/*               1 .. FL, DIMO, B0, DIPL (used for calculation INVDIP inside) */
/*         INVDIP - "mix" coordinate of the dip latitude and of */
/*                    the invariant latitude; */
/*                    positive northward, in deg, range <-90.0;90.0> */
/*         FL, DIMO, B0 - McIlwain L parameter, dipole moment in */
/*                        Gauss, magnetic field strength in Gauss - */
/*                        parameters needed for invariant latitude */
/*                        calculation */
/*         DIPL - dip latitude */
/*                positive northward, in deg, range <-90.0;90.0> */
/*         MLT - magnetic local time (central dipole) */
/*               in hours, range <0;24) */
/*         ALT - altitude above the Earth's surface; */
/*               in km, range <350;2000> */
/*         DDD - day of year; range <0;365> */
/*         F107 - F107 index */
/* Output: NO,NH,NHE,NN - relative density of O+, H+, He+, and N+ */
/* Versions:  1.0 FORTRAN */
/* Author of the code: */
/*         Vladimir Truhlik */
/*         Institute of Atm. Phys. */
/*         Bocni II. */
/*         141 31 Praha 4, Sporilov */
/*         Czech Republic */
/*         e-mail: vtr@ufa.cas.cz */
/*         tel/fax: +420 267103058, +420 728073539 / +420 272 762528 */
/* /////////////////////coefficients high solar activity//////////////////////// */
/* //////////////////////////////////O+///////////////////////////////////////// */
/*     550km equinox */
/*     550km June solstice */
/*     900km equinox */
/*     900km June solstice */
/*     1500km equinox */
/*     1500km June solstice */
/*     2250km equinox */
/*     2250km June solstice */
/* //////////////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////////////H+//////////////////////////////////////////////// */
/*     550km equinox */
/*     550km June solstice */
/*     900km equinox */
/*     900km June solstice */
/*     1500km equinox */
/*     1500km June solstice */
/*     2250km equinox */
/*     2250km June solstice */
/* //////////////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////////////He+/////////////////////////////////////////////// */
/*     550km equinox */
/*     550km June solstice */
/*     900km equinox */
/*     900km June solstice */
/*     1500km equinox */
/*     1500km June solstice */
/*     2250km equinox */
/*     2250km June solstice */
/* //////////////////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////N+/////////////////////////////////////////////// */
/*     550km equinox */
/*     550km June solstice */
/*     900km equinox */
/*     900km June solstice */
/*     1500km equinox */
/*     1500km June solstice */
/*     2250km equinox */
/*     2250km June solstice */
/* //////////////////////////////////////////////////////////////////////////////////// */
/* /////////////////////coefficients low solar activity//////////////////////////////// */
/* //////////////////////////////////O+//////////////////////////////////////////////// */
/*     400km equinox */
/*     400km June solstice */
/*     650km equinox */
/*     650km June solstice */
/*     1000km equinox */
/*     1000km June solstice */
/* //////////////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////////////H+//////////////////////////////////////////////// */
/*     400km equinox */
/*     400km June solstice */
/*     650km equinox */
/*     650km June solstice */
/*     1000km equinox */
/*     1000km June solstice */
/* ///////////////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////////////He+//////////////////////////////////////////////// */
/*     400km equinox */
/*     400km June solstice */
/*     650km equinox */
/*     650km June solstice */
/*     1000km equinox */
/*     1000km June solstice */
/* //////////////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////////////N+//////////////////////////////////////////////// */
/*     400km equinox */
/*     400km June solstice */
/*     650km equinox */
/*     650km June solstice */
/*     1000km equinox */
/*     1000km June solstice */
/* //////////////////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////solar minimum//////////////////////////////////////// */
    ionlow_(crd, invdip, fl, dimo, b0, dipl, mlt, alt, ddd, dol, &c__0, &nol);
    ionlow_(crd, invdip, fl, dimo, b0, dipl, mlt, alt, ddd, dhl, &c__1, &nhl);
    ionlow_(crd, invdip, fl, dimo, b0, dipl, mlt, alt, ddd, dhel, &c__2, &
	    nhel);
    ionlow_(crd, invdip, fl, dimo, b0, dipl, mlt, alt, ddd, dnl, &c__3, &nnl);
/*     normalization */
    ntot = nol + nhl + nhel + nnl;
    nol /= ntot;
    nhl /= ntot;
    nhel /= ntot;
    nnl /= ntot;
/* ///////////////////////////////solar maximum//////////////////////////////////////// */
    ionhigh_(crd, invdip, fl, dimo, b0, dipl, mlt, alt, ddd, doh, &c__0, &noh)
	    ;
    ionhigh_(crd, invdip, fl, dimo, b0, dipl, mlt, alt, ddd, dhh, &c__1, &nhh)
	    ;
    ionhigh_(crd, invdip, fl, dimo, b0, dipl, mlt, alt, ddd, dheh, &c__2, &
	    nheh);
    ionhigh_(crd, invdip, fl, dimo, b0, dipl, mlt, alt, ddd, dnh, &c__3, &nnh)
	    ;
/*     normalization */
    ntot = noh + nhh + nheh + nnh;
    noh /= ntot;
    nhh /= ntot;
    nheh /= ntot;
    nnh /= ntot;
/*     interpolation (in logarithm) */
    if (*f107 > 200.) {
	*f107 = 200.;
    }
    if (*f107 < 85.) {
	*f107 = 85.;
    }
    *no = (d_lg10(&noh) - d_lg10(&nol)) / 115. * (*f107 - 85.) + d_lg10(&nol);
    *nh = (d_lg10(&nhh) - d_lg10(&nhl)) / 115. * (*f107 - 85.) + d_lg10(&nhl);
    *nhe = (d_lg10(&nheh) - d_lg10(&nhel)) / 115. * (*f107 - 85.) + d_lg10(&
	    nhel);
    *nn = (d_lg10(&nnh) - d_lg10(&nnl)) / 115. * (*f107 - 85.) + d_lg10(&nnl);
/*     percentages */
    *no = pow_dd(&c_b30, no);
    *nh = pow_dd(&c_b30, nh);
    *nhe = pow_dd(&c_b30, nhe);
    *nn = pow_dd(&c_b30, nn);
/*     last normalization */
    ntot = *no + *nh + *nhe + *nn;
    *no /= ntot;
    *nh /= ntot;
    *nhe /= ntot;
    *nn /= ntot;
    return 0;
} /* calion_ */

#undef dnh
#undef dheh
#undef dhh
#undef doh


/* Subroutine */ int ionlow_(integer *crd, doublereal *invdip, doublereal *fl,
	 doublereal *dimo, doublereal *b0, doublereal *dipl, doublereal *mlt, 
	doublereal *alt, integer *ddd, doublereal *d__, integer *ion, 
	doublereal *nion)
{
    /* Initialized data */

    static integer mirreq[49] = { 1,-1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,
	    -1,1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1,1,-1,
	    1,-1,1,1 };

    /* Builtin functions */
    double log(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c__[49];
    static integer i__;
    extern /* Subroutine */ int spharm_ik__(doublereal *, integer *, integer *
	    , doublereal *, doublereal *);
    static doublereal aa, bb, ah[3], st[2], n400, n650, st1, st2, n1000, ano[
	    3], dno[1], sum, n100a, n100b, n400a, n400b, n650a, n650b;
    static integer ddda, dddb, dddd;
    static doublereal n0a100, n0b100, n0a400, n0b400, n0a650, n0b650;
    static integer seza, sezb;
    static doublereal dtor;
    extern doublereal eptr_(doublereal *, doublereal *, doublereal *);
    static doublereal rmlt;
    static integer sezai, sezbi;
    static doublereal invdp;
    extern doublereal invdpc_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal rcolat;

/* IONLOW calculates relative density of O+, H+, He+ or N+  in the outer */
/* ionosphere for a low solar activity (F107 < 100). */
/* Based on spherical harmonics approximation of relative ion density */
/* (by AE-C, and AE-E) at altitudes centred on 400km, 650km, and 1000km. */
/* For intermediate altitudes an interpolation is used. */
/* Recommended altitude range: 350-2000 km!!! */
/* For days between seasons centred at (21.3. = 79; 21.6. = 171; */
/* 23.9. 265; 21.12. = 354) relative ion density is linearly interpolated. */
/* Inputs: CRD - 0 .. INVDIP */
/*               1 .. FL, DIMO, B0, DIPL (used for calculation INVDIP inside) */
/*         INVDIP - "mix" coordinate of the dip latitude and of */
/*                    the invariant latitude; */
/*                    positive northward, in deg, range <-90.0;90.0> */
/*         FL, DIMO, BO - McIlwain L parameter, dipole moment in */
/*                        Gauss, magnetic field strength in Gauss - */
/*                        parameters needed for invariant latitude */
/*                        calculation */
/*         DIPL - dip latitude */
/*                positive northward, in deg, range <-90.0;90.0> */
/*         MLT - magnetic local time (central dipole) */
/*               in hours, range <0;24) */
/*         ALT - altitude above the Earth's surface; */
/*               in km, range <350;2000> */
/*         DDD - day of year; range <0;365> */
/*         D - coefficints of spherical harmonics for a given ion */
/*         ION - ion species (0...O+, 1...H+, 2...He+, 3...N+) */
/* Output: NION - relative density for a given ion */
    /* Parameter adjustments */
    d__ -= 13;

    /* Function Body */
/* //////////////////////////////////////////////////////////////////////////////////// */
    dtor = .01745329252;
/*     coefficients for mirroring */
    for (i__ = 1; i__ <= 49; ++i__) {
	d__[(i__ * 3 + 3) * 3 + 1] = d__[(i__ * 3 + 2) * 3 + 1] * mirreq[i__ 
		- 1];
	d__[(i__ * 3 + 3) * 3 + 2] = d__[(i__ * 3 + 2) * 3 + 2] * mirreq[i__ 
		- 1];
/* L10: */
	d__[(i__ * 3 + 3) * 3 + 3] = d__[(i__ * 3 + 2) * 3 + 3] * mirreq[i__ 
		- 1];
    }
    if (*crd == 1) {
	invdp = invdpc_(fl, dimo, b0, dipl, &dtor);
    } else if (*crd == 0) {
	invdp = *invdip;
    } else {
	return 0;
    }
    rmlt = *mlt * dtor * 15.;
    rcolat = (90. - invdp) * dtor;
    spharm_ik__(c__, &c__6, &c__6, &rcolat, &rmlt);
/*     21.3. - 20.6. */
    if (*ddd >= 79 && *ddd < 171) {
	seza = 1;
	sezb = 2;
	ddda = 79;
	dddb = 171;
	dddd = *ddd;
    }
/*     21.6. - 22.9. */
    if (*ddd >= 171 && *ddd < 265) {
	seza = 2;
	sezb = 4;
	ddda = 171;
	dddb = 265;
	dddd = *ddd;
    }
/*     23.9. - 20.12. */
    if (*ddd >= 265 && *ddd < 354) {
	seza = 4;
	sezb = 3;
	ddda = 265;
	dddb = 354;
	dddd = *ddd;
    }
/*     21.12. - 20.3. */
    if (*ddd >= 354 || *ddd < 79) {
	seza = 3;
	sezb = 1;
	ddda = 354;
	dddb = 444;
	dddd = *ddd;
	if (*ddd >= 354) {
	    dddd = *ddd;
	} else {
	    dddd = *ddd + 365;
	}
    }
    sezai = (seza - 1) % 3 + 1;
    sezbi = (sezb - 1) % 3 + 1;
/*     400km level */
    n0a400 = 0.;
    n0b400 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a400 += c__[i__ - 1] * d__[(sezai + i__ * 3) * 3 + 1];
/* L30: */
	n0b400 += c__[i__ - 1] * d__[(sezbi + i__ * 3) * 3 + 1];
    }
    n400a = n0a400;
    n400b = n0b400;
    n400 = (n400b - n400a) / (dddb - ddda) * (dddd - ddda) + n400a;
/*     650km level */
    n0a650 = 0.;
    n0b650 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a650 += c__[i__ - 1] * d__[(sezai + i__ * 3) * 3 + 2];
/* L70: */
	n0b650 += c__[i__ - 1] * d__[(sezbi + i__ * 3) * 3 + 2];
    }
    n650a = n0a650;
    n650b = n0b650;
    n650 = (n650b - n650a) / (dddb - ddda) * (dddd - ddda) + n650a;
/*     1000km level */
    n0a100 = 0.;
    n0b100 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a100 += c__[i__ - 1] * d__[(sezai + i__ * 3) * 3 + 3];
/* L110: */
	n0b100 += c__[i__ - 1] * d__[(sezbi + i__ * 3) * 3 + 3];
    }
    n100a = n0a100;
    n100b = n0b100;
    n1000 = (n100b - n100a) / (dddb - ddda) * (dddd - ddda) + n100a;
/*      IF (ALT .LT. 650) NO=(N650-N400)/250.0*(ALT-400)+N400 */
/*      IF (ALT .GE. 650) NO=(N1000-N650)/350.0*(ALT-650)+N650 */
/*      NION=10**NO */
    ano[0] = n400;
    ano[1] = n650;
    ano[2] = n1000;
    ah[0] = 400.;
    ah[1] = 650.;
    ah[2] = 1e3;
    dno[0] = 20.;
    st1 = (ano[1] - ano[0]) / (ah[1] - ah[0]);
    i__ = 2;
    st2 = (ano[i__] - ano[i__ - 1]) / (ah[i__] - ah[i__ - 1]);
    ano[i__ - 1] -= (st2 - st1) * dno[i__ - 2] * log(2.);
    for (i__ = 1; i__ <= 2; ++i__) {
/* L220: */
	st[i__ - 1] = (ano[i__] - ano[i__ - 1]) / (ah[i__] - ah[i__ - 1]);
    }
    argexp_1.argmax = 88.;
    sum = ano[0] + st[0] * (*alt - ah[0]);
    i__ = 1;
    aa = eptr_(alt, &dno[i__ - 1], &ah[i__]);
    bb = eptr_(ah, &dno[i__ - 1], &ah[i__]);
    sum += (st[i__] - st[i__ - 1]) * (aa - bb) * dno[i__ - 1];
    *nion = pow_dd(&c_b30, &sum);
    return 0;
} /* ionlow_ */

/* Subroutine */ int ionhigh_(integer *crd, doublereal *invdip, doublereal *
	fl, doublereal *dimo, doublereal *b0, doublereal *dipl, doublereal *
	mlt, doublereal *alt, integer *ddd, doublereal *d__, integer *ion, 
	doublereal *nion)
{
    /* Initialized data */

    static integer mirreq[49] = { 1,-1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,
	    -1,1,-1,1,-1,1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1,1,-1,
	    1,-1,1,1 };

    /* Builtin functions */
    double log(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c__[49];
    static integer i__;
    extern /* Subroutine */ int spharm_ik__(doublereal *, integer *, integer *
	    , doublereal *, doublereal *);
    static doublereal aa, bb, ah[4], st[3], n900, n550, st1, st2, n1500, 
	    n2500, ano[4], dno[2], sum, n150a, n150b, n250a, n900a, n550a, 
	    n550b, n900b, n250b;
    static integer ddda, dddb, dddd;
    static doublereal n0a150, n0b150, n0a250, n0a900, n0a550, n0b550, n0b900, 
	    n0b250;
    static integer seza, sezb;
    static doublereal dtor;
    extern doublereal eptr_(doublereal *, doublereal *, doublereal *);
    static doublereal rmlt;
    static integer sezai, sezbi;
    static doublereal invdp;
    extern doublereal invdpc_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal rcolat;

/* IONHIGH calculates relative density of O+, H+, He+ or N+  in the outer */
/* ionosphere for high solar activity conditions (F107 >= 100). */
/* Based on spherical harmonics approximation of relative ion density */
/* (by IK24) at altitudes centred on 550km, 900km, 1500km, and 2250km. */
/* For intermediate altitudes a interpolation is used. */
/* Recommended altitude range: 500-3000 km!!! */
/* For days between seasons centred at (21.3. = 79; 21.6. = 171; */
/* 23.9. 265; 21.12. = 354) relative ion density is linearly interpolated. */
/* Inputs: CRD - 0 .. INVDIP */
/*               1 .. FL, DIMO, B0, DIPL (used for calculation INVDIP inside) */
/*         INVDIP - "mix" coordinate of the dip latitude and of */
/*                    the invariant latitude; */
/*                    positive northward, in deg, range <-90.0;90.0> */
/*         FL, DIMO, BO - McIlwain L parameter, dipole moment in */
/*                        Gauss, magnetic field strength in Gauss - */
/*                        parameters needed for invariant latitude */
/*                        calculation */
/*         DIPL - dip latitude */
/*                positive northward, in deg, range <-90.0;90.0> */
/*         MLT - magnetic local time (central dipole) */
/*               in hours, range <0;24) */
/*         ALT - altitude above the Earth's surface; */
/*               in km, range <500;3000> */
/*         DDD - day of year; range <0;365> */
/*         D - coefficints of spherical harmonics for a given ion */
/*         ION - ion species (0...O+, 1...H+, 2...He+, 3...N+) */
/* Output: NION - relative density for a given ion */
    /* Parameter adjustments */
    d__ -= 17;

    /* Function Body */
/* //////////////////////////////////////////////////////////////////////////////////// */
    dtor = .01745329252;
/*     coefficients for mirroring */
    for (i__ = 1; i__ <= 49; ++i__) {
	d__[(i__ * 3 + 3 << 2) + 1] = d__[(i__ * 3 + 2 << 2) + 1] * mirreq[
		i__ - 1];
	d__[(i__ * 3 + 3 << 2) + 2] = d__[(i__ * 3 + 2 << 2) + 2] * mirreq[
		i__ - 1];
	d__[(i__ * 3 + 3 << 2) + 3] = d__[(i__ * 3 + 2 << 2) + 3] * mirreq[
		i__ - 1];
/* L10: */
	d__[(i__ * 3 + 3 << 2) + 4] = d__[(i__ * 3 + 2 << 2) + 4] * mirreq[
		i__ - 1];
    }
    if (*crd == 1) {
	invdp = invdpc_(fl, dimo, b0, dipl, &dtor);
    } else if (*crd == 0) {
	invdp = *invdip;
    } else {
	return 0;
    }
    rmlt = *mlt * dtor * 15.;
    rcolat = (90. - invdp) * dtor;
    spharm_ik__(c__, &c__6, &c__6, &rcolat, &rmlt);
/*     21.3. - 20.6. */
    if (*ddd >= 79 && *ddd < 171) {
	seza = 1;
	sezb = 2;
	ddda = 79;
	dddb = 171;
	dddd = *ddd;
    }
/*     21.6. - 22.9. */
    if (*ddd >= 171 && *ddd < 265) {
	seza = 2;
	sezb = 4;
	ddda = 171;
	dddb = 265;
	dddd = *ddd;
    }
/*     23.9. - 20.12. */
    if (*ddd >= 265 && *ddd < 354) {
	seza = 4;
	sezb = 3;
	ddda = 265;
	dddb = 354;
	dddd = *ddd;
    }
/*     21.12. - 20.3. */
    if (*ddd >= 354 || *ddd < 79) {
	seza = 3;
	sezb = 1;
	ddda = 354;
	dddb = 444;
	dddd = *ddd;
	if (*ddd >= 354) {
	    dddd = *ddd;
	} else {
	    dddd = *ddd + 365;
	}
    }
    sezai = (seza - 1) % 3 + 1;
    sezbi = (sezb - 1) % 3 + 1;
/*     550km level */
    n0a550 = 0.;
    n0b550 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a550 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) + 1];
/* L30: */
	n0b550 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) + 1];
    }
    n550a = n0a550;
    n550b = n0b550;
    n550 = (n550b - n550a) / (dddb - ddda) * (dddd - ddda) + n550a;
/*     900km level */
    n0a900 = 0.;
    n0b900 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a900 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) + 2];
/* L70: */
	n0b900 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) + 2];
    }
    n900a = n0a900;
    n900b = n0b900;
    n900 = (n900b - n900a) / (dddb - ddda) * (dddd - ddda) + n900a;
/*     1500km level */
    n0a150 = 0.;
    n0b150 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a150 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) + 3];
/* L110: */
	n0b150 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) + 3];
    }
    n150a = n0a150;
    n150b = n0b150;
    n1500 = (n150b - n150a) / (dddb - ddda) * (dddd - ddda) + n150a;
/*     2500km level */
    n0a250 = 0.;
    n0b250 = 0.;
    for (i__ = 1; i__ <= 49; ++i__) {
	n0a250 += c__[i__ - 1] * d__[(sezai + i__ * 3 << 2) + 4];
/* L150: */
	n0b250 += c__[i__ - 1] * d__[(sezbi + i__ * 3 << 2) + 4];
    }
    n250a = n0a250;
    n250b = n0b250;
    n2500 = (n250b - n250a) / (dddb - ddda) * (dddd - ddda) + n250a;
/*      IF (ALT .LT. 900) NO=(N900-N550)/350.0*(ALT-550)+N550 */
/*      IF ((ALT .GE. 900) .AND. (ALT .LT. 1500)) */
/*     &  NO=(N1500-N900)/600.0*(ALT-900)+N900 */
/*      IF (ALT .GE. 1500) NO=(N2500-N1500)/1000.0*(ALT-1500)+N1500 */
/*     O+ AND N+ may not increase above 1500km */
    if ((*ion == 0 || *ion == 3) && n2500 > n1500) {
	n2500 = n1500;
    }
/*     H+ may not decrease above 1500km */
    if (*ion == 1 && n2500 < n1500) {
	n2500 = n1500;
    }
    ano[0] = n550;
    ano[1] = n900;
    ano[2] = n1500;
    ano[3] = n2500;
    ah[0] = 550.;
    ah[1] = 900.;
    ah[2] = 1500.;
    ah[3] = 2250.;
    dno[0] = 20.;
    dno[1] = 20.;
    st1 = (ano[1] - ano[0]) / (ah[1] - ah[0]);
    for (i__ = 2; i__ <= 3; ++i__) {
	st2 = (ano[i__] - ano[i__ - 1]) / (ah[i__] - ah[i__ - 1]);
	ano[i__ - 1] -= (st2 - st1) * dno[i__ - 2] * log(2.);
/* L200: */
	st1 = st2;
    }
    for (i__ = 1; i__ <= 3; ++i__) {
/* L220: */
	st[i__ - 1] = (ano[i__] - ano[i__ - 1]) / (ah[i__] - ah[i__ - 1]);
    }
    argexp_1.argmax = 88.;
    sum = ano[0] + st[0] * (*alt - ah[0]);
    for (i__ = 1; i__ <= 2; ++i__) {
	aa = eptr_(alt, &dno[i__ - 1], &ah[i__]);
	bb = eptr_(ah, &dno[i__ - 1], &ah[i__]);
/* L230: */
	sum += (st[i__] - st[i__ - 1]) * (aa - bb) * dno[i__ - 1];
    }
    *nion = pow_dd(&c_b30, &sum);
    return 0;
} /* ionhigh_ */



doublereal invdpc_(doublereal *fl, doublereal *dimo, doublereal *b0, 
	doublereal *dipl, doublereal *dtor)
{
    /* Initialized data */

    static doublereal b[8] = { 1.259921,-.1984259,-.04686632,-.01314096,
	    -.00308824,8.2777e-4,-.00105877,.00183142 };

    /* System generated locals */
    doublereal ret_val, d__1, d__2, d__3, d__4, d__5, d__6, d__7, d__8;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), sqrt(doublereal), acos(
	    doublereal), sin(doublereal), cos(doublereal), d_sign(doublereal *
	    , doublereal *);

    /* Local variables */
    static doublereal a, asa, alfa, beta, invl, rdipl, rinvl;

/*      calculation of INVDIP from FL, DIMO, BO, and DIPL */
/*      invariant latitude calculated by highly */
/*      accurate polynomial expansion */
    d__1 = *dimo / *b0;
    a = pow_dd(&d__1, &c_b55) / *fl;
/* Computing 2nd power */
    d__1 = a;
/* Computing 3rd power */
    d__2 = a;
/* Computing 4th power */
    d__3 = a, d__3 *= d__3;
/* Computing 5th power */
    d__4 = a, d__5 = d__4, d__4 *= d__4;
/* Computing 6th power */
    d__6 = a, d__6 *= d__6;
/* Computing 7th power */
    d__7 = a, d__8 = d__7, d__7 *= d__7, d__8 *= d__7;
    asa = a * (b[0] + b[1] * a + b[2] * (d__1 * d__1) + b[3] * (d__2 * (d__2 *
	     d__2)) + b[4] * (d__3 * d__3) + b[5] * (d__5 * (d__4 * d__4)) + 
	    b[6] * (d__6 * (d__6 * d__6)) + b[7] * (d__8 * (d__7 * d__7)));
    if (asa > 1.) {
	asa = 1.;
    }
/*      invariant latitude (absolute value) */
    rinvl = acos(sqrt(asa));
    invl = rinvl / *dtor;
    rdipl = *dipl * *dtor;
/* Computing 3rd power */
    d__1 = sin((abs(rdipl)));
    alfa = d__1 * (d__1 * d__1);
/* Computing 3rd power */
    d__1 = cos(rinvl);
    beta = d__1 * (d__1 * d__1);
    ret_val = (alfa * d_sign(&c_b18, dipl) * invl + beta * *dipl) / (alfa + 
	    beta);
    return ret_val;
} /* invdpc_ */



/* ************************************************************* */
/* ************* PEAK VALUES ELECTRON DENSITY ****************** */
/* ************************************************************* */


doublereal fout_(doublereal *xmodip, doublereal *xlati, doublereal *xlongi, 
	doublereal *ut, doublereal *ff0)
{
    /* Initialized data */

    static integer qf[9] = { 11,11,8,4,1,0,0,0,0 };

    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal gamma1_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, integer 
	    *, integer *, doublereal *);

/* CALCULATES CRITICAL FREQUENCY FOF2/MHZ USING SUBROUTINE GAMMA1. */
/* XMODIP = MODIFIED DIP LATITUDE, XLATI = GEOG. LATITUDE, XLONGI= */
/* LONGITUDE (ALL IN DEG.), MONTH = MONTH, UT =  UNIVERSAL TIME */
/* (DEC. HOURS), FF0 = ARRAY WITH RZ12-ADJUSTED CCIR/URSI COEFF. */
/* D.BILITZA,JULY 85. */
    /* Parameter adjustments */
    --ff0;

    /* Function Body */
    ret_val = gamma1_(xmodip, xlati, xlongi, ut, &c__6, qf, &c__9, &c__76, &
	    c__13, &c__988, &ff0[1]);
    return ret_val;
} /* fout_ */



doublereal xmout_(doublereal *xmodip, doublereal *xlati, doublereal *xlongi, 
	doublereal *ut, doublereal *xm0)
{
    /* Initialized data */

    static integer qm[7] = { 6,7,5,2,1,0,0 };

    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal gamma1_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, integer 
	    *, integer *, doublereal *);

/* CALCULATES PROPAGATION FACTOR M3000 USING THE SUBROUTINE GAMMA1. */
/* XMODIP = MODIFIED DIP LATITUDE, XLATI = GEOG. LATITUDE, XLONGI= */
/* LONGITUDE (ALL IN DEG.), MONTH = MONTH, UT =  UNIVERSAL TIME */
/* (DEC. HOURS), XM0 = ARRAY WITH RZ12-ADJUSTED CCIR/URSI COEFF. */
/* D.BILITZA,JULY 85. */
    /* Parameter adjustments */
    --xm0;

    /* Function Body */
    ret_val = gamma1_(xmodip, xlati, xlongi, ut, &c__4, qm, &c__7, &c__49, &
	    c__9, &c__441, &xm0[1]);
    return ret_val;
} /* xmout_ */



doublereal hmf2ed_(doublereal *xmagbr, doublereal *r__, doublereal *x, 
	doublereal *xm3)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal f1, f2, f3, delm;

/* CALCULATES THE PEAK HEIGHT HMF2/KM FOR THE MAGNETIC */
/* LATITUDE XMAGBR/DEG. AND THE SMOOTHED ZUERICH SUNSPOT */
/* NUMBER R USING CCIR-M3000 XM3 AND THE RATIO X=FOF2/FOE. */
/* [REF. D.BILITZA ET AL., TELECOMM.J., 46, 549-553, 1979] */
/* D.BILITZA,1980. */
    f1 = *r__ * .00232 + .222;
    f2 = 1.2 - exp(*r__ * .0239) * .0116;
    f3 = (*r__ - 25.) * .096 / 150.;
    delm = f1 * (1. - *r__ / 150. * exp(-(*xmagbr) * *xmagbr / 1600.)) / (*x 
	    - f2) + f3;
    ret_val = 1490. / (*xm3 + delm) - 176.;
    return ret_val;
} /* hmf2ed_ */



doublereal xm3000hm_(doublereal *xmagbr, doublereal *r__, doublereal *x, 
	doublereal *hmf2)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal f1, f2, f3, delm;

/* CALCULATES THE PROPAGATION FACTOR M3000 FOR THE MAGNETIC LATITUDE */
/* XMAGBR/DEG. AND THE SMOOTHED ZUERICH SUNSPOT NUMBER R USING THE */
/* PEAK HEIGHT HMF2/KM AND THE RATIO X=FOF2/FOE. Reverse of HMF2ED. */
/* [REF. D.BILITZA ET AL., TELECOMM.J., 46, 549-553, 1979] */
/* D.BILITZA,1980. */
    f1 = *r__ * .00232 + .222;
    f2 = 1.2 - exp(*r__ * .0239) * .0116;
    f3 = (*r__ - 25.) * .096 / 150.;
    delm = f1 * (1. - *r__ / 150. * exp(-(*xmagbr) * *xmagbr / 1600.)) / (*x 
	    - f2) + f3;
    ret_val = 1490. / (*hmf2 + 176.) - delm;
    return ret_val;
} /* xm3000hm_ */



doublereal fof1ed_(doublereal *ylati, doublereal *r__, doublereal *chi)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    double cos(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal f0, fs, f100, dla, chi0, fof1, chim, xmue, chi100;

/* -------------------------------------------------------------- */
/* CALCULATES THE F1 PEAK PLASMA FREQUENCY (FOF1/MHZ) */
/* FOR   DIP-LATITUDE (YLATI/DEGREE) */
/*       SMOOTHED ZURICH SUNSPOT NUMBER (R) */
/*       SOLAR ZENITH ANGLE (CHI/DEGREE) */
/* REFERENCE: */
/*       E.D.DUCHARME ET AL., RADIO SCIENCE 6, 369-378, 1971 */
/*                                      AND 8, 837-839, 1973 */
/*       HOWEVER WITH MAGNETIC DIP LATITUDE INSTEAD OF GEOMAGNETIC */
/*       DIPOLE LATITUDE, EYFRIG, 1979 */
/* --------------------------------------------- D. BILITZA, 1988. */
    ret_val = 0.;
    if (*chi > 90.) {
	return ret_val;
    }
    dla = *ylati;
    f0 = dla * (.0058 - dla * 1.2e-4) + 4.35;
    f100 = dla * (.011 - dla * 2.3e-4) + 5.348;
    fs = f0 + (f100 - f0) * *r__ / 100.;
    xmue = dla * (.0046 - dla * 5.4e-5) + .093 + *r__ * 3e-4;
    d__1 = cos(*chi * const_1.umr);
    fof1 = fs * pow_dd(&d__1, &xmue);
    chi0 = dla * .349504 + 49.84733;
    chi100 = dla * .509932 + 38.96113;
    chim = chi0 + (chi100 - chi0) * *r__ / 100.;
    if (*chi > chim) {
	fof1 = -fof1;
    }
    ret_val = fof1;
    return ret_val;
} /* fof1ed_ */



doublereal f1_c1__(doublereal *xmodip, doublereal *hour, doublereal *suxnon, 
	doublereal *saxnon)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal), cos(doublereal);

    /* Local variables */
    static doublereal c1, pi, dela, c1old, absmdp;

/* F1 layer shape parameter C1 after Reinisch and Huang, Advances in */
/* Space Research, Volume 25, Number 1, 81-88, 2000. */
    pi = const_1.umr * 180.;
    absmdp = abs(*xmodip);
    dela = 4.32;
    if (absmdp >= 18.) {
	dela = exp(-(absmdp - 30.) / 10.) + 1.;
    }
    c1old = .11 / dela + .09;
    if (*suxnon == *saxnon) {
	c1 = c1old * 2.5;
    } else {
	c1 = c1old * 2.5 * cos((*hour - 12.) / (*suxnon - *saxnon) * pi);
    }
    if (c1 < 0.) {
	c1 = 0.;
    }
    ret_val = c1;
    return ret_val;
} /* f1_c1__ */



/* Subroutine */ int f1_prob__(doublereal *sza, doublereal *glat, doublereal *
	rz12, doublereal *f1prob, doublereal *f1probl)
{
    /* Builtin functions */
    double cos(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal a, b, c__, f1pr, xarg, f1prl, gamma;

/* Occurrence probability of F1 layer after Scotto et al., Advances in */
/* Space Research, Volume 20, Number 9, 1773-1775, 1997. */
/* Input: solar zenith angle (sza) in degrees, geomagnetic latitude */
/* (glat) in degrees, 12-month running mean of sunspot number (Rz12). */
/* Output: F1 occurrence probability without L-condition cases (f1prob) */
/* and with L-condition cases (f1probl) */
    xarg = cos(*sza * const_1.umr) * .5 + .5;
    a = *rz12 * .0854 + 2.98;
    b = .0107 - *rz12 * .0022;
    c__ = *rz12 * 1.47e-5 - 2.56e-4;
    gamma = a + (b + c__ * *glat) * *glat;
    f1pr = pow_dd(&xarg, &gamma);
    if (f1pr < .001) {
	f1pr = 0.;
    }
    *f1prob = f1pr;
    f1prl = pow_dd(&xarg, &c_b207);
    if (f1prl < .001) {
	f1prl = 0.;
    }
    *f1probl = f1prl;
    return 0;
} /* f1_prob__ */



doublereal foeedi_(doublereal *cov, doublereal *xhi, doublereal *xhim, 
	doublereal *xlati)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    double cos(doublereal), pow_dd(doublereal *, doublereal *), exp(
	    doublereal), log(doublereal);

    /* Local variables */
    static doublereal a, b, c__, d__, sl, sm, sp, xhic, smin, r4foe;

/* ------------------------------------------------------- */
/* CALCULATES FOE/MHZ BY THE EDINBURGH-METHOD. */
/* INPUT: MEAN 10.7CM SOLAR RADIO FLUX (COV), GEOGRAPHIC */
/* LATITUDE (XLATI/DEG), SOLAR ZENITH ANGLE (XHI/DEG AND */
/* XHIM/DEG AT NOON). */
/* REFERENCE: */
/*       KOURIS-MUGGELETON, CCIR DOC. 6/3/07, 1973 */
/*       TROST, J. GEOPHYS. RES. 84, 2736, 1979 (was used */
/*               to improve the nighttime varition) */
/* D.BILITZA--------------------------------- AUGUST 1986. */
/* variation with solar activity (factor A) ............... */
    a = (*cov - 66.) * .0094 + 1.;
/* variation with noon solar zenith angle (B) and with latitude (C) */
    sl = cos(*xlati * const_1.umr);
    if (*xlati < 32.) {
	sm = sl * 1.92 - 1.93;
	c__ = sl * 116. + 23.;
    } else {
	sm = .11 - sl * .49;
	c__ = sl * 35. + 92.;
    }
    if (*xhim >= 90.) {
	*xhim = 89.999;
    }
    d__1 = cos(*xhim * const_1.umr);
    b = pow_dd(&d__1, &sm);
/* variation with solar zenith angle (D) .......................... */
    if (*xlati > 12.) {
	sp = 1.2;
    } else {
	sp = 1.31;
    }
/* adjusted solar zenith angle during nighttime (XHIC) ............. */
    xhic = *xhi - log(exp((*xhi - 89.98) / 3.) + 1.) * 3.;
    d__1 = cos(xhic * const_1.umr);
    d__ = pow_dd(&d__1, &sp);
/* determine foE**4 ................................................ */
    r4foe = a * b * c__ * d__;
/* minimum allowable foE (sqrt[SMIN])............................... */
    smin = (*cov - 60.) * .0015 + .121;
    smin *= smin;
    if (r4foe < smin) {
	r4foe = smin;
    }
    ret_val = pow_dd(&r4foe, &c_b209);
    return ret_val;
} /* foeedi_ */



doublereal xmded_(doublereal *xhi, doublereal *r__, doublereal *yw)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double cos(doublereal), pow_dd(doublereal *, doublereal *), exp(
	    doublereal);

    /* Local variables */
    static doublereal y, yy, ymd;

/* D. BILITZA, 1978, CALCULATES ELECTRON DENSITY OF D MAXIMUM. */
/* XHI/DEG. IS SOLAR ZENITH ANGLE, R SMOOTHED ZURICH SUNSPOT NUMBER */
/* AND YW/M-3 THE ASSUMED CONSTANT NIGHT VALUE. */
/* [REF.: D.BILITZA, WORLD DATA CENTER A REPORT UAG-82,7,BOULDER,1981] */
/* corrected 4/25/97 - D. Bilitza */


    if (*xhi >= 90.) {
	goto L100;
    }
    y = *r__ * 8.8e6 + 6.05e8;
    yy = cos(*xhi * const_1.umr);
    ymd = y * exp(-.1 / pow_dd(&yy, &c_b212));
    if (ymd < *yw) {
	ymd = *yw;
    }
    ret_val = ymd;
    return ret_val;
L100:
    ret_val = *yw;
    return ret_val;
} /* xmded_ */



doublereal gamma1_(doublereal *smodip, doublereal *slat, doublereal *slong, 
	doublereal *hour, integer *iharm, integer *nq, integer *k1, integer *
	m, integer *mm, integer *m3, doublereal *sfe)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal);

    /* Local variables */
    static doublereal c__[12];
    static integer i__, j, l;
    static doublereal s[12], s0, s1, s2, s3;
    static integer mi, np;
    static doublereal ss, hou, sum, coef[100];
    static integer index;
    static doublereal xsinx[13];

/* CALCULATES GAMMA1=FOF2 OR M3000 USING CCIR NUMERICAL MAP */
/* COEFFICIENTS SFE(M3) FOR MODIFIED DIP LATITUDE (SMODIP/DEG) */
/* GEOGRAPHIC LATITUDE (SLAT/DEG) AND LONGITUDE (SLONG/DEG) */
/* AND UNIVERSIAL TIME (HOUR/DECIMAL HOURS). */
/* NQ(K1) IS AN INTEGER ARRAY GIVING THE HIGHEST DEGREES IN */
/* LATITUDE FOR EACH LONGITUDE HARMONIC. */
/* M=1+NQ1+2(NQ2+1)+2(NQ3+1)+... . */
/* SHEIKH,4.3.77. */
    /* Parameter adjustments */
    --nq;
    --sfe;

    /* Function Body */
    hou = (*hour * 15. - 180.) * const_1.umr;
    s[0] = sin(hou);
    c__[0] = cos(hou);
    i__1 = *iharm;
    for (i__ = 2; i__ <= i__1; ++i__) {
	c__[i__ - 1] = c__[0] * c__[i__ - 2] - s[0] * s[i__ - 2];
	s[i__ - 1] = c__[0] * s[i__ - 2] + s[0] * c__[i__ - 2];
/* L250: */
    }
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	mi = (i__ - 1) * *mm;
	coef[i__ - 1] = sfe[mi + 1];
	i__2 = *iharm;
	for (j = 1; j <= i__2; ++j) {
	    coef[i__ - 1] = coef[i__ - 1] + sfe[mi + (j << 1)] * s[j - 1] + 
		    sfe[mi + (j << 1) + 1] * c__[j - 1];
/* L300: */
	}
    }
    sum = coef[0];
    ss = sin(*smodip * const_1.umr);
    s3 = ss;
    xsinx[0] = 1.;
    index = nq[1];
    i__2 = index;
    for (j = 1; j <= i__2; ++j) {
	sum += coef[j] * ss;
	xsinx[j] = ss;
	ss *= s3;
/* L350: */
    }
    xsinx[nq[1] + 1] = ss;
    np = nq[1] + 1;
    ss = cos(*slat * const_1.umr);
    s3 = ss;
    i__2 = *k1;
    for (j = 2; j <= i__2; ++j) {
	s0 = *slong * (j - 1.) * const_1.umr;
	s1 = cos(s0);
	s2 = sin(s0);
	index = nq[j] + 1;
	i__1 = index;
	for (l = 1; l <= i__1; ++l) {
	    ++np;
	    sum += coef[np - 1] * xsinx[l - 1] * ss * s1;
	    ++np;
	    sum += coef[np - 1] * xsinx[l - 1] * ss * s2;
/* L450: */
	}
	ss *= s3;
/* L400: */
    }
    ret_val = sum;
    return ret_val;
} /* gamma1_ */



/* ************************************************************ */
/* ***************** PROFILE PARAMETERS *********************** */
/* ************************************************************ */


doublereal b0_98__(doublereal *hour, doublereal *sax, doublereal *sux, 
	integer *nseasn, doublereal *r__, doublereal *zlo, doublereal *zmodip)
{
    /* Initialized data */

    static doublereal b0f[48]	/* was [2][4][2][3] */ = { 201.,68.,210.,61.,
	    192.,68.,199.,67.,240.,80.,245.,83.,233.,71.,230.,65.,108.,65.,
	    142.,81.,110.,68.,77.,75.,124.,98.,164.,100.,120.,94.,96.,112.,
	    78.,81.,94.,84.,81.,81.,65.,70.,102.,87.,127.,91.,109.,88.,81.,
	    78. };
    static doublereal zx[5] = { 45.,72.,90.,108.,135. };
    static doublereal dd[5] = { 3.,3.,3.,3.,3. };

    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Local variables */
    static doublereal g[6];
    static integer i__;
    static doublereal aa, bb, zz, zx1, zz0, zx2, zx3, zx4, zx5, bfd[6]	/* 
	    was [2][3] */, bfr[12]	/* was [2][2][3] */;
    static integer isd, isl, iss;
    static doublereal sum;
    extern doublereal hpol_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal dsum;
    extern doublereal eptr_(doublereal *, doublereal *, doublereal *);
    static doublereal dayval;
    static integer jseasn;
    static doublereal nitval;
    static integer num_lat__;

/* ----------------------------------------------------------------- */
/* Interpolation procedure for bottomside thickness parameter B0. */
/* Array B0F(ILT,ISEASON,IR,ILATI) distinguishes between day and */
/* night (ILT=1,2), four seasons (ISEASON is northern season with */
/* ISEASON=1 northern spring), low and high solar activity Rz12=10, */
/* 100 (IR=1,2), and modified dip latitudes of 0, 18 and 45 */
/* degress (ILATI=1,2,3). In the DATA statement the first value */
/* corresponds to B0F(1,1,1,1), the second to B0F(2,1,1,1), the */
/* third to B0F(1,2,1,1) and so on. */

/* input: */
/*       hour    LT in decimal hours */
/*       SAX     time of sunrise in decimal hours */
/*       SUX     time of sunset in decimal hours */
/*       nseasn  season in northern hemisphere (1=spring) */
/*       R       12-month running mean of sunspot number */
/*       ZLO     longitude */
/*       ZMODIP  modified dip latitude */

/* JUNE 1989 --------------------------------------- Dieter Bilitza */

/* Updates (B0_new -> B0_98): */

/* 01/98 corrected to include a smooth transition at the modip equator */
/*       and no discontinuity at the equatorial change in season. */
/* 09/98 new B0 values incl values at the magnetic equator */
/* 10/98 longitude as input to determine if magnetic equator in northern */
/*         or southern hemisphere */

    num_lat__ = 3;
/* jseasn is southern hemisphere season */
    jseasn = *nseasn + 2;
    if (jseasn > 4) {
	jseasn += -4;
    }
    zz = *zmodip + 90.;
    zz0 = 0.;
/* Interpolation in Rz12: linear from 10 to 100 */
    i__1 = num_lat__;
    for (isl = 1; isl <= i__1; ++isl) {
	for (isd = 1; isd <= 2; ++isd) {
	    bfr[isd + ((isl << 1) + 1 << 1) - 7] = b0f[isd + (*nseasn + ((isl 
		    << 1) + 1 << 2) << 1) - 27] + (b0f[isd + (*nseasn + ((isl 
		    << 1) + 2 << 2) << 1) - 27] - b0f[isd + (*nseasn + ((isl 
		    << 1) + 1 << 2) << 1) - 27]) / 90. * (*r__ - 10.);
	    bfr[isd + ((isl << 1) + 2 << 1) - 7] = b0f[isd + (jseasn + ((isl 
		    << 1) + 1 << 2) << 1) - 27] + (b0f[isd + (jseasn + ((isl 
		    << 1) + 2 << 2) << 1) - 27] - b0f[isd + (jseasn + ((isl <<
		     1) + 1 << 2) << 1) - 27]) / 90. * (*r__ - 10.);
/* L7034: */
	}
/* Interpolation day/night with transitions at SAX (sunrise) */
/* and SUX (sunset) for northern/southern hemisphere iss=1/2 */
	for (iss = 1; iss <= 2; ++iss) {
	    dayval = bfr[(iss + (isl << 1) << 1) - 6];
	    nitval = bfr[(iss + (isl << 1) << 1) - 5];
	    bfd[iss + (isl << 1) - 3] = hpol_(hour, &dayval, &nitval, sax, 
		    sux, &c_b18, &c_b18);
/* L7033: */
	}
/* L7035: */
    }
/* Interpolation with epstein-transitions in modified dip latitude. */
/* Transitions at +/-18 and +/-45 degrees; constant above +/-45. */

/* g(1:5) are the latitudinal slopes of B0; */
/*       g(1) is for the region from -90 to -45 degrees */
/*       g(2) is for the region from -45 to -18 degrees */
/*       g(3) is for the region from -18 to   0 degrees */
/*       g(4) is for the region from   0 to  18 degrees */
/*       g(5) is for the region from  18 to  45 degrees */
/*       g(6) is for the region from  45 to  90 degrees */

/* B0 =  bfd(2,3) at modip = -45, */
/*       bfd(2,2) at modip = -18, */
/*       bfd(2,1) or bfd(1,1) at modip = 0, */
/*       bfd(1,2) at modip = 20, */
/*       bfd(1,3) at modip = 45. */
/* If the Longitude is between 200 and 320 degrees than the modip */
/* equator is in the southern hemisphere and bfd(2,1) is used at the */
/* equator, otherwise bfd(1,1) is used. */

    zx1 = bfd[5];
    zx2 = bfd[3];
    zx3 = bfd[0];
    if (*zlo > 200. && *zlo < 320.) {
	zx3 = bfd[1];
    }
    zx4 = bfd[2];
    zx5 = bfd[4];
    g[0] = 0.;
    g[1] = (zx2 - zx1) / 27.;
    g[2] = (zx3 - zx2) / 18.;
    g[3] = (zx4 - zx3) / 18.;
    g[4] = (zx5 - zx4) / 27.;
    g[5] = 0.;
/*        bb0 = bfd(2,3) */
/*      SUM = bb0 */
    sum = zx1;
    for (i__ = 1; i__ <= 5; ++i__) {
	aa = eptr_(&zz, &dd[i__ - 1], &zx[i__ - 1]);
	bb = eptr_(&zz0, &dd[i__ - 1], &zx[i__ - 1]);
	dsum = (g[i__] - g[i__ - 1]) * (aa - bb) * dd[i__ - 1];
	sum += dsum;
/* L1: */
    }
    ret_val = sum;
    return ret_val;
} /* b0_98__ */



/* Subroutine */ int tal_(doublereal *shabr, doublereal *sdelta, doublereal *
	shbr, doublereal *sdtdh0, logical *aus6, doublereal *spt)
{
    /* Builtin functions */
    double log(doublereal), sqrt(doublereal);

    /* Local variables */
    static doublereal b, c__, z1, z2, z3, z4;

/* CALCULATES THE COEFFICIENTS SPT FOR THE POLYNOMIAL */
/* Y(X)=1+SPT(1)*X**2+SPT(2)*X**3+SPT(3)*X**4+SPT(4)*X**5 */
/* TO FIT THE VALLEY IN Y, REPRESENTED BY: */
/* Y(X=0)=1, THE X VALUE OF THE DEEPEST VALLEY POINT (SHABR), */
/* THE PRECENTAGE DEPTH (SDELTA), THE WIDTH (SHBR) AND THE */
/* DERIVATIVE DY/DX AT THE UPPER VALLEY BOUNDRY (SDTDH0). */
/* IF THERE IS AN UNWANTED ADDITIONAL EXTREMUM IN THE VALLEY */
/* REGION, THEN AUS6=.TRUE., ELSE AUS6=.FALSE.. */
/* FOR -SDELTA THE COEFF. ARE CALCULATED FOR THE FUNCTION */
/* Y(X)=EXP(SPT(1)*X**2+...+SPT(4)*X**5). */
    /* Parameter adjustments */
    --spt;

    /* Function Body */
    z1 = -(*sdelta) / (*shabr * 100. * *shabr);
    if (*sdelta > 0.) {
	goto L500;
    }
    *sdelta = -(*sdelta);
    z1 = log(1. - *sdelta / 100.) / (*shabr * *shabr);
L500:
    z3 = *sdtdh0 / (*shbr * 2.);
    z4 = *shabr - *shbr;
    spt[4] = (z1 * (*shbr - *shabr * 2.) * *shbr + z3 * z4 * *shabr) * 2. / (*
	    shabr * *shbr * z4 * z4 * z4);
    spt[3] = z1 * (*shbr * 2. - *shabr * 3.) / (*shabr * z4 * z4) - (*shabr * 
	    2. + *shbr) * spt[4];
    spt[2] = z1 * -2. / *shabr - *shabr * 2. * spt[3] - *shabr * 3. * *shabr *
	     spt[4];
    spt[1] = z1 - *shabr * (spt[2] + *shabr * (spt[3] + *shabr * spt[4]));
    *aus6 = FALSE_;
    b = spt[3] * 4. / (spt[4] * 5.) + *shabr;
    c__ = spt[1] * -2. / (spt[4] * 5 * *shabr);
    z2 = b * b / 4. - c__;
    if (z2 < 0.) {
	goto L300;
    }
    z3 = sqrt(z2);
    z1 = b / 2.;
    z2 = -z1 + z3;
    if (z2 > 0. && z2 < *shbr) {
	*aus6 = TRUE_;
    }
    if (abs(z3) > 1e-15) {
	goto L400;
    }
    z2 = c__ / z2;
    if (z2 > 0. && z2 < *shbr) {
	*aus6 = TRUE_;
    }
    return 0;
L400:
    z2 = -z1 - z3;
    if (z2 > 0. && z2 < *shbr) {
	*aus6 = TRUE_;
    }
L300:
    return 0;
} /* tal_ */



/* Subroutine */ int valgul_(doublereal *xhi, doublereal *hvb, doublereal *
	vwu, doublereal *vwa, doublereal *vdp)
{
    /* Builtin functions */
    double cos(doublereal), log(doublereal);

    /* Local variables */
    static doublereal cs, abc, arl, zzz;

/* --------------------------------------------------------------------- */
/*   CALCULATES E-F VALLEY PARAMETERS; T.L. GULYAEVA, ADVANCES IN */
/*   SPACE RESEARCH 7, #6, 39-48, 1987. */

/*       INPUT:  XHI     SOLAR ZENITH ANGLE [DEGREE] */

/*       OUTPUT: VDP     VALLEY DEPTH  (NVB/NME) */
/*               VWU     VALLEY WIDTH  [KM] */
/*               VWA     VALLEY WIDTH  (SMALLER, CORRECTED BY RAWER) */
/*               HVB     HEIGHT OF VALLEY BASE [KM] */
/* ----------------------------------------------------------------------- */


    cs = cos(const_1.umr * *xhi) + .1;
    abc = abs(cs);
    *vdp = cs * .45 / (abc + .1) + .55;
    arl = (abc + .1 + cs) / (abc + .1 - cs);
    zzz = log(arl);
    *vwu = 45. - zzz * 10.;
    *vwa = 45. - zzz * 5.;
    *hvb = 1e3 / (cs * .224 + 7.024 + abc * .966);
    return 0;
} /* valgul_ */



/* ************************************************************ */
/* *************** EARTH MAGNETIC FIELD *********************** */
/* ************************************************************** */


/* Subroutine */ int ggm_(integer *art, doublereal *long__, doublereal *lati, 
	doublereal *mlong, doublereal *mlat)
{
    /* Builtin functions */
    double cos(doublereal), sin(doublereal), d_sign(doublereal *, doublereal *
	    ), asin(doublereal), acos(doublereal);

    /* Local variables */
    static doublereal ci, si, cbg, cbm, clg, clm, sbg, sbm, slg, slm, ylg, 
	    zpi;

/* CALCULATES GEOMAGNETIC LONGITUDE (MLONG) AND LATITUDE (MLAT) */
/* FROM GEOGRAFIC LONGITUDE (LONG) AND LATITUDE (LATI) FOR ART=0 */
/* AND REVERSE FOR ART=1. ALL ANGLES IN DEGREE. */
/* LATITUDE:-90 TO 90. LONGITUDE:0 TO 360 EAST. */
    zpi = const_2.faktor * 360.;
    cbg = const_2.faktor * 11.4;
    ci = cos(cbg);
    si = sin(cbg);
    if (*art == 0) {
	goto L10;
    }
    cbm = cos(*mlat * const_2.faktor);
    sbm = sin(*mlat * const_2.faktor);
    clm = cos(*mlong * const_2.faktor);
    slm = sin(*mlong * const_2.faktor);
    sbg = sbm * ci - cbm * clm * si;
    if (abs(sbg) > 1.) {
	sbg = d_sign(&c_b18, &sbg);
    }
    *lati = asin(sbg);
    cbg = cos(*lati);
    slg = cbm * slm / cbg;
    clg = (sbm * si + cbm * clm * ci) / cbg;
    if (abs(clg) > 1.) {
	clg = d_sign(&c_b18, &clg);
    }
    *long__ = acos(clg);
    if (slg < 0.) {
	*long__ = zpi - *long__;
    }
    *lati /= const_2.faktor;
    *long__ /= const_2.faktor;
    *long__ += -69.8;
    if (*long__ < 0.) {
	*long__ += 360.;
    }
    return 0;
L10:
    ylg = *long__ + 69.8;
    cbg = cos(*lati * const_2.faktor);
    sbg = sin(*lati * const_2.faktor);
    clg = cos(ylg * const_2.faktor);
    slg = sin(ylg * const_2.faktor);
    sbm = sbg * ci + cbg * clg * si;
    if (abs(sbm) > 1.) {
	sbm = d_sign(&c_b18, &sbm);
    }
    *mlat = asin(sbm);
    cbm = cos(*mlat);
    slm = cbg * slg / cbm;
    clm = (-sbg * si + cbg * clg * ci) / cbm;
    if (abs(clm) > 1.) {
	clm = d_sign(&c_b18, &clm);
    }
    *mlong = acos(clm);
    if (slm < 0.) {
	*mlong = zpi - *mlong;
    }
    *mlat /= const_2.faktor;
    *mlong /= const_2.faktor;
    return 0;
} /* ggm_ */



/* Subroutine */ int fieldg_(doublereal *dlat, doublereal *dlong, doublereal *
	alt, doublereal *x, doublereal *y, doublereal *z__, doublereal *f, 
	doublereal *dip, doublereal *dec, doublereal *smodip)
{
    /* Initialized data */

    static doublereal fel1[72] = { 0.,.1506723,.0101742,-.0286519,.0092606,
	    -.0130846,.0089594,-.0136808,-1.508e-4,-.0093977,.013065,.002052,
	    -.0121956,-.0023451,-.0208555,.0068416,-.0142659,-.0093322,
	    -.0021364,-.007891,.0045586,.0128904,-2.951e-4,-.0237245,.0289493,
	    .0074605,-.0105741,-5.116e-4,-.0105732,-.0058542,.0033268,
	    .0078164,.0211234,.0099309,.0362792,-.020107,-.004635,-.0058722,
	    .0011147,-.0013949,-.0108838,.0322263,-.014739,.0031247,.0111986,
	    -.0109394,.0058112,.2739046,-.0155682,-.0253272,.0163782,.020573,
	    .0022081,.0112749,-.0098427,.0072705,.0195189,-.0081132,-.0071889,
	    -.057997,-.0856642,.188426,-.7391512,.1210288,-.0241888,-.0052464,
	    -.0096312,-.0044834,.0201764,.0258343,.0083033,.0077187 };
    static doublereal fel2[72] = { .0586055,.0102236,-.0396107,-.016786,
	    -.2019911,-.5810815,.0379916,3.7508268,1.813303,-.056425,
	    -.0557352,.1335347,-.0142641,-.1024618,.0970994,-.075183,
	    -.1274948,.0402073,.038629,.1883088,.183896,-.7848989,.7591817,
	    -.9302389,-.856096,.663325,-4.6363869,-13.2599277,.1002136,
	    .0855714,-.0991981,-.0765378,-.0455264,.1169326,-.2604067,
	    .1800076,-.2223685,-.6347679,.5334222,-.3459502,-.1573697,
	    .8589464,1.781599,-6.3347645,-3.1513653,-9.992775,13.3327637,
	    -35.4897308,37.3466339,-.5257398,.0571474,-.5421217,.240477,
	    -.1747774,-.3433644,.4829708,.3935944,.4885033,.8488121,-.7640999,
	    -1.8884945,3.2930784,-7.3497229,.1672821,-.2306652,10.5782146,
	    12.6031065,8.6579742,215.5209961,-27.141922,22.3405762,
	    1108.6394043 };

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal), sqrt(doublereal), d_sign(
	    doublereal *, doublereal *), asin(doublereal);

    /* Local variables */
    static doublereal d__, g[144], h__[144];
    static integer i__, k, m;
    static doublereal s, f1, x1, y1, z1;
    static integer ih;
    static doublereal cp;
    static integer il;
    static doublereal ct, xi[3], sp, rq, st, xt, rho, xxx, yyy, brh0, zzz;
    static integer imax;
    static doublereal rlat;
    static integer nmax, last, ihmax;
    static doublereal rlong, zdivf, ydivs, dipdiv;

/* THIS IS A SPECIAL VERSION OF THE POGO 68/10 MAGNETIC FIELD */
/* LEGENDRE MODEL. TRANSFORMATION COEFF. G(144) VALID FOR 1973. */
/* INPUT: DLAT, DLONG=GEOGRAPHIC COORDINATES/DEG.(-90/90,0/360), */
/*        ALT=ALTITUDE/KM. */
/* OUTPUT: F TOTAL FIELD (GAUSS), Z DOWNWARD VERTICAL COMPONENT */
/*        X,Y COMPONENTS IN THE EQUATORIAL PLANE (X TO ZERO LONGITUDE). */
/*        DIP INCLINATION ANGLE(DEGREE). SMODIP RAWER'S MODFIED DIP. */
/* SHEIK,1977. */
    k = 0;
    for (i__ = 1; i__ <= 72; ++i__) {
	++k;
	g[k - 1] = fel1[i__ - 1];
/* L10: */
	g[k + 71] = fel2[i__ - 1];
    }
    rlat = *dlat * const_1.umr;
    ct = sin(rlat);
    st = cos(rlat);
    nmax = 11;
    d__ = sqrt(40680925. - ct * 272336. * ct);
    rlong = *dlong * const_1.umr;
    cp = cos(rlong);
    sp = sin(rlong);
    zzz = (*alt + 40408589. / d__) * ct / 6371.2;
    rho = (*alt + 40680925. / d__) * st / 6371.2;
    xxx = rho * cp;
    yyy = rho * sp;
    rq = 1. / (xxx * xxx + yyy * yyy + zzz * zzz);
    xi[0] = xxx * rq;
    xi[1] = yyy * rq;
    xi[2] = zzz * rq;
    ihmax = nmax * nmax + 1;
    last = ihmax + nmax + nmax;
    imax = nmax + nmax - 1;
    i__1 = last;
    for (i__ = ihmax; i__ <= i__1; ++i__) {
/* L100: */
	h__[i__ - 1] = g[i__ - 1];
    }
    for (k = 1; k <= 3; k += 2) {
	i__ = imax;
	ih = ihmax;
L300:
	il = ih - i__;
	f1 = 2. / (i__ - k + 2.);
	x1 = xi[0] * f1;
	y1 = xi[1] * f1;
	z1 = xi[2] * (f1 + f1);
	i__ += -2;
	if (i__ - 1 < 0) {
	    goto L400;
	}
	if (i__ - 1 == 0) {
	    goto L500;
	}
	i__1 = i__;
	for (m = 3; m <= i__1; m += 2) {
	    h__[il + m] = g[il + m] + z1 * h__[ih + m] + x1 * (h__[ih + m + 2]
		     - h__[ih + m - 2]) - y1 * (h__[ih + m + 1] + h__[ih + m 
		    - 3]);
	    h__[il + m - 1] = g[il + m - 1] + z1 * h__[ih + m - 1] + x1 * (
		    h__[ih + m + 1] - h__[ih + m - 3]) + y1 * (h__[ih + m + 2]
		     + h__[ih + m - 2]);
/* L600: */
	}
L500:
	h__[il + 1] = g[il + 1] + z1 * h__[ih + 1] + x1 * h__[ih + 3] - y1 * (
		h__[ih + 2] + h__[ih - 1]);
	h__[il] = g[il] + z1 * h__[ih] + y1 * h__[ih + 3] + x1 * (h__[ih + 2] 
		- h__[ih - 1]);
L400:
	h__[il - 1] = g[il - 1] + z1 * h__[ih - 1] + (x1 * h__[ih] + y1 * h__[
		ih + 1]) * 2.;
/* L700: */
	ih = il;
	if (i__ >= k) {
	    goto L300;
	}
/* L200: */
    }
    s = h__[0] * .5 + (h__[1] * xi[2] + h__[2] * xi[0] + h__[3] * xi[1]) * 2.;
    xt = (rq + rq) * sqrt(rq);
    *x = xt * (h__[2] - s * xxx);
    *y = xt * (h__[3] - s * yyy);
    *z__ = xt * (h__[1] - s * zzz);
    *f = sqrt(*x * *x + *y * *y + *z__ * *z__);
    brh0 = *y * sp + *x * cp;
    *y = *y * cp - *x * sp;
    *x = *z__ * st - brh0 * ct;
    *z__ = -(*z__) * ct - brh0 * st;
    zdivf = *z__ / *f;
    if (abs(zdivf) > 1.) {
	zdivf = d_sign(&c_b18, &zdivf);
    }
    *dip = asin(zdivf);
    ydivs = *y / sqrt(*x * *x + *y * *y);
    if (abs(ydivs) > 1.) {
	ydivs = d_sign(&c_b18, &ydivs);
    }
    *dec = asin(ydivs);
    dipdiv = *dip / sqrt(*dip * *dip + st);
    if (abs(dipdiv) > 1.) {
	dipdiv = d_sign(&c_b18, &dipdiv);
    }
    *smodip = asin(dipdiv);
    *dip /= const_1.umr;
    *dec /= const_1.umr;
    *smodip /= const_1.umr;
    return 0;
} /* fieldg_ */



/* ************************************************************ */
/* *********** INTERPOLATION AND REST *************************** */
/* ************************************************************** */


/* Subroutine */ int regfa1_(doublereal *x11, doublereal *x22, doublereal *
	fx11, doublereal *fx22, doublereal *eps, doublereal *fw, D_fp f, 
	logical *schalt, doublereal *x)
{
    /* System generated locals */
    doublereal d__1;

    /* Local variables */
    static logical k;
    static doublereal f1, f2;
    static logical l1;
    static doublereal x1, x2, ep;
    static integer ng;
    static doublereal dx, fx;
    static integer lfd;
    static logical links;

/* REGULA-FALSI-PROCEDURE TO FIND X WITH F(X)-FW=0. X1,X2 ARE THE */
/* STARTING VALUES. THE COMUTATION ENDS WHEN THE X-INTERVAL */
/* HAS BECOME LESS THAN EPS . IF SIGN(F(X1)-FW)= SIGN(F(X2)-FW) */
/* THEN SCHALT=.TRUE. */
    *schalt = FALSE_;
    ep = *eps;
    x1 = *x11;
    x2 = *x22;
    f1 = *fx11 - *fw;
    f2 = *fx22 - *fw;
    k = FALSE_;
    ng = 2;
    lfd = 0;
    if (f1 * f2 <= 0.) {
	goto L200;
    }
    *x = 0.;
    *schalt = TRUE_;
    return 0;
L200:
    *x = (x1 * f2 - x2 * f1) / (f2 - f1);
    goto L400;
L300:
    l1 = links;
    dx = (x2 - x1) / ng;
    if (! links) {
	dx *= ng - 1;
    }
    *x = x1 + dx;
L400:
    fx = (*f)(x) - *fw;
    ++lfd;
    if (lfd > 20) {
	ep *= 10.;
	lfd = 0;
    }
    links = f1 * fx > 0.;
    k = ! k;
    if (links) {
	x1 = *x;
	f1 = fx;
    } else {
	x2 = *x;
	f2 = fx;
    }
    if ((d__1 = x2 - x1, abs(d__1)) <= ep) {
	goto L800;
    }
    if (k) {
	goto L300;
    }
    if (links && ! l1 || ! links && l1) {
	ng <<= 1;
    }
    goto L200;
L800:
    return 0;
} /* regfa1_ */



/* ****************************************************************** */
/* ********** ZENITH ANGLE, DAY OF YEAR, TIME *********************** */
/* ****************************************************************** */


/* Subroutine */ int soco_(integer *ld, doublereal *t, doublereal *flat, 
	doublereal *elon, doublereal *height, doublereal *declin, doublereal *
	zenith, doublereal *sunrse, doublereal *sunset)
{
    /* Initialized data */

    static doublereal p1 = .017203534;
    static doublereal p2 = .034407068;
    static doublereal p3 = .051610602;
    static doublereal p4 = .068814136;
    static doublereal p6 = .103221204;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal), d_sign(doublereal *, doublereal *
	    ), acos(doublereal), sqrt(doublereal);

    /* Local variables */
    static doublereal a, b, h__, dc, fa, ch, td, te, tf, et, dcl, phi, eqt, 
	    chih, cosx, wlon, secphi, cosphi;

/* -------------------------------------------------------------------- */
/*       s/r to calculate the solar declination, zenith angle, and */
/*       sunrise & sunset times  - based on Newbern Smith's algorithm */
/*       [leo mcnamara, 1-sep-86, last modified 16-jun-87] */
/*       {dieter bilitza, 30-oct-89, modified for IRI application} */

/* in:   ld      local day of year */
/*       t       local hour (decimal) */
/*       flat    northern latitude in degrees */
/*       elon    east longitude in degrees */
/* 		height	height in km */

/* out:  declin      declination of the sun in degrees */
/*       zenith      zenith angle of the sun in degrees */
/*       sunrse      local time of sunrise in hours */
/*       sunset      local time of sunset in hours */
/* ------------------------------------------------------------------- */

/* amplitudes of Fourier coefficients  --  1955 epoch................. */

/* s/r is formulated in terms of WEST longitude....................... */
    wlon = 360. - *elon;

/* time of equinox for 1980........................................... */
    td = *ld + (*t + wlon / 15.) / 24.;
    te = td + .9369;

/* declination of the sun.............................................. */
    dcl = sin(p1 * (te - 82.242)) * 23.256 + sin(p2 * (te - 44.855)) * .381 + 
	    sin(p3 * (te - 23.355)) * .167 - sin(p4 * (te + 11.97)) * .013 + 
	    sin(p6 * (te - 10.41)) * .011 + .339137;
    *declin = dcl;
    dc = dcl * const_3.dtr;

/* the equation of time................................................ */
    tf = te - .5;
    eqt = sin(p1 * (tf - 4.)) * -7.38 - sin(p2 * (tf + 9.)) * 9.87 + sin(p3 * 
	    (tf - 53.)) * .27 - cos(p4 * (tf - 17.)) * .2;
    et = eqt * const_3.dtr / 4.;

    fa = *flat * const_3.dtr;
    phi = const1_1.humr * (*t - 12.) + et;

    a = sin(fa) * sin(dc);
    b = cos(fa) * cos(dc);
    cosx = a + b * cos(phi);
    if (abs(cosx) > 1.) {
	cosx = d_sign(&c_b18, &cosx);
    }
    *zenith = acos(cosx) / const_3.dtr;

/* calculate sunrise and sunset times --  at the ground........... */
/* see Explanatory Supplement to the Ephemeris (1961) pg 401...... */
/* sunrise at height h metres is at............................... */
    h__ = *height * 1e3;
    chih = sqrt(h__) * .0347 + 90.83;
/* this includes corrections for horizontal refraction and........ */
/* semi-diameter of the solar disk................................ */
    ch = cos(chih * const_3.dtr);
    cosphi = (ch - a) / b;
/* if abs(secphi) > 1., sun does not rise/set..................... */
/* allow for sun never setting - high latitude summer............. */
    secphi = 999999.;
    if (cosphi != 0.) {
	secphi = 1. / cosphi;
    }
    *sunset = 99.;
    *sunrse = 99.;
    if (secphi > -1. && secphi <= 0.) {
	return 0;
    }
/* allow for sun never rising - high latitude winter.............. */
    *sunset = -99.;
    *sunrse = -99.;
    if (secphi > 0. && secphi < 1.) {
	return 0;
    }

    if (cosphi > 1.) {
	cosphi = d_sign(&c_b18, &cosphi);
    }
    phi = acos(cosphi);
    et /= const1_1.humr;
    phi /= const1_1.humr;
    *sunrse = 12. - phi - et;
    *sunset = phi + 12. - et;
    if (*sunrse < 0.) {
	*sunrse += 24.;
    }
    if (*sunset >= 24.) {
	*sunset += -24.;
    }

    return 0;
} /* soco_ */



doublereal hpol_(doublereal *hour, doublereal *tw, doublereal *xnw, 
	doublereal *sa, doublereal *su, doublereal *dsa, doublereal *dsu)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal epst_(doublereal *, doublereal *, doublereal *);

/* ------------------------------------------------------- */
/* PROCEDURE FOR SMOOTH TIME-INTERPOLATION USING EPSTEIN */
/* STEP FUNCTION AT SUNRISE (SA) AND SUNSET (SU). THE */
/* STEP-WIDTH FOR SUNRISE IS DSA AND FOR SUNSET DSU. */
/* TW,NW ARE THE DAY AND NIGHT VALUE OF THE PARAMETER TO */
/* BE INTERPOLATED. SA AND SU ARE TIME OF SUNRIES AND */
/* SUNSET IN DECIMAL HOURS. */
/* BILITZA----------------------------------------- 1979. */
    if (abs(*su) > 25.) {
	if (*su > 0.) {
	    ret_val = *tw;
	} else {
	    ret_val = *xnw;
	}
	return ret_val;
    }
    ret_val = *xnw + (*tw - *xnw) * epst_(hour, dsa, sa) + (*xnw - *tw) * 
	    epst_(hour, dsu, su);
    return ret_val;
} /* hpol_ */



/* Subroutine */ int moda_(integer *in, integer *iyear, integer *month, 
	integer *iday, integer *idoy, integer *nrdaymo)
{
    /* Initialized data */

    static integer mm[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, imo, mobe, moold, mosum;

/* ------------------------------------------------------------------- */
/* CALCULATES DAY OF YEAR (IDOY, ddd) FROM YEAR (IYEAR, yy or yyyy), */
/* MONTH (MONTH, mm) AND DAY OF MONTH (IDAY, dd) IF IN=0, OR MONTH */
/* AND DAY FROM YEAR AND DAY OF YEAR IF IN=1. NRDAYMO is an output */
/* parameter providing the number of days in the specific month. */
/* ------------------------------------------------------------------- */
    imo = 0;
    mobe = 0;

/*  leap year rule: years evenly divisible by 4 are leap years, except */
/*  years also evenly divisible by 100 are not leap years, except years */
/*  also evenly divisible by 400 are leap years. The year 2000 therefore */
/*  is a leap year. The 100 and 400 year exception rule */
/*     if((iyear/4*4.eq.iyear).and.(iyear/100*100.ne.iyear)) mm(2)=29 */
/*  will become important again in the year 2100 which is not a leap */
/*  year. */

    mm[1] = 28;
    if (*iyear / 4 << 2 == *iyear) {
	mm[1] = 29;
    }
    if (*in > 0) {
	goto L5;
    }
    mosum = 0;
    if (*month > 1) {
	i__1 = *month - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L1234: */
	    mosum += mm[i__ - 1];
	}
    }
    *idoy = mosum + *iday;
    *nrdaymo = mm[*month - 1];
    return 0;
L5:
    ++imo;
    if (imo > 12) {
	goto L55;
    }
    moold = mobe;
    *nrdaymo = mm[imo - 1];
    mobe += *nrdaymo;
    if (mobe < *idoy) {
	goto L5;
    }
L55:
    *month = imo;
    *iday = *idoy - moold;
    return 0;
} /* moda_ */



/* Subroutine */ int ut_lt__(integer *mode, doublereal *ut, doublereal *slt, 
	doublereal *glong, integer *iyyy, integer *ddd)
{
    static doublereal xlong;
    static integer dddend;

/* ----------------------------------------------------------------- */
/* Converts Universal Time UT (decimal hours) into Solar Local Time */
/* SLT (decimal hours) for given date (iyyy is year, e.g. 1995; ddd */
/* is day of year, e.g. 1 for Jan 1) and geodatic longitude in degrees. */
/* For mode=0 UT->LT and for mode=1 LT->UT */
/* Please NOTE that iyyy and ddd are input as well as output parameters */
/* since the determined LT may be for a day before or after the UT day. */
/* ------------------------------------------------- bilitza nov 95 */
    xlong = *glong;
    if (*glong > 180.) {
	xlong = *glong - 360;
    }
    if (*mode != 0) {
	goto L1;
    }

/* UT ---> LT */

    *slt = *ut + xlong / 15.;
    if (*slt >= 0. && *slt <= 24.) {
	goto L2;
    }
    if (*slt > 24.) {
	goto L3;
    }
    *slt += 24.;
    --(*ddd);
    if ((doublereal) (*ddd) < 1.) {
	--(*iyyy);
	*ddd = 365;

/* leap year if evenly divisible by 4 and not by 100, except if evenly */
/* divisible by 400. Thus 2000 will be a leap year. */

	if (*iyyy / 4 << 2 == *iyyy) {
	    *ddd = 366;
	}
    }
    goto L2;
L3:
    *slt += -24.;
    ++(*ddd);
    dddend = 365;
    if (*iyyy / 4 << 2 == *iyyy) {
	dddend = 366;
    }
    if (*ddd > dddend) {
	++(*iyyy);
	*ddd = 1;
    }
    goto L2;

/* LT ---> UT */

L1:
    *ut = *slt - xlong / 15.;
    if (*ut >= 0. && *ut <= 24.) {
	goto L2;
    }
    if (*ut > 24.) {
	goto L5;
    }
    *ut += 24.;
    --(*ddd);
    if ((doublereal) (*ddd) < 1.) {
	--(*iyyy);
	*ddd = 365;
	if (*iyyy / 4 << 2 == *iyyy) {
	    *ddd = 366;
	}
    }
    goto L2;
L5:
    *ut += -24.;
    ++(*ddd);
    dddend = 365;
    if (*iyyy / 4 << 2 == *iyyy) {
	dddend = 366;
    }
    if (*ddd > dddend) {
	++(*iyyy);
	*ddd = 1;
    }
L2:
    return 0;
} /* ut_lt__ */



/* ********************************************************************* */
/* ************************ EPSTEIN FUNCTIONS ************************** */
/* ********************************************************************* */
/* REF:  H. G. BOOKER, J. ATMOS. TERR. PHYS. 39, 619-623, 1977 */
/*       K. RAWER, ADV. SPACE RES. 4, #1, 11-15, 1984 */
/* ********************************************************************* */


doublereal rlay_(doublereal *x, doublereal *xm, doublereal *sc, doublereal *
	hx)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal y1, y1m, y2m;
    extern doublereal eptr_(doublereal *, doublereal *, doublereal *), epst_(
	    doublereal *, doublereal *, doublereal *);

/* -------------------------------------------------------- RAWER  LAYER */
    y1 = eptr_(x, sc, hx);
    y1m = eptr_(xm, sc, hx);
    y2m = epst_(xm, sc, hx);
    ret_val = y1 - y1m - (*x - *xm) * y2m / *sc;
    return ret_val;
} /* rlay_ */



doublereal d1lay_(doublereal *x, doublereal *xm, doublereal *sc, doublereal *
	hx)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal epst_(doublereal *, doublereal *, doublereal *);

/* ------------------------------------------------------------ dLAY/dX */
    ret_val = (epst_(x, sc, hx) - epst_(xm, sc, hx)) / *sc;
    return ret_val;
} /* d1lay_ */



doublereal d2lay_(doublereal *x, doublereal *xm, doublereal *sc, doublereal *
	hx)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal epla_(doublereal *, doublereal *, doublereal *);

/* ---------------------------------------------------------- d2LAY/dX2 */
    ret_val = epla_(x, sc, hx) / (*sc * *sc);
    return ret_val;
} /* d2lay_ */



doublereal eptr_(doublereal *x, doublereal *sc, doublereal *hx)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal), log(doublereal);

    /* Local variables */
    static doublereal d1;

/* --------------------------------------------------------- TRANSITION */
    d1 = (*x - *hx) / *sc;
    if (abs(d1) < argexp_1.argmax) {
	goto L1;
    }
    if (d1 > 0.) {
	ret_val = d1;
    } else {
	ret_val = 0.;
    }
    return ret_val;
L1:
    ret_val = log(exp(d1) + 1.);
    return ret_val;
} /* eptr_ */



doublereal epst_(doublereal *x, doublereal *sc, doublereal *hx)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal d1;

/* -------------------------------------------------------------- STEP */
    d1 = (*x - *hx) / *sc;
    if (abs(d1) < argexp_1.argmax) {
	goto L1;
    }
    if (d1 > 0.) {
	ret_val = 1.;
    } else {
	ret_val = 0.;
    }
    return ret_val;
L1:
    ret_val = 1. / (exp(-d1) + 1.);
    return ret_val;
} /* epst_ */



doublereal epstep_(doublereal *y2, doublereal *y1, doublereal *sc, doublereal 
	*hx, doublereal *x)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal epst_(doublereal *, doublereal *, doublereal *);

/* ---------------------------------------------- STEP FROM Y1 TO Y2 */
    ret_val = *y1 + (*y2 - *y1) * epst_(x, sc, hx);
    return ret_val;
} /* epstep_ */



doublereal epla_(doublereal *x, doublereal *sc, doublereal *hx)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal d0, d1, d2;

/* ------------------------------------------------------------ PEAK */
    d1 = (*x - *hx) / *sc;
    if (abs(d1) < argexp_1.argmax) {
	goto L1;
    }
    ret_val = 0.;
    return ret_val;
L1:
    d0 = exp(d1);
    d2 = d0 + 1.;
    ret_val = d0 / (d2 * d2);
    return ret_val;
} /* epla_ */



doublereal xe2to5_(doublereal *h__, doublereal *hmf2, integer *nl, doublereal 
	*hx, doublereal *sc, doublereal *amp)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__;
    static doublereal sum;
    extern doublereal rlay_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal ylay, zlay;

/* ---------------------------------------------------------------------- */
/* NORMALIZED ELECTRON DENSITY (N/NMF2) FOR THE MIDDLE IONOSPHERE FROM */
/* HME TO HMF2 USING LAY-FUNCTIONS. */
/* ---------------------------------------------------------------------- */
    /* Parameter adjustments */
    --amp;
    --sc;
    --hx;

    /* Function Body */
    sum = 1.;
    i__1 = *nl;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ylay = amp[i__] * rlay_(h__, hmf2, &sc[i__], &hx[i__]);
	zlay = pow_dd(&c_b30, &ylay);
/* L1: */
	sum *= zlay;
    }
    ret_val = sum;
    return ret_val;
} /* xe2to5_ */



doublereal xen_(doublereal *h__, doublereal *hmf2, doublereal *xnmf2, 
	doublereal *hme, integer *nl, doublereal *hx, doublereal *sc, 
	doublereal *amp)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal xe1_(doublereal *), xe6_(doublereal *), xe2to5_(
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *);

/* ---------------------------------------------------------------------- */
/* ELECTRON DENSITY WITH NEW MIDDLE IONOSPHERE */
/* ---------------------------------------------------------------------- */

    /* Parameter adjustments */
    --amp;
    --sc;
    --hx;

    /* Function Body */
    if (*h__ < *hmf2) {
	goto L100;
    }
    ret_val = xe1_(h__);
    return ret_val;
L100:
    if (*h__ < *hme) {
	goto L200;
    }
    ret_val = *xnmf2 * xe2to5_(h__, hmf2, nl, &hx[1], &sc[1], &amp[1]);
    return ret_val;
L200:
    ret_val = xe6_(h__);
    return ret_val;
} /* xen_ */



/* Subroutine */ int rogul_(integer *iday, doublereal *xhi, doublereal *sx, 
	doublereal *gro)
{
    /* Builtin functions */
    double cos(doublereal), exp(doublereal);

    /* Local variables */
    static doublereal xs;

/* --------------------------------------------------------------------- */
/*   CALCULATES RATIO H0.5/HMF2 FOR HALF-DENSITY POINT (NE(H0.5)=0.5* */
/*   NMF2) T. GULYAEVA, ADVANCES IN SPACE RESEARCH 7, #6, 39-48, 1987. */

/*       INPUT:  IDAY    DAY OF YEAR */
/*               XHI     SOLAR ZENITH ANGLE [DEGREE] */

/*       OUTPUT: GRO     RATIO OF HALF DENSITY HEIGHT TO F PEAK HEIGHT */
/*               SX      SMOOTHLY VARYING SEASON PARAMTER (SX=1 FOR */
/*                       DAY=1; SX=3 FOR DAY=180; SX=2 FOR EQUINOX) */
/* --------------------------------------------------------------------- */

    *sx = 2. - cos(*iday * const1_1.dumr);
    xs = (*xhi - *sx * 20.) / 15.;
    *gro = .8 - .2 / (exp(xs) + 1.);
/* same as gro=0.6+0.2/(1+exp(-xs)) */
    return 0;
} /* rogul_ */



/* Subroutine */ int lnglsn_(integer *n, doublereal *a, doublereal *b, 
	logical *aus)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;

    /* Local variables */
    static integer k, l, m, nn, izg;
    static doublereal hsp, azv[10], amax;
    static integer imax;

/* -------------------------------------------------------------------- */
/* SOLVES QUADRATIC SYSTEM OF LINEAR EQUATIONS: */

/*       INPUT:  N       NUMBER OF EQUATIONS (= NUMBER OF UNKNOWNS) */
/*               A(N,N)  MATRIX (LEFT SIDE OF SYSTEM OF EQUATIONS) */
/*               B(N)    VECTOR (RIGHT SIDE OF SYSTEM) */

/*       OUTPUT: AUS     =.TRUE.   NO SOLUTION FOUND */
/*                       =.FALSE.  SOLUTION IS IN  A(N,J) FOR J=1,N */
/* -------------------------------------------------------------------- */


    /* Parameter adjustments */
    --b;
    a -= 6;

    /* Function Body */
    nn = *n - 1;
    *aus = FALSE_;
    i__1 = *n - 1;
    for (k = 1; k <= i__1; ++k) {
	imax = k;
	l = k;
	izg = 0;
	amax = (d__1 = a[k + k * 5], abs(d__1));
L110:
	++l;
	if (l > *n) {
	    goto L111;
	}
	hsp = (d__1 = a[l + k * 5], abs(d__1));
	if (hsp < 1e-8) {
	    ++izg;
	}
	if (hsp <= amax) {
	    goto L110;
	}
L111:
	if (abs(amax) >= 1e-10) {
	    goto L133;
	}
	*aus = TRUE_;
	return 0;
L133:
	if (imax == k) {
	    goto L112;
	}
	i__2 = *n;
	for (l = k; l <= i__2; ++l) {
	    azv[l] = a[imax + l * 5];
	    a[imax + l * 5] = a[k + l * 5];
/* L2: */
	    a[k + l * 5] = azv[l];
	}
	azv[0] = b[imax];
	b[imax] = b[k];
	b[k] = azv[0];
L112:
	if (izg == *n - k) {
	    goto L1;
	}
	amax = 1. / a[k + k * 5];
	azv[0] = b[k] * amax;
	i__2 = *n;
	for (m = k + 1; m <= i__2; ++m) {
/* L3: */
	    azv[m] = a[k + m * 5] * amax;
	}
	i__2 = *n;
	for (l = k + 1; l <= i__2; ++l) {
	    amax = a[l + k * 5];
	    if (abs(amax) < 1e-8) {
		goto L4;
	    }
	    a[l + k * 5] = 0.;
	    b[l] -= azv[0] * amax;
	    i__3 = *n;
	    for (m = k + 1; m <= i__3; ++m) {
/* L5: */
		a[l + m * 5] -= amax * azv[m];
	    }
L4:
	    ;
	}
L1:
	;
    }
    for (k = *n; k >= 1; --k) {
	amax = 0.;
	if (k < *n) {
	    i__1 = *n;
	    for (l = k + 1; l <= i__1; ++l) {
/* L7: */
		amax += a[k + l * 5] * a[*n + l * 5];
	    }
	}
	if ((d__1 = a[k + k * 5], abs(d__1)) < 1e-6) {
	    a[*n + k * 5] = 0.;
	} else {
	    a[*n + k * 5] = (b[k] - amax) / a[k + k * 5];
	}
/* L6: */
    }
    return 0;
} /* lnglsn_ */



/* Subroutine */ int lsknm_(integer *n, integer *m, integer *m0, integer *m1, 
	doublereal *hm, doublereal *sc, doublereal *hx, doublereal *w, 
	doublereal *x, doublereal *y, doublereal *var, logical *sing)
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, m01;
    static doublereal ali[25]	/* was [5][5] */, bli[5], scm, xli[50]	/* 
	    was [5][10] */;
    extern doublereal rlay_(doublereal *, doublereal *, doublereal *, 
	    doublereal *), d1lay_(doublereal *, doublereal *, doublereal *, 
	    doublereal *), d2lay_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    extern /* Subroutine */ int lnglsn_(integer *, doublereal *, doublereal *,
	     logical *);

/* -------------------------------------------------------------------- */
/*   DETERMINES LAY-FUNCTIONS AMPLITUDES FOR A NUMBER OF CONSTRAINTS: */

/*       INPUT:  N       NUMBER OF AMPLITUDES ( LAY-FUNCTIONS) */
/*               M       NUMBER OF CONSTRAINTS */
/*               M0      NUMBER OF POINT CONSTRAINTS */
/*               M1      NUMBER OF FIRST DERIVATIVE CONSTRAINTS */
/*               HM      F PEAK ALTITUDE  [KM] */
/*               SC(N)   SCALE PARAMETERS FOR LAY-FUNCTIONS  [KM] */
/*               HX(N)   HEIGHT PARAMETERS FOR LAY-FUNCTIONS  [KM] */
/*               W(M)    WEIGHT OF CONSTRAINTS */
/*               X(M)    ALTITUDES FOR CONSTRAINTS  [KM] */
/*               Y(M)    LOG(DENSITY/NMF2) FOR CONSTRAINTS */

/*       OUTPUT: VAR(M)  AMPLITUDES */
/*               SING    =.TRUE.   NO SOLUTION */
/* --------------------------------------------------------------------- */


    /* Parameter adjustments */
    --var;
    --hx;
    --sc;
    --y;
    --x;
    --w;

    /* Function Body */
    m01 = *m0 + *m1;
    scm = 0.;
    for (j = 1; j <= 5; ++j) {
	bli[j - 1] = 0.;
	for (i__ = 1; i__ <= 5; ++i__) {
/* L1: */
	    ali[j + i__ * 5 - 6] = 0.;
	}
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *m0;
	for (k = 1; k <= i__2; ++k) {
/* L3: */
	    xli[i__ + k * 5 - 6] = rlay_(&x[k], hm, &sc[i__], &hx[i__]);
	}
	i__2 = m01;
	for (k = *m0 + 1; k <= i__2; ++k) {
/* L4: */
	    xli[i__ + k * 5 - 6] = d1lay_(&x[k], hm, &sc[i__], &hx[i__]);
	}
	i__2 = *m;
	for (k = m01 + 1; k <= i__2; ++k) {
/* L5: */
	    xli[i__ + k * 5 - 6] = d2lay_(&x[k], hm, &sc[i__], &hx[i__]);
	}
/* L2: */
    }
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (k = 1; k <= i__2; ++k) {
	    bli[j - 1] += w[k] * y[k] * xli[j + k * 5 - 6];
	    i__3 = *n;
	    for (i__ = 1; i__ <= i__3; ++i__) {
/* L6: */
		ali[j + i__ * 5 - 6] += w[k] * xli[i__ + k * 5 - 6] * xli[j + 
			k * 5 - 6];
	    }
	}
/* L7: */
    }
    lnglsn_(n, ali, bli, sing);
    if (! (*sing)) {
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L8: */
	    var[i__] = ali[*n + i__ * 5 - 6];
	}
    }
    return 0;
} /* lsknm_ */



/* Subroutine */ int inilay_(logical *night, logical *f1reg, doublereal *
	xnmf2, doublereal *xnmf1, doublereal *xnme, doublereal *vne, 
	doublereal *hmf2, doublereal *hmf1, doublereal *hme, doublereal *hv1, 
	doublereal *hv2, doublereal *hhalf, doublereal *hxl, doublereal *scl, 
	doublereal *amp, integer *iqual)
{
    /* Builtin functions */
    double d_lg10(doublereal *);

    /* Local variables */
    static doublereal ww[8], xx[8], yy[8];
    static integer nc0, nc1;
    static doublereal zet, scl0, hfff, xfff;
    extern doublereal epst_(doublereal *, doublereal *, doublereal *);
    static logical ssin;
    static doublereal alg102, hxl1t, alogf, xhalf;
    extern /* Subroutine */ int lsknm_(integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, logical *);
    static doublereal alogef;
    static integer numcon, numlay;

/* ------------------------------------------------------------------- */
/* CALCULATES AMPLITUDES FOR LAY FUNCTIONS */
/* D. BILITZA, DECEMBER 1988 */

/* INPUT:        NIGHT   LOGICAL VARIABLE FOR DAY/NIGHT DISTINCTION */
/*               F1REG   LOGICAL VARIABLE FOR F1 OCCURRENCE */
/*               XNMF2   F2 PEAK ELECTRON DENSITY [M-3] */
/*               XNMF1   F1 PEAK ELECTRON DENSITY [M-3] */
/*               XNME    E  PEAK ELECTRON DENSITY [M-3] */
/*               VNE     ELECTRON DENSITY AT VALLEY BASE [M-3] */
/*               HMF2    F2 PEAK ALTITUDE [KM] */
/*               HMF1    F1 PEAK ALTITUDE [KM] */
/*               HME     E  PEAK ALTITUDE [KM] */
/*               HV1     ALTITUDE OF VALLEY TOP [KM] */
/*               HV2     ALTITUDE OF VALLEY BASE [KM] */
/*               HHALF   ALTITUDE OF HALF-F2-PEAK-DENSITY [KM] */

/* OUTPUT:       HXL(4)  HEIGHT PARAMETERS FOR LAY FUNCTIONS [KM] */
/*               SCL(4)  SCALE PARAMETERS FOR LAY FUNCTIONS [KM] */
/*               AMP(4)  AMPLITUDES FOR LAY FUNCTIONS */
/*               IQUAL   =0 ok, =1 ok using second choice for HXL(1) */
/*                       =2 NO SOLUTION */
/* --------------------------------------------------------------- */

/* constants -------------------------------------------------------- */
    /* Parameter adjustments */
    --amp;
    --scl;
    --hxl;

    /* Function Body */
    numlay = 4;
    nc1 = 2;
    alg102 = d_lg10(&c_b306);

/* constraints: xx == height     yy == log(Ne/NmF2)    ww == weights */
/* ----------------------------------------------------------------- */
    alogf = d_lg10(xnmf2);
    alogef = d_lg10(xnme) - alogf;
    xhalf = *xnmf2 / 2.;
    xx[0] = *hhalf;
    xx[1] = *hv1;
    xx[2] = *hv2;
    xx[3] = *hme;
    xx[4] = *hme - (*hv2 - *hme);
    yy[0] = -alg102;
    yy[1] = alogef;
    yy[2] = d_lg10(vne) - alogf;
    yy[3] = alogef;
    yy[4] = yy[2];
    yy[6] = 0.;
    ww[1] = 1.;
    ww[2] = 2.;
    ww[3] = 5.;

/* geometric paramters for LAY ------------------------------------- */
/* difference to earlier version:  HXL(3) = HV2 + SCL(3) */

    scl0 = ((*hmf2 - *hhalf) * .216 + 56.8) * .7;
    scl[1] = scl0 * .8;
    scl[2] = 10.;
    scl[3] = 9.;
    scl[4] = 6.;
    hxl[3] = *hv2;

/* DAY CONDITION-------------------------------------------------- */
/* earlier tested:       HXL(2) = HMF1 + SCL(2) */

    if (*night) {
	goto L7711;
    }
    numcon = 8;
    hxl[1] = *hmf2 * .9;
    hxl1t = *hhalf;
    hxl[2] = *hmf1;
    hxl[4] = *hme - scl[4];
    xx[5] = *hmf1;
    xx[6] = *hv2;
    xx[7] = *hme;
    yy[7] = 0.;
    ww[4] = 1.;
    ww[6] = 50.;
    ww[7] = 500.;
/* without F-region ---------------------------------------------- */
    if (*f1reg) {
	goto L100;
    }
    hxl[2] = (*hmf2 + *hhalf) / 2.;
    yy[5] = 0.;
    ww[5] = 0.;
    ww[0] = 1.;
    goto L7722;
/* with F-region -------------------------------------------- */
L100:
    yy[5] = d_lg10(xnmf1) - alogf;
    ww[5] = 3.;
    if ((*xnmf1 - xhalf) * (*hmf1 - *hhalf) < 0.) {
	ww[0] = .5;
    } else {
	zet = yy[0] - yy[5];
	ww[0] = epst_(&zet, &c_b310, &c_b311);
    }
    if (*hhalf > *hmf1) {
	hfff = *hmf1;
	xfff = *xnmf1;
    } else {
	hfff = *hhalf;
	xfff = xhalf;
    }
    goto L7722;

/* NIGHT CONDITION--------------------------------------------------- */
/* different HXL,SCL values were tested including: */
/*       SCL(1) = HMF2 * 0.15 - 27.1     HXL(2) = 200. */
/*       HXL(2) = HMF1 + SCL(2)          HXL(3) = 140. */
/*       SCL(3) = 5.                     HXL(4) = HME + SCL(4) */
/*       HXL(4) = 105. */

L7711:
    numcon = 7;
    hxl[1] = *hhalf;
    hxl1t = *hmf2 * .4 + 30.;
    hxl[2] = (*hmf2 + *hv1) / 2.;
    hxl[4] = *hme;
    xx[5] = *hv2;
    xx[6] = *hme;
    yy[5] = 0.;
    ww[0] = 1.;
    ww[2] = 3.;
    ww[4] = .5;
    ww[5] = 50.;
    ww[6] = 500.;
    hfff = *hhalf;
    xfff = xhalf;

/* are valley-top and bottomside point compatible ? ------------- */

L7722:
    if ((*hv1 - hfff) * (*xnme - xfff) < 0.) {
	ww[1] = .5;
    }
    if (*hv1 <= *hv2 + 5.) {
	ww[1] = .5;
    }

/* DETERMINE AMPLITUDES----------------------------------------- */

    nc0 = numcon - nc1;
    *iqual = 0;
L2299:
    lsknm_(&numlay, &numcon, &nc0, &nc1, hmf2, &scl[1], &hxl[1], ww, xx, yy, &
	    amp[1], &ssin);
    if (*iqual > 0) {
	goto L1937;
    }
    if (abs(amp[1]) > 10. || ssin) {
	*iqual = 1;
	hxl[1] = hxl1t;
	goto L2299;
    }
L1937:
    if (ssin) {
	*iqual = 2;
    }
    return 0;
} /* inilay_ */



/* Subroutine */ int tcon_(integer *yr, integer *mm, integer *day, integer *
	idn, doublereal *rz, doublereal *ig, doublereal *rsn, integer *nmonth)
{
    /* Format strings */
    static char fmt_8000[] = "(1x,i10,\002** OUT OF RANGE **\002/,5x,\002The\
 file IG_RZ.DAT which contains the indices Rz12\002,\002 and IG12\002/5x,\
\002currently only covers the time period\002,\002 (yymm) : \002,i6,\002-\
\002,i6)";

    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsle(cilist *), do_lio(integer *, integer *, 
	    char *, ftnlen), e_rsle();
    double sqrt(doublereal);
    integer f_clos(cllist *), s_wsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_wsfe();

    /* Local variables */
    static doublereal ionoindx[722];
    static integer i__, inum_vals__, jj;
    static doublereal zi;
    static integer num;
    static doublereal rrr;
    static integer idd1, idd2, imm2, iyy2;
    extern /* Subroutine */ int moda_(integer *, integer *, integer *, 
	    integer *, integer *, integer *);
    static integer midm, iupd;
    static doublereal covr;
    static integer iupm, imst, iupy, iyst, iflag, imend, iyend;
    static doublereal indrz[722];
    static integer iytmp, iymst, iymend, nrdaym;

    /* Fortran I/O blocks */
    static cilist io___718 = { 0, 12, 0, 0, 0 };
    static cilist io___722 = { 0, 12, 0, 0, 0 };
    static cilist io___730 = { 0, 12, 0, 0, 0 };
    static cilist io___733 = { 0, 12, 0, 0, 0 };
    static cilist io___740 = { 0, 0, 0, fmt_8000, 0 };


/* ---------------------------------------------------------------- */
/* input:        yr,mm,day       year(yyyy),month(mm),day(dd) */
/*               idn             day of year(ddd) */
/* output:       rz(3)           12-month-smoothed solar sunspot number */
/*               ig(3)           12-month-smoothed IG index */
/*               rsn             interpolation parameter */
/*               nmonth          previous or following month depending */
/*                               on day */

/* rz(1), ig(1) contain the indices for the month mm and rz(2), ig(2) */
/* for the previous month (if day less than 15) or for the following */
/* month (otherwise). These indices are for the mid of the month. The */
/* indices for the given day are obtained by linear interpolation and */
/* are stored in rz(3) and ig(3). */

/* the indices are obtained from the indices file ig_rz.dat that is */
/* read in subroutine initialize and stored in COMMON/indices/ */
/* ---------------------------------------------------------------- */

/* Rz12 and IG are determined from the file IG_RZ.DAT which has the */
/* following structure: */
/* day, month, year of the last update of this file, */
/* start month, start year, end month, end year, */
/* the 12 IG indices (13-months running mean) for the first year, */
/* the 12 IG indices for the second year and so on until the end year, */
/* the 12 Rz indices (13-months running mean) for the first year, */
/* the 12 Rz indices for the second year and so on until the end year. */
/* The inteporlation procedure also requires the IG and Rz values for */
/* the month preceeding the start month and the IG and Rz values for the */
/* month following the end month. These values are also included in */
/* IG_RZ. */

/* A negative Rz index means that the given index is the 13-months- */
/* running mean of the solar radio flux (F10.7). The close correlation */
/* between (Rz)12 and (F10.7)12 is used to derive the (Rz)12 indices. */

/* An IG index of -111 indicates that no IG values are available for the */
/* time period. In this case a correlation function between (IG)12 and */
/* (Rz)12 is used to obtain (IG)12. */

/* The computation of the 13-month-running mean for month M requires the */
/* indices for the six months preceeding M and the six months following */
/* M (month: M-6, ..., M+6). To calculate the current running mean one */
/* therefore requires predictions of the indix for the next six months. */
/* Starting from six months before the UPDATE DATE (listed at the top of */
/* the file) and onward the indices are therefore based on indices */
/* predictions. */

    /* Parameter adjustments */
    --ig;
    --rz;

    /* Function Body */
    if (iflag == 0) {
	o__1.oerr = 0;
	o__1.ounit = 12;
	o__1.ofnmlen = 9;
	o__1.ofnm = "ig_rz.dat";
	o__1.orl = 0;
	o__1.osta = "old";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
/* -web- special for web version */
/*          open(unit=12,file= */
/*     *'/usr/local/etc/httpd/cgi-bin/models/IRI/ig_rz.dat', */
/*     *status='old') */
/* Read the update date, the start date and the end date (mm,yyyy), and */
/* get number of data points to read. */
	s_rsle(&io___718);
	do_lio(&c__3, &c__1, (char *)&iupd, (ftnlen)sizeof(integer));
	do_lio(&c__3, &c__1, (char *)&iupm, (ftnlen)sizeof(integer));
	do_lio(&c__3, &c__1, (char *)&iupy, (ftnlen)sizeof(integer));
	e_rsle();
	s_rsle(&io___722);
	do_lio(&c__3, &c__1, (char *)&imst, (ftnlen)sizeof(integer));
	do_lio(&c__3, &c__1, (char *)&iyst, (ftnlen)sizeof(integer));
	do_lio(&c__3, &c__1, (char *)&imend, (ftnlen)sizeof(integer));
	do_lio(&c__3, &c__1, (char *)&iyend, (ftnlen)sizeof(integer));
	e_rsle();
	iymst = iyst * 100 + imst;
	iymend = iyend * 100 + imend;
/* inum_vals= 12-imst+1+(iyend-iyst-1)*12 +imend + 2 */
/*            1st year \ full years       \last y\ before & after */
	inum_vals__ = 3 - imst + (iyend - iyst) * 12 + imend;
/* Read all the ionoindx and indrz values */
	s_rsle(&io___730);
	i__1 = inum_vals__;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_lio(&c__5, &c__1, (char *)&ionoindx[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsle();
	s_rsle(&io___733);
	i__1 = inum_vals__;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_lio(&c__5, &c__1, (char *)&indrz[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsle();
	i__1 = inum_vals__;
	for (jj = 1; jj <= i__1; ++jj) {
	    rrr = indrz[jj - 1];
	    if (rrr < 0.) {
		covr = abs(rrr);
		rrr = sqrt(covr + 85.12) * 33.52 - 408.99;
		if (rrr < 0.) {
		    rrr = 0.;
		}
		indrz[jj - 1] = rrr;
	    }
	    if (ionoindx[jj - 1] > -90.) {
		goto L1;
	    }
	    zi = (1.4683266 - rrr * .00267690893) * rrr - 12.349154;
	    if (zi > 274.) {
		zi = 274.;
	    }
	    ionoindx[jj - 1] = zi;
L1:
	    ;
	}
	cl__1.cerr = 0;
	cl__1.cunit = 12;
	cl__1.csta = 0;
	f_clos(&cl__1);
	iflag = 1;
    }
    iytmp = *yr * 100 + *mm;
    if (iytmp < iymst || iytmp > iymend) {
	if (iounit_1.konsol > 1) {
	    io___740.ciunit = iounit_1.konsol;
	    s_wsfe(&io___740);
	    do_fio(&c__1, (char *)&iytmp, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&iymst, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&iymend, (ftnlen)sizeof(integer));
	    e_wsfe();
	}
	*nmonth = -1;
	return 0;
    }
/*       num=12-imst+1+(yr-iyst-1)*12+mm+1 */
    num = 2 - imst + (*yr - iyst) * 12 + *mm;
    rz[1] = indrz[num - 1];
    ig[1] = ionoindx[num - 1];
    midm = 15;
    if (*mm == 2) {
	midm = 14;
    }
    moda_(&c__0, yr, mm, &midm, &idd1, &nrdaym);
    if (*day < midm) {
	goto L1926;
    }
    imm2 = *mm + 1;
    if (imm2 > 12) {
	imm2 = 1;
	iyy2 = *yr + 1;
	idd2 = 380;
/*               if((yr/4*4.eq.yr).and.(yr/100*100.ne.yr)) idd2=381 */
	if (*yr / 4 << 2 == *yr) {
	    idd2 = 381;
	}
	if (*yr / 4 << 2 == *yr) {
	    idd2 = 381;
	}
    } else {
	iyy2 = *yr;
	midm = 15;
	if (imm2 == 2) {
	    midm = 14;
	}
	moda_(&c__0, &iyy2, &imm2, &midm, &idd2, &nrdaym);
    }
    rz[2] = indrz[num];
    ig[2] = ionoindx[num];
    *rsn = (*idn - idd1) * 1. / (idd2 - idd1);
    rz[3] = rz[1] + (rz[2] - rz[1]) * *rsn;
    ig[3] = ig[1] + (ig[2] - ig[1]) * *rsn;
    goto L1927;
L1926:
    imm2 = *mm - 1;
    if (imm2 < 1) {
	imm2 = 12;
	idd2 = -16;
	iyy2 = *yr - 1;
    } else {
	iyy2 = *yr;
	midm = 15;
	if (imm2 == 2) {
	    midm = 14;
	}
	moda_(&c__0, &iyy2, &imm2, &midm, &idd2, &nrdaym);
    }
    rz[2] = indrz[num - 2];
    ig[2] = ionoindx[num - 2];
    *rsn = (*idn - idd2) * 1. / (idd1 - idd2);
    rz[3] = rz[2] + (rz[1] - rz[2]) * *rsn;
    ig[3] = ig[2] + (ig[1] - ig[2]) * *rsn;
L1927:
    *nmonth = imm2;
    return 0;
} /* tcon_ */



/* Subroutine */ int lstid_(doublereal *fi, integer *icez, doublereal *r__, 
	doublereal *ae, doublereal *tm, doublereal *sax, doublereal *sux, 
	doublereal *ts70, doublereal *df0f2, doublereal *dhf2)
{
    /* Initialized data */

    static doublereal y1[84] = { 150.,250.,207.8,140.7,158.3,87.2,158.,150.,
	    250.,207.8,140.7,158.3,87.2,158.,115.,115.,183.5,144.2,161.4,
	    151.9,272.4,115.,115.,183.5,144.2,161.4,151.9,272.4,64.,320.,
	    170.6,122.3,139.,79.6,180.6,64.,320.,170.6,122.3,139.,79.6,180.6,
	    72.,84.,381.9,20.1,75.1,151.2,349.5,120.,252.,311.2,241.,187.4,
	    230.1,168.7,245.,220.,294.7,181.2,135.5,237.7,322.,170.,110.,
	    150.2,136.3,137.4,177.,114.,170.,314.,337.8,155.5,157.4,196.7,
	    161.8,100.,177.,159.8,165.6,137.5,132.2,94.3 };
    static doublereal y2[84] = { 2.5,2.,1.57,2.02,2.12,1.46,2.46,2.5,2.,1.57,
	    2.02,2.12,1.46,2.46,2.3,1.6,1.68,1.65,2.09,2.25,2.82,2.3,1.6,1.68,
	    1.65,2.09,2.25,2.82,.8,2.,1.41,1.57,1.51,1.46,2.2,.8,2.,1.41,1.57,
	    1.51,1.46,2.2,3.7,1.8,3.21,3.31,2.61,2.82,2.34,2.8,3.2,3.32,3.33,
	    2.96,3.43,2.44,3.5,2.8,2.37,2.79,2.26,3.4,2.28,3.9,2.,2.22,1.98,
	    2.33,3.07,1.56,3.7,3.,3.3,2.99,3.57,2.98,3.02,2.6,2.8,1.66,2.04,
	    1.91,1.49,.43 };
    static doublereal y3[84] = { -1.8,-1.9,-1.42,-1.51,-1.53,-1.05,-1.66,-1.8,
	    -1.9,-1.42,-1.51,-1.53,-1.05,-1.66,-1.5,-1.3,-1.46,-1.39,-1.53,
	    -1.59,-1.9,-1.5,-1.3,-1.46,-1.39,-1.53,-1.59,-1.9,-.7,-2.,-1.41,
	    -1.09,-1.22,-.84,-1.32,-.7,-2.,-1.41,-1.09,-1.22,-.84,-1.32,-1.7,
	    -1.,-2.08,-1.8,-1.35,-1.55,-1.79,-1.5,-2.,-2.08,-2.16,-1.86,-2.19,
	    -1.7,-2.2,-1.7,-1.57,-1.62,-1.19,-1.89,-1.47,-1.9,-1.5,-1.26,
	    -1.23,-1.52,-1.89,-1.02,-1.7,-1.7,-1.76,-1.43,-1.66,-1.54,-1.24,
	    -1.1,-1.5,-1.09,-1.23,-1.11,-1.14,-.4 };
    static doublereal y4[84] = { -2.,-5.,-5.,0.,0.,0.,2.,-2.,-5.,-5.,0.,0.,0.,
	    2.,-5.,-5.,6.,0.,1.,5.,2.,-5.,-5.,6.,0.,1.,5.,2.,0.,-7.,-3.,-6.,
	    2.,2.,3.,0.,-7.,-3.,-6.,2.,2.,3.,-5.,-1.,-11.,-6.,0.,-5.,-6.,-5.,
	    -10.,1.,4.,-6.,-2.,1.,2.,-13.,-10.,0.,-8.,10.,-16.,0.,-3.,-7.,-2.,
	    -2.,4.,2.,-11.,-12.,-13.,0.,0.,7.,0.,-8.,6.,-1.,-5.,-7.,4.,-4. };
    static doublereal y5[28] = { 0.,0.,-.1,-.19,-.19,-.25,-.06,0.,0.,-.31,
	    -.28,-.27,-.06,.02,0.,0.,.18,-.07,-.2,-.1,.3,0.,0.,-.24,-.5,-.4,
	    -.27,-.48 };
    static doublereal y6[28] = { 0.,0.,-3.5e-4,-2.8e-4,-3.3e-4,-2.3e-4,-7e-4,
	    0.,0.,-3e-4,-2.5e-4,-3e-4,-6e-4,-7.3e-4,0.,0.,-.0011,-6e-4,-3e-4,
	    -5e-4,-.0015,0.,0.,-8e-4,-.003,-2e-4,-5e-4,-3e-4 };

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle();
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal a[84]	/* was [7][2][3][2] */, b[84]	/* was [7][2][
	    3][2] */, c__[84]	/* was [7][2][3][2] */, d__[84]	/* was [7][2][
	    3][2] */;
    static integer i__, j, k, m, n;
    static doublereal t, a1[28]	/* was [7][2][2] */, b1[28]	/* was [7][2][
	    2] */;
    static integer n1;
    static doublereal ts, df1, df2, dh1, dh2;
    static integer inn;

    /* Fortran I/O blocks */
    static cilist io___767 = { 0, 6, 0, 0, 0 };
    static cilist io___769 = { 0, 6, 0, 0, 0 };


/* ***************************************************************** */
/*   COMPUTER PROGRAM FOR UPDATING FOF2 AND HMF2 FOR EFFECTS OF */
/*   THE LARGE SCALE SUBSTORM. */

/*   P.V.Kishcha, V.M.Shashunkina, E.E.Goncharova, Modelling of the */
/*   ionospheric effects of isolated and consecutive substorms on */
/*   the basis of routine magnetic data, Geomagn. and Aeronomy v.32, */
/*   N.3, 172-175, 1992. */

/*   P.V.Kishcha et al. Updating the IRI ionospheric model for */
/*   effects of substorms, Adv. Space Res.(in press) 1992. */

/*   Address: Dr. Pavel V. Kishcha, */
/*            Institute of Terrestrial Magnetism,Ionosphere and Radio */
/*            Wave Propagation, Russian Academy of Sciences, */
/*            142092, Troitsk, Moscow Region, Russia */

/* ***       INPUT PARAMETERS: */
/*       FI ------ GEOMAGNETIC LATITUDE, */
/*       ICEZ ---- INDEX OF SEASON(1-WINTER AND EQUINOX,2-SUMMER), */
/*       R ------- ZURICH SUNSPOT NUMBER, */
/*       AE ------ MAXIMUM AE-INDEX REACHED DURING SUBSTORM, */
/*       TM ------ LOCAL TIME, */
/*       SAX,SUX - TIME OF SUNSET AND SUNRISE, */
/*       TS70 ---- ONSET TIME (LT) OF SUBSTORMS ONSET */
/*                        STARTING ON FI=70 DEGR. */
/* ***      OUTPUT PARAMETERS: */
/*       DF0F2,DHF2- CORRECTIONS TO foF2 AND hmF2 FROM IRI OR */
/*                   OBSERVATIONAL MEDIAN  OF THOSE VALUES. */
/* ***************************************************************** */
    inn = 0;
    if (*ts70 > 12. && *tm < *sax) {
	inn = 1;
    }
    if (*fi < 0.) {
	*fi = abs(*fi);
    }
    n = 0;
    for (m = 1; m <= 2; ++m) {
	for (k = 1; k <= 3; ++k) {
	    for (j = 1; j <= 2; ++j) {
		for (i__ = 1; i__ <= 7; ++i__) {
		    ++n;
		    a[i__ + (j + (k + m * 3 << 1)) * 7 - 64] = y1[n - 1];
		    b[i__ + (j + (k + m * 3 << 1)) * 7 - 64] = y2[n - 1];
		    c__[i__ + (j + (k + m * 3 << 1)) * 7 - 64] = y3[n - 1];
/* L1: */
		    d__[i__ + (j + (k + m * 3 << 1)) * 7 - 64] = y4[n - 1];
		}
	    }
	}
    }
    n1 = 0;
    for (m = 1; m <= 2; ++m) {
	for (j = 1; j <= 2; ++j) {
	    for (i__ = 1; i__ <= 7; ++i__) {
		++n1;
		a1[i__ + (j + (m << 1)) * 7 - 22] = y5[n1 - 1];
/* L2: */
		b1[i__ + (j + (m << 1)) * 7 - 22] = y6[n1 - 1];
	    }
	}
    }
    if (*fi > 65. || *ae < 500.) {
	s_wsle(&io___767);
	do_lio(&c__9, &c__1, "LSTID are for AE>500. and ABS(FI)<65.", (ftnlen)
		37);
	e_wsle();
	goto L4;
    }
    ts = *ts70 + (*fi * -1.5571 + 109.) / 60.;
    if (ts < *sux && ts > *sax) {
	s_wsle(&io___769);
	do_lio(&c__9, &c__1, " LSTID are only at night", (ftnlen)24);
	e_wsle();
	goto L4;
    }
    if (inn == 1) {
	*tm += 24.;
    }
    if (ts >= *tm || ts < *tm - 5.) {
/*        WRITE(*,*)'LSTID are onli if  TM-5.<TS<TM ;Here TS=',TS, */
/*     &     'TM=',TM */
	goto L4;
    }
    for (i__ = 1; i__ <= 7; ++i__) {
	if (*fi >= (i__ - 1) * 10. - 5. && *fi < (i__ - 1) * 10. + 5.) {
	    goto L8;
	}
/* L7: */
    }
L8:
    j = *icez;
    if (*ae >= 500. && *ae <= 755.) {
	k = 1;
    }
    if (*ae > 755. && *ae < 1e3) {
	k = 2;
    }
    if (*ae >= 1e3) {
	k = 3;
    }
    m = -1;
    if (*r__ <= 20.) {
	m = 1;
    }
    if (*r__ >= 120.) {
	m = 2;
    }
    t = *tm - ts;
    if (m < 0) {
	goto L3;
    }
/*        WRITE(*,*)'A1=',A1(I,J,M),' B1=',B1(I,J,M) */
/*        WRITE(*,*)'A=',A(I,J,K,M),' B=',B(I,J,K,M),' C=',C(I,J,K,M), */
/*     *'D=',D(I,J,K,M) */
    *df0f2 = a1[i__ + (j + (m << 1)) * 7 - 22] + b1[i__ + (j + (m << 1)) * 7 
	    - 22] * *ae;
    *dhf2 = a[i__ + (j + (k + m * 3 << 1)) * 7 - 64] * pow_dd(&t, &b[i__ + (j 
	    + (k + m * 3 << 1)) * 7 - 64]) * exp(c__[i__ + (j + (k + m * 3 << 
	    1)) * 7 - 64] * t) + d__[i__ + (j + (k + m * 3 << 1)) * 7 - 64];
    goto L5;
L3:
    df1 = a1[i__ + (j + 2) * 7 - 22] + b1[i__ + (j + 2) * 7 - 22] * *ae;
    df2 = a1[i__ + (j + 4) * 7 - 22] + b1[i__ + (j + 4) * 7 - 22] * *ae;
    *df0f2 = df1 + (df2 - df1) * (*r__ - 20.) / 100.;
    dh1 = a[i__ + (j + (k + 3 << 1)) * 7 - 64] * pow_dd(&t, &b[i__ + (j + (k 
	    + 3 << 1)) * 7 - 64]) * exp(c__[i__ + (j + (k + 3 << 1)) * 7 - 64]
	     * t) + d__[i__ + (j + (k + 3 << 1)) * 7 - 64];
    dh2 = a[i__ + (j + (k + 6 << 1)) * 7 - 64] * pow_dd(&t, &b[i__ + (j + (k 
	    + 6 << 1)) * 7 - 64]) * exp(c__[i__ + (j + (k + 6 << 1)) * 7 - 64]
	     * t) + d__[i__ + (j + (k + 6 << 1)) * 7 - 64];
    *dhf2 = dh1 + (dh2 - dh1) * (*r__ - 20.) / 100.;
    goto L5;
L4:
    *dhf2 = 0.;
    *df0f2 = 0.;
L5:
    if (inn == 1) {
	*tm += -24.;
    }
    return 0;
} /* lstid_ */



/* Subroutine */ int apf_(integer *iyyyy, integer *imn, integer *id, 
	doublereal *hour, integer *iap)
{
    /* Initialized data */

    static integer lm[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    /* Format strings */
    static char fmt_10[] = "(3i3,8i3,f5.1)";
    static char fmt_100[] = "(1x,\002Date is outside range of Ap indices fil\
e.\002,\002 STORM model is turned off.\002)";

    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rdfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rdfe(), s_wsfe(cilist *), e_wsfe(), f_clos(cllist *);

    /* Local variables */
    static doublereal f;
    static integer i__, j1, j2, i9, jd, is, jy, idn, jmn, nyd, iss, iiap[8], 
	    ihour;

    /* Fortran I/O blocks */
    static cilist io___781 = { 1, 13, 0, fmt_10, 0 };
    static cilist io___790 = { 1, 13, 0, fmt_10, 0 };
    static cilist io___792 = { 1, 13, 0, fmt_10, 0 };
    static cilist io___793 = { 0, 0, 0, fmt_100, 0 };


/* -------------------------------------------------------------------- */
/* Finds 3-hourly Ap indices for IRI-storm for given year IYYYY (yyyy), */
/* month (IMN), day (ID), and UT (HOUR, decimal hours). The indices are */
/* stored in IAP(13) providing the 13 3-hourly indices prior to HOUR. */
/* The 3-hour UT intervals during the day are: (0-3),)3-6),)6-9),9-12, */
/* 12-15,15-18,18-21,)21-24(. */
/* If date is outside the range of the Ap indices file than iap(1)=-5 */
/* -------------------------------------------------------------------- */
    /* Parameter adjustments */
    --iap;

    /* Function Body */
    o__1.oerr = 0;
    o__1.ounit = 13;
    o__1.ofnmlen = 6;
    o__1.ofnm = "ap.dat";
    o__1.orl = 39;
    o__1.osta = "OLD";
    o__1.oacc = "DIRECT";
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
/* -web-sepcial vfor web version */
/*      OPEN(13,FILE='/usr/local/etc/httpd/cgi-bin/models/IRI/ap.dat', */
    for (i__ = 1; i__ <= 8; ++i__) {
	iap[i__] = -1;
    }
    if (*iyyyy < 1960) {
	goto L21;
    }
/* file starts at Jan 1, 1960 */
    is = 0;
    if (*iyyyy > 1960) {
	i__1 = *iyyyy - 1;
	for (i__ = 1960; i__ <= i__1; ++i__) {
	    nyd = 365;
	    if (i__ / 4 << 2 == i__) {
		nyd = 366;
	    }
	    is += nyd;
	}
    }
    lm[1] = 28;
    if (*iyyyy / 4 << 2 == *iyyyy) {
	lm[1] = 29;
    }
    idn = 0;
    i__1 = *imn - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	idn += lm[i__ - 1];
    }
    idn += *id;
    is += idn;
    ihour = (integer) (*hour / 3.) + 1;
    if (ihour > 8) {
	ihour = 8;
    }
    if ((is << 3) + ihour < 13) {
	goto L21;
    }
/* at least 13 indices available */
    io___781.cirec = is;
    i__1 = s_rdfe(&io___781);
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&jy, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&jmn, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&jd, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__8, (char *)&iiap[0], (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&f, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = e_rdfe();
    if (i__1 != 0) {
	goto L21;
    }
    for (i9 = 1; i9 <= 8; ++i9) {
	if (iiap[i9 - 1] < -2) {
	    goto L21;
	}
    }
    j1 = 13 - ihour;
    i__1 = ihour;
    for (i__ = 1; i__ <= i__1; ++i__) {
	iap[j1 + i__] = iiap[i__ - 1];
    }
    iss = is - 1;
    io___790.cirec = iss;
    i__1 = s_rdfe(&io___790);
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&jy, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&jmn, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&jd, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__8, (char *)&iiap[0], (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&f, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = e_rdfe();
    if (i__1 != 0) {
	goto L21;
    }
    for (i9 = 1; i9 <= 8; ++i9) {
	if (iiap[i9 - 1] < -2) {
	    goto L21;
	}
    }
    if (ihour > 4) {
	i__1 = j1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    iap[i__] = iiap[8 - j1 + i__ - 1];
	}
    } else {
	j2 = 5 - ihour;
	for (i__ = 1; i__ <= 8; ++i__) {
	    iap[j2 + i__] = iiap[i__ - 1];
	}
	iss = is - 2;
	io___792.cirec = iss;
	i__1 = s_rdfe(&io___792);
	if (i__1 != 0) {
	    goto L21;
	}
	i__1 = do_fio(&c__1, (char *)&jy, (ftnlen)sizeof(integer));
	if (i__1 != 0) {
	    goto L21;
	}
	i__1 = do_fio(&c__1, (char *)&jmn, (ftnlen)sizeof(integer));
	if (i__1 != 0) {
	    goto L21;
	}
	i__1 = do_fio(&c__1, (char *)&jd, (ftnlen)sizeof(integer));
	if (i__1 != 0) {
	    goto L21;
	}
	i__1 = do_fio(&c__8, (char *)&iiap[0], (ftnlen)sizeof(integer));
	if (i__1 != 0) {
	    goto L21;
	}
	i__1 = do_fio(&c__1, (char *)&f, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L21;
	}
	i__1 = e_rdfe();
	if (i__1 != 0) {
	    goto L21;
	}
	for (i9 = 1; i9 <= 8; ++i9) {
	    if (iiap[i9 - 1] < -2) {
		goto L21;
	    }
	}
	i__1 = j2;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    iap[i__] = iiap[8 - j2 + i__ - 1];
	}
    }
    goto L20;
L21:
    if (iounit_1.konsol > 1) {
	io___793.ciunit = iounit_1.konsol;
	s_wsfe(&io___793);
	e_wsfe();
    }
    iap[1] = -5;
L20:
    cl__1.cerr = 0;
    cl__1.cunit = 13;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* apf_ */



/* Subroutine */ int apf_only__(integer *iyyyy, integer *imn, integer *id, 
	doublereal *f107d)
{
    /* Initialized data */

    static integer lm[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    /* Format strings */
    static char fmt_10[] = "(3i3,8i3,f5.1)";
    static char fmt_100[] = "(1x,\002Date is outside range of F10.7D indices\
 file.\002)";

    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rdfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rdfe(), s_wsfe(cilist *), e_wsfe(), f_clos(cllist *);

    /* Local variables */
    static doublereal f;
    static integer i__, jd, is, jy, idn, jmn, nyd, iiap[8];

    /* Fortran I/O blocks */
    static cilist io___799 = { 1, 13, 0, fmt_10, 0 };
    static cilist io___805 = { 0, 0, 0, fmt_100, 0 };


/* -------------------------------------------------------------------- */
/* Finds daily F10.7 index, F107D, for given year IYYYY (yyyy), month */
/* (IMN), and day (ID). Using AP.DAT file on UNIT=13. */
/* Is used for vdrift. */
/* If date is outside the range of indices file than F107D=-5 */
/* -------------------------------------------------------------------- */
    o__1.oerr = 0;
    o__1.ounit = 13;
    o__1.ofnmlen = 6;
    o__1.ofnm = "ap.dat";
    o__1.orl = 39;
    o__1.osta = "OLD";
    o__1.oacc = "DIRECT";
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
/* -web-sepcial vfor web version */
/*      OPEN(13,FILE='/usr/local/etc/httpd/cgi-bin/models/IRI/ap.dat', */
    if (*iyyyy < 1960) {
	goto L21;
    }
/* AP.DAT starts at Jan 1, 1960 */
    is = 0;
    i__1 = *iyyyy - 1;
    for (i__ = 1960; i__ <= i__1; ++i__) {
	nyd = 365;
	if (i__ / 4 << 2 == i__) {
	    nyd = 366;
	}
/* leap year */
	is += nyd;
    }
    lm[1] = 28;
    if (*iyyyy / 4 << 2 == *iyyyy) {
	lm[1] = 29;
    }
/* leap year */
    idn = 0;
    i__1 = *imn - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	idn += lm[i__ - 1];
    }
    is = is + idn + *id;
    io___799.cirec = is;
    i__1 = s_rdfe(&io___799);
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&jy, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&jmn, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&jd, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__8, (char *)&iiap[0], (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = do_fio(&c__1, (char *)&f, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L21;
    }
    i__1 = e_rdfe();
    if (i__1 != 0) {
	goto L21;
    }
    *f107d = f;
    if (f < -4.) {
	goto L21;
    }
    goto L20;
L21:
    if (iounit_1.konsol > 1) {
	io___805.ciunit = iounit_1.konsol;
	s_wsfe(&io___805);
	e_wsfe();
    }
L20:
    cl__1.cerr = 0;
    cl__1.cunit = 13;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* apf_only__ */



/* ----------------------STORM MODEL -------------------------------- */

/* Subroutine */ int conver_(doublereal *rga, doublereal *rgo, doublereal *
	rgma)
{
    /* Initialized data */

    static doublereal cormag[1820]	/* was [20][91] */ = { 163.68,163.68,
	    163.68,163.68,163.68,163.68,163.68,163.68,163.68,163.68,163.68,
	    163.68,163.68,163.68,163.68,163.68,163.68,163.68,163.68,163.68,
	    162.6,163.12,163.64,164.18,164.54,164.9,165.16,165.66,166.,165.86,
	    165.2,164.38,163.66,162.94,162.42,162.,161.7,161.7,161.8,162.14,
	    161.2,162.18,163.26,164.44,165.62,166.6,167.42,167.8,167.38,
	    166.82,166.,164.66,163.26,162.16,161.18,160.4,159.94,159.8,159.98,
	    160.44,159.8,161.14,162.7,164.5,166.26,167.9,169.18,169.72,169.36,
	    168.24,166.7,164.8,162.9,161.18,159.74,158.6,157.94,157.8,157.98,
	    158.72,158.4,160.1,162.02,164.28,166.64,169.,170.8,171.72,171.06,
	    169.46,167.1,164.64,162.18,160.02,158.2,156.8,156.04,155.8,156.16,
	    157.02,157.,158.96,161.24,163.86,166.72,169.8,172.42,173.72,
	    172.82,170.34,167.3,164.22,161.34,158.74,156.6,155.,154.08,153.9,
	    154.36,155.36,155.5,157.72,160.36,163.32,166.6,170.2,173.7,175.64,
	    174.18,170.8,167.1,163.56,160.24,157.36,154.96,153.1,152.08,
	    151.92,152.46,153.76,154.1,156.52,159.36,162.52,166.24,170.3,
	    174.62,177.48,175.04,170.82,166.6,162.7,159.02,155.88,153.22,
	    151.2,150.08,149.92,150.64,152.2,152.8,155.32,158.28,161.7,165.58,
	    170.,174.84,178.46,175.18,170.38,165.8,161.64,157.8,154.38,151.52,
	    149.3,148.18,148.02,148.92,150.6,151.4,154.08,157.18,160.68,
	    164.78,169.4,174.34,177.44,174.28,169.44,164.7,160.34,156.3,
	    152.78,149.72,147.4,146.18,146.04,147.12,149.04,150.1,152.88,156.,
	    159.58,163.78,168.5,173.28,175.6,172.86,168.14,163.4,158.98,
	    154.88,151.1,147.98,145.5,144.18,144.14,145.4,147.48,148.8,151.68,
	    154.88,158.48,162.68,167.4,171.76,173.6,171.12,166.68,162.,157.48,
	    153.28,149.5,146.18,143.5,142.18,142.24,143.68,145.98,147.5,
	    150.54,153.68,157.28,161.42,166.1,170.1,171.48,169.22,164.98,
	    160.4,155.88,151.68,147.8,144.34,141.6,140.18,140.26,141.98,
	    144.62,146.3,149.34,152.48,155.98,160.08,164.6,168.34,169.38,
	    167.2,163.18,158.6,154.18,149.98,146.02,142.54,139.7,138.18,
	    138.46,140.26,143.16,145.1,148.14,151.18,154.6,158.68,163.1,
	    166.48,167.28,165.18,161.32,156.9,152.48,148.28,144.32,140.74,
	    137.8,136.22,136.48,138.64,141.76,143.9,146.98,149.98,153.3,
	    157.24,161.4,164.52,165.16,162.86,159.42,155.,150.68,146.48,
	    142.52,138.94,135.9,134.22,134.68,137.02,140.4,142.7,145.84,
	    148.76,151.92,155.74,159.7,162.52,162.96,160.98,157.42,153.1,
	    148.84,144.68,140.82,137.2,134.,132.32,132.8,135.42,139.1,141.6,
	    144.74,147.46,150.52,154.2,158.,160.46,160.76,158.86,155.36,151.2,
	    146.94,142.88,139.02,135.4,132.1,130.32,131.,133.8,137.74,140.5,
	    143.58,146.24,149.12,152.6,156.2,158.4,158.66,156.76,153.36,149.3,
	    145.04,141.08,137.3,133.6,130.3,128.42,129.12,132.28,136.44,139.3,
	    142.48,144.94,147.64,150.48,154.3,156.34,156.36,154.56,151.26,
	    147.3,143.14,139.2,135.5,131.9,128.4,126.52,127.32,130.76,135.18,
	    138.2,141.28,143.72,146.24,149.26,152.4,154.24,154.16,152.36,
	    149.16,145.3,141.24,137.3,133.7,130.1,126.6,124.62,125.54,129.16,
	    133.92,137.1,140.18,142.42,144.66,147.62,150.5,152.18,151.96,
	    150.16,147.1,143.3,139.24,135.5,131.9,128.36,124.8,122.72,123.74,
	    127.64,132.62,135.9,139.02,141.12,143.18,145.92,148.6,149.98,
	    149.76,148.04,145.,141.2,137.3,133.6,130.1,126.6,123.,120.86,
	    121.96,126.12,131.36,134.8,137.88,139.8,141.68,144.08,146.6,
	    147.88,147.56,145.84,142.9,139.2,135.3,131.7,128.28,124.86,121.3,
	    118.96,120.18,124.7,130.16,133.6,136.72,138.48,140.1,142.38,144.6,
	    145.72,145.34,143.64,140.8,137.1,133.3,129.72,126.48,123.1,119.5,
	    117.16,118.48,123.18,128.86,132.4,135.42,137.08,138.5,140.54,
	    142.6,143.52,143.06,141.44,138.7,135.1,131.3,127.82,124.58,121.4,
	    117.7,115.26,116.7,121.66,127.6,131.2,134.22,135.66,136.82,138.7,
	    140.6,141.36,140.86,139.24,136.5,133.,129.3,125.92,122.78,119.6,
	    116.,113.4,114.92,120.16,126.3,130.,132.92,134.24,135.14,136.8,
	    138.6,139.16,138.64,137.12,134.4,130.9,127.2,123.92,120.96,117.9,
	    114.2,111.56,113.12,118.64,124.9,128.7,131.56,132.74,133.44,134.9,
	    136.5,137.,136.36,134.82,132.3,128.7,125.16,121.94,119.06,116.1,
	    112.5,109.7,111.42,117.14,123.6,127.3,130.16,131.22,131.66,133.,
	    134.5,134.8,134.14,132.62,130.14,126.6,123.06,119.94,117.16,114.3,
	    110.7,107.8,109.64,115.62,122.24,125.9,128.76,129.62,129.96,
	    131.06,132.4,132.6,131.86,130.42,128.,124.5,120.96,117.96,115.26,
	    112.54,108.9,105.94,107.86,114.02,120.84,124.05,126.79,127.55,
	    127.83,128.9,130.21,130.41,129.71,128.33,125.96,122.49,118.96,
	    115.97,113.26,110.52,106.89,104.01,106.,112.21,119.06,122.19,
	    124.82,125.48,125.69,126.73,128.03,128.22,127.55,126.23,123.92,
	    120.47,116.97,113.97,111.26,108.5,104.89,102.08,104.14,110.41,
	    117.29,120.34,122.85,123.4,123.56,124.57,125.84,126.03,125.4,
	    124.14,121.88,118.46,114.97,111.98,109.26,106.48,102.88,100.15,
	    102.28,108.6,115.51,118.49,120.88,121.33,121.42,122.4,123.65,
	    123.84,123.24,122.04,119.83,116.45,112.97,109.98,107.26,104.46,
	    100.87,98.22,100.42,106.79,113.74,116.63,118.91,119.26,119.29,
	    120.24,121.47,121.65,121.09,119.95,117.79,114.43,110.98,107.99,
	    105.26,102.44,98.87,96.29,98.56,104.98,111.96,114.78,116.94,
	    117.19,117.15,118.07,119.28,119.46,118.93,117.86,115.75,112.42,
	    108.98,106.,103.26,100.42,96.86,94.36,96.7,103.18,110.19,112.93,
	    114.97,115.12,115.02,115.91,117.09,117.27,116.78,115.76,113.71,
	    110.41,106.98,104.,101.26,98.4,94.85,92.43,94.84,101.37,108.41,
	    111.07,113.,113.04,112.88,113.74,114.91,115.08,114.62,113.67,
	    111.67,108.39,104.99,102.01,99.26,96.38,92.85,90.51,92.97,99.56,
	    106.64,109.22,111.03,110.97,110.75,111.58,112.72,112.89,112.47,
	    111.57,109.63,106.38,102.99,100.01,97.26,94.36,90.84,88.58,91.11,
	    97.75,104.86,107.37,109.06,108.9,108.61,109.41,110.53,110.7,
	    110.31,109.48,107.59,104.37,100.99,98.02,95.26,92.34,88.83,86.65,
	    89.25,95.95,103.09,105.51,107.09,106.83,106.48,107.25,108.35,
	    108.51,108.16,107.39,105.55,102.35,99.,96.03,93.26,90.32,86.83,
	    84.72,87.39,94.14,101.31,103.66,105.12,104.76,104.34,105.08,
	    106.16,106.32,106.,105.29,103.5,100.34,97.,94.03,91.26,88.3,84.82,
	    82.79,85.53,92.33,99.54,101.81,103.15,102.68,102.21,102.92,103.97,
	    104.13,103.85,103.2,101.46,98.33,95.,92.04,89.26,86.28,82.81,
	    80.86,83.67,90.52,97.76,99.95,101.18,100.61,100.07,100.75,101.79,
	    101.94,101.69,101.1,99.42,96.31,93.01,90.04,87.26,84.26,80.81,
	    78.93,81.81,88.72,95.99,98.1,99.21,98.54,97.94,98.59,99.6,99.75,
	    99.54,99.01,97.38,94.3,91.01,88.05,85.26,82.24,78.8,77.,79.95,
	    86.91,94.21,96.25,97.24,96.47,95.81,96.43,97.41,97.56,97.39,96.92,
	    95.34,92.29,89.01,86.06,83.26,80.22,76.79,75.07,78.09,85.1,92.43,
	    94.39,95.27,94.4,93.67,94.26,95.23,95.37,95.23,94.82,93.3,90.27,
	    87.02,84.06,81.26,78.2,74.79,73.14,76.23,83.3,90.66,92.54,93.3,
	    92.32,91.54,92.1,93.04,93.18,93.08,92.73,91.26,88.26,85.02,82.07,
	    79.26,76.18,72.78,71.21,74.37,81.49,88.88,90.69,91.33,90.25,89.4,
	    89.93,90.85,90.99,90.92,90.63,89.21,86.25,83.02,80.07,77.26,74.16,
	    70.77,69.28,72.51,79.68,87.11,88.83,89.36,88.18,87.27,87.77,88.67,
	    88.8,88.77,88.54,87.17,84.23,81.03,78.08,75.26,72.14,68.77,67.35,
	    70.65,77.87,85.33,86.98,87.39,86.11,85.13,85.6,86.48,86.61,86.61,
	    86.45,85.13,82.22,79.03,76.09,73.26,70.12,66.76,65.42,68.79,76.07,
	    83.56,85.13,85.42,84.04,83.,83.44,84.29,84.42,84.46,84.35,83.09,
	    80.21,77.03,74.09,71.26,68.1,64.75,63.49,66.93,74.26,81.78,83.27,
	    83.45,81.96,80.86,81.27,82.11,82.23,82.3,82.26,81.05,78.19,75.04,
	    72.1,69.26,66.08,62.75,61.57,65.06,72.45,80.01,81.42,81.48,79.89,
	    78.73,79.11,79.92,80.04,80.15,80.16,79.01,76.18,73.04,70.1,67.26,
	    64.06,60.74,59.64,63.2,70.64,78.23,79.57,79.51,77.82,76.59,76.94,
	    77.73,77.85,77.99,78.07,76.97,74.17,71.04,68.11,65.26,62.04,58.73,
	    57.71,61.34,68.84,76.46,77.71,77.54,75.75,74.46,74.78,75.55,75.66,
	    75.84,75.98,74.93,72.15,69.05,66.12,63.26,60.02,56.73,55.78,59.48,
	    67.03,74.68,75.86,75.57,73.68,72.32,72.61,73.36,73.47,73.68,73.88,
	    72.88,70.14,67.05,64.12,61.26,58.,54.72,53.85,57.62,65.22,72.91,
	    74.01,73.6,71.6,70.19,70.45,71.17,71.28,71.53,71.79,70.84,68.13,
	    65.05,62.13,59.26,55.98,52.71,51.92,55.76,63.41,71.13,72.15,71.63,
	    69.53,68.05,68.28,68.99,69.09,69.37,69.69,68.8,66.11,63.06,60.13,
	    57.26,53.96,50.71,49.99,53.9,61.61,69.36,70.3,69.66,67.46,65.92,
	    66.12,66.8,66.9,67.22,67.6,66.76,64.1,61.06,58.14,55.26,51.94,
	    48.7,48.06,52.04,59.8,67.58,67.7,67.06,65.08,63.72,63.98,64.6,
	    64.8,65.12,65.6,64.86,62.4,59.26,56.24,53.18,49.84,46.6,46.12,
	    50.12,57.52,64.8,64.9,64.42,62.7,61.62,61.78,62.4,62.6,63.04,
	    63.58,63.,60.6,57.46,54.42,51.18,47.7,44.6,44.22,48.02,55.06,
	    61.92,62.1,61.72,60.32,59.5,59.68,60.2,60.46,60.94,61.58,61.,58.7,
	    55.66,52.52,49.18,45.6,42.5,42.22,46.,52.6,58.98,59.2,59.18,58.12,
	    57.32,57.48,58.,58.3,58.84,59.48,59.04,56.9,53.86,50.62,47.1,43.5,
	    40.5,40.28,43.98,50.22,56.18,56.4,56.64,55.84,55.2,55.38,55.8,
	    56.16,56.84,57.48,57.04,55.1,52.06,48.7,45.1,41.4,38.4,38.28,
	    41.88,47.94,53.44,53.7,54.14,53.56,53.1,53.24,53.7,54.06,54.74,
	    55.38,55.14,53.2,50.26,46.8,43.1,39.34,36.4,36.38,39.96,45.56,
	    50.84,51.1,51.7,51.36,51.,51.14,51.5,51.96,52.64,53.38,53.08,51.3,
	    48.36,44.9,41.02,37.24,34.4,34.38,37.86,43.28,48.2,48.5,49.26,
	    49.18,48.9,49.04,49.4,49.86,50.64,51.28,51.08,49.4,46.46,42.98,
	    39.02,35.14,32.4,32.48,35.72,41.,45.7,46.,46.96,46.98,46.8,46.94,
	    47.3,47.76,48.54,49.28,49.08,47.4,44.56,41.08,37.02,33.14,30.4,
	    30.58,33.84,38.72,43.2,43.5,44.62,44.8,44.8,44.94,45.2,45.76,
	    46.54,47.18,46.98,45.5,42.66,39.08,35.02,31.14,28.4,28.58,31.82,
	    36.52,40.8,41.2,42.32,42.54,42.7,42.84,43.2,43.66,44.44,45.08,
	    44.98,43.5,40.76,37.08,33.04,29.04,26.4,26.68,29.82,34.34,38.4,
	    38.8,40.12,40.6,40.7,40.84,41.1,41.62,42.34,42.98,42.88,41.5,
	    38.76,35.18,31.04,27.14,24.5,24.78,27.7,32.14,36.06,36.5,37.88,
	    38.5,38.68,38.84,39.1,39.56,40.34,40.88,40.82,39.4,36.76,33.18,
	    29.12,25.14,22.5,22.88,25.9,29.96,33.86,34.3,35.68,36.42,36.68,
	    36.84,37.1,37.56,38.24,38.88,38.72,37.4,34.76,31.18,27.12,23.14,
	    20.6,20.98,23.9,27.88,31.66,32.1,33.58,34.32,34.68,34.84,35.1,
	    35.56,36.24,36.78,36.62,35.3,32.72,29.18,25.14,21.24,18.7,19.08,
	    21.9,25.88,29.42,29.9,31.48,32.32,32.68,32.84,33.1,33.56,34.22,
	    34.68,34.42,33.2,30.72,27.28,23.22,19.34,16.8,17.24,20.,23.78,
	    27.32,27.7,29.38,30.24,30.68,30.94,31.2,31.66,32.22,32.58,32.32,
	    31.1,28.62,25.28,21.32,17.48,15.,15.38,18.18,21.8,25.22,25.7,
	    27.28,28.24,28.78,29.04,29.3,29.66,30.22,30.5,30.22,29.,26.62,
	    23.3,19.42,15.64,13.1,13.54,16.28,19.8,23.12,23.6,25.24,26.24,
	    26.78,27.14,27.4,27.76,28.22,28.4,28.12,26.8,24.52,21.3,17.52,
	    13.78,11.3,11.74,14.48,17.9,21.12,21.6,23.24,24.34,24.88,25.24,
	    25.5,25.86,26.22,26.4,25.98,24.7,22.48,19.4,15.72,12.04,9.5,9.94,
	    12.58,16.02,19.12,19.6,21.24,22.34,22.98,23.34,23.7,24.,24.3,24.4,
	    23.88,22.6,20.48,17.52,14.,10.34,7.8,8.18,10.88,14.22,17.18,17.6,
	    19.34,20.44,21.16,21.54,21.9,22.16,22.4,22.32,21.78,20.6,18.48,
	    15.62,12.2,8.68,6.,6.44,9.18,12.42,15.28,15.8,17.44,18.54,19.26,
	    19.74,20.1,20.3,20.5,20.32,19.72,18.5,16.54,13.84,10.68,7.14,4.4,
	    4.74,7.58,10.74,13.48,14.,15.54,16.74,17.46,17.94,18.3,18.5,18.58,
	    18.32,17.72,16.5,14.64,12.24,9.18,5.84,2.9,3.3,6.16,9.14,11.84,
	    12.3,13.78,14.94,15.66,16.24,16.5,16.7,16.7,16.42,15.78,14.6,12.9,
	    10.66,7.86,4.88,1.6,1.72,4.96,7.84,10.24,10.7,12.14,13.24,13.96,
	    14.44,14.8,14.9,14.88,14.52,13.92,12.8,11.3,9.28,6.94,4.32,1.8,
	    1.94,4.34,6.78,8.94,9.4,10.58,11.64,12.36,12.74,13.1,13.2,13.08,
	    12.72,12.12,11.1,9.86,8.3,6.5,4.6,3.1,3.16,4.5,6.2,7.9,8.4,9.42,
	    10.14,10.76,11.14,11.4,11.4,11.38,11.02,10.46,9.7,8.72,7.64,6.46,
	    5.42,4.6,4.7,5.34,6.24,7.36,7.9,8.46,8.92,9.28,9.54,9.7,9.7,9.68,
	    9.42,9.06,8.6,8.08,7.56,7.02,6.56,6.3,6.3,6.52,6.96,7.38,8.15,
	    8.15,8.15,8.15,8.15,8.15,8.15,8.15,8.15,8.15,8.15,8.15,8.15,8.15,
	    8.15,8.15,8.15,8.15,8.15,8.15 };

    /* System generated locals */
    doublereal d__1;

    /* Local variables */
    static doublereal x, y, x1, x2, y1, y2;
    static integer la1, la2;
    static doublereal gm1, gm2, gm3, gm4;
    static integer lo1, lo2;
    static doublereal rla, rlo, gmla, rlan;

/*     This subroutine converts a geographic latitude and longitude */
/*     location to a corrected geomagnetic latitude. */

/*     INPUT: */
/*       geographic latitude   -90. to +90. */
/*       geographic longitude  0. to 360. positive east from Greenwich. */

/*     OUTPUT: */
/*       corrected geomagnetic latitude	-90. to +90. */
/*     Data Input */
    rlan = *rga;
    rlo = *rgo;
/*     From "normal" geographic latitude */
/*     to angle from South Pole. */
    rla = rlan + 90;
    if (rlo == 360.) {
	rlo = 0.;
    }
/*     PROXIMITY */
/*     coefficients of the latitudinal points */
    la1 = (integer) (rla / 2) + 1;
    la2 = la1 + 1;
    if (la2 > 91) {
	la2 = 91;
    }
/*     coefficients of the longitudinal points */
    lo1 = (integer) (rlo / 18) + 1;
/* orr      LO2 = LO1 + 1 */
    lo2 = lo1 % 20 + 1;
/*     Four points of Geomagnetic Coordinates */
    gm1 = cormag[lo1 + la1 * 20 - 21];
    gm2 = cormag[lo1 + la2 * 20 - 21];
    gm3 = cormag[lo2 + la1 * 20 - 21];
    gm4 = cormag[lo2 + la2 * 20 - 21];
/*     latitudinal points */
    x1 = (d__1 = rla - (integer) rla, abs(d__1));
    x2 = 2. - x1;
/*     longitudinal points */
    y1 = (d__1 = rlo - (integer) rlo, abs(d__1));
    y2 = 18. - y1;
/*     X AND Y VALUES */
    x = x1 / (x1 + x2);
    y = y1 / (y1 + y2);
/*     INTERPOLATION */
    gmla = gm1 * (1 - x) * (1 - y) + gm2 * (1 - y) * x + gm3 * y * (1 - x) + 
	    gm4 * x * y;
/*     OUTPUT OF THE PROGRAM */
/*     From corrected geomagnetic latitude from North Pole */
/*     to "normal"  geomagnetic latitude. */
    *rgma = 90. - gmla;
    return 0;
} /* conver_ */



/* Subroutine */ int storm_(integer *ap, doublereal *rga, doublereal *rgo, 
	integer *coor, doublereal *rgma, integer *ut, integer *doy, 
	doublereal *cf)
{
    /* Initialized data */

    static doublereal c4[20] = { 0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0. };
    static doublereal c3[20] = { 0.,0.,0.,0.,0.,-9.44e-12,0.,3.04e-12,0.,
	    9.32e-12,-1.07e-11,0.,0.,0.,1.09e-11,0.,0.,0.,0.,-1.01e-11 };
    static doublereal c2[20] = { 1.16e-8,0.,0.,-1.46e-8,0.,9.86e-8,2.25e-8,
	    -1.67e-8,-1.62e-8,-9.42e-8,1.17e-7,4.32e-8,3.97e-8,3.13e-8,
	    -8.04e-8,3.91e-8,2.58e-8,3.45e-8,4.76e-8,1.13e-7 };
    static doublereal c1[20] = { -9.17e-5,-1.37e-5,0.,7.14e-5,0.,-3.21e-4,
	    -1.66e-4,-4.1e-5,1.36e-4,2.29e-4,-3.89e-4,-3.08e-4,-2.81e-4,
	    -1.9e-4,4.76e-5,-2.8e-4,-2.07e-4,-2.91e-4,-3.3e-4,-4.04e-4 };
    static doublereal c0[20] = { 1.0136,1.0478,1.,1.0258,1.,1.077,1.0543,
	    1.0103,.99927,.96876,1.0971,1.0971,1.0777,1.1134,1.0237,1.0703,
	    1.0248,1.0945,1.1622,1.1393 };
    static doublereal fap[36] = { 0.,0.,.037037037,.074074074,.111111111,
	    .148148148,.185185185,.222222222,.259259259,.296296296,.333333333,
	    .37037037,.407407407,.444444444,.481481481,.518518519,.555555556,
	    .592592593,.62962963,.666666667,.703703704,.740740741,.777777778,
	    .814814815,.851851852,.888888889,.925925926,.962962963,1.,
	    .66666667,.33333334,0.,.333333,.666666,1.,.7 };
    static integer code[48]	/* was [8][6] */ = { 3,4,5,4,3,2,1,2,3,2,1,2,
	    3,4,5,4,8,7,6,7,8,9,10,9,13,12,11,12,13,14,15,14,18,17,16,17,18,
	    19,20,19,18,17,16,17,18,19,20,19 };

    /* System generated locals */
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle();

    /* Local variables */
    static integer i__, j, k, l1, l2, n1, n2, n3, n4, s1, s2;
    static doublereal rl, rs, cf1, cf2, cf3, cf4;
    static integer ape[39];
    static doublereal rap, cf300, facl, facs, rapf;
    static integer dayno;
    extern /* Subroutine */ int conver_(doublereal *, doublereal *, 
	    doublereal *);

    /* Fortran I/O blocks */
    static cilist io___832 = { 0, 6, 0, 0, 0 };
    static cilist io___833 = { 0, 6, 0, 0, 0 };
    static cilist io___834 = { 0, 6, 0, 0, 0 };
    static cilist io___835 = { 0, 6, 0, 0, 0 };
    static cilist io___839 = { 0, 6, 0, 0, 0 };
    static cilist io___840 = { 0, 6, 0, 0, 0 };
    static cilist io___841 = { 0, 6, 0, 0, 0 };
    static cilist io___842 = { 0, 6, 0, 0, 0 };
    static cilist io___845 = { 0, 6, 0, 0, 0 };
    static cilist io___846 = { 0, 6, 0, 0, 0 };
    static cilist io___847 = { 0, 6, 0, 0, 0 };
    static cilist io___848 = { 0, 6, 0, 0, 0 };
    static cilist io___849 = { 0, 6, 0, 0, 0 };
    static cilist io___850 = { 0, 6, 0, 0, 0 };
    static cilist io___851 = { 0, 6, 0, 0, 0 };
    static cilist io___852 = { 0, 6, 0, 0, 0 };
    static cilist io___853 = { 0, 6, 0, 0, 0 };
    static cilist io___854 = { 0, 6, 0, 0, 0 };


/* ---------------------------------------------------------------------- */
/*      Fortran code to obtain the foF2 storm-time correction factor at */
/*      a given location and time, using the current and the 12 previous */
/*      ap values as input. */

/*      ap ---> (13 elements integer array). Array with the preceeding */
/*              13 value of the 3-hourly ap index. The 13th value */
/*              in the array will contain the ap at the UT of interest, */
/*              the 12th value will contain the 1st three hourly interval */
/*              preceeding the time of interest, and so on to the 1st */
/*              ap value at the earliest time. */
/*     coor --> (integer). If coor = 2, rga should contain the */
/*                         geomagnetic latitude. */
/*                         If coor = 1, rga should contain the */
/*                         geographic latitude. */
/*     rga ---> (real, -90 to 90) geographic or geomagnetic latitude. */
/*     rgo ---> (real, 0 to 360, positive east from Greenwich.) */
/*                           geographic longitude, only used if coor=1. */
/*     ut  ---> (integer, hours 00 to 23) Universal Time of interest. */
/*     doy ---> (integer, 1 to 366)Day of the year. */
/*     cf  ---> (real) The output; the storm-time correction factor used */
/*              to scale foF2, foF2 * cf. */

/*     This model and computer code was developed by E. Araujo-Pradere, */
/*     T. Fuller-Rowell and M. Condrescu, SEC, NOAA, Boulder, USA */
/*     Ref: */
/*     T. Fuller-Rowell, E. Araujo-Pradere, and M. Condrescu, An */
/*       Empirical Ionospheric Storm-Time Ionospheric Correction Model, */
/*       Adv. Space Res. 8, 8, 15-24, 2000. */
/* ---------------------------------------------------------------------- */
/*     DIMENSIONS AND COEFFICIENTS VALUES */
    /* Parameter adjustments */
    --ap;

    /* Function Body */
/*      CALLING THE PROGRAM TO CONVERT TO GEOMAGNETIC COORDINATES */
    if (*coor == 1) {
	conver_(rga, rgo, rgma);
    } else if (*coor == 2) {
	*rgma = *rga;
    } else {
	s_wsle(&io___832);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	s_wsle(&io___833);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	s_wsle(&io___834);
	do_lio(&c__9, &c__1, "   Wrong Coordinates Selection -------- >>", (
		ftnlen)42);
	do_lio(&c__3, &c__1, (char *)&(*coor), (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___835);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	goto L100;
    }
/* FROM 3-HOURLY TO HOURLY ap (New, interpolates between the three hourly ap values) */
    ape[0] = ap[1];
    ape[1] = ap[1];
    ape[37] = ap[13];
    ape[38] = ap[13];
    for (k = 1; k <= 13; ++k) {
	i__ = k * 3 - 1;
	ape[i__ - 1] = ap[k];
    }
    for (k = 1; k <= 12; ++k) {
	i__ = k * 3;
	ape[i__ - 1] = (integer) (((ap[k] << 1) + ap[k + 1]) / 3.);
    }
    for (k = 2; k <= 13; ++k) {
	i__ = k * 3 - 2;
	ape[i__ - 1] = (integer) ((ap[k - 1] + (ap[k] << 1)) / 3.);
    }
/*     FROM 3-HOURLY TO HOURLY ap (old version without interpolation) */
/*      i = 1 */
/*      DO 10 k = 1,13 */
/*         DO j = 1,3 */
/*            ape(i) = ap(k) */
/*            i = i + 1 */
/*            END DO */
/* 10    CONTINUE */
/*     TO OBTAIN THE INTEGRAL OF ap. */
/*     INTEGRAL OF ap */
    if (*ut == 24) {
	*ut = 0;
    }
    if (*ut == 0 || *ut == 3 || *ut == 6 || *ut == 9 || *ut == 12 || *ut == 
	    15 || *ut == 18 || *ut == 21) {
	k = 1;
    } else if (*ut == 1 || *ut == 4 || *ut == 7 || *ut == 10 || *ut == 13 || *
	    ut == 16 || *ut == 19 || *ut == 22) {
	k = 2;
    } else if (*ut == 2 || *ut == 5 || *ut == 8 || *ut == 11 || *ut == 14 || *
	    ut == 17 || *ut == 20 || *ut == 23) {
	k = 3;
    } else {
	s_wsle(&io___839);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	s_wsle(&io___840);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	s_wsle(&io___841);
	do_lio(&c__9, &c__1, "  Wrong Universal Time value -------- >>", (
		ftnlen)40);
	do_lio(&c__3, &c__1, (char *)&(*ut), (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___842);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	goto L100;
    }
    rap = 0.;
    for (j = 1; j <= 36; ++j) {
	rap += fap[j - 1] * ape[k + j - 1];
    }
    if (rap <= 200.) {
	*cf = 1.;
	goto L100;
    }
    if (*doy > 366 || *doy < 1) {
	s_wsle(&io___845);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	s_wsle(&io___846);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	s_wsle(&io___847);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	s_wsle(&io___848);
	do_lio(&c__9, &c__1, "      Wrong Day of Year value --- >>", (ftnlen)
		36);
	do_lio(&c__3, &c__1, (char *)&(*doy), (ftnlen)sizeof(integer));
	e_wsle();
	s_wsle(&io___849);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	goto L100;
    }
    if (*rgma > 90. || *rgma < -90.) {
	s_wsle(&io___850);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	s_wsle(&io___851);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	s_wsle(&io___852);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	s_wsle(&io___853);
	do_lio(&c__9, &c__1, "   Wrong GEOMAGNETIC LATITUDE value --- >>", (
		ftnlen)42);
	do_lio(&c__5, &c__1, (char *)&(*rgma), (ftnlen)sizeof(doublereal));
	e_wsle();
	s_wsle(&io___854);
	do_lio(&c__9, &c__1, " ", (ftnlen)1);
	e_wsle();
	goto L100;
    }
/*      write(6,*)rgma */
    dayno = *doy;
    if (*rgma < 0.) {
	dayno = *doy + 172;
	if (dayno > 365) {
	    dayno += -365;
	}
    }
    if (dayno >= 82) {
	rs = (dayno - 82.) / 45.6 + 1.;
    }
    if (dayno < 82) {
	rs = (dayno + 283.) / 45.6 + 1.;
    }
    s1 = (integer) rs;
    facs = rs - s1;
    s2 = s1 + 1;
    if (s2 == 9) {
	s2 = 1;
    }
/*      write(6,*)s1,s2,rs */
    *rgma = abs(*rgma);
    rl = (*rgma + 10.) / 20. + 1;
    if (rl == 6.) {
	rl = 5.9;
    }
    l1 = (integer) rl;
    facl = rl - l1;
    l2 = l1 + 1;
/*      write(6,*)l1,l2,rl */
/*     FACTORS CALCULATIONS */
    if (rap < 300.) {
	rapf = 300.;
	n1 = code[s1 + (l1 << 3) - 9];
/* Computing 4th power */
	d__1 = rapf, d__1 *= d__1;
/* Computing 3rd power */
	d__2 = rapf;
/* Computing 2nd power */
	d__3 = rapf;
	cf1 = c4[n1 - 1] * (d__1 * d__1) + c3[n1 - 1] * (d__2 * (d__2 * d__2))
		 + c2[n1 - 1] * (d__3 * d__3) + c1[n1 - 1] * rapf + c0[n1 - 1]
		;
	n2 = code[s1 + (l2 << 3) - 9];
/* Computing 4th power */
	d__1 = rapf, d__1 *= d__1;
/* Computing 3rd power */
	d__2 = rapf;
/* Computing 2nd power */
	d__3 = rapf;
	cf2 = c4[n2 - 1] * (d__1 * d__1) + c3[n2 - 1] * (d__2 * (d__2 * d__2))
		 + c2[n2 - 1] * (d__3 * d__3) + c1[n2 - 1] * rapf + c0[n2 - 1]
		;
	n3 = code[s2 + (l1 << 3) - 9];
/* Computing 4th power */
	d__1 = rapf, d__1 *= d__1;
/* Computing 3rd power */
	d__2 = rapf;
/* Computing 2nd power */
	d__3 = rapf;
	cf3 = c4[n3 - 1] * (d__1 * d__1) + c3[n3 - 1] * (d__2 * (d__2 * d__2))
		 + c2[n3 - 1] * (d__3 * d__3) + c1[n3 - 1] * rapf + c0[n3 - 1]
		;
	n4 = code[s2 + (l2 << 3) - 9];
/* Computing 4th power */
	d__1 = rapf, d__1 *= d__1;
/* Computing 3rd power */
	d__2 = rapf;
/* Computing 2nd power */
	d__3 = rapf;
	cf4 = c4[n4 - 1] * (d__1 * d__1) + c3[n4 - 1] * (d__2 * (d__2 * d__2))
		 + c2[n4 - 1] * (d__3 * d__3) + c1[n4 - 1] * rapf + c0[n4 - 1]
		;
/*     INTERPOLATION */
	cf300 = cf1 * (1 - facs) * (1 - facl) + cf2 * (1 - facs) * facl + cf3 
		* facs * (1 - facl) + cf4 * facs * facl;
	*cf = (cf300 - 1.) * rap / 100. - cf300 * 2. + 3.;
	goto L100;
    }
    n1 = code[s1 + (l1 << 3) - 9];
/*      write(6,*)n1 */
/* Computing 4th power */
    d__1 = rap, d__1 *= d__1;
/* Computing 3rd power */
    d__2 = rap;
/* Computing 2nd power */
    d__3 = rap;
    cf1 = c4[n1 - 1] * (d__1 * d__1) + c3[n1 - 1] * (d__2 * (d__2 * d__2)) + 
	    c2[n1 - 1] * (d__3 * d__3) + c1[n1 - 1] * rap + c0[n1 - 1];
    n2 = code[s1 + (l2 << 3) - 9];
/* Computing 4th power */
    d__1 = rap, d__1 *= d__1;
/* Computing 3rd power */
    d__2 = rap;
/* Computing 2nd power */
    d__3 = rap;
    cf2 = c4[n2 - 1] * (d__1 * d__1) + c3[n2 - 1] * (d__2 * (d__2 * d__2)) + 
	    c2[n2 - 1] * (d__3 * d__3) + c1[n2 - 1] * rap + c0[n2 - 1];
    n3 = code[s2 + (l1 << 3) - 9];
/* Computing 4th power */
    d__1 = rap, d__1 *= d__1;
/* Computing 3rd power */
    d__2 = rap;
/* Computing 2nd power */
    d__3 = rap;
    cf3 = c4[n3 - 1] * (d__1 * d__1) + c3[n3 - 1] * (d__2 * (d__2 * d__2)) + 
	    c2[n3 - 1] * (d__3 * d__3) + c1[n3 - 1] * rap + c0[n3 - 1];
    n4 = code[s2 + (l2 << 3) - 9];
/* Computing 4th power */
    d__1 = rap, d__1 *= d__1;
/* Computing 3rd power */
    d__2 = rap;
/* Computing 2nd power */
    d__3 = rap;
    cf4 = c4[n4 - 1] * (d__1 * d__1) + c3[n4 - 1] * (d__2 * (d__2 * d__2)) + 
	    c2[n4 - 1] * (d__3 * d__3) + c1[n4 - 1] * rap + c0[n4 - 1];
/*     INTERPOLATION */
    *cf = cf1 * (1 - facs) * (1 - facl) + cf2 * (1 - facs) * facl + cf3 * 
	    facs * (1 - facl) + cf4 * facs * facl;
L100:
    return 0;
} /* storm_ */



/* **************************************************************************** */

/* Subroutine */ int vdrift_(doublereal *xt, doublereal *xl, doublereal *
	param, doublereal *y)
{
    /* Initialized data */

    static integer index_t__ = 13;
    static integer index_l__ = 8;
    static integer nfunc = 6;
    static doublereal coeff1[594] = { -10.80592,-9.63722,-11.52666,-.05716,
	    -.06288,.03564,-5.80962,-7.86988,-8.50888,-.05194,-.05798,-.00138,
	    2.09876,-19.99896,-5.11393,-.0537,-.06585,.03171,-10.22653,
	    -3.62499,-14.85924,-.04023,-.0119,-.09656,-4.8518,-26.26264,
	    -6.20501,-.05342,-.05174,.02419,-13.98936,-18.10416,-9.30503,
	    -.01969,-.03132,-.01984,-18.36633,-24.44898,-16.69001,.02033,
	    -.03414,-.02062,-20.27621,-16.95623,-36.58234,.01445,-.02044,
	    -.08297,1.4445,5.53004,4.55166,-.02356,-.04267,.05023,5.50589,
	    7.05381,1.94387,-.03147,-.03548,.01166,3.24165,10.05002,4.26218,
	    -.03419,-.02651,.07456,7.02218,.06708,-11.31012,-.03252,-.01021,
	    -.09008,-3.47588,-2.82534,-4.17668,-.03719,-.01519,.06507,
	    -4.02607,-11.19563,-10.52923,-.00592,-.01286,-.00477,-11.47478,
	    -9.57758,-10.36887,.04555,-.02249,.00528,-14.19283,7.86422,
	    -8.76821,.05758,-.02398,-.04075,14.5889,36.63322,27.57497,.01358,
	    -.02316,.04723,12.53122,29.38367,21.40356,-7.1e-4,-.00553,.01484,
	    18.64421,26.27327,18.32704,.00578,.03349,.11249,4.53014,6.15099,
	    7.41935,-.0286,-.00395,-.08394,14.29422,9.77569,2.85689,-.00107,
	    .04263,.10739,7.17246,4.40242,-1.00794,8.9e-4,.01436,.00626,
	    7.75487,5.01928,4.36908,.03952,-.00614,.03039,10.25556,8.82631,
	    24.21745,.05492,-.02968,.00177,21.86648,24.03218,39.82008,.0049,
	    -.01281,-.01715,19.18547,23.97403,34.44242,.01978,.01564,-.02434,
	    26.30614,14.22662,31.16844,.06495,.1959,.05631,21.09354,25.56253,
	    29.91629,-.04397,-.08079,-.07903,28.30202,16.80567,38.63945,
	    .05864,.16407,.07622,22.68528,25.91119,40.45979,-.03185,-.01039,
	    -.01206,31.98703,24.46271,38.13028,-.08738,-.0028,.01322,46.67387,
	    16.80171,22.7719,-.13643,-.05277,-.01982,13.87476,20.52521,
	    5.22899,.00485,-.04357,.0997,21.46928,13.55871,10.23772,-.04457,
	    .01307,.06589,16.18181,16.0296,9.28661,-.01225,.14623,-.0157,
	    18.16289,-1.5823,14.54986,-.00375,-8.7e-4,.04991,10.00292,
	    11.82653,.44417,-.00768,.1594,-.01775,12.15362,5.65843,-1.94855,
	    -.00689,.03851,.04851,-1.25167,9.05439,.74164,.01065,.03153,
	    .02433,-15.46799,18.23132,27.4532,.00899,-1.7e-4,.03385,2.70396,
	    -.87077,6.11476,-8.1e-4,.05167,-.08932,3.21321,-1.06622,5.43623,
	    .01942,.05449,-.03084,17.79267,-3.44694,7.10702,.04734,-.00945,
	    .11516,.46435,6.78467,4.27231,-.02122,.10922,-.03331,15.31708,
	    1.70927,7.99584,.07462,.07515,.08934,4.19893,6.01231,8.04861,
	    .04023,.14767,-.04308,9.97541,5.99412,5.93588,.06611,.12144,
	    -.02124,13.02837,10.2995,-4.862,.04521,.10715,-.05465,5.26779,
	    7.09019,1.76617,.09339,.22256,.09222,9.1781,5.27558,5.45022,
	    .14749,.11616,.10418,9.26391,4.19982,12.6625,.11334,.02532,.18919,
	    13.18695,6.06564,11.87835,.26347,.02858,.14801,10.08476,6.14899,
	    17.62618,.09331,.08832,.28208,10.75302,7.09244,13.90643,.09556,
	    .16652,.22751,6.70338,11.97698,18.51413,.15873,.18936,.15705,
	    5.68102,23.81606,20.65174,.1993,.15645,.08151,29.61644,5.49433,
	    48.90934,.7071,.40791,.26325,17.11994,19.6538,44.8881,.4551,
	    .41689,.22398,8.457,34.54442,27.25364,.40867,.37223,.22374,
	    -2.30305,32.0066,47.75799,.02178,.43626,.30187,8.98134,33.0182,
	    33.09674,.33703,.33242,.41156,14.27619,20.70858,50.10005,.30115,
	    .3257,.45061,14.44685,16.14272,45.40065,.37552,.31419,.30129,
	    6.19718,18.89559,28.24927,.08864,.41627,.19993,7.70847,-2.36281,
	    -21.41381,.13766,.05113,-.11631,-9.07236,3.76797,-20.49962,.03343,
	    .0863,.00188,-8.58113,5.06009,-6.23262,.04967,.03334,.24214,
	    -27.85742,8.34615,-27.72532,-.08935,.15905,-.03655,2.77234,.14626,
	    -4.01786,.22338,-.04478,.1865,5.61364,-3.82235,-16.72282,.26456,
	    -.03119,-.08376,13.35847,-6.11518,-16.50327,.28957,-.01345,
	    -.19223,-5.3729,-.09562,-27.27889,.00266,.22823,-.35585,-15.29676,
	    -18.36622,-24.62948,-.31299,-.23832,-.08463,-23.37099,-13.69954,
	    -26.71177,-.19654,-.18522,-.20679,-26.33762,-15.96657,-42.51953,
	    -.13575,-.00329,-.28355,-25.4214,-14.14291,-21.91748,-.2096,
	    -.19176,-.32593,-23.36042,-23.89895,-46.0527,-.10336,.0303,
	    -.21839,-19.46259,-21.27918,-32.38143,-.17673,-.15484,-.11226,
	    -19.06169,-21.1324,-34.01677,-.25497,-.16878,-.11004,-18.39463,
	    -16.11516,-19.55804,-.19834,-.23271,-.25699,-19.93482,-17.56433,
	    -18.58818,.06508,-.18075,.02796,-23.64078,-18.77269,-22.77715,
	    -.02456,-.12238,.02959,-12.44508,-21.06941,-19.36011,.02746,
	    -.16329,.19792,-26.34187,-19.78854,-24.06651,-.07299,-.03082,
	    -.03535,-10.71667,-26.04401,-16.59048,.0285,-.0968,.15143,
	    -18.40481,-23.3777,-16.3145,-.03989,-.00729,-.01688,-9.68886,
	    -20.59304,-18.46657,.01092,-.07901,.03422,-.06685,-19.2459,
	    -29.35494,.12265,-.24792,.05978,-15.32341,-9.0732,-13.76101,
	    -.17018,-.15122,-.06144,-14.68939,-14.82251,-13.65846,-.11173,
	    -.1441,-.07133,-18.38628,-18.94631,-19.00893,-.08062,-.14481,
	    -.12949,-16.15328,-17.40999,-14.08705,-.08485,-.06896,-.11583,
	    -14.50295,-16.91671,-25.25793,-.06814,-.13727,-.12213,-10.92188,
	    -14.10852,-24.43877,-.09375,-.11638,-.09053,-11.64716,-14.9202,
	    -19.99063,-.14792,-.08681,-.12085,-24.09766,-16.14519,-8.05683,
	    -.24065,-.05877,-.23726,-25.18396,-15.02034,-15.50531,-.12236,
	    -.0961,-.00529,-15.27905,-19.36708,-12.94046,-.08571,-.0956,
	    -.03544,-7.48927,-16.00753,-13.02842,-.07862,-.1011,-.05807 };
    static doublereal coeff2[30] = { -13.06383,-27.98698,-18.80004,-.05875,
	    -.03737,-.11214,-13.6737,-16.44925,-16.12632,-.07228,-.09322,
	    -.05652,-22.61245,-21.24717,-18.09933,-.05197,-.07477,-.05235,
	    -27.09189,-21.85181,-20.34676,-.05123,-.05683,-.07214,-27.09561,
	    -22.76383,-25.41151,-.10272,-.02058,-.1672 };

    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Local variables */
    extern /* Subroutine */ int g_(doublereal *, doublereal *, doublereal *);
    static integer i__, j;
    extern doublereal bspl4_time__(integer *, doublereal *), bspl4_long__(
	    integer *, doublereal *);
    static integer il, kk, ind;
    static doublereal bspl4, coeff[624], funct[6];

/* ------------------------------------------------------------------- */
/*       SUBROUTINE CALCULATES EQUATORIAL VERTICAL DRIFT AS DESCRIBED */
/*       IN SCHERLIESS AND FEJER, JGR, 104, 6829-6842, 1999 */

/*       INPUT:   XT: SOLAR LOCAL TIME  [h] */
/*                XL: GEOGRAPHIC LONGITUDE (+ EAST) [degrees] */

/*           PARAM: 2-DIM ARRAY (DOY,F10.7CM) */
/*                  DOY     :Day of Year has to run from 1 to 365(366) */
/*                  F10.7cm : F10.7cm solar flux (daily value) */

/*       OUTPUT:   Y: EQUATORIAL VERTICAL DRIFT [m/s] */

/* ------------------------------------------------------------------- */
/*        IMPLICIT REAL*8 (A-H,O-Z) */
/*        real*8 param(2),coeff(624),coeff1(594),coeff2(30),funct(6) */
/*        real*8 xt,xl,y */
/*        real*8 bspl4,bspl4_time,bspl4_long */
    /* Parameter adjustments */
    --param;

    /* Function Body */
    for (i__ = 1; i__ <= 594; ++i__) {
	coeff[i__ - 1] = coeff1[i__ - 1];
    }
    for (i__ = 1; i__ <= 30; ++i__) {
	coeff[i__ + 593] = coeff2[i__ - 1];
    }
    g_(&param[1], funct, xl);
    *y = 0.;
    i__1 = index_t__;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = index_l__;
	for (il = 1; il <= i__2; ++il) {
	    kk = index_l__ * (i__ - 1) + il;
	    i__3 = nfunc;
	    for (j = 1; j <= i__3; ++j) {
		ind = nfunc * (kk - 1) + j;
		bspl4 = bspl4_time__(&i__, xt) * bspl4_long__(&il, xl);
		*y += bspl4 * funct[j - 1] * coeff[ind - 1];
	    }
	}
    }
    return 0;
} /* vdrift_ */



/*        real*8 function bspl4_time(i,x1) */
doublereal bspl4_time__(integer *i__, doublereal *x1)
{
    /* Initialized data */

    static doublereal t_t__[40] = { 0.,2.75,4.75,5.5,6.25,7.25,10.,14.,17.25,
	    18.,18.75,19.75,21.,24.,26.75,28.75,29.5,30.25,31.25,34.,38.,
	    41.25,42.,42.75,43.75,45.,48.,50.75,52.75,53.5,54.25,55.25,58.,
	    62.,65.25,66.,66.75,67.75,69.,72. };

    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val;

    /* Local variables */
    static doublereal b[400]	/* was [20][20] */;
    static integer j, k;
    static doublereal x;
    static integer order;

/*       ************************************************* */
/*        implicit REAL*8 (A-H,O-Z) */
/*        real*8 t_t(0:39) */
/*        real*8 x,b(20,20),x1 */
    order = 4;
    x = *x1;
    if (*i__ >= 0) {
	if (x < t_t__[*i__]) {
	    x += 24;
	}
    }
    i__1 = *i__ + order - 1;
    for (j = *i__; j <= i__1; ++j) {
	if (x >= t_t__[j] && x < t_t__[j + 1]) {
	    b[j - 1] = 1.;
	} else {
	    b[j - 1] = 0.;
	}
    }
    i__1 = order;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *i__ + order - j;
	for (k = *i__; k <= i__2; ++k) {
	    b[k + j * 20 - 21] = (x - t_t__[k]) / (t_t__[k + j - 1] - t_t__[k]
		    ) * b[k + (j - 1) * 20 - 21];
	    b[k + j * 20 - 21] += (t_t__[k + j] - x) / (t_t__[k + j] - t_t__[
		    k + 1]) * b[k + 1 + (j - 1) * 20 - 21];
	}
    }
    ret_val = b[*i__ + order * 20 - 21];
    return ret_val;
} /* bspl4_time__ */



/*        real*8 function bspl4_long(i,x1) */
doublereal bspl4_long__(integer *i__, doublereal *x1)
{
    /* Initialized data */

    static doublereal t_l__[25] = { 0.,10.,100.,190.,200.,250.,280.,310.,360.,
	    370.,460.,550.,560.,610.,640.,670.,720.,730.,820.,910.,920.,970.,
	    1e3,1030.,1080. };

    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val;

    /* Local variables */
    static doublereal b[400]	/* was [20][20] */;
    static integer j, k;
    static doublereal x;
    static integer order;

/*       ************************************************* */
/*       implicit real*8 (A-H,O-Z) */
/*        real*8 t_l(0:24) */
/*        real*8 x,b(20,20),x1 */
    order = 4;
    x = *x1;
    if (*i__ >= 0) {
	if (x < t_l__[*i__]) {
	    x += 360;
	}
    }
    i__1 = *i__ + order - 1;
    for (j = *i__; j <= i__1; ++j) {
	if (x >= t_l__[j] && x < t_l__[j + 1]) {
	    b[j - 1] = 1.;
	} else {
	    b[j - 1] = 0.;
	}
    }
    i__1 = order;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *i__ + order - j;
	for (k = *i__; k <= i__2; ++k) {
	    b[k + j * 20 - 21] = (x - t_l__[k]) / (t_l__[k + j - 1] - t_l__[k]
		    ) * b[k + (j - 1) * 20 - 21];
	    b[k + j * 20 - 21] += (t_l__[k + j] - x) / (t_l__[k + j] - t_l__[
		    k + 1]) * b[k + 1 + (j - 1) * 20 - 21];
	}
    }
    ret_val = b[*i__ + order * 20 - 21];
    return ret_val;
} /* bspl4_long__ */



/* Subroutine */ int g_(doublereal *param, doublereal *funct, doublereal *x)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal a;
    static integer i__;
    static doublereal flux, sigma, cflux, gauss;

/*       ************************************************* */
/*        implicit real*8 (A-H,O-Z) */
/*        real*8 param(2),funct(6) */
/*        real*8 x,a,sigma,gauss,flux,cflux */
/*       ************************************************* */
    /* Parameter adjustments */
    --funct;
    --param;

    /* Function Body */
    flux = param[2];
    if (param[2] <= 75.) {
	flux = 75.;
    }
    if (param[2] >= 230.) {
	flux = 230.;
    }
    cflux = flux;
    a = 0.;
    if (param[1] >= 120. && param[1] <= 240.) {
	a = 170.;
    }
    if (param[1] >= 120. && param[1] <= 240.) {
	sigma = 60.;
    }
    if (param[1] <= 60. || param[1] >= 300.) {
	a = 170.;
    }
    if (param[1] <= 60. || param[1] >= 300.) {
	sigma = 40.;
    }
    if (flux <= 95. && a != 0.) {
/* Computing 2nd power */
	d__1 = *x - a;
/* Computing 2nd power */
	d__2 = sigma;
	gauss = exp(d__1 * d__1 * -.5 / (d__2 * d__2));
	cflux = gauss * 95. + (1 - gauss) * flux;
    }
/*       ************************************************* */
/*       ************************************************* */
    for (i__ = 1; i__ <= 6; ++i__) {
	funct[i__] = 0.;
    }
/*       ************************************************* */
/*       ************************************************* */
    if (param[1] >= 135. && param[1] <= 230.) {
	funct[1] = 1.;
    }
    if (param[1] <= 45. || param[1] >= 320.) {
	funct[2] = 1.;
    }
    if (param[1] > 75. && param[1] < 105.) {
	funct[3] = 1.;
    }
    if (param[1] > 260. && param[1] < 290.) {
	funct[3] = 1.;
    }
/*       ************************************************* */
    if (param[1] >= 45. && param[1] <= 75.) {
/* W-E */
	funct[2] = 1. - (param[1] - 45.) / 30.;
	funct[3] = 1 - funct[2];
    }
    if (param[1] >= 105. && param[1] <= 135.) {
/* E-S */
	funct[3] = 1. - (param[1] - 105.) / 30.;
	funct[1] = 1 - funct[3];
    }
    if (param[1] >= 230. && param[1] <= 260.) {
/* S-E */
	funct[1] = 1. - (param[1] - 230.) / 30.;
	funct[3] = 1 - funct[1];
    }
    if (param[1] >= 290. && param[1] <= 320.) {
/* E-W */
	funct[3] = 1. - (param[1] - 290.) / 30.;
	funct[2] = 1 - funct[3];
    }
/*       ************************************************* */
    funct[4] = (cflux - 140) * funct[1];
    funct[5] = (cflux - 140) * funct[2];
    funct[6] = (flux - 140) * funct[3];
/*       ************************************************* */
    return 0;
} /* g_ */



/* Subroutine */ int stormvd_(integer *flag__, integer *ip, doublereal *ae, 
	doublereal *slt, doublereal *promptvd, doublereal *dynamovd, 
	doublereal *vd)
{
    /* Initialized data */

    static doublereal coff1[45]	/* was [5][9] */ = { .0124,-.0168,-.0152,
	    -.0174,-.0704,-.009,-.0022,-.0107,.0152,-.0674,.0275,.0051,-.0132,
	    .002,-.011,-.0022,.0044,.0095,.0036,-.0206,.0162,7e-4,.0085,-.014,
	    .0583,.0181,.0185,-.0109,-.0031,-.0427,-.0057,2e-4,.0086,.0149,
	    .2637,-.0193,.0035,.0117,.0099,.3002,-.0492,-.0201,.0338,.0099,
	    .0746 };
    static doublereal coff15[54]	/* was [6][9] */ = { .0177,.0118,
	    -6e-4,-.0152,-.0174,-.0704,.0051,-.0074,-.0096,-.0107,.0152,
	    -.0674,.0241,.0183,.0122,-.0132,.002,-.011,.0019,-.001,1e-4,.0095,
	    .0036,-.0206,.017,.0183,.0042,.0085,-.014,.0583,.0086,.0189,.02,
	    -.0109,-.0031,-.0427,-.007,-.0053,-.009,.0086,.0149,.2637,-.0326,
	    -.0101,.0076,.0117,.0099,.3002,-.047,-.0455,-.0274,.0338,.0099,
	    .0746 };

    /* Builtin functions */
    double exp(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle();

    /* Local variables */
    static integer i__, j;
    extern doublereal bspl4_ptime__(integer *, doublereal *);
    static doublereal ae1_6__, alfa, beta, ae1_12__, aed1_6__, aed7_12__, 
	    ae7_12s__, aed22_28__, daet_30__, aed1_6s__, daet_90__, daet_75__,
	     aed7_12s__, aed22_28p__, aed22_28s__, daet_7p5__;

    /* Fortran I/O blocks */
    static cilist io___929 = { 0, 6, 0, 0, 0 };


/* ******************************************************************* */
/*  Empirical vertical disturbance drifts model */
/*  After Fejer and Scherliess, JGR, 102, 24047-24056,1997 */
/* ********************************************************************* */
/*  INPUT: */
/*    AE: AE(in nT) in 1 hour or 15 minute resolution; */
/*    SLT: Local time(in hrs) for wanted Vd; */
/*  OUTPUT: */
/*    PromptVd: Prompt penetration vertical drifts at given conditions; */
/*    DynamoVd: Disturbane dynamo vertical drifts at given conditions; */
/*    Vd: PromptVd+DynamoVd; */
/* ********************************************************************* */
    /* Parameter adjustments */
    --ae;

    /* Function Body */
/* CCCCCCCCCCCCCCCC**Define to variables**CCCCCCCCCCCCCCCCCCCCC */
/* To 1 h time resolution: */
/* dAEt_30=AE(t)-AE(t-1 hour); */
/* dAEt_90=AE(t-1 hour)-AE(t-2 hour); */
/* C */
/* To 15 MIN time resolution : */
/* dAEt_7P5=AE(t)-AE(t-15min); */
/* dAEt_30=AE(t-15)-AE(t-45min); */
/* dAEt_75=AE(t-45)-AE(t-105min); */
/* C */
/*  Following variables are the same to two resolution: */
/* AE1_6=average(AE(1-6hours)); */
/* AE7_12=average(AE(7-12hours)); */
/* AE1_12=average(AE(1-12hours)); */
/* AEd1_6=average(X(AE(1-6hours)-130 nT)); */
/* AEd7_12=average(X(AE(7-12hours)-130 nT)); */
/* AEd1_12=average(X(AE(1-12hours)-130 nT)); */
/* AEd22_28=average(X(AE(22-28hours)-130 nT)); */
/* Here X(a)=a, a>0; =0, a<=0; */
/* Alfa=0,            AE1_6<200 nT; */
/*      AE1_6/100-2, 200 nT<AE1_6<200 nT; */
/*      1,            AE1_6>300 nT; */
/* Beta=exp(-AE1_12/90),  AE1_12>=70nT; */
/*      0.46,              AE1_12<70 nT; */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCccccccc */
/* ***************************************************** */
/* C        FLAG>0--> 1 h time resolution */
/* **************************************************** */
    if (*flag__ > 0) {

	daet_30__ = ae[*ip] - ae[*ip - 1];
	daet_90__ = ae[*ip - 1] - ae[*ip - 2];

	ae1_6__ = 0.;
	aed1_6__ = 0.;
	for (i__ = -1; i__ >= -6; --i__) {
	    ae1_6__ += ae[*ip + i__];
	    aed1_6s__ = ae[*ip + i__] - 130.;
	    if (aed1_6s__ <= 0.) {
		aed1_6s__ = 0.;
	    }
	    aed1_6__ += aed1_6s__;
	}
	ae1_6__ /= 6.;
	aed1_6__ /= 6.;

	aed7_12__ = 0.;
	for (i__ = -7; i__ >= -12; --i__) {
	    aed7_12s__ = ae[*ip + i__] - 130.;
	    if (aed7_12s__ <= 0.) {
		ae7_12s__ = 0.;
	    }
	    aed7_12__ += aed7_12s__;
	}
	aed7_12__ /= 6.;

	ae1_12__ = 0.;
	for (i__ = -1; i__ >= -12; --i__) {
	    ae1_12__ += ae[*ip + i__];
	}
	ae1_12__ /= 12.;

	aed22_28__ = 0.;
	for (i__ = -22; i__ >= -28; --i__) {
	    aed22_28s__ = ae[*ip + i__] - 130.;
	    if (aed22_28s__ <= 0.) {
		aed22_28s__ = 0.;
	    }
	    aed22_28__ += aed22_28s__;
	}
	aed22_28__ /= 7.;
	aed22_28p__ = aed22_28__ - 200.;
	if (aed22_28p__ <= 0.) {
	    aed22_28p__ = 0.;
	}
/* C */
	if (ae1_6__ > 300.) {
	    alfa = 1.;
	} else if (ae1_6__ > 200.) {
	    alfa = ae1_6__ / 100. - 2.;
	} else {
	    alfa = 0.;
	}
/* C */
	if (ae1_12__ >= 70.) {
	    beta = exp(-ae1_12__ / 90.);
	} else {
	    beta = .46;
	}
	*promptvd = 0.;
	for (j = 1; j <= 9; ++j) {
	    *promptvd += (coff1[j * 5 - 5] * daet_30__ + coff1[j * 5 - 4] * 
		    daet_90__) * bspl4_ptime__(&j, slt);
	}
	*dynamovd = 0.;
	for (j = 1; j <= 9; ++j) {
	    *dynamovd += (coff1[j * 5 - 3] * aed1_6__ + coff1[j * 5 - 2] * 
		    alfa * aed7_12__ + coff1[j * 5 - 1] * beta * aed22_28p__) 
		    * bspl4_ptime__(&j, slt);
	}
	*vd = *promptvd + *dynamovd;
	return 0;
/* 1 h time resolution end; */
/* ******************************************************************** */
/*                  15 min time resolution */
/* ******************************************************************** */
    } else {
	daet_7p5__ = ae[*ip] - ae[*ip - 1];
	daet_30__ = ae[*ip - 1] - ae[*ip - 3];
	daet_75__ = ae[*ip - 3] - ae[*ip - 7];
	ae1_6__ = 0.;
	aed1_6__ = 0.;
	for (i__ = -4; i__ >= -24; --i__) {
	    ae1_6__ += ae[*ip + i__];
	    aed1_6s__ = ae[*ip + i__] - 130.;
	    if (aed1_6s__ <= 0.) {
		aed1_6s__ = 0.;
	    }
	    aed1_6__ += aed1_6s__;
	}
	ae1_6__ /= 21.;
	aed1_6__ /= 21.;
/* C */
	aed7_12__ = 0.;
	for (i__ = -28; i__ >= -48; --i__) {
	    aed7_12s__ = ae[*ip + i__] - 130.;
	    if (aed7_12s__ <= 0.) {
		aed7_12s__ = 0.;
	    }
	    aed7_12__ += aed7_12s__;
	}
	aed7_12__ /= 21.;
/* C */
	ae1_12__ = 0.;
	for (i__ = -4; i__ >= -48; --i__) {
	    ae1_12__ += ae[*ip + i__];
	}
	ae1_12__ /= 45.;
/* C */
	aed22_28__ = 0.;
	for (i__ = -88; i__ >= -112; --i__) {
	    aed22_28s__ = ae[*ip + i__] - 130.;
	    if (aed22_28s__ <= 0.) {
		aed22_28s__ = 0.;
	    }
	    aed22_28__ += aed22_28s__;
	}
	aed22_28__ /= 25.;
	aed22_28p__ = aed22_28__ - 200.;
	if (aed22_28p__ <= 0.) {
	    aed22_28p__ = 0.;
	}
/*         AE1_6=0.0D0 */
/*         AEd1_6=0.0D0 */
/*         AEd7_12=0.0D0 */
/*         AEd22_28P=0.0D0 */
/*         AE1_12=0.0D0 */
/*         dAEt_7P5=400.D0 */
/*         dAEt_30=0.D0 */
/*         dAEt_75=0.D0 */
/* C */
	if (ae1_6__ > 300.) {
	    alfa = 1.;
	} else if (ae1_6__ > 200.) {
	    alfa = ae1_6__ / 100. - 2.;
	} else {
	    alfa = 0.;
	}
/* C */
	if (ae1_12__ >= 70.) {
	    beta = exp(-ae1_12__ / 90.);
	} else {
	    beta = .46;
	}
/* C */
	*promptvd = 0.;
	for (j = 1; j <= 9; ++j) {
	    *promptvd += (coff15[j * 6 - 6] * daet_7p5__ + coff15[j * 6 - 5] *
		     daet_30__ + coff15[j * 6 - 4] * daet_75__) * 
		    bspl4_ptime__(&j, slt);
	}
	*dynamovd = 0.;
	s_wsle(&io___929);
	do_lio(&c__5, &c__1, (char *)&aed1_6__, (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&aed7_12__, (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&aed22_28p__, (ftnlen)sizeof(doublereal))
		;
	do_lio(&c__5, &c__1, (char *)&alfa, (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&beta, (ftnlen)sizeof(doublereal));
	e_wsle();
	for (j = 1; j <= 9; ++j) {
	    *dynamovd += (coff15[j * 6 - 3] * aed1_6__ + coff15[j * 6 - 2] * 
		    alfa * aed7_12__ + coff15[j * 6 - 1] * beta * aed22_28p__)
		     * bspl4_ptime__(&j, slt);
	}
	*vd = *promptvd + *dynamovd;
    }
    return 0;
} /* stormvd_ */



doublereal bspl4_ptime__(integer *i__, doublereal *x1)
{
    /* Initialized data */

    static doublereal t_t__[28] = { 0.,3.,4.5,6.,9.,12.,15.,18.,21.,24.,27.,
	    28.5,30.,33.,36.,39.,42.,45.,48.,51.,52.5,54.,57.,60.,63.,66.,69.,
	    72. };

    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val;

    /* Local variables */
    static doublereal b[400]	/* was [20][20] */;
    static integer j, k;
    static doublereal x;
    static integer order;

/* ************************************************* */

    order = 4;
    x = *x1;
    if (*i__ >= 0) {
	if (x < t_t__[*i__]) {
	    x += 24;
	}
    }
    i__1 = *i__ + order - 1;
    for (j = *i__; j <= i__1; ++j) {
	if (x >= t_t__[j] && x < t_t__[j + 1]) {
	    b[j - 1] = 1.;
	} else {
	    b[j - 1] = 0.;
	}
    }

    i__1 = order;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *i__ + order - j;
	for (k = *i__; k <= i__2; ++k) {
	    b[k + j * 20 - 21] = (x - t_t__[k]) / (t_t__[k + j - 1] - t_t__[k]
		    ) * b[k + (j - 1) * 20 - 21];
	    b[k + j * 20 - 21] += (t_t__[k + j] - x) / (t_t__[k + j] - t_t__[
		    k + 1]) * b[k + 1 + (j - 1) * 20 - 21];
	}
    }
    ret_val = b[*i__ + order * 20 - 21];
    return ret_val;
} /* bspl4_ptime__ */


/* *************************************************************************** */

/* Subroutine */ int spreadf_brazil__(integer *idoy, integer *idiy, 
	doublereal *f107, doublereal *geolat, doublereal *osfbr)
{
    /* Initialized data */

    static doublereal coef_sfa__[684] = { .07,.13,0.,0.,0.,0.,0.,0.,0.,.05,
	    .04,.03,.06,.07,.02,.03,.03,.07,.06,.07,.21,.28,.34,.16,.12,0.,
	    .02,.02,.04,.05,.02,.11,.19,.31,.31,.11,.14,.16,.03,0.,0.,.02,0.,
	    0.,.05,.55,.61,.28,.26,.1,.15,.23,.07,.06,.03,.03,.41,.88,.89,.65,
	    .19,.18,.17,.1,.14,.15,.03,.14,.46,.72,.71,.53,.57,.38,.3,.14,0.,
	    .04,.03,.02,.21,.84,.87,.72,.79,.6,.65,.7,.29,.19,.19,.32,.73,.96,
	    .99,.84,.75,.78,.79,.7,.63,.24,.28,.53,.75,.77,.75,.85,.78,.51,
	    .59,.24,0.,.07,.05,.06,.33,.92,.96,.89,.9,.84,.86,.81,.33,.27,.23,
	    .47,.9,1.,1.,.96,.96,.89,.92,.84,.8,.27,.35,.61,.81,.93,.86,.97,
	    .84,.65,.75,.25,0.,.04,.08,.06,.53,.93,.96,.94,.95,.84,.91,.71,
	    .18,.17,.21,.42,.92,.99,.97,.92,.92,.93,.92,.67,.58,.21,.38,.55,
	    .83,.9,.89,.97,.84,.71,.91,.21,.02,.07,.03,.03,.6,.95,.96,.92,.97,
	    .91,.92,.67,.11,.08,.09,.23,.9,.99,.99,.96,.96,.93,.98,.63,.25,
	    .08,.12,.41,.79,.95,.98,.99,.86,.8,.94,.22,.02,.04,.03,.03,.63,
	    .95,.96,.94,.98,.9,.91,.59,.1,.04,.07,.15,.83,.97,.97,.9,.92,.93,
	    .95,.57,.12,.03,.05,.23,.74,.94,.94,.99,.84,.84,.9,.24,.02,.07,
	    .07,.03,.6,.95,.96,.97,.93,.82,.83,.51,.08,.07,.09,.09,.71,.95,
	    .92,.87,.91,.91,.89,.5,.14,.03,.06,.14,.61,.84,.89,.94,.77,.82,
	    .84,.34,.1,.11,.12,.06,.43,.87,.94,.97,.91,.77,.68,.42,.06,.08,.1,
	    .04,.51,.78,.71,.77,.85,.88,.77,.35,.16,.05,.08,.15,.53,.7,.6,.89,
	    .85,.71,.72,.26,.16,.17,.08,.15,.38,.73,.91,.91,.89,.68,.53,.26,
	    .06,.12,.08,.09,.32,.63,.67,.77,.81,.79,.59,.21,.14,.03,.06,.09,
	    .23,.51,.34,.79,.88,.66,.59,.16,.18,.15,.16,.16,.33,.67,.75,.88,
	    .8,.64,.52,.16,.04,.09,.04,.09,.24,.47,.53,.5,.73,.69,.48,.11,.14,
	    .03,.03,.03,.2,.37,.28,.54,.81,.64,.49,.18,.12,.17,.16,.19,.31,
	    .57,.7,.83,.76,.57,.52,.13,.04,.06,.05,.08,.21,.49,.47,.39,.69,
	    .66,.43,.11,.1,.02,0.,.03,.16,.39,.24,.35,.77,.45,.39,.1,.1,.13,
	    .15,.18,.29,.57,.7,.69,.71,.49,.54,.2,.05,.06,.05,.06,.27,.42,.36,
	    .42,.61,.59,.5,.08,.06,.02,.03,.02,.16,.4,.17,.31,.68,.3,.28,.13,
	    .1,.16,.14,.08,.19,.5,.63,.62,.63,.45,.51,.13,.06,.07,.04,.06,.27,
	    .42,.28,.35,.68,.53,.57,.15,.05,0.,0.,.05,.31,.33,.18,.22,.59,.32,
	    .21,.06,.1,.16,.12,.1,.19,.41,.55,.54,.69,.43,.43,.15,.06,.05,.05,
	    .08,.29,.39,.23,.29,.57,.51,.56,.13,.06,0.,0.,.05,.34,.27,.19,.24,
	    .49,.16,.13,.09,.04,.11,.11,.05,.17,.32,.49,.49,.6,.42,.38,.11,
	    .06,.04,.07,.07,.25,.36,.21,.25,.65,.48,.53,.17,.05,0.,0.,.11,.29,
	    .14,.2,.22,.44,.16,.18,.07,.04,.04,.07,.03,.12,.23,.39,.43,.57,.4,
	    .35,.14,.06,.03,.04,.07,.18,.27,.14,.15,.45,.5,.5,.19,.06,0.,.02,
	    .05,.26,.19,.15,.18,.23,.09,.12,.06,.04,.02,.02,.02,.1,.03,.14,
	    .26,.39,.34,.22,.07,.03,0.,.04,.01,.15,.01,.04,.14,.41,.39,.35,
	    .13,.02,0.,0.,.06,.17,.07,.06,.14,.07,.02,.03,0.,0.,0.,0.,0.,0.,
	    .01,.03,.08,.19,.14,.14,0.,.03,.01,.02,0.,.09,0.,.01,0.,.18,.09,
	    .16,.08,.01,0.,.02,.02,.15,0.,.03,.04 };
    static doublereal coef_sfb__[684] = { 0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,.03,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,.02,.01,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,.01,0.,0.,0.,0.,
	    0.,.01,.01,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,.05,.03,0.,.02,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,.04,0.,.01,0.,0.,0.,.01,.01,.05,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,.04,0.,.03,.03,0.,.01,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,.01,0.,.01,.04,.04,.03,0.,.01,0.,.01,0.,.27,.14,.06,
	    .05,.04,.02,0.,0.,0.,0.,.04,.09,.48,.43,.27,.05,.04,.01,0.,0.,0.,
	    0.,0.,0.,.13,.16,.06,.26,.12,.29,.04,.01,.02,0.,.01,.08,.65,.56,
	    .45,.43,.42,.42,.09,0.,.02,0.,0.,.34,.67,.73,.72,.1,.05,.04,0.,
	    .01,0.,0.,0.,0.,.18,.39,.15,.61,.37,.51,.06,.01,.02,.01,.01,.18,
	    .72,.63,.8,.77,.66,.7,.19,0.,.02,.02,.02,.41,.68,.88,.85,.24,.11,
	    .08,0.,.01,0.,0.,0.,0.,.28,.51,.29,.75,.48,.57,.11,0.,.02,.01,.01,
	    .19,.77,.77,.88,.89,.81,.74,.21,.02,.02,.02,.02,.42,.71,.93,.95,
	    .49,.3,.19,0.,0.,0.,0.,.01,.06,.38,.64,.48,.86,.6,.62,.12,0.,.02,
	    .01,0.,.18,.81,.84,.94,.88,.79,.7,.26,.03,.02,.02,.02,.36,.61,.98,
	    .93,.6,.46,.31,.03,0.,.01,0.,0.,.09,.5,.71,.58,.9,.65,.66,.1,0.,
	    .02,.01,.02,.15,.69,.8,.86,.84,.75,.64,.09,.03,0.,0.,.04,.26,.54,
	    .78,.92,.62,.59,.44,.01,0.,.01,0.,0.,.13,.52,.77,.63,.84,.67,.63,
	    .11,0.,0.,.03,.03,.18,.65,.75,.84,.81,.63,.47,.06,.02,0.,0.,.05,
	    .14,.49,.76,.91,.58,.63,.47,.09,0.,.07,.01,.04,.15,.48,.68,.61,
	    .79,.63,.55,.12,.01,.01,.02,.05,.13,.57,.51,.63,.72,.54,.43,.11,
	    .02,0.,0.,.09,.16,.39,.59,.72,.46,.55,.39,.07,.01,.03,.03,.06,.15,
	    .37,.51,.5,.61,.43,.38,.11,.01,.03,.02,.03,.1,.38,.38,.6,.58,.42,
	    .38,.15,.02,0.,0.,.11,.13,.24,.41,.51,.36,.36,.21,.04,.04,.03,.06,
	    .05,.06,.26,.39,.43,.43,.31,.24,.09,.02,0.,.02,.02,.06,.24,.24,.4,
	    .53,.19,.28,.13,.02,.02,.02,.09,.13,.17,.24,.4,.32,.27,.17,.03,
	    .04,.02,.04,.03,.06,.13,.34,.36,.42,.31,.2,.09,.03,0.,.02,.01,.07,
	    .19,.24,.32,.44,.1,.23,.13,.03,.02,0.,.09,.12,.17,.21,.33,.32,.23,
	    .16,0.,.02,.04,.03,.03,.06,.15,.29,.34,.36,.26,.28,.07,.01,0.,.01,
	    .02,.04,.19,.17,.27,.34,.14,.26,.09,.03,.02,0.,.06,.13,.09,.16,
	    .22,.29,.21,.15,0.,.02,.02,.02,.03,.11,.16,.26,.28,.29,.22,.27,
	    .05,.01,0.,.01,.01,.02,.14,.09,.19,.25,.19,.25,.07,.02,.02,0.,0.,
	    .09,.07,.12,.15,.23,.2,.16,0.,.03,.04,0.,0.,.08,.09,.21,.18,.22,
	    .21,.19,.02,.02,0.,.01,.03,.04,.08,.06,.14,.2,.12,.23,.02,0.,.02,
	    0.,0.,.05,.05,.09,.11,.14,.16,.13,0.,.03,.04,0.,0.,.05,.05,.04,
	    .09,.09,.13,.16,.03,.01,0.,.01,.03,.01,.03,.04,.1,.14,.09,.17,.02,
	    .02,0.,0.,.02,.04,.04,.03,.07,0.,.11,.09,0.,.02,0.,0.,0.,.01,0.,
	    .02,.02,.02,.06,.11,0.,0.,0.,0.,.01,0.,0.,.01,.02,.06,.09,.13,0.,
	    .02,0.,.03,.02,.03,.01,.02,.01 };

    static integer i__, j, k, l, m, kc, il, kk, jl, ml, it, iii;
    static doublereal slt, sosf[2304]	/* was [2][32][3][12] */, osft, bspl4,
	     param[3];
    extern doublereal bspl2f_(integer *, doublereal *), bspl2l_(integer *, 
	    doublereal *), bspl2s_(integer *, doublereal *), bspl4t_(integer *
	    , doublereal *);

/* ********************************************************************* */

/*       SUBROUTINE CALCULATES PERCENTAGE OF SPREAD F OCCURRENCE OVER */
/*       BRAZILIAN SECTOR AS DESCRIBED IN: */
/*       ABDU ET AL., Advances in Space Research, 31(3), */
/*       703-716, 2003 */

/*    INPUT: */
/*         IDOY: DAY OF YEAR (1 TO 365/366) */
/*         IDIY: DAYS IN YEAR (365 OR 366) */
/*         F107: F10.7 cm SOLAR FLUX (DAILY VALUE) */
/*         GEOLAT: BRAZILIAN GEOGRAPHIC LATITUDE BETWEEN -4 AND -22.5 */

/*    OUTPUT: */
/*         OSFBR(25): PERCENTAGE OF SPREAD F OCCURRENCE FOR 25 TIME */
/*                    STEPS FROM LT=18 TO LT=7 ON THE NEXT DAY IN */
/*                    STEPS OF 0.5 HOURS. */

/* ********************************************************************* */

    /* Parameter adjustments */
    --osfbr;

    /* Function Body */


    param[0] = (doublereal) (*idoy);
    param[1] = *f107;
    param[2] = *geolat;
    mflux_1.n = *idiy - 365;

    if (param[0] <= 31.) {
	mflux_1.kf = 1;
    }
    if (param[0] > 31. && param[0] <= (doublereal) (mflux_1.n + 59)) {
	mflux_1.kf = 2;
    }
    if (param[0] > (doublereal) (mflux_1.n + 59) && param[0] <= (doublereal) (
	    mflux_1.n + 90)) {
	mflux_1.kf = 3;
    }
    if (param[0] > (doublereal) (mflux_1.n + 90) && param[0] <= (doublereal) (
	    mflux_1.n + 120)) {
	mflux_1.kf = 4;
    }
    if (param[0] > (doublereal) (mflux_1.n + 120) && param[0] <= (doublereal) 
	    (mflux_1.n + 151)) {
	mflux_1.kf = 5;
    }
    if (param[0] > (doublereal) (mflux_1.n + 151) && param[0] <= (doublereal) 
	    (mflux_1.n + 181)) {
	mflux_1.kf = 6;
    }
    if (param[0] > (doublereal) (mflux_1.n + 181) && param[0] <= (doublereal) 
	    (mflux_1.n + 212)) {
	mflux_1.kf = 7;
    }
    if (param[0] > (doublereal) (mflux_1.n + 212) && param[0] <= (doublereal) 
	    (mflux_1.n + 243)) {
	mflux_1.kf = 8;
    }
    if (param[0] > (doublereal) (mflux_1.n + 243) && param[0] <= (doublereal) 
	    (mflux_1.n + 273)) {
	mflux_1.kf = 9;
    }
    if (param[0] > (doublereal) (mflux_1.n + 273) && param[0] <= (doublereal) 
	    (mflux_1.n + 304)) {
	mflux_1.kf = 10;
    }
    if (param[0] > (doublereal) (mflux_1.n + 304) && param[0] <= (doublereal) 
	    (mflux_1.n + 334)) {
	mflux_1.kf = 11;
    }
    if (param[0] > (doublereal) (mflux_1.n + 334) && param[0] <= (doublereal) 
	    (mflux_1.n + 365)) {
	mflux_1.kf = 12;
    }

    for (i__ = 1; i__ <= 32; ++i__) {
	for (j = 1; j <= 3; ++j) {
	    for (k = 1; k <= 12; ++k) {
		sosf[(i__ + (j + k * 3 << 5) << 1) - 258] = 0.;
		sosf[(i__ + (j + k * 3 << 5) << 1) - 257] = 0.;
	    }
	}
    }

    kc = 0;
    for (i__ = 5; i__ <= 23; ++i__) {
	for (j = 1; j <= 3; ++j) {
	    for (k = 1; k <= 12; ++k) {
		++kc;
		sosf[(i__ + (j + k * 3 << 5) << 1) - 258] = coef_sfa__[kc - 1]
			;
		sosf[(i__ + (j + k * 3 << 5) << 1) - 257] = coef_sfb__[kc - 1]
			;
	    }
	}
    }
    kk = 0;
    for (it = 1600; it <= 3200; it += 50) {
	slt = it / 100.;
	osft = 0.;
	for (i__ = 1; i__ <= 23; ++i__) {
	    il = i__ + 3;
	    if (il > 23) {
		il += -23;
	    }
	    for (j = 1; j <= 12; ++j) {
		jl = j + 2;
		if (jl > 12) {
		    jl += -12;
		}
		for (m = 1; m <= 3; ++m) {
		    ml = m + 1;
		    if (ml > 3) {
			ml += -3;
		    }
		    for (l = 1; l <= 2; ++l) {
			bspl4 = bspl4t_(&i__, &slt) * bspl2s_(&j, param) * 
				bspl2l_(&l, &param[2]) * bspl2f_(&m, &param[1]
				);
			osft += bspl4 * sosf[l + (il + (ml + jl * 3 << 5) << 
				1) - 259];
		    }
		}
	    }
	}
	if (slt > 17.98 && slt < 30.01) {
	    ++kk;
	    osfbr[kk] = osft;
	}
    }


    for (iii = 1; iii <= 25; ++iii) {
	if (osfbr[iii] > 1.) {
	    osfbr[iii] = 1.;
	}
	if (osfbr[iii] < 0.) {
	    osfbr[iii] = 0.;
	}
    }
    return 0;
} /* spreadf_brazil__ */


/* ********************************************************************* */
doublereal bspl4t_(integer *i__, doublereal *t1)
{
    /* Initialized data */

    static doublereal tt[79] = { 16.,16.5,17.,17.5,18.,18.5,19.,19.5,20.,20.5,
	    21.,22.,23.,24.,25.,26.,27.,27.5,28.,28.5,29.,29.5,30.,30.5,31.,
	    32.,40.,40.5,41.,41.5,42.,42.5,43.,43.5,44.,44.5,45.,46.,47.,48.,
	    49.,50.,51.,51.5,52.,52.5,53.,53.5,54.,54.5,55.,56.,64.,64.5,65.,
	    65.5,66.,66.5,67.,67.5,68.,68.5,69.,70.,71.,72.,73.,74.,75.,75.5,
	    76.,76.5,77.,77.5,78.,78.5,79.,80.,88. };

    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Local variables */
    static doublereal b[400]	/* was [20][20] */;
    static integer j, k;
    static doublereal t;

/* ********************************************************************* */


    t = *t1;
    if (*i__ >= 0 && t < tt[*i__]) {
	t += 24.;
    }
    i__1 = *i__ + 3;
    for (j = *i__; j <= i__1; ++j) {
	if (t >= tt[j] && t < tt[j + 1]) {
	    b[j - 1] = 1.;
	} else {
	    b[j - 1] = 0.;
	}
    }
    for (j = 2; j <= 4; ++j) {
	i__1 = *i__ + 4 - j;
	for (k = *i__; k <= i__1; ++k) {
	    b[k + j * 20 - 21] = (t - tt[k]) / (tt[k + j - 1] - tt[k]) * b[k 
		    + (j - 1) * 20 - 21];
	    b[k + j * 20 - 21] += (tt[k + j] - t) / (tt[k + j] - tt[k + 1]) * 
		    b[k + 1 + (j - 1) * 20 - 21];
	}
    }

    ret_val = b[*i__ + 59];

    return ret_val;

} /* bspl4t_ */


/* ***************************************************************** */
doublereal bspl2s_(integer *i__, doublereal *t1)
{
    /* Initialized data */

    static doublereal ts[37] = { 15.,46.,74.,105.,135.,166.,196.,227.,258.,
	    288.,319.,349.,380.,411.,439.,470.,500.,531.,561.,592.,623.,653.,
	    684.,714.,745.,776.,804.,835.,865.,896.,926.,957.,988.,1018.,
	    1049.,1079.,1110. };

    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Local variables */
    static doublereal b[400]	/* was [20][20] */;
    static integer j, k;
    static doublereal t;

/* ***************************************************************** */


    t = *t1;
    if (*i__ >= 0 && t < ts[*i__]) {
	t += 365.;
    }
    i__1 = *i__ + 1;
    for (j = *i__; j <= i__1; ++j) {
	if (t >= ts[j] && t < ts[j + 1]) {
	    b[j - 1] = 1.;
	} else {
	    b[j - 1] = 0.;
	}
    }

    for (j = 2; j <= 2; ++j) {
	i__1 = *i__ + 4 - j;
	for (k = *i__; k <= i__1; ++k) {
	    b[k + j * 20 - 21] = (t - ts[k]) / (ts[k + j - 1] - ts[k]) * b[k 
		    + (j - 1) * 20 - 21];
	    b[k + j * 20 - 21] += (ts[k + j] - t) / (ts[k + j] - ts[k + 1]) * 
		    b[k + 1 + (j - 1) * 20 - 21];
	}
    }

    ret_val = b[*i__ + 19];
    return ret_val;
} /* bspl2s_ */


/* ****************************************************************** */
doublereal bspl2l_(integer *i__, doublereal *t1)
{
    /* Initialized data */

    static doublereal ts[7] = { 94.,112.5,454.,472.5,814.,832.5,1174. };

    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Local variables */
    static doublereal b[400]	/* was [20][20] */;
    static integer j, k;
    static doublereal t;

/* ****************************************************************** */


    t = *t1;
    if (*i__ >= 0 && t < ts[*i__]) {
	t += 360.;
    }
    i__1 = *i__ + 1;
    for (j = *i__; j <= i__1; ++j) {
	if (t >= ts[j] && t < ts[j + 1]) {
	    b[j - 1] = 1.;
	} else {
	    b[j - 1] = 0.;
	}
    }

    for (j = 2; j <= 2; ++j) {
	i__1 = *i__ + 2 - j;
	for (k = *i__; k <= i__1; ++k) {
	    b[k + j * 20 - 21] = (t - ts[k]) / (ts[k + j - 1] - ts[k]) * b[k 
		    + (j - 1) * 20 - 21];
	    b[k + j * 20 - 21] += (ts[k + j] - t) / (ts[k + j] - ts[k + 1]) * 
		    b[k + 1 + (j - 1) * 20 - 21];
	}
    }

    ret_val = b[*i__ + 19];

    return ret_val;

} /* bspl2l_ */


/* ************************************************************************ */
doublereal bspl2f_(integer *i__, doublereal *t1)
{
    /* Initialized data */

    static integer ifnodes1[12] = { 78,77,75,79,80,77,78,80,76,81,78,78 };
    static integer ifnodes2[12] = { 144,140,139,142,139,146,142,139,150,151,
	    150,157 };
    static integer ifnodes3[12] = { 214,211,201,208,213,220,203,209,213,215,
	    236,221 };

    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Local variables */
    static doublereal b[400]	/* was [20][20] */;
    static integer j, k;
    static doublereal t, ts[10];

/* ************************************************************************ */


    ts[0] = (doublereal) ifnodes1[(0 + (0 + (mflux_1.kf - 1 << 2))) / 4];
    ts[1] = (doublereal) ifnodes2[mflux_1.kf - 1];
    ts[2] = (doublereal) ifnodes3[mflux_1.kf - 1];
    ts[3] = ts[1] + 367;
    ts[4] = ts[2] + 367;
    ts[5] = ts[3] + 367;
    ts[6] = ts[4] + 367;
    ts[7] = ts[5] + 367;
    ts[8] = ts[6] + 367;
    ts[9] = ts[7] + 367;

    t = *t1;
    if (*i__ >= 0 && t < ts[*i__]) {
	t += 367.;
    }
    i__1 = *i__ + 1;
    for (j = *i__; j <= i__1; ++j) {
	if (t >= ts[j] && t < ts[j + 1]) {
	    b[j - 1] = 1.;
	} else {
	    b[j - 1] = 0.;
	}
    }

    for (j = 2; j <= 2; ++j) {
	i__1 = *i__ + 2 - j;
	for (k = *i__; k <= i__1; ++k) {
	    b[k + j * 20 - 21] = (t - ts[k]) / (ts[k + j - 1] - ts[k]) * b[k 
		    + (j - 1) * 20 - 21];
	    b[k + j * 20 - 21] += (ts[k + j] - t) / (ts[k + j] - ts[k + 1]) * 
		    b[k + 1 + (j - 1) * 20 - 21];
	}
    }

    ret_val = b[*i__ + 19];
    return ret_val;
} /* bspl2f_ */

#ifdef __cplusplus
	}
#endif
