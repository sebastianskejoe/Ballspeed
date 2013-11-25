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

void Logger::addMessage(std::string msg) {
    mFrames[mCur].messages.append(msg);
}

void Logger::printTotalTime() {
    int time = 0, i;
    for (i = 0; i < mFrames.size() ; i++) {
        time += mFrames[i].matchTime;
    }
    std::cout << "Total match time: " << time << std::endl;
}

void Logger::printFrame(int frame) {
    int i;
    std::cout << "#" << frame << " "
              << "Iterations: " << mFrames[frame].boundaries.size()
              << ", Time match: " << mFrames[frame].matchTime
              << ", End size: " << mFrames[frame].boundaries.last().width() << "x" << mFrames[frame].boundaries.last().height()
              << std::endl;
    for (i = 0; i < mFrames[frame].messages.size(); i++) {
        std::cout << "#" << frame << "## " << mFrames[frame].messages[i] << std::endl;
    }
}
