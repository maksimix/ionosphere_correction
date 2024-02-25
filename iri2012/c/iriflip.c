/* iriflip.f -- translated by f2c (version 20000121).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    real euvion[36]	/* was [3][12] */, pexcit[36]	/* was [3][12] */, 
	    pepion[36]	/* was [3][12] */, othpr1[6], othpr2[6];
} euvprd_;

#define euvprd_1 euvprd_

struct {
    real uvfac[59], euv;
} sol_;

#define sol_1 sol_

union {
    struct {
	real zflux[37], sigabs[111]	/* was [3][37] */, zlam[37], sigion[
		111]	/* was [3][37] */, tpot[30]	/* was [3][10] */;
	integer nni[3];
	real lamax;
    } _1;
    struct {
	real zflux[37], sigabs[111]	/* was [3][37] */, zlam[37], sigion[
		111]	/* was [3][37] */, tpot[30]	/* was [3][10] */;
	integer nni[3], lamax;
    } _2;
} sigs_;

#define sigs_1 (sigs_._1)
#define sigs_2 (sigs_._2)

/* Table of constant values */

static integer c__0 = 0;
static integer c__1 = 1;
static integer c__7 = 7;
static integer c__8 = 8;
static integer c__4 = 4;
static real c_b8 = (float)1.;
static integer c__27 = 27;
static real c_b10 = (float)0.;
static integer c__16 = 16;
static integer c__9 = 9;
static integer c__10 = 10;
static integer c__28 = 28;
static integer c__15 = 15;
static integer c__11 = 11;
static integer c__12 = 12;
static doublereal c_b199 = .45;
static doublereal c_b200 = 2.12;
static doublereal c_b201 = .52;
static doublereal c_b202 = .6;
static doublereal c_b203 = .85;
static doublereal c_b204 = .7;
static doublereal c_b205 = .56;
static doublereal c_b206 = .81;
static doublereal c_b207 = .44;
static doublereal c_b208 = -.2;
static doublereal c_b209 = .39;
static doublereal c_b210 = .5;
static doublereal c_b213 = 1.16;
static doublereal c_b214 = .67;
static doublereal c_b215 = -.55;
static doublereal c_b217 = .66;
static doublereal c_b218 = .87;
static doublereal c_b219 = .55;
static doublereal c_b220 = .21;
static doublereal c_b221 = -.41;
static doublereal c_b222 = .94;
static doublereal c_b223 = .14;
static doublereal c_b224 = .24;
static doublereal c_b227 = .91;
static doublereal c_b228 = .23;
static integer c__501 = 501;
static doublereal c_b237 = .03;
static doublereal c_b238 = 2.36;
static doublereal c_b240 = 7.1;
static doublereal c_b241 = -.7;
static doublereal c_b242 = 8.6;
static doublereal c_b243 = -.65;
static doublereal c_b244 = 34.3;
static doublereal c_b251 = 2.67;
static doublereal c_b252 = 4.;

/* flipiri.for */

/* 2012.00 10/05/11 IRI-2012: bottomside B0 B1 model (SHAMDB0D, SHAB1D), */
/* 2012.00 10/05/11    bottomside Ni model (iriflip.for), auroral foE */
/* 2012.00 10/05/11    storm model (storme_ap), Te with PF10.7 (elteik), */
/* 2012.00 10/05/11    oval kp model (auroral_boundary), IGRF-11(igrf.for), */
/* 2012.00 10/05/11    NRLMSIS00 (cira.for), CGM coordinates, F10.7 daily */
/* 2012.00 10/05/11    81-day 365-day indices (apf107.dat), ap->kp (ckp), */
/* 2012.00 10/05/11    array size change jf(50) outf(20,1000), oarr(100). */
/* 2012.01 12/12/11 Deleted ALT_RATES (not used) */
/* 2012.01 01/04/12 Deleted FINDAP,READAP,CONV_DATE,GET_DATA,RATCHK (not used) */
/* 2012.01 01/04/12 Deleted BRACE,ACTUAL_DAY,EPHEM SOLDEC,TFILE,RUN_ERROR (not used) */
/* 2012.01 01/04/12 COP2D: 99 FOMRAT ',' missing; commented out all WRITEs */
/* **************************************************************************************** */
/* subroutines for IDC model */

/* includes: main subroutine CHEMION and the following subroutines and functions */
/*           KEMPPRN.FOR: CN2D, CNO, CN4S, CN2PLS, CNOP, CO2P, COP4S, COP2D, COP2P, */
/*                        CNPLS, CN2A, CN2P, CNOPV */
/*           RATES.FOR:   RATS */
/*           PESIMP.FOR:  SECIPRD, FLXCAL, FACFLX, SIGEXS, TXSION, OXRAT, T_XS_N2, */
/*                        T_XS_OX, OXSIGS */
/*           RSPRIM.FOR:  PRIMPR, SCOLUM, PARAMS, PROBS, PROBN2, YLDISS, PROBO2, */
/*                        SCHUMN, FACEUV, FACSR, */

/* turn on printout of intermediate quantities with JPRINT=1 also in PARAMS, PROBS, */
/* PROBN2, YLDISS, and PROBO2 with ISW=1. */

/* Richards, P. G., D. Bilitza, and D. Voglozin (2010), Ion density calculator (IDC): */
/* 	A new efficient model of ionospheric ion densities, Radio Sci., 45, RS5007, */
/*   doi:10.1029/2009RS004332. */

/* **************************************************************************************** */


/* Subroutine */ int chemion_(jprint, alt, f107, f107a, te, ti, tn, oxn, o2n, 
	n2n, hen, user_no__, n4s, ne, user_nplus__, szad, oxplus, o2plus, 
	noplus, n2plus, nplus, nno, n2d, inewt)
integer *jprint;
real *alt, *f107, *f107a, *te, *ti, *tn, *oxn, *o2n, *n2n, *hen, *user_no__, *
	n4s, *ne, *user_nplus__, *szad, *oxplus, *o2plus, *noplus, *n2plus, *
	nplus, *nno, *n2d;
integer *inewt;
{
    /* Initialized data */

    static real vcon = (float)1.;
    static real heplus = (float)0.;
    static integer k = 0;
    static real pno = (float)0.;
    static real lno = (float)0.;
    static real pdnosr = (float)0.;
    static real plynop = (float)0.;
    static real n2a = (float)0.;
    static real disn2d = (float)0.;
    static real uvdisn = (float)0.;

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    double exp();

    /* Local variables */
    static real psec;
    extern /* Subroutine */ int cnop_(), rats_(), cop2d_(), cop2p_(), cop4s_()
	    ;
    static real h__;
    static integer jiter;
    static real disnp;
    extern /* Subroutine */ int cnpls_();
    static integer iters;
    static real photn, tpnop, n2aprd;
    extern /* Subroutine */ int cn2pls_();
    static real disn4s, oxplusave, tprod1, tprod2, tprod3, tprod5, pdisop;
    extern /* Subroutine */ int primpr_();
    static real n2p, o2pprod;
    extern /* Subroutine */ int cno_();
    static real dex, fex[2], altchem;
    static integer its;
    static real rts[99];
    extern /* Subroutine */ int seciprd_(), cn2a_(), cn2d_();
    static real ln2d, pn2d, op2d;
    extern /* Subroutine */ int co2p_(), cn4s_();
    static real sumions, op2p, ln4s, pn4s;

/* ------------------------------------------------------------------------------------- */
/* ... This routine was written by Phil Richards April 2010. */
/* ... It takes the specified input electron density and returns O+, O2+, NO+, */
/* ... N2+, N+, NO, and N(2D) densities.These densities generally agree well */
/* ... with the FLIP model densities. */
/* ... All the densities except O+ are calculated from chemical equilibrium. */
/* ... O+ is calculated using a Newton iterative procedure so that the total */
/* ... ion density matches the input electron density. */
/* ... N+ and NO densities can either be user specified or calculated by the model. */
/* ... N+ generally agrees well with AE-C data and the FLIP model during the day, */
/* ... but is inaccurate at night due to lack of diffusion. */
/* ... NO will be very good except below about 130 km where it will be */
/* ... underestimated due to neglect of diffusion. There is an artificial */
/* ... floor on the NO density to prevent it from getting too low below 130 km. */
/* ... If the Newton procedure fails to converge, all ions including O+ are */
/* ... calculated from chemical equilibrium and then normalized to reproduce */
/* ... the input electron density. This generally works well. */
/* ... The Newton procedure usually works if the total calculated molecular ion */
/* ... densities do not approach the input electron density. Difficulties are most */
/* ... likely to happen below ~150 km and especially at night. A Newton solution is */
/* ... usually found when the O+ density is not too much smaller than the modeled */
/* ... molecular ion density. */
/* ... The EUVAC model is used for solar EUV irradiances */
/* ------------------------------------------------------------------------------------- */
/* .. Input: Turn file output on or off */
/* .. Input: Altitude(km) */
/* .. Input: Solar activity indices */
/* .. Input: Electron, ion and neutral t */
/* .. Input: O, O2, N2, and He densities */
/* .. Input: User specified NO density ( */
/* .. Input: N4S should be 0.5*MSIS N de */
/* .. Input: electron density (cm-3) */
/* .. Input: User specified N+ density ( */
/* .. Input: solar zenith angle(D) */
/* .. OUTPUT: O+, O2+, NO+ densities (cm */
/* .. OUTPUT: N2+ and N+ densities (cm-3 */
/* .. OUTPUT: NO and N(2D) density (cm-3 */
/* .. OUTPUT: Newton procedure fails if */
/* .. Turns on printing of production and loss */
/* .. Signifies when the Newton procedure fail */
/* .. loop control variables */
/* .. Switch for different rates */
/* .. Variables for Newton procedure */
/* .. Geophysical parameters */
/* .. Electron and ion temperatures */
/* .. Measured H+, He+, O+, N2+, NO+, O2+, N+, RPA ion density */
/* .. O2,O,N2,NO,He,N4S, user specified NO */
/* .. Ne, N(2P),N(2D),O+(2P),O+(2D) densities */
/* .. Total (photon & photoel) production rates O+(4S),O+(2P),O+(2D) */
/* .. Total Production rates from all sources for NO+, O2+, */
/* .. Production rates hv(e*)+N2->N+, hv+N->N+, Lyman-a -> NO+ */
/* .. generic PE production */
/* .. Reaction rates array */
/* .. N2+ total production */
/* .. used in Newton solver */
/* .. Sum of the major ions */
/* .. Production and loss of NO */
/* .. N2(A) density */
/* .. FLIP N2(v) factor. Not used here */
/* .. Production and loss of N(2D) */
/* .. altitude for chemistry calculati */
/* .. PE production rate of N2(A) */
/* .. various ionization and excitation rates by EUV and PE */
/* .. initialize parameters */
    altchem = (float)150.;
/* .. Initial altitude for O+ for imposing chemistry */
    jiter = 0;
/* .. Counts the number of Newton iterations */
    n2p = (float)0.;
/* .. N(2P) density */
    rats_(&c__0, te, ti, tn, rts);
/* .. PRIMPR calculates solar EUV production rates. */
/*      print*,'ALT,OXN,N2N,O2N,HEN,SZAD*0.01745,TN,F107,F107A,N4S' */
/*      print*,ALT,OXN,N2N,O2N,HEN,SZAD*0.01745,TN,F107,F107A,N4S */
/* .. Get the reaction rates */
    uvdisn = euvprd_1.othpr1[0];
    r__1 = *szad * (float).01745;
    primpr_(&c__1, alt, oxn, n2n, o2n, hen, &r__1, tn, f107, f107a, n4s);
    uvdisn = euvprd_1.othpr1[0];
/* .. Calculate secondary Production from photoelectrons */
    seciprd_(alt, szad, f107, f107a, te, tn, oxn, o2n, n2n, ne, &n2aprd);
    disnp = euvprd_1.euvion[11] + euvprd_1.euvion[14] + euvprd_1.euvion[17] + 
	    (euvprd_1.pepion[2] + euvprd_1.pepion[5] + euvprd_1.pepion[8]) * (
	    float).1 + euvprd_1.pepion[11] + euvprd_1.pepion[14] + 
	    euvprd_1.pepion[17];
/* .. Rydberg diss */
    disn2d = euvprd_1.pepion[2] * (float)2. + euvprd_1.othpr2[2];
    disn4s = euvprd_1.pepion[2] * (float)2. + euvprd_1.othpr2[2];
/* **********  Come back here if Newton fails */
L5:
/* .. initialize variables to avoid using left over values */
    heplus = (float)0.;
    *oxplus = (float)0.;
    *n2plus = (float)0.;
    *noplus = (float)0.;
    *o2plus = (float)0.;
    *nplus = (float)0.;
    n2p = (float)0.;
    *n2d = (float)0.;
    op2d = (float)0.;
    op2p = (float)0.;
    n2a = (float)0.;
/* .. Iterate through chemistry twice in case O+ is chemical equilib */
    for (iters = 1; iters <= 3; ++iters) {
/* .. K counts number of iterations for printing headers in routin */
	++k;
/* .. Set initial value for electron density */
/* .. O+(2P) Calculate and print densities, production, loss */
	psec = euvprd_1.pepion[6];
/* .. Photoelectron production */
	tprod3 = euvprd_1.euvion[6] + psec;
/* .. Add EUV and photoelectrons */
	cop2p_(jprint, &c__7, &k, alt, rts, oxn, o2n, n2n, ne, &op2p, &tprod3,
		 &psec, &heplus, n4s, nno, te);
/* .. O+(2D) Calculate and print densities, production, loss */
	psec = euvprd_1.pepion[3];
/* .. Photoelectron production */
	tprod2 = euvprd_1.euvion[3];
/* .. EUV */
	cop2d_(jprint, &c__8, &k, alt, rts, oxn, o2n, n2n, ne, &op2d, &tprod2,
		 &op2p, &heplus, n4s, nno, &psec);
/* .. O+(4S) Calculate and print densities, production, loss. */
	tprod1 = euvprd_1.euvion[0];
	pdisop = euvprd_1.euvion[10] + euvprd_1.euvion[13] + euvprd_1.pepion[
		10] + euvprd_1.pepion[13];
/*        write(*,*) JPRINT,K,ALT */
	cop4s_(jprint, &c__4, &k, alt, rts, oxn, o2n, n2n, ne, oxplus, &
		tprod1, &op2d, &op2p, euvprd_1.pepion, &pdisop, n2plus, n2d, 
		nno, &c_b8, &heplus);
/*        write(*,*) OXPLUS,TPROD1,OP2D */
/*     >    ,OP2P,PEPION(1,1),PDISOP,N2PLUS,N2D,NNO,HEPLUS */
	cn2a_(jprint, &c__27, &k, alt, rts, oxn, o2n, n2n, ne, &n2a, &n2aprd, 
		&c_b10, &c_b10, &c_b10);
/* ..CALL CN2P(JPRINT,0,K,ALT,RTS,OXN,O2N,N2N,NE,PN2P,LN2P */
/* ..> ,N2P,P3X7,UVDISN,O2PLUS,NNO,N2PLUS) */
/* .. N(2D) Calculate and print densities, production, loss. */
	cn2d_(jprint, &c__16, &k, alt, rts, oxn, o2n, n2n, noplus, ne, &pn2d, 
		&ln2d, n2plus, &disn2d, &uvdisn, nplus, &n2p, n2d, oxplus, 
		nno, &n2a);
	*n2d = pn2d / ln2d;
/* .. N2+ Calculate and print densities, production, loss. */
	cn2pls_(jprint, &c__9, &k, alt, rts, oxn, o2n, n2n, ne, n2plus, &
		euvprd_1.euvion[2], &euvprd_1.euvion[5], &euvprd_1.euvion[8], 
		&euvprd_1.pepion[2], &euvprd_1.pepion[5], &euvprd_1.pepion[8],
		 &op2d, &op2p, &heplus, nplus, nno, n4s);
/* .. N+ Calculate and print densities, production, loss. */
/* .. Note that N(2D) is turned off in N+ solution */
	photn = euvprd_1.othpr2[2];
/* .. N+ prod */
	cnpls_(jprint, &c__10, &k, alt, rts, oxn, o2n, n2n, ne, &disnp, nplus,
		 oxplus, n2d, &op2p, &heplus, &photn, o2plus, n4s, &op2d, 
		n2plus, nno);
	if (*user_nplus__ > (float)0.) {
	    *nplus = *user_nplus__;
	}
/* .. User specified N+ */
	cn4s_(jprint, &c__28, &k, alt, rts, oxn, o2n, n2n, ne, &pn4s, &ln4s, 
		n4s, &disn4s, n2d, &n2p, oxplus, n2plus, &uvdisn, noplus, 
		nplus, nno, o2plus, &pdnosr, &c_b8);
/* ..N4S=PN4S/LN4S */
/* .. NO Calculate and print densities, production, loss. */
	cno_(jprint, &c__15, &k, alt, rts, oxn, o2n, n2n, ne, &pno, &lno, n2d,
		 n4s, &n2p, nno, o2plus, oxplus, &euvprd_1.othpr2[1], 
		euvprd_1.othpr2, &n2a, nplus);
	*nno = pno / lno;
/* .. Set a floor on NO density, which is needed below ~150 km at */
/* .. NO chemical equilibrium density */
	if (*nno < exp((100 - *alt) / 20) * (float)1e8) {
	    *nno = exp((100 - *alt) / 20) * (float)1e8;
	}
	if (*user_no__ > (float)1.) {
	    *nno = *user_no__;
	}
/* .. substitute user specified va */
	if (*nno > (float)1.5e8) {
	    *nno = (float)1.5e8;
	}
/* .. NO+ Calculate and print densities, production, loss. */
/* .. Don't let NO get too big */
	cnop_(jprint, &c__11, &k, alt, rts, oxn, o2n, n2n, ne, &tpnop, noplus,
		 oxplus, n2plus, o2plus, n4s, nno, nplus, &n2p, &plynop, &
		vcon, n2d, &op2d);
/* .. O2+ Calculate and print densities, production, loss. */
/* .. EUV + PE production */
	tprod5 = euvprd_1.euvion[1] + euvprd_1.euvion[4] + euvprd_1.euvion[7] 
		+ euvprd_1.pepion[1] + euvprd_1.pepion[4] + euvprd_1.pepion[7]
		;
	co2p_(jprint, &c__12, &k, alt, rts, oxn, o2n, n2n, ne, &o2pprod, 
		o2plus, &tprod5, oxplus, &op2d, n2plus, nplus, n4s, nno, &
		op2p);
    }
/* .. This section for chemical equilibrium densities for all specie */
/* .. including O+. It is used when the Newton procedure fails to ge */
/* .. Don't bother if molecular ions greater than Ne/2 */
/* .. It increments ALTCHEM to force this action. The ion densities */
/* .. normalized to the input NE. N+ is excluded in case it is user */
    *inewt = 1;
    sumions = *oxplus + *noplus + *o2plus + *nplus;
    if (*alt < altchem || *noplus + *o2plus > *ne * (float).85) {
	*oxplus = *oxplus * *ne / sumions;
	*noplus = *noplus * *ne / sumions;
	*o2plus = *o2plus * *ne / sumions;
	*nplus = *nplus * *ne / sumions;
	*inewt = 0;
	return 0;
    }
/* .. Newton solution for O+ density given the electron density (NE) */
/* .. Go through twice to set up the derivative (F(x+h)-F(x))/h */
/* .. First O+ guess for Newton. This is important for high altitude */
/* .. because Newton may converge on first try. */
    oxplusave = *oxplus;
    if (*ne - *noplus - *o2plus > (float)100.) {
	*oxplus = *ne - *noplus - *o2plus;
    }
/* ..IF(SZAD.GT.89) OXPLUS=NE  !.. first guess at night */
L9:
    for (its = 1; its <= 2; ++its) {
	if (its == 1) {
	    h__ = *oxplus * (float)1e-4;
	}
/* .. increment for dn/dt */
	if (its == 2) {
	    *oxplus += h__;
	}
/* .. N+ Calculate and print densities, production, loss. */
/* .. increment N */
	cnpls_(jprint, &c__10, &k, alt, rts, oxn, o2n, n2n, ne, &disnp, nplus,
		 oxplus, n2d, &op2p, &heplus, &photn, o2plus, n4s, &op2d, 
		n2plus, nno);
	if (*user_nplus__ > (float)0.) {
	    *nplus = *user_nplus__;
	}
/* .. N2+ Calculate and print densities, production, loss. */
/* .. User specified N+ */
	cn2pls_(jprint, &c__9, &k, alt, rts, oxn, o2n, n2n, ne, n2plus, &
		euvprd_1.euvion[2], &euvprd_1.euvion[5], &euvprd_1.euvion[8], 
		&euvprd_1.pepion[2], &euvprd_1.pepion[5], &euvprd_1.pepion[8],
		 &op2d, &op2p, &heplus, nplus, nno, n4s);
/* .. NO+ Calculate and print densities, production, loss. */
	cnop_(jprint, &c__11, &k, alt, rts, oxn, o2n, n2n, ne, &tpnop, noplus,
		 oxplus, n2plus, o2plus, n4s, nno, nplus, &n2p, &plynop, &
		vcon, n2d, &op2d);
/* .. O2+ Calculate and print densities, production, loss. */
/* .. EUV + PE production */
	tprod5 = euvprd_1.euvion[1] + euvprd_1.euvion[4] + euvprd_1.euvion[7] 
		+ euvprd_1.pepion[1] + euvprd_1.pepion[4] + euvprd_1.pepion[7]
		;
	co2p_(jprint, &c__12, &k, alt, rts, oxn, o2n, n2n, ne, &o2pprod, 
		o2plus, &tprod5, oxplus, &op2d, n2plus, nplus, n4s, nno, &
		op2p);
/* .. N(2D) Calculate and print densities, production, loss. */
	cn2d_(jprint, &c__16, &k, alt, rts, oxn, o2n, n2n, noplus, ne, &pn2d, 
		&ln2d, n2plus, &disn2d, &uvdisn, nplus, &n2p, n2d, oxplus, 
		nno, &n2a);
	*n2d = pn2d / ln2d;
/* .. calculation of F(x) from the total ion concentration */
	fex[its - 1] = *oxplus + *noplus + *o2plus + *n2plus + *nplus - *ne;
    }
/* .. Test for convergence and add increment to O+ if not */
    ++jiter;
/* .. for stopping the iterations */
    dex = (fex[1] - fex[0]) / h__;
    *oxplus = *oxplus - h__ - fex[0] / dex;
/* .. If Newton fails, go back and calculate O+ chem equilibrium */
    if (jiter > 6 || *oxplus < (float)0. || *oxplus > (float)1e7) {
	altchem = *alt + 1;
/* .. forces chemical equilibrium densities */
	goto L5;
/* .. Go back to chemical eqilibrium */
    }
/* .. Test for convergence */
    sumions = *oxplus + *noplus + *o2plus + *n2plus + *nplus;
    if ((r__1 = (*ne - sumions) / *ne, dabs(r__1)) > (float).05) {
	goto L9;
    }
/* .. Normalize ion densities to the input electron density */
    *oxplus = *oxplus * *ne / sumions;
    *noplus = *noplus * *ne / sumions;
    *o2plus = *o2plus * *ne / sumions;
    *nplus = *nplus * *ne / sumions;
/* .. If O+ a very minor ion, Newton solution may not be good, force */
/* .. chemical equilibrium solution instead */
    if (*oxplus / sumions < (float).1) {
	altchem = *alt + 1;
/* .. forces chemical equilibrium densities */
	goto L5;
/* .. Go back to chemical eqilibrium */
    }
    return 0;
} /* chemion_ */



/* .................... KEMPRN.FOR ...................................... */
/* .. This file contains the chemistry routines for ions and neutrals */
/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int cn2d_(jpr, i__, jpt, z__, rts, on, o2n, n2n, nop, ne, p1,
	 l1, n2pls, disn2d, uvdisn, nplus, n2p, n2d, opls, nno, n2a)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *nop, *ne, *p1, *l1, *n2pls, *disn2d, *
	uvdisn, *nplus, *n2p, *n2d, *opls, *nno, *n2a;
{
    /* Format strings */
    static char fmt_189[] = "(/2x,\002N(2D)\002,25x,\002EMISSION\002,28x,\
\002:\002,20x,\002Loss rate\002)";
    static char fmt_191[] = "(/2x,\002N(2D)\002,25x,\002Production\002,36x\
,\002:\002,20x,\002Loss rate\002)";
    static char fmt_96[] = "(2x,\002ALT   [N2D]   NO++e   N2++e   N2++O    e\
+N2   hv+N2\002,3x,\002N++O2   N(2P)   N2A+O    +O     +O2      +e     +O\
+\002,5x,\002RAD     +NO\002)";
    static char fmt_7[] = "(f6.1,1p,22e8.1)";

    /* System generated locals */
    real r__1, r__2, r__3;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real ef, lr[22], pr[22];

    /* Fortran I/O blocks */
    static cilist io___43 = { 0, 0, 0, fmt_189, 0 };
    static cilist io___44 = { 0, 0, 0, fmt_191, 0 };
    static cilist io___45 = { 0, 0, 0, fmt_96, 0 };
    static cilist io___46 = { 0, 0, 0, fmt_7, 0 };


/* .......n(2d) */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = *nop * *ne * rts[50];
    pr[1] = *n2pls * *ne * rts[32] * rts[11];
    pr[2] = *n2pls * *on * rts[10];
    pr[3] = *disn2d;
    pr[4] = rts[63] * *uvdisn;
    pr[5] = rts[65] * *nplus * *o2n;
    pr[6] = *n2p * rts[57];
    pr[7] = rts[27] * *n2a * *on;
    lr[0] = *on * rts[15];
    lr[1] = *o2n * rts[16];
    lr[2] = *ne * rts[8];
    lr[3] = *opls * rts[29];
    lr[4] = rts[61];
    lr[5] = rts[41] * *nno;
    *p1 = pr[0] + pr[1] + pr[2] + pr[3] + pr[4] + pr[5] + pr[6] + pr[7];
    *l1 = lr[0] + lr[1] + lr[2] + lr[3] + lr[4] + lr[5];
/* ....... EF is used to convert production rates to volume emission rates */
    ef = (float)1.;
/* ....... This line in for volume emission rates */
/* ...      EF=RTS(61)*0.76/L1 */
    if (*jpt == 1 && *jpr > 0 && (integer) (ef + (float).1) != 1) {
	io___43.ciunit = *i__;
	s_wsfe(&io___43);
	e_wsfe();
    }
    if (*jpt == 1 && *jpr > 0 && (integer) (ef + (float).1) == 1) {
	io___44.ciunit = *i__;
	s_wsfe(&io___44);
	e_wsfe();
    }
    if (*jpt == 1 && *jpr > 0) {
	io___45.ciunit = *i__;
	s_wsfe(&io___45);
	e_wsfe();
    }
    if (*jpr > 0) {
	io___46.ciunit = *i__;
	s_wsfe(&io___46);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	r__1 = *p1 / *l1;
	do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	for (k = 1; k <= 8; ++k) {
	    r__2 = pr[k - 1] * ef;
	    do_fio(&c__1, (char *)&r__2, (ftnlen)sizeof(real));
	}
	for (k = 1; k <= 6; ++k) {
	    r__3 = lr[k - 1] * *n2d;
	    do_fio(&c__1, (char *)&r__3, (ftnlen)sizeof(real));
	}
	e_wsfe();
    }
    return 0;
} /* cn2d_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int cno_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, p1, l1, 
	n2d, n4s, n2p, nno, o2p, opls, pdnosr, plynop, n2a, nplus)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *p1, *l1, *n2d, *n4s, *n2p, *nno, *o2p,
	 *opls, *pdnosr, *plynop, *n2a, *nplus;
{
    /* Format strings */
    static char fmt_192[] = "(/2x,\002NO\002,17x,\002PRODUCTION\002,20x\
,\002:\002,10x,\002LOSS RATES\002/,4x,\002ALT\002,3x,\002[NO]\002,5x,\002[NO\
]c\002,3x,\002O2+N2D\002,3x,\002O2+N4S   N2P+O2   N2A+O    N++O2    N4S+NO  \
 O2P+NO   O++NO\002,3x,\002N2D+NO   hv<1910   Lyman-a\002)";
    static char fmt_7[] = "(f6.1,1p,22e9.2)";

    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real lr[22], pr[22];

    /* Fortran I/O blocks */
    static cilist io___50 = { 0, 0, 0, fmt_192, 0 };
    static cilist io___51 = { 0, 0, 0, fmt_7, 0 };


/* ........no */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = rts[16] * *o2n * *n2d;
    pr[1] = rts[7] * *o2n * *n4s;
    pr[2] = rts[38] * *n2p * *o2n;
    pr[3] = rts[27] * *n2a * *on;
    pr[4] = rts[22] * *nplus * *o2n;
/* .. Fox */
    lr[0] = rts[9] * *n4s;
    lr[1] = rts[23] * *o2p;
    lr[2] = rts[24] * *opls;
    lr[3] = rts[41] * *n2d;
    lr[4] = *pdnosr;
    lr[5] = *plynop;
    *p1 = pr[0] + pr[1] + pr[2] + pr[3] + pr[4];
    *l1 = lr[0] + lr[1] + lr[2] + lr[3] + (lr[4] + lr[5]);
    if (*jpt == 1 && *jpr > 0) {
	io___50.ciunit = *i__;
	s_wsfe(&io___50);
	e_wsfe();
    }
    if (*jpr > 0) {
	io___51.ciunit = *i__;
	s_wsfe(&io___51);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*nno), (ftnlen)sizeof(real));
	r__1 = *p1 / *l1;
	do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	for (k = 1; k <= 5; ++k) {
	    do_fio(&c__1, (char *)&pr[k - 1], (ftnlen)sizeof(real));
	}
	for (k = 1; k <= 6; ++k) {
	    r__2 = lr[k - 1] * *nno;
	    do_fio(&c__1, (char *)&r__2, (ftnlen)sizeof(real));
	}
	e_wsfe();
    }
    return 0;
} /* cno_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int cn4s_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, p1, l1, 
	n4s, disn4s, n2d, n2p, opls, n2pls, uvdisn, nop, nplus, nno, o2p, 
	pdnosr, vcon)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *p1, *l1, *n4s, *disn4s, *n2d, *n2p, *
	opls, *n2pls, *uvdisn, *nop, *nplus, *nno, *o2p, *pdnosr, *vcon;
{
    /* Format strings */
    static char fmt_193[] = "(/2x,\002N(4S)\002,38x,\002PRODUCTION\002,46x\
,\002:\002,7x,\002LOSS RATES\002/,3x,\002ALT\002,2x,\002[N4S]\002,2x,\002hv-\
>N+\002,3x,\002O+N2D\002,2x,\002e+N2D\002,3x,\002O++N2\002,3x,\002N2++e\002,\
4x,\002hv->2N\002,2x,\002NO++e\002,2x,\002N(2D)\002,4x,\002N(2P)   N+&X    h\
v+NO    +O2  \002,2x,\002 +NO  \002,2x,\002+O2+ & N2+\002)";
    static char fmt_7[] = "(f6.1,1p,22e8.1)";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real lr[22], pr[22];

    /* Fortran I/O blocks */
    static cilist io___55 = { 0, 0, 0, fmt_193, 0 };
    static cilist io___56 = { 0, 0, 0, fmt_7, 0 };


/* ........N(4S) */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = *disn4s;
    pr[1] = rts[15] * *on * *n2d;
    pr[2] = rts[8] * *ne * *n2d;
    pr[3] = *vcon * rts[3] * *opls * *n2n;
    pr[4] = rts[53] * rts[11] * *n2pls * *ne;
    pr[5] = rts[62] * *uvdisn;
    pr[6] = *nop * *ne * rts[49];
    pr[7] = *n2d * rts[61];
    pr[8] = *n2p * rts[58];
    pr[9] = rts[25] * *nplus * *o2n;
    pr[10] = *pdnosr * *nno;
    pr[11] = *nplus * *nno * rts[81];
/* ..Fox */
    lr[0] = rts[7] * *o2n;
    lr[1] = rts[9] * *nno;
    lr[2] = rts[21] * *o2p;
    lr[3] = rts[79] * *n2pls;
/* ..Fox */
    *p1 = pr[0] + pr[1] + pr[2] + pr[3] + pr[4] + pr[5] + pr[6] + pr[7] + pr[
	    8] + pr[9] + pr[10] + pr[11];
    *l1 = lr[0] + lr[1] + lr[2] + lr[3];
    if (*jpt == 1 && *jpr > 0) {
	io___55.ciunit = *i__;
	s_wsfe(&io___55);
	e_wsfe();
    }
    pr[9] += pr[11];
/* ... for printing fit */
    lr[2] += lr[3];
/* ... for printing fit */
    if (*jpr > 0) {
	io___56.ciunit = *i__;
	s_wsfe(&io___56);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*n4s), (ftnlen)sizeof(real));
	for (k = 1; k <= 11; ++k) {
	    do_fio(&c__1, (char *)&pr[k - 1], (ftnlen)sizeof(real));
	}
	for (k = 1; k <= 3; ++k) {
	    r__1 = lr[k - 1] * *n4s;
	    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	}
	e_wsfe();
    }
    return 0;
} /* cn4s_ */

/* ::::::::::::::::::::::::::::::: CN2PLS ::::::::::::::::::::::::::::::: */
/* ..... Simplified chemistry of N2+.  PUN2P* = production of N2+ by euv */
/* ..... in the (X,A,B states). PEN2P* same for p.e.s (X,A,B states) */
/* Subroutine */ int cn2pls_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, n2pls,
	 pun2px, pun2pa, pun2pb, pen2px, pen2pa, pen2pb, op2d, op2p, heplus, 
	nplus, nno, n4s)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *n2pls, *pun2px, *pun2pa, *pun2pb, *
	pen2px, *pen2pa, *pen2pb, *op2d, *op2p, *heplus, *nplus, *nno, *n4s;
{
    /* Format strings */
    static char fmt_95[] = "(/2x,\002N2+\002,29x,\002PRODUCTION\002,45x\
,\002:\002,12x,\002LOSS RATES\002/,3x,\002ALT  [N2+]  EUV-X   EUV-A    EUV-B\
   PE-X\002,5x,\002PE-A    PE-B  O+2D+N2  O+2P+N2  He++N2  O+N2+\002,2x,\002\
e+N2+  O2+N2+  N2++O  Other\002)";
    static char fmt_7[] = "(f6.1,1p,22e8.1)";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real lr[22], pr[22];

    /* Fortran I/O blocks */
    static cilist io___60 = { 0, 0, 0, fmt_95, 0 };
    static cilist io___61 = { 0, 0, 0, fmt_7, 0 };


    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = *pun2px;
    pr[1] = *pun2pa;
    pr[2] = *pun2pb;
    pr[3] = *pen2px;
    pr[4] = *pen2pa;
    pr[5] = *pen2pb;
    pr[6] = rts[19] * *op2d * *n2n;
    pr[7] = rts[20] * *op2p * *n2n;
    pr[8] = rts[44] * *heplus * *n2n;
    pr[9] = rts[82] * *nplus * *nno;
/* ..Fox */
    lr[0] = rts[10] * *on;
    lr[1] = rts[11] * *ne;
    lr[2] = rts[17] * *o2n;
    lr[3] = rts[99] * *on;
    lr[4] = rts[79] * *n4s;
/* ..Fox */
    lr[5] = rts[80] * *nno;
/* ..Fox */
    *n2pls = (pr[0] + pr[1] + pr[2] + pr[3] + pr[4] + pr[5] + pr[6] + pr[7] + 
	    pr[8] + pr[9]) / (lr[0] + lr[1] + lr[2] + lr[3] + lr[4] + lr[5]);
    if (*jpt == 1 && *jpr > 0) {
	io___60.ciunit = *i__;
	s_wsfe(&io___60);
	e_wsfe();
    }
    pr[8] += pr[9];
/* .. for printing fit */
    lr[4] += lr[5];
/* .. for printing fit */
    if (*jpr > 0) {
	io___61.ciunit = *i__;
	s_wsfe(&io___61);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*n2pls), (ftnlen)sizeof(real));
	for (k = 1; k <= 9; ++k) {
	    do_fio(&c__1, (char *)&pr[k - 1], (ftnlen)sizeof(real));
	}
	for (k = 1; k <= 5; ++k) {
	    r__1 = lr[k - 1] * *n2pls;
	    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	}
	e_wsfe();
    }
    return 0;
} /* cn2pls_ */

/* :::::::::::::::::::::::::::::: CNOP :::::::::::::::::::::::::::::::::: */
/* Subroutine */ int cnop_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, p1, nop,
	 opls, n2pls, o2p, n4s, nno, nplus, n2p, plynop, vcon, n2d, op2d)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *p1, *nop, *opls, *n2pls, *o2p, *n4s, *
	nno, *nplus, *n2p, *plynop, *vcon, *n2d, *op2d;
{
    /* Format strings */
    static char fmt_96[] = "(/2x,\002NO+\002,31x,\002PRODUCTION\002,48x\
,\002:\002,2x,\002LOSS RATES\002/,3x,\002ALT\002,3x,\002[NO+]\002,4x,\002O++\
N2\002,3x,\002N2++O\002,3x,\002O2++N4S\002,3x,\002O2++NO\002,3x,\002N++O2\
\002,4x,\002N2P+O\002,3x,\002O++NO   hv+NO\002,5x,\002O2++N2D   N2++NO   N++\
NO   OP2D+NO   OP2D+N2  NO++e\002)";
    static char fmt_7[] = "(f6.1,1p,22e9.2)";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real lr[22], pr[22];

    /* Fortran I/O blocks */
    static cilist io___65 = { 0, 0, 0, fmt_96, 0 };
    static cilist io___66 = { 0, 0, 0, fmt_7, 0 };


/* ........no+ */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = *vcon * rts[3] * *n2n * *opls;
    pr[1] = *n2pls * *on * rts[10];
    pr[2] = *o2p * *n4s * rts[21];
    pr[3] = *o2p * *nno * rts[23];
/* .. N+ + O2 -> O2+ + N(2D,4S) or NO+ + O(1S) */
    pr[4] = (rts[30] + rts[66] + rts[59]) * *nplus * *o2n;
    pr[5] = rts[37] * *n2p * *on;
    pr[6] = rts[24] * *opls * *nno;
    pr[7] = *plynop * *nno;
    pr[8] = *o2p * *n2d * rts[77];
/* ..Fox */
    pr[9] = *n2pls * *nno * rts[80];
/* ..Fox */
    pr[10] = *nplus * *nno * rts[81];
/* ..Fox */
    pr[11] = rts[83] * *nno * *op2d;
/* ..Fox */
    pr[12] = *op2d * rts[90] * *n2n;
/* .. -> NO+ + N, Li et al. [1997] */
    lr[0] = *ne * rts[5];
    *p1 = pr[0] + pr[1] + pr[2] + pr[3] + pr[4] + pr[5] + pr[6] + pr[7] + pr[
	    8] + pr[9] + pr[10] + pr[11] + pr[12];
    *nop = *p1 / lr[0];
    if (*jpt == 1 && *jpr > 0) {
	io___65.ciunit = *i__;
	s_wsfe(&io___65);
	e_wsfe();
    }
/* PR(9)=PR(9)+PR(10)+PR(11)+PR(12)+PR(13) */
    if (*jpr > 0) {
	io___66.ciunit = *i__;
	s_wsfe(&io___66);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*nop), (ftnlen)sizeof(real));
	for (k = 1; k <= 13; ++k) {
	    do_fio(&c__1, (char *)&pr[k - 1], (ftnlen)sizeof(real));
	}
	r__1 = lr[0] * *nop;
	do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	e_wsfe();
    }
    return 0;
} /* cnop_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int co2p_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, p1, o2p,
	 tprod5, opls, op2d, n2pls, nplus, n4s, nno, op2p)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *p1, *o2p, *tprod5, *opls, *op2d, *
	n2pls, *nplus, *n4s, *nno, *op2p;
{
    /* Format strings */
    static char fmt_97[] = "(/2x,\002O2+\002,22x,\002PRODUCTION\002,24x\
,\002:\002,12x,\002LOSS RATES\002/,3x,\002ALT\002,3x,\002[O2+]\002,3x,\002hv\
+O2\002,3x,\002O++O2\002,3x,\002O+(2D)+O2\002,4x,\002N2++O2   N++O2   O+(2P)\
+O2  O2++e   O2++N   O2++NO\002)";
    static char fmt_7[] = "(f6.1,1p,22e9.2)";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real lr[22], pr[22];

    /* Fortran I/O blocks */
    static cilist io___70 = { 0, 0, 0, fmt_97, 0 };
    static cilist io___71 = { 0, 0, 0, fmt_7, 0 };


/* ........o2+ */
/* ......... TPROD5=euv @ p.e. production */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = *tprod5;
    pr[1] = rts[4] * *o2n * *opls;
    pr[2] = rts[43] * *op2d * *o2n;
    pr[3] = rts[17] * *o2n * *n2pls;
    pr[4] = rts[25] * *nplus * *o2n;
    pr[5] = rts[86] * *op2p * *o2n;
/* .. Fox */
    pr[6] = rts[65] * *nplus * *o2n;
    lr[0] = rts[6] * *ne;
    lr[1] = rts[21] * *n4s;
    lr[2] = rts[23] * *nno;
    *p1 = pr[0] + pr[1] + pr[2] + pr[3] + pr[4] + pr[5] + pr[6];
    *o2p = *p1 / (lr[0] + lr[1] + lr[2]);
    if (*jpt == 1 && *jpr > 0) {
	io___70.ciunit = *i__;
	s_wsfe(&io___70);
	e_wsfe();
    }
    if (*jpr > 0) {
	io___71.ciunit = *i__;
	s_wsfe(&io___71);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*o2p), (ftnlen)sizeof(real));
	for (k = 1; k <= 7; ++k) {
	    do_fio(&c__1, (char *)&pr[k - 1], (ftnlen)sizeof(real));
	}
	for (k = 1; k <= 3; ++k) {
	    r__1 = lr[k - 1] * *o2p;
	    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	}
	e_wsfe();
    }
    return 0;
} /* co2p_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int cop4s_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, opls, 
	tprod1, op2d, op2p, pepion, pdisop, n2pls, n2d, nno, vcon, heplus)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *opls, *tprod1, *op2d, *op2p, *pepion, 
	*pdisop, *n2pls, *n2d, *nno, *vcon, *heplus;
{
    /* Format strings */
    static char fmt_98[] = "(/2x,\002O+\002,41x,\002PRODUCTION\002,39x,\002\
:\002,10x,\002LOSS RATES\002/,\002 ALT    [O+]   hv+O  O+(2D)+e O+(2P)+O   e\
*+O  O2-diss  \002,\002N2++O  O+(2P)+e O+(2P) O+O+(2D)   Other  +N2     +O2 \
   \002,\002+NO   +N2D\002)";
    static char fmt_7[] = "(f6.1,1p,22e8.1)";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real nplus, lrtot, prtot, lr[22], pr[22];

    /* Fortran I/O blocks */
    static cilist io___78 = { 0, 0, 0, fmt_98, 0 };
    static cilist io___79 = { 0, 0, 0, fmt_7, 0 };


/* ...........o+(4s) */
/* .........pr(1)= euv production of o+(4s) */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = *tprod1;
    pr[1] = *op2d * *ne * rts[12];
    pr[2] = *op2p * *on * rts[26];
    pr[3] = *pepion;
    pr[4] = *pdisop;
    pr[5] = rts[99] * *n2pls * *on;
    pr[6] = *op2p * *ne * rts[14];
    pr[7] = *op2p * (float).047;
    pr[8] = rts[28] * *on * *op2d;
    pr[9] = rts[85] * *op2p * *o2n;
/* .. Fox */
    pr[10] = *heplus * *o2n * (rts[91] + rts[93]);
/* ..Fox */
    pr[11] = rts[95] * *nno * *heplus;
/* ..Fox */
    pr[12] = rts[22] * nplus * *o2n;
/* ..Fox */
    lr[0] = *n2n * *vcon * rts[3];
    lr[1] = *o2n * rts[4];
    lr[2] = *nno * rts[24];
    lr[3] = *n2d * rts[29];
/* ..LR(4)=(LR(1)+LR(2)+LR(3))  !.. total loss for printing */
/* .... small loss?? ..Fox */
    pr[9] = pr[9] + pr[10] + pr[11] + pr[12];
    prtot = pr[0] + pr[1] + pr[2] + pr[3] + pr[4] + pr[5] + pr[6] + pr[7] + 
	    pr[8] + pr[9];
    lrtot = lr[0] + lr[1] + lr[2] + lr[3];
    *opls = prtot / lrtot;
    if (*jpt == 1 && *jpr > 0) {
	io___78.ciunit = *i__;
	s_wsfe(&io___78);
	e_wsfe();
    }
    if (*jpr > 0) {
	io___79.ciunit = *i__;
	s_wsfe(&io___79);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*opls), (ftnlen)sizeof(real));
	for (k = 1; k <= 10; ++k) {
	    do_fio(&c__1, (char *)&pr[k - 1], (ftnlen)sizeof(real));
	}
	for (k = 1; k <= 4; ++k) {
	    r__1 = lr[k - 1] * *opls;
	    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	}
	e_wsfe();
    }
    return 0;
} /* cop4s_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int cop2d_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, op2d, 
	tprod2, op2p, heplus, n4s, nno, psec)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *op2d, *tprod2, *op2p, *heplus, *n4s, *
	nno, *psec;
{
    /* Format strings */
    static char fmt_99[] = "(/2x,\002O+(2D)\002,13x,\002PRODUCTION\002,27x\
,\002:\002,18x,\002LOSS RATES\002/,3x,\002ALT\002,3x,\002[O+2D]\002,3x,\002h\
v+O\002,4x,\002e*+O\002,4x,\002O+2P+e\002,3x,\002O+2P>hv\002,2x,\002He++O2  \
   +N2    E3726_29    +e       +O\002,\002      +O2      +NO     +N  +N2>NO\
+\002)";
    static char fmt_7[] = "(f6.1,1p,22e9.2)";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real lr[22], pr[22];

    /* Fortran I/O blocks */
    static cilist io___83 = { 0, 0, 0, fmt_99, 0 };
    static cilist io___84 = { 0, 0, 0, fmt_7, 0 };


/* .......o+(2d) */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = *tprod2;
/* EUV  prod */
    pr[1] = *op2p * *ne * rts[13];
    pr[2] = *op2p * (float).171;
    pr[3] = *heplus * *o2n * rts[76];
/* ..Fox */
    pr[4] = *psec;
    lr[0] = rts[19] * *n2n;
    lr[1] = (float)7.7e-5;
/* .. radiation at 3726 and 3729 A */
    lr[2] = *ne * rts[12];
    lr[3] = *on * rts[28];
    lr[4] = rts[43] * *o2n;
    lr[5] = rts[83] * *nno;
/* ..Fox */
    lr[6] = rts[84] * *n4s;
/* ..Fox */
    lr[7] = rts[90] * *n2n;
/* .. -> NO+ + N, Li et al. [1997] */
    *op2d = (pr[0] + pr[1] + pr[2] + pr[3] + pr[4]) / (lr[0] + lr[1] + lr[2] 
	    + lr[3] + lr[4] + lr[5] + lr[6] + lr[7]);
    if (*jpt == 1 && *jpr > 0) {
	io___83.ciunit = *i__;
	s_wsfe(&io___83);
	e_wsfe();
    }
    if (*jpr > 0) {
	io___84.ciunit = *i__;
	s_wsfe(&io___84);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*op2d), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&pr[0], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&pr[4], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&pr[1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&pr[2], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&pr[3], (ftnlen)sizeof(real));
	for (k = 1; k <= 8; ++k) {
	    r__1 = lr[k - 1] * *op2d;
	    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	}
	e_wsfe();
    }
    return 0;
} /* cop2d_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int cop2p_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, op2p, 
	tprod3, psec, heplus, n4s, nno, te)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *op2p, *tprod3, *psec, *heplus, *n4s, *
	nno, *te;
{
    /* Format strings */
    static char fmt_100[] = "(/2x,\002 O+(2P)\002,6x,\002PRODUCTION\002,10x\
,\002:\002,12x,\002LOSS RATES\002/,3x,\002ALT   [O+2P]    hv+O     e*+O  He+\
+O2      +O\002,7x,\002+N2\002,6x,\002+e       RAD      +e      +O2      +N4\
S     +NO\002,6x,\002OX       N2        e      Te       E7320\002)";
    static char fmt_7[] = "(f6.1,1p,22e9.2)";

    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real lr[22], pr[22];

    /* Fortran I/O blocks */
    static cilist io___88 = { 0, 0, 0, fmt_100, 0 };
    static cilist io___89 = { 0, 0, 0, fmt_7, 0 };


/* .......o+(2p) */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = (float)0.;
    if (*tprod3 >= *psec) {
	pr[0] = *tprod3 - *psec;
    }
    pr[1] = *psec;
    pr[2] = *heplus * *o2n * rts[92];
/* ..Fox */
    lr[0] = rts[26] * *on;
    lr[1] = rts[20] * *n2n;
    lr[2] = rts[13] * *ne;
    lr[3] = (float).218;
    lr[4] = rts[14] * *ne;
    lr[5] = (rts[85] + rts[86]) * *o2n;
/* ..Fox */
    lr[6] = rts[87] * *n4s;
/* ..Fox */
    lr[7] = rts[88] * *nno;
/* ..Fox */
    *op2p = (*tprod3 + pr[2]) / (lr[0] + lr[1] + lr[2] + lr[3] + lr[4] + lr[5]
	     + lr[6] + lr[7]);
    if (*jpt == 1 && *jpr > 0) {
	io___88.ciunit = *i__;
	s_wsfe(&io___88);
	e_wsfe();
    }
    if (*jpr > 0) {
	io___89.ciunit = *i__;
	s_wsfe(&io___89);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*op2p), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&pr[0], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&pr[1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&pr[2], (ftnlen)sizeof(real));
	for (k = 1; k <= 8; ++k) {
	    r__1 = lr[k - 1] * *op2p;
	    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	}
	do_fio(&c__1, (char *)&(*on), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*n2n), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*ne), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*te), (ftnlen)sizeof(real));
	r__2 = *op2p * (float).218 * (float).781;
	do_fio(&c__1, (char *)&r__2, (ftnlen)sizeof(real));
	e_wsfe();
    }
    return 0;
} /* cop2p_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int cnpls_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, disnp, 
	nplus, opls, n2d, op2p, heplus, photn, o2p, n4s, op2d, n2pls, nno)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *disnp, *nplus, *opls, *n2d, *op2p, *
	heplus, *photn, *o2p, *n4s, *op2d, *n2pls, *nno;
{
    /* Format strings */
    static char fmt_101[] = "(/2x,\002N+\002,20x,\002PRODUCTION\002,71x\
,\002:\002,8x,\002LOSS RATES\002/,4x,\002ALT   [N+]   [N+]c     hv+N2   O++N\
2D  O+2P+N2\002,3x,\002He++N2\002,3x,\002 hv+N   O2++N2D  N2++N4S O+(2D)+N4S\
  He++NO\002,3x,\002N++O2    N++O2    N++O2    N++O2    N++O2    N++O\002)";
    static char fmt_7[] = "(f6.1,1p,22e9.2)";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real lr[22], pr[22], cnplus;

    /* Fortran I/O blocks */
    static cilist io___94 = { 0, 0, 0, fmt_101, 0 };
    static cilist io___95 = { 0, 0, 0, fmt_7, 0 };


/* ........n+ */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = *disnp;
    pr[1] = rts[29] * *opls * *n2d;
    pr[2] = (float)0.;
    pr[3] = rts[45] * *heplus * *n2n;
    pr[4] = *photn;
    pr[5] = *o2p * *n2d * rts[78];
/* ..Fox */
    pr[6] = *n2pls * *n4s * rts[79];
/* ..Fox */
    pr[7] = *op2d * *n4s * rts[84];
/* ..Fox */
    pr[8] = rts[94] * *nno * *heplus;
/* ..Fox */
    lr[0] = rts[30] * *o2n;
/* ..Fox */
    lr[1] = rts[25] * *o2n;
/* ..Fox */
    lr[2] = rts[22] * *o2n;
/* ..Fox */
    lr[3] = rts[65] * *o2n;
/* ..Fox */
    lr[4] = rts[66] * *o2n;
/* ..Fox */
    lr[5] = rts[31] * *on;
/* ..Fox */
    cnplus = (float)0.;
    if (lr[0] + lr[1] + lr[2] > (float)0.) {
	cnplus = (pr[0] + pr[1] + pr[2] + pr[3] + pr[4] + pr[5] + pr[6] + pr[
		7] + pr[8]) / (lr[0] + lr[1] + lr[2] + lr[3] + lr[4] + lr[5]);
    }
    *nplus = cnplus;
    if (*jpt == 1 && *jpr > 0) {
	io___94.ciunit = *i__;
	s_wsfe(&io___94);
	e_wsfe();
    }
    if (*jpr > 0) {
	io___95.ciunit = *i__;
	s_wsfe(&io___95);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*nplus), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&cnplus, (ftnlen)sizeof(real));
	for (k = 1; k <= 9; ++k) {
	    do_fio(&c__1, (char *)&pr[k - 1], (ftnlen)sizeof(real));
	}
	for (k = 1; k <= 6; ++k) {
	    r__1 = lr[k - 1] * *nplus;
	    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	}
	e_wsfe();
    }
    return 0;
} /* cnpls_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int cn2a_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, n2a, 
	p3x1, p3x2, p3x3, p3x4)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *n2a, *p3x1, *p3x2, *p3x3, *p3x4;
{
    /* Format strings */
    static char fmt_102[] = "(/2x,\002N2(A)\002,12x,\002PRODUCTION\002,13x\
,\002:\002,5x,\002LOSS RATES\002,3x,\002:  Total LBH\002/,3x,\002ALT\002,3x\
,\002N2(A)\002,3x,\002e*->N2A\002,3x,\002e*->N2B\002,3x,\002e*->N2C\002,2x\
,\002N2A>O1S\002,2x,\002N2A>NO\002,2x,\002RAD\002,5x,\002LBH\002)";
    static char fmt_7[] = "(f6.1,1p,22e9.2)";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real lr[22], pr[22];

    /* Fortran I/O blocks */
    static cilist io___99 = { 0, 0, 0, fmt_102, 0 };
    static cilist io___100 = { 0, 0, 0, fmt_7, 0 };


/* ........n2(a3sigma) and total LBH */
/* ....... pr(1,2,3)= electron impact excitation of n2(a,b,c) states */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = *p3x1;
    pr[1] = *p3x2;
    pr[2] = *p3x3;
    lr[0] = rts[36] * *on;
    lr[1] = rts[27] * *on;
    lr[2] = (float).57;
    *n2a = (pr[0] + pr[1] + pr[2]) / (lr[0] + lr[1] + lr[2]);
    if (*jpt == 1 && *jpr > 0) {
	io___99.ciunit = *i__;
	s_wsfe(&io___99);
	e_wsfe();
    }
    if (*jpr > 0) {
	io___100.ciunit = *i__;
	s_wsfe(&io___100);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*n2a), (ftnlen)sizeof(real));
	for (k = 1; k <= 3; ++k) {
	    do_fio(&c__1, (char *)&pr[k - 1], (ftnlen)sizeof(real));
	}
	for (k = 1; k <= 3; ++k) {
	    r__1 = lr[k - 1] * *n2a;
	    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	}
	do_fio(&c__1, (char *)&(*p3x4), (ftnlen)sizeof(real));
	e_wsfe();
    }
    return 0;
} /* cn2a_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int cn2p_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, p1, l1, 
	n2p, p3x7, uvdisn, o2p, nno, n2plus)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *p1, *l1, *n2p, *p3x7, *uvdisn, *o2p, *
	nno, *n2plus;
{
    /* Format strings */
    static char fmt_103[] = "(/2x,\002N(2P)\002,9x,\002PRODUCTION\002,17x\
,\002:\002,20x,\002LOSS RATES\002/,3x,\002ALT\002,3x,\002[N2P]\002,3x,\002e+\
N2\002,5x,\002hv+N2\002,3x,\002e+N2+\002,6x,\002+O  \002,3x,\002+O2      +O2\
+      +NO       +2D     +4S      +e\002)";
    static char fmt_7[] = "(f6.1,1p,22e9.2)";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer k;
    static real lr[22], pr[22];

    /* Fortran I/O blocks */
    static cilist io___104 = { 0, 0, 0, fmt_103, 0 };
    static cilist io___105 = { 0, 0, 0, fmt_7, 0 };


/* ....... N(2P). the rates are from Zipf et al JGR, 1980 p687 */
/* .... 21-AUG-1992. Added N2+ recombination source */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    pr[0] = *p3x7;
    pr[1] = rts[64] * *uvdisn;
    pr[2] = rts[73] * rts[11] * *n2plus * *ne;
    lr[0] = rts[37] * *on;
    lr[1] = rts[38] * *o2n;
    lr[2] = rts[39] * *o2p;
    lr[3] = rts[40] * *nno;
    lr[4] = rts[57];
    lr[5] = rts[58];
    lr[6] = (rts[96] + rts[97]) * *ne;
/* ..Fox */
    *p1 = pr[0] + pr[1] + pr[2];
    *l1 = lr[0] + lr[1] + lr[2] + lr[3] + lr[4] + lr[5] + lr[6];
    if (*jpt == 1 && *jpr > 0) {
	io___104.ciunit = *i__;
	s_wsfe(&io___104);
	e_wsfe();
    }
    if (*jpr > 0) {
	io___105.ciunit = *i__;
	s_wsfe(&io___105);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&(*n2p), (ftnlen)sizeof(real));
	for (k = 1; k <= 3; ++k) {
	    do_fio(&c__1, (char *)&pr[k - 1], (ftnlen)sizeof(real));
	}
	for (k = 1; k <= 7; ++k) {
	    r__1 = lr[k - 1] * *n2p;
	    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	}
	e_wsfe();
    }
    return 0;
} /* cn2p_ */

/* :::::::::::::::::::::::::::::: CNOPV :::::::::::::::::::::::::::::::::: */
/* ...... This routine calculates the vibrational distribution of no+ */
/* ...... Uses AFRL report by Winick et al. AFGL-TR-87-0334, Environmental */
/* ...... Research papers, NO. 991, "An infrared spectral radiance code */
/* ...... for the auroral thermosphere (AARC) */
/* ...... Written by P. Richards in February 2004 */
/* Subroutine */ int cnopv_(jpr, i__, jpt, z__, rts, on, o2n, n2n, ne, p1, 
	nop, opls, n2pls, o2p, n4s, nno, nplus, n2p, plynop, vcon, n2d, op2d)
integer *jpr, *i__, *jpt;
real *z__, *rts, *on, *o2n, *n2n, *ne, *p1, *nop, *opls, *n2pls, *o2p, *n4s, *
	nno, *nplus, *n2p, *plynop, *vcon, *n2d, *op2d;
{
    /* Initialized data */

    static real prv1[20] = { (float)0.,(float).05,(float).07,(float).09,(
	    float).11,(float).13,(float).14,(float).17,(float).07,(float).01,(
	    float).02,(float).06,(float).08,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };
    static real prv2[20] = { (float)0.,(float).05,(float).07,(float).09,(
	    float).11,(float).13,(float).14,(float).17,(float).07,(float).01,(
	    float).02,(float).06,(float).08,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };
    static real prv3[20] = { (float)0.,(float).05,(float).07,(float).09,(
	    float).11,(float).13,(float).14,(float).17,(float).07,(float).01,(
	    float).02,(float).06,(float).08,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };
    static real prv4[20] = { (float)0.,(float).05,(float).07,(float).09,(
	    float).11,(float).13,(float).14,(float).17,(float).07,(float).01,(
	    float).02,(float).06,(float).08,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };
    static real prv5[20] = { (float)0.,(float).05,(float).07,(float).09,(
	    float).11,(float).13,(float).14,(float).17,(float).07,(float).01,(
	    float).02,(float).06,(float).08,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };
    static real prv6[20] = { (float)0.,(float).05,(float).07,(float).09,(
	    float).11,(float).13,(float).14,(float).17,(float).07,(float).01,(
	    float).02,(float).06,(float).08,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };
    static real prv7[20] = { (float)0.,(float).05,(float).07,(float).09,(
	    float).11,(float).13,(float).14,(float).17,(float).07,(float).01,(
	    float).02,(float).06,(float).08,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };
    static real prv8[20] = { (float)0.,(float).05,(float).07,(float).09,(
	    float).11,(float).13,(float).14,(float).17,(float).07,(float).01,(
	    float).02,(float).06,(float).08,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };
    static real prv9[20] = { (float)0.,(float).05,(float).07,(float).09,(
	    float).11,(float).13,(float).14,(float).17,(float).07,(float).01,(
	    float).02,(float).06,(float).08,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };
    static real prv10[20] = { (float)0.,(float).05,(float).07,(float).09,(
	    float).11,(float).13,(float).14,(float).17,(float).07,(float).01,(
	    float).02,(float).06,(float).08,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };
    static real prv12[20] = { (float)0.,(float).05,(float).07,(float).09,(
	    float).11,(float).13,(float).14,(float).17,(float).07,(float).01,(
	    float).02,(float).06,(float).08,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };
    static real k_n2_q__ = (float)7e-12;
    static real einsco1[20] = { (float)0.,(float)10.9,(float)20.2,(float)28.4,
	    (float)35.5,(float)41.5,(float)46.6,(float)50.9,(float)54.3,(
	    float)57.,(float)58.9,(float)60.2,(float)60.8,(float)60.7,(float)
	    59.9,(float)60.,(float)60.,(float)60.,(float)60.,(float)60. };
    static real einsco2[20] = { (float)0.,(float)0.,(float).697,(float)1.93,(
	    float)3.61,(float)5.74,(float)8.24,(float)11.1,(float)14.2,(float)
	    17.7,(float)21.3,(float)25.1,(float)29.,(float)33.2,(float)37.4,(
	    float)40.,(float)40.,(float)40.,(float)40.,(float)40. };
    static real lrv[20] = { (float)1.,(float).3333,(float).3333,(float).3333,(
	    float).3333,(float).3333,(float).3333,(float).3333,(float).3333,(
	    float).3333,(float).3333,(float).3333,(float).3333,(float).3333,(
	    float).3333,(float).3333,(float).3333,(float).3333,(float).3333,(
	    float).3333 };

    /* Format strings */
    static char fmt_96[] = "(/5x,\002NO+\002,34x,\002PRODUCTION\002,69x,\002\
:LOSS RATE\002/,3x,\002ALT NO+(v=0) NO+(v=1) NO+(v=2)  NO+(v=3) O++N2    N2+\
+O\002,4x,\002O2++N4S   O2++NO   N++O2    N2P+O   O++NO   hv+NO\002,4x,\002O\
ther_P   NO++e\002)";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    integer s_wsfe(), do_fio(), e_wsfe();

    /* Local variables */
    static real lrad, prv11[20], nopv[20];
    static integer k;
    static real pcasc, lnopv, pnopv, l_n2_q__, p_n2_q__;
    static integer ij;
    static real lr[22];
    static integer iv;
    static real pr[22], noptot;

    /* Fortran I/O blocks */
    static cilist io___135 = { 0, 6, 0, "(F10.1,I7,1P,22E10.2)", 0 };
    static cilist io___136 = { 0, 0, 0, fmt_96, 0 };
    static cilist io___137 = { 0, 0, 0, "(F6.1,1P,22E9.2)", 0 };


/* .. NO+(v) array dimensions */
/* .. Fractions of each source going to each vib. level. Assume */
/* .. N+ + O2 fractions for each source. NEED UPDATE */
/* .. Altitude, rate coefficients */
/* .. O, N2, O2, electron densities */
/* .. total source output for finding */
/* .. NO+, )+,N2+,O2+ densities */
/* .. N(4S), NO, N+, N(2P) densities */
/* .. Lyman-a source, N2(v) rate facto */
/* .. N(2D), O+(2D) densities */
/* .. NO+(v) densities and total NO+ d */
/* .. storage for NO+ sources and sink */
/* .. Einstein coeffs for delv=1,2 */
/* .. NO+(v) + e rate factors */
/* .. Sources and sinks of NO+(v) */
/* .. Temp total cascade source, sink */
/* .. N2 queching rate :- coeff, sourc */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
/* .. Quenching rate coeff. by N2 */
/* .. Einstein coeff delv=1 */
/* .. rate factors for NO+(v)+e -> N + O. Sheehan and St-Maurice 200 */
/* .. Einstein coeff delv=1 */
/* ... Evaluate total production and loss rates */
    pr[0] = *vcon * rts[3] * *n2n * *opls;
/* .. N2 + O+ */
    pr[1] = *n2pls * *on * rts[10];
/* .. N2+ + O */
    pr[2] = *o2p * *n4s * rts[21];
/* .. O2+ + N(4S) */
    pr[3] = *o2p * *nno * rts[23];
/* .. N+ + O2 -> O2+ + N(2D,4S) or NO+ + O(1S) */
/* .. O2+ + NO */
    pr[4] = (rts[30] + rts[66] + rts[59]) * *nplus * *o2n;
    pr[5] = rts[37] * *n2p * *on;
/* .. N2+ + O */
    pr[6] = rts[24] * *opls * *nno;
/* .. O+ + NO */
    pr[7] = *plynop * *nno;
/* .. Lyman-a + NO */
    pr[8] = *o2p * *n2d * rts[77];
/* .. Fox: O2+ + N(2D) */
    pr[9] = *n2pls * *nno * rts[80];
/* .. Fox: N2+ + NO */
    pr[10] = *nplus * *nno * rts[81];
/* .. Fox: N+ + NO */
    pr[11] = rts[83] * *nno * *op2d;
/* .. Fox: O+(2D) + NO */
    pr[12] = *op2d * rts[90] * *n2n;
/* .. -> NO+ + N, Li et al. [1997] */
    lr[0] = *ne * rts[5];
/* ..Total source term used in main program to calculate [e] */
/* .. NO+ + e */
    *p1 = pr[0] + pr[1] + pr[2] + pr[3] + pr[4] + pr[5] + pr[6] + pr[7] + pr[
	    8] + pr[9] + pr[10] + pr[11] + pr[12];
    *nop = *p1 / lr[0];
/* .. NO+ density */
    for (ij = 1; ij <= 20; ++ij) {
	nopv[ij - 1] = (float)0.;
    }
    noptot = (float)0.;
/* .. loop down evaluating the vibrational populations. Must start */
/* .. less than INV-1 because need cascade from v+2 */
    for (iv = 16; iv >= 1; --iv) {
/* ... chemical production for v=IV = total source * fraction */
	pnopv = pr[0] * prv1[iv - 1] + pr[1] * prv2[iv - 1] + pr[2] * prv3[iv 
		- 1] + pr[3] * prv4[iv - 1] + pr[4] * prv5[iv - 1] + pr[5] * 
		prv6[iv - 1] + pr[6] * prv7[iv - 1] + pr[7] * prv8[iv - 1] + 
		pr[8] * prv9[iv - 1] + pr[9] * prv10[iv - 1] + pr[10] * prv11[
		iv - 1] + pr[11] * prv12[iv - 1];
/* .. cascade production from v+1, v+2 */
	pcasc = nopv[iv] * einsco1[iv] + nopv[iv + 1] * einsco2[iv + 1];
	lrad = einsco1[iv - 1] + einsco2[iv - 1];
/* .. total radiative loss */
	l_n2_q__ = k_n2_q__ * *n2n;
/* .. sink of quanta by N2 quenchin */
	if (iv == 1) {
	    l_n2_q__ = (float)0.;
	}
	p_n2_q__ = k_n2_q__ * *n2n * nopv[iv];
/* .. source of quanta by N2 quench */
	lnopv = lr[0] * lrv[iv - 1];
/* .. evaluate NO+(iV) population */
/* .. recombination rate for level */
	nopv[iv - 1] = (pnopv + pcasc + p_n2_q__) / (lnopv + lrad + l_n2_q__);
	noptot += nopv[iv - 1];
/* ... diagnostic print. Set alt range to invoke */
/* .. total NO+ concentration */
	if (*jpr > 0 && *z__ >= (float)0. && *z__ < (float)10.) {
	    s_wsfe(&io___135);
	    do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&iv, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&pnopv, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*p1), (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&pcasc, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&p_n2_q__, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&lnopv, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&lrad, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&l_n2_q__, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&nopv[iv - 1], (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*nop), (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&noptot, (ftnlen)sizeof(real));
	    e_wsfe();
	}
    }
    pr[8] = pr[8] + pr[9] + pr[10] + pr[11];
/* .. for printing only */
    if (*jpt == 1 && *jpr > 0) {
	io___136.ciunit = *i__;
	s_wsfe(&io___136);
	e_wsfe();
    }
    if (*jpr > 0) {
	io___137.ciunit = *i__;
	s_wsfe(&io___137);
	do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	for (k = 1; k <= 4; ++k) {
	    do_fio(&c__1, (char *)&nopv[k - 1], (ftnlen)sizeof(real));
	}
	for (k = 1; k <= 9; ++k) {
	    do_fio(&c__1, (char *)&pr[k - 1], (ftnlen)sizeof(real));
	}
	r__1 = lr[0] * *nop;
	do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	e_wsfe();
    }
    return 0;
} /* cnopv_ */



/* .................................... RATES.FOR ................. */
/* .... This is the reaction rate subroutine for the FLIP model. It takes */
/* .... temperatures as input and puts the rates in array RTS. It includes */
/* .... reaction rates, efficiencies for various products, and Einstein */
/* .... coefficients. For a complete set of references see Fox and Sung JGR */
/* .... 2001, page 21,305. Rates different from Fox and Sung indicated by PGR */
/* Subroutine */ int rats_(j, te, ti, tn, rts)
integer *j;
real *te, *ti, *tn, *rts;
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double exp(), pow_dd(), sqrt();

    /* Local variables */
    static integer itjs;
    static real tot_np_o2_rate__, zed;

/* .. zero out array */
    /* Parameter adjustments */
    --rts;

    /* Function Body */
    for (itjs = 1; itjs <= 99; ++itjs) {
/* L898: */
	rts[itjs] = (float)0.;
    }
/* .. O + H+ -> O+ + H      Fox and Sung [2001] */
    zed = exp((float)-228. / *tn) * (float).6 + 1 + exp((float)-326. / *tn) * 
	    (float).2;
    rts[1] = (float)5.1199999999999997e-9 / (zed * 9) * (exp((float)-232.1 / *
	    ti) + exp((float)-228. / *ti) * (float).6 + exp((float)-326. / *
	    ti) * (float).2);
/* .. O+ + H -> O + H+    Anicich et al. [1993] */
    rts[2] = (float)6.4e-10;
/* .. O+ + N2 --> NO+ + N,   Hierl et al.[1997] */
/* .. The Hierl et al. [1997] lab rate is contaminated by N2(v) */
/* .. for T > 1300K. Therefore, the Hierl et al. rate is not really */
/* .. appropriate  in the ionosphere. The IDC model uses the Hierl e */
/* .. al. rate because it does not solve for N2(v). The FLIP model */
/* .. solves for N2(v) and uses the St. Maurice and Torr rate (JGR,1 */
    if (*ti <= (float)1e3) {
	d__1 = (doublereal) (300 / *ti);
	rts[3] = pow_dd(&d__1, &c_b199) * (float)1.2e-12;
    }
/* .. Hierl et al.[ */
    if (*ti > (float)1e3) {
	d__1 = (doublereal) (*ti / 1000);
	rts[3] = pow_dd(&d__1, &c_b200) * (float)7e-13;
    }
/* .. O+ + O2 -> O2+ + O,   Lindinger et al. [1974] */
/* .. Hierl et al. lists different rates. Hierl et al. [1997] not */
/* .. used above 1600 because rates are contaminated by O2(v) for */
/* .. T > 1000K. We don't know the vibrational state in the */
/* .. thermosphere. This fit was done by PGR May 2009. It is similar */
/* .. to Fox and Sung but does not increase sharply above 1000K. */
/* .. Hierl et al.[ */
    if (*ti <= (float)1600.) {
	d__1 = (doublereal) (300 / *ti);
	rts[4] = pow_dd(&d__1, &c_b201) * (float)1.6e-11;
    }
    if (*ti > (float)1600.) {
	d__1 = (doublereal) (*ti / 1600);
	rts[4] = pow_dd(&d__1, &c_b202) * (float)6.7e-12;
    }
/* .. NO+ + e -> N + O    Walls and Dunn [1974) */
/* .. Vejby-Christensen et al [1998] gives 4.0E-7*(300/TE)**0.5 */
/* .. Torr and Torr [1979] gives 4.3E-7*(300/TE)**0.83(-0.16,+.08) */
/* .. Sheehan and St. Maurice gives 3.5E-7*(300/TE)**0.65 */
    d__1 = (doublereal) (300 / *te);
    rts[5] = pow_dd(&d__1, &c_b203) * (float)4e-7;
/* .. O2+ + e -> O + O   Mehr and Biondi (1969) */
    if (*te <= (float)1200.) {
	d__1 = (doublereal) (300 / *te);
	rts[6] = pow_dd(&d__1, &c_b204) * (float)1.953e-7;
    }
    if (*te > (float)1200.) {
	d__1 = (doublereal) (1200 / *te);
	rts[6] = pow_dd(&d__1, &c_b205) * (float)7.389e-8;
    }
/* ..  O2 + N(4S)-> NO + O           Baulch et al.[1994] */
    rts[7] = *tn * (float)1.5e-14 * exp((float)-3270. / *tn);
/* ..   N(2D) + e -> N(4S) + e     Berrington and Burke [1981] */
    d__1 = (doublereal) (*te / (float)300.);
    rts[8] = pow_dd(&d__1, &c_b206) * (float)3.86e-10;
/* ..   NO + N(4S) -> N2 + O      Lee et al. [1978] */
    rts[9] = (float)3.4e-11;
/* .. N2+ + O -> NO+ + N   Scott et al.[1999] */
    if (*ti <= (float)1500.) {
	d__1 = (doublereal) (300 / *ti);
	rts[10] = pow_dd(&d__1, &c_b207) * (float)1.33e-10;
    }
    if (*ti > (float)1500.) {
	d__1 = (doublereal) (1500 / *ti);
	rts[10] = pow_dd(&d__1, &c_b208) * (float)6.55e-11;
    }
/* .. N2+ + e -> N + N  Mehr and Biondi (1969) */
    d__1 = (doublereal) (300 / *te);
    rts[11] = pow_dd(&d__1, &c_b209) * (float)2.2e-7;
/* .. O+(2D) + e -> O+(4S) + e   McLaughlin and Bell (1998) */
/* .. Henry [1969] gives 7.8E-8*(300/TE)**0.5 */
/* .. Zipf (1980) */
    d__1 = (doublereal) (300 / *te);
    rts[12] = pow_dd(&d__1, &c_b210) * (float)6.03e-8;
/* .. O+(2P) + e ->  O+(2D) + e   McLaughlin and Bell (1998) */
/* .. RTS(13)+RTS(14) agrees with Walker et al (1975) and */
/* .. Chang et al (1993) */
    d__1 = (doublereal) (300 / *te);
    rts[13] = pow_dd(&d__1, &c_b210) * (float)1.84e-7;
/* .. O+(2P) + e -> O+(4S) + e  McLaughlin and Bell (1998) */
    d__1 = (doublereal) (300 / *te);
    rts[14] = pow_dd(&d__1, &c_b210) * (float)3.03e-8;
/* .. N(2D) + O ->  N(4S) + O  Fell et al.[1990]. Lin and Kaufman[19 */
    rts[15] = (float)6.9e-13;
/* .. N(2D) + O2 -> NO + O  Herron[1999]. Shihira et al.[1994] */
    rts[16] = exp((float)-185. / *tn) * (float)9.7e-12;
/* .. N2+ + O2 -> O2+ + N2   Scott et al.[1999] */
    if (*ti < (float)1e3) {
	d__1 = (doublereal) (300 / *ti);
	rts[17] = pow_dd(&d__1, &c_b213) * (float)5.1e-11;
    } else if (*ti <= (float)2e3) {
	d__1 = (doublereal) (*ti / 1000);
	rts[17] = pow_dd(&d__1, &c_b214) * (float)1.26e-11;
    } else {
	rts[17] = (float)2.39e-11;
    }
/* .. thermal electron excitation of O(1D); Rees et al 1967 pss, p10 */
    rts[18] = sqrt(*te) * (float)1.1e-10 * exp((float)-22700. / *te) * (*te * 
	    (float)3.57e-5 + (float).406 - (*te * (float)1.83e-5 + (float)
	    .333) * exp((float)-13700. / *te) - (*te * (float)1.74e-5 + (
	    float).456) * exp((float)-29700. / *te));
/* .. N2 + O+(2D) -> N2+ + O */
/* ..RTS(19)=8.0E-10                   !.. Johnson and Biondi */
    d__1 = (doublereal) (300 / *ti);
    rts[19] = pow_dd(&d__1, &c_b215) * (float)1.5e-10;
/* .. N2 + O+(2P) -> N2+ + 0    Fox */
/* .. RTS(20)=6.2E-10*EXP(-340/TI)   !.. Li et al from Fox wrong */
/* .. Li et al by PGR */
    d__1 = (doublereal) (300 / *ti);
    rts[20] = pow_dd(&d__1, &c_b215) * (float)2e-10;
/* .. O2+ + N(4S) -> NO+ + 0   Scott et al.[1999] */
/* .. Li et al by PGR */
    rts[21] = (float)1e-10;
/* .. N+ + O2 -> O+ + NO */
/* .. Torr and Torr gives 6.0E-10 for total N+ + O2 reaction rate */
/* .. Dotan et al [1997] from Fox and Sung gives */
/* IF(TI.LE.1000) TOT_NP_O2_RATE=2.02E-10*(300/TI)**(-0.45) */
/* IF(TI.GT.1000) TOT_NP_O2_RATE=3.49E-10 */
/* .. does not seem to be correct. Probably vibrationally excited O2 */
/* .. Branching ratios for N+ + O2 from O'Keefe et al J. Chem. Phys. */
/* .. NO+ +O(3P) = .09, NO+ + O(1D) = .36, O2+ + N(4S) = 0.35, */
/* .. O2+ + N(2D) = 0.15, O+(4S) + NO = .05 */
    tot_np_o2_rate__ = (float)6e-10;
/* .. Total N+ + O2 rate */
    rts[22] = tot_np_o2_rate__ * (float).05;
/* .. O2+ + NO -> NO+ + O2 Midey and Viggiano [1999] */
    rts[23] = (float)4.5e-10;
/* .. O+ + NO -> O + NO+   Dotan and Viggiano [1999] */
    if (*ti <= (float)300.) {
	d__1 = (doublereal) (300 / *ti);
	rts[24] = pow_dd(&d__1, &c_b217) * (float)7e-13;
    }
    if (*ti > (float)300.) {
	d__1 = (doublereal) (*ti / 300);
	rts[24] = pow_dd(&d__1, &c_b218) * (float)7e-13;
    }
/* .. N+ + O2 -> O2+ + N(4S) */
    rts[25] = tot_np_o2_rate__ * (float).35;
/* .. O+(2P) + O -> O+(4S) + O */
/* ..RTS(26)=5.2E-10  !.. Fox appears to be wrong */
/* .. (Chang et al., JGR 1993) c.f. 5.2E-11  (Rusch) */
    rts[26] = (float)4e-10;
/* .. N2(A3sig) + O -> NO + N(2D) */
    rts[27] = (float)2e-11;
/* ..see Campbell et al. 2006 */
    rts[27] = (float)0.;
/* .. O+(2D) + O ->  O+(4S) + O  Torr and Torr [1980] */
/* .. Torr and Torr value */
    rts[28] = (float)1e-11;
/* .. O+ + N(2D) -> O + N+  Constantinides et al.[1979].Bates[1989] */
    rts[29] = (float)1.3e-10;
/* .. O2 + N+ -> O(3P) + NO+ */
/* .. Branching ratio from O'Keefe et al J. Chem. Phys. 1968 */
    rts[30] = tot_np_o2_rate__ * (float).09;
/* .. O + N+ -> O+ + N   Constantinides et al.[1979].Bates[1989] */
    rts[31] = (float)2.2e-12;
/* .. Efficiency for   N2+ + e -> N(2D) + N(2D) */
    rts[32] = (float)1.46;
/* .. N2 + O(1D) -> O + NO */
    rts[33] = exp((float)107. / *tn) * (float)1.8e-11;
/* .. O2 + O(1D) -> O + O2 */
    rts[34] = exp(67 / *tn) * (float)3.2e-11;
/* .. O2 + N(4S) -> O(1S) + NO. Kopp et al. 1977, JGR, p4715 */
    rts[35] = (float)2.5e-11;
/* .. N2(A3sig) + O -> O(1S) + N2 */
    d__1 = (doublereal) exp(*tn / 298);
    rts[36] = pow_dd(&d__1, &c_b219) * (float)2.5e-11;
/* ..  see Campbell et al. 2006 */
    rts[36] = (float)2e-11;
/* .. N(2P) + O -> products (N(2D,4S) and NO+) and O(3P,1D) */
/* .. from Piper et al 1993, J. Chem. Phys. vol 98 page 8560. */
/* .. Torr et al. */
    rts[37] = (float)1.7e-11;
/* .. N(2P) + O2 -> NO + O */
    rts[38] = exp(-60 / *tn) * (float)3.9e-12;
/* .. N(2P) quenching rates(O2+,NO) from Zipf et al jgr 1980 p687 */
    rts[39] = (float)2.2e-11;
    rts[40] = (float)1.8e-10;
/* .. N(2D) + NO -> N2 + O */
    rts[41] = (float)6.7e-11;
/* .. efficiency N2+ + O -> N2 + O+(4S) */
    if (*ti <= (float)1500.) {
	d__1 = (doublereal) (300 / *ti);
	rts[42] = pow_dd(&d__1, &c_b220) * (float)7e-12;
    }
    if (*ti > (float)1500.) {
	d__1 = (doublereal) (1500 / *ti);
	rts[42] = pow_dd(&d__1, &c_b221) * (float)4.83e-12;
    }
    rts[42] /= rts[10];
/* .. O+(2D) + O2 -> O2+ + O   Fox */
/* .. converts to efficiency */
    rts[43] = (float)7e-10;
/* .. He+ + N2 -> He + N2+ */
    rts[44] = (float)5.2e-10;
/* .. He+ + N2 -> He + N+ */
    rts[45] = (float)7.8e-10;
/* .. O(1S)+ e -> O(1D) + e */
    rts[46] = (float)8.5e-9;
/* .. O(1S)+ e -> O(3P) + e */
    d__1 = (doublereal) (*te / 300);
    rts[47] = pow_dd(&d__1, &c_b222) * (float)1.56e-10;
/* .. O(1S) + O2 -> O2 + O */
    rts[48] = exp((float)-815. / *tn) * (float)4.4e-12;
/* .. NO+ + e -> N(4S) + O */
    rts[49] = rts[5] * (float).15;
/* .. NO+ + e -> N(2D) + O */
    rts[50] = rts[5] * (float).85;
/* .. O2+ + e -> O(1D) + O */
    rts[51] = rts[6] * (float)1.11;
/* .. O2+ + e -> O(1S) + O */
    rts[52] = rts[6] * (float).05;
/* .. Efficiency for   N2+ + e -> N(4S) + N(2D) */
    rts[53] = (float).46;
/* .. O(1D) -> O + 6300 + 6364 */
    rts[54] = (float).00934;
/* .. O(1S) -> O(1D) + 5577 */
    rts[55] = (float)1.06;
/* .. O(1S) -> O(3P) + hv (2972) RTS(56)= 4.5E-2 !.. old value */
    rts[56] = rts[55] * (float).1;
/* .. N(2P) -> N(2D) + hv */
/* .. From Slanger, Spring AGU 2005 */
    rts[57] = (float).079;
/* .. N(2P) -> N(4S) + hv */
    rts[58] = (float).005;
/* .. N+ + O2 -> NO+ + O(1S) Langford et al., PSS, 33,1225,1985 */
    rts[59] = tot_np_o2_rate__ * (float).001;
/* .. Efficiency for   N2(A3sig) + O -> O(1S) + N2 */
    rts[60] = (float).37;
/* .. N(2D) -> N(4S) + hv */
    rts[61] = (float)1.07e-5;
/* .. hv(>600A) + N2 -> N(4S) + N   branching ratio */
    rts[62] = (float).5;
/* .. hv(>600A) + N2 -> N(2D) + N   branching ratio */
    rts[63] = (float).4;
/* .. hv(>600A) + N2 -> N(2P) + N   branching ratio */
    rts[64] = (float).1;
/* .. N+ + O2 -> O2+ + N(2D) */
/* .. Branching ratio from O'Keefe et al J. Chem. Phys. 1968 */
    rts[65] = tot_np_o2_rate__ * (float).15;
/* .. N+ + O2 -> NO+ + O(1D) */
/* .. Branching ratio from O'Keefe et al J. Chem. Phys. 1968 */
    rts[66] = tot_np_o2_rate__ * (float).36;
/* .. hv(Scum-Runge) + O2 -> O(1S) + O   branching ratio */
    rts[67] = (float).001;
/* .. Effic of O2(A3,DEL) + O -> O(1S) */
    rts[68] = (float).1;
/* .. O(1D) + O -> O + O   Abreu et al. PSS, p1143, 1986 */
    d__1 = (doublereal) (*tn / 300);
    rts[69] = pow_dd(&d__1, &c_b223) * (float)6.47e-12;
/* .. hv + N2 -> N+(5S) -> 2143 A emission yield from the 2s sigma g */
/* .. of N2. This was taken as 0.6 the value of Cleary and Barth JGR */
/* .. p13,635 because they did not double EUV below 250 A. */
    rts[70] = (float).06;
/* .. hv + N2 -> N+(1D) -> 6584 A emission (guess) */
    rts[71] = (float).3;
/* .. hv + N2 -> N+(1S) -> 5755 A emission (guess) */
    rts[72] = (float).03;
/* .. efficiency of production of N(2P) from e + N2+ reaction */
    rts[73] = (float).08;
/* .. Efficiency for production of O(1D) from N(2D) + O2 reaction */
/* .. See Link and Swaminathan, PSS, 1992, page 699 */
    rts[74] = (float).1;
/* .. He+ + O2 -> He + O2+ */
/* ??? check */
    rts[75] = (float)9.2e-12;
/* .. He+ + O2 -> He + O+(2D) + O(3P) */
    rts[76] = (float)2.37e-10;
/* .. O2+ + N(2D) -> NO+ + O */
    rts[77] = (float)1.8e-10;
/* .. O2+ + N(2D) -> N+ + O2 */
    rts[78] = (float)8.65e-10;
/* .. N2+ + N(4S) -> N+ + N2 */
    rts[79] = (float)1e-11;
/* .. N2+ + NO -> NO+ + N2 */
    rts[80] = (float)3.6e-10;
/* .. N+ + NO -> N(4S) + NO+ */
    d__1 = (doublereal) (300 / *ti);
    rts[81] = pow_dd(&d__1, &c_b224) * (float)4.72e-10;
/* .. N+ + NO -> N2+ + O */
    d__1 = (doublereal) (300 / *ti);
    rts[82] = pow_dd(&d__1, &c_b224) * (float)8.33e-11;
/* .. O+(2D) + NO -> NO+ + O */
    rts[83] = (float)1.2e-9;
/* .. O+(2D) + N -> N+ + O */
    rts[84] = (float)1.5e-10;
/* .. O+(2P) + O2 -> O+ + O2  Fox */
    rts[85] = (float)1.3e-10;
/* .. O+(2P) + O2 -> O2+ + O */
    rts[86] = (float)1.3e-10;
/* .. O+(2P) + N -> O+ + N(2D) */
    rts[87] = (float)1e-11;
/* .. O+(2P) + NO -> NO+ + O */
    rts[88] = (float)1.2e-9;
/* .. H+ + O2 -> O2+ + H */
    rts[89] = (float)3.8e-9;
/* .. O+(2D) + N2 -> NO+ + N  !.. Li et al. (1997). */
/* .. From the ratio of the cross sections. */
/* .. The branching ratio to O+(4S) + N2 not given by Li et al. */
    rts[90] = (float)2.5e-11;
/* .. He+ + O2 -> He + O+(4S) + O */
    rts[91] = (float)2.39e-11;
/* .. He+ + O2 -> He + O+(2P) + O */
    rts[92] = (float)6.04e-10;
/* .. He+ + O2 -> He + O+(4S) + O(1D) */
    rts[93] = (float)4.6e-11;
/* .. He+ + NO -> He + N+ + O */
    rts[94] = (float)1.35e-9;
/* .. He+ + NO -> He + O+ + N */
    rts[95] = (float)1e-10;
/* .. N(2P) + e -> N(4S) + e */
    d__1 = (doublereal) (*te / 300);
    rts[96] = pow_dd(&d__1, &c_b203) * (float)2.04e-10;
/* .. N(2P) + e -> N(2D) + e */
    rts[97] = (float)9.5e-9;
/* .. O(1D) + e -> O(3P) + e */
    d__1 = (doublereal) (*te / 300);
    rts[98] = pow_dd(&d__1, &c_b227) * (float)2.87e-10;
/* .. N2+ + O -> O+ + N2  !.. McFarland et al.(1974) */
/* .. From Fox and Sung 2001 */
    d__1 = (doublereal) (300 / *ti);
    rts[99] = pow_dd(&d__1, &c_b228) * (float)7.0000000000000009e-12;
    return 0;
} /* rats_ */



/* .........................<PESIMP.FOR>......................3 APR 92 */
/* ...... This test driver demonstrates how to call the model and */
/* ...... how to calculate electron heating rate and 3371 excitation rate. */
/* Subroutine */ int seciprd_(alt, szadeg, f107, f107a, te, tn, oxn, o2n, n2n,
	 xne, n2aprd)
real *alt, *szadeg, *f107, *f107a, *te, *tn, *oxn, *o2n, *n2n, *xne, *n2aprd;
{
    /* Initialized data */

    static real sprd[18]	/* was [3][6] */ = { (float).4,(float).56,(
	    float).44,(float).4,(float).28,(float).44,(float).2,(float).06,(
	    float).1,(float)0.,(float).05,(float)0.,(float)0.,(float).05,(
	    float)0.,(float)0.,(float)0.,(float).02 };
    static integer imax = 0;

    /* System generated locals */
    integer i__1;

    /* Local variables */
    static real sign2, xop2d, e;
    static integer i__, k;
    static real sigee, peflx, sigit[3], sigex[22], sigox;
    extern /* Subroutine */ int oxrat_();
    static real de[501];
    static integer ik;
    static real ep, ev[501], xn[3];
    extern /* Subroutine */ int flxcal_(), sigexs_();
    static real peflux[501];
    extern /* Subroutine */ int oxsigs_(), txsion_();
    static real xn2d, afac;

/* -- loop control variables */
/* .. Array dimensions */
/* .. Maximum PE energy */
/* -- PE flux */
/* -- Total electron impact cross sections */
/* -- Electron impact cross sections for OX */
/* -- ALT = altitude (km)  { 120 -> 500 } */
/* -- solar zenith angle {0 -> 90 degrees} */
/* -- F107 = Solar 10.7 cm flux */
/* -- electron, neutral temperatures (K) */
/* -- XN, O, O2, N2, neutral densities  (cm */
/* -- electron density  (cm-3) */
/* -- N(2D) density for N(2D) + e -> 2.5 eV */
/* -- O+(2D) density for O+(2D) + e -> 3.3 */
/* .. Total exciation cross sections for O, */
/* .. Production of N2A */
/* .. various ionization and excitation rates by EUV and PE */
/* .. Transfer neutral densities to the density array */
/* .. Initialize IMAX Reset in FLXCAL */
    xn[0] = *oxn;
    xn[1] = *o2n;
    xn[2] = *n2n;
    *n2aprd = (float)0.;
    for (k = 1; k <= 3; ++k) {
	for (ik = 1; ik <= 6; ++ik) {
	    euvprd_1.pepion[k + ik * 3 - 4] = (float)1e-15;
	    euvprd_1.pexcit[k + ik * 3 - 4] = (float)1e-15;
	}
    }
/* .. Cannot calculate PE if no densities */
    if (*oxn < (float)1e5 || *n2n < (float)1e5) {
	return 0;
    }
    if (*szadeg > (float)105.) {
	return 0;
    }
/* ***************************************************************** */
/* .. Go and get the photoelectron fluxes */
    xn2d = (float)0.;
/* .. N(2D) density for calculating N(2D) + e -> 2.5 */
    xop2d = (float)0.;
/* .. O+(2D) density for calculating O+(2D) + e -> 3. */
    flxcal_(&c__501, alt, szadeg, te, tn, xn, xne, &xn2d, &xop2d, peflux, &
	    afac, &imax, de, ev);
/* *************************************************************** */
/* ........ sample calculation of ion production rates. */
    i__1 = imax;
    for (i__ = 1; i__ <= i__1; ++i__) {
	e = ev[i__ - 1];
	txsion_(&e, sigit);
/* .. total ion XS */
	sigexs_(&e, te, xne, &sigox, &sign2, &sigee);
/* .. Total excitation XS */
	oxsigs_(&e, sigex, &sigox);
/* .. OX cross sections */
	if (e < (float)250.) {
	    *n2aprd += peflux[i__ - 1] * (float).22 * sign2 * xn[2] * de[i__ 
		    - 1];
	}
/* .. */
	euvprd_1.pexcit[0] += peflux[i__ - 1] * sigex[0] * xn[0] * de[i__ - 1]
		;
/* .. O(1 */
	euvprd_1.pexcit[3] += peflux[i__ - 1] * sigex[1] * xn[0] * de[i__ - 1]
		;
/* .. Evaluate ionization branching ratios for O+ */
/* .. O(1 */
	oxrat_(&e, sprd, &sprd[3], &sprd[6]);
/* .. Calculate ion production rates */
	for (k = 1; k <= 3; ++k) {
	    for (ik = 1; ik <= 6; ++ik) {
		euvprd_1.pepion[k + ik * 3 - 4] += peflux[i__ - 1] * sigit[k 
			- 1] * xn[k - 1] * sprd[k + ik * 3 - 4] * de[i__ - 1];
	    }
	}
	ep = e + 17;
	peflx = peflux[i__ - 1] / (float)12.57;
/*      WRITE(29,'(3F8.1,1P,22E10.2)') ALT,E,12398/EP,PEFLX, */
/*     >     PEFLUX(I),(SIGIT(K),K=1,3),T_XS_OX(EP),2.2*T_XS_OX(EP), */
/*     >     T_XS_N2(EP),PEPION(1,1),PEXCIT(1,1) */
    }
    return 0;
} /* seciprd_ */

/* :::::::::::::::::::::::::: PHOTOELECTRON MODEL  :::::::::::::::::::::::: */
/* ....... This subroutine evaluates the photoelectron flux using the concept */
/* .......  production frequencies developed by Phil Richards at Utah */
/* ....... State University March 1984. It supercedes the model described in */
/* ....... JGR, p2155, 1983. Contact EAST::CSPARA::RICHARDS on SPAN network */
/* ------- Some minor updates in April 1992 indicated by C---- */
/* ....... I would appreciate any feedback on bugs or clarity and if it */
/* ....... contributes substantially to a paper, I would appreciate the */
/* ....... appropriate acknowledgement. */
/* ......       **************** WARNING **************** */
/* ...... This program is constructed to produce reasonable agreement with */
/* ...... the Atmosphere Explorer-E PES fluxes of John Doering (Lee et al. */
/* ...... PSS 1980, page 947). It will NOT give good fluxes if the EUV */
/* ...... attenuation is greater than about a factor of 7 (AFAC < 0.14). */
/* ...... The model accurately reproduces the measured fluxes very closely */
/* ...... for the case in the test driver at 148 km SZA=53 when AFAC=0.19. */
/* ...... You should compare the output against the Lee et al. 1980 fluxes */
/* ...... periodically as a check. It is doubtful below 140km during the */
/* ...... day and below 200km near sunset. Between 200km & 350km, it should */
/* ...... be good for solar zenith angles < 90 degrees. Above 350 km there */
/* ...... is considerable uncertainty due to neglect of transport but most */
/* ...... models have similar uncertainties at high altitudes due to the */
/* ...... uncertainty in the conjugate photoelectron flux, and the pitch */
/* ...... angle distribution. */

/* ------ ALT = altitude (km)  { 120 -> 500 } */
/* ------ SZADEG = solar zenith angle  {0 -> 90 degrees ? } */
/* ------ TE, TN = electron, neutral temperatures (K) */
/* ------ XN, XNE = O, O2, N2, and electron densities  (cm-3) */
/* ------ XN2D, XOP2D = N(2D) and O+(2D) densities for electron quenching */
/* ------ (cm-3). You may put these to ZERO if not available. */
/* ------ PEFLUX = photoelectron flux to be returned (eV cm2 sec)-1 */
/* ------ AFAC = the solar EUV attenuation warning flag */
/* Subroutine */ int flxcal_(idim, alt, szadeg, te, tn, xn, xne, xn2d, xop2d, 
	peflux, afac, imax, de, ev)
integer *idim;
real *alt, *szadeg, *te, *tn, *xn, *xne, *xn2d, *xop2d, *peflux, *afac;
integer *imax;
real *de, *ev;
{
    /* Initialized data */

    static real rjox[84] = { (float)19.,(float)19.,(float)19.,(float)19.,(
	    float)19.,(float)19.,(float)19.,(float)19.,(float)19.,(float)19.,(
	    float)15.,(float)18.,(float)14.,(float)10.,(float)13.,(float)9.,(
	    float)13.,(float)9.,(float)7.,(float)11.,(float)6.,(float)26.,(
	    float)6.,(float)31.,(float)6.,(float)5.,(float)22.,(float)4.,(
	    float)4.,(float)5.,(float)4.04,(float)2.56,(float)1.9,(float)2.28,
	    (float)2.12,(float).96,(float).24,(float).14,(float).14,(float).1,
	    (float).1,(float).1,(float).1,(float).1,(float).05,(float).05,(
	    float).05,(float).05,(float).05,(float).05,(float).05,(float).05,(
	    float).05,(float).05,(float).04,(float).04,(float).04,(float).04,(
	    float).04,(float).04,(float).04,(float).04,(float).04,(float).04,(
	    float).01,(float).01,(float).01,(float).01,(float).01,(float).01,(
	    float).01,(float).01,(float).01,(float).01,(float).02,(float).02,(
	    float).02,(float).02,(float).02,(float).02,(float).02,(float).02,(
	    float).02,(float).02 };
    static real rjn2[84] = { (float)40.,(float)40.,(float)40.,(float)40.,(
	    float)40.,(float)40.,(float)43.,(float)35.,(float)35.,(float)28.,(
	    float)29.,(float)21.,(float)25.,(float)19.,(float)19.,(float)13.,(
	    float)19.,(float)16.,(float)12.,(float)11.,(float)7.,(float)18.,(
	    float)8.,(float)46.,(float)27.,(float)5.,(float)5.,(float)5.,(
	    float)5.,(float)5.,(float)5.34,(float)2.92,(float)1.84,(float)
	    2.22,(float)1.62,(float).62,(float).05,(float).05,(float).05,(
	    float).05,(float).05,(float).05,(float).05,(float).044,(float).02,
	    (float).02,(float).02,(float).02,(float).02,(float).02,(float).02,
	    (float).02,(float).02,(float).02,(float).01,(float).01,(float).01,
	    (float).01,(float).01,(float).01,(float).01,(float).01,(float).01,
	    (float).01,(float).01,(float).01,(float).01,(float).01,(float).01,
	    (float).01,(float).01,(float).01,(float).01,(float).01,(float).01,
	    (float).01,(float).01,(float).01,(float).01,(float).01,(float).01,
	    (float).01,(float).01,(float).01 };
    static real en[84] = { (float).5,(float)1.5,(float)2.5,(float)3.5,(float)
	    4.5,(float)5.5,(float)6.5,(float)7.5,(float)8.5,(float)9.5,(float)
	    10.5,(float)11.5,(float)12.5,(float)13.5,(float)14.5,(float)15.5,(
	    float)16.5,(float)17.5,(float)18.5,(float)19.5,(float)20.5,(float)
	    21.5,(float)22.5,(float)23.5,(float)24.5,(float)25.5,(float)26.5,(
	    float)27.5,(float)28.5,(float)29.5,(float)32.5,(float)37.5,(float)
	    42.5,(float)47.5,(float)52.5,(float)57.5,(float)62.5,(float)67.5,(
	    float)72.5,(float)77.5,(float)82.5,(float)87.5,(float)92.5,(float)
	    97.5,(float)105.,(float)115.,(float)125.,(float)135.,(float)145.,(
	    float)155.,(float)165.,(float)175.,(float)185.,(float)195.,(float)
	    205.,(float)215.,(float)225.,(float)235.,(float)245.,(float)255.,(
	    float)265.,(float)275.,(float)285.,(float)295.,(float)305.,(float)
	    315.,(float)325.,(float)335.,(float)345.,(float)355.,(float)365.,(
	    float)375.,(float)385.,(float)395.,(float)405.,(float)415.,(float)
	    425.,(float)435.,(float)445.,(float)455.,(float)465.,(float)475.,(
	    float)485.,(float)495. };
    static real delte[84] = { (float)1.,(float)1.,(float)1.,(float)1.,(float)
	    1.,(float)1.,(float)1.,(float)1.,(float)1.,(float)1.,(float)1.,(
	    float)1.,(float)1.,(float)1.,(float)1.,(float)1.,(float)1.,(float)
	    1.,(float)1.,(float)1.,(float)1.,(float)1.,(float)1.,(float)1.,(
	    float)1.,(float)1.,(float)1.,(float)1.,(float)1.,(float)1.,(float)
	    5.,(float)5.,(float)5.,(float)5.,(float)5.,(float)5.,(float)5.,(
	    float)5.,(float)5.,(float)5.,(float)5.,(float)5.,(float)5.,(float)
	    5.,(float)10.,(float)10.,(float)10.,(float)10.,(float)10.,(float)
	    10.,(float)10.,(float)10.,(float)10.,(float)10.,(float)10.,(float)
	    10.,(float)10.,(float)10.,(float)10.,(float)10.,(float)10.,(float)
	    10.,(float)10.,(float)10.,(float)10.,(float)10.,(float)10.,(float)
	    10.,(float)10.,(float)10.,(float)10.,(float)10.,(float)10.,(float)
	    10.,(float)10.,(float)10.,(float)10.,(float)10.,(float)10.,(float)
	    10.,(float)10.,(float)10.,(float)10.,(float)10. };
    static real emax = (float)286.;

    /* System generated locals */
    integer i__1;
    real r__1;

    /* Builtin functions */
    double sqrt(), exp();
    integer i_nint();

    /* Local variables */
    static real prod, casn2, epn2d, sign2, pop2d;
    static integer i__;
    static real xsn2t, xso2t, casel, sigee, casox, colum[3], sigox, rloss, 
	    xsoxt, epop2d, prodn2, ee;
    static integer ie;
    static real ep;
    extern /* Subroutine */ int facflx_(), scolum_(), sigexs_();
    static real prodox;
    extern doublereal t_xs_n2__();
    static real tau, sza;
    extern doublereal t_xs_ox__();
    static real pn2d, ffac;

/* .. maximum photoelectron energy. */
/*      REAL RJOX(RDIM),RJN2(RDIM),XN(3),COLUM(3),PEFLUX(IDIM) */
/*     >  ,DE(RDIM),DELTE(RDIM),EV(RDIM),EN(RDIM),UVFAC,EUV */
/*      COMMON/SOL/UVFAC(59),EUV */
/* .. photoelectron production frequencies by 1.0E9. Renormalized be */
/* -- O production frequencies */
    /* Parameter adjustments */
    --peflux;
    --xn;
    --de;
    --ev;

    /* Function Body */
/* -- N2 production frequencies */
/* -- PE energy grid */
/* -- PE energy steps */
/* ..  Maximum PE energy */
    sza = *szadeg / (float)57.29578;
/* .. convert solar zenith angle to radians */
    if (*imax < 10) {
/* .. transfer energy grid to pass back */
	for (ie = 1; ie <= 84; ++ie) {
	    if (en[ie - 1] < emax) {
		*imax = ie;
	    }
	    de[ie] = delte[ie - 1];
	    ev[ie] = en[ie - 1];
	}
    }
/* .. 2.5eV production from electron quenching of N2D */
    pn2d = *xn2d * *xne * (float)6e-10 * sqrt(*te / (float)300.);
/* .. 3.3eV production from electron quenching of O+(2D) */
    pop2d = *xop2d * *xne * (float)6.6e-8 * sqrt((float)300. / *te);
    casel = (float)0.;
/* .. evaluate the neutral column density  &&&&&&&& */
    r__1 = *alt * (float)1e5;
    scolum_(&i__, &sza, &r__1, tn, &xn[1], colum);
/* ...... begin flux calculation loop............................ */
    i__1 = *imax;
    for (ie = 1; ie <= i__1; ++ie) {
	i__ = *imax + 1 - ie;
	if (i__ < 1) {
	    goto L55;
	}
	peflux[i__] = (float)0.;
/* ... evaluate energy of photon responsible for electron at energ */
	ee = ev[i__];
	ep = ee + 17;
	if (ee < (float)22.) {
	    ep = (float)45.;
	}
	if (ee >= (float)22. && ee < (float)28.) {
	    ep = (float)41.;
	}
	if (ee >= (float)28. && ee < (float)38.) {
	    ep = (float)49.;
	}
/* .. evaluate total photoionization cross sections for photon ene */
	xsoxt = t_xs_ox__(&ep);
/* .. New OX cross section */
	xso2t = t_xs_ox__(&ep) * (float)2.2;
/* .. O2 XS is 2.2* O XS */
	xsn2t = t_xs_n2__(&ep);
/* ... evaluate EUV attenuation factor AFAC */
/* .. New N2 cross section */
	tau = colum[0] * xsoxt + colum[1] * xso2t + colum[2] * xsn2t;
	*afac = exp(-tau);
/* ..... low energy cascade production from O(1D) and N2* impact */
	casox = (float)0.;
	if (ee < (float)10.) {
	    casox = peflux[i__ + 2] * sigox * xn[1];
	}
	casn2 = (float)0.;
	if (ee < (float)6.) {
	    casn2 = peflux[i__ + 1] * sign2 * xn[3];
	}
/* ..... cascade production from thermal electron degradation */
	casel = (float)0.;
	if (i__ < *imax) {
	    casel = peflux[i__ + 1] * sigee * *xne;
	}
/* ... Production from electron quenching of metastables */
	epn2d = (float)0.;
	if (i_nint(&ee) == 3) {
	    epn2d = pn2d;
	}
	epop2d = (float)0.;
	if (i_nint(&ee) == 4) {
	    epop2d = pop2d;
	}
/* .... evaluate cross sections (must be after cascade production) */
	sigexs_(&ee, te, xne, &sigox, &sign2, &sigee);
/* ..... adjust EUV production rate for different period of solar */
	facflx_(&ee, sol_1.uvfac, &ffac);
/* ..... Production of pe's at energy EE, taking into account */
/* ..... attenuation and EUV variation, and renormalize frequencie */
	prodox = rjox[i__ - 1] * xn[1] * *afac * ffac * (float)1e-9;
	prodn2 = rjn2[i__ - 1] * xn[3] * *afac * ffac * (float)1e-9;
/* ..... Sum all the production rates */
	prod = prodox + prodn2 + casel + casox + casn2 + epn2d + epop2d;
/* .... total loss through collisions */
	rloss = sigox * xn[1] + sign2 * xn[3] + sigee * *xne;
/* ....... evaluate photoelectron flux */
	peflux[i__] = prod / rloss;
/* L133: */
    }
L55:
    return 0;
} /* flxcal_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int facflx_(ee, uvfac, ffac)
real *ee, *uvfac, *ffac;
{
/* ....... solar UVFAC factors. Correspond to the first 9 wavelengths */
/* ....... TORR et al.[1979] GRL page 771 table 3. UVFAC(9) is for 304A */
    /* Parameter adjustments */
    --uvfac;

    /* Function Body */
    *ffac = (uvfac[9] * 7 + uvfac[8] + uvfac[6] * (float).2) / (float)8.2;
    if (*ee > (float)30. && *ee <= (float)38.) {
	*ffac = (uvfac[7] * 2 + uvfac[5] * (float).5) / (float)2.5;
    }
    if (*ee > (float)38. && *ee <= (float)45.) {
	*ffac = uvfac[4];
    }
    if (*ee > (float)45. && *ee <= (float)66.) {
	*ffac = uvfac[3];
    }
    if (*ee > (float)66. && *ee <= (float)108.) {
	*ffac = uvfac[2];
    }
    if (*ee > (float)108.) {
	*ffac = uvfac[1];
    }
    return 0;
} /* facflx_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int sigexs_(e, te, xne, sigox, sign2, sigee)
real *e, *te, *xne, *sigox, *sign2, *sigee;
{
    /* System generated locals */
    real r__1, r__2, r__3;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double pow_dd(), r_lg10(), exp();

    /* Local variables */
    static real sigo, sigo1d, al, et, sigion;

/* ..... Program for evaluating the total inelastic cross sections */

/* ........ loss to thermal electrons .... */
    et = *te * (float)8.618e-5;
    d__1 = (doublereal) (*e);
    d__2 = (doublereal) (*xne);
    d__3 = (doublereal) ((*e - et) / (*e - et * (float).53));
    *sigee = (float)3.37e-12 / pow_dd(&d__1, &c_b222) / pow_dd(&d__2, &c_b237)
	     * pow_dd(&d__3, &c_b238);

/* ...... cross section for o(1d) */
    sigo1d = (float)0.;
    if (*e > (float)1.96) {
/* Computing 2nd power */
	r__1 = 1 - (float)1.96 / *e;
	sigo1d = r__1 * r__1 * (float)4e-16 / *e;
    }
/* ...... total excitation cross section for O excluding O(1D) */
    if (*e < (float)25.) {
	sigo = (*e * (float).4 - 5) * (float)1.4e-17;
    }
    if (*e >= (float)25.) {
	sigo = (float)7e-17;
    }
    if (sigo < (float)0.) {
	sigo = (float)0.;
    }

/* ...... total excitation cross section for N2...... */
    if (*e < (float)12.) {
	*sign2 = (*e * (float)15.5 - (float)104.8) * (float)1.7e-18;
    }
    if (*e < (float)4.) {
/* Computing 9th power */
	r__1 = 1 - (float)1.4 / *e, r__2 = r__1, r__1 *= r__1, r__1 *= r__1;
/* Computing 16th power */
	r__3 = (float)1.4 / *e, r__3 *= r__3, r__3 *= r__3, r__3 *= r__3;
	*sign2 = r__2 * (r__1 * r__1) * (float)5e-9 * (r__3 * r__3);
    }
    if (*e > (float)11.5) {
	*sign2 = (float)1.4e-16;
    }
    if (*sign2 < (float)0.) {
	*sign2 = (float)0.;
    }

/* ........ total ionization cross sections from Keiffer and Dunn .... */
    sigion = (float)0.;
    al = r_lg10(e);
    if (al < (float)2.7 && al >= (float)1.2) {
	sigion = (al - (float)1.2) * (float)-3.6e-16 * (al - 3);
    }
    if (al > (float)2.7) {
	sigion = exp(-al * (float)1.6) * (float)1.2e-14;
    }
    if (*e < (float)50.) {
	sigion = (*e * (float).068 - (float)1.06) * (float)1e-16;
    }
    if (sigion <= (float)0.) {
	sigion = (float)0.;
    }

    *sigox = sigo1d + sigo + sigion * (float).5;
    *sign2 += sigion;
    return 0;
} /* sigexs_ */

/* ::::::::::::::::::::::: TXSION :::::::::::::::::::::::::::::::::: */
/* ..... total ionization cross sections for O, O2, and N2 */
/* ..... ionization cross sections keiffer and dunn ........ */
/* ..... The N2+ and O2+ cross sections were modified in April 99 to agree */
/* ..... with the Schram et al. cross sections at high energies */
/* Subroutine */ int txsion_(e, sigit)
real *e, *sigit;
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double r_lg10(), exp(), pow_dd();

    /* Local variables */
    static real sigtmp;

/* ... SIGTMP is used for N2+ and O2+ at the high energies */
    /* Parameter adjustments */
    --sigit;

    /* Function Body */
    sigtmp = exp(r_lg10(e) * (float)-2.303) * (float)1e-13;
/* ... N2+ cross section */
    sigit[3] = (float)0.;
    if (*e > (float)15.) {
	d__1 = (doublereal) (1 - (float)9. / *e);
	d__2 = (doublereal) (*e);
	sigit[3] = pow_dd(&d__1, &c_b240) * (float)1.42e-14 * pow_dd(&d__2, &
		c_b241);
    }
    if (sigtmp < sigit[3]) {
	sigit[3] = sigtmp;
    }
/* ... This correction to convert units to cm**2. Keiffer and Dunn p */
    sigit[3] *= (float).87972;
/* ... O2+ cross section */
    sigit[2] = (float)0.;
    if (*e > (float)12.) {
	d__1 = (doublereal) (1 - (float)7. / *e);
	d__2 = (doublereal) (*e);
	sigit[2] = pow_dd(&d__1, &c_b242) * (float)1.08e-14 * pow_dd(&d__2, &
		c_b243);
    }
    if (sigtmp < sigit[2]) {
	sigit[2] = sigtmp;
    }
/* ... This correction to convert units to cm**2. Keiffer and Dunn p */
    sigit[2] *= (float).87972;
/* ... O+ cross section from Brook et al. J. Phys. B. Vol 11 p 3115, */
    sigit[1] = (float)0.;
    if (*e > (float)12.) {
	d__1 = (doublereal) (1 - (float)2. / *e);
	d__2 = (doublereal) (*e);
	sigit[1] = pow_dd(&d__1, &c_b244) * (float)7.33e-15 * pow_dd(&d__2, &
		c_b241);
    }
    return 0;
} /* txsion_ */

/* :::::::::::::::::::::::::::::::::::: OXRAT :::::::::::::::::::::::::::::::: */
/* Subroutine */ int oxrat_(e, r4s, r2d, r2p)
real *e, *r4s, *r2d, *r2p;
{
    static real rtot, ev;

/* ....... This subroutine returns the electron impact branching ratios */
/* ....... for atomic oxygen from Burnett and Rountree Phys. Rev. A. 20 */
/* ....... 1979 page 1468 */
    *r4s = (float)1.;
    *r2d = (float)0.;
    *r2p = (float)0.;
    ev = *e;
    if (*e > (float)100.) {
	ev = (float)100.;
    }
    if (ev > (float)17.) {
	*r4s = ev * (float)-.0016 + (float).56;
    }
    if (ev > (float)17.) {
	*r2d = ev * (float).001067 + (float).2933;
    }
    *r2p = 1 - *r4s - *r2d;
    if (ev < (float)22.) {
	*r2p = (float)0.;
	rtot = *r4s + *r2d;
	*r4s /= rtot;
	*r2d /= rtot;
    }
    return 0;
} /* oxrat_ */

/* ::::::::::::::::::::: T_XS_N2 ::::::::::::::::::::::::::: */
/* .... This function calculates the N2 total photoionization */
/* .... cross section. P. Richards 2003-10-04 */
doublereal t_xs_n2__(ep)
real *ep;
{
    /* Initialized data */

    static real esave = (float)0.;

    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double log(), exp();

/* ... photon energy */
/* .. Wavelength < 20 A, Auger ionization */
    if (*ep >= (float)600.) {
	ret_val = (float)5e-19;
/* .. Wavelength < 31 A, Auger ionization */
    } else if (*ep >= (float)400.) {
	ret_val = (float)1e-18;
/* .. Wavelength 31.62 to 23.70 A */
    } else if (*ep >= (float)392.) {
	ret_val = exp(log(*ep) * (float)7.9864 - (float)91.6604);
/* .. Wavelength 225 to 125 A */
    } else if (*ep >= (float)55.09) {
	ret_val = exp(log(*ep) * (float)-2.3711 - (float)29.8142);
/* .. Wavelength > 225 A */
    } else {
	ret_val = exp(log(*ep) * (float)-1.1077 - (float)34.8787);
    }
/* ..IF(NINT(10*EP).NE.NINT(10*ESAVE)) WRITE(6,'(2F8.1,1P,2E10.2)') */
/* ..> 12394.224/EP,EP, T_XS_N2/(3.39E-17*EXP(-0.0263*EP)), T_XS_N2 */
    esave = *ep;
/* .. old parameterization */
/* ..T_XS_N2=3.39E-17*EXP(-0.0263*EP) */
    return ret_val;
} /* t_xs_n2__ */

/* ::::::::::::::::::::: T_XS_OX ::::::::::::::::::::::::::: */
/* .... This function calculates the OX total photoionization */
/* .... cross section. P. Richards 2003-10-04 */
/* .... Samson and Pareek Phys. Rev. A, 31, 1470, 1985 */
doublereal t_xs_ox__(ep)
real *ep;
{
    /* Initialized data */

    static real esave = (float)0.;

    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double log(), exp();

/* ... photon energy */
/* .. NEW parameterization */
    if (*ep >= (float)500.) {
/* .. Wavelength shorter than 25 A, Auger ionization */
	ret_val = (float)5e-19;
    } else if (*ep >= (float)165.26) {
/* .. Wavelength shorter than 75 A */
	ret_val = exp(log(*ep) * (float)-2.5209 - (float)28.8855);
    } else if (*ep >= (float)55.09) {
/* .. Wavelength between 78 and 256.26 A */
	ret_val = exp(log(*ep) * (float)-1.7871 - (float)32.6335);
    } else {
/* .. Wavelength longer than 256.26 A */
	ret_val = exp(log(*ep) * (float)-1.3077 - (float)34.5556);
    }
/* ..IF(NINT(10*EP).NE.NINT(10*ESAVE)) WRITE(6,'(2F8.1,1P,2E10.2)') */
/* ..> 12394.224/EP,EP, T_XS_OX/(27.2E-18*EXP(-3.09E-2*EP)), T_XS_OX */
    esave = *ep;
/* .. old parameterization */
/* .. T_XS_OX=27.2E-18*EXP(-3.09E-2*EP) */
    return ret_val;
} /* t_xs_ox__ */



/* :::::::::::::::::::::: OXSIGS ::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int oxsigs_(e, sigex, sigext)
real *e, *sigex, *sigext;
{

    /* System generated locals */
    real r__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(), pow_dd();

    /* Local variables */
    static integer i__;

/* ....... Inelastic cross sections for electron impact on atomic oxygen */
/* ....... E=electron energy, SIGEX(22)=array of partial cross sections, */
/* ....... SIGEXT=total excitation cross section, and S */
    /* Parameter adjustments */
    --sigex;

    /* Function Body */
    for (i__ = 1; i__ <= 22; ++i__) {
/* L9: */
	sigex[i__] = (float)0.;
    }
/* ..- CROSS SECTION FOR O(1D) - New Doering cross section from JGR */
/* ..- p19531, 1992. Increases production by a factor of 1.13 */
/* ..      IF(E.GT.6.5) SIGEX(1)=3.77E-15*(1-2.0/E)**4.25/E**1.7 */
/* ..      IF(E.LE.7.3) SIGEX(1)=SO1D(NINT(E))*1.0E-18 */

/* ..... Old cross section of Henry */
    if (*e > (float)1.96) {
/* Computing 2nd power */
	r__1 = 1 - (float)1.96 / *e;
	sigex[1] = r__1 * r__1 * (float)4e-16 / *e;
    }
/* ........ O(1S) cross section: may be double Shyn et al. JGR 1986, 13751 */
    if (*e > (float)4.17) {
	sigex[2] = (1 - sqrt((float)4.17 / *e)) * (float)6.54e-17 / *e;
    }
/* ....... 1304, 1027 A, Zipf and Erdman JGR 1985, 11088 include cascade. */
/* ....... Direct excitation is half for  1304 (Vaughan and Doering, */
/* ........ JGR 1986, 13755 and 1987 in press) */
    if (*e >= (float)10.) {
/* Computing 2nd power */
	r__1 = *e;
	sigex[3] = (*e - 10) * (float)6.76e-16 / (r__1 * r__1);
    }
/* ....... 989 cross section from Doering 1987 (1/2 of Zipf) */
    if (*e >= (float)14.) {
	sigex[4] = (1 - 14 / *e) * (float)7e-17 / sqrt(*e);
    }
    sigex[5] = sigex[4] * (float).38;
/* ....... O(5S) 1356 A Stone And Zipf Corrected By Zipf And Erdman 1985 */
/* ..- reparameterized 1 May 92 using FITXS.FOR (PGR) */
    if (*e > (float)10.) {
	d__1 = (doublereal) ((float)1. - (float)9. / *e);
	d__2 = (doublereal) (*e);
	sigex[6] = pow_dd(&d__1, &c_b251) * (float)4.867e-12 / pow_dd(&d__2, &
		c_b252);
    }
    *sigext = sigex[1] + (sigex[2] + sigex[3] + sigex[4] + sigex[5] + sigex[6]
	    );
    return 0;
} /* oxsigs_ */



/* .................... RSPRIM.FOR .................................. */
/* .... This routine evaluates the ionization rates for photon impact */
/* .... It is based on a FLIP model routine that was modified in August */
/* .... 2009 for the chemical equilibrium model by P. richards. */
/* Subroutine */ int primpr_(ij, z__, zox, zn2, zo2, he, sza, tn, f107, f107a,
	 n4s)
integer *ij;
real *z__, *zox, *zn2, *zo2, *he, *sza, *tn, *f107, *f107a, *n4s;
{
    /* Initialized data */

    static integer lmax = 0;
    static real f107sv = (float)0.;
    static integer iprobs = 0;
    static real fnite[37] = { (float)9e5,(float)0.,(float)9e5,(float)0.,(
	    float)0.,(float)9e6,(float)0.,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)
	    0.,(float)0.,(float)0.,(float)3e5,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)3e5,(
	    float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)
	    0.,(float)0. };
    static real fnfac = (float)1.;
    static real o2lyxs = (float)1e-20;
    static real o2srxs = (float)1e-21;
    static real freqsr = (float)5e-6;
    static real xsnpls[37] = { (float)0.,(float)0.,(float)0.,(float)0.,(float)
	    0.,(float)0.,(float).211,(float)10.294,(float)11.171,(float)
	    10.961,(float)11.244,(float)11.323,(float)12.098,(float)13.265,(
	    float)12.423,(float)11.951,(float)11.212,(float)11.798,(float)
	    11.758,(float)11.778,(float)11.772,(float)11.503,(float)11.016,(
	    float)10.578,(float)9.556,(float)8.15,(float)8.302,(float)7.298,(
	    float)6.413,(float)6.399,(float)5.192,(float)5.725,(float)4.787,(
	    float)3.778,(float)2.3,(float).878,(float).286 };

    /* System generated locals */
    integer i__1, i__2;
    real r__1;

    /* Builtin functions */
    double exp(), sin();
    integer i_nint();

    /* Local variables */
    static real altg, disn, prob[666]	/* was [3][6][37] */, taun, flux;
    static integer i__, k, l;
    static real fbsbn;
    extern /* Subroutine */ int facsr_();
    static real hepls, colum[3], fluxg, tprob[666]	/* was [3][6][37] */;
    extern /* Subroutine */ int probs_();
    static integer k1;
    static real fluxn;
    static integer ik, is;
    static real xn[3];
    extern /* Subroutine */ int faceuv_();
    static real taugam, clnite[3], dspect;
    extern /* Subroutine */ int params_();
    static real zz, column[3], xnsigf;
    extern /* Subroutine */ int schumn_();
    static real freqly;
    extern /* Subroutine */ int scolum_();
    static real chi, tau, tnj;

/* pgr */
/* pgr */
/* -- common to hold the EUV and photoelectron production rates */
/* .. Save values that are only calc once */
/* .. Fluxes for nighttime ion production in the 37 wavelength bins */
/* .. Torr et al GRL 1979. The fluxes are set to reproduce the produ */
/* .. rates in Strobel et al. PSS, p1027, 1980. Note that most bins */
/* .. set to zero and that the Strobel production rates are scaled b */
/* .. FNFAC to stabilize the O+ solution below 200 km. Note also tha */
/* .. the wavelengths in FNITE go from largest (#3=HI) to smallest. */
/* .. UVFAC(58) is left over from FLIP routines for compatibility */
    sol_1.uvfac[57] = (float)-1.;
    if ((r__1 = (*f107 - f107sv) / *f107, dabs(r__1)) > (float).005) {
/* .. update UV flux factors */
	faceuv_(sol_1.uvfac, f107, f107a);
	facsr_(sol_1.uvfac, f107, f107a);
/* .. call params to get solar flux data and cross sections */
	params_(&c__0, &lmax);
	f107sv = *f107;
    }
/* ..  find probability for formation of each state  ........ */
    if (iprobs == 0) {
	probs_(&c__0, prob, sigs_1.zlam, &lmax, sigs_1.nni);
	for (i__ = 1; i__ <= 3; ++i__) {
	    for (k = 1; k <= 6; ++k) {
		for (l = 1; l <= 37; ++l) {
		    tprob[i__ + (k + l * 6) * 3 - 22] = prob[i__ + (k + l * 6)
			     * 3 - 22];
		}
	    }
	}
	iprobs = 1;
    }
/* ... initialization of production rates. 1.0E-15 stabilizes */
/* ... e density evaluation at low altitudes in CMINOR */
    for (is = 1; is <= 3; ++is) {
	for (ik = 1; ik <= 12; ++ik) {
	    euvprd_1.euvion[is + ik * 3 - 4] = (float)1e-15;
/* L10: */
	}
    }
    disn = (float)0.;
    for (i__ = 1; i__ <= 6; ++i__) {
	euvprd_1.othpr2[i__ - 1] = (float)1e-15;
/* L687: */
	euvprd_1.othpr1[i__ - 1] = (float)1e-15;
    }

/* ........ Nighttime He+ production is calculated and stored. Attenuated to */
/* ........ avoid excess production at low altitudes */
    euvprd_1.othpr1[1] = exp(*zn2 * (float)-1e-11) * (float)8e-11 * *he;
    for (i__ = 1; i__ <= 3; ++i__) {
/* L786: */
	colum[i__ - 1] = (float)1e25;
    }
    tnj = *tn;
    xn[0] = *zox;
    xn[1] = *zo2;
    xn[2] = *zn2;
    zz = *z__ * (float)1e5;
    chi = *sza;

/* *****  obtain reaction rates from subr rats to get their densities */
/* ....... determine if sun is below the horizon ... */
/* ---- Must now do calculation for night production - Feb 93 */
    altg = (*z__ + (float)6371.) * sin((float)3.1416 - chi) - (float)6371.;
/* ....      IF(CHI.GT.1.57.AND.ALTG.LT.85.) RETURN */
    if (*z__ > (float)1500.) {
	return 0;
    }

/* ...... get column densities for scattered light at night  &&&&&&&& */
    scolum_(ij, &c_b10, &zz, &tnj, xn, clnite);

/* ...... evaluate the neutral column density  &&&&&&&& */
    scolum_(ij, &chi, &zz, &tnj, xn, column);
/* ........ Store the column densities for the 2-Stream program */
    colum[0] = column[0];
    colum[1] = column[1];
    colum[2] = column[2];

/* ........ O2 dissociation by Schumann-Runge UV. */
/* ........ OTHPR1(3)= dissociation rate. OTHPR1(5)= Energy */
    schumn_(ij, z__, zo2, column, &euvprd_1.othpr1[2], &euvprd_1.othpr1[4]);

/* ---- Calculate hv + NO ion. freq. from Lyman-a (Brasseur & Solomon) */
/* ---- OTHPR2(2) is photodissociation of NO in the SR bands. */
/* ---- A small night production from scattered light is included. FREQLY */
/* ---- varies with solar activity using Richards et al. 1994 page 8981 */
/* ---- LY_a=2.5E11 (Lean), sigi(NO)=2.0E-18 (Brasseur & Solomon page 329) */
    freqly = (((*f107 + *f107a) * (float).5 - (float)80.) * (float).004 + 1) *
	     (float)5e-7;
    euvprd_1.othpr2[0] = freqly * (exp(-o2lyxs * column[1]) + exp(-o2lyxs * 
	    clnite[1]) * (float).001);
    euvprd_1.othpr2[1] = freqsr * (exp(-o2srxs * column[1]) + exp(-o2srxs * 
	    clnite[1]) * (float).001);

/* ..  wavelength loop begins here  ---------- */
/* ..  TAU, TAUN = optical depth for day, night */
    hepls = (float)0.;
    i__1 = lmax;
    for (l = 1; l <= i__1; ++l) {
	tau = (float)0.;
	taun = (float)0.;
	for (i__ = 1; i__ <= 3; ++i__) {
	    taun += sigs_1.sigabs[i__ + l * 3 - 4] * clnite[i__ - 1];
	    tau += sigs_1.sigabs[i__ + l * 3 - 4] * column[i__ - 1];
	}
/* .. evaluate nighttime flux and daytime flux */
	fluxn = fnfac * (*f107 / (float)75.) * fnite[l - 1] * exp(-taun);
	flux = sigs_1.zflux[l - 1] * exp(-tau) + fluxn;
/* ..WRITE(9,'(I6,1P,22E10.2)') L,COLUMN(1),COLUMN(3),TAU,EXP(-TAU */
/* ..>    FLUX, ZFLUX(L),FLUXN */
/* .. he+ production. He+ X-S  = 0.25 N2  X-S. HEPRDN = nite He+ */
	if (sigs_1.zlam[l - 1] < (float)500.) {
	    hepls += *he * (float).25 * sigs_1.sigion[l * 3 - 1] * flux;
	}
/* -- hv + N -> N+ + e. ion. freq. Richards et al. JGR 1994 page 8 */
	euvprd_1.othpr2[2] += xsnpls[l - 1] * (float)1e-18 * flux * *n4s;
	if (sigs_1.zlam[l - 1] >= (float)600.) {
/* ...... calculation of total euv absorption-ionization..... */
	    fbsbn = flux * (sigs_1.sigabs[l * 3 - 1] - sigs_1.sigion[l * 3 - 
		    1]) * xn[2];
/* .. Save energy absorbed in the photodissociative process */
	    euvprd_1.othpr1[3] += fbsbn * (float)12400. / sigs_1.zlam[l - 1];
/* .. production on atomic nitrogen by dissociation */
	    disn += fbsbn;
/* ..      IF(J.EQ.1) WRITE(6,95) L,ZLAM(L),TAU,FLUX,FBSBN,DISN, */
/* 95   FORMAT(I4,F9.1,1P,22E9.1) */
/* .. take into account the large n2 absorption of lyman gamma(9 */
	    if (i_nint(&sigs_1.zlam[l - 1]) == 975) {
		taugam = column[2] * (float)3.7e-16;
		if (taugam > (float)70.) {
		    taugam = (float)70.;
		}
		fluxg = sol_1.uvfac[33] * (float)8.2e8 * exp(-taugam);
		disn += fluxg * (float)3.7e-16 * xn[2];
	    }
	}
/* ***** species loop begins here ***** */
	for (i__ = 1; i__ <= 3; ++i__) {
	    xnsigf = xn[i__ - 1] * sigs_1.sigion[i__ + l * 3 - 4] * flux;
	    k1 = sigs_1.nni[i__ - 1];
/* .. dspect=# ions formed by w-l l by ionization of k state of */
	    i__2 = k1;
	    for (k = 1; k <= i__2; ++k) {
		dspect = xnsigf * prob[i__ + (k + l * 6) * 3 - 22];
/* .. store ion production rates ..... */
		euvprd_1.euvion[i__ + k * 3 - 4] += dspect;
/* .. calculation of ion heating rate...... */
		euvprd_1.euvion[27] += dspect * sigs_1.tpot[i__ + k * 3 - 4];
/* p           write(6,'(3I4,1P,9E10.2)') I,K,L,PROB(I,K,L),TPROB(I,K,L) */
/* p     >     ,XN(I),SIGION(I,L),FLUX,XNSIGF,EUVION(I,K),XSNPLS(1),FNITE(1) */
/* L302: */
	    }
/* L304: */
	}
/* L6: */
    }

/* ..---   wavelength loop ends here   ----------- */

/* .........Store UV disoc of N2 2 atoms produced for every dissociation */
    euvprd_1.othpr1[0] = disn * (float)2.;
/* ........ Transfer He+ production to storage */
    euvprd_1.othpr1[1] += hepls;
/* p      WRITE(6,*) 'After 6: EUVION(1,1), EUVION(2,1), EUVION(3,1)' */
/* p      write(6,'(1P,9E10.2)') EUVION(1,1), EUVION(2,1), EUVION(3,1) */
/* L777: */
    return 0;
} /* primpr_ */

/* :::::::::::::::::::::::::::: SCOLUM :::::::::::::::::::::::::::::::::: */
/* .... this routine evaluates the neutral column density for O, O2, and N2 */
/* .... see Smith & Smith JGR 1972 p 3592 */
/* .... chi=solar zenith angle, RE & GE radius and grav constant for earth */
/* .... Modified by P. Richards January 2010 to eliminate need for calling */
/* .... the MSIS model at grazing incidence */
/* Subroutine */ int scolum_(j, chi, z__, tn, xn, column)
integer *j;
real *chi, *z__, *tn, *xn, *column;
{
    /* Initialized data */

    static real a = (float)1.0606963;
    static real b = (float).55643831;
    static real c__ = (float)1.0619896;
    static real d__ = (float)1.7245609;
    static real f = (float).56498823;
    static real g = (float).06651874;
    static real sn[3] = { (float)0.,(float)0.,(float)0. };
    static real em = (float)1.662e-24;
    static real m[3] = { (float)16.,(float)32.,(float)28. };
    static real re = (float)6.357e8;
    static real ge = (float)980.;
    static real altg = (float)0.;
    static real erfy2 = (float)0.;

    /* Format strings */
    static char fmt_100[] = "(\002WARNING, Y IN COLUMN(I) > 100\002,i4,1p,9e\
10.2)";

    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double sin(), exp(), sqrt(), cos();
    integer s_wsfe(), do_fio(), e_wsfe();

    /* Local variables */
    static real tinf;
    static integer i__;
    static real y, hg, gn[3], gr, rg, sh, chapfn, xg, zg, rp, xi, xp, gtn, 
	    tnj;

    /* Fortran I/O blocks */
    static cilist io___268 = { 0, 6, 0, fmt_100, 0 };


    /* Parameter adjustments */
    --column;
    --xn;

    /* Function Body */
    for (i__ = 1; i__ <= 3; ++i__) {
	sn[i__ - 1] = (float)0.;
	column[i__] = (float)1e25;
    }
    tnj = *tn;
/* .. Avoids changing Tn at grazing incidence */
    if (*chi < (float)1.5708) {
	goto L2938;
    }
/* ..Grazing incidence parameters */
/* .. is sza>90.0 degrees */
    altg = (*z__ + (float)6.371e8) * sin((float)3.1416 - *chi) - (float)
	    6.371e8;
    if (altg >= (float)8.5e6) {
	zg = altg * (float)1e-5;
/* .. Bates-Walker temperature */
	xi = (zg - (float)120.) * (float)6477. / (zg + (float)6357.);
	tinf = dmax(*tn,(float)500.);
/* .. Crude TINF */
/* Computing MAX */
	r__1 = tinf - (tinf - (float)300.) * exp(xi * (float)-.025);
	gtn = dmax(r__1,(float)180.);
/* .. Neutral densities are extrapolated from altitude to grazing */
/* .. altitude. Weighted average Tn and GTn is used */
/* Computing 2nd power */
	r__1 = re / (re + *z__);
	gr = ge * (r__1 * r__1);
/* .. gravity */
	for (i__ = 1; i__ <= 3; ++i__) {
	    gn[i__ - 1] = xn[i__] * exp((*z__ - altg) / ((*tn + gtn * 2) * (
		    float)1.38e-16 / 3 / (em * m[i__ - 1] * gr)));
	}
/* ..   WRITE(88,'(6F8.2,1P,22E10.2)') Z/1.0E5,ZG,CHI*180/3.1416,T */
/* .. >      ,TNJ,((XN(I),GN(I),SN(I)),I=1,3) */
/* .. Make sure that grazing incidence density is not lower than M */
/* .. This is for using non MSIS densities like CTIPe */
	tnj = gtn;
	for (i__ = 1; i__ <= 3; ++i__) {
	    sn[i__ - 1] = gn[i__ - 1];
	    if (sn[i__ - 1] < xn[i__]) {
		sn[i__ - 1] = xn[i__];
	    }
	}
    } else {
	return 0;
    }
/* .. sn(1)=o , sn(2)=o2 , sn(3)=n2 , tnj=tn,  gr=gravity, rp=distan */
/* .. to pt p, sh=scale height, rg=distance to pt g, hg=scale height */
L2938:
/* Computing 2nd power */
    r__1 = re / (re + *z__);
    gr = ge * (r__1 * r__1);
    rp = re + *z__;
/* .. Calculate column densities for each species */
    for (i__ = 1; i__ <= 3; ++i__) {
	sh = tnj * (float)1.38e-16 / (em * m[i__ - 1] * gr);
	xp = rp / sh;
	y = sqrt(xp * (float).5) * (r__1 = cos(*chi), dabs(r__1));
	if (y > (float)100.) {
	    s_wsfe(&io___268);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    r__1 = *z__ / (float)1e5;
	    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
	    r__2 = *chi * (float)57.3;
	    do_fio(&c__1, (char *)&r__2, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&tnj, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&em, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&m[i__ - 1], (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&gr, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&rp, (ftnlen)sizeof(real));
	    e_wsfe();
	}
	if (y > (float)8.) {
	    erfy2 = f / (g + y);
	}
	if (y < (float)8.) {
	    erfy2 = (a + b * y) / (c__ + d__ * y + y * y);
	}
/* L4: */
	if (*chi > (float)1.5708) {
	    goto L2;
	}
	chapfn = sqrt(xp * (float)1.5708) * erfy2;
	column[i__] = xn[i__] * sh * chapfn;
	goto L10;
L2:
	rg = rp * sin((float)3.1416 - *chi);
/* Computing 2nd power */
	r__1 = (float)6.371e8 / (altg + (float)6.371e8);
	hg = tnj * (float)1.38e-16 / (em * m[i__ - 1] * (float)980. * (r__1 * 
		r__1));
	xg = rg / hg;
	column[i__] = sqrt(xg * (float)1.5708) * hg * (sn[i__ - 1] * (float)
		2. - xn[i__] * erfy2);
L10:
	;
    }
    return 0;
} /* scolum_ */

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int params_(isw, lmax)
integer *isw, *lmax;
{
    /* Initialized data */

    static real x3[18] = { (float)13.6,(float)16.9,(float)18.6,(float)28.5,(
	    float)40.,(float)0.,(float)12.1,(float)16.5,(float)18.2,(float)
	    20.,(float)25.,(float)0.,(float)15.6,(float)16.7,(float)18.8,(
	    float)25.,(float)29.,(float)37. };
    static real zlx[37] = { (float)1025.,(float)1031.91,(float)1025.72,(float)
	    975.,(float)977.02,(float)925.,(float)875.,(float)825.,(float)
	    775.,(float)789.36,(float)770.41,(float)765.15,(float)725.,(float)
	    703.36,(float)675.,(float)625.,(float)629.73,(float)609.76,(float)
	    575.,(float)584.33,(float)554.31,(float)525.,(float)475.,(float)
	    465.22,(float)425.,(float)375.,(float)368.07,(float)325.,(float)
	    303.78,(float)303.31,(float)275.,(float)284.15,(float)256.3,(
	    float)225.,(float)175.,(float)125.,(float)75. };
    static real zfx[37] = { (float)2.4665,(float)2.1,(float)3.5,(float)1.4746,
	    (float)4.4,(float)3.,(float)3.537,(float)1.625,(float).758,(float)
	    .702,(float).26,(float).17,(float).141,(float).36,(float).23,(
	    float).342,(float)1.59,(float).53,(float).357,(float)1.27,(float)
	    .72,(float).452,(float).285,(float).29,(float).383,(float).314,(
	    float).65,(float).965,(float)6.9,(float).8,(float)1.679,(float)
	    .21,(float).46,(float)3.1,(float)4.8,(float).45,(float)1.2 };
    static real x1[111] = { (float)0.,(float)0.,(float)0.,(float)0.,(float)0.,
	    (float)1.315,(float)4.554,(float)3.498,(float)5.091,(float)3.749,(
	    float)3.89,(float)4.,(float)10.736,(float)11.46,(float)17.245,(
	    float)13.365,(float)13.4,(float)13.4,(float)13.024,(float)13.09,(
	    float)12.59,(float)12.059,(float)12.127,(float)11.93,(float)
	    11.496,(float)9.687,(float)9.84,(float)8.693,(float)7.7,(float)
	    7.68,(float)6.461,(float)7.08,(float)6.05,(float)5.202,(float)
	    3.732,(float)1.839,(float).73,(float)1.346,(float)1.,(float)1.63,(
	    float)21.108,(float)18.73,(float)12.817,(float)8.562,(float)
	    16.631,(float)22.145,(float)26.668,(float)18.91,(float)20.8,(
	    float)28.535,(float)27.44,(float)21.919,(float)26.017,(float)
	    32.06,(float)28.07,(float)26.61,(float)22.79,(float)26.04,(float)
	    24.606,(float)23.101,(float)21.91,(float)20.31,(float)18.118,(
	    float)18.32,(float)17.438,(float)16.81,(float)16.8,(float)14.387,(
	    float)15.79,(float)13.37,(float)10.9,(float)7.509,(float)3.806,(
	    float)1.316,(float)0.,(float)0.,(float)0.,(float)50.988,(float)
	    2.24,(float)9.68,(float)20.249,(float)16.992,(float)33.578,(float)
	    16.487,(float)14.18,(float)120.49,(float)24.662,(float)26.54,(
	    float)31.755,(float)23.339,(float)23.37,(float)22.79,(float)
	    22.787,(float)22.4,(float)24.13,(float)24.501,(float)23.471,(
	    float)23.16,(float)21.675,(float)16.395,(float)16.91,(float)
	    13.857,(float)11.7,(float)11.67,(float)10.493,(float)10.9,(float)
	    10.21,(float)8.392,(float)4.958,(float)2.261,(float).72 };
    static real x2[111] = { (float)0.,(float)0.,(float)0.,(float)0.,(float)0.,
	    (float)1.315,(float)4.554,(float)3.498,(float)5.091,(float)3.749,(
	    float)3.89,(float)4.,(float)10.736,(float)11.46,(float)17.245,(
	    float)13.365,(float)13.4,(float)13.4,(float)13.024,(float)13.09,(
	    float)12.59,(float)12.059,(float)12.127,(float)11.93,(float)
	    11.496,(float)9.687,(float)9.84,(float)8.693,(float)7.7,(float)
	    7.68,(float)6.461,(float)7.08,(float)6.05,(float)5.202,(float)
	    3.732,(float)1.839,(float).73,(float).259,(float)0.,(float)1.05,(
	    float)13.94,(float)15.54,(float)9.374,(float)5.494,(float)6.413,(
	    float)10.597,(float)10.191,(float)8.47,(float)11.72,(float)23.805,
	    (float)23.75,(float)21.306,(float)24.937,(float)31.1,(float)26.39,
	    (float)26.61,(float)22.79,(float)26.04,(float)24.606,(float)
	    23.101,(float)21.91,(float)20.31,(float)18.118,(float)18.32,(
	    float)17.438,(float)16.81,(float)16.8,(float)14.387,(float)15.79,(
	    float)13.37,(float)10.9,(float)7.509,(float)3.806,(float)1.316,(
	    float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)
	    0.,(float)0.,(float)14.274,(float)8.86,(float)8.5,(float)65.8,(
	    float)15.06,(float)25.48,(float)29.235,(float)23.339,(float)23.37,
	    (float)22.79,(float)22.787,(float)22.4,(float)24.13,(float)24.501,
	    (float)23.471,(float)23.16,(float)21.675,(float)16.395,(float)
	    16.91,(float)13.857,(float)11.7,(float)11.67,(float)10.493,(float)
	    10.9,(float)10.21,(float)8.392,(float)4.958,(float)2.261,(float)
	    .72 };

    /* Format strings */
    static char fmt_95[] = "(/5x,\002EUV fluxes, Photoabsorption, and Photoi\
onization \002,\002Cross sections\002,/4x,\002I\002,5x,\002lam\002,5x,\002fl\
ux\002,4x,\002sigaOX\002,3x,\002sigaO2\002,3x,\002sigaN2\002,3x,\002sigiO\
X\002,3x,\002sigiO2\002,3x,\002sigiN2\002,3x,\002UVfac\002)";
    static char fmt_90[] = "(1x,i4,f9.2,1p,22e9.2)";
    static char fmt_94[] = "(/5x,\002 Ionization potentials for O, O2, N2\
\002,/2x,\0024S   2D   2P   4P   2P*  -   X2   a+A  b4   B2   dis  -\002,\
\002  X2   A2   B2   C2   F2   2s\002)";
    static char fmt_91[] = "(22f5.1)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer i__, j, l, in, is;
    static real ffac;

    /* Fortran I/O blocks */
    static cilist io___278 = { 0, 17, 0, fmt_95, 0 };
    static cilist io___283 = { 0, 17, 0, fmt_90, 0 };
    static cilist io___285 = { 0, 17, 0, fmt_94, 0 };
    static cilist io___286 = { 0, 17, 0, fmt_91, 0 };


/* ........ this program determines the cross sections, solar fluxes, and */
/* ........ given in m. torr et al g.r.l 1979 p771, table 2 and 3. but */
/* ........ the longer wavelengths come first */

/* ....... ionization potentials for o,o2 and n2 see kirby et al note the */
/* ....... o2 2(pi)u and 2(sigma-)u , and n2 f2(sigma)u pots are guesses */
/* ....... the sixth n2 potential is for dissociation */
/* ........ wavelength data. average is taken for bands */
/* ........ fluxes from table 3. these are for 74113. just replace this data */
/* ........ for other years in the table. note!!!! flux doubled for lambda<250 */
/* ........ shortest wavelenghts have been tripled */
/* ........ absorption cross sections -- o first ,o2, then n2 */
/* ....... ionization cross sections */

    sigs_2.nni[0] = 5;
    sigs_2.nni[1] = 5;
    sigs_2.nni[2] = 6;
    *lmax = 37;
    if (*isw != 0) {
	s_wsfe(&io___278);
	e_wsfe();
    }

    i__1 = *lmax;
    for (l = 1; l <= i__1; ++l) {
	sigs_2.zlam[l - 1] = zlx[l - 1];
	ffac = sol_1.uvfac[*lmax + 1 - l - 1];
	if (zfx[l - 1] < (float)100.) {
	    sigs_2.zflux[l - 1] = zfx[l - 1] * (float)1e9 * ffac;
	}
/* ..- setting up ionization potentials */
	if (l <= 6) {
	    sigs_2.tpot[l * 3 - 3] = x3[l - 1];
	    sigs_2.tpot[l * 3 - 2] = x3[l + 5];
	    sigs_2.tpot[l * 3 - 1] = x3[l + 11];
	}
/* ..- setting up cross sections */
	for (is = 1; is <= 3; ++is) {
	    in = *lmax * (is - 1) + l;
	    sigs_2.sigabs[is + l * 3 - 4] = x1[in - 1] * (float)1e-18;
	    sigs_2.sigion[is + l * 3 - 4] = x2[in - 1] * (float)1e-18;
	    if (sigs_2.sigabs[is + l * 3 - 4] < sigs_2.sigion[is + l * 3 - 4])
		     {
		sigs_2.sigabs[is + l * 3 - 4] = sigs_2.sigion[is + l * 3 - 4];
	    }
/* L10: */
	}

	if (*isw == 0) {
	    goto L20;
	}
	s_wsfe(&io___283);
	do_fio(&c__1, (char *)&l, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&sigs_2.zlam[l - 1], (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&sigs_2.zflux[l - 1], (ftnlen)sizeof(real));
	for (i__ = 1; i__ <= 3; ++i__) {
	    do_fio(&c__1, (char *)&sigs_2.sigabs[i__ + l * 3 - 4], (ftnlen)
		    sizeof(real));
	}
	for (i__ = 1; i__ <= 3; ++i__) {
	    do_fio(&c__1, (char *)&sigs_2.sigion[i__ + l * 3 - 4], (ftnlen)
		    sizeof(real));
	}
	do_fio(&c__1, (char *)&ffac, (ftnlen)sizeof(real));
	e_wsfe();
L20:
	;
    }

    if (*isw == 0) {
	return 0;
    }
    s_wsfe(&io___285);
    e_wsfe();
/* L60: */
    s_wsfe(&io___286);
    for (i__ = 1; i__ <= 3; ++i__) {
	for (j = 1; j <= 6; ++j) {
	    do_fio(&c__1, (char *)&sigs_2.tpot[i__ + j * 3 - 4], (ftnlen)
		    sizeof(real));
	}
    }
    e_wsfe();

    return 0;
} /* params_ */

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int probs_(isw, prob, zlam, lmax, nni)
integer *isw;
real *prob, *zlam;
integer *lmax, *nni;
{
    /* Initialized data */

    static real yo[185]	/* was [37][5] */ = { (float).19,(float).486,(float)
	    .952,(float)1.311,(float)1.539,(float)1.77,(float)1.628,(float)
	    1.92,(float)1.925,(float)2.259,(float)2.559,(float)2.523,(float)
	    3.073,(float)3.34,(float)3.394,(float)3.421,(float)3.65,(float)
	    3.92,(float)3.62,(float)3.61,(float)3.88,(float)4.25,(float)5.128,
	    (float)4.89,(float)6.739,(float)4.,(float)3.89,(float)3.749,(
	    float)5.091,(float)3.498,(float)4.554,(float)1.315,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0.,(float).206,(float).529,(
	    float)1.171,(float)1.762,(float)2.138,(float)2.62,(float)2.325,(
	    float)2.842,(float)2.849,(float)3.446,(float)3.936,(float)3.883,(
	    float)4.896,(float)5.37,(float)5.459,(float)5.427,(float)5.67,(
	    float)6.02,(float)5.91,(float)6.17,(float)6.29,(float)6.159,(
	    float)11.453,(float)6.57,(float)3.997,(float)0.,(float)0.,(float)
	    0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float).134,(float).345,(float).768,(
	    float)1.144,(float)1.363,(float)1.63,(float)1.488,(float)1.92,(
	    float)1.925,(float)2.173,(float)2.558,(float)2.422,(float)2.986,(
	    float)3.22,(float)3.274,(float)3.211,(float)3.27,(float)3.15,(
	    float)3.494,(float)3.62,(float)3.23,(float)2.956,(float).664,(
	    float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)
	    0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float).062,(float).163,(float).348,(float).508,(float)
	    .598,(float).71,(float).637,(float).691,(float).693,(float).815,(
	    float).787,(float).859,(float).541,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)
	    0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)
	    0.,(float)0.,(float).049,(float).13,(float).278,(float).366,(
	    float).412,(float).35,(float).383,(float).307,(float).308,(float)
	    0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)
	    0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)
	    0.,(float)0. };

    /* Format strings */
    static char fmt_95[] = "(/5x,\002 Photoionization branching ratios for O\
, O2, N2\002,/3x,\002Lam    4S   2D   2P   4P   2P*   -   X2   a+A  b4   B2\
 \002,\002  dis   -  X2   A2   B2   C2   F2   2s\002)";
    static char fmt_90[] = "(f8.2,22f5.2)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    static integer i__, j, l;
    extern /* Subroutine */ int probn2_(), probo2_();
    static integer ll, is;
    static real sum;

    /* Fortran I/O blocks */
    static cilist io___293 = { 0, 17, 0, fmt_95, 0 };
    static cilist io___294 = { 0, 17, 0, fmt_90, 0 };


/* .... program for finding branching ratios (probabilities for various ion */
/* .... and molecular states) of o,o2,n2 */
/* .... ---refs--- m. torr et al grl 1979 page 771, kirby et al atomic data */
/* .... and nuclear tables 1979 23,page 63 */
/* ...... coefficients of o ionization cross sections from torr et al */
/* ..... table 2 */
    /* Parameter adjustments */
    --nni;
    --zlam;
    prob -= 22;

    /* Function Body */

/* ....... production of o states from torr et al table 2 (yo array) */
/* ....... need to reverse order of yo to correspond with lambda */
    i__1 = *lmax;
    for (l = 1; l <= i__1; ++l) {
	ll = *lmax + 1 - l;
	sum = yo[ll - 1] + yo[ll + 36] + yo[ll + 73] + yo[ll + 110] + yo[ll + 
		147];
	for (i__ = 1; i__ <= 5; ++i__) {
	    prob[(i__ + l * 6) * 3 + 1] = (float)0.;
/* L20: */
	    if (sum != (float)0.) {
		prob[(i__ + l * 6) * 3 + 1] = yo[ll + i__ * 37 - 38] / sum;
	    }
	}
/* L10: */
    }

/* ....... call separate subroutines for o2 and n2 probabilities */
    i__1 = *lmax;
    for (l = 1; l <= i__1; ++l) {
	probo2_(&c__1, &l, &zlam[l], &prob[22], &nni[2]);
	probn2_(&c__1, &l, &zlam[l], &prob[22], &nni[3]);
/* L30: */
    }

    if (*isw == 0) {
	return 0;
    }
    s_wsfe(&io___293);
    e_wsfe();
    i__1 = *lmax;
    for (l = 1; l <= i__1; ++l) {
/* L50: */
	s_wsfe(&io___294);
	do_fio(&c__1, (char *)&zlam[l], (ftnlen)sizeof(real));
	for (is = 1; is <= 3; ++is) {
	    for (j = 1; j <= 6; ++j) {
		do_fio(&c__1, (char *)&prob[is + (j + l * 6) * 3], (ftnlen)
			sizeof(real));
	    }
	}
	e_wsfe();
    }
    return 0;
} /* probs_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int probn2_(isw, l, zlam, prob, jpts)
integer *isw, *l;
real *zlam, *prob;
integer *jpts;
{
    /* Initialized data */

    static integer ipts = 14;
    static real x[14] = { (float)50.,(float)210.,(float)240.,(float)280.,(
	    float)300.,(float)332.,(float)428.,(float)500.,(float)600.,(float)
	    660.,(float)660.01,(float)720.,(float)747.,(float)796. };
    static real y[84]	/* was [14][6] */ = { (float).32,(float).32,(float)
	    .32,(float).32,(float).32,(float).3,(float).46,(float).404,(float)
	    .308,(float).308,(float).308,(float).42,(float)1.,(float)1.,(
	    float).55,(float).55,(float).55,(float).55,(float).55,(float).52,(
	    float).46,(float).506,(float).589,(float).589,(float).692,(float)
	    .58,(float)0.,(float)0.,(float).13,(float).13,(float).13,(float)
	    .13,(float).13,(float).12,(float).08,(float).09,(float).103,(
	    float).103,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float).05,(float).1,(float).15,(float).83,(
	    float)1.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)
	    0.,(float)0.,(float)0.,(float)0.,(float).3,(float).4,(float).79,(
	    float).17,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)1.,(float)1.,(float)1.,(float).65,(
	    float).5,(float).06,(float)0.,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0. };

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsle(), do_lio(), e_wsle();

    /* Local variables */
    static real ylam, a[6], b[6];
    static integer i__, j;
    static real yield;
    extern /* Subroutine */ int yldiss_();
    static real sum;

    /* Fortran I/O blocks */
    static cilist io___303 = { 0, 6, 0, 0, 0 };


/* ...... the n2 probabilities are taken from kirby et al tables b and c */
/* ...... the yield of n+ is determined first then the remaining portion */
/* ...... of the cross section is distributed amongst the n2+ ion states */
/* ...... (x,a,b). the dissociation yield is divided between the 3 higher */
/* ...... energy states according to wight et al. j.phys. b, 1976 */
/* ...... the 2 other states of kirby et al are not included */

    /* Parameter adjustments */
    prob -= 22;

    /* Function Body */

/* ...... if zlam is too big set equal to x(max) */
    ylam = *zlam;
/* .. Prevent divide by zero */
    if (*zlam > x[13]) {
	ylam = x[13] - 1;
    }
    if (*zlam < x[0]) {
	ylam = x[0] + 1;
    }
    yield = (float)0.;
/* ...... determine yield of n+, and store in prob array */
    yldiss_(&c__1, &ylam, &yield);

    i__1 = ipts;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* kjh 6/22/92   NOTE:  I realize the following statement is strange */
/*   looking, but its purpose is to prevent the CRAY compiler from */
/*   vectorizing this loop.  (Which it does incorrectly). */
	if (i__ == 25) {
	    s_wsle(&io___303);
	    do_lio(&c__9, &c__1, " ", (ftnlen)1);
	    e_wsle();
	}
	if (ylam > x[i__ - 1] && ylam <= x[i__]) {
	    goto L20;
	}
/* L10: */
    }
L20:
    sum = (float)0.;
/* ...... fit straight line between points */
    i__1 = *jpts;
    for (j = 1; j <= i__1; ++j) {
	a[j - 1] = (y[i__ + 1 + j * 14 - 15] - y[i__ + j * 14 - 15]) / (x[i__]
		 - x[i__ - 1]);
	b[j - 1] = y[i__ + j * 14 - 15] - a[j - 1] * x[i__ - 1];
/* L30: */
    }
/* ...... determine probabilities of n2+ states */
    i__1 = *jpts;
    for (j = 1; j <= i__1; ++j) {
	if (j <= 3) {
	    prob[(j + *l * 6) * 3 + 3] = (a[j - 1] * ylam + b[j - 1]) * (1 - 
		    yield);
	}
	if (j > 3) {
	    prob[(j + *l * 6) * 3 + 3] = (a[j - 1] * ylam + b[j - 1]) * yield;
	}
	sum += prob[(j + *l * 6) * 3 + 3];
/* L40: */
    }

    if (sum == (float)0.) {
	return 0;
    }
/* ....... normalise probabilities */
    i__1 = *jpts;
    for (j = 1; j <= i__1; ++j) {
/* L50: */
	prob[(j + *l * 6) * 3 + 3] /= sum;
    }
    return 0;
} /* probn2_ */

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int yldiss_(isw, zlam, yield)
integer *isw;
real *zlam, *yield;
{
    /* Initialized data */

    static integer ipts = 9;
    static real x[9] = { (float)50.,(float)210.,(float)240.,(float)302.,(
	    float)387.,(float)477.,(float)496.,(float)509.,(float)2e3 };
    static real y[9] = { (float).36,(float).36,(float).346,(float).202,(float)
	    .033,(float).041,(float).024,(float)0.,(float)0. };

    /* System generated locals */
    integer i__1;
    real r__1;

    /* Builtin functions */
    integer s_wsle(), do_lio(), e_wsle();

    /* Local variables */
    static integer i__;

    /* Fortran I/O blocks */
    static cilist io___312 = { 0, 6, 0, 0, 0 };


/* ..... determination of dissociative yield of n+, refer to kirby et al */
/* ..... page 66 and table b */


    i__1 = ipts;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* kjh 6/22/92   NOTE:  I realize the following statement is strange */
/*   looking, but its purpose is to prevent the CRAY compiler from */
/*   vectorizing this loop.  (Which it does incorrectly). */
	if (i__ == 25) {
	    s_wsle(&io___312);
	    do_lio(&c__9, &c__1, " ", (ftnlen)1);
	    e_wsle();
	}
	if (*zlam >= x[i__ - 1] && *zlam < x[i__]) {
	    goto L20;
	}
/* L10: */
    }
L20:
    if (*zlam > (float)387. && *zlam < (float)477.) {
	goto L40;
    }
/* ....... linear interpolation */
    *yield = (*zlam - x[i__ - 1]) / (x[i__] - x[i__ - 1]) * (y[i__] - y[i__ - 
	    1]) + y[i__ - 1];
    goto L30;
/* ...... parabolic interpolation see formula page 66 kirby et al */
L40:
/* Computing 2nd power */
    r__1 = *zlam - 442;
    *yield = r__1 * r__1 * (float)8.13e-6 + (float).0329;
L30:
    return 0;
} /* yldiss_ */

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int probo2_(isw, l, zlam, prob, jpts)
integer *isw, *l;
real *zlam, *prob;
integer *jpts;
{
    /* Initialized data */

    static integer ipts = 20;
    static real x[20] = { (float)304.,(float)323.,(float)454.,(float)461.,(
	    float)504.,(float)537.,(float)556.,(float)573.,(float)584.,(float)
	    598.,(float)610.,(float)637.,(float)645.,(float)662.,(float)684.,(
	    float)704.,(float)720.,(float)737.,(float)774.,(float)1026. };
    static real y[100]	/* was [20][5] */ = { (float).365,(float).374,(float)
	    .432,(float).435,(float).384,(float).345,(float).356,(float).365,(
	    float).306,(float).23,(float).235,(float).245,(float).34,(float)
	    .27,(float).482,(float).675,(float).565,(float).565,(float)1.,(
	    float)1.,(float).205,(float).21,(float).243,(float).245,(float)
	    .27,(float).29,(float).23,(float).27,(float).33,(float).295,(
	    float).385,(float).35,(float).305,(float).385,(float).518,(float)
	    .325,(float).435,(float).435,(float)0.,(float)0.,(float).125,(
	    float).124,(float).12,(float).12,(float).126,(float).13,(float)
	    .225,(float).216,(float).21,(float).375,(float).305,(float).37,(
	    float).33,(float).345,(float)0.,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float).055,(float).167,(float).11,(float).105,
	    (float).194,(float).234,(float).189,(float).149,(float).155,(
	    float).103,(float).075,(float).036,(float).025,(float)0.,(float)
	    0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float).25,(
	    float).125,(float).095,(float).95,(float).026,(float)0.,(float)0.,
	    (float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(
	    float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)0.,(float)
	    0. };

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsle(), do_lio(), e_wsle();

    /* Local variables */
    static real ylam, a[5], b[5];
    static integer i__, j;
    static real sum;

    /* Fortran I/O blocks */
    static cilist io___318 = { 0, 6, 0, 0, 0 };


/* ....... o2 branching ratios are taken from kirby et al table d */
/* ....... columns 4 & 9 are combined. columns 5,6,7&8 are combined */
    /* Parameter adjustments */
    prob -= 22;

    /* Function Body */

/* ...... if zlam is too big set equal to x(max) */
    ylam = *zlam;
/* ...... if zlam is outside range of data values set equal to max or min */
    if (*zlam > x[19]) {
	ylam = x[19];
    }
    if (*zlam <= x[0]) {
	ylam = x[0] + (float).001;
    }

    i__1 = ipts;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* kjh 6/22/92   NOTE:  I realize the following statement is strange */
/*   looking, but its purpose is to prevent the CRAY compiler from */
/*   vectorizing this loop.  (Which it does incorrectly). */
	if (i__ == 25) {
	    s_wsle(&io___318);
	    do_lio(&c__9, &c__1, " ", (ftnlen)1);
	    e_wsle();
	}
	if (ylam > x[i__ - 1] && ylam <= x[i__]) {
	    goto L20;
	}
/* L10: */
    }
L20:
    sum = (float)0.;

    i__1 = *jpts;
    for (j = 1; j <= i__1; ++j) {
	a[j - 1] = (y[i__ + 1 + j * 20 - 21] - y[i__ + j * 20 - 21]) / (x[i__]
		 - x[i__ - 1]);
	b[j - 1] = y[i__ + j * 20 - 21] - a[j - 1] * x[i__ - 1];
	sum = sum + a[j - 1] * ylam + b[j - 1];
/* L30: */
    }

    i__1 = *jpts;
    for (j = 1; j <= i__1; ++j) {
	prob[(j + *l * 6) * 3 + 2] = (a[j - 1] * ylam + b[j - 1]) / sum;
/* L40: */
    }

    return 0;
} /* probo2_ */

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int schumn_(j, z__, zo2, column, schupr, schuht)
integer *j;
real *z__, *zo2, *column, *schupr, *schuht;
{
    /* Initialized data */

    static real srflux[8] = { (float)2.4,(float)1.4,(float).63,(float).44,(
	    float).33,(float).17,(float).12,(float).053 };
    static real srxs[8] = { (float).5,(float)1.5,(float)3.4,(float)6.,(float)
	    10.,(float)13.,(float)15.,(float)12. };
    static real srlam[8] = { (float)1725.,(float)1675.,(float)1625.,(float)
	    1575.,(float)1525.,(float)1475.,(float)1425.,(float)1375. };

    /* Builtin functions */
    double exp();

    /* Local variables */
    static integer lmax;
    static real hsrx, srxsct, fld;
    static integer jti, lsr;

/* ......... production of o(1d) by schumann-runge bands */
/* ......... The fluxes are from Torr et al. GRL 1980 p6063. Scaling is */
/* ......... done using UVFAC which may be set according to F10.7 cm flux */
/* ......... may be done in FACEUV */
    /* Parameter adjustments */
    --column;

    /* Function Body */

/* ........ lmax=# of lambdas in sub. primpr: schuht=heating: schupr=o(1d) prod */
    lmax = 37;

    for (lsr = 1; lsr <= 8; ++lsr) {
/* ......... photoabsorption cross section */
	srxsct = srxs[lsr - 1] * (float)1e-18;
	hsrx = srxsct * column[2];
	if (hsrx > (float)70.) {
	    hsrx = (float)70.;
	}
/* ........ attentuated solar flux */
	fld = sol_1.uvfac[lmax + lsr - 1] * (float)1e11 * srflux[lsr - 1] * 
		exp(-hsrx);
/* ............ neutral heating SCHUHT and photodissociation rate SCHUPR */
	*schuht += fld * srxsct * (float)12400. * *zo2 / srlam[lsr - 1];
	*schupr += fld * srxsct;
/* IF(JTI.EQ.0) WRITE(24,90) LSR,SRXSCT,FLD,SCHUPR,COLUMN(2),FLD, */
/* >   UVFAC(LMAX+LSR) */
/* L505: */
    }

    *schupr = *zo2 * *schupr;
/* L90: */
    jti = 1;
    return 0;
} /* schumn_ */

/* :::::::::::::::::::::::::::::::: FACEUV ::::::::::::::::::::::: */
/* Subroutine */ int faceuv_(uvfac, f107, f107a)
real *uvfac, *f107, *f107a;
{
    /* Initialized data */

    static real hfg200[37] = { (float)2.202,(float)1.855,(float)2.605,(float)
	    3.334,(float)1.333,(float)17.522,(float)4.176,(float)4.,(float)
	    1.4,(float)3.694,(float)1.791,(float)5.385,(float)1.889,(float)
	    1.899,(float)3.427,(float)2.051,(float)1.392,(float)1.619,(float)
	    1.439,(float)2.941,(float)1.399,(float)2.416,(float)1.512,(float)
	    1.365,(float)1.57,(float)1.462,(float)2.537,(float)1.393,(float)
	    1.572,(float)1.578,(float)1.681,(float)1.598,(float)1.473,(float)
	    1.53,(float)1.622,(float)1.634,(float)1.525 };

    /* Builtin functions */
    integer i_nint();

    /* Local variables */
    static real f107av, a, b;
    static integer i__;

/* ----- This routine uses the EUV scaling from Richards et al.[1994] */
/* ----- The EUVAC flux model is based on the F74113 solar reference */
/* ----- spectrum and Hinteregger's scaling factors. This subroutine */
/* ----- just provides the scaling factors as a function of the proxy */
/* ----- (F107+F107A)/2 */
    /* Parameter adjustments */
    --uvfac;

    /* Function Body */
/* --  Test to see if need to scale - see DATRD2 subroutine */
    if (i_nint(&uvfac[58]) == -1 || i_nint(&uvfac[58]) == -3) {
/* ........... EUV scaling */
	f107av = (*f107 + *f107a) * (float).5;
	for (i__ = 1; i__ <= 37; ++i__) {
	    a = (hfg200[i__ - 1] - 1) / (float)120.;
	    b = 1 - a * (float)80.;
	    uvfac[i__] = a * f107av + b;
	    if (uvfac[i__] < (float).8) {
		uvfac[i__] = (float).8;
	    }
/* L50: */
	}
    }
    return 0;
} /* faceuv_ */

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* Subroutine */ int facsr_(uvfac, f107, f107a)
real *uvfac, *f107, *f107a;
{
    /* Initialized data */

    static real srflux[8] = { (float)2.4,(float)1.4,(float).63,(float).44,(
	    float).33,(float).17,(float).12,(float).053 };
    static real sra[8] = { (float)25.5,(float)20.7,(float)13.2,(float)11.6,(
	    float)11.3,(float)7.86,(float)7.68,(float)4.56 };
    static real srb[8] = { (float)222.,(float)129.,(float)53.4,(float)36.,(
	    float)25.,(float)11.3,(float)6.35,(float)2.05 };

    static integer i__, lsr;

/* ........ The Schumann-Runge factors are scaled according to F10.7 */
/* ........ from Torr et al. GRL 1980 p6063 */
/* ............. Schumann-Runge scaling */
    /* Parameter adjustments */
    --uvfac;

    /* Function Body */
/* ...... first two SRA and SRB values out of order in Marsha's pape */

/* ----  Test to see if need to scale - see DATRD2 subroutine */
/* IF(NINT(UVFAC(58)).EQ.-1.OR.NINT(UVFAC(58)).EQ.-3) THEN */

    for (i__ = 38; i__ <= 50; ++i__) {
	lsr = i__ - 37;
	uvfac[i__] = (float)1.;
	if (lsr <= 8) {
	    uvfac[i__] = (sra[lsr - 1] * (float)1e7 * *f107 + srb[lsr - 1] * (
		    float)1e9) / srflux[lsr - 1] / (float)1e11;
	}
/* L505: */
    }
/* ENDIF */
    return 0;
} /* facsr_ */

