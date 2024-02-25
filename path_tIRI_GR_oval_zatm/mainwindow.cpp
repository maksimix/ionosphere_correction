using namespace std;

//#include <qapplication.h>
#include <iostream>
//#include <qlineedit.h>
//#include <qslider.h>
//#include <qcheckbox.h>
//#include <qframe.h>
//#include <qheader.h>
//#include <qlabel.h>
//#include <qlineedit.h>
//#include <qlistview.h>
//#include <qpushbutton.h>
//#include <qradiobutton.h>
//#include <qspinbox.h>
//#include <qlayout.h>
//#include <qvariant.h>
//#include <qtooltip.h>
//#include <qwhatsthis.h>
//#include <qtable.h>
//#include <qcombobox.h>
//#include <qbuttongroup.h>
#include <QFileDialog>
#include <qmessagebox.h>
#include "./ui/ui_path.h"
#include "mainwindow.h"

int mainPath(int argc, char *argv[]);

MainWindow::MainWindow(QDialog* parent, int argc, char **argv)
{
    argC=argc;
    argV=argv;
    nPoint=0;
    nF=5;
    hMin=.0;
    hMax=400.;
    fMin=.0;
    fMax=20.;
    sMin=.0;
    sMax=2000.;
    kolTr=0;
    setupUi(this);

    if (argC>1)
    {
        strcpy(nameFile,argV[1]);
        pushButtonRun->setEnabled ( true );
    }
    else
        pushButtonRun->setEnabled ( false );

    for(int i=0; i<MaxKolTr; i++)
    {
        pointTr[i]=0;
        for(int j=0; j<MaxPointTr; j++)
        {
            hTr[i][j]=.0;
            sTr[i][j]=.0;
        }
    }

    gridI=new QGridLayout(frameIon);
    gridI->setSpacing(0);
    gridI->setMargin(0);
    drawI = new Draw( frameIon, nF, "fpl, MHz", "h, km", fMin, fMax, hMin, hMax, 1, 1, 17, 9);

    gridI->addWidget(drawI,0,0);

    drawI->setFlagMouseEnable();
    drawI->setOtst(0);
    drawI->setOtstBegX(40);
    drawI->setOtstBegY(0);
    drawI->setColorFon(QColor(255,249,201));
    drawI->setSizePoint(0);
    drawI->setColorLine(QColor(0,0,255),0);
    drawI->setColorLine(QColor(255,0,0),1);
    drawI->setPenWidth(1,0);
    drawI->setPenWidth(1,1);

    gridT=new QGridLayout(frameTrek);
    gridT->setSpacing(0);
    gridT->setMargin(0);
    drawT=0;
    drawT = new Draw2( frameTrek, MaxKolTr, "s, km", "h, km", sMin, sMax, hMin, hMax, 1, 1, 17, 9);

    gridT->addWidget(drawT,0,0);
    drawT->setColor(true);
    drawT->setFlagMouseEnable();
    drawT->setOtst(0);
    drawT->setOtstBegX(40);
    drawT->setOtstBegY(0);
    //drawT->setColorFon(QColor(255,249,201));
    drawT->setColorFon(QColor(255,255,255));

    drawT->setSizePoint(0);
    for(int i=0; i<MaxKolTr; i++)
    {
        drawT->setColorLine(QColor(0,0,255),i);
        drawT->setPenWidth(1,i);
    }

}


MainWindow::~MainWindow()
{
}

void MainWindow::slotExit()
{
    qApp->quit();
}

void MainWindow::slotDraw()
{
}

void MainWindow::slotRun()
{
    static int c=0;
    QColor col;
    if (argC<2)
        argC=2;
    argV[1]=nameFile;

    if (c>=0)
    {
        if (drawT)
            drawT->resetData();
        drawI->resetData();
    }
    pushButtonRun->setEnabled ( false );
    pushButtonExit->setEnabled ( false );
    pushButtonRead->setEnabled ( false );
    qApp->processEvents();

    c%=3;
    switch(c)
    {
    case 0:
        col=QColor(0,0,0);
        break;
    case 1:
        col=QColor(255,255,255);
        break;
    case 2:
        col=QColor(200,200,200);
    }

    if (drawT)
    {
        for(int i=0; i<MaxKolTr; i++)
        {
            drawT->setColorLine(col,i);
        }
    }
    for(int i=0; i<5; i++)
    {
        drawI->setColorLine(col,i);
    }

    mainPath(argC,argV);

    pushButtonRun->setEnabled ( true );
    pushButtonExit->setEnabled ( true );
    pushButtonRead->setEnabled ( true );

    c++;
}

void drawIon(double *fpl, double *hpl, int nf, int npoint, double hmin, double hmax, double fmax)
{
    int i,j;

    mainwindow->fMax=fmax;
    //mainwindow->hMin=hmin;
    mainwindow->hMax=hmax;
    mainwindow->nF=nf;
    mainwindow->nPoint=npoint;

    mainwindow->drawI->setXYminmax(mainwindow->fMin, mainwindow->fMax, mainwindow->hMin, mainwindow->hMax);
    qApp->processEvents();


    for(i=mainwindow->nF; i<5; i++)
    {
        mainwindow->drawI->setY(&(mainwindow->hPl[100*i]), 0, i);
        mainwindow->drawI->setX(&(mainwindow->fPl[100*i]), 0, i);
    }

    for(i=0; i<mainwindow->nF; i++)
    {
        for(j=0; j<mainwindow->nPoint; j++)
        {
            mainwindow->fPl[100*i+j]=fpl[100*i+j];
            mainwindow->hPl[100*i+j]=hpl[100*i+j];
            //printf("\n %f  %f",mainwindow->hPl[100*i+j],mainwindow->fPl[100*i+j]);
        }
        mainwindow->drawI->setY(&(mainwindow->hPl[100*i]), mainwindow->nPoint, i);
        mainwindow->drawI->setX(&(mainwindow->fPl[100*i]), mainwindow->nPoint, i);
        mainwindow->drawI->upDate();
        qApp->processEvents();
    }

    mainwindow->sMin=sMinIon;
    mainwindow->sMax=sMaxIon;
    mainwindow->drawT->setXYminmax(mainwindow->sMin, mainwindow->sMax, mainwindow->hMin, mainwindow->hMax);
    mainwindow->drawT->reset();

    mainwindow->drawT->setXBegDx(mainwindow->sMin, dsIon);
    mainwindow->drawT->setYBegDy(hminIon, dhIon);
    mainwindow->drawT->setNormAmp(fmaxIon);
    mainwindow->drawT->setMinAmp(0.0);
    for(i=0; i<MaxSion; i++)
    {
        //((DrawPoligonMemFull*)mainwindow->drawT)->setY(&fplIon[i][0],MaxHion);
        mainwindow->drawT->setY(&fplIon[i][0],MaxHion);
        qApp->processEvents();
    }
}

void drawTrek(double *s, double *h, long p)
{
    static bool flag=true;
    static int  k=0;

    if (!(mainwindow->drawT))
        return;
    if (flag)
    {
        //mainwindow->drawT->setXYminmax(mainwindow->sMin, mainwindow->sMax, mainwindow->hMin, mainwindow->hMax);
        //qApp->processEvents();
        for(int i=0; i<MaxKolTr; i++)
        {
            mainwindow->drawT->setY(&(mainwindow->hTr[i][0]), 0, i);
            mainwindow->drawT->setX(&(mainwindow->sTr[i][0]), 0, i);
        }
        flag=false;
    }

    mainwindow->pointTr[mainwindow->kolTr]=p;
    for(int i=0; i<p; i++)
    {
        mainwindow->sTr[mainwindow->kolTr][i]=s[i];
        mainwindow->hTr[mainwindow->kolTr][i]=h[i];
        //printf("\ns=%f  h=%f n=%d",s[i],h[i],p);
    }
    mainwindow->drawT->setY(&(mainwindow->hTr[mainwindow->kolTr][0]), mainwindow->pointTr[mainwindow->kolTr], mainwindow->kolTr);
    mainwindow->drawT->setX(&(mainwindow->sTr[mainwindow->kolTr][0]), mainwindow->pointTr[mainwindow->kolTr], mainwindow->kolTr);
    mainwindow->drawT->upDate();
    qApp->processEvents();
    (mainwindow->kolTr)++;
    if (mainwindow->kolTr>=MaxKolTr)
    {
        mainwindow->kolTr=0;
    }

}

void drawInf(char *inf)
{
    QString str(inf);
    mainwindow->lineEditInf->setText(str);
    qApp->processEvents();
}

void MainWindow::slotRead()
//
// ввод имени входного файла
//
{
    QString fn;
    fn = QFileDialog::getOpenFileName(0, 0, 0, tr("InFiles (*.dat);;All Files (*)"));
    QFileInfo fi(fn);

    //Проверка длины переменной имени файла (д.б. не нулевым)
    if (fn.isEmpty())
    {
        QMessageBox::critical(this,tr("Error!"),
                              tr("Name File ")
                              +"\""+fi.absoluteFilePath()+"\"\n"
                              +tr("is not exists!"));
        fn=QString::null;
    }

    //Проверка существования директории
    else
        if ( !fi.dir().exists() )
        {
            QMessageBox::critical(this,tr("Error!"),
                                  tr("Directory ")
                                  +"\""+fi.absoluteFilePath()+"\"\n"
                                  +tr("is not exists!"));
            
            fn=QString::null;
        }
        
        //Проверка на читаемость директории (права доступа)
        else
            if ( !fi.dir().isReadable() )
            {
                QMessageBox::critical(this,tr("Error!"),
                                      tr("Could not enter directory")
                                      +"\n\""+fi.absoluteFilePath()+"\"!\n"
                                      +tr("You don't have access rights!"));
                
                fn=QString::null;
            }

            //Если всё нормально то:
            else
            {
                if(fi.suffix()!="dat")
                {
                    fn+=".dat";
                    fi.setFile(fn);
                }
        
                if (!fi.exists())
                {
                    QMessageBox::critical(this,tr("Error!"),
                                          tr("Reading aborted")+"\"\n");
                    fn=QString::null;
                }
            }
    if (fn.length()>0)
    {
        strcpy(nameFile,fn.toUtf8().constData());
        printf("\n%s\n",nameFile);
    }
    else
        strcpy(nameFile,"");
    if (strlen(nameFile)>0)
        pushButtonRun->setEnabled ( true );
    else
        pushButtonRun->setEnabled ( false );
}

void MainWindow::slotSaveImageWidget(QWidget *w, QString fn, const QString &filt)
{

    if ( !w->isVisible() )
	return;			// don't eat resources when iconified

    QPixmap p = QPixmap::grabWidget ( w );

    if ( !p.isNull() )
    {
        if ( !fn.isEmpty() )
        {
            QFileInfo fi(fn);

            if ( filt=="png" || fi.suffix()=="png" || fi.suffix()=="PNG" )
            {
                if(fi.suffix()!="png" || fi.suffix()==!"PNG" )
                {
                    fn=fn+".png";
                    fi.setFile(fn);
                }
                p.save( fn, "PNG" );
            }

            if ( filt=="bmp" || fi.suffix()=="bmp" || fi.suffix()=="BMP" )
            {
                if(fi.suffix()!="bmp" || fi.suffix()!="BMP")
                {
                    fn=fn+".bmp";
                    fi.setFile(fn);
                }
                p.save( fn, "BMP" );
            }
        }
    }
}

void drawFrame(char *name)
{
    mainwindow->slotSaveImageWidget((QWidget*)(mainwindow->frameAll),QString(name),QString("png"));
}

