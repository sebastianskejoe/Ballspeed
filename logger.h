#ifndef LOGGER_H
#define LOGGER_H

#include <QRect>
#include <QVector>
#include <QTime>

class Logger {
public:
    Logger(int frames);
    void setCurrentFrame(int);
    void startMatching();
    void stopMatching();
    void addIteration(QPoint, int, int);
    void setHough(bool);
    void startHough();
    void stopHough();
    void addMessage(std::string);
    void printTotalTime();
    void printFrame(int);

private:
    struct FrameStats {
        // Boundaries for matching
        QVector<QRect> boundaries;
        // Match timing
        QTime matchTimer;
        int matchTime;
        // Did we do hough transformation?
        bool hough;
        // Hough timing
        QTime houghTimer;
        int houghTime;
        QVector<std::string> messages;
    };

    QVector<FrameStats> mFrames;
    int mCur;
};

#endif
