#include "barsongarea.h"
#include "ui_barsongarea.h"
#include <QGraphicsRectItem>

/**
 * @brief Displays the list of pattern bars on the left, and the timeline on the right.
 * Is displayed in the song tab of the main window.
 */

/**
 * @brief Default constructor.
 * @param parent widget.
 */
BARSongArea::BARSongArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARSongArea)
{
    ui->setupUi(this);
}

/**
 * @brief Default destructor.
 */
BARSongArea::~BARSongArea()
{
    delete ui;
}
