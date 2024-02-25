/********************************************************************************
** Form generated from reading UI file 'path.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATH_H
#define UI_PATH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Path
{
public:
    QGridLayout *gridLayout_2;
    QFrame *frameAll;
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QFrame *frameIon;
    QFrame *frameTrek;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditInf;
    QSpacerItem *spacer1;
    QPushButton *pushButtonRead;
    QPushButton *pushButtonWrite;
    QPushButton *pushButtonWriteMUF;
    QPushButton *pushButtonRun;
    QPushButton *pushButtonExit;

    void setupUi(QDialog *Path)
    {
        if (Path->objectName().isEmpty())
            Path->setObjectName(QStringLiteral("Path"));
        Path->resize(584, 539);
        gridLayout_2 = new QGridLayout(Path);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        frameAll = new QFrame(Path);
        frameAll->setObjectName(QStringLiteral("frameAll"));
        frameAll->setFrameShape(QFrame::StyledPanel);
        frameAll->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frameAll);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        frameIon = new QFrame(frameAll);
        frameIon->setObjectName(QStringLiteral("frameIon"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frameIon->sizePolicy().hasHeightForWidth());
        frameIon->setSizePolicy(sizePolicy);
        frameIon->setMinimumSize(QSize(100, 200));
        frameIon->setMaximumSize(QSize(200, 32767));
        frameIon->setFrameShape(QFrame::Box);
        frameIon->setFrameShadow(QFrame::Raised);

        hboxLayout->addWidget(frameIon);

        frameTrek = new QFrame(frameAll);
        frameTrek->setObjectName(QStringLiteral("frameTrek"));
        sizePolicy.setHeightForWidth(frameTrek->sizePolicy().hasHeightForWidth());
        frameTrek->setSizePolicy(sizePolicy);
        frameTrek->setMinimumSize(QSize(300, 200));
        frameTrek->setFrameShape(QFrame::Box);
        frameTrek->setFrameShadow(QFrame::Raised);

        hboxLayout->addWidget(frameTrek);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);


        gridLayout_2->addWidget(frameAll, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEditInf = new QLineEdit(Path);
        lineEditInf->setObjectName(QStringLiteral("lineEditInf"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditInf->sizePolicy().hasHeightForWidth());
        lineEditInf->setSizePolicy(sizePolicy1);
        lineEditInf->setMinimumSize(QSize(150, 24));
        lineEditInf->setMaximumSize(QSize(32767, 24));

        horizontalLayout->addWidget(lineEditInf);

        spacer1 = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacer1);

        pushButtonRead = new QPushButton(Path);
        pushButtonRead->setObjectName(QStringLiteral("pushButtonRead"));
        pushButtonRead->setMinimumSize(QSize(80, 24));
        pushButtonRead->setMaximumSize(QSize(80, 24));
        pushButtonRead->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonRead);

        pushButtonWrite = new QPushButton(Path);
        pushButtonWrite->setObjectName(QStringLiteral("pushButtonWrite"));
        pushButtonWrite->setMinimumSize(QSize(80, 24));
        pushButtonWrite->setMaximumSize(QSize(80, 24));
        pushButtonWrite->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonWrite);

        pushButtonWriteMUF = new QPushButton(Path);
        pushButtonWriteMUF->setObjectName(QStringLiteral("pushButtonWriteMUF"));
        pushButtonWriteMUF->setMinimumSize(QSize(80, 24));
        pushButtonWriteMUF->setMaximumSize(QSize(80, 24));
        pushButtonWriteMUF->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonWriteMUF);

        pushButtonRun = new QPushButton(Path);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));
        pushButtonRun->setMinimumSize(QSize(80, 24));
        pushButtonRun->setMaximumSize(QSize(80, 24));
        pushButtonRun->setAutoDefault(false);

        horizontalLayout->addWidget(pushButtonRun);

        pushButtonExit = new QPushButton(Path);
        pushButtonExit->setObjectName(QStringLiteral("pushButtonExit"));
        pushButtonExit->setMinimumSize(QSize(80, 24));
        pushButtonExit->setMaximumSize(QSize(80, 24));

        horizontalLayout->addWidget(pushButtonExit);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        QWidget::setTabOrder(pushButtonExit, pushButtonRead);
        QWidget::setTabOrder(pushButtonRead, pushButtonRun);

        retranslateUi(Path);
        QObject::connect(pushButtonExit, SIGNAL(pressed()), Path, SLOT(slotExit()));
        QObject::connect(pushButtonRun, SIGNAL(pressed()), Path, SLOT(slotRun()));
        QObject::connect(pushButtonRead, SIGNAL(pressed()), Path, SLOT(slotRead()));
        QObject::connect(pushButtonWriteMUF, SIGNAL(clicked()), Path, SLOT(slotWriteMUF()));
        QObject::connect(pushButtonWrite, SIGNAL(clicked()), Path, SLOT(slotWrite()));

        pushButtonExit->setDefault(true);


        QMetaObject::connectSlotsByName(Path);
    } // setupUi

    void retranslateUi(QDialog *Path)
    {
        Path->setWindowTitle(QApplication::translate("Path", "Path", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonRead->setToolTip(QApplication::translate("Path", "Input FileName", 0));
#endif // QT_NO_TOOLTIP
        pushButtonRead->setText(QApplication::translate("Path", "In File", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonWrite->setToolTip(QApplication::translate("Path", "Input FileName", 0));
#endif // QT_NO_TOOLTIP
        pushButtonWrite->setText(QApplication::translate("Path", "Out File", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonWriteMUF->setToolTip(QApplication::translate("Path", "Input FileName", 0));
#endif // QT_NO_TOOLTIP
        pushButtonWriteMUF->setText(QApplication::translate("Path", "MUF File", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonRun->setToolTip(QApplication::translate("Path", "Run Calculated", 0));
#endif // QT_NO_TOOLTIP
        pushButtonRun->setText(QApplication::translate("Path", "Run", 0));
#ifndef QT_NO_TOOLTIP
        pushButtonExit->setToolTip(QApplication::translate("Path", "Exit", 0));
#endif // QT_NO_TOOLTIP
        pushButtonExit->setText(QApplication::translate("Path", "Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class Path: public Ui_Path {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATH_H
