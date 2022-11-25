#include "mainwindow.h"
#include <QColor>
#include <QImage>
#include <QMouseEvent>
#include <cmath>
#include <vector>

bool compBigger(const QColor&, const QColor&);

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

    takenPart = QImage(QSize(circle->getMaxCircleArea(), circle->getMaxCircleArea()), QImage::Format_ARGB32);

    maxSize = circle->getMaxCircleArea();

    message->setFont(QFont("SF Pro Display", 8));

    tLabel->setFont(QFont("SF Pro Display", 14));
    circleRadLabel->setFont(QFont("SF Pro Display", 10));

    slider->setMaximum(100);
    slider->setMinimum(10);
    slider->setFixedWidth(200);

    hbox = new QHBoxLayout(this);
    vbox = new QVBoxLayout(this);

    vbox->addWidget(tLabel, 10, Qt::AlignCenter);
    vbox->addWidget(circle,5,Qt::AlignHCenter);
    vbox->addWidget(slider,5,Qt::AlignCenter);
    vbox->addWidget(circleRadLabel,5,Qt::AlignCenter);


    hbox->setSpacing(16);
    hbox->addStretch(10);
    hbox->addLayout(vbox);
    hbox->addWidget(pLabel1,5,Qt::AlignCenter);


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

                if(sqrt((x-pX)*(x-pX) + (y-pY)*(y-pY)) <= (circle->getCircleRad()/2.0f))
                {
                    colorBase.push_back(color);
                }
            }
        }

        if(colorBase.size() < (3*(circle->getCircleRad()*circle->getCircleRad())/4))
        {
            QMessageBox::critical(this, "Warning", "You can't take this area");
            return;
        }

        takenPart.fill(QColor(255,255,255,0));
        int counter = 0;
        for(int y=0; y <= circle->getMaxCircleArea(); y++)
        {
            for(int x= 0; x<= circle->getMaxCircleArea();x++)
            {
                if(sqrt((x-circle->getMaxCircleArea()/2)*(x-circle->getMaxCircleArea()/2)+
                        (y-circle->getMaxCircleArea()/2)*(y-circle->getMaxCircleArea()/2)) <= circle->getCircleRad()/2.0f)
                {
                    takenPart.setPixelColor(QPoint(x,y),colorBase[counter]);
                    counter++;
                }
            }
        }
        circle->setImage(takenPart);

        maxSat = colorBase[0].hslSaturation();
        minSat = colorBase[0].hslSaturation();

        for(int c=0; c < colorBase.size(); c++) // Поиск максимального значения интенсивности
        {
            if(maxSat < colorBase[c].hslSaturation())
            {
                maxSat = colorBase[c].hslSaturation();
            }
            else if(minSat > colorBase[c].hslSaturation())
            {
                minSat = colorBase[c].hslSaturation();
            }
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


