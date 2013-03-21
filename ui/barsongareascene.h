#ifndef BARSONGAREASCENE_H
#define BARSONGAREASCENE_H

#include <QGraphicsScene>
#include <QVector>
#include <QGraphicsRectItem>
#include <QDropEvent>
#include <QGraphicsSceneDragDropEvent>
class BARSongAreaScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BARSongAreaScene(QObject *parent = 0);
    
signals:
    
public slots:

private:
    QVector<QGraphicsRectItem*> stock;

protected:
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
};

#endif // BARSONGAREASCENE_H
