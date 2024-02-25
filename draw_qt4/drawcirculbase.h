#ifndef DRAWCIRCULBASE_H

#ifndef QPAINTER_H
#include <qpainter.h>
#endif
#ifndef QSTRING_H
#include <qstring.h>
#endif
#ifndef QWIDGET_H
#include <qwidget.h>
#endif

#define DRAWCIRCULBASE_H

/***************************************************************/
/*                                                             */
/*             ������� ��������� ���� �������� ���������       */
/*                                                             */
/* fildView    - �������������, � ������� ����������� ����     */
/*               ���������;                                    */
/* nx          - ������ � �������� ���� ������� �� ��� ������; */
/* ny          - ������ ���� � �������� �� ��� �������;        */
/* irx,iry     - 0 - �������� ������ ����� �� ����,            */
/*               1 - �������� ������������ �����;              */
/* kxr         - ���������� ����� �������� �� ��� x (alfa);    */
/* kyr         - ���������� ����� �������� �� ��� y (r);       */
/* left        - ����� ������� �������;                        */
/* top         - ������� ������� �������;                      */
/* right       - ������ ������� �������;                       */
/* bottom      - ������ ������� �������;                       */
/* flag        - ������ ��������� ���������� ����������;       */
/* ix          - ���������� ������ ������� ���� ���� ���������;*/
/* iy                                                          */
/* xCentr      - ���������� ������ �������� ���������;         */
/* yCentr                                                      */
/* R           - ������ �������� ���������                     */
/*                                                             */
/*VGG                                                          */
/***************************************************************/

class DrawCirculBase: public QWidget
{
public:
    enum FlagCirculBase {fcbCos, fcbLin}; // ���� ��������� ���������� ���
    // fcbCos - ������� �������������� �������� ������������� ����
    // fcbLin - ������� ��������
    DrawCirculBase(QWidget *parent,
                   FlagCirculBase flag=fcbCos,
                   long irx=1, long iry=1, long kxr=12, long kyr=6);
    ~DrawCirculBase();
    void   setKrx(long i){krx=i;};
    long   getKrx(){return krx;};
    void   setKry(long i){kry=i;};
    long   getKry(){return kry;};
    void   setIrX(long i){irx=i;};
    long   getIrX(){return irx;};
    void   setIrY(long i){iry=i;};
    long   getIrY(){return iry;};
    void           setFlag(FlagCirculBase f){flag=f;};
    FlagCirculBase getFlag(){return flag;};
    long   getR(){return R;};
    long   getXCentr(){return xCentr;};
    long   getYCentr(){return yCentr;};
    void   setIxy(long x, long y){ix=x; iy=y;};
    void   getIxy(long &x, long &y){x=ix; y=iy;};
    void   setNxy(long x, long y){nx=x; ny=y;};
    void   getNxy(long &x, long &y){x=nx; y=ny;};
    void setColorFon(QColor col){colorFon=col;};
    QColor getColorFon(){return colorFon;};
    void setColorFonCircul(QColor col){colorFonCircul=col;};
    QColor getColorFonCircul(){return colorFonCircul;};
    void setColorText(QColor col){colorText=col;};
    QColor getColorText(){return colorText;};
    void setColorSetka(QColor col){colorSetka=col;};
    QColor getColorSetka(){return colorSetka;};
    void setColorAngle(QColor col){colorAngle=col;};
    QColor getColorRiski(){return colorRiski;};
    void setColorRiski(QColor col){colorRiski=col;};
    QColor getColorAngle(){return colorAngle;};
    void setColorTextCircul(QColor col){colorTextCircul=col;};
    QColor getColorAxeCircul(){return colorTextCircul;};
    void setEndAngl(double a){endAngl=a;};
    double getEndAngl(){return endAngl;};
    void setBeginAngl(double a){beginAngl=a;};
    double getBeginAngl(){return beginAngl;};
    
protected:
    virtual void paintEvent(QPaintEvent *e);
    QRect  fildView;
    QRect  rectCircul; // �������� ������� �������� ���������
    QRect  rClear; // ������� ��������
    QColor colorAngle;      // ���� ����������� �������
    QColor colorFon;        // ��� ��������������� ��������������
    QColor colorFonCircul;  // �������� ��� ���������
    QColor colorText;       // ����� ��� ���� ���������
    QColor colorTextCircul; // ����� � ���� ���������
    QColor colorSetka;      // ���� �����
    QColor colorRiski;
    FlagCirculBase flag;
    short  *divot;  // ������� ����������
    long left, right, top, bottom;
    long ix, iy, nx, ny, irx, iry,  krx, kry;
    long xCentr, yCentr, R;
    bool error;
    bool flagRangeX; // true, ���� �������� ��������� ��������� ���������
    bool flagRangeY; // true, ���� �������� ��������� �������� ���������
    double beginAngl, endAngl;
private:
    long grraz(QPainter &p);
};

#endif
