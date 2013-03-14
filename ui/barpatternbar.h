#ifndef BARPATTERNBAR_H
#define BARPATTERNBAR_H

#include <QWidget>
#include <QString>
#include <QColor>



namespace Ui {
class BARPatternBar;
}

class BARPatternBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARPatternBar(QWidget *parent = 0, QString name="",QColor color=QColor(0,0,0));
    ~BARPatternBar();
    
private:
    Ui::BARPatternBar *ui;
    QString fileName;
    QColor bgColor;

};

#endif // BARPATTERNBAR_H
