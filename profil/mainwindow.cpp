using namespace std;

#include <qapplication.h>
#include <iostream>
#include <qlineedit.h>
#include <qslider.h>
#include <qcheckbox.h>
#include <qframe.h>
//#include <qheader.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qspinbox.h>
//#include <qtable.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qcombobox.h>
#include <qbuttongroup.h>
#include "./ui/ui_profilwindow.h"
#include "./ui/ui_options.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
            QDialog(parent)
{
    lat0=43.*RAD;
    lon0=39.*RAD;
    time0=12.;
    time1=13.;
    lat=lat0;
    lon=lon0;
    time=time0*3600.;
    flagDraw=false;
    flagExit=false;
    flagUT=true;
    keyes=false;
    flagWIG=false;
    iyear=2003;
    iday=1029;
    ig=w=IG=W=.0;
    v=.0;
    nu=.0;
    latB=(43.-10)*RAD;
    lonB=(39.-10.)*RAD;
    latE=(43.+10.)*RAD;
    lonE=(39.+10.)*RAD;
    latS=1.*RAD;
    lonS=1.*RAD;
    latIon_1=lat0/RAD;
    lonIon_1=lon0/RAD;
    tIon_1=time0;
    f0E_1=hmE_1=f0F1_1=hmF1_1=f0F2_1=hmF2_1=f0Es_1=hmEs_1=.0;
    latIon_2=lat0/RAD;
    lonIon_2=lon0/RAD;
    tIon_2=time1;
    f0E_2=hmE_2=f0F1_2=hmF1_2=f0F2_2=hmF2_2=f0Es_2=hmEs_2=.0;
    flagCorr=false;

    setupUi(this);

    str.sprintf("%5.2f",time0);
    lineEditTimeBeg->setText(str);
    lineEditTime->setText(str);
    str.sprintf("%5.2f",time1);
    lineEditTimeEnd->setText(str);
    str.sprintf("%8.3f",lat0/RAD);
    lineEditLat0->setText(str);
    lineEditLat->setText(str);
    str.sprintf("%8.3f",lon0/RAD);
    lineEditLon0->setText(str);
    lineEditLon->setText(str);
    str.sprintf("%8.3f",lonB/RAD);
    lineEditLonB->setText(str);
    str.sprintf("%8.3f",lonE/RAD);
    lineEditLonE->setText(str);
    str.sprintf("%8.3f",latB/RAD);
    lineEditLatB->setText(str);
    str.sprintf("%8.3f",latE/RAD);
    lineEditLatE->setText(str);
    str.sprintf("%8.3f",lonS/RAD);
    lineEditLonS->setText(str);
    str.sprintf("%8.3f",latS/RAD);
    lineEditLatS->setText(str);

    rmax=4000.; zmin=H0*100.; dz=DZ*100.; nz=NZ; nx=NX; ny=NY;

    str.sprintf("%7.1f",rmax);
    lineEditRMax->setText(str);

    splitter=new QSplitter(frameDraw);
    splitter->setOrientation( Qt::Horizontal );
    grid=new QGridLayout(frameDraw);
    grid->addWidget(splitter,0,0);
    grid->setSpacing(0);
    grid->setMargin(0);
    /*
    drawMemF=new DrawMem(splitter,1,tr("f,MHz"),tr("h,km"),fMin, fMax, hMin, hMax, 1, 1, 20, 8);
    drawMemN=new DrawMem(splitter,1,tr("nU,MHz"),tr("h,km"),nMin, nMax, hMin, hMax, 1, 1, 20, 8);

    drawMemF->setFlagMouseEnable();
    drawMemF->setMaxKolMarkFild(1);
    drawMemF->setOtst(0);
    drawMemF->setOtstBegX(40);
    drawMemF->setOtstBegY(0);
    drawMemF->setColorFon(QColor(255,249,201));
    drawMemF->setSizePoint(0);
    drawMemF->setColorLine(QColor(255,0,0),0);
    drawMemF->setPenWidth(1,0);

    drawMemN->setFlagMouseEnable();
    drawMemN->setMaxKolMarkFild(1);
    drawMemN->setOtst(0);
    drawMemN->setOtstBegX(40);
    drawMemN->setOtstBegY(0);
    drawMemN->setColorFon(QColor(255,249,201));
    drawMemN->setSizePoint(0);
    drawMemN->setColorLine(QColor(255,0,0),0);
    drawMemN->setPenWidth(1,0);
*/
    //drawF=new Draw(splitter,1,tr("f,MHz"),tr("h,km"),fMin, fMax, hMin, hMax, 1, 1, 20, 8);
    //drawN=new Draw(splitter,1,tr("log10(nU),MHz"),tr("h,km"),nMin, nMax, hMin, hMax, 1, 1, 20, 8);

    drawF=new Draw(splitter,2,tr("log10(nU); f,MHz"),tr("h,km"),fMin, fMax, hMin, hMax, 1, 1, 20, 8);
    //drawF=new Draw(frameDraw,2,tr("log10(nU); f,MHz"),tr("h,km"),fMin, fMax, hMin, hMax, 1, 1, 20, 8);

    drawF->setFlagMouseEnable();
    drawF->setOtst(0);
    drawF->setOtstBegX(40);
    drawF->setOtstBegY(0);
    drawF->setColorFon(QColor(255,249,201));
    drawF->setSizePoint(0);
    drawF->setColorLine(QColor(0,0,255),0);
    drawF->setColorLine(QColor(255,0,0),1);
    drawF->setPenWidth(1,0);
    drawF->setPenWidth(1,1);
    /*
    drawN->setFlagMouseEnable();
    drawN->setOtst(0);
    drawN->setOtstBegX(40);
    drawN->setOtstBegY(0);
    drawN->setColorFon(QColor(255,249,201));
    drawN->setSizePoint(0);
    drawN->setColorLine(QColor(255,0,0),0);
    drawN->setPenWidth(1,0);
    */

    reCalc();
}


MainWindow::~MainWindow()
{
}

void MainWindow::slotExit()
{
    flagExit=true;
    qApp->quit();
}

void MainWindow::slotDraw()
{
    drawF->setX(fPl,iMax,0);
    drawF->setY(h,iMax,0);
    drawF->setX(nU,iMax,1);
    drawF->setY(h,iMax,1);

    drawF->upDate();
    //drawN->upDate();
}

void MainWindow::slotChangeLat(int l)
{
    lat=lat0+(double)l*RAD;
    str.sprintf("%8.3f",lat/RAD);
    lineEditLat->setText(str);
    newProf();
}

void MainWindow::slotChangeLon(int l)
{
    lon=lon0+(double)l*RAD;
    str.sprintf("%8.3f",lon/RAD);
    lineEditLon->setText(str);
    newProf();
}

void MainWindow::slotChangeTime(int t)
{
    time=(time0+(time1-time0)*(double)t/(double)(sliderTime->maximum()));
    str.sprintf("%5.2f",time);
    lineEditTime->setText(str);
    time*=3600.;
    newProf();
}

void MainWindow::slotLat0()
{
    reCalc();
}

void MainWindow::slotLon0()
{
    reCalc();
}

void MainWindow::slotTimeBeg()
{
    reCalc();
}

void MainWindow::slotTimeEnd()
{
    reCalc();
}

void MainWindow::slotLat()
{
    slotTime();
}

void MainWindow::slotLon()
{
    slotTime();
}

void MainWindow::slotTime()
{
    time=lineEditTime->text().toDouble()*3600.;
    lon=lineEditLon->text().toDouble()*RAD;
    lat=lineEditLat->text().toDouble()*RAD;

    newProf();
}

void MainWindow::reCalc()
{
    if (iri_3dbase)
        delete iri_3dbase;
    if (iri_3dbase2)
        delete iri_3dbase2;

    time0=lineEditTimeBeg->text().toDouble();
    time1=lineEditTimeEnd->text().toDouble();
    lon0=lineEditLon0->text().toDouble()*RAD;
    lat0=lineEditLat0->text().toDouble()*RAD;

    str.sprintf("%5.2f",time0);
    lineEditTime->setText(str);
    str.sprintf("%8.3f",lat0/RAD);
    lineEditLat->setText(str);
    str.sprintf("%8.3f",lon0/RAD);
    lineEditLon->setText(str);

    lon=lon0;
    lat=lat0;
    double t1,t2;

    if (flagUT)
    {
        timeTemp0=time0+25.;
        timeTemp1=time1+25.;
        t1=tIon_1+25.;
        t2=tIon_2+25.;
    }
    else
    {
        timeTemp0=time0;
        timeTemp1=time1;
        t1=tIon_1;
        t2=tIon_2;
    }

    iri_3dbase = new IRI_3D(lon/RAD,lat/RAD,rmax*.01,zmin*.01,dz*.01,nx,ny,nz);
    iri_3dbase->setYear(iyear);
    iri_3dbase->setDay(iday);
    iri_3dbase->setTime(timeTemp0);
    iri_3dbase->setKeyEs(keyes);
    iri_3dbase->setSunActiv(W);
    iri_3dbase->setSunIgActiv(IG);

    iri_3dbase2= new IRI_3D(lon/RAD,lat/RAD,rmax*.01,zmin*.01,dz*.01,nx,ny,nz); // дополнительные профиль
 
    iri_3dbase2->setYear(iyear);
    iri_3dbase2->setDay(iday);
    iri_3dbase2->setTime(timeTemp1);
    iri_3dbase2->setKeyEs(keyes);
    iri_3dbase2->setSunActiv(W);
    iri_3dbase2->setSunIgActiv(IG);

    if (flagCorr)
    {
        iri_3dbase->setKeyCorIon( true );
        iri_3dbase->ioncorr( false, latIon_1,lonIon_1,t1,f0E_1,hmE_1,f0F1_1,hmF1_1,f0F2_1,hmF2_1,f0Es_1,hmEs_1);
        iri_3dbase2->setKeyCorIon( true );
        iri_3dbase2->ioncorr( false, latIon_2,lonIon_2,t2,f0E_2,hmE_2,f0F1_2,hmF1_2,f0F2_2,hmF2_2,f0Es_2,hmEs_2);
    }
    else
    {
        iri_3dbase->setKeyCorIon( false );
        iri_3dbase2->setKeyCorIon( false );
    }

    iri_3dbase->getAppzocsim3DProfil();
    ig=iri_3dbase->getSunIgActiv();
    w =iri_3dbase->getSunActiv();

    iri_3dbase2->getAppzocsim3DProfil();

    zmax=iri_3dbase->getMaxH();
    iMax=(int)((zmax-zmin)/dz+.5);

    fi1=lon;
    teta1=PI05-lat;
    r1=100.*R0+zmin;

    fMin=.0;
    fMax=25.;
    hMin=.0;
    hMax=500.;
    nMin=.0;
    nMax=.0;

    time=time0*3600.;

    for(i=0; i<iMax; i++)
    {
        ionosf(fi1, teta1, r1, time, v, vfi, vteta, vr, vt);
        nuprof(fi1, teta1, r1, time, nu);
        h[i]=r1-100.*R0;
        fPl[i]=sqrt(v);
        nU[i]=log10(nu*1.e6);
        //std::cout<<std::endl<<"r="<<r1-100.*R0<<" v="<<sqrt(v)<<" nu="<<nu<<"  "<<std::flush;
        if (fMax<fPl[i])
            fMax=fPl[i];
        if (hMax<h[i])
            hMax=h[i];
        if (nMax<nU[i])
            nMax=nU[i];
        r1+=dz;
    }

    drawF->resetData();
    cout<<endl<<"iMax="<<iMax<<" fMin="<<fMin<<" fMax="<<fMax<<" hMin="<<hMin<<" hMax="<<hMax<<flush;
    drawF->setX(fPl,iMax,0);
    drawF->setY(h,iMax,0);
    drawF->setX(nU,iMax,1);
    drawF->setY(h,iMax,1);

    drawF->setXYminmax(fMin, fMax, hMin, hMax);
    drawF->upDate();

}

void MainWindow::slotHMin(int h)
{
    hMin=(double)h;
    drawF->setXYminmax(fMin, fMax, hMin, hMax);
}

void MainWindow::slotHMax(int h)
{
    hMax=(double)h;
    drawF->setXYminmax(fMin, fMax, hMin, hMax);
}

void MainWindow::slotFMin(int f)
{
    fMin=(double)f/10.;
    drawF->setXYminmax(fMin, fMax, hMin, hMax);
}

void MainWindow::slotFMax(int f)
{
    fMax=(double)f/10.;
    drawF->setXYminmax(fMin, fMax, hMin, hMax);
}

void MainWindow::newProf()
{
    fi1=lon;
    teta1=PI05-lat;
    r1=100.*R0+zmin;

    fMin=.0;
    //fMax=.0;
    hMin=.0;
    //hMax=.0;
    nMin=.0;
    nMax=.0;

    for(i=0; i<iMax; i++)
    {
        ionosf(fi1, teta1, r1, time, v, vfi, vteta, vr, vt);
        nuprof(fi1, teta1, r1, time, nu);
        h[i]=r1-100.*R0;
        fPl[i]=sqrt(v);
        nU[i]=log10(nu*1.e6);
        //std::cout<<std::endl<<"r="<<r1-100.*R0<<" v="<<sqrt(v)<<" nu="<<nu<<"  "<<std::flush;
        if (fMax<fPl[i])
            fMax=fPl[i];
        if (hMax<h[i])
            hMax=h[i];
        if (nMax<nU[i])
            nMax=nU[i];
        r1+=dz;
    }

    /*
    // пример получения профиля
    long nn;
    iri_3dbase->getProfil(lat, lon, time/3600., &fPl[0], &nU[0], nn);
    //std::cout<<std::endl<<"lat="<<lat/RAD<<" lon="<<lon/RAD<<" time="<<time/3600.<<std::endl;
    iMax=nn;
    for(i=0; i<iMax; i++)
    {
        h[i]=zmin+dz*i;;
        nU[i]=log10(nU[i]*1.e6);
    }
    */
    drawF->setXYminmax(fMin, fMax, hMin, hMax);
}

void MainWindow::slotCorrection()
{
    QString str;
    QDialog dlgTemp(this);
    Ui::DialogCorrection dlg;
    dlg.setupUi(&dlgTemp);

    flagCorr=false;

    str.sprintf("%5.2f",tIon_1);
    dlg.lineEditTimeBeg->setText(str);
    str.sprintf("%8.3f",latIon_1);
    dlg.lineEditLatB->setText(str);
    str.sprintf("%8.3f",lonIon_1);
    dlg.lineEditLonB->setText(str);

    str.sprintf("%5.2f",f0E_1);
    dlg.lineEditF0E_1->setText(str);
    str.sprintf("%6.2f",hmE_1);
    dlg.lineEditHmE_1->setText(str);
    str.sprintf("%5.2f",f0F1_1);
    dlg.lineEditF0F1_1->setText(str);
    str.sprintf("%6.2f",hmF1_1);
    dlg.lineEditHmF1_1->setText(str);
    str.sprintf("%5.2f",f0F2_1);
    dlg.lineEditF0F2_1->setText(str);
    str.sprintf("%6.2f",hmF2_1);
    dlg.lineEditHmF2_1->setText(str);
    str.sprintf("%5.2f",f0Es_1);
    dlg.lineEditF0ES_1->setText(str);
    str.sprintf("%6.2f",hmEs_1);
    dlg.lineEditHES_1->setText(str);


    str.sprintf("%5.2f",tIon_2);
    dlg.lineEditTimeEnd->setText(str);
    str.sprintf("%8.3f",latIon_2);
    dlg.lineEditLatE->setText(str);
    str.sprintf("%8.3f",lonIon_2);
    dlg.lineEditLonE->setText(str);

    str.sprintf("%5.2f",f0E_2);
    dlg.lineEditF0E_2->setText(str);
    str.sprintf("%6.2f",hmE_2);
    dlg.lineEditHmE_2->setText(str);
    str.sprintf("%5.2f",f0F1_2);
    dlg.lineEditF0F1_2->setText(str);
    str.sprintf("%6.2f",hmF1_2);
    dlg.lineEditHmF1_2->setText(str);
    str.sprintf("%5.2f",f0F2_2);
    dlg.lineEditF0F2_2->setText(str);
    str.sprintf("%6.2f",hmF2_2);
    dlg.lineEditHmF2_2->setText(str);
    str.sprintf("%5.2f",f0Es_2);
    dlg.lineEditF0ES_2->setText(str);
    str.sprintf("%6.2f",hmEs_2);
    dlg.lineEditHES_2->setText(str);

    if (dlgTemp.exec())
    {
        tIon_1=dlg.lineEditTimeBeg->text().toDouble();
        latIon_1=dlg.lineEditLatB->text().toDouble();
        lonIon_1=dlg.lineEditLonB->text().toDouble();
        f0E_1=dlg.lineEditF0E_1->text().toDouble();
        hmE_1=dlg.lineEditHmE_1->text().toDouble();
        f0F1_1=dlg.lineEditF0F1_1->text().toDouble();
        hmF1_1=dlg.lineEditHmF1_1->text().toDouble();
        f0F2_1=dlg.lineEditF0F2_1->text().toDouble();
        hmF2_1=dlg.lineEditHmF2_1->text().toDouble();
        f0Es_1=dlg.lineEditF0ES_1->text().toDouble();
        hmEs_1=dlg.lineEditHES_1->text().toDouble();

        tIon_2=dlg.lineEditTimeEnd->text().toDouble();
        latIon_2=dlg.lineEditLatE->text().toDouble();
        lonIon_2=dlg.lineEditLonE->text().toDouble();
        f0E_2=dlg.lineEditF0E_2->text().toDouble();
        hmE_2=dlg.lineEditHmE_2->text().toDouble();
        f0F1_2=dlg.lineEditF0F1_2->text().toDouble();
        hmF1_2=dlg.lineEditHmF1_2->text().toDouble();
        f0F2_2=dlg.lineEditF0F2_2->text().toDouble();
        hmF2_2=dlg.lineEditHmF2_2->text().toDouble();
        f0Es_2=dlg.lineEditF0ES_2->text().toDouble();
        hmEs_2=dlg.lineEditHES_2->text().toDouble();

        flagCorr=true;

        reCalc();
    }
    else
    {
        flagCorr=false;
    }

}

void MainWindow::slotOptions()
{
    QDialog dlgTemp(this);
    Ui::Options dlg;
    dlg.setupUi(&dlgTemp);

    QRadioButton *button[]={dlg.radioButtonU,dlg.radioButtonC};
    button[(int)iri_3dbase->getCCIR_URSI()]->setChecked(true);

    str.sprintf("%04d",iyear);
    dlg.lineEditYear->setText(str);
    str.sprintf("%04d",iday);
    dlg.lineEditMonth->setText(str);
    str.sprintf("%5.1f",w);
    dlg.lineEditW->setText(str);
    str.sprintf("%5.1f",ig);
    dlg.lineEditIG->setText(str);
    dlg.checkBoxES->setChecked(keyes);
    dlg.checkBoxWIG->setChecked(flagWIG);

    dlg.checkBoxB0->setChecked(iri_3dbase->getJF(3));
    dlg.checkBoxNI->setChecked(iri_3dbase->getJF(5));
    dlg.checkBoxTE->setChecked(iri_3dbase->getJF(9));
    dlg.checkBoxNE->setChecked(iri_3dbase->getJF(10));
    dlg.checkBoxF1->setChecked(iri_3dbase->getJF(19));
    dlg.checkBoxD->setChecked(iri_3dbase->getJF(23));
    dlg.checkBoxStorm->setChecked(iri_3dbase->getJF(25));

    qApp->processEvents();
    if (dlgTemp.exec())
    {
        iyear=dlg.lineEditYear->text().toInt();
        iday =dlg.lineEditMonth->text().toInt();
        keyes=dlg.checkBoxES->isChecked();
        flagWIG=dlg.checkBoxWIG->isChecked();
        
        iri_3dbase->resetProfil();
        iri_3dbase2->resetProfil();

        if (button[1]->isChecked())
        {
            iri_3dbase->setCCIR();
            iri_3dbase2->setCCIR();
        }
        else
        {
            iri_3dbase->setURSI();
            iri_3dbase2->setURSI();
        }

        if (flagWIG)
        {
            W=dlg.lineEditW->text().toDouble();
            IG=dlg.lineEditIG->text().toDouble();
        }
        else
            W=IG=.0;

        iri_3dbase->setYear(iyear);
        iri_3dbase->setDay(iday);
        iri_3dbase->setTime(timeTemp0);
        iri_3dbase->setKeyEs(keyes);
        iri_3dbase->setSunActiv(W);
        iri_3dbase->setSunIgActiv(IG);
        iri_3dbase->setJF((long)dlg.checkBoxB0->isChecked(),3);
        iri_3dbase->setJF((long)dlg.checkBoxNI->isChecked(),5);
        iri_3dbase->setJF((long)dlg.checkBoxTE->isChecked(),9);
        iri_3dbase->setJF((long)dlg.checkBoxNE->isChecked(),10);
        iri_3dbase->setJF((long)dlg.checkBoxF1->isChecked(),19);
        iri_3dbase->setJF((long)dlg.checkBoxD->isChecked(),23);
        iri_3dbase->setJF((long)dlg.checkBoxStorm->isChecked(),25);

        iri_3dbase->getAppzocsim3DProfil();
        ig=iri_3dbase->getSunIgActiv();
        w =iri_3dbase->getSunActiv();

        iri_3dbase2->setYear(iyear);
        iri_3dbase2->setDay(iday);
        iri_3dbase2->setTime(timeTemp1);
        iri_3dbase2->setKeyEs(keyes);
        iri_3dbase2->setSunActiv(W);
        iri_3dbase2->setSunIgActiv(IG);
        iri_3dbase2->setJF((long)dlg.checkBoxB0->isChecked(),3);
        iri_3dbase2->setJF((long)dlg.checkBoxNI->isChecked(),5);
        iri_3dbase2->setJF((long)dlg.checkBoxTE->isChecked(),9);
        iri_3dbase2->setJF((long)dlg.checkBoxNE->isChecked(),10);
        iri_3dbase2->setJF((long)dlg.checkBoxF1->isChecked(),19);
        iri_3dbase2->setJF((long)dlg.checkBoxD->isChecked(),23);
        iri_3dbase2->setJF((long)dlg.checkBoxStorm->isChecked(),25);
    
        iri_3dbase2->getAppzocsim3DProfil();
        //ig=iri_3dbase2->getSunIgActiv();
        //w =iri_3dbase2->getSunActiv();

        newProf();
    }
}

void MainWindow::slotSave()
{
    double lon,lat;
    int i;
    char str[256];
    fstream out;

    lonB=lineEditLonB->text().toDouble()*RAD;
    latB=lineEditLatB->text().toDouble()*RAD;
    lonE=lineEditLonE->text().toDouble()*RAD;
    latE=lineEditLatE->text().toDouble()*RAD;
    lonS=lineEditLonS->text().toDouble()*RAD;
    latS=lineEditLatS->text().toDouble()*RAD;

    out.open("profil.dat",ios::out);

    double s0,alf,alf1;

    for(lat=latB; lat<latE; lat+=latS)
    {
        for(lon=lonB; lon<lonE; lon+=lonS)
        {
            path(lon0,lat0,lon,lat,s0,alf,alf1);
            if (s0>rmax)
                continue;
            fi1=lon;
            teta1=PI05-lat;
            r1=100.*R0+zmin;
            sprintf(str,"%8.3f  %8.3f   %8.2f %8.2f",lat/RAD,lon/RAD,s0,rmax);
            out<<endl<<str<<endl;
            for(i=0; i<iMax; i++)
            {
                ionosf(fi1, teta1, r1, time, v, vfi, vteta, vr, vt);
                nuprof(fi1, teta1, r1, time, nu);

                sprintf(str,"%7.3f  %6.3f  %12.5e  %12.5e  %12.5e  %12.5e  %9.5f",r1-100.*R0,sqrt(v),vfi,vteta,vr,nu,log10(nu*1.e6));
                out<<str<<endl;

                r1+=dz;
            }
        }
    }
    out.close();
}

double MainWindow::path(double lon0, double lat0, double lon1, double lat1, double &s0, double &alf, double &alf1)
{
  double dlon;
  dlon=lon1-lon0;

  s0=sin(lat0)*sin(lat1)+cos(lat0)*cos(lat1)*cos(dlon);
  s0=100.*R0*atan2(sqrt(1.-s0*s0),s0);
  alf =atan2(cos(lat1)*sin(dlon),sin(lat1)*cos(lat0)-
             sin(lat0)*cos(lat1)*cos(dlon));
  alf1=atan2(-cos(lat0)*sin(dlon),sin(lat0)*cos(lat1)-
             sin(lat1)*cos(lat0)*cos(dlon));

  return s0;
}

void MainWindow::slotRMax()
{
    rmax=lineEditRMax->text().toDouble();
    reCalc();
}
