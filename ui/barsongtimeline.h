#ifndef BARSONGTIMELINE_H
#define BARSONGTIMELINE_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class BARSongTimeLine;
}

/**
 * @brief This class is not used anymore. Can be deleted.
 */
class BARSongTimeLine : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARSongTimeLine(QWidget *parent = 0);
    ~BARSongTimeLine();
    
private:
    Ui::BARSongTimeLine *ui;
};

#endif // BARSONGTIMELINE_H
