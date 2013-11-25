#include "videoframe.h"

#include <QPainter>
#include <opencv2/opencv.hpp>

VideoFrame::VideoFrame(QWidget *parent) :
    QLabel(parent)
{
}

VideoFrame::~VideoFrame() {
}

void VideoFrame::paintEvent(QPaintEvent *pe) {
    // Draw image
    QLabel::paintEvent(pe);

    // Draw text
    QPainter painter(this);

    drawFrame();

    drawHough(&painter);

    drawBalls(&painter);

    drawCalibration(&painter);
}

void VideoFrame::setMainWidget(MainWidget *mw) {
    mParent = mw;
}

void VideoFrame::drawFrame() {
    if (!mParent->mVidcap.isOpened()) {
        return;
    }

    // Get frame and create QImage
    cv::Mat mat, rgb;
    mParent->mVidcap.set(CV_CAP_PROP_POS_FRAMES, mParent->mCur);
    if (!mParent->mVidcap.read(mat)) {
        return;
    }
    cv::cvtColor(mat, rgb, CV_BGR2RGB);
    QImage img(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);

    // Draw
    setPixmap(QPixmap::fromImage(img).scaled(width(), height(), Qt::KeepAspectRatio));

    mScaleFactor = (double)pixmap()->width()/(double)img.width();
    mSpacing = QPoint((geometry().width()-pixmap()->width())/2, 0);
}

void VideoFrame::drawHough(QPainter *painter) {
    if (mParent->mCur > mParent->mHoughResults.size() || mParent->mHoughResults.size() == 0) {
        return;
    }

    HoughResult result = mParent->mHoughResults.at(mParent->mCur);
    if (!result.found) {
        return;
    }

    painter->drawEllipse(result.pt*mScaleFactor+mSpacing, (int)(result.radius*mScaleFactor), (int)(result.radius*mScaleFactor));
}

void VideoFrame::drawBalls(QPainter *painter) {
    int i, alpha;
    MatchResult res;

    // Setup drawing
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(Qt::NoPen);

    for (i = mParent->mCur; i < mParent->mCur+5; i++) {
        // Check vector access
        if (i < 0) {
            continue;
        }
        if (i >= mParent->mBallMatches.size() || mParent->mBallMatches.size() == 0) {
            return;
        }

        // Draw result
        res = mParent->mBallMatches.at(i);
        if (!res.found) {
            continue;
        }

        alpha = (int)(255.0*(float)(i-mParent->mCur)/(float)(5));
       
        brush.setColor(QColor(alpha,255,alpha, 255-alpha));
        painter->setBrush(brush); 
        painter->drawEllipse(res.pt*mScaleFactor+mSpacing, 3, 3);
    }
}

void VideoFrame::drawCalibration(QPainter *painter) {
    MatchResult res;
    QVector<MatchResult> cals;
    QPoint pt;
    Subimage img;
    int i;

    if (mParent->mCur == 0) { // On first frame draw selected points
        for (i = 0; i < mParent->mCalibrationTmpl.size(); i++) {
            img = mParent->mCalibrationTmpl.at(i);
            pt = QPoint(img.offset().x()+img.width()/2, img.offset().y()+img.width()/2);
            cals.append(MatchResult{pt, 255, 1});
        }
    } else if (!mParent->mCalibrations.isEmpty() && mParent->mCalibrations.first().size() >= mParent->mCur+1) {
        for (i = 0; i < mParent->mCalibrations.size(); i++) {
            cals.append(mParent->mCalibrations[i][mParent->mCur]);
        }
    } else {
        return;
    }

    for (i = 0; i < cals.size(); i++) {
        res = cals.at(i);
        if (!res.found) {
            return;
        }

        // Setup drawing
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(255,0,0, 100));

        painter->setPen(Qt::NoPen);
        painter->setBrush(brush);

        QPoint pt = res.pt*mScaleFactor+mSpacing;

        painter->drawRect(pt.x(), pt.y(), 10, 10);
    }
}

void VideoFrame::mousePressEvent(QMouseEvent *me) {
    emit clicked(me);
}

QPoint VideoFrame::trueCoords(QPoint pos) {
    if (!pixmap()) {
        return QPoint();
    }

    std::cout << pos.x() << "," << pos.y() << "," << mScaleFactor << std::endl;
    return pos/mScaleFactor-mSpacing;
}
