#include "barsongtimeline.h"
#include "ui_barsongtimeline.h"

/**
 * @brief This class is not used anymore. Can be deleted.
 */

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
