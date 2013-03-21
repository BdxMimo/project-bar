#ifndef BARGAUGE_H
#define BARGAUGE_H

#include <QWidget>
#include <QColor>
#include <QMouseEvent>

namespace Ui {
class BARGauge;
}

class BARGauge : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARGauge(QWidget *parent = 0);
    ~BARGauge();
    void mousePressEvent(QMouseEvent*);
    
private:
    Ui::BARGauge *ui;
    QColor offColor,onColor,playingColor;
    float volume;
};

#endif // BARGAUGE_H
