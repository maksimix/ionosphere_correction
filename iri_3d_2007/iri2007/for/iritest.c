/* iritest.f -- translated by f2c (version 20000121).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__3 = 3;
static integer c__5 = 5;
static integer c__8 = 8;

/* iritest.for, version number can be found at the end of this comment. */
/* ----------------------------------------------------------------------- */

/* test program for the iri_web subroutine */

/* corrections */
/* -version-mm/dd/yy------------------------------------------------------ */
/* 2000.01 05/07/01 initial version */
/* 2000.02 07/11/01 line 210: do i=1,100 instead of i=2,100 (K. Tokar) */
/* 2000.03 28/12/01 output oar(39) for IG12 (R. Conkright, NGDC, NOAA) */
/* 2000.04 28/10/02 replace TAB/6 blanks, enforce 72/line (D. Simpson) */
/* 2000.05 02/06/03 Ne(Te) only 300,400; foF1 and hmF1 output corr. */
/* 2000.06 01/19/05 (.not.jf(20)) instead of (..jf(2)) (G. Schiralli) */
/* 2005.01 05/06/06 included spread-F (jf(28)) and topside (jf(29)) options */
/* 2007.00 05/18/07 Release of IRI-2007 */
/* 2007.02 10/31/08 outf(100) -> outf(500), numhei=numstp=500 */

/* Main program */ MAIN__()
{
    /* Initialized data */

    static char imz[4*8+1] = " km GEODGEODyyyy mm  dd YEARL.T.";
    static char itext[5*8+1] = "  H   LATI LONG YEARMONTH DAY DAYOF HOUR";
    static char pna[6*48+1] = "NmF2  hmF2  NmF1  hmF1  NmE   hmE   NmD   hmD\
   h05   B0    NVmin hVtop Tpeak hTpek T300  T400  T600  T1400 T3000 T120  T\
i450 hTeTi sza   sndec dip   dipla modip dela  Srise Sset  seasn nseas Rz12 \
 cov   B1    M3000 TEC   TECtp IG12  F1prb F107d C1    daynr vdrft foF2r F1n\
oL F1+L  sp_F  ";
    static char uni[3*48+1] = "m-3km m-3km m-3km m-3km km km m-3km K  km K  \
K  K  K  K  K  K  km degdegdegdegdeg   h  h                    m-2%         \
        m/s            ";
    static char timev[2*2+1] = "LTUT";
    static char coorv[4*2+1] = "geoggeom";
    static integer jfi[6] = { 8,9,13,14,15,16 };

    /* Format strings */
    static char fmt_3991[] = "(///\002DATE(yyyy/-ddd or mmdd/hh.h):\002,i4\
,\002/\002,i4,\002/\002,f4.1,a2,2x,a4,\002 Lat/Long=\002,f5.1,\002/\002,f6.1\
/)";
    static char fmt_3314[] = "(\002IRI-2001 is used for topside Ne profil\
e\002)";
    static char fmt_3315[] = "(\002TTS model is used for topside Ne profil\
e\002)";
    static char fmt_3316[] = "(\002Corrected IRI01 is used for topside Ne pr\
ofile\002)";
    static char fmt_3317[] = "(\002NeQuick is used for topside Ne profile\
\002)";
    static char fmt_301[] = "(a4,\002 maps are used for the F2 peak density \
(NmF2)\002)";
    static char fmt_303[] = "(\002CCIR maps are used for the F2 peak height \
(hmF2)\002)";
    static char fmt_3081[] = "(\002Special D-region output with all option\
s\002)";
    static char fmt_309[] = "(a8,\002 option is used for the bottomside thic\
kness \002,\002parameter B0\002)";
    static char fmt_3291[] = "(\002The foF2 STORM model is turned \002,a3)";
    static char fmt_3295[] = "(a16,\002 option is used for the F1 occurrence\
 probability\002)";
    static char fmt_302[] = "(a9,\002 provided by user:\002)";
    static char fmt_402[] = "(7(1pe10.3))";
    static char fmt_3292[] = "(a9,\002 option is used for the electron tempe\
rature\002)";
    static char fmt_329[] = "(a10,\002 option is used for ion composition\
\002)";
    static char fmt_213[] = "(/\002Peak Densities/cm-3: NmF2=\002,f9.1,\002 \
  NmF1=\002,f9.1,\002   NmE=\002,f9.1)";
    static char fmt_214[] = "(\002Peak Heights/km:     hmF2=\002,f9.2,\002  \
 hmF1=\002,f9.2,\002   hmE=\002,f9.2/)";
    static char fmt_307[] = "(1x/\002Solar and magnetic parameter for the 1s\
t profile\002,\002 point:\002)";
    static char fmt_211[] = "(\002Solar Zenith Angle/degree\002,28x,f6.1/\
\002Dip (Magnetic Inclination)/degree\002,20x,f6.2/\002Modip (Modified Dip)/\
degree\002,26x,f6.2)";
    static char fmt_223[] = "(\002Solar Sunspot Number (12-months running me\
an) Rz12\002,4x,f5.1,\002{user provided input}\002)";
    static char fmt_212[] = "(\002Solar Sunspot Number (12-months running me\
an) Rz12\002,4x,f5.1)";
    static char fmt_2231[] = "(\002Ionospheric-Effective Solar Index IG12\
\002,16x,f5.1,\002{user provided input}\002)";
    static char fmt_2121[] = "(\002Ionospheric-Effective Solar Index IG12\
\002,16x,f5.1)";
    static char fmt_3914[] = "(/\002TEC [1.E16 m-2] is obtained by numerical\
 integration\002,\002 in 1km steps\002/\002  from 50 to \002,f6.1,\002 km.  \
t is the\002,\002 percentage of TEC above the F peak.\002)";
    static char fmt_3915[] = "(/\002vdrft: equatorial vertical F-region drif\
t.\002)";
    static char fmt_4915[] = "(/\002F1_pb: F1-layer occurrence probabilit\
y\002)";
    static char fmt_4916[] = "(/\002foF2r: foF2_storm/foF2_quiet\002)";
    static char fmt_4196[] = "(/\002sp_F: spread-F occurrence probability\
\002)";
    static char fmt_8199[] = "(/\002-\002/1x,a5,12x,\002 D-REGION ELECTRON D\
ENSITY IN CM-3\002/2x,a4,7x,\002Mechtley\002,3x,\002Friedrich\002,7x,\002Dan\
ilov et al. 1995\002/13x,\002-Bilitza\002,4x,\002-Torkar\002,5x,\002standar\
d\002,2x,\002major SW\002,2x,\002strong WA\002)";
    static char fmt_8194[] = "(/\002-\002/2x,a5,15x,\002E-VALLEY\002,3x,\002\
PLAS FREQ/\002,\002 MHz  \002,a6,3x,a6,3x,a6/3x,a4,\002 M3000 B0/km  W/km De\
pth \002,\002 foF2 foF1  foE   \002,a3,6x,a3,6x,a3)";
    static char fmt_8192[] = "(/\002-\002/2x,a5,6x,\002PEAK ALTITUDES IN K\
M\002,8x,\002PEAK DEN\002,\002SITIES IN cm-3  TEC top/%\002/3x,a4,\002    hm\
F2  hmF1   hmE   \002,\002hmD      NmF2   NmF1    NmE    NmD  1E16m-2\002)";
    static char fmt_8193[] = "(/\002-\002/1x,a5,\002 ELECTRON DENSITY   TEMP\
ERATURES \002,8x,\002ION PERCENTAGES/%\002,5x,\0021E16m-2\002/2x,a4,\002 Ne/\
cm-3 Ne/NmF2\002,\002 Tn/K  Ti/K  Te/K  O+  N+  H+ He+ O2+ NO+ Clust TEC t/\
%\002)";
    static char fmt_3910[] = "(f7.1,2x,4f6.1,1x,i9,3i7,1x,f6.2,i4)";
    static char fmt_3919[] = "(f7.1,2x,f4.2,1x,f5.1,1x,f5.1,1x,f5.3,f6.2,2f5\
.2,1pe9.2,1pe9.2,1pe9.2)";
    static char fmt_3819[] = "(f7.1,2x,2i10,5x,3i10)";
    static char fmt_7117[] = "(f6.1,i8,1x,f6.3,3i6,7i4,f6.1,i4)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsle(), do_lio(), e_wsle(), s_rsle(), e_rsle();
    /* Subroutine */ int s_copy();
    integer s_wsfe(), do_fio(), e_wsfe();
    double sqrt();
    /* Subroutine */ int s_stop();

    /* Local variables */
    static integer jmag, jihe, mmdd, jicl;
    static doublereal vbeg, agnr, vend;
    static integer jino;
    static doublereal hihx;
    static integer ivar, ixne;
    static char bopt[8];
    static doublereal htec_max__, xlat;
    static integer numi;
    static char iopt[10];
    static doublereal xcor, outf[10000]	/* was [20][500] */, hour, xner, xlon;
    static char sopt[3], topt[9], xtex[4];
    static doublereal vstp;
    static char f1opt[16];
    static integer i__, j;
    static char pname[9*6];
    static integer itopp, icontinue;
    static logical jf[30];
    static integer ij, li, jm;
    static doublereal hx;
    static integer iy;
    static doublereal piktab;
    static integer ih1, ih2, ip1, ip2, numstp;
    static doublereal yp1, yp2, yp3;
    static integer imd, jih;
    static doublereal tec;
    static integer jne;
    static char map[4];
    static integer jin;
    static doublereal oar[25000]	/* was [50][500] */;
    static integer jte, jchoice, jio, jti;
    static doublereal var;
    static integer ihx, jtn;
    extern /* Subroutine */ int iri_web__();
    static integer iut;
    static doublereal hxx, f107d;
    static integer pad1, pad2, pad3, jio2, ixn1, num1, ixn2, iyp1, iyp2, iyp3,
	     iyp4;

    /* Fortran I/O blocks */
    static cilist io___8 = { 0, 6, 0, 0, 0 };
    static cilist io___9 = { 0, 5, 0, 0, 0 };
    static cilist io___13 = { 0, 6, 0, 0, 0 };
    static cilist io___14 = { 0, 5, 0, 0, 0 };
    static cilist io___19 = { 0, 6, 0, 0, 0 };
    static cilist io___20 = { 0, 6, 0, 0, 0 };
    static cilist io___21 = { 0, 6, 0, 0, 0 };
    static cilist io___22 = { 0, 6, 0, 0, 0 };
    static cilist io___23 = { 0, 6, 0, 0, 0 };
    static cilist io___24 = { 0, 6, 0, 0, 0 };
    static cilist io___25 = { 0, 5, 0, 0, 0 };
    static cilist io___27 = { 0, 6, 0, 0, 0 };
    static cilist io___28 = { 0, 5, 0, 0, 0 };
    static cilist io___30 = { 0, 6, 0, 0, 0 };
    static cilist io___31 = { 0, 5, 0, 0, 0 };
    static cilist io___33 = { 0, 6, 0, 0, 0 };
    static cilist io___34 = { 0, 5, 0, 0, 0 };
    static cilist io___38 = { 0, 6, 0, 0, 0 };
    static cilist io___39 = { 0, 6, 0, 0, 0 };
    static cilist io___40 = { 0, 6, 0, 0, 0 };
    static cilist io___41 = { 0, 5, 0, 0, 0 };
    static cilist io___45 = { 0, 6, 0, 0, 0 };
    static cilist io___46 = { 0, 5, 0, 0, 0 };
    static cilist io___47 = { 0, 6, 0, 0, 0 };
    static cilist io___48 = { 0, 5, 0, 0, 0 };
    static cilist io___49 = { 0, 6, 0, 0, 0 };
    static cilist io___50 = { 0, 5, 0, 0, 0 };
    static cilist io___51 = { 0, 6, 0, 0, 0 };
    static cilist io___52 = { 0, 5, 0, 0, 0 };
    static cilist io___53 = { 0, 6, 0, 0, 0 };
    static cilist io___54 = { 0, 5, 0, 0, 0 };
    static cilist io___55 = { 0, 6, 0, 0, 0 };
    static cilist io___56 = { 0, 5, 0, 0, 0 };
    static cilist io___57 = { 0, 6, 0, 0, 0 };
    static cilist io___58 = { 0, 5, 0, 0, 0 };
    static cilist io___59 = { 0, 6, 0, 0, 0 };
    static cilist io___60 = { 0, 5, 0, 0, 0 };
    static cilist io___61 = { 0, 6, 0, 0, 0 };
    static cilist io___62 = { 0, 5, 0, 0, 0 };
    static cilist io___63 = { 0, 6, 0, 0, 0 };
    static cilist io___64 = { 0, 5, 0, 0, 0 };
    static cilist io___65 = { 0, 6, 0, 0, 0 };
    static cilist io___66 = { 0, 5, 0, 0, 0 };
    static cilist io___67 = { 0, 6, 0, 0, 0 };
    static cilist io___68 = { 0, 5, 0, 0, 0 };
    static cilist io___69 = { 0, 6, 0, 0, 0 };
    static cilist io___70 = { 0, 5, 0, 0, 0 };
    static cilist io___71 = { 0, 6, 0, 0, 0 };
    static cilist io___72 = { 0, 5, 0, 0, 0 };
    static cilist io___73 = { 0, 6, 0, 0, 0 };
    static cilist io___74 = { 0, 5, 0, 0, 0 };
    static cilist io___75 = { 0, 6, 0, 0, 0 };
    static cilist io___76 = { 0, 5, 0, 0, 0 };
    static cilist io___77 = { 0, 6, 0, 0, 0 };
    static cilist io___78 = { 0, 5, 0, 0, 0 };
    static cilist io___79 = { 0, 6, 0, 0, 0 };
    static cilist io___80 = { 0, 5, 0, 0, 0 };
    static cilist io___81 = { 0, 6, 0, 0, 0 };
    static cilist io___82 = { 0, 5, 0, 0, 0 };
    static cilist io___83 = { 0, 6, 0, 0, 0 };
    static cilist io___84 = { 0, 5, 0, 0, 0 };
    static cilist io___85 = { 0, 6, 0, 0, 0 };
    static cilist io___86 = { 0, 5, 0, 0, 0 };
    static cilist io___87 = { 0, 6, 0, 0, 0 };
    static cilist io___88 = { 0, 5, 0, 0, 0 };
    static cilist io___89 = { 0, 6, 0, 0, 0 };
    static cilist io___90 = { 0, 5, 0, 0, 0 };
    static cilist io___91 = { 0, 6, 0, 0, 0 };
    static cilist io___92 = { 0, 5, 0, 0, 0 };
    static cilist io___93 = { 0, 6, 0, 0, 0 };
    static cilist io___94 = { 0, 5, 0, 0, 0 };
    static cilist io___95 = { 0, 6, 0, 0, 0 };
    static cilist io___96 = { 0, 5, 0, 0, 0 };
    static cilist io___97 = { 0, 6, 0, 0, 0 };
    static cilist io___98 = { 0, 5, 0, 0, 0 };
    static cilist io___99 = { 0, 6, 0, 0, 0 };
    static cilist io___100 = { 0, 5, 0, 0, 0 };
    static cilist io___101 = { 0, 6, 0, 0, 0 };
    static cilist io___102 = { 0, 6, 0, 0, 0 };
    static cilist io___104 = { 0, 6, 0, 0, 0 };
    static cilist io___105 = { 0, 6, 0, 0, 0 };
    static cilist io___106 = { 0, 6, 0, 0, 0 };
    static cilist io___107 = { 0, 6, 0, 0, 0 };
    static cilist io___108 = { 0, 6, 0, 0, 0 };
    static cilist io___109 = { 0, 5, 0, 0, 0 };
    static cilist io___113 = { 0, 6, 0, 0, 0 };
    static cilist io___114 = { 0, 6, 0, 0, 0 };
    static cilist io___115 = { 0, 6, 0, 0, 0 };
    static cilist io___118 = { 0, 6, 0, 0, 0 };
    static cilist io___119 = { 0, 5, 0, 0, 0 };
    static cilist io___122 = { 0, 6, 0, 0, 0 };
    static cilist io___123 = { 0, 5, 0, 0, 0 };
    static cilist io___124 = { 0, 6, 0, 0, 0 };
    static cilist io___125 = { 0, 5, 0, 0, 0 };
    static cilist io___126 = { 0, 6, 0, 0, 0 };
    static cilist io___127 = { 0, 5, 0, 0, 0 };
    static cilist io___128 = { 0, 6, 0, 0, 0 };
    static cilist io___129 = { 0, 5, 0, 0, 0 };
    static cilist io___130 = { 0, 6, 0, 0, 0 };
    static cilist io___131 = { 0, 5, 0, 0, 0 };
    static cilist io___132 = { 0, 6, 0, 0, 0 };
    static cilist io___133 = { 0, 5, 0, 0, 0 };
    static cilist io___134 = { 0, 6, 0, 0, 0 };
    static cilist io___135 = { 0, 5, 0, 0, 0 };
    static cilist io___137 = { 0, 6, 0, 0, 0 };
    static cilist io___138 = { 0, 5, 0, 0, 0 };
    static cilist io___139 = { 0, 6, 0, 0, 0 };
    static cilist io___140 = { 0, 5, 0, 0, 0 };
    static cilist io___152 = { 0, 7, 0, fmt_3991, 0 };
    static cilist io___153 = { 0, 7, 0, fmt_3314, 0 };
    static cilist io___154 = { 0, 7, 0, fmt_3315, 0 };
    static cilist io___155 = { 0, 7, 0, fmt_3316, 0 };
    static cilist io___156 = { 0, 7, 0, fmt_3317, 0 };
    static cilist io___157 = { 0, 7, 0, fmt_301, 0 };
    static cilist io___158 = { 0, 7, 0, fmt_303, 0 };
    static cilist io___159 = { 0, 7, 0, fmt_3081, 0 };
    static cilist io___160 = { 0, 7, 0, fmt_309, 0 };
    static cilist io___161 = { 0, 7, 0, fmt_3291, 0 };
    static cilist io___162 = { 0, 7, 0, fmt_3295, 0 };
    static cilist io___165 = { 0, 7, 0, fmt_302, 0 };
    static cilist io___166 = { 0, 7, 0, fmt_402, 0 };
    static cilist io___167 = { 0, 7, 0, fmt_3292, 0 };
    static cilist io___168 = { 0, 7, 0, fmt_329, 0 };
    static cilist io___170 = { 0, 7, 0, fmt_213, 0 };
    static cilist io___171 = { 0, 7, 0, fmt_214, 0 };
    static cilist io___172 = { 0, 7, 0, fmt_307, 0 };
    static cilist io___173 = { 0, 7, 0, fmt_211, 0 };
    static cilist io___174 = { 0, 7, 0, fmt_223, 0 };
    static cilist io___175 = { 0, 7, 0, fmt_212, 0 };
    static cilist io___176 = { 0, 7, 0, fmt_2231, 0 };
    static cilist io___177 = { 0, 7, 0, fmt_2121, 0 };
    static cilist io___178 = { 0, 7, 0, fmt_3914, 0 };
    static cilist io___179 = { 0, 7, 0, fmt_3915, 0 };
    static cilist io___180 = { 0, 7, 0, fmt_4915, 0 };
    static cilist io___181 = { 0, 7, 0, fmt_4916, 0 };
    static cilist io___182 = { 0, 7, 0, fmt_4196, 0 };
    static cilist io___186 = { 0, 7, 0, fmt_8199, 0 };
    static cilist io___187 = { 0, 7, 0, fmt_8194, 0 };
    static cilist io___188 = { 0, 7, 0, fmt_8192, 0 };
    static cilist io___189 = { 0, 7, 0, fmt_8193, 0 };
    static cilist io___198 = { 0, 7, 0, fmt_3910, 0 };
    static cilist io___201 = { 0, 7, 0, fmt_3919, 0 };
    static cilist io___211 = { 0, 7, 0, fmt_3819, 0 };
    static cilist io___224 = { 0, 7, 0, fmt_7117, 0 };
    static cilist io___225 = { 0, 6, 0, 0, 0 };
    static cilist io___226 = { 0, 5, 0, 0, 0 };


/* user input of IRI input parameters */

L1:
    s_wsle(&io___8);
    do_lio(&c__9, &c__1, "jmag(=0/1,geog/geom),lati/deg,long/deg", (ftnlen)38)
	    ;
    e_wsle();
    s_rsle(&io___9);
    do_lio(&c__3, &c__1, (char *)&jm, (ftnlen)sizeof(integer));
    do_lio(&c__5, &c__1, (char *)&xlat, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&xlon, (ftnlen)sizeof(doublereal));
    e_rsle();
    s_wsle(&io___13);
    do_lio(&c__9, &c__1, "year(yyyy),mmdd(or -ddd),iut(=0/1,LT/UT),hour", (
	    ftnlen)45);
    e_wsle();
    s_rsle(&io___14);
    do_lio(&c__3, &c__1, (char *)&iy, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&imd, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&iut, (ftnlen)sizeof(integer));
    do_lio(&c__5, &c__1, (char *)&hour, (ftnlen)sizeof(doublereal));
    e_rsle();
    s_wsle(&io___19);
    do_lio(&c__9, &c__1, "height/km", (ftnlen)9);
    e_wsle();
    s_wsle(&io___20);
    do_lio(&c__9, &c__1, "(enter  0 for list of peak heights and densities)", 
	    (ftnlen)49);
    e_wsle();
    s_wsle(&io___21);
    do_lio(&c__9, &c__1, "(enter -1 for plasma frequencies, B0, M3000, ", (
	    ftnlen)45);
    do_lio(&c__9, &c__1, "valley, width and depth,)", (ftnlen)25);
    e_wsle();
    s_wsle(&io___22);
    do_lio(&c__9, &c__1, "(enter -2 for F1 probability, equatorial vertical ",
	     (ftnlen)50);
    do_lio(&c__9, &c__1, "ion drift, and)", (ftnlen)15);
    e_wsle();
    s_wsle(&io___23);
    do_lio(&c__9, &c__1, "(         foF2 storm/quiet ratio,)", (ftnlen)34);
    e_wsle();
    s_wsle(&io___24);
    do_lio(&c__9, &c__1, "(         or 3 parameter of your choice)", (ftnlen)
	    40);
    e_wsle();
    s_rsle(&io___25);
    do_lio(&c__5, &c__1, (char *)&hx, (ftnlen)sizeof(doublereal));
    e_rsle();
    s_wsle(&io___27);
    do_lio(&c__9, &c__1, "upper height [km] for TEC integration (0 for no TE\
C)", (ftnlen)52);
    e_wsle();
    s_rsle(&io___28);
    do_lio(&c__5, &c__1, (char *)&htec_max__, (ftnlen)sizeof(doublereal));
    e_rsle();
    s_wsle(&io___30);
    do_lio(&c__9, &c__1, "variable? (1/2/../8 for height/lat/long/year/month/"
	    , (ftnlen)51);
    do_lio(&c__9, &c__1, "day/day of year/hour)", (ftnlen)21);
    e_wsle();
    s_rsle(&io___31);
    do_lio(&c__3, &c__1, (char *)&ivar, (ftnlen)sizeof(integer));
    e_rsle();
    s_wsle(&io___33);
    do_lio(&c__9, &c__1, "begin, end, and stepsize for the selected variable",
	     (ftnlen)50);
    e_wsle();
    s_rsle(&io___34);
    do_lio(&c__5, &c__1, (char *)&vbeg, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&vend, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&vstp, (ftnlen)sizeof(doublereal));
    e_rsle();
    s_wsle(&io___38);
    do_lio(&c__9, &c__1, "Options: t(rue) or f(alse)", (ftnlen)26);
    e_wsle();
    s_wsle(&io___39);
    do_lio(&c__9, &c__1, "Standard: t,t,t,t,f,f,t,t,t,t,t,t,t,t,t,t,t,t,t,t,",
	     (ftnlen)50);
    do_lio(&c__9, &c__1, "f,t,f,t,t,t,t,f,f,f", (ftnlen)19);
    e_wsle();
    s_wsle(&io___40);
    do_lio(&c__9, &c__1, "Enter 0 to use standard or 1 to enter your own", (
	    ftnlen)46);
    e_wsle();
    s_rsle(&io___41);
    do_lio(&c__3, &c__1, (char *)&jchoice, (ftnlen)sizeof(integer));
    e_rsle();
    for (i__ = 1; i__ <= 30; ++i__) {
	jf[i__ - 1] = TRUE_;
    }
    if (jchoice == 0) {
/*          jf(2)=.false.				  ! no temperatures */
/*          jf(3)=.false.				  ! no ion composition */
	jf[4] = FALSE_;
/* URSI foF2 model */
	jf[5] = FALSE_;
/* Newest ion composition model */
	jf[20] = FALSE_;
/* no ion drift */
	jf[22] = FALSE_;
/* TTS Te model is standard */
	jf[27] = FALSE_;
/* no spread-F */
	jf[28] = FALSE_;
/* New Topside options */
	jf[29] = FALSE_;
/* NeQuick topside */
    } else {
	s_wsle(&io___45);
	do_lio(&c__9, &c__1, "Compute Ne, T, Ni? (enter: t,t,t  if you want \
all)", (ftnlen)50);
	e_wsle();
	s_rsle(&io___46);
	do_lio(&c__8, &c__1, (char *)&jf[0], (ftnlen)sizeof(logical));
	do_lio(&c__8, &c__1, (char *)&jf[1], (ftnlen)sizeof(logical));
	do_lio(&c__8, &c__1, (char *)&jf[2], (ftnlen)sizeof(logical));
	e_rsle();
	if (jf[0]) {
	    s_wsle(&io___47);
	    do_lio(&c__9, &c__1, "LAY version: t=standard ver., f=LAY versio\
n. {t}", (ftnlen)48);
	    e_wsle();
	    s_rsle(&io___48);
	    do_lio(&c__8, &c__1, (char *)&jf[10], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___49);
	    do_lio(&c__9, &c__1, "Ne Topside: t=IRI-2001, f=new options {t}", 
		    (ftnlen)41);
	    e_wsle();
	    s_rsle(&io___50);
	    do_lio(&c__8, &c__1, (char *)&jf[28], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___51);
	    do_lio(&c__9, &c__1, "Ne Topside: t=IRI01_corrt, f=NeQuick {t}", (
		    ftnlen)40);
	    e_wsle();
	    s_rsle(&io___52);
	    do_lio(&c__8, &c__1, (char *)&jf[29], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___53);
	    do_lio(&c__9, &c__1, "Ne Topside: t=F10.7<188, f=unlimited {t}", (
		    ftnlen)40);
	    e_wsle();
	    s_rsle(&io___54);
	    do_lio(&c__8, &c__1, (char *)&jf[6], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___55);
	    do_lio(&c__9, &c__1, "foF2 model: t=CCIR, f=URSI-88 {standard:f}",
		     (ftnlen)42);
	    e_wsle();
	    s_rsle(&io___56);
	    do_lio(&c__8, &c__1, (char *)&jf[4], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___57);
	    do_lio(&c__9, &c__1, "foF2: t=with storm model, f=without {t}", (
		    ftnlen)39);
	    e_wsle();
	    s_rsle(&io___58);
	    do_lio(&c__8, &c__1, (char *)&jf[25], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___59);
	    do_lio(&c__9, &c__1, "F2 peak density or foF2: t=model, ", (
		    ftnlen)34);
	    do_lio(&c__9, &c__1, "f=user input {t}", (ftnlen)16);
	    e_wsle();
	    s_rsle(&io___60);
	    do_lio(&c__8, &c__1, (char *)&jf[7], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___61);
	    do_lio(&c__9, &c__1, "F2 peak height or M3000F2: t=model, ", (
		    ftnlen)36);
	    do_lio(&c__9, &c__1, "f=user input {t}", (ftnlen)16);
	    e_wsle();
	    s_rsle(&io___62);
	    do_lio(&c__8, &c__1, (char *)&jf[8], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___63);
	    do_lio(&c__9, &c__1, "Bottomside thickness B0: t=Table-option, ", 
		    (ftnlen)41);
	    do_lio(&c__9, &c__1, "f=Gulyaeva {t}.", (ftnlen)15);
	    e_wsle();
	    s_rsle(&io___64);
	    do_lio(&c__8, &c__1, (char *)&jf[3], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___65);
	    do_lio(&c__9, &c__1, "F1 peak density or foF1: t=model, ", (
		    ftnlen)34);
	    do_lio(&c__9, &c__1, "f=user input {t}", (ftnlen)16);
	    e_wsle();
	    s_rsle(&io___66);
	    do_lio(&c__8, &c__1, (char *)&jf[12], (ftnlen)sizeof(logical));
	    e_rsle();
	    if (! jf[10]) {
		s_wsle(&io___67);
		do_lio(&c__9, &c__1, "F1 peak height: t=model, f=user input \
{t}", (ftnlen)41);
		e_wsle();
		s_rsle(&io___68);
		do_lio(&c__8, &c__1, (char *)&jf[13], (ftnlen)sizeof(logical))
			;
		e_rsle();
	    }
	    s_wsle(&io___69);
	    do_lio(&c__9, &c__1, "F1: t=with probability model, f=without   \
{t}", (ftnlen)45);
	    e_wsle();
	    s_rsle(&io___70);
	    do_lio(&c__8, &c__1, (char *)&jf[18], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___71);
	    do_lio(&c__9, &c__1, "F1: t=standard probability, f=with L ", (
		    ftnlen)37);
	    do_lio(&c__9, &c__1, "condition {t}", (ftnlen)13);
	    e_wsle();
	    s_rsle(&io___72);
	    do_lio(&c__8, &c__1, (char *)&jf[19], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___73);
	    do_lio(&c__9, &c__1, "E peak density or foE: t=model, f=user inp\
ut {t}", (ftnlen)48);
	    e_wsle();
	    s_rsle(&io___74);
	    do_lio(&c__8, &c__1, (char *)&jf[14], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___75);
	    do_lio(&c__9, &c__1, "E peak height: t=model, f=user input {t}", (
		    ftnlen)40);
	    e_wsle();
	    s_rsle(&io___76);
	    do_lio(&c__8, &c__1, (char *)&jf[15], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___77);
	    do_lio(&c__9, &c__1, "D: t=old model, f=new options {t}", (ftnlen)
		    33);
	    e_wsle();
	    s_rsle(&io___78);
	    do_lio(&c__8, &c__1, (char *)&jf[23], (ftnlen)sizeof(logical));
	    e_rsle();
	}
	if (jf[1]) {
	    s_wsle(&io___79);
	    do_lio(&c__9, &c__1, "Te(Ne) model: t=not used, f=correlation is",
		     (ftnlen)42);
	    do_lio(&c__9, &c__1, " used. {t}", (ftnlen)10);
	    e_wsle();
	    s_rsle(&io___80);
	    do_lio(&c__8, &c__1, (char *)&jf[9], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___81);
	    do_lio(&c__9, &c__1, "Te: t=AEROS/ISIS model, f=InterKosmos mode\
l {f}", (ftnlen)47);
	    e_wsle();
	    s_rsle(&io___82);
	    do_lio(&c__8, &c__1, (char *)&jf[22], (ftnlen)sizeof(logical));
	    e_rsle();
	}
	if (jf[2]) {
	    s_wsle(&io___83);
	    do_lio(&c__9, &c__1, "Ion comp. model: t=DS78/DY85, f=DS95/TTS05\
 {f}", (ftnlen)46);
	    e_wsle();
	    s_rsle(&io___84);
	    do_lio(&c__8, &c__1, (char *)&jf[5], (ftnlen)sizeof(logical));
	    e_rsle();
	    s_wsle(&io___85);
	    do_lio(&c__9, &c__1, "Ni: t=ion composition in %, f=ion densities"
		    , (ftnlen)43);
	    do_lio(&c__9, &c__1, "in cm-3 {t}", (ftnlen)11);
	    e_wsle();
	    s_rsle(&io___86);
	    do_lio(&c__8, &c__1, (char *)&jf[21], (ftnlen)sizeof(logical));
	    e_rsle();
	}
	s_wsle(&io___87);
	do_lio(&c__9, &c__1, "Equat. Vert. Ion Drift: t=computed, ", (ftnlen)
		36);
	do_lio(&c__9, &c__1, "f=not computed {t}", (ftnlen)18);
	e_wsle();
	s_rsle(&io___88);
	do_lio(&c__8, &c__1, (char *)&jf[20], (ftnlen)sizeof(logical));
	e_rsle();
	s_wsle(&io___89);
	do_lio(&c__9, &c__1, "Spread-F probability: t=computed, ", (ftnlen)34)
		;
	do_lio(&c__9, &c__1, "f=not computed {t}", (ftnlen)18);
	e_wsle();
	s_rsle(&io___90);
	do_lio(&c__8, &c__1, (char *)&jf[27], (ftnlen)sizeof(logical));
	e_rsle();
	s_wsle(&io___91);
	do_lio(&c__9, &c__1, "Sunspot index: t=from file, f=user input.  {t}",
		 (ftnlen)46);
	e_wsle();
	s_rsle(&io___92);
	do_lio(&c__8, &c__1, (char *)&jf[16], (ftnlen)sizeof(logical));
	e_rsle();
	s_wsle(&io___93);
	do_lio(&c__9, &c__1, "Ionospheric index: t=from file, f=user input. \
{t}", (ftnlen)49);
	e_wsle();
	s_rsle(&io___94);
	do_lio(&c__8, &c__1, (char *)&jf[26], (ftnlen)sizeof(logical));
	e_rsle();
	s_wsle(&io___95);
	do_lio(&c__9, &c__1, "F10.7D Index: t=from file, f=user input {t}", (
		ftnlen)43);
	e_wsle();
	s_rsle(&io___96);
	do_lio(&c__8, &c__1, (char *)&jf[24], (ftnlen)sizeof(logical));
	e_rsle();
	s_wsle(&io___97);
	do_lio(&c__9, &c__1, "UT/LT computation: t=no date change, f=ut_lt ", 
		(ftnlen)45);
	do_lio(&c__9, &c__1, "subroutine {t}", (ftnlen)14);
	e_wsle();
	s_rsle(&io___98);
	do_lio(&c__8, &c__1, (char *)&jf[17], (ftnlen)sizeof(logical));
	e_rsle();
	s_wsle(&io___99);
	do_lio(&c__9, &c__1, "Message output unit: t=(UNIT=6), f=(UNIT=12). \
{t}", (ftnlen)49);
	e_wsle();
	s_rsle(&io___100);
	do_lio(&c__8, &c__1, (char *)&jf[11], (ftnlen)sizeof(logical));
	e_rsle();
    }
/* option to enter three additional parameters */

    if (hx < 0.) {
	s_wsle(&io___101);
	do_lio(&c__9, &c__1, "Three additional output parameters (number:1-4\
8)", (ftnlen)48);
	e_wsle();
	s_wsle(&io___102);
	for (j = 1; j <= 10; ++j) {
	    do_lio(&c__9, &c__1, pna + (j - 1) * 6, (ftnlen)6);
	}
	e_wsle();
	s_wsle(&io___104);
	for (j = 11; j <= 20; ++j) {
	    do_lio(&c__9, &c__1, pna + (j - 1) * 6, (ftnlen)6);
	}
	e_wsle();
	s_wsle(&io___105);
	for (j = 21; j <= 30; ++j) {
	    do_lio(&c__9, &c__1, pna + (j - 1) * 6, (ftnlen)6);
	}
	e_wsle();
	s_wsle(&io___106);
	for (j = 31; j <= 40; ++j) {
	    do_lio(&c__9, &c__1, pna + (j - 1) * 6, (ftnlen)6);
	}
	e_wsle();
	s_wsle(&io___107);
	for (j = 41; j <= 48; ++j) {
	    do_lio(&c__9, &c__1, pna + (j - 1) * 6, (ftnlen)6);
	}
	e_wsle();
	s_wsle(&io___108);
	do_lio(&c__9, &c__1, "or 0,0,0 for default (F1 probability[40], equ.\
 vert. ", (ftnlen)53);
	do_lio(&c__9, &c__1, "ion drift[44], foF2_st/_quiet[45])", (ftnlen)34)
		;
	e_wsle();
	s_rsle(&io___109);
	do_lio(&c__3, &c__1, (char *)&pad1, (ftnlen)sizeof(integer));
	do_lio(&c__3, &c__1, (char *)&pad2, (ftnlen)sizeof(integer));
	do_lio(&c__3, &c__1, (char *)&pad3, (ftnlen)sizeof(integer));
	e_rsle();
	if (pad1 == 0) {
	    pad1 = 40;
	}
/* F1 probability */
	if (pad2 == 0) {
	    pad2 = 44;
/* equatorial vertical ion drift */
	    jf[20] = TRUE_;
	}
	if (pad3 == 0) {
	    pad3 = 45;
	}
/* fof2_storm/foF2_quiet */
    }
/* option to enter measured values for NmF2, hmF2, NmF1, hmF1, NmE, hmE, */
/* N(300), N(400), N(600) if available; */

    s_wsle(&io___113);
    do_lio(&c__9, &c__1, " ", (ftnlen)1);
    e_wsle();
    s_wsle(&io___114);
    do_lio(&c__9, &c__1, " ", (ftnlen)1);
    e_wsle();
    s_wsle(&io___115);
    do_lio(&c__9, &c__1, " ", (ftnlen)1);
    e_wsle();
    numstp = (integer) ((vend - vbeg) / vstp) + 1;
    if (ivar == 1) {
	numstp = 1;
    }
    if (jf[0]) {
	if (! jf[7] || ! jf[8] || ! jf[12] || ! jf[13] || ! jf[14] || ! jf[15]
		) {
	    var = vbeg;
	    i__ = 1;
L2234:
	    if (! jf[7]) {
		jf[25] = FALSE_;
/* storm model off, if user input */
		s_wsle(&io___118);
		do_lio(&c__9, &c__1, "foF2/Mhz or NmF2/m-3 for ", (ftnlen)25);
		do_lio(&c__9, &c__1, itext + (ivar - 1) * 5, (ftnlen)5);
		do_lio(&c__9, &c__1, "=", (ftnlen)1);
		do_lio(&c__5, &c__1, (char *)&var, (ftnlen)sizeof(doublereal))
			;
		e_wsle();
		s_rsle(&io___119);
		do_lio(&c__5, &c__1, (char *)&oar[i__ * 50 - 50], (ftnlen)
			sizeof(doublereal));
		e_rsle();
		s_copy(pname, "foF2/MHz", (ftnlen)9, (ftnlen)8);
		if (oar[i__ * 50 - 50] > 30.) {
		    s_copy(pname, "NmF2/m-3", (ftnlen)9, (ftnlen)8);
		}
	    }
	    if (! jf[8]) {
		s_wsle(&io___122);
		do_lio(&c__9, &c__1, "hmF2/km or M3000F2 for ", (ftnlen)23);
		do_lio(&c__9, &c__1, itext + (ivar - 1) * 5, (ftnlen)5);
		do_lio(&c__9, &c__1, "=", (ftnlen)1);
		do_lio(&c__5, &c__1, (char *)&var, (ftnlen)sizeof(doublereal))
			;
		e_wsle();
		s_rsle(&io___123);
		do_lio(&c__5, &c__1, (char *)&oar[i__ * 50 - 49], (ftnlen)
			sizeof(doublereal));
		e_rsle();
		s_copy(pname + 9, "M(3000)F2", (ftnlen)9, (ftnlen)9);
		if (oar[i__ * 50 - 49] > 50.) {
		    s_copy(pname + 9, "hmF2/km", (ftnlen)9, (ftnlen)7);
		}
	    }
	    if (! jf[12]) {
		s_wsle(&io___124);
		do_lio(&c__9, &c__1, "foF1/MHz or NmF1/m-3 for ", (ftnlen)25);
		do_lio(&c__9, &c__1, itext + (ivar - 1) * 5, (ftnlen)5);
		do_lio(&c__9, &c__1, "=", (ftnlen)1);
		do_lio(&c__5, &c__1, (char *)&var, (ftnlen)sizeof(doublereal))
			;
		e_wsle();
		s_rsle(&io___125);
		do_lio(&c__5, &c__1, (char *)&oar[i__ * 50 - 48], (ftnlen)
			sizeof(doublereal));
		e_rsle();
		s_copy(pname + 18, "foF1/MHz", (ftnlen)9, (ftnlen)8);
		if (oar[i__ * 50 - 48] > 30.) {
		    s_copy(pname + 18, "NmF1/m-3", (ftnlen)9, (ftnlen)8);
		}
	    }
	    if (! jf[13]) {
		s_wsle(&io___126);
		do_lio(&c__9, &c__1, "hmF1/km for ", (ftnlen)12);
		do_lio(&c__9, &c__1, itext + (ivar - 1) * 5, (ftnlen)5);
		do_lio(&c__9, &c__1, "=", (ftnlen)1);
		do_lio(&c__5, &c__1, (char *)&var, (ftnlen)sizeof(doublereal))
			;
		e_wsle();
		s_rsle(&io___127);
		do_lio(&c__5, &c__1, (char *)&oar[i__ * 50 - 47], (ftnlen)
			sizeof(doublereal));
		e_rsle();
		s_copy(pname + 27, "hmF1/km", (ftnlen)9, (ftnlen)7);
	    }
	    if (! jf[14]) {
		s_wsle(&io___128);
		do_lio(&c__9, &c__1, "foE/MHz or NmE/m-3 for ", (ftnlen)23);
		do_lio(&c__9, &c__1, itext + (ivar - 1) * 5, (ftnlen)5);
		do_lio(&c__9, &c__1, "=", (ftnlen)1);
		do_lio(&c__5, &c__1, (char *)&var, (ftnlen)sizeof(doublereal))
			;
		e_wsle();
		s_rsle(&io___129);
		do_lio(&c__5, &c__1, (char *)&oar[i__ * 50 - 46], (ftnlen)
			sizeof(doublereal));
		e_rsle();
		s_copy(pname + 36, "foE/MHz", (ftnlen)9, (ftnlen)7);
		if (oar[i__ * 50 - 46] > 30.) {
		    s_copy(pname + 36, "NmE/m-3", (ftnlen)9, (ftnlen)7);
		}
	    }
	    if (! jf[15]) {
		s_wsle(&io___130);
		do_lio(&c__9, &c__1, "hmE/km for ", (ftnlen)11);
		do_lio(&c__9, &c__1, itext + (ivar - 1) * 5, (ftnlen)5);
		do_lio(&c__9, &c__1, "=", (ftnlen)1);
		do_lio(&c__5, &c__1, (char *)&var, (ftnlen)sizeof(doublereal))
			;
		e_wsle();
		s_rsle(&io___131);
		do_lio(&c__5, &c__1, (char *)&oar[i__ * 50 - 45], (ftnlen)
			sizeof(doublereal));
		e_rsle();
		s_copy(pname + 45, "hmE/km", (ftnlen)9, (ftnlen)6);
	    }
	    ++i__;
	    var += vstp;
	    if (ivar > 1 && var <= vend) {
		goto L2234;
	    }
	}
    }
/* option to enter Ne for Te-Ne relationship */

    if (jf[1] && ! jf[9]) {
	var = vbeg;
	i__1 = numstp;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    s_wsle(&io___132);
	    do_lio(&c__9, &c__1, "Ne(300km),Ne(400km)/m-3", (ftnlen)23);
	    do_lio(&c__9, &c__1, " for ", (ftnlen)5);
	    do_lio(&c__9, &c__1, itext + (ivar - 1) * 5, (ftnlen)5);
	    do_lio(&c__9, &c__1, "=", (ftnlen)1);
	    do_lio(&c__5, &c__1, (char *)&var, (ftnlen)sizeof(doublereal));
	    do_lio(&c__9, &c__1, " [-1 if not]", (ftnlen)12);
	    e_wsle();
	    s_rsle(&io___133);
	    do_lio(&c__5, &c__1, (char *)&oar[i__ * 50 - 36], (ftnlen)sizeof(
		    doublereal));
	    do_lio(&c__5, &c__1, (char *)&oar[i__ * 50 - 35], (ftnlen)sizeof(
		    doublereal));
	    e_rsle();
/* L1235: */
	    var += vstp;
	}
    }
/* option to enter F107D */

    if (! jf[24]) {
	s_wsle(&io___134);
	do_lio(&c__9, &c__1, "User input for F107D:", (ftnlen)21);
	e_wsle();
	s_rsle(&io___135);
	do_lio(&c__5, &c__1, (char *)&f107d, (ftnlen)sizeof(doublereal));
	e_rsle();
	for (i__ = 1; i__ <= 100; ++i__) {
	    oar[i__ * 50 - 10] = f107d;
	}
    }
/* option to enter Rz12 and/or IG12 */

    if (! jf[16]) {
	s_wsle(&io___137);
	do_lio(&c__9, &c__1, "User input for Rz12", (ftnlen)19);
	e_wsle();
	s_rsle(&io___138);
	do_lio(&c__5, &c__1, (char *)&oar[32], (ftnlen)sizeof(doublereal));
	e_rsle();
	for (i__ = 2; i__ <= 100; ++i__) {
	    oar[i__ * 50 - 18] = oar[32];
	}
    }
    if (! jf[26]) {
	s_wsle(&io___139);
	do_lio(&c__9, &c__1, "User input for IG12", (ftnlen)19);
	e_wsle();
	s_rsle(&io___140);
	do_lio(&c__5, &c__1, (char *)&oar[38], (ftnlen)sizeof(doublereal));
	e_rsle();
	for (i__ = 2; i__ <= 100; ++i__) {
	    oar[i__ * 50 - 12] = oar[38];
	}
    }
/* end of user input */

    num1 = (integer) ((vend - vbeg) / vstp + 1);
    numstp = abs(num1);
    if (numstp > 500) {
	numstp = 500;
    }
    s_copy(map, "URSI", (ftnlen)4, (ftnlen)4);
    if (jf[4]) {
	s_copy(map, "CCIR", (ftnlen)4, (ftnlen)4);
    }
    s_copy(bopt, "Gulyaeva", (ftnlen)8, (ftnlen)8);
    if (jf[3]) {
	s_copy(bopt, "B0-Table", (ftnlen)8, (ftnlen)8);
    }
    s_copy(iopt, "DS95&TTS04", (ftnlen)10, (ftnlen)10);
    if (jf[5]) {
	s_copy(iopt, "DS78&DY85 ", (ftnlen)10, (ftnlen)10);
    }
    s_copy(sopt, "off", (ftnlen)3, (ftnlen)3);
    if (jf[25]) {
	s_copy(sopt, "on ", (ftnlen)3, (ftnlen)3);
    }
    s_copy(topt, "TTSA-2000", (ftnlen)9, (ftnlen)9);
    if (jf[22]) {
	s_copy(topt, "IRI-95", (ftnlen)9, (ftnlen)6);
    }
    if (jf[18]) {
	s_copy(f1opt, "Scotto-97 no L", (ftnlen)16, (ftnlen)14);
	if (! jf[19]) {
	    s_copy(f1opt, "Scotto-97 with L", (ftnlen)16, (ftnlen)16);
	}
    } else {
	s_copy(f1opt, "IRI-95", (ftnlen)16, (ftnlen)6);
    }
    hxx = hx;
    jmag = jm;
    mmdd = imd;
/* calling IRI subroutine */

    iri_web__(&jmag, jf, &xlat, &xlon, &iy, &mmdd, &iut, &hour, &hxx, &
	    htec_max__, &ivar, &vbeg, &vend, &vstp, outf, oar);
/* preparation of results page */

    s_wsfe(&io___152);
    do_fio(&c__1, (char *)&iy, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&mmdd, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&hour, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, timev + (iut << 1), (ftnlen)2);
    do_fio(&c__1, coorv + (jmag << 2), (ftnlen)4);
    do_fio(&c__1, (char *)&xlat, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&xlon, (ftnlen)sizeof(doublereal));
    e_wsfe();
    if (jf[0]) {
	if (jf[28]) {
	    if (jf[29]) {
		s_wsfe(&io___153);
		e_wsfe();
	    } else {
		s_wsfe(&io___154);
		e_wsfe();
	    }
	} else {
	    if (jf[29]) {
		s_wsfe(&io___155);
		e_wsfe();
	    } else {
		s_wsfe(&io___156);
		e_wsfe();
	    }
	}
	if (jf[7]) {
	    s_wsfe(&io___157);
	    do_fio(&c__1, map, (ftnlen)4);
	    e_wsfe();
	}
	if (jf[8]) {
	    s_wsfe(&io___158);
	    e_wsfe();
	}
	if (! jf[23]) {
	    s_wsfe(&io___159);
	    e_wsfe();
	}
	s_wsfe(&io___160);
	do_fio(&c__1, bopt, (ftnlen)8);
	e_wsfe();
	s_wsfe(&io___161);
	do_fio(&c__1, sopt, (ftnlen)3);
	e_wsfe();
	s_wsfe(&io___162);
	do_fio(&c__1, f1opt, (ftnlen)16);
	e_wsfe();
	numi = numstp;
	if (ivar == 1) {
	    numi = 1;
	}
	for (j = 1; j <= 6; ++j) {
	    ij = jfi[j - 1];
	    if (! jf[ij - 1]) {
		s_wsfe(&io___165);
		do_fio(&c__1, pname + (j - 1) * 9, (ftnlen)9);
		e_wsfe();
		s_wsfe(&io___166);
		i__1 = numi;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    do_fio(&c__1, (char *)&oar[j + i__ * 50 - 51], (ftnlen)
			    sizeof(doublereal));
		}
		e_wsfe();
	    }
	}
    }
    if (jf[1]) {
	s_wsfe(&io___167);
	do_fio(&c__1, topt, (ftnlen)9);
	e_wsfe();
    }
    if (jf[2]) {
	s_wsfe(&io___168);
	do_fio(&c__1, iopt, (ftnlen)10);
	e_wsfe();
    }
    if (ivar == 1) {
	if (oar[2] < 1.) {
	    oar[3] = 0.;
	}
	yp2 = 0.;
	if (oar[2] > 0.) {
	    yp2 = oar[2] / 1e6;
	}
	s_wsfe(&io___170);
	d__1 = oar[0] / 1e6;
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&yp2, (ftnlen)sizeof(doublereal));
	d__2 = oar[4] / 1e6;
	do_fio(&c__1, (char *)&d__2, (ftnlen)sizeof(doublereal));
	e_wsfe();
	s_wsfe(&io___171);
	do_fio(&c__1, (char *)&oar[1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&oar[3], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&oar[5], (ftnlen)sizeof(doublereal));
	e_wsfe();
    } else {
	s_wsfe(&io___172);
	e_wsfe();
    }
    s_wsfe(&io___173);
    do_fio(&c__1, (char *)&oar[22], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&oar[24], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&oar[26], (ftnlen)sizeof(doublereal));
    e_wsfe();
    if (! jf[16]) {
	s_wsfe(&io___174);
	do_fio(&c__1, (char *)&oar[32], (ftnlen)sizeof(doublereal));
	e_wsfe();
    } else {
	s_wsfe(&io___175);
	do_fio(&c__1, (char *)&oar[32], (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    if (! jf[26]) {
	s_wsfe(&io___176);
	do_fio(&c__1, (char *)&oar[38], (ftnlen)sizeof(doublereal));
	e_wsfe();
    } else {
	s_wsfe(&io___177);
	do_fio(&c__1, (char *)&oar[38], (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    if (htec_max__ > 50.) {
	s_wsfe(&io___178);
	do_fio(&c__1, (char *)&htec_max__, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    if (pad1 == 44 || pad2 == 44 || pad3 == 44) {
	s_wsfe(&io___179);
	e_wsfe();
    }
    if (pad1 == 40 || pad2 == 40 || pad3 == 40) {
	s_wsfe(&io___180);
	e_wsfe();
    }
    if (pad1 == 45 || pad2 == 45 || pad3 == 45) {
	s_wsfe(&io___181);
	e_wsfe();
    }
    if (pad1 == 48 || pad2 == 48 || pad3 == 48) {
	s_wsfe(&io___182);
	e_wsfe();
    }
/* L3916: */
/* L304: */
/* L3293: */

/* table head ....................................................... */

    agnr = 7.;
/* output unit number */
    s_copy(xtex, imz + (ivar - 1 << 2), (ftnlen)4, (ftnlen)4);
    if (jmag > 0 && (ivar == 2 || ivar == 3)) {
	s_copy(xtex, "GEOM", (ftnlen)4, (ftnlen)4);
    }
    if (iut > 0 && ivar == 8) {
	s_copy(xtex, "U.T.", (ftnlen)4, (ftnlen)4);
    }
    piktab = 0.;
    if (ivar != 1) {
	if (hx < 1.) {
	    piktab = 1.;
	}
	if (hx < 0.) {
	    piktab = 2.;
	}
    }
    if (! jf[23]) {
	piktab = 3.;
    }
    if (piktab == 3.) {
	s_wsfe(&io___186);
	do_fio(&c__1, itext + (ivar - 1) * 5, (ftnlen)5);
	do_fio(&c__1, xtex, (ftnlen)4);
	e_wsfe();
    }
    if (piktab == 2.) {
	s_wsfe(&io___187);
	do_fio(&c__1, itext + (ivar - 1) * 5, (ftnlen)5);
	do_fio(&c__1, pna + (pad1 - 1) * 6, (ftnlen)6);
	do_fio(&c__1, pna + (pad2 - 1) * 6, (ftnlen)6);
	do_fio(&c__1, pna + (pad3 - 1) * 6, (ftnlen)6);
	do_fio(&c__1, xtex, (ftnlen)4);
	do_fio(&c__1, uni + (pad1 - 1) * 3, (ftnlen)3);
	do_fio(&c__1, uni + (pad2 - 1) * 3, (ftnlen)3);
	do_fio(&c__1, uni + (pad3 - 1) * 3, (ftnlen)3);
	e_wsfe();
    }
    if (piktab == 1.) {
	s_wsfe(&io___188);
	do_fio(&c__1, itext + (ivar - 1) * 5, (ftnlen)5);
	do_fio(&c__1, xtex, (ftnlen)4);
	e_wsfe();
    }
    if (piktab == 0.) {
	s_wsfe(&io___189);
	do_fio(&c__1, itext + (ivar - 1) * 5, (ftnlen)5);
	do_fio(&c__1, xtex, (ftnlen)4);
	e_wsfe();
    }
    xcor = vbeg;
    i__1 = numstp;
    for (li = 1; li <= i__1; ++li) {

/* special output: peak densities and altitudes */

	if (piktab == 1.) {
	    if (oar[li * 50 - 48] < 1.) {
		oar[li * 50 - 47] = 0.;
	    }
	    iyp1 = (integer) (oar[li * 50 - 50] / 1e6 + .5);
	    iyp2 = 0;
	    if (oar[li * 50 - 48] > 0.) {
		iyp2 = (integer) (oar[li * 50 - 48] / 1e6 + .5);
	    }
	    iyp3 = (integer) (oar[li * 50 - 46] / 1e6 + .5);
	    iyp4 = (integer) (oar[li * 50 - 44] / 1e6 + .5);
	    tec = oar[li * 50 - 14];
	    if (tec > 0.) {
		tec /= 1e16;
		itopp = (integer) (oar[li * 50 - 13] + .5);
	    } else {
		tec = -1.;
		itopp = -1;
	    }
	    s_wsfe(&io___198);
	    do_fio(&c__1, (char *)&xcor, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&oar[li * 50 - 49], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&oar[li * 50 - 47], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&oar[li * 50 - 45], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&oar[li * 50 - 43], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&iyp1, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&iyp2, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&iyp3, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&iyp4, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&tec, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&itopp, (ftnlen)sizeof(integer));
	    e_wsfe();
	    goto L1234;
	}
	if (piktab == 2.) {
	    yp1 = sqrt(oar[li * 50 - 50] / 1.24e10);
	    yp2 = 0.;
	    if (oar[li * 50 - 48] > 0.) {
		yp2 = sqrt(oar[li * 50 - 48] / 1.24e10);
	    }
	    yp3 = sqrt(oar[li * 50 - 46] / 1.24e10);
/*        if(pad1.eq.45.and.oar(pad1,li).le.0.0) oar(pad1,li)=-1. */
/*        if(pad2.eq.45.and.oar(pad2,li).le.0.0) oar(pad2,li)=-1. */
/*        if(pad3.eq.45.and.oar(pad3,li).le.0.0) oar(pad3,li)=-1. */
	    s_wsfe(&io___201);
	    do_fio(&c__1, (char *)&xcor, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&oar[li * 50 - 15], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&oar[li * 50 - 41], (ftnlen)sizeof(
		    doublereal));
	    d__1 = oar[li * 50 - 39] - oar[li * 50 - 45];
	    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    d__2 = oar[li * 50 - 40] / oar[li * 50 - 46];
	    do_fio(&c__1, (char *)&d__2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&yp1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&yp2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&yp3, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&oar[pad1 + li * 50 - 51], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&oar[pad2 + li * 50 - 51], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&oar[pad3 + li * 50 - 51], (ftnlen)sizeof(
		    doublereal));
	    e_wsfe();
	    goto L1234;
	}
/* special output for D-region options */

	if (piktab == 3.) {
	    hxx = hx;
	    if (ivar != 1 && hx < 20.) {
		hxx = 85.;
	    }
	    ip1 = (integer) (outf[li * 20 - 20] / 1e6 + .5);
	    ip2 = (integer) (outf[li * 20 - 8] / 1e6 + .5);
	    if (ivar == 1) {
		hxx = xcor;
	    }
	    ihx = (integer) ((hxx - 60) / 5.) + 1;
	    ixne = -1;
	    ixn1 = -1;
	    ixn2 = -1;
	    if (ihx > 0 && ihx < 7) {
		hihx = (doublereal) ((ihx - 1) * 5 + 60);
		ixne = (integer) ((outf[ihx * 20 - 7] + (outf[(ihx + 1) * 20 
			- 7] - outf[ihx * 20 - 7]) / 5 * (hxx - hihx)) / 1e6 
			+ .5);
		ih1 = ihx + 7;
		ixn1 = (integer) ((outf[ih1 * 20 - 7] + (outf[(ih1 + 1) * 20 
			- 7] - outf[ih1 * 20 - 7]) / 5 * (hxx - hihx)) / 1e6 
			+ .5);
		ih2 = ihx + 14;
		ixn2 = (integer) ((outf[ih2 * 20 - 7] + (outf[(ih2 + 1) * 20 
			- 7] - outf[ih2 * 20 - 7]) / 5 * (hxx - hihx)) / 1e6 
			+ .5);
	    }
	    s_wsfe(&io___211);
	    do_fio(&c__1, (char *)&xcor, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ip1, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ip2, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ixne, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ixn1, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ixn2, (ftnlen)sizeof(integer));
	    e_wsfe();
	    goto L1234;
	}

/* normal output */

	if (ivar == 1) {
	    oar[li * 50 - 50] = oar[0];
	    oar[li * 50 - 14] = oar[36];
	    oar[li * 50 - 13] = oar[37];
	}
	jne = (integer) (outf[li * 20 - 20] / 1e6 + .5);
	xner = outf[li * 20 - 20] / oar[li * 50 - 50];
	jtn = (integer) (outf[li * 20 - 19] + .5);
	jti = (integer) (outf[li * 20 - 18] + .5);
	jte = (integer) (outf[li * 20 - 17] + .5);
	jio = (integer) (outf[li * 20 - 16] + .5);
	jih = (integer) (outf[li * 20 - 15] + .5);
	jihe = (integer) (outf[li * 20 - 14] + .5);
	jino = (integer) (outf[li * 20 - 13] + .5);
	jio2 = (integer) (outf[li * 20 - 12] + .5);
	jicl = (integer) (outf[li * 20 - 11] + .5);
	jin = (integer) (outf[li * 20 - 10] + .5);
	if (outf[li * 20 - 20] < 0.) {
	    jne = -1;
	}
	if (outf[li * 20 - 20] < 0.) {
	    xner = -1.;
	}
	if (outf[li * 20 - 19] < 0.) {
	    jtn = -1;
	}
	if (outf[li * 20 - 18] < 0.) {
	    jti = -1;
	}
	if (outf[li * 20 - 17] < 0.) {
	    jte = -1;
	}
	if (outf[li * 20 - 16] < 0.) {
	    jio = -1;
	}
	if (outf[li * 20 - 15] < 0.) {
	    jih = -1;
	}
	if (outf[li * 20 - 14] < 0.) {
	    jihe = -1;
	}
	if (outf[li * 20 - 13] < 0.) {
	    jino = -1;
	}
	if (outf[li * 20 - 12] < 0.) {
	    jio2 = -1;
	}
	if (outf[li * 20 - 11] < 0.) {
	    jicl = -1;
	}
	if (outf[li * 20 - 10] < 0.) {
	    jin = -1;
	}
	if (tec > 0.) {
	    tec = oar[li * 50 - 14] / 1e16;
	    itopp = (integer) (oar[li * 50 - 13] + .5);
	} else {
	    tec = -1.;
	    itopp = -1;
	}
	s_wsfe(&io___224);
	do_fio(&c__1, (char *)&xcor, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&jne, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&xner, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&jtn, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&jti, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&jte, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&jio, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&jin, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&jih, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&jihe, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&jino, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&jio2, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&jicl, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&tec, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&itopp, (ftnlen)sizeof(integer));
	e_wsfe();
L1234:
	xcor += vstp;
    }
    s_wsle(&io___225);
    do_lio(&c__9, &c__1, "Enter 0 to exit or 1 to generate another profile?", 
	    (ftnlen)49);
    e_wsle();
    s_rsle(&io___226);
    do_lio(&c__3, &c__1, (char *)&icontinue, (ftnlen)sizeof(integer));
    e_rsle();
    if (icontinue > 0) {
	goto L1;
    }
    s_stop("", (ftnlen)0);
} /* MAIN__ */

