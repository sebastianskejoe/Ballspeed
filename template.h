#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <opencv2/opencv.hpp>
#include <QPoint>

#include "subimage.h"

struct MatchResult {
    QPoint pt;
    double value;
    bool found;
};

class TemplateMatcher {
    public:
        TemplateMatcher(Subimage tmpl);
        TemplateMatcher() {}

        void setTemplate(Subimage tmpl);
        MatchResult match(Subimage img);

    private:
        Subimage mTmpl;
};

#endif
