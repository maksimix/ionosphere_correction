#include <math.h>
#include <QWidget>
#include <QDialog>
#include <qstring.h>
#include <qsplitter.h>
#include <qlayout.h>
#include "../iri_3d/iri_3d_new.h"
#include "./ui/ui_path.h"
#include "./paths.h"
#include "../draw/drawpoligonmemfull.h"
#include "../draw/drawmem.h"
#include "../draw/draw.h"
#include "../draw/draw2.h"

class MainWindow : public QDialog, Ui::Path
{
    Q_OBJECT

public:
    MainWindow(QDialog* parent, int argc, char **argv);
    ~MainWindow();

public slots:
    void slotExit();
    void slotDraw();
    void slotRead();
    void slotRun();
    friend void drawIon(double *fpl, double *hpl, int nf, int npoin, double hMin, double hMax, double fMax);
    friend void drawTrek(double *sTr, double *hTr, long pointTr);
    friend void drawInf(char *inf);
    friend void drawClear();
private:
    int argC;
    char **argV;
    char nameFile[256];
    double fPl[500], hPl[500], hMin, hMax;
    double sTr[MaxKolTr][MaxPointTr], hTr[MaxKolTr][MaxPointTr];
    int    pointTr[MaxKolTr],kolTr;
    double fMin, fMax;
    double sMin, sMax;
    int nPoint, nF;
    //DrawMem *drawMemI, *drawMemT;
    Draw2 *drawMemT;
    Draw *drawI;
    QGridLayout *gridI, *gridT;
};

extern MainWindow *mainwindow;
