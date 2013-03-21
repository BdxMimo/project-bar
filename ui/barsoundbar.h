#ifndef BARSOUNDBAR_H
#define BARSOUNDBAR_H

#include <QWidget>
#include <QVector>
#include <QString>

/**
 * @brief Creates a soundbar in the tab "pattern".
 *
 * Each instance of this class is associated to a sound.
 * When pressing the "+" button (BARTabPattern), a soundbar is created and inserted under the last one.
 * Dialog box pops up, and the selected sound is associated to the new soundbar.
 * The name of the selected file is displayed on the tag.
 * Finally, upon creation of the soundbar, a certain number of soundgauges is created after the tag displaying the name.
 */

namespace Ui {
class BARSoundBar;
}

class BARSoundBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARSoundBar(QWidget *parent = 0,QString name="");
    ~BARSoundBar();
    QString getFileName();
    void setFileName(QString);
    
private slots:
    void on_buttonSoundImport_2_clicked();
    void on_buttonSoundDelete_2_clicked();

private:
    QVector<bool> rhythm; /**< Vector that contains the values of the soundgauges. */
    Ui::BARSoundBar *ui;
    QString fileName; /**< Name of the sound associated to the soundbar. */
    int gaugeNumber; /**< Number of soundgauges the will be created on the right of the tag displaying the name of the file. */
};

#endif // BARSOUNDBAR_H
