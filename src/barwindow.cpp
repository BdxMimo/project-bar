#include "barwindow.h"
#include "ui_barwindow.h"
#include <QString>
#include <QFileDialog>

/**
 * @brief Constuctor of the main window.
 *
 * Nothing special in this constuctor. The TabWidget has been created through QtDesigner (see UI file).
*/
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
