#include "barpatternbarscrollareacontents.h"
#include "ui_barpatternbarscrollareacontents.h"
#include <QFileDialog>
#include <QFileInfo>
#include "barpatternbar.h"
#include <QLabel>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QDebug>

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

void BARPatternBarScrollAreaContents::mousePressEvent(QMouseEvent *event)
{
    int x=event->pos().x();

    QLabel *child= static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
    {qDebug() <<childAt(event->pos())->accessibleName()<<endl;
        return;}
    else
    {qDebug() <<"objet"<<endl;
    qDebug() <<childAt(event->pos())->accessibleName()<<endl;}
      //  QPixmap pixmap = *child->pixmap();

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << QPoint(event->pos() - child->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);

        drag->setHotSpot(event->pos() - child->pos());





        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
            child->close();
        else {
            child->show();

        }
}
