#ifndef BARWINDOW_H
#define BARWINDOW_H

#include <QWidget>

namespace Ui {
class BARWindow;
}

class BARWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARWindow(QWidget *parent = 0);
    ~BARWindow();
    
private slots:
    void on_buttonSoundImport_clicked();

private:
    Ui::BARWindow *ui;
};

#endif // BARWINDOW_H
