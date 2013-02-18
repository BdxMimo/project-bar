#include "barsoundbar.h"
#include "ui_barsoundbar.h"
#include <QString>
#include <QFileDialog>

BARSoundBar::BARSoundBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARSoundBar)
{
    ui->setupUi(this);
}

BARSoundBar::~BARSoundBar()
{
    delete ui;
}

void BARSoundBar::on_buttonSoundImport_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Files(*.*)"));
    ui->labelSoundName_2->setText(fileName);
}
