#include "barsongareaview.h"

/**
 * @brief Display BARSongAreaScene.
 * BARSongAreaScene is the model of the timeline. This class displays it.
 */

/**
 * @brief Constructor.
 * @param[in] parent widget.
 */
BARSongAreaView::BARSongAreaView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new BARSongAreaScene(); /**< creates the scene of the timeline. */
    this->setScene(scene); /**< adds the scene to our instance, so that it is displayed. */
    setAcceptDrops(true); /**< allows drag-and-drops to be done on the timeline. */
}
