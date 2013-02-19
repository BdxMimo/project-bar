#ifndef BARSOUNDBAR_H
#define BARSOUNDBAR_H

#include <QWidget>

namespace Ui {
class BARSoundBar;
}

class BARSoundBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARSoundBar(QWidget *parent = 0);
    ~BARSoundBar();
    
private slots:
    void on_buttonSoundImport_2_clicked();

private:
    Ui::BARSoundBar *ui;
};

#endif // BARSOUNDBAR_H
