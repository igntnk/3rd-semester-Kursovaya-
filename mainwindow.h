#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "circlelabel.h"
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QDebug>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class PixWork: public QWidget
{
public:
    PixWork(QWidget* parent =0);

private:
    CircleLabel* circle;

    QString t1;

    QPushButton* pLabel1;
    QLabel* tLabel;
    QLabel* circleRadLabel;

    QImage photo;

    QSlider* slider;

    QHBoxLayout* hbox;
    QVBoxLayout* vbox;

    void mousePressEvent(QMouseEvent* event);
};

#endif // MAINWINDOW_H
