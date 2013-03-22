#ifndef BARGAUGE_H
#define BARGAUGE_H

#include <QWidget>
#include <QColor>
#include <QMouseEvent>

/**
 * @brief Implements the gauge played in the "pattern" tab.
 * This gauge controls when a sound is played, and at which volume.
 * A series of gauges is created in each soundbar, by the constructor of the class "barsoundbar".
 */

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
    QColor offColor,onColor,playingColor; /**< variables that control the color of the gauge : transparent when not clicked, colored when clicked. */
    unsigned int volume; /**< value of the volume at which the sound has to be played (proportional to the height of the colored part of the gauge. */
};

#endif // BARGAUGE_H
