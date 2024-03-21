#ifndef READDIR_H
#define READDIR_H

#endif // READDIR_H

char**  readDir(char dirName[], int*count);
std::vector<std::string> readDir(const char dirName[]);
char * getCity(int city);
double DayCalculate(int year, int month, int day);
char *getInputFile(int m, std::string dataFileName, int freq, int hop, int city, int day, int month, int year);
