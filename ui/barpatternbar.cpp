#include "barpatternbar.h"
#include "ui_barpatternbar.h"


BARPatternBar::BARPatternBar(QWidget *parent, QString name, QColor color) :
    QWidget(parent),
    ui(new Ui::BARPatternBar)
{
    ui->setupUi(this);
    patternLength=1;

    setAcceptDrops(true);

    fileName=name;
    this->setAccessibleName(fileName);
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

QString BARPatternBar::getFileName()
{
    return fileName;
}

QColor BARPatternBar::getBgColor()
{
    return bgColor;
}

int BARPatternBar::getPatternLength()
{
    return patternLength;
}

/*
void BARPatternBar::mousePressEvent(QMouseEvent *event)
{
    int x=event->pos().x();


    if (!child)
    {qDebug() <<fileName<<endl;
        return;}
    else
    {qDebug() <<childAt(event->pos())->whatsThis()<<endl;

    }

qDebug() <<fileName<<endl;
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << QPoint(event->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);
        mimeData->setText(fileName);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);

        drag->setHotSpot(event->pos());








}
*/
