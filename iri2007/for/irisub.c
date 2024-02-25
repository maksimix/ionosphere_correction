/* irisub.f -- translated by f2c (version 20000121).
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
    doublereal humr, dumr;
} const1_;

#define const1_1 const1_

struct {
    doublereal argmax;
} argexp_;

#define argexp_1 argexp_

struct {
    doublereal hmf2, nmf2, hmf1;
    logical f1reg;
} block1_;

#define block1_1 block1_

struct {
    doublereal b0, b1, c1;
} block2_;

#define block2_1 block2_

struct {
    doublereal hz, t, hst;
} block3_;

#define block3_1 block3_

struct {
    doublereal hme, nme, hef;
} block4_;

#define block4_1 block4_

struct {
    logical enight;
    doublereal e[4];
} block5_;

#define block5_1 block5_

struct {
    doublereal hmd, nmd, hdx;
} block6_;

#define block6_1 block6_

struct {
    doublereal d1, xkk, fp30, fp3u, fp1, fp2;
} block7_;

#define block7_1 block7_

struct {
    doublereal hs, tnhs, xsm[4], mm[5], dti[4];
    integer mxsm;
} block8_;

#define block8_1 block8_

struct {
    doublereal xsm1, texos, tlbdh, sigma;
} blotn_;

#define blotn_1 blotn_

struct {
    doublereal ahh[7], ate1, stte[6], dte[5];
} blote_;

#define blote_1 blote_

struct {
    doublereal beta, eta, delta, zeta;
} blo10_;

#define blo10_1 blo10_

struct {
    doublereal b2top, tc3;
    integer itopn;
    doublereal alg10, hcor1;
} blo11_;

#define blo11_1 blo11_

struct {
    integer konsol, monito;
} iounit_;

#define iounit_1 iounit_

/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;
static doublereal c_b66 = 300.;
static doublereal c_b71 = 70.;
static doublereal c_b72 = 110.;
static doublereal c_b73 = 200.;
static doublereal c_b74 = 500.;
static doublereal c_b75 = 12.;
static integer c__1976 = 1976;
static integer c__882 = 882;
static doublereal c_b119 = 1.;
static doublereal c_b123 = 1.9;
static doublereal c_b124 = 2.6;
static doublereal c_b127 = 28.;
static doublereal c_b132 = 81.;
static doublereal c_b135 = .06;
static doublereal c_b143 = 4e8;
static doublereal c_b145 = 88.;
static doublereal c_b148 = .05;
static doublereal c_b151 = 4.6;
static doublereal c_b152 = 4.5;
static doublereal c_b155 = -11.5;
static doublereal c_b156 = -4.;
static doublereal c_b159 = 10.;
static doublereal c_b166 = .001;
static doublereal c_b184 = 0.;
static doublereal c_b191 = 2.;
static doublereal c_b192 = 1.5;
static doublereal c_b202 = 3.;
static doublereal c_b209 = 130.;
static doublereal c_b213 = .01;
static integer c__12 = 12;
static integer c__4 = 4;
static integer c__2 = 2;
static doublereal c_b242 = 50.;

/* irisub.for, version number can be found at the end of this comment. */
/* ----------------------------------------------------------------------- */

/* Includes subroutines IRI_SUB and IRI_WEB to compute IRI parameters */
/* for specified location, date, time, and altitude range and subroutine */
/* IRI_WEB to computes IRI parameters for specified location, date, time */
/* and variable range; variable can be altitude, latitude, longitude, */
/* year, month, day of month, day of year, or hour (UT or LT). */
/* IRI_WEB requires IRI_SUB. Both subroutines require linking with the */
/* following library files IRIFUN.FOR, IRITEC.FOR, IRIDREG.FOR, */
/* CIRA.FOR, IGRF.FOR */

/* !!!!! Subroutine INITIALIZE has to be called once before calling */
/* !!!!! iri_sub. This is already included in subroutine IRI_WEB which */
/* !!!!! calls iri_sub. */

/* i/o units:  6   messages (during execution) to monitor */
/*            10   CCIR and URSI coefficients */
/*            11   alternate unit for message file (if jf(12)=.false.) */
/*            12   solar/ionospheric indices: ig_rz.dat */
/*            13   magnetic indices: ap.dat */
/*            14   igrf coefficients */

/* ----------------------------------------------------------------------- */

/* CHANGES FROM  IRIS11.FOR  TO   IRIS12.FOR: */
/*    - CIRA-1986 INSTEAD OF CIRA-1972 FOR NEUTRAL TEMPERATURE */
/*    - 10/30/91 VNER FOR NIGHTTIME LAY-VERSION:  ABS(..) */
/*    - 10/30/91 XNE(..) IN CASE OF LAY-VERSION */
/*    - 10/30/91 CHANGE SSIN=F/T TO IIQU=0,1,2 */
/*    - 10/30/91 Te > Ti > Tn ENFORCED IN FINAL PROFILE */
/*    - 10/30/91 SUB ALL NAMES WITH 6 OR MORE CHARACTERS */
/*    - 10/31/91 CORRECTED HF1 IN HST SEARCH:  NE(HF1)>NME */
/*    - 11/14/91 C1=0 IF NO F1-REGION */
/*    - 11/14/91 CORRECTED HHMIN AND HZ FOR LIN. APP. */
/*    -  1/28/92 RZ12=0 included */
/*    -  1/29/92 NEQV instead of NE between URSIF2 and URSIFO */
/*    -  5/ 1/92 CCIR and URSI input as in IRID12 */
/*    -  9/ 2/94 Decimal month (ZMONTH) for IONCOM */
/*    -  9/ 2/94 Replace B0POL with B0_TAB; better annually */
/*    -  1/ 4/95 DY for h>hmF2 */
/*    -  2/ 2/95 IG for foF2, topside; RZ for hmF2, B0_TAB, foF1, NmD */
/*    -  2/ 2/95 winter no longer exclusive for F1 occurrrence */
/*    -  2/ 2/95 RZ and IG incl as DATA statement; smooth annual var. */
/* CHANGES FROM  IRIS12.FOR  TO   IRIS13.FOR: */
/*    - 10/26/95 incl year as input and corrected MODA; nrm for zmonth */
/*    - 10/26/95 use TCON and month-month interpolation in foF2, hmF2 */
/*    - 10/26/95 TCON only if date changes */
/*    - 11/25/95 take out logicals TOPSI, BOTTO, and BELOWE */
/*    - 12/ 1/95 UT_LT for (date-)correct UT<->LT conversion */
/*    - 12/22/95 Change ZETA cov term to cov < 180; use cov inst covsat */
/*    -  2/23/96 take covmax(R<150) for topside; lyear,.. for lt */
/*    -  3/26/96 topside: 94.5/BETA inst 94.45/..; cov -> covsat(<=188) */
/*    -  5/01/96 No longer DY for h>hmF2 (because of discontinuity) */
/*    - 12/01/96 IRIV13: HOUR for IVAR=1 (height) */
/*    -  4/25/97 D-region: XKK le 10 with D1 calc accordingly. */
/*    -  1/12/97 DS model for lower ion compoistion DY model */
/*    -  5/19/98 seamon=zmonth if lati>0; zmonth= ...(1.0*iday)/.. */
/*    -  5/19/98 DY ion composition model below 300 km now DS model */
/*    -  5/19/98 DS model includes N+, Cl down to 75 km HNIA changed */
/*    -  5/28/98 User input for Rz12, foF1/NmF1, hmF1, foE/NmE, hmE */
/*    -  9/ 2/98 1 instead of 0 in MODA after UT_LT call */
/*    -  4/30/99 constants moved from DATA statement into program */
/*    -  4/30/99 changed konsol-unit to 13 (12 is for IG_RZ). */
/*    -  5/29/99 the limit for IG comp. from Rz12-input is 174 not 274 */
/*    - 11/08/99 jf(18)=t simple UT to LT conversion, otherwise UT_LT */
/*    - 11/09/99 added COMMON/const1/humr,dumr also for CIRA86 */
/* CHANGES FROM  IRIS13.FOR  TO   IRISUB.FOR: */
/* ----------------------------------------------------------------------- */
/* -Version-MM/DD/YY-Description (person reporting correction) */
/* 2000.01 05/09/00 B0_98 replaces B0_TAB and B1: 1.9/day to 2.6/night */
/* 2000.02 06/11/00 including new F1 and indermediate region */
/* 2000.03 10/15/00 include Scherliess-Fejer drift model */
/* 2000.04 10/29/00 include special option for D region models */
/* 2000.05 12/07/00 change name IRIS13 to IRISUB */
/* 2000.06 12/14/00 jf(30),outf(20,100),oarr(50) */
/* 2000.07 03/17/01 include Truhlik-Triskova Te model and IGRF */
/* 2000.08 05/07/01 include Fuller-Rowell-Condrescu storm model */
/* 2000.09 07/09/01 LATI instead of LAT1 in F00 call -------- M. Torkar */
/* 2000.10 07/09/01 sdte instead of dte in ELTEIK call --- P. Wilkinson */
/* 2000.11 09/18/01 correct computation of foF2 for Rz12 user input */
/* 2000.12 09/19/01 Call APF only if different date and time -- P. Webb */
/* 2000.13 10/28/02 replace TAB/6 blanks, enforce 72/line -- D. Simpson */
/* 2000.14 11/08/02 change unit for message file to 11 (13 is Kp) */
/* 2000.15 01/27/03 change F1_prob output; Te-IK for fix h and ELTE(h) */
/* 2000.16 02/04/03 along<0 -> along=along+360; F1 occ for hmf1&foF1 */
/* 2000.17 02/05/03 zyear =12.97 (Dec 31); idayy=#days per year */
/* 2000.18 02/06/03 jf(27) for IG12 user input; all F1 prob in oar */
/* 2000.19 07/14/04 covsat<188 instead of covsat=<f(IG)<188 */
/* 2000.19 02/09/05 declare INVDIP as real ------------------ F. Morgan */
/* 2000.20 11/09/05 replace B0B1 with BCOEF --------------- T. Gulyaeva */
/* 2005.01 11/09/05 new topside ion composition; F107D from file */
/* 2005.02 11/14/05 jf(18) now IGRF/POGO; dip,mlat now IGRF10; */
/* 2005.03 11/15/05 sunrise/sunset/night for D,E,F1,F2; UT_LT removed */
/* 2005.04 05/06/06 FIRI D-region option not tied to peak */
/* 2005.04 05/06/06 Spread-F included, NeQuick included */
/* 2005.05 01/15/07 NeQuick uses CCIR-M3000F2 even if user-hmF2 */
/* 2007.00 05/18/07 Release of IRI-2007 */
/* 2007.01 01/23/08 ryear = .. (daynr-1.0)/idayy ---------- R. Scharroo */
/* 2007.02 10/31/08 outf(100) -> outf(500), numhei=numstp=500 */

/* ***************************************************************** */
/* ********* INTERNATIONAL REFERENCE IONOSPHERE (IRI). ************* */
/* ***************************************************************** */
/* **************** ALL-IN-ONE SUBROUTINE  ************************* */
/* ***************************************************************** */


/* Subroutine */ int iri_sub__(jf, jmag, alati, along, iyyyy, mmdd, dhour, 
	heibeg, heiend, heistp, outf, oarr)
logical *jf;
integer *jmag;
doublereal *alati, *along;
integer *iyyyy, *mmdd;
doublereal *dhour, *heibeg, *heiend, *heistp, *outf, *oarr;
{
    /* Format strings */
    static char fmt_1939[] = "(\002 *Ne* User input of hmF1 is only possible\
 for the LAY-\002,\002version\002)";
    static char fmt_2911[] = "(\002*** IRI parameters are being calculated *\
**\002)";
    static char fmt_9012[] = "(\002Ne, E-F: The LAY-Version is prelimenary\
.\002,\002 Erroneous profile features can occur.\002)";
    static char fmt_9013[] = "(\002Ne, B0: Bottomside thickness is \002,\002\
obtained with Gulyaeva-1987 model.\002)";
    static char fmt_9014[] = "(\002Ne: No upper limit for F10.7 in\002,\002 \
topside formula.\002)";
    static char fmt_9206[] = "(\002Ne: TTS for Topside\002)";
    static char fmt_9204[] = "(\002Ne: Corrected Topside Formula\002)";
    static char fmt_9205[] = "(\002Ne: NeQuick for Topside\002)";
    static char fmt_9015[] = "(\002Ne, foF2/NmF2: provided by user.\002)";
    static char fmt_9016[] = "(\002Ne, foF2: URSI model is used.\002)";
    static char fmt_9017[] = "(\002Ne, foF2: CCIR model is used.\002)";
    static char fmt_9018[] = "(\002Ne, hmF2/M3000F2: provided by user.\002)";
    static char fmt_9019[] = "(\002Ne, foF1/NmF1: provided by user.\002)";
    static char fmt_9021[] = "(\002Ne, hmF1: provided by user.\002)";
    static char fmt_9022[] = "(\002Ne, foE/NmE: provided by user.\002)";
    static char fmt_9023[] = "(\002Ne, hmE: provided by user.\002)";
    static char fmt_9024[] = "(\002Ne, foF1: probability function used.\002)";
    static char fmt_9025[] = "(\002Ne, foF1: L condition cases included.\002)"
	    ;
    static char fmt_9026[] = "(\002Ne, D: IRI-90\002)";
    static char fmt_9027[] = "(\002Ne, D: IRI-90, DRS-95,and FIRI-01)\002)";
    static char fmt_9028[] = "(\002Ne, foF2: Storm model turned off if foF2 \
or\002,\002 NmF2 user input\002)";
    static char fmt_9029[] = "(\002Ne, foF2: storm model included\002)";
    static char fmt_9031[] = "(\002Ion Com.: DS-95 & TTS-03\002)";
    static char fmt_9039[] = "(\002Ion Com.: DS-78 & DY-85\002)";
    static char fmt_9032[] = "(\002Te: Temperature-density correlation is us\
ed.\002)";
    static char fmt_9033[] = "(\002Te: Aeros/ISIS model\002)";
    static char fmt_9034[] = "(\002Te: Interkosmos model\002)";
    static char fmt_104[] = "(\002ccir\002,i2,\002.asc\002)";
    static char fmt_4689[] = "(1x,4e15.8)";
    static char fmt_1144[] = "(\002ursi\002,i2,\002.asc\002)";
    static char fmt_8449[] = "(1x////,\002 The file \002,a30,\002is not in y\
our directory.\002)";
    static char fmt_650[] = "(1x,\002*NE* E-REGION VALLEY CAN NOT BE MODEL\
LED\002)";
    static char fmt_11[] = "(1x,\002*NE* HMF1 IS NOT EVALUATED BY THE FUNCTI\
ON XE2\002/1x,\002CORR.: NO F1 REGION, B1=3, C1=0.0\002)";
    static char fmt_100[] = "(1x,\002*NE* HST IS NOT EVALUATED BY THE FUNCTI\
ON XE3\002)";
    static char fmt_901[] = "(6x,\002CORR.: LIN. APP. BETWEEN HZ=\002,f5.1\
,\002 AND HEF=\002,f5.1)";
    static char fmt_7733[] = "(\002*NE* LAY amplitudes found with 2nd choice\
 of HXL(1).\002)";
    static char fmt_7722[] = "(\002*NE* LAY amplitudes could not be found\
.\002)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    double atan(), log(), sqrt();
    integer s_wsfe(), e_wsfe();
    double tan(), exp();
    integer s_wsfi(), do_fio(), e_wsfi(), f_open(), s_rsfe(), e_rsfe(), 
	    f_clos();
    double cos(), pow_dd(), d_sign();

    /* Local variables */
    static logical sam_date__;
    extern /* Subroutine */ int igrf_dip__(), igrf_sub__(), apf_only__();
    static logical f1_l_cond__;
    static doublereal d__, f[3];
    static integer i__, j, k, l;
    static doublereal x, y, z__, f2[1976]	/* was [13][76][2] */, r2, x1,
	     z1, z2, z3;
    extern /* Subroutine */ int f00_();
    static doublereal stormcorr, ee;
    static integer ii, ki, kk;
    static doublereal ho[4], pi, mo[5];
    static logical dy;
    static doublereal ex, x12;
    extern doublereal ti_();
    static doublereal zi;
    extern doublereal tn_();
    static doublereal xl, ut, ff0[988], b2k, hf1, hf2;
    static integer do2[2];
    static doublereal fm3[882]	/* was [9][49][2] */, f2n[1976]	/* was [13][
	    76][2] */, ho2[2], r2d, x1d, mo2[3];
    extern doublereal xe2_();
    static doublereal ex1, r2n, xm0[441], rr2, rr1, x1n, ut0, xf1, xf2, ti1, 
	    h0o, xl1, dec;
    static integer icd, ddo[4];
    static doublereal elg[7], ate[7], tea[6], amp[4], rif[4], scl[4], dip, 
	    xma, yma, zma, hxl[4], bet;
    static logical ext;
    static doublereal cov, xhi, rrr, foe;
    extern /* Subroutine */ int apf_();
    static integer kut;
    static doublereal ttt, flu;
    extern /* Subroutine */ int tal_();
    static doublereal xdx, vkp, f107d;
    extern doublereal b0_98__();
    static doublereal hta, sec;
    static integer iyz, idz;
    static doublereal hte, f1pb, ff0n[988], fof2, eta1, fof1, ett, nmf1, fm3n[
	    882]	/* was [9][49][2] */, f6wa, pf1o[12], pg1o[80], pg2o[
	    32], pg3o[80], pf2o[4], pf3o[12], xhi1, sud1, xhi2, xhi3, sax1, 
	    cos2, xm0n[441], rr2n, rr1n, f5sw, xe2h, zmp1, zmp2;
    extern doublereal f1_c1__();
    static doublereal hv1r, hv2r, tn120, tet, ten, sux1;
    static integer ijk;
    static doublereal teh2, tid1, dela, tin1, babs, ten1, tnn1, afoe, ahme, 
	    hnea;
    extern doublereal xe3_1__();
    static doublereal arig[3];
    static logical dreg;
    static integer kind;
    static logical igin;
    static doublereal dnds[4], lati, dion[7];
    extern /* Subroutine */ int moda_();
    static integer iday;
    static doublereal mlat;
    static logical old79;
    static doublereal gind, hnee, dell, sax70;
    static logical topc;
    extern /* Subroutine */ int tcon_();
    static doublereal xnar[2];
    extern /* Subroutine */ int soco_();
    static doublereal zm3000, rzar[3], hour;
    static logical topo, rzin;
    extern doublereal fout_();
    static doublereal alg100, rssn, sux70;
    static integer midm;
    static doublereal xm3000, epin, afof1, afof2, ahmf2, ahmf1, zmp11, zmp22;
    extern doublereal hpol_();
    static doublereal seax, alog2, grat, f1pbl, b2bot;
    static logical gulb0;
    static doublereal f107dx, fof2n, sax110, sax200, nobo2, sax500, f1pbw, 
	    f1pbo, xdel, vner, xm300n, zfof2, yfof2, zmp111, hmex, dxdx, 
	    zmp222, bnmf1, hmf1m, hhmf2;
    static integer iiqu;
    static doublereal sux110, sux200, utni, sux500, tn1ni;
    extern /* Subroutine */ int teba_();
    static doublereal dimo, dipl, sdte;
    extern doublereal tede_();
    static doublereal stte1, stte2, bcoef;
    extern doublereal elte_();
    static doublereal ti13, ti50, hhalf;
    static integer icode;
    static doublereal xtts, hdeep, tex, aigin, magbr;
    static integer indap[13];
    static doublereal cglat, ddens[21]	/* was [3][7] */, dlndh, param[2];
    static logical foein, hmein, noden, igino;
    extern doublereal teder_();
    static doublereal longi, modip;
    static logical tecon[2];
    static doublereal osfbr[25], mlong;
    static integer daynr, iyear;
    static doublereal xdels[4];
    static integer idayy;
    static logical notem, noion;
    static doublereal arzin;
    static integer jxnar, month;
    static doublereal ryear;
    static integer nmono;
    extern /* Subroutine */ int rogul_();
    static doublereal width, depth;
    extern doublereal xmded_();
    static doublereal xnehz;
    extern /* Subroutine */ int cira86_();
    static doublereal secni;
    static logical rzino;
    extern /* Subroutine */ int ut_lt__(), storm_();
    extern doublereal hmf2ed_(), fof1ed_();
    extern /* Subroutine */ int regfa1_();
    static doublereal texni, signi, tlbdn, hmaxd;
    extern doublereal xmout_();
    static doublereal hmaxn, b0cnew, tmaxd, tmaxn;
    extern doublereal dtndh_();
    static logical fof1in, fof2in, hmf2in, hmf1in;
    static doublereal tnahh2, tix, xteti, hnia, hnie;
    extern /* Subroutine */ int koefp1_(), koefp2_(), koefp3_();
    static doublereal sunde1;
    extern /* Subroutine */ int sufe_();
    static doublereal zzz1;
    static integer msumo;
    static doublereal ho05, hfixo, delx, ymaxx;
    extern doublereal rpid_();
    static doublereal yo2h0o, yoh0o;
    static logical ursif2;
    static doublereal hfixo2, rdo2mx, ymo2z, aldo21, xhmf1, elede;
    extern doublereal xen_(), xe_1__();
    static doublereal dipl1, babs1;
    extern /* Subroutine */ int calne_();
    static doublereal tnh, tih, teh;
    extern /* Subroutine */ int fieldg_();
    extern doublereal foeedi_();
    static doublereal rox, rhx, rnx, rhex, dndhbr, hefold, rnox, ro2x;
    extern /* Subroutine */ int rdhhe_();
    static integer seaday;
    static char filnam[12];
    static integer icalls;
    extern /* Subroutine */ int geodip_();
    static doublereal abslat, absmdp, absmbr;
    static logical dnight, schalt, fnight;
    static integer iuccir;
    static doublereal absmlt, sundec;
    static integer numhei, icoord, nseasn, season;
    static doublereal invdip;
    static logical sam_ut__, teneop;
    static integer nrdaym, iyearo;
    static doublereal covsat, dndhmx;
    extern /* Subroutine */ int inilay_();
    static logical layver;
    static integer nmonth, montho;
    static logical ursifo;
    static doublereal xhinon, xkkmax, diplat;
    extern /* Subroutine */ int elteik_();
    static doublereal tnahhi, rdomax;
    extern doublereal epstep_();
    static doublereal height, rclust;
    extern doublereal rdno_();
    static doublereal xnorm, edens;
    static integer ierror;
    static doublereal drift;
    extern /* Subroutine */ int vdrift_();
    static doublereal daynr1;
    extern /* Subroutine */ int f1_prob__(), spreadf_brazil__();
    static integer ispf;
    static logical sam_yea__;
    static doublereal spreadf;
    extern /* Subroutine */ int dregion_();
    static logical sam_mon__, sam_doy__;
    static integer iseamon;
    extern /* Subroutine */ int ioncomp_();
    static integer idaynro;
    static doublereal spfhour;
    static logical f1_ocpro__;

    /* Fortran I/O blocks */
    static cilist io___41 = { 0, 0, 0, fmt_1939, 0 };
    static cilist io___49 = { 0, 0, 0, fmt_2911, 0 };
    static cilist io___50 = { 0, 0, 0, fmt_9012, 0 };
    static cilist io___51 = { 0, 0, 0, fmt_9013, 0 };
    static cilist io___52 = { 0, 0, 0, fmt_9014, 0 };
    static cilist io___53 = { 0, 0, 0, fmt_9206, 0 };
    static cilist io___54 = { 0, 0, 0, fmt_9204, 0 };
    static cilist io___55 = { 0, 0, 0, fmt_9205, 0 };
    static cilist io___56 = { 0, 0, 0, fmt_9015, 0 };
    static cilist io___57 = { 0, 0, 0, fmt_9016, 0 };
    static cilist io___58 = { 0, 0, 0, fmt_9017, 0 };
    static cilist io___59 = { 0, 0, 0, fmt_9018, 0 };
    static cilist io___60 = { 0, 0, 0, fmt_9019, 0 };
    static cilist io___61 = { 0, 0, 0, fmt_9021, 0 };
    static cilist io___62 = { 0, 0, 0, fmt_9022, 0 };
    static cilist io___63 = { 0, 0, 0, fmt_9023, 0 };
    static cilist io___64 = { 0, 0, 0, fmt_9024, 0 };
    static cilist io___65 = { 0, 0, 0, fmt_9025, 0 };
    static cilist io___66 = { 0, 0, 0, fmt_9026, 0 };
    static cilist io___67 = { 0, 0, 0, fmt_9027, 0 };
    static cilist io___68 = { 0, 0, 0, fmt_9028, 0 };
    static cilist io___69 = { 0, 0, 0, fmt_9029, 0 };
    static cilist io___70 = { 0, 0, 0, fmt_9031, 0 };
    static cilist io___71 = { 0, 0, 0, fmt_9039, 0 };
    static cilist io___72 = { 0, 0, 0, fmt_9032, 0 };
    static cilist io___73 = { 0, 0, 0, fmt_9033, 0 };
    static cilist io___74 = { 0, 0, 0, fmt_9034, 0 };
    static icilist io___154 = { 0, filnam, 0, fmt_104, 12, 1 };
    static cilist io___155 = { 0, 0, 0, fmt_4689, 0 };
    static icilist io___158 = { 0, filnam, 0, fmt_1144, 12, 1 };
    static cilist io___159 = { 0, 0, 0, fmt_4689, 0 };
    static icilist io___160 = { 0, filnam, 0, fmt_104, 12, 1 };
    static cilist io___161 = { 0, 0, 0, fmt_4689, 0 };
    static icilist io___164 = { 0, filnam, 0, fmt_1144, 12, 1 };
    static cilist io___165 = { 0, 0, 0, fmt_4689, 0 };
    static cilist io___166 = { 0, 0, 0, fmt_8449, 0 };
    static cilist io___234 = { 0, 0, 0, fmt_650, 0 };
    static cilist io___252 = { 0, 0, 0, fmt_11, 0 };
    static cilist io___253 = { 0, 0, 0, fmt_650, 0 };
    static cilist io___259 = { 0, 0, 0, fmt_100, 0 };
    static cilist io___261 = { 0, 0, 0, fmt_901, 0 };
    static cilist io___271 = { 0, 0, 0, fmt_7733, 0 };
    static cilist io___272 = { 0, 0, 0, fmt_7722, 0 };


/* ----------------------------------------------------------------- */

/* INPUT:  JF(1:30)      true/false switches for several options */
/*         JMAG          =0 geographic   = 1 geomagnetic coordinates */
/*         ALATI,ALONG   LATITUDE NORTH AND LONGITUDE EAST IN DEGREES */
/*         IYYYY         Year as YYYY, e.g. 1985 */
/*         MMDD (-DDD)   DATE (OR DAY OF YEAR AS A NEGATIVE NUMBER) */
/*         DHOUR         LOCAL TIME (OR UNIVERSAL TIME + 25) IN DECIMAL */
/*                          HOURS */
/*         HEIBEG,       HEIGHT RANGE IN KM; maximal 100 heights, i.e. */
/*          HEIEND,HEISTP        int((heiend-heibeg)/heistp)+1.le.100 */

/*    JF switches to turn off/on (.true./.false.) several options */

/*    i       .true.                  .flase.          standard version */
/*    ----------------------------------------------------------------- */
/*    1    Ne computed            Ne not computed                     t */
/*    2    Te, Ti computed        Te, Ti not computed                 t */
/*    3    Ne & Ni computed       Ni not computed                     t */
/*    4    B0 - Table option      B0 - Gulyaeva (1987)                t */
/*    5    foF2 - CCIR            foF2 - URSI                     false */
/*    6    Ni - DS-78 & DY-85     Ni - DS-95 & TTS-03             false */
/*    7    Ne - Tops: f10.7<188   f10.7 unlimited                     t */
/*    8    foF2 from model        foF2 or NmF2 - user input           t */
/*    9    hmF2 from model        hmF2 or M3000F2 - user input        t */
/*   10    Te - Standard          Te - Using Te/Ne correlation        t */
/*   11    Ne - Standard Profile  Ne - Lay-function formalism         t */
/*   12    Messages to unit 6     no messages                         t */
/*   13    foF1 from model        foF1 or NmF1 - user input           t */
/*   14    hmF1 from model        hmF1 - user input (only Lay version)t */
/*   15    foE  from model        foE or NmE - user input             t */
/*   16    hmE  from model        hmE - user input                    t */
/*   17    Rz12 from file         Rz12 - user input                   t */
/*   18    IGRF dip, magbr, modip old FIELDG using POGO68/10 for 1973 t */
/*   19    F1 probability model   critical solar zenith angle (old)   t */
/*   20    standard F1            standard F1 plus L condition        t */
/*   21    ion drift computed     ion drift not computed          false */
/*   22    ion densities in %     ion densities in m-3                t */
/*   23    Te_tops (Aeros,ISIS)   Te_topside (Intercosmos)        false */
/*   24    D-region: IRI-95       Special: 3 D-region models          t */
/*   25    F107D from AP.DAT      F107D user input (oarr(41))         t */
/*   26    foF2 storm model       no storm updating                   t */
/*   27    IG12 from file         IG12 - user input					 t */
/*   28    spread-F probability 	 not computed                    false */
/*   29    IRI01-topside          new options as def. by JF(30)   false */
/*   30    IRI01-topside corr.    NeQuick topside model   	     false */
/*     (29,30) = (t,t) IRIold, (f,t) IRIcor, (f,f) NeQuick, (t,f) TTS */
/*   ------------------------------------------------------------------ */

/*  Depending on the jf() settings additional INPUT parameters may */
/*  be required: */

/*       Setting              INPUT parameter */
/*    ----------------------------------------------------------------- */
/*    jf(8)  =.false.     OARR(1)=user input for foF2/MHz or NmF2/m-3 */
/*    jf(9)  =.false.     OARR(2)=user input for hmF2/km or M(3000)F2 */
/*    jf(10 )=.false.     OARR(15),OARR(16)=user input for Ne(300km), */
/*       Ne(400km)/m-3. Use OARR()=-1 if one of these values is not */
/*       available. If jf(23)=.false. then Ne(300km), Ne(550km)/m-3. */
/*    jf(13) =.false.     OARR(3)=user input for foF1/MHz or NmF1/m-3 */
/*    jf(14) =.false.     OARR(4)=user input for hmF1/km */
/*    jf(15) =.false.     OARR(5)=user input for foE/MHz or NmE/m-3 */
/*    jf(16) =.false.     OARR(6)=user input for hmE/km */
/*    jf(17) =.flase.     OARR(33)=user input for Rz12 */
/*    jf(21) =.true.      OARR(41)=user input for daily F10.7 index */
/*    jf(23) =.false.     OARR(41)=user input for daily F10.7 index */
/*    jf(24) =.false.     OARR(41)=user input for daily F10.7 index */
/*          optional for jf(21:24); default is F10.7D=COV */
/*    jf(25) =.false.     OARR(41)=user input for daily F10.7 index */
/*          if oarr(41).le.0 then 12-month running mean is */
/*          taken from internal file] */
/*    jf(27) =.flase.     OARR(39)=user input for IG12 */
/*    jf(21) =.true.      OARR(41)=user input for daily F10.7 index */


/*  OUTPUT:  OUTF(1:20,1:500) */
/*               OUTF(1,*)  ELECTRON DENSITY/M-3 */
/*               OUTF(2,*)  NEUTRAL TEMPERATURE/K */
/*               OUTF(3,*)  ION TEMPERATURE/K */
/*               OUTF(4,*)  ELECTRON TEMPERATURE/K */
/*               OUTF(5,*)  O+ ION DENSITY/% or /M-3 if jf(22)=f */
/*               OUTF(6,*)  H+ ION DENSITY/% or /M-3 if jf(22)=f */
/*               OUTF(7,*)  HE+ ION DENSITY/% or /M-3 if jf(22)=f */
/*               OUTF(8,*)  O2+ ION DENSITY/% or /M-3 if jf(22)=f */
/*               OUTF(9,*)  NO+ ION DENSITY/% or /M-3 if jf(22)=f */
/*                 AND, IF JF(6)=.FALSE.: */
/*               OUTF(10,*)  CLUSTER IONS DEN/% or /M-3 if jf(22)=f */
/*               OUTF(11,*)  N+ ION DENSITY/% or /M-3 if jf(22)=f */
/*               OUTF(12,*) */
/*               OUTF(13,*)  D/E-region densities (Friedrich) */
/*               OUTF(14,*)  1:7 Danilov for 60,65..90km; 8:14 for a */
/*                  major Stratospheric Warming (SW=1) event; 15:21 */
/*                  for strong Winter Anomaly (WA=1) conditions */
/*               OUTF(15-20,*)  free */

/*            OARR(1:50)   ADDITIONAL OUTPUT PARAMETERS */

/*      #OARR(1) = NMF2/M-3           #OARR(2) = HMF2/KM */
/*      #OARR(3) = NMF1/M-3           #OARR(4) = HMF1/KM */
/*      #OARR(5) = NME/M-3            #OARR(6) = HME/KM */
/*       OARR(7) = NMD/M-3             OARR(8) = HMD/KM */
/*       OARR(9) = HHALF/KM            OARR(10) = B0/KM */
/*       OARR(11) =VALLEY-BASE/M-3     OARR(12) = VALLEY-TOP/KM */
/*       OARR(13) = TE-PEAK/K          OARR(14) = TE-PEAK HEIGHT/KM */
/*      #OARR(15) = TE-MOD(300KM)     #OARR(16) = TE-MOD(400KM)/K */
/*       OARR(17) = TE-MOD(600KM)      OARR(18) = TE-MOD(1400KM)/K */
/*       OARR(19) = TE-MOD(3000KM)     OARR(20) = TE(120KM)=TN=TI/K */
/*       OARR(21) = TI-MOD(430KM)      OARR(22) = X/KM, WHERE TE=TI */
/*       OARR(23) = SOL ZENITH ANG/DEG OARR(24) = SUN DECLINATION/DEG */
/*       OARR(25) = DIP/deg            OARR(26) = DIP LATITUDE/deg */
/*       OARR(27) = MODIFIED DIP LAT.  OARR(28) = DELA */
/*       OARR(29) = sunrise/dec. hours OARR(30) = sunset/dec. hours */
/*       OARR(31) = ISEASON (1=spring) OARR(32) = NSEASON (northern) */
/*      #OARR(33) = Rz12               OARR(34) = Covington Index */
/*       OARR(35) = B1                 oarr(36) = M(3000)F2 */
/*      $oarr(37) = TEC/m-2           $oarr(38) = TEC_top/TEC*100. */
/*      #OARR(39) = gind (IG12)        oarr(40) = F1 probability (old) */
/*      #OARR(41) = F10.7 daily        oarr(42) = c1 (F1 shape) */
/*       OARR(43) = daynr */
/*       OARR(44) = equatorial vertical ion drift in m/s */
/*       OARR(45) = foF2_storm/foF2_quiet */
/*       OARR(46) = F1 probability without L condition */
/*       OARR(47) = F1 probability with L condition incl. */
/*       OARR(48) = spread-F occurrence probability (Brazilian model) */
/*                # INPUT as well as OUTPUT parameter */
/*                $ special for IRIWeb (only place-holders) */
/* ----------------------------------------------------------------------- */
/* ***************************************************************** */
/* *** THE ALTITUDE LIMITS ARE:  LOWER (DAY/NIGHT)  UPPER        *** */
/* ***     ELECTRON DENSITY         60/80 KM       1000 KM       *** */
/* ***     TEMPERATURES              120 KM        2500/3000 KM  *** */
/* ***     ION DENSITIES             100 KM        1000 KM       *** */
/* ***************************************************************** */
/* ***************************************************************** */
/* *********            INTERNALLY                    ************** */
/* *********       ALL ANGLES ARE IN DEGREE           ************** */
/* *********       ALL DENSITIES ARE IN M-3           ************** */
/* *********       ALL ALTITUDES ARE IN KM            ************** */
/* *********     ALL TEMPERATURES ARE IN KELVIN       ************** */
/* *********     ALL TIMES ARE IN DECIMAL HOURS       ************** */
/* ***************************************************************** */
/* ***************************************************************** */
/* ***************************************************************** */
/* -web-for webversion */
/*      CHARACTER FILNAM*53 */
    /* Parameter adjustments */
    --oarr;
    outf -= 21;
    --jf;

    /* Function Body */
    for (ki = 1; ki <= 20; ++ki) {
	for (kk = 1; kk <= 500; ++kk) {
/* L7397: */
	    outf[ki + kk * 20] = -1.;
	}
    }
    for (kind = 7; kind <= 14; ++kind) {
/* L8398: */
	oarr[kind] = -1.;
    }
    for (kind = 17; kind <= 32; ++kind) {
/* L8378: */
	oarr[kind] = -1.;
    }
    for (kind = 34; kind <= 38; ++kind) {
/* L8478: */
	oarr[kind] = -1.;
    }
    oarr[40] = -1.;
    for (kind = 42; kind <= 50; ++kind) {
/* L8428: */
	oarr[kind] = -1.;
    }

/* PROGRAM CONSTANTS */

    ++icalls;
    argexp_1.argmax = 88.;
    pi = atan(1.) * 4.;
    const_1.umr = pi / 180.;
    const1_1.humr = pi / 12.;
    const1_1.dumr = pi / 182.5;
    alog2 = log(2.);
    blo11_1.alg10 = log(10.);
    alg100 = log(100.);
    numhei = (integer) ((d__1 = *heiend - *heibeg, abs(d__1)) / abs(*heistp)) 
	    + 1;
    if (numhei > 500) {
	numhei = 500;
    }

/* Code inserted to aleviate block data problem for PC version. */
/* Thus avoiding DATA statement with parameters from COMMON block. */

    xdels[0] = 5.;
    xdels[1] = 5.;
    xdels[2] = 5.;
    xdels[3] = 10.;
    dnds[0] = .016;
    dnds[1] = .01;
    dnds[2] = .016;
    dnds[3] = .016;
    ddo[0] = 9;
    ddo[1] = 5;
    ddo[2] = 5;
    ddo[3] = 25;
    do2[0] = 5;
    do2[1] = 5;
    xnar[0] = 0.;
    xnar[1] = 0.;
    blote_1.dte[0] = 5.;
    blote_1.dte[1] = 5.;
    blote_1.dte[2] = 10.;
    blote_1.dte[3] = 20.;
    blote_1.dte[4] = 20.;
    block8_1.dti[0] = 10.;
    block8_1.dti[1] = 10.;
    block8_1.dti[2] = 20.;
    block8_1.dti[3] = 20.;

/* FIRST SPECIFY YOUR COMPUTERS CHANNEL NUMBERS .................... */
/* AGNR=OUTPUT (OUTPUT IS DISPLAYED OR STORED IN FILE OUTPUT.IRI)... */
/* IUCCIR=UNIT NUMBER FOR CCIR COEFFICIENTS ........................ */
/* set konsol=1 if you do not want the konsol information */

    iounit_1.monito = 6;
    iuccir = 10;
/* -web- special for web version */
/* -web-      KONSOL=1 */
    iounit_1.konsol = 6;
    if (! jf[12]) {
	iounit_1.konsol = 1;
    }
/*        if(.not.jf(12)) then */
/*                konsol=11 */
/*                open(11,file='messages.txt') */
/*                endif */

/* selection of density, temperature and ion composition options ...... */

    noden = ! jf[1];
    notem = ! jf[2];
    noion = ! jf[3];
    if (! noion) {
	noden = FALSE_;
    }
    dy = ! jf[6];
    layver = ! jf[11];
    old79 = ! jf[7];
    gulb0 = ! jf[4];
    f1_ocpro__ = jf[19];
    f1_l_cond__ = FALSE_;
    if (f1_ocpro__) {
	f1_l_cond__ = ! jf[20];
    }
    dreg = jf[24];
    topo = jf[29];
    topc = jf[30];

/* rz12, F10.7D input option .......................................... */

    rzin = ! jf[17];
    if (rzin) {
	arzin = oarr[33];
    } else {
	oarr[33] = -1.;
    }
    igin = ! jf[27];
    if (igin) {
	aigin = oarr[39];
    } else {
	oarr[39] = -1.;
    }
    if (! jf[25]) {
	f107d = oarr[41];
    } else {
	oarr[41] = -1.;
    }

/* Topside density .................................................... */

    if (topo) {
	if (topc) {
	    blo11_1.itopn = 0;
	} else {
	    blo11_1.itopn = 3;
	}
    } else {
	if (topc) {
	    blo11_1.itopn = 1;
	} else {
	    blo11_1.itopn = 2;
	}
    }

/* F2 peak density .................................................... */

    fof2in = ! jf[8];
    if (fof2in) {
	afof2 = oarr[1];
	if (afof2 > 100.) {
	    afof2 = sqrt(afof2 / 1.24e10);
	}
    } else {
	oarr[1] = -1.;
    }
    ursif2 = ! jf[5];

/* F2 peak altitude .................................................. */

    hmf2in = ! jf[9];
    if (hmf2in) {
	ahmf2 = oarr[2];
    } else {
	oarr[2] = -1.;
    }

/* F1 peak density ................................................... */

    fof1in = ! jf[13];
    if (fof1in) {
	afof1 = oarr[3];
	if (afof1 > 100.) {
	    afof1 = sqrt(afof1 / 1.24e10);
	}
    } else {
	oarr[3] = -1.;
    }

/* F1 peak altitude .................................................. */

    hmf1in = ! jf[14];
    if (hmf1in) {
	ahmf1 = oarr[4];
	if (! layver && iounit_1.konsol > 1) {
	    io___41.ciunit = iounit_1.konsol;
	    s_wsfe(&io___41);
	    e_wsfe();
	}
    } else {
	oarr[4] = -1.;
    }

/* E peak density .................................................... */

    foein = ! jf[15];
    if (foein) {
	afoe = oarr[5];
	if (afoe > 100.) {
	    afoe = sqrt(afoe / 1.24e10);
	}
    } else {
	oarr[5] = -1.;
    }

/* E peak altitude .................................................. */

    hmein = ! jf[16];
    if (hmein) {
	ahme = oarr[6];
    } else {
	oarr[6] = -1.;
    }

/* TE-NE MODEL OPTION .............................................. */

    teneop = ! jf[10];
    if (teneop) {
	for (jxnar = 1; jxnar <= 2; ++jxnar) {
	    xnar[jxnar - 1] = oarr[jxnar + 14];
	    tecon[jxnar - 1] = FALSE_;
/* L8154: */
	    if (xnar[jxnar - 1] > 0.) {
		tecon[jxnar - 1] = TRUE_;
	    }
	}
    } else {
	oarr[15] = -1.;
	oarr[16] = -1.;
    }

/* lists the selected options before starting the table */

    if (icalls > 1 || iounit_1.konsol == 1) {
	goto L8201;
    }
    io___49.ciunit = iounit_1.konsol;
    s_wsfe(&io___49);
    e_wsfe();
    if (noden) {
	goto L2889;
    }
    if (layver) {
	io___50.ciunit = iounit_1.konsol;
	s_wsfe(&io___50);
	e_wsfe();
    }
    if (gulb0) {
	io___51.ciunit = iounit_1.konsol;
	s_wsfe(&io___51);
	e_wsfe();
    }
    if (old79) {
	io___52.ciunit = iounit_1.konsol;
	s_wsfe(&io___52);
	e_wsfe();
    }
    if (topo && ! topc) {
	io___53.ciunit = iounit_1.konsol;
	s_wsfe(&io___53);
	e_wsfe();
    }
    if (! topo) {
	if (topc) {
	    io___54.ciunit = iounit_1.konsol;
	    s_wsfe(&io___54);
	    e_wsfe();
	} else {
	    io___55.ciunit = iounit_1.konsol;
	    s_wsfe(&io___55);
	    e_wsfe();
	}
    }
    if (fof2in) {
	io___56.ciunit = iounit_1.konsol;
	s_wsfe(&io___56);
	e_wsfe();
	goto L2889;
    }
    if (ursif2) {
	io___57.ciunit = iounit_1.konsol;
	s_wsfe(&io___57);
	e_wsfe();
    } else {
	io___58.ciunit = iounit_1.konsol;
	s_wsfe(&io___58);
	e_wsfe();
    }
    if (hmf2in) {
	io___59.ciunit = iounit_1.konsol;
	s_wsfe(&io___59);
	e_wsfe();
    }
    if (fof1in) {
	io___60.ciunit = iounit_1.konsol;
	s_wsfe(&io___60);
	e_wsfe();
    }
    if (hmf1in && layver) {
	io___61.ciunit = iounit_1.konsol;
	s_wsfe(&io___61);
	e_wsfe();
    }
    if (foein) {
	io___62.ciunit = iounit_1.konsol;
	s_wsfe(&io___62);
	e_wsfe();
    }
    if (hmein) {
	io___63.ciunit = iounit_1.konsol;
	s_wsfe(&io___63);
	e_wsfe();
    }
    if (f1_ocpro__) {
	io___64.ciunit = iounit_1.konsol;
	s_wsfe(&io___64);
	e_wsfe();
    }
    if (f1_l_cond__) {
	io___65.ciunit = iounit_1.konsol;
	s_wsfe(&io___65);
	e_wsfe();
    }
    if (dreg) {
	io___66.ciunit = iounit_1.konsol;
	s_wsfe(&io___66);
	e_wsfe();
    } else {
	io___67.ciunit = iounit_1.konsol;
	s_wsfe(&io___67);
	e_wsfe();
    }
    if (jf[26]) {
	if (fof2in) {
	    io___68.ciunit = iounit_1.konsol;
	    s_wsfe(&io___68);
	    e_wsfe();
	    jf[26] = FALSE_;
	} else {
	    io___69.ciunit = iounit_1.konsol;
	    s_wsfe(&io___69);
	    e_wsfe();
	}
    }
L2889:
    if (! noion && dy) {
	io___70.ciunit = iounit_1.konsol;
	s_wsfe(&io___70);
	e_wsfe();
    }
    if (! noion && ! dy) {
	io___71.ciunit = iounit_1.konsol;
	s_wsfe(&io___71);
	e_wsfe();
    }
    if (notem) {
	goto L8201;
    }
    if (teneop) {
	io___72.ciunit = iounit_1.konsol;
	s_wsfe(&io___72);
	e_wsfe();
    }
    if (jf[23]) {
	io___73.ciunit = iounit_1.konsol;
	s_wsfe(&io___73);
	e_wsfe();
    } else {
	io___74.ciunit = iounit_1.konsol;
	s_wsfe(&io___74);
	e_wsfe();
    }
L8201:

/* CALCULATION OF DAY OF YEAR OR MONTH/DAY AND DECIMAL YEAR */

/*  leap year rule: years evenly divisible by 4 are leap years, except */
/*  years also evenly divisible by 100 are not leap years, except years */
/*  also evenly divisible by 400 are leap years. The year 2000 is a 100 */
/*  and 400 year exception and therefore it is a normal leap year. */
/*  The next 100 year exception will be in the year 2100! */

    iyear = *iyyyy;
    if (iyear < 100) {
	iyear += 1900;
    }
    idayy = 365;
    if (iyear / 4 << 2 == iyear) {
	idayy = 366;
    }
/* leap year */
    if (*mmdd < 0) {
	daynr = -(*mmdd);
	moda_(&c__1, &iyear, &month, &iday, &daynr, &nrdaym);
    } else {
	month = *mmdd / 100;
	iday = *mmdd - month * 100;
	moda_(&c__0, &iyear, &month, &iday, &daynr, &nrdaym);
    }
    ryear = iyear + (daynr - 1.) / idayy;

/* CALCULATION OF GEODETIC/GEOMAGNETIC COORDINATES (LATI, LONGI AND */
/* MLAT, MLONG), MAGNETIC INCLINATION (DIP), DIP LATITUDE (MAGBR) */
/* AND MODIFIED DIP (MODIP), ALL IN DEGREES */

    if (*along < 0.) {
	*along += 360.;
    }
/* -180/180 to 0-360 */
    if (*jmag > 0) {
	mlat = *alati;
	mlong = *along;
    } else {
	lati = *alati;
	longi = *along;
    }
    geodip_(&iyear, &lati, &longi, &mlat, &mlong, jmag);
/*        CALL GGM(JMAG,XLONGI1,XLATI1,XMLONG1,XMLAT1) */
    igrf_dip__(&lati, &longi, &ryear, &c_b66, &dip, &magbr, &modip);
    if (! jf[18]) {
	fieldg_(&lati, &longi, &c_b66, &xma, &yma, &zma, &bet, &dip, &dec, &
		modip);
	magbr = atan(tan(dip * const_1.umr) * .5) / const_1.umr;
    }
    abslat = abs(lati);
    absmlt = abs(mlat);
    absmdp = abs(modip);
    absmbr = abs(magbr);

/* CALCULATION OF UT/LT  ............... */

    if (*dhour <= 24.) {
	hour = *dhour;
/* dhour =< 24 is LT */
	ut = hour - longi / 15.;
	if (ut < 0.) {
	    ut += 24.;
	}
    } else {
	ut = *dhour - 25.;
/* dhour>24 is UT+25 */
	hour = ut + longi / 15.;
/* hour becomes LT */
	if (hour > 24.) {
	    hour += -24.;
	}
    }

/* season assumes equal length seasons (92 days) with spring */
/* (season=1) starting at day-of-year=47; for lati<0 adjustment */
/* for southern hemisphere is made. some models require the */
/* seasonal month or the seasonal day-of year */

/* zmonth is decimal month (Jan 1 = 1.0 and Dec 31 = 12.97) */
/* 		zmonth = month + (iday*1.-1.)/nrdaym */
/* is not used currently */
    season = (integer) ((daynr + 45.) / 92.);
    if (season < 1) {
	season = 4;
    }
    nseasn = season;
/* Northern hemisphere season */
    seaday = daynr;
    iseamon = month;
    if (lati >= 0.) {
	goto L5592;
    }
    season += -2;
    if (season < 1) {
	season += 4;
    }
    iseamon = month + 6;
    if (iseamon > 12) {
	iseamon += -12;
    }
    seaday = (integer) (daynr + idayy / 2.);
    if (seaday > idayy) {
	seaday -= idayy;
    }

/* 12-month running mean sunspot number (rssn) and Ionospheric Global */
/* index (gind), daily F10.7 cm solar radio flux (f107d) and monthly */
/* F10.7 (cov) index */

L5592:
    sam_mon__ = month == montho;
    sam_yea__ = iyear == iyearo;
    sam_doy__ = daynr == idaynro;
    sam_date__ = sam_yea__ && sam_doy__;
    sam_ut__ = ut == ut0;
    if (sam_date__ && ! rzino && ! rzin && ! igin && ! igino) {
	goto L2910;
    }
    tcon_(&iyear, &month, &iday, &daynr, rzar, arig, &ttt, &nmonth);
    if (nmonth < 0) {
	goto L3330;
    }
/* jump to end of program */
    if (rzin) {
	rrr = arzin;
	rzar[0] = rrr;
	rzar[1] = rrr;
	rzar[2] = rrr;
/*       	zi=-12.349154+(1.4683266-2.67690893e-03*rrr)*rrr */
/*       	if(zi.gt.174.0) zi=174.0 */
/*       	arig(1) = zi */
/*       	arig(2) = zi */
/*       	arig(3) = zi */
    }
    if (igin) {
	zi = aigin;
	arig[0] = zi;
	arig[1] = zi;
	arig[2] = zi;
    }
    rssn = rzar[2];
    gind = arig[2];
    cov = rssn * (rssn * 8.9e-4 + .728) + 63.75;
/*        rlimit=gind */
/*        COVSAT=63.75+rlimit*(0.728+rlimit*0.00089) */
    covsat = cov;
    if (covsat > 188.) {
	covsat = 188.;
    }
    if (jf[25]) {
	f107d = cov;
	apf_only__(&iyear, &month, &iday, &f107dx);
	if (f107dx > -2.) {
	    f107d = f107dx;
	}
    }

/* CALCULATION OF SOLAR ZENITH ANGLE (XHI/DEG), SUN DECLINATION ANGLE */
/* (SUNDEC),SOLAR ZENITH ANGLE AT NOON (XHINON) AND TIME OF LOCAL */
/* SUNRISE/SUNSET (SAX, SUX; dec. hours) AT 70 KM (D-REGION), 110 KM */
/* (E-REGION), 200 KM (F1-REGION), AND 500 KM (TE, TI). */

L2910:
    soco_(&daynr, &hour, &lati, &longi, &c_b71, &sundec, &xhi1, &sax70, &
	    sux70);
    soco_(&daynr, &hour, &lati, &longi, &c_b72, &sud1, &xhi2, &sax110, &
	    sux110);
    soco_(&daynr, &hour, &lati, &longi, &c_b73, &sud1, &xhi, &sax200, &sux200)
	    ;
    soco_(&daynr, &hour, &lati, &longi, &c_b74, &sud1, &xhi3, &sax500, &
	    sux500);
    soco_(&daynr, &c_b75, &lati, &longi, &c_b72, &sunde1, &xhinon, &sax1, &
	    sux1);
    dnight = FALSE_;
    if (abs(sax70) > 25.) {
	if (sax70 < 0.) {
	    dnight = TRUE_;
	}
	goto L9334;
    }
    if (sax70 <= sux70) {
	goto L1386;
    }
    if (hour > sux70 && hour < sax70) {
	dnight = TRUE_;
    }
    goto L9334;
L1386:
    if (hour > sux70 || hour < sax70) {
	dnight = TRUE_;
    }
L9334:
    block5_1.enight = FALSE_;
    if (abs(sax110) > 25.) {
	if (sax110 < 0.) {
	    block5_1.enight = TRUE_;
	}
	goto L8334;
    }
    if (sax110 <= sux110) {
	goto L9386;
    }
    if (hour > sux110 && hour < sax110) {
	block5_1.enight = TRUE_;
    }
    goto L8334;
L9386:
    if (hour > sux110 || hour < sax110) {
	block5_1.enight = TRUE_;
    }
L8334:
    fnight = FALSE_;
    if (abs(sax200) > 25.) {
	if (sax200 < 0.) {
	    fnight = TRUE_;
	}
	goto L1334;
    }
    if (sax200 <= sux200) {
	goto L7386;
    }
    if (hour > sux200 && hour < sax200) {
	fnight = TRUE_;
    }
    goto L1334;
L7386:
    if (hour > sux200 || hour < sax200) {
	fnight = TRUE_;
    }

/* CALCULATION OF ELECTRON DENSITY PARAMETERS................ */
/* lower height boundary (HNEA), upper boundary (HNEE) */

L1334:
    hnea = 65.;
    if (dnight) {
	hnea = 80.;
    }
    hnee = 2e3;
    if (noden) {
	goto L4933;
    }
    dela = 4.32;
    if (absmdp >= 18.) {
	dela = exp(-(absmdp - 30.) / 10.) + 1.;
    }
    dell = exp(-(abslat - 20.) / 10.) + 1;

/* E peak critical frequency (foF2), density (NmE), and height (hmE) */

    if (foein) {
	foe = afoe;
    } else {
	foe = foeedi_(&cov, &xhi, &xhinon, &abslat);
    }
    block4_1.nme = foe * 1.24e10 * foe;
    if (hmein) {
	block4_1.hme = ahme;
    } else {
	block4_1.hme = 110.;
    }

/* F2 peak critical frequency foF2, density NmF2, and height hmF2 */

/* READ CCIR AND URSI COEFFICIENT SET FOR CHOSEN MONTH */

    if (fof2in && hmf2in && blo11_1.itopn != 2) {
	goto L501;
    }
    if (ursif2 != ursifo) {
	goto L7797;
    }
    if (! rzin && ! rzino && ! igin && ! igino) {
	if (sam_mon__ && nmonth == nmono && sam_yea__) {
	    goto L4292;
	}
	if (sam_mon__) {
	    goto L4293;
	}
    }

/* the program expects the coefficients files in ASCII format; if you */
/* want to use the binary version of the coefficients, please use the */
/* the statements that are commented-out below and comment-out the */
/* ASCII-related statements. */

L7797:
    ursifo = ursif2;
    s_wsfi(&io___154);
    i__1 = month + 10;
    do_fio(&c__1, (char *)&i__1, (ftnlen)sizeof(integer));
    e_wsfi();
/* -binary- if binary files than use: */
/* -binary-104   FORMAT('ccir',I2,'.bin') */
/* -web- special for web-version: */
/* 104   FORMAT('/usr/local/etc/httpd/cgi-bin/models/IRI/ccir',I2,'.asc') */
/* -web- special for web-version: */

    o__1.oerr = 1;
    o__1.ounit = iuccir;
    o__1.ofnmlen = 12;
    o__1.ofnm = filnam;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    i__1 = f_open(&o__1);
    if (i__1 != 0) {
	goto L8448;
    }
/* -binary- if binary files than use: */
/* -binary-     &          FORM='UNFORMATTED') */

    io___155.ciunit = iuccir;
    s_rsfe(&io___155);
    do_fio(&c__1976, (char *)&f2[0], (ftnlen)sizeof(doublereal));
    do_fio(&c__882, (char *)&fm3[0], (ftnlen)sizeof(doublereal));
    e_rsfe();
/* -binary- if binary files than use: */
/* -binary-        READ(IUCCIR) F2,FM3 */

    cl__1.cerr = 0;
    cl__1.cunit = iuccir;
    cl__1.csta = 0;
    f_clos(&cl__1);

/* then URSI if chosen .................................... */

    if (ursif2) {
	s_wsfi(&io___158);
	i__1 = month + 10;
	do_fio(&c__1, (char *)&i__1, (ftnlen)sizeof(integer));
	e_wsfi();
/* -web- special for web-version: */
/* 1144  FORMAT('/usr/local/etc/httpd/cgi-bin/models/IRI/ursi',I2,'.asc') */
/* -binary- if binary files than use: */
/* -binary-1144          FORMAT('ursi',I2,'.bin') */
	o__1.oerr = 1;
	o__1.ounit = iuccir;
	o__1.ofnmlen = 12;
	o__1.ofnm = filnam;
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = "FORMATTED";
	o__1.oblnk = 0;
	i__1 = f_open(&o__1);
	if (i__1 != 0) {
	    goto L8448;
	}
/* -binary- if binary files than use: */
/* -binary-     &         FORM='UNFORMATTED') */
	io___159.ciunit = iuccir;
	s_rsfe(&io___159);
	do_fio(&c__1976, (char *)&f2[0], (ftnlen)sizeof(doublereal));
	e_rsfe();
/* -binary- if binary files than use: */
/* -binary-          READ(IUCCIR) F2 */
	cl__1.cerr = 0;
	cl__1.cunit = iuccir;
	cl__1.csta = 0;
	f_clos(&cl__1);
    }

/* READ CCIR AND URSI COEFFICIENT SET FOR NMONTH, i.e. previous */
/* month if day is less than 15 and following month otherwise */

L4293:

/* first CCIR .............................................. */

    s_wsfi(&io___160);
    i__1 = nmonth + 10;
    do_fio(&c__1, (char *)&i__1, (ftnlen)sizeof(integer));
    e_wsfi();
    o__1.oerr = 1;
    o__1.ounit = iuccir;
    o__1.ofnmlen = 12;
    o__1.ofnm = filnam;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    i__1 = f_open(&o__1);
    if (i__1 != 0) {
	goto L8448;
    }
/* -binary- if binary files than use: */
/* -binary-     &          FORM='unFORMATTED') */
    io___161.ciunit = iuccir;
    s_rsfe(&io___161);
    do_fio(&c__1976, (char *)&f2n[0], (ftnlen)sizeof(doublereal));
    do_fio(&c__882, (char *)&fm3n[0], (ftnlen)sizeof(doublereal));
    e_rsfe();
/* -binary- if binary files than use: */
/* -binary-        READ(IUCCIR) F2N,FM3N */
    cl__1.cerr = 0;
    cl__1.cunit = iuccir;
    cl__1.csta = 0;
    f_clos(&cl__1);

/* then URSI if chosen ..................................... */

    if (ursif2) {
	s_wsfi(&io___164);
	i__1 = nmonth + 10;
	do_fio(&c__1, (char *)&i__1, (ftnlen)sizeof(integer));
	e_wsfi();
	o__1.oerr = 1;
	o__1.ounit = iuccir;
	o__1.ofnmlen = 12;
	o__1.ofnm = filnam;
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = "FORMATTED";
	o__1.oblnk = 0;
	i__1 = f_open(&o__1);
	if (i__1 != 0) {
	    goto L8448;
	}
/* -binary- if binary files than use: */
/* -binary-     &         FORM='unFORMATTED') */
	io___165.ciunit = iuccir;
	s_rsfe(&io___165);
	do_fio(&c__1976, (char *)&f2n[0], (ftnlen)sizeof(doublereal));
	e_rsfe();
/* -binary- if binary files than use: */
/* -binary-          READ(IUCCIR) F2N */
	cl__1.cerr = 0;
	cl__1.cunit = iuccir;
	cl__1.csta = 0;
	f_clos(&cl__1);
    }
    goto L4291;
L8448:
    io___166.ciunit = iounit_1.konsol;
    s_wsfe(&io___166);
    do_fio(&c__1, filnam, (ftnlen)12);
    e_wsfe();
    goto L3330;

/* LINEAR INTERPOLATION IN SOLAR ACTIVITY. IG12 used for foF2 */

L4291:
    rr2 = arig[0] / 100.;
    rr2n = arig[1] / 100.;
    rr1 = 1. - rr2;
    rr1n = 1. - rr2n;
    for (i__ = 1; i__ <= 76; ++i__) {
	for (j = 1; j <= 13; ++j) {
	    k = j + (i__ - 1) * 13;
	    ff0n[k - 1] = f2n[j + (i__ + 76) * 13 - 1002] * rr1n + f2n[j + (
		    i__ + 152) * 13 - 1002] * rr2n;
/* L20: */
	    ff0[k - 1] = f2[j + (i__ + 76) * 13 - 1002] * rr1 + f2[j + (i__ + 
		    152) * 13 - 1002] * rr2;
	}
    }
    rr2 = rzar[0] / 100.;
    rr2n = rzar[1] / 100.;
    rr1 = 1. - rr2;
    rr1n = 1. - rr2n;
    for (i__ = 1; i__ <= 49; ++i__) {
	for (j = 1; j <= 9; ++j) {
	    k = j + (i__ - 1) * 9;
	    xm0n[k - 1] = fm3n[j + (i__ + 49) * 9 - 451] * rr1n + fm3n[j + (
		    i__ + 98) * 9 - 451] * rr2n;
/* L30: */
	    xm0[k - 1] = fm3[j + (i__ + 49) * 9 - 451] * rr1 + fm3[j + (i__ + 
		    98) * 9 - 451] * rr2;
	}
    }
L4292:
    zfof2 = fout_(&modip, &lati, &longi, &ut, ff0);
    fof2n = fout_(&modip, &lati, &longi, &ut, ff0n);
    zm3000 = xmout_(&modip, &lati, &longi, &ut, xm0);
    xm300n = xmout_(&modip, &lati, &longi, &ut, xm0n);
    midm = 15;
    if (month == 2) {
	midm = 14;
    }
    if (iday < midm) {
	yfof2 = fof2n + ttt * (zfof2 - fof2n);
	xm3000 = xm300n + ttt * (zm3000 - xm300n);
    } else {
	yfof2 = zfof2 + ttt * (fof2n - zfof2);
	xm3000 = zm3000 + ttt * (xm300n - zm3000);
    }
L501:
    if (fof2in) {
	fof2 = afof2;
    } else {
	fof2 = yfof2;
    }
    block1_1.nmf2 = fof2 * 1.24e10 * fof2;
    if (hmf2in) {
	if (ahmf2 < 50.) {
	    xm3000 = ahmf2;
	    d__1 = fof2 / foe;
	    block1_1.hmf2 = hmf2ed_(&magbr, &rssn, &d__1, &xm3000);
	} else {
	    block1_1.hmf2 = ahmf2;
/*          	XM3000=XM3000HM(MAGBR,RSSN,FOF2/FOE,HMF2) */
	}
    } else {
	d__1 = fof2 / foe;
	block1_1.hmf2 = hmf2ed_(&magbr, &rssn, &d__1, &xm3000);
    }

/* stormtime updating */

    stormcorr = -1.;
    if (jf[26]) {
	if (! sam_date__ || ! sam_ut__) {
	    apf_(&iyear, &month, &iday, &ut, indap);
	}
	if (indap[0] > -2) {
	    icoord = 1;
	    kut = (integer) ut;
	    storm_(indap, &lati, &longi, &icoord, &cglat, &kut, &daynr, &
		    stormcorr);
	    fof2 *= stormcorr;
	    block1_1.nmf2 = fof2 * 1.24e10 * fof2;
	}
    }
    nmono = nmonth;
    montho = month;
    iyearo = iyear;
    idaynro = daynr;
    rzino = rzin;
    igino = igin;
    ut0 = ut;

/* topside profile parameters ............................. */

    cos2 = cos(mlat * const_1.umr);
    cos2 *= cos2;
    flu = (covsat - 40.) / 30.;
/* option to use unlimiited F10.7M for the topside */
    if (old79) {
	flu = (cov - 40.) / 30.;
    }
/* previously: IF(OLD79) ETA1=-0.0070305*COS2 */
    ex = exp(-mlat / 15.);
    ex1 = ex + 1;
    epin = ex * 4. / (ex1 * ex1);
    eta1 = epin * -.02;
    blo10_1.eta = eta1 + .058798 - flu * (.014065 - cos2 * .0069724) + fof2 * 
	    (cos2 * .004281 + .0024287 - fof2 * 1.528e-4);
/*        fluu=flu */
/* orr    if(fluu.gt.flumax) fluu=flumax */
    blo10_1.zeta = .078922 - cos2 * .0046702 - flu * (.019132 - cos2 * 
	    .0076545) + fof2 * (cos2 * .006029 + .0032513 - fof2 * 2.0872e-4);
    blo10_1.beta = cos2 * 20.253 - 128.03 - flu * (cos2 * .65896 + 8.0755) + 
	    fof2 * (cos2 * .71458 + .44041 - fof2 * .042966);
    z__ = exp(94.5 / blo10_1.beta);
/* orr    Z=EXP(94.45/BETA) */
    z1 = z__ + 1;
    z2 = z__ / (blo10_1.beta * z1 * z1);
    blo10_1.delta = (blo10_1.eta / z1 - blo10_1.zeta / 2.) / (blo10_1.eta * 
	    z2 + blo10_1.zeta / 400.);

/* Correction term for topside */

    if (blo11_1.itopn == 1) {
	zmp1 = exp(modip / 10.);
	zmp11 = zmp1 + 1.;
	zmp111 = zmp1 / (zmp11 * zmp11);
	zmp2 = exp(modip / 19.);
	zmp22 = zmp2 + 1.;
	zmp222 = zmp2 / (zmp22 * zmp22);
	r2n = -.84 - zmp111 * 1.6;
	r2d = -.84 - zmp111 * .64;
	x1n = 230. - zmp222 * 700.;
	x1d = 550. - zmp222 * 1900.;
	r2 = hpol_(&hour, &r2d, &r2n, &sax500, &sux500, &c_b119, &c_b119);
	x1 = hpol_(&hour, &x1d, &x1n, &sax500, &sux500, &c_b119, &c_b119);
	blo11_1.hcor1 = block1_1.hmf2 + x1;
	x12 = 1500. - x1;
	blo11_1.tc3 = r2 / x12;
    }

/* NeQuick topside parameters (use CCIR-M3000F2 even if user-hmF2) */

    if (blo11_1.itopn == 2) {
	dndhmx = log(fof2) * 1.714 - 3.467 + log(xm3000) * 2.02;
	dndhmx = exp(dndhmx) * .01;
	b2bot = fof2 * .04774 * fof2 / dndhmx;
	b2k = 3.22 - fof2 * .0538 - block1_1.hmf2 * .00664 + block1_1.hmf2 * 
		.113 / b2bot + rssn * .00257;
	ee = exp((b2k - 1.) * 2.);
	b2k = (b2k * ee + 1.) / (ee + 1.);
	blo11_1.b2top = b2k * b2bot;
    }

/* F layer - bottomside thickness parameter B0 and shape parameters B1 */

    block2_1.b1 = hpol_(&hour, &c_b123, &c_b124, &sax200, &sux200, &c_b119, &
	    c_b119);
    if (gulb0) {
	rogul_(&seaday, &xhi, &seax, &grat);
	if (fnight) {
	    grat = .91 - block1_1.hmf2 / 4e3;
	}
	bcoef = block2_1.b1 * (block2_1.b1 * (block2_1.b1 * .0046 - .0548) + 
		.2546) + .3606;
	b0cnew = block1_1.hmf2 * (1. - grat);
	block2_1.b0 = b0cnew / bcoef;
    } else {
	block2_1.b0 = b0_98__(&hour, &sax200, &sux200, &nseasn, &rssn, &longi,
		 &modip);
    }

/* F1 layer height hmF1, critical frequency foF1, peak density NmF1 */

    if (fof1in) {
	fof1 = afof1;
    } else {
	fof1 = fof1ed_(&absmbr, &rssn, &xhi);
    }
/* F1 layer thickness parameter c1 */
    block2_1.c1 = f1_c1__(&modip, &hour, &sux200, &sax200);
/* F1 occurrence probability with Scotto et al. 1997 */
    f1_prob__(&xhi, &mlat, &rssn, &f1pbw, &f1pbl);
/* F1 occurrence probability Ducharme et al. */
    f1pbo = 0.;
    if (fof1in || ! fnight && fof1 > 0.) {
	f1pbo = 1.;
    }
    if (f1_ocpro__) {
	f1pb = f1pbw;
	if (f1_l_cond__) {
	    f1pb = f1pbl;
	}
	block1_1.f1reg = FALSE_;
	if (fof1in || f1pb >= .5) {
	    block1_1.f1reg = TRUE_;
	}
    } else {
	f1pb = f1pbo;
	block1_1.f1reg = FALSE_;
	if (f1pb > 0.) {
	    block1_1.f1reg = TRUE_;
	}
    }
    nmf1 = fof1 * 1.24e10 * fof1;

/* E-valley: depth, width, height of deepest point (HDEEP), */
/* height of valley top (HEF) */

    xdel = xdels[season - 1] / dela;
    dndhbr = dnds[season - 1] / dela;
    d__1 = 10.5 / dela;
    hdeep = hpol_(&hour, &d__1, &c_b127, &sax110, &sux110, &c_b119, &c_b119);
    d__1 = 17.8 / dela;
    d__2 = 22. / dela + 45.;
    width = hpol_(&hour, &d__1, &d__2, &sax110, &sux110, &c_b119, &c_b119);
    depth = hpol_(&hour, &xdel, &c_b132, &sax110, &sux110, &c_b119, &c_b119);
    dlndh = hpol_(&hour, &dndhbr, &c_b135, &sax110, &sux110, &c_b119, &c_b119)
	    ;
    if (depth < 1.) {
	goto L600;
    }
    if (block5_1.enight) {
	depth = -depth;
    }
    tal_(&hdeep, &depth, &width, &dlndh, &ext, block5_1.e);
    if (! ext) {
	goto L667;
    }
    if (iounit_1.konsol > 1) {
	io___234.ciunit = iounit_1.konsol;
	s_wsfe(&io___234);
	e_wsfe();
    }
L600:
    width = 0.;
L667:
    block4_1.hef = block4_1.hme + width;
    hefold = block4_1.hef;
    vner = (1. - abs(depth) / 100.) * block4_1.nme;

/* Parameters below E  ............................. */

/* L2727: */
    hmex = block4_1.hme - 9.;
    block6_1.nmd = xmded_(&xhi, &rssn, &c_b143);
    block6_1.hmd = hpol_(&hour, &c_b132, &c_b145, &sax70, &sux70, &c_b119, &
	    c_b119);
    d__1 = .03 / dela + .02;
    f[0] = hpol_(&hour, &d__1, &c_b148, &sax70, &sux70, &c_b119, &c_b119);
    f[1] = hpol_(&hour, &c_b151, &c_b152, &sax70, &sux70, &c_b119, &c_b119);
    f[2] = hpol_(&hour, &c_b155, &c_b156, &sax70, &sux70, &c_b119, &c_b119);
    block7_1.fp1 = f[0];
    block7_1.fp2 = -block7_1.fp1 * block7_1.fp1 / 2.;
    block7_1.fp30 = (-f[1] * block7_1.fp2 - block7_1.fp1 + 1. / f[1]) / (f[1] 
	    * f[1]);
    block7_1.fp3u = (-f[2] * block7_1.fp2 - block7_1.fp1 - 1. / f[2]) / (f[2] 
	    * f[2]);
    block6_1.hdx = block6_1.hmd + f[1];

/* indermediate region between D and E region; parameters xkk */
/* and d1 are found such that the function reaches hdx/xdx/dxdh */

    x = block6_1.hdx - block6_1.hmd;
    xdx = block6_1.nmd * exp(x * (block7_1.fp1 + x * (block7_1.fp2 + x * 
	    block7_1.fp30)));
    dxdx = xdx * (block7_1.fp1 + x * (block7_1.fp2 * 2. + x * 3. * 
	    block7_1.fp30));
    x = block4_1.hme - block6_1.hdx;
    block7_1.xkk = -dxdx * x / (xdx * log(xdx / block4_1.nme));

/* if exponent xkk is larger than xkkmax, then xkk will be set to */
/* xkkmax and d1 will be determined such that the point hdx/xdx is */
/* reached; derivative is no longer continuous. */

    xkkmax = 5.;
    if (block7_1.xkk > xkkmax) {
	block7_1.xkk = xkkmax;
	block7_1.d1 = -log(xdx / block4_1.nme) / pow_dd(&x, &block7_1.xkk);
    } else {
	d__1 = block7_1.xkk - 1.;
	block7_1.d1 = dxdx / (xdx * block7_1.xkk * pow_dd(&x, &d__1));
    }

/* compute Danilov et al. (1995) D-region model values */

    if (! dreg) {
	vkp = 1.;
	f5sw = 0.;
	f6wa = 0.;
	dregion_(&xhi, &month, &f107d, &vkp, &f5sw, &f6wa, elg);
	for (ii = 1; ii <= 7; ++ii) {
	    d__1 = elg[ii - 1] + 6;
	    ddens[ii * 3 - 3] = pow_dd(&c_b159, &d__1);
	}
	f5sw = 1.;
	f6wa = 0.;
	dregion_(&xhi, &month, &f107d, &vkp, &f5sw, &f6wa, elg);
	for (ii = 1; ii <= 7; ++ii) {
	    d__1 = elg[ii - 1] + 6;
	    ddens[ii * 3 - 2] = pow_dd(&c_b159, &d__1);
	}
	f5sw = 0.;
	f6wa = 1.;
	dregion_(&xhi, &month, &f107d, &vkp, &f5sw, &f6wa, elg);
	for (ii = 1; ii <= 7; ++ii) {
	    d__1 = elg[ii - 1] + 6;
	    ddens[ii * 3 - 1] = pow_dd(&c_b159, &d__1);
	}
    }

/* SEARCH FOR HMF1 .................................................. */

    if (layver) {
	goto L6153;
    }
    block1_1.hmf1 = 0.;
    if (! block1_1.f1reg) {
	goto L380;
    }
/* omit F1 feature if nmf1*0.9 is smaller than nme */
    bnmf1 = nmf1 * .9;
    if (block4_1.nme >= bnmf1) {
	goto L9427;
    }
L9245:
    xe2h = xe2_(&block4_1.hef);
    if (xe2h > bnmf1) {
	block4_1.hef += -1;
	if (block4_1.hef <= block4_1.hme) {
	    goto L9427;
	}
	goto L9245;
    }
    regfa1_(&block4_1.hef, &block1_1.hmf2, &xe2h, &block1_1.nmf2, &c_b166, &
	    nmf1, xe2_, &schalt, &block1_1.hmf1);
    if (! schalt) {
	goto L3801;
    }

/* omit F1 feature .................................................... */

L9427:
    if (iounit_1.konsol > 1) {
	io___252.ciunit = iounit_1.konsol;
	s_wsfe(&io___252);
	e_wsfe();
    }
    block1_1.hmf1 = 0.;
    block1_1.f1reg = FALSE_;
/*        NMF1=0. */
/*        C1=0.0 */

/* Determine E-valley parameters if HEF was changed */

L3801:
    if (block4_1.hef != hefold) {
	width = block4_1.hef - block4_1.hme;
	if (block5_1.enight) {
	    depth = -depth;
	}
	tal_(&hdeep, &depth, &width, &dlndh, &ext, block5_1.e);
	if (! ext) {
	    goto L380;
	}
	if (iounit_1.konsol > 1) {
	    io___253.ciunit = iounit_1.konsol;
	    s_wsfe(&io___253);
	    e_wsfe();
	}
	width = 0.;
	block4_1.hef = block4_1.hme;
	hefold = block4_1.hef;
	goto L9245;
    }

/* SEARCH FOR HST [NE3(HST)=NME] ...................................... */

L380:
    if (block1_1.f1reg) {
	hf1 = block1_1.hmf1;
	xf1 = nmf1;
    } else {
	hf1 = (block1_1.hmf2 + block4_1.hef) / 2.;
	xf1 = xe2_(&hf1);
    }
    hf2 = block4_1.hef;
    xf2 = xe3_1__(&hf2);
    if (xf2 > block4_1.nme) {
	goto L3885;
    }
    regfa1_(&hf1, &hf2, &xf1, &xf2, &c_b166, &block4_1.nme, xe3_1__, &schalt, 
	    &block3_1.hst);
    if (schalt) {
	goto L3885;
    }
    block3_1.hz = (block3_1.hst + hf1) / 2.;
    d__ = block3_1.hz - block3_1.hst;
    block3_1.t = d__ * d__ / (block3_1.hz - block4_1.hef - d__);
    goto L4933;

/* assume linear interpolation between HZ and HEF .................. */

L3885:
    if (iounit_1.konsol > 1) {
	io___259.ciunit = iounit_1.konsol;
	s_wsfe(&io___259);
	e_wsfe();
    }
    block3_1.hz = (block4_1.hef + hf1) / 2.;
    xnehz = xe3_1__(&block3_1.hz);
    if (iounit_1.konsol > 1) {
	io___261.ciunit = iounit_1.konsol;
	s_wsfe(&io___261);
	do_fio(&c__1, (char *)&block3_1.hz, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&block4_1.hef, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    block3_1.t = (xnehz - block4_1.nme) / (block3_1.hz - block4_1.hef);
    block3_1.hst = -333.;
    goto L4933;

/* LAY-functions for middle ionosphere */

L6153:
    if (hmf1in) {
	hmf1m = ahmf1;
    } else {
	hmf1m = xhi * .6428 + 165.;
    }
    hhalf = grat * block1_1.hmf2;
    hv1r = block4_1.hme + width;
    hv2r = block4_1.hme + hdeep;
    hhmf2 = block1_1.hmf2;
    inilay_(&fnight, &block1_1.f1reg, &block1_1.nmf2, &nmf1, &block4_1.nme, &
	    vner, &hhmf2, &hmf1m, &block4_1.hme, &hv1r, &hv2r, &hhalf, hxl, 
	    scl, amp, &iiqu);
    if (iiqu == 1 && iounit_1.konsol > 1) {
	io___271.ciunit = iounit_1.konsol;
	s_wsfe(&io___271);
	e_wsfe();
    }
    if (iiqu == 2 && iounit_1.konsol > 1) {
	io___272.ciunit = iounit_1.konsol;
	s_wsfe(&io___272);
	e_wsfe();
    }

/* ---------- CALCULATION OF NEUTRAL TEMPERATURE PARAMETER------- */

L4933:
    hta = 120.;
    if (notem) {
	goto L240;
    }
    sec = ut * 3600.;
    cira86_(&daynr, &sec, &lati, &longi, &hour, &cov, &blotn_1.texos, &tn120, 
	    &blotn_1.sigma);
    if (hour != 0.) {
	iyz = iyear;
	idz = daynr;
	if (jf[18]) {
	    secni = (24. - longi / 15) * 3600.;
	} else {
	    ut_lt__(&c__1, &utni, &c_b184, &longi, &iyz, &idz);
	    secni = utni * 3600.;
	}
	cira86_(&daynr, &secni, &lati, &longi, &c_b184, &cov, &texni, &tn1ni, 
		&signi);
    } else {
	texni = blotn_1.texos;
	tn1ni = tn120;
	signi = blotn_1.sigma;
    }
    blotn_1.tlbdh = blotn_1.texos - tn120;
    tlbdn = texni - tn1ni;

/* --------- CALCULATION OF ELECTRON TEMPERATURE PARAMETER-------- */

/* L881: */
/* Te(120km) = Tn(120km) */
    blote_1.ahh[0] = 120.;
    ate[0] = tn120;
/* Te-MAXIMUM based on JICAMARCA and ARECIBO data */
/* Computing 2nd power */
    d__1 = mlat / 22.41;
    hmaxd = exp(-(d__1 * d__1)) * 60. + 210.;
    hmaxn = 150.;
    blote_1.ahh[1] = hpol_(&hour, &hmaxd, &hmaxn, &sax200, &sux200, &c_b119, &
	    c_b119);
/* Computing 2nd power */
    d__1 = mlat / 33.;
    tmaxd = exp(-(d__1 * d__1)) * 800. + 1500.;
    tmaxn = tn_(&hmaxn, &texni, &tlbdn, &signi) + 20;
    ate[1] = hpol_(&hour, &tmaxd, &tmaxn, &sax200, &sux200, &c_b119, &c_b119);
/* Te(300km), Te(400km) from AE-C, Te(1400km), Te(3000km) from */
/* ISIS, Brace and Theis */
    diplat = magbr;
    teba_(&diplat, &hour, &nseasn, tea);
    icd = 0;
    if (jf[23]) {
/* Te at fixed heights taken from Brace and Theis */
	blote_1.ahh[2] = 300.;
	blote_1.ahh[3] = 400.;
	blote_1.ahh[4] = 600.;
	blote_1.ahh[5] = 1400.;
	blote_1.ahh[6] = 3e3;
	hte = 3e3;
	ate[2] = tea[0];
	ate[3] = tea[1];
	ate[5] = tea[2];
	ate[6] = tea[3];
/* Te(600km) from AEROS, Spenner and Plugge (1979) */
	ett = exp(-mlat / 11.35);
	d__1 = ett + 1;
	tet = 2900. - ett * 5600. / pow_dd(&d__1, &c_b191);
	ten = 1161. / (exp(-(absmlt - 45.) / 5.) + 1.) + 839.;
	ate[4] = hpol_(&hour, &tet, &ten, &sax500, &sux500, &c_b192, &c_b192);
    } else {
/* Te at fixed heights from IK, Truhlik, Triskova, Smilauer */
	blote_1.ahh[2] = 300.;
	blote_1.ahh[3] = 550.;
	blote_1.ahh[4] = 900.;
	blote_1.ahh[5] = 1500.;
	blote_1.ahh[6] = 2500.;
	hte = 2500.;
	dimo = .311653;
/*              icd=1    ! compute INVDIP */
/*              isa=0    ! solar activity correction off */
/*              ise=0    ! season correction off */
	for (ijk = 4; ijk <= 7; ++ijk) {
	    igrf_sub__(&lati, &longi, &ryear, &blote_1.ahh[ijk - 1], &xl, &
		    icode, &dipl, &babs);
	    if (xl > 10.) {
		xl = 10.;
	    }
	    elteik_(&c__1, &c__0, &c__0, &invdip, &xl, &dimo, &babs, &dipl, &
		    hour, &blote_1.ahh[ijk - 1], &daynr, &f107d, &teh2, &sdte)
		    ;
/* L3491: */
	    ate[ijk - 1] = teh2;
	}
	ate[2] = tea[0];
    }
/* Option to use Te = f(Ne) relation at ahh(3), ahh(4) */
    if (teneop) {
	for (i__ = 1; i__ <= 2; ++i__) {
/* L3395: */
	    if (tecon[i__ - 1]) {
		d__1 = -cov;
		ate[i__ + 1] = tede_(&blote_1.ahh[i__ + 1], &xnar[i__ - 1], &
			d__1);
	    }
	}
    }
/* Te corrected and Te > Tn enforced */
    tnahh2 = tn_(&blote_1.ahh[1], &blotn_1.texos, &blotn_1.tlbdh, &
	    blotn_1.sigma);
    if (ate[1] < tnahh2) {
	ate[1] = tnahh2;
    }
    stte1 = (ate[1] - ate[0]) / (blote_1.ahh[1] - blote_1.ahh[0]);
    for (i__ = 2; i__ <= 6; ++i__) {
	tnahhi = tn_(&blote_1.ahh[i__], &blotn_1.texos, &blotn_1.tlbdh, &
		blotn_1.sigma);
	if (ate[i__] < tnahhi) {
	    ate[i__] = tnahhi;
	}
	stte2 = (ate[i__] - ate[i__ - 1]) / (blote_1.ahh[i__] - blote_1.ahh[
		i__ - 1]);
	ate[i__ - 1] -= (stte2 - stte1) * blote_1.dte[i__ - 2] * alog2;
/* L1901: */
	stte1 = stte2;
    }
/* Te gradients STTE are computed for each segment */
    for (i__ = 1; i__ <= 6; ++i__) {
/* L1902: */
	blote_1.stte[i__ - 1] = (ate[i__] - ate[i__ - 1]) / (blote_1.ahh[i__] 
		- blote_1.ahh[i__ - 1]);
    }
    blote_1.ate1 = ate[0];
/* L887: */

/* ------------ CALCULATION OF ION TEMPERATURE PARAMETERS-------- */

/* Ti(430km) during daytime from AEROS data */
    blotn_1.xsm1 = 430.;
    block8_1.xsm[0] = blotn_1.xsm1;
    z1 = exp(mlat * -.09);
    z2 = z1 + 1.;
    tid1 = 1240. - z1 * 1400. / (z2 * z2);
    block8_1.mm[1] = hpol_(&hour, &c_b202, &c_b184, &sax500, &sux500, &c_b119,
	     &c_b119);
/* Ti(430km) duirng nighttime from AEROS data */
    z1 = absmlt;
    z2 = z1 * (z1 * .024 + .47) * const_1.umr;
    z3 = cos(z2);
    tin1 = 1200. - d_sign(&c_b119, &z3) * 300. * sqrt((abs(z3)));
/* Ti(430km) for specified time using HPOL */
    ti1 = tin1;
    if (tid1 > tin1) {
	ti1 = hpol_(&hour, &tid1, &tin1, &sax500, &sux500, &c_b119, &c_b119);
    }
/* Tn < Ti < Te enforced */
    ten1 = elte_(&blotn_1.xsm1);
    tnn1 = tn_(&blotn_1.xsm1, &texni, &tlbdn, &signi);
    if (ten1 < tnn1) {
	ten1 = tnn1;
    }
    if (ti1 > ten1) {
	ti1 = ten1;
    }
    if (ti1 < tnn1) {
	ti1 = tnn1;
    }
/* Tangent on Tn profile determines HS */
    ti13 = teder_(&c_b209);
    ti50 = teder_(&c_b74);
    regfa1_(&c_b209, &c_b74, &ti13, &ti50, &c_b213, &ti1, teder_, &schalt, &
	    block8_1.hs);
    if (schalt) {
	block8_1.hs = 200.;
    }
    block8_1.tnhs = tn_(&block8_1.hs, &blotn_1.texos, &blotn_1.tlbdh, &
	    blotn_1.sigma);
    block8_1.mm[0] = dtndh_(&block8_1.hs, &blotn_1.texos, &blotn_1.tlbdh, &
	    blotn_1.sigma);
    if (schalt) {
	block8_1.mm[0] = (ti1 - block8_1.tnhs) / (blotn_1.xsm1 - block8_1.hs);
    }
    block8_1.mxsm = 2;
/* XTETI is altitude where Te=Ti */
/* L2391: */
    xtts = 500.;
    x = 500.;
L2390:
    x += xtts;
    if (x >= blote_1.ahh[6]) {
	goto L240;
    }
    tex = elte_(&x);
    tix = ti_(&x);
    if (tix < tex) {
	goto L2390;
    }
    x -= xtts;
    xtts /= 10.;
    if (xtts > .1) {
	goto L2390;
    }
    xteti = x + xtts * 5.;
/* Ti=Te above XTETI */
    block8_1.mxsm = 3;
    block8_1.mm[2] = blote_1.stte[5];
    block8_1.xsm[1] = xteti;
    if (xteti > blote_1.ahh[5]) {
	goto L240;
    }
    block8_1.mxsm = 4;
    block8_1.mm[2] = blote_1.stte[4];
    block8_1.mm[3] = blote_1.stte[5];
    block8_1.xsm[2] = blote_1.ahh[5];
    if (xteti > blote_1.ahh[4]) {
	goto L240;
    }
    block8_1.mxsm = 5;
    block8_1.dti[0] = 5.;
    block8_1.dti[1] = 5.;
    block8_1.mm[2] = blote_1.stte[3];
    block8_1.mm[3] = blote_1.stte[4];
    block8_1.mm[4] = blote_1.stte[5];
    block8_1.xsm[2] = blote_1.ahh[4];
    block8_1.xsm[3] = blote_1.ahh[5];

/* CALCULATION OF ION DENSITY PARAMETER.................. */

L240:
    if (noion) {
	goto L141;
    }
    hnia = 100.;
    if (dy) {
	hnia = 75.;
    }
    hnie = 2e3;
    if (dy) {
	goto L141;
    }

/* INPUT OF THE ION DENSITY PARAMETER ARRAYS PF1O,PF2O AND PF3O...... */

    rif[0] = 2.;
    if (abslat < 30.) {
	rif[0] = 1.;
    }
    rif[1] = 2.;
    if (cov < 100.) {
	rif[1] = 1.;
    }
    rif[2] = (doublereal) season;
    if (season == 1) {
	rif[2] = 3.;
    }
    rif[3] = 1.;
    if (fnight) {
	rif[3] = 2.;
    }
    koefp1_(pg1o);
    koefp2_(pg2o);
    koefp3_(pg3o);
    sufe_(pg1o, rif, &c__12, pf1o);
    sufe_(pg2o, rif, &c__4, pf2o);
    sufe_(pg3o, rif, &c__12, pf3o);

/* calculate O+ profile parameters */

    if (fnight) {
	zzz1 = 0.;
    } else {
	zzz1 = cos(xhi * const_1.umr);
    }
    msumo = 4;
    rdomax = 100.;
    mo[0] = epstep_(pf1o, &pf1o[1], &pf1o[2], &pf1o[3], &zzz1);
    mo[1] = epstep_(&pf1o[4], &pf1o[5], &pf1o[6], &pf1o[7], &zzz1);
    mo[2] = 0.;
    ho[0] = epstep_(&pf1o[8], &pf1o[9], &pf1o[10], &pf1o[11], &zzz1);
    ho[1] = 290.;
    if (rif[1] == 2. && rif[2] == 2.) {
	ho[1] = 237.;
    }
    ho[3] = pf2o[0];
    ho05 = pf2o[3];
    mo[3] = pf2o[1];
    mo[4] = pf2o[2];

/* adjust gradient MO(4) of O+ profile segment above F peak */

L7100:
    ho[2] = (alg100 - mo[4] * (ho[3] - ho05)) / mo[3] + ho[3];
    if (ho[2] <= ho[1] + 20.) {
	mo[3] += -.001;
	goto L7100;
    }
    hfixo = (ho[1] + ho[2]) / 2.;

/* find height H0O of maximum O+ relative density */

    delx = 5.;
    x = ho[1];
    ymaxx = 0.;
L7102:
    x += delx;
    y = rpid_(&x, &hfixo, &rdomax, &msumo, mo, ddo, ho);
    if (y <= ymaxx) {
	if (delx <= .1) {
	    goto L7104;
	}
	x -= delx;
	delx /= 5.;
    } else {
	ymaxx = y;
    }
    goto L7102;
L7104:
    h0o = x - delx / 2.;
L7101:
    if (y < 100.) {
	goto L7103;
    }
    rdomax += -.01;
    y = rpid_(&h0o, &hfixo, &rdomax, &msumo, mo, ddo, ho);
    goto L7101;
L7103:
    yo2h0o = 100. - y;
    yoh0o = y;

/* calculate parameters for O2+ profile */

    hfixo2 = pf3o[0];
    rdo2mx = pf3o[1];
    for (l = 1; l <= 2; ++l) {
	i__ = l << 1;
	ho2[l - 1] = pf3o[i__] + pf3o[i__ + 1] * zzz1;
/* L7105: */
	mo2[l] = pf3o[i__ + 6] + pf3o[i__ + 7] * zzz1;
    }
    mo2[0] = pf3o[6] + pf3o[7] * zzz1;
    if (hfixo2 > ho2[0]) {
	ymo2z = mo2[1];
    } else {
	ymo2z = mo2[0];
    }
    aldo21 = log(rdo2mx) + ymo2z * (ho2[0] - hfixo2);
    hfixo2 = (ho2[1] + ho2[0]) / 2.;
    rdo2mx = exp(aldo21 + mo2[1] * (hfixo2 - ho2[0]));

/* make sure that rd(O2+) is less or equal 100-rd(O+) at O+ maximum */

L7106:
    y = rpid_(&h0o, &hfixo2, &rdo2mx, &c__2, mo2, do2, ho2);
    if (y > yo2h0o) {
	mo2[2] += -.02;
	goto L7106;
    }

/* use ratio of NO+ to O2+ density at O+ maximum to calculate */
/* NO+ density above the O+ maximum (H0O) */

    if (y < 1.) {
	nobo2 = 0.;
    } else {
	nobo2 = (yo2h0o - y) / y;
    }

/* CALCULATION FOR THE REQUIRED HEIGHT RANGE....................... */
/* In the absence of an F1 layer hmf1=hz since hmf1 is used in XE */

L141:
    xhmf1 = block1_1.hmf1;
    if (block1_1.hmf1 <= 0.) {
	block1_1.hmf1 = block3_1.hz;
    }
    height = *heibeg;
    kk = 1;
L300:
    if (noden) {
	goto L330;
    }
    if (height > hnee || height < hnea) {
	goto L330;
    }
    if (layver) {
	elede = -9.;
	if (iiqu < 2) {
	    elede = xen_(&height, &block1_1.hmf2, &block1_1.nmf2, &
		    block4_1.hme, &c__4, hxl, scl, amp);
	}
	outf[kk * 20 + 1] = elede;
	goto L330;
    }
    elede = xe_1__(&height);

/* TTS model option for topside */

    if (blo11_1.itopn == 3 && height >= 400.) {
	igrf_sub__(&lati, &longi, &ryear, &height, &xl1, &icode, &dipl1, &
		babs1);
	if (xl1 > 10.) {
	    xl1 = 10.;
	}
/*              icd=1    ! compute INVDIP */
	dimo = .311653;
	calne_(&c__1, &invdip, &xl1, &dimo, &babs1, &dipl, &hour, &height, &
		daynr, &f107d, &elede);
    }

/* electron density in m-3 in outf(1,*) */

    outf[kk * 20 + 1] = elede;

/* plasma temperatures */

L330:
    if (notem) {
	goto L7108;
    }
    if (height > hte || height < hta) {
	goto L7108;
    }
    tnh = tn_(&height, &blotn_1.texos, &blotn_1.tlbdh, &blotn_1.sigma);
    tih = tnh;
    if (height >= block8_1.hs) {
	tih = ti_(&height);
    }
    teh = elte_(&height);
    if (tih < tnh) {
	tih = tnh;
    }
    if (teh < tih) {
	teh = tih;
    }
    outf[kk * 20 + 2] = tnh;
    outf[kk * 20 + 3] = tih;
    outf[kk * 20 + 4] = teh;

/* ion composition */

L7108:
    if (noion) {
	goto L7118;
    }
    if (height > hnie || height < hnia) {
	goto L7118;
    }
    if (dy) {
	ioncomp_(&ryear, &daynr, &iseamon, &hour, &height, &xhi, &lati, &
		longi, &cov, dion);
	rox = dion[0];
	rhx = dion[1];
	rnx = dion[2];
	rhex = dion[3];
	rnox = dion[4];
	ro2x = dion[5];
	rclust = dion[6];
    } else {
	rox = rpid_(&height, &hfixo, &rdomax, &msumo, mo, ddo, ho);
	ro2x = rpid_(&height, &hfixo2, &rdo2mx, &c__2, mo2, do2, ho2);
	rdhhe_(&height, &h0o, &rox, &ro2x, &nobo2, &c_b159, &rhx, &rhex);
	rnox = rdno_(&height, &h0o, &ro2x, &rox, &nobo2);
	rnx = -1.;
	rclust = -1.;
    }

/* ion densities are given in percent of total electron density; */

    if (jf[22]) {
	xnorm = 1.;
    } else {
	xnorm = elede / 100.;
    }
    outf[kk * 20 + 5] = rox * xnorm;
    outf[kk * 20 + 6] = rhx * xnorm;
    outf[kk * 20 + 7] = rhex * xnorm;
    outf[kk * 20 + 8] = ro2x * xnorm;
    outf[kk * 20 + 9] = rnox * xnorm;
    outf[kk * 20 + 10] = rclust * xnorm;
    outf[kk * 20 + 11] = rnx * xnorm;

/* D region special: Friedrich&Torkar model in outf(13,*) */

L7118:
    if (! dreg) {
	outf[kk * 20 + 13] = -1.;
	f00_(&height, &lati, &daynr, &xhi, &f107d, &edens, &ierror);
	if (ierror == 0) {
	    outf[kk * 20 + 13] = edens;
	}
    }
    height += *heistp;
    ++kk;
    if (kk <= numhei) {
	goto L300;
    }

/* D region special: Danilov et al. model in outf(14,*): */
/* outf(14,1:7)=Ne(h,SW=0,WA=0) h=60,65,70,75,80,85,90 km; */
/* outf(14,8:14)=Ne(h,SW=1,WA=0); outf(14,15:21)=Ne(h,SW=0,WA=1) */

    if (! dreg) {
	for (ii = 1; ii <= 7; ++ii) {
	    outf[ii * 20 + 14] = ddens[ii * 3 - 3];
	    outf[(ii + 7) * 20 + 14] = ddens[ii * 3 - 2];
	    outf[(ii + 14) * 20 + 14] = ddens[ii * 3 - 1];
	}
    }

/* equatorial vertical ion drift */

    drift = -1.;
    if (jf[21] && abs(magbr) < 25.) {
	param[0] = (doublereal) daynr;
	param[1] = f107d;
	vdrift_(&hour, &longi, param, &drift);
    }

/* spread-F occurrence probability */

    spreadf = -1.;
    if (! jf[28]) {
	goto L1937;
    }
    if (hour > 7.25 && hour < 17.75) {
	goto L1937;
    }
    if (abs(lati) > 25.) {
	goto L1937;
    }
    spfhour = hour;
    daynr1 = (doublereal) daynr;
    if (hour < 12.) {
	spfhour = hour + 24.;
	daynr1 = (doublereal) (daynr - 1);
	if (daynr1 < 1.) {
	    daynr1 = (doublereal) idayy;
	}
    }
    spreadf_brazil__(&daynr, &idayy, &f107d, &lati, osfbr);
    ispf = (integer) ((spfhour - 17.75) / .5) + 1;
    if (ispf > 0 && ispf < 26) {
	spreadf = osfbr[ispf - 1];
    }
L1937:

/* ADDITIONAL PARAMETER FIELD OARR */

    if (noden) {
	goto L6192;
    }
    oarr[1] = block1_1.nmf2;
    oarr[2] = block1_1.hmf2;
    if (block1_1.f1reg) {
	oarr[3] = nmf1;
    }
    if (block1_1.f1reg) {
	oarr[4] = xhmf1;
    }
    oarr[5] = block4_1.nme;
    oarr[6] = block4_1.hme;
    oarr[7] = block6_1.nmd;
    oarr[8] = block6_1.hmd;
    oarr[9] = hhalf;
    oarr[10] = block2_1.b0;
    oarr[11] = vner;
    oarr[12] = block4_1.hef;
L6192:
    if (notem) {
	goto L6092;
    }
    oarr[13] = ate[1];
    oarr[14] = blote_1.ahh[1];
    oarr[15] = ate[2];
    oarr[16] = ate[3];
    oarr[17] = ate[4];
    oarr[18] = ate[5];
    oarr[19] = ate[6];
    oarr[20] = ate[0];
    oarr[21] = ti1;
    oarr[22] = xteti;
L6092:
    oarr[23] = xhi;
    oarr[24] = sundec;
    oarr[25] = dip;
    oarr[26] = magbr;
    oarr[27] = modip;
    oarr[28] = dela;
    oarr[29] = sax200;
    oarr[30] = sux200;
    oarr[31] = (doublereal) season;
    oarr[32] = (doublereal) nseasn;
    oarr[33] = rssn;
    oarr[34] = cov;
    oarr[35] = block2_1.b1;
    oarr[36] = xm3000;
    oarr[39] = gind;
    oarr[40] = f1pbo;
    oarr[41] = f107d;
    oarr[42] = block2_1.c1;
    oarr[43] = (doublereal) daynr;
    oarr[44] = drift;
    oarr[45] = stormcorr;
    oarr[46] = f1pbw;
    oarr[47] = f1pbl;
    oarr[48] = spreadf;
L3330:
    return 0;
} /* iri_sub__ */



/* Subroutine */ int iri_web__(jmag, jf, alati, along, iyyyy, mmdd, iut, 
	dhour, height, h_tec_max__, ivar, vbeg, vend, vstp, a, b)
integer *jmag;
logical *jf;
doublereal *alati, *along;
integer *iyyyy, *mmdd, *iut;
doublereal *dhour, *height, *h_tec_max__;
integer *ivar;
doublereal *vbeg, *vend, *vstp, *a, *b;
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    static integer i__, ii, iii;
    static doublereal tec, oar[50], tecb, tect, oarr[50], outf[10000]	/* 
	    was [20][500] */, xvar[8], xhour;
    static integer numstp;
    extern /* Subroutine */ int iri_tec__(), iri_sub__();

/* ----------------------------------------------------------------------- */
/* changes: */
/*       11/16/99 jf(30) instead of jf(17) */

/* ----------------------------------------------------------------------- */
/* input:   jmag,alati,along,iyyyy,mmdd,dhour  see IRI_SUB */
/*          height  height in km */
/*          h_tec_max  =0 no TEC otherwise upper boundary for integral */
/*          iut     =1 for UT       =0 for LT */
/*          ivar    =1      altitude */
/*                  =2,3    latitude,longitude */
/*                  =4,5,6  year,month,day */
/*                  =7      day of year */
/*                  =8      hour (UT or LT) */
/*          vbeg,vend,vstp  variable range (begin,end,step) */
/* output:  a       similar to outf in IRI_SUB */
/*          b       similar to oarr in IRI_SUB */

/*          numstp  number of steps; maximal 500 */
/* ----------------------------------------------------------------------- */
    /* Parameter adjustments */
    b -= 51;
    a -= 21;
    --jf;

    /* Function Body */
    numstp = (integer) ((*vend - *vbeg) / *vstp) + 1;
    if (numstp > 500) {
	numstp = 500;
    }
    for (i__ = 1; i__ <= 50; ++i__) {
/* L6249: */
	oar[i__ - 1] = b[i__ + 50];
    }
    if (*ivar == 1) {
	for (i__ = 1; i__ <= 50; ++i__) {
/* L1249: */
	    oarr[i__ - 1] = oar[i__ - 1];
	}
	xhour = *dhour + *iut * 25.;
	iri_sub__(&jf[1], jmag, alati, along, iyyyy, mmdd, &xhour, vbeg, vend,
		 vstp, &a[21], oarr);
	if (*h_tec_max__ > 50.) {
	    iri_tec__(&c_b242, h_tec_max__, &c__2, &tec, &tect, &tecb);
	    oarr[36] = tec;
	    oarr[37] = tect;
	}
	for (i__ = 1; i__ <= 50; ++i__) {
/* L1111: */
	    b[i__ + 50] = oarr[i__ - 1];
	}
	return 0;
    }
    if (*height <= 0.) {
	*height = 100.;
    }
    xvar[1] = *alati;
    xvar[2] = *along;
    xvar[3] = (doublereal) (*iyyyy);
    xvar[4] = (doublereal) (*mmdd / 100);
    xvar[5] = *mmdd - xvar[4] * 100;
    xvar[6] = (d__1 = *mmdd * 1., abs(d__1));
    xvar[7] = *dhour;
    xvar[*ivar - 1] = *vbeg;
    *alati = xvar[1];
    *along = xvar[2];
    *iyyyy = (integer) xvar[3];
    if (*ivar == 7) {
	*mmdd = -((integer) (*vbeg));
    } else {
	*mmdd = (integer) (xvar[4] * 100 + xvar[5]);
    }
    *dhour = xvar[7] + *iut * 25.;
    i__1 = numstp;
    for (i__ = 1; i__ <= i__1; ++i__) {
	for (iii = 1; iii <= 50; ++iii) {
/* L1349: */
	    oarr[iii - 1] = b[iii + i__ * 50];
	}
	iri_sub__(&jf[1], jmag, alati, along, iyyyy, mmdd, dhour, height, 
		height, &c_b119, outf, oarr);
	if (*h_tec_max__ > 50.) {
	    iri_tec__(&c_b242, h_tec_max__, &c__2, &tec, &tect, &tecb);
	    oarr[36] = tec;
	    oarr[37] = tect;
	}
	for (ii = 1; ii <= 20; ++ii) {
/* L2: */
	    a[ii + i__ * 20] = outf[ii - 1];
	}
	for (ii = 1; ii <= 50; ++ii) {
/* L2222: */
	    b[ii + i__ * 50] = oarr[ii - 1];
	}
	xvar[*ivar - 1] += *vstp;
	*alati = xvar[1];
	*along = xvar[2];
	*iyyyy = (integer) xvar[3];
	if (*ivar == 7) {
	    *mmdd = (integer) (-xvar[6]);
	} else {
	    *mmdd = (integer) (xvar[4] * 100 + xvar[5]);
	}
	*dhour = xvar[7] + *iut * 25.;
/* L1: */
    }
    return 0;
} /* iri_web__ */

