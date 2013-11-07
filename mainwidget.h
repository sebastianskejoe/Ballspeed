#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QPaintEvent>
#include <QMouseEvent>

#include "template.h"
#include "hough.h"

namespace Ui {
    class BallspeedUI;
}

class MainWidget : public QWidget
{
    Q_OBJECT

friend class VideoFrame;

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void loadPath(std::string);

public slots:
    void on_loadVideoButton_clicked();
    void on_frame_clicked(QMouseEvent *);
    void on_diameter_valueChanged(int);
    void on_houghThreshold_valueChanged(int);
    void on_firstFrame_clicked();
    void on_lastFrame_clicked();
    void on_nextFrame_clicked();
    void on_prevFrame_clicked();
    void on_matchTemplate_clicked();
    void on_matchAllBalls_clicked();
    void on_calculateSpeed_clicked();

protected:
    Ui::BallspeedUI *ui;
    cv::VideoCapture mVidcap;
    int mCur, mFrameCount;
    int mDiameter;

    QVector<MatchResult> mBallMatches;
    QVector< QVector<MatchResult> > mCalibrations;
    QVector<HoughResult> mHoughResults;

    HoughDetector *mHough;
    TemplateMatcher *mMatcher;
    TemplateMatcher *mCalibrationMatcher;

    Subimage mTmpl;
    QVector<Subimage> mCalibrationTmpl;

    Subimage getSubimage(QPoint pos);
    Subimage getSubimage(QPoint pos, int diameter);
    Subimage getSubimage(QPoint pos, int frame, int diameter, bool *filled = 0, bool adjust = false);

    MatchResult matchBallFrame(int);
    MatchResult matchCalibration(int,int);

    QPoint getCalibratedPoint(int);
    QPoint getCalibration(int);
};

#endif
