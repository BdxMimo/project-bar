#ifndef BARSONGAREAVIEW_H
#define BARSONGAREAVIEW_H

#include <QGraphicsView>
#include "barsongareascene.h"

class BARSongAreaView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BARSongAreaView(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    BARSongAreaScene *scene;

};

#endif // BARSONGAREAVIEW_H
