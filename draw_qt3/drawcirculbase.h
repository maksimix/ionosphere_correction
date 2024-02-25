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
/*             Функция оформляет поле круговой диаграммы       */
/*                                                             */
/* fildView    - прямоугольник, в который вписывается поле     */
/*               диаграммы;                                    */
/* nx          - ширина в пикселях поля графика по оси абцисс; */
/* ny          - ширина поля в пикселях по оси ординат;        */
/* irx,iry     - 0 - ставятся только риски по осям,            */
/*               1 - чертится координатная сетка;              */
/* kxr         - количество точек разметки по оси x (alfa);    */
/* kyr         - количество точек разметки по оси y (r);       */
/* left        - левая граница графика;                        */
/* top         - верхняя граница графика;                      */
/* right       - правая граница графика;                       */
/* bottom      - нижняя граница графика;                       */
/* flag        - способ оцифровки радиальной координаты;       */
/* ix          - координаты левого нижнего угла поля диаграммы;*/
/* iy                                                          */
/* xCentr      - координаты центра круговой диаграммы;         */
/* yCentr                                                      */
/* R           - радиус круговой диаграммы                     */
/*                                                             */
/*VGG                                                          */
/***************************************************************/

class DrawCirculBase: public QWidget
{
public:
    enum FlagCirculBase {fcbCos, fcbLin}; // флаг оцифровки радиальной оси
    // fcbCos - масштаб пропорционален косинусу вертикального угла
    // fcbLin - масштаб линейный
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
    QRect  rectCircul; // содержит область круговой диаграммы
    QRect  rClear; // область отчистки
    QColor colorAngle;      // цвет запрещенной области
    QColor colorFon;        // фон окантовывающего прямоугольника
    QColor colorFonCircul;  // основной фон диаграммы
    QColor colorText;       // текст вне поля диаграммы
    QColor colorTextCircul; // текст в поле диаграммы
    QColor colorSetka;      // цвет сетки
    QColor colorRiski;
    FlagCirculBase flag;
    short  *divot;  // область сохранения
    long left, right, top, bottom;
    long ix, iy, nx, ny, irx, iry,  krx, kry;
    long xCentr, yCentr, R;
    bool error;
    bool flagRangeX; // true, если диапазон изменений аргумента определен
    bool flagRangeY; // true, если диапазон изменений функцииы определен
    double beginAngl, endAngl;
private:
    long grraz(QPainter &p);
};

#endif
