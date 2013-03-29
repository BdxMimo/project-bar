#ifndef BARSOUNDBAR_H
#define BARSOUNDBAR_H

#include <QWidget>
#include <QVector>
#include <QString>

#include "bargauge.h"

namespace Ui {
class BARSoundBar;
}

/**
 * @brief Creates a soundbar in the tab "pattern".
 *
 * Each instance of this class is associated to a sound.
 * When pressing the "+" button (BARTabPattern), a soundbar is created and inserted under the last one.
 * Dialog box pops up, and the selected sound is associated to the new soundbar.
 * The name of the selected file is displayed on the tag.
 * Finally, upon creation of the soundbar, a certain number of soundgauges is created after the tag displaying the name.
 */
class BARSoundBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARSoundBar(unsigned int i, QWidget *parent = 0, QString name="");
    ~BARSoundBar();
    QString getFileName();
    void setFileName(QString);
    void setIndex(unsigned int i);
    
public slots:
    void on_buttonSoundImport_2_clicked();
    void on_buttonSoundDelete_2_clicked();
    void on_buttonSoundPlay_2_clicked();
    void onGaugeValueChanged(unsigned int value, unsigned int iNote);
    void playNote(unsigned int iNote);

signals:
    void valueChanged(unsigned int iTrack, unsigned int iNote, unsigned int value);
    void hasBeenDeleted(unsigned int iTrack);
    void wantPreview(unsigned int iTrack);

private:
    QVector<BARGauge*> gauges; /**< Vector that contains the values of the soundgauges. */
    Ui::BARSoundBar *ui;
    QString fileName; /**< Name of the sound associated to the soundbar. */
    int nGauges; /**< Number of soundgauges the will be created on the right of the tag displaying the name of the file. */
    unsigned int iTrack;
};

#endif // BARSOUNDBAR_H
