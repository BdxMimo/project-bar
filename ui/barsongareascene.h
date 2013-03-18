#ifndef BARSONGAREASCENE_H
#define BARSONGAREASCENE_H

#include <QGraphicsScene>
#include <QVector>
#include <QGraphicsRectItem>

class BARSongAreaScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BARSongAreaScene(QObject *parent = 0);
    
signals:
    
public slots:

private:
    QVector<QGraphicsRectItem*> stock;
};

#endif // BARSONGAREASCENE_H
