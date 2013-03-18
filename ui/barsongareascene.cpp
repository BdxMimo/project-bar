#include "barsongareascene.h"

BARSongAreaScene::BARSongAreaScene(QObject *parent) :
    QGraphicsScene(parent)
{

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
                addItem(rectangle);
                addItem(label);
                stock.push_back(rectangle);
    }

}
