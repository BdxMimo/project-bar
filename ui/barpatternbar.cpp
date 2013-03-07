#include "barpatternbar.h"
#include "ui_barpatternbar.h"

BARPatternBar::BARPatternBar(QWidget *parent, QString name, QColor color) :
    QWidget(parent),
    ui(new Ui::BARPatternBar)
{
    ui->setupUi(this);
    fileName=name;
    ui->labelPatternName->setText(fileName);
    bgColor=color;
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background,bgColor);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

BARPatternBar::~BARPatternBar()
{
    delete ui;
}
