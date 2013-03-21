#include "bartabsong.h"
#include "ui_bartabsong.h"
#include "barpatternbar.h"
#include <QGraphicsRectItem>


BARTabSong::BARTabSong(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARTabSong)
{
    ui->setupUi(this);


}

BARTabSong::~BARTabSong()
{
    delete ui;
}


