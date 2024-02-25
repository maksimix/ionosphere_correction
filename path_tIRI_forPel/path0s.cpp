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
#include "readDir.h"
#include "dataProcessor.h"

void inions(FILE *in, FILE *out);

void infils(FILE *in, FILE *out);
std::map<int,// 0 - cor(0),nocOR(0),
std::map<int, //1 - freq,
std::map<int, // 3 - hop (1,2,3),
std::map<int, // 4 - mode (0 - E, 1 - F),
std::map<int, // 5 - time (0 -24),
std::map<int, double>>>>>> FreqDataProc; //  6 - param(0 - <dlta>, 1 - sigmaDelta,...)
std::map <int,std::map<int,std::map<int,std::vector<double>>>> S_Map;       // S - for 3-d hour interval (1 int - cor/noCor; 2 int - day , 2 int - hop ; 3 int (mode - E,F1,F2)
std::map <int,std::map<int,std::map<int,std::vector<double>>>> a_Map;      // a - for 3-d hour interval
std::map <int,std::map<int,std::map<int,std::vector<double>>>> delta_Map; // delta - for 3-d hour interval
extern std::map<int, std::vector<double>> TECTimeArr ;// TEC DATA
#define STR1 "\ndelt0=%8.1lg  eps=%8.1lg  ep=%8.1lg  ep1=%8.1lg"

/*==============================================================*/
int noCor_number=0;
int Cor_number=0;
int noCor_numberF=0;
int Cor_numberF=0;
int noCor_numberE=0;
int Cor_numberE=0;
int Param=0;
/*==============================================================*/
double trueDistant;
double trueAzimut ;
int dTimeHour=0;
int dMonth=0;
int dYear =0;
int dDay =0;
/*==============================================================*/


int main(int argc, char *argv[])
{


    int freqsM[3] = {4996,9996,14996}; //freqsMoscow
    int freqsK[2] = {17650};            //freqKashi

    FILE *fileResOut;
    std::map<int,std::vector<int>>  CityData = { {0,{9996}}, {1,{17650}}}; //0 - Moscow, 1 - Kashi
    //std::map<int,std::vector<int>>  CityData = { {0,{4996,9996,14996}}, {1,{9996,17650}}}; //0 - Moscow, 1 - Kashi
    // DIR PATH NAME
    char dirnameFreq[256];

    char **filesName;
    char fileResName[256]; // resultFileName
    char fileResName_Copy[256]; // resultFileName
    int YEARDIR = 2022;
    getcwd(dirnameFreq, sizeof(dirnameFreq)); //name current dir
    int len = strlen(dirnameFreq);


     strcpy(fileResName_Copy, dirnameFreq);

     for(auto City: CityData){

              char fileResName_Copy[256]; // resultFileName
              strcpy(fileResName_Copy, dirnameFreq);
              int lenRes = strlen(fileResName_Copy);
              char dirnameFreqCity[256]; // resultFileName
              strcpy(dirnameFreqCity, dirnameFreq);
              int lenDIRCity = len;


         switch (City.first) {
         case 0:
              printf("Moscow, Russia----------------------------------->\n");
              sprintf(fileResName_Copy+lenRes,"/%d/results_%s/%s.txt",YEARDIR,"Moscow","Moscow");
              sprintf(dirnameFreqCity+lenDIRCity,"/%d/Moscow/",YEARDIR);
              printf("fileResName:%s, dirnameFrq:%s\n",fileResName_Copy,dirnameFreqCity);
              fileResOut = fopen(fileResName_Copy,"w");
//            printf("%s\n",fileResName_Copy);
              printf("fileResName:%s, dirnameFrq:%s\n",fileResName_Copy,dirnameFreqCity);
              trueDistant = 1067;
              trueAzimut = 353.4;
              printf("%lf %lf \n",trueDistant, trueAzimut);
             break;

         case 1:
             printf("Kashi, China----------------------------------->\n");
             sprintf(fileResName_Copy+lenRes,"/%d/results_%s/%s.txt",YEARDIR,"Kashi","Kashi");

             sprintf(dirnameFreqCity+lenDIRCity,"/%d/Kashi/",YEARDIR);
             fileResOut = fopen(fileResName_Copy,"w");
             if (fileResOut == NULL)printf( "Error\n");
//           printf("%s\n",fileResName_Copy);

             trueDistant = 3017.5;
             trueAzimut = 93.97;
             printf("%lf %lf \n",trueDistant, trueAzimut);
             break;
         }

            lenDIRCity = strlen(dirnameFreqCity);
            for(auto freqVectorElem: City.second){

                 sprintf(dirnameFreqCity+lenDIRCity,"%d",freqVectorElem);
                 // sprintf(dirnameFreq+len,"/201904_03_10/%d",freqs[freqElem]);

                 int c = 0;
                       printf("c1: %d\n",c);
                 filesName = readDir(dirnameFreqCity,&c);
                       printf("c2: %d\n",c);
                 int k2 = 1;
                 int TimeCounter = 0;
                 int hop =3;

                 for(int k=0;k<c;k++){

                 sscanf(filesName[k],"%*d_%*d_%*d_%d%*s",&dTimeHour);
                 sscanf(filesName[k],"%*d_%d_%*d_%*d%*s",&dMonth);
                 sscanf(filesName[k],"%*d_%*d_%d_%*d%*s",&dDay);
                 sscanf(filesName[k],"%d_%*d_%*d_%*d%*s",&dYear);

                 dTimeHour = (int)ceil(((double)dTimeHour/100));

                 switch(YEARDIR){

                 case 2019 :
                     TECTimeArr[4] = {38, 38, 50, 58, 71, 84, 93, 98, 104, 113, 114, 109, 105, 101, 93, 91, 89, 86, 83, 78, 75, 72, 71, 65};
                     TECTimeArr[18] = {46, 48, 47, 41, 44, 56, 68, 75, 82, 88, 86, 81, 81, 73, 57, 44, 42, 42, 46, 48, 53, 56, 56, 54};
                     TECTimeArr[19] = {41, 38, 37, 39, 47, 61, 73, 78, 79, 83, 81, 79, 77, 67, 54, 44, 42, 45, 53, 53, 56, 60, 58, 59};
                     TECTimeArr[20] = {52, 46, 41, 40, 50, 66, 76, 80, 82, 86, 85, 81, 81, 74, 62, 50, 48, 52, 59, 56, 57, 61, 59, 57};
                     TECTimeArr[21] = {37, 32, 36, 40, 46, 59, 71, 76, 77, 80, 79, 76, 74, 68, 57, 49, 47, 50, 53, 53, 51, 50, 46, 47};
                     TECTimeArr[22] = {45, 41, 39, 43, 58, 75, 84, 85, 86, 89, 85, 81, 79, 72, 60, 53, 51, 57, 60, 56, 56, 55, 52, 53};
                     TECTimeArr[23] = {49, 42, 41, 43, 51, 65, 79, 86, 91, 95, 92, 84, 81, 72, 58, 51, 48, 50, 52, 48, 52, 55, 54, 54};
                     TECTimeArr[24] = {43, 44, 42, 40, 53, 66, 77, 82, 90, 96, 95, 89, 83, 70, 57, 49, 47, 52, 58, 57, 55, 56, 56, 52};
                     TECTimeArr[25] = {36, 33, 34, 35, 40, 55, 71, 79, 86, 87, 84, 78, 72, 65, 56, 50, 45, 48, 49, 46, 52, 54, 52, 51};
                     TECTimeArr[26] = {43, 34, 35, 34, 44, 58, 72, 74, 81, 81, 79, 78, 76, 69, 55, 44, 40, 46, 51, 47, 49, 50, 48, 45};
                     TECTimeArr[27] = {44, 39, 40, 42, 52, 62, 67, 68, 71, 74, 71, 71, 69, 61, 48, 39, 37, 47, 54, 50, 52, 51, 50, 49};
                     TECTimeArr[28] = {38, 37, 40, 44, 50, 64, 70, 71, 79, 82, 81, 79, 76, 66, 54, 45, 44, 51, 52, 50, 54, 52, 52, 50};

                 break;



                 case 2022:
                     switch (dMonth) {
                     case 11:

                         TECTimeArr[21] = {59, 52, 60, 71, 106, 151, 188, 213, 234, 241, 245, 233, 215, 184, 138, 91, 62, 61, 62, 71, 79, 77, 75, 79};
                         TECTimeArr[22] = {66, 62, 72, 70, 98, 146, 186, 214, 237, 245, 242, 231, 227, 197, 144, 92, 69, 72, 76, 78, 78, 77, 84, 88};
                         TECTimeArr[23] = {60, 56, 53, 63, 82, 120, 155, 178, 200, 210, 208, 193, 178, 154, 116, 75, 54, 51, 59, 72, 75, 79, 81, 84};
                         TECTimeArr[24] = {66, 64, 72, 71, 83, 122, 157, 188, 214, 230, 224, 204, 193, 157, 115, 77, 53, 50, 57, 68, 73, 77, 85, 88};
                         TECTimeArr[25] = {68, 55, 60, 64, 83, 114, 155, 185, 211, 223, 224, 212, 195, 162, 121, 83, 59, 55, 59, 71, 84, 85, 82, 90};
                         TECTimeArr[26] = {63, 54, 58, 70, 93, 128, 170, 201, 227, 238, 239, 233, 216, 181, 134, 96, 73, 68, 69, 71, 72, 69, 66, 73};
                         TECTimeArr[27] = {53, 48, 57, 66, 86, 127, 175, 221, 256, 259, 247, 224, 207, 174, 132, 95, 79, 75, 75, 80, 85, 82, 79, 83};
                         TECTimeArr[28] = {60, 67, 71, 75, 100, 135, 174, 209, 232, 235, 225, 215, 202, 169, 129, 88, 66, 63, 68, 71, 70, 72, 78, 89};
                         TECTimeArr[29] = {39, 41, 60, 70, 90, 125, 164, 196, 214, 223, 227, 223, 210, 178, 134, 90, 62, 58, 65, 66, 68, 63, 62, 67};
                     break;



                     case 12:

                         TECTimeArr[20] =  {82, 74, 79, 89, 92, 108, 140, 193, 235, 233, 232, 237, 231, 203, 166, 127, 87, 71, 79, 82, 83, 90, 95, 95};//354
                         TECTimeArr[21] =  {81, 57, 62, 68, 83, 103, 140, 193, 235, 242, 231, 226, 226, 201, 162, 119, 92, 81, 90, 87, 76, 81, 88, 84};//355
                         TECTimeArr[22] =  {50, 51, 66, 75, 78, 88, 124, 180, 225, 233, 229, 221, 212, 185, 148, 113, 86, 77, 77, 70, 70, 70, 69, 69};//356
                         TECTimeArr[23] =  {55, 46, 53, 71, 78, 91, 123, 176, 217, 226, 217, 213, 214, 188, 154, 120, 79, 68, 71, 69, 69, 73, 77, 75};
                         TECTimeArr[24] =  {48, 42, 44, 54, 76, 87, 114, 164, 220, 232, 228, 222, 206, 176, 146, 108, 75, 61, 58, 57, 56, 57, 62, 71};
                         TECTimeArr[25] =  {49, 50, 60, 61, 66, 84, 111, 160, 204, 219, 204, 196, 189, 165, 130, 91, 58, 52, 51, 51, 56, 60, 60, 58};
                         TECTimeArr[26] =  {59, 55, 51, 51, 56, 76, 113, 169, 211, 222, 205, 196, 187, 166, 124, 87, 58, 46, 48, 49, 48, 51, 51, 51}; //360*/
                         break;


                        }


                     break;


                 default:
                     break;





                 }





                    if(
              //(City.first == 1    && freqVectorElem ==17650  && ( dTimeHour == 6 || dTimeHour == 7   || dTimeHour == 8   ))
                //   ||
                     // && (dTimeHour == 12 || dTimeHour ==13|| dTimeHour == 14 || dTimeHour == 15 || dTimeHour == 16 )
                   ( City.first == 0   &&  (dTimeHour == 12 || dTimeHour == 13 || dTimeHour == 14 ))
                      )
              {
                  printf("%s\n",filesName[k]);

                 TimeCounter++;
                 printf("DAY:%d, MONTH:%d, HOUR:%d, TEC:%lf YEAR: %d\n ",dDay, dMonth, dTimeHour,TECTimeArr[dDay],dYear);
                 printf("%s\n",dirnameFreqCity);
                 printf("%s\n",filesName[k]);


                 printf("HOP: %d City:%d\n",hop,City.first);

                 char* ch1noCor = getInputFile(0,filesName[k],freqVectorElem,hop,City.first, dDay, dMonth,dYear); // files

                 char*  ch1 = getInputFile(1,filesName[k],freqVectorElem,hop,City.first, dDay,dMonth,dYear);

                 resultMain(ch1,filesName[k],1,freqVectorElem,hop); //Calculate data  with cor
                 printf("\n\n---------------------------------------------------------------\n");
                 free(ch1);
                 resultMain(ch1noCor,filesName[k],0,freqVectorElem,hop);//Calculate data  without cor
                 free(ch1noCor);

                if(TimeCounter == 3 ){




                 }


             }


             }
                 printf("END FOLDER FREQ:%d\n-----------------------------------------------------------------///",freqVectorElem);
                 printf("_____%d__________\n",dTimeHour);
                 printf("_______________NOCOR\n");
                 printf("1E data count:%d\n",S_Map[0][0][0].size());
                 printf("1F1 data count:%d\n",S_Map[0][0][1].size());
                 printf("1F2 data count:%d\n",S_Map[0][0][2].size());

                 printf("2E data count:%d\n",S_Map[0][1][0].size());
                 printf("2F1 data count:%d\n",S_Map[0][1][1].size());
                 printf("2F2 data count:%d\n",S_Map[0][1][2].size());

                 printf("3E data count:%d\n",S_Map[0][2][0].size());
                 printf("3F1 data count:%d\n",S_Map[0][2][1].size());
                 printf("3F2 data count:%d\n",S_Map[0][2][2].size());
                 printf("\n\n\n\n_______________COR\n");



                 printf("1E data count:%d\n",S_Map[1][0][0].size());
                 printf("1F1 data count:%d\n",S_Map[1][0][1].size());
                 printf("1F2 data count:%d\n",S_Map[1][0][2].size());

                 printf("2E data count:%d\n",S_Map[1][1][0].size());
                 printf("2F1 data count:%d\n",S_Map[1][1][1].size());
                 printf("2F2 data count:%d\n",S_Map[1][1][2].size());

                 printf("3E data count:%d\n",S_Map[1][2][0].size());
                 printf("3F1 data count:%d\n",S_Map[1][2][1].size());
                 printf("3F2 data count:%d\n-----------------------------------------------------------------///",S_Map[1][2][2].size());
                Data_Processing(FreqDataProc,S_Map,a_Map,delta_Map,freqVectorElem,0,12,trueDistant,trueAzimut);
                Data_Processing(FreqDataProc,S_Map,a_Map,delta_Map,freqVectorElem,1,12,trueDistant,trueAzimut);
                printf("END FOLDER FREQ:%d\n-----------------------------------------------------------------///\n",freqVectorElem);
                dynamic_array_free(filesName, c);

                S_Map.clear();
                delta_Map.clear();
                a_Map.clear() ;
             }

            WriteDataInFile(FreqDataProc,fileResOut);
            FreqDataProc.clear();
            printf("END\n");
         }



     fclose(fileResOut);
     printf("TEC: %d, noTEC: %d", Cor_number,noCor_number   );
return 0;
     }




 /* path0s */
void resultMain( char*fileInName, char *filePelName, int cor, int freq,int _hop){
    Param++;
    //cor = 1 - TEC, cor = 0 - noCor
    if(cor){
        printf("TEC\n");
    }
    printf("%s\n",fileInName);
    printf("RESULTFUNC -  %s\n",filePelName);
    double alfa,d0,delt0,eps,ep,ep1,
           f[500],d[500],a[500],t[500];
    double lat0,lon0,
           w,W,ig,IG,ames,ptr,b,rmax;
    long   it1,it2,it3,hou1,hou2,hou3,min1,min2,min3,
           sek1,sek2,sek3;
    double t1,t2,t3,time,tmre,dt,
           time1,time2,dtime;


  double TECval=0;
  double e=.0625;
  int n,io,ix,ihop,kolf,iyear;
  long keyvod, keyMod, keyEs, keypri;
  int i,j,id;

  PUTDAT *putdat;

  FILE *in,*out,*outL,*outR, *outR_OneFileData, *out_not_filtered;
  FILE *outFIle_1hop,*outFIle_2hop, *outFIle_3hop;

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
    char name_NotFiltered[256];
    char name_1hop[256];
    char name_2hop[256];
    char name_3hop[256];

    //RESULT FILES
    sprintf(name,"results/out/%d/%d_%d_%s_",freq,freq,_hop,filePelName);
    sprintf(nameR,"results/outR/%d/%d_%d_%s",freq,freq,_hop,filePelName);
    sprintf(nameR_OneFileData,"results/outR_OneFileData/%d/%d_%d_%s",freq,freq,_hop,filePelName);
    sprintf(name_NotFiltered,"%d/results_Moscow/%d/%d_%d_%s",dYear,freq,freq,_hop,filePelName);
    sprintf(name_1hop,"%d/results_Moscow/%d/hop1/%d_%d_%s",dYear,freq,freq,1,filePelName);
    sprintf(name_2hop,"%d/results_Moscow/%d/hop2/%d_%d_%s",dYear,freq,freq,2,filePelName);
    sprintf(name_3hop,"%d/results_Moscow/%d/hop3/%d_%d_%s",dYear,freq,freq,3,filePelName);



    sprintf(nameL,"results/outL/%d/%d_%d_%s",freq,freq,_hop, filePelName);
    int strLen=strlen(name);
    int strLenR=strlen(nameR);
    int strLenR_OneFileData=strlen(nameR_OneFileData);
    int strLen_NotFiltered=strlen(name_NotFiltered);
    int strLen_name_1hop=strlen(name_1hop);

    int strLenL=strlen(nameL);
    switch (cor) {
    case 0: {
        //file without TEC correction
        sprintf(name+strLen-5,"_noCor.txt");
        sprintf(nameL+strLenL-5,"_noCor_L.txt");
        sprintf(nameR+strLenR-5,"_noCor_R.txt");
        sprintf(name_NotFiltered+strLen_NotFiltered-4,"_noCor.txt");
        sprintf(name_1hop+strLen_name_1hop-4,"_noCor.txt");
        sprintf(name_2hop+strLen_name_1hop-4,"_noCor.txt");
        sprintf(name_3hop+strLen_name_1hop-4,"_noCor.txt");
        printf("%s\n",name_1hop);
           printf("%s\n",name_2hop);
              printf("%s\n",name_3hop);
        break;
    };
    case 1:{
        //file with TEC correction
        sprintf(name+strLen-5,"_TEC.txt");
        sprintf(nameL+strLenL-5,"_TEC_L.txt");
        sprintf(nameR+strLenR-5,"_TEC_R.txt");
        sprintf(name_NotFiltered+strLen_NotFiltered-4,"_TEC.txt");
        break;
    };
    default: break;
    }

    outL=fopen(nameL,"wt");
    if (outL==NULL)
      {
        printf("Input File:%s error open\n",nameL);
        exit(EXIT_FAILURE);
      }
    outR = fopen(nameR,"wt");
    if (outR==NULL)
      {
        printf("Input File:%s error open\n",nameR);
        exit(EXIT_FAILURE);
      }
    outR_OneFileData = fopen(nameR_OneFileData,"a");
    if (outR_OneFileData==NULL)
      {
        printf("Input File:%s error open\n",nameR_OneFileData);
        exit(EXIT_FAILURE);
      }
    out_not_filtered = fopen(name_NotFiltered,"wt");
    if (out_not_filtered==NULL)
      {
        printf("Input File:%s error open\n",name_NotFiltered);
        exit(EXIT_FAILURE);
      }



    out=fopen(name,"wt");
    if (out==NULL)
      {
        printf("Input File:%s error open\n",name);
        exit(EXIT_FAILURE);
      }
    if (out==NULL)
      {
        printf("Output File:%s error open\n",filePelName);
        printf("%s\n",name);
        exit(EXIT_FAILURE);
      }

//FILLING THE REQUIRED VARIABLES WITH VALUES FROM THE INPUT FILE

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


    hou1=it1/10000l;
    hou2=it2/10000l;
    hou3=it3/10000l;
    min1=(it1-hou1*10000l)/100l;
    min2=(it2-hou2*10000l)/100l;
    min3=(it3-hou3*10000l)/100l;
    sek1=it1-hou1*10000l-min1*100l;
    sek2=it2-hou2*10000l-min2*100l;
    sek3=it3-hou3*10000l-min3*100l;

    t1=hou1*3600.+min1*60.+sek1;
    t2=hou2*3600.+min2*60.+sek2;
    t3=hou3*3600.+min3*60.+sek3;
    dt=t3;

    if (t1>t2)
      t1-=86400.;


    infils(in,out);

    W=w;
    IG=ig;
    inions(in,out,iyear,ames,W,IG,rmax,keyvod,keyMod,keyEs,t1,t2,dt);



    fscanf(in,"%d",&ihop);
    printf("%d===================================\n",ihop);


    fscanf(in,"%d%d",&io,&ix);

    fscanf(in,"%d",&n);

    fprintf(out,"\n\nNumber diff. equation:%2d\n",n);

    putdat=(PUTDAT*)malloc(sizeof(PUTDAT)*ihop);

    char namePel[256],str[512],str2[512];
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

        tim=t;


        sscanf(str+25,"%lg",&fr);
        sscanf(str+77,"%lg",&d0);
        sscanf(str+84,"%lg",&alfa);


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

        //PARAMETR CALCULATOR
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
               // printf("ihop                          %d\n",ihop);
                for(int ih=0; ih<ihop; ih++)//ih
                {
                    double at=AT(ih);
                    double lat=90.-Y(ih);
                    double lon=X(ih);

                    moda(Moda(ih),strModa);
                    if (at<.0) at+=360.;
                    if (ZOTR(ih)<=.0)
                                   {
                                       S(ih)=at=lat=lon=.0;
                                   }
                    if(S(ih)>=.0)
                    {
                        if(cor){   Cor_number++;
                        }
                        else noCor_number++;

//DATA FILTERING: THE DISTANCE SHOULD BE IN THE RIGHT RANGE, AS SHOULD THE AZIMUTH OF THE RADIATIOIN SOURCE
    if(S(ih)<trueDistant*1.2 &&S(ih)>trueDistant*0.8 && at > (trueAzimut -10) && at < (trueAzimut + 10) ){

//MODE FILTERING: EACH MODE OF RADIO WAVE PROPAGATION IN THE IONOSPHERE HAS ITS OWN INDEX
    if(Moda(ih) == 222 || Moda(ih) == 22 || Moda(ih) == 2 ){
//FILL IN THE PLACE ANGLE? AZIMUTH AND DISTANCE ARRAYS WITH DATA
   S_Map[cor][ih][0].push_back(S(ih));
   delta_Map[cor][ih][0].push_back(D1(ih));
   a_Map[cor][ih][0].push_back(at);
//    fprintf(out_not_filtered,"%7.1f %6.2f %6.2f %s\n",S(ih),at,D2(ih),strModa);

};
//MODE FILTERING: EACH MODE OF RADIO WAVE PROPAGATION IN THE IONOSPHERE HAS ITS OWN INDEX
    if(  Moda (ih) == 333 ||  Moda (ih) == 33 ||  Moda (ih) == 3 || Moda(ih) == 44 || Moda(ih) == 444 || Moda(ih) == 4 ){
//FILL IN THE PLACE ANGLE? AZIMUTH AND DISTANCE ARRAYS WITH DATA
    S_Map[cor][ih][1].push_back(S(ih));
    delta_Map[cor][ih][1].push_back(D1(ih));
    a_Map[cor][ih][1].push_back(at);
  //  fprintf(out_not_filtered,"%7.1f %6.2f %6.2f %s\n",S(ih),at,D2(ih),strModa);
};

   }



// IH - NUMBER OF JUMPS
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
        str[162]=' ';
        sprintf(str+163,"%6.2f",at);
        str[169]=' ';
        sprintf(str+171,"%6.2f",lat);
        str[177]=' ';
        sprintf(str+179,"%6.2f",lon);
        str[185]=' ';

        break;
    }

//}


}

//FILE OUTPUT
sprintf(str+240,"%s",strModa);
fprintf(out_not_filtered," %5.2f %5.2f %7.2f %7.2f %s\n",D1(0),D2(ih),S(ih),AT(ih),P(i)/300.,104.7-L(ih)-LS(ih),moda(Moda(ih),strModa));
fprintf(outL,"%d %s ",iox,str);
fprintf(outL,"\n");


}



  }


        }
  y++;

        fgets(str,256,inPel);
    }

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







    outtrs(out,putdat,-1);

    free(putdat);


    if (!spN_H)
        delete spN_H;

    if (outL>0){
        fclose(out);
        fclose(outL);
        fclose(outR);
        fclose(outR_OneFileData);


  }



}








void modeDistributor(double val, int en,  double **arrE, double **arrF1,double **arrF2,double **arr,unsigned long modaVal,int wox){
    //  wox-ordinary or extraordinary waves
    //  en -
    //  arrE,arrF1,arrF2 - array of data
    //  modaVal 2 - E, 3 - F1, 4 - F2
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






