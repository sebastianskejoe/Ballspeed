#include "mainwidget.h"
#include "ui_ui.h"

#include <QString>
#include <QFileDialog>
#include <QErrorMessage>
#include <QPixmap>
#include <QVector>
#include <QRgb>
#include <cmath>
#include <cstdio>

#define WITHIN(a,b,c) b-c < a && a < b+c

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BallspeedUI),
    mHough(new HoughDetector),
    mMatcher(new TemplateMatcher),
    mCalibrationMatcher(new TemplateMatcher)
{
    ui->setupUi(this);
    ui->frame->setMainWidget(this);
    mDiameter = ui->diameter->value();
    mHough->setThreshold(ui->houghThreshold->value());

    ui->hough->setFixedSize(100, 100);
}

MainWidget::~MainWidget()
{
    delete ui;
}

/*
 * Slots
 */
/**
 * Load video
 */
void MainWidget::on_loadVideoButton_clicked() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), QString("Movies (*.avi *.MOV *.mp4)"));
    if (path == "") {
        return;
    }
    ui->videoPath->setText(path);
    loadPath(path.toStdString());
}

/**
 * Change diameter of hough search area and initial template search area
 */
void MainWidget::on_diameter_valueChanged(int diam) {
    mDiameter = diam;
}

/**
 * Change hough threshold value
 */
void MainWidget::on_houghThreshold_valueChanged(int val) {
    mHough->setThreshold(val);
}

/**
 * Handle clicks on the frame
 */
void MainWidget::on_frame_clicked(QMouseEvent *me) {
    QPoint pt;
    Subimage sub;
    HoughResult res;
    int i;

    // Left click = find template
    if (me->button() == Qt::LeftButton) {
        // Get sub image
        pt = ui->frame->trueCoords(me->pos());
        sub = getSubimage(pt);
        if (!sub.exists) {
            return;
        }

        // Show hough search area
        ui->hough->setPixmap(QPixmap::fromImage(sub.toImage()));

        // Detect
        res = mHough->detect(sub);
        if (res.found) {
            mHoughResults.replace(mCur, res);

            mTmpl = getSubimage(res.pt, (int)res.radius*2);
            ui->templateImage->setPixmap(QPixmap::fromImage(mTmpl.toImage()));
            mMatcher->setTemplate(mTmpl);
        }
    // Right click = set template for calibration
    } else if (me->button() == Qt::RightButton && mCalibrationTmpl.size() < 4) {
        pt = ui->frame->trueCoords(me->pos());
        i = mCalibrationTmpl.size();
        mCalibrationTmpl.append(getSubimage(pt-QPoint(5,5), 10));

        // Fill mCalibrations with empty values so we can .replace() later
        mCalibrations.append(QVector<MatchResult>());
        mCalibrations[i].fill({QPoint(), 0.0, false}, mFrameCount);
    }
}

/**
 * Do ball matching in current frame
 */
void MainWidget::on_matchTemplate_clicked() {
    MatchResult res, cal;
    QPoint pt;
 
    // Match ball
    res = matchBallFrame(mCur);
    mBallMatches.replace(mCur, res);

    // Print result
    if (mCur <= 0) {
        return;
    }

    pt = getCalibratedPoint(mCur);
    std::cout << "#" << mCur << ": match(" << res.pt.x() << "," << res.pt.y() << ") calibrated(" << pt.x() << ", " << pt.y() << ") value = " << res.value << std::endl;
}

/**
 * Do ball matching in all frames
 */
void MainWidget::on_matchAllBalls_clicked() {
    int i, tmpl;
    MatchResult res, cal;
    QPoint pt;

    for (i = 0; i < ui->frameCount->text().toInt(); i++) {
        res = matchBallFrame(i);
        mBallMatches.replace(i, res);

        // Calibrate
        for (tmpl = 0; tmpl < mCalibrationTmpl.size(); tmpl++) {
            cal = matchCalibration(tmpl,i);
            mCalibrations[tmpl].replace(i, cal);
        }

        // Print results
        if (i <= 0) {
            continue;
        }

        pt = getCalibratedPoint(i);
        std::cout << "#" << i << ": match(" << res.pt.x() << "," << res.pt.y() << ") calibrated(" << pt.x() << ", " << pt.y() << ") value = " << res.value << std::endl;
    }
}

/**
 * Go to first frame
 */
void MainWidget::on_firstFrame_clicked() {
    mCur = 0;
    ui->frameEdit->setText(QString::number(mCur));
}

/**
 * Go to last frame
 */
void MainWidget::on_lastFrame_clicked() {
    mCur = mFrameCount-1;
    ui->frameEdit->setText(QString::number(mCur));
}

/**
 * Go to next frame
 */
void MainWidget::on_nextFrame_clicked() {
    mCur++;
    ui->frameEdit->setText(QString::number(mCur));
}

/**
 * Go to previous frame
 */
void MainWidget::on_prevFrame_clicked() {
    mCur--;
    ui->frameEdit->setText(QString::number(mCur));
}

/**
 * Calculates and prints the ball speed between each matched frame
 */
void MainWidget::on_calculateSpeed_clicked() {
    float mpp, speed, speedX, speedY;
    float diameter, goalheight;
    int i, distanceX, distanceY;
    bool convertDia, convertGoal;
    MatchResult first, prevcal, curcal, prevmr, curmr;
    QPoint prev, cur;

    // Check if diameter or goal height is set
    diameter = ui->ballDiameter->text().toFloat(&convertDia);
    goalheight = ui->goalHeight->text().toFloat(&convertGoal);
    if (!convertDia && !convertGoal) {
        std::cerr << "Diameter  not set!" << std::endl;
        return;
    }

    // Get meters per pixel
    // Try to use goal first.
    if (convertGoal && mCalibrationTmpl.size() == 4) {
        // Find each goal post
        QPoint pair1, pair2;
        pair1.setX(mCalibrationTmpl[0].offset().x());
        // Check if #2 belongs with #1
        if (WITHIN(mCalibrationTmpl[1].offset().x(), pair1.x(), 25)) {
            pair1.setY(1);
            pair2.setX(2);
            pair2.setY(3);
        } else { // #2 is not with #1, 
            pair2.setX(1);
            if (WITHIN(mCalibrationTmpl[2].offset().x(), pair1.x(), 25)) { // check if #3 is with #1
                pair1.setY(2);
                pair2.setY(3);
            } else { // #4 and #1 is together and #2 and #3 is together
                pair1.setY(3);
                pair2.setY(2);
            }
        }

        // Find difference in goal post heights
        float diff, diff1, diff2;
        diff1 = (float)mCalibrationTmpl[0].offset().y()-(float)mCalibrationTmpl[pair1.y()].offset().y();
        diff2 = (float)mCalibrationTmpl[pair2.x()].offset().y()-(float)mCalibrationTmpl[pair2.y()].offset().y();
        diff = (fabs(diff1)+fabs(diff2))/2; // XXX: Ball is placed in the middle of the goal

        // Calculate goal height in pixels
        mpp = ((float)goalheight)/diff;
        std::cout << "Ball calc: " << ((float)diameter)/(float)mTmpl.width() << std::endl;
        std::cout << "Goal height (px): " << diff << std::endl;
    } else { // Use ball diameter instead
        mpp = ((float)diameter)/(float)mTmpl.width();
    } 
    std::cout << "Meters per pixel: " << mpp << std::endl << "Template width: " << (float)mTmpl.width() << std::endl;

    // Calculate speeds
    for (i = 1; i < mFrameCount; i++) {
        prev = getCalibratedPoint(i-1);
        cur = getCalibratedPoint(i);

        // If we don't have to results, continue
        if (prev == QPoint(-1, -1) || cur == QPoint(-1,-1)) {
            continue;
        }

        // Calculate horizontal, vertical and ... speeds
        // Assume 30 fps
        distanceX = cur.x()-prev.x();
        distanceY = cur.y()-prev.y();

        speedX = mpp*(float)distanceX*15;
        speedY = mpp*(float)distanceY*15;
        speed = sqrt(speedX*speedX+speedY*speedY);

        // Print results
        printf("#%02d-#%02d:\t%3f\t| %3f\t| %3f\n", i-1, i, speedX, speedY, speed);
    }
}

/*
 * Helpers
 */
Subimage MainWidget::getSubimage(QPoint pos) {
    return getSubimage(pos, mDiameter);
}

Subimage MainWidget::getSubimage(QPoint pos, int diameter) {
    return getSubimage(pos, mCur, diameter);
}

/**
 * Return a rectangular subimage of a given frame.
 * If adjust is true, the function will automatically adjust the boundaries of the subimage 
 * to boundaries of the frame. If adjust is false and the boundaries exceed the boundaries of the
 * frame, an empty subimage will be returned.
 * @param pos Center point of subimage
 * @param frame Frame number
 * @param diameter Intented width/height of subimage
 * @param filled Filled is set to true if the subimage fills the subimage
 * @param adjust Indicates whether the subimage boundaries should be adjusted to the frame boundaries
 */
Subimage MainWidget::getSubimage(QPoint pos, int frame, int diameter, bool *filled, bool adjust) {
    int adjs = 0; // number of adjustments
    cv::Mat mat, omat;
    cv::Rect rect;

    // Return empty image if there's no video opened
    if (!mVidcap.isOpened()) {
        return Subimage();
    }

    // Read frame
    mVidcap.set(CV_CAP_PROP_POS_FRAMES, frame);
    mVidcap.read(mat);

    // Translate pos to upper left corner
    pos -= QPoint(diameter/2, diameter/2);
    rect = cv::Rect(pos.x(), pos.y(), diameter, diameter);

    // Check if subrect is within bounds
    if (pos.x() < 0 || pos.x()+diameter > mat.cols ||
        pos.y() < 0 || pos.y()+diameter > mat.rows) {
        if (!adjust && filled != 0) {
            *filled = true;
            return Subimage();
        } else {
            // Adjust sub image
            if (pos.x() < 0) { // Left bound
                rect.x = 0;
                adjs++;
            }
            if (pos.y() < 0) { // Upper bound
                rect.y = 0;
                adjs++;
            }
            if (rect.x+diameter > mat.cols) { // Right bound
                rect.width = mat.cols-rect.x;
                adjs++;
            }
            if (rect.y+diameter > mat.rows) { // Lower bound
                rect.height = mat.rows-rect.y;
                adjs++;
            }

            if (adjs == 4 && filled != 0) {
                *filled = true;
            }
        }
    }

    pos = QPoint(rect.tl().x, rect.tl().y);

    // Get subimage
    mat(rect).copyTo(omat);
    return Subimage(omat, pos);
}

/**
 * Matches the ball template against frame #i
 */
MatchResult MainWidget::matchBallFrame(int i) {
    Subimage sub;
    MatchResult res = {QPoint(), 0, false}, mr;
    HoughResult hr;
    int diam;
    bool filled = false;

    // Find where to search
    for (diam = mDiameter; !filled; diam *= 2) {
        hr = mHoughResults.at(i);

        // Try to get MatchResult from previous frame
        if (i >= 1) {
            mr = mBallMatches.at(i-1);
        }

        // If we have a MatchResult from previous frame, use that to set subimage area
        if (i-1 >= 0 && mr.found) {
            sub = getSubimage(mr.pt, i, diam, &filled, true);
        } else if (hr.found) { // Else use hough results if possible
            sub = getSubimage(hr.pt, i, diam, &filled, true);
        } else { // Otherwise we have no good guess - break XXX
            break;
        }

        // Match it
        ui->hough->setPixmap(QPixmap::fromImage(sub.toImage()));
        res = mMatcher->match(sub);

        // If value is less than 0.80 it probably isn't a proper match, try in a bigger area
        if (res.value < 0.80) {
            continue;
        }

        break;
    }

    return res;
}

/**
 * Matches calibration template #tmpl against frame #i
 */
MatchResult MainWidget::matchCalibration(int tmpl, int i) {
    MatchResult res, prev;
    QPoint pt;
    Subimage sub;
    bool filled = false;

    if (!mCalibrationTmpl.at(tmpl).exists) {
        return res;
    }

    // Find search area
    if (i > 0) {
        prev = mCalibrations.at(tmpl).at(i-1);
    }

    if (i > 0 && prev.found) {
        pt = prev.pt;
    } else {
        pt = mCalibrationTmpl[tmpl].offset();
    }
   
    sub = getSubimage(pt, i, mDiameter, &filled);

    if (filled) {
        return res;
    }

    mCalibrationMatcher->setTemplate(mCalibrationTmpl[tmpl]);
    res = mCalibrationMatcher->match(sub);

    return res;
}

/**
 * Load video
 * XXX: Gives wrong frame count with some videos and needs to check framerate
 */
void MainWidget::loadPath(std::string path) {
    // Try to open path
    mVidcap.open(path);
    if (!mVidcap.isOpened()) {
        QErrorMessage *errDialog = new QErrorMessage(this);
        errDialog->showMessage("Could not open file");
        return;
    }

    // Get info
    mFrameCount = mVidcap.get(CV_CAP_PROP_FRAME_COUNT);
    mCur = 0;

    // Fill vectors
    HoughResult dummy = {QPoint(), 0, false};
    MatchResult match = {QPoint(), 0.0, false};
    mHoughResults.fill(dummy, mFrameCount);
    mBallMatches.fill(match, mFrameCount);
}


/**
 * Returns the calibrated point for the given frame
 * XXX: Not used right now
 */
QPoint MainWidget::getCalibratedPoint(int frame) {
    MatchResult mr, cal, first;

    // Get matchresults
    mr = mBallMatches.at(frame);
/*    first = mCalibrations.at(0);
    cal = mCalibrations.at(frame);

        printf("n: %d\n", cals.size()
    if (!first.found || !cal.found) {
        if (mr.found) {
            return mr.pt;
        }
        return QPoint(-1,-1);
    }

    // Calibrate
    return mr.pt - (cal.pt-first.pt);*/
    return mr.pt;
}

/**
 * Match all calibration templates and return the translation needed to calibrate
 * XXX: Calculate translation
 */
QPoint MainWidget::getCalibration(int frame) {
    MatchResult cal;
    QPoint pt;
    int i;

    // Match calibration templates
    for (i = 0; i < mCalibrationTmpl.size(); i++) {
        cal = matchCalibration(i,frame);
        mCalibrations[i].replace(frame, cal);
    }

    return pt;
}
