#ifndef SUBIMAGE_H
#define SUBIMAGE_H

#include <opencv2/opencv.hpp>
#include <QPoint>
#include <QImage>

class Subimage {
public:
    Subimage();
    Subimage(cv::Mat, QPoint);
    int width() { return mMat.cols; }
    int height() { return mMat.rows; }
    QPoint offset() { return mOffset; }
    cv::Mat gray();
    const cv::Mat mat();
    QImage toImage();
    void printImage();

    bool exists;

private:
    cv::Mat mMat;
    cv::Mat mGray;
    QPoint mOffset;
    QImage mImg;

    void createImage();
    void createGray();
};

#endif
