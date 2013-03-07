#ifndef BARPATTERNBAR_H
#define BARPATTERNBAR_H

#include <QWidget>
#include <QString>

namespace Ui {
class BARPatternBar;
}

class BARPatternBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARPatternBar(QWidget *parent = 0, QString name="");
    ~BARPatternBar();
    
private:
    Ui::BARPatternBar *ui;
    QString fileName;
};

#endif // BARPATTERNBAR_H
