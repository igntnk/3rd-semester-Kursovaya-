#include "mainwindow.h"
#include <QColor>
#include <QImage>
#include <QMouseEvent>
#include <cmath>
#include <vector>

PixWork::PixWork(QWidget* parent):
    QWidget(parent)
{
    message = new QMessageBox(this);

    photo = QImage("C:/Users/ilyai/Downloads/zamok.png");
    pLabel1 = new QLabel(this);
    pLabel1->setPixmap(QPixmap::fromImage(photo));
    pLabel1->setFixedHeight(photo.height());
    pLabel1->setFixedWidth(photo.width());
    pLabel1->show();

    sniper = new CircleLabel(pLabel1);
    sniper->setGeometry(-sniper->getMaxCircleArea(),0,0,0);

    slider = new QSlider(Qt::Horizontal,this);

    t1 = "Circle's radius\n       (Pixels)";
    tLabel = new QLabel(t1, this);
    circle = new CircleLabel(this);
    circleRadLabel = new QLabel("10", this);
    circle->show();

    maxSize = circle->getMaxCircleArea();

    message->setFont(QFont("SF Pro Display", 8));

    tLabel->setFont(QFont("SF Pro Display", 14));
    circleRadLabel->setFont(QFont("SF Pro Display", 10));

    slider->setMaximum(100);
    slider->setMinimum(10);
    slider->setFixedWidth(200);

    hbox = new QHBoxLayout(this);
    vbox = new QVBoxLayout(this);

    vbox->setSpacing(16);
    vbox->addStretch(1);
    vbox->addWidget(tLabel,5,Qt::AlignHCenter);
    vbox->addWidget(circle,5,Qt::AlignHCenter);
    vbox->addWidget(slider, 5, Qt::AlignHCenter);
    vbox->addWidget(circleRadLabel, 5, Qt::AlignHCenter);


    hbox->setSpacing(16);
    hbox->addStretch(1);
    hbox->addLayout(vbox);
    hbox->addWidget(pLabel1,5, Qt::AlignHCenter);

    setLayout(hbox);

    connect(slider, &QSlider::valueChanged, circle, &CircleLabel::setCircleRad);
    connect(slider, &QSlider::valueChanged, sniper, &CircleLabel::setCircleRad);
    connect(slider,&QSlider::valueChanged, circleRadLabel,
            static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    pLabel1->setMouseTracking(true);
    sniper->setMouseTracking(true);
    setMouseTracking(true);

}

void PixWork::mousePressEvent(QMouseEvent* event)//Обработка нажатия мышкой
{
    QString satInfo;
    int maxSat=0;
    int minSat = 255;
    int midSat = 0;

    if(isGoal(event,pLabel1->geometry()))
    {
        std::vector<QColor> colorBase;
        for(int y=0;y < photo.height(); y++) //Выборка попавших в круг пикселей
        {
            for(int x = 0; x < photo.width(); x++)
            {
                QColor color = photo.pixelColor(x,y);
                int pX = event->pos().x() - pLabel1->geometry().topLeft().x();
                int pY = event->pos().y() - pLabel1->geometry().topLeft().y();
                if(((x-pX)*(x-pX) + (y-pY)*(y-pY)) < (circle->getCircleRad()*circle->getCircleRad()))
                {
                    colorBase.push_back(color);
                }
            }
        }

        for(int c=0; c < colorBase.size(); c++) // Поиск максимального значения интенсивности
        {
            if(maxSat < colorBase[c].hsvSaturation())
            {
                maxSat = colorBase[c].hsvSaturation();
            }
        }

        for(int c=0; c < colorBase.size(); c++) // Поиск минимального значения интенсивности
        {
            if(minSat > colorBase[c].hsvSaturation())
            {
                minSat = colorBase[c].hsvSaturation();
            }
        }

        for(int c=0; c < colorBase.size(); c++) // Поиск срднего значения интенсивности
        {
            midSat += colorBase[c].hsvSaturation();
            if(c == colorBase.size()-1)
            {
                midSat /= colorBase.size();
            }
        }

        satInfo = "Min Saturation: " + QString::number(minSat) + '\n'
                + "Max Saturation: " + QString::number(maxSat) + '\n'
                + "Middle Saturation: " + QString::number(midSat) + '\n'
                + "Was analised: " + QString::number(colorBase.size()) + "pixels";

        QRect recter;
        recter.setHeight(maxSize);
        recter.setWidth(maxSize);
        recter.moveCenter(event->pos()-pLabel1->geometry().topLeft());
        sniper->setGeometry(recter);

        message->setWindowTitle("Saturation information");
        message->setText(satInfo);
        message->show();
    }
}

bool PixWork::isGoal(QMouseEvent* event, QRect refer)
{
    return(refer.topLeft().x() <= event->pos().x() and event->pos().x()<= refer.bottomRight().x()
           and refer.topLeft().y() <= event->pos().y() and event->pos().y() <= refer.bottomRight().y());
}

void PixWork::mouseMoveEvent(QMouseEvent* event)
{
    if(isGoal(event,pLabel1->geometry()))
    {
        QRect recter;
        recter.setHeight(maxSize);
        recter.setWidth(maxSize);
        recter.moveCenter(event->pos()-pLabel1->geometry().topLeft());
        sniper->setGeometry(recter);
    }
    else
    {
        sniper->setGeometry(-sniper->getMaxCircleArea(),0,0,0);
    }
}





