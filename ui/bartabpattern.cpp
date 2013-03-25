#include "bartabpattern.h"
#include "ui_bartabpattern.h"
#include "barsoundbar.h"
#include <QString>
#include <QFileDialog>
#include <QFileInfo>

/**
 * @brief Implements the interface in the "pattern" tab.
 * Allows the manipulation of the sound bars.
 */

/**
 * @brief Standard constructor.
 * @param[in] parent widget.
 */
BARtabPattern::BARtabPattern(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARtabPattern)
{
    ui->setupUi(this);
    nTracks = 0;
    soundSystem = new BARSoxPatternSoundSystem(60, 8, 2);

    connect(this, SIGNAL(newTrackCreated(const char*)), soundSystem, SLOT(addTrack(const char*)));
    connect(this, SIGNAL(tempoChanged(uint)), soundSystem, SLOT(changeTempo(uint)));
    connect(this, SIGNAL(trackDeleted(uint)), soundSystem, SLOT(deleteTrack(uint)));
    connect(this, SIGNAL(volumeChanged(uint,uint,uint)), soundSystem, SLOT(changeVolume(uint,uint,uint)));
    connect(this, SIGNAL(wantPreview(uint)), soundSystem, SLOT(preview(uint)));
    connect(this, SIGNAL(wantPlay()), soundSystem, SLOT(playNote()));
    connect(this, SIGNAL(wantNextNote(uint)), soundSystem, SLOT(playNote(uint)));
    connect(soundSystem, SIGNAL(endOfNoteDetected(uint)), this, SLOT(playNote(uint)));
}

/**
 * @brief Default destructor.
 */
BARtabPattern::~BARtabPattern()
{
    delete ui;
}

/**
 * @brief Slot that triggers the creation of a new sound bar.
 */
void BARtabPattern::on_buttonAddSoundBar_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("WAV Files(*.wav)")); /**< open dialog box. The user selects the sound he wants to add, and the path is retrieved. */
    QFileInfo fi(path); /**< retrieve the full path to the file. */
    QString name=fi.baseName(); /**< extract the name of the sound from the full path. */

    if(name!="") /**< check if the path is not void, in case the user canceled the transaction in the dialog box or selected no file. */
    {
        BARSoundBar *newBarSoundBar=new BARSoundBar(nTracks,this,name); /**< creates the new sound bar and provides the name of the sound associated to the new soundbar to the constructor. */
        soundBars.push_back(newBarSoundBar);
        ui->soundBarArea->addWidget(newBarSoundBar); /** adds the new sound bar at the bottom of the layout, under the last sound bar and over the "+" button. */

        connect(newBarSoundBar, SIGNAL(hasBeenDeleted(uint)), this, SLOT(deleteTrack(uint)));
        connect(newBarSoundBar, SIGNAL(valueChanged(uint,uint,uint)), this, SLOT(changeVolume(uint,uint,uint)));
        connect(newBarSoundBar, SIGNAL(wantPreview(uint)), this, SLOT(trackPreview(uint)));

        emit newTrackCreated(path.toStdString().c_str());
        nTracks++;
    }
}

void BARtabPattern::trackPreview(unsigned int iTrack)
{
    emit wantPreview(iTrack);
}

void BARtabPattern::changeVolume(unsigned int iTrack, unsigned int iNote, unsigned int volume)
{
    emit volumeChanged(iTrack, iNote, volume);
}

void BARtabPattern::changeTempo(int tempo)
{
    emit tempoChanged(tempo > 20 ? (unsigned int)tempo : 20);
}

void BARtabPattern::on_buttonPlay_clicked()
{
    for (unsigned int i=0; i < nTracks; i++) {
        soundBars[i]->playNote(0);
    }

    emit wantPlay();
}

void BARtabPattern::deleteTrack(unsigned int i)
{
    soundBars.erase(soundBars.begin()+i);
    for (int j=i; j < soundBars.size(); j++) {
        soundBars[j]->setIndex(j);
    }

    nTracks--;

    emit trackDeleted(i);
}

void BARtabPattern::playNote(unsigned int iNote)
{
    for (unsigned int i=0; i < nTracks; i++) {
        soundBars[i]->playNote(iNote+1);
    }
    emit wantNextNote(iNote+1);
}
