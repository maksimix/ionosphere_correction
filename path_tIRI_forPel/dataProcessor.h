#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#endif // DATAPROCESSOR_H


#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <map>
#include <vector>
double standardDeviation(std::vector<double> &vData, double trueVal) ;
double averageVal(std::vector<double> &vData);
void Data_Processing(std::map<int,std::map<int, std::map<int, std::map<int,std::map<int,std::map<int, double>>>>>> &Data_map,
                     std::map <int,std::map<int,std::map<int,std::vector<double>>>> &S_map,
                     std::map <int,std::map<int,std::map<int,std::vector<double>>>> &a_map,
                      std::map <int,std::map<int,std::map<int,std::vector<double>>>> &delta_map,
                     int freq,int cor, int time,
                     double trueDist, double trueAzimut);
void WriteDataInFile(std::map<int,std::map<int, std::map<int, std::map<int,std::map<int,std::map<int, double>>>>>> &Data_map, FILE *file);

