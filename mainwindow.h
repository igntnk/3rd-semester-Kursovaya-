#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "circlelabel.h"
#include <QPixmap>
#include <QWidget>
#include <QDebug>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QResizeEvent>

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

    QImage photo;

    QSlider* slider;

    QHBoxLayout* hbox;
    QVBoxLayout* vbox;

    bool isGoal(QMouseEvent* event, QRect refer);

public slots:

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // MAINWINDOW_H
