#include "paths.h"

#define M 2 /* ���������� ���������� ����� */
#define EPS .17e-4

#define FORM "\nMPCHE f,d8,s,dd,d7,ihop,key,no,ox %6.2lf%7.2lf%7.1lf\
%7.3lf%7.2lf%4d%4d%4d"

double mpchs(double s0,
             double alfa,
             long   ihop,
             double db,
             double de,
             double delt,
             double eps,
             double ep,
             double ep1,
             double e,
             double eps2,
             double epsa, // �������� �� �������
             double dd0,  // ��� �� ���� �����
             double aa0,  // ��� �� �������
             PUTDAT *putdat)
/***************************************************************/
/*                                                             */
/* ������� ������� ������������ ���������� ������� ��� ��������*/
/*                 ������������� ������.                       */
/*                                                             */
/* s0   - ����� ������,                                        */
/* ihop - ����� �������,                                       */
/* dd   - ��������� ��� �� ����,                               */
/* d1   - ����������� �� ������������ ���� ������,             */
/* eps2 - ����������� �� ����������� ��������� ��� ������      */
/*        ��������, ���������� ����� ��������� ������: s(d)=s0;*/
/*                                                             */
/*VGG  ������ 24.06.06                                         */
/***************************************************************/

{
  long    l,ikor,io,no,io_key;
  double f2,f3,d2,d3,d7,d8,s,p,dd,df,f,
         d0,pg,eps1,dff,ls,s1;

  df=(fMin>5.)? 5. : fMin;

  //printf("\ndf=%f  fMin=%f  db=%f  de=%f",df,fMin,db/RAD,de/RAD);

  eps1=.01*s0;
  p=s0/(2.*ihop*R0);
  if (db<=.0)
  {
      db=atan2((h0*cos(p)-R0),h0*sin(p));//-dd0;
      if (db<.0) db=1.*RAD;
  }
  if (de<.0) de=PI;
  d0=db;

  f=fMin+.5*df;

  l=0;
  ikor=0;

  /* ikor=1 - ������� ����, ��� �� �����-�� ������� ��� ������; */
  /* l      - ������� ������� ���� �� �������;                  */
  /*                                                            */
  /*              ������ ������������ ������ �� ���             */
  //printf("\nf=%f d0=%f",f,d0/RAD);
  while (df>.5e-1)
    {
      io=0;
      f2=f3=d2=d3=.0;
      s1=.0;
      d8=db;
      dd=dd0;
      io_key=-M; /* ���� io_key=0, �� ��� ��������, ��� ��� �������   */
                 /* ���� ��������� ��������� ���������� � ����������� */
                 /* ������������ � ��������� ������ s0                */
      fr=f;
      fr2=fr*fr;
      u1=fh/fr;
      u=u1*u1;
      //if (keytr<0)
        //draw_sol(0);

  /* ���������� ��������� ��� ��������� ���� ������             */
  /* key - -1 - ����� ��������� �����,                          */
  /*        1 - ������ ������� ������� ���������,               */
  /*        0 - ����� ��������� ������ �������;                 */
  /* no  -  0 - ������� ��������� �� ���� �������,              */
  /*        1 - ������������,                                   */

      //no=treki(f,d8,ihop,4,delt,eps,e,&s,&d7,&p,&pg,&dff,&ls,&n_laey);

      //if (keympr)
      //  printf(FORM,f,d8/RAD,s,dd,d7/RAD,ihop,key,no,iox);
      //s *=.01;
      //if (s<s0 && (d8>PI5 || d7>PI5) && !no || !no && key<0) dd=-dd;

// ���������� �� ���� ��������� �� ��� ���, ����
      // ��������� �� ����� �� ������ ������ ����� ������
      d8+=dd0;
      dd=-dd0;
      do
      {
          d8 +=dd;
          if (d8<.0)
          {
              io=1;
              d8-=dd;
              break;
          }
          no=soltA(d8,alfa,ihop,delt,eps,ep,ep1,e,epsa,aa0,putdat);
          s=S(ihop-1);
          d7=D2(ihop-1)*RAD;
    
          if (keympr)
            printf(FORM,-f,d8/RAD,s,dd,d7/RAD,ihop,no,iox);
    
          s *=.01;
      }
      while(s<s0 && !no);

      if (no==-1)
      {
          //return n;
          dd=-dd;
          io=0;
          while(no==-1 && d8<PI05)
          {
              d8+=dd;
              no=soltA(d8,alfa,ihop,delt,eps,ep,ep1,e,epsa,aa0,putdat);
              s=S(ihop-1);
              d7=D2(ihop-1)*RAD;
        
              if (keympr)
                printf(FORM,-f,d8/RAD,s,dd,d7/RAD,ihop,no,iox);

              s *=.01;
          }
      }
      else
          if (!io)
              dd=-dd;

      if (no)
      { /* ��� ������ �� ����������� ������� */
          l=1;
          df *=0.5;
          f -=df;
          continue;
      }
    
      while (no)
      {
          d8 +=dd;
          no=soltA(d8,alfa,ihop,delt,eps,ep,ep1,e,epsa,aa0,putdat);
          s=S(ihop-1);
          d7=D2(ihop-1)*RAD;
          if (keympr)
            printf(FORM,f,d8/RAD,s,dd,d7/RAD,ihop,no,iox);
          s *=.01;
    
          if (no)
            { /* ��� ������ �� ����������� ������� */
              l=1;
              df *=0.5;
              f -=df;
              break;
            }
      }
    
      if (no) continue;
    
      d0=d8;
    
      while (fabs(dd)>EPS && (!io || io_key))
      {
          if (s<eps2 || d8>de) break;
    
          if (s<=s0)
            {
              f2=s-s0;
              d2=d8;
            }
          else
            {
              f3=s-s0;
              d3=d8;
            }
    
          if (f2*f3<0)
            { /* yes */
              if (zero_t(d2,f2,d3,f3,s0,alfa,ihop,delt,eps,ep,ep1,e,eps1,epsa,aa0,putdat)>=.0)
                {
                  ikor=1;
                  db=d0;
                  /* ������������� ��������� ���� ��� ��������  */
                  /* ����� ������, �.�. �� ������ ������� ����  */
                  /* ������� ��������� ������.                  */
                  break;
                }
              f2=f3=d2=d3=.0;
            } /* yes */
          else
            { /* no */
              do
                {
                  if (io)
                  {
                      dd*=.5;
                      if (no)
                          d8-=dd;
                      else
                      {
                          if (dd<.0)
                          {
                              d8+=dd;
                              while(d8<.0)
                              {
                                  dd*=.5;
                                  d8-=dd;
                              }
                          }
                          else
                              d8+=dd;
                      }
                  }
                  else
                      d8+=dd;
    
                  no=soltA(d8,alfa,ihop,delt,eps,ep,ep1,e,epsa,aa0,putdat);
                  s=S(ihop-1);
                  d7=D2(ihop-1)*RAD;
    
                  if (keympr)
                    printf(FORM,f,d8/RAD,s,dd,d7/RAD,ihop,no,iox);
                  s *=.01;
    
                  if (no && !io) io=1;
    
                  if (!no && io)
                    if (s>s0 && s>s1)
                      { s1=s;  io_key++; }
                    else
                      { s1=.0; io_key=-M; }
    
                }
              while (no && fabs(dd)>EPS && (!io || io_key));
    
            } /* no */
        }
    
        if (f2==.0)
          {
            l=1;
            df *=0.5;
            f -=df;
          }
        else
          {
            if (l) df *=0.5;
            f +=df;
          }
    }

  f -=df;
  if (!ikor) f=.0;

  return f;
} /* mpche */