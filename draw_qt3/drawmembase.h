#ifndef DRAWMEMBASE_H

#ifndef QPAINTER_H
#include <qpainter.h>
#endif
#ifndef QSTRING_H
#include <qstring.h>
#endif
#ifndef QWIDGET_H
#include <qwidget.h>
#endif
#include <qpixmap.h>
#include <qrect.h>

#define DRAWMEMBASE_H

#if defined( GL )
#include <qgl.h>
#define  WIDGET  QGLWidget
#else
#include <qwidget.h>
#define  WIDGET  QWidget
#endif

#ifndef __MaxKolMarkFild
const int MaxKolMarkFild=300;
#define __MaxKolMarkFild
#endif

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

class MyMarker
{
public:
    MyMarker(double xMin, double xMax, double yMin, double yMax,
             long iX, long iY, long nX, long nY);
    void setGeometry(long iX, long iY, long nX, long nY);
    void setMinMax(double xMin, double xMax, double yMin, double yMax);
    void setColorMarker(QColor c);
    void setCenterMarker(double x, double y);
    void draw( QPainter & painter );
    void setOtst(long i){otst=i;};
private:
    QColor colorMarker;
    double X, Y;
    double xmin,xmax,ymin,ymax,sizex,sizey;
    long   ix,iy,nx,ny,otst;
    long   xH1,xH2,xV1,xV2,yH1,yH2,yV1,yV2;
};


class DrawMemBase: public WIDGET
{
    Q_OBJECT

  public:
    DrawMemBase(QWidget *parent,
                //char *infX, char *infY,
                const QString &infX, const QString &infY,
                double xmin, double xmax, double ymin, double ymax,
                long ir=1, long ipgr=1, long kxr=8, long kyr=8);
    DrawMemBase(QWidget *parent,
                //char *infX, char *infY,
                const QString &infX, const QString &infY,
                long ir=1, long ipgr=1, long kxr=8, long kyr=8);
    ~DrawMemBase();
    void   setXmin(double x);
    double getXmin(){return xmin;};
    void   setYmin(double y);
    double getYmin(){return ymin;};
    void   setXmax(double x);
    double getXmax(){return xmax;};
    void   setYmax(double y);
    double getYmax(){return ymax;};
    void   setXYminmax(double x1, double x2, double y1, double y2);
    void   setOtst(long i){otst=i; marker->setOtst(otst);};
    long   getOtst(){return otst;};
    void   setOtstBegX(long i){otstBegX=i;};
    void   setOtstBegY(long i){otstBegY=i;};
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
    void setColorFon(QColor col){colorFon=col;};
    QColor getColorFon(){return colorFon;};
    void setColorText(QColor col){colorText=col;};
    QColor getColorText(){return colorText;};
    void setColorTextMetka(QColor col){colorTextMetka=col;};
    QColor getColorTextMetka(){return colorTextMetka;};
    void setColorSetka(QColor col){colorSetka=col;};
    QColor getColorSetka(){return colorSetka;};
    void setColorAxe(QColor col){colorAxe=col;};
    QColor getColorAxe(){return colorAxe;};
    void setColorMarkFild(QColor col){colorMarkFild=col;};
    QColor getColorMarkFild(){return colorMarkFild;};
    void setColorLineFild(QColor col){colorLineFild=col;};
    QColor getColorLineFild(){return colorLineFild;};
    void   setLatch(bool b){latch=b;};
    void   setInfXY( const QString &infX, const QString &infY );//char* infX, char* infY);
    void   setFlagMouseDesable(){flagMouseDesable=true;};
    void   setFlagMouseEnable(){flagMouseDesable=false;};
    void   setMaxKolMarkFild(int n){maxKolMarkFild=n;};    // ������������� ������������ ����� ����� ���������
    int    getMaxKolMarkFild(){return maxKolMarkFild;};
    void   setKolMarkFild(int n); // ������ ����� ���������� ��������
    void   setNumberWindow(long n){numberWindow=n;};
    void   setMarkFild(double x1, double x2, int n);
    void   setCenterMarker(double x, double y);
    void   setRealBegX(double x){realBegX=x;};
    void   setRealBegY(double y){realBegY=y;};
    bool   getShowMarker(){return flagMarker;};
    void   setShowMarker(bool b){flagMarker=b;};

  protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void mousePressEvent ( QMouseEvent * e );
    virtual void mouseReleaseEvent ( QMouseEvent * e );
    virtual void mouseMoveEvent ( QMouseEvent * e );
    virtual void mouseDoubleClickEvent ( QMouseEvent * e );
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    void drawMetka(QPainter &p);
    QRect fildView;
    QRect rClear; // ������� ��������
    QColor colorFon;
    QColor colorText;
    QColor colorTextMetka;
    QColor colorSetka;
    QColor colorAxe;
    QColor colorMarkFild;   // ���� ���������� ��������
    QColor colorSelectFild; // ���� ���������� �������
    QColor colorLineFild;   // ���� ���� ��� ��������
    long left, right, top, bottom;
    long ix, iy, nx, ny, ir, ipgr, krx, krx0, kry, kry0;
    long otst, otstBegX, otstBegY;
    //char *infx,*infy;
    QString infx, infy;
    double xmin, xmax, ymin, ymax;
    bool error;
    bool flagRangeX; // true, ���� �������� ��������� ��������� ���������
    bool flagRangeY; // true, ���� �������� ��������� �������� ���������
    bool flagMinMax; // true - ������ ����������� � ������������ �������� �� X � Y
    bool latch; // ������� ����������� ����� ������
    QSize grraz(QPainter &p);
    QPixmap *pix;
    QSize size;

  public slots:
      void slotSetMarkerToPosition(double, double);
      void setTextMetka(QString &str); // ����� ����� ������� ����

  private:
    bool flagMouseLeftPress, flagMouseRelease,
         flagMouseMove, flagMouseMidPress,
         flagMouseRihtPress;
    bool flagMouseDesable;
    bool flagKeyCtrl;
    QPoint pointBegin, pointEnd, pointMetka, pointTemp;
    double posX,posY; // �������� �������� ������� � ����� ������������ �������
    double realBegX, realBegY; // �������� ��������� �������� �� X � Y
    QRect  lineMarkFild[MaxKolMarkFild]; // ���������� �������
    QRect  lineSelectFild; // ���������� �������
    QRect lineCtrl;
    double xMarkBegin[MaxKolMarkFild], xMarkEnd[MaxKolMarkFild]; // ���������� ������������� ��������
    int kolMarkFild; // ���������� ���������� �����   (�� ����� 10)
    int maxKolMarkFild; // ������� ��������� ������������ �������� ����� ���������� �����
    long numberWindow;
    long otstup;
    bool flagResize;
    bool flagIn;
    bool flagMarker;
    QFont *font;
    QFontMetrics *fm;
    QString metkaText;
    MyMarker *marker;

signals:
    void signalRealValue(double, double);
    void signalResetMarkFild();
    void signalChangeMarkFild(int kol, double x1, double x2);
    void signalChangeSelectFild(double x1, double x2);
    void signalPressMouse(long, ButtonState);
    void signalResetSelectFild();
    void signalReleaseMouseMid();
};

#endif
