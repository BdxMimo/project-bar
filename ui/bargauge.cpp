#include "bargauge.h"
#include "ui_bargauge.h"
#include <QPalette>

/**
 * @brief Implements the gauge played in the "pattern" tab.
 * This gauge controls when a sound is played, and at which volume.
 * A series of gauges is created in each soundbar, by the constructor of the class "barsoundbar".
 */

/**
 * @brief Constructor.
 * @param[in] parent widget.
 */
BARGauge::BARGauge(unsigned int i, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BARGauge)
{
    ui->setupUi(this);

    volume=0; /**< gauge volume is iniated as inactive : thus volume value is 0. */
    offColor=QColor(255,255,255,200); /**< define the color of the gauge when inactive (clicked). */
    onColor=QColor(0,0,255,127); /**< define the color of the gauge when active (clicked). */
    iNote = i;

    QPalette palette = this->palette();
    palette.setColor(QPalette::Background,offColor); /**< gauge is iniated as inactive : the corresponding color is set upon creation of the gauge. */
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    this->setFixedSize(20,50); /**< size of the gauge is fixed to make sure it is always visible and clickable. */
}

/**
 * @brief Default destructor.
 */
BARGauge::~BARGauge()
{
    delete ui;
}

/**
 * @brief This slot change the state of the clicked gauge (inactive <-> active).
 * @param[in] Mouse pressed event.
 */
void BARGauge::mousePressEvent(QMouseEvent *event)
{
    volume=100-volume; /**< Reverses the volume of the gauge to activate/inactivate it. Temporary implementation for the test, where volume is 0 or 1. */

    QPalette palette = this->palette();
    palette.setColor(QPalette::Background,volume == 0 ? offColor : onColor);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    emit valueChanged(volume, iNote);
}
