#include "barsoundbar.h"
#include "ui_barsoundbar.h"
#include <QString>
#include <QFileDialog>
#include <ui/bargauge.h>

BARSoundBar::BARSoundBar(QWidget *parent,QString name) :
    QWidget(parent),
    ui(new Ui::BARSoundBar)
{
    ui->setupUi(this);
    fileName=name;
    ui->labelSoundName_2->setText(fileName);
    gaugeNumber=16;
    for(int i=0;i<gaugeNumber;i++)
    {
        BARGauge *newBarGauge = new BARGauge();
        ui->horizontalLayout->addWidget(newBarGauge);
    }
}

BARSoundBar::~BARSoundBar()
{
    delete ui;
}

void BARSoundBar::on_buttonSoundImport_2_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Files(*.*)"));
    ui->labelSoundName_2->setText(fileName);
}

void BARSoundBar::on_buttonSoundDelete_2_clicked()
{
    delete this;
}

void BARSoundBar::setFileName(QString name)
{
    fileName=name;
    ui->labelSoundName_2->setText(fileName);
}

QString BARSoundBar::getFileName()
{
    return fileName;
}
