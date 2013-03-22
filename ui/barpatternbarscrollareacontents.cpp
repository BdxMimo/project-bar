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

    if(name!="") /**< prevents the creation of a bar associated to no pattern, in case the user closes dialog box without selecting any file. */
    {
        BARPatternBar *newBarPatternBar=new BARPatternBar(this,name,patternBarColorList[nbPatternCreated % 5]); /**< the color of the new bar is selected in the list of possible colors. Modulo allows to create more bars than the number of possible colors. */
        ui->patternBarArea->addWidget(newBarPatternBar); /**< the new bar is added to the layout in last position. */
        nbPatternCreated+=1; /**< counter of number of pattern bars stored in the layout is updated. */
    }
}

/**
 * @brief Slot triggers drag-and-drop.
 * The user start draging the pattern he wants to add to the timeline.
 * @param[in] mouse pressed event.
 */
void BARPatternBarScrollAreaContents::mousePressEvent(QMouseEvent *event)
{
    int x=event->pos().x(); /**< retrieves the position of the cursor. */

    BARPatternBar *pBar = static_cast<BARPatternBar*>(childAt(event->pos())); /**< childAt returns a pointer to the child that was clicked. This pointer, of type "widget", is then converted into a BARPatternBar type. */
    if (!pBar){return;} /**< checks that the object created isn't empty (NULL). */

    QSize patternSize(100,60); /**< the following lines created a pixmap that will be displayed on the cursor during drag-and-drop. */
    QPixmap pixmap(patternSize);
    pixmap.fill(pBar->getBgColor());

    QByteArray itemData; /**< the following lines pack up the data to be sent through the drag-and-drop. */
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pBar->getBgColor(); /**< stores the color of the bar being dragged. */
    dataStream << pBar->getPatternLength(); /**< stores the duration of the pattern associated to the bar being dragged. */

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData); /**< store the data we prepared into the QMimeFile. */
    mimeData->setText(childAt(event->pos())->accessibleName()); /**< store the name of the pattern associated to the bar being dragged. */

    QDrag *drag = new QDrag(this); /**< crates the QDrag object. */
    drag->setMimeData(mimeData); /**< stores the data we packed up into the drag object. */
    drag->setPixmap(pixmap); /**< sets the image to be displayed on the cursor during the drag-and-drop. */

    drag->setHotSpot(event->pos() - pBar->pos()); /**< actually displays the pixmap on the cursor during drag-and-drop. */

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction){pBar->close();} /**< lines found on the Internet... */
    else {pBar->show();}
}
