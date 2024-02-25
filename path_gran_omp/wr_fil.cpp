#include <stdlib.h>
#include <string.h>
#include "paths.h"

static void writeInfr(FILE *dasf, INFR &infr)
{
  fseek(dasf,0,SEEK_SET);
  fwrite(&infr,sizeof(INFR),1,dasf);
  for(int i=0; i<infr.kfr; i++)
    fwrite((infr.fr+i),sizeof(double),1,dasf);
  delete[] infr.fr;
}

static void readInfr(FILE *dasf, INFR &infr)
{
  fseek(dasf,0,SEEK_SET);
  fread(&infr,sizeof(INFR),1,dasf);
  infr.fr=new double[infr.kfr];
  for(int i=0; i<infr.kfr; i++)
    fread((infr.fr+i),sizeof(double),1,dasf);
}

void wr_fil(char   *name,
            INFR   &infr0,
            long    keyini,
            COR    *cor)
/*****************************************************************/
/* Функция предназначена для формирования файла сохраненных      */
/* параметров модели; файл открывается, а при выходе - закрыва-  */
/* ется.                                                         */
/*                                                               */
/* name   - имя файла;                                           */
/* nfr    - количество рабочих частот;                           */
/* t      - время, для которого расчитаны параметры;             */
/* keyini - 0 - дополнение файла,                                */
/*          1 - инициализация файла,                             */
/*          2 - коррекция данных в файле;                        */
/* cor    - указатель на структуру параметров модели канала.     */
/*                                                               */
/*VGG                                                            */
/*****************************************************************/
{
  INFR infr;
  long sizeInfr;
  long ndasf;
  long key,i,j,n,m,l;
  FILE *dasf;
  COR  *cor0,*cor1,*corr,*corw;

  dasf=fopen(name,"r+b");

  readInfr(dasf,infr);
  sizeInfr=(long)sizeof(INFR)+(long)sizeof(double)*infr.kfr;

  switch (keyini)
    {
      case 0:
      case 1:
        ndasf=sizeInfr+(long)sizeof(COR)*infr.kfr*infr.kzap;
        fseek(dasf,ndasf,SEEK_SET);
        fwrite(cor,sizeof(COR),infr.kfr,dasf);
        infr.kzap++;
        infr.timek=infr0.timek;
        writeInfr(dasf,infr);
        infr0.kzap=infr.kzap;
        fclose(dasf);
        break;
      case 2:
        cor0=new COR[infr.kfr];
        if (!cor0)
          {
            printf("\nНЕТ ПАМЯТИ ПОД РАБОЧИЕ МАССИВЫ");
            exit(EXIT_FAILURE);
          }

        while ((key=fread(cor0,sizeof(COR),infr.kfr,dasf)) && infr0.timek>cor0->time);

        if (infr0.timek<cor0->time || !key)
          { /* вставка новой записи внутрь файла */
            if (infr0.kfr!=infr.kfr)
              {
                printf("\n ДАННЫЕ НЕ СООТВЕТСТВУЮТ ФАЙЛУ:%s",name);
                exit(EXIT_FAILURE);
              }

            if (key)
              {
                fseek(dasf,ftell(dasf)-sizeof(COR)*infr.kfr,SEEK_SET);
                fwrite(cor,sizeof(COR),infr.kfr,dasf);
                corw=cor0;
                corr=cor;

                while (!fseek(dasf,0,SEEK_CUR) &&
                       fread(corr,sizeof(COR),infr.kfr,dasf))
                  {
                    fseek(dasf,ftell(dasf)-sizeof(COR)*infr.kfr,SEEK_SET);
                    fwrite(corw,sizeof(COR),infr.kfr,dasf);
                    cor1=corr;
                    corr=corw;
                    corw=cor1;
                  }
              }
            else
              {
                corw=cor;
                infr.timek=infr0.timek;
              }

            fseek(dasf,0,SEEK_END);
            fwrite(corw,sizeof(COR),infr.kfr,dasf);
            infr.kzap++;
            writeInfr(dasf,infr);
            infr0.kzap=infr.kzap;
            fclose(dasf);
          }
        else
          { /* коррекция существующей записи */
            key=0;

            for(i=0; i<infr0.kfr; i++)
              for(j=0; j<infr.kfr; j++)
                if ((cor+i)->fr==(cor0+j)->fr)
                  for(m=0; m<(cor+i)->k; m++)
                    {
                      for(n=0; n<(cor0+j)->k; n++)
                        if (fabs((cor+i)->di[m]-(cor0+j)->di[n])<.17e-2 &&
                            fabs((cor+i)->dk[m]-(cor0+j)->dk[n])<.17e-2 &&
                            (cor+i)->pg[m]*(cor0+j)->pg[n]>.0)
                          break;

                      if (n==(cor0+j)->k)
                        {
                          key=1;
                          if ((cor0+j)->k<12)
                            (cor0+j)->k++;
                          else
                            if ((cor0+j)->e[n-1]<(cor+i)->e[m])
                              n--;
                            else
                              continue;
                          (cor0+j)->di[n]=(cor+i)->di[m];
                          (cor0+j)->ai[n]=(cor+i)->ai[m];
                          (cor0+j)->dk[n]=(cor+i)->dk[m];
                          (cor0+j)->ak[n]=(cor+i)->ak[m];
                          (cor0+j)->e[n] =(cor+i)->e[m];
                          (cor0+j)->l_es[n] =(cor+i)->l_es[m];
                          (cor0+j)->p[n] =(cor+i)->p[m];
                          (cor0+j)->pg[n]=(cor+i)->pg[m];
                          (cor0+j)->df[n]=(cor+i)->df[m];
                          (cor0+j)->moda[n]=(cor0+j)->moda[m];
                          shell((cor0+j)->e,
                                (cor0+j)->l_es,
                                (cor0+j)->di,
                                (cor0+j)->ai,
                                (cor0+j)->dk,
                                (cor0+j)->ak,
                                (cor0+j)->p,
                                (cor0+j)->pg,
                                (cor0+j)->df,
                                (cor0+j)->moda,
                                (cor0+j)->k);
                        }
                    }

            if (key)
              {
                fseek(dasf,ftell(dasf)-sizeof(COR)*infr.kfr,SEEK_SET);
                fwrite(cor0,sizeof(COR),infr.kfr,dasf);
              }
            fclose(dasf);
          }
        delete[] cor0;
        break;
      case 3: // Замена существующей записи
        cor0=new COR[infr.kfr];
        if (!cor0)
          {
            printf("\nНЕТ ПАМЯТИ ПОД РАБОЧИЕ МАССИВЫ");
            exit(EXIT_FAILURE);
          }

        while ((key=fread(cor0,sizeof(COR),infr.kfr,dasf)) && infr0.timek>cor0->time);

        if (infr0.timek==cor0->time || !key)
          { /* коррекция существующей записи */
            fseek(dasf,ftell(dasf)-sizeof(COR)*infr.kfr,SEEK_SET);
            fwrite(cor,sizeof(COR),infr.kfr,dasf);
          }
        if (!key)
          {
            infr.kzap++;
            infr.timek=infr0.timek;
            writeInfr(dasf,infr);
            infr0.kzap=infr.kzap;
          }
        fclose(dasf);
        delete[] cor0;
        break;
    }

  return;

} /* wr_fil */

void writeIndexDasf(char *name)
{
    FILE *dasf;
    char index[]={"DASF-FILE"};

    dasf=fopen(name,"r+b");
    fseek(dasf,0,SEEK_END);
    fwrite(index,sizeof(index),1,dasf);
    fclose(dasf);
}

bool readIndexDasf(char *name)
{
    FILE *dasf;
    char index[]={"DASF-FILE"};
    char temp[10];

    dasf=fopen(name,"r+b");
    fseek(dasf,-sizeof(index),SEEK_END);
    fread(temp,sizeof(index),1,dasf);
    fclose(dasf);
    bool cmp=(bool)strcmp(index,temp);

    return cmp;
}
