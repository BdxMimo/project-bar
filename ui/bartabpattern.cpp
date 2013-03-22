#include "bartabpattern.h"
#include "ui_bartabpattern.h"
#include "barsoundbar.h"
#include <QString>
#include <QFileDialog>
#include <QFileInfo>>

/**
 * @brief Implements the interface in the "pattern" tab.
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
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Files(*.*)")); /**< open dialog box. The user selects the sound he wants to add, and the path is retrieved. */
    QFileInfo fi(path); /**< retrieve the full path to the file. */
    QString name=fi.baseName(); /**< extract the name of the sound from the full path. */

    if(name!="") /**< check if the path is not void, in case the user canceled the transaction in the dialog box or selected no file. */
    {
        BARSoundBar *newBarSoundBar=new BARSoundBar(this,name); /**< creates the new sound bar and provides the name of the sound associated to the new soundbar to the constructor. */
        ui->soundBarArea->addWidget(newBarSoundBar); /** adds the new sound bar at the bottom of the layout, under the last sound bar and over the "+" button. */
    }
}
