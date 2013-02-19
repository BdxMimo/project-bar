#include "bartabpattern.h"
#include "ui_bartabpattern.h"
#include "barsoundbar.h"

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
    BARSoundBar *newBarSoundBar=new BARSoundBar(this);
    ui->soundBarArea->addWidget(newBarSoundBar);
}
