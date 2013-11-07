#include "subimage.h"

Subimage::Subimage() {
    exists = false;
}

Subimage::Subimage(cv::Mat mat, QPoint offset) 
{
    cv::cvtColor(mat, mMat, CV_BGR2RGB);
    mOffset = offset;
    exists = true;

    createImage();
    createGray();
}

cv::Mat Subimage::gray() {
    return mGray;
}

const cv::Mat Subimage::mat() {
    return mMat;
}

QImage Subimage::toImage() {
    return mImg;
}

void Subimage::createImage() {
    mImg = QImage((uchar *)mMat.data, mMat.cols, mMat.rows, mMat.step, QImage::Format_RGB888);
}

void Subimage::createGray() {
    cv::cvtColor(mMat, mGray, CV_BGR2GRAY);
}

void Subimage::printImage() {
}
