#include "logger.h"
#include <iostream>
#include <QSize>

Logger::Logger(int frames) {
    mFrames.fill(FrameStats{}, frames);
}

void Logger::setCurrentFrame(int frame) {
    mCur = frame;
    // Empty stats for this frames
    mFrames[mCur] = FrameStats{};
}

void Logger::startMatching() {
    mFrames[mCur].matchTimer.start();
}

void Logger::stopMatching() {
    mFrames[mCur].matchTime = mFrames[mCur].matchTimer.elapsed();
}

void Logger::addIteration(QPoint offset, int width, int height) {
    mFrames[mCur].boundaries.append(QRect(offset, QSize(width, height)));
}

void Logger::setHough(bool hough) {
    mFrames[mCur].hough = hough;
}

void Logger::startHough() {
    mFrames[mCur].houghTimer.start();
}

void Logger::stopHough() {
    mFrames[mCur].houghTime = mFrames[mCur].houghTimer.elapsed();
}

void Logger::printFrame(int frame) {
    std::cout << "Iterations: " << mFrames[frame].boundaries.size()
              << ", Time match: " << mFrames[frame].matchTime
              << ", End size: " << mFrames[frame].boundaries.last().width()
              << std::endl;
}
