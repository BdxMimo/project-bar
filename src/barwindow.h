#ifndef BARWINDOW_H
#define BARWINDOW_H

#include <QWidget>

/**
 * @brief Creates the main window.
 * This window only contains a TabWidget with two tabs.
 */

namespace Ui {
class BARWindow;
}

class BARWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARWindow(QWidget *parent = 0);
    ~BARWindow();

private:
    Ui::BARWindow *ui;
};

#endif // BARWINDOW_H
