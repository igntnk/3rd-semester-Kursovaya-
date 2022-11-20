#ifndef CIRCLELABEL_H
#define CIRCLELABEL_H

#include <QLabel>
#include <QPainter>

class CircleLabel: public QLabel
{
public:
    CircleLabel(QWidget* parent=0);
    int getCircleRad();
    int getMaxCircleArea();

public slots:
    void setCircleRad(int);

private:
    void paintEvent(QPaintEvent* q);
    void doPainting(QPainter *qp);
    int circleRad = 10;
    const int maxCircleArea = 110;
};

#endif // CIRCLELABEL_H
