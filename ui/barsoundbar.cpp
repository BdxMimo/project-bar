#include "barsoundbar.h"
#include "ui_barsoundbar.h"
#include <QString>
#include <QFileDialog>
#include <ui/bargauge.h>
#include <QFileInfo>

/**
 * @brief Creates a soundbar in the tab "pattern".
 *
 * Each instance of this class is associated to a sound.
 * When pressing the "+" button (BARTabPattern), a soundbar is created and inserted under the last one.
 * Dialog box pops up, and the selected sound is associated to the new soundbar.
 * The name of the selected file is displayed on the tag.
 * Finally, upon creation of the soundbar, a certain number of soundgauges is created after the tag displaying the name.
 */

/**
 * @brief Constructor of the class.
 *
 * @param[in] parent widget.
 * @param[in] name of the sound associated to the soundbar.
 */
BARSoundBar::BARSoundBar(QWidget *parent,QString name) :
    QWidget(parent),
    ui(new Ui::BARSoundBar)
{
    ui->setupUi(this);
    fileName=name;
    ui->labelSoundName_2->setText(fileName); /**< Initialize tag to display the name of the sound associated to the soundbar. */
    gaugeNumber=16;
    for(int i=0;i<gaugeNumber;i++) /**< Create gaugeNumber soundgauges placed on the right of the soundbar. */
    {
        BARGauge *newBarGauge = new BARGauge();
        ui->horizontalLayout->addWidget(newBarGauge);
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
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Files(*.*)")); /**< Opens dialog box and retrieves file path. */
    QFileInfo fi(path);
    fileName=fi.baseName(); /**< Extracts the name of the file from the path. */
    ui->labelSoundName_2->setText(fileName); /**< Changes the name of the sound associated to the soundbar. */
}

/**
 * @brief This slot allows user to destroy the soundbar.
 */
void BARSoundBar::on_buttonSoundDelete_2_clicked()
{
    delete this;
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
