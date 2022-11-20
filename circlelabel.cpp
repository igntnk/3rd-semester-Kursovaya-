#include "circlelabel.h"
#include <cmath>

CircleLabel::CircleLabel(QWidget* parent):
    QLabel(parent)
{
    this->setMinimumSize(maxCircleArea, maxCircleArea);
}

void CircleLabel::paintEvent(QPaintEvent* q)
{
    Q_UNUSED(q);

    QPainter paint(this);
    doPainting(&paint);
}

void CircleLabel::doPainting(QPainter* painter)
{
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QBrush(Qt::NoBrush));
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawEllipse(QRect(maxCircleArea/2-circleRad/2,maxCircleArea/2-circleRad/2,circleRad, circleRad));
}

void CircleLabel::setCircleRad(int rad)
{
    circleRad = rad;
    this->update();
}

int CircleLabel::getCircleRad()
{
    return circleRad;
}

int CircleLabel::getMaxCircleArea()
{
    return maxCircleArea;
}
