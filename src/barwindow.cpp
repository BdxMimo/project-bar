#include "barwindow.h"
#include "ui_barwindow.h"

BARWindow::BARWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARWindow)
{
    ui->setupUi(this);
}

BARWindow::~BARWindow()
{
    delete ui;
}
