#ifndef DRAWBASE_H

#ifndef QPAINTER_H
#include <qpainter.h>
#endif
#ifndef QSTRING_H
#include <qstring.h>
#endif
#ifndef QWIDGET_H
#include <qwidget.h>
#endif

#define DRAWBASE_H

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

class DrawBase: public QWidget
{
    Q_OBJECT

  public:
    DrawBase(QWidget *parent,
             //char *infX, char *infY,
             const QString &infX, const QString &infY,
             double xmin, double xmax, double ymin, double ymax,
             long ir=1, long ipgr=1, long kxr=8, long kyr=8);
    DrawBase(QWidget *parent,
             //char *infX, char *infY,
             const QString &infX, const QString &infY,
             long ir=1, long ipgr=1, long kxr=8, long kyr=8);
    ~DrawBase();
    void   setXmin(double x)
    {
        xmin=x;
        //repaint(false);
        update();
    };
    double getXmin(){return xmin;};
    void   setYmin(double y)
    {
        ymin=y;
        //repaint(false);
        update();
    };
    double getYmin(){return ymin;};
    void   setXmax(double x)
    {
        xmax=x;
        //repaint(false);
        update();
    };
    double getXmax(){return xmax;};
    void   setYmax(double y)
    {
        ymax=y;
        //repaint(false);
        update();
    };
    double getYmax(){return ymax;};
    void   setXYminmax(double x1, double x2, double y1, double y2)
    {
        xmin=x1;
        xmax=x2;
        ymin=y1;
        ymax=y2;
        //repaint(false);
        update();
    };
    void   setOtst(long i){otst=i;};
    long   getOtst(){return otst;};
    void   setOtstBegX(long i) { otstBegX=i; };
    void   setOtstBegY(long i) { otstBegY=i; };
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
    void setColorSetka(QColor col){colorSetka=col;};
    QColor getColorSetka(){return colorSetka;};
    void setColorAxe(QColor col){colorAxe=col;};
    QColor getColorAxe(){return colorAxe;};
    void setLatch(bool b){latch=b;};
    void setInfXY( const QString &infX, const QString &infY );//char* infX, char* infY);
    void setFlagMouseDesable(){flagMouseDesable=true;};
    void setFlagMouseEnable(){flagMouseDesable=false;};

  protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void mousePressEvent ( QMouseEvent * e );
    virtual void mouseReleaseEvent ( QMouseEvent * e );
    virtual void mouseMoveEvent ( QMouseEvent * e );
    virtual void mouseDoubleClickEvent ( QMouseEvent * e );
    QRect fildView;
    QRect rClear; // ������� ��������
    QColor colorFon;
    QColor colorText;
    QColor colorSetka;
    QColor colorAxe;
    short  *divot;  // ������� ����������
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
    long grraz(QPainter &p);
    QPixmap *pix;

  private:
    bool flagMouseLeftPress, flagMouseRelease,
         flagMouseMove, flagMouseMidPress,
         flagMouseRihtPress;
    bool flagMouseDesable;
    QPoint pointBegin, pointEnd, pointMetka;
    double posX,posY; // �������� �������� ������� � ����� ������������ �������

signals:
    void signalRealValue(double, double);
};

#endif
