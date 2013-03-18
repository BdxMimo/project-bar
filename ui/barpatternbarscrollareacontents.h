#ifndef BARPATTERNBARSCROLLAREACONTENTS_H
#define BARPATTERNBARSCROLLAREACONTENTS_H
#include <QVector>
#include <QColor>

#include <QWidget>

namespace Ui {
class BARPatternBarScrollAreaContents;
}

class BARPatternBarScrollAreaContents : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARPatternBarScrollAreaContents(QWidget *parent = 0);
    ~BARPatternBarScrollAreaContents();

private slots:


    void on_buttonAddPatternBar_clicked();


private:
    Ui::BARPatternBarScrollAreaContents *ui;
    QVector<QColor> patternBarColorList;
    int nbPatternCreated;

protected:
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    //void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // BARPATTERNBARSCROLLAREACONTENTS_H
