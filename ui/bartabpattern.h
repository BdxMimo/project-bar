#ifndef BARTABPATTERN_H
#define BARTABPATTERN_H

#include <QWidget>

namespace Ui {
class BARtabPattern;
}

class BARtabPattern : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARtabPattern(QWidget *parent = 0);
    ~BARtabPattern();
    
private:
    Ui::BARtabPattern *ui;
};

#endif // BARTABPATTERN_H
