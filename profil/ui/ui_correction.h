/********************************************************************************
** Form generated from reading UI file 'correction.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CORRECTION_H
#define UI_CORRECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_DialogCorrection
{
public:
    QGridLayout *gridLayout_10;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *textLabelTimeBeg;
    QLineEdit *lineEditTimeBeg;
    QHBoxLayout *horizontalLayout_2;
    QLabel *textLabel1_2_3;
    QLineEdit *lineEditLonB;
    QHBoxLayout *horizontalLayout_3;
    QLabel *textLabel1_2;
    QLineEdit *lineEditLatB;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *textLabel1_3;
    QLineEdit *lineEditF0E_1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *textLabel1_4;
    QLineEdit *lineEditHmE_1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *textLabel1_5;
    QLineEdit *lineEditF0F1_1;
    QHBoxLayout *horizontalLayout_6;
    QLabel *textLabel1_6;
    QLineEdit *lineEditHmF1_1;
    QHBoxLayout *horizontalLayout_7;
    QLabel *textLabel1_7;
    QLineEdit *lineEditF0F2_1;
    QHBoxLayout *horizontalLayout_8;
    QLabel *textLabel1_8;
    QLineEdit *lineEditHmF2_1;
    QHBoxLayout *horizontalLayout_9;
    QLabel *textLabel1_9;
    QLineEdit *lineEditF0ES_1;
    QHBoxLayout *horizontalLayout_10;
    QLabel *textLabel1_10;
    QLineEdit *lineEditHES_1;
    QFrame *frame_4;
    QGridLayout *gridLayout_7;
    QFrame *frame_7;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_23;
    QLabel *textLabelTimeBeg_3;
    QLineEdit *lineEditTimeEnd;
    QHBoxLayout *horizontalLayout_24;
    QLabel *textLabel1_2_5;
    QLineEdit *lineEditLonE;
    QHBoxLayout *horizontalLayout_25;
    QLabel *textLabel1_20;
    QLineEdit *lineEditLatE;
    QFrame *frame_8;
    QGridLayout *gridLayout_9;
    QHBoxLayout *horizontalLayout_26;
    QLabel *textLabel1_21;
    QLineEdit *lineEditF0E_2;
    QHBoxLayout *horizontalLayout_27;
    QLabel *textLabel1_22;
    QLineEdit *lineEditHmE_2;
    QHBoxLayout *horizontalLayout_28;
    QLabel *textLabel1_23;
    QLineEdit *lineEditF0F1_2;
    QHBoxLayout *horizontalLayout_29;
    QLabel *textLabel1_24;
    QLineEdit *lineEditHmF1_2;
    QHBoxLayout *horizontalLayout_30;
    QLabel *textLabel1_25;
    QLineEdit *lineEditF0F2_2;
    QHBoxLayout *horizontalLayout_31;
    QLabel *textLabel1_26;
    QLineEdit *lineEditHmF2_2;
    QHBoxLayout *horizontalLayout_32;
    QLabel *textLabel1_27;
    QLineEdit *lineEditF0ES_2;
    QHBoxLayout *horizontalLayout_33;
    QLabel *textLabel1_28;
    QLineEdit *lineEditHES_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogCorrection)
    {
        if (DialogCorrection->objectName().isEmpty())
            DialogCorrection->setObjectName(QStringLiteral("DialogCorrection"));
        DialogCorrection->resize(527, 432);
        gridLayout_10 = new QGridLayout(DialogCorrection);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        frame_3 = new QFrame(DialogCorrection);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        frame = new QFrame(frame_3);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textLabelTimeBeg = new QLabel(frame);
        textLabelTimeBeg->setObjectName(QStringLiteral("textLabelTimeBeg"));
        textLabelTimeBeg->setMinimumSize(QSize(100, 22));
        textLabelTimeBeg->setMaximumSize(QSize(100, 22));
        textLabelTimeBeg->setWordWrap(false);

        horizontalLayout->addWidget(textLabelTimeBeg);

        lineEditTimeBeg = new QLineEdit(frame);
        lineEditTimeBeg->setObjectName(QStringLiteral("lineEditTimeBeg"));
        lineEditTimeBeg->setMinimumSize(QSize(80, 24));
        lineEditTimeBeg->setMaximumSize(QSize(80, 24));

        horizontalLayout->addWidget(lineEditTimeBeg);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        textLabel1_2_3 = new QLabel(frame);
        textLabel1_2_3->setObjectName(QStringLiteral("textLabel1_2_3"));
        textLabel1_2_3->setMinimumSize(QSize(130, 22));
        textLabel1_2_3->setMaximumSize(QSize(100, 22));
        textLabel1_2_3->setWordWrap(false);

        horizontalLayout_2->addWidget(textLabel1_2_3);

        lineEditLonB = new QLineEdit(frame);
        lineEditLonB->setObjectName(QStringLiteral("lineEditLonB"));
        lineEditLonB->setMinimumSize(QSize(80, 24));
        lineEditLonB->setMaximumSize(QSize(80, 24));

        horizontalLayout_2->addWidget(lineEditLonB);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        textLabel1_2 = new QLabel(frame);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setMinimumSize(QSize(130, 22));
        textLabel1_2->setMaximumSize(QSize(100, 22));
        textLabel1_2->setWordWrap(false);

        horizontalLayout_3->addWidget(textLabel1_2);

        lineEditLatB = new QLineEdit(frame);
        lineEditLatB->setObjectName(QStringLiteral("lineEditLatB"));
        lineEditLatB->setMinimumSize(QSize(80, 24));
        lineEditLatB->setMaximumSize(QSize(80, 24));

        horizontalLayout_3->addWidget(lineEditLatB);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        textLabelTimeBeg->raise();

        gridLayout_3->addWidget(frame, 0, 0, 1, 1);

        frame_2 = new QFrame(frame_3);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        textLabel1_3 = new QLabel(frame_2);
        textLabel1_3->setObjectName(QStringLiteral("textLabel1_3"));
        textLabel1_3->setMinimumSize(QSize(100, 22));
        textLabel1_3->setMaximumSize(QSize(100, 22));
        textLabel1_3->setWordWrap(false);

        horizontalLayout_11->addWidget(textLabel1_3);

        lineEditF0E_1 = new QLineEdit(frame_2);
        lineEditF0E_1->setObjectName(QStringLiteral("lineEditF0E_1"));
        lineEditF0E_1->setMinimumSize(QSize(80, 24));
        lineEditF0E_1->setMaximumSize(QSize(80, 24));

        horizontalLayout_11->addWidget(lineEditF0E_1);


        gridLayout_2->addLayout(horizontalLayout_11, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        textLabel1_4 = new QLabel(frame_2);
        textLabel1_4->setObjectName(QStringLiteral("textLabel1_4"));
        textLabel1_4->setMinimumSize(QSize(100, 22));
        textLabel1_4->setMaximumSize(QSize(100, 22));
        textLabel1_4->setWordWrap(false);

        horizontalLayout_4->addWidget(textLabel1_4);

        lineEditHmE_1 = new QLineEdit(frame_2);
        lineEditHmE_1->setObjectName(QStringLiteral("lineEditHmE_1"));
        lineEditHmE_1->setMinimumSize(QSize(80, 24));
        lineEditHmE_1->setMaximumSize(QSize(80, 24));

        horizontalLayout_4->addWidget(lineEditHmE_1);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        textLabel1_5 = new QLabel(frame_2);
        textLabel1_5->setObjectName(QStringLiteral("textLabel1_5"));
        textLabel1_5->setMinimumSize(QSize(100, 22));
        textLabel1_5->setMaximumSize(QSize(100, 22));
        textLabel1_5->setWordWrap(false);

        horizontalLayout_5->addWidget(textLabel1_5);

        lineEditF0F1_1 = new QLineEdit(frame_2);
        lineEditF0F1_1->setObjectName(QStringLiteral("lineEditF0F1_1"));
        lineEditF0F1_1->setMinimumSize(QSize(80, 24));
        lineEditF0F1_1->setMaximumSize(QSize(80, 24));

        horizontalLayout_5->addWidget(lineEditF0F1_1);


        gridLayout_2->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        textLabel1_6 = new QLabel(frame_2);
        textLabel1_6->setObjectName(QStringLiteral("textLabel1_6"));
        textLabel1_6->setMinimumSize(QSize(100, 22));
        textLabel1_6->setMaximumSize(QSize(100, 22));
        textLabel1_6->setWordWrap(false);

        horizontalLayout_6->addWidget(textLabel1_6);

        lineEditHmF1_1 = new QLineEdit(frame_2);
        lineEditHmF1_1->setObjectName(QStringLiteral("lineEditHmF1_1"));
        lineEditHmF1_1->setMinimumSize(QSize(80, 24));
        lineEditHmF1_1->setMaximumSize(QSize(80, 24));

        horizontalLayout_6->addWidget(lineEditHmF1_1);


        gridLayout_2->addLayout(horizontalLayout_6, 3, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        textLabel1_7 = new QLabel(frame_2);
        textLabel1_7->setObjectName(QStringLiteral("textLabel1_7"));
        textLabel1_7->setMinimumSize(QSize(100, 22));
        textLabel1_7->setMaximumSize(QSize(100, 22));
        textLabel1_7->setWordWrap(false);

        horizontalLayout_7->addWidget(textLabel1_7);

        lineEditF0F2_1 = new QLineEdit(frame_2);
        lineEditF0F2_1->setObjectName(QStringLiteral("lineEditF0F2_1"));
        lineEditF0F2_1->setMinimumSize(QSize(80, 24));
        lineEditF0F2_1->setMaximumSize(QSize(80, 24));

        horizontalLayout_7->addWidget(lineEditF0F2_1);


        gridLayout_2->addLayout(horizontalLayout_7, 4, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        textLabel1_8 = new QLabel(frame_2);
        textLabel1_8->setObjectName(QStringLiteral("textLabel1_8"));
        textLabel1_8->setMinimumSize(QSize(100, 22));
        textLabel1_8->setMaximumSize(QSize(100, 22));
        textLabel1_8->setWordWrap(false);

        horizontalLayout_8->addWidget(textLabel1_8);

        lineEditHmF2_1 = new QLineEdit(frame_2);
        lineEditHmF2_1->setObjectName(QStringLiteral("lineEditHmF2_1"));
        lineEditHmF2_1->setMinimumSize(QSize(80, 24));
        lineEditHmF2_1->setMaximumSize(QSize(80, 24));

        horizontalLayout_8->addWidget(lineEditHmF2_1);


        gridLayout_2->addLayout(horizontalLayout_8, 5, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        textLabel1_9 = new QLabel(frame_2);
        textLabel1_9->setObjectName(QStringLiteral("textLabel1_9"));
        textLabel1_9->setMinimumSize(QSize(100, 22));
        textLabel1_9->setMaximumSize(QSize(100, 22));
        textLabel1_9->setWordWrap(false);

        horizontalLayout_9->addWidget(textLabel1_9);

        lineEditF0ES_1 = new QLineEdit(frame_2);
        lineEditF0ES_1->setObjectName(QStringLiteral("lineEditF0ES_1"));
        lineEditF0ES_1->setMinimumSize(QSize(80, 24));
        lineEditF0ES_1->setMaximumSize(QSize(80, 24));

        horizontalLayout_9->addWidget(lineEditF0ES_1);


        gridLayout_2->addLayout(horizontalLayout_9, 6, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        textLabel1_10 = new QLabel(frame_2);
        textLabel1_10->setObjectName(QStringLiteral("textLabel1_10"));
        textLabel1_10->setMinimumSize(QSize(100, 22));
        textLabel1_10->setMaximumSize(QSize(100, 22));
        textLabel1_10->setWordWrap(false);

        horizontalLayout_10->addWidget(textLabel1_10);

        lineEditHES_1 = new QLineEdit(frame_2);
        lineEditHES_1->setObjectName(QStringLiteral("lineEditHES_1"));
        lineEditHES_1->setMinimumSize(QSize(80, 24));
        lineEditHES_1->setMaximumSize(QSize(80, 24));

        horizontalLayout_10->addWidget(lineEditHES_1);


        gridLayout_2->addLayout(horizontalLayout_10, 7, 0, 1, 1);


        gridLayout_3->addWidget(frame_2, 1, 0, 1, 1);


        gridLayout_10->addWidget(frame_3, 0, 0, 1, 1);

        frame_4 = new QFrame(DialogCorrection);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_7 = new QGridLayout(frame_4);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        frame_7 = new QFrame(frame_4);
        frame_7->setObjectName(QStringLiteral("frame_7"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        gridLayout_8 = new QGridLayout(frame_7);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        textLabelTimeBeg_3 = new QLabel(frame_7);
        textLabelTimeBeg_3->setObjectName(QStringLiteral("textLabelTimeBeg_3"));
        textLabelTimeBeg_3->setMinimumSize(QSize(100, 22));
        textLabelTimeBeg_3->setMaximumSize(QSize(100, 22));
        textLabelTimeBeg_3->setWordWrap(false);

        horizontalLayout_23->addWidget(textLabelTimeBeg_3);

        lineEditTimeEnd = new QLineEdit(frame_7);
        lineEditTimeEnd->setObjectName(QStringLiteral("lineEditTimeEnd"));
        lineEditTimeEnd->setMinimumSize(QSize(80, 24));
        lineEditTimeEnd->setMaximumSize(QSize(80, 24));

        horizontalLayout_23->addWidget(lineEditTimeEnd);


        gridLayout_8->addLayout(horizontalLayout_23, 0, 0, 1, 1);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        textLabel1_2_5 = new QLabel(frame_7);
        textLabel1_2_5->setObjectName(QStringLiteral("textLabel1_2_5"));
        textLabel1_2_5->setMinimumSize(QSize(130, 22));
        textLabel1_2_5->setMaximumSize(QSize(100, 22));
        textLabel1_2_5->setWordWrap(false);

        horizontalLayout_24->addWidget(textLabel1_2_5);

        lineEditLonE = new QLineEdit(frame_7);
        lineEditLonE->setObjectName(QStringLiteral("lineEditLonE"));
        lineEditLonE->setMinimumSize(QSize(80, 24));
        lineEditLonE->setMaximumSize(QSize(80, 24));

        horizontalLayout_24->addWidget(lineEditLonE);


        gridLayout_8->addLayout(horizontalLayout_24, 1, 0, 1, 1);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        textLabel1_20 = new QLabel(frame_7);
        textLabel1_20->setObjectName(QStringLiteral("textLabel1_20"));
        textLabel1_20->setMinimumSize(QSize(130, 22));
        textLabel1_20->setMaximumSize(QSize(100, 22));
        textLabel1_20->setWordWrap(false);

        horizontalLayout_25->addWidget(textLabel1_20);

        lineEditLatE = new QLineEdit(frame_7);
        lineEditLatE->setObjectName(QStringLiteral("lineEditLatE"));
        lineEditLatE->setMinimumSize(QSize(80, 24));
        lineEditLatE->setMaximumSize(QSize(80, 24));

        horizontalLayout_25->addWidget(lineEditLatE);


        gridLayout_8->addLayout(horizontalLayout_25, 2, 0, 1, 1);


        gridLayout_7->addWidget(frame_7, 0, 0, 1, 1);

        frame_8 = new QFrame(frame_4);
        frame_8->setObjectName(QStringLiteral("frame_8"));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        gridLayout_9 = new QGridLayout(frame_8);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        textLabel1_21 = new QLabel(frame_8);
        textLabel1_21->setObjectName(QStringLiteral("textLabel1_21"));
        textLabel1_21->setMinimumSize(QSize(100, 22));
        textLabel1_21->setMaximumSize(QSize(100, 22));
        textLabel1_21->setWordWrap(false);

        horizontalLayout_26->addWidget(textLabel1_21);

        lineEditF0E_2 = new QLineEdit(frame_8);
        lineEditF0E_2->setObjectName(QStringLiteral("lineEditF0E_2"));
        lineEditF0E_2->setMinimumSize(QSize(80, 24));
        lineEditF0E_2->setMaximumSize(QSize(80, 24));

        horizontalLayout_26->addWidget(lineEditF0E_2);


        gridLayout_9->addLayout(horizontalLayout_26, 0, 0, 1, 1);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        textLabel1_22 = new QLabel(frame_8);
        textLabel1_22->setObjectName(QStringLiteral("textLabel1_22"));
        textLabel1_22->setMinimumSize(QSize(100, 22));
        textLabel1_22->setMaximumSize(QSize(100, 22));
        textLabel1_22->setWordWrap(false);

        horizontalLayout_27->addWidget(textLabel1_22);

        lineEditHmE_2 = new QLineEdit(frame_8);
        lineEditHmE_2->setObjectName(QStringLiteral("lineEditHmE_2"));
        lineEditHmE_2->setMinimumSize(QSize(80, 24));
        lineEditHmE_2->setMaximumSize(QSize(80, 24));

        horizontalLayout_27->addWidget(lineEditHmE_2);


        gridLayout_9->addLayout(horizontalLayout_27, 1, 0, 1, 1);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        textLabel1_23 = new QLabel(frame_8);
        textLabel1_23->setObjectName(QStringLiteral("textLabel1_23"));
        textLabel1_23->setMinimumSize(QSize(100, 22));
        textLabel1_23->setMaximumSize(QSize(100, 22));
        textLabel1_23->setWordWrap(false);

        horizontalLayout_28->addWidget(textLabel1_23);

        lineEditF0F1_2 = new QLineEdit(frame_8);
        lineEditF0F1_2->setObjectName(QStringLiteral("lineEditF0F1_2"));
        lineEditF0F1_2->setMinimumSize(QSize(80, 24));
        lineEditF0F1_2->setMaximumSize(QSize(80, 24));

        horizontalLayout_28->addWidget(lineEditF0F1_2);


        gridLayout_9->addLayout(horizontalLayout_28, 2, 0, 1, 1);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        textLabel1_24 = new QLabel(frame_8);
        textLabel1_24->setObjectName(QStringLiteral("textLabel1_24"));
        textLabel1_24->setMinimumSize(QSize(100, 22));
        textLabel1_24->setMaximumSize(QSize(100, 22));
        textLabel1_24->setWordWrap(false);

        horizontalLayout_29->addWidget(textLabel1_24);

        lineEditHmF1_2 = new QLineEdit(frame_8);
        lineEditHmF1_2->setObjectName(QStringLiteral("lineEditHmF1_2"));
        lineEditHmF1_2->setMinimumSize(QSize(80, 24));
        lineEditHmF1_2->setMaximumSize(QSize(80, 24));

        horizontalLayout_29->addWidget(lineEditHmF1_2);


        gridLayout_9->addLayout(horizontalLayout_29, 3, 0, 1, 1);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        textLabel1_25 = new QLabel(frame_8);
        textLabel1_25->setObjectName(QStringLiteral("textLabel1_25"));
        textLabel1_25->setMinimumSize(QSize(100, 22));
        textLabel1_25->setMaximumSize(QSize(100, 22));
        textLabel1_25->setWordWrap(false);

        horizontalLayout_30->addWidget(textLabel1_25);

        lineEditF0F2_2 = new QLineEdit(frame_8);
        lineEditF0F2_2->setObjectName(QStringLiteral("lineEditF0F2_2"));
        lineEditF0F2_2->setMinimumSize(QSize(80, 24));
        lineEditF0F2_2->setMaximumSize(QSize(80, 24));

        horizontalLayout_30->addWidget(lineEditF0F2_2);


        gridLayout_9->addLayout(horizontalLayout_30, 4, 0, 1, 1);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setObjectName(QStringLiteral("horizontalLayout_31"));
        textLabel1_26 = new QLabel(frame_8);
        textLabel1_26->setObjectName(QStringLiteral("textLabel1_26"));
        textLabel1_26->setMinimumSize(QSize(100, 22));
        textLabel1_26->setMaximumSize(QSize(100, 22));
        textLabel1_26->setWordWrap(false);

        horizontalLayout_31->addWidget(textLabel1_26);

        lineEditHmF2_2 = new QLineEdit(frame_8);
        lineEditHmF2_2->setObjectName(QStringLiteral("lineEditHmF2_2"));
        lineEditHmF2_2->setMinimumSize(QSize(80, 24));
        lineEditHmF2_2->setMaximumSize(QSize(80, 24));

        horizontalLayout_31->addWidget(lineEditHmF2_2);


        gridLayout_9->addLayout(horizontalLayout_31, 5, 0, 1, 1);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setObjectName(QStringLiteral("horizontalLayout_32"));
        textLabel1_27 = new QLabel(frame_8);
        textLabel1_27->setObjectName(QStringLiteral("textLabel1_27"));
        textLabel1_27->setMinimumSize(QSize(100, 22));
        textLabel1_27->setMaximumSize(QSize(100, 22));
        textLabel1_27->setWordWrap(false);

        horizontalLayout_32->addWidget(textLabel1_27);

        lineEditF0ES_2 = new QLineEdit(frame_8);
        lineEditF0ES_2->setObjectName(QStringLiteral("lineEditF0ES_2"));
        lineEditF0ES_2->setMinimumSize(QSize(80, 24));
        lineEditF0ES_2->setMaximumSize(QSize(80, 24));

        horizontalLayout_32->addWidget(lineEditF0ES_2);


        gridLayout_9->addLayout(horizontalLayout_32, 6, 0, 1, 1);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setObjectName(QStringLiteral("horizontalLayout_33"));
        textLabel1_28 = new QLabel(frame_8);
        textLabel1_28->setObjectName(QStringLiteral("textLabel1_28"));
        textLabel1_28->setMinimumSize(QSize(100, 22));
        textLabel1_28->setMaximumSize(QSize(100, 22));
        textLabel1_28->setWordWrap(false);

        horizontalLayout_33->addWidget(textLabel1_28);

        lineEditHES_2 = new QLineEdit(frame_8);
        lineEditHES_2->setObjectName(QStringLiteral("lineEditHES_2"));
        lineEditHES_2->setMinimumSize(QSize(80, 24));
        lineEditHES_2->setMaximumSize(QSize(80, 24));

        horizontalLayout_33->addWidget(lineEditHES_2);


        gridLayout_9->addLayout(horizontalLayout_33, 7, 0, 1, 1);


        gridLayout_7->addWidget(frame_8, 1, 0, 1, 1);


        gridLayout_10->addWidget(frame_4, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(DialogCorrection);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_10->addWidget(buttonBox, 1, 0, 1, 2);


        retranslateUi(DialogCorrection);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogCorrection, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogCorrection, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogCorrection);
    } // setupUi

    void retranslateUi(QDialog *DialogCorrection)
    {
        DialogCorrection->setWindowTitle(QApplication::translate("DialogCorrection", "Dialog", 0));
        textLabelTimeBeg->setText(QApplication::translate("DialogCorrection", "TimeBeg,hh:mm", 0));
        lineEditTimeBeg->setText(QString());
        textLabel1_2_3->setText(QApplication::translate("DialogCorrection", "Longitude Beg,deg", 0));
        textLabel1_2->setText(QApplication::translate("DialogCorrection", "Latitude Beg,deg", 0));
        textLabel1_3->setText(QApplication::translate("DialogCorrection", "F0E, MHz", 0));
        textLabel1_4->setText(QApplication::translate("DialogCorrection", "HmE, km", 0));
        textLabel1_5->setText(QApplication::translate("DialogCorrection", "F0F1, MHz", 0));
        textLabel1_6->setText(QApplication::translate("DialogCorrection", "HmF1, km", 0));
        textLabel1_7->setText(QApplication::translate("DialogCorrection", "F0F2, MHz", 0));
        textLabel1_8->setText(QApplication::translate("DialogCorrection", "HmF2, km", 0));
        textLabel1_9->setText(QApplication::translate("DialogCorrection", "F0Es, MHz", 0));
        textLabel1_10->setText(QApplication::translate("DialogCorrection", "HEs km", 0));
        textLabelTimeBeg_3->setText(QApplication::translate("DialogCorrection", "TimeEnd,hh:mm", 0));
        lineEditTimeEnd->setText(QString());
        textLabel1_2_5->setText(QApplication::translate("DialogCorrection", "Longitude End,deg", 0));
        textLabel1_20->setText(QApplication::translate("DialogCorrection", "Latitude End,deg", 0));
        textLabel1_21->setText(QApplication::translate("DialogCorrection", "F0E, MHz", 0));
        textLabel1_22->setText(QApplication::translate("DialogCorrection", "HmE, km", 0));
        textLabel1_23->setText(QApplication::translate("DialogCorrection", "F0F1, MHz", 0));
        textLabel1_24->setText(QApplication::translate("DialogCorrection", "HmF1, km", 0));
        textLabel1_25->setText(QApplication::translate("DialogCorrection", "F0F2, MHz", 0));
        textLabel1_26->setText(QApplication::translate("DialogCorrection", "HmF2, km", 0));
        textLabel1_27->setText(QApplication::translate("DialogCorrection", "F0Es, MHz", 0));
        textLabel1_28->setText(QApplication::translate("DialogCorrection", "HEs km", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogCorrection: public Ui_DialogCorrection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORRECTION_H
