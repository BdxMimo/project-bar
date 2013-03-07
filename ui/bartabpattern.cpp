#include "bartabpattern.h"
#include "ui_bartabpattern.h"
#include "barsoundbar.h"
#include <QString>
#include <QFileDialog>

BARtabPattern::BARtabPattern(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARtabPattern)
{
    ui->setupUi(this);
}

BARtabPattern::~BARtabPattern()
{
    delete ui;
}

void BARtabPattern::on_buttonAddSoundBar_clicked()
{
    QString name = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Files(*.*)"));

    // test if user didn't cancel in the file explorer : avoid the creation of a new soundbar with no file
    if(name!="")
    {
        BARSoundBar *newBarSoundBar=new BARSoundBar(this,name);
        ui->soundBarArea->addWidget(newBarSoundBar);
    }
}
