#ifndef BARTABSONG_H
#define BARTABSONG_H

#include <QWidget>
#include <QFileDialog>
#include <QVector>
#include <QColor>
#include <QGraphicsScene>
#include "barexportdialog.h"

/**
 * @brief Implements the interface in the "song" tab.
 * Allows the manipulation of the pattern bars.
 */

namespace Ui {
class BARTabSong;
}

class BARTabSong : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARTabSong(QWidget *parent = 0);
    ~BARTabSong();

private slots:
    void on_buttonExport_clicked();

private:
    Ui::BARTabSong *ui;
    BARExportDialog dialog; /**< dialog box to set up the exportation of the song as a standard format (wave...). */
};

#endif // BARTABSONG_H
