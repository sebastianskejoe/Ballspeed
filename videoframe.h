#ifndef VIDEOFRAME_H
#define VIDEOFRAME_H

#include <QLabel>
#include <QPaintEvent>
#include <opencv2/opencv.hpp>
#include <QMouseEvent>
#include <QPoint>

#include "mainwidget.h"

class VideoFrame : public QLabel {
    Q_OBJECT
public:
    VideoFrame(QWidget *parent);
    ~VideoFrame();
    void setMainWidget(MainWidget *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    QPoint trueCoords(QPoint);

signals:
    void clicked(QMouseEvent *);

private:
    MainWidget *mParent;
    double mScaleFactor;
    QPoint mSpacing;

    void drawFrame();
    void drawHough(QPainter *);
    void drawBalls(QPainter *);
    void drawCalibration(QPainter *);
};

#endif
