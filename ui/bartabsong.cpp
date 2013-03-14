#include "bartabsong.h"
#include "ui_bartabsong.h"
#include "barpatternbar.h"
#include <QGraphicsRectItem>


BARTabSong::BARTabSong(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARTabSong)
{
    ui->setupUi(this);

    nbPatternCreated=0;
    patternBarColorList.push_back(QColor(255,102,102,255));
    patternBarColorList.push_back(QColor(255,153,102,255));
    patternBarColorList.push_back(QColor(255,255,51,255));
    patternBarColorList.push_back(QColor(200,200,100,255));
    patternBarColorList.push_back(QColor(120,240,130,255));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::white);
    QPen blackPen(Qt::black);

    blackPen.setWidth(1);
    for(int i=0;i<50;i++)
    {
        QGraphicsRectItem *rectangle=new QGraphicsRectItem(i*100,0,100,60);
        QGraphicsTextItem *label=new QGraphicsTextItem(QString::number(i));
        label->setPos(i*100-5,-25);
                rectangle->setBrush(redBrush);
                rectangle->setPen(blackPen);
                scene->addItem(rectangle);
                scene->addItem(label);
                stock.push_back(rectangle);
    }

}

BARTabSong::~BARTabSong()
{
    delete ui;
}

void BARTabSong::on_buttonAddPatternBar_clicked()
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
