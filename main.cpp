#include "template.h"

#include <QApplication>
#include <QtGui>

#include "ui_ui.h"
#include "mainwidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWidget *mw = new MainWidget;
/*    QGridLayout *layout = new QGridLayout();

    // Top
    QWidget top;
    QHBoxLayout *toplayout = new QHBoxLayout();
    QLineEdit *path = new QLineEdit();
    path->setReadOnly(true);
    QPushButton *load = new QPushButton("Load");     
    toplayout->addWidget(path);
    toplayout->addWidget(load);

    // Sliders
    QWidget sliders;
    QVBoxLayout *sliderlayout = new QVBoxLayout();
    QLabel *thresholdLabel = new QLabel("Threshold:");
    QSlider *thresholdSlider = new QSlider();
    thresholdSlider->setOrientation(Qt::Horizontal);
    sliderlayout->addWidget(thresholdLabel);
    sliderlayout->addWidget(thresholdSlider);

    // Image view
    QFrame *imgView = new QFrame();

    TemplateMatcher tm = TemplateMatcher();

    layout->addLayout(toplayout, 0,0, 1, 2);
    layout->addLayout(sliderlayout, 1, 0);
    layout->addWidget(imgView, 1,1);
    window.setLayout(layout);*/
    mw->show();

    return app.exec();
}
