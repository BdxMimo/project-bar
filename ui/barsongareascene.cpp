#include "barsongareascene.h"

#include <QLabel>
#include <QDebug>
#include <QMimeData>
#include <QPointF>
#

BARSongAreaScene::BARSongAreaScene(QObject *parent) :
    QGraphicsScene(parent)
{
    timeLineSize=100;
    QBrush redBrush(Qt::white);
    QPen blackPen(Qt::black);

    blackPen.setWidth(1);
    for(int i=0;i<50;i++)
    {
        QGraphicsRectItem *rectangle=new QGraphicsRectItem(i*timeLineSize,0,timeLineSize,60);
        QGraphicsTextItem *label=new QGraphicsTextItem(QString::number(i));
        label->setPos(i*timeLineSize-timeLineSize/20,-25);
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
    int patternLength;
    QByteArray itemData= event->mimeData()->data("application/x-dnditemdata");
    QDataStream droppedData(&itemData, QIODevice::ReadOnly);
    droppedData>>currentColor;
    droppedData>>patternLength;


    qDebug() << event->scenePos().toPoint().x() << endl;
    QGraphicsRectItem *testdrop=new QGraphicsRectItem(event->scenePos().toPoint().x() - (event->scenePos().toPoint().x() % timeLineSize),0,timeLineSize*patternLength,60);
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
