/********************************************************************************
** Form generated from reading UI file 'options.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Options
{
public:
    QGridLayout *gridLayout_3;
    QFrame *frame11;
    QGridLayout *gridLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *textLabelYear;
    QLineEdit *lineEditYear;
    QHBoxLayout *hboxLayout1;
    QLabel *textLabelMonth;
    QLineEdit *lineEditMonth;
    QHBoxLayout *hboxLayout2;
    QLabel *textLabelW;
    QLineEdit *lineEditW;
    QHBoxLayout *hboxLayout3;
    QLabel *textLabelIG;
    QLineEdit *lineEditIG;
    QCheckBox *checkBoxWIG;
    QFrame *frame5;
    QVBoxLayout *vboxLayout1;
    QCheckBox *checkBoxB0;
    QCheckBox *checkBoxNI;
    QCheckBox *checkBoxTE;
    QCheckBox *checkBoxNE;
    QCheckBox *checkBoxF1;
    QCheckBox *checkBoxD;
    QCheckBox *checkBoxStorm;
    QVBoxLayout *vboxLayout2;
    QSpacerItem *spacer4;
    QPushButton *pushButton5;
    QPushButton *pushButton5_2;
    QFrame *frame12;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBoxES;
    QGroupBox *buttonGroupF2;
    QGridLayout *gridLayout1;
    QRadioButton *radioButtonU;
    QRadioButton *radioButtonC;

    void setupUi(QDialog *Options)
    {
        if (Options->objectName().isEmpty())
            Options->setObjectName(QStringLiteral("Options"));
        Options->resize(596, 335);
        gridLayout_3 = new QGridLayout(Options);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        frame11 = new QFrame(Options);
        frame11->setObjectName(QStringLiteral("frame11"));
        frame11->setFrameShape(QFrame::Box);
        frame11->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame11);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        textLabelYear = new QLabel(frame11);
        textLabelYear->setObjectName(QStringLiteral("textLabelYear"));
        textLabelYear->setMinimumSize(QSize(130, 22));
        textLabelYear->setMaximumSize(QSize(130, 22));
        textLabelYear->setWordWrap(false);

        hboxLayout->addWidget(textLabelYear);

        lineEditYear = new QLineEdit(frame11);
        lineEditYear->setObjectName(QStringLiteral("lineEditYear"));
        lineEditYear->setMinimumSize(QSize(60, 24));
        lineEditYear->setMaximumSize(QSize(60, 24));

        hboxLayout->addWidget(lineEditYear);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        textLabelMonth = new QLabel(frame11);
        textLabelMonth->setObjectName(QStringLiteral("textLabelMonth"));
        textLabelMonth->setMinimumSize(QSize(130, 22));
        textLabelMonth->setMaximumSize(QSize(130, 22));
        textLabelMonth->setWordWrap(false);

        hboxLayout1->addWidget(textLabelMonth);

        lineEditMonth = new QLineEdit(frame11);
        lineEditMonth->setObjectName(QStringLiteral("lineEditMonth"));
        lineEditMonth->setMinimumSize(QSize(60, 24));
        lineEditMonth->setMaximumSize(QSize(60, 24));

        hboxLayout1->addWidget(lineEditMonth);


        vboxLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QStringLiteral("hboxLayout2"));
        textLabelW = new QLabel(frame11);
        textLabelW->setObjectName(QStringLiteral("textLabelW"));
        textLabelW->setMinimumSize(QSize(130, 22));
        textLabelW->setMaximumSize(QSize(130, 22));
        textLabelW->setWordWrap(false);

        hboxLayout2->addWidget(textLabelW);

        lineEditW = new QLineEdit(frame11);
        lineEditW->setObjectName(QStringLiteral("lineEditW"));
        lineEditW->setEnabled(false);
        lineEditW->setMinimumSize(QSize(60, 24));
        lineEditW->setMaximumSize(QSize(60, 24));

        hboxLayout2->addWidget(lineEditW);


        vboxLayout->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QStringLiteral("hboxLayout3"));
        textLabelIG = new QLabel(frame11);
        textLabelIG->setObjectName(QStringLiteral("textLabelIG"));
        textLabelIG->setMinimumSize(QSize(130, 22));
        textLabelIG->setMaximumSize(QSize(130, 22));
        textLabelIG->setWordWrap(false);

        hboxLayout3->addWidget(textLabelIG);

        lineEditIG = new QLineEdit(frame11);
        lineEditIG->setObjectName(QStringLiteral("lineEditIG"));
        lineEditIG->setEnabled(false);
        lineEditIG->setMinimumSize(QSize(60, 24));
        lineEditIG->setMaximumSize(QSize(60, 24));

        hboxLayout3->addWidget(lineEditIG);


        vboxLayout->addLayout(hboxLayout3);


        gridLayout->addLayout(vboxLayout, 0, 0, 1, 1);

        checkBoxWIG = new QCheckBox(frame11);
        checkBoxWIG->setObjectName(QStringLiteral("checkBoxWIG"));

        gridLayout->addWidget(checkBoxWIG, 1, 0, 1, 1);


        gridLayout_3->addWidget(frame11, 0, 0, 1, 1);

        frame5 = new QFrame(Options);
        frame5->setObjectName(QStringLiteral("frame5"));
        frame5->setFrameShape(QFrame::StyledPanel);
        frame5->setFrameShadow(QFrame::Raised);
        vboxLayout1 = new QVBoxLayout(frame5);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(11, 11, 11, 11);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        checkBoxB0 = new QCheckBox(frame5);
        checkBoxB0->setObjectName(QStringLiteral("checkBoxB0"));
        checkBoxB0->setMinimumSize(QSize(160, 22));
        checkBoxB0->setMaximumSize(QSize(160, 22));

        vboxLayout1->addWidget(checkBoxB0);

        checkBoxNI = new QCheckBox(frame5);
        checkBoxNI->setObjectName(QStringLiteral("checkBoxNI"));
        checkBoxNI->setMinimumSize(QSize(160, 22));
        checkBoxNI->setMaximumSize(QSize(160, 22));

        vboxLayout1->addWidget(checkBoxNI);

        checkBoxTE = new QCheckBox(frame5);
        checkBoxTE->setObjectName(QStringLiteral("checkBoxTE"));
        checkBoxTE->setMinimumSize(QSize(160, 22));
        checkBoxTE->setMaximumSize(QSize(160, 22));

        vboxLayout1->addWidget(checkBoxTE);

        checkBoxNE = new QCheckBox(frame5);
        checkBoxNE->setObjectName(QStringLiteral("checkBoxNE"));
        checkBoxNE->setMinimumSize(QSize(160, 22));
        checkBoxNE->setMaximumSize(QSize(160, 22));

        vboxLayout1->addWidget(checkBoxNE);

        checkBoxF1 = new QCheckBox(frame5);
        checkBoxF1->setObjectName(QStringLiteral("checkBoxF1"));
        checkBoxF1->setMinimumSize(QSize(160, 22));
        checkBoxF1->setMaximumSize(QSize(160, 22));

        vboxLayout1->addWidget(checkBoxF1);

        checkBoxD = new QCheckBox(frame5);
        checkBoxD->setObjectName(QStringLiteral("checkBoxD"));
        checkBoxD->setMinimumSize(QSize(160, 22));
        checkBoxD->setMaximumSize(QSize(160, 22));

        vboxLayout1->addWidget(checkBoxD);

        checkBoxStorm = new QCheckBox(frame5);
        checkBoxStorm->setObjectName(QStringLiteral("checkBoxStorm"));
        checkBoxStorm->setMinimumSize(QSize(160, 22));
        checkBoxStorm->setMaximumSize(QSize(160, 22));

        vboxLayout1->addWidget(checkBoxStorm);


        gridLayout_3->addWidget(frame5, 0, 1, 2, 1);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        spacer4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout2->addItem(spacer4);

        pushButton5 = new QPushButton(Options);
        pushButton5->setObjectName(QStringLiteral("pushButton5"));
        pushButton5->setMinimumSize(QSize(80, 24));
        pushButton5->setMaximumSize(QSize(80, 24));
        pushButton5->setDefault(true);

        vboxLayout2->addWidget(pushButton5);

        pushButton5_2 = new QPushButton(Options);
        pushButton5_2->setObjectName(QStringLiteral("pushButton5_2"));
        pushButton5_2->setMinimumSize(QSize(80, 24));
        pushButton5_2->setMaximumSize(QSize(80, 24));

        vboxLayout2->addWidget(pushButton5_2);


        gridLayout_3->addLayout(vboxLayout2, 0, 2, 1, 1);

        frame12 = new QFrame(Options);
        frame12->setObjectName(QStringLiteral("frame12"));
        frame12->setMinimumSize(QSize(220, 150));
        frame12->setFrameShape(QFrame::Box);
        frame12->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame12);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        checkBoxES = new QCheckBox(frame12);
        checkBoxES->setObjectName(QStringLiteral("checkBoxES"));
        checkBoxES->setMinimumSize(QSize(160, 22));
        checkBoxES->setMaximumSize(QSize(160, 22));

        gridLayout_2->addWidget(checkBoxES, 0, 0, 1, 1);

        buttonGroupF2 = new QGroupBox(frame12);
        buttonGroupF2->setObjectName(QStringLiteral("buttonGroupF2"));
        buttonGroupF2->setAutoFillBackground(false);
        gridLayout1 = new QGridLayout(buttonGroupF2);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        radioButtonU = new QRadioButton(buttonGroupF2);
        radioButtonU->setObjectName(QStringLiteral("radioButtonU"));
        radioButtonU->setMinimumSize(QSize(160, 22));
        radioButtonU->setMaximumSize(QSize(160, 22));
        radioButtonU->setChecked(true);

        gridLayout1->addWidget(radioButtonU, 0, 0, 1, 1);

        radioButtonC = new QRadioButton(buttonGroupF2);
        radioButtonC->setObjectName(QStringLiteral("radioButtonC"));
        radioButtonC->setMinimumSize(QSize(160, 22));
        radioButtonC->setMaximumSize(QSize(160, 22));

        gridLayout1->addWidget(radioButtonC, 1, 0, 1, 1);


        gridLayout_2->addWidget(buttonGroupF2, 1, 0, 1, 1);


        gridLayout_3->addWidget(frame12, 1, 0, 1, 1);


        retranslateUi(Options);
        QObject::connect(checkBoxWIG, SIGNAL(toggled(bool)), lineEditYear, SLOT(setDisabled(bool)));
        QObject::connect(checkBoxWIG, SIGNAL(toggled(bool)), lineEditW, SLOT(setEnabled(bool)));
        QObject::connect(checkBoxWIG, SIGNAL(toggled(bool)), lineEditIG, SLOT(setEnabled(bool)));
        QObject::connect(pushButton5, SIGNAL(pressed()), Options, SLOT(accept()));
        QObject::connect(pushButton5_2, SIGNAL(pressed()), Options, SLOT(reject()));

        QMetaObject::connectSlotsByName(Options);
    } // setupUi

    void retranslateUi(QDialog *Options)
    {
        Options->setWindowTitle(QApplication::translate("Options", "Optoins", 0));
        textLabelYear->setText(QApplication::translate("Options", "Year", 0));
        textLabelMonth->setText(QApplication::translate("Options", "Mons, Day:mmdd", 0));
        lineEditMonth->setText(QString());
        textLabelW->setText(QApplication::translate("Options", "W", 0));
        textLabelIG->setText(QApplication::translate("Options", "IG", 0));
        checkBoxWIG->setText(QApplication::translate("Options", "InPut W,IG", 0));
        checkBoxB0->setText(QApplication::translate("Options", "B0 - Table option", 0));
        checkBoxNI->setText(QApplication::translate("Options", "Ni - Standard", 0));
        checkBoxTE->setText(QApplication::translate("Options", "Te - Standard", 0));
        checkBoxNE->setText(QApplication::translate("Options", "Ne - Standard Profile", 0));
        checkBoxF1->setText(QApplication::translate("Options", "Standard F1", 0));
        checkBoxD->setText(QApplication::translate("Options", "D-region: IRI-95", 0));
        checkBoxStorm->setText(QApplication::translate("Options", "F0F2 storm model", 0));
        pushButton5->setText(QApplication::translate("Options", "Ok", 0));
        pushButton5_2->setText(QApplication::translate("Options", "Cancel", 0));
        checkBoxES->setText(QApplication::translate("Options", "Es-Layer Foricast", 0));
        buttonGroupF2->setTitle(QApplication::translate("Options", "F2-Layer Foricast", 0));
        radioButtonU->setText(QApplication::translate("Options", "URSI", 0));
        radioButtonC->setText(QApplication::translate("Options", "CCIR", 0));
    } // retranslateUi

};

namespace Ui {
    class Options: public Ui_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
