#include "barpatternbar.h"
#include "ui_barpatternbar.h"

BARPatternBar::BARPatternBar(QWidget *parent, QString name) :
    QWidget(parent),
    ui(new Ui::BARPatternBar)
{
    ui->setupUi(this);
    fileName=name;
    ui->labelPatternName->setText(fileName);
}

BARPatternBar::~BARPatternBar()
{
    delete ui;
}
