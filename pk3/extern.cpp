#include "paths.h"

double fl[5],hl[5],yl[5],al[5],
       dx[99],df[100],ff[100],xx[100],
       u,u1,fh,
       sf,cf,st,ct,
       sf0,cf0,st0,ct0,
       fi0,teta0, // ���������� ����� ���������
       z0,z1,rH0, // ������ ����������� � ���������
       v,vp[3],vpp[3][3],dvt,s,par,
       dmrtf[3],dmv,ov,sa2,ak,anorm,
       h[3],dh[3][3],dh2[3][3][3],
       fr,fr2,
       tim,
       de[3],om[3],pf[3],pt[3],pr[3],fit[3],
       fot,tot,rot,
       fpl[100],hpl[100],
       f0,hm,ym,h0,f02,
       gx,gy,
       fMin,
       //HmF2,HmF1,HmE,HmD,HmEs,F0F2,F0F1,F0E,F0D,F0Es,FbEs,PEs,fMin,Hi,
       FHhop[MaxHop][2],Ihop[MaxHop][2],Dhop[MaxHop][2],
       //fhTemp,DTemp,ITemp,
       FHhopk[RAY][MaxHop][2],Ihopk[RAY][MaxHop][2],Dhopk[RAY][MaxHop][2],
       dhop[MaxHop][2],ref[MaxHop],dhopk[RAY][MaxHop][2],refk[RAY][MaxHop];
double sTr[MaxPointTr],hTr[MaxPointTr];
double dfi_a,dfi_d,dteta_a,dteta_d;
long   pointTr;

int    nm,ii,mod,iox,koltid,klay,ivar,keytr;
int    keysol,keyEs,keympr,keyugl,keynu,keyl2;

 