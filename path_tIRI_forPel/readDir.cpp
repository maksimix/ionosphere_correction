#include "paths.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include "readDir.h"

//const double TECTimeArr[] = {38,38,50,58,71,84,93,98,104,113,114,109,105,101,93,91,89,86,83,78,75,72,71,65};//2019 04 04
std::map<int, std::vector<double>> TECTimeArr ;//2022 11 22

const char *strArrTEC[] = {

   ".1 .00001 .000001 .001 4000.\n",
   "3 0 0 0 0 1 -1\n",
   "39.8140 47.2806 0. 0.\n",
   "2022 4.1 0 0 1 1\n",
   "-200. 2500. 000.0\n",
   "100000 105900 1500\n",
   "0\n",
   "1.344 65.2 6.77\n",
   "1\n",
   ".0 200 20 -45.0 45 0\n",
   "1\n",
   "-0.0 200. 39.0 55. 20. 00.0 20. 100. 20.\n",
   "10\n",
   "39.8140 47.2806\n",
   "40.0 47.50 100000 450 11.30e16\n",
   "40.0 47.50 101500 450 11.30e16\n",
   "40.0 47.50 103000 450 11.30e16\n",
   "40.0 47.50 104500 450 11.30e16\n",
   "3\n",
   "0 0\n",
   "6\n",


};

const char *strArrNoCor[] = {

   "1 .00001 .000001 .001 4000.\n" ,
    "0 0 0 0 0 1 -1\n"             ,
     "39.8140 47.2806 0. 0.\n"     ,
    "2019 12.7 0 0 1 1\n"          ,
    "-200. 2500. 000.0\n"          ,
    "100000 105900 1500\n"         ,
    "0\n"                          ,
    "1.344 65.2 6.77\n"            ,
    "1\n"                          ,
    ".0 200 20 -45.0 45 0\n"       ,
    "1\n"                          ,
     "-0.0 200. 39.0 55. 20. 00.0 20. 100. 20.\n",
     "10\n",
    "39.8140 47.2806\n",
     "3\n",
    "0 0\n",
    "6\n",


};



char**  readDir(char dirName[], int*count){
    char**  filesName;
    //printf("%s\n",dirName);
    int filesCount = 0;
    struct dirent *in_file;
    DIR *dir = opendir(dirName);
    while((in_file=readdir(dir))!=NULL){
            if(!strcmp(in_file->d_name,".")) continue;
            if(!strcmp(in_file->d_name,"..")) continue;
 filesCount++;
}
    *count = filesCount;
    filesName = dynamic_array_alloc<char>(filesCount,256);
    closedir(dir);
    dir = opendir(dirName);
    int i = 0;
    while((in_file=readdir(dir))!=NULL){
        if(!strcmp(in_file->d_name,".")) continue;
        if(!strcmp(in_file->d_name,"..")) continue;


   strcpy(filesName[i],in_file->d_name);
//  *(filesName[i]) = *(in_file->d_name);
  i++;

}

return filesName;
};
char * getCity(int city){
switch(city){

case 0:
    return "Moscow";
    break;
case 1:
    return "Kashi";
    break;

 default:
        return "Moscow";
    break;


}
}
double DayCalculate(int year, int month, int day){
    int monthDay =0;
    switch (month) {
            case 2:
                if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
                    monthDay = 29;
                else
                    monthDay = 28;
            case 4:
            case 6:
            case 9:
            case 11:
                monthDay = 30;
            default:
               monthDay = 31;
        }
    return round((month + (double)day/monthDay)*10)/10;

}
char *getInputFile(int m, char * dataFileName, int freq, int hop, int city, int day, int month, int year){
//m:1 - TEC, 0 - noCOr

    double DAY = DayCalculate(year,month,day);

   printf("day - %lg\n",DAY);
    switch(m){
    case 0:{

        char *inFileName = (char*)malloc(sizeof(char)*200) ;
        const int strNum = 5;
        sprintf(inFileName,"results/out_tIRI_path0s_Rostov_%s_noCor_%d_%s",getCity(city),freq,dataFileName );

          //    printf("datafilename - %s\n",inFileName);
        FILE* file = fopen(inFileName,"w");
  //      printf("file norm");
        int d1 = 0;
        sscanf(dataFileName,"%*[^_]_%*[^_]_%*[^_]_%d%*s",&d1);
        d1 = (int)ceil(((double)d1/100))*10000;
        for(int i=0; i<17; i++){
            if(i==strNum)  fprintf(file,"%d %d 1500\n",d1,d1+5900);
            else if(i==3) fprintf(file,"%d %lg 0 0 1 1\n",year, DAY);
            else if(i==14) fprintf(file,"%d\n",hop);
            else fprintf(file,"%s",strArrNoCor[i]);
        };
        fprintf(file,"%d/%s/%d/%s",year,getCity(city),freq,dataFileName);
        fclose(file);
//         printf("file norm2\n\n\n");
        return inFileName;
        break;
}
    case 1:{

       char* inFileName = (char*) malloc(sizeof(char)*200) ;
        const int TECstrNum = 5; // number of TEC's string in input file
        sprintf(inFileName,"results/out_tIRI_path0s_Rostov_%s_TEC_%d_%s",getCity(city),freq,dataFileName);


         FILE* file = fopen(inFileName,"w");


         int d1 = 0;

      sscanf(dataFileName,"%*[^_]_%*[^_]_%*[^_]_%d%*s",&d1);

      int d0 = (int)ceil(((double)d1/100));

      d1 = d0*10000;

      for(int i=0; i<21; i++){
           if(i==TECstrNum)  fprintf(file,"%d %d 1500\n",d1,d1+5900);
          else if(i==3) fprintf(file,"%d %lg 0 0 1 1\n",year, DAY);
           else if((i>13)&&(i<18)){
           fprintf(file,"40.0 47.50 %d 450 %fe+15\n",d1,TECTimeArr[day].at(d0));
           d1+=1500;
       }
           else if(i==18) fprintf(file,"%d\n",hop);
           else  fprintf(file,"%s",strArrTEC[i]);

      };
      fprintf(file,"%d/%s/%d/%s",year, getCity(city),freq,dataFileName);
      fclose(file);


      return inFileName;
      break;



    }


}
}
