/***************************************************************/
/*                                                             */
/* ???????? ???????, ???????????? ??????????? ??????? ???????- */
/* ??? ? ?????????? ???????? ?????????????-????????????        */
/* ??????????????? ?????????.                                  */
/*                                                             */
/*VGG                                                          */
/***************************************************************/

#pragma once
#include "paths.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>


//#include "dataProcessor.h"

void inions(FILE* in, FILE* out);

void infils(FILE* in, FILE* out);
std::map<int,// 0 - cor(0),nocOR(0),
  std::map<int, //1 - freq,
  std::map<int, // 3 - hop (1,2,3),
  std::map<int, // 4 - mode (0 - E, 1 - F),
  std::map<int, // 5 - time (0 -24),
  std::map<int, double>>>>>> FreqDataProc; //  6 - param(0 - <dlta>, 1 - sigmaDelta,...)
std::map <int, std::map<int, std::map<int, std::vector<double>>>> S_Map;       // S - for 3-d hour interval (1 int - cor/noCor; 2 int - day , 2 int - hop ; 3 int (mode - E,F1,F2)
std::map <int, std::map<int, std::map<int, std::vector<double>>>> a_Map;      // a - for 3-d hour interval
std::map <int, std::map<int, std::map<int, std::vector<double>>>> delta_Map; // delta - for 3-d hour interval
extern std::map<int, std::vector<double>> TECTimeArr;// TEC DATA
#define STR1 "\ndelt0=%8.1lg  eps=%8.1lg  ep=%8.1lg  ep1=%8.1lg"

/*===;===========================================================*/
int noCor_number = 0;
int Cor_number = 0;
int noCor_numberF = 0;
int Cor_numberF = 0;
int noCor_numberE = 0;
int Cor_numberE = 0;
int Param = 0;
/*==============================================================*/
double trueDistant;
double trueAzimut;
int dTimeHour = 0;
int dMonth = 0;
int dYear = 0;
int dDay = 0;
/*==============================================================*/

void resultMain(std::string fileInName, std::string filePelName, int cor, int freq, int _hop) {
  Param++;
  //cor = 1 - TEC, cor = 0 - noCor
  if (cor) {
    printf("TEC\n");
  }
  printf("%s\n", fileInName.c_str());
  printf("RESULTFUNC -  %s\n", filePelName.c_str());
  double alfa, d0, delt0, eps, ep, ep1,
    f[500], d[500], a[500], t[500];
  double lat0, lon0,
    w, W, ig, IG, ames, ptr, b, rmax;
  long   it1, it2, it3, hou1, hou2, hou3, min1, min2, min3,
    sek1, sek2, sek3;
  double t1, t2, t3, time, tmre, dt,
    time1, time2, dtime;


  double TECval = 0;
  double e = .0625;
  int n, io, ix, ihop, kolf, iyear;
  long keyvod, keyMod, keyEs, keypri;
  int i, j, id;

  PUTDAT* putdat;

  FILE* in, * out, * outL, * outR, * outR_OneFileData, * out_not_filtered;
  FILE* outFIle_1hop, * outFIle_2hop, * outFIle_3hop;

  keyEs = 0;

  outL = 0;

  in = fopen(fileInName.c_str(), "rt");


  if (in == NULL)
  {
    printf("Input File:%s error open\n", fileInName.c_str());
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
  sprintf(name, "results/out/%d/%d_%d_%s_", freq, freq, _hop, filePelName.c_str());
  sprintf(nameR, "results/outR/%d/%d_%d_%s", freq, freq, _hop, filePelName.c_str());
  sprintf(nameR_OneFileData, "results/outR_OneFileData/%d/%d_%d_%s", freq, freq, _hop, filePelName.c_str());
  sprintf(name_NotFiltered, "%d/results_Germany/%d/%d_%d_%s", dYear, freq, freq, _hop, filePelName.c_str());
  sprintf(name_1hop, "%d/results_Germany/%d/%d_%d_%s", dYear, freq, freq, 1, filePelName.c_str());
  sprintf(name_2hop, "%d/results_Germany/%d/%d_%d_%s", dYear, freq, freq, 2, filePelName.c_str());
  sprintf(name_3hop, "%d/results_Germany/%d/%d_%d_%s", dYear, freq, freq, 3, filePelName.c_str());



  sprintf(nameL, "results/outL/%d/%d_%d_%s", freq, freq, _hop, filePelName.c_str());
  int strLen = strlen(name);
  int strLenR = strlen(nameR);
  int strLenR_OneFileData = strlen(nameR_OneFileData);
  int strLen_NotFiltered = strlen(name_NotFiltered);
  int strLen_name_1hop = strlen(name_1hop);

  int strLenL = strlen(nameL);
  switch (cor) {
  case 0: {
    //file without TEC correction
    sprintf(name + strLen - 5, "_noCor.txt");
    sprintf(nameL + strLenL - 5, "_noCor_L.txt");
    sprintf(nameR + strLenR - 5, "_noCor_R.txt");
    sprintf(name_NotFiltered + strLen_NotFiltered - 4, "_noCor.txt");
    sprintf(name_1hop + strLen_name_1hop - 4, "_noCor.txt");
    sprintf(name_2hop + strLen_name_1hop - 4, "_noCor.txt");
    sprintf(name_3hop + strLen_name_1hop - 4, "_noCor.txt");
    printf("%s\n", name_1hop);
    printf("%s\n", name_2hop);
    printf("%s\n", name_3hop);
    break;
  };
  case 1: {
    //file with TEC correction
    sprintf(name + strLen - 5, "_TEC.txt");
    sprintf(nameL + strLenL - 5, "_TEC_L.txt");
    sprintf(nameR + strLenR - 5, "_TEC_R.txt");
    sprintf(name_NotFiltered + strLen_NotFiltered - 4, "_TEC.txt");
    break;
  };
  default: break;
  }

  outL = fopen(nameL, "wt");
  if (outL == NULL)
  {
    printf("Input File:%s error open\n", nameL);
    exit(EXIT_FAILURE);
  }
  outR = fopen(nameR, "wt");
  if (outR == NULL)
  {
    printf("Input File:%s error open\n", nameR);
    exit(EXIT_FAILURE);
  }
  outR_OneFileData = fopen(nameR_OneFileData, "a");
  if (outR_OneFileData == NULL)
  {
    printf("Input File:%s error open\n", nameR_OneFileData);
    exit(EXIT_FAILURE);
  }
  out_not_filtered = fopen(name_NotFiltered, "wt");
  if (out_not_filtered == NULL)
  {
    printf("Input File:%s error open\n", name_NotFiltered);
    exit(EXIT_FAILURE);
  }



  out = fopen(name, "wt");
  if (out == NULL)
  {
    printf("Input File:%s error open\n", name);
    exit(EXIT_FAILURE);
  }
  if (out == NULL)
  {
    printf("Output File:%s error open\n", filePelName.c_str());
    printf("%s\n", name);
    exit(EXIT_FAILURE);
  }

  //FILLING THE REQUIRED VARIABLES WITH VALUES FROM THE INPUT FILE

  fscanf(in, "%lg%lg%lg%lg%lg", &delt0, &eps, &ep, &ep1, &rmax);
  fprintf(out, STR1, delt0, eps, ep, ep1);
  fscanf(in, "%ld%ld%ld%ld%ld%ld%ld", &keyvod, &keynu, &keyMod, &keyl2, &keyEs, &keypri, &keytr);

  RMax = rmax;
  e = e * eps;
  z0 = z1 = R0;
  rmax *= .01;

  fscanf(in, "%lg%lg%lg%lg%ld%lg%lg%lg%lg%lg",
    &lon0, &lat0, &z0, &z1, &iyear, &ames, &w, &ig, &ptr, &b);

  fscanf(in, "%lg%lg%lg", &sMinIon, &sMaxIon, &alfIon);

  z0 = .01 * z0 + R0;
  z1 = .01 * z1 + R0;
  fi0 = lon0 * RAD;
  teta0 = (90. - lat0) * RAD;

  lon0 *= RAD;
  lat0 *= RAD;


  fscanf(in, "%ld%ld%ld", &it1, &it2, &it3);


  hou1 = it1 / 10000l;
  hou2 = it2 / 10000l;
  hou3 = it3 / 10000l;
  min1 = (it1 - hou1 * 10000l) / 100l;
  min2 = (it2 - hou2 * 10000l) / 100l;
  min3 = (it3 - hou3 * 10000l) / 100l;
  sek1 = it1 - hou1 * 10000l - min1 * 100l;
  sek2 = it2 - hou2 * 10000l - min2 * 100l;
  sek3 = it3 - hou3 * 10000l - min3 * 100l;

  t1 = hou1 * 3600. + min1 * 60. + sek1;
  t2 = hou2 * 3600. + min2 * 60. + sek2;
  t3 = hou3 * 3600. + min3 * 60. + sek3;
  dt = t3;

  if (t1 > t2)
    t1 -= 86400.;


  infils(in, out);

  W = w;
  IG = ig;
  inions(in, out, iyear, ames, W, IG, rmax, keyvod, keyMod, keyEs, t1, t2, dt);



  fscanf(in, "%d", &ihop);
  printf("%d===================================\n", ihop);


  fscanf(in, "%d%d", &io, &ix);

  fscanf(in, "%d", &n);

  fprintf(out, "\n\nNumber diff. equation:%2d\n", n);

  putdat = (PUTDAT*)malloc(sizeof(PUTDAT) * ihop);

  char namePel[256], str[512], str2[512];
  FILE* inPel;

  fscanf(in, "%s", namePel);
  inPel = fopen(namePel, "rt");
  if (!inPel)
  {
    printf("Error open File:%s\n", namePel);
    printf("%s\t\t%s\n", fileInName.c_str(), filePelName.c_str());
    exit(1);
  }


  int count = -1;
  int y = 0;
  while (!feof(inPel))
  {
    int rab = 0;
    while (!feof(inPel) && !rab)
    {
      fgets(str, 256, inPel);
      if (feof(inPel))
        break;
      sscanf(str, "%d", &rab);
    }
    if (feof(inPel))
      break;
    int hh, mm;
    double ss, t;
    sscanf(str + 11, "%d", &hh);
    sscanf(str + 14, "%d", &mm);
    sscanf(str + 17, "%lg", &ss);
    t = hh * 3600. + mm * 60. + ss;

    if (iri_NTime > 1)
    {
      int i = 0;
      if (t >= iri_tTime[0] && t <= iri_tTime[iri_NTime - 1])
      {
        int n = iri_NTime - 1;
        for (int j = 0; j < n; j++)
        {
          if (t >= iri_tTime[j] && t < iri_tTime[j + 1])
          {
            i = j;
            break;
          }
        }
      }

      if (t >= iri_tTime[iri_NTime - 1])
        i = iri_NTime - 2;
      iri_3dbase = iri_4dbase[i];
      iri_3dbase2 = iri_4dbase[i + 1];
      if (count != i)
      {
        // //  printf("\niri_NTime=%d  iIon=%d\n",iri_NTime,i);
        prion(out, lat0, lon0, lat0, lon0, tim, W, IG, keypri, keyEs);
        count = i;
      }
    }

    tim = t;


    sscanf(str + 25, "%lg", &fr);
    sscanf(str + 77, "%lg", &d0);
    sscanf(str + 84, "%lg", &alfa);


    fr2 = fr * fr;
    u1 = fh / fr;
    u = u1 * u1;

    if (t < .0)
      time = t + 86400.;
    else
      time = t;
    long hou = (long)(time / 3600.);
    long min = (long)((time - hou * 3600.) / 60.);
    long sek = (long)(time - hou * 3600. - min * 60.);
    long msek = (long)((time - hou * 3600. - min * 60. - sek) * 100.);
    while (hou > 24) hou -= 24;

    time /= 3600.;
    d0 *= RAD;
    alfa *= RAD;

    //PARAMETR CALCULATOR
    for (iox = io; iox <= ix; iox++)
    {
      for (i = 0; i < ihop; i++)
        IOX(i) = iox;
      for (i = 0; i < ihop; i++)
        FR(i) = fr;
      for (i = 0; i < ihop; i++)
        TIME(i) = tim;

      treks(d0, alfa, ihop, n, delt0, eps, ep, ep1, e, putdat);

      outtrs(out, putdat, ihop);

      if (outL > 0)
      {
        char strModa[17];
        // printf("ihop                          %d\n",ihop);
        for (int ih = 0; ih < ihop; ih++)//ih
        {
          double at = AT(ih);
          double lat = 90. - Y(ih);
          double lon = X(ih);

          moda(Moda(ih), strModa);
          if (at < .0) at += 360.;
          if (ZOTR(ih) <= .0)
          {
            S(ih) = at = lat = lon = .0;
          }
          if (S(ih) > .0)
          {
              printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
              return ;
            if (cor) {
              Cor_number++;
            }
            else noCor_number++;

            //DATA FILTERING: THE DISTANCE SHOULD BE IN THE RIGHT RANGE, AS SHOULD THE AZIMUTH OF THE RADIATIOIN SOURCE
            if (S(ih) < trueDistant * 1.2 && S(ih) > trueDistant * 0.8 && at > (trueAzimut - 10) && at < (trueAzimut + 10)) {

              //MODE FILTERING: EACH MODE OF RADIO WAVE PROPAGATION IN THE IONOSPHERE HAS ITS OWN INDEX
              if (Moda(ih) == 222 || Moda(ih) == 22 || Moda(ih) == 2) {
                //FILL IN THE PLACE ANGLE? AZIMUTH AND DISTANCE ARRAYS WITH DATA
                S_Map[cor][ih][0].push_back(S(ih));
                delta_Map[cor][ih][0].push_back(D1(ih));
                a_Map[cor][ih][0].push_back(at);
                //    fprintf(out_not_filtered,"%7.1f %6.2f %6.2f %s\n",S(ih),at,D2(ih),strModa);

              };
              //MODE FILTERING: EACH MODE OF RADIO WAVE PROPAGATION IN THE IONOSPHERE HAS ITS OWN INDEX
              if (Moda(ih) == 333 || Moda(ih) == 33 || Moda(ih) == 3 || Moda(ih) == 44 || Moda(ih) == 444 || Moda(ih) == 4) {
                //FILL IN THE PLACE ANGLE? AZIMUTH AND DISTANCE ARRAYS WITH DATA
                S_Map[cor][ih][1].push_back(S(ih));
                delta_Map[cor][ih][1].push_back(D1(ih));
                a_Map[cor][ih][1].push_back(at);
                //  fprintf(out_not_filtered,"%7.1f %6.2f %6.2f %s\n",S(ih),at,D2(ih),strModa);
              };

            }



            // IH - NUMBER OF JUMPS
            switch (ih)
            {
            case 0:

              sprintf(str + 90, "%7.1f", S(ih));
              str[97] = ' ';
              sprintf(str + 99, "%6.2f", at);
              str[105] = ' ';
              sprintf(str + 107, "%6.2f", lat);
              str[113] = ' ';
              sprintf(str + 115, "%6.2f", lon);
              str[121] = ' ';

              break;
            case 1:

              sprintf(str + 122, "%7.1f", S(ih));
              str[129] = ' ';
              sprintf(str + 131, "%6.2f", at);
              str[137] = ' ';
              sprintf(str + 139, "%6.2f", lat);
              str[145] = ' ';
              sprintf(str + 147, "%6.2f", lon);
              str[153] = ' ';

              break;
            case 2:

              sprintf(str + 155, "%7.1f", S(ih));
              str[162] = ' ';
              sprintf(str + 163, "%6.2f", at);
              str[169] = ' ';
              sprintf(str + 171, "%6.2f", lat);
              str[177] = ' ';
              sprintf(str + 179, "%6.2f", lon);
              str[185] = ' ';

              break;
            }



          }

          //FILE OUTPUT
          sprintf(str + 240, "%s", strModa);
          fprintf(out_not_filtered, " %5.2f %5.2f %7.2f %7.2f %s\n", D1(0), D2(ih), S(ih), AT(ih), P(i) / 300., 104.7 - L(ih) - LS(ih), moda(Moda(ih), strModa));
          fprintf(outL, "%d %s ", iox, str);
          fprintf(outL, "\n");
        }
      }
    }
    y++;

    fgets(str, 256, inPel);
  }

  if (keyvod == 3) {
    int ci = 0;
    FILE* ff = fopen(fileInName.c_str(), "rt");
    while (ci != 17) {
      ci++;
      fscanf(ff, "%*lg%*lg%*ld%*lg%lg", &TECval);
    }
    fclose(ff);
  }

  printf("\n");

  outtrs(out, putdat, -1);

  free(putdat);

  if (!spN_H)
    delete spN_H;

  if (outL > 0) {
    fclose(out);
    fclose(outL);
    fclose(outR);
    fclose(outR_OneFileData);
  }
}

/* path0s */
int main(int argc, char* argv[])
{

  trueDistant = 2320;
  trueAzimut = 276.18;
  int freqsM[3] = { 4996,9996,14996 }; //freqsMoscow
  int freqCity[2] = { 9996,13996 }; // freqsGermany

  FILE* fileResOut;

  char dirnameFreq[256];
  char** filesName;
  char fileResName[256]; // resultFileName
  char fileResName_Copy[256]; // resultFileName

  std::vector<std::string> files_name_vector;
  std::vector<std::string> freqs;
  //49.361700, 8.322800
  int YEARDIR = 2023;
  getcwd(dirnameFreq, sizeof(dirnameFreq)); //name current dir

  int len = strlen(dirnameFreq);
  strcpy(fileResName_Copy, dirnameFreq);

  strcpy(fileResName_Copy, dirnameFreq);
  int lenRes = strlen(fileResName_Copy);

  char dirnameFreqCity[256]; // resultFileName
  strcpy(dirnameFreqCity, dirnameFreq);
  int lenDIRCity = len;

  // CITY PROPETY

  sprintf(fileResName_Copy + lenRes, "/%d/results_%s/%s.txt", YEARDIR, "Germany", "Germany");
  sprintf(dirnameFreqCity + lenDIRCity, "/%d/Germany/", YEARDIR); //dir data .log


  DIR* dir = opendir(dirnameFreqCity);
  if (dir != nullptr) {
    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
      if (entry->d_type == DT_DIR && (std::string)entry->d_name != "." && (std::string)entry->d_name != "..") {
        freqs.push_back(entry->d_name);
      }
    }
    closedir(dir);
  }


  fileResOut = fopen(fileResName_Copy, "w"); //open results datafile
  for (auto& freq : freqs) {
    printf("%s\n", freq.c_str());

    char dirnameFreqCity_Copy[256];

    strcpy(dirnameFreqCity_Copy,dirnameFreqCity);
    lenDIRCity = strlen(dirnameFreqCity_Copy);
    sprintf(dirnameFreqCity_Copy + lenDIRCity, "%d", std::stoi(freq));

    printf("dirnameFreqCity: %s\n", dirnameFreqCity_Copy);
    files_name_vector = readDir(dirnameFreqCity_Copy); // read filenames in folder and write its in array
    printf("size: %d\n",files_name_vector.size());
    for (auto file : files_name_vector) {
      printf("filename: %s\n", file.c_str());


      int k2 = 1;
      int TimeCounter = 0;
      int hop =0;

      for(int k=0;k<files_name_vector.size();k++){

      sscanf(file.c_str(), "%d_%d_%d_%d_%*d%*s", &dYear, &dMonth, &dDay, &dTimeHour);
      //printf("%d\n",dYear);
      dTimeHour = (int)ceil(((double)dTimeHour/100));

      TimeCounter++;

      //printf("HOP: %d City:%d\n",hop,City.first);

      char* ch1noCor = getInputFile(0,file.c_str(),std::stoi(freq),hop, 0, dDay, dMonth,dYear); // files
      //printf("%s\n",ch1noCor);

      //char*  ch1 = getInputFile(1,file,freq,hop, 0, dDay,dMonth,dYear);

      //resultMain(ch1,filesName[k],1,freqVectorElem,hop); //Calculate data  with cor
      //free(ch1);

if(dTimeHour == 8 && std::stoi(freq)== 9996 && dDay == 12){
printf("time: %d freq:%d\n",dTimeHour, std::stoi(freq));
      resultMain(ch1noCor,file,0,std::stoi(freq),hop);//Calculate data  without cor
      free(ch1noCor);
}


  }


  }

}
  /*
      int k2 = 1;
      int TimeCounter = 0;
      int hop =3;

      for(int k=0;k<c;k++){

  //        sscanf(filesName[k],"%*d_%*d_%*d_%d%*s",&dTimeHour);
  //        sscanf(filesName[k],"%*d_%d_%*d_%*d%*s",&dMonth);
  //        sscanf(filesName[k],"%*d_%*d_%d_%*d%*s",&dDay);
  //        sscanf(filesName[k],"%d_%*d_%*d_%*d%*s",&dYear);
      sscanf(filesName[k], "%*d_%d_%d_%d_%d%*s", &dYear, &dMonth, &dDay, &dTimeHour);
      dTimeHour = (int)ceil(((double)dTimeHour/100));

      TimeCounter++;

      //printf("HOP: %d City:%d\n",hop,City.first);

      char* ch1noCor = getInputFile(0,filesName[k],freqCity[0],hop, 0, dDay, dMonth,dYear); // files
      char*  ch1 = getInputFile(1,filesName[k],freqCity[0],hop, 0, dDay,dMonth,dYear);

      //resultMain(ch1,filesName[k],1,freqVectorElem,hop); //Calculate data  with cor
      printf("%s",filesName[k]);
      printf("\n\n---------------------------------------------------------------\n");
      free(ch1);

      //resultMain(ch1noCor,filesName[k],0,freqCity,hop);//Calculate data  without cor
      free(ch1noCor);


  }


                   //printf("END FOLDER FREQ:%d\n-----------------------------------------------------------------///",freqVectorElem);
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
                  //Data_Processing(FreqDataProc,S_Map,a_Map,delta_Map,freqVectorElem,0,12,trueDistant,trueAzimut);
                 // Data_Processing(FreqDataProc,S_Map,a_Map,delta_Map,freqVectorElem,1,12,trueDistant,trueAzimut);
                  //printf("END FOLDER FREQ:%d\n-----------------------------------------------------------------///\n",freqVectorElem);
                  dynamic_array_free(filesName, c);

                  S_Map.clear();
                  delta_Map.clear();
                  a_Map.clear() ;


              WriteDataInFile(FreqDataProc,fileResOut);
              FreqDataProc.clear();
              printf("END\n");




       fclose(fileResOut);
       printf("TEC: %d, noTEC: %d", Cor_number,noCor_number   );
       */
  return 0;
}
void drawIon(double* fpl, double* hpl, int nf, int npoin, double hMin, double hMax, double fMax)
{
}

void drawTrek(double* sTr, double* hTr, long pointTr)
{
}

void drawInf(char*)
{
}
void modeDistributor(double val, int en, double** arrE, double** arrF1, double** arrF2, double** arr, unsigned long modaVal, int wox) {
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
