#ifndef GROUND_H
#define GROUND_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QBrush>
#include <Box2D/Box2D.h>
#include <iostream>

//header files
#include "game.h"

class Ground: public QGraphicsRectItem {
public:
    //Constructor
    Ground (int x, int y, int w, int h, QGraphicsItem *parent=0);

    //Public Methods
    void initGround(b2World *world, float x, float y);
    int getWidth();
    int getHeight();
private:
    int gWidth;
    int gHeight;
};

#endif // GROUND_H
