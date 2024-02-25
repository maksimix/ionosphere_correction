/********************************************************************************
** Form generated from reading UI file 'profilwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILWINDOW_H
#define UI_PROFILWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProfilWindow
{
public:
    QGridLayout *gridLayout;
    QFrame *frameDraw;
    QFrame *frame4;
    QGridLayout *gridLayout1;
    QFrame *frame5;
    QGridLayout *gridLayout2;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *textLabelLat0;
    QLineEdit *lineEditLat0;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabelLon0;
    QLineEdit *lineEditLon0;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout2;
    QLabel *textLabelTimeBeg;
    QLineEdit *lineEditTimeBeg;
    QHBoxLayout *hboxLayout3;
    QLabel *textLabelTimeEnd;
    QLineEdit *lineEditTimeEnd;
    QFrame *frame8;
    QGridLayout *gridLayout3;
    QHBoxLayout *hboxLayout4;
    QLabel *textLabelLat;
    QLineEdit *lineEditLat;
    QHBoxLayout *hboxLayout5;
    QLabel *textLabelLon;
    QLineEdit *lineEditLon;
    QHBoxLayout *hboxLayout6;
    QLabel *textLabelTime;
    QLineEdit *lineEditTime;
    QFrame *frame7;
    QGridLayout *gridLayout4;
    QHBoxLayout *hboxLayout7;
    QLabel *textLabel3;
    QSlider *sliderTime;
    QHBoxLayout *hboxLayout8;
    QLabel *textLabel2;
    QSlider *sliderLon;
    QHBoxLayout *hboxLayout9;
    QLabel *textLabel1;
    QSlider *sliderLat;
    QFrame *frame9;
    QGridLayout *gridLayout5;
    QHBoxLayout *hboxLayout10;
    QLabel *textLabelHMin;
    QSlider *sliderHMin;
    QHBoxLayout *hboxLayout11;
    QLabel *textLabelHMax;
    QSlider *sliderHMax;
    QHBoxLayout *hboxLayout12;
    QLabel *textLabelFMin;
    QSlider *sliderFMin;
    QHBoxLayout *hboxLayout13;
    QLabel *textLabelFMax;
    QSlider *sliderFMax;
    QFrame *frame9_2;
    QVBoxLayout *vboxLayout2;
    QSpacerItem *spacer1;
    QPushButton *pushButtonO;
    QPushButton *pushButtonCor;
    QPushButton *pushButtonSave;
    QVBoxLayout *vboxLayout3;
    QPushButton *pushButtonDraw;
    QPushButton *pushButtonExit;
    QHBoxLayout *hboxLayout14;
    QFrame *frame10;
    QGridLayout *gridLayout6;
    QHBoxLayout *hboxLayout15;
    QHBoxLayout *hboxLayout16;
    QLabel *textLabel1_2;
    QLineEdit *lineEditLatB;
    QHBoxLayout *hboxLayout17;
    QLabel *textLabel1_2_2;
    QLineEdit *lineEditLatE;
    QHBoxLayout *hboxLayout18;
    QLabel *textLabel1_2_2_2;
    QLineEdit *lineEditLatS;
    QHBoxLayout *hboxLayout19;
    QHBoxLayout *hboxLayout20;
    QLabel *textLabel1_2_3;
    QLineEdit *lineEditLonB;
    QHBoxLayout *hboxLayout21;
    QLabel *textLabel1_2_2_3;
    QLineEdit *lineEditLonE;
    QHBoxLayout *hboxLayout22;
    QLabel *textLabel1_2_2_2_2;
    QLineEdit *lineEditLonS;
    QVBoxLayout *vboxLayout4;
    QHBoxLayout *hboxLayout23;
    QLabel *textLabelRMax;
    QLineEdit *lineEditRMax;
    QFrame *frame11;

    void setupUi(QDialog *ProfilWindow)
    {
        if (ProfilWindow->objectName().isEmpty())
            ProfilWindow->setObjectName(QStringLiteral("ProfilWindow"));
        ProfilWindow->resize(802, 759);
        gridLayout = new QGridLayout(ProfilWindow);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frameDraw = new QFrame(ProfilWindow);
        frameDraw->setObjectName(QStringLiteral("frameDraw"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frameDraw->sizePolicy().hasHeightForWidth());
        frameDraw->setSizePolicy(sizePolicy);
        frameDraw->setMinimumSize(QSize(400, 200));
        frameDraw->setFrameShape(QFrame::Box);
        frameDraw->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameDraw, 0, 0, 1, 1);

        frame4 = new QFrame(ProfilWindow);
        frame4->setObjectName(QStringLiteral("frame4"));
        frame4->setMaximumSize(QSize(32767, 300));
        frame4->setFrameShape(QFrame::Box);
        frame4->setFrameShadow(QFrame::Raised);
        gridLayout1 = new QGridLayout(frame4);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        frame5 = new QFrame(frame4);
        frame5->setObjectName(QStringLiteral("frame5"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame5->sizePolicy().hasHeightForWidth());
        frame5->setSizePolicy(sizePolicy1);
        frame5->setFrameShape(QFrame::Box);
        frame5->setFrameShadow(QFrame::Raised);
        gridLayout2 = new QGridLayout(frame5);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        textLabelLat0 = new QLabel(frame5);
        textLabelLat0->setObjectName(QStringLiteral("textLabelLat0"));
        textLabelLat0->setMinimumSize(QSize(100, 22));
        textLabelLat0->setMaximumSize(QSize(100, 22));
        textLabelLat0->setWordWrap(false);

        hboxLayout->addWidget(textLabelLat0);

        lineEditLat0 = new QLineEdit(frame5);
        lineEditLat0->setObjectName(QStringLiteral("lineEditLat0"));
        lineEditLat0->setMinimumSize(QSize(80, 24));
        lineEditLat0->setMaximumSize(QSize(80, 24));

        hboxLayout->addWidget(lineEditLat0);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        textLabelLon0 = new QLabel(frame5);
        textLabelLon0->setObjectName(QStringLiteral("textLabelLon0"));
        textLabelLon0->setMinimumSize(QSize(100, 22));
        textLabelLon0->setMaximumSize(QSize(100, 22));
        textLabelLon0->setWordWrap(false);

        hboxLayout1->addWidget(textLabelLon0);

        lineEditLon0 = new QLineEdit(frame5);
        lineEditLon0->setObjectName(QStringLiteral("lineEditLon0"));
        lineEditLon0->setMinimumSize(QSize(80, 24));
        lineEditLon0->setMaximumSize(QSize(80, 24));

        hboxLayout1->addWidget(lineEditLon0);


        vboxLayout->addLayout(hboxLayout1);


        gridLayout2->addLayout(vboxLayout, 0, 0, 1, 1);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QStringLiteral("hboxLayout2"));
        textLabelTimeBeg = new QLabel(frame5);
        textLabelTimeBeg->setObjectName(QStringLiteral("textLabelTimeBeg"));
        textLabelTimeBeg->setMinimumSize(QSize(100, 22));
        textLabelTimeBeg->setMaximumSize(QSize(100, 22));
        textLabelTimeBeg->setWordWrap(false);

        hboxLayout2->addWidget(textLabelTimeBeg);

        lineEditTimeBeg = new QLineEdit(frame5);
        lineEditTimeBeg->setObjectName(QStringLiteral("lineEditTimeBeg"));
        lineEditTimeBeg->setMinimumSize(QSize(80, 24));
        lineEditTimeBeg->setMaximumSize(QSize(80, 24));

        hboxLayout2->addWidget(lineEditTimeBeg);


        vboxLayout1->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QStringLiteral("hboxLayout3"));
        textLabelTimeEnd = new QLabel(frame5);
        textLabelTimeEnd->setObjectName(QStringLiteral("textLabelTimeEnd"));
        textLabelTimeEnd->setMinimumSize(QSize(100, 22));
        textLabelTimeEnd->setMaximumSize(QSize(100, 22));
        textLabelTimeEnd->setWordWrap(false);

        hboxLayout3->addWidget(textLabelTimeEnd);

        lineEditTimeEnd = new QLineEdit(frame5);
        lineEditTimeEnd->setObjectName(QStringLiteral("lineEditTimeEnd"));
        lineEditTimeEnd->setMinimumSize(QSize(80, 24));
        lineEditTimeEnd->setMaximumSize(QSize(80, 24));

        hboxLayout3->addWidget(lineEditTimeEnd);


        vboxLayout1->addLayout(hboxLayout3);


        gridLayout2->addLayout(vboxLayout1, 2, 0, 1, 1);


        gridLayout1->addWidget(frame5, 0, 0, 2, 1);

        frame8 = new QFrame(frame4);
        frame8->setObjectName(QStringLiteral("frame8"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(210);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame8->sizePolicy().hasHeightForWidth());
        frame8->setSizePolicy(sizePolicy2);
        frame8->setMinimumSize(QSize(210, 120));
        frame8->setFrameShape(QFrame::Box);
        frame8->setFrameShadow(QFrame::Raised);
        gridLayout3 = new QGridLayout(frame8);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName(QStringLiteral("gridLayout3"));
        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QStringLiteral("hboxLayout4"));
        textLabelLat = new QLabel(frame8);
        textLabelLat->setObjectName(QStringLiteral("textLabelLat"));
        textLabelLat->setMinimumSize(QSize(100, 22));
        textLabelLat->setMaximumSize(QSize(100, 22));
        textLabelLat->setWordWrap(false);

        hboxLayout4->addWidget(textLabelLat);

        lineEditLat = new QLineEdit(frame8);
        lineEditLat->setObjectName(QStringLiteral("lineEditLat"));
        lineEditLat->setMinimumSize(QSize(80, 24));
        lineEditLat->setMaximumSize(QSize(80, 24));

        hboxLayout4->addWidget(lineEditLat);


        gridLayout3->addLayout(hboxLayout4, 0, 0, 1, 1);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QStringLiteral("hboxLayout5"));
        textLabelLon = new QLabel(frame8);
        textLabelLon->setObjectName(QStringLiteral("textLabelLon"));
        textLabelLon->setMinimumSize(QSize(100, 22));
        textLabelLon->setMaximumSize(QSize(100, 22));
        textLabelLon->setWordWrap(false);

        hboxLayout5->addWidget(textLabelLon);

        lineEditLon = new QLineEdit(frame8);
        lineEditLon->setObjectName(QStringLiteral("lineEditLon"));
        lineEditLon->setMinimumSize(QSize(80, 24));
        lineEditLon->setMaximumSize(QSize(80, 24));

        hboxLayout5->addWidget(lineEditLon);


        gridLayout3->addLayout(hboxLayout5, 1, 0, 1, 1);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QStringLiteral("hboxLayout6"));
        textLabelTime = new QLabel(frame8);
        textLabelTime->setObjectName(QStringLiteral("textLabelTime"));
        textLabelTime->setMinimumSize(QSize(100, 22));
        textLabelTime->setMaximumSize(QSize(100, 22));
        textLabelTime->setWordWrap(false);

        hboxLayout6->addWidget(textLabelTime);

        lineEditTime = new QLineEdit(frame8);
        lineEditTime->setObjectName(QStringLiteral("lineEditTime"));
        lineEditTime->setMinimumSize(QSize(80, 22));
        lineEditTime->setMaximumSize(QSize(80, 24));

        hboxLayout6->addWidget(lineEditTime);


        gridLayout3->addLayout(hboxLayout6, 2, 0, 1, 1);


        gridLayout1->addWidget(frame8, 2, 0, 1, 1);

        frame7 = new QFrame(frame4);
        frame7->setObjectName(QStringLiteral("frame7"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(240);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frame7->sizePolicy().hasHeightForWidth());
        frame7->setSizePolicy(sizePolicy3);
        frame7->setFrameShape(QFrame::Box);
        frame7->setFrameShadow(QFrame::Raised);
        gridLayout4 = new QGridLayout(frame7);
        gridLayout4->setSpacing(6);
        gridLayout4->setContentsMargins(11, 11, 11, 11);
        gridLayout4->setObjectName(QStringLiteral("gridLayout4"));
        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(6);
        hboxLayout7->setObjectName(QStringLiteral("hboxLayout7"));
        textLabel3 = new QLabel(frame7);
        textLabel3->setObjectName(QStringLiteral("textLabel3"));
        textLabel3->setMinimumSize(QSize(90, 22));
        textLabel3->setMaximumSize(QSize(90, 22));
        textLabel3->setWordWrap(false);

        hboxLayout7->addWidget(textLabel3);

        sliderTime = new QSlider(frame7);
        sliderTime->setObjectName(QStringLiteral("sliderTime"));
        sliderTime->setMinimumSize(QSize(100, 0));
        sliderTime->setMaximum(60);
        sliderTime->setPageStep(1);
        sliderTime->setOrientation(Qt::Horizontal);

        hboxLayout7->addWidget(sliderTime);


        gridLayout4->addLayout(hboxLayout7, 2, 0, 1, 1);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(6);
        hboxLayout8->setObjectName(QStringLiteral("hboxLayout8"));
        textLabel2 = new QLabel(frame7);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setMinimumSize(QSize(90, 22));
        textLabel2->setMaximumSize(QSize(90, 22));
        textLabel2->setWordWrap(false);

        hboxLayout8->addWidget(textLabel2);

        sliderLon = new QSlider(frame7);
        sliderLon->setObjectName(QStringLiteral("sliderLon"));
        sliderLon->setMinimumSize(QSize(100, 0));
        sliderLon->setMinimum(-180);
        sliderLon->setMaximum(180);
        sliderLon->setPageStep(1);
        sliderLon->setOrientation(Qt::Horizontal);

        hboxLayout8->addWidget(sliderLon);


        gridLayout4->addLayout(hboxLayout8, 1, 0, 1, 1);

        hboxLayout9 = new QHBoxLayout();
        hboxLayout9->setSpacing(6);
        hboxLayout9->setObjectName(QStringLiteral("hboxLayout9"));
        textLabel1 = new QLabel(frame7);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setMinimumSize(QSize(90, 22));
        textLabel1->setMaximumSize(QSize(90, 22));
        textLabel1->setWordWrap(false);

        hboxLayout9->addWidget(textLabel1);

        sliderLat = new QSlider(frame7);
        sliderLat->setObjectName(QStringLiteral("sliderLat"));
        sliderLat->setMinimumSize(QSize(100, 0));
        sliderLat->setMinimum(-90);
        sliderLat->setMaximum(90);
        sliderLat->setPageStep(1);
        sliderLat->setOrientation(Qt::Horizontal);

        hboxLayout9->addWidget(sliderLat);


        gridLayout4->addLayout(hboxLayout9, 0, 0, 1, 1);


        gridLayout1->addWidget(frame7, 0, 2, 1, 1);

        frame9 = new QFrame(frame4);
        frame9->setObjectName(QStringLiteral("frame9"));
        frame9->setMinimumSize(QSize(10, 110));
        frame9->setFrameShape(QFrame::Box);
        frame9->setFrameShadow(QFrame::Raised);
        gridLayout5 = new QGridLayout(frame9);
        gridLayout5->setSpacing(6);
        gridLayout5->setContentsMargins(11, 11, 11, 11);
        gridLayout5->setObjectName(QStringLiteral("gridLayout5"));
        hboxLayout10 = new QHBoxLayout();
        hboxLayout10->setSpacing(6);
        hboxLayout10->setObjectName(QStringLiteral("hboxLayout10"));
        textLabelHMin = new QLabel(frame9);
        textLabelHMin->setObjectName(QStringLiteral("textLabelHMin"));
        textLabelHMin->setMinimumSize(QSize(90, 22));
        textLabelHMin->setMaximumSize(QSize(90, 22));
        textLabelHMin->setWordWrap(false);

        hboxLayout10->addWidget(textLabelHMin);

        sliderHMin = new QSlider(frame9);
        sliderHMin->setObjectName(QStringLiteral("sliderHMin"));
        sliderHMin->setMinimumSize(QSize(100, 0));
        sliderHMin->setMinimum(0);
        sliderHMin->setMaximum(500);
        sliderHMin->setPageStep(1);
        sliderHMin->setOrientation(Qt::Horizontal);

        hboxLayout10->addWidget(sliderHMin);


        gridLayout5->addLayout(hboxLayout10, 0, 0, 1, 1);

        hboxLayout11 = new QHBoxLayout();
        hboxLayout11->setSpacing(6);
        hboxLayout11->setObjectName(QStringLiteral("hboxLayout11"));
        textLabelHMax = new QLabel(frame9);
        textLabelHMax->setObjectName(QStringLiteral("textLabelHMax"));
        textLabelHMax->setMinimumSize(QSize(90, 22));
        textLabelHMax->setMaximumSize(QSize(90, 22));
        textLabelHMax->setWordWrap(false);

        hboxLayout11->addWidget(textLabelHMax);

        sliderHMax = new QSlider(frame9);
        sliderHMax->setObjectName(QStringLiteral("sliderHMax"));
        sliderHMax->setMinimumSize(QSize(100, 0));
        sliderHMax->setMinimum(50);
        sliderHMax->setMaximum(500);
        sliderHMax->setPageStep(1);
        sliderHMax->setValue(500);
        sliderHMax->setOrientation(Qt::Horizontal);

        hboxLayout11->addWidget(sliderHMax);


        gridLayout5->addLayout(hboxLayout11, 1, 0, 1, 1);

        hboxLayout12 = new QHBoxLayout();
        hboxLayout12->setSpacing(6);
        hboxLayout12->setObjectName(QStringLiteral("hboxLayout12"));
        textLabelFMin = new QLabel(frame9);
        textLabelFMin->setObjectName(QStringLiteral("textLabelFMin"));
        textLabelFMin->setMinimumSize(QSize(90, 22));
        textLabelFMin->setMaximumSize(QSize(90, 22));
        textLabelFMin->setWordWrap(false);

        hboxLayout12->addWidget(textLabelFMin);

        sliderFMin = new QSlider(frame9);
        sliderFMin->setObjectName(QStringLiteral("sliderFMin"));
        sliderFMin->setMinimumSize(QSize(100, 0));
        sliderFMin->setMinimum(0);
        sliderFMin->setMaximum(240);
        sliderFMin->setPageStep(1);
        sliderFMin->setOrientation(Qt::Horizontal);

        hboxLayout12->addWidget(sliderFMin);


        gridLayout5->addLayout(hboxLayout12, 2, 0, 1, 1);

        hboxLayout13 = new QHBoxLayout();
        hboxLayout13->setSpacing(6);
        hboxLayout13->setObjectName(QStringLiteral("hboxLayout13"));
        textLabelFMax = new QLabel(frame9);
        textLabelFMax->setObjectName(QStringLiteral("textLabelFMax"));
        textLabelFMax->setMinimumSize(QSize(90, 22));
        textLabelFMax->setMaximumSize(QSize(90, 22));
        textLabelFMax->setWordWrap(false);

        hboxLayout13->addWidget(textLabelFMax);

        sliderFMax = new QSlider(frame9);
        sliderFMax->setObjectName(QStringLiteral("sliderFMax"));
        sliderFMax->setMinimumSize(QSize(100, 0));
        sliderFMax->setMinimum(1);
        sliderFMax->setMaximum(250);
        sliderFMax->setPageStep(1);
        sliderFMax->setValue(250);
        sliderFMax->setOrientation(Qt::Horizontal);

        hboxLayout13->addWidget(sliderFMax);


        gridLayout5->addLayout(hboxLayout13, 3, 0, 1, 1);


        gridLayout1->addWidget(frame9, 1, 2, 2, 1);

        frame9_2 = new QFrame(frame4);
        frame9_2->setObjectName(QStringLiteral("frame9_2"));
        frame9_2->setMinimumSize(QSize(10, 0));
        frame9_2->setFrameShape(QFrame::Box);
        frame9_2->setFrameShadow(QFrame::Raised);

        gridLayout1->addWidget(frame9_2, 0, 1, 3, 1);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        spacer1 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout2->addItem(spacer1);

        pushButtonO = new QPushButton(frame4);
        pushButtonO->setObjectName(QStringLiteral("pushButtonO"));
        pushButtonO->setMaximumSize(QSize(80, 30));

        vboxLayout2->addWidget(pushButtonO);

        pushButtonCor = new QPushButton(frame4);
        pushButtonCor->setObjectName(QStringLiteral("pushButtonCor"));
        pushButtonCor->setMaximumSize(QSize(80, 30));

        vboxLayout2->addWidget(pushButtonCor);

        pushButtonSave = new QPushButton(frame4);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));
        pushButtonSave->setMaximumSize(QSize(80, 30));

        vboxLayout2->addWidget(pushButtonSave);

        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setSpacing(6);
        vboxLayout3->setObjectName(QStringLiteral("vboxLayout3"));
        pushButtonDraw = new QPushButton(frame4);
        pushButtonDraw->setObjectName(QStringLiteral("pushButtonDraw"));
        pushButtonDraw->setMaximumSize(QSize(80, 30));

        vboxLayout3->addWidget(pushButtonDraw);

        pushButtonExit = new QPushButton(frame4);
        pushButtonExit->setObjectName(QStringLiteral("pushButtonExit"));
        pushButtonExit->setMaximumSize(QSize(80, 30));
        pushButtonExit->setDefault(true);

        vboxLayout3->addWidget(pushButtonExit);


        vboxLayout2->addLayout(vboxLayout3);


        gridLayout1->addLayout(vboxLayout2, 0, 3, 3, 1);


        gridLayout->addWidget(frame4, 2, 0, 1, 1);

        hboxLayout14 = new QHBoxLayout();
        hboxLayout14->setSpacing(6);
        hboxLayout14->setObjectName(QStringLiteral("hboxLayout14"));
        frame10 = new QFrame(ProfilWindow);
        frame10->setObjectName(QStringLiteral("frame10"));
        frame10->setFrameShape(QFrame::Box);
        frame10->setFrameShadow(QFrame::Raised);
        gridLayout6 = new QGridLayout(frame10);
        gridLayout6->setSpacing(6);
        gridLayout6->setContentsMargins(11, 11, 11, 11);
        gridLayout6->setObjectName(QStringLiteral("gridLayout6"));
        hboxLayout15 = new QHBoxLayout();
        hboxLayout15->setSpacing(6);
        hboxLayout15->setObjectName(QStringLiteral("hboxLayout15"));
        hboxLayout16 = new QHBoxLayout();
        hboxLayout16->setSpacing(6);
        hboxLayout16->setObjectName(QStringLiteral("hboxLayout16"));
        textLabel1_2 = new QLabel(frame10);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setMinimumSize(QSize(100, 22));
        textLabel1_2->setMaximumSize(QSize(100, 22));
        textLabel1_2->setWordWrap(false);

        hboxLayout16->addWidget(textLabel1_2);

        lineEditLatB = new QLineEdit(frame10);
        lineEditLatB->setObjectName(QStringLiteral("lineEditLatB"));
        lineEditLatB->setMinimumSize(QSize(80, 24));
        lineEditLatB->setMaximumSize(QSize(80, 24));

        hboxLayout16->addWidget(lineEditLatB);


        hboxLayout15->addLayout(hboxLayout16);

        hboxLayout17 = new QHBoxLayout();
        hboxLayout17->setSpacing(6);
        hboxLayout17->setObjectName(QStringLiteral("hboxLayout17"));
        textLabel1_2_2 = new QLabel(frame10);
        textLabel1_2_2->setObjectName(QStringLiteral("textLabel1_2_2"));
        textLabel1_2_2->setMinimumSize(QSize(100, 22));
        textLabel1_2_2->setMaximumSize(QSize(100, 22));
        textLabel1_2_2->setWordWrap(false);

        hboxLayout17->addWidget(textLabel1_2_2);

        lineEditLatE = new QLineEdit(frame10);
        lineEditLatE->setObjectName(QStringLiteral("lineEditLatE"));
        lineEditLatE->setMinimumSize(QSize(80, 24));
        lineEditLatE->setMaximumSize(QSize(80, 24));

        hboxLayout17->addWidget(lineEditLatE);


        hboxLayout15->addLayout(hboxLayout17);

        hboxLayout18 = new QHBoxLayout();
        hboxLayout18->setSpacing(6);
        hboxLayout18->setObjectName(QStringLiteral("hboxLayout18"));
        textLabel1_2_2_2 = new QLabel(frame10);
        textLabel1_2_2_2->setObjectName(QStringLiteral("textLabel1_2_2_2"));
        textLabel1_2_2_2->setMinimumSize(QSize(100, 22));
        textLabel1_2_2_2->setMaximumSize(QSize(100, 22));
        textLabel1_2_2_2->setWordWrap(false);

        hboxLayout18->addWidget(textLabel1_2_2_2);

        lineEditLatS = new QLineEdit(frame10);
        lineEditLatS->setObjectName(QStringLiteral("lineEditLatS"));
        lineEditLatS->setMinimumSize(QSize(80, 24));
        lineEditLatS->setMaximumSize(QSize(80, 24));

        hboxLayout18->addWidget(lineEditLatS);


        hboxLayout15->addLayout(hboxLayout18);


        gridLayout6->addLayout(hboxLayout15, 0, 0, 1, 1);

        hboxLayout19 = new QHBoxLayout();
        hboxLayout19->setSpacing(6);
        hboxLayout19->setObjectName(QStringLiteral("hboxLayout19"));
        hboxLayout20 = new QHBoxLayout();
        hboxLayout20->setSpacing(6);
        hboxLayout20->setObjectName(QStringLiteral("hboxLayout20"));
        textLabel1_2_3 = new QLabel(frame10);
        textLabel1_2_3->setObjectName(QStringLiteral("textLabel1_2_3"));
        textLabel1_2_3->setMinimumSize(QSize(100, 22));
        textLabel1_2_3->setMaximumSize(QSize(100, 22));
        textLabel1_2_3->setWordWrap(false);

        hboxLayout20->addWidget(textLabel1_2_3);

        lineEditLonB = new QLineEdit(frame10);
        lineEditLonB->setObjectName(QStringLiteral("lineEditLonB"));
        lineEditLonB->setMinimumSize(QSize(80, 24));
        lineEditLonB->setMaximumSize(QSize(80, 24));

        hboxLayout20->addWidget(lineEditLonB);


        hboxLayout19->addLayout(hboxLayout20);

        hboxLayout21 = new QHBoxLayout();
        hboxLayout21->setSpacing(6);
        hboxLayout21->setObjectName(QStringLiteral("hboxLayout21"));
        textLabel1_2_2_3 = new QLabel(frame10);
        textLabel1_2_2_3->setObjectName(QStringLiteral("textLabel1_2_2_3"));
        textLabel1_2_2_3->setMinimumSize(QSize(100, 22));
        textLabel1_2_2_3->setMaximumSize(QSize(100, 22));
        textLabel1_2_2_3->setWordWrap(false);

        hboxLayout21->addWidget(textLabel1_2_2_3);

        lineEditLonE = new QLineEdit(frame10);
        lineEditLonE->setObjectName(QStringLiteral("lineEditLonE"));
        lineEditLonE->setMinimumSize(QSize(80, 24));
        lineEditLonE->setMaximumSize(QSize(80, 24));

        hboxLayout21->addWidget(lineEditLonE);


        hboxLayout19->addLayout(hboxLayout21);

        hboxLayout22 = new QHBoxLayout();
        hboxLayout22->setSpacing(6);
        hboxLayout22->setObjectName(QStringLiteral("hboxLayout22"));
        textLabel1_2_2_2_2 = new QLabel(frame10);
        textLabel1_2_2_2_2->setObjectName(QStringLiteral("textLabel1_2_2_2_2"));
        textLabel1_2_2_2_2->setMinimumSize(QSize(100, 22));
        textLabel1_2_2_2_2->setMaximumSize(QSize(100, 22));
        textLabel1_2_2_2_2->setWordWrap(false);

        hboxLayout22->addWidget(textLabel1_2_2_2_2);

        lineEditLonS = new QLineEdit(frame10);
        lineEditLonS->setObjectName(QStringLiteral("lineEditLonS"));
        lineEditLonS->setMinimumSize(QSize(80, 24));
        lineEditLonS->setMaximumSize(QSize(80, 24));

        hboxLayout22->addWidget(lineEditLonS);


        hboxLayout19->addLayout(hboxLayout22);


        gridLayout6->addLayout(hboxLayout19, 1, 0, 1, 1);


        hboxLayout14->addWidget(frame10);

        vboxLayout4 = new QVBoxLayout();
        vboxLayout4->setSpacing(6);
        vboxLayout4->setObjectName(QStringLiteral("vboxLayout4"));
        hboxLayout23 = new QHBoxLayout();
        hboxLayout23->setSpacing(6);
        hboxLayout23->setObjectName(QStringLiteral("hboxLayout23"));
        textLabelRMax = new QLabel(ProfilWindow);
        textLabelRMax->setObjectName(QStringLiteral("textLabelRMax"));
        textLabelRMax->setMaximumSize(QSize(70, 22));
        textLabelRMax->setWordWrap(false);

        hboxLayout23->addWidget(textLabelRMax);

        lineEditRMax = new QLineEdit(ProfilWindow);
        lineEditRMax->setObjectName(QStringLiteral("lineEditRMax"));
        lineEditRMax->setMaximumSize(QSize(80, 24));

        hboxLayout23->addWidget(lineEditRMax);


        vboxLayout4->addLayout(hboxLayout23);

        frame11 = new QFrame(ProfilWindow);
        frame11->setObjectName(QStringLiteral("frame11"));
        frame11->setMinimumSize(QSize(100, 24));
        frame11->setFrameShape(QFrame::Box);
        frame11->setFrameShadow(QFrame::Raised);

        vboxLayout4->addWidget(frame11);


        hboxLayout14->addLayout(vboxLayout4);


        gridLayout->addLayout(hboxLayout14, 1, 0, 1, 1);

        QWidget::setTabOrder(lineEditLat0, lineEditLon0);
        QWidget::setTabOrder(lineEditLon0, lineEditTimeBeg);
        QWidget::setTabOrder(lineEditTimeBeg, lineEditTimeEnd);
        QWidget::setTabOrder(lineEditTimeEnd, sliderLat);
        QWidget::setTabOrder(sliderLat, sliderLon);
        QWidget::setTabOrder(sliderLon, sliderTime);
        QWidget::setTabOrder(sliderTime, lineEditLat);
        QWidget::setTabOrder(lineEditLat, lineEditLon);
        QWidget::setTabOrder(lineEditLon, lineEditTime);
        QWidget::setTabOrder(lineEditTime, pushButtonDraw);
        QWidget::setTabOrder(pushButtonDraw, pushButtonExit);

        retranslateUi(ProfilWindow);
        QObject::connect(pushButtonExit, SIGNAL(pressed()), ProfilWindow, SLOT(slotExit()));
        QObject::connect(pushButtonDraw, SIGNAL(pressed()), ProfilWindow, SLOT(slotDraw()));
        QObject::connect(sliderLat, SIGNAL(valueChanged(int)), ProfilWindow, SLOT(slotChangeLat(int)));
        QObject::connect(sliderLon, SIGNAL(valueChanged(int)), ProfilWindow, SLOT(slotChangeLon(int)));
        QObject::connect(sliderTime, SIGNAL(valueChanged(int)), ProfilWindow, SLOT(slotChangeTime(int)));
        QObject::connect(lineEditLat0, SIGNAL(returnPressed()), ProfilWindow, SLOT(slotLat0()));
        QObject::connect(lineEditLon0, SIGNAL(returnPressed()), ProfilWindow, SLOT(slotLon0()));
        QObject::connect(lineEditTimeBeg, SIGNAL(returnPressed()), ProfilWindow, SLOT(slotTimeBeg()));
        QObject::connect(lineEditTimeEnd, SIGNAL(returnPressed()), ProfilWindow, SLOT(slotTimeEnd()));
        QObject::connect(lineEditLat, SIGNAL(returnPressed()), ProfilWindow, SLOT(slotLat()));
        QObject::connect(lineEditLon, SIGNAL(returnPressed()), ProfilWindow, SLOT(slotLon()));
        QObject::connect(lineEditTime, SIGNAL(returnPressed()), ProfilWindow, SLOT(slotTime()));
        QObject::connect(sliderHMin, SIGNAL(valueChanged(int)), ProfilWindow, SLOT(slotHMin(int)));
        QObject::connect(sliderHMax, SIGNAL(valueChanged(int)), ProfilWindow, SLOT(slotHMax(int)));
        QObject::connect(sliderFMin, SIGNAL(valueChanged(int)), ProfilWindow, SLOT(slotFMin(int)));
        QObject::connect(sliderFMax, SIGNAL(valueChanged(int)), ProfilWindow, SLOT(slotFMax(int)));
        QObject::connect(pushButtonO, SIGNAL(pressed()), ProfilWindow, SLOT(slotOptions()));
        QObject::connect(pushButtonCor, SIGNAL(pressed()), ProfilWindow, SLOT(slotCorection()));
        QObject::connect(pushButtonSave, SIGNAL(pressed()), ProfilWindow, SLOT(slotSave()));
        QObject::connect(lineEditRMax, SIGNAL(returnPressed()), ProfilWindow, SLOT(slotRMax()));
        QObject::connect(pushButtonCor, SIGNAL(pressed()), ProfilWindow, SLOT(slotCorrection()));

        QMetaObject::connectSlotsByName(ProfilWindow);
    } // setupUi

    void retranslateUi(QDialog *ProfilWindow)
    {
        ProfilWindow->setWindowTitle(QApplication::translate("ProfilWindow", "Profil", 0));
        textLabelLat0->setText(QApplication::translate("ProfilWindow", "Latitude0,deg", 0));
        lineEditLat0->setText(QString());
        textLabelLon0->setText(QApplication::translate("ProfilWindow", "Longitude0,deg", 0));
        lineEditLon0->setText(QString());
        textLabelTimeBeg->setText(QApplication::translate("ProfilWindow", "TimeBeg,hh:mm", 0));
        lineEditTimeBeg->setText(QString());
        textLabelTimeEnd->setText(QApplication::translate("ProfilWindow", "TimeEnd,hh:mm", 0));
        lineEditTimeEnd->setText(QString());
        textLabelLat->setText(QApplication::translate("ProfilWindow", "Latitude,deg", 0));
        lineEditLat->setText(QString());
        textLabelLon->setText(QApplication::translate("ProfilWindow", "Longitude,deg", 0));
        lineEditLon->setText(QString());
        textLabelTime->setText(QApplication::translate("ProfilWindow", "Time,hh:mm", 0));
        lineEditTime->setText(QString());
        textLabel3->setText(QApplication::translate("ProfilWindow", "Time", 0));
        textLabel2->setText(QApplication::translate("ProfilWindow", "Longitude", 0));
        textLabel1->setText(QApplication::translate("ProfilWindow", "Latitude", 0));
        textLabelHMin->setText(QApplication::translate("ProfilWindow", "hMin,km", 0));
        textLabelHMax->setText(QApplication::translate("ProfilWindow", "hMax,km", 0));
        textLabelFMin->setText(QApplication::translate("ProfilWindow", "fMin,MHz", 0));
        textLabelFMax->setText(QApplication::translate("ProfilWindow", "fMax,MHz", 0));
        pushButtonO->setText(QApplication::translate("ProfilWindow", "Options", 0));
        pushButtonCor->setText(QApplication::translate("ProfilWindow", "Corection", 0));
        pushButtonSave->setText(QApplication::translate("ProfilWindow", "Save", 0));
        pushButtonDraw->setText(QApplication::translate("ProfilWindow", "Draw", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonExit->setToolTip(QApplication::translate("ProfilWindow", "Exit", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        pushButtonExit->setWhatsThis(QApplication::translate("ProfilWindow", "Exit", 0));
#endif // QT_NO_WHATSTHIS
        pushButtonExit->setText(QApplication::translate("ProfilWindow", "Exit", 0));
        textLabel1_2->setText(QApplication::translate("ProfilWindow", "Latitude Beg,deg", 0));
        textLabel1_2_2->setText(QApplication::translate("ProfilWindow", "Latitude End,deg", 0));
        textLabel1_2_2_2->setText(QApplication::translate("ProfilWindow", "Latitude Step,deg", 0));
        textLabel1_2_3->setText(QApplication::translate("ProfilWindow", "Longitude Beg,deg", 0));
        textLabel1_2_2_3->setText(QApplication::translate("ProfilWindow", "Longitude End,deg", 0));
        textLabel1_2_2_2_2->setText(QApplication::translate("ProfilWindow", "Longitude Step,deg", 0));
        textLabelRMax->setText(QApplication::translate("ProfilWindow", "rMax,km", 0));
    } // retranslateUi

};

namespace Ui {
    class ProfilWindow: public Ui_ProfilWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILWINDOW_H
