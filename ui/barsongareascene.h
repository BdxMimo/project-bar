#ifndef BARSONGAREASCENE_H
#define BARSONGAREASCENE_H

#include <QGraphicsScene>
#include <QVector>
#include <QGraphicsRectItem>
#include <QDropEvent>
#include <QGraphicsSceneDragDropEvent>

/**
 * @brief Scene of the timeline.
 */

class BARSongAreaScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BARSongAreaScene(QObject *parent = 0);

private:
    QVector<QGraphicsRectItem*> stock; /**< the timeline is composed of rectangles. This vectors contains is the list of the rectangles of the timeline. */
    int timeLineSize; /**< length of each rectangle composing the timeline. */

protected:
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
};

#endif // BARSONGAREASCENE_H
