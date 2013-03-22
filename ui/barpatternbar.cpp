#include "barpatternbar.h"
#include "ui_barpatternbar.h"

/**
 * @brief Creates the pattern bar in the "song" tab.
 * Each bar is associated to one pattern.
 * A new bar is added in the left column of "barpatternbarscrollarea", under the last pattern bar, when clicking the "+" button under it.
 */

/**
 * @brief Constructor.
 * @param[in] parent widget.
 * @param[in] name of the pattern associated to the bar.
 * @param[in] color to be set to the bar.
 */
BARPatternBar::BARPatternBar(QWidget *parent, QString name, QColor color) :
    QWidget(parent),
    ui(new Ui::BARPatternBar)
{
    ui->setupUi(this);
    patternLength=1; /**< during development of the interface, duration is set to 1 by default (since no pattern is actually loaded yet). */

    setAcceptDrops(true); /**< allows drag-and-drop operations. This way it will be possible to drag the bar to the timeline in order to create the final song. */

    fileName=name; /**< sets the name of the pattern associated to the bar. */
    this->setAccessibleName(fileName); /**< modify the name by which Qt identifies the object to correspond to the name of the pattern associated to the bar. */
    ui->labelPatternName->setText(fileName); /** updates pattern name on the tag. */

    bgColor=color; /**< in the following lines, the color of the bar is set according to one given to the constructor. */
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background,bgColor);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

/**
 * @brief Default destructor.
 */
BARPatternBar::~BARPatternBar()
{
    delete ui;
}

/**
 * @brief Returns the name of the pattern associated to the bar.
 * @return Name of the pattern associated to the bar.
 */
QString BARPatternBar::getFileName()
{
    return fileName;
}

/**
 * @brief Returns the color of the bar.
 * @return Color of the bar.
 */
QColor BARPatternBar::getBgColor()
{
    return bgColor;
}

/**
 * @brief Returns duration of the pattern associated to the bar.
 * @return Duration of the pattern associated to the bar.
 */
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
