#include "bartabpattern.h"
#include "ui_bartabpattern.h"

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
