#include "bartabsong.h"
#include "ui_bartabsong.h"
#include "barpatternbar.h"
#include <QGraphicsRectItem>

/**
 * @brief Implements the interface in the "song" tab.
 * Allows the manipulation of the pattern bars.
 */

/**
 * @brief Standard constructor.
 * @param[in] parent widget.
 */
BARTabSong::BARTabSong(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARTabSong),
    dialog(this)
{
    ui->setupUi(this);
}

/**
 * @brief Standard destructor.
 */
BARTabSong::~BARTabSong()
{
    delete ui;
}

/**
 * @brief Slot the launches dialog box to export the final song.
 */
void BARTabSong::on_buttonExport_clicked()
{
    dialog.show();
}
