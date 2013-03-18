#include "barsongareaview.h"

BARSongAreaView::BARSongAreaView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene= new BARSongAreaScene();
    this->setScene(scene);
}
