#include "barpatternbarscrollareacontents.h"
#include "ui_barpatternbarscrollareacontents.h"
#include <QFileDialog>
#include <QFileInfo>
#include "barpatternbar.h"

BARPatternBarScrollAreaContents::BARPatternBarScrollAreaContents(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARPatternBarScrollAreaContents)
{
    ui->setupUi(this);

    nbPatternCreated=0;
    patternBarColorList.push_back(QColor(255,102,102,255));
    patternBarColorList.push_back(QColor(255,153,102,255));
    patternBarColorList.push_back(QColor(255,255,51,255));
    patternBarColorList.push_back(QColor(200,200,100,255));
    patternBarColorList.push_back(QColor(120,240,130,255));
}

BARPatternBarScrollAreaContents::~BARPatternBarScrollAreaContents()
{
    delete ui;
}

void BARPatternBarScrollAreaContents::on_buttonAddPatternBar_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Files(*.*)"));
    QFileInfo fi(path);
    QString name=fi.baseName();
    // test if user didn't cancel in the file explorer : avoid the creation of a new soundbar with no file
    if(name!="")
    {

        BARPatternBar *newBarPatternBar=new BARPatternBar(this,name,patternBarColorList[nbPatternCreated % 5]);
        ui->patternBarArea->addWidget(newBarPatternBar);
        nbPatternCreated+=1;
    }
}
