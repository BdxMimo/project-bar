#include "barsongtimeline.h"
#include "ui_barsongtimeline.h"

BARSongTimeLine::BARSongTimeLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARSongTimeLine)
{
    ui->setupUi(this);

}

BARSongTimeLine::~BARSongTimeLine()
{
    delete ui;
}
