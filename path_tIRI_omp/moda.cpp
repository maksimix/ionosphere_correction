#include <stdio.h>

char* moda(unsigned long  m,
           char* str)
/***************************************************************/
/* Функция принимает указатель на строку str, заполняет ее     */
/* символами, идентифицирующими отражающий ионосферный слой в  */
/* соответствии со структурой, заданной целой переменной м и   */
/* возвращает указатель на строку str.                         */
/* Предполагается, что число скачков не более 8.               */
/*                                                             */
/* m  - 1 - D, 2 - E, 3 и более - F отражения;                 */
/*                                                             */
/*VGG                                                          */
/***************************************************************/
{
  long  j;
  unsigned long i;

  i=m%10l;
  j=0;

  while(i)
    {
      switch(i)
       {
         case 1:
           sprintf((str+j),"%c",'D');
           j++;
           break;
         case 2:
           sprintf((str+j),"%c",'E');
           j++;
           break;
         case 9:
           sprintf((str+j),"%s","Es");
           j +=2;
           break;
         case 3:
           sprintf((str+j),"%s","F1");
           j +=2;
           break;
         case 4:
         case 5:
         case 6:
         case 7:
         case 8:
           sprintf((str+j),"%s","F2");
           j +=2;
           break;
         default:
           break;
       }
      m /=10l;
      i=m%10l;
    }

  while(j<24)
    {
      *(str+j)=' ';
      j++;
    }

  *(str+j)='\0';

  return str;
}
