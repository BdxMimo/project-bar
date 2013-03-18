#include "barsongarea.h"
#include "ui_barsongarea.h"
#include <QGraphicsRectItem>


BARSongArea::BARSongArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARSongArea)
{
    ui->setupUi(this);



    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::white);
    QPen blackPen(Qt::black);

    blackPen.setWidth(1);
    for(int i=0;i<50;i++)
    {
        QGraphicsRectItem *rectangle=new QGraphicsRectItem(i*100,0,100,60);
        QGraphicsTextItem *label=new QGraphicsTextItem(QString::number(i));
        label->setPos(i*100-5,-25);
                rectangle->setBrush(redBrush);
                rectangle->setPen(blackPen);
                scene->addItem(rectangle);
                scene->addItem(label);
                stock.push_back(rectangle);
    }

}

BARSongArea::~BARSongArea()
{
    delete ui;
}


