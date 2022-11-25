#ifndef CIRCLELABEL_H
#define CIRCLELABEL_H

#include <QLabel>
#include <QPainter>
#include <QImage>

class CircleLabel: public QLabel
{
public:
    CircleLabel(QWidget* parent=0);
    int getCircleRad();
    int getMaxCircleArea();
    void setImage(QImage i);
public slots:
    void setCircleRad(int);

private:
    void paintEvent(QPaintEvent* q);
    void doPainting(QPainter *qp);
    QImage image;
    int circleRad = 10;
    const int maxCircleArea = 110;
};

#endif // CIRCLELABEL_H
