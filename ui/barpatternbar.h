#ifndef BARPATTERNBAR_H
#define BARPATTERNBAR_H

#include <QWidget>
#include <QString>
#include <QColor>
#include <QLabel>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QDebug>

/**
 * @brief Creates the pattern bar in the "song" tab.
 * Each bar is associated to one pattern.
 * A new bar is added in the left column of "barpatternbarscrollarea", under the last pattern bar, when clicking the "+" button under it.
 */

namespace Ui {
class BARPatternBar;
}

class BARPatternBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARPatternBar(QWidget *parent = 0, QString name="",QColor color=QColor(0,0,0));
    ~BARPatternBar();
    QString getFileName();
    QColor getBgColor();
    int getPatternLength();
    
private:
    Ui::BARPatternBar *ui;
    QString fileName; /**< stores the name of the pattern associated to the bar. */
    QColor bgColor; /**< stores the color of the bar. Each bar has a different color to give more visibility. */
    int patternLength; /**< stores the duration of the pattern associated to the bar. */
/*
protected:
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    //void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
*/
};

#endif // BARPATTERNBAR_H
