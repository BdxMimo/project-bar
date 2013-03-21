#include "bartabsong.h"
#include "ui_bartabsong.h"
#include "barpatternbar.h"
#include <QGraphicsRectItem>


BARTabSong::BARTabSong(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARTabSong),
    dialog(this)
{
    ui->setupUi(this);


}

BARTabSong::~BARTabSong()
{
    delete ui;
}


void BARTabSong::on_buttonExport_clicked()
{
    dialog.show();
}
