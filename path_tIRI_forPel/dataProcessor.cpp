#include "paths.h"
#include "dataProcessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <map>
#include <vector>



double standardDeviation(std::vector<double> &vData, double trueVal) {
double sum = .0;
if(vData.size() == 0) return 0;
for(double val : vData)
{
    sum+=pow(val-trueVal,2);
  }

    return sqrt(sum / vData.size());
}


double averageVal(std::vector<double> &vData)
{
if(vData.size() == 0) return 0;
double sum = 0;
for(double val : vData)
{
    sum+=val;
  }
    return sum/vData.size();
}


char* ModeToString(int mode) {
   switch (mode) {
       case 0:
           return "E";
       case 1:
           return "F";
       default:
           return "Unknown mode";
   }
}
void Data_Processing(std::map<int,std::map<int, std::map<int, std::map<int,std::map<int,std::map<int, double>>>>>> &Data_map,
                     std::map <int,std::map<int,std::map<int,std::vector<double>>>> &S_map,
                     std::map <int,std::map<int,std::map<int,std::vector<double>>>> &a_map,
                      std::map <int,std::map<int,std::map<int,std::vector<double>>>> &delta_map,
                     int freq,int cor, int time,
                     double trueDist, double trueAzimut){
//printf("FREq:%d\n",freq);
//printf("Time:%d\n",time);
for(int hop =0; hop< 3; ++hop){

    for (int mode = 0; mode < 2; ++mode) {
         printf("HOP: %d, MODE: %s\n",hop+1,ModeToString(mode));
Data_map[cor][freq][hop][mode][time][0] = averageVal(delta_map[cor][hop][mode]);
//printf("<delta>: %lf\n",Data_map[cor][freq][hop][mode][time][0]);


Data_map[cor][freq][hop][mode][time][1] = standardDeviation(delta_map[cor][hop][mode], Data_map[cor][freq][hop][mode][time][0]);
//printf("sigmaDelta^ %lf\n",Data_map[cor][freq][hop][mode][time][1]);

Data_map[cor][freq][hop][mode][time][2] = averageVal(a_map[cor][hop][mode]);
//printf("<a>^ %lf\n",Data_map[cor][freq][hop][mode][time][2]);

Data_map[cor][freq][hop][mode][time][3] = standardDeviation(a_map[cor][hop][mode], trueAzimut);
//printf("sigmaA: %lf\n",Data_map[cor][freq][hop][mode][time][3]);


Data_map[cor][freq][hop][mode][time][4] = averageVal(S_map[cor][hop][mode]);
//printf("<S>: %lf\n",Data_map[cor][freq][hop][mode][time][4] );


Data_map[cor][freq][hop][mode][time][5] = standardDeviation(S_map[cor][hop][mode], trueDist);
//printf("sigmaS: %lf\n",Data_map[cor][freq][hop][mode][time][5] );


Data_map[cor][freq][hop][mode][time][6] = 100*Data_map[cor][freq][hop][mode][time][5]/trueDist;
//printf("sigmaS/S0: %lf\n",Data_map[cor][freq][hop][mode][time][6] );


Data_map[cor][freq][hop][mode][time][7] = S_map[cor][hop][mode].size();
//printf("N: %lf\n",Data_map[cor][freq][hop][mode][time][7]);
//printf("--------------------------------------------------------------\n\n\n\n");

    }

}

}

void WriteDataInFile(std::map<int,std::map<int, std::map<int, std::map<int,std::map<int,std::map<int, double>>>>>> &Data_map, FILE *file){


//    for(auto CorMap: Data_map){

//    fprintf(file,"%d\n",CorMap.first);//cor
//    for(auto FreqMap : CorMap.second){
//          fprintf(file,"%d ",FreqMap.first);//freq
//                for(auto HopMap : FreqMap.second){
//                    fprintf(file,"%d ",HopMap.first+1);//hop
//                    for(auto ModeMap : HopMap.second){
//                        fprintf(file,"%s ",ModeToString(ModeMap.first));//mode
//                        for(auto TimeMap : ModeMap.second){
//                            fprintf(file,"%d ",(int)TimeMap.first);//time
//                        for (auto ParamsMap : TimeMap.second) {
//                            fprintf(file,"%.2lf ",ParamsMap);//param
//                        }
//                         fprintf(file,"\n        ");
//                    }
//                }

//              }
//          }
//      }



       for(auto CorMap: Data_map){

       fprintf(file,"%d\n",CorMap.first);//cor
       for(auto FreqMap : CorMap.second){

                   for(auto HopMap : FreqMap.second){

                      for(auto ModeMap : HopMap.second){

                            for(auto TimeMap : ModeMap.second){
if(TimeMap.second[0] == 0 ) continue;
fprintf(file,"%d %d %s %d ",FreqMap.first,HopMap.first+1,ModeToString(ModeMap.first), TimeMap.first);
//                            for (auto ParamsMap : TimeMap.second) {

 fprintf(file,"%.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %d",TimeMap.second[0],TimeMap.second[1],TimeMap.second[2],TimeMap.second[3],TimeMap.second[4],TimeMap.second[5],TimeMap.second[6],(int)TimeMap.second[7]);//param
// fprintf(file,"%d %d %s %d %lf \n",FreqMap.first,HopMap.first+1,ModeToString(ModeMap.first), TimeMap.first,ParamsMap.second[1]);//param
// fprintf(file,"%d %d %s %d %lf \n",FreqMap.first,HopMap.first+1,ModeToString(ModeMap.first), TimeMap.first,ParamsMap.second[2]);//param
// fprintf(file,"%d %d %s %d %lf \n",FreqMap.first,HopMap.first+1,ModeToString(ModeMap.first), TimeMap.first,ParamsMap.second[3]);//param
// fprintf(file,"%d %d %s %d %lf \n",FreqMap.first,HopMap.first+1,ModeToString(ModeMap.first), TimeMap.first,ParamsMap.second[4]);//param
// fprintf(file,"%d %d %s %d %lf \n",FreqMap.first,HopMap.first+1,ModeToString(ModeMap.first), TimeMap.first,ParamsMap.second[5]);//param
// fprintf(file,"%d %d %s %d %lf \n",FreqMap.first,HopMap.first+1,ModeToString(ModeMap.first), TimeMap.first,ParamsMap.second[6]);//param
// fprintf(file,"%d %d %s %d %lf \n",FreqMap.first,HopMap.first+1,ModeToString(ModeMap.first), TimeMap.first,ParamsMap.second[7]);//param







//                            }
                             fprintf(file,"\n");//param

                        }
                    }

                  }
             }
          }
}

