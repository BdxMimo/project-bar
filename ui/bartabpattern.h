#ifndef BARTABPATTERN_H
#define BARTABPATTERN_H

#include <QWidget>
#include <QVector>

#include "barsoundbar.h"
#include "BARSox/BARSoxPatternSoundSystem.h"

/**
 * @brief Implements the interface in the "pattern" tab.
 * Allows the manipulation of the sound bars.
 */

namespace Ui {
class BARtabPattern;
}

class BARtabPattern : public QWidget
{
    Q_OBJECT
    
public:
    explicit BARtabPattern(QWidget *parent = 0);
    ~BARtabPattern();

signals:
    void newTrackCreated(const char* filename);
    void trackDeleted(unsigned int i);
    void wantPreview(unsigned int iTrack);
    void volumeChanged(unsigned int iTrack, unsigned int iNote, unsigned int volume);
    void tempoChanged(unsigned int tempo);
    void wantPlay();
    void wantNextNote(unsigned int iNote);
    
private slots:
    void on_buttonAddSoundBar_clicked();
    void on_buttonPlay_clicked();
    void deleteTrack(unsigned int i);
    void trackPreview(unsigned int iTrack);
    void changeVolume(unsigned int iTrack, unsigned int iNote, unsigned int volume);
    void changeTempo(int tempo);
    void playNote(unsigned int iNote);

private:
    Ui::BARtabPattern *ui;
    QVector<BARSoundBar*> soundBars;
    BARSoxPatternSoundSystem* soundSystem;
    unsigned int nTracks;
};

#endif // BARTABPATTERN_H
