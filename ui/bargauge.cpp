#include "bargauge.h"
#include "ui_bargauge.h"
#include <QPalette>
#include <iostream>

BARGauge::BARGauge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARGauge)
{
    ui->setupUi(this);

    volume=0;
    offColor=QColor(255,0,0,127);
    onColor=QColor(0,0,255,127);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Background,offColor);
    this->setAutoFillBackground(true);
    this->setGeometry(0,0,100,200);
    this->setPalette(palette);
}

BARGauge::~BARGauge()
{
    delete ui;
}

void BARGauge::mousePressEvent(QMouseEvent *event)
{
    volume=1-volume;
    std::cout<<"volume : "<<volume<<std::endl;

    if(volume==0)
    {
        QPalette palette = this->palette();
        palette.setColor(QPalette::Background,offColor);
        this->setAutoFillBackground(true);
        this->setPalette(palette);
    }
    else
    {
        QPalette palette = this->palette();
        palette.setColor(QPalette::Background,onColor);
        this->setAutoFillBackground(true);
        this->setPalette(palette);
    }
}
