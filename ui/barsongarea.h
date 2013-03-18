#ifndef BARSONGAREA_H
#define BARSONGAREA_H
#include <QVector>
#include <QColor>


#include <QWidget>

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
    QVector<QColor> patternBarColorList;
    int nbPatternCreated;




};

#endif // BARSONGAREA_H
