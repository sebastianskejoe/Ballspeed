#include "hough.h"

HoughDetector::HoughDetector() {
}

void HoughDetector::setThreshold(int t) {
    mThreshold = t;
}

HoughResult HoughDetector::detect(Subimage subimage) {
    // Run hough transform
    HoughResult result = {QPoint(), 0, false};
    cv::vector<cv::Vec3f> circles;
    cv::HoughCircles(subimage.gray(), circles, CV_HOUGH_GRADIENT, 2, subimage.height()/4, 200, mThreshold);
    cv::imwrite("gray.png", subimage.gray());
    if (circles.size() > 0) {
        result.pt.setX((int)circles[0][0]);
        result.pt.setY((int)circles[0][1]);
        result.pt += subimage.offset();
        result.radius = circles[0][2];
        result.found = true;
        std::cout << "At (" << result.pt.x() << "," << result.pt.y() << ")" << std::endl;
    }
    return result;
}
