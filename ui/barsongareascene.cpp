#include "barsongareascene.h"

#include <QLabel>
#include <QDebug>
#include <QMimeData>


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

void BARSongAreaScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug()<<"DROOOOP à "<<event->scenePos().x()<<" et à "<<event->scenePos().y()<<endl;


    QColor currentColor;
    QByteArray itemData= event->mimeData()->data("application/x-dnditemdata");
    QDataStream droppedData(&itemData, QIODevice::ReadOnly);
    droppedData>>currentColor;
    QGraphicsRectItem *testdrop=new QGraphicsRectItem(event->scenePos().x(),0,100,60);
    QBrush currentBrush(currentColor);
    testdrop->setBrush(currentBrush);

    //event->mimeData()->data()



    addItem(testdrop);



}

void BARSongAreaScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(true);
    qDebug()<<"DRAG EN COUUUURS !"<<endl;
    event->acceptProposedAction();
}

void BARSongAreaScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug()<<"Ça bouuuuuge ! "<<event->scenePos().x()<<endl;
}
