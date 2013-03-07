#ifndef BARSONGTIMELINE_H
#define BARSONGTIMELINE_H

#include <QScrollArea>

namespace Ui {
class BARSongTimeLine;
}

class BARSongTimeLine : public QScrollArea
{
    Q_OBJECT
    
public:
    explicit BARSongTimeLine(QWidget *parent = 0);
    ~BARSongTimeLine();
    
private:
    Ui::BARSongTimeLine *ui;
};

#endif // BARSONGTIMELINE_H
