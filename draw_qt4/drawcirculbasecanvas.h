#ifndef DRAWCIRCULBASE_CANVAS_H

#ifndef QPAINTER_H
#include <qpainter.h>
#endif
#ifndef QSTRING_H
#include <qstring.h>
#endif
#ifndef QWIDGET_H
#include <qwidget.h>
#endif
#ifndef QCANVAS_H
#include <qcanvas.h>
#endif

#define DRAWCIRCULBASE_CANVAS_H

enum FlagCirculBase {fcbCos, fcbLin}; // флаг оцифровки радиальной оси
    // fcbCos - масштаб пропорционален косинусу вертикального угла
    // fcbLin - масштаб линейный

class MyCanvasPolygon : public QCanvasPolygon
{
public:
    MyCanvasPolygon(QCanvas *canvas) : QCanvasPolygon(canvas){};
private:
    virtual void drawShape( QPainter & p );
};


class MyCanvasSetka : public QCanvasEllipse
{
public:
    MyCanvasSetka(QCanvas *canvas, int r,
                  FlagCirculBase Flag=fcbCos,
                  long kRx=8, long kRy=8, long iRx=1, long iRy=1);

    ~MyCanvasSetka();
    
    long getR(){return R;};
    void setColorText(QColor c){colorText=c;};
    void setColorRiski(QColor c){colorRiski=c;};
    void setColorSetka(QColor c){colorSetka=c;};
    void setColorGist(QColor c){colorGist=c;};
    void setColorTextCircul(QColor c){colorTextCircul=c;};

private:
    FlagCirculBase flag;
    long irx, iry, krx, kry, isw, ihw, maxSizeChar;
    long R, xCentr, yCentr;
    QColor colorSetka, colorRiski, colorText, colorTextCircul, colorGist;
    virtual void drawShape( QPainter & painter );
    QFont *font;
    QFontMetrics *fm;
    
public:
    void setSize(int w, int h)
    {
        QCanvasEllipse::setSize(w,h);
        R=(long)(w/2-maxSizeChar*1.5);
    };
};
    
class MyCanvasSektor : public QCanvasEllipse
{
public:
    MyCanvasSektor(QCanvas *can, int r) : QCanvasEllipse(r*2,r*2,can)
    {
        canvas=can;
        beginAngl=endAngl=.0;
    };

    ~MyCanvasSektor(){};
    
    void setColorAngl(QColor c)
    {
        QBrush brush( c, SolidPattern );
        setBrush(brush);
    };
    void setEndAngl(double a)
    {
        endAngl=a;
        end  =(long)(endAngl*16.);
        begin=(long)(beginAngl*16.);
        kol  =begin-end;
        if (kol>0)
            kol-=5760; //360*16
        // kol по часовой стрелки -  отрицательно
        begin=1440-begin; // 90*16
      
        setAngles(begin,kol);
        canvas->setAllChanged();
    };
    
    void setBeginAngl(double a)
    {
        beginAngl=a;
        end  =(long)(endAngl*16.);
        begin=(long)(beginAngl*16.);
        kol  =begin-end;
        if (kol>0)
            kol-=5760; //360*16
        // kol по часовой стрелки -  отрицательно
        begin=1440-begin; // 90*16
      
        setAngles(begin,kol);
        canvas->setAllChanged();
    };

private:
    double endAngl, beginAngl;
    long begin, end, kol;
    QCanvas *canvas;
    virtual void drawShape( QPainter & painter )
    {
        QCanvasEllipse::drawShape( painter );
    };
};
    

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

class DrawCirculBaseCanvas: public QCanvasView
{
public:
    DrawCirculBaseCanvas(QCanvas *viewing, QWidget *parent=0,
                         FlagCirculBase flag=fcbCos,
                         long irx=1, long iry=1, long kxr=12, long kyr=6);
    ~DrawCirculBaseCanvas();
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
    void setColorText(QColor col){colorText=col;canvasSetka->setColorText(colorText);};
    QColor getColorText(){return colorText;};
    void setColorSetka(QColor col){colorSetka=col;canvasSetka->setColorSetka(colorSetka);};
    QColor getColorSetka(){return colorSetka;};
    void setColorAngle(QColor col){colorAngle=col;};
    QColor getColorRiski(){return colorRiski;};
    void setColorRiski(QColor col){colorRiski=col;canvasSetka->setColorRiski(colorRiski);};
    QColor getColorAngle(){return colorAngle;};
    void setColorTextCircul(QColor col){colorTextCircul=col;canvasSetka->setColorTextCircul(colorTextCircul);};
    QColor getColorAxeCircul(){return colorTextCircul;};
    void setEndAngl(double a){endAngl=a; canvasSektor->setEndAngl(endAngl);};
    double getEndAngl(){return endAngl;};
    void setBeginAngl(double a){beginAngl=a; canvasSektor->setBeginAngl(beginAngl);};
    double getBeginAngl(){return beginAngl;};
    //
    void setDXYGist(double dx, double dy);
    void setGistX(long *x);
    void setGistY(long *y);
    void drawGistX();
    void drawGistY();
    
protected:
    QRect  fildView;
    QRect  rectCircul; // содержит область круговой диаграммы
    QColor colorAngle;      // цвет запрещенной области
    QColor colorFon;        // фон окантовывающего прямоугольника
    QColor colorFonCircul;  // основной фон диаграммы
    QColor colorText;       // текст вне поля диаграммы
    QColor colorTextCircul; // текст в поле диаграммы
    QColor colorSetka;      // цвет сетки
    QColor colorRiski;
    QColor colorGist;
    FlagCirculBase flag;
    long left, right, top, bottom;
    long ix, iy, nx, ny, irx, iry,  krx, kry;
    long xCentr, yCentr, R;
    bool error;
    bool flagRangeX; // true, если диапазон изменений аргумента определен
    bool flagRangeY; // true, если диапазон изменений функцииы определен
    double beginAngl, endAngl;
    double zFild, zAngl, zBase, zSetka, zText, zGist;

    QCanvas *canvas;
    QWidget *widget;

    void resizeEvent(QResizeEvent *event);

private:

    QCanvasEllipse *fildDiagramm; // закрашенное круговое поле диаграммы
    MyCanvasSetka  *canvasSetka;  // оцифровка диаграммы
    MyCanvasSektor *canvasSektor; // запрещенный сектор
    MyCanvasPolygon **canvasGistY, **canvasGistX;// гистограммы
    long grraz();

    void resizeMyCanvas(); // подстроить канвас под размер виджета

    bool   flagGist;
    double dxGist, dyGist;
    long   nxGist, nyGist;
    long   *gistX, *gistY;
};

#endif
