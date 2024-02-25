/****************************************************************************
**  main.cpp
**
**  Copyright (C)2007 "SIGNAL" Laboratory, RSU.  All rights reserved.
**  Vertogradov G.G.;
**
*****************************************************************************/

#include <qapplication.h>
#include <qtranslator.h>
#include <qtextcodec.h>
#include <qfileinfo.h>
#include <qmessagebox.h>
#include <QLocale>
#include "./mainwindow.h"

MainWindow *mainwindow = 0;

void setLanguage(const QString &l);

int main( int argc, char ** argv ) {
    QApplication a( argc, argv );

    // определение кодовой страницы
    //const char* local = QTextCodec::locale();

    //setLanguage(QString(local).left(2));

    setlocale(LC_NUMERIC,"C");
    mainwindow = new MainWindow(0, argc, argv);
    mainwindow->show();
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    return a.exec();
    return a.exec();
}

void setLanguage(const QString &l)
{
    QString lang = l;
    QString lang_qt = l;

    if (lang!=QString("ru"))
        return;

    lang = "paths0gr_"+lang+".qm";
    lang_qt = "qt_"+lang_qt+".qm";

    QFileInfo fi(lang);
    if (!fi.exists())
    {
        QMessageBox::critical(0,"Warning!",QString("Cannot find translation file: "+lang));
        return;
    }
    else
    {
        QTranslator* translator = new QTranslator(0);
        translator->load(lang,".");
        qApp->installTranslator(translator);
    }

    QFileInfo fi_qt(lang_qt);
        if(!fi_qt.exists())
    {
        return;
    }
    else
    {
        QTranslator* tr_qt = new QTranslator(0);
        tr_qt->load(lang_qt,".");
        qApp->installTranslator(tr_qt);
    }
}

