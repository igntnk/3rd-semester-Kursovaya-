#include "mainwindow.h"
#include <QHBoxLayout>
#include <QColor>
#include <QImage>
#include <QPainter>

PixWork::PixWork(QWidget* parent):
    QWidget(parent)
{
    QTextStream out(stdout);

    photo = QImage("C:/Users/ilyai/Downloads/zamok.png");
    pLabel1 = new QPushButton(this);
    pLabel1->setIcon(QIcon(QPixmap::fromImage(photo)));
    pLabel1->setIconSize(QSize(898,466));
    pLabel1->setFixedHeight(466);
    pLabel1->setFixedWidth(898);
    pLabel1->show();

    slider = new QSlider(this);
    t1 = "Circle's radius(Pixels)";
    tLabel = new QLabel(t1, this);
    circle = new CircleLabel(this);
    circleRadLabel = new QLabel("10", this);
    circle->show();

    tLabel->setFont(QFont("SF Pro Display", 14));
    circleRadLabel->setFont(QFont("SF Pro Display", 14));

    slider->setMaximum(100);
    slider->setMinimum(10);

    hbox = new QHBoxLayout(this);
    vbox = new QVBoxLayout(this);

    vbox->setSpacing(16);
    vbox->addStretch(1);

    vbox->addWidget(tLabel,5,Qt::AlignHCenter);
    vbox->addWidget(circle,5,Qt::AlignHCenter);
    vbox->addWidget(circleRadLabel, 5, Qt::AlignHCenter);


    hbox->setSpacing(16);
    hbox->addStretch(1);
    hbox->addLayout(vbox);
    hbox->addWidget(slider, 5, Qt::AlignHCenter);
    hbox->addWidget(pLabel1,5, Qt::AlignHCenter);

    setLayout(hbox);

    connect(slider, &QSlider::valueChanged, circle, &CircleLabel::setCircleRad);
    connect(slider,&QSlider::valueChanged, circleRadLabel,
            static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    out << pLabel1->geometry().topLeft().x() << ' ' << pLabel1->geometry().topLeft().y()
        << Qt::endl << pLabel1->geometry().bottomRight().x() << ' ' << pLabel1->geometry().bottomRight().y();
}

void PixWork::mousePressEvent(QMouseEvent* event)
{

}




