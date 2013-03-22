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

/**
 * @brief Contains the list of the pattern bars.
 * When clicking the "+" button, a new pattern bar is created and added under the last one.
 * There is no "list" in the sense of C++, the bars are just added to the layout upon creation.
 */

/**
 * @brief Constructor.
 * @param[in] parent widget.
 */
BARPatternBarScrollAreaContents::BARPatternBarScrollAreaContents(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARPatternBarScrollAreaContents)
{
    ui->setupUi(this);

    nbPatternCreated=0; /**< when the area is created, no sound bars exist yet, thus this variable is iniated to 0. */
    patternBarColorList.push_back(QColor(255,102,102,255)); /**< the following lines add new colors to the list of colors. This variable is explained in the header file. */
    patternBarColorList.push_back(QColor(255,153,102,255));
    patternBarColorList.push_back(QColor(255,255,51,255));
    patternBarColorList.push_back(QColor(200,200,100,255));
    patternBarColorList.push_back(QColor(120,240,130,255));
}

/**
 * @brief Default destructor.
 */
BARPatternBarScrollAreaContents::~BARPatternBarScrollAreaContents()
{
    delete ui;
}

/**
 * @brief Slots that creates a new pattern bar upon clicking the "+" button.
 */
void BARPatternBarScrollAreaContents::on_buttonAddPatternBar_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Files(*.*)")); /**< open the dialog box to allow the user to selected the pattern they want to import. The path to the file is stored. */
    QFileInfo fi(path); /**< retrieve the entire path to the selected file. */
    QString name=fi.baseName(); /**< extracts the name of the file from the entire path. */

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
    {
        return;}

        BARPatternBar *pBar = static_cast<BARPatternBar*>(childAt(event->pos()));

        QSize patternSize(100,60);
        QPixmap pixmap(patternSize);
        pixmap.fill(pBar->getBgColor());

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << pBar->getBgColor();
        dataStream << pBar->getPatternLength();


        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);
        mimeData->setText(childAt(event->pos())->accessibleName());

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);

        drag->setHotSpot(event->pos() - child->pos());

        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
            child->close();
        else {
            child->show();
        }
}
