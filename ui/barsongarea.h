#ifndef BARSONGAREA_H
#define BARSONGAREA_H
#include <QVector>
#include <QColor>
#include <QWidget>

/**
 * @brief Displays the list of pattern bars on the left, and the timeline on the right.
 * Is displayed in the song tab of the main window.
 */

namespace Ui {
class BARSongArea;
}

class BARSongArea : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARSongArea(QWidget *parent = 0);
    ~BARSongArea();

private:
    Ui::BARSongArea *ui;
    // QVector<QColor> patternBarColorList;
    // int nbPatternCreated;
};

#endif // BARSONGAREA_H
