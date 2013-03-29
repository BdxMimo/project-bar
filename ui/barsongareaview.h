#ifndef BARSONGAREAVIEW_H
#define BARSONGAREAVIEW_H

#include <QGraphicsView>
#include "barsongareascene.h"

/**
 * @brief Display BARSongAreaScene.
 * BARSongAreaScene is the model of the timeline. This class displays it.
 */

class BARSongAreaView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BARSongAreaView(QWidget *parent = 0);

private:
    BARSongAreaScene *scene; /**< scene of the timeline. */
};

#endif // BARSONGAREAVIEW_H
