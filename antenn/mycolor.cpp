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
  colorDiagr, // 梥� ����� ��㣮��� ����ࠬ��
  colorFon,   // 梥� 䮭�, �� ���஬ ���⠥��� ⥪��
  colorFild,  // 梥� �뤥������� ���⪠
  colorMouse, // 梥� ���������� ���� �� ��६�饭�� ��� (�뤥����� �����)
  colorGist,
  colorGistB;

void myColor(color_t maxColor)
//
// �㭪�� �।�����祭� ��� �����祭�� 梥⮢, �ᯮ��㥬�� � �ணࠬ��
// maxColor - ���ᨬ��쭮� �᫮ 梥⮢ � ⥪�饩 ����
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

  colorDiagr=(maxColor<256)? 11 : 103; // 梥� ����� ��㣮��� ����ࠬ��
  colorFon  =(maxColor<256)?  2 :  30; // 梥� 䮭�, �� ���஬ ���⠥��� ⥪��
  colorGist =(maxColor<256)? 13 :  37;
  colorGistB=(maxColor<256)? 14 :  42;
  colorFild =6;   // 梥� �뤥������� ���⪠
  colorMouse=9;   // 梥� ���������� ���� �� ��६�饭�� ��� (�뤥����� �����)
}