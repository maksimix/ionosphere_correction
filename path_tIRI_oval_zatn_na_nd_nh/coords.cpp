#include <math.h>
#include "paths.h"


void coords(double x[3],
	    double y[3],
	    double xa[3],
	    double ya[3],
	    double xd[3],
	    double yd[3],
	    double fa,
	    double fd,
	    double ta,
	    double td,
	    int    i,
	    int    key)
/**************************************************************/
/*                                                            */
/*     ןףץ‎וףפקלסופ נועוקןה קוכפןעב ט ית הוכבעפןקןך ף/כ       */
/*      ק ףזועי‏וףכץא, וףלי i=1, י ןגעבפמןו נעוןגעבתןקמיוס    */
/*      ק ןףפבלרמשט ףלץ‏בסט.                                  */
/*                                                            */
/*VGG                                                         */
/**************************************************************/
{
  double ctcf,ctsf,stcf,stsf;

  ctcf=ct*cf;
  ctsf=ct*sf;
  stcf=st*cf;
  stsf=st*sf;

  switch (i)
    {
      case 1:  /* נעוןגעבתןקבמיו ק ףזועי‏וףכץא ף/כ */
	     y[0]=-sf*x[0]+cf*x[1];
	     y[1]=ctcf*x[0]+ctsf*x[1]-st*x[2];
	     y[2]=stcf*x[0]+stsf*x[1]+ct*x[2];

	     if (key) return;

	     ya[0]=-cf*fa*x[0]-sf*fa*x[1]-sf*xa[0]+cf*xa[1];
	     ya[1]=-(stcf*ta+ctsf*fa)*x[0]+(ctcf*fa-stsf*ta)*x[1]-
		   ct*ta*x[2]+ctcf*xa[0]+ctsf*xa[1]-st*xa[2];
	     ya[2]=(ctcf*ta-stsf*fa)*x[0]+(ctsf*ta+stcf*fa)*x[1]-
		   st*ta*x[2]+stcf*xa[0]+stsf*xa[1]+ct*xa[2];

	     yd[0]=-cf*fd*x[0]-sf*fd*x[1]-sf*xd[0]+cf*xd[1];
	     yd[1]=-(stcf*td+ctsf*fd)*x[0]+(ctcf*fd-stsf*td)*x[1]-
		   ct*td*x[2]+ctcf*xd[0]+ctsf*xd[1]-st*xd[2];
	     yd[2]=(ctcf*td-stsf*fd)*x[0]+(ctsf*td+stcf*fd)*x[1]-
		   st*td*x[2]+stcf*xd[0]+stsf*xd[1]+ct*xd[2];

	     return;

      case 2: /*  נעוןגעבתןקבמיו ק הוכבעפןקץ ף/כ */
	     y[0]=-sf*x[0]+ctcf*x[1]+stcf*x[2];
	     y[1]=cf*x[0]+ctsf*x[1]+stsf*x[2];
	     y[2]=-st*x[1]+ct*x[2];

	     if (key) return;

	     ya[0]=-cf*fa*x[0]-(stcf*ta+ctsf*fa)*x[1]+(ctcf*ta-stsf*fa)*x[2]-
		   sf*xa[0]+ctcf*xa[1]+stcf*xa[2];
	     ya[1]=-sf*fa*x[0]+(ctcf*fa-stsf*ta)*x[1]+(ctsf*ta+stcf*fa)*x[2]+
		   cf*xa[0]+ctsf*xa[1]+stsf*xa[2];
	     ya[2]=-ct*ta*x[1]-st*ta*x[2]-st*xa[1]+ct*xa[2];

	     yd[0]=-cf*fd*x[0]-(stcf*td+ctsf*fd)*x[1]+(ctcf*td-stsf*fd)*x[2]-
		   sf*xd[0]+ctcf*xd[1]+stcf*xd[2];
	     yd[1]=-sf*fd*x[0]+(ctcf*fd-stsf*td)*x[1]+(ctsf*td+stcf*fd)*x[2]+
		   cf*xd[0]+ctsf*xd[1]+stsf*xd[2];
	     yd[2]=-ct*td*x[1]-st*td*x[2]-st*xd[1]+ct*xd[2];

	     return;
    }
} /* coords */
