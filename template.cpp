#include "template.h"

#include <opencv2/opencv.hpp>

TemplateMatcher::TemplateMatcher(Subimage tmpl) {
    mTmpl = tmpl;
}

void TemplateMatcher::setTemplate(Subimage tmpl) {
    mTmpl = tmpl;
}

MatchResult TemplateMatcher::match(Subimage img) {
    MatchResult mr;
    cv::Mat res;
    cv::Point *pt = new cv::Point;
    
    res.create(img.height()-mTmpl.height()+1, img.width()-mTmpl.width()+1, CV_32FC1);

    cv::matchTemplate(img.mat(), mTmpl.mat(), res, CV_TM_CCOEFF_NORMED);
    cv::minMaxLoc(res, 0, &(mr.value), 0, pt);

    mr.pt = QPoint(pt->x, pt->y) + img.offset();
    mr.found = true;
    return mr;
}
