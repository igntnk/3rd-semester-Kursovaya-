#ifndef CIRCLELABEL_H
#define CIRCLELABEL_H

#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>

class CircleLabel: public QLabel
{
public:
    CircleLabel(QWidget* parent=0);
    int getCircleRad();

public slots:
    void setCircleRad(int);

private:
    void paintEvent(QPaintEvent* q);
    void doPainting(QPainter *qp);
    int circleRad = 10;
    int maxCircleArea = 110;
};

#endif // CIRCLELABEL_H
