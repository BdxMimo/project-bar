#include "barsongareascene.h"

#include <QLabel>
#include <QDebug>
#include <QMimeData>
#include <QPointF>

/**
 * @brief Scene of the timeline.
 */

/**
 * @brief Constructor.
 * @param[in] parent widget.
 */
BARSongAreaScene::BARSongAreaScene(QObject *parent) : QGraphicsScene(parent)
{
    timeLineSize=100; /**< length of each rectangle composing the timeline. */

    QBrush redBrush(Qt::white); /**< desired color for the background of the rectangles when empty. */
    QPen blackPen(Qt::black); /**< desired color for the outline of the rectangle. */
    blackPen.setWidth(1); /**< sets width of the outline of the rectangle. */

    for(int i=0;i<50;i++) /**< this boucle creates the 50 rectangles of the timeline. */
    {
        QGraphicsRectItem *rectangle=new QGraphicsRectItem(i*timeLineSize,0,timeLineSize,60); /**< create the new rectangle on the right of the last one. */
        QGraphicsTextItem *label=new QGraphicsTextItem(QString::number(i)); /**< displays the number of the rectangle in the timeline. */
        label->setPos(i*timeLineSize-timeLineSize/20,-25); /**< position the label in the top left corner of the rectangle. */
        rectangle->setBrush(redBrush); /**< set the background color. */
        rectangle->setPen(blackPen); /**< set the outline. */
        addItem(rectangle); /**< the last three lines add the rectangle to the timeline. */
        addItem(label);
        stock.push_back(rectangle);
    }
}

/**
 * @brief Implements the drop of a pattern on the timeline.
 * The drag-and-dropped pattern is inserted in the pointed rectangle of the timeline.
 * @param[in] drop event.
 */
void BARSongAreaScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QColor currentColor; /**< creation of the two variables that will receive the information sent by through the drag-and-drop. */
    int patternLength;

    QByteArray itemData= event->mimeData()->data("application/x-dnditemdata"); /**< unpack the information stored in the MIME file. */
    QDataStream droppedData(&itemData, QIODevice::ReadOnly);

    droppedData>>currentColor; /**< store the unpacked information in each relevant variable. */
    droppedData>>patternLength;

    QGraphicsRectItem *testdrop=new QGraphicsRectItem(event->scenePos().toPoint().x() - (event->scenePos().toPoint().x() % timeLineSize),0,timeLineSize*patternLength,60); /**< creates a rectangle in the rectangle of the timeline where the drop occured. */
    QBrush currentBrush(currentColor); /**< sets the color of the rectangle. This color corresponds to the color of the pattern that was dragged-and-dropped. */
    testdrop->setBrush(currentBrush);

    addItem(testdrop);
}

/**
 * @brief Give clearance for the drop.
 * @param[in] drag enter event
 */
void BARSongAreaScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(true);
    event->acceptProposedAction();
}

/**
 * @brief Required for the drop to happen (don't know exactly why, found on the Internet).
 * @param[in] drag enter event
 */
void BARSongAreaScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event){}
