/***************************************************************/
/*                                                             */
/* ???????? ???????, ???????????? ??????????? ??????? ???????- */
/* ??? ? ?????????? ???????? ?????????????-????????????        */
/* ??????????????? ?????????.                                  */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
#include "paths.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "readDir.cpp"


void inions(FILE *in, FILE *out);

void infils(FILE *in, FILE *out);


#define STR1 "\ndelt0=%8.1lg  eps=%8.1lg  ep=%8.1lg  ep1=%8.1lg"

/*==============================================================*/

int main(int argc, char *argv[])
{


    char dirname[256];
    getcwd(dirname, sizeof(dirname));
    int dTimeHour=0;
    int len = strlen(dirname);


    sprintf(dirname+len,"/201904_03_10/9996");
    printf("%s\n",dirname);
    int c = 0;
    char **filesName = readDir(dirname,&c);
    int k2 = 1;


    for(int k=0;k<c;k++){

    sscanf(filesName[k],"%*[^_]_%*[^_]_%*[^_]_%d%*s",&dTimeHour);
    dTimeHour = (int)ceil(((double)dTimeHour/100));
    int dataDay = 0;
    sscanf(filesName[k],"%*[^_]_%*[^_]_%d%*s",&dataDay);

 if(dataDay==4 && dTimeHour == 10) {
   char*  ch1 = getInputFile(1,filesName[k],9996);
   char* ch1noCor = getInputFile(0,filesName[k],9996);
printf("%d \n",dTimeHour);
//  printf("%s\n",filesName[k]);
//   printf("\n\n--------------------%d-------------------------------------\n",dTimeHour);
 resultMain(ch1,filesName[k],1);
   printf("\n\n---------------------------------------------------------------\n");
   free(ch1);


 resultMain(ch1noCor,filesName[k],0);
   free(ch1noCor);

 }


}

return 0;



} /* path0s */
void resultMain( char*fileInName, char *filePelName, int cor){
    //cor = 1 - TEC, cor = 0 - noCor
    double alfa,d0,delt0,eps,ep,ep1,
           f[500],d[500],a[500],t[500];
    double lat0,lon0,
           w,W,ig,IG,ames,ptr,b,rmax;
    long   it1,it2,it3,hou1,hou2,hou3,min1,min2,min3,
           sek1,sek2,sek3;
    double t1,t2,t3,time,tmre,dt,
           time1,time2,dtime;


  double **distValuesE = dynamic_array_alloc<double>(2,500); //?????? ?? ?????????? ????????? ?? ??? (E mode)
  double **distValuesF1 = dynamic_array_alloc<double>(2,500); //?????? ?? ?????????? ????????? ?? ??? (f1 mode)
  double **distValuesF2 = dynamic_array_alloc<double>(2,500); //?????? ?? ?????????? ????????? ?? ??? (f2 mode)

  double **azimutValuesE = dynamic_array_alloc<double>(2,500); //?????? ?? ?????????? ???????  ?? ??? (E mode)
  double **azimutValuesF1 = dynamic_array_alloc<double>(2,500); //?????? ?? ?????????? ???????  ?? ??? (f1 mode)
  double **azimutValuesF2 = dynamic_array_alloc<double>(2,500); //?????? ?? ?????????? ???????  ?? ??? (f2 mode)

  double **anglePosValuesE = dynamic_array_alloc<double>(2,500); //?????? ?? ?????????? ????????? ?? ???
  double **anglePosValuesF1 = dynamic_array_alloc<double>(2,500); //?????? ?? ?????????? ????????? ?? ???
  double **anglePosValuesF2 = dynamic_array_alloc<double>(2,500); //?????? ?? ?????????? ????????? ?? ???

  double TECval=0;
  double e=.0625;
  int n,io,ix,ihop,kolf,iyear;
  long keyvod, keyMod, keyEs, keypri;
  int i,j,id;

  PUTDAT *putdat;

  FILE *in,*out,*outL,*outR, *outR_OneFileData;


  keyEs=0;

  outL=0;

  in=fopen(fileInName,"rt");


    if (in==NULL)
      {
        printf("Input File:%s error open\n",fileInName);
        exit(EXIT_FAILURE);
      }


    char name[256];
    char nameL[256];
    char nameR[256];
    char nameR_OneFileData[256];


    sprintf(name,"results/out/%s",filePelName);
    sprintf(nameR,"results/outR/%s",filePelName);
    sprintf(nameR_OneFileData,"results/nameR_OneFileData/%s",filePelName);
    sprintf(nameL,"results/outL/%s",filePelName);
    int strLen=strlen(name);
    int strLenR=strlen(nameR);
    int strLenR_OneFileData=strlen(nameR_OneFileData);
    int strLenL=strlen(nameL);
    switch (cor) {
    case 0: {

        sprintf(name+strLen-4,"_noCor.txt");
        sprintf(nameL+strLenL-4,"_noCor_L.txt");
        sprintf(nameR+strLenR-4,"_noCor_R.txt");

        break;
    };
    case 1:{
        sprintf(name+strLen-4,"_TEC.txt");
        sprintf(nameL+strLenL-4,"_TEC_L.txt");
        sprintf(nameR+strLenR-4,"_TEC_R.txt");

        break;
    };
    default: break;
    }


    outL=fopen(nameL,"wt");
    outR = fopen(nameR,"wt");
    outR_OneFileData = fopen(nameR_OneFileData,"a");
    out=fopen(name,"wt");

    if (out==NULL)
      {
        printf("Output File:%s error open\n",filePelName);
        printf("%s\n",name);
        exit(EXIT_FAILURE);
      }


    fscanf(in,"%lg%lg%lg%lg%lg",&delt0,&eps,&ep,&ep1,&rmax);
    fprintf(out,STR1,delt0,eps,ep,ep1);
    fscanf(in,"%ld%ld%ld%ld%ld%ld%ld",&keyvod,&keynu,&keyMod,&keyl2,&keyEs,&keypri,&keytr);

    RMax=rmax;
    e=e*eps;
    z0=z1=R0;
    rmax*=.01;

    fscanf(in,"%lg%lg%lg%lg%ld%lg%lg%lg%lg%lg",
           &lon0,&lat0,&z0,&z1,&iyear,&ames,&w,&ig,&ptr,&b);

    fscanf(in,"%lg%lg%lg",&sMinIon,&sMaxIon,&alfIon);

    z0=.01*z0+R0;
    z1=.01*z1+R0;
    fi0=lon0*RAD;
    teta0=(90.-lat0)*RAD;

    lon0*=RAD;
    lat0*=RAD;


    fscanf(in,"%ld%ld%ld",&it1,&it2,&it3);
// //   printf("\nit1=%ld  it2=%ld  t3=%ld",it1,it2,it3);

    hou1=it1/10000l;
    hou2=it2/10000l;
    hou3=it3/10000l;
    min1=(it1-hou1*10000l)/100l;
    min2=(it2-hou2*10000l)/100l;
    min3=(it3-hou3*10000l)/100l;
    sek1=it1-hou1*10000l-min1*100l;
    sek2=it2-hou2*10000l-min2*100l;
    sek3=it3-hou3*10000l-min3*100l;
  // //  printf("\nh=%ld m=%ld s=%ld h2=%ld m2=%ld s2=%ld",hou1,min1,sek1,hou2,min2,sek2);
    t1=hou1*3600.+min1*60.+sek1;
    t2=hou2*3600.+min2*60.+sek2;
    t3=hou3*3600.+min3*60.+sek3;
    dt=t3;
   // // printf("\nt1=%f  t2=%f  t3=%f",t1,t2,t3);
    if (t1>t2)
      t1-=86400.; // ?????? ??????? ?????????? ?????? ????????? ?????????????


    infils(in,out);

    W=w;
    IG=ig;
    inions(in,out,iyear,ames,W,IG,rmax,keyvod,keyMod,keyEs,t1,t2,dt);

   // // printf("\ninion\n");

    //prion(out,lat0,lon0,lat0,lon0,t1,W,IG,keypri,keyEs);

    //printf("\nprion\n");

    fscanf(in,"%d",&ihop);
  // //  printf("\nihop=%d",ihop);

    //fscanf(in,"%d",&kolf);

    //for(id=0; id<kolf; id++)
    //  fscanf(in,"%lg%lg%lg%lg",&f[id],&d[id],&a[id],&t[id]);

    //printf("\nkolf=%d\n",kolf);

    fscanf(in,"%d%d",&io,&ix);

    fscanf(in,"%d",&n);
  // //  printf("\n\nNumber diff. equation:%2d\n",n);
    fprintf(out,"\n\nNumber diff. equation:%2d\n",n);

    putdat=(PUTDAT*)malloc(sizeof(PUTDAT)*ihop);

    char namePel[256],str[512];
    FILE *inPel;

    fscanf(in,"%s",namePel);
    inPel=fopen(namePel,"rt");
    if(!inPel)
    {
        printf("Error open File:%s\n",namePel);
        printf("%s\t\t%s\n",fileInName,filePelName);
        exit(1);
    }


    int count=-1;
  int y=0;
    while(!feof(inPel))
    {
        int rab=0;
        while(!feof(inPel) && !rab)
        {
            fgets(str,256,inPel);
             if (feof(inPel))
                 break;
            sscanf(str,"%d",&rab);
        }
        if (feof(inPel))
            break;
        int hh,mm;
        double ss,t;
        sscanf(str+11,"%d",&hh);
        sscanf(str+14,"%d",&mm);
        sscanf(str+17,"%lg",&ss);
        t=hh*3600.+mm*60.+ss;

        if (iri_NTime>1)
        {
            int i=0;
            if (t>=iri_tTime[0] && t<=iri_tTime[iri_NTime-1])
            {
                int n=iri_NTime-1;
                for(int j=0; j<n; j++)
                {
                    if (t>=iri_tTime[j] && t<iri_tTime[j+1])
                    {
                        i=j;
                        break;
                    }
                }
            }

            if (t>=iri_tTime[iri_NTime-1])
                i=iri_NTime-2;
            iri_3dbase =iri_4dbase[i];
            iri_3dbase2=iri_4dbase[i+1];
            if (count!=i)
            {
              // //  printf("\niri_NTime=%d  iIon=%d\n",iri_NTime,i);
                prion(out,lat0,lon0,lat0,lon0,tim,W,IG,keypri,keyEs);
                count=i;
            }
        }

        tim=t; // ????? ??? ??? ????????????? ?? 0 (?? ??????? ???????? ???)
        //prion(out,lat0,lon0,lat0,lon0,tim,W,IG,keypri,keyEs);

        sscanf(str+25,"%lg",&fr);
        sscanf(str+77,"%lg",&d0);
        sscanf(str+84,"%lg",&alfa);

   // //     printf("%f  %f  %f  %f\n",t,fr,d0,alfa);

        fr2=fr*fr;
        u1=fh/fr;
        u=u1*u1;

        if (t<.0)
          time=t+86400.;
        else
          time=t;
        long hou=(long)(time/3600.);
        long min=(long)((time-hou*3600.)/60.);
        long sek=(long)(time-hou*3600.-min*60.);
        long msek=(long)((time-hou*3600.-min*60.-sek)*100.);
        while(hou>24) hou -=24;

        time/=3600.;
        d0*=RAD;
        alfa*=RAD;

        for(iox=io; iox<=ix; iox++)
        {
            for(i=0; i<ihop; i++)
              IOX(i)=iox;
            for(i=0; i<ihop; i++)
              FR(i)=fr;
            for(i=0; i<ihop; i++)
                TIME(i)=tim;

            treks(d0,alfa,ihop,n,delt0,eps,ep,ep1,e,putdat);

            outtrs(out,putdat,ihop);

            if (outL>0)
            {
                char strModa[17];
                for(int ih=0; ih<ihop; ih++)//ih
                {
                    double at=AT(ih);
                    double lat=90.-Y(ih);
                    double lon=X(ih);

                    moda(Moda(ih),strModa);
                    if (at<.0)
                        at+=360.;
                    if(S(ih)>.0)
                    {
                        printf("\nDist: ");
                        modeDistributor(S(ih),y,distValuesE,distValuesF1,distValuesF2,Moda(ih),iox);

                         printf("Azim: ");
                        modeDistributor(at,y,azimutValuesE,azimutValuesF1,azimutValuesF2,Moda(ih),iox);
                        printf("Angle: ");
                        modeDistributor(D2(ih),y, anglePosValuesE, anglePosValuesF1, anglePosValuesF2,Moda(ih),iox);
                          printf("\n\n");
                        switch(ih)
                        {
                        case 0:
                            sprintf(str+90,"%7.1f",S(ih));



                            str[97]=' ';
                            sprintf(str+99,"%6.2f",at);
                            str[105]=' ';
                            sprintf(str+107,"%6.2f",lat);
                            str[113]=' ';
                            sprintf(str+115,"%6.2f",lon);
                            str[121]=' ';
                            break;
                        case 1:
                            sprintf(str+122,"%7.1f",S(ih));


//                            modeDistributor(S(ih),y,distValuesE,distValuesF1,distValuesF2,Moda(ih),iox);
//                            modeDistributor(at,y,azimutValuesE,azimutValuesF1,azimutValuesF2,Moda(ih),iox);
//                            modeDistributor(D2(ih),y, anglePosValuesE, anglePosValuesF1, anglePosValuesF2,Moda(ih),iox);
                            str[129]=' ';
                            sprintf(str+131,"%6.2f",at);
                            str[137]=' ';
                            sprintf(str+139,"%6.2f",lat);
                            str[145]=' ';
                            sprintf(str+147,"%6.2f",lon);
                            str[153]=' ';
                            break;
                        case 2:
                            sprintf(str+155,"%7.1f",S(ih));

//                            modeDistributor(S(ih),y,distValuesE,distValuesF1,distValuesF2,Moda(ih),iox);
//                            modeDistributor(at,y,azimutValuesE,azimutValuesF1,azimutValuesF2,Moda(ih),iox);

//                            modeDistributor(D2(ih),y, anglePosValuesE, anglePosValuesF1, anglePosValuesF2,Moda(ih),iox);
                            str[162]=' ';
                            sprintf(str+163,"%6.2f",at);
                            str[169]=' ';
                            sprintf(str+171,"%6.2f",lat);
                            str[177]=' ';
                            sprintf(str+179,"%6.2f",lon);
                            str[185]=' ';
                            break;
                        }
                    }
                }
                sprintf(str+240,"%s",strModa);
  //              fprintf(outR,"%6.3f %2d %5.2f %5.2f %7.2f %7.2f %5.2f %5.1f %s",fr,iox,D1(0),D2(ih),S(ih),AT(ih),P(i)/300.,104.7-L(ih)-LS(ih),moda(Moda(ih),strModa));
                fprintf(outL,"%d %s ",iox,str);
                fprintf(outL,"\n");
  //              fprintf(outR,"%6.3f %s %d %f\n",fr,strModa,iox,IG);
  }

        }
  y++;

        fgets(str,256,inPel);
    }
  //for(int j=0;j<400;j++) fprintf(outR,"%f %f %f\n",distValuesV[j],azimutValuesV[j],anglePosValuesV[j]);
  //fprintf(outR,"%f ",standardDeviation(distValuesV,500,1062.8));
  if(keyvod==3){
      int ci=0;
    FILE *ff = fopen(fileInName,"rt");
      while(ci!=17){
          ci++;
          fscanf(ff,"%*lg%*lg%*ld%*lg%lg",&TECval);
      }
    fclose(ff);
  }


    printf("\n");

// ------------------------------------------------------------------------------------------------- o wave ---------------------------------------------------------------------
    outProcessedData outprocDataE_0 = {standardDeviation(distValuesE[0],500,trueDistant),standardDeviation(azimutValuesE[0],500,trueAzimut),averageD(distValuesE[0],500),averageD(azimutValuesE[0],500),averageD(anglePosValuesE[0],500)};
    outprocDataE_0.absoluteErrorD = absoluteErrorFunc(outprocDataE_0.averageDist,trueDistant) ;
    outprocDataE_0.absoluteErrorAz = absoluteErrorFunc(outprocDataE_0.averageAzim,trueAzimut) ;
    outprocDataE_0.relativeErrorD = relativeErrorFunc(outprocDataE_0.absoluteErrorD ,trueDistant) ;
    outprocDataE_0.relativeErrorAz = relativeErrorFunc( outprocDataE_0.absoluteErrorAz,trueAzimut) ;

    outProcessedData outprocDataF1_0 = {standardDeviation(distValuesF1[0],500,trueDistant),standardDeviation(azimutValuesF1[0],500,trueAzimut),averageD(distValuesF1[0],500),averageD(azimutValuesF1[0],500),averageD(anglePosValuesF1[0],500),};
    outprocDataF1_0.absoluteErrorD = absoluteErrorFunc(outprocDataF1_0.averageDist,trueDistant);
    outprocDataF1_0.absoluteErrorAz = absoluteErrorFunc(outprocDataF1_0.averageAzim,trueAzimut);
    outprocDataF1_0.relativeErrorD = relativeErrorFunc(outprocDataF1_0.absoluteErrorD ,trueDistant) ;
    outprocDataF1_0.relativeErrorAz = relativeErrorFunc( outprocDataF1_0.absoluteErrorAz,trueAzimut) ;

    outProcessedData outprocDataF2_0 = {standardDeviation(distValuesF2[0],500,trueDistant),standardDeviation(azimutValuesF2[0],500,trueAzimut),averageD(distValuesF2[0],500),averageD(azimutValuesF2[0],500),averageD(anglePosValuesF2[0],500),};
    outprocDataF2_0.absoluteErrorD = absoluteErrorFunc(outprocDataF2_0.averageDist,trueDistant);
    outprocDataF2_0.absoluteErrorAz = absoluteErrorFunc(outprocDataF2_0.averageAzim,trueAzimut);
    outprocDataF2_0.relativeErrorD = relativeErrorFunc(outprocDataF2_0.absoluteErrorD ,trueDistant) ;
    outprocDataF2_0.relativeErrorAz = relativeErrorFunc( outprocDataF2_0.absoluteErrorAz,trueAzimut) ;


//fprintf(outR,"fr         E/f1/f2 iox\tSDD\tSDA\tAD\tAAz\tAAn\tAeD\tAeAz\tReD\tReAz\tIG\tTEC\n");
fprintf(outR,"%f  E   0  %6.3f   %6.3f   %6.3f   %6.3f  %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %e\n",
            fr,
            outprocDataE_0.standardDeviationDist,
            outprocDataE_0.standardDeviationAzim,
            outprocDataE_0.averageDist,
            outprocDataE_0.averageAzim,
            outprocDataE_0.averageAngle,
            outprocDataE_0.absoluteErrorD,
            outprocDataE_0.absoluteErrorAz,
            outprocDataE_0.relativeErrorD,
            outprocDataE_0.relativeErrorAz,
            IG,
            TECval
            );
fprintf(outR,"%f  F1  0  %6.3f   %6.3f   %6.3f   %6.3f  %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %e\n",
            fr,
            outprocDataF1_0.standardDeviationDist,
            outprocDataF1_0.standardDeviationAzim,
            outprocDataF1_0.averageDist,
            outprocDataF1_0.averageAzim,
            outprocDataF1_0.averageAngle,
            outprocDataF1_0.absoluteErrorD,
            outprocDataF1_0.absoluteErrorAz,
            outprocDataF1_0.relativeErrorD,
            outprocDataF1_0.relativeErrorAz,
            IG,
            TECval
            );
fprintf(outR,"%f  F2  0  %6.3f   %6.3f   %6.3f   %6.3f  %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %e\n",
            fr,
            outprocDataF2_0.standardDeviationDist,
            outprocDataF2_0.standardDeviationAzim,
            outprocDataF2_0.averageDist,
            outprocDataF2_0.averageAzim,
            outprocDataF2_0.averageAngle,
            outprocDataF2_0.absoluteErrorD,
            outprocDataF2_0.absoluteErrorAz,
            outprocDataF2_0.relativeErrorD,
            outprocDataF2_0.relativeErrorAz,
            IG,
            TECval

            );




fprintf(outR_OneFileData,"%f  E   0  %6.3f   %6.3f   %6.3f   %6.3f  %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %e\n",
            fr,
            outprocDataE_0.standardDeviationDist,
            outprocDataE_0.standardDeviationAzim,
            outprocDataE_0.averageDist,
            outprocDataE_0.averageAzim,
            outprocDataE_0.averageAngle,
            outprocDataE_0.absoluteErrorD,
            outprocDataE_0.absoluteErrorAz,
            outprocDataE_0.relativeErrorD,
            outprocDataE_0.relativeErrorAz,
            IG,
            TECval
            );
fprintf(outR_OneFileData,"%f  F1  0  %6.3f   %6.3f   %6.3f   %6.3f  %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %e\n",
            fr,
            outprocDataF1_0.standardDeviationDist,
            outprocDataF1_0.standardDeviationAzim,
            outprocDataF1_0.averageDist,
            outprocDataF1_0.averageAzim,
            outprocDataF1_0.averageAngle,
            outprocDataF1_0.absoluteErrorD,
            outprocDataF1_0.absoluteErrorAz,
            outprocDataF1_0.relativeErrorD,
            outprocDataF1_0.relativeErrorAz,
            IG,
            TECval
            );
fprintf(outR_OneFileData,"%f  F2  0  %6.3f   %6.3f   %6.3f   %6.3f  %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %6.3f   %e\n\n\n\n\n",
            fr,
            outprocDataF2_0.standardDeviationDist,
            outprocDataF2_0.standardDeviationAzim,
            outprocDataF2_0.averageDist,
            outprocDataF2_0.averageAzim,
            outprocDataF2_0.averageAngle,
            outprocDataF2_0.absoluteErrorD,
            outprocDataF2_0.absoluteErrorAz,
            outprocDataF2_0.relativeErrorD,
            outprocDataF2_0.relativeErrorAz,
            IG,
            TECval
            );
// ------------------------------------------------------------------------------------------------- x wave ---------------------------------------------------------------------

//    outProcessedData outprocDataE_1 = {standardDeviation(distValuesE[1],500,trueDistant),standardDeviation(azimutValuesE[1],500,trueAzimut),averageD(distValuesE[1],500),averageD(azimutValuesE[1],500),averageD(anglePosValuesE[1],500)};
//    outprocDataE_1.absoluteErrorD = absoluteErrorFunc(outprocDataE_1.averageDist,trueDistant) ;
//    outprocDataE_1.absoluteErrorAz = absoluteErrorFunc(outprocDataE_1.averageAzim,trueAzimut) ;
//    outprocDataE_1.relativeErrorD = relativeErrorFunc(outprocDataE_1.absoluteErrorD ,trueDistant) ;
//    outprocDataE_1.relativeErrorAz = relativeErrorFunc( outprocDataE_1.absoluteErrorAz,trueAzimut) ;

//    outProcessedData outprocDataF1_1 = {standardDeviation(distValuesF1[1],500,trueDistant),standardDeviation(azimutValuesF1[1],500,trueAzimut),averageD(distValuesF1[1],500),averageD(azimutValuesF1[1],500),averageD(anglePosValuesF1[1],500),};
//    outprocDataF1_1.absoluteErrorD = absoluteErrorFunc(outprocDataF1_1.averageDist,trueDistant);
//    outprocDataF1_1.absoluteErrorAz = absoluteErrorFunc(outprocDataF1_1.averageAzim,trueAzimut);
//    outprocDataF1_1.relativeErrorD = relativeErrorFunc(outprocDataF1_1.absoluteErrorD ,trueDistant) ;
//    outprocDataF1_1.relativeErrorAz = relativeErrorFunc( outprocDataF1_1.absoluteErrorAz,trueAzimut) ;

//    outProcessedData outprocDataF2_1 = {standardDeviation(distValuesF2[1],500,trueDistant),standardDeviation(azimutValuesF2[1],500,trueAzimut),averageD(distValuesF2[1],500),averageD(azimutValuesF2[1],500),averageD(anglePosValuesF2[1],500),};
//    outprocDataF2_1.absoluteErrorD = absoluteErrorFunc(outprocDataF2_1.averageDist,trueDistant);
//    outprocDataF2_1.absoluteErrorAz = absoluteErrorFunc(outprocDataF2_1.averageAzim,trueAzimut);
//    outprocDataF2_1.relativeErrorD = relativeErrorFunc(outprocDataF2_1.absoluteErrorD ,trueDistant) ;
//    outprocDataF2_1.relativeErrorAz = relativeErrorFunc( outprocDataF2_1.absoluteErrorAz,trueAzimut) ;





//   fprintf(outR,"%f  E  1  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %e\n",
//            fr,
//            outprocDataE_1.standardDeviationDist,
//            outprocDataE_1.standardDeviationAzim,
//            outprocDataE_1.averageDist,
//            outprocDataE_1.averageAzim,
//            outprocDataE_1.averageAngle,
//            outprocDataE_1.absoluteErrorD,
//            outprocDataE_1.absoluteErrorAz,
//            outprocDataE_1.relativeErrorD,
//            outprocDataE_1.relativeErrorAz,
//            IG,
//            TECval);
//   fprintf(outR,"%f  F1  1  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %e\n",
//            fr,
//            outprocDataF1_1.standardDeviationDist,
//            outprocDataF1_1.standardDeviationAzim,
//            outprocDataF1_1.averageDist,
//            outprocDataF1_1.averageAzim,
//            outprocDataF1_1.averageAngle,
//            outprocDataF1_1.absoluteErrorD,
//            outprocDataF1_1.absoluteErrorAz,
//            outprocDataF1_1.relativeErrorD,
//            outprocDataF1_1.relativeErrorAz,
//            IG,
//            TECval);
//fprintf(outR,"%f  F2  1  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %6.3f  %e\n",
//            fr,
//            outprocDataF2_1.standardDeviationDist,
//            outprocDataF2_1.standardDeviationAzim,
//            outprocDataF2_1.averageDist,
//            outprocDataF2_1.averageAzim,
//            outprocDataF2_1.averageAngle,
//            outprocDataF2_1.absoluteErrorD,
//            outprocDataF2_1.absoluteErrorAz,
//            outprocDataF2_1.relativeErrorD,
//            outprocDataF2_1.relativeErrorAz,
//            IG,
//            TECval);



    outtrs(out,putdat,-1);

  free(putdat);
  dynamic_array_free<double>(distValuesE,2);
  dynamic_array_free<double>(distValuesF1,2);
  dynamic_array_free<double>(distValuesF2,2);

  dynamic_array_free<double>(azimutValuesE,2);
  dynamic_array_free<double>(azimutValuesF1,2);
  dynamic_array_free<double>(azimutValuesF2,2);

  dynamic_array_free<double>(anglePosValuesE,2);
  dynamic_array_free<double>(anglePosValuesF1,2);
  dynamic_array_free<double>(anglePosValuesF2,2);


    if (!spN_H)
        delete spN_H;

    if (outL>0){
        fclose(out);
        fclose(outL);
        fclose(outR);
        fclose(outR_OneFileData);

  }

}

void drawIon(double *fpl, double *hpl, int nf, int npoin, double hMin, double hMax, double fMax)
{
}

void drawTrek(double *sTr, double *hTr, long pointTr)
{
}

void drawInf(char *)
{
}

double standardDeviation(double* arr, int countArrEl, double realVal) {
    double sum = 0;
    int n = 0;
    for (int k = 0; k < countArrEl; k++) {
        if (arr[k] != 0) {
            sum += pow(arr[k]-realVal,2);
            n++;
        }

    }
    if(n==0) n=1;
    return sqrt(sum / n);
}

double standardDeviation(double *arr, int countArrEl){
    double sum = 0;
    for(int k=0;k<countArrEl;k++){

    }
return 0;
}

double absoluteErrorFunc(double measuredVal, double trueVal){
return  abs(measuredVal - trueVal);
}

double relativeErrorFunc( double absoluteError,double trueVal){
return 100*absoluteError/trueVal;
}

void modeDistributor(double val, int en,  double **arrE, double **arrF1,double **arrF2,unsigned long modaVal,int wox){//wox-ordinary or extraordinary waves
    switch (modaVal) {
case 2:
        arrE[wox][en] = val;

        break;
case 3:
        arrF1[wox][en] = val;

        break;
case 4:
        arrF2[wox][en] = val;
        break;
default: break;
    }
}



double averageD(double *arr,int en)
{
double sum = 0;
int count = 0;
for(int k=0;k<en;k++){
    if(arr[k]!=0){

        sum+=arr[k];
        count++;
}
}
    return sum/count;
}


template <typename T>
T** dynamic_array_alloc(int N, int M)
{
    T **A = (T **)malloc(N*sizeof(T *));
    for(int i = 0; i < N; i++) {
        A[i] = (T *)malloc(M*sizeof(T));
        for(int j=0; j<M; j++){
       A[i][j] =0;
        };
    }
    return A;
}


template<typename T>
void  dynamic_array_free(T **arr, int N)
{
   for(int i=0; i < N; i++)
   {


free(arr[i]);


   }
free(arr);
}
