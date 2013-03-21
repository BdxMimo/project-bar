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
    
private:
    Ui::BARPatternBar *ui;
    QString fileName;
    QColor bgColor;
/*
protected:
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    //void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
*/
};

#endif // BARPATTERNBAR_H
