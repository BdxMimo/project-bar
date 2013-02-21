#include "bartabpattern.h"
#include "ui_bartabpattern.h"
#include "barsoundbar.h"
#include <QString>
#include <QFileDialog>
#include <iostream>

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
    std::cout<<"On y est";

    QString name = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Files(*.*)"));
    BARSoundBar *newBarSoundBar=new BARSoundBar(this,name);

    ui->soundBarArea->addWidget(newBarSoundBar);
}
