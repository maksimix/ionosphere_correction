#ifndef DRAWBASECANVAS_H

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


#define DRAWBASECANVAS_H

/***************************************************************/
/*                                                             */
/*             ������� ��������� ���� �������                  */
/*                                                             */
/* ix          - ������� � �������� ������� ������ ����        */
/*               ���� �������;                                 */
/* iy          - �������� � ��������;                          */
/* xmin        - ����������� �������� �������;                 */
/* xmax        - ������������ �������� �������;                */
/* ymin        - ����������� �������� ��������;                */
/* ymax        - ������������� �������� ��������;              */
/* nx          - ������ � �������� ���� ������� �� ��� ������; */
/* ny          - ������ ���� � �������� �� ��� �������;        */
/* ir          - 0 - �������� ������ ����� �� ����,            */
/*               1 - �������� ������������ �����;              */
/* kxr         - ���������� ����� �������� �� ��� x;           */
/* kyr         - ���������� ����� �������� �� ��� y;           */
/* ipgr        - 0 - �������� ������ ������������ ���,         */
/*               1 - �������� ����� ������ �������;            */
/* isim        - ������������ ������ �������� ���������;       */
/* left        - ����� ������� �������;                        */
/* top         - ������� ������� �������;                      */
/* right       - ������ ������� �������;                       */
/* bottom      - ������ ������� �������;                       */
/* infx        - ������������ ��������, ������������� �� ��� x;*/
/* infy        - ������������ ��������, ������������� �� ��� y;*/
/* otst        - ������ � �������� �� �������� ����� ����      */
/*               �������.                                      */
/*                                                             */
/*VGG                                                          */
/***************************************************************/

#ifndef __MaxKolMarkFild
const int MaxKolMarkFild=300;
#define __MaxKolMarkFild
#endif

class MyCanvasMarker : public QCanvasLine
{
public:
    MyCanvasMarker(QCanvas *canvas, double xMin, double xMax, double yMin, double yMax,
                   long iX, long iY, long nX, long nY);
    void setGeometry(long iX, long iY, long nX, long nY);
    void setMinMax(double xMin, double xMax, double yMin, double yMax);
    void setColorMarker(QColor c);
    void setCenterMarker(double x, double y);
    void setOtst(int i){otst=i;};
private:
    QCanvas *canvas;
    virtual void drawShape( QPainter & painter );
    QColor colorMarker;
    double X, Y;
    double xmin,xmax,ymin,ymax,sizex,sizey;
    long   ix,iy,nx,ny,otst;
    long   xH1,xH2,xV1,xV2,yH1,yH2,yV1,yV2;
};

class MyRectCanvasSetka : public QCanvasRectangle
{
public:
    MyRectCanvasSetka(QCanvas *canvas, QRect &r,
                      double *xmin, double *xmax, double *ymin,double *ymax,
                      long *iX, long *iY, long *nX, long *nY,
                      long *Top, long *Left, long *Bottom, long *Right,
                      long kRx=8, long kRy=8, long iR=1);

    ~MyRectCanvasSetka();

    void setFlagText(bool flag){flagText=flag;};
    void setColorText(QColor c){colorText=c;};
    void setColorRiski(QColor c){colorRiski=c;};
    void setColorSetka(QColor c){colorSetka=c;};
    void setColorAxe(QColor col){colorAxe=col;};
    
    bool getError(){return error;};
    //void setInf(const char *infX, const char *infY){infx=infX; infy=infY;};
    void setInf( const QString &infX, const QString &infY ){ infx=infX; infy=infY; };

    void setIpgr(long i){ipgr=i;};
    long getIpgr(){return ipgr;};
    void setFildView(QRect &r){fullView=r;};
    QSize grraz();

private:
    bool error;
    bool flagText;
    long ir, krx, kry, krx0, kry0, isw, ihw, maxSizeChar;
    long *ix, *iy, *nx, *ny;
    long *top, *left, *right, *bottom;
    long ipgr;
    double *xmin, *xmax, *ymin, *ymax;
    QRect fullView;
    QColor colorSetka, colorRiski, colorText, colorAxe;
    virtual void drawShape( QPainter & painter );
    QFont *font;
    QFontMetrics *fm;
    //const char *infx, *infy;
    QString infx, infy;
    double zxmin,hx,xmin1,hzx,z,z1,
           zymin,hy,ymin1,hzy;
    long   mdx,mdy,iy1,ix1,nrx,nry,
           kporx,kpory,lx,ly,i,j,mz,k,
           keyx,  // ������� ��������� ����� ��������� (��������� �������)
           keyy,
           kx,ky,isim,
           maxx,maxy,
           otst, otstBegX, otstBegY,
           mx,my;   // ����� ������ ����� �������
    
    void grstan(double xmin, double xmax,
                long nx, long kr,
                double *zxmin, double *hzx,
                long *kxr,
                double *hx,
                long *kporx,
                double *xmin1,
                long *kx);
    
    void khz1(double r, double *hzx, double *zxm,
              long *kxr1,
              double xi1, double xi2, double xa1);
    
    void khz2(double r, double *hzx, double *zxm,
              long *kxr1,
              double xi1, double xi2, double xa1);
    
    void khz3(double r, double *hzx, double *zxm,
              long *kxr1,
              double xi1, double xi2, double xa1);

public:
    void setSize(int w, int h)
    {
        QCanvasRectangle::setSize(w,h);
    };

    void setOtst(long i){otst=i;};
    void setOtstBegX(long i){otstBegX=i;};
    void setOtstBegY(long i){otstBegY=i;};
};

class DrawBaseCanvas: public QCanvasView
{

    Q_OBJECT

  public:
    DrawBaseCanvas(QCanvas *viewing, QWidget *parent,
                   //char *infx, char *infy,
                   const QString &infX, const QString &infY,
                   double xmin, double xmax, double ymin, double ymax,
                   long ir=1, long ipgr=1, long krx=8, long kry=8);
    DrawBaseCanvas(QCanvas *viewing, QWidget *parent,
                   //char *infx, char *infy,
                   const QString &infX, const QString &infY,
                   long ir=1, long ipgr=1, long krx=8, long kry=8);
    ~DrawBaseCanvas();

    double getXmin(){return xmin;};
    double getYmin(){return ymin;};
    double getXmax(){return xmax;};
    double getYmax(){return ymax;};
    void   setMinMax(double xMin, double xMax, double yMin, double yMax);
    void   setOtst(long i){otst=i; canvasSetka->setOtst(otst); canvasMarker->setOtst(otst);};
    void   setOtstBegX(long i){otstBegX=i; canvasSetka->setOtstBegX(otstBegX);};
    void   setOtstBegY(long i){otstBegY=i; canvasSetka->setOtstBegY(otstBegY);};
    long   getOtst(){return otst;};
    long   getOtstBegX(){return otstBegX;};
    long   getOtstBegY(){return otstBegY;};
    void   setKrx(long i){krx=i;};
    long   getKrx(){return krx;};
    void   setKry(long i){kry=i;};
    long   getKry(){return kry;};
    void   setIr(long i){ir=i;};
    long   getIr(){return ir;};
    void   setIpgr(long i){ipgr=i;};
    long   getIpgr(){return ipgr;};
    void   setIxy(long x, long y){ix=x; iy=y;};
    void   getIxy(long &x, long &y){x=ix; y=iy;};
    void   setNxy(long x, long y){nx=x; ny=y;};
    void   getNxy(long &x, long &y){x=nx; y=ny;};
    void   setMaxKolMarkFild(int n){maxKolMarkFild=n;};    // ������������� ������������ ����� ����� ���������
    int    getMaxKolMarkFild(){return maxKolMarkFild;};
    void   setRealBegX(double x){realBegX=x;};
    void   setRealBegY(double y){realBegY=y;};

    void   setKolMarkFild(int n, bool allChanged=false); // ������ ����� ���������� ��������

    void   setColorFon(QColor col)
    {
        colorFon=col;
        setBackgroundColor(colorFon);
        canvas->setBackgroundColor(colorFon);
    };

    QColor getColorFon(){return colorFon;};
    void setColorText(QColor col){colorText=col;};
    QColor getColorText(){return colorText;};
    void setColorSetka(QColor col){colorSetka=col;};
    QColor getColorSetka(){return colorSetka;};
    void setColorAxe(QColor col){colorAxe=col;};
    QColor getColorAxe(){return colorAxe;};
    void setColorLineFild(QColor col){colorLineFild=col;};
    QColor getColorLineFild(){return colorLineFild;};
    void setColorMarkFild(QColor col){colorMarkFild=col;};
    QColor getColorMarkFild(){return colorMarkFild;};

    void resizeMyCanvas();

    void setFlagMouseDesable(){flagMouseDesable=true;};
    void setFlagMouseEnable(){flagMouseDesable=false;};

    void setMarkFild(double x1, double x2, int n);

    void setFlagText(bool flag){flagText=flag; canvasSetka->setFlagText(flag);};

    void setTextMetka(QString &str); // ����� ����� ������� ����

void setNumberWindow(long n){numberWindow=n;};

protected:
    QRect fildView;
    QRect rClear; // ������� ��������
    QColor colorFon;
    QColor colorText;
    QColor colorSetka;
    QColor colorAxe;
    QColor colorLineFild;   // ���� ���� ��� ��������
    QColor colorMarkFild;   // ���� ���������� ��������
    QColor colorSelectFild; // ���� ���������� �������
    short  *divot;  // ������� ����������
    long left, right, top, bottom;
    long ix, iy, nx, ny, ir, ipgr, krx, kry;
    long otst, otstBegX, otstBegY;
    //char *infx,*infy;
    QString infx, infy;
    double xmin, xmax, ymin, ymax;
    bool error;
    bool flagRangeX; // true, ���� �������� ��������� ��������� ���������
    bool flagRangeY; // true, ���� �������� ��������� �������� ���������
    bool flagMinMax; // true - ������ ����������� � ������������ �������� �� X � Y
    bool flagText;
    QSize size;      // �������� ������� �� ������� ������ ���� ���� �� ������ ��������� �������

    MyRectCanvasSetka  *canvasSetka;   // ��������� �������
    MyCanvasMarker     *canvasMarker;

    QCanvas *canvas;
    QWidget *widget;
    
    double zFild, zAngl, zBase, zSetka, zLineFild, zMarkFild, zTextMetka, zSelectFild;
    void resizeEvent(QResizeEvent *event);
    virtual void contentsMousePressEvent ( QMouseEvent * e );
    virtual void contentsMouseReleaseEvent ( QMouseEvent * e );
    virtual void contentsMouseMoveEvent ( QMouseEvent * e );
    virtual void contentsMouseDoubleClickEvent ( QMouseEvent * e );
    virtual bool eventFilter ( QObject * obj, QEvent * e );
private:
    QCanvasRectangle *fildDiagramm; // ����������� ���� �������
    QCanvasRectangle      *lineFild;     // ���� ��� ��������
    QCanvasRectangle      *lineMarkFild[MaxKolMarkFild]; // ���������� �������
    QCanvasRectangle      *lineSelectFild; // ���������� �������
    QCanvasText      *canvasText;

    QFontMetrics *fm;
    QFont        *font;

    double xMarkBegin[MaxKolMarkFild], xMarkEnd[MaxKolMarkFild]; // ���������� ������������� ��������
    int kolMarkFild; // ���������� ���������� �����   (�� ����� 10)
    int maxKolMarkFild; // ������� ��������� ������������ �������� ����� ���������� �����
    QPoint pointBegin, pointEnd, pointMetka;
    bool flagMouseLeftPress, flagMouseRelease,
         flagMouseMove, flagMouseMidPress,
         flagMouseRihtPress;
    bool flagKeyCtrl,flagKeyShift;
    bool flagMouseDesable;
    long numberWindow;

    double realBegX, realBegY; // �������� ��������� �������� �� X � Y
    double posX,posY; // �������� �������� ������� � ����� ������������ �������

public slots:
    void slotKeyPressEvent(QKeyEvent *e);
    void slotKeyReleaseEvent(QKeyEvent *e);
    void slotSetMarkerToPosition(double, double);
    void slotSetMarkerHide();

signals:
    void signalChangeMarkFild(int kol, double x1, double x2);
    void signalChangeSelectFild(double x1, double x2);
    void signalResetSelectFild();
    void signalResetMarkFild(); // ������ � ���, ��� ���������� ���� ��������
    void signalPressMouse(long, ButtonState);
    void signalMidReleasedMouse();
    void signalRealValue(double, double);
    void signalDelSector(double);
    void signalRight();
    void signalPlus();
    void signalLeft();
    void signalMinus();
};

#endif
