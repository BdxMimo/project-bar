#ifndef BARSOUNDBAR_H
#define BARSOUNDBAR_H

#include <QWidget>
#include <QVector>

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

    void on_buttonSoundDelete_2_clicked();



private:
    QVector<bool> rhythm; // vector that contains the values of checkboxes
    Ui::BARSoundBar *ui;
};

#endif // BARSOUNDBAR_H
