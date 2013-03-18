#include "barsongarea.h"
#include "ui_barsongarea.h"
#include <QGraphicsRectItem>


BARSongArea::BARSongArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARSongArea)
{
    ui->setupUi(this);




}

BARSongArea::~BARSongArea()
{
    delete ui;
}


