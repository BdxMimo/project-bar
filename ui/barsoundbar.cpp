#include "barsoundbar.h"
#include "ui_barsoundbar.h"
#include <QString>
#include <QFileDialog>
#include <ui/bargauge.h>
#include <QFileInfo>

/**
 * @brief Constructor of the class.
 *
 * @param[in] parent widget.
 * @param[in] name of the sound associated to the soundbar.
 */
BARSoundBar::BARSoundBar(unsigned int i, QWidget *parent, QString name) :
    QWidget(parent),
    ui(new Ui::BARSoundBar)
{
    ui->setupUi(this);
    fileName=name;
    ui->labelSoundName_2->setText(fileName); /**< Initialize tag to display the name of the sound associated to the soundbar. */
    nGauges=16;
    iTrack = i;
    for(unsigned int j=0;j<nGauges;j++) /**< Create gaugeNumber soundgauges placed on the right of the soundbar. */
    {
        BARGauge *newGauge = new BARGauge(j, this);
        connect(newGauge, SIGNAL(valueChanged(uint,uint)), this, SLOT(onGaugeValueChanged(uint,uint)));
        ui->horizontalLayout->addWidget(newGauge);
        gauges.push_back(newGauge);
    }
}

BARSoundBar::~BARSoundBar()
{
    delete ui;
}

/**
 * @brief This slot handles the sound import procedure.
 *
 * This slot allows the user to modify the sound attached to the soundbar.
 * Upon clicking the "import" button, dialog box pops up, and the path of the selected file is retrieved.
 * The name of the file is extracted from the entire path and the new name of the sound is set in the parameter "fileName".
 */
void BARSoundBar::on_buttonSoundImport_2_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Files(*.wav)")); /**< Opens dialog box and retrieves file path. */
    QFileInfo fi(path);
    fileName=fi.baseName(); /**< Extracts the name of the file from the path. */
    ui->labelSoundName_2->setText(fileName); /**< Changes the name of the sound associated to the soundbar. */
}

/**
 * @brief This slot allows user to destroy the soundbar.
 */
void BARSoundBar::on_buttonSoundDelete_2_clicked()
{
    emit hasBeenDeleted(iTrack);
    delete this;
}

void BARSoundBar::on_buttonSoundPlay_2_clicked()
{
    emit wantPreview(iTrack);
}

void BARSoundBar::onGaugeValueChanged(unsigned int value, unsigned int iNote)
{
    emit valueChanged(iTrack, iNote, value);
}

void BARSoundBar::playNote(unsigned int iNote)
{
    if (iNote != nGauges) {
        gauges[iNote]->activatePlaying();
    }
    if (iNote != 0) {
        gauges[iNote-1]->deactivatePlaying();
    }
}

/**
 * @brief Modify the name of the sound associated to the soundbar.
 */
void BARSoundBar::setFileName(QString name)
{
    fileName=name;
    ui->labelSoundName_2->setText(fileName);
}

/**
 * @brief Returns the name of the sound associated to the soundbar.
 * @return name of the sound associated to the soundbar.
 */
QString BARSoundBar::getFileName()
{
    return fileName;
}

void BARSoundBar::setIndex(unsigned int i)
{
    iTrack = i;
}
