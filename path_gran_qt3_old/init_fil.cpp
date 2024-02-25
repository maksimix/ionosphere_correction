#include <stdlib.h>
#include "paths.h"

void init_fil(char   *name,
              INFR   &infr,
              long   keyini)
/***************************************************************/
/*                                                             */
/* ������� ������������� ��� ������������� ����� �����������   */
/* ������� ��� ��� �������� ������������ ��� �������������.    */
/*                                                             */
/* name   - ��� �����;                                         */
/* keyini   0 - ���������� �����,                              */
/*        - 1 - ������������� �����,                           */
/*        - 2 - ������������� ������ � �����;                  */
/* ���� name ��� ������ �� ������� �������� ��������.          */
/*                                                             */
/* VGG                                                         */
/***************************************************************/
{
  INFR   infr0;
  long   i,j;
  long   ndasf;
  double fr;
  FILE   *dasf;
  const double eps=.1e-14; // ��������� ��� ��������� ������ � �����

  switch (keyini)
    {
      case 0: // ���������� ������� � ����
        dasf=fopen(name,"rb");
        if (ferror(dasf))
          {
            clearerr(dasf);
            fclose(dasf);
            printf("\n����-���� � ������:%s �� ����� ���� ������",name);
            exit(EXIT_FAILURE);
          }
        ndasf=0;
        fseek(dasf,ndasf,SEEK_SET);
        fread(&infr0,sizeof(INFR),1,dasf);
        if (infr0.kfr!=infr.kfr                            ||
            infr0.trassa.typeAntT!=infr.trassa.typeAntT    ||
            infr0.trassa.typeAntR!=infr.trassa.typeAntR    ||
            fabs(infr0.trassa.lon0-infr.trassa.lon0)>eps   ||
            fabs(infr0.trassa.lat0-infr.trassa.lat0)>eps   ||
            fabs(infr0.trassa.lon1-infr.trassa.lon1)>eps   ||
            fabs(infr0.trassa.lat1-infr.trassa.lat1)>eps   ||
            fabs(infr0.trassa.w-infr.trassa.w)>eps         ||
            fabs(infr0.trassa.month-infr.trassa.month)>eps ||
            fabs(infr0.trassa.P-infr.trassa.P)>eps         ||
            fabs(infr0.trassa.band-infr.trassa.band)>eps   ||
            fabs(infr0.trassa.tBeg-infr.trassa.tBeg)>eps   ||
            fabs(infr0.trassa.tEnd-infr.trassa.tEnd)>eps   ||
            fabs(infr0.trassa.tStep-infr.trassa.tStep)>eps)
          {
            printf("\n��������� ������ �� ������������� �����:%s\n",name);
            exit(EXIT_FAILURE);
          }
        for(i=0; i<infr.kfr; i++)
          {
            fread(&fr,sizeof(double),1,dasf);
            if (fabs(fr-infr.fr[i])>eps)
              {
                printf("\n��������� ������ �� ������������� �����:%s\n",name);
                exit(EXIT_FAILURE);
              }
          }
        fclose(dasf);
        break;

      case 1: // ������������� ������ �����
        dasf=fopen(name,"wb");
        if (ferror(dasf))
          {
            clearerr(dasf);
            fclose(dasf);
            printf("\n����-���� � ������:%s �� ����� ���� ������",name);
            exit(EXIT_FAILURE);
          }
        infr0=infr;
        infr0.fr=NULL;

        ndasf=0;
        fseek(dasf,ndasf,SEEK_SET);
        fwrite(&infr0,sizeof(INFR),1,dasf);
        for(i=0; i<infr.kfr; i++)
          fwrite((infr.fr+i),sizeof(double),1,dasf);
        fclose(dasf);
        break;

      case 2: // ��������� ������������ ������
      case 3: // ������ ������������ ������
        dasf=fopen(name,"rb");
        if (ferror(dasf))
          {
            clearerr(dasf);
            fclose(dasf);
            printf("\n����-���� � ������:%s �� ����� ���� ������",name);
            exit(EXIT_FAILURE);
          }
        fseek(dasf,0,SEEK_SET);
        fread(&infr0,sizeof(INFR),1,dasf);
        // ��� ��������� ����� ������ �� ������� ���������
        if (infr0.trassa.typeAntT!=infr.trassa.typeAntT    ||
            infr0.trassa.typeAntR!=infr.trassa.typeAntR    ||
            fabs(infr0.trassa.lon0-infr.trassa.lon0)>eps   ||
            fabs(infr0.trassa.lat0-infr.trassa.lat0)>eps   ||
            fabs(infr0.trassa.lon1-infr.trassa.lon1)>eps   ||
            fabs(infr0.trassa.lat1-infr.trassa.lat1)>eps   ||
            fabs(infr0.trassa.w-infr.trassa.w)>eps         ||
            fabs(infr0.trassa.month-infr.trassa.month)>eps ||
            fabs(infr0.trassa.P-infr.trassa.P)>eps         ||
            fabs(infr0.trassa.band-infr.trassa.band)>eps   ||
            fabs(infr0.trassa.tBeg-infr.trassa.tBeg)>eps   ||
            fabs(infr0.trassa.tEnd-infr.trassa.tEnd)>eps   ||
            fabs(infr0.trassa.tStep-infr.trassa.tStep)>eps)
          {
            printf("\n��������� ������ �� ������������� �����:%s\n",name);
            exit(EXIT_FAILURE);
          }
        for(i=0; i<infr0.kfr; i++)
          {
            fread(&fr,sizeof(double),1,dasf);
            for(j=0; j<infr.kfr; j++)
              {
                if (fr != infr.fr[i])
                  continue;
                else
                  break;
              }
            if (j==infr.kfr)
              {
                printf("\n��������� ������ �� ������������� �����:%s\n",name);
                exit(EXIT_FAILURE);
              }
          }
        fclose(dasf);
        break;

      default:
        break;
    }
  return;
} /* init_fil */
