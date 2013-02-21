#include "bargauge.h"
#include "ui_bargauge.h"
#include <QPalette>

BARGauge::BARGauge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARGauge)
{
    ui->setupUi(this);

    volume=0;
    offColor=QColor(255,255,255,200);
    onColor=QColor(0,0,255,127);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Background,offColor);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    this->setFixedSize(20,50);
}

BARGauge::~BARGauge()
{
    delete ui;
}

void BARGauge::mousePressEvent(QMouseEvent *event)
{
    volume=1-volume;

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
