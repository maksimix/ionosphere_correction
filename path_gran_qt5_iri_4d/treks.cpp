#include <stdio.h>
#include <math.h>
#include "paths.h"

void magfis(double fi, double teta, double r,
	    double h[3], double dh[3][3], double dh3[3][3][3]);

void coords(double aksf[3], double akglob[3],
	    double aksfa[3], double akga[3],
	    double aksfd[3], double akgd[3],
	    double y8, double y14, double y9, double y15,
	    int i, int key);

int coors(double z[3], double akglob[3], double xa[3], double xd[3],
	  double akga[3], double akgd[3],
	  double r1, double r2, double sig,
	  double *p, double *f, double *t,
	  int    key);

int ionos(double f, double t, double r,
	  int    n);

int soluts(double *x, double *y,
	   int    n,
	   double delt, double eps, double ep,
	   double ep1,  double e);

int funcs(double x,
	  double *y,
	  double *f,
	  int    n);

int  treks(double d0,
	   double alfa,
	   int    ihop,
	   int    n,
	   double delt,
	   double eps,
	   double ep,
	   double ep1,
           double e,
	   PUTDAT *putdat)
/*******************************************************************/
/*                                                                 */
/*     ðïäðòïçòáííá ðïäçïôá÷ìé÷áåô îáþáìøîùå äáîîùå äìñ òåûåîéñ    */
/*     õòá÷îåîéê ìõþá é ÷ùþéóìñåô éîôåçòáìøîùå èáòáëôåòéóôéëé      */
/*     íîïçïóëáþëï÷ïê ôòáåëôïòéé.                                  */
/*                                                                 */
/*  ÷ üôïê ðïäðòïçòáííå ÷ ëáþåóô÷å ðáòáíåôòï÷ äìñ ðòéóïåäéîåîîïê   */
/*       óéóôåíù õòá÷îåîéê ÷ùâòáîù õçìù éúìõþåîéñ                  */
/*                                                                 */
/* d0   -õçïì éúìõþåîéñ;                                           */
/* alfa -áúéíõô éúìõþåîéñ;                                         */
/* ihop -þéóìï óëáþëï÷;                                            */
/* n    -ëïìéþåóô÷ï éîôåçòéòõåíùè õòá÷îåîéê;                       */
/* delt0,eps,ep,ep1,e-ôïþîïóôîùå èáòáëôåòéóôéëé;                   */
/* *putdat-íáóóé÷ ÷ùèïäîùè éîôåçòáìøîùè èáòáëôåòéóôéë.             */
/*                                                                 */
/*VGG                                                              */
/*******************************************************************/
{
  double y[22],fa[22],p,x,ca2,usa2,r,d,a,at,
         z[3],akglob[3],
         f,t,sg,cg,sat,cat,cb,sb,cff0,akga[3],akgd[3],
         rE,rB,
         hmod=1;
  double *aksf,*aksfa,*aksfd,*xa,*xd;

  int i,key,one,kol,no;
  long n_laey;
  bool flagIn=false;

  no=1; // 0 - ÔÒÁÅËÔÏÒÉÑ ÐÏÓÔÒÏÅÎÁ

  aksf=&y[3];

  aksfa=&y[11];
  aksfd=&y[17];

  xa=&y[8];
  xd=&y[14];

  key=1;
  one=1;
  if (z0>h0)
      flagIn=true;

  for(i=0; i<n; i++)
    y[i]=.0;

  x=.0;
  d=d0;
  a=alfa;

  y[0]=fi0;                // The koordinates of RO
  y[1]=teta0;
  y[2]=z0;

  y[3]=cos(d0)*sin(alfa);
  y[4]=-cos(d0)*cos(alfa);
  y[5]=sin(d0);

  if (flagIn)
  {
      y[0]=fi0;                // The koordinates of RO
      y[1]=teta0;
      y[2]=z0;
      if (funcs(x,y,fa,6))
      {
          printf("\nThe ray does not exist here");
          return 1;
      }
      amy0=amy;
      //y[3]*=amy0;
      //y[4]*=amy0;
      //y[5]*=amy0;
      if (n>8)
      {
          key=0;
    
          double dcd,dca,dmcam,dmcamd,dmcama;
          double sd,cd,sa,ca;
    
          sd=sin(d0);
          cd=cos(d0);
          sa=sin(alfa);
          ca=cos(alfa);
    
          printf("\n####  amy=%f  dmca=%f",amy,dmca0);
          dcd=-h[0]*sa*sd+h[1]*ca*sd+h[2]*cd;
          dca= h[0]*ca*cd+h[1]*sa*cd;
          dmcam=dmca0/amy;
          dmcamd=dmcam*dcd;
          dmcama=dmcam*dca;
          y[11]= dmcama*sa*cd+amy*ca*cd; // dk_phi/dalfa
          y[12]=-dmcama*ca*cd+amy*sa*cd; // dk_teta/dalfa, y[13] = dk_r/dalfa
          y[13]= dmcama*sd;              // dk_r/dalfa
          y[17]= dmcamd*sa*cd-amy*sa*sd; // dk_phi/ddo
          y[18]=-dmcamd*ca*cd+amy*ca*sd; // dk_teta/ddo
          y[19]= dmcamd*sd+amy*cd;       // dk_r/ddo
          // y[8]=dphi/dalfa=0, y[9]=dteta/dalfa=0, y[10]=dr/dalfa=0,
          // y[14]=dphi/dd0=0, y[15]=dteta/dd0=0, y[16]=dr/dd0=0.
      }                                  
  }
  else
  {
      amy0=1.;
      if (n>8)
        {
          key=0;
    
          y[11]=-y[4];
          y[12]=y[3];
          y[17]=-sin(d0)*sin(alfa);
          y[18]=sin(d0)*cos(alfa);
          y[19]=cos(d0);
        }
  }

  sf=sf0;
  cf=cf0;
  st=st0;
  ct=ct0;

  z[0]=z0*st*cf;
  z[1]=z0*st*sf;
  z[2]=z0*ct;
  rB=z0;
  //printf("\nz0=%f d0=%f",z0-R0,d0/RAD);
  //printf("\n0 i=%d  d=%f",i,asin(y[5])/RAD);

  if (keytr<0)
  {
      pointTr=0;
      hTr[pointTr]=100.*(z0-R0);
      sTr[pointTr]=.0;
      fiTr[pointTr]=y[0];
      tetaTr[pointTr]=y[1];
      pointTr++;
  }

  for(i=0; i<ihop; i++)
  {
      D2(i)=A2(i)=X(i)=Y(i)=S(i)=AT(i)=DEV(i)=DF(i)=L(i)=.0;
      XOTR(i)=YOTR(i)=ZOTR(i)=LS(i)=PG(i)=PS(i)=.0;
      Moda(i)=0;
      if (i<ihop-1)
      {
          rE=R0;
          rH0=h0;
      }
      else
      {
          rE=z1;
          rH0=h0;
      }
      if (i==0)
          rB=z0;
      else
          rB=R0;

      if (i || !flagIn)
      {
          //printf("\n1 i=%d  d=%f",i,asin(y[5])/RAD);
          coords(aksf,akglob,aksfa,akga,aksfd,akgd,
                 y[8],y[14],y[9],y[15],2,key);
          //printf("\n2 i=%d  d=%f",i,asin(y[5])/RAD);
          //printf("\nhop=%2d  ihop=%2d one=%d",i,ihop,one);
      }
      no=one;
      //printf(" one=%d",one);
      if (one)
      {
          if (i || !flagIn)
          {
              one=coors(z,akglob,xa,xd,akga,akgd,rB,h0,1.,&p,&f,&t,key);
              //printf(" 2one=%d",one);
    
              y[0]=f;
              y[1]=t;
              y[2]=h0;
    
              if (keytr<0 && pointTr<MaxPointTr-1)
              {
                  hTr[pointTr]=100.*(y[2]-R0);
                  sTr[pointTr]=dist(fi0,teta0,y[0],y[1]);
                  fiTr[pointTr]=y[0];
                  tetaTr[pointTr]=y[1];
                  pointTr++;
              }
              //printf("\n h0=%f",h0);
    
              x +=p;
          }

          D1(i)=d/RAD;
          A1(i)=a/RAD;
          dhop[i][0]=d;

          if (n>20)
          {
              y[20] +=p;
              y[21] +=p;
          }

	  for(kol=0; kol<5; kol++)
	  {
             if (i || !flagIn || kol)
             {
                  coords(akglob,aksf,akga,aksfa,akgd,aksfd,
                         y[8],y[14],y[9],y[15],1,key);
                  //printf(" key=%d  kol=%d d=%f",key,kol,acos(y[5])/RAD);
             }

	      if (n>8)
	      {
                  if (ionos(y[0],y[1],y[2],6))
                  {
                      no=1;
                      if (keytr<0)
                          drawTrek(sTr,hTr,pointTr);
                      //printf("\n1 no=%d",no);
                      return no;
                  }

		  if (ivar)
		  {
		      magfis(y[0],y[1],y[2],h,dh,dh2);

		      hmod=sqrt(h[0]*h[0]+h[1]*h[1]+h[2]*h[2]);
		      fh=2.79*hmod;
		  }

		  u1=fh/fr;
		  u=u1*u1;
		  ak=sqrt(y[3]*y[3]+y[4]*y[4]+y[5]*y[5]);
		  ca2=(h[0]*y[3]+h[1]*y[4]+h[2]*y[5])/(hmod*ak);
		  ca2 *=ca2;
		  usa2=u*(1.-ca2);
		  r=sqrt(usa2*usa2+4.*u*ca2);

		  if(iox) r=-r;

		  dmv=-1./(2.-usa2+r);

		  y[13] +=dmv*vp[2]*y[10]/y[5];
		  y[19] +=dmv*vp[2]*y[16]/y[5];
              }

              FHhop[i][0]=fh;
              Ihop[i][0]=-asin(h[2]);
              Dhop[i][0]=atan2(h[0],h[1]);

	      if (!(no=soluts(&x,y,n,delt,e,eps,ep,ep1)))
              {
                    //printf("\nrot=%f  HmF2=%f  HmF1=%f  HmE=%f HmEs=%f",rot-R0,HmF2-R0,HmF1-R0,HmE-R0,HmEs-R0);
                    if (rot<HmD)
                        n_laey=1;
                    else
                        if (rot<HmE)
                            n_laey=2;
                        else
                            if (rot<HmF1)
                                n_laey=3;
                            else
                                if (rot<HmF2)
                                    n_laey=4;
                                else
                                    n_laey=5;
                    if (keyEs && rot<HmEs && rot>HmEs-.025)
                        n_laey=9;

                    Moda(i)=10*((i)? Moda(i-1) : 0)+n_laey;

                    if (n>8)
                    {
                        y[13] -=dmv*vp[2]*y[10]/y[5];
                        y[19] -=dmv*vp[2]*y[16]/y[5];
                    }

		    coords(aksf,akglob,aksfa,akga,aksfd,akgd,
                           y[8],y[14],y[9],y[15],2,key);

		    r=y[2];

		    z[0]=r*st*cf;
		    z[1]=r*st*sf;
		    z[2]=r*ct;

                    one=coors(z,akglob,xa,xd,akga,akgd,r,rE,-1.,
                              &p,&f,&t,key);
                    //printf(" 3one=%d r=%f  rE=%f",one,r-R0,rE-R0);

		    if (!one)
		    {
			one=1;

			z[0]=st*cf;
			z[1]=st*sf;
			z[2]=ct;

			x +=p;

                        if (n>20)
                          {
                            y[20] +=p;
                            y[21] +=p;
                            PG(i)=y[20]*100.;
                            PS(i)=y[21]*100.;
                          }

			coords(akglob,aksf,akga,aksfa,akgd,aksfd,
			       y[8],y[14],y[9],y[15],1,key);

			if (n>8)
			  {
			    r=y[3]*(y[9]*y[16]-y[15]*y[10])/(rE*st)-
			      y[4]*(y[8]*y[16]-y[14]*y[10])/rE+
			      y[5]*(y[8]*y[15]-y[14]*y[9]);

			    r *=R0*R0*st/(amy0*cos(d0));

			    LS(i)=10.*log10(fabs(r)*10000.);
			  }

                        cff0=cf*cf0+sf*sf0;
			cb=ct0*ct+st0*st*cff0;
			sb=sqrt(1.-cb*cb);
                        S(i)=R0*100.*atan2(sb,cb);
                        /*
                        if (S(i)>RMax)
                        {
                            no=-1;
                            if (keytr<0)
                                drawTrek(sTr,hTr,pointTr);
                            //printf("\n2 no=%d",no);
                            return no;
                        }
                        */
			cat=st0*ct-st*ct0*cff0;
			sat=st*(sf*cf0-sf0*cf);
			at=atan2(sat,cat);

			AT(i)=at/RAD;

			X(i)=f/RAD;

			Y(i)=t/RAD;

			P(i)=x*100.;

                        if (n>6) DF(i)=-y[6]*fr*100./C;

			if (n>7) L(i)=-y[7]*PI*fr*868.588/.2997925;

			XOTR(i)=fot/RAD;
			YOTR(i)=tot/RAD;
			ZOTR(i)=(rot-R0)*100.;

			cg=fabs(z[0]*akglob[0]+z[1]*akglob[1]+
				z[2]*akglob[2]);
			sg=sqrt(1.-cg*cg);
                        d=atan2(cg,sg);
                        a=atan2(y[3],-y[4]);
                        D2(i)=d/RAD;
                        A2(i)=atan2(-y[3],y[4])/RAD;
                        dhop[i][1]=d;
                        ref[i]=(rot-R0)*100.;
                        FHhop[i][1]=fh;
                        Ihop[i][1]=-asin(h[2]);
                        Dhop[i][1]=atan2(h[0],h[1]);

                        //DEV(i)=(at-alfa)/RAD;
                        DEV(i)=atan2(sin(at-alfa),cos(at-alfa))/RAD;
                        //printf("\n d=%6.2f i=%2d one=%2d",asin(-aksf[2])/RAD,i,one);
                        //printf("\nD1=%6.2f A1=%8.3f D2=%6.2f A2=%8.3f DEV=%8.3f y[2]=%f y[3]=%f y[4]=%f y[5]=%f",D1(i),A1(i),D2(i),A2(i),DEV(i),y[2],y[3],y[4],y[5]);

                        if (keytr<0 && pointTr<MaxPointTr-1)
                        {
                            hTr[pointTr]=100.*(rE-R0);
                            sTr[pointTr]=S(i);//dist(fi0,teta0,y[0],y[1]);
                            fiTr[pointTr]=y[0];
                            tetaTr[pointTr]=y[1];
                            pointTr++;
                        }

                        if(i==ihop-1)
                        {
                            if (keytr<0)
                            {
                                drawTrek(sTr,hTr,pointTr);
                                //printf("\n3 no=%d  pointTr=%d",no,pointTr);
                            }
                            return no;
                        }

			z[0]=z[0]*R0;
			z[1]=z[1]*R0;
                        z[2]=z[2]*R0;
                        rB=R0;

			if (n>8)
			{
			    aksfa[2]=-aksfa[2];
			    aksfd[2]=-aksfd[2];
			    //aksf[2]=-aksf[2];
                        }
                        aksf[2]=-aksf[2];
                        break;
		    }
		    else
                    {
                        one=coors(z,akglob,xa,xd,akga,akgd,r,h0,1.,
                                  &p,&f,&t,key);

			x +=p;

			y[0]=f;
			y[1]=t;
			y[2]=h0;

                        if (keytr<0 && pointTr<MaxPointTr-1)
                        {
                            hTr[pointTr]=100.*(y[2]-R0);
                            sTr[pointTr]=dist(fi0,teta0,y[0],y[1]);
                            fiTr[pointTr]=y[0];
                            tetaTr[pointTr]=y[1];
                            pointTr++;
                        }

			if (n>20) y[20] +=p;
		    }
	      }
              else
              {
                  D1(i)=.0;
                  P(i) =.0;
                  if (keytr<0)
                      drawTrek(sTr,hTr,pointTr);
                  //printf("\n4 no=%d",no);
                  return no;
              }
          }
          if (kol==5)
          {
              no=-1;
              if (keytr<0)
                  drawTrek(sTr,hTr,pointTr);
              //printf("\n5 no=%d",no);
              return no;
          }
      }
      else
      {
          if (keytr<0)
              drawTrek(sTr,hTr,pointTr);
          //printf("\n6 no=%d",no);
          return no;
      }
    }
} /* treks */


double dist(double fi0, double teta0, double fi1, double teta1)
{
    double lat0,lon0,lat1,lon1,dlon;
    double s0;

    lat0=PI05-teta0;
    lat1=PI05-teta1;
    lon0=fi0;
    lon1=fi1;
    dlon=lon1-lon0;

    s0=sin(lat0)*sin(lat1)+cos(lat0)*cos(lat1)*cos(dlon);
    s0=R0*atan2(sqrt(1.-s0*s0),s0);
    //alf =atan2(cos(lat1)*sin(dlon),sin(lat1)*cos(lat0)-
    //           sin(lat0)*cos(lat1)*cos(dlon));
    //alf1=atan2(-cos(lat0)*sin(dlon),sin(lat0)*cos(lat1)-
    //           sin(lat1)*cos(lat0)*cos(dlon));

    return 100.*s0;
}

