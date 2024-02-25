#include "mycolor.hpp"

unsigned long
  Black,
  White,
  LightGray,
  Gray,
  DarkBlue,
  DarkGreen,
  LightYellow,
  Yellow,
  DarkGray,
  Blue,
  LightGreen,
  LightBlue,
  Red,
  Violet,
  DarkYellow,
  colorDiagr, // цвет линий круговой диаграммы
  colorFon,   // цвет фона, на котором печатается текст
  colorFild,  // цвет выделенного участка
  colorMouse, // цвет заполнения поля при перемещении мыши (выделение мышью)
  colorGist,
  colorGistB;

void myColor(color_t maxColor)
//
// Функция предназначена для назначения цветов, используемых в программе
// maxColor - максимальное число цветов в текущей моде
//
{
  Black      =0;
  White      =1;
  LightGray   =2;
  Gray       =3;
  DarkBlue   =4;
  DarkGreen  =5;
  LightYellow =6;
  Yellow     =7;
  DarkGray   =8;
  Blue       =9;
  LightGreen  =10;
  LightBlue   =11;
  Red        =12;
  Violet     =13;
  DarkYellow =14;

  colorDiagr=(maxColor<256)? 11 : 103; // цвет линий круговой диаграммы
  colorFon  =(maxColor<256)?  2 :  30; // цвет фона, на котором печатается текст
  colorGist =(maxColor<256)? 13 :  37;
  colorGistB=(maxColor<256)? 14 :  42;
  colorFild =6;   // цвет выделенного участка
  colorMouse=9;   // цвет заполнения поля при перемещении мыши (выделение мышью)
}