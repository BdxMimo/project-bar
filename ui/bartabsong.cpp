#include "bartabsong.h"
#include "ui_bartabsong.h"
#include "barpatternbar.h"

BARTabSong::BARTabSong(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARTabSong)
{
    ui->setupUi(this);
}

BARTabSong::~BARTabSong()
{
    delete ui;
}

void BARTabSong::on_buttonAddPatternBar_clicked()
{
    QString name = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Files(*.*)"));

    // test if user didn't cancel in the file explorer : avoid the creation of a new soundbar with no file
    if(name!="")
    {
        BARPatternBar *newBarPatternBar=new BARPatternBar(this,name);
        ui->patternBarArea->addWidget(newBarPatternBar);
    }
}
