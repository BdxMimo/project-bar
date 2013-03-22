#include "barsongarea.h"
#include "ui_barsongarea.h"
#include <QGraphicsRectItem>

/**
 * @brief Displays the list of pattern bars on the left, and the timeline on the right.
 * Is displayed in the song tab of the main window.
 */

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


