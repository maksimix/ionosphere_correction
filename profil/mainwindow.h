#include <math.h>
#include <qstring.h>
#include <qsplitter.h>
#include <qlayout.h>
#include "../iri_3d/iri_3d_new.h"
#include "./ui/ui_profilwindow.h"
#include "./ui/ui_correction.h"
#include "../draw_qt4/drawmem.h"
#include "../draw_qt4/draw.h"

class MainWindow : public QDialog, Ui::ProfilWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void slotExit();
    void slotDraw();
    void slotChangeLat(int);
    void slotChangeLon(int);
    void slotChangeTime(int);
    void slotLat0();
    void slotLon0();
    void slotTimeBeg();
    void slotTimeEnd();
    void slotLat();
    void slotLon();
    void slotTime();
    void slotHMin(int);
    void slotHMax(int);
    void slotFMin(int);
    void slotFMax(int);
    void slotOptions();
    void slotSave();
    void slotRMax();
    double path(double lon0, double lat0, double lon, double lat, double &s0, double &alf, double &alf1);
    void slotCorrection();

private:
    double lat0,lon0,time0,time1,timeTemp0,timeTemp1;
    double lat,lon,time;
    bool flagDraw;
    bool flagExit;
    bool flagUT;
    bool flagWIG; // ��������� ��������� ����������
    bool keyes;
    bool flagCorr;
    double rmax,zmin,dz,zmax;
    long nx,ny,nz;
    double fi1,teta1,r1,nu,v,vfi,vteta,vr,vt;
    int i,iMax;
    int iyear, iday;
    double W,IG,w,ig;
    QString str;
    DrawMem *drawMemF, *drawMemN;
    Draw *drawF, *drawN;
    QSplitter   *splitter;
    QGridLayout *grid;
    double fPl[1000],h[1000],nU[1000];
    double fMin, fMax, hMin, hMax, nMin,nMax;
    double latB,lonB,latE,lonE,latS,lonS;
    double latIon_1,lonIon_1,tIon_1,f0E_1,hmE_1,f0F1_1,hmF1_1,f0F2_1,hmF2_1,f0Es_1,hmEs_1;
    double latIon_2,lonIon_2,tIon_2,f0E_2,hmE_2,f0F1_2,hmF1_2,f0F2_2,hmF2_2,f0Es_2,hmEs_2;

    void reCalc();
    void newProf();
};
