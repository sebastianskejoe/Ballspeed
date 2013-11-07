#ifndef HOUGH_H
#define HOUGH_H

#include <opencv2/opencv.hpp>
#include <QPoint>

#include "subimage.h"

struct HoughResult {
    QPoint pt;
    double radius;
    bool found;
};

class HoughDetector {
    public:
        HoughDetector();

        void setThreshold(int);
        HoughResult detect(Subimage subimage);

    private:
        int mThreshold;
};

#endif
