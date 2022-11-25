#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "circlelabel.h"
#include <QPixmap>
#include <QWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QStackedLayout>

class PixWork: public QWidget
{
    Q_OBJECT;

public:
    PixWork(QWidget* parent =0);

private:
    int maxSize;

    CircleLabel* circle;
    CircleLabel* sniper;

    QMessageBox* message;

    QString t1;

    QLabel* pLabel1;
    QLabel* tLabel;
    QLabel* circleRadLabel;
    QLabel* upperPhoto;

    QImage photo;
    QImage takenPart;

    QSlider* slider;

    QHBoxLayout* hbox;
    QVBoxLayout* vbox;
    QStackedLayout* sbox;

    bool isGoal(QMouseEvent* event, QRect refer);

public slots:

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // MAINWINDOW_H
