#ifndef BARPATTERNBARSCROLLAREACONTENTS_H
#define BARPATTERNBARSCROLLAREACONTENTS_H

#include <QVector>
#include <QColor>
#include <QWidget>

namespace Ui {
class BARPatternBarScrollAreaContents;
}


/**
 * @brief Contains the list of the pattern bars.
 * When clicking the "+" button, a new pattern bar is created and added under the last one.
 * There is no "list" in the sense of C++, the bars are just added to the layout upon creation.
 */
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
    QVector<QColor> patternBarColorList; /**< list of all the possible colors of the sound bars. Upon creation of a new bar, its color is selected in this list. */
    int nbPatternCreated; /**< number of pattern bars in the "list". */

protected:
    //void dragEnterEvent(QDragEnterEvent *event);
    //void dragMoveEvent(QDragMoveEvent *event);
    //void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // BARPATTERNBARSCROLLAREACONTENTS_H
