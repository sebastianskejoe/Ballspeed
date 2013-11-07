/********************************************************************************
** Form generated from reading UI file 'ui.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_H
#define UI_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <videoframe.h>

QT_BEGIN_NAMESPACE

class Ui_BallspeedUI
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *topLayout;
    QLineEdit *videoPath;
    QPushButton *loadVideoButton;
    QVBoxLayout *settingsLayout;
    QLabel *ballDiametersLabel;
    QLineEdit *ballDiameter;
    QLabel *goalHeightLabel;
    QLineEdit *goalHeight;
    QLabel *diameterLabel;
    QSlider *diameter;
    QLabel *houghLabel;
    QLabel *hough;
    QLabel *houghThresholdLabel;
    QSlider *houghThreshold;
    QLabel *templateLabel;
    QLabel *templateImage;
    QPushButton *calculateSpeed;
    QPushButton *matchTemplate;
    QHBoxLayout *hboxLayout;
    QPushButton *matchAllBalls;
    QLineEdit *frameCount;
    QVBoxLayout *vboxLayout;
    VideoFrame *frame;
    QHBoxLayout *hboxLayout1;
    QPushButton *firstFrame;
    QPushButton *prevFrame;
    QLineEdit *frameEdit;
    QPushButton *nextFrame;
    QPushButton *lastFrame;

    void setupUi(QWidget *mainWidget)
    {
        if (mainWidget->objectName().isEmpty())
            mainWidget->setObjectName(QStringLiteral("mainWidget"));
        mainWidget->resize(800, 600);
        gridLayout = new QGridLayout(mainWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        topLayout = new QHBoxLayout();
        topLayout->setObjectName(QStringLiteral("topLayout"));
        videoPath = new QLineEdit(mainWidget);
        videoPath->setObjectName(QStringLiteral("videoPath"));
        videoPath->setReadOnly(true);

        topLayout->addWidget(videoPath);

        loadVideoButton = new QPushButton(mainWidget);
        loadVideoButton->setObjectName(QStringLiteral("loadVideoButton"));

        topLayout->addWidget(loadVideoButton);


        gridLayout->addLayout(topLayout, 0, 0, 1, 2);

        settingsLayout = new QVBoxLayout();
        settingsLayout->setObjectName(QStringLiteral("settingsLayout"));
        ballDiametersLabel = new QLabel(mainWidget);
        ballDiametersLabel->setObjectName(QStringLiteral("ballDiametersLabel"));

        settingsLayout->addWidget(ballDiametersLabel);

        ballDiameter = new QLineEdit(mainWidget);
        ballDiameter->setObjectName(QStringLiteral("ballDiameter"));

        settingsLayout->addWidget(ballDiameter);

        goalHeightLabel = new QLabel(mainWidget);
        goalHeightLabel->setObjectName(QStringLiteral("goalHeightLabel"));

        settingsLayout->addWidget(goalHeightLabel);

        goalHeight = new QLineEdit(mainWidget);
        goalHeight->setObjectName(QStringLiteral("goalHeight"));

        settingsLayout->addWidget(goalHeight);

        diameterLabel = new QLabel(mainWidget);
        diameterLabel->setObjectName(QStringLiteral("diameterLabel"));

        settingsLayout->addWidget(diameterLabel);

        diameter = new QSlider(mainWidget);
        diameter->setObjectName(QStringLiteral("diameter"));
        diameter->setOrientation(Qt::Horizontal);
        diameter->setMinimum(5);
        diameter->setMaximum(200);
        diameter->setValue(50);

        settingsLayout->addWidget(diameter);

        houghLabel = new QLabel(mainWidget);
        houghLabel->setObjectName(QStringLiteral("houghLabel"));

        settingsLayout->addWidget(houghLabel);

        hough = new QLabel(mainWidget);
        hough->setObjectName(QStringLiteral("hough"));

        settingsLayout->addWidget(hough);

        houghThresholdLabel = new QLabel(mainWidget);
        houghThresholdLabel->setObjectName(QStringLiteral("houghThresholdLabel"));

        settingsLayout->addWidget(houghThresholdLabel);

        houghThreshold = new QSlider(mainWidget);
        houghThreshold->setObjectName(QStringLiteral("houghThreshold"));
        houghThreshold->setOrientation(Qt::Horizontal);
        houghThreshold->setMinimum(5);
        houghThreshold->setMaximum(200);
        houghThreshold->setValue(50);

        settingsLayout->addWidget(houghThreshold);

        templateLabel = new QLabel(mainWidget);
        templateLabel->setObjectName(QStringLiteral("templateLabel"));

        settingsLayout->addWidget(templateLabel);

        templateImage = new QLabel(mainWidget);
        templateImage->setObjectName(QStringLiteral("templateImage"));

        settingsLayout->addWidget(templateImage);

        calculateSpeed = new QPushButton(mainWidget);
        calculateSpeed->setObjectName(QStringLiteral("calculateSpeed"));

        settingsLayout->addWidget(calculateSpeed);

        matchTemplate = new QPushButton(mainWidget);
        matchTemplate->setObjectName(QStringLiteral("matchTemplate"));

        settingsLayout->addWidget(matchTemplate);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        matchAllBalls = new QPushButton(mainWidget);
        matchAllBalls->setObjectName(QStringLiteral("matchAllBalls"));

        hboxLayout->addWidget(matchAllBalls);

        frameCount = new QLineEdit(mainWidget);
        frameCount->setObjectName(QStringLiteral("frameCount"));

        hboxLayout->addWidget(frameCount);


        settingsLayout->addLayout(hboxLayout);


        gridLayout->addLayout(settingsLayout, 1, 0, 1, 1);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        frame = new VideoFrame(mainWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(800, 0));
        frame->setAlignment(Qt::AlignTop);

        vboxLayout->addWidget(frame);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        firstFrame = new QPushButton(mainWidget);
        firstFrame->setObjectName(QStringLiteral("firstFrame"));

        hboxLayout1->addWidget(firstFrame);

        prevFrame = new QPushButton(mainWidget);
        prevFrame->setObjectName(QStringLiteral("prevFrame"));

        hboxLayout1->addWidget(prevFrame);

        frameEdit = new QLineEdit(mainWidget);
        frameEdit->setObjectName(QStringLiteral("frameEdit"));

        hboxLayout1->addWidget(frameEdit);

        nextFrame = new QPushButton(mainWidget);
        nextFrame->setObjectName(QStringLiteral("nextFrame"));

        hboxLayout1->addWidget(nextFrame);

        lastFrame = new QPushButton(mainWidget);
        lastFrame->setObjectName(QStringLiteral("lastFrame"));

        hboxLayout1->addWidget(lastFrame);


        vboxLayout->addLayout(hboxLayout1);


        gridLayout->addLayout(vboxLayout, 1, 1, 1, 1);


        retranslateUi(mainWidget);

        QMetaObject::connectSlotsByName(mainWidget);
    } // setupUi

    void retranslateUi(QWidget *mainWidget)
    {
        mainWidget->setWindowTitle(QApplication::translate("BallspeedUI", "Ballspeed", 0));
        loadVideoButton->setText(QApplication::translate("BallspeedUI", "Load ...", 0));
        ballDiametersLabel->setText(QApplication::translate("BallspeedUI", "Ball diameter", 0));
        goalHeightLabel->setText(QApplication::translate("BallspeedUI", "Goal height", 0));
        diameterLabel->setText(QApplication::translate("BallspeedUI", "Diameter", 0));
        houghLabel->setText(QApplication::translate("BallspeedUI", "Hough image", 0));
        houghThresholdLabel->setText(QApplication::translate("BallspeedUI", "Hough threshold", 0));
        templateLabel->setText(QApplication::translate("BallspeedUI", "Template", 0));
        calculateSpeed->setText(QApplication::translate("BallspeedUI", "Calculate speed", 0));
        matchTemplate->setText(QApplication::translate("BallspeedUI", "Match template", 0));
        matchAllBalls->setText(QApplication::translate("BallspeedUI", "Match # of frames", 0));
        frameCount->setText(QApplication::translate("BallspeedUI", "25", 0));
        firstFrame->setText(QApplication::translate("BallspeedUI", "<<", 0));
        prevFrame->setText(QApplication::translate("BallspeedUI", "<", 0));
        nextFrame->setText(QApplication::translate("BallspeedUI", ">", 0));
        lastFrame->setText(QApplication::translate("BallspeedUI", ">>", 0));
    } // retranslateUi

};

namespace Ui {
    class BallspeedUI: public Ui_BallspeedUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_H
